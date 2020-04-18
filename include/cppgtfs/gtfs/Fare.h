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

        FareRule(Route::Ref route, std::string originId, std::string destId, std::string containsId);

        Route::Ref getRoute() const;

        [[nodiscard]] const std::string& getOriginId() const;

        [[nodiscard]] const std::string& getDestId() const;

        [[nodiscard]] const std::string& getContainsId() const;


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

        Fare() = default;

        explicit Fare(std::string id, double price, std::string currencyType, PAYMENT_METHOD paymentMethod, NUM_TRANSFERS numTransfers, Agency* agency, int64_t dur);

        [[nodiscard]] const std::string& getId() const;

        [[nodiscard]] double getPrice() const;

        [[nodiscard]] const std::string& getCurrencyType() const;

        [[nodiscard]] PAYMENT_METHOD getPaymentMethod() const;

        [[nodiscard]] NUM_TRANSFERS getNumTransfers() const;

        [[nodiscard]] Agency* getAgency() const;

        [[nodiscard]] int64_t getDuration() const;

        const std::vector<FareRule>& getFareRules() const;

        void addFareRule(const FareRule& rule);

        [[nodiscard]] Flat getFlat() const;

        void setId(const std::string& id);
        void setPrice(double price);
        void setCurrencyType(const std::string& currencyType);
        void setPaymentMethod(PAYMENT_METHOD paymentMethod);
        void setNumTransfers(NUM_TRANSFERS numTransfers);
        void setAgency(Agency* agency);
        void setDuration(int64_t duration);

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
