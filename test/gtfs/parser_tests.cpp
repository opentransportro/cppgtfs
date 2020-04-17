#include <catch2/catch.hpp>
#include <cppgtfs/Reader.h>
#include <config.h>
using Catch::Matchers::EndsWith;
using Catch::Matchers::StartsWith;

TEST_CASE("Create reader and parse exemple files", "[Reader]")
{
    cppgtfs::Reader reader(DATA_FOLDER "/incorrect");
    cppgtfs::gtfs::Feed feed;

    REQUIRE_THROWS(reader.parse(&feed));
}

TEST_CASE("Create ok reader and parse exemple files", "[Reader]")
{
    cppgtfs::Reader reader(DATA_FOLDER "/correct");
    cppgtfs::gtfs::Feed feed;

    try {
        reader.parse(&feed);
    } catch (exception &e) {
        printf("%s", e.what());
    }
}


