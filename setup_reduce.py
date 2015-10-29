# setup.py
from distutils.core import setup, Extension
setup(name="windrosebin",
      py_modules=['windrosebin'],
      ext_modules=[Extension("_windrosebin_reduce",
                             ["windrosebin_reduce.i","windrosebin_reduc.cpp"],
                             swig_opts=['-c++'],
                             )]
      
      )