# setup.py
from distutils.core import setup, Extension
setup(name="windrose",
      py_modules=['windrose'],
      ext_modules=[Extension("_windrose",
                             ["windrose.i","windrose.cpp"],
                             swig_opts=['-c++'],
                             )]
      
      )