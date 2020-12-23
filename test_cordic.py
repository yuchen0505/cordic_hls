from __future__ import print_function
from pynq import Overlay
from pynq import MMIO
import numpy as np
import struct
import binascii
import cmath
import random
import matplotlib.pyplot as plt
import sys

overlay = Overlay("/home/xilinx/IPBitFile/cordic.bit")
overlay.download()
regIP = overlay.cordic_0

NUM_DEGREE=90;
M_PI= 3.1415926536897932384626

error_sin=np.zeros(NUM_DEGREE)
error_cos=np.zeros(NUM_DEGREE)

print("Entry:", sys.argv[0])
print("System argument(s):", len(sys.argv))
print("Start of \"" + sys.argv[0] + "\"")

print("============================")
for i in range(NUM_DEGREE):
    th = i
    radian = i*M_PI/180
    # Computing gold data
    zs = np.sin(radian)
    zc = np.cos(radian)
    # write theta
    regIP.write(0x10, int(radian*2**26))
    IP_s = regIP.read(0x18)
    IP_c = regIP.read(0x20)

    s = IP_s / 2**26
    c = IP_c / 2**26
    print("degree= ", th, "radian=", radian, "cos=", c, "sin=", s)
    error_sin = "{0:.6f}".format(abs(s-zs))   
    error_cos = "{0:.6f}".format(abs(c-zc))     
    print(error_cos, error_sin)
print("Exit process")