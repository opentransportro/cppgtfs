//
// Created by vvesa on 17.04.2020.
//
#include <cppgtfs/gtfs/StopTime.h>

namespace cppgtfs::gtfs
{
    StopTime::Fields StopTime::Fields::fromCsvParser(const csv::CsvParser& csvp)
    {
        StopTime::Fields s;
        s.stopIdFld = csvp.getFieldIndex("stop_id");
        s.tripIdFld = csvp.getFieldIndex("trip_id");
        s.arrivalTimeFld = csvp.getFieldIndex("arrival_time");
        s.departureTimeFld = csvp.getFieldIndex("departure_time");
        s.stopSequenceFld = csvp.getFieldIndex("stop_sequence");
        s.stopHeadsignFld = csvp.getOptFieldIndex("stop_headsign");
        s.shapeDistTraveledFld = csvp.getOptFieldIndex("shape_dist_traveled");
        s.timepointFld = csvp.getOptFieldIndex("timepoint");
        s.pickUpTypeFld = csvp.getOptFieldIndex("pickup_type");
        s.dropOffTypeFld = csvp.getOptFieldIndex("drop_off_type");
        return s;
    }
    StopTime::StopTime(const Time& at, const Time& dt, Stop::Ref s, uint32_t seq, const std::string& hs, StopTime::PU_DO_TYPE put, StopTime::PU_DO_TYPE dot, float distTrav, bool isTp) :
        _at(at),
        _dt(dt),
        _s(s),
        _sequence(seq),
        _headsign(hs),
        _pickupType(put),
        _dropOffType(dot),
        _isTimepoint(isTp),
        _shapeDistTravelled(distTrav) {}
    const Time& StopTime::getArrivalTime() const { return _at; }
    const Time& StopTime::getDepartureTime() const { return _dt; }
    Stop::Ref StopTime::getStop() const { return _s; }
    Stop::Ref StopTime::getStop() { return _s; }
    const std::string& StopTime::getHeadsign() const { return _headsign; }
    StopTime::PU_DO_TYPE StopTime::getPickupType() const
    {
        return static_cast<PU_DO_TYPE>(_pickupType);
    }
    StopTime::PU_DO_TYPE StopTime::getDropOffType() const
    {
        return static_cast<PU_DO_TYPE>(_dropOffType);
    }
    float StopTime::getShapeDistanceTravelled() const { return _shapeDistTravelled; }
    void StopTime::setShapeDistanceTravelled(double d) { _shapeDistTravelled = d; }
    bool StopTime::isTimepoint() const { return _isTimepoint; }
    uint16_t StopTime::getSeq() const { return _sequence; }
    bool StopTimeCompare::operator()(const StopTime& lh, const StopTime& rh) const
    {
        return lh.getSeq() < rh.getSeq();
    }
}    // namespace cppgtfs::gtfs