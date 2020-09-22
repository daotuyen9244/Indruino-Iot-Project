// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2020
// MIT License

#pragma once

#include <ArduinoJson/Deserialization/deserialize.hpp>
#include <ArduinoJson/Json/EscapeSequence.hpp>
#include <ArduinoJson/Json/Latch.hpp>
#include <ArduinoJson/Json/Utf16.hpp>
#include <ArduinoJson/Json/Utf8.hpp>
#include <ArduinoJson/Memory/MemoryPool.hpp>
#include <ArduinoJson/Numbers/parseNumber.hpp>
#include <ArduinoJson/Polyfills/assert.hpp>
#include <ArduinoJson/Polyfills/type_traits.hpp>
#include <ArduinoJson/Variant/VariantData.hpp>

namespace ARDUINOJSON_NAMESPACE {

template <typename TReader, typename TStringStorage>
class JsonDeserializer {
<<<<<<< HEAD
 public:
  JsonDeserializer(MemoryPool &pool, TReader reader,
                   TStringStorage stringStorage)
      : _stringStorage(stringStorage),
        _latch(reader),
        _pool(&pool),
        _error(DeserializationError::Ok) {}
=======
  typedef typename remove_reference<TStringStorage>::type::StringBuilder
      StringBuilder;

  struct StringOrError {
    DeserializationError err;
    const char *value;

    StringOrError(DeserializationError e) : err(e) {}
    StringOrError(DeserializationError::Code c) : err(c) {}
    StringOrError(const char *s) : err(DeserializationError::Ok), value(s) {}
  };

 public:
  JsonDeserializer(MemoryPool &pool, TReader reader,
                   TStringStorage stringStorage)
      : _pool(&pool), _stringStorage(stringStorage), _latch(reader) {}
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323

  template <typename TFilter>
  DeserializationError parse(VariantData &variant, TFilter filter,
                             NestingLimit nestingLimit) {
<<<<<<< HEAD
    parseVariant(variant, filter, nestingLimit);

    if (!_error && _latch.last() != 0 && !variant.isEnclosed()) {
      // We don't detect trailing characters earlier, so we need to check now
      _error = DeserializationError::InvalidInput;
    }

    return _error;
=======
    DeserializationError err = parseVariant(variant, filter, nestingLimit);

    if (!err && _latch.last() != 0 && !variant.isEnclosed()) {
      // We don't detect trailing characters earlier, so we need to check now
      err = DeserializationError::InvalidInput;
    }

    return err;
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
  }

 private:
  JsonDeserializer &operator=(const JsonDeserializer &);  // non-copiable

  char current() {
    return _latch.current();
  }

  void move() {
    _latch.clear();
  }

  bool eat(char charToSkip) {
    if (current() != charToSkip)
      return false;
    move();
    return true;
  }

