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
}    // namespace cppgtfs::gtfs