// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_STOP_H_
#define AD_CPPGTFS_GTFS_STOP_H_

#include <cstdint>
#include <cassert>
#include <string>
#include <utility>
#include "flat/Stop.h"

namespace ad::cppgtfs::gtfs
{
    class Stop
    {
    public:
        using Ref = Stop *;

        static std::string getId(Ref r) { return r->getId(); }

        using LOCATION_TYPE = flat::Stop::LOCATION_TYPE;
        using WHEELCHAIR_BOARDING = flat::Stop::WHEELCHAIR_BOARDING;

        Stop() = default;

        Stop(std::string  id, std::string  code, std::string  name, std::string  desc, float lat, float lng, std::string  zone_id, std::string  stop_url, flat::Stop::LOCATION_TYPE location_type, Stop* parent_station, std::string  stop_timezone, flat::Stop::WHEELCHAIR_BOARDING wheelchair_boarding, std::string  platform_code) :
            _id(std::move(id)),
            _code(std::move(code)),
            _name(std::move(name)),
            _desc(std::move(desc)),
            _zone_id(std::move(zone_id)),
            _stop_url(std::move(stop_url)),
            _stop_timezone(std::move(stop_timezone)),
            _platform_code(std::move(platform_code)),
            _parent_station(parent_station),
            _lat(lat),
            _lng(lng),
            _wheelchair_boarding(wheelchair_boarding),
            _location_type(location_type) {}

        [[nodiscard]] const std::string& getId() const { return _id; }

        [[nodiscard]] const std::string& getCode() const { return _code; }

        [[nodiscard]] const std::string& getName() const { return _name; }

        [[nodiscard]] const std::string& getPlatformCode() const { return _platform_code; }

        [[nodiscard]] const std::string& getDesc() const { return _desc; }

        [[nodiscard]] float getLat() const { return _lat; }

        [[nodiscard]] float getLng() const { return _lng; }

        [[nodiscard]] const std::string& getZoneId() const { return _zone_id; }

        [[nodiscard]] const std::string& getStopUrl() const { return _stop_url; }

        [[nodiscard]] flat::Stop::LOCATION_TYPE getLocationType() const { return _location_type; }

        [[nodiscard]] const Stop* getParentStation() const { return _parent_station; }

        Stop* getParentStation() { return _parent_station; }

        void setParentStation(Stop* p) { _parent_station = p; }

        [[nodiscard]] const std::string& getStopTimezone() const { return _stop_timezone; }

        [[nodiscard]] flat::Stop::WHEELCHAIR_BOARDING getWheelchairBoarding() const
        {
            return _wheelchair_boarding;
        }

        [[nodiscard]] flat::Stop getFlat() const
        {
            flat::Stop r;
            r.id = _id;
            r.code = _code;
            r.name = _name;
            r.desc = _desc;
            r.zone_id = _zone_id;
            r.stop_url = _stop_url;
            r.stop_timezone = _stop_timezone;
            r.platform_code = _platform_code;
            r.parent_station = (_parent_station != nullptr ? _parent_station->getId() : "");
            r.lat = _lat;
            r.lng = _lng;
            r.wheelchair_boarding = _wheelchair_boarding;
            r.location_type = _location_type;
            return r;
        }

        // TODO(patrick): implement setters

    private:
        std::string _id{};
        std::string _code{};
        std::string _name{};
        std::string _desc{};
        std::string _zone_id{};
        std::string _stop_url{};
        std::string _stop_timezone{};
        std::string _platform_code{};
        Stop* _parent_station{};
        float _lat{};
        float _lng{};
        flat::Stop::WHEELCHAIR_BOARDING _wheelchair_boarding;
        flat::Stop::LOCATION_TYPE _location_type;
    };

}    // namespace ad::cppgtfs::gtfs

#endif    // AD_CPPGTFS_GTFS_STOP_H_
