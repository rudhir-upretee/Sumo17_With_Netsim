/****************************************************************************/
/// @file    NIVissimSingleTypeParser_Fahrtverlaufdateien.h
/// @author  Daniel Krajzewicz
/// @date    Wed, 30 Apr 2003
/// @version $Id: NIVissimSingleTypeParser_Fahrtverlaufdateien.h 13811 2013-05-01 20:31:43Z behrisch $
///
//
/****************************************************************************/
// SUMO, Simulation of Urban MObility; see http://sumo.sourceforge.net/
// Copyright (C) 2001-2013 DLR (http://www.dlr.de/) and contributors
/****************************************************************************/
//
//   This file is part of SUMO.
//   SUMO is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//
/****************************************************************************/
#ifndef NIVissimSingleTypeParser_Fahrtverlaufdateien_h
#define NIVissimSingleTypeParser_Fahrtverlaufdateien_h


// ===========================================================================
// included modules
// ===========================================================================
#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif

#include <iostream>
#include "../NIImporter_Vissim.h"


// ===========================================================================
// class definitions
// ===========================================================================
/**
 * @class NIVissimSingleTypeParser_Fahrtverlaufdateien
 *
 */
class NIVissimSingleTypeParser_Fahrtverlaufdateien :
    public NIImporter_Vissim::VissimSingleTypeParser {
public:
    /// Constructor
    NIVissimSingleTypeParser_Fahrtverlaufdateien(NIImporter_Vissim& parent);

    /// Destructor
    ~NIVissimSingleTypeParser_Fahrtverlaufdateien();

    /// Parses the data type from the given stream
    bool parse(std::istream& from);

};


#endif

/****************************************************************************/

