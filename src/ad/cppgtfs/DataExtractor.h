//
// Created by vvesa on 15.04.2020.
//

#ifndef CPPGTFS_DATAEXTRACTOR_H
#define CPPGTFS_DATAEXTRACTOR_H
#include <string>
#include <ad/util/CsvParser.h>
#include <ad/cppgtfs/gtfs/Service.h>
#include <ad/cppgtfs/gtfs/Route.h>
#include <ad/cppgtfs/gtfs/flat/Time.h>
#include <ad/cppgtfs/gtfs/Service.h>

namespace ad::cppgtfs
{
    class DataExtractor
    {
    public:
        explicit DataExtractor(bool strict):
            _strict(strict)
        {}
        std::string getString(const CsvParser& csv, size_t field) const;

        std::string getString(const CsvParser& csv, size_t field, const std::string& def) const;

        double getDouble(const CsvParser& csv, size_t field) const;

        double getDouble(const CsvParser& csv, size_t fld, double def) const;

        int64_t getRangeInteger(const CsvParser& csv, size_t field, int64_t minv, int64_t maxv) const;

        int64_t getRangeInteger(const CsvParser& csv, size_t field, int64_t minv, int64_t maxv, int64_t def) const;

        uint32_t getColorFromHexString(const CsvParser& csv, size_t field, const std::string& def) const;

        gtfs::flat::ServiceDate getServiceDate(const CsvParser& csv, size_t field) const;

        gtfs::flat::ServiceDate getServiceDate(const CsvParser& csv, size_t field, bool req) const;

        gtfs::flat::Time getTime(const CsvParser& csv, size_t field) const;

        gtfs::flat::Route::TYPE getRouteType(const CsvParser& csv, size_t field, int64_t t) const;

    private:
        bool _strict;
    };

}

#endif    //CPPGTFS_DATAEXTRACTOR_H
