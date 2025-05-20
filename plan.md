# FormLang++ Project Setup Guide

## Project Structure

Here's the recommended directory structure for your FormLang++ project:

```
FormLang/
├── src/                  # Source code files
│   ├── lexer.l           # Flex lexical analyzer
│   ├── parser.y          # Bison parser
│   ├── formLang.h        # Common header file
│   ├── html_generator.c  # HTML generation functions
│   └── Makefile          # Build configuration
├── examples/             # Example FormLang++ files
│   ├── registration.form
│   └── invalid.form
├── tests/                # Test scripts
│   ├── test.sh
│   └── debug.sh
├── output/               # Generated HTML output
└── docs/                 # Documentation
    └── grammar.pdf
```

This structure separates source code, examples, tests, and output, making the project easier to maintain and understand.

## Setting Up Your Linux Environment

### 1. Install Required Packages

You need to install the following tools to build your FormLang++ project:

#### For Ubuntu/Debian-based systems:
```bash
sudo apt update
sudo apt install flex bison build-essential gcc make
```

#### For Red Hat/Fedora-based systems:
```bash
sudo dnf install flex bison gcc make
```

#### For Arch Linux:
```bash
sudo pacman -S flex bison gcc make
```

### 2. Verify Installation

Confirm that all tools are properly installed:

```bash
flex --version    # Should show something like flex 2.6.4
bison --version   # Should show something like bison (GNU Bison) 3.8.2
gcc --version     # Should show GCC version
make --version    # Should show GNU Make version
```

### 3. Create Project Directory and Files

Set up your project structure:

```bash
# Create directories
mkdir -p FormLang/src FormLang/examples FormLang/tests FormLang/output FormLang/docs

# Change to project directory
cd FormLang

# Create source files
touch src/lexer.l src/parser.y src/formLang.h src/html_generator.c src/Makefile

# Create example files
touch examples/registration.form

# Create test scripts
touch tests/test.sh tests/debug.sh
chmod +x tests/test.sh tests/debug.sh
```

### 4. Makefile Setup

Create a `Makefile` in the `src` directory with the following content:

```makefile
# FormLang++ Makefile
# Builds the FormLang++ DSL parser and HTML generator

# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Flex and Bison
FLEX = flex
BISON = bison

# Output executable
TARGET = formLang

# Source files
LEX_SRC = lexer.l
YACC_SRC = parser.y
C_SRC = html_generator.c

# Generated files
LEX_C = lex.yy.c
YACC_C = y.tab.c
YACC_H = y.tab.h
OBJS = $(LEX_C:.c=.o) $(YACC_C:.c=.o) $(C_SRC:.c=.o)

# Default target
all: $(TARGET)

# Linking the target executable
$(TARGET): $(LEX_C) $(YACC_C) $(C_SRC)
	$(CC) $(CFLAGS) -o $@ $^ -lfl

# Generate parser from Bison grammar
$(YACC_C) $(YACC_H): $(YACC_SRC)
	$(BISON) -d -y $

# Generate lexer from Flex specification
$(LEX_C): $(LEX_SRC) $(YACC_H)
	$(FLEX) $

# Clean build artifacts
clean:
	rm -f $(TARGET) $(LEX_C) $(YACC_C) $(YACC_H) *.o

# Run tests
test: $(TARGET)
	../tests/test.sh

# Debug with valgrind
debug: $(TARGET)
	../tests/debug.sh

# Phony targets
.PHONY: all clean test debug
```

### 5. Build Instructions

To build and test your FormLang++ project:

```bash
# Change to the src directory
cd src

# Build the project
make

# Run tests
make test

# Debug with valgrind
make debug

# Clean build artifacts
make clean
```

### 6. Running the FormLang++ Parser

After building, you can run the parser directly:

```bash
# Parse a FormLang++ file and generate HTML
./formLang ../examples/registration.form > ../output/registration.html

# Alternatively, with explicit output file
./formLang ../examples/registration.form -o ../output/registration.html
```

### 7. Development Workflow

