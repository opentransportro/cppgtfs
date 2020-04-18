#include <cppgtfs/Reader.h>

int main()
{
    cppgtfs::Reader reader("/home/vvesa/Projects/ot/cppgtfs/test/data" "/correct");
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
    //reader.parseTransfers(targetFeed);
    reader.parseFareAttributes(targetFeed);
    reader.parseFareRules(targetFeed);
//    cppgtfs::gtfs::Feed::Routes routes = targetFeed.getRoutes();

    return 0;
}