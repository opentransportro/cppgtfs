// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_FLAT_STOP_H_
#define AD_CPPGTFS_GTFS_FLAT_STOP_H_

#include <stdint.h>
#include <cassert>
#include <string>

namespace ad::cppgtfs::gtfs::flat
{
    struct StopFlds
    {
        size_t stopIdFld;
        size_t stopNameFld;
        size_t stopLatFld;
        size_t stopLonFld;
        size_t parentStationFld;
        size_t stopCodeFld;
        size_t stopDescFld;
        size_t zoneIdFld;
        size_t stopUrlFld;
        size_t stopTimezoneFld;
        size_t wheelchairBoardingFld;
        size_t locationTypeFld;
        size_t platformCodeFld;
    };

    struct Stop
    {
        enum LOCATION_TYPE : uint8_t
        {
            STOP = 0,
            STATION = 1,
            STATION_ENTRANCE = 2
        };

        enum WHEELCHAIR_BOARDING : uint8_t
        {
            NO_INFORMATION = 0,
            BOARDING_POSSIBLE = 1,
            BOARDING_NOT_POSSIBLE = 2
        };

        std::string id, code, name, desc, zone_id, stop_url, stop_timezone,
            platform_code, parent_station;
        float lat, lng;
        Stop::WHEELCHAIR_BOARDING wheelchair_boarding;
        Stop::LOCATION_TYPE location_type;
    };

}    // namespace ad

#endif    // AD_CPPGTFS_GTFS_FLAT_STOP_H_
