#include <catch2/catch.hpp>

#include <ad/cppgtfs/Parser.h>

unsigned int Factorial(unsigned int number)
{
  return number <= 1 ? number : Factorial(number - 1) * number;
}

TEST_CASE("Test", "[test]")
{
    ad::cppgtfs::Parser parser;
    ad::cppgtfs::gtfs::Feed feed;

    parser.parse(&feed, "path/to/gtfs/folder");
}

TEST_CASE("Factorials are computed", "[factorial]")
{
  REQUIRE(Factorial(1) == 1);
  REQUIRE(Factorial(2) == 2);
  REQUIRE(Factorial(3) == 6);
  REQUIRE(Factorial(10) == 3628800);
}
