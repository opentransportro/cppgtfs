// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_TRIP_H_
#define AD_CPPGTFS_GTFS_TRIP_H_

#include <cstdint>
#include <algorithm>
#include <set>
#include <string>
#include "Frequency.h"
#include "Route.h"
#include "Service.h"
#include "Shape.h"
#include "Stop.h"
#include "StopTime.h"

namespace cppgtfs::gtfs
{
    using fieldId = csv::fieldId;
    struct TripFields
    {
        fieldId shapeIdFld;
        fieldId tripIdFld;
        fieldId serviceIdFld;
        fieldId routeIdFld;
        fieldId blockIdFld;
        fieldId tripHeadsignFld;
        fieldId tripShortNameFld;
        fieldId bikesAllowedFld;
        fieldId wheelchairAccessibleFld;
        fieldId directionIdFld;

        // ____________________________________________________________________________
        static TripFields fromCsvParser(const csv::CsvParser& csvp)
        {
            TripFields t;
            t.shapeIdFld = csvp.getOptFieldIndex("shape_id");
            t.tripIdFld = csvp.getFieldIndex("trip_id");
            t.serviceIdFld = csvp.getFieldIndex("service_id");
            t.routeIdFld = csvp.getFieldIndex("route_id");
            t.blockIdFld = csvp.getOptFieldIndex("block_id");
            t.tripHeadsignFld = csvp.getOptFieldIndex("trip_headsign");
            t.tripShortNameFld = csvp.getOptFieldIndex("trip_short_name");
            t.bikesAllowedFld = csvp.getOptFieldIndex("bikes_allowed");
            t.wheelchairAccessibleFld = csvp.getOptFieldIndex("wheelchair_accessible");
            t.directionIdFld = csvp.getOptFieldIndex("direction_id");
            return t;
        }
    };

    struct TripFlat
    {
        enum WC_BIKE_ACCESSIBLE : uint8_t
        {
            NO_INFORMATION = 0,
            AT_LEAST_ONE = 1,
            NOT_ACCESSIBLE = 2
        };

        enum DIRECTION : uint8_t
        {
            OUTBOUND = 0,
            INBOUND = 1,
            NOT_SET = 2
        };

        std::string id;
        std::string route;
        std::string service;
        std::string headsign;
        std::string short_name;
        DIRECTION dir;
        std::string block_id;
        std::string shape;
        WC_BIKE_ACCESSIBLE wc;
        WC_BIKE_ACCESSIBLE ba;
    };

    template<typename StopTimeT, typename ServiceT, typename RouteT, typename ShapeT>
    class TripB
    {
        // typedef std::set<StopTimeT, StopTimeCompare<StopTimeT>> StopTimes;
        using StopTimes = std::vector<StopTimeT>;
        using Frequencies = std::vector<Frequency>;

    public:
        using Ref = TripB<StopTimeT, ServiceT, RouteT, ShapeT> *;

        static std::string getId(Ref r) { return r->getId(); }

        using WC_BIKE_ACCESSIBLE = TripFlat::WC_BIKE_ACCESSIBLE;
        using DIRECTION = TripFlat::DIRECTION;

        TripB() = default;

        TripB(const std::string& id, typename RouteT::Ref r, typename ServiceT::Ref s, const std::string& hs, const std::string& short_name, DIRECTION dir, const std::string& blockid, typename ShapeT::Ref shp, WC_BIKE_ACCESSIBLE wc, WC_BIKE_ACCESSIBLE ba);

        [[nodiscard]] const std::string& getId() const;

        const typename RouteT::Ref getRoute() const;

        typename RouteT::Ref getRoute();

        typename ServiceT::Ref getService();

        const typename ServiceT::Ref getService() const;

        [[nodiscard]] const std::string& getHeadsign() const;

        [[nodiscard]] const std::string& getShortname() const;

        [[nodiscard]] DIRECTION getDirection() const;

        [[nodiscard]] const std::string& getBlockId() const;

        const typename ShapeT::Ref getShape() const;

        typename ShapeT::Ref getShape();

        void setShape(typename ShapeT::Ref shp);

        [[nodiscard]] WC_BIKE_ACCESSIBLE getWheelchairAccessibility() const;

        [[nodiscard]] WC_BIKE_ACCESSIBLE getBikesAllowed() const;

        const StopTimes& getStopTimes() const;

        StopTimes& getStopTimes();

        Frequencies& getFrequencies();

        [[nodiscard]] const Frequencies& getFrequencies() const;

        bool addStopTime(const StopTimeT& t);

        void addFrequency(const Frequency& t);

        [[nodiscard]] gtfs::TripFlat getFlat() const
        {
            return gtfs::TripFlat{
                _id,
                RouteT::getId(_route),
                ServiceT::getId(_service),
                _headsign,
                _short_name,
                _dir,
                _block_id,
                ShapeT::getId(_shape),
                _wc,
                _ba
            };
        };

    private:
        std::string _id{};
        typename RouteT::Ref _route{};
        typename ServiceT::Ref _service{};
        std::string _headsign{};
        std::string _short_name{};
        DIRECTION _dir{};
        std::string _block_id{};
        typename ShapeT::Ref _shape{};
        WC_BIKE_ACCESSIBLE _wc{};
        WC_BIKE_ACCESSIBLE _ba{};

        StopTimes _stoptimes;
        Frequencies _frequencies;
    };

    using Trip = TripB<StopTime<Stop>, Service, Route, Shape>;

#include "Trip.tpp"

}    // namespace cppgtfs::gtfs


#endif    // AD_CPPGTFS_GTFS_TRIP_H_