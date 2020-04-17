// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_TRANSFER_H_
#define AD_CPPGTFS_GTFS_TRANSFER_H_

#include <string>
#include <cppgtfs/gtfs/StopTime.h>
#include <csv/CsvParser.h>
#include "Stop.h"

namespace cppgtfs::gtfs
{
    struct TransfersFields
    {
        fieldId fromStopIdFld;
        fieldId toStopIdFld;
        fieldId transferTypeFld;
        fieldId minTransferTimeFld;

        // ____________________________________________________________________________
        static TransfersFields fromCsvParser(const csv::CsvParser& csvp);

    };
    struct TransferFlat
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

    class Transfer
    {
    public:
        using TYPE = gtfs::TransferFlat::TYPE;

        Transfer() = default;

        Transfer(Stop* fromStop, Stop* toStop, TYPE type, int32_t tTime) :
            _fromStop(fromStop), _toStop(toStop), _type(type), _tTime(tTime) {}

        [[nodiscard]] Stop* getFromStop() const { return _fromStop; }

        [[nodiscard]] Stop* getToStop() const { return _toStop; }

        [[nodiscard]] TYPE getType() const { return _type; }

        [[nodiscard]] int32_t getMinTransferTime() const { return _tTime; }

        [[nodiscard]] gtfs::TransferFlat getFlat() const
        {
            return gtfs::TransferFlat{ getFromStop()->getId(), getToStop()->getId(), getType(), getMinTransferTime() };
        }

        // TODO(patrick): implement setters

    private:
        Stop* _fromStop;
        Stop* _toStop;
        TYPE _type;
        int32_t _tTime;
    };
}    // namespace cppgtfs::gtfs

#endif    // AD_CPPGTFS_GTFS_TRANSFER_H_
