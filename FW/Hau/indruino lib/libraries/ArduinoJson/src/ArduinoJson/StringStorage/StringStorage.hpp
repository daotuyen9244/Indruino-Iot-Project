// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2020
// MIT License

#pragma once

#include <ArduinoJson/StringStorage/StringCopier.hpp>
#include <ArduinoJson/StringStorage/StringMover.hpp>

namespace ARDUINOJSON_NAMESPACE {

template <typename TInput, typename Enable = void>
struct StringStorage {
  typedef StringCopier type;

<<<<<<< HEAD
  static type create(TInput&) {
    return type();
=======
  static type create(MemoryPool& pool, TInput&) {
    return type(&pool);
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
  }
};

template <typename TChar>
struct StringStorage<TChar*,
                     typename enable_if<!is_const<TChar>::value>::type> {
  typedef StringMover type;

<<<<<<< HEAD
  static type create(TChar* input) {
=======
  static type create(MemoryPool&, TChar* input) {
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
    return type(reinterpret_cast<char*>(input));
  }
};

template <typename TInput>
<<<<<<< HEAD
typename StringStorage<TInput>::type makeStringStorage(TInput& input) {
  return StringStorage<TInput>::create(input);
}

template <typename TChar>
typename StringStorage<TChar*>::type makeStringStorage(TChar* input) {
  return StringStorage<TChar*>::create(input);
=======
typename StringStorage<TInput>::type makeStringStorage(MemoryPool& pool,
                                                       TInput& input) {
  return StringStorage<TInput>::create(pool, input);
}

template <typename TChar>
typename StringStorage<TChar*>::type makeStringStorage(MemoryPool& pool,
                                                       TChar* input) {
  return StringStorage<TChar*>::create(pool, input);
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
}
}  // namespace ARDUINOJSON_NAMESPACE
