#include <ad/cppgtfs/gtfs/flat/StopTime.h>

namespace ad::cppgtfs::gtfs::flat
{
    flat::StopTimeFlds StopTimeFlds::fromCsvParser(const CsvParser& csvp)
    {
        flat::StopTimeFlds s;
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
}
