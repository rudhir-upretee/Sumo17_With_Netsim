#!/usr/bin/env python
"""
@file    sumopoi.py
@author  Daniel Krajzewicz
@author  Michael Behrisch
@date    2010-02-18
@version $Id: sumopoi.py 13811 2013-05-01 20:31:43Z behrisch $

Deprecated version of sumolib/poi.py.

SUMO, Simulation of Urban MObility; see http://sumo.sourceforge.net/
Copyright (C) 2010-2013 DLR (http://www.dlr.de/) and contributors
All rights reserved
"""

import os, sys
print >> sys.stderr, "Using this library is deprecated, please use sumolib.poi instead!"
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from sumolib.shapes.poi import *
