#!/bin/bash

echo "-----------------------------------------"
cd treeftp
echo "Cleaning ..."
mvn clean
rm test.txt
cd ../
rm out.txt