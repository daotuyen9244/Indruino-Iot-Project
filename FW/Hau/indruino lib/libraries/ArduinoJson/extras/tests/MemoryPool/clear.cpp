// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2020
// MIT License

#include <ArduinoJson/Memory/MemoryPool.hpp>
<<<<<<< HEAD
#include <ArduinoJson/Strings/StringAdapters.hpp>
=======
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
#include <catch.hpp>

using namespace ARDUINOJSON_NAMESPACE;

static const size_t poolCapacity = 512;

TEST_CASE("MemoryPool::clear()") {
  char buffer[poolCapacity];
  MemoryPool pool(buffer, sizeof(buffer));

  SECTION("Discards allocated variants") {
    pool.allocVariant();

    pool.clear();
    REQUIRE(pool.size() == 0);
  }

  SECTION("Discards allocated strings") {
<<<<<<< HEAD
    pool.saveString(adaptString(const_cast<char *>("123456789")));
    REQUIRE(pool.size() == 10);
=======
    pool.allocFrozenString(10);
    REQUIRE(pool.size() > 0);
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323

    pool.clear();

    REQUIRE(pool.size() == 0);
  }
}
