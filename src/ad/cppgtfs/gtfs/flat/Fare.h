// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_FLAT_FARE_H_
#define AD_CPPGTFS_GTFS_FLAT_FARE_H_

#include <string>
#include <vector>
#include <ad/util/CsvParser.h>
using namespace ad::util;

namespace ad::cppgtfs::gtfs::flat
{
    struct FareRuleFlds
    {
        fieldId fareIdFld;
        fieldId routeIdFld;
        fieldId originIdFld;
        fieldId destinationIdFld;
        fieldId containsIdFld;

        static FareRuleFlds fromCsvParser(const util::CsvParser& csvp);
    };

    struct FareRule
    {
        std::string fare;
        std::string route;
        std::string originZone;
        std::string destZone;
        std::string containsZone;
    };

    struct FareFlds
    {
        fieldId fareIdFld;
        fieldId priceFld;
        fieldId currencyTypeFld;
        fieldId paymentMethodFld;
        fieldId transfersFld;
        fieldId agencyFld;
        fieldId transferDurationFld;

        // ____________________________________________________________________________
        static FareFlds fromCsvParser(const util::CsvParser& csvp);
    };

    struct Fare
    {
        enum PAYMENT_METHOD : bool
        {
            ON_BOARD = 0,
            BEFORE_BOARDING = 1
        };

        enum NUM_TRANSFERS : uint8_t
        {
            NO_TRANSFERS = 0,
            ONCE = 1,
            TWICE = 2,
            UNLIMITED = 3
        };

        std::string id;
        double price;
        std::string currencyType;
        PAYMENT_METHOD paymentMethod;
        NUM_TRANSFERS numTransfers;
        std::string agency;
        int64_t duration;
    };

}    // namespace ad

#endif    // AD_CPPGTFS_GTFS_FLAT_FARE_H_