  template <typename TFilter>
<<<<<<< HEAD
  bool parseVariant(VariantData &variant, TFilter filter,
                    NestingLimit nestingLimit) {
    if (!skipSpacesAndComments())
      return false;
=======
  DeserializationError parseVariant(VariantData &variant, TFilter filter,
                                    NestingLimit nestingLimit) {
    DeserializationError err = skipSpacesAndComments();
    if (err)
      return err;
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323

    switch (current()) {
      case '[':
        if (filter.allowArray())
          return parseArray(variant.toArray(), filter, nestingLimit);
        else
          return skipArray(nestingLimit);

      case '{':
        if (filter.allowObject())
          return parseObject(variant.toObject(), filter, nestingLimit);
        else
          return skipObject(nestingLimit);

      case '\"':
      case '\'':
        if (filter.allowValue())
          return parseStringValue(variant);
        else
          return skipString();

      default:
        if (filter.allowValue())
          return parseNumericValue(variant);
        else
          return skipNumericValue();
    }
  }

<<<<<<< HEAD
  bool skipVariant(NestingLimit nestingLimit) {
    if (!skipSpacesAndComments())
      return false;
=======
  DeserializationError skipVariant(NestingLimit nestingLimit) {
    DeserializationError err = skipSpacesAndComments();
    if (err)
      return err;
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323

    switch (current()) {
      case '[':
        return skipArray(nestingLimit);

      case '{':
        return skipObject(nestingLimit);

      case '\"':
      case '\'':
        return skipString();

      default:
        return skipNumericValue();
    }
  }

  template <typename TFilter>
<<<<<<< HEAD
  bool parseArray(CollectionData &array, TFilter filter,
                  NestingLimit nestingLimit) {
    if (nestingLimit.reached()) {
      _error = DeserializationError::TooDeep;
      return false;
    }
=======
  DeserializationError parseArray(CollectionData &array, TFilter filter,
                                  NestingLimit nestingLimit) {
    if (nestingLimit.reached())
      return DeserializationError::TooDeep;
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323

    // Skip opening braket
    ARDUINOJSON_ASSERT(current() == '[');
    move();

    // Skip spaces
<<<<<<< HEAD
    if (!skipSpacesAndComments())
      return false;

    // Empty array?
    if (eat(']'))
      return true;
=======
    DeserializationError err = skipSpacesAndComments();
    if (err)
      return err;

    // Empty array?
    if (eat(']'))
      return DeserializationError::Ok;
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323

    TFilter memberFilter = filter[0UL];

    // Read each value
    for (;;) {
      if (memberFilter.allow()) {
        // Allocate slot in array
        VariantData *value = array.addElement(_pool);
<<<<<<< HEAD
        if (!value) {
          _error = DeserializationError::NoMemory;
          return false;
        }

        // 1 - Parse value
        if (!parseVariant(*value, memberFilter, nestingLimit.decrement()))
          return false;
      } else {
        if (!skipVariant(nestingLimit.decrement()))
          return false;
      }

      // 2 - Skip spaces
      if (!skipSpacesAndComments())
        return false;

      // 3 - More values?
      if (eat(']'))
        return true;
      if (!eat(',')) {
        _error = DeserializationError::InvalidInput;
        return false;
      }
    }
  }

  bool skipArray(NestingLimit nestingLimit) {
    if (nestingLimit.reached()) {
      _error = DeserializationError::TooDeep;
      return false;
    }
=======
        if (!value)
          return DeserializationError::NoMemory;

        // 1 - Parse value
        err = parseVariant(*value, memberFilter, nestingLimit.decrement());
        if (err)
          return err;
      } else {
        err = skipVariant(nestingLimit.decrement());
        if (err)
          return err;
      }

      // 2 - Skip spaces
      err = skipSpacesAndComments();
      if (err)
        return err;

      // 3 - More values?
      if (eat(']'))
        return DeserializationError::Ok;
      if (!eat(','))
        return DeserializationError::InvalidInput;
    }
  }

  DeserializationError skipArray(NestingLimit nestingLimit) {
    if (nestingLimit.reached())
      return DeserializationError::TooDeep;
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323

    // Skip opening braket
    ARDUINOJSON_ASSERT(current() == '[');
    move();

    // Read each value
    for (;;) {
      // 1 - Skip value
<<<<<<< HEAD
      if (!skipVariant(nestingLimit.decrement()))
        return false;

      // 2 - Skip spaces
      if (!skipSpacesAndComments())
        return false;

      // 3 - More values?
      if (eat(']'))
        return true;
      if (!eat(',')) {
        _error = DeserializationError::InvalidInput;
        return false;
      }
=======
      DeserializationError err = skipVariant(nestingLimit.decrement());
      if (err)
        return err;

      // 2 - Skip spaces
      err = skipSpacesAndComments();
      if (err)
        return err;

      // 3 - More values?
      if (eat(']'))
        return DeserializationError::Ok;
      if (!eat(','))
        return DeserializationError::InvalidInput;
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
    }
  }

  template <typename TFilter>
<<<<<<< HEAD
  bool parseObject(CollectionData &object, TFilter filter,
                   NestingLimit nestingLimit) {
    if (nestingLimit.reached()) {
      _error = DeserializationError::TooDeep;
      return false;
    }
=======
  DeserializationError parseObject(CollectionData &object, TFilter filter,
                                   NestingLimit nestingLimit) {
    if (nestingLimit.reached())
      return DeserializationError::TooDeep;
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323

    // Skip opening brace
    ARDUINOJSON_ASSERT(current() == '{');
    move();

    // Skip spaces
<<<<<<< HEAD
    if (!skipSpacesAndComments())
      return false;

    // Empty object?
    if (eat('}'))
      return true;
=======
    DeserializationError err = skipSpacesAndComments();
    if (err)
      return err;

    // Empty object?
    if (eat('}'))
      return DeserializationError::Ok;
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323

    // Read each key value pair
    for (;;) {
      // Parse key
<<<<<<< HEAD
      if (!parseKey())
        return false;

      // Skip spaces
      if (!skipSpacesAndComments())
        return false;

      // Colon
      if (!eat(':')) {
        _error = DeserializationError::InvalidInput;
        return false;
      }

      const char *key = _stringStorage.c_str();

      TFilter memberFilter = filter[key];

      if (memberFilter.allow()) {
        VariantData *variant = object.getMember(adaptString(key));
        if (!variant) {
          // Save key in memory pool.
          // This MUST be done before adding the slot.
          key = _stringStorage.save(_pool);

          // Allocate slot in object
          VariantSlot *slot = object.addSlot(_pool);
          if (!slot) {
            _error = DeserializationError::NoMemory;
            return false;
          }

          slot->setKey(key, typename TStringStorage::storage_policy());
=======
      StringOrError key = parseKey();
      err = key.err;  // <- this trick saves 62 bytes on AVR
      if (err)
        return err;

      // Skip spaces
      err = skipSpacesAndComments();
      if (err)
        return err;  // Colon
      if (!eat(':'))
        return DeserializationError::InvalidInput;

      TFilter memberFilter = filter[key.value];

      if (memberFilter.allow()) {
        VariantData *variant = object.getMember(adaptString(key.value));
        if (!variant) {
          // Allocate slot in object
          VariantSlot *slot = object.addSlot(_pool);
          if (!slot)
            return DeserializationError::NoMemory;

          slot->setOwnedKey(make_not_null(key.value));
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323

          variant = slot->data();
        }

        // Parse value
<<<<<<< HEAD
        if (!parseVariant(*variant, memberFilter, nestingLimit.decrement()))
          return false;
      } else {
        if (!skipVariant(nestingLimit.decrement()))
          return false;
      }

      // Skip spaces
      if (!skipSpacesAndComments())
        return false;

      // More keys/values?
      if (eat('}'))
        return true;
      if (!eat(',')) {
        _error = DeserializationError::InvalidInput;
        return false;
      }

      // Skip spaces
      if (!skipSpacesAndComments())
        return false;
    }
  }

  bool skipObject(NestingLimit nestingLimit) {
    if (nestingLimit.reached()) {
      _error = DeserializationError::TooDeep;
      return false;
    }
=======
        err = parseVariant(*variant, memberFilter, nestingLimit.decrement());
        if (err)
          return err;
      } else {
        _stringStorage.reclaim(key.value);
        err = skipVariant(nestingLimit.decrement());
        if (err)
          return err;
      }

      // Skip spaces
      err = skipSpacesAndComments();
      if (err)
        return err;

      // More keys/values?
      if (eat('}'))
        return DeserializationError::Ok;
      if (!eat(','))
        return DeserializationError::InvalidInput;

      // Skip spaces
      err = skipSpacesAndComments();
      if (err)
        return err;
    }
  }

  DeserializationError skipObject(NestingLimit nestingLimit) {
    if (nestingLimit.reached())
      return DeserializationError::TooDeep;
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323

    // Skip opening brace
    ARDUINOJSON_ASSERT(current() == '{');
    move();

    // Skip spaces
<<<<<<< HEAD
    if (!skipSpacesAndComments())
      return false;

    // Empty object?
    if (eat('}'))
      return true;
=======
    DeserializationError err = skipSpacesAndComments();
    if (err)
      return err;

    // Empty object?
    if (eat('}'))
      return DeserializationError::Ok;
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323

    // Read each key value pair
    for (;;) {
      // Skip key
<<<<<<< HEAD
      if (!skipVariant(nestingLimit.decrement()))
        return false;

      // Skip spaces
      if (!skipSpacesAndComments())
        return false;

      // Colon
      if (!eat(':')) {
        _error = DeserializationError::InvalidInput;
        return false;
      }

      // Skip value
      if (!skipVariant(nestingLimit.decrement()))
        return false;

      // Skip spaces
      if (!skipSpacesAndComments())
        return false;

      // More keys/values?
      if (eat('}'))
        return true;
      if (!eat(',')) {
        _error = DeserializationError::InvalidInput;
        return false;
      }
    }
  }

  bool parseKey() {
    _stringStorage.startString(_pool);
=======
      err = skipVariant(nestingLimit.decrement());
      if (err)
        return err;

      // Skip spaces
      err = skipSpacesAndComments();
      if (err)
        return err;

      // Colon
      if (!eat(':'))
        return DeserializationError::InvalidInput;

      // Skip value
      err = skipVariant(nestingLimit.decrement());
      if (err)
        return err;

      // Skip spaces
      err = skipSpacesAndComments();
      if (err)
        return err;

      // More keys/values?
      if (eat('}'))
        return DeserializationError::Ok;
      if (!eat(','))
        return DeserializationError::InvalidInput;
    }
  }

  StringOrError parseKey() {
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
    if (isQuote(current())) {
      return parseQuotedString();
    } else {
      return parseNonQuotedString();
    }
  }

<<<<<<< HEAD
  bool parseStringValue(VariantData &variant) {
    _stringStorage.startString(_pool);
    if (!parseQuotedString())
      return false;
    const char *value = _stringStorage.save(_pool);
    variant.setString(make_not_null(value),
                      typename TStringStorage::storage_policy());
    return true;
  }

  bool parseQuotedString() {
=======
  DeserializationError parseStringValue(VariantData &variant) {
    StringOrError result = parseQuotedString();
    if (result.err)
      return result.err;
    variant.setOwnedString(make_not_null(result.value));
    return DeserializationError::Ok;
  }

  StringOrError parseQuotedString() {
    StringBuilder builder = _stringStorage.startString();
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
#if ARDUINOJSON_DECODE_UNICODE
    Utf16::Codepoint codepoint;
#endif
    const char stopChar = current();

    move();
    for (;;) {
      char c = current();
      move();
      if (c == stopChar)
        break;

<<<<<<< HEAD
      if (c == '\0') {
        _error = DeserializationError::IncompleteInput;
        return false;
      }

      if (c == '\\') {
        c = current();

        if (c == '\0') {
          _error = DeserializationError::IncompleteInput;
          return false;
        }

=======
      if (c == '\0')
        return DeserializationError::IncompleteInput;

      if (c == '\\') {
        c = current();
        if (c == '\0')
          return DeserializationError::IncompleteInput;
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
        if (c == 'u') {
#if ARDUINOJSON_DECODE_UNICODE
          move();
          uint16_t codeunit;
<<<<<<< HEAD
          if (!parseHex4(codeunit))
            return false;
          if (codepoint.append(codeunit))
            Utf8::encodeCodepoint(codepoint.value(), _stringStorage);
          continue;
#else
          _error = DeserializationError::NotSupported;
          return false;
#endif
        }

        // replace char
        c = EscapeSequence::unescapeChar(c);
        if (c == '\0') {
          _error = DeserializationError::InvalidInput;
          return false;
        }
        move();
      }

      _stringStorage.append(c);
    }

    _stringStorage.append('\0');

    if (!_stringStorage.isValid()) {
      _error = DeserializationError::NoMemory;
      return false;
    }

    return true;
  }

  bool parseNonQuotedString() {
=======
          DeserializationError err = parseHex4(codeunit);
          if (err)
            return err;
          if (codepoint.append(codeunit))
            Utf8::encodeCodepoint(codepoint.value(), builder);
          continue;
#else
          return DeserializationError::NotSupported;
#endif
        }
        // replace char
        c = EscapeSequence::unescapeChar(c);
        if (c == '\0')
          return DeserializationError::InvalidInput;
        move();
      }

      builder.append(c);
    }

    const char *result = builder.complete();
    if (!result)
      return DeserializationError::NoMemory;
    return result;
  }

