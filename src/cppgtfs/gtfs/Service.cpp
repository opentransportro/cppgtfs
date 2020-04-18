// Copyright 2016, University of Freiburg,
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <cppgtfs/gtfs/Service.h>

namespace cppgtfs::gtfs
{
    Service::Service(std::string id) :
        _id(std::move(id)),
        _serviceDays(Service::SERVICE_DAY::NEVER),
        _begin(),
        _end() {}

    Service::Service(std::string id, uint8_t serviceDays, ServiceDate start, ServiceDate end) :
        _id(std::move(id)),
        _serviceDays(serviceDays),
        _begin(start),
        _end(end) {}

    const std::string& Service::getId() const { return _id; }

    const std::map<ServiceDate, Service::EXCEPTION_TYPE>& Service::getExceptions() const
    {
        return _exceptions;
    }

    void Service::addException(const ServiceDate& d, Service::EXCEPTION_TYPE t)
    {
        _exceptions[d] = t;
    }

    bool Service::isActiveOn(const ServiceDate& d) const
    {
        return ((d >= _begin && d <= _end) && (_serviceDays & getServiceDay(d)) && getExceptionOn(d) != EXCEPTION_TYPE::SERVICE_REMOVED) || getExceptionOn(d) == EXCEPTION_TYPE::SERVICE_ADDED;
    }

    const ServiceDate& Service::getBeginDate() const
    {
        return _begin;
    }

    const ServiceDate& Service::getEndDate() const
    {
        return _end;
    }


    uint8_t Service::getServiceDates() const
    {
        return _serviceDays;
    }


    Service::SERVICE_DAY Service::getServiceDay(const ServiceDate& d)
    {
        return static_cast<SERVICE_DAY>(1 << (((d.getTimeStrc().tm_wday + 6) % 7)));
    }


    Service::EXCEPTION_TYPE Service::getExceptionOn(const ServiceDate& d) const
    {
        auto ex = _exceptions.find(d);
        if (ex != _exceptions.end()) {
            return ex->second;
        }
        return EXCEPTION_TYPE::NOT_SET;
    }


    bool Service::hasServiceDays() const
    {
        return !_begin.empty() && !_end.empty();
    }


    CalendarFields CalendarFields::fromCsvParser(const csv::CsvParser& csvp)
    {
        CalendarFields c;
        c.serviceIdFld = csvp.getFieldIndex("service_id");
        c.mondayFld = csvp.getFieldIndex("monday");
        c.tuesdayFld = csvp.getFieldIndex("tuesday");
        c.wednesdayFld = csvp.getFieldIndex("wednesday");
        c.thursdayFld = csvp.getFieldIndex("thursday");
        c.fridayFld = csvp.getFieldIndex("friday");
        c.saturdayFld = csvp.getFieldIndex("saturday");
        c.sundayFld = csvp.getFieldIndex("sunday");
        c.startDateFld = csvp.getFieldIndex("start_date");
        c.endDateFld = csvp.getFieldIndex("end_date");
        return c;
    }
    CalendarDateFields CalendarDateFields::fromCsvParser(const csv::CsvParser& csvp)
    {
        CalendarDateFields c;
        c.serviceIdFld = csvp.getFieldIndex("service_id");
        c.exceptionTypeFld = csvp.getFieldIndex("exception_type");
        c.dateFld = csvp.getFieldIndex("date");
        return c;
    }
    tm ServiceDateFlat::getTimeStrc() const
    {
        tm ret;
        ret.tm_year = getYear() - 1900;
        ret.tm_mon = getMonth() - 1;
        ret.tm_mday = getDay();
        ret.tm_hour = 12;
        mktime(&ret);
        return ret;
    }
    bool ServiceDateFlat::empty() const
    {
        return _yyyymmdd == 0;
    }
    void ServiceDateFlat::setYear(uint16_t year)
    {
        _yyyymmdd = _yyyymmdd - (getYear() - 1900) * 10000 + (year - 1900) * 10000;
    }
    void ServiceDateFlat::setMonth(uint8_t month)
    {
        _yyyymmdd = _yyyymmdd - getMonth() * 100 + month * 100;
    }
    void ServiceDateFlat::setDay(uint8_t day) { _yyyymmdd = _yyyymmdd - getDay() + day; }
    uint8_t ServiceDateFlat::getDay() const
    {
        return _yyyymmdd - ((getYear() - 1900) * 10000) - (getMonth() * 100);
    }
    uint8_t ServiceDateFlat::getMonth() const
    {
        return (_yyyymmdd - ((getYear() - 1900) * 10000)) / 100;
    }
    uint16_t ServiceDateFlat::getYear() const { return (_yyyymmdd / 10000) + 1900; }
    uint32_t ServiceDateFlat::getYYYYMMDD() const { return _yyyymmdd + (1900 * 10000); }
    ServiceDateFlat::ServiceDateFlat() :
        _yyyymmdd(0) {}
    ServiceDateFlat::ServiceDateFlat(uint8_t day, uint8_t month, uint16_t year) :
        _yyyymmdd((year * 10000 + month * 100 + day) - (1900 * 10000)) {}
    ServiceDateFlat::ServiceDateFlat(uint32_t yyyymmdd) :
        _yyyymmdd(yyyymmdd - (1900 * 10000)) {}
    bool operator>(const ServiceDateFlat& lh, const ServiceDateFlat& rh)
    {
        return lh.getYYYYMMDD() > rh.getYYYYMMDD();
    }
    bool operator<(const ServiceDateFlat& lh, const ServiceDateFlat& rh)
    {
        return rh > lh;
    }
    bool operator==(const ServiceDateFlat& lh, const ServiceDateFlat& rh)
    {
        return !(lh > rh) && !(lh < rh);
    }
    bool operator!=(const ServiceDateFlat& lh, const ServiceDateFlat& rh)
    {
        return !(lh == rh);
    }
    bool operator>=(const ServiceDateFlat& lh, const ServiceDateFlat& rh)
    {
        return lh > rh || lh == rh;
    }
    bool operator<=(const ServiceDateFlat& lh, const ServiceDateFlat& rh)
    {
        return rh > lh || lh == rh;
    }
    ServiceDateFlat operator+(const ServiceDateFlat& lh, int i)
    {
        tm tStrc = lh.getTimeStrc();
        tStrc.tm_mday += i;
        mktime(&tStrc);

        return ServiceDateFlat(tStrc.tm_mday, tStrc.tm_mon + 1, tStrc.tm_year + 1900);
    }
    ServiceDateFlat operator-(const ServiceDateFlat& lh, int i)
    {
        return lh + (-i);
    }
    ServiceDateFlat operator--(ServiceDateFlat& lh)
    {
        ServiceDateFlat ret = lh - 1;
        lh.setDay(ret.getDay());
        lh.setMonth(ret.getMonth());
        lh.setYear(ret.getYear());
        return ret;
    }
    ServiceDateFlat operator++(ServiceDateFlat& lh)
    {
        ServiceDateFlat ret = lh + 1;
        lh.setDay(ret.getDay());
        lh.setMonth(ret.getMonth());
        lh.setYear(ret.getYear());
        return ret;
    }
}    // namespace cppgtfs::gtfs