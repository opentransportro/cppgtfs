#include <cppgtfs/gtfs/Route.h>

namespace cppgtfs::gtfs
{
    Route::Fields Route::Fields::fromCsvParser(const csv::CsvParser& csvp)
    {
        Route::Fields r;
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
    std::string Route::Flat::getHexColorString(uint32_t color)
    {
        // using stringstream here, because it doesnt add "0x" to the front
        std::stringstream ss;
        ss << std::hex << std::setfill('0') << std::setw(6) << color;
        return ss.str();
    }
    std::string Route::Flat::getTypeString(Route::Flat::TYPE t)
    {
        if (t == TYPE::COACH) {
            return "coach";
        }
        std::string names[8] = { "tram", "subway", "rail", "bus", "ferry", "cablecar", "gondola", "funicular" };
        return names[static_cast<size_t>(t)];
    }
    Route::Flat::TYPE Route::Flat::getRouteType(int t)
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
    std::set<Route::Flat::TYPE> Route::Flat::getTypesFromString(std::string name)
    {
        std::set<Route::Flat::TYPE> ret;

        if (name.empty()) return ret;

        char* rem;
        uint64_t num = strtol(name.c_str(), &rem, 10);
        if (!*rem) {
            auto i = getRouteType(num);
            if (i != Route::Flat::TYPE::NONE) ret.insert(i);
            return ret;
        }

        std::transform(name.begin(), name.end(), name.begin(), ::tolower);

        if (name == "all") {
            ret.insert(Route::Flat::TYPE::TRAM);
            ret.insert(Route::Flat::TYPE::SUBWAY);
            ret.insert(Route::Flat::TYPE::RAIL);
            ret.insert(Route::Flat::TYPE::BUS);
            ret.insert(Route::Flat::TYPE::COACH);
            ret.insert(Route::Flat::TYPE::FERRY);
            ret.insert(Route::Flat::TYPE::CABLE_CAR);
            ret.insert(Route::Flat::TYPE::GONDOLA);
            ret.insert(Route::Flat::TYPE::FUNICULAR);
            return ret;
        }

        if (name == "bus") {
            ret.insert(Route::Flat::TYPE::BUS);
            return ret;
        }

        if (name == "tram" || name == "streetcar" || name == "light_rail" || name == "lightrail" || name == "light-rail") {
            ret.insert(Route::Flat::TYPE::TRAM);
            return ret;
        }

        if (name == "train" || name == "rail") {
            ret.insert(Route::Flat::TYPE::RAIL);
            return ret;
        }

        if (name == "ferry" || name == "boat" || name == "ship") {
            ret.insert(Route::Flat::TYPE::FERRY);
            return ret;
        }

        if (name == "subway" || name == "metro") {
            ret.insert(Route::Flat::TYPE::SUBWAY);
            return ret;
        }

        if (name == "cablecar" || name == "cable_car" || name == "cable-car") {
            ret.insert(Route::Flat::TYPE::CABLE_CAR);
            return ret;
        }

        if (name == "gondola") {
            ret.insert(Route::Flat::TYPE::GONDOLA);
            return ret;
        }

        if (name == "funicular") {
            ret.insert(Route::Flat::TYPE::FUNICULAR);
            return ret;
        }

        if (name == "coach") {
            ret.insert(Route::Flat::TYPE::COACH);
            return ret;
        }

        return ret;
    }
    Route::Route(std::string id, Agency::Ref agency, std::string short_name, std::string long_name, std::string desc, Route::Flat::TYPE type, std::string url, uint32_t color, uint32_t text_color) :
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
        return Route::Flat::getHexColorString(_color);
    }
    std::string Route::getTextColorString() const
    {
        return Route::Flat::getHexColorString(_text_color);
    }
    const std::string& Route::getId() const { return _id; }
    const std::string& Route::getShortName() const { return _short_name; }
    const std::string& Route::getLongName() const { return _long_name; }
    const std::string& Route::getDesc() const { return _desc; }
    typename Route::Flat::TYPE Route::getType() const { return _type; }
    const std::string& Route::getUrl() const { return _url; }
    uint32_t Route::getColor() const { return _color; }
    uint32_t Route::getTextColor() const { return _text_color; }
    void Route::setId(const std::string& id)
    {
        _id = id;
    }
    void Route::setShortName(const std::string& shortName)
    {
        _short_name = shortName;
    }
    void Route::setLongName(const std::string& longName)
    {
        _long_name = longName;
    }
    void Route::setDesc(const std::string& desc)
    {
        _desc = desc;
    }
    void Route::setType(Route::Flat::TYPE type)
    {
        _type = type;
    }
    void Route::setUrl(const std::string& url)
    {
        _url = url;
    }
    void Route::setColor(uint32_t color)
    {
        _color = color;
    }
    void Route::setTextColor(uint32_t textColor)
    {
        _text_color = textColor;
    }
    Agency::Ref Route::getAgency() const { return _agency; }
    Agency::Ref Route::getAgency() { return _agency; }
    Route::Flat Route::getFlat() const
    {
        Route::Flat r;
        r.id = _id;
        r.short_name = _short_name;
        r.long_name = _long_name;
        r.desc = _desc;
        r.type = _type;
        r.url = _url;
        r.color = _color;
        r.text_color = _text_color;
        r.agency = _agency->getId();
        return r;
    }
}    // namespace cppgtfs::gtfs