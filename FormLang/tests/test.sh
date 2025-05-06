#!/bin/bash

# Compile the lexer
cd ../src
flex lexer.l
gcc -o lexer lex.yy.c -lfl

# Test the lexer with the example file
echo "Testing lexer with registration.form..."
./lexer < ../examples/registration.form

# Clean up
rm lex.yy.c lexer 