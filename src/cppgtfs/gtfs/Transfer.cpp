#include <cppgtfs/gtfs/Transfer.h>

namespace cppgtfs::gtfs
{
    TransfersFields TransfersFields::fromCsvParser(const csv::CsvParser& csvp)
    {
        cppgtfs::gtfs::TransfersFields t;
        t.fromStopIdFld = csvp.getFieldIndex("from_stop_id");
        t.toStopIdFld = csvp.getFieldIndex("to_stop_id");
        t.transferTypeFld = csvp.getFieldIndex("transfer_type");
        t.minTransferTimeFld = csvp.getOptFieldIndex("min_transfer_time");
        return t;
    }
}    // namespace cppgtfs::gtfs