import re
import copy
from bs4 import BeautifulSoup as Soup

class SensorMLParser():
    def __init__(self):
        self.tree = {}
        self.toplevel(s, self.tree, 'characteristics', 'CharacteristicList',
                'characteristic')
        self.toplevel(s, self.tree, 'identification', 'IdentifierList',
                'identifier')
        self.toplevel(s, self.tree, 'capabilities', 'CapabilityList',
                'capability')

    def toplevel(self, souptag, d, class_tag, list_tag, element_tag):
        souptag = souptag.find(class_tag)
        d.update({class_tag : {}})
        souptag = souptag.find(list_tag)
        d[class_tag].update({list_tag : {}})
        souptag = souptag.find(element_tag)
        while souptag:
            if 'name' in souptag.attrs:
                element_name = souptag.attrs['name']
                d[class_tag][list_tag].update({element_name : {}})
                pass_d = d[class_tag][list_tag][element_name]
            else:
                pass_d = d[class_tag][list_tag]
            getattr(self, element_tag)(souptag,
                                       pass_d)
            souptag = souptag.find_next_sibling(element_tag)

    def identifier(self, souptag, d):
        souptag = souptag.find('Term')
        self.term(souptag, d)

    def term(self, souptag, d):
        id_name = souptag.attrs['name']
        value = souptag.find('value').get_text()
        d.update({id_name : value})

    def characteristic(self, souptag, d):
        souptag = souptag.find('DataRecord')
        while souptag:
            # If multiple datarecords, need labels
            self.datarecord(souptag, d)
            souptag = souptag.find_next_sibling()

    def capability(self, souptag, d):
        self.characteristic(souptag, d)

    def datarecord(self, souptag, d, **kwargs):
        souptag = souptag.find('field')
        while souptag:
            self.field(souptag, d, **kwargs)
            souptag = souptag.find_next_sibling('field')

    def field(self, souptag, d, declaration=False):
        fieldname = souptag.attrs['name']
        print(fieldname)
        typetag = souptag.find()
        typename = typetag.name.lower()
        d.update({fieldname : {}})
        d[fieldname].update({'type' : typename})
        if not declaration:
            getattr(self, typename)(souptag, d[fieldname])

    def count(self, souptag, d):
        souptag = souptag.find('value')
        value = int(souptag.get_text())
        d.update({'value' : value})

    def quantity(self, souptag, d):
        souptag = souptag.find('value')
        value = float(souptag.get_text())
        d.update({'value' : value})

    def text(self, souptag, d):
        souptag = souptag.find('value')
        value = souptag.get_text()
        d.update({'value' : value})

    def _str_to_bool(self, value):
        value = value.lower()
        if value in ('true', '1'):
            return True
        elif value in ('false', '0'):
            return False
        else:
            raise ValueError("Boolean value must be 'true' or 'false'")

    def _type_handler(self, value, dtype):
        dtype = dtype.lower()
        if dtype == 'text':
            return str(value)
        elif dtype == 'boolean':
            return self._str_to_bool(value)
        elif dtype == 'count':
            return int(value)
        elif dtype == 'quantity':
            return float(value)

    def boolean(self, souptag, d):
        souptag = souptag.find('value')
        value = self._str_to_bool(souptag.get_text().lower())
        d.update({'value' : value})

    def category(self, souptag, d):
        self.text(souptag, d)

    def datastream(self, souptag, d):
        elemtype = souptag.find('elementType')
        declarations = elemtype.find('DataRecord')
        self.datarecord(declarations, d, declaration=True)
        field_labels = [field.attrs['name'] for field in declarations.find_all('field')]
        for label in field_labels:
            d[label].update({'value' : []})
        encoding = souptag.find('encoding')
        text_encoding = encoding.find('TextEncoding')
        block_separator = text_encoding.attrs['blockSeparator']
        token_separator = text_encoding.attrs['tokenSeparator']
        # TODO: Not implemented
        decimalseparator = (text_encoding.attrs
                               .setdefault('decimalSeparator', '.'))
        # TODO: Not implemented
        collapsewhitespaces = (self._str_to_bool(text_encoding.attrs
                               .setdefault('collapseWhiteSpaces', 'true')))
        raw_values = souptag.find('values').get_text()  
        blocks = raw_values.split(block_separator)
        for block in blocks:
            tokens = block.split(token_separator)
            for label, token in zip(field_labels, tokens):
                typename = d[label]['type']
                tokenvalue = self._type_handler(token, typename)
                d[label]['value'].append(tokenvalue)

    def quantityrange(self, souptag, d):
        souptag = souptag.find('value')
        values = souptag.get_text().lower()
        value_list = [float(value) for value in values.split()]
        d.update({'value' : value_list})


sensor = 'maxbotix_mb7383.xml'
desired_protocol = 'ttl'

with open('maxbotix_mb7383.xml', 'r') as infile:
    x = ''.join(infile.readlines())
s = Soup(x, 'xml')

parser = SensorMLParser()

parser.tree = parser._extract_values(parser.tree, term='value')
keylist = ['CharacteristicList', 'firmwareProtocols', 'ttl', 'DriverProperties', 'ParsingLogic']
collapse_level(parser.tree, keylist)
