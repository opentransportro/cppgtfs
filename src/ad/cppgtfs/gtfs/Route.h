// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_ROUTE_H_
#define AD_CPPGTFS_GTFS_ROUTE_H_

#include <cstdint>
#include <algorithm>
#include <iomanip>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include "Agency.h"
#include "flat/Route.h"

using std::exception;

namespace ad::cppgtfs::gtfs
{
    template<typename AgencyT>
    class RouteB
    {
    public:
        using Ref = RouteB<AgencyT> *;
        using TYPE = flat::Route::TYPE;

        static std::string getId(Ref r) { return r->getId(); }

        RouteB() = default;

        explicit RouteB(std::string  id, typename AgencyT::Ref agency, std::string  short_name, std::string  long_name, std::string  desc, flat::Route::TYPE type, std::string  url, uint32_t color, uint32_t text_color) :
            _id(std::move(id)),
            _agency(agency),
            _short_name(std::move(short_name)),
            _long_name(std::move(long_name)),
            _desc(std::move(desc)),
            _type(type),
            _url(std::move(url)),
            _color(color),
            _text_color(text_color) {}

        [[nodiscard]] const std::string& getId() const { return _id; }

        const typename AgencyT::Ref getAgency() const { return _agency; }

        typename AgencyT::Ref getAgency() { return _agency; }

        [[nodiscard]] const std::string& getShortName() const { return _short_name; }

        [[nodiscard]] const std::string& getLongName() const { return _long_name; }

        [[nodiscard]] const std::string& getDesc() const { return _desc; }

        [[nodiscard]] flat::Route::TYPE getType() const { return _type; }

        [[nodiscard]] const std::string& getUrl() const { return _url; }

        [[nodiscard]] uint32_t getColor() const { return _color; }

        [[nodiscard]] std::string getColorString() const
        {
            return flat::Route::getHexColorString(_color);
        }

        [[nodiscard]] uint32_t getTextColor() const { return _text_color; }

        [[nodiscard]] std::string getTextColorString() const
        {
            return flat::Route::getHexColorString(_text_color);
        }

        [[nodiscard]] flat::Route getFlat() const
        {
            flat::Route r;
            r.id = _id;
            r.agency = _agency->getId();
            r.short_name = _short_name;
            r.long_name = _long_name;
            r.desc = _desc;
            r.type = _type;
            r.url = _url;
            r.color = _color;
            r.text_color = _text_color;
            return r;
        }

        void setId(const std::string& id)
        {
            _id = id;
        }
        void setAgency(Ref agency)
        {
            _agency = agency;
        }
        void setShortName(const std::string& shortName)
        {
            _short_name = shortName;
        }
        void setLongName(const std::string& longName)
        {
            _long_name = longName;
        }
        void setDesc(const std::string& desc)
        {
            _desc = desc;
        }
        void setType(TYPE type)
        {
            _type = type;
        }
        void setUrl(const std::string& url)
        {
            _url = url;
        }
        void setColor(uint32_t color)
        {
            _color = color;
        }
        void setTextColor(uint32_t textColor)
        {
            _text_color = textColor;
        }

    private:
        std::string _id;
        typename AgencyT::Ref _agency;
        std::string _short_name;
        std::string _long_name;
        std::string _desc;
        flat::Route::TYPE _type;
        std::string _url;
        uint32_t _color;
        uint32_t _text_color;
    };

    using Route = RouteB<Agency>;

}    // namespace ad::cppgtfs::gtfs

#endif    // AD_CPPGTFS_GTFS_ROUTE_H_
