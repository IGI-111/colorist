#include "../disjoint.h"
#include "../color.h"

#include "catch.h"

TEST_CASE("disjoint sets")
{
    SECTION("creating singletons")
    {
        Disjoint<Color> colorSet(Color::white);
        REQUIRE(colorSet.repr() == Color::white);

        Disjoint<std::string> strSet("hello");
        REQUIRE(strSet.repr() == std::string("hello"));
    }
}
