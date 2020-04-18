// Copyright 2016, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_PARSER_H_
#define AD_CPPGTFS_PARSER_H_

#include <cstdint>
#include <cstring>
#include <exception>
#include <iostream>
#include <istream>
#include <sstream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "csv/CsvParser.h"
#include "cppgtfs/DataExtractor.h"
#include "cppgtfs/gtfs/Feed.h"
#include "cppgtfs/gtfs/Frequency.h"
#include "cppgtfs/gtfs/Route.h"
#include "cppgtfs/gtfs/Service.h"
#include "cppgtfs/gtfs/Shape.h"
#include "cppgtfs/gtfs/Transfer.h"
#include "cppgtfs/gtfs/StopTime.h"
#include "cppgtfs/exceptions/ParseException.h"
#include "cppgtfs/exceptions/FileNotFoundException.h"
#include <cppgtfs/gtfs/Model.h>

using namespace cppgtfs::gtfs;
using namespace csv;


// A GTFS parser
namespace cppgtfs
{
    using namespace exceptions;

    class ReaderBase
    {
    public:
        ReaderBase(bool strict);

        // ____________________________________________________________________________
        bool nextShapePoint(CsvParser& csvp, ShapePoint::Flat* c, const Shape::Fields& flds) const;

        // ____________________________________________________________________________
        bool nextStopTime(CsvParser& csvp, StopTime::Flat* s, const StopTime::Fields& flds) const;

        // ____________________________________________________________________________
        bool nextTransfer(CsvParser& csvp, Transfer::Flat* t, const Transfer::Fields& flds) const;

        // ____________________________________________________________________________
        bool nextFrequency(CsvParser& csvp, Frequency::Flat* r, const Frequency::Fields& flds) const;

        // ____________________________________________________________________________
        bool nextFare(CsvParser& csvp, Fare::Flat* t, const Fare::Fields& flds) const;

        // ____________________________________________________________________________
        bool nextFareRule(CsvParser& csvp, FareRule::Flat* t, const FareRule::Fields& flds) const;

        // ____________________________________________________________________________
        bool nextAgency(CsvParser& csvp, gtfs::Agency::Flat* a, const gtfs::Agency::Fields& flds) const;

        // ____________________________________________________________________________
        bool nextStop(CsvParser& csvp, Stop::Flat* s, const Stop::Fields& flds) const;

        // ____________________________________________________________________________
        bool nextRoute(CsvParser& csvp, Route::Flat* r, const Route::Fields& flds) const;

        // ____________________________________________________________________________
        bool nextCalendar(CsvParser& csvp, CalendarFlat* c, const CalendarFields& flds) const;

        // ____________________________________________________________________________
        bool nextCalendarDate(CsvParser& csvp, CalendarDateFlat* c, const CalendarDateFields& flds) const;

        // ____________________________________________________________________________
        bool nextTrip(CsvParser& csvp, TripFlat* c, const TripFields& flds) const;

    protected:
        DataExtractor _dataExtractor;
    };


    class Reader : public ReaderBase
    {
    public:
        // Default initialization.
        Reader(const std::string& path);

        explicit Reader(const std::string& path, bool strict);

        // parse a zip/folder into a GtfsFeed
        bool parse(Feed& targetFeed) const;
        void parseAgencies(Feed& targetFeed) const;
        void parseStops(Feed& targetFeed) const;
        void parseRoutes(Feed& targetFeed) const;
        void parseTrips(Feed& targetFeed) const;
        void parseStopTimes(Feed& targetFeed) const;
        void parseCalendar(Feed& targetFeed) const;
        void parseCalendarDates(Feed& targetFeed) const;
        void parseFareAttributes(Feed& targetFeed) const;
        void parseFareRules(Feed& targetFeed) const;
        void parseShapes(Feed& targetFeed) const;
        void parseFrequencies(Feed& targetFeed) const;
        void parseTransfers(Feed& targetFeed) const;
        void parseFeedInfo(Feed& targetFeed) const;

    private:
        std::string _path;
        void parseAgencies(Feed& targetFeed, std::istream*) const;
        void parseStops(Feed& targetFeed, std::istream*) const;
        void parseRoutes(Feed& targetFeed, std::istream*) const;
        void parseTrips(Feed& targetFeed, std::istream*) const;
        void parseStopTimes(Feed& targetFeed, std::istream*) const;
        void parseCalendar(Feed& targetFeed, std::istream*) const;
        void parseCalendarDates(Feed& targetFeed, std::istream*) const;
        void parseFareAttributes(Feed& targetFeed, std::istream*) const;
        void parseFareRules(Feed& targetFeed, std::istream*) const;
        void parseShapes(Feed& targetFeed, std::istream*) const;
        void parseFrequencies(Feed& targetFeed, std::istream*) const;
        void parseTransfers(Feed& targetFeed, std::istream*) const;
        void parseFeedInfo(Feed& targetFeed, std::istream*) const;
    };
}    // namespace cppgtfs

#endif    // AD_CPPGTFS_PARSER_H_
