#!/usr/bin/env python

from distutils.core import setup

setup(name='firmament',
      version='0.1',
      description='Sensor firmware generation',
      author='Matt Bartos',
      author_email='mdbartos@umich.edu',
      url='open-storm.org',
      include_package_data=True,
      packages=['firmament'],
      install_requires=[
      'BeautifulSoup4', 'lxml', 'pyyaml'
      ]
     )
