// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_FLAT_SHAPE_H_
#define AD_CPPGTFS_GTFS_FLAT_SHAPE_H_

#include <string>

using std::exception;
using std::string;

namespace ad::cppgtfs::gtfs::flat
{
    struct ShapeFlds
    {
        size_t shapeIdFld;
        size_t shapePtSequenceFld;
        size_t shapePtLonFld;
        size_t shapePtLatFld;
        size_t shapeDistTraveledFld;
    };

    struct ShapePoint
    {
        std::string id;
        float lat, lng;
        float travelDist;
        uint32_t seq;
    };

}    // namespace ad

#endif    // AD_CPPGTFS_GTFS_FLAT_SHAPE_H_
