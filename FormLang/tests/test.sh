#!/bin/bash

cd ../src

echo "Building parser..."
make clean
make

echo "Testing parser with registration form..."
./formLang ../examples/registration.form

echo "Testing invalid form syntax..."
echo "form Invalid {" > ../examples/invalid.form
echo "  section Test {" >> ../examples/invalid.form
echo "    field test: text" >> ../examples/invalid.form
echo "  }" >> ../examples/invalid.form
echo "}" >> ../examples/invalid.form

./formLang ../examples/invalid.form

echo "Testing complete." 