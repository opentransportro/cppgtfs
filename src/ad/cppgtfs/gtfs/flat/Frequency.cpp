//
// Created by vlad on 14.04.2020.
//
#include <ad/cppgtfs/gtfs/flat/Frequency.h>

namespace ad::cppgtfs::gtfs::flat
{
    FrequencyFlds FrequencyFlds::fromCsvParser(const CsvParser& csvp)
    {
        flat::FrequencyFlds r;
        r.tripIdFld = csvp.getFieldIndex("trip_id");
        r.startTimeFld = csvp.getFieldIndex("start_time");
        r.endTimeFld = csvp.getFieldIndex("end_time");
        r.headwaySecsFld = csvp.getFieldIndex("headway_secs");
        r.exactTimesFld = csvp.getOptFieldIndex("exact_times");
        return r;
    }
}
