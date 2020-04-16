//
// Created by vlad on 14.04.2020.
//
#include <ad/cppgtfs/gtfs/flat/Fare.h>

namespace ad::cppgtfs::gtfs::flat
{
    FareRuleFlds FareRuleFlds::fromCsvParser(const util::CsvParser& csvp)
    {
        flat::FareRuleFlds f;
        f.fareIdFld = csvp.getFieldIndex("fare_id");
        f.routeIdFld = csvp.getOptFieldIndex("route_id");
        f.originIdFld = csvp.getOptFieldIndex("origin_id");
        f.destinationIdFld = csvp.getOptFieldIndex("destination_id");
        f.containsIdFld = csvp.getOptFieldIndex("contains_id");
        return f;
    }
    FareFlds FareFlds::fromCsvParser(const CsvParser& csvp)
    {
        flat::FareFlds f;
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
