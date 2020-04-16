// Copyright 2016, University of Freiburg,
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include "Service.h"

using ad::cppgtfs::gtfs::Service;
using ad::cppgtfs::gtfs::ServiceDate;

// _____________________________________________________________________________
Service::Service(std::string  id) :
    _id(std::move(id)),
    _serviceDays(Service::SERVICE_DAY::NEVER),
    _begin(),
    _end() {}

// _____________________________________________________________________________
Service::Service(std::string  id, uint8_t serviceDays, ServiceDate start, ServiceDate end) :
    _id(std::move(id)),
    _serviceDays(serviceDays),
    _begin(start),
    _end(end) {}

// _____________________________________________________________________________
const std::string& Service::getId() const { return _id; }

// _____________________________________________________________________________
const std::map<ServiceDate, Service::EXCEPTION_TYPE>& Service::getExceptions()
    const
{
    return _exceptions;
}

// _____________________________________________________________________________
void Service::addException(const ServiceDate& d, Service::EXCEPTION_TYPE t)
{
    _exceptions[d] = t;
}

// _____________________________________________________________________________
bool Service::isActiveOn(const ServiceDate& d) const
{
    return ((d >= _begin && d <= _end) && (_serviceDays & getServiceDay(d)) && getExceptionOn(d) != EXCEPTION_TYPE::SERVICE_REMOVED) || getExceptionOn(d) == EXCEPTION_TYPE::SERVICE_ADDED;
}

// _____________________________________________________________________________
const ServiceDate& Service::getBeginDate() const
{
    return _begin;
}

// _____________________________________________________________________________
const ServiceDate& Service::getEndDate() const
{
    return _end;
}

// _____________________________________________________________________________
uint8_t Service::getServiceDates() const
{
    return _serviceDays;
}

// _____________________________________________________________________________
Service::SERVICE_DAY Service::getServiceDay(const ServiceDate& d)
{
    return static_cast<SERVICE_DAY>(1 << (((d.getTimeStrc().tm_wday + 6) % 7)));
}

// _____________________________________________________________________________
Service::EXCEPTION_TYPE Service::getExceptionOn(const ServiceDate& d) const
{
    auto ex = _exceptions.find(d);
    if (ex != _exceptions.end()) {
        return ex->second;
    }
    return EXCEPTION_TYPE::NOT_SET;
}


// _____________________________________________________________________________
bool Service::hasServiceDays() const
{
    return !_begin.empty() && !_end.empty();
}