  StringOrError parseNonQuotedString() {
    StringBuilder builder = _stringStorage.startString();

>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
    char c = current();
    ARDUINOJSON_ASSERT(c);

    if (canBeInNonQuotedString(c)) {  // no quotes
      do {
        move();
<<<<<<< HEAD
        _stringStorage.append(c);
        c = current();
      } while (canBeInNonQuotedString(c));
    } else {
      _error = DeserializationError::InvalidInput;
      return false;
    }

    _stringStorage.append('\0');

    if (!_stringStorage.isValid()) {
      _error = DeserializationError::NoMemory;
      return false;
    }

    return true;
  }

  bool skipString() {
=======
        builder.append(c);
        c = current();
      } while (canBeInNonQuotedString(c));
    } else {
      return DeserializationError::InvalidInput;
    }

    const char *result = builder.complete();
    if (!result)
      return DeserializationError::NoMemory;
    return result;
  }

  DeserializationError skipString() {
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
    const char stopChar = current();

    move();
    for (;;) {
      char c = current();
      move();
      if (c == stopChar)
        break;
<<<<<<< HEAD
      if (c == '\0') {
        _error = DeserializationError::IncompleteInput;
        return false;
      }
=======
      if (c == '\0')
        return DeserializationError::IncompleteInput;
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
      if (c == '\\') {
        if (current() != '\0')
          move();
      }
    }

<<<<<<< HEAD
    return true;
  }

  bool parseNumericValue(VariantData &result) {
=======
    return DeserializationError::Ok;
  }

  DeserializationError parseNumericValue(VariantData &result) {
    char buffer[64];
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
    uint8_t n = 0;

    char c = current();
    while (canBeInNonQuotedString(c) && n < 63) {
      move();
<<<<<<< HEAD
      _buffer[n++] = c;
      c = current();
    }
    _buffer[n] = 0;

    c = _buffer[0];
    if (c == 't') {  // true
      result.setBoolean(true);
      if (n != 4) {
        _error = DeserializationError::IncompleteInput;
        return false;
      }
      return true;
    }
    if (c == 'f') {  // false
      result.setBoolean(false);
      if (n != 5) {
        _error = DeserializationError::IncompleteInput;
        return false;
      }
      return true;
    }
    if (c == 'n') {  // null
      // the variant is already null
      if (n != 4) {
        _error = DeserializationError::IncompleteInput;
        return false;
      }
      return true;
    }

    ParsedNumber<Float, UInt> num;
    parseNumber<Float, UInt>(_buffer, num);
=======
      buffer[n++] = c;
      c = current();
    }
    buffer[n] = 0;

    c = buffer[0];
    if (c == 't') {  // true
      result.setBoolean(true);
      return n == 4 ? DeserializationError::Ok
                    : DeserializationError::IncompleteInput;
    }
    if (c == 'f') {  // false
      result.setBoolean(false);
      return n == 5 ? DeserializationError::Ok
                    : DeserializationError::IncompleteInput;
    }
    if (c == 'n') {  // null
      // the variant is already null
      return n == 4 ? DeserializationError::Ok
                    : DeserializationError::IncompleteInput;
    }

    ParsedNumber<Float, UInt> num = parseNumber<Float, UInt>(buffer);
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323

    switch (num.type()) {
      case VALUE_IS_NEGATIVE_INTEGER:
        result.setNegativeInteger(num.uintValue);
<<<<<<< HEAD
        return true;

      case VALUE_IS_POSITIVE_INTEGER:
        result.setPositiveInteger(num.uintValue);
        return true;

      case VALUE_IS_FLOAT:
        result.setFloat(num.floatValue);
        return true;

      default:
        _error = DeserializationError::InvalidInput;
        return false;
    }
  }

  bool skipNumericValue() {
=======
        return DeserializationError::Ok;

      case VALUE_IS_POSITIVE_INTEGER:
        result.setPositiveInteger(num.uintValue);
        return DeserializationError::Ok;

      case VALUE_IS_FLOAT:
        result.setFloat(num.floatValue);
        return DeserializationError::Ok;
    }

    return DeserializationError::InvalidInput;
  }

  DeserializationError skipNumericValue() {
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
    char c = current();
    while (canBeInNonQuotedString(c)) {
      move();
      c = current();
    }
<<<<<<< HEAD
    return true;
  }

  bool parseHex4(uint16_t &result) {
    result = 0;
    for (uint8_t i = 0; i < 4; ++i) {
      char digit = current();
      if (!digit) {
        _error = DeserializationError::IncompleteInput;
        return false;
      }
      uint8_t value = decodeHex(digit);
      if (value > 0x0F) {
        _error = DeserializationError::InvalidInput;
        return false;
      }
      result = uint16_t((result << 4) | value);
      move();
    }
    return true;
=======
    return DeserializationError::Ok;
  }

  DeserializationError parseHex4(uint16_t &result) {
    result = 0;
    for (uint8_t i = 0; i < 4; ++i) {
      char digit = current();
      if (!digit)
        return DeserializationError::IncompleteInput;
      uint8_t value = decodeHex(digit);
      if (value > 0x0F)
        return DeserializationError::InvalidInput;
      result = uint16_t((result << 4) | value);
      move();
    }
    return DeserializationError::Ok;
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
  }

  static inline bool isBetween(char c, char min, char max) {
    return min <= c && c <= max;
  }

  static inline bool canBeInNonQuotedString(char c) {
    return isBetween(c, '0', '9') || isBetween(c, '_', 'z') ||
           isBetween(c, 'A', 'Z') || c == '+' || c == '-' || c == '.';
  }

  static inline bool isQuote(char c) {
    return c == '\'' || c == '\"';
  }

  static inline uint8_t decodeHex(char c) {
    if (c < 'A')
      return uint8_t(c - '0');
    c = char(c & ~0x20);  // uppercase
    return uint8_t(c - 'A' + 10);
  }

