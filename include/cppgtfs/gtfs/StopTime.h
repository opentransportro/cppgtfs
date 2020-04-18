// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_STOPTIME_H_
#define AD_CPPGTFS_GTFS_STOPTIME_H_

#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <cppgtfs/gtfs/Stop.h>
#include <cppgtfs/util/Time.h>
#include <csv/CsvParser.h>
#include "Stop.h"

namespace cppgtfs::gtfs
{
    using Time = util::Time;

    struct StopTimeFields
    {
        fieldId stopIdFld;
        fieldId tripIdFld;
        fieldId arrivalTimeFld;
        fieldId departureTimeFld;
        fieldId stopSequenceFld;
        fieldId stopHeadsignFld;
        fieldId shapeDistTraveledFld;
        fieldId timepointFld;
        fieldId pickUpTypeFld;
        fieldId dropOffTypeFld;

        // ____________________________________________________________________________
        static StopTimeFields fromCsvParser(const csv::CsvParser& csvp);
    };
    struct StopTimeFlat
    {
        enum PU_DO_TYPE : uint8_t
        {
            REGULAR = 0,
            NEVER = 1,
            MUST_PHONE_AGENCY = 2,
            MUST_COORDINATE_W_DRIVER = 3
        };

        util::Time at;
        util::Time dt;

        std::string trip;
        std::string s;
        uint32_t sequence;
        std::string headsign;
        PU_DO_TYPE pickupType;
        PU_DO_TYPE dropOffType;
        bool isTimepoint;
        double shapeDistTravelled;
    };

    class StopTime
    {
    public:
        using PU_DO_TYPE = gtfs::StopTimeFlat::PU_DO_TYPE;

        StopTime(const Time& at, const Time& dt, Stop::Ref s, uint32_t seq, const std::string& hs, PU_DO_TYPE put, PU_DO_TYPE dot, float distTrav, bool isTp) :
            _at(at),
            _dt(dt),
            _s(s),
            _sequence(seq),
            _headsign(hs),
            _pickupType(put),
            _dropOffType(dot),
            _isTimepoint(isTp),
            _shapeDistTravelled(distTrav) {}

        const Time& getArrivalTime() const { return _at; }

        const Time& getDepartureTime() const { return _dt; }

        Stop::Ref getStop() const { return _s; }

        Stop::Ref getStop() { return _s; }

        const std::string& getHeadsign() const { return _headsign; }

        PU_DO_TYPE getPickupType() const
        {
            return static_cast<PU_DO_TYPE>(_pickupType);
        }

        PU_DO_TYPE getDropOffType() const
        {
            return static_cast<PU_DO_TYPE>(_dropOffType);
        }

        float getShapeDistanceTravelled() const { return _shapeDistTravelled; }

        void setShapeDistanceTravelled(double d) { _shapeDistTravelled = d; }

        bool isTimepoint() const { return _isTimepoint; }

        uint16_t getSeq() const { return _sequence; }

    private:
        Time _at;
        Time _dt;

        Stop::Ref _s;
        uint32_t _sequence;
        std::string _headsign;
        uint8_t _pickupType : 2;
        uint8_t _dropOffType : 2;
        bool _isTimepoint : 1;
        float _shapeDistTravelled;
    };

    struct StopTimeCompare
    {
        bool operator()(const StopTime& lh, const StopTime& rh) const
        {
            return lh.getSeq() < rh.getSeq();
        }
    };


}    // namespace cppgtfs::gtfs

#endif    // AD_CPPGTFS_GTFS_STOPTIME_H_
