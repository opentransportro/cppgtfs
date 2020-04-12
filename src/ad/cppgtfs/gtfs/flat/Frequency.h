// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_FLAT_FREQUENCY_H_
#define AD_CPPGTFS_GTFS_FLAT_FREQUENCY_H_

#include <string>

namespace ad::cppgtfs::gtfs::flat
{
    struct FrequencyFlds
    {
        size_t tripIdFld;
        size_t startTimeFld;
        size_t endTimeFld;
        size_t headwaySecsFld;
        size_t exactTimesFld;
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