For efficient development, follow this workflow:

1. Start with a simple lexer that recognizes basic tokens
2. Add a simple parser that handles basic form structure
3. Incrementally add support for more field types and attributes
4. Test frequently with example forms to verify functionality
5. Add HTML generation features as you progress
6. Refine error handling and recovery mechanisms
7. Document your grammar and implementation

### 8. Debugging Tips

- Use `flex -d` to enable debug mode in your lexer
- Use `bison -v` to generate a verbose output file explaining grammar states
- Use `valgrind` to check for memory leaks
- Add printf statements to trace parsing and AST building
- Check for common issues like uninitialized variables or buffer overflows

This comprehensive setup provides you with all the tools and structure needed to successfully implement your FormLang++ DSL project.

# Technical Implementation Plan for FormLang++ DSL

Here's a detailed 10-milestone plan for building your FormLang++ DSL, starting with the most fundamental components and progressively adding features. Each milestone builds on the previous one and delivers a functional system that you can test and refine.

## Milestone 1: Grammar Definition and Basic Lexer
**Estimated time: 1.5 hours**

**Tasks:**
1. Write the EBNF grammar for the core language elements:
   - Form declaration
   - Section declaration
   - Basic field types (text, email, password)
   - Simple attributes (required, optional)

2. Implement the initial lexer (lexer.l) with:
   - Token definitions for keywords (form, section, field)
   - Basic types and attributes
   - Identifiers and literals (strings, numbers)
   - Symbol tokens (braces, semicolons, colons)

3. Write a test script to verify lexer output:
   - Create a simple input.form file
   - Run the lexer to output token stream
   - Verify correct token identification

**Success criteria:** Lexer correctly identifies all tokens in a simple form definition and reports correct line numbers for errors.

## Milestone 2: Basic Parser Structure
**Estimated time: 2 hours**

**Tasks:**
1. Implement a basic parser (parser.y) that can:
   - Parse form declarations
   - Handle section declarations
   - Process basic field declarations with types
   - Report syntax errors with line numbers

2. Add basic semantic checks:
   - Verify field names are unique within sections
   - Ensure required attributes are present for certain field types

3. Create a simple AST (Abstract Syntax Tree) structure:
   - Define node types for forms, sections, fields
   - Build the tree during parsing
   - Add a simple tree printer for debugging

**Success criteria:** Parser can successfully parse a simple form definition and build an AST representation.

## Milestone 3: HTML Generator Foundation
**Estimated time: 2 hours**

**Tasks:**
1. Create HTML generation functions:
   - Form header/footer generation
   - Section (fieldset) generation
   - Basic field rendering for text, email, and password types

2. Integrate HTML generation with parser:
   - Call generation functions during parsing
   - Output HTML to a file
   - Add basic CSS for form styling

3. Add command-line options:
   - Input file specification
   - Output file path
   - Verbose mode for debugging

**Success criteria:** The system can parse a simple form and generate basic HTML with proper structure.

## Milestone 4: Extended Field Types & Attributes
**Estimated time: 2 hours**

**Tasks:**
1. Extend lexer and parser to support more field types:
   - textarea, number, date, checkbox
   - dropdown, radio, file

2. Add support for field attributes:
   - minLength/maxLength for text fields
   - min/max for number fields
   - rows/cols for textarea
   - pattern for validation
   - default values

3. Update HTML generator to handle new field types:
   - Generate appropriate input elements
   - Add attributes based on field specifications
   - Handle arrays for dropdowns and radio buttons

**Success criteria:** Parser can handle all basic field types with their attributes and generate corresponding HTML elements.

## Milestone 5: Registration-Specific Fields
**Estimated time: 2 hours**

**Tasks:**
1. Add specialized field types for registration forms:
   - username field type with pattern validation
   - password field with strength validation
   - confirmable email fields
   - address fields with sub-components

2. Extend the parser to handle the specialized types:
   - Add tokens and grammar rules
   - Process specialized attributes

