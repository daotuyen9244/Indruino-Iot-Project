// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2020
// MIT License

#define ARDUINOJSON_DECODE_UNICODE 1
#include <ArduinoJson.h>
#include <catch.hpp>

TEST_CASE("Valid JSON strings value") {
  struct TestCase {
    const char* input;
    const char* expectedOutput;
  };

  TestCase testCases[] = {
      {"\"hello world\"", "hello world"},
      {"\'hello world\'", "hello world"},
      {"'\"'", "\""},
      {"'\\\\'", "\\"},
      {"'\\/'", "/"},
      {"'\\b'", "\b"},
      {"'\\f'", "\f"},
      {"'\\n'", "\n"},
      {"'\\r'", "\r"},
      {"'\\t'", "\t"},
      {"\"1\\\"2\\\\3\\/4\\b5\\f6\\n7\\r8\\t9\"", "1\"2\\3/4\b5\f6\n7\r8\t9"},
      {"'\\u0041'", "A"},
      {"'\\u00e4'", "\xc3\xa4"},                 // ä
      {"'\\u00E4'", "\xc3\xa4"},                 // ä
      {"'\\u3042'", "\xe3\x81\x82"},             // あ
      {"'\\ud83d\\udda4'", "\xf0\x9f\x96\xa4"},  // 🖤
      {"'\\uF053'", "\xef\x81\x93"},             // issue #1173
      {"'\\uF015'", "\xef\x80\x95"},             // issue #1173
      {"'\\uF054'", "\xef\x81\x94"},             // issue #1173
  };
  const size_t testCount = sizeof(testCases) / sizeof(testCases[0]);

  DynamicJsonDocument doc(4096);

  for (size_t i = 0; i < testCount; i++) {
    const TestCase& testCase = testCases[i];
    CAPTURE(testCase.input);
    DeserializationError err = deserializeJson(doc, testCase.input);
    CHECK(err == DeserializationError::Ok);
    CHECK(doc.as<std::string>() == testCase.expectedOutput);
  }
}

TEST_CASE("Truncated JSON string") {
  const char* testCases[] = {"\"hello", "\'hello", "'\\u", "'\\u00", "'\\u000"};
  const size_t testCount = sizeof(testCases) / sizeof(testCases[0]);

  DynamicJsonDocument doc(4096);

  for (size_t i = 0; i < testCount; i++) {
    const char* input = testCases[i];
    CAPTURE(input);
    REQUIRE(deserializeJson(doc, input) ==
            DeserializationError::IncompleteInput);
  }
}

TEST_CASE("Invalid JSON string") {
  const char* testCases[] = {"'\\u'",     "'\\u000g'", "'\\u000'",
                             "'\\u000G'", "'\\u000/'", "'\\x1234'"};
  const size_t testCount = sizeof(testCases) / sizeof(testCases[0]);

  DynamicJsonDocument doc(4096);

  for (size_t i = 0; i < testCount; i++) {
    const char* input = testCases[i];
    CAPTURE(input);
    REQUIRE(deserializeJson(doc, input) == DeserializationError::InvalidInput);
  }
}

<<<<<<< HEAD
TEST_CASE("Not enough room to save the key") {
  DynamicJsonDocument doc(JSON_OBJECT_SIZE(1) + 8);

  SECTION("Quoted string") {
    REQUIRE(deserializeJson(doc, "{\"accuracy\":1}") ==
=======
TEST_CASE("Not enough room to duplicate the string") {
  DynamicJsonDocument doc(JSON_OBJECT_SIZE(0));

  SECTION("Quoted string") {
    REQUIRE(deserializeJson(doc, "{\"example\":1}") ==
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
            DeserializationError::NoMemory);
  }

  SECTION("Non-quoted string") {
<<<<<<< HEAD
    REQUIRE(deserializeJson(doc, "{accuracy:1}") ==
=======
    REQUIRE(deserializeJson(doc, "{example:1}") ==
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
            DeserializationError::NoMemory);
  }
}
