#!/bin/bash

TAG=$(git describe)
OUTPUT="ArduinoJson-$TAG.zip"

cd $(dirname $0)/../../..

# remove existing file
rm -f $OUTPUT

# create zip
7z a $OUTPUT \
<<<<<<< HEAD
    -xr!.vs \
=======
>>>>>>> dce77748af3c22e162ad61f1af6ada0e8e718323
	ArduinoJson/CHANGELOG.md \
	ArduinoJson/examples \
	ArduinoJson/src \
	ArduinoJson/keywords.txt \
	ArduinoJson/library.properties \
	ArduinoJson/LICENSE.md \
	ArduinoJson/README.md \
	ArduinoJson/ArduinoJson.h
