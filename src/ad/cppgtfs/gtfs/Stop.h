// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_STOP_H_
#define AD_CPPGTFS_GTFS_STOP_H_

#include <stdint.h>
#include <cassert>
#include <string>
#include "flat/Stop.h"

using std::exception;
using std::string;

namespace ad::cppgtfs::gtfs
{
    class Stop
    {
    public:
        typedef Stop* Ref;

        static std::string getId(Ref r) { return r->getId(); }

        typedef flat::Stop::LOCATION_TYPE LOCATION_TYPE;
        typedef flat::Stop::WHEELCHAIR_BOARDING WHEELCHAIR_BOARDING;

        Stop() {}

        Stop(const string& id, const string& code, const string& name, const string& desc, float lat, float lng, string zone_id, const string& stop_url, flat::Stop::LOCATION_TYPE location_type, Stop* parent_station, const string& stop_timezone, flat::Stop::WHEELCHAIR_BOARDING wheelchair_boarding, const std::string& platform_code) :
            _id(id),
            _code(code),
            _name(name),
            _desc(desc),
            _zone_id(zone_id),
            _stop_url(stop_url),
            _stop_timezone(stop_timezone),
            _platform_code(platform_code),
            _parent_station(parent_station),
            _lat(lat),
            _lng(lng),
            _wheelchair_boarding(wheelchair_boarding),
            _location_type(location_type) {}

        const std::string& getId() const { return _id; }

        const std::string& getCode() const { return _code; }

        const std::string& getName() const { return _name; }

        const std::string& getPlatformCode() const { return _platform_code; }

        const std::string& getDesc() const { return _desc; }

        float getLat() const { return _lat; }

        float getLng() const { return _lng; }

        const std::string& getZoneId() const { return _zone_id; }

        const std::string& getStopUrl() const { return _stop_url; }

        flat::Stop::LOCATION_TYPE getLocationType() const { return _location_type; }

        const Stop* getParentStation() const { return _parent_station; }

        Stop* getParentStation() { return _parent_station; }

        void setParentStation(Stop* p) { _parent_station = p; }

        const std::string& getStopTimezone() const { return _stop_timezone; }

        flat::Stop::WHEELCHAIR_BOARDING getWheelchairBoarding() const
        {
            return _wheelchair_boarding;
        }

        flat::Stop getFlat() const
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
            r.parent_station = (_parent_station ? _parent_station->getId() : "");
            r.lat = _lat;
            r.lng = _lng;
            r.wheelchair_boarding = _wheelchair_boarding;
            r.location_type = _location_type;
            return r;
        }

        // TODO(patrick): implement setters

    private:
        string _id, _code, _name, _desc, _zone_id, _stop_url, _stop_timezone,
            _platform_code;
        Stop* _parent_station;
        float _lat, _lng;
        flat::Stop::WHEELCHAIR_BOARDING _wheelchair_boarding;
        flat::Stop::LOCATION_TYPE _location_type;
    };

}    // namespace ad::cppgtfs::gtfs

#endif    // AD_CPPGTFS_GTFS_STOP_H_
