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

    class StopTime
    {
    public:
        struct Fields
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
            static Fields fromCsvParser(const csv::CsvParser& csvp);
        };
        struct Flat
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

        using PU_DO_TYPE = gtfs::StopTime::Flat::PU_DO_TYPE;

        StopTime(const Time& at, const Time& dt, Stop::Ref s, uint32_t seq, const std::string& hs, PU_DO_TYPE put, PU_DO_TYPE dot, float distTrav, bool isTp);

        const Time& getArrivalTime() const;

        const Time& getDepartureTime() const;

        Stop::Ref getStop() const;

        Stop::Ref getStop();

        const std::string& getHeadsign() const;

        PU_DO_TYPE getPickupType() const;

        PU_DO_TYPE getDropOffType() const;

        float getShapeDistanceTravelled() const;

        void setShapeDistanceTravelled(double d);

        bool isTimepoint() const;

        uint16_t getSeq() const;

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
        bool operator()(const StopTime& lh, const StopTime& rh) const;
    };


}    // namespace cppgtfs::gtfs

#endif    // AD_CPPGTFS_GTFS_STOPTIME_H_
