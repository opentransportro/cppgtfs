// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_FLAT_STOPTIME_H_
#define AD_CPPGTFS_GTFS_FLAT_STOPTIME_H_

#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <ad/cppgtfs/gtfs/Stop.h>
#include <ad/cppgtfs/gtfs/flat/Time.h>
#include <ad/util/CsvParser.h>

using namespace ad::util;

namespace ad::cppgtfs::gtfs::flat
{
    struct StopTimeFlds
    {
        fieldId stopIdFld;
        fieldId tripIdFld;
        fieldId arrivalTimeFld;
        fieldId departureTimeFld;
        fieldId stopSequenceFld;
        fieldId stopHeadsignFld;
        fieldId shapeDistTraveledFld;
        fieldId timepointFld;
        fieldId pickUpTypeFld;
        fieldId dropOffTypeFld;

        // ____________________________________________________________________________
        static flat::StopTimeFlds fromCsvParser(const util::CsvParser& csvp);
    };


    struct StopTime
    {
        enum PU_DO_TYPE : uint8_t
        {
            REGULAR = 0,
            NEVER = 1,
            MUST_PHONE_AGENCY = 2,
            MUST_COORDINATE_W_DRIVER = 3
        };

        Time at;
        Time dt;

        std::string trip;
        std::string s;
        uint32_t sequence;
        std::string headsign;
        PU_DO_TYPE pickupType;
        PU_DO_TYPE dropOffType;
        bool isTimepoint;
        double shapeDistTravelled;
    };

}    // namespace ad

#endif    // AD_CPPGTFS_GTFS_FLAT_STOPTIME_H_
