#include <ad/cppgtfs/gtfs/flat/Trip.h>

namespace ad::cppgtfs::gtfs::flat
{
    TripFlds TripFlds::fromCsvParser(const CsvParser& csvp)
    {
        flat::TripFlds t;
        t.shapeIdFld = csvp.getOptFieldIndex("shape_id");
        t.tripIdFld = csvp.getFieldIndex("trip_id");
        t.serviceIdFld = csvp.getFieldIndex("service_id");
        t.routeIdFld = csvp.getFieldIndex("route_id");
        t.blockIdFld = csvp.getOptFieldIndex("block_id");
        t.tripHeadsignFld = csvp.getOptFieldIndex("trip_headsign");
        t.tripShortNameFld = csvp.getOptFieldIndex("trip_short_name");
        t.bikesAllowedFld = csvp.getOptFieldIndex("bikes_allowed");
        t.wheelchairAccessibleFld = csvp.getOptFieldIndex("wheelchair_accessible");
        t.directionIdFld = csvp.getOptFieldIndex("direction_id");
        return t;
    }
}
