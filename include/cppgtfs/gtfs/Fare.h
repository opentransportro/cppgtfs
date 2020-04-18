// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_FARE_H_
#define AD_CPPGTFS_GTFS_FARE_H_

#include <string>
#include <utility>
#include <vector>
#include "Agency.h"
#include "Route.h"

namespace cppgtfs::gtfs
{
    class FareRule
    {
    public:
        struct Fields
        {
            fieldId fareIdFld;
            fieldId routeIdFld;
            fieldId originIdFld;
            fieldId destinationIdFld;
            fieldId containsIdFld;

            static Fields fromCsvParser(const csv::CsvParser& csvp);
        };

        struct Flat
        {
            std::string fare;
            std::string route;
            std::string originZone;
            std::string destZone;
            std::string containsZone;
        };


        FareRule() = default;

        FareRule(Route::Ref route, std::string originId, std::string destId, std::string containsId) :
            _route(route),
            _originId(std::move(originId)),
            _destId(std::move(destId)),
            _containsId(std::move(containsId)) {}

        Route::Ref getRoute() const { return _route; }

        [[nodiscard]] const std::string& getOriginId() const { return _originId; }

        [[nodiscard]] const std::string& getDestId() const { return _destId; }

        [[nodiscard]] const std::string& getContainsId() const { return _containsId; }


    private:
        Route::Ref _route;
        std::string _originId;
        std::string _destId;
        std::string _containsId;
    };


    class Fare
    {
    public:
        struct Fields
        {
            fieldId fareIdFld;
            fieldId priceFld;
            fieldId currencyTypeFld;
            fieldId paymentMethodFld;
            fieldId transfersFld;
            fieldId agencyFld;
            fieldId transferDurationFld;

            static Fields fromCsvParser(const csv::CsvParser& csvp);
        };

        struct Flat
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

        using Ref = Fare*;

        using PAYMENT_METHOD = Flat::PAYMENT_METHOD;
        using NUM_TRANSFERS = Flat::NUM_TRANSFERS;

        static std::string getId(Ref r) { return r->getId(); }

        Fare() = default;

        explicit Fare(std::string id, double price, std::string currencyType, PAYMENT_METHOD paymentMethod, NUM_TRANSFERS numTransfers, Agency* agency, int64_t dur) :
            _id(std::move(id)),
            _price(price),
            _currencyType(std::move(currencyType)),
            _paymentMethod(paymentMethod),
            _numTransfers(numTransfers),
            _agency(agency),
            _duration(dur) {}

        [[nodiscard]] const std::string& getId() const { return _id; }

        [[nodiscard]] double getPrice() const { return _price; }

        [[nodiscard]] const std::string& getCurrencyType() const { return _currencyType; }

        [[nodiscard]] PAYMENT_METHOD getPaymentMethod() const { return _paymentMethod; }

        [[nodiscard]] NUM_TRANSFERS getNumTransfers() const { return _numTransfers; }

        [[nodiscard]] Agency* getAgency() const { return _agency; }

        [[nodiscard]] int64_t getDuration() const { return _duration; }

        const std::vector<FareRule>& getFareRules() const
        {
            return _fareRules;
        }

        void addFareRule(const FareRule& rule) { _fareRules.push_back(rule); }

        [[nodiscard]] Flat getFlat() const
        {
            return { _id, _price, _currencyType, _paymentMethod, _numTransfers, _agency != nullptr ? _agency->getId() : "", _duration };
        }

        void setId(const std::string& id)
        {
            _id = id;
        }
        void setPrice(double price)
        {
            _price = price;
        }
        void setCurrencyType(const std::string& currencyType)
        {
            _currencyType = currencyType;
        }
        void setPaymentMethod(PAYMENT_METHOD paymentMethod)
        {
            _paymentMethod = paymentMethod;
        }
        void setNumTransfers(NUM_TRANSFERS numTransfers)
        {
            _numTransfers = numTransfers;
        }
        void setAgency(Agency* agency)
        {
            _agency = agency;
        }
        void setDuration(int64_t duration)
        {
            _duration = duration;
        }

    private:
        std::string _id{};
        double _price{ 0.0 };
        std::string _currencyType{};
        PAYMENT_METHOD _paymentMethod{};
        NUM_TRANSFERS _numTransfers{};
        Agency* _agency{ nullptr };
        int64_t _duration{ 0 };

        std::vector<FareRule> _fareRules;
    };

}    // namespace cppgtfs::gtfs

#endif    // AD_CPPGTFS_GTFS_FARE_H_
