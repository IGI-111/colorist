#include "../disjoint.h"
#include "../color.h"

#include "catch.h"

TEST_CASE("set creation", "[disjoint]")
{
    SECTION("Color set singleton")
    {
        Disjoint<Color> colorSet(Color::white);
        REQUIRE(colorSet.find() == Color::white);
    }

    SECTION("std::string set singleton")
    {
        Disjoint<std::string> strSet("hello");
        REQUIRE(strSet.find() == std::string("hello"));
    }
}

TEST_CASE("set unions", "[disjoint]")
{
    SECTION("basic function")
    {
        auto a = std::make_shared<Disjoint<std::string>>("foo");
        auto b = std::make_shared<Disjoint<std::string>>("bar");
        auto c = std::make_shared<Disjoint<std::string>>("foo");

        Disjoint<std::string>::unite(a, b);
        REQUIRE(a != b);
        REQUIRE(a->size() == 1);
        REQUIRE(b->size() == 1);
        Disjoint<std::string>::unite(a, c);
        REQUIRE(a == c);
        REQUIRE(a->size() == 2);
        REQUIRE(c->size() == 2);
    }

    SECTION("uniting with oneself")
    {
        auto a = std::make_shared<Disjoint<std::string>>("foo");
        auto b = std::make_shared<Disjoint<std::string>>("foo");

        Disjoint<std::string>::unite(a, b);

        REQUIRE(a->size() == 2);
        REQUIRE(b->size() == 2);

        Disjoint<std::string>::unite(b, a);

        REQUIRE(a->size() == 2);
        REQUIRE(b->size() == 2);
    }

    SECTION("multiple element unions")
    {
        auto a = std::make_shared<Disjoint<std::string>>("foo");
        auto b = std::make_shared<Disjoint<std::string>>("bar");
        auto c = std::make_shared<Disjoint<std::string>>("foo");
        auto d = std::make_shared<Disjoint<std::string>>("bar");
        auto e = std::make_shared<Disjoint<std::string>>("bar");

        std::vector<std::shared_ptr<Disjoint<std::string>>> setVec =
        {a, b, c, d, e};
        for(auto &set1 : setVec)
            for(auto &set2 : setVec)
                    Disjoint<std::string>::unite(set1, set2);

        REQUIRE(setVec[0]->size() == 2);
        REQUIRE(setVec[1]->size() == 3);

    }
}
