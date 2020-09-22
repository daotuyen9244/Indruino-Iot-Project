// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2020
// MIT License

#include <ArduinoJson/Numbers/parseNumber.hpp>
#include <catch.hpp>

using namespace ARDUINOJSON_NAMESPACE;

TEST_CASE("Test uint32_t overflow") {
<<<<<<< HEAD
  ParsedNumber<float, uint32_t> first, second;
  parseNumber("4294967295", first);
  parseNumber("4294967296", second);
=======
  ParsedNumber<float, uint32_t> first =
      parseNumber<float, uint32_t>("4294967295");
  ParsedNumber<float, uint32_t> second =
      parseNumber<float, uint32_t>("4294967296");
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323

  REQUIRE(first.type() == uint8_t(VALUE_IS_POSITIVE_INTEGER));
  REQUIRE(second.type() == uint8_t(VALUE_IS_FLOAT));
}

TEST_CASE("Invalid value") {
<<<<<<< HEAD
  ParsedNumber<float, uint32_t> result;
  parseNumber("6a3", result);
=======
  ParsedNumber<float, uint32_t> result = parseNumber<float, uint32_t>("6a3");
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323

  REQUIRE(result.type() == uint8_t(VALUE_IS_NULL));
}
