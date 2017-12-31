import os
import yaml
import itertools
from bs4 import BeautifulSoup

paths = {
        'config' : '../config/device_config.yml',
        'locations' : '../config/device_locations.yml',
        'aliases' : '../config/psoc_aliases.yml',
        'master' : '../config/master_component_list.yml',
        'project' : '../master.cydsn',
        'dwr' : '../master.cydsn/master.cydwr'
        }

class CypressBuilder():
    def __init__(self):
        self.paths = paths

        # Initialize dicts
        self.config = {}
        self.locations = {}
        self.docs = {}
        self.protocol_docs = {}
        self.devices = {}
        self.aliases = {}
        self.master = {}

        # Read config info
        self._read_config()

        # Construct master component list
        self.master_component_list = []
        for subsystem in self.master:
            self.master_component_list.extend(self.master[subsystem]['base'])
            self.master_component_list.extend(self.master[subsystem]['peripheral'])

        self._generate_private_components()
        self._generate_global_components()

        # Get all enabled components
        self.enabled_components = self.enabled_global_components + self.enabled_private_components

        # Generate params for param file
        self._generate_params()

    def _read_config(self):
        # Read board configuration
        with open(self.paths['config'], 'r') as stream:
            self.config.update(yaml.load(stream))

        # Get locations of sensor documents
        with open(self.paths['locations'], 'r') as stream:
            self.locations.update(yaml.load(stream))

        # Get PSoC aliases
        with open(self.paths['aliases'], 'r') as stream:
            self.aliases.update(yaml.load(stream))

        # Get master components
        with open(self.paths['master'], 'r') as stream:
            self.master.update(yaml.load(stream))


    def _generate_private_components(self):
        # Determine device-specific requirements
        private_component_list = []
        self.private_components = {}
        device_ids = []
        for device in self.config['external']:
            # Get device id
            device_id = device['identifier']
            # Account for duplicate devices
            instance_name = device_id + ':{0}'.format(device_ids.count(device_id))
            device_ids.append(device_id)
            protocol = device['communication_protocol']
            sensor_path = self.locations[device_id]
            self.docs.update({device_id : {}})
            # Load full sensor config file
            with open(sensor_path, 'r') as stream:
                self.docs[device_id].update(yaml.load(stream))
            protocol_info = self.docs[device_id]['supported_communication_protocols'][protocol]
            self.protocol_docs[instance_name] = protocol_info
            components = protocol_info['components']
            component_info = {}
            for component in components:
                count = private_component_list.count(component)
                port = device['pins'][component]
                component_info.update({component : {'count' : count,
                                                    'port' : port}})
            private_component_list.extend(components)
            self.private_components.update({instance_name : component_info})

        self.enabled_private_components = []
        for component_dict in self.private_components.values():
            components = ['{0}_{1}'.format(k, v['count']) for k, v in
                        component_dict.items()]
            self.enabled_private_components.extend(components)

    def _generate_global_components(self):
        # Determine global components needed
        protocols = []
        for components in self.private_components.values():
            if 'power' in components:
                protocols.append('power')
                break
        for device in self.config['external']:
            protocols.append(device['communication_protocol'])
        self.global_components = [self.aliases['protocols'].setdefault(protocol, protocol)
                                  for protocol in protocols]
        global_components_set = set(self.global_components)
        self.enabled_global_components = [self.master[component]['base'] for
                                          component in global_components_set]
        self.enabled_global_components = list(itertools.chain.from_iterable(
                                            self.enabled_global_components))

    def _generate_params(self):
        # Generate params file
        self.params_list = []
        self.params_dict = {component : ({'CY_REMOVE' : 'false', 'CY_SUPPRESS_API_GEN' : 'false'}
                                    if component in self.enabled_components else
                                    {'CY_REMOVE' : 'true', 'CY_SUPPRESS_API_GEN' : 'true'})
                    for component in self.master_component_list}
        for instance, params in self.params_dict.items():
            self.params_list.append("inst_name={0}".format(instance))
            for param, value in params.items():
                self.params_list.append("{0}={1}".format(param, value))
            self.params_list.append("\n")

    def write_params_file(self):
        # Write params file
        params_file_path = os.path.join(self.paths['project'], 'params')
        param_lines = '\n'.join(self.params_list)
        with open(params_file_path, 'w') as params_file:
            params_file.write(param_lines)

    def _modify_dwr(self):
        #### This needs to be done after building the project with the params file
        #### because there's no other way to know the key for each pin

        # Get desired pins from config file
        desired_pins = {}
        for component, subcomponents in self.private_components.items():
            for subcomponent, info in subcomponents.items():
                component_name = "{0}_{1}".format(subcomponent, info['count'])
                port = info['port']
                desired_pins[component_name] = port

        # Read design-wide resources
        with open(self.paths['dwr']) as infile:
            x = ''.join(infile.readlines())

        # Parse XML
        s = BeautifulSoup(x, 'lxml')

        # Get pin ids
        # TODO: This does not capture internal pins
        pins = {}
        pin_ids = s.find('group', key='Pin')
        pin_ids = pin_ids.find_all('data')
        for pin in pin_ids:
            pins[pin['value']] = pin['key']

        # Write ports
        pin_ports = s.find('group', key='Pin2')
        unassigned = pin_ports.find('group', key='UnAssigned Pins')

        for pin_name, pin_id in pins.items():
            assigned_pin = pin_ports.find('group', key=pin_id)
            unassigned_pin = unassigned.find('group', key=pin_id)
            if unassigned_pin:
                print(unassigned_pin)
                unassigned_pin.decompose()
                newgroup = s.new_tag('group', key=pin_id)
                unassigned.insert_before(newgroup)
                new_innergroup = s.new_tag('group', key="0")
                newgroup.append(new_innergroup)
                newdata = s.new_tag('data', key='Port Format', value='69,420')
                new_innergroup.append(newdata)
            elif assigned_pin:
                print(assigned_pin)
                existing_entry = assigned_pin.find('data')
                existing_entry['value'] = '420,69'

        # Does this need to be done?
        unassigned.decompose()
        print(pin_ports.prettify())

        # Write design wide resources file
        ########

if __name__ == "__main__":
    builder = CypressBuilder()
    builder.write_params_file()
    # Need to edit includes and driver files here
    # Need to build project here
    builder._modify_dwr()
