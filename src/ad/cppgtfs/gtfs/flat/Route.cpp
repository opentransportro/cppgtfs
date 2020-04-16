//
// Created by vlad on 14.04.2020.
//
#include <ad/cppgtfs/gtfs/flat/Route.h>

namespace ad::cppgtfs::gtfs::flat
{
    RouteFlds RouteFlds::fromCsvParser(const CsvParser& csvp)
    {
        RouteFlds r;
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
}
