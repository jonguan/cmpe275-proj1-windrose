#!/bin/sh

#  exec.sh
#
#
#  Created by Akshar Joshi on 10/28/15.
#

#swig -python windrosebin.i
#g++-5 -c -fpic  windrosebin.cpp windrosebin_wrap.c -I/usr/include/python2.7 -lpython
#g++-5 -shared -fopenmp  windrosebin.o windrosebin_wrap.o -o _windrosebin.so
#python run.py csvdata/ AP061 0800


swig -python windrosebin_reduce.i

g++-5 -std=gnu++11 -c -fPIC -fopenmp -x none windrosebin_reduc.cpp -x none -I /System/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7

g++-5 -shared -fPIC -fopenmp windrosebin_reduc.o windrosebin_reduc_wrap.o -o _windrosebin_reduc.so -lpython

python run.py csvdata/ AP061 0800