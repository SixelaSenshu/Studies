#!/bin/bash

echo "-----------------------------------------"
cd treeftp
echo "Generating doc ..."
mvn javadoc:javadoc
cd ../