import sys
import os
sys.path.append(os.path.join('..', 'build-tools'))
from shared_wscript import *

def options(opt):
    options_desktop(opt)

def configure(conf):
    configure_desktop(conf)

def build(bld):
    bld.stlib(source=GMOCK_SOURCE,
              includes=GMOCK_INCLUDE,
              target='gmock')

GMOCK_SOURCE = [
    'src/gmock-all.cc'
]

