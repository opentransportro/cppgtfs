// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_FLAT_TRANSFER_H_
#define AD_CPPGTFS_GTFS_FLAT_TRANSFER_H_

#include <string>
#include "../StopTime.h"

namespace ad::cppgtfs::gtfs::flat
{
    struct TransfersFlds
    {
        size_t fromStopIdFld;
        size_t toStopIdFld;
        size_t transferTypeFld;
        size_t minTransferTimeFld;
    };

    struct Transfer
    {
        enum TYPE : uint8_t
        {
            RECOMMENDED = 0,
            TIMED = 1,
            MIN_TIME = 2,
            NO_TRANSFER = 3
        };

        std::string fromStop;
        std::string toStop;
        TYPE type;
        int32_t tTime;
    };

}    // namespace ad

#endif    // AD_CPPGTFS_GTFS_FLAT_TRANSFER_H_
