import yaml
import itertools
from bs4 import BeautifulSoup

config_path = 'device_config.yml'
locations_path = 'device_locations.yml'
alias_path = 'psoc_aliases.yml'
master_path = 'master_component_list.yml'
project_path = ''
dwr_path = '/Users/mdbartos/Git/perfect-cell/perfect-cell.cydsn/perfect-cell.cydwr'

# Read config info
config = {}
locations = {}
docs = {}
protocol_docs = {}
devices = {}
aliases = {}
master = {}

# Read board configuration
with open(config_path, 'r') as stream:
    config.update(yaml.load(stream))

# Get locations of sensor documents
with open(locations_path, 'r') as stream:
    locations.update(yaml.load(stream))

# Get PSoC aliases
with open(alias_path, 'r') as stream:
    aliases.update(yaml.load(stream))

# Get master components
with open(master_path, 'r') as stream:
    master.update(yaml.load(stream))
master_component_list = []
for subsystem in master:
    master_component_list.extend(master[subsystem]['base'])
    master_component_list.extend(master[subsystem]['peripheral'])

# Determine device-specific requirements
private_component_list = []
private_components = {}
device_ids = []
for device in config['external']:
    # Get device id
    device_id = device['identifier']
    # Account for duplicate devices
    instance_name = device_id + ':{0}'.format(device_ids.count(device_id))
    device_ids.append(device_id)
    protocol = device['communication_protocol']
    sensor_path = locations[device_id]
    docs.update({device_id : {}})
    # Load full sensor config file
    with open(sensor_path, 'r') as stream:
        docs[device_id].update(yaml.load(stream))
    protocol_info = docs[device_id]['supported_communication_protocols'][protocol]
    protocol_docs[instance_name] = protocol_info
    components = protocol_info['components']
    component_info = {}
    for component in components:
        count = private_component_list.count(component)
        port = device['pins'][component]
        component_info.update({component : {'count' : count,
                                            'port' : port}})
    private_component_list.extend(components)
    private_components.update({instance_name : component_info})

enabled_private_components = []
for component_dict in private_components.values():
    components = ['{0}_{1}'.format(k, v['count']) for k, v in
                  component_dict.items()]
    enabled_private_components.extend(components)

# Determine global components needed
protocols = []
for components in private_components.values():
    if 'power' in components:
        protocols.append('power')
        break
for device in config['external']:
    protocols.append(device['communication_protocol'])
global_components = [aliases['protocols'].setdefault(protocol, protocol)
                     for protocol in protocols]
global_components_set = set(global_components)
enabled_global_components = [master[component]['base'] for
                          component in global_components_set]
enabled_global_components = list(itertools.chain.from_iterable(
    enabled_global_components))

# Get all enabled components
enabled_components = enabled_global_components + enabled_private_components

# Generate params file
params_list = []
params_dict = {component : ({'CY_REMOVE' : 'false', 'CY_SUPPRESS_API_GEN' : 'false'}
                            if component in enabled_components else 
                            {'CY_REMOVE' : 'true', 'CY_SUPPRESS_API_GEN' : 'true'})
               for component in master_component_list}
for instance, params in params_dict.items():
    params_list.append("inst_name={0}".format(instance))
    for param, value in params.items():
        params_list.append("{0}={1}".format(param, value))
    params_list.append("\n")

# Write params file
########

#### This needs to be done after building the project with the params file
#### because there's no other way to know the key for each pin

# Get desired pins from config file
desired_pins = {}
for component, subcomponents in private_components.items():
    for subcomponent, info in subcomponents.items():
        component_name = "{0}_{1}".format(subcomponent, info['count'])
        port = info['port']
        desired_pins[component_name] = port

# Read design-wide resources
with open(dwr_path) as infile:
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

