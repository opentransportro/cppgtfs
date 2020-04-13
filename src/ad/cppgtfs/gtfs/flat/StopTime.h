// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_FLAT_STOPTIME_H_
#define AD_CPPGTFS_GTFS_FLAT_STOPTIME_H_

#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include "Stop.h"

namespace ad::cppgtfs::gtfs::flat
{
    struct StopTimeFlds
    {
        size_t stopIdFld;
        size_t tripIdFld;
        size_t arrivalTimeFld;
        size_t departureTimeFld;
        size_t stopSequenceFld;
        size_t stopHeadsignFld;
        size_t shapeDistTraveledFld;
        size_t timepointFld;
        size_t pickUpTypeFld;
        size_t dropOffTypeFld;
    };

    struct Time
    {
        Time() :
            m(61), s(0), h(0) {}

        Time(uint8_t h, uint8_t m, uint8_t s) :
            m(m), s(s), h(h) {}

        bool empty() const { return m > 60; }

        std::string toString() const
        {
            std::stringstream ss;
            if (!empty()) {
                ss << std::setfill('0') << std::setw(2) << static_cast<int>(h) << ":"
                   << std::setfill('0') << std::setw(2) << static_cast<int>(m) << ":"
                   << std::setfill('0') << std::setw(2) << static_cast<int>(s);
            }
            return ss.str();
        }

        uint8_t m : 6;
        uint8_t s : 6;
        uint8_t h : 8;
    };

    inline bool operator>(const Time& lh, const Time& rh)
    {
        return lh.h * 3600 + lh.m * 60 + lh.s > rh.h * 3600 + rh.m * 60 + rh.s;
    }

    inline bool operator<(const Time& lh, const Time& rh) { return rh > lh; }

    inline bool operator==(const Time& lh, const Time& rh)
    {
        return !(rh > lh) && !(rh < lh);
    }

    inline bool operator!=(const Time& lh, const Time& rh) { return !(rh == lh); }

    inline bool operator>=(const Time& lh, const Time& rh)
    {
        return lh > rh || lh == rh;
    }

    inline bool operator<=(const Time& lh, const Time& rh)
    {
        return lh < rh || lh == rh;
    }

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
