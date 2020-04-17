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

#include <csv/CsvParser.h>

using std::exception;

namespace cppgtfs::gtfs
{
    using fieldId = csv::fieldId;

    struct RouteFields
    {
        fieldId routeIdFld;
        fieldId routeLongNameFld;
        fieldId routeShortNameFld;
        fieldId routeTypeFld;
        fieldId routeUrlFld;
        fieldId routeDescFld;
        fieldId agencyIdFld;
        fieldId routeColorFld;
        fieldId routeTextColorFld;

        static RouteFields fromCsvParser(const csv::CsvParser& csvp)
        {
            RouteFields r;
            r.routeIdFld = csvp.getFieldIndex("route_id");
            r.routeLongNameFld = csvp.getOptFieldIndex("route_long_name");
            r.routeShortNameFld = csvp.getOptFieldIndex("route_short_name");
            r.routeTypeFld = csvp.getFieldIndex("route_type");
            r.routeUrlFld = csvp.getOptFieldIndex("route_url");
            r.routeDescFld = csvp.getOptFieldIndex("route_desc");
            r.agencyIdFld = csvp.getOptFieldIndex("agency_id");
            r.routeColorFld = csvp.getOptFieldIndex("route_color");
            r.routeTextColorFld = csvp.getOptFieldIndex("route_text_color");
            return r;
        }

    };

    struct RouteFlat
    {
        enum class TYPE
        {
            TRAM = 0,
            SUBWAY = 1,
            RAIL = 2,
            BUS = 3,
            FERRY = 4,
            CABLE_CAR = 5,
            GONDOLA = 6,
            FUNICULAR = 7,
            COACH = 200,
            NONE = 99
        };

        std::string id;
        std::string agency;
        std::string short_name;
        std::string long_name;
        std::string desc;
        TYPE type;
        std::string url;
        uint32_t color;
        uint32_t text_color;

        static std::string getHexColorString(uint32_t color)
        {
            // using stringstream here, because it doesnt add "0x" to the front
            std::stringstream ss;
            ss << std::hex << std::setfill('0') << std::setw(6) << color;
            return ss.str();
        }

        static std::string getTypeString(RouteFlat::TYPE t)
        {
            if (t == TYPE::COACH)
            {
                return "coach";
            }
            std::string names[8] = { "tram", "subway", "rail", "bus", "ferry", "cablecar", "gondola", "funicular" };
            return names[static_cast<size_t>(t)];
        }

        static RouteFlat::TYPE getRouteType(int t)
        {
            switch (t) {
                case 2:
                case 100:
                case 101:
                case 102:
                case 103:
                case 104:
                case 105:
                case 106:
                case 107:
                case 108:
                case 109:
                case 110:
                case 111:
                case 112:
                case 113:
                case 114:
                case 115:
                case 117:
                case 300:
                case 400:
                case 403:
                case 404:
                case 405:
                case 1503:
                    return TYPE::RAIL;
                case 3:
                    return TYPE::BUS;
                case 200:
                case 201:
                case 202:
                case 203:
                case 204:
                case 205:
                case 206:
                case 207:
                case 208:
                case 209:
                    return TYPE::COACH;
                case 700:
                case 701:
                case 702:
                case 703:
                case 704:
                case 705:
                case 706:
                case 707:
                case 708:
                case 709:
                case 710:
                case 711:
                case 712:
                case 713:
                case 714:
                case 715:
                case 716:
                case 717:
                case 800:
                case 1500:
                case 1501:
                case 1505:
                case 1506:
                case 1507:
                    return TYPE::BUS;
                case 1:
                case 401:
                case 402:
                case 500:
                case 600:
                    return TYPE::SUBWAY;
                case 0:
                case 900:
                case 901:
                case 902:
                case 903:
                case 904:
                case 905:
                case 906:
                    return TYPE::TRAM;
                    // TODO(patrick): from here on not complete!
                case 4:
                case 1000:
                case 1200:
                case 1502:
                    return TYPE::FERRY;
                case 6:
                case 1300:
                case 1301:
                case 1304:
                case 1306:
                case 1307:
                    return TYPE::GONDOLA;
                case 7:
                case 116:
                case 1303:
                case 1302:
                case 1400:
                    return TYPE::FUNICULAR;
                case 5:
                    return TYPE::CABLE_CAR;
                default:
                    return TYPE::NONE;
            }
        }

