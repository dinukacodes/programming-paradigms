#!/bin/bash

# Test script for FormLang++

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Function to run a test
run_test() {
    local input_file=$1
    local expected_output=$2
    local test_name=$3
    local output_file="../output/$(basename $input_file .form).html"

    echo "Running test: $test_name"
    echo "Input file: $input_file"
    echo "Output file: $output_file"

    # Run the parser and save output to file
    ../bin/formLang < $input_file > $output_file 2>$output_file.err
    result=$?

    if [ $result -eq 0 ]; then
        echo -e "${GREEN}Test passed: $test_name${NC}"
        echo "HTML output saved to: $output_file"
        return 0
    else
        echo -e "${RED}Test failed: $test_name${NC}"
        echo "Error output:"
        cat $output_file.err
        return 1
    fi
}

# Create output directory if it doesn't exist
mkdir -p ../output

# Test cases
echo "Starting FormLang++ tests..."

# Test 1: Basic form with text fields
run_test "../examples/registration.form" "success" "Basic Registration Form"

# Test 2: Form with all field types
run_test "../examples/all_fields.form" "success" "All Field Types"

# Test 3: Invalid form syntax
run_test "../examples/invalid.form" "error" "Invalid Syntax"

echo "Tests completed." 