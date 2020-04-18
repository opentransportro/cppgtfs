// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_FREQUENCY_H_
#define AD_CPPGTFS_GTFS_FREQUENCY_H_

#include <cppgtfs/gtfs/StopTime.h>

namespace csv
{
    class CsvParser;
}

namespace cppgtfs::gtfs
{
    using fieldId = csv::fieldId;

    class Frequency
    {
    public:
        struct Fields
        {
            fieldId tripIdFld;
            fieldId startTimeFld;
            fieldId endTimeFld;
            fieldId headwaySecsFld;
            fieldId exactTimesFld;

            static Fields fromCsvParser(const csv::CsvParser& csvp);
        };

        struct Flat
        {
            std::string tripId;
            Time startTime, endTime;
            uint16_t headwaySecs;
            bool exactTimes;
        };

        Frequency(const Time& startTime, const Time& endTime, uint16_t headwaySecs, bool exactTimes);

        [[nodiscard]] const Time& getStartTime() const;

        [[nodiscard]] const Time& getEndTime() const;

        [[nodiscard]] uint16_t getHeadwaySecs() const;

        [[nodiscard]] bool hasExactTimes() const;

        void setStartTime(const Time& startTime);
        void setEndTime(const Time& endTime);
        void setHeadwaySecs(uint16_t headwaySecs);
        void setExactTimes(bool exactTimes);

    private:
        Time _startTime, _endTime;
        uint16_t _headwaySecs;
        bool _exactTimes;
    };

}    // namespace cppgtfs::gtfs

#endif    // AD_CPPGTFS_GTFS_FREQUENCY_H_