        static std::set<RouteFlat::TYPE> getTypesFromString(std::string name)
        {
            std::set<RouteFlat::TYPE> ret;

            if (name.empty()) return ret;

            char* rem;
            uint64_t num = strtol(name.c_str(), &rem, 10);
            if (!*rem) {
                auto i = getRouteType(num);
                if (i != RouteFlat::TYPE::NONE) ret.insert(i);
                return ret;
            }

            std::transform(name.begin(), name.end(), name.begin(), ::tolower);

            if (name == "all") {
                ret.insert(RouteFlat::TYPE::TRAM);
                ret.insert(RouteFlat::TYPE::SUBWAY);
                ret.insert(RouteFlat::TYPE::RAIL);
                ret.insert(RouteFlat::TYPE::BUS);
                ret.insert(RouteFlat::TYPE::COACH);
                ret.insert(RouteFlat::TYPE::FERRY);
                ret.insert(RouteFlat::TYPE::CABLE_CAR);
                ret.insert(RouteFlat::TYPE::GONDOLA);
                ret.insert(RouteFlat::TYPE::FUNICULAR);
                return ret;
            }

            if (name == "bus") {
                ret.insert(RouteFlat::TYPE::BUS);
                return ret;
            }

            if (name == "tram" || name == "streetcar" || name == "light_rail" || name == "lightrail" || name == "light-rail") {
                ret.insert(RouteFlat::TYPE::TRAM);
                return ret;
            }

            if (name == "train" || name == "rail") {
                ret.insert(RouteFlat::TYPE::RAIL);
                return ret;
            }

            if (name == "ferry" || name == "boat" || name == "ship") {
                ret.insert(RouteFlat::TYPE::FERRY);
                return ret;
            }

            if (name == "subway" || name == "metro") {
                ret.insert(RouteFlat::TYPE::SUBWAY);
                return ret;
            }

            if (name == "cablecar" || name == "cable_car" || name == "cable-car") {
                ret.insert(RouteFlat::TYPE::CABLE_CAR);
                return ret;
            }

            if (name == "gondola") {
                ret.insert(RouteFlat::TYPE::GONDOLA);
                return ret;
            }

            if (name == "funicular") {
                ret.insert(RouteFlat::TYPE::FUNICULAR);
                return ret;
            }

            if (name == "coach") {
                ret.insert(RouteFlat::TYPE::COACH);
                return ret;
            }

            return ret;
        }
    };

    template<typename AgencyT>
    class RouteB
    {
    public:
        using Ref = RouteB<AgencyT> *;

        static std::string getId(Ref r) { return r->getId(); }

        RouteB() = default;

        explicit RouteB(std::string  id, typename AgencyT::Ref agency, std::string  short_name, std::string  long_name, std::string  desc, typename RouteFlat::TYPE type, std::string  url, uint32_t color, uint32_t text_color) :
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

        [[nodiscard]] typename RouteFlat::TYPE getType() const { return _type; }

        [[nodiscard]] const std::string& getUrl() const { return _url; }

        [[nodiscard]] uint32_t getColor() const { return _color; }

        [[nodiscard]] std::string getColorString() const
        {
            return RouteFlat::getHexColorString(_color);
        }

        [[nodiscard]] uint32_t getTextColor() const { return _text_color; }

        [[nodiscard]] std::string getTextColorString() const
        {
            return RouteFlat::getHexColorString(_text_color);
        }

        [[nodiscard]] RouteFlat getFlat() const
        {
            RouteFlat r;
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
        void setType(typename RouteFlat::TYPE type)
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
        std::string _id {};
        typename AgencyT::Ref _agency {nullptr};
        std::string _short_name{};
        std::string _long_name{};
        std::string _desc{};
        typename RouteFlat::TYPE _type{};
        std::string _url{};
        uint32_t _color{};
        uint32_t _text_color{};
    };

    using Route = RouteB<Agency>;

}    // namespace cppgtfs::gtfs

#endif    // AD_CPPGTFS_GTFS_ROUTE_H_
