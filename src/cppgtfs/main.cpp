#include <cppgtfs/Reader.h>
#include <cppgtfs/gtfs/Model.h>
int main()
{

    using Test = Model<Agency::Fields, Agency>;


    auto agency = Test::create("id", "name", "url", "timezone", "lang", "phone", "fare_url", "agency_email");
    auto test = Test("id", "name", "url", "timezone", "lang", "phone", "fare_url", "agency_email");
    auto test2 = test.object();


    Test::Container container;
    container.add(test2);

    test2.setAgencyEmail("vesa");
    auto fields = test.fields();

    int x = fields.agencyEmailFld;
    printf("%x", x);

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