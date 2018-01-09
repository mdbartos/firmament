# firmament

**firmament** is a document-based platform for automated sensor firmware generation.

## Principle

**firmament** generates sensor and actuator drivers for use in embedded systems.
The code generator uses two types of documents: *driver* documents and *configuration* documents.
These documents can be formatted as sensorML, or as a simplified yaml document.

### Driver documents

Driver documents are used to generate drivers for individual sensors or actuators.
These documents provide information about the sensor's communication protocols, and describe any information needed to intepret the data stream.
An example (in simplified yaml format) is shown below:

```yaml
# Component description
identifier : "urn:maxbotix:mb7383"
manufacturer : "Maxbotix"
name : "MB7383 HRXL-MaxSonar-WRLST"
description : "High performance ultrasonic rangefinder"
alias : "mb7383"

# Communications
firmware:
    ttl:
        static:
            data_bits : 8
            parity : "none"
            parity_api_control : 0
            stop_bits : 1
            flow_control : "none"
            logic_level : "high"
        dynamic:
            baud : 9600
            on_time : 800
            buffer_len : 5
            nvars : 1
            skipchars : 86
            str_start :
                - "\rR"
            str_end :
                - "\r"
            label :
                - "maxbotix_depth"
            invalid :
                - 9999
            default :
                - -9999
        components:
            - "generic_uart_rx"
            - "power"
```

Example yaml driver documents can be found in `firmament/peripherals/yaml`

Example sensorml driver documents can be found in `firmament/peripherals/sensorml

### Configuration document

A single configuration document is used to specify desired sensors, desired communication protocols, and the ports that they will use.

```yaml
platform: 'cypress'
external:
    - identifier : "urn:maxbotix:mb7383"
      communication_protocol : "ttl"
      pins:
          power : '12,6'
          generic_uart_rx : '12,7'
    - identifier : 'urn:battery_internal'
      communication_protocol : 'analog_delsig'
      pins:
          power : '12,1'
          analog_delsig_signal : '0,0'
```

An example configuration document can be found in `firmament/device_config.yml`

## Installation

### Cloning from github

```bash
git clone https://github.com/mdbartos/firmament
```

## Running the code generator (Cypress devices)

Navigate to the root directory of the repo and run:

```bash
python firmament/build/cypress.py firmament/device_config.yml
```

This will generate and compile the firmware into a binary. This binary can be flashed to a Cypress PSoC device using PSoC Creator or PSoC Programmer.

Note that only Python 3 is supported.

### Dependencies

- Python libraries:
  - pyyaml
  - lxml
  - BeautifulSoup4
- PSoC Creator 4.1 or greater

## Supported communication protocols

**firmament** currently supports:

- Analog
- TTL
- RS-232
- RS-485
- I2C

## Supported hardware platforms

**firmament** currently only supports Cypress PSoC devices.

Integration with Arduino and Raspberry Pi is planned.
