# firmament

**firmament** is a document-based platform for automated sensor firmware generation.

## Installation

### Cloning from github

```bash
git clone https://github.com/mdbartos/firmament
```

## Running the code generator

Navigate to the root directory of the repo and run:

```bash
python cypress/prebuild/cypress_prebuild.py
```

Note that only Python 3 is supported.

### Dependencies

- Python libraries:
  - pyyaml
  - lxml
  - BeautifulSoup4
- PSoC Creator 4.1 or greater

## Supported hardware platforms

**firmament** currently only supports Cypress PSoC devices.

Integration with Arduino and Raspberry Pi is planned.
