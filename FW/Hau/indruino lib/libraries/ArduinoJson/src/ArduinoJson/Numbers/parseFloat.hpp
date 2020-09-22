// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2020
// MIT License

#pragma once

#include <ArduinoJson/Numbers/convertNumber.hpp>
#include <ArduinoJson/Numbers/parseNumber.hpp>

namespace ARDUINOJSON_NAMESPACE {

template <typename T>
inline T parseFloat(const char* s) {
  // try to reuse the same parameters as JsonDeserializer
  typedef typename choose_largest<Float, T>::type TFloat;
<<<<<<< HEAD
  ParsedNumber<TFloat, UInt> value;
  parseNumber(s, value);
  return value.template as<T>();
=======
  return parseNumber<TFloat, UInt>(s).template as<T>();
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
}
}  // namespace ARDUINOJSON_NAMESPACE
