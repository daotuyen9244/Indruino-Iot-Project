// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2020
// MIT License

#include "custom_string.hpp"
#include "progmem_emulation.hpp"
#include "weird_strcmp.hpp"

<<<<<<< HEAD
#include <ArduinoJson/Strings/ArduinoStringAdapter.hpp>
=======
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
#include <ArduinoJson/Strings/ConstRamStringAdapter.hpp>
#include <ArduinoJson/Strings/FlashStringAdapter.hpp>
#include <ArduinoJson/Strings/SizedRamStringAdapter.hpp>
#include <ArduinoJson/Strings/StlStringAdapter.hpp>

#include <catch.hpp>

using namespace ARDUINOJSON_NAMESPACE;

TEST_CASE("ConstRamStringAdapter") {
  SECTION("null") {
    ConstRamStringAdapter adapter(NULL);

    CHECK(adapter.compare("bravo") < 0);
    CHECK(adapter.compare(NULL) == 0);

    CHECK(adapter.equals(NULL));
    CHECK_FALSE(adapter.equals("charlie"));

    CHECK(adapter.size() == 0);
  }

  SECTION("non-null") {
    ConstRamStringAdapter adapter("bravo");

    CHECK(adapter.compare(NULL) > 0);
    CHECK(adapter.compare("alpha") > 0);
    CHECK(adapter.compare("bravo") == 0);
    CHECK(adapter.compare("charlie") < 0);

    CHECK(adapter.equals("bravo"));
    CHECK_FALSE(adapter.equals("charlie"));

    CHECK(adapter.size() == 5);
  }
}

TEST_CASE("SizedRamStringAdapter") {
  SECTION("null") {
    SizedRamStringAdapter adapter(NULL, 10);

    CHECK(adapter.compare("bravo") < 0);
    CHECK(adapter.compare(NULL) == 0);

    CHECK(adapter.equals(NULL));
    CHECK_FALSE(adapter.equals("charlie"));

    CHECK(adapter.size() == 10);
  }

  SECTION("non-null") {
    SizedRamStringAdapter adapter("bravo", 5);

    CHECK(adapter.compare(NULL) > 0);
    CHECK(adapter.compare("alpha") > 0);
    CHECK(adapter.compare("bravo") == 0);
    CHECK(adapter.compare("charlie") < 0);

    CHECK(adapter.equals("bravo"));
    CHECK_FALSE(adapter.equals("charlie"));

    CHECK(adapter.size() == 5);
  }
}

TEST_CASE("FlashStringAdapter") {
  SECTION("null") {
    FlashStringAdapter adapter(NULL);

    CHECK(adapter.compare("bravo") < 0);
    CHECK(adapter.compare(NULL) == 0);

    CHECK(adapter.equals(NULL));
    CHECK_FALSE(adapter.equals("charlie"));

    CHECK(adapter.size() == 0);
  }

  SECTION("non-null") {
    FlashStringAdapter adapter = adaptString(F("bravo"));

    CHECK(adapter.compare(NULL) > 0);
    CHECK(adapter.compare("alpha") > 0);
    CHECK(adapter.compare("bravo") == 0);
    CHECK(adapter.compare("charlie") < 0);

    CHECK(adapter.equals("bravo"));
    CHECK_FALSE(adapter.equals("charlie"));

    CHECK(adapter.size() == 5);
  }
}

TEST_CASE("std::string") {
  std::string str("bravo");
  StlStringAdapter<std::string> adapter = adaptString(str);

  CHECK(adapter.compare(NULL) > 0);
  CHECK(adapter.compare("alpha") > 0);
  CHECK(adapter.compare("bravo") == 0);
  CHECK(adapter.compare("charlie") < 0);

  CHECK(adapter.equals("bravo"));
  CHECK_FALSE(adapter.equals("charlie"));

  CHECK(adapter.size() == 5);
}

<<<<<<< HEAD
TEST_CASE("Arduino String") {
  ::String str("bravo");
  ArduinoStringAdapter adapter = adaptString(str);

  CHECK(adapter.compare(NULL) > 0);
  CHECK(adapter.compare("alpha") > 0);
  CHECK(adapter.compare("bravo") == 0);
  CHECK(adapter.compare("charlie") < 0);

  CHECK(adapter.equals("bravo"));
  CHECK_FALSE(adapter.equals("charlie"));

  CHECK(adapter.size() == 5);
}

=======
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
TEST_CASE("custom_string") {
  custom_string str("bravo");
  StlStringAdapter<custom_string> adapter = adaptString(str);

  CHECK(adapter.compare(NULL) > 0);
  CHECK(adapter.compare("alpha") > 0);
  CHECK(adapter.compare("bravo") == 0);
  CHECK(adapter.compare("charlie") < 0);

  CHECK(adapter.equals("bravo"));
  CHECK_FALSE(adapter.equals("charlie"));

  CHECK(adapter.size() == 5);
}

TEST_CASE("IsString<T>") {
  SECTION("std::string") {
    CHECK(IsString<std::string>::value == true);
  }

  SECTION("basic_string<wchar_t>") {
    CHECK(IsString<std::basic_string<wchar_t> >::value == false);
  }

  SECTION("custom_string") {
    CHECK(IsString<custom_string>::value == true);
  }

  SECTION("const __FlashStringHelper*") {
    CHECK(IsString<const __FlashStringHelper*>::value == true);
  }
<<<<<<< HEAD

  SECTION("const char*") {
    CHECK(IsString<const char*>::value == true);
  }

  SECTION("const char[]") {
    CHECK(IsString<const char[8]>::value == true);
  }
=======
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
}
