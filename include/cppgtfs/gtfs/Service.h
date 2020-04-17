// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_SERVICE_H_
#define AD_CPPGTFS_GTFS_SERVICE_H_

#include <ctime>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <csv/CsvParser.h>

namespace cppgtfs::gtfs
{
    using fieldId = csv::fieldId;

    struct CalendarFields
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

        static CalendarFields fromCsvParser(const csv::CsvParser& csvp);
    };
    struct CalendarDateFields
    {
        fieldId serviceIdFld;
        fieldId exceptionTypeFld;
        fieldId dateFld;

        static CalendarDateFields fromCsvParser(const csv::CsvParser& csvp);

    };
    class ServiceDateFlat
    {
    public:
        ServiceDateFlat();

        explicit ServiceDateFlat(uint8_t day, uint8_t month, uint16_t year);

        explicit ServiceDateFlat(uint32_t yyyymmdd);

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
    struct CalendarFlat
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
        ServiceDateFlat begin;
        ServiceDateFlat end;
    };
    struct CalendarDateFlat
    {
        enum EXCEPTION_TYPE : uint8_t
        {
            NOT_SET = 0,
            SERVICE_ADDED = 1,
            SERVICE_REMOVED = 2
        };

        std::string id;
        EXCEPTION_TYPE type;
        ServiceDateFlat date;
    };
    bool operator>(const ServiceDateFlat& lh, const ServiceDateFlat& rh);
    bool operator<(const ServiceDateFlat& lh, const ServiceDateFlat& rh);
    bool operator==(const ServiceDateFlat& lh, const ServiceDateFlat& rh);
    bool operator!=(const ServiceDateFlat& lh, const ServiceDateFlat& rh);
    bool operator>=(const ServiceDateFlat& lh, const ServiceDateFlat& rh);
    bool operator<=(const ServiceDateFlat& lh, const ServiceDateFlat& rh);
    ServiceDateFlat operator+(const ServiceDateFlat& lh, int i);
    ServiceDateFlat operator-(const ServiceDateFlat& lh, int i);
    ServiceDateFlat operator--(ServiceDateFlat& lh);
    ServiceDateFlat operator++(ServiceDateFlat& lh);


    using ServiceDate = ServiceDateFlat;

    class Service
    {
    public:
        using Ref = Service *;
        using SERVICE_DAY = CalendarFlat::SERVICE_DAY;
        using EXCEPTION_TYPE = CalendarDateFlat::EXCEPTION_TYPE;

        static std::string getId(Ref r) { return r->getId(); }

        explicit Service(std::string  id);

        Service(std::string  id, uint8_t serviceDays, ServiceDate start, ServiceDate end);

        [[nodiscard]] const std::string& getId() const;

        [[nodiscard]] const std::map<ServiceDate, Service::EXCEPTION_TYPE>& getExceptions() const;

        void addException(const ServiceDate& d, EXCEPTION_TYPE t);

        [[nodiscard]] bool isActiveOn(const ServiceDate& d) const;

        static SERVICE_DAY getServiceDay(const ServiceDate& d);

        [[nodiscard]] uint8_t getServiceDates() const;

        [[nodiscard]] EXCEPTION_TYPE getExceptionOn(const ServiceDate& d) const;

        [[nodiscard]] const ServiceDate& getBeginDate() const;

        [[nodiscard]] const ServiceDate& getEndDate() const;

        [[nodiscard]] bool hasServiceDays() const;

        [[nodiscard]] CalendarFlat getFlat() const
        {
            return {
                _id, _serviceDays, _begin, _end
            };
        }

    private:
        std::string _id;
        uint8_t _serviceDays;
        std::map<ServiceDate, Service::EXCEPTION_TYPE> _exceptions;
        ServiceDate _begin, _end;
    };

}    // namespace cppgtfs::gtfs

#endif    // AD_CPPGTFS_GTFS_SERVICE_H_
