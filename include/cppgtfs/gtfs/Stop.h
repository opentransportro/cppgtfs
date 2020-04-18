// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_STOP_H_
#define AD_CPPGTFS_GTFS_STOP_H_

#include <cstdint>
#include <cassert>
#include <string>
#include <utility>
#include <csv/CsvParser.h>

namespace cppgtfs::gtfs
{
    using fieldId = csv::fieldId;

    class Stop
    {
    public:
        struct Fields
        {
            fieldId stopIdFld;
            fieldId stopNameFld;
            fieldId stopLatFld;
            fieldId stopLonFld;
            fieldId parentStationFld;
            fieldId stopCodeFld;
            fieldId stopDescFld;
            fieldId zoneIdFld;
            fieldId stopUrlFld;
            fieldId stopTimezoneFld;
            fieldId wheelchairBoardingFld;
            fieldId locationTypeFld;
            fieldId platformCodeFld;

            static Fields fromCsvParser(const csv::CsvParser& csvp);
        };

        struct Flat
        {
            enum LOCATION_TYPE : uint8_t
            {
                STOP = 0,
                STATION = 1,
                STATION_ENTRANCE = 2
            };

            enum WHEELCHAIR_BOARDING : uint8_t
            {
                NO_INFORMATION = 0,
                BOARDING_POSSIBLE = 1,
                BOARDING_NOT_POSSIBLE = 2
            };

            std::string id;
            std::string code;
            std::string name;
            std::string desc;
            std::string zone_id;
            std::string stop_url;
            std::string stop_timezone;
            std::string platform_code;
            std::string parent_station;
            float lat, lng;
            Flat::WHEELCHAIR_BOARDING wheelchair_boarding;
            Flat::LOCATION_TYPE location_type;
        };

        using Ref = Stop*;

        using LOCATION_TYPE = Flat::LOCATION_TYPE;
        using WHEELCHAIR_BOARDING = Flat::WHEELCHAIR_BOARDING;

        Stop() = default;

        Stop(std::string id, std::string code, std::string name, std::string desc, float lat, float lng, std::string zone_id, std::string stop_url, Stop::Flat::LOCATION_TYPE location_type, Stop* parent_station, std::string stop_timezone, Stop::Flat::WHEELCHAIR_BOARDING wheelchair_boarding, std::string platform_code);

        [[nodiscard]] const std::string& getId() const;

        [[nodiscard]] const std::string& getCode() const;

        [[nodiscard]] const std::string& getName() const;

        [[nodiscard]] const std::string& getPlatformCode() const;

        [[nodiscard]] const std::string& getDesc() const;

        [[nodiscard]] float getLat() const;

        [[nodiscard]] float getLng() const;

        [[nodiscard]] const std::string& getZoneId() const;

        [[nodiscard]] const std::string& getStopUrl() const;

        [[nodiscard]] Stop::Flat::LOCATION_TYPE getLocationType() const;

        [[nodiscard]] const Stop* getParentStation() const;

        Stop* getParentStation();

        void setParentStation(Stop* p);

        [[nodiscard]] const std::string& getStopTimezone() const;

        [[nodiscard]] Stop::Flat::WHEELCHAIR_BOARDING getWheelchairBoarding() const;

        [[nodiscard]] Stop::Flat getFlat() const;

        // TODO(patrick): implement setters

    private:
        std::string _id{};
        std::string _code{};
        std::string _name{};
        std::string _desc{};
        std::string _zone_id{};
        std::string _stop_url{};
        std::string _stop_timezone{};
        std::string _platform_code{};
        Stop* _parent_station{};
        float _lat{};
        float _lng{};
        Stop::Flat::WHEELCHAIR_BOARDING _wheelchair_boarding{};
        Stop::Flat::LOCATION_TYPE _location_type{};
    };

}    // namespace cppgtfs::gtfs

#endif    // AD_CPPGTFS_GTFS_STOP_H_
