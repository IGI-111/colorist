#include "../pixmap.h"
#include "../color.h"

#define CATCH_CONFIG_MAIN
#include "catch.h"


TEST_CASE("reading PBM file")
{
    SECTION("read another type of file")
    {
        REQUIRE_THROWS_AS(
                readMonochrome("sample/feep.ppm"),
                std::runtime_error);
    }

    SECTION("read valid file")
    {
        auto feep = readMonochrome("sample/feep.pbm");

        const Color b(0,0,0);
        const Color w(255,255,255);
        const ColorMatrix reference = {
            {w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w},
            {w,b,b,b,b,w,w,b,b,b,b,w,w,b,b,b,b,w,w,b,b,b,b,w},
            {w,b,w,w,w,w,w,b,w,w,w,w,w,b,w,w,w,w,w,b,w,w,b,w},
            {w,b,b,b,w,w,w,b,b,b,w,w,w,b,b,b,w,w,w,b,b,b,b,w},
            {w,b,w,w,w,w,w,b,w,w,w,w,w,b,w,w,w,w,w,b,w,w,w,w},
            {w,b,w,w,w,w,w,b,b,b,b,w,w,b,b,b,b,w,w,b,w,w,w,w},
            {w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w},
        };
        REQUIRE(feep == reference);
    }

}
