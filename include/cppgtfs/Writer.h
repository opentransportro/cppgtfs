// Copyright 2018, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Patrick Brosi <brosi@informatik.uni-freiburg.de>

#ifndef AD_CPPGTFS_WRITER_H_
#define AD_CPPGTFS_WRITER_H_

#include <stdint.h>
#include <exception>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "csv/CsvWriter.h"
#include <cppgtfs/gtfs/Agency.h>
#include "cppgtfs/gtfs/Feed.h"
#include "cppgtfs/gtfs/Frequency.h"
#include "cppgtfs/gtfs/Fare.h"
#include "cppgtfs/gtfs/Route.h"
#include "cppgtfs/gtfs/Transfer.h"
#include "cppgtfs/gtfs/Shape.h"
#include "cppgtfs/gtfs/Trip.h"
#include "cppgtfs/gtfs/StopTime.h"
#include "cppgtfs/gtfs/Service.h"

using csv::CsvWriter;

// A GTFS writer
namespace cppgtfs
{
    class Writer
    {
    public:
        // Default initialization.
        Writer() {}

        // write a GtfsFeed to a zip/folder
        bool write(gtfs::Feed* sourceFeed, const std::string& path) const;

        bool writeAgency(const gtfs::Agency::Flat& ag, CsvWriter* csvw) const;

        bool writeAgencies(gtfs::Feed* f, std::ostream* os) const;

        bool writeStop(const gtfs::Stop::Flat& ag, CsvWriter* csvw) const;

        bool writeStops(gtfs::Feed* f, std::ostream* os) const;

        bool writeShapePoint(const gtfs::ShapePoint::Flat& ag, CsvWriter* csvw) const;

        bool writeShapes(gtfs::Feed* f, std::ostream* os) const;

        bool writeTrip(const gtfs::TripFlat& ag, CsvWriter* csvw) const;

        bool writeTrips(gtfs::Feed* f, std::ostream* os) const;

        bool writeStopTime(const gtfs::StopTime::Flat& ag, CsvWriter* csvw) const;

        bool writeStopTimes(gtfs::Feed* f, std::ostream* os) const;

        bool writeRoute(const gtfs::Route::Flat& ag, CsvWriter* csvw) const;

        bool writeRoutes(gtfs::Feed* f, std::ostream* os) const;

        bool writeFeedInfo(gtfs::Feed* f, std::ostream* os) const;

        bool writeTransfer(const gtfs::Transfer::Flat& ag, CsvWriter* csvw) const;

        bool writeTransfers(gtfs::Feed* f, std::ostream* os) const;

        bool writeCalendar(const gtfs::CalendarFlat& ag, CsvWriter* csvw) const;

        bool writeCalendars(gtfs::Feed* f, std::ostream* os) const;

        bool writeCalendarDate(const gtfs::CalendarDateFlat& ag, CsvWriter* csvw) const;

        bool writeCalendarDates(gtfs::Feed* f, std::ostream* os) const;

        bool writeFrequency(const gtfs::Frequency::Flat& ag, CsvWriter* csvw) const;

        bool writeFrequencies(gtfs::Feed* f, std::ostream* os) const;

        bool writeFare(const gtfs::Fare::Flat& ag, CsvWriter* csvw) const;

        bool writeFares(gtfs::Feed* f, std::ostream* os) const;

        bool writeFareRule(const gtfs::FareRule::Flat& ag, CsvWriter* csvw) const;

        bool writeFareRules(gtfs::Feed* f, std::ostream* os) const;

        static void cannotWrite(const std::string& file);

        static CsvWriter getAgencyCsvw(std::ostream* os);

        static CsvWriter getStopsCsvw(std::ostream* os);

        static CsvWriter getRoutesCsvw(std::ostream* os);

        static CsvWriter getCalendarCsvw(std::ostream* os);

        static CsvWriter getCalendarDatesCsvw(std::ostream* os);

        static CsvWriter getFrequencyCsvw(std::ostream* os);

        static CsvWriter getTransfersCsvw(std::ostream* os);

        static CsvWriter getFaresCsvw(std::ostream* os);

        static CsvWriter getFareRulesCsvw(std::ostream* os);

        static CsvWriter getShapesCsvw(std::ostream* os);

        static CsvWriter getTripsCsvw(std::ostream* os);

        static CsvWriter getStopTimesCsvw(std::ostream* os);

        static CsvWriter getFeedInfoCsvw(std::ostream* os);
    };
}    // namespace cppgtfs

#endif    // AD_CPPGTFS_WRITER_H_
