#include "../pixmap.h"
#include "../color.h"

#define CATCH_CONFIG_MAIN
#include "catch.h"

TEST_CASE("read invalid file", "[pbm]")
{
    SECTION("read another type of file")
    {
        REQUIRE_THROWS_AS(
                readMonochrome("sample/feep.ppm"),
                std::runtime_error);
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
        REQUIRE(feep == reference);
    }

}

//TODO: write ppm tests
