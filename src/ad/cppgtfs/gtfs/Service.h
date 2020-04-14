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

namespace ad::cppgtfs::gtfs
{
    using ServiceDate = flat::ServiceDate;

    class Service
    {
    public:
        using Ref = Service *;
        using SERVICE_DAY = flat::Calendar::SERVICE_DAY;
        using EXCEPTION_TYPE = flat::CalendarDate::EXCEPTION_TYPE;

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

        [[nodiscard]] flat::Calendar getFlat() const
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

}    // namespace ad::cppgtfs::gtfs

#endif    // AD_CPPGTFS_GTFS_SERVICE_H_
