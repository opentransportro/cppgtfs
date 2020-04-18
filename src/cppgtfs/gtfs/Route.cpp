#include <cppgtfs/gtfs/Route.h>

namespace cppgtfs::gtfs
{
    RouteFields RouteFields::fromCsvParser(const csv::CsvParser& csvp)
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
    std::string RouteFlat::getHexColorString(uint32_t color)
    {
        // using stringstream here, because it doesnt add "0x" to the front
        std::stringstream ss;
        ss << std::hex << std::setfill('0') << std::setw(6) << color;
        return ss.str();
    }
    std::string RouteFlat::getTypeString(RouteFlat::TYPE t)
    {
        if (t == TYPE::COACH) {
            return "coach";
        }
        std::string names[8] = { "tram", "subway", "rail", "bus", "ferry", "cablecar", "gondola", "funicular" };
        return names[static_cast<size_t>(t)];
    }
    RouteFlat::TYPE RouteFlat::getRouteType(int t)
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
    std::set<RouteFlat::TYPE> RouteFlat::getTypesFromString(std::string name)
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
    Route::Route(std::string id, Agency::Ref agency, std::string short_name, std::string long_name, std::string desc, RouteFlat::TYPE type, std::string url, uint32_t color, uint32_t text_color) :
        _id(std::move(id)),
        _short_name(std::move(short_name)),
        _long_name(std::move(long_name)),
        _desc(std::move(desc)),
        _type(type),
        _url(std::move(url)),
        _color(color),
        _text_color(text_color),
        _agency(agency)
    {

    }
    std::string Route::getColorString() const
    {
        return RouteFlat::getHexColorString(_color);
    }
    std::string Route::getTextColorString() const
    {
        return RouteFlat::getHexColorString(_text_color);
    }
}