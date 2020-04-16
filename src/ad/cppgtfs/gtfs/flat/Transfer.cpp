#include <ad/cppgtfs/gtfs/flat/Transfer.h>

namespace ad::cppgtfs::gtfs::flat
{
    TransfersFlds TransfersFlds::fromCsvParser(const CsvParser& csvp)
    {
        flat::TransfersFlds t;
        t.fromStopIdFld = csvp.getFieldIndex("from_stop_id");
        t.toStopIdFld = csvp.getFieldIndex("to_stop_id");
        t.transferTypeFld = csvp.getFieldIndex("transfer_type");
        t.minTransferTimeFld = csvp.getOptFieldIndex("min_transfer_time");
        return t;
    }
}
