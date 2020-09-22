// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2020
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

using namespace ARDUINOJSON_NAMESPACE;

<<<<<<< HEAD
TEST_CASE("ElementProxy::operator[]") {
=======
TEST_CASE("MemberProxy::operator[]") {
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
  DynamicJsonDocument doc(4096);
  ElementProxy<JsonDocument&> ep = doc[1];

  SECTION("set member") {
    ep["world"] = 42;

    REQUIRE(doc.as<std::string>() == "[null,{\"world\":42}]");
  }

  SECTION("set element") {
    ep[2] = 42;

    REQUIRE(doc.as<std::string>() == "[null,[null,null,42]]");
  }
}
