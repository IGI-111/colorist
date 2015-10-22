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
        Node<std::string> *aPtr = a.repr();
        Disjoint<std::string> b("bar");
        Node<std::string> *bPtr = b.repr();
        Disjoint<std::string> c("foo");
        Node<std::string> *cPtr = c.repr();

        Disjoint<std::string>::unite(&a, &b);
        REQUIRE(aPtr->parent == &a);
        INFO("&b = " << &b);
        REQUIRE(bPtr->parent == &a);
        REQUIRE(bPtr->content == aPtr->content);
        REQUIRE(a.repr() != b.repr());
        REQUIRE(a.size() == 2);
        REQUIRE(b.size() == 0);

        Disjoint<std::string>::unite(&a, &c);
        REQUIRE(aPtr->parent == &a);
        REQUIRE(bPtr->parent == &a);
        REQUIRE(cPtr->parent == &a);
        REQUIRE(cPtr->content == aPtr->content);
        REQUIRE(a.repr() != c.repr());
        REQUIRE(a.size() == 3);
        REQUIRE(c.size() == 0);
    }

    SECTION("uniting with oneself")
    {
        Disjoint<std::string> a("foo");
        Node<std::string> *aPtr = a.repr();
        Disjoint<std::string> b("foo");
        Node<std::string> *bPtr = b.repr();

        Disjoint<std::string>::unite(&a, &b);

        REQUIRE(aPtr->parent == &a);
        REQUIRE(bPtr->parent == &a);
        REQUIRE(bPtr->content == aPtr->content);
        REQUIRE(a.repr() != b.repr());
        REQUIRE(a.size() == 2);
        REQUIRE(b.size() == 0);

        Disjoint<std::string>::unite(&a, &a);

        REQUIRE(aPtr->parent == &a);
        REQUIRE(bPtr->parent == &a);
        REQUIRE(bPtr->content == aPtr->content);
        REQUIRE(a.repr() != b.repr());
        REQUIRE(a.size() == 2);
        REQUIRE(b.size() == 0);
    }

}
