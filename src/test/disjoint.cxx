#include "../disjoint.h"
#include "../color.h"

#include "catch.h"

TEST_CASE("set creation", "[disjoint]")
{
    SECTION("Color set singleton")
    {
        Disjoint<Color> colorSet(Color::white);
        REQUIRE(colorSet.repr()->content == Color::white);
    }

    SECTION("std::string set singleton")
    {
        Disjoint<std::string> strSet("hello");
        REQUIRE(strSet.repr()->content == std::string("hello"));
    }
}

TEST_CASE("set unions", "[disjoint]")
{
    SECTION("basic function")
    {
        Disjoint<std::string> a("foo");
        Disjoint<std::string> b("bar");
        Disjoint<std::string> c("foo");

        Disjoint<std::string>::unite(&a, &b);
        REQUIRE(a.repr() != b.repr());
        REQUIRE(a.size() == 2);
        REQUIRE(b.size() == 0);
        Disjoint<std::string>::unite(&a, &c);
        REQUIRE(a.repr() != c.repr());
        REQUIRE(a.size() == 3);
        REQUIRE(c.size() == 0);
    }

    SECTION("uniting with oneself")
    {
        Disjoint<std::string> a("foo");
        Disjoint<std::string> b("foo");

        Disjoint<std::string>::unite(&a, &b);

        REQUIRE(a.size() == 2);
        REQUIRE(b.size() == 0);

        Disjoint<std::string>::unite(&a, &a);

        REQUIRE(a.size() == 2);
        REQUIRE(b.size() == 0);
    }

}
