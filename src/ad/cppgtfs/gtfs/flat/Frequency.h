// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_FLAT_FREQUENCY_H_
#define AD_CPPGTFS_GTFS_FLAT_FREQUENCY_H_

#include <string>
#include <ad/util/CsvParser.h>
#include <ad/cppgtfs/gtfs/flat/StopTime.h>
using namespace ad::util;

namespace ad::cppgtfs::gtfs::flat
{
    struct FrequencyFlds
    {
        fieldId tripIdFld;
        fieldId startTimeFld;
        fieldId endTimeFld;
        fieldId headwaySecsFld;
        fieldId exactTimesFld;

        static FrequencyFlds fromCsvParser(const util::CsvParser& csvp);
    };

    struct Frequency
    {
        std::string tripId;
        Time startTime, endTime;
        uint16_t headwaySecs;
        bool exactTimes;
    };
}    // namespace ad

#endif    // AD_CPPGTFS_GTFS_FLAT_FREQUENCY_H_
