#include <cppgtfs/gtfs/Stop.h>
namespace cppgtfs::gtfs
{
    Stop::Fields Stop::Fields::fromCsvParser(const csv::CsvParser& csvp)
    {
        Stop::Fields r;
        r.stopIdFld = csvp.getFieldIndex("stop_id");
        r.stopNameFld = csvp.getFieldIndex("stop_name");
        r.stopLatFld = csvp.getFieldIndex("stop_lat");
        r.stopLonFld = csvp.getFieldIndex("stop_lon");
        r.parentStationFld = csvp.getOptFieldIndex("parent_station");
        r.stopCodeFld = csvp.getOptFieldIndex("stop_code");
        r.stopDescFld = csvp.getOptFieldIndex("stop_desc");
        r.zoneIdFld = csvp.getOptFieldIndex("zone_id");
        r.stopUrlFld = csvp.getOptFieldIndex("stop_url");
        r.stopTimezoneFld = csvp.getOptFieldIndex("stop_timezone");
        r.wheelchairBoardingFld = csvp.getOptFieldIndex("wheelchair_boarding");
        r.locationTypeFld = csvp.getOptFieldIndex("location_type");
        r.platformCodeFld = csvp.getOptFieldIndex("platform_code");
        return r;
    }
    Stop::Stop(std::string id, std::string code, std::string name, std::string desc, float lat, float lng, std::string zone_id, std::string stop_url, Stop::Flat::LOCATION_TYPE location_type, Stop* parent_station, std::string stop_timezone, Stop::Flat::WHEELCHAIR_BOARDING wheelchair_boarding, std::string platform_code) :
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
    const std::string& Stop::getId() const { return _id; }
    const std::string& Stop::getCode() const { return _code; }
    const std::string& Stop::getName() const { return _name; }
    const std::string& Stop::getPlatformCode() const { return _platform_code; }
    const std::string& Stop::getDesc() const { return _desc; }
    float Stop::getLat() const { return _lat; }
    float Stop::getLng() const { return _lng; }
    const std::string& Stop::getZoneId() const { return _zone_id; }
    const std::string& Stop::getStopUrl() const { return _stop_url; }
    Stop::Flat::LOCATION_TYPE Stop::getLocationType() const { return _location_type; }
    const Stop* Stop::getParentStation() const { return _parent_station; }
    Stop* Stop::getParentStation() { return _parent_station; }
    void Stop::setParentStation(Stop* p) { _parent_station = p; }
    const std::string& Stop::getStopTimezone() const { return _stop_timezone; }
    Stop::Flat::WHEELCHAIR_BOARDING Stop::getWheelchairBoarding() const
    {
        return _wheelchair_boarding;
    }
    Stop::Flat Stop::getFlat() const
    {
        Stop::Flat r;
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
}    // namespace cppgtfs::gtfs