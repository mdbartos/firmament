import os
import subprocess
import itertools
import yaml
from bs4 import BeautifulSoup

try:
    filepath = __file__
    parent_path = os.path.abspath(os.path.join(
        os.path.abspath(os.path.join(
            os.path.realpath(filepath),os.pardir)),
        os.pardir))
except:
    filepath = os.path.realpath(os.curdir)

# TODO: Fix bad relative paths
paths = {
        'config' : '../config/device_config.yml',
        'locations' : '../config/device_locations.yml',
        'aliases' : '../config/psoc_aliases.yml',
        'master' : '../config/master_component_list.yml',
        'protocols' : '../config/protocols.yml',
        'project' : '../master.cydsn',
        'workspace' : '../master.cywrk',
        'cyprjmgr' : 'c://Program Files (x86)/Cypress/PSoC Creator/4.1/PSoC Creator/bin/cyprjmgr.exe',
        'dwr' : '../master.cydsn/master.cydwr',
        'params' : '../master.cydsn/params',
        'globals' : '../master.cydsn/peripheral_globals.h',
        'instances' : '../master.cydsn/peripheral_instances.h',
        'calls' : '../master.cydsn/peripheral_calls.c',
        }

project_name = 'master'

class CypressBuilder():
    def __init__(self):
        self.paths = paths
        self.project_name = project_name

        # Initialize dicts
        self.config = {}
        self.locations = {}
        self.docs = {}
        self.instances = {}
        self.protocols = {}
        self.aliases = {}
        self.master = {}

        # Read config info
        self._read_config()

        # Construct master component list
        self.master_component_list = []
        for subsystem in self.master:
            self.master_component_list.extend(self.master[subsystem]['base'])
            if 'peripheral' in self.master[subsystem]:
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

        # Get protocol info
        with open(self.paths['protocols'], 'r') as stream:
            self.protocols.update(yaml.load(stream))

    def _generate_private_components(self):
        # Determine device-specific requirements
        # TODO: Separate building instance dict from private components
        # TODO: Private components can be rolled into instances
        private_component_list = []
        self.private_components = {}
        device_ids = []
        for device in self.config['external']:
            # Get device id
            device_id = device['identifier']
            # Account for duplicate devices
            instance_number = device_ids.count(device_id)
            instance_name = device_id + ':{0}'.format(instance_number)
            device_ids.append(device_id)
            protocol = device['communication_protocol']
            sensor_path = self.locations[device_id]
            self.docs.update({device_id : {}})
            # Load full sensor config file
            with open(sensor_path, 'r') as stream:
                self.docs[device_id].update(yaml.load(stream))
            protocol_info = self.docs[device_id]['supported_communication_protocols'][protocol]
            self.instances[instance_name] = protocol_info
            self.instances[instance_name]['meta'] = {}
            self.instances[instance_name]['meta'].update({'instance_number' :
                                                          instance_number})
            device_alias = self.docs[device_id]['alias']
            instance_alias = '_'.join((str(item) for item in (device_alias, protocol,
                                       instance_number)))
            self.instances[instance_name]['meta'].update({'instance_alias' :
                                                          instance_alias})
            self.instances[instance_name]['meta'].update({'protocol' :
                                                           protocol})
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
        # TODO: Rename enabled_global_components to enabled_base_components
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
        # TODO: Right now this is only set up to enable or disable components
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
        param_lines = '\n'.join(self.params_list)
        with open(self.paths['params'], 'w') as params_file:
            params_file.write(param_lines)

    def build_project(self, commands, params=False, **kwargs):
        cmd_list = [self.paths['cyprjmgr'], '-wrk', self.paths['workspace'], '-prj',
                self.project_name]
        cmd_list.extend(commands)
        if params:
            cmd_list.extend(['-m', self.paths['params']])
        print(' '.join(cmd_list))
        result = subprocess.call(cmd_list)
        return result

    def write_globals_file(self):
        head = ["#ifndef PERIPHERAL_GLOBALS_H",
                "#define PERIPHERAL_GLOBALS_H"]
        tail = ["#endif", "/* [] END OF FILE */"]
        body = []
        body.extend(head)
        body.append('\n')
        activated_global_components = set(self.global_components)
        for global_component in self.master:
            if global_component in activated_global_components:
                activated = 1
            else:
                activated = 0
            define_str = ("#define {0}_ACTIVATED {1}u"
                          .format(global_component.upper(), activated))
            body.append(define_str)
        body.append('\n')
        for device in self.instances:
            # Get alias
            instance_alias = self.instances[device]['meta']['instance_alias']

            # Check for attached components
            subcomponents = self.private_components[device]
            for subcomponent in subcomponents:
                param_value = subcomponents[subcomponent]['count']
                define_str = ("#define {0}_{1} {2}"
                                .format(instance_alias.upper(),
                                        subcomponent.upper(), param_value))
                body.append(define_str)

            # Define device params
            dynamic_params = self.instances[device]['dynamic']
            for param, value in dynamic_params.items():
                if hasattr(value, "__len__") and not isinstance(value, str):
                    for num, item in enumerate(value):
                        if isinstance(item, str):
                            item = '"' + item.encode('unicode_escape').decode('ascii') + '"'
                        define_str = ("#define {0}_{1}_{2} {3}"
                                    .format(instance_alias.upper(),
                                            param.upper(), num,
                                            item))
                        body.append(define_str)
                else:
                    if isinstance(value, str):
                        value = '"' + value + '"'
                    define_str = ("#define {0}_{1} {2}"
                                  .format(instance_alias.upper(), param.upper(), value))
                    body.append(define_str)
            body.append('\n')
        body.extend(tail)
        body = '\n'.join(body)
        with open(paths['globals'], 'w') as globals_file:
            globals_file.write(body)

    def write_instances_file(self):
        head = ["#ifndef PERIPHERAL_INSTANCES_H",
                "#define PERIPHERAL_INSTANCES_H",
                '\n',
                '#include "peripheral_globals.h"',
                '#include "device_dict.h"']
        tail = ["#endif", "/* [] END OF FILE */"]
        body = []
        body.extend(head)
        body.append('\n')
        for device in self.instances:
            # Get alias
            instance_alias = self.instances[device]['meta']['instance_alias']
            nvars = self.instances[device]['dynamic']['nvars']
            protocol = self.instances[device]['meta']['protocol']
            base_protocol = self.aliases['protocols'][protocol]
            protocol_info = self.protocols[base_protocol]
            for array in protocol_info['dynamic_memory']:
                dtype = protocol_info['dynamic_memory'][array]['type']
                nvars_str = "{0}_NVARS".format(instance_alias.upper())
                # TODO: Messy implementation
                if array == 'reading':
                    array_elem = 'default'.upper()
                else:
                    array_elem = array.upper()
                array_elems = ', '.join(("{0}_{1}_{2}"
                                         .format(instance_alias.upper(),
                                                 array_elem,
                                                 num)
                                                 for num in range(nvars)))
                define_str = ("{0} {1}_{2}[{3}] = {{{4}}};"
                              .format(dtype, instance_alias,
                                      array, nvars_str, array_elems))
                body.append(define_str)
            struct_head = "static DeviceDict {0} = \n{{".format(instance_alias)
            body.append(struct_head)
            for param, struct_label in protocol_info['struct_elems'].items():
                if param in protocol_info['dynamic_memory']:
                    ptr_flag = '&'
                    value = "{0}_{1}".format(instance_alias, param)
                else:
                    ptr_flag = ''
                    value = "{0}_{1}".format(instance_alias.upper(), param.upper())
                define_str = "    .{0} = {1}{2},".format(struct_label, ptr_flag,
                                                        value)
                body.append(define_str)
            struct_tail = "\n};\n"
            body.append(struct_tail)
        body.extend(tail)
        body = '\n'.join(body)
        with open(paths['instances'], 'w') as instances_file:
            instances_file.write(body)

    def write_calls_file(self):
        head = ['#include "peripheral_globals.h"',
                '#include "peripheral_instances.h"',
                '#include "strlib.h"',
                '#include "public_vars.h"',
                '\n',
                '#if GENERIC_UART_ACTIVATED',
                '    #include "generic_uart_control.h"',
                '#endif',
                '\n',
                '#if ANALOG_DELSIG_ACTIVATED',
                '    #include "analog_delsig_control.h"',
                '#endif',
                '\n',
                '#if I2C_ACTIVATED',
                '    #include "i2c_control.h"',
                '#endif',
                '\n',
                'char *labels[MAIN_BUFFER_LEN] = {0};',
                'float readings[MAIN_BUFFER_LEN] = {0};',
                'int array_ix = 0u;']
        tail = ['/* [] END OF FILE */']
        body = []
        body.extend(head)
        body.append('\n')
        body.append('uint8 run_peripherals(){')
        for device in self.instances:
            # Get alias
            instance_alias = self.instances[device]['meta']['instance_alias']
            protocol = self.instances[device]['meta']['protocol']
            base_protocol = self.aliases['protocols'][protocol]
            define_str = ("    {0}_get_reading({1});"
                          .format(base_protocol, instance_alias))
            body.append(define_str)
        body.append('    return 1u;\n}\n')
        body.append('uint8 zip_peripherals(){')
        for device in self.instances:
            # Get alias
            instance_alias = self.instances[device]['meta']['instance_alias']
            define_str = ("    zip_measurements(labels, readings, {0}, &array_ix, MAIN_BUFFER_LEN);"
                          .format(instance_alias))
            body.append(define_str)
        body.append('    return 1u;\n}\n')
        body.extend(tail)
        body = '\n'.join(body)
        with open(paths['calls'], 'w') as calls_file:
            calls_file.write(body)


    def modify_dwr(self):
        # Get desired pins from config file
        desired_pins = {}
        for component, subcomponents in self.private_components.items():
            for subcomponent, info in subcomponents.items():
                component_name = "{0}_{1}".format(subcomponent, info['count'])
                port = info['port']
                desired_pins[component_name] = port

        # Read design-wide resources
        with open(self.paths['dwr']) as dwr_file:
            x = ''.join(dwr_file.readlines())

        # Parse XML
        s = BeautifulSoup(x, 'xml')

        # Get pin ids
        # TODO: This does not capture internal pins
        pins = {}
        pin_group = s.find('group', key='Pin')
        pin_ids = pin_group.find_all('data')
        # TODO: This does not account for duplicately-named pins
        for pin in pin_ids:
            pins[pin['value']] = pin['key']

        # Write ports
        pin_ports = s.find('group', key='Pin2')
        unassigned = pin_ports.find('group', key='UnAssigned Pins')

        for pin_name, pin_id in pins.items():
            assigned_pin = pin_ports.find('group', key=pin_id)
            unassigned_pin = unassigned.find('group', key=pin_id)
            if pin_name in desired_pins:
                pin_port = desired_pins[pin_name]
                if unassigned_pin:
                    print(unassigned_pin)
                    unassigned_pin.decompose()
                    newgroup = s.new_tag('group', key=pin_id)
                    unassigned.insert_before(newgroup)
                    new_innergroup = s.new_tag('group', key="0")
                    newgroup.append(new_innergroup)
                    newdata = s.new_tag('data', key='Port Format', value=pin_port)
                    new_innergroup.append(newdata)
                elif assigned_pin:
                    print(assigned_pin)
                    existing_entry = assigned_pin.find('data')
                    existing_entry['value'] = pin_port
            # Remove pin if it wasn't specified in config
            else:
                extraneous_entry = pin_group.find('data', key=pin_id)
                extraneous_entry.decompose()

        # Write design wide resources file
        with open(paths['dwr'], 'w') as dwr_file:
            dwr_file.write(s.prettify())

if __name__ == "__main__":
    builder = CypressBuilder()
    builder.write_params_file()
    builder.write_globals_file()
    builder.write_instances_file()
    builder.write_calls_file()
    builder.build_project(commands=['-build'], params=True)
    builder.modify_dwr()
    builder.build_project(commands=['-rebuild'], params=False)