<<<<<<< HEAD
  bool skipSpacesAndComments() {
=======
  DeserializationError skipSpacesAndComments() {
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
    for (;;) {
      switch (current()) {
        // end of string
        case '\0':
<<<<<<< HEAD
          _error = DeserializationError::IncompleteInput;
          return false;
=======
          return DeserializationError::IncompleteInput;
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323

        // spaces
        case ' ':
        case '\t':
        case '\r':
        case '\n':
          move();
          continue;

#if ARDUINOJSON_ENABLE_COMMENTS
        // comments
        case '/':
          move();  // skip '/'
          switch (current()) {
            // block comment
            case '*': {
              move();  // skip '*'
              bool wasStar = false;
              for (;;) {
                char c = current();
<<<<<<< HEAD
                if (c == '\0') {
                  _error = DeserializationError::IncompleteInput;
                  return false;
                }
=======
                if (c == '\0')
                  return DeserializationError::IncompleteInput;
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
                if (c == '/' && wasStar) {
                  move();
                  break;
                }
                wasStar = c == '*';
                move();
              }
              break;
            }

            // trailing comment
            case '/':
              // no need to skip "//"
              for (;;) {
                move();
                char c = current();
<<<<<<< HEAD
                if (c == '\0') {
                  _error = DeserializationError::IncompleteInput;
                  return false;
                }
=======
                if (c == '\0')
                  return DeserializationError::IncompleteInput;
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
                if (c == '\n')
                  break;
              }
              break;

            // not a comment, just a '/'
            default:
<<<<<<< HEAD
              _error = DeserializationError::InvalidInput;
              return false;
=======
              return DeserializationError::InvalidInput;
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
          }
          break;
#endif

        default:
<<<<<<< HEAD
          return true;
=======
          return DeserializationError::Ok;
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
      }
    }
  }

<<<<<<< HEAD
  TStringStorage _stringStorage;
  Latch<TReader> _latch;
  MemoryPool *_pool;
  char _buffer[64];  // using a member instead of a local variable because it
                     // ended in the recursive path after compiler inlined the
                     // code
  DeserializationError _error;
=======
  MemoryPool *_pool;
  TStringStorage _stringStorage;
  Latch<TReader> _latch;
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
};

