// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_SHAPE_H_
#define AD_CPPGTFS_GTFS_SHAPE_H_

#include <set>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <csv/CsvParser.h>

namespace cppgtfs::gtfs
{
    using fieldId = csv::fieldId;

    struct ShapePoint
    {
        struct Flat
        {
            std::string id;
            double lat, lng;
            double travelDist;
            uint32_t seq;
        };

        ShapePoint(float lat, float ln, float dist, uint32_t seq);

        ShapePoint();

        float lat{ 0.F };
        float lng{ 0.F };
        float travelDist{ -1.F };
        uint32_t seq{ 0 };
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
        struct Fields
        {
            fieldId shapeIdFld;
            fieldId shapePtSequenceFld;
            fieldId shapePtLonFld;
            fieldId shapePtLatFld;
            fieldId shapeDistTraveledFld;

            // ____________________________________________________________________________
            static Fields fromCsvParser(const csv::CsvParser& csvp);
        };

        using Ref = Shape*;

        Shape() = default;

        explicit Shape(std::string id);

        [[nodiscard]] const std::string& getId() const;

        [[nodiscard]] const ShapePoints& getPoints() const;

        bool addPoint(const ShapePoint& p);

    private:
        std::string _id;
        ShapePoints _shapePoints;
    };

}    // namespace cppgtfs::gtfs

#endif    // AD_CPPGTFS_GTFS_SHAPE_H_
