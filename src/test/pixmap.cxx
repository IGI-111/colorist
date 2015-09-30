#include "../pixmap.h"
#include "../color.h"

#define CATCH_CONFIG_MAIN
#include "catch.h"


TEST_CASE("reading PBM file")
{
    SECTION("read another type of file")
    {
        bool caught = false;
        try{
            readMonochrome("sample/feep.ppm");
        }
        catch(std::runtime_error &e){
            caught = true;
            auto message = e.what();
            REQUIRE(std::string("Trying to read PBM file with wrong magic identifier: P3") == message);
        }
        REQUIRE(caught);
    }
    SECTION("read various valid files")
    {
        //TODO
    }
}
