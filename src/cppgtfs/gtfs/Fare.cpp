#include <cppgtfs/gtfs/Fare.h>

namespace cppgtfs::gtfs
{
    FareRule::Fields cppgtfs::gtfs::FareRule::Fields::fromCsvParser(const csv::CsvParser& csvp)

    {
        FareRule::Fields f;
        f.fareIdFld = csvp.getFieldIndex("fare_id");
        f.routeIdFld = csvp.getOptFieldIndex("route_id");
        f.originIdFld = csvp.getOptFieldIndex("origin_id");
        f.destinationIdFld = csvp.getOptFieldIndex("destination_id");
        f.containsIdFld = csvp.getOptFieldIndex("contains_id");
        return f;
    }
    Fare::Fields cppgtfs::gtfs::Fare::Fields::fromCsvParser(const csv::CsvParser& csvp)
    {
        Fare::Fields f;
        f.fareIdFld = csvp.getFieldIndex("fare_id");
        f.priceFld = csvp.getFieldIndex("price");
        f.currencyTypeFld = csvp.getFieldIndex("currency_type");
        f.paymentMethodFld = csvp.getFieldIndex("payment_method");
        f.transfersFld = csvp.getFieldIndex("transfers");
        f.agencyFld = csvp.getOptFieldIndex("agency");
        f.transferDurationFld = csvp.getOptFieldIndex("transfer_duration");
        return f;
    }
}    // namespace cppgtfs::gtfs
