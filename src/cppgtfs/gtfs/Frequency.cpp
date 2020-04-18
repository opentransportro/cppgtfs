#include <csv/CsvParser.h>
#include <cppgtfs/gtfs/Frequency.h>

namespace cppgtfs::gtfs
{
    Frequency::Fields Frequency::Fields::fromCsvParser(const csv::CsvParser& csvp)
    {
        Frequency::Fields r;
        r.tripIdFld = csvp.getFieldIndex("trip_id");
        r.startTimeFld = csvp.getFieldIndex("start_time");
        r.endTimeFld = csvp.getFieldIndex("end_time");
        r.headwaySecsFld = csvp.getFieldIndex("headway_secs");
        r.exactTimesFld = csvp.getOptFieldIndex("exact_times");
        return r;
    }
    Frequency::Frequency(const Time& startTime, const Time& endTime, uint16_t headwaySecs, bool exactTimes) :
        _startTime(startTime),
        _endTime(endTime),
        _headwaySecs(headwaySecs),
        _exactTimes(exactTimes) {}
    const Time& Frequency::getStartTime() const { return _startTime; }
    const Time& Frequency::getEndTime() const { return _endTime; }
    uint16_t Frequency::getHeadwaySecs() const { return _headwaySecs; }
    bool Frequency::hasExactTimes() const { return _exactTimes; }
    void Frequency::setStartTime(const Time& startTime)
    {
        _startTime = startTime;
    }
    void Frequency::setEndTime(const Time& endTime)
    {
        _endTime = endTime;
    }
    void Frequency::setHeadwaySecs(uint16_t headwaySecs)
    {
        _headwaySecs = headwaySecs;
    }
    void Frequency::setExactTimes(bool exactTimes)
    {
        _exactTimes = exactTimes;
    }
}    // namespace cppgtfs::gtfs
