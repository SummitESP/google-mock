import sys
import os
sys.path.append(os.path.join('..', 'build-tools'))
from shared_wscript import *

def init(ctx):
    init_all_variants(ctx, VARIANTS)

def options(opt):
    options_desktop(opt)

def configure(conf):
    conf.setenv('test')
    configure_desktop(conf)

def build(bld):
    if bld.variant and bld.variant == 'test':
        bld.stlib(source=GMOCK_SOURCE,
                  includes=GMOCK_INCLUDE,
                  cppcheck_skip=True,
                  target='gmock')

GMOCK_SOURCE = [
    'src/gmock-all.cc'
]

VARIANTS = ['test', 'microchip']
