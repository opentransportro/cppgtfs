#include <catch2/catch.hpp>
#include <ad/cppgtfs/Reader.h>
#include <config.h>
using Catch::Matchers::EndsWith;
using Catch::Matchers::StartsWith;

TEST_CASE("Create reader and parse exemple files", "[Reader]")
{
    ad::cppgtfs::Reader reader(DATA_FOLDER "/incorrect");
    ad::cppgtfs::gtfs::Feed feed;

    REQUIRE_THROWS(reader.parse(&feed));


}

