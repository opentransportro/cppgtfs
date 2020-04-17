#include <cppgtfs/gtfs/Shape.h>
cppgtfs::gtfs::ShapePoint::ShapePoint(float lat, float ln, float dist, uint32_t seq) :
        lat(lat), lng(ln), travelDist(dist), seq(seq) {}
