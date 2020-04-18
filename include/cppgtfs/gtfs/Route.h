// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_GTFS_ROUTE_H_
#define AD_CPPGTFS_GTFS_ROUTE_H_

#include <cstdint>
#include <algorithm>
#include <iomanip>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include "Agency.h"

#include <csv/CsvParser.h>

using std::exception;

namespace cppgtfs::gtfs
{
    using fieldId = csv::fieldId;

    class Route
    {
    public:
        struct Fields
        {
            fieldId routeIdFld;
            fieldId routeLongNameFld;
            fieldId routeShortNameFld;
            fieldId routeTypeFld;
            fieldId routeUrlFld;
            fieldId routeDescFld;
            fieldId agencyIdFld;
            fieldId routeColorFld;
            fieldId routeTextColorFld;

            static Fields fromCsvParser(const csv::CsvParser& csvp);
        };

        struct Flat
        {
            enum class TYPE
            {
                TRAM = 0,
                SUBWAY = 1,
                RAIL = 2,
                BUS = 3,
                FERRY = 4,
                CABLE_CAR = 5,
                GONDOLA = 6,
                FUNICULAR = 7,
                COACH = 200,
                NONE = 99
            };

            std::string id;
            std::string agency;
            std::string short_name;
            std::string long_name;
            std::string desc;
            TYPE type;
            std::string url;
            uint32_t color;
            uint32_t text_color;

            static std::string getHexColorString(uint32_t color);

            static std::string getTypeString(Flat::TYPE t);

            static Flat::TYPE getRouteType(int t);

            static std::set<Flat::TYPE> getTypesFromString(std::string name);
        };


        using Ref = Route*;

        explicit Route(std::string id, Agency::Ref agency, std::string short_name, std::string long_name, std::string desc, typename Route::Flat::TYPE type, std::string url, uint32_t color, uint32_t text_color);

        [[nodiscard]] const std::string& getId() const { return _id; }

        [[nodiscard]] const std::string& getShortName() const { return _short_name; }

        [[nodiscard]] const std::string& getLongName() const { return _long_name; }

        [[nodiscard]] const std::string& getDesc() const { return _desc; }

        [[nodiscard]] typename Route::Flat::TYPE getType() const { return _type; }

        [[nodiscard]] const std::string& getUrl() const { return _url; }

        [[nodiscard]] uint32_t getColor() const { return _color; }

        [[nodiscard]] std::string getColorString() const;

        [[nodiscard]] uint32_t getTextColor() const { return _text_color; }

        [[nodiscard]] std::string getTextColorString() const;


        void setId(const std::string& id)
        {
            _id = id;
        }
        void setShortName(const std::string& shortName)
        {
            _short_name = shortName;
        }
        void setLongName(const std::string& longName)
        {
            _long_name = longName;
        }
        void setDesc(const std::string& desc)
        {
            _desc = desc;
        }
        void setType(typename Route::Flat::TYPE type)
        {
            _type = type;
        }
        void setUrl(const std::string& url)
        {
            _url = url;
        }
        void setColor(uint32_t color)
        {
            _color = color;
        }
        void setTextColor(uint32_t textColor)
        {
            _text_color = textColor;
        }
        Agency::Ref getAgency() const { return _agency; }

        Agency::Ref getAgency() { return _agency; }

        Route::Flat getFlat() const
        {
            Route::Flat r;
            r.id = _id;
            r.short_name = _short_name;
            r.long_name = _long_name;
            r.desc = _desc;
            r.type = _type;
            r.url = _url;
            r.color = _color;
            r.text_color = _text_color;
            r.agency = _agency->getId();
            return r;
        }

    private:
        std::string _id{};
        std::string _short_name{};
        std::string _long_name{};
        std::string _desc{};
        typename Route::Flat::TYPE _type{};
        std::string _url{};
        uint32_t _color{};
        uint32_t _text_color{};
        Agency::Ref _agency{ nullptr };
    };
}    // namespace cppgtfs::gtfs

#endif    // AD_CPPGTFS_GTFS_ROUTE_H_
