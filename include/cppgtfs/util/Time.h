//
// Created by vlad on 14.04.2020.
//

#ifndef CPPGTFS_TIME_H
#define CPPGTFS_TIME_H

#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace cppgtfs::util
{
    struct Time
    {
        Time();

        explicit Time(uint8_t h, uint8_t m, uint8_t s);

        bool empty() const;

        std::string toString() const;

        uint8_t m : 6;
        uint8_t s : 6;
        uint8_t h : 8;
    };

    bool operator>(const Time& lh, const Time& rh);

    bool operator<(const Time& lh, const Time& rh);

    bool operator==(const Time& lh, const Time& rh);

    bool operator!=(const Time& lh, const Time& rh);

    bool operator>=(const Time& lh, const Time& rh);

    bool operator<=(const Time& lh, const Time& rh);
}    // namespace cppgtfs::util


#endif    //CPPGTFS_TIME_H