3. Enhance HTML generation:
   - Generate complex fields with appropriate structure
   - Add client-side validation for specialized fields
   - Implement password strength meters

**Success criteria:** The system generates registration-specific field types with appropriate HTML and client-side validation.


## Milestone 5: Validation Block Implementation

**Estimated time: 2 hours**

**Tasks:**

1. Add validation block syntax to lexer and parser:

   * Implement `validate` keyword and block structure
   * Add support for conditional expressions (`if` statements)
   * Implement comparison operators (`<`, `>`, `==`, `!=`, etc.)
   * Define grammar rules for nested blocks

2. Implement field reference and validation logic:

   * Allow field references in conditions
   * Check that referenced fields exist
   * Handle type comparisons correctly
   * Support error message declarations

3. Generate client-side validation JavaScript:

   * Form submission event handlersa
   * Condition evaluation functions
   * Field value retrieval logic
   * Error message display functions
   * Test with example: `if age < 18 { error "You must be at least 18."; }`

**Success criteria:** The parser correctly handles validation blocks from the assignment brief example and generates functional JavaScript validation code.

---

## Milestone 6: Metadata & Pattern Support

**Estimated time: 1.5 hours**

**Tasks:**

1. Implement metadata declaration support:

   * Add `meta` keyword to lexer
   * Create grammar rules for meta declarations
   * Support string, number, and boolean values
   * Store metadata in form structure
   * Test with example: `meta author = "SE2062 Team";`

2. Complete field attribute implementation:

   * Add `pattern` attribute for `text`/`email`/`password` fields
   * Ensure all required attributes work for each field type per assignment spec
   * Implement options arrays for `dropdown` and `radio` fields
   * Support default values across all applicable field types

3. Update HTML generation for metadata and patterns:

   * Add metadata as HTML comments or data attributes
   * Translate patterns to HTML5 `pattern` attributes
   * Generate appropriate HTML for all field attributes
   * Ensure semantic correctness of generated HTML

**Success criteria:** Parser correctly handles metadata declarations and all field attributes from the assignment specification, generating proper HTML output.

---

## Milestone 7: EBNF Documentation & Comprehensive Example

**Estimated time: 2 hours**

**Tasks:**

1. Create formal EBNF grammar specification (`grammar.pdf`):

   * Document grammar for `form`, `section`, `field`, `validate`, `meta`

2. Write comprehensive example form:

   * Include all field types, attributes, metadata, and validation
   * Ensure the form is representative of all supported features

3. Run parser and HTML generator on the example:

   * Verify generated HTML is fully functional and valid
   * Include JavaScript for validation
   * Ensure metadata is present in HTML output

**Success criteria:** Complete and correct grammar documentation, a comprehensive example `.form` file, and verified output.

---

## Milestone 8: Final Testing, Cleanup & Packaging

**Estimated time: 1.5 hours**

**Tasks:**

1. Perform final testing on:

   * Lexer and parser with invalid and edge-case inputs
   * HTML output structure and validation logic
   * Memory usage and error handling with Valgrind

2. Cleanup:

   * Remove debug prints
   * Organize code, comments, and folder structure
   * Ensure consistent naming conventions

3. Prepare final package:

   * Include complete documentation
   * Final `.form` examples
   * Source code and Makefile
   * Instructions for building and running

**Success criteria:** All tests pass, output is clean, submission is structured and complete.


## Implementation Strategy Notes

1. **Incremental Testing**: After completing each milestone, write tests to verify functionality before moving to the next milestone.

2. **Version Control**: Commit your changes after each milestone, so you can revert if needed.

3. **Focus on Core Features First**: For the registration form focus, prioritize username, email, and password field types early in implementation.

4. **Modular Design**: Structure your code so that adding new field types or attributes is easy.

5. **Don't Overengineer**: For this assignment, focus on demonstrating understanding rather than building an enterprise-grade system.

Would you like me to elaborate on any specific milestone or provide code examples for critical components? For example, I could provide more detailed lexer/parser rules for the registration-specific fields in Milestone 5.