#include "../src/disjoint.h"
#include "../src/color.h"
#include "catch.h"

TEST_CASE("set creation", "[disjoint]") {
  SECTION("Color set singleton") {
    Disjoint<Color> colorSet(Color::white);
    REQUIRE(colorSet.repr()->content == Color::white);
  }

  SECTION("std::string set singleton") {
    Disjoint<std::string> strSet("hello");
    REQUIRE(strSet.repr()->content == std::string("hello"));
  }
}

TEST_CASE("set unions", "[disjoint]") {
  SECTION("basic function") {
    Disjoint<std::string> a("foo");
    Node<std::string> *aPtr = a.repr();
    Disjoint<std::string> b("bar");
    Node<std::string> *bPtr = b.repr();
    Disjoint<std::string> c("foobar");
    Node<std::string> *cPtr = c.repr();

    INFO("&a = " << &a);
    INFO("&b = " << &b);
    INFO("&c = " << &c);

    Disjoint<std::string>::unite(&a, &b);
    REQUIRE(aPtr->parent == &a);
    REQUIRE(bPtr->parent == &a);
    REQUIRE(aPtr->content == "foo");
    REQUIRE(bPtr->content == "foo");
    REQUIRE(a.repr() != b.repr());
    REQUIRE(a.size() == 2);
    REQUIRE(b.size() == 0);

    Disjoint<std::string>::unite(&c, &a);
    REQUIRE(aPtr->parent == &a);
    REQUIRE(bPtr->parent == &a);
    REQUIRE(cPtr->parent == &a);
    REQUIRE(aPtr->content == "foo");
    REQUIRE(bPtr->content == "foo");
    REQUIRE(cPtr->content == "foo");
    REQUIRE(cPtr->content == aPtr->content);
    REQUIRE(a.repr() != c.repr());
    REQUIRE(c.size() == 0);
    REQUIRE(a.size() == 3);
  }

  SECTION("uniting with oneself") {
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
