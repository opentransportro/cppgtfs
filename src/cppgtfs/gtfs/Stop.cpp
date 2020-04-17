#include <cppgtfs/gtfs/Stop.h>
namespace cppgtfs::gtfs
{
    StopFields StopFields::fromCsvParser(const csv::CsvParser& csvp)
    {
        StopFields r;
        r.stopIdFld = csvp.getFieldIndex("stop_id");
        r.stopNameFld = csvp.getFieldIndex("stop_name");
        r.stopLatFld = csvp.getFieldIndex("stop_lat");
        r.stopLonFld = csvp.getFieldIndex("stop_lon");
        r.parentStationFld = csvp.getOptFieldIndex("parent_station");
        r.stopCodeFld = csvp.getOptFieldIndex("stop_code");
        r.stopDescFld = csvp.getOptFieldIndex("stop_desc");
        r.zoneIdFld = csvp.getOptFieldIndex("zone_id");
        r.stopUrlFld = csvp.getOptFieldIndex("stop_url");
        r.stopTimezoneFld = csvp.getOptFieldIndex("stop_timezone");
        r.wheelchairBoardingFld = csvp.getOptFieldIndex("wheelchair_boarding");
        r.locationTypeFld = csvp.getOptFieldIndex("location_type");
        r.platformCodeFld = csvp.getOptFieldIndex("platform_code");
        return r;
    }
}    // namespace cppgtfs::gtfs