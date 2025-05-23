#!/bin/bash

# Test script for FormLang++

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Function to run a test
run_test() {
    local input_file=$1
    local expected_output=$2
    local test_name=$3
    local output_file="../output/$(basename $input_file .form).html"
    local error_file="../output/$(basename $input_file .form).err"

    echo -e "${YELLOW}Running test: $test_name${NC}"
    echo "Input file: $input_file"
    echo "Output file: $output_file"

    # Run the parser and save output to file
    ../bin/formLang < $input_file > $output_file 2>$error_file
    result=$?

    if [ $result -eq 0 ]; then
        if [ "$expected_output" = "success" ]; then
            echo -e "${GREEN}Test passed: $test_name${NC}"
            echo "HTML output saved to: $output_file"
            return 0
        else
            echo -e "${RED}Test failed: $test_name (Expected error but got success)${NC}"
            return 1
        fi
    else
        if [ "$expected_output" = "error" ]; then
            echo -e "${GREEN}Test passed: $test_name (Expected error)${NC}"
            echo "Error output:"
            cat $error_file
            return 0
        else
            echo -e "${RED}Test failed: $test_name${NC}"
            echo "Error output:"
            cat $error_file
            return 1
        fi
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

# Test 3: Edge cases
run_test "../examples/edge_cases.form" "success" "Edge Cases"

# Test 4: Invalid form syntax
cat > ../examples/invalid.form << 'EOF'
form Invalid {
  section Test {
    field test: invalid required;
    field test2: text
  }
}
EOF
run_test "../examples/invalid.form" "error" "Invalid Syntax"

# Test 5: Empty form
cat > ../examples/empty.form << 'EOF'
form Empty {}
EOF
run_test "../examples/empty.form" "success" "Empty Form"

# Test 6: Form with duplicate field names
cat > ../examples/duplicate.form << 'EOF'
form Duplicate {
  section Test {
    field test: text required;
    field test: text required;
  }
}
EOF
run_test "../examples/duplicate.form" "error" "Duplicate Field Names"

# Test 7: Form with invalid field type
cat > ../examples/invalid_type.form << 'EOF'
form InvalidType {
  section Test {
    field test: invalid required;
  }
}
EOF
run_test "../examples/invalid_type.form" "error" "Invalid Field Type"

# Test 8: Form with missing semicolon
cat > ../examples/missing_semicolon.form << 'EOF'
form MissingSemicolon {
  section Test {
    field test: text required
  }
}
EOF
run_test "../examples/missing_semicolon.form" "error" "Missing Semicolon"

# Test 9: Form with invalid section nesting
cat > ../examples/invalid_nesting.form << 'EOF'
form InvalidNesting {
  section Outer {
    section Inner {
      field test: text required;
    }
  }
}
EOF
run_test "../examples/invalid_nesting.form" "error" "Invalid Section Nesting"

# Test 10: Form with invalid field attribute
cat > ../examples/invalid_attribute.form << 'EOF'
form InvalidAttribute {
  section Test {
    field test: text invalid;
  }
}
EOF
run_test "../examples/invalid_attribute.form" "error" "Invalid Field Attribute"

# Test 11: Form with missing field type
cat > ../examples/missing_type.form << 'EOF'
form MissingType {
  section Test {
    field test: required;
  }
}
EOF
run_test "../examples/missing_type.form" "error" "Missing Field Type"

# Test 12: Form with missing field name
cat > ../examples/missing_name.form << 'EOF'
form MissingName {
  section Test {
    field : text required;
  }
}
EOF
run_test "../examples/missing_name.form" "error" "Missing Field Name"

# Cleanup temporary test files
rm -f ../examples/empty.form ../examples/duplicate.form ../examples/invalid_type.form \
      ../examples/missing_semicolon.form ../examples/invalid_nesting.form \
      ../examples/invalid_attribute.form ../examples/missing_type.form \
      ../examples/missing_name.form

echo "Tests completed." 