// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_SHAPE_H_
#define AD_CPPGTFS_GTFS_SHAPE_H_

#include <set>
#include <string>
#include <utility>
#include <vector>

namespace ad::cppgtfs::gtfs
{
    struct ShapePoint
    {
        ShapePoint(float lat, float ln, float dist, uint32_t seq) :
            lat(lat), lng(ln), travelDist(dist), seq(seq) {}

        ShapePoint() :
            lat(0), lng(0), travelDist(-1), seq(0) {}

        float lat {0.F};
        float lng {0.F};
        float travelDist {-1.F};
        uint32_t seq {0};
    };

    struct ShapePointCompare
    {
        bool operator()(const ShapePoint& lh, const ShapePoint& rh) const
        {
            return lh.seq < rh.seq;
        }
    };

    using ShapePoints = std::vector<ShapePoint>;

    class Shape
    {
    public:
        using Ref = Shape *;

        static std::string getId(Ref r) { return r->getId(); }

        Shape() = default;

        explicit Shape(std::string  id) :
            _id(std::move(id)) {}

        [[nodiscard]] const std::string& getId() const { return _id; }

        [[nodiscard]] const ShapePoints& getPoints() const { return _shapePoints; }

        bool addPoint(const ShapePoint& p)
        {
            for (auto & _shapePoint : _shapePoints) {
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

    private:
        std::string _id;
        ShapePoints _shapePoints;
    };

}    // namespace ad::cppgtfs::gtfs

#endif    // AD_CPPGTFS_GTFS_SHAPE_H_
