// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_FLAT_TRANSFER_H_
#define AD_CPPGTFS_GTFS_FLAT_TRANSFER_H_

#include <string>
#include <ad/cppgtfs/gtfs/StopTime.h>
#include <ad/util/CsvParser.h>

using namespace ad::util;

namespace ad::cppgtfs::gtfs::flat
{
    struct TransfersFlds
    {
        fieldId fromStopIdFld;
        fieldId toStopIdFld;
        fieldId transferTypeFld;
        fieldId minTransferTimeFld;

        // ____________________________________________________________________________
        static TransfersFlds fromCsvParser(const util::CsvParser& csvp);

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
