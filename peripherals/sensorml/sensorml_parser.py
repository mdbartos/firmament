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

    def datarecord(self, souptag, d):
        souptag = souptag.find('field')
        while souptag:
            self.field(souptag, d)
            souptag = souptag.find_next_sibling('field')

    def field(self, souptag, d, declaration=False):
        fieldname = souptag.attrs['name']
        print(fieldname)
        typetag = souptag.find()
        typename = typetag.name.lower()
        # Hacky but works for right now
        if typename == 'datarecord':
            d.update({fieldname : {}})
            getattr(self, typename)(souptag, d[fieldname])
        else:
            getattr(self, typename)(souptag, d)

    def count(self, souptag, d):
        fieldname = souptag.attrs['name']
        souptag = souptag.find('value')
        value = int(souptag.get_text())
        d.update({fieldname : value})

    def quantity(self, souptag, d):
        fieldname = souptag.attrs['name']
        souptag = souptag.find('value')
        value = float(souptag.get_text())
        d.update({fieldname : value})

    def text(self, souptag, d):
        fieldname = souptag.attrs['name']
        souptag = souptag.find('value')
        value = souptag.get_text()
        d.update({fieldname : value})

    def boolean(self, souptag, d):
        fieldname = souptag.attrs['name']
        souptag = souptag.find('value')
        value = souptag.get_text().lower()
        if value in ('true', '1'):
            value = True
        elif value in ('false', '0'):
            value = False
        else:
            raise ValueError("Boolean value must be 'true' or 'false'")
        d.update({fieldname : value})

    def category(self, souptag, d):
        self.text(souptag, d)

    def datastream(self, souptag, d):
        pass

    def quantityrange(self, souptag, d):
        pass

sensor = 'maxbotix_mb7383.xml'
desired_protocol = 'ttl'

with open('maxbotix_mb7383.xml', 'r') as infile:
    x = ''.join(infile.readlines())
s = Soup(x, 'xml')

parser = SensorMLParser()
parser.characteristics(s, parser.tree)
