#include <catch2/catch.hpp>
#include <ad/cppgtfs/Parser.h>
#include <config.h>
using Catch::Matchers::EndsWith;
using Catch::Matchers::StartsWith;

TEST_CASE("Create parser and parse exemple files", "[Parser]")
{
    ad::cppgtfs::Parser parser;
    ad::cppgtfs::gtfs::Feed feed;

    parser.parse(&feed, DATA_FOLDER);


}

