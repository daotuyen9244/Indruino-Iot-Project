// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2020
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

using namespace ARDUINOJSON_NAMESPACE;

TEST_CASE("MemberProxy::operator==()") {
  DynamicJsonDocument doc(4096);

<<<<<<< HEAD
  SECTION("1 vs 1") {
    doc["a"] = 1;
    doc["b"] = 1;

    REQUIRE(doc["a"] <= doc["b"]);
    REQUIRE(doc["a"] == doc["b"]);
    REQUIRE(doc["a"] >= doc["b"]);
    REQUIRE_FALSE(doc["a"] != doc["b"]);
    REQUIRE_FALSE(doc["a"] < doc["b"]);
    REQUIRE_FALSE(doc["a"] > doc["b"]);
  }

  SECTION("1 vs 2") {
    doc["a"] = 1;
    doc["b"] = 2;

    REQUIRE(doc["a"] != doc["b"]);
    REQUIRE(doc["a"] < doc["b"]);
    REQUIRE(doc["a"] <= doc["b"]);
    REQUIRE_FALSE(doc["a"] == doc["b"]);
    REQUIRE_FALSE(doc["a"] > doc["b"]);
    REQUIRE_FALSE(doc["a"] >= doc["b"]);
  }

  SECTION("'abc' vs 'bcd'") {
    doc["a"] = "abc";
    doc["b"] = "bcd";

    REQUIRE(doc["a"] != doc["b"]);
    REQUIRE(doc["a"] < doc["b"]);
    REQUIRE(doc["a"] <= doc["b"]);
    REQUIRE_FALSE(doc["a"] == doc["b"]);
    REQUIRE_FALSE(doc["a"] > doc["b"]);
    REQUIRE_FALSE(doc["a"] >= doc["b"]);
=======
  SECTION("same values") {
    doc["key1"] = "value";
    doc["key2"] = "value";
    REQUIRE(doc["key1"] == doc["key2"]);
    REQUIRE_FALSE(doc["key1"] != doc["key2"]);
  }

  SECTION("different values") {
    doc["key1"] = "value1";
    doc["key2"] = "value2";
    REQUIRE_FALSE(doc["key1"] == doc["key2"]);
    REQUIRE(doc["key1"] != doc["key2"]);
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
  }
}
