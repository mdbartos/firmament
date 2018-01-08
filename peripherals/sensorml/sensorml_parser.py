from bs4 import BeautifulSoup as Soup

class SensorMLParser():
    def __init__(self):
        self.tree = {}
    
    def characteristics(self, souptag, d):
        souptag = souptag.find('CharacteristicList')
        d.update({'CharacteristicList' : {}})
        souptag = souptag.find('characteristic')
        while souptag:
            print(souptag.attrs['name'])
            characteristic_name = souptag.attrs['name']
            d['CharacteristicList'].update({characteristic_name : {}})
            self.characteristic(souptag,
                                d['CharacteristicList'][characteristic_name])
            souptag = souptag.find_next('characteristic')

    def characteristic(self, souptag, d):
        souptag = souptag.find('DataRecord')
        while souptag:
            # If multiple datarecords, need labels
            self.datarecord(souptag, d)
            souptag = souptag.find_next_sibling()

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
        decimalseparator = (text_encoding.attrs
                               .setdefault('decimalSeparator', '.'))
        collapsewhitespaces = (self._str_to_bool(text_encoding.attrs
                               .setdefault('collapseWhiteSpaces', 'true')))
        raw_values = souptag.find('values').get_text()  
        if collapsewhitespaces:
            raw_values = raw_values.strip()
        blocks = raw_values.split(block_separator)
        for block in blocks:
            tokens = block.split(token_separator)
            for label, token in zip(field_labels, tokens):
                # TODO: Still need to handle typing 
                typename = d[label]['type']
                d[label]['value'].append(token)

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
parser.characteristics(s, parser.tree)

def walk(node):
    for key, item in node.items():
        if item is a collection:
            walk(item)
        else:
            It is a leaf, do your thing
