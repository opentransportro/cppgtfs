#include <catch2/catch.hpp>
#include <ad/util/CsvField.h>

using Catch::Matchers::EndsWith;
using Catch::Matchers::StartsWith;

TEST_CASE("Check field generation and return of string value", "[CsvField]")
{
    ad::util::CsvField field("test", "a");

    REQUIRE_THAT(field.toString(), StartsWith("a"));
    REQUIRE_FALSE(field.toBool());
    REQUIRE(field.toInt() == 0);
    REQUIRE(field.toDouble() == 0);

}


TEST_CASE("Check field generation and return of double value", "[CsvField]")
{
    ad::util::CsvField field("test", 25.0);

    REQUIRE(field.toString().empty());
    REQUIRE_FALSE(field.toBool());
    REQUIRE(field.toInt() == 0);
    REQUIRE(field.toDouble() == 25.0);
}

TEST_CASE("Check field generation and return of int value", "[CsvField]")
{
    ad::util::CsvField field("test", 25);

    REQUIRE(field.toString().empty());
    REQUIRE_FALSE(field.toBool());
    REQUIRE(field.toInt() == 25);
    REQUIRE(field.toDouble() == 0.0);
}