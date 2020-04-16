// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_FREQUENCY_H_
#define AD_CPPGTFS_GTFS_FREQUENCY_H_

#include "StopTime.h"
#include "flat/Frequency.h"

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

        [[nodiscard]] const Time& getStartTime() const { return _startTime; }

        [[nodiscard]] const Time& getEndTime() const { return _endTime; }

        [[nodiscard]] uint16_t getHeadwaySecs() const { return _headwaySecs; }

        [[nodiscard]] bool hasExactTimes() const { return _exactTimes; }

        void setStartTime(const Time& startTime)
        {
            _startTime = startTime;
        }
        void setEndTime(const Time& endTime)
        {
            _endTime = endTime;
        }
        void setHeadwaySecs(uint16_t headwaySecs)
        {
            _headwaySecs = headwaySecs;
        }
        void setExactTimes(bool exactTimes)
        {
            _exactTimes = exactTimes;
        }

    private:
        Time _startTime, _endTime;
        uint16_t _headwaySecs;
        bool _exactTimes;
    };

}    // namespace ad::cppgtfs::gtfs

#endif    // AD_CPPGTFS_GTFS_FREQUENCY_H_
