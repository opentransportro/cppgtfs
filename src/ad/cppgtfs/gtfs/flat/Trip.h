// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_FLAT_TRIP_H_
#define AD_CPPGTFS_GTFS_FLAT_TRIP_H_

#include <string>

namespace ad::cppgtfs::gtfs::flat
{
    struct TripFlds
    {
        size_t shapeIdFld;
        size_t tripIdFld;
        size_t serviceIdFld;
        size_t routeIdFld;
        size_t blockIdFld;
        size_t tripHeadsignFld;
        size_t tripShortNameFld;
        size_t bikesAllowedFld;
        size_t wheelchairAccessibleFld;
        size_t directionIdFld;
    };

    struct Trip
    {
        enum WC_BIKE_ACCESSIBLE : uint8_t
        {
            NO_INFORMATION = 0,
            AT_LEAST_ONE = 1,
            NOT_ACCESSIBLE = 2
        };

        enum DIRECTION : uint8_t
        {
            OUTBOUND = 0,
            INBOUND = 1,
            NOT_SET = 2
        };

        std::string id;
        std::string route;
        std::string service;
        std::string headsign;
        std::string short_name;
        DIRECTION dir;
        std::string block_id;
        std::string shape;
        WC_BIKE_ACCESSIBLE wc;
        WC_BIKE_ACCESSIBLE ba;
    };
}    // namespace ad

#endif    // AD_CPPGTFS_GTFS_FLAT_TRIP_H_
