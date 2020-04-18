// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_FEED_H_
#define AD_CPPGTFS_GTFS_FEED_H_

#include <iterator>
#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

#include "cppgtfs/containers/ContContainer.h"
#include "cppgtfs/containers/Container.h"

#include "Agency.h"
#include "Fare.h"
#include "Route.h"
#include "Service.h"
#include "Shape.h"
#include "Stop.h"
#include "Transfer.h"
#include "Trip.h"

#define FEEDTPL             \
    template<template<typename> class ContainerT>
#define FEEDB \
    FeedBase<ContainerT>

namespace cppgtfs::gtfs
{
    template<
        template<typename> class ContainerT
    >
    class FeedBase
    {
    public:
        using Agencies = ContainerT<Agency>;
        using Stops = ContainerT<Stop>;
        using Routes = ContainerT<Route>;
        using Trips = ContainerT<Trip>;
        using Shapes = ContainerT<Shape>;
        using Services = ContainerT<Service>;
        using Fares = ContainerT<Fare>;
        using Transfers = std::vector<Transfer>;
        using Zones = std::set<std::string>;

        FeedBase() :
            _maxLat(std::numeric_limits<double>::lowest()),
            _maxLon(std::numeric_limits<double>::lowest()),
            _minLat(std::numeric_limits<double>::max()),
            _minLon(std::numeric_limits<double>::max())
        {}

        const Agencies& getAgencies() const
        {
            return _agencies;
        }

        Agencies& getAgencies()
        {
            return _agencies;
        }

        const Stops& getStops() const
        {
            return _stops;
        }
        Stops& getStops()
        {
            return _stops;
        }

        const Routes& getRoutes() const
        {
            return _routes;
        }
        Routes& getRoutes()
        {
            return _routes;
        }

        const Trips& getTrips() const
        {
            return _trips;
        }
        Trips& getTrips()
        {
            return _trips;
        }

        const Shapes& getShapes() const
        {
            return _shapes;
        }
        Shapes& getShapes()
        {
            return _shapes;
        }
        const Services& getServices() const
        {
            return _services;
        }
        Services& getServices()
        {
            return _services;
        }

        const Transfers& getTransfers() const
        {
            return _transfers;
        }
        Transfers& getTransfers()
        {
            return _transfers;
        }

        [[nodiscard]] const Zones& getZones() const
        {
            return _zones;
        }
        Zones& getZones()
        {
            return _zones;
        }

        const Fares& getFares() const
        {
            return _fares;
        }
        Fares& getFares()
        {
            return _fares;
        }

        [[nodiscard]] const std::string& getPublisherName() const
        {
            return _publisherName;
        }
        [[nodiscard]] const std::string& getPublisherUrl() const
        {
            return _publisherUrl;
        }
        [[nodiscard]] const std::string& getLang() const
        {
            return _lang;
        }
        [[nodiscard]] const std::string& getVersion() const
        {
            return _version;
        }
        [[nodiscard]] const ServiceDate& getStartDate() const
        {
            return _startDate;
        }
        [[nodiscard]] const ServiceDate& getEndDate() const
        {
            return _endDate;
        }

        void setPublisherName(const std::string& name)
        {
            _publisherName = name;
        }
        void setPublisherUrl(const std::string& url)
        {
            _publisherUrl = url;
        }
        void setLang(const std::string& lang)
        {
            _lang = lang;
        }
        void setVersion(const std::string& version)
        {
            _version = version;
        }
        void setStartDate(const ServiceDate& start)
        {
            _startDate = start;
        }
        void setEndDate(const ServiceDate& end)
        {
            _endDate = end;
        }

        void updateBox(double lat, double lon)
        {
            if (lat > _maxLat) _maxLat = lat;
            if (lon > _maxLon) _maxLon = lon;
            if (lat < _minLat) _minLat = lat;
            if (lon < _minLon) _minLon = lon;
        }
        [[nodiscard]] double getMinLat() const
        {
            return _minLat;
        }
        [[nodiscard]] double getMinLon() const
        {
            return _minLon;
        }
        [[nodiscard]] double getMaxLat() const
        {
            return _maxLat;
        }
        [[nodiscard]] double getMaxLon() const
        {
            return _maxLon;
        }

        [[nodiscard]] const std::string& getPath() const { return _path; }
        void setPath(const std::string& p) { _path = p; }

    private:
        Agencies _agencies;
        Stops _stops;
        Routes _routes;
        Trips _trips;
        Shapes _shapes;
        Services _services;
        Transfers _transfers;
        Zones _zones;
        Fares _fares;

        double _maxLat, _maxLon, _minLat, _minLon;

        std::string _publisherName, _publisherUrl, _lang, _version, _path;
        ServiceDate _startDate, _endDate;
    };

    using Feed = FeedBase<Container>;
    using ContFeed = FeedBase<ContContainer>;

}    // namespace cppgtfs::gtfs

#endif    // AD_CPPGTFS_GTFS_FEED_H_
