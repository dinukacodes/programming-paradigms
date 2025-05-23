#!/bin/bash

# Test script for metadata functionality
echo "Testing metadata functionality..."

# Create test directory if it doesn't exist
mkdir -p ../output

# Test 1: Basic metadata
echo "Test 1: Basic metadata"
cat > ../examples/test1.form << 'EOF'
form TestForm {
    meta author = "Test Author";
    meta version = "1.0";
    meta description = "Test form with basic metadata";

    section Test {
        field name: text {
            required;
        }
    }
}
EOF

# Test 2: Multiple metadata entries
echo "Test 2: Multiple metadata entries"
cat > ../examples/test2.form << 'EOF'
form TestForm {
    meta author = "Test Author";
    meta version = "1.0";
    meta description = "Test form with multiple metadata";
    meta created = "2024-03-20";
    meta tags = "test,metadata";

    section Test {
        field name: text {
            required;
        }
    }
}
EOF

# Test 3: Metadata with special characters
echo "Test 3: Metadata with special characters"
cat > ../examples/test3.form << 'EOF'
form TestForm {
    meta author = "Test Author & Co.";
    meta description = "Test form with special chars: @#$%^&*()";
    meta version = "1.0-beta";

    section Test {
        field name: text {
            required;
        }
    }
}
EOF

# Test 4: Empty metadata value
echo "Test 4: Empty metadata value"
cat > ../examples/test4.form << 'EOF'
form TestForm {
    meta author = "";
    meta version = "1.0";

    section Test {
        field name: text {
            required;
        }
    }
}
EOF

# Run tests
for i in {1..4}; do
    echo "Running test $i..."
    ./formLang ../examples/test$i.form > ../output/test$i.html
    
    # Check if HTML contains metadata
    if grep -q "<!-- Metadata:" ../output/test$i.html; then
        echo "Test $i: PASSED - Metadata found in HTML"
    else
        echo "Test $i: FAILED - Metadata not found in HTML"
    fi
done

# Test 5: Invalid metadata (should fail gracefully)
echo "Test 5: Invalid metadata"
cat > ../examples/test5.form << 'EOF'
form TestForm {
    meta author = "Test Author"
    meta version = 1.0;
    meta description = "Test form with invalid metadata";

    section Test {
        field name: text {
            required;
        }
    }
}
EOF

echo "Running test 5 (should show error)..."
./formLang ../examples/test5.form > ../output/test5.html 2>&1

# Cleanup
echo "Cleaning up..."
rm -f ../examples/test*.form
rm -f ../output/test*.html

echo "Testing complete!" 