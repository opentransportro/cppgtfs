#include <catch2/catch.hpp>
#include <cppgtfs/Reader.h>
#include <config.h>
using Catch::Matchers::EndsWith;
using Catch::Matchers::StartsWith;

TEST_CASE("Create reader and parse exemple files", "[Reader]")
{
    cppgtfs::Reader reader(DATA_FOLDER "/incorrect");
    cppgtfs::gtfs::Feed feed;

    REQUIRE_THROWS(reader.parse(feed));
}

TEST_CASE("Create ok reader and parse exemple files", "[Reader]")
{
    cppgtfs::Reader reader(DATA_FOLDER "/correct");
    cppgtfs::gtfs::Feed targetFeed;

    reader.parseFeedInfo(targetFeed);
    reader.parseAgencies(targetFeed);
    reader.parseStops(targetFeed);
    reader.parseRoutes(targetFeed);
    reader.parseCalendar(targetFeed);
    reader.parseCalendarDates(targetFeed);
    reader.parseShapes(targetFeed);
    reader.parseTrips(targetFeed);
    reader.parseStopTimes(targetFeed);
    reader.parseFrequencies(targetFeed);
    reader.parseTransfers(targetFeed);
    reader.parseFareAttributes(targetFeed);
    reader.parseFareRules(targetFeed);

}


