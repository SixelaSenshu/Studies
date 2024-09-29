#!/bin/bash

echo "-----------------------------------------"
cd serverFtp
echo "Generating doc ..."
mvn javadoc:javadoc
cd ../