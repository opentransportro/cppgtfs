#include <cppgtfs/gtfs/Shape.h>
namespace cppgtfs::gtfs
{
    ShapePoint::ShapePoint(float lat, float ln, float dist, uint32_t seq) :
        lat(lat), lng(ln), travelDist(dist), seq(seq) {}
    ShapePoint::ShapePoint() :
        lat(0), lng(0), travelDist(-1), seq(0) {}
}