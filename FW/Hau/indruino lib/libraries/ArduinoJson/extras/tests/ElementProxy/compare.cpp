// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2020
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

using namespace ARDUINOJSON_NAMESPACE;

TEST_CASE("ElementProxy::operator==()") {
  DynamicJsonDocument doc(4096);

<<<<<<< HEAD
  SECTION("1 vs 1") {
    doc.add(1);
    doc.add(1);

    REQUIRE(doc[0] <= doc[1]);
    REQUIRE(doc[0] == doc[1]);
    REQUIRE(doc[0] >= doc[1]);
    REQUIRE_FALSE(doc[0] != doc[1]);
    REQUIRE_FALSE(doc[0] < doc[1]);
    REQUIRE_FALSE(doc[0] > doc[1]);
  }

  SECTION("1 vs 2") {
    doc.add(1);
    doc.add(2);

    REQUIRE(doc[0] != doc[1]);
    REQUIRE(doc[0] < doc[1]);
    REQUIRE(doc[0] <= doc[1]);
    REQUIRE_FALSE(doc[0] == doc[1]);
    REQUIRE_FALSE(doc[0] > doc[1]);
    REQUIRE_FALSE(doc[0] >= doc[1]);
  }

  SECTION("'abc' vs 'bcd'") {
    doc.add("abc");
    doc.add("bcd");

    REQUIRE(doc[0] != doc[1]);
    REQUIRE(doc[0] < doc[1]);
    REQUIRE(doc[0] <= doc[1]);
    REQUIRE_FALSE(doc[0] == doc[1]);
    REQUIRE_FALSE(doc[0] > doc[1]);
    REQUIRE_FALSE(doc[0] >= doc[1]);
=======
  SECTION("same value") {
    doc.add(1);
    doc.add(1);

    REQUIRE(doc[0] == doc[1]);
    REQUIRE_FALSE(doc[0] != doc[1]);
  }

  SECTION("different values") {
    doc.add(1);
    doc.add(2);

    REQUIRE_FALSE(doc[0] == doc[1]);
    REQUIRE(doc[0] != doc[1]);
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
  }
}
