/****************************************************************************/
/// @file    NIImporter_ITSUMO.h
/// @author  Daniel Krajzewicz
/// @date    2011-09-16
/// @version $Id: NIImporter_ITSUMO.h 13811 2013-05-01 20:31:43Z behrisch $
///
// Importer for networks stored in ITSUMO format
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
#ifndef NIImporter_ITSUMO_h
#define NIImporter_ITSUMO_h


// ===========================================================================
// included modules
// ===========================================================================
#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif

#include <string>
#include <map>
#include <netbuild/NBCapacity2Lanes.h>
#include <utils/xml/SUMOSAXHandler.h>
#include <utils/common/UtilExceptions.h>


// ===========================================================================
// class declarations
// ===========================================================================
class NBEdge;
class NBEdgeCont;
class NBNetBuilder;
class NBNode;
class NBNodeCont;
class NBTrafficLightLogicCont;
class NBTypeCont;
class OptionsCont;


// ===========================================================================
// class definitions
// ===========================================================================
/**
 * @class NIImporter_ITSUMO
 * @brief Importer for networks stored in ITSUMO format
 *
 */
class NIImporter_ITSUMO {
public:
    /** @brief Loads content of the optionally given ITSUMO network files
     *
     * If the option "itsumo-files" is set, the file(s) stored therein is read and
     *  the network definition stored therein is stored within the given network
     *  builder.
     *
     * If the option "itsumo-files" is not set, this method simply returns.
     *
     * @param[in] oc The options to use
     * @param[in] nb The network builder to fill
     */
    static void loadNetwork(const OptionsCont& oc, NBNetBuilder& nb);


private:
    /**
     * @class NodesHandler
     * @brief A class which parses an ITSUMO file
     */
    class Handler : public GenericSAXHandler {
    public:
        /** @brief Contructor
         * @param[in] toFill The container to fill
         */
        Handler(NBNetBuilder& toFill);


        /// @brief Destructor
        ~Handler();


    protected:
        /// @name inherited from GenericSAXHandler
        //@{

        /** @brief Called on the opening of a tag;
         *
         * @param[in] element ID of the currently opened element
         * @param[in] attrs Attributes within the currently opened element
         * @exception ProcessError If something fails
         * @see GenericSAXHandler::myStartElement
         */
        void myStartElement(int element, const SUMOSAXAttributes& attrs);


        /**
         * @brief Callback method for characters to implement by derived classes
         *
         * Called by "endElement" (see there).
         * @param[in] element The opened element, given as a int
         * @param[in] chars The complete embedded character string
         * @exceptions ProcessError These method may throw a ProcessError if something fails
         */
        void myCharacters(int element, const std::string& chars);


        /** @brief Callback method for a closing tag to implement by derived classes
         *
         * Called by "endElement" (see there).
         * @param[in] element The closed element, given as a int
         * @exceptions ProcessError These method may throw a ProcessError if something fails
         */
        void myEndElement(int element);
        //@}


    private:
        /// @brief The container to fill
        NBNetBuilder& myNetBuilder;

        /// @brief A temporary parameter map
        std::map<std::string, std::string> myParameter;


        struct Lane {
        public:
            Lane(const std::string& id, unsigned int idx, SUMOReal v)
                : myID(id), myIndex(idx), myV(v) {}
            std::string myID;
            unsigned int myIndex;
            SUMOReal myV;
        };

        std::vector<Lane> myCurrentLanes;

        struct LaneSet {
        public:
            LaneSet(const std::string& id, const std::vector<Lane>& lanes, SUMOReal v, int pos, NBNode* from, NBNode* to)
                : myID(id), myLanes(lanes), myV(v), myPosition(pos), myFrom(from), myTo(to) {}
            std::string myID;
            std::vector<Lane> myLanes;
            SUMOReal myV;
            int myPosition;
            NBNode* myFrom;
            NBNode* myTo;
        };

        std::map<std::string, LaneSet*> myLaneSets;
        std::vector<LaneSet*> myCurrentLaneSets;

        struct Section {
        public:
            Section(const std::string& id, const std::vector<LaneSet*>& laneSets)
                : myID(id), myLaneSets(laneSets) {}
            std::string myID;
            std::vector<LaneSet*> myLaneSets;
        };

        std::vector<Section*> mySections;


    private:
        /** @brief invalidated copy constructor */
        Handler(const Handler& s);

        /** @brief invalidated assignment operator */
        Handler& operator=(const Handler& s);

    };



    /**
     * @enum ItsumoXMLTag
     * @brief Numbers representing ITSUMO-XML - element names
     * @see GenericSAXHandler
     */
    enum ItsumoXMLTag {
        ITSUMO_TAG_NOTHING = 0,
        ITSUMO_TAG_SIMULATION,
        ITSUMO_TAG_NETWORK_ID,
        ITSUMO_TAG_NETWORK_NAME,
        ITSUMO_TAG_NODES,
        ITSUMO_TAG_NODE,
        ITSUMO_TAG_NODE_ID,
        ITSUMO_TAG_NODE_NAME,
        ITSUMO_TAG_X_COORD,
        ITSUMO_TAG_Y_COORD,
        ITSUMO_TAG_SOURCES,
        ITSUMO_TAG_SINKS,
        ITSUMO_TAG_TRAFFIC_LIGHTS,
        ITSUMO_TAG_STREETS,
        ITSUMO_TAG_STREET,
        ITSUMO_TAG_STREET_ID,
        ITSUMO_TAG_STREET_NAME,
        ITSUMO_TAG_SECTIONS,
        ITSUMO_TAG_SECTION,
        ITSUMO_TAG_SECTION_ID,
        ITSUMO_TAG_SECTION_NAME,
        ITSUMO_TAG_IS_PREFERENCIAL,
        ITSUMO_TAG_DELIMITING_NODE,
        ITSUMO_TAG_LANESETS,
        ITSUMO_TAG_LANESET,
        ITSUMO_TAG_LANESET_ID,
        ITSUMO_TAG_LANESET_POSITION,
        ITSUMO_TAG_START_NODE,
        ITSUMO_TAG_END_NODE,
        ITSUMO_TAG_TURNING_PROBABILITIES,
        ITSUMO_TAG_DIRECTION,
        ITSUMO_TAG_DESTINATION_LANESET,
        ITSUMO_TAG_PROBABILITY,
        ITSUMO_TAG_LANES,
        ITSUMO_TAG_LANE,
        ITSUMO_TAG_LANE_ID,
        ITSUMO_TAG_LANE_POSITION,
        ITSUMO_TAG_MAXIMUM_SPEED,
        ITSUMO_TAG_DECELERATION_PROB
    };


    /**
     * @enum ItsumoXMLAttr
     * @brief Numbers representing MATSIM-XML - attributes
     * @see GenericSAXHandler
     */
    enum ItsumoXMLAttr {
        ITSUMO_ATTR_NOTHING = 0
    };

    /// The names of MATSIM-XML elements (for passing to GenericSAXHandler)
    static StringBijection<int>::Entry itsumoTags[];

    /// The names of MATSIM-XML attributes (for passing to GenericSAXHandler)
    static StringBijection<int>::Entry itsumoAttrs[];


};


#endif

/****************************************************************************/

