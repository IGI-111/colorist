#include "../disjoint.h"
#include "../color.h"

#include "catch.h"

TEST_CASE("set creation", "[disjoint]")
{
    SECTION("set singleton")
    {
        Disjoint colorSet(0,0);
        REQUIRE(colorSet.find() == Coord(0,0));
    }

}

TEST_CASE("set unions", "[disjoint]")
{
    auto o = Color::black;
    auto _ = Color::white;
    ColorMatrix bitmap = {
        {o,_,o},
        {_,_,_}
    };

    SECTION("basic function")
    {
        auto a = std::make_shared<Disjoint>(0,1);
        auto b = std::make_shared<Disjoint>(1,1);

        Disjoint::unite(a, b, bitmap);
        REQUIRE(a == b);
        REQUIRE(a->size() == 2);
        REQUIRE(b->size() == 2);
    }
    SECTION("multiple element unions")
    {
        auto a = std::make_shared<Disjoint>(0,1);
        auto b = std::make_shared<Disjoint>(1,1);
        auto c = std::make_shared<Disjoint>(2,1);
        auto d = std::make_shared<Disjoint>(1,0);

        std::vector<std::shared_ptr<Disjoint>> setVec =
        {a, b, c, d};
        for (std::size_t i = 0; i < setVec.size()-1; ++i) {
            Disjoint::unite(setVec[i], setVec[i+1], bitmap);
        }
        for(auto ptr : setVec)
                REQUIRE(setVec[0] == ptr);
    }
}
