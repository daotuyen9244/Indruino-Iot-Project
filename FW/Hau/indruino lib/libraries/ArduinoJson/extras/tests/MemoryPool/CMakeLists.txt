# ArduinoJson - arduinojson.org
# Copyright Benoit Blanchon 2014-2020
# MIT License

add_executable(MemoryPoolTests 
	allocVariant.cpp
<<<<<<< HEAD
	clear.cpp
	saveString.cpp
	size.cpp
	StringCopier.cpp
=======
	allocString.cpp
	clear.cpp
	size.cpp
	StringBuilder.cpp
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
)

add_test(MemoryPool MemoryPoolTests)
