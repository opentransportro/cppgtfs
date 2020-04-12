// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_FLAT_SERVICE_H_
#define AD_CPPGTFS_GTFS_FLAT_SERVICE_H_

#include <ctime>
#include <map>
#include <string>
#include <vector>
#include <iostream>

using std::exception;
using std::string;

namespace ad::cppgtfs::gtfs::flat
{
    struct CalendarFlds
    {
        size_t serviceIdFld;
        size_t mondayFld;
        size_t tuesdayFld;
        size_t wednesdayFld;
        size_t thursdayFld;
        size_t fridayFld;
        size_t saturdayFld;
        size_t sundayFld;
        size_t startDateFld;
        size_t endDateFld;
    };

    struct CalendarDateFlds
    {
        size_t serviceIdFld;
        size_t exceptionTypeFld;
        size_t dateFld;
    };

    class ServiceDate
    {
    public:
        ServiceDate(uint8_t day, uint8_t month, uint16_t year) :
            _yyyymmdd((year * 10000 + month * 100 + day) - (1900 * 10000)) {}

        explicit ServiceDate(uint32_t yyyymmdd) :
            _yyyymmdd(yyyymmdd - (1900 * 10000)) {}

        ServiceDate() :
            _yyyymmdd(0) {}

        uint32_t getYYYYMMDD() const { return _yyyymmdd + (1900 * 10000); }

        uint16_t getYear() const { return (_yyyymmdd / 10000) + 1900; }

        uint8_t getMonth() const
        {
            return (_yyyymmdd - ((getYear() - 1900) * 10000)) / 100;
        }

        uint8_t getDay() const
        {
            return _yyyymmdd - ((getYear() - 1900) * 10000) - (getMonth() * 100);
        }

        void setDay(uint8_t day) { _yyyymmdd = _yyyymmdd - getDay() + day; }

        void setMonth(uint8_t month)
        {
            _yyyymmdd = _yyyymmdd - getMonth() * 100 + month * 100;
        }

        void setYear(uint16_t year)
        {
            _yyyymmdd = _yyyymmdd - (getYear() - 1900) * 10000 + (year - 1900) * 10000;
        }

        bool empty() const
        {
            return _yyyymmdd == 0;
        }

        // returns a time struct of this date at 12:00
        tm getTimeStrc() const
        {
            tm ret;
            ret.tm_year = getYear() - 1900;
            ret.tm_mon = getMonth() - 1;
            ret.tm_mday = getDay();
            ret.tm_hour = 12;
            mktime(&ret);
            return ret;
        }

    private:
        uint32_t _yyyymmdd : 24;
    };

    inline bool operator>(const ServiceDate& lh,
        const ServiceDate& rh)
    {
        return lh.getYYYYMMDD() > rh.getYYYYMMDD();
    }

    inline bool operator<(const ServiceDate& lh,
        const ServiceDate& rh)
    {
        return rh > lh;
    }

    inline bool operator==(const ServiceDate& lh,
        const ServiceDate& rh)
    {
        return !(lh > rh) && !(lh < rh);
    }

    inline bool operator!=(const ServiceDate& lh,
        const ServiceDate& rh)
    {
        return !(lh == rh);
    }

    inline bool operator>=(const ServiceDate& lh,
        const ServiceDate& rh)
    {
        return lh > rh || lh == rh;
    }

    inline bool operator<=(const ServiceDate& lh,
        const ServiceDate& rh)
    {
        return rh > lh || lh == rh;
    }

    inline ServiceDate operator+(const ServiceDate& lh, int i)
    {
        tm tStrc = lh.getTimeStrc();
        tStrc.tm_mday += i;
        mktime(&tStrc);

        return ServiceDate(tStrc.tm_mday, tStrc.tm_mon + 1, tStrc.tm_year + 1900);
    }

    inline ServiceDate operator-(const ServiceDate& lh, int i)
    {
        return lh + (-i);
    }

    inline ServiceDate operator--(ServiceDate& lh)
    {
        ServiceDate ret = lh - 1;
        lh.setDay(ret.getDay());
        lh.setMonth(ret.getMonth());
        lh.setYear(ret.getYear());
        return ret;
    }

    inline ServiceDate operator++(ServiceDate& lh)
    {
        ServiceDate ret = lh + 1;
        lh.setDay(ret.getDay());
        lh.setMonth(ret.getMonth());
        lh.setYear(ret.getYear());
        return ret;
    }

    struct Calendar
    {
        enum SERVICE_DAY : uint8_t
        {
            NEVER = 0,         // 0000000
            MONDAYS = 1,       // 0000001
            TUESDAYS = 2,      // 0000010
            WEDNESDAYS = 4,    // 0000100
            THURSDAYS = 8,     // 0001000
            FRIDAYS = 16,      // 0010000
            SATURDAYS = 32,    // 0100000
            SUNDAYS = 64,      // 1000000
            WEEKDAYS = 31,     // 0011111 (shorthand)
            WEEKENDS = 96,     // 1100000 (shorthand)
            ALL_WEEK = 127     // 1111111 (shorthand)
        };

        string id;
        uint8_t serviceDays;
        ServiceDate begin, end;
    };

    struct CalendarDate
    {
        enum EXCEPTION_TYPE : uint8_t
        {
            NOT_SET = 0,
            SERVICE_ADDED = 1,
            SERVICE_REMOVED = 2
        };

        string id;
        EXCEPTION_TYPE type;
        ServiceDate date;
    };

}    // namespace ad

#endif    // AD_CPPGTFS_GTFS_SERVICE_H_
