#include <ad/cppgtfs/gtfs/flat/Shape.h>

namespace ad::cppgtfs::gtfs::flat
{
    ShapeFlds ShapeFlds::fromCsvParser(const CsvParser& csvp)
    {
        flat::ShapeFlds s;
        s.shapeIdFld = csvp.getFieldIndex("shape_id");
        s.shapePtSequenceFld = csvp.getFieldIndex("shape_pt_sequence");
        s.shapePtLonFld = csvp.getFieldIndex("shape_pt_lon");
        s.shapePtLatFld = csvp.getFieldIndex("shape_pt_lat");
        s.shapeDistTraveledFld = csvp.getOptFieldIndex("shape_dist_traveled");
        return s;
    }
}