// deserializeJson(JsonDocument&, const std::string&, ...)
template <typename TInput>
DeserializationError deserializeJson(
    JsonDocument &doc, const TInput &input,
    NestingLimit nestingLimit = NestingLimit()) {
  return deserialize<JsonDeserializer>(doc, input, nestingLimit,
                                       AllowAllFilter());
}
template <typename TInput>
DeserializationError deserializeJson(
    JsonDocument &doc, const TInput &input, Filter filter,
    NestingLimit nestingLimit = NestingLimit()) {
  return deserialize<JsonDeserializer>(doc, input, nestingLimit, filter);
}
template <typename TInput>
DeserializationError deserializeJson(JsonDocument &doc, const TInput &input,
                                     NestingLimit nestingLimit, Filter filter) {
  return deserialize<JsonDeserializer>(doc, input, nestingLimit, filter);
}

// deserializeJson(JsonDocument&, const std::istream&, ...)
template <typename TInput>
DeserializationError deserializeJson(
    JsonDocument &doc, TInput &input,
    NestingLimit nestingLimit = NestingLimit()) {
  return deserialize<JsonDeserializer>(doc, input, nestingLimit,
                                       AllowAllFilter());
}
template <typename TInput>
DeserializationError deserializeJson(
    JsonDocument &doc, TInput &input, Filter filter,
    NestingLimit nestingLimit = NestingLimit()) {
  return deserialize<JsonDeserializer>(doc, input, nestingLimit, filter);
}
template <typename TInput>
DeserializationError deserializeJson(JsonDocument &doc, TInput &input,
                                     NestingLimit nestingLimit, Filter filter) {
  return deserialize<JsonDeserializer>(doc, input, nestingLimit, filter);
}

