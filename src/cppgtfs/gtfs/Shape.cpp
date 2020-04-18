#include <cppgtfs/gtfs/Shape.h>
namespace cppgtfs::gtfs
{
    ShapePoint::ShapePoint(float lat, float ln, float dist, uint32_t seq) :
        lat(lat), lng(ln), travelDist(dist), seq(seq) {}
    ShapePoint::ShapePoint() :
        lat(0), lng(0), travelDist(-1), seq(0) {}
    Shape::Fields Shape::Fields::fromCsvParser(const csv::CsvParser& csvp)
    {
        Fields s;
        s.shapeIdFld = csvp.getFieldIndex("shape_id");
        s.shapePtSequenceFld = csvp.getFieldIndex("shape_pt_sequence");
        s.shapePtLonFld = csvp.getFieldIndex("shape_pt_lon");
        s.shapePtLatFld = csvp.getFieldIndex("shape_pt_lat");
        s.shapeDistTraveledFld = csvp.getOptFieldIndex("shape_dist_traveled");
        return s;
    }
    Shape::Shape(std::string id) :
        _id(std::move(id)) {}
    const std::string& Shape::getId() const { return _id; }
    const ShapePoints& Shape::getPoints() const { return _shapePoints; }
    bool Shape::addPoint(const ShapePoint& p)
    {
        for (auto& _shapePoint : _shapePoints) {
            if (_shapePoint.seq == p.seq) {
                return false;
            }
        }
        _shapePoints.reserve(_shapePoints.size() + 1);
        _shapePoints.push_back(p);
        auto cmp = ShapePointCompare();
        std::sort(_shapePoints.begin(), _shapePoints.end(), cmp);
        return true;
    }
}