// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_FLAT_SHAPE_H_
#define AD_CPPGTFS_GTFS_FLAT_SHAPE_H_

#include <string>
#include <ad/util/CsvParser.h>

using namespace ad::util;

namespace ad::cppgtfs::gtfs::flat
{
    struct ShapeFlds
    {
        fieldId shapeIdFld;
        fieldId shapePtSequenceFld;
        fieldId shapePtLonFld;
        fieldId shapePtLatFld;
        fieldId shapeDistTraveledFld;

        // ____________________________________________________________________________
        static ShapeFlds fromCsvParser(const util::CsvParser& csvp);
    };

    struct ShapePoint
    {
        std::string id;
        double lat, lng;
        double travelDist;
        uint32_t seq;
    };

}    // namespace ad

#endif    // AD_CPPGTFS_GTFS_FLAT_SHAPE_H_
