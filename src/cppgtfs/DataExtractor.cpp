//
// Created by vvesa on 15.04.2020.
//

#include <cstring>
#include <cppgtfs/exceptions/ParseException.h>
#include <cppgtfs/DataExtractor.h>
#include <cppgtfs/gtfs/Service.h>
#include <csv/CsvParser.h>
namespace cppgtfs
{
    using namespace exceptions;
    using namespace csv;

    // ___________________________________________________________________________
    std::string DataExtractor::getString(const CsvParser& csv, size_t field) const
    {
        const char* r = csv.getTString(field);
        if (r[0] == 0) {
            throw ParseException("expected non-empty string", csv.getFieldName(field), csv.getCurLine());
        }
        return r;
    }

    // ___________________________________________________________________________
    std::string DataExtractor::getString(const CsvParser& csv, size_t field, const std::string& def) const
    {
        if (field < csv.getNumColumns() && !csv.fieldIsEmpty(field)) {
            return csv.getTString(field);
        }

        return def;
    }

    // ___________________________________________________________________________
    double DataExtractor::getDouble(const CsvParser& csv, size_t field) const
    {
        return csv.getDouble(field);
    }

// ___________________________________________________________________________
    double DataExtractor::getDouble(const CsvParser& csv, size_t field, double ret) const
    {
        if (field < csv.getNumColumns() && !csv.fieldIsEmpty(field)) {
            return csv.getDouble(field);
        }

        return ret;
    }

// ___________________________________________________________________________
    int64_t DataExtractor::getRangeInteger(const CsvParser& csv, size_t field, int64_t minv, int64_t maxv) const
    {
        int64_t ret = csv.getLong(field);

        if (ret < minv || ret > maxv) {
            std::stringstream msg;
            msg << "expected integer in range [" << minv << "," << maxv << "]";
            throw ParseException(msg.str(), csv.getFieldName(field), csv.getCurLine());
        }

        return ret;
    }

// ___________________________________________________________________________
    int64_t DataExtractor::getRangeInteger(const CsvParser& csv, size_t field, int64_t minv, int64_t maxv, int64_t def) const
    {
        int64_t ret;

        if (field < csv.getNumColumns() && !csv.fieldIsEmpty(field)) {
            ret = csv.getLong(field);

            if (ret < minv || ret > maxv) {
                if (_strict) {
                    std::stringstream msg;
                    msg << "expected integer in range [" << minv << "," << maxv << "]";
                    throw ParseException(msg.str(), csv.getFieldName(field), csv.getCurLine());
                } else
                    return def;
            }

            return ret;
        }

        return def;
    }

    // ___________________________________________________________________________
    uint32_t DataExtractor::getColorFromHexString(const CsvParser& csv, size_t field, const std::string& def) const
    {
        std::string color_string;

        if (field < csv.getNumColumns()) {
            color_string = csv.getTString(field);
        }

        if (color_string.empty()) {
            color_string = def;
        }

        size_t chars_processed = 0;
        uint32_t ret = 0;

        try {
            ret = std::stoul("0x" + color_string, &chars_processed, 16);
        } catch (const std::exception& e) {
            if (_strict) {
                std::stringstream msg;
                msg << "expected a 6-character hexadecimal color string, found '" << color_string << "' instead. (Error while parsing was: " << e.what() << ")";
                throw ParseException(msg.str(), csv.getFieldName(field), csv.getCurLine());
            } else {
                return std::stoul("0x" + def, &chars_processed, 16);
            }
        }

        if (color_string.size() != 6 || chars_processed != 8) {
            if (_strict) {
                std::stringstream msg;
                msg << "expected a 6-character hexadecimal color string, found '" << color_string << "' instead.";
                throw ParseException(msg.str(), csv.getFieldName(field), csv.getCurLine());
            } else {
                return std::stoul("0x" + def, &chars_processed, 16);
            }
        }

        return ret;
    }

    // ____________________________________________________________________________
    gtfs::ServiceDateFlat DataExtractor::getServiceDate(const CsvParser& csv, size_t field) const
    {
        return getServiceDate(csv, field, false);
    }


// ____________________________________________________________________________
    gtfs::ServiceDateFlat DataExtractor::getServiceDate(const CsvParser& csv, size_t field, bool req) const
    {
        size_t p;
        const char* val = csv.getTString(field);
        if (strlen(val) == 0 && !req) return gtfs::ServiceDateFlat();

        try {
            int32_t yyyymmdd = std::stoul(val, &p, 10);
            if (p != strlen(val) || yyyymmdd > 99999999) {
                std::stringstream msg;
                msg << "expected a date in the YYYYMMDD format, found '" << val << "' instead.";
                throw ParseException(msg.str(), csv.getFieldName(field), csv.getCurLine());
            }
            return gtfs::ServiceDateFlat(yyyymmdd);
        } catch (const std::out_of_range& e) {
            std::stringstream msg;
            msg << "expected a date in the YYYYMMDD format, found '" << val << "' instead. (Integer out of range).";
            throw ParseException(msg.str(), csv.getFieldName(field), csv.getCurLine());
        } catch (const std::invalid_argument& e) {
            std::stringstream msg;
            msg << "expected a date in the YYYYMMDD format, found '" << val << "' instead.";
            throw ParseException(msg.str(), csv.getFieldName(field), csv.getCurLine());
        }
    }

    // ____________________________________________________________________________
    util::Time DataExtractor::getTime(const CsvParser& csv, size_t field) const
    {
        size_t p;
        const char* val = csv.getTString(field);

        if (val == nullptr || val[0] == 0) {
            return util::Time();
        }

        try {
            uint64_t h = std::stoul(val, &p, 10);
            if (h > 255)
                throw std::out_of_range(
                    "only hour-values up to 255 are "
                    "supported. (read "
                    + std::to_string(h) + ")");
            val += p + 1;

            uint64_t m = std::stoul(val, &p, 10);
            if (p == 1) {
                if (_strict) {
                    throw std::invalid_argument("one-digit minute values are not allowed.");
                }
            }
            // allow values of 60, although standard forbids it
            if (m > 60)
                throw std::out_of_range(
                    "only minute-values up to 60 are "
                    "allowed. (read "
                    + std::to_string(m) + ")");
            val += p + 1;

            uint64_t s = std::stoul(val, &p, 10);
            if (p == 0) s = 0;    // support HH:MM format (although standard forbids it)
            if (p == 1) {
                if (_strict) {
                    throw std::invalid_argument("one-digit second values are not allowed.");
                }
            }
            // allow values of 60, although standard forbids it
            if (s > 60)
                throw std::out_of_range(
                    "only second-values up to 60 are "
                    "allowed. (read "
                    + std::to_string(s) + ")");

            return util::Time(h, m % 60, s % 60);
        } catch (const std::exception& e) {
            std::stringstream msg;
            msg << "expected a time in HH:MM:SS (or H:MM:SS) format, found '" << val
                << "' instead. (" << e.what() << ")";
            throw ParseException(msg.str(), csv.getFieldName(field), csv.getCurLine());
        }
    }

    // ____________________________________________________________________________
    gtfs::RouteFlat::TYPE DataExtractor::getRouteType(const CsvParser& csv, size_t field, int64_t tn) const
    {
        auto t = gtfs::RouteFlat::getRouteType(tn);
        if (t == gtfs::RouteFlat::TYPE::NONE) {
            std::stringstream msg;
            msg << "route type '" << tn << "' not supported.";
            throw ParseException(msg.str(), csv.getFieldName(field), csv.getCurLine());
        }
        return t;
    }


}