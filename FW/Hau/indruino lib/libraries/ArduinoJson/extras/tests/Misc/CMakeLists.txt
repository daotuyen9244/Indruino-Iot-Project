# ArduinoJson - arduinojson.org
# Copyright Benoit Blanchon 2014-2020
# MIT License

add_executable(MiscTests
<<<<<<< HEAD
	arithmeticCompare.cpp
	conflicts.cpp
	FloatParts.cpp
	JsonString.cpp
=======
	conflicts.cpp
	FloatParts.cpp
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
	Readers.cpp
	StringAdapters.cpp
	StringWriter.cpp
	TypeTraits.cpp
	unsigned_char.cpp
<<<<<<< HEAD
	Utf16.cpp
	Utf8.cpp
=======
	Utf8.cpp
	Utf16.cpp
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
	version.cpp
)

set_target_properties(MiscTests PROPERTIES UNITY_BUILD OFF)

add_test(Misc MiscTests)
