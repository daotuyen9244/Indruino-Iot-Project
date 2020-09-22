// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2020
// MIT License

#pragma once

#include <stddef.h>  // for size_t

#include <ArduinoJson/Namespace.hpp>

<<<<<<< HEAD
#define JSON_STRING_SIZE(SIZE) (SIZE + 1)
=======
#define JSON_STRING_SIZE(SIZE) (SIZE)
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323

namespace ARDUINOJSON_NAMESPACE {

struct StringSlot {
  char *value;
  size_t size;
};
}  // namespace ARDUINOJSON_NAMESPACE
