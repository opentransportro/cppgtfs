// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_FLAT_STOP_H_
#define AD_CPPGTFS_GTFS_FLAT_STOP_H_

#include <stdint.h>
#include <cassert>
#include <string>
#include <ad/util/CsvParser.h>

using namespace ad::util;

namespace ad::cppgtfs::gtfs::flat
{
    struct StopFlds
    {
        fieldId stopIdFld;
        fieldId stopNameFld;
        fieldId stopLatFld;
        fieldId stopLonFld;
        fieldId parentStationFld;
        fieldId stopCodeFld;
        fieldId stopDescFld;
        fieldId zoneIdFld;
        fieldId stopUrlFld;
        fieldId stopTimezoneFld;
        fieldId wheelchairBoardingFld;
        fieldId locationTypeFld;
        fieldId platformCodeFld;

        static StopFlds fromCsvParser(const ad::util::CsvParser& csvp);
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

        std::string id;
        std::string code;
        std::string name;
        std::string desc;
        std::string zone_id;
        std::string stop_url;
        std::string stop_timezone;
        std::string platform_code;
        std::string parent_station;
        float lat, lng;
        Stop::WHEELCHAIR_BOARDING wheelchair_boarding;
        Stop::LOCATION_TYPE location_type;
    };

}    // namespace ad

#endif    // AD_CPPGTFS_GTFS_FLAT_STOP_H_
