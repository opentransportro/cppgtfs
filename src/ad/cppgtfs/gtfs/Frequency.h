// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_FREQUENCY_H_
#define AD_CPPGTFS_GTFS_FREQUENCY_H_

#include "StopTime.h"
#include "flat/Frequency.h"

using std::exception;
using std::string;

namespace ad::cppgtfs::gtfs
{
    class Frequency
    {
    public:
        Frequency(const Time& startTime, const Time& endTime, uint16_t headwaySecs, bool exactTimes) :
            _startTime(startTime),
            _endTime(endTime),
            _headwaySecs(headwaySecs),
            _exactTimes(exactTimes) {}

        const Time& getStartTime() const { return _startTime; }

        const Time& getEndTime() const { return _endTime; }

        uint16_t getHeadwaySecs() const { return _headwaySecs; }

        bool hasExactTimes() const { return _exactTimes; }

    private:
        Time _startTime, _endTime;
        uint16_t _headwaySecs;
        bool _exactTimes;
    };

}    // namespace ad::cppgtfs::gtfs

#endif    // AD_CPPGTFS_GTFS_FREQUENCY_H_