// deserializeJson(JsonDocument&, char*, ...)
template <typename TChar>
DeserializationError deserializeJson(
    JsonDocument &doc, TChar *input,
    NestingLimit nestingLimit = NestingLimit()) {
  return deserialize<JsonDeserializer>(doc, input, nestingLimit,
                                       AllowAllFilter());
}
template <typename TChar>
DeserializationError deserializeJson(
    JsonDocument &doc, TChar *input, Filter filter,
    NestingLimit nestingLimit = NestingLimit()) {
  return deserialize<JsonDeserializer>(doc, input, nestingLimit, filter);
}
template <typename TChar>
DeserializationError deserializeJson(JsonDocument &doc, TChar *input,
                                     NestingLimit nestingLimit, Filter filter) {
  return deserialize<JsonDeserializer>(doc, input, nestingLimit, filter);
}

// deserializeJson(JsonDocument&, char*, size_t, ...)
template <typename TChar>
DeserializationError deserializeJson(
    JsonDocument &doc, TChar *input, size_t inputSize,
    NestingLimit nestingLimit = NestingLimit()) {
  return deserialize<JsonDeserializer>(doc, input, inputSize, nestingLimit,
                                       AllowAllFilter());
}
template <typename TChar>
DeserializationError deserializeJson(
    JsonDocument &doc, TChar *input, size_t inputSize, Filter filter,
    NestingLimit nestingLimit = NestingLimit()) {
  return deserialize<JsonDeserializer>(doc, input, inputSize, nestingLimit,
                                       filter);
}
template <typename TChar>
DeserializationError deserializeJson(JsonDocument &doc, TChar *input,
                                     size_t inputSize,
                                     NestingLimit nestingLimit, Filter filter) {
  return deserialize<JsonDeserializer>(doc, input, inputSize, nestingLimit,
                                       filter);
}

}  // namespace ARDUINOJSON_NAMESPACE
