// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_TRANSFER_H_
#define AD_CPPGTFS_GTFS_TRANSFER_H_

#include <string>
#include "Stop.h"
#include "flat/Transfer.h"

namespace ad::cppgtfs::gtfs
{
    class Transfer
    {
    public:
        using TYPE = flat::Transfer::TYPE;

        Transfer() = default;

        Transfer(Stop* fromStop, Stop* toStop, TYPE type, int32_t tTime) :
            _fromStop(fromStop), _toStop(toStop), _type(type), _tTime(tTime) {}

        [[nodiscard]] Stop* getFromStop() const { return _fromStop; }

        [[nodiscard]] Stop* getToStop() const { return _toStop; }

        [[nodiscard]] TYPE getType() const { return _type; }

        [[nodiscard]] int32_t getMinTransferTime() const { return _tTime; }

        [[nodiscard]] flat::Transfer getFlat() const
        {
            return flat::Transfer{ getFromStop()->getId(), getToStop()->getId(), getType(), getMinTransferTime() };
        }

        // TODO(patrick): implement setters

    private:
        Stop* _fromStop;
        Stop* _toStop;
        TYPE _type;
        int32_t _tTime;
    };

}    // namespace ad::cppgtfs::gtfs

#endif    // AD_CPPGTFS_GTFS_TRANSFER_H_
