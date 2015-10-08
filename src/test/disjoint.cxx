#include "../disjoint.h"
#include "../color.h"

#include "catch.h"

TEST_CASE("disjoint sets")
{
    SECTION("creating singletons")
    {
        Disjoint<Color> colorSet(Color::white);
        REQUIRE(colorSet.find() == Color::white);

        Disjoint<std::string> strSet("hello");
        REQUIRE(strSet.find() == std::string("hello"));
    }
    SECTION("unions")
    {
        auto aSet = std::make_shared<Disjoint<std::string>>("foo");
        auto bSet = std::make_shared<Disjoint<std::string>>("bar");
        auto cSet = std::make_shared<Disjoint<std::string>>("foo");

        Disjoint<std::string>::unite(aSet, bSet);
        REQUIRE(aSet != bSet);
        REQUIRE(aSet->find() != bSet->find());
        Disjoint<std::string>::unite(aSet, cSet);
        REQUIRE(aSet == cSet);
        REQUIRE(aSet->find() == cSet->find());
    }
}
