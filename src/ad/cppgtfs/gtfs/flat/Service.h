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

#include <ad/util/CsvParser.h>
using namespace ad::util;

namespace ad::cppgtfs::gtfs::flat
{
    struct CalendarFlds
    {
        fieldId serviceIdFld;
        fieldId mondayFld;
        fieldId tuesdayFld;
        fieldId wednesdayFld;
        fieldId thursdayFld;
        fieldId fridayFld;
        fieldId saturdayFld;
        fieldId sundayFld;
        fieldId startDateFld;
        fieldId endDateFld;

        static CalendarFlds fromCsvParser(const util::CsvParser& csvp);
    };

    struct CalendarDateFlds
    {
        fieldId serviceIdFld;
        fieldId exceptionTypeFld;
        fieldId dateFld;

        static CalendarDateFlds fromCsvParser(const util::CsvParser& csvp);

    };

    class ServiceDate
    {
    public:
        ServiceDate();

        explicit ServiceDate(uint8_t day, uint8_t month, uint16_t year);

        explicit ServiceDate(uint32_t yyyymmdd);

        uint32_t getYYYYMMDD() const;

        uint16_t getYear() const;

        uint8_t getMonth() const;

        uint8_t getDay() const;

        void setDay(uint8_t day);

        void setMonth(uint8_t month);

        void setYear(uint16_t year);

        bool empty() const;

        // returns a time struct of this date at 12:00
        tm getTimeStrc() const;

    private:
        uint32_t _yyyymmdd : 24;
    };

    bool operator>(const ServiceDate& lh, const ServiceDate& rh);

    bool operator<(const ServiceDate& lh, const ServiceDate& rh);

    bool operator==(const ServiceDate& lh, const ServiceDate& rh);

    bool operator!=(const ServiceDate& lh, const ServiceDate& rh);

    bool operator>=(const ServiceDate& lh, const ServiceDate& rh);

    bool operator<=(const ServiceDate& lh, const ServiceDate& rh);

    ServiceDate operator+(const ServiceDate& lh, int i);

    ServiceDate operator-(const ServiceDate& lh, int i);

    ServiceDate operator--(ServiceDate& lh);

    ServiceDate operator++(ServiceDate& lh);

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

        std::string id;
        uint8_t serviceDays;
        ServiceDate begin;
        ServiceDate end;
    };

    struct CalendarDate
    {
        enum EXCEPTION_TYPE : uint8_t
        {
            NOT_SET = 0,
            SERVICE_ADDED = 1,
            SERVICE_REMOVED = 2
        };

        std::string id;
        EXCEPTION_TYPE type;
        ServiceDate date;
    };

}    // namespace ad

#endif    // AD_CPPGTFS_GTFS_SERVICE_H_
