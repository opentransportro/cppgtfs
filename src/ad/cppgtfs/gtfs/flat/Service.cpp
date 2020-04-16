//
// Created by vlad on 14.04.2020.
//
#include <ad/cppgtfs/gtfs/flat/Service.h>

namespace ad::cppgtfs::gtfs::flat
{
    CalendarFlds CalendarFlds::fromCsvParser(const CsvParser& csvp)
    {
        flat::CalendarFlds c;
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
    CalendarDateFlds CalendarDateFlds::fromCsvParser(const CsvParser& csvp)
    {
        flat::CalendarDateFlds c;
        c.serviceIdFld = csvp.getFieldIndex("service_id");
        c.exceptionTypeFld = csvp.getFieldIndex("exception_type");
        c.dateFld = csvp.getFieldIndex("date");
        return c;
    }
    tm ServiceDate::getTimeStrc() const
    {
        tm ret;
        ret.tm_year = getYear() - 1900;
        ret.tm_mon = getMonth() - 1;
        ret.tm_mday = getDay();
        ret.tm_hour = 12;
        mktime(&ret);
        return ret;
    }
    bool operator>(const ServiceDate& lh, const ServiceDate& rh)
    {
        return lh.getYYYYMMDD() > rh.getYYYYMMDD();
    }
    bool operator<(const ServiceDate& lh, const ServiceDate& rh)
    {
        return rh > lh;
    }
    bool operator==(const ServiceDate& lh, const ServiceDate& rh)
    {
        return !(lh > rh) && !(lh < rh);
    }
    bool operator!=(const ServiceDate& lh, const ServiceDate& rh)
    {
        return !(lh == rh);
    }
    bool operator>=(const ServiceDate& lh, const ServiceDate& rh)
    {
        return lh > rh || lh == rh;
    }
    bool operator<=(const ServiceDate& lh, const ServiceDate& rh)
    {
        return rh > lh || lh == rh;
    }
    ServiceDate operator+(const ServiceDate& lh, int i)
    {
        tm tStrc = lh.getTimeStrc();
        tStrc.tm_mday += i;
        mktime(&tStrc);

        return ServiceDate(tStrc.tm_mday, tStrc.tm_mon + 1, tStrc.tm_year + 1900);
    }
    ServiceDate operator-(const ServiceDate& lh, int i)
    {
        return lh + (-i);
    }
    ServiceDate operator--(ServiceDate& lh)
    {
        ServiceDate ret = lh - 1;
        lh.setDay(ret.getDay());
        lh.setMonth(ret.getMonth());
        lh.setYear(ret.getYear());
        return ret;
    }
    ServiceDate operator++(ServiceDate& lh)
    {
        ServiceDate ret = lh + 1;
        lh.setDay(ret.getDay());
        lh.setMonth(ret.getMonth());
        lh.setYear(ret.getYear());
        return ret;
    }
    bool ServiceDate::empty() const
    {
        return _yyyymmdd == 0;
    }
    void ServiceDate::setYear(uint16_t year)
    {
        _yyyymmdd = _yyyymmdd - (getYear() - 1900) * 10000 + (year - 1900) * 10000;
    }
    void ServiceDate::setMonth(uint8_t month)
    {
        _yyyymmdd = _yyyymmdd - getMonth() * 100 + month * 100;
    }
    void ServiceDate::setDay(uint8_t day) { _yyyymmdd = _yyyymmdd - getDay() + day; }
    uint8_t ServiceDate::getDay() const
    {
        return _yyyymmdd - ((getYear() - 1900) * 10000) - (getMonth() * 100);
    }
    uint8_t ServiceDate::getMonth() const
    {
        return (_yyyymmdd - ((getYear() - 1900) * 10000)) / 100;
    }
    uint16_t ServiceDate::getYear() const { return (_yyyymmdd / 10000) + 1900; }
    uint32_t ServiceDate::getYYYYMMDD() const { return _yyyymmdd + (1900 * 10000); }
    ServiceDate::ServiceDate() :
        _yyyymmdd(0) {}
    ServiceDate::ServiceDate(uint8_t day, uint8_t month, uint16_t year) :
        _yyyymmdd((year * 10000 + month * 100 + day) - (1900 * 10000)) {}
    ServiceDate::ServiceDate(uint32_t yyyymmdd) :
        _yyyymmdd(yyyymmdd - (1900 * 10000)) {}
}
