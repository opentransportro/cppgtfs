#include <catch2/catch.hpp>
#include <ad/util/CsvParser.h>
#include <ad/util/CsvField.h>

#include <fstream>
#include "config.h"

using Catch::Matchers::EndsWith; 
using Catch::Matchers::StartsWith;

TEST_CASE("Test CSV Parser file reading", "[CsvParser]")
{
    std::ifstream fs;
    std::string curFile = DATA_FOLDER "/parser_test.txt";

    fs.open(curFile.c_str());
    if (fs.good()) {
        ad::util::CsvParser csvp(&fs);

        size_t longField = csvp.getOptFieldIndex("long");
        size_t doubleField = csvp.getOptFieldIndex("double");
        size_t stringField = csvp.getOptFieldIndex("string");

        REQUIRE(csvp.getCurLine() == 1);
        REQUIRE(csvp.getNumColumns() == 3);

        REQUIRE_THAT(csvp.getFieldName(0), StartsWith("long"));
        REQUIRE_THAT(csvp.getFieldName(1), StartsWith("double"));
        REQUIRE_THAT(csvp.getFieldName(2), StartsWith("string"));

        REQUIRE(csvp.hasItem("string"));

        while (csvp.readNextLine()) {
            double a = csvp.getDouble(doubleField);
            long b = csvp.getLong(longField);
            const char* string = csvp.getTString(stringField);

            REQUIRE(a == 2394.5);
            REQUIRE(b == 123564);
            REQUIRE_THAT(string, EndsWith("this is a test"));
        }

        fs.close();
    }
}
TEST_CASE("Opening parser with null stream", "[CsvParser]")
{
    ad::util::CsvParser csvp(nullptr);
    REQUIRE(csvp.getNumColumns() == 0);
    REQUIRE(csvp.getCurLine() == 0);
    REQUIRE(csvp.eof());
    REQUIRE(csvp.fieldIsEmpty(0));
    REQUIRE_FALSE(csvp.hasItem("dummy field"));
    REQUIRE_FALSE(csvp.readNextLine());
}
