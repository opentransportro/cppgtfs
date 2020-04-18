//
// Created by vvesa on 15.04.2020.
//

#ifndef CPPGTFS_DATAEXTRACTOR_H
#define CPPGTFS_DATAEXTRACTOR_H
#include <string>
#include <cppgtfs/gtfs/Service.h>
#include <cppgtfs/gtfs/Route.h>
#include <cppgtfs/util/Time.h>
#include <cppgtfs/gtfs/Service.h>
namespace csv
{
    class CsvParser;
}
namespace cppgtfs
{
    class DataExtractor
    {
    public:
        explicit DataExtractor(bool strict) :
            _strict(strict)
        {}
        std::string getString(const csv::CsvParser& csv, size_t field) const;

        std::string getString(const csv::CsvParser& csv, size_t field, const std::string& def) const;

        double getDouble(const csv::CsvParser& csv, size_t field) const;

        double getDouble(const csv::CsvParser& csv, size_t fld, double def) const;

        int64_t getRangeInteger(const csv::CsvParser& csv, size_t field, int64_t minv, int64_t maxv) const;

        int64_t getRangeInteger(const csv::CsvParser& csv, size_t field, int64_t minv, int64_t maxv, int64_t def) const;

        uint32_t getColorFromHexString(const csv::CsvParser& csv, size_t field, const std::string& def) const;

        gtfs::ServiceDateFlat getServiceDate(const csv::CsvParser& csv, size_t field) const;

        gtfs::ServiceDateFlat getServiceDate(const csv::CsvParser& csv, size_t field, bool req) const;

        util::Time getTime(const csv::CsvParser& csv, size_t field) const;

        gtfs::Route::Flat::TYPE getRouteType(const csv::CsvParser& csv, size_t field, int64_t t) const;

    private:
        bool _strict;
    };

}    // namespace cppgtfs

#endif    //CPPGTFS_DATAEXTRACTOR_H
