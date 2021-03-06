"""
@file    roundabout.py
@author  Daniel Krajzewicz
@author  Laura Bieker
@author  Karol Stosiek
@author  Michael Behrisch
@date    2011-11-28
@version $Id: roundabout.py 13811 2013-05-01 20:31:43Z behrisch $

This file contains a Python-representation of a single roundabout.

SUMO, Simulation of Urban MObility; see http://sumo.sourceforge.net/
Copyright (C) 2008-2013 DLR (http://www.dlr.de/) and contributors
All rights reserved
"""
class Roundabout:
    def __init__(self, nodes):
        self._nodes = nodes

    def getNodes(self):
        return self._nodes
