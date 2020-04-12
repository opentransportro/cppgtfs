// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_FLAT_FARE_H_
#define AD_CPPGTFS_GTFS_FLAT_FARE_H_

#include <string>
#include <vector>

using std::exception;
using std::string;

namespace ad::cppgtfs::gtfs::flat
{
    struct FareRuleFlds
    {
        size_t fareIdFld;
        size_t routeIdFld;
        size_t originIdFld;
        size_t destinationIdFld;
        size_t containsIdFld;
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
        size_t fareIdFld;
        size_t priceFld;
        size_t currencyTypeFld;
        size_t paymentMethodFld;
        size_t transfersFld;
        size_t agencyFld;
        size_t transferDurationFld;
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
