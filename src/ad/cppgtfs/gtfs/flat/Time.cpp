//
// Created by vlad on 14.04.2020.
//

#include <ad/cppgtfs/gtfs/flat/Time.h>

namespace ad::cppgtfs::gtfs::flat
{
    std::string Time::toString() const
    {
        std::stringstream ss;
        if (!empty()) {
            ss << std::setfill('0') << std::setw(2) << static_cast<int>(h) << ":"
               << std::setfill('0') << std::setw(2) << static_cast<int>(m) << ":"
               << std::setfill('0') << std::setw(2) << static_cast<int>(s);
        }
        return ss.str();
    }
    Time::Time() :
        m(61), s(0), h(0)
    {
    }
    Time::Time(uint8_t h, uint8_t m, uint8_t s) :
        m(m), s(s), h(h)
    {
    }
    bool Time::empty() const
    {
        return m > 60;
    }
    bool operator>(const Time& lh, const Time& rh)
    {
        return lh.h * 3600 + lh.m * 60 + lh.s > rh.h * 3600 + rh.m * 60 + rh.s;
    }
    bool operator<(const Time& lh, const Time& rh)
    {
        return rh > lh;
    }
    bool operator==(const Time& lh, const Time& rh)
    {
        return !(rh > lh) && !(rh < lh);
    }
    bool operator!=(const Time& lh, const Time& rh)
    {
        return !(rh == lh);
    }
    bool operator>=(const Time& lh, const Time& rh)
    {
        return lh > rh || lh == rh;
    }
    bool operator<=(const Time& lh, const Time& rh)
    {
        return lh < rh || lh == rh;
    }
}