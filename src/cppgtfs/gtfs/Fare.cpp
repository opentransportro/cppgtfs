#include <cppgtfs/gtfs/Fare.h>

namespace cppgtfs::gtfs
{
    FareRuleFields cppgtfs::gtfs::FareRuleFields::fromCsvParser(const csv::CsvParser& csvp)

    {
        FareRuleFields f;
        f.fareIdFld = csvp.getFieldIndex("fare_id");
        f.routeIdFld = csvp.getOptFieldIndex("route_id");
        f.originIdFld = csvp.getOptFieldIndex("origin_id");
        f.destinationIdFld = csvp.getOptFieldIndex("destination_id");
        f.containsIdFld = csvp.getOptFieldIndex("contains_id");
        return f;
    }
    FareFields cppgtfs::gtfs::FareFields::fromCsvParser(const csv::CsvParser& csvp)
    {
        FareFields f;
        f.fareIdFld = csvp.getFieldIndex("fare_id");
        f.priceFld = csvp.getFieldIndex("price");
        f.currencyTypeFld = csvp.getFieldIndex("currency_type");
        f.paymentMethodFld = csvp.getFieldIndex("payment_method");
        f.transfersFld = csvp.getFieldIndex("transfers");
        f.agencyFld = csvp.getOptFieldIndex("agency");
        f.transferDurationFld = csvp.getOptFieldIndex("transfer_duration");
        return f;
    }
}
