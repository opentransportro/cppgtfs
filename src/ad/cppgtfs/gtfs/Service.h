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
#include "flat/Service.h"

using std::exception;
using std::string;

namespace ad::cppgtfs::gtfs
{
    using ServiceDate = flat::ServiceDate;

    class Service
    {
    public:
        typedef Service* Ref;

        static std::string getId(Ref r) { return r->getId(); }

        typedef flat::Calendar::SERVICE_DAY SERVICE_DAY;
        typedef flat::CalendarDate::EXCEPTION_TYPE EXCEPTION_TYPE;

        explicit Service(const string& id);

        Service(const string& id, uint8_t serviceDays, ServiceDate start, ServiceDate end);

        const std::string& getId() const;

        const std::map<ServiceDate, Service::EXCEPTION_TYPE>& getExceptions() const;

        void addException(const ServiceDate& d, EXCEPTION_TYPE t);

        bool isActiveOn(const ServiceDate& d) const;

        static SERVICE_DAY getServiceDay(const ServiceDate& d);

        uint8_t getServiceDates() const;

        EXCEPTION_TYPE getExceptionOn(const ServiceDate& d) const;

        const ServiceDate& getBeginDate() const;

        const ServiceDate& getEndDate() const;

        bool hasServiceDays() const;

        flat::Calendar getFlat() const
        {
            flat::Calendar c;
            c.id = _id;
            c.serviceDays = _serviceDays;
            c.begin = _begin;
            c.end = _end;
            return c;
        }

    private:
        string _id;
        uint8_t _serviceDays;
        std::map<ServiceDate, Service::EXCEPTION_TYPE> _exceptions;
        ServiceDate _begin, _end;
    };

}    // namespace ad::cppgtfs::gtfs

#endif    // AD_CPPGTFS_GTFS_SERVICE_H_
