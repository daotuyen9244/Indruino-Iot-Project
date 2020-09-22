// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2020
// MIT License

#pragma once

#include <ArduinoJson/Configuration.hpp>
#include <ArduinoJson/version.hpp>

#ifndef ARDUINOJSON_NAMESPACE

<<<<<<< HEAD
#define ARDUINOJSON_HEX_DIGIT_0000() 0
#define ARDUINOJSON_HEX_DIGIT_0001() 1
#define ARDUINOJSON_HEX_DIGIT_0010() 2
#define ARDUINOJSON_HEX_DIGIT_0011() 3
#define ARDUINOJSON_HEX_DIGIT_0100() 4
#define ARDUINOJSON_HEX_DIGIT_0101() 5
#define ARDUINOJSON_HEX_DIGIT_0110() 6
#define ARDUINOJSON_HEX_DIGIT_0111() 7
#define ARDUINOJSON_HEX_DIGIT_1000() 8
#define ARDUINOJSON_HEX_DIGIT_1001() 9
#define ARDUINOJSON_HEX_DIGIT_1010() A
#define ARDUINOJSON_HEX_DIGIT_1011() B
#define ARDUINOJSON_HEX_DIGIT_1100() C
#define ARDUINOJSON_HEX_DIGIT_1101() D
#define ARDUINOJSON_HEX_DIGIT_1110() E
#define ARDUINOJSON_HEX_DIGIT_1111() F
#define ARDUINOJSON_HEX_DIGIT_(A, B, C, D) ARDUINOJSON_HEX_DIGIT_##A##B##C##D()
#define ARDUINOJSON_HEX_DIGIT(A, B, C, D) ARDUINOJSON_HEX_DIGIT_(A, B, C, D)

#define ARDUINOJSON_CONCAT_(A, B) A##B
#define ARDUINOJSON_CONCAT2(A, B) ARDUINOJSON_CONCAT_(A, B)
#define ARDUINOJSON_CONCAT4(A, B, C, D) \
  ARDUINOJSON_CONCAT2(ARDUINOJSON_CONCAT2(A, B), ARDUINOJSON_CONCAT2(C, D))

#define ARDUINOJSON_NAMESPACE                                         \
  ARDUINOJSON_CONCAT4(                                                \
      ARDUINOJSON_CONCAT4(ArduinoJson, ARDUINOJSON_VERSION_MAJOR,     \
                          ARDUINOJSON_VERSION_MINOR,                  \
                          ARDUINOJSON_VERSION_REVISION),              \
      _,                                                              \
      ARDUINOJSON_HEX_DIGIT(0, ARDUINOJSON_USE_LONG_LONG,             \
                            ARDUINOJSON_USE_DOUBLE,                   \
                            ARDUINOJSON_ENABLE_STRING_DEDUPLICATION), \
      ARDUINOJSON_HEX_DIGIT(                                          \
          ARDUINOJSON_ENABLE_NAN, ARDUINOJSON_ENABLE_INFINITY,        \
          ARDUINOJSON_ENABLE_COMMENTS, ARDUINOJSON_DECODE_UNICODE))
=======
#define ARDUINOJSON_DO_CONCAT(A, B) A##B
#define ARDUINOJSON_CONCAT2(A, B) ARDUINOJSON_DO_CONCAT(A, B)
#define ARDUINOJSON_CONCAT4(A, B, C, D) \
  ARDUINOJSON_CONCAT2(ARDUINOJSON_CONCAT2(A, B), ARDUINOJSON_CONCAT2(C, D))
#define ARDUINOJSON_CONCAT8(A, B, C, D, E, F, G, H)    \
  ARDUINOJSON_CONCAT2(ARDUINOJSON_CONCAT4(A, B, C, D), \
                      ARDUINOJSON_CONCAT4(E, F, G, H))
#define ARDUINOJSON_CONCAT12(A, B, C, D, E, F, G, H, I, J, K, L) \
  ARDUINOJSON_CONCAT8(A, B, C, D, E, F, G,                       \
                      ARDUINOJSON_CONCAT4(H, I, J, ARDUINOJSON_CONCAT2(K, L)))

#define ARDUINOJSON_NAMESPACE                                            \
  ARDUINOJSON_CONCAT12(                                                  \
      ArduinoJson, ARDUINOJSON_VERSION_MAJOR, ARDUINOJSON_VERSION_MINOR, \
      ARDUINOJSON_VERSION_REVISION, _, ARDUINOJSON_USE_LONG_LONG,        \
      ARDUINOJSON_USE_DOUBLE, ARDUINOJSON_DECODE_UNICODE,                \
      ARDUINOJSON_ENABLE_NAN, ARDUINOJSON_ENABLE_INFINITY,               \
      ARDUINOJSON_ENABLE_PROGMEM, ARDUINOJSON_ENABLE_COMMENTS)
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323

#endif
