#include "../pixmap.h"
#include "../color.h"

#define CATCH_CONFIG_MAIN
#include "catch.h"

#include <iostream>

TEST_CASE("read invalid file", "[pbm]")
{
    SECTION("read another type of file")
    {
        REQUIRE_THROWS_AS(
                readMonochrome("sample/feep.ppm"),
                std::runtime_error);
    }
    SECTION("read a file missing some values")
    {
        REQUIRE_THROWS(
                readMonochrome("sample/brokenFeep.pbm"));
    }
    SECTION("read a file with invalid color descriptors")
    {
        REQUIRE_THROWS_AS(
                readMonochrome("sample/moreBrokenFeep.pbm"),
                std::runtime_error);
    }
    SECTION("read random garbage")
    {
        REQUIRE_THROWS(
                readMonochrome("sample/randomGarbage"));
    }
    SECTION("readf file with negative header values")
    {
        REQUIRE_THROWS(
                readMonochrome("sample/reallyBrokenFeep.pbm"));
    }
}

TEST_CASE("reading PBM file", "[pbm]")
{
    SECTION("read valid file")
    {
        auto feep = readMonochrome("sample/feep.pbm");

        auto o = Color::black;
        auto _ = Color::white;
        const ColorMatrix reference = {
            {_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
            {_,o,o,o,o,_,_,o,o,o,o,_,_,o,o,o,o,_,_,o,o,o,o,_},
            {_,o,_,_,_,_,_,o,_,_,_,_,_,o,_,_,_,_,_,o,_,_,o,_},
            {_,o,o,o,_,_,_,o,o,o,_,_,_,o,o,o,_,_,_,o,o,o,o,_},
            {_,o,_,_,_,_,_,o,_,_,_,_,_,o,_,_,_,_,_,o,_,_,_,_},
            {_,o,_,_,_,_,_,o,o,o,o,_,_,o,o,o,o,_,_,o,_,_,_,_},
            {_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_},
        };

        std::stringstream feepValue;
        for(auto line : feep){
            for(auto val : line){
                feepValue << (val == Color::black ? 'o' : ' ');
            }
            feepValue << std::endl;
        }

        INFO("feep:\n" << feepValue.str());
        REQUIRE(feep == reference);
    }

}

TEST_CASE("writing invalid matrix to PPM file", "[ppm]")
{
    SECTION("empty ColorMatrix")
    {
        ColorMatrix empty = {};
        REQUIRE_THROWS_AS(
                writeColored(empty, "bin/out.ppm"),
                std::logic_error);
    }
    SECTION("nonrectangular ColorMatrix")
    {
        ColorMatrix totallyARectangleISwear = {{},{Color::black}};
        REQUIRE_THROWS_AS(
                writeColored(totallyARectangleISwear, "bin/out.ppm"),
                std::logic_error);
    }
}
