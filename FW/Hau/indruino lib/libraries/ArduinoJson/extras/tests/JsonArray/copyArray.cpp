// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2020
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

TEST_CASE("copyArray()") {
<<<<<<< HEAD
  SECTION("int[] -> JsonArray") {
=======
  SECTION("1D -> JsonArray") {
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
    DynamicJsonDocument doc(4096);
    JsonArray array = doc.to<JsonArray>();
    char json[32];
    int source[] = {1, 2, 3};

    bool ok = copyArray(source, array);
<<<<<<< HEAD
    CHECK(ok);

    serializeJson(array, json);
    CHECK(std::string("[1,2,3]") == json);
  }

  SECTION("std::string[] -> JsonArray") {
    DynamicJsonDocument doc(4096);
    JsonArray array = doc.to<JsonArray>();
    char json[32];
    std::string source[] = {"a", "b", "c"};

    bool ok = copyArray(source, array);
    CHECK(ok);

    serializeJson(array, json);
    CHECK(std::string("[\"a\",\"b\",\"c\"]") == json);
  }

  SECTION("int[] -> JsonDocument") {
=======
    REQUIRE(ok);

    serializeJson(array, json, sizeof(json));
    REQUIRE(std::string("[1,2,3]") == json);
  }

  SECTION("1D -> JsonDocument") {
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
    DynamicJsonDocument doc(4096);
    char json[32];
    int source[] = {1, 2, 3};

    bool ok = copyArray(source, doc);
<<<<<<< HEAD
    CHECK(ok);

    serializeJson(doc, json);
    CHECK(std::string("[1,2,3]") == json);
  }

  SECTION("int[] -> MemberProxy") {
    DynamicJsonDocument doc(4096);
    char json[32];
    int source[] = {1, 2, 3};

    bool ok = copyArray(source, doc["data"]);
    CHECK(ok);

    serializeJson(doc, json);
    CHECK(std::string("{\"data\":[1,2,3]}") == json);
  }

  SECTION("int[] -> JsonArray, but not enough memory") {
=======
    REQUIRE(ok);

    serializeJson(doc, json, sizeof(json));
    REQUIRE(std::string("[1,2,3]") == json);
  }

  SECTION("1D -> JsonArray, but not enough memory") {
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
    const size_t SIZE = JSON_ARRAY_SIZE(2);
    StaticJsonDocument<SIZE> doc;
    JsonArray array = doc.to<JsonArray>();
    char json[32];
    int source[] = {1, 2, 3};

    bool ok = copyArray(source, array);
    REQUIRE_FALSE(ok);

<<<<<<< HEAD
    serializeJson(array, json);
    CHECK(std::string("[1,2]") == json);
  }

  SECTION("int[][] -> JsonArray") {
=======
    serializeJson(array, json, sizeof(json));
    REQUIRE(std::string("[1,2]") == json);
  }

  SECTION("2D -> JsonArray") {
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
    DynamicJsonDocument doc(4096);
    JsonArray array = doc.to<JsonArray>();
    char json[32];
    int source[][3] = {{1, 2, 3}, {4, 5, 6}};

    bool ok = copyArray(source, array);
<<<<<<< HEAD
    CHECK(ok);

    serializeJson(array, json);
    CHECK(std::string("[[1,2,3],[4,5,6]]") == json);
  }

  SECTION("int[][] -> MemberProxy") {
    DynamicJsonDocument doc(4096);
    char json[32];
    int source[][3] = {{1, 2, 3}, {4, 5, 6}};

    bool ok = copyArray(source, doc["data"]);
    CHECK(ok);

    serializeJson(doc, json);
    CHECK(std::string("{\"data\":[[1,2,3],[4,5,6]]}") == json);
  }

  SECTION("int[][] -> JsonDocument") {
=======
    REQUIRE(ok);

    serializeJson(array, json, sizeof(json));
    REQUIRE(std::string("[[1,2,3],[4,5,6]]") == json);
  }

  SECTION("2D -> JsonDocument") {
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
    DynamicJsonDocument doc(4096);
    char json[32];
    int source[][3] = {{1, 2, 3}, {4, 5, 6}};

    bool ok = copyArray(source, doc);
<<<<<<< HEAD
    CHECK(ok);

    serializeJson(doc, json);
    CHECK(std::string("[[1,2,3],[4,5,6]]") == json);
  }

  SECTION("int[][] -> JsonArray, but not enough memory") {
=======
    REQUIRE(ok);

    serializeJson(doc, json, sizeof(json));
    REQUIRE(std::string("[[1,2,3],[4,5,6]]") == json);
  }

  SECTION("2D -> JsonArray, but not enough memory") {
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
    const size_t SIZE =
        JSON_ARRAY_SIZE(2) + JSON_ARRAY_SIZE(3) + JSON_ARRAY_SIZE(2);
    StaticJsonDocument<SIZE> doc;
    JsonArray array = doc.to<JsonArray>();
    char json[32] = "";
    int source[][3] = {{1, 2, 3}, {4, 5, 6}};

    CAPTURE(SIZE)

    bool ok = copyArray(source, array);
    CAPTURE(doc.memoryUsage());
    CHECK_FALSE(ok);

<<<<<<< HEAD
    serializeJson(array, json);
    CHECK(std::string("[[1,2,3],[4,5]]") == json);
  }

  SECTION("JsonArray -> int[], with more space than needed") {
    DynamicJsonDocument doc(4096);
    char json[] = "[1,2,3]";
    DeserializationError err = deserializeJson(doc, json);
    CHECK(err == DeserializationError::Ok);
=======
    serializeJson(array, json, sizeof(json));
    REQUIRE(std::string("[[1,2,3],[4,5]]") == json);
  }

  SECTION("JsonArray -> 1D, with more space than needed") {
    DynamicJsonDocument doc(4096);
    char json[] = "[1,2,3]";
    DeserializationError err = deserializeJson(doc, json);
    REQUIRE(err == DeserializationError::Ok);
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
    JsonArray array = doc.as<JsonArray>();

    int destination[4] = {0};
    size_t result = copyArray(array, destination);

<<<<<<< HEAD
    CHECK(3 == result);
    CHECK(1 == destination[0]);
    CHECK(2 == destination[1]);
    CHECK(3 == destination[2]);
    CHECK(0 == destination[3]);
  }

  SECTION("JsonArray -> int[], without enough space") {
    DynamicJsonDocument doc(4096);
    char json[] = "[1,2,3]";
    DeserializationError err = deserializeJson(doc, json);
    CHECK(err == DeserializationError::Ok);
=======
    REQUIRE(3 == result);
    REQUIRE(1 == destination[0]);
    REQUIRE(2 == destination[1]);
    REQUIRE(3 == destination[2]);
    REQUIRE(0 == destination[3]);
  }

  SECTION("JsonArray -> 1D, without enough space") {
    DynamicJsonDocument doc(4096);
    char json[] = "[1,2,3]";
    DeserializationError err = deserializeJson(doc, json);
    REQUIRE(err == DeserializationError::Ok);
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
    JsonArray array = doc.as<JsonArray>();

    int destination[2] = {0};
    size_t result = copyArray(array, destination);

<<<<<<< HEAD
    CHECK(2 == result);
    CHECK(1 == destination[0]);
    CHECK(2 == destination[1]);
  }

  SECTION("JsonArray -> std::string[]") {
    DynamicJsonDocument doc(4096);
    char json[] = "[\"a\",\"b\",\"c\"]";
    DeserializationError err = deserializeJson(doc, json);
    CHECK(err == DeserializationError::Ok);
    JsonArray array = doc.as<JsonArray>();

    std::string destination[4];
    size_t result = copyArray(array, destination);

    CHECK(3 == result);
    CHECK("a" == destination[0]);
    CHECK("b" == destination[1]);
    CHECK("c" == destination[2]);
    CHECK("" == destination[3]);
  }

  SECTION("JsonDocument -> int[]") {
    DynamicJsonDocument doc(4096);
    char json[] = "[1,2,3]";
    DeserializationError err = deserializeJson(doc, json);
    CHECK(err == DeserializationError::Ok);
=======
    REQUIRE(2 == result);
    REQUIRE(1 == destination[0]);
    REQUIRE(2 == destination[1]);
  }

  SECTION("JsonDocument -> 1D") {
    DynamicJsonDocument doc(4096);
    char json[] = "[1,2,3]";
    DeserializationError err = deserializeJson(doc, json);
    REQUIRE(err == DeserializationError::Ok);
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323

    int destination[4] = {0};
    size_t result = copyArray(doc, destination);

<<<<<<< HEAD
    CHECK(3 == result);
    CHECK(1 == destination[0]);
    CHECK(2 == destination[1]);
    CHECK(3 == destination[2]);
    CHECK(0 == destination[3]);
  }

  SECTION("MemberProxy -> int[]") {
    DynamicJsonDocument doc(4096);
    char json[] = "{\"data\":[1,2,3]}";
    DeserializationError err = deserializeJson(doc, json);
    CHECK(err == DeserializationError::Ok);

    int destination[4] = {0};
    size_t result = copyArray(doc["data"], destination);

    CHECK(3 == result);
    CHECK(1 == destination[0]);
    CHECK(2 == destination[1]);
    CHECK(3 == destination[2]);
    CHECK(0 == destination[3]);
  }

  SECTION("ElementProxy -> int[]") {
    DynamicJsonDocument doc(4096);
    char json[] = "[[1,2,3]]";
    DeserializationError err = deserializeJson(doc, json);
    CHECK(err == DeserializationError::Ok);

    int destination[4] = {0};
    size_t result = copyArray(doc[0], destination);

    CHECK(3 == result);
    CHECK(1 == destination[0]);
    CHECK(2 == destination[1]);
    CHECK(3 == destination[2]);
    CHECK(0 == destination[3]);
  }

  SECTION("JsonArray -> int[][]") {
=======
    REQUIRE(3 == result);
    REQUIRE(1 == destination[0]);
    REQUIRE(2 == destination[1]);
    REQUIRE(3 == destination[2]);
    REQUIRE(0 == destination[3]);
  }

  SECTION("JsonArray -> 2D") {
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
    DynamicJsonDocument doc(4096);
    char json[] = "[[1,2],[3],[4]]";

    DeserializationError err = deserializeJson(doc, json);
<<<<<<< HEAD
    CHECK(err == DeserializationError::Ok);
=======
    REQUIRE(err == DeserializationError::Ok);
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
    JsonArray array = doc.as<JsonArray>();

    int destination[3][2] = {{0}};
    copyArray(array, destination);

<<<<<<< HEAD
    CHECK(1 == destination[0][0]);
    CHECK(2 == destination[0][1]);
    CHECK(3 == destination[1][0]);
    CHECK(0 == destination[1][1]);
    CHECK(4 == destination[2][0]);
    CHECK(0 == destination[2][1]);
  }

  SECTION("JsonDocument -> int[][]") {
=======
    REQUIRE(1 == destination[0][0]);
    REQUIRE(2 == destination[0][1]);
    REQUIRE(3 == destination[1][0]);
    REQUIRE(0 == destination[1][1]);
    REQUIRE(4 == destination[2][0]);
    REQUIRE(0 == destination[2][1]);
  }

  SECTION("JsonDocument -> 2D") {
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
    DynamicJsonDocument doc(4096);
    char json[] = "[[1,2],[3],[4]]";

    DeserializationError err = deserializeJson(doc, json);
<<<<<<< HEAD
    CHECK(err == DeserializationError::Ok);
=======
    REQUIRE(err == DeserializationError::Ok);
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323

    int destination[3][2] = {{0}};
    copyArray(doc, destination);

<<<<<<< HEAD
    CHECK(1 == destination[0][0]);
    CHECK(2 == destination[0][1]);
    CHECK(3 == destination[1][0]);
    CHECK(0 == destination[1][1]);
    CHECK(4 == destination[2][0]);
    CHECK(0 == destination[2][1]);
  }

  SECTION("MemberProxy -> int[][]") {
    DynamicJsonDocument doc(4096);
    char json[] = "{\"data\":[[1,2],[3],[4]]}";

    DeserializationError err = deserializeJson(doc, json);
    CHECK(err == DeserializationError::Ok);

    int destination[3][2] = {{0}};
    copyArray(doc["data"], destination);

    CHECK(1 == destination[0][0]);
    CHECK(2 == destination[0][1]);
    CHECK(3 == destination[1][0]);
    CHECK(0 == destination[1][1]);
    CHECK(4 == destination[2][0]);
    CHECK(0 == destination[2][1]);
=======
    REQUIRE(1 == destination[0][0]);
    REQUIRE(2 == destination[0][1]);
    REQUIRE(3 == destination[1][0]);
    REQUIRE(0 == destination[1][1]);
    REQUIRE(4 == destination[2][0]);
    REQUIRE(0 == destination[2][1]);
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
  }
}
