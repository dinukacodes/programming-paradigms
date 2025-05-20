Project Structure:
├── FormLang
│   ├── Makefile
│   ├── parser.output
│   ├── parser.tab.c
│   ├── progress.md
├── codefetch
│   └── codebase.md
├── plan.md
└── tips.md


plan.md
```
1 | # FormLang++ Project Setup Guide
2 | 
3 | ## Project Structure
4 | 
5 | Here's the recommended directory structure for your FormLang++ project:
6 | 
7 | ```
8 | FormLang/
9 | ├── src/                  # Source code files
10 | │   ├── lexer.l           # Flex lexical analyzer
11 | │   ├── parser.y          # Bison parser
12 | │   ├── formLang.h        # Common header file
13 | │   ├── html_generator.c  # HTML generation functions
14 | │   └── Makefile          # Build configuration
15 | ├── examples/             # Example FormLang++ files
16 | │   ├── registration.form
17 | │   └── invalid.form
18 | ├── tests/                # Test scripts
19 | │   ├── test.sh
20 | │   └── debug.sh
21 | ├── output/               # Generated HTML output
22 | └── docs/                 # Documentation
23 |     └── grammar.pdf
24 | ```
25 | 
26 | This structure separates source code, examples, tests, and output, making the project easier to maintain and understand.
27 | 
28 | ## Setting Up Your Linux Environment
29 | 
30 | ### 1. Install Required Packages
31 | 
32 | You need to install the following tools to build your FormLang++ project:
33 | 
34 | #### For Ubuntu/Debian-based systems:
35 | ```bash
36 | sudo apt update
37 | sudo apt install flex bison build-essential gcc make
38 | ```
39 | 
40 | #### For Red Hat/Fedora-based systems:
41 | ```bash
42 | sudo dnf install flex bison gcc make
43 | ```
44 | 
45 | #### For Arch Linux:
46 | ```bash
47 | sudo pacman -S flex bison gcc make
48 | ```
49 | 
50 | ### 2. Verify Installation
51 | 
52 | Confirm that all tools are properly installed:
53 | 
54 | ```bash
55 | flex --version    # Should show something like flex 2.6.4
56 | bison --version   # Should show something like bison (GNU Bison) 3.8.2
57 | gcc --version     # Should show GCC version
58 | make --version    # Should show GNU Make version
59 | ```
60 | 
61 | ### 3. Create Project Directory and Files
62 | 
63 | Set up your project structure:
64 | 
65 | ```bash
66 | # Create directories
67 | mkdir -p FormLang/src FormLang/examples FormLang/tests FormLang/output FormLang/docs
68 | 
69 | # Change to project directory
70 | cd FormLang
71 | 
72 | # Create source files
73 | touch src/lexer.l src/parser.y src/formLang.h src/html_generator.c src/Makefile
74 | 
75 | # Create example files
76 | touch examples/registration.form
77 | 
78 | # Create test scripts
79 | touch tests/test.sh tests/debug.sh
80 | chmod +x tests/test.sh tests/debug.sh
81 | ```
82 | 
83 | ### 4. Makefile Setup
84 | 
85 | Create a `Makefile` in the `src` directory with the following content:
86 | 
87 | ```makefile
88 | # FormLang++ Makefile
89 | # Builds the FormLang++ DSL parser and HTML generator
90 | 
91 | # Compiler and flags
92 | CC = gcc
93 | CFLAGS = -Wall -g
94 | 
95 | # Flex and Bison
96 | FLEX = flex
97 | BISON = bison
98 | 
99 | # Output executable
100 | TARGET = formLang
101 | 
102 | # Source files
103 | LEX_SRC = lexer.l
104 | YACC_SRC = parser.y
105 | C_SRC = html_generator.c
106 | 
107 | # Generated files
108 | LEX_C = lex.yy.c
109 | YACC_C = y.tab.c
110 | YACC_H = y.tab.h
111 | OBJS = $(LEX_C:.c=.o) $(YACC_C:.c=.o) $(C_SRC:.c=.o)
112 | 
113 | # Default target
114 | all: $(TARGET)
115 | 
116 | # Linking the target executable
117 | $(TARGET): $(LEX_C) $(YACC_C) $(C_SRC)
118 | 	$(CC) $(CFLAGS) -o $@ $^ -lfl
119 | 
120 | # Generate parser from Bison grammar
121 | $(YACC_C) $(YACC_H): $(YACC_SRC)
122 | 	$(BISON) -d -y $
123 | 
124 | # Generate lexer from Flex specification
125 | $(LEX_C): $(LEX_SRC) $(YACC_H)
126 | 	$(FLEX) $
127 | 
128 | # Clean build artifacts
129 | clean:
130 | 	rm -f $(TARGET) $(LEX_C) $(YACC_C) $(YACC_H) *.o
131 | 
132 | # Run tests
133 | test: $(TARGET)
134 | 	../tests/test.sh
135 | 
136 | # Debug with valgrind
137 | debug: $(TARGET)
138 | 	../tests/debug.sh
139 | 
140 | # Phony targets
141 | .PHONY: all clean test debug
142 | ```
143 | 
144 | ### 5. Build Instructions
145 | 
146 | To build and test your FormLang++ project:
147 | 
148 | ```bash
149 | # Change to the src directory
150 | cd src
151 | 
152 | # Build the project
153 | make
154 | 
155 | # Run tests
156 | make test
157 | 
158 | # Debug with valgrind
159 | make debug
160 | 
161 | # Clean build artifacts
162 | make clean
163 | ```
164 | 
165 | ### 6. Running the FormLang++ Parser
166 | 
167 | After building, you can run the parser directly:
168 | 
169 | ```bash
170 | # Parse a FormLang++ file and generate HTML
171 | ./formLang ../examples/registration.form > ../output/registration.html
172 | 
173 | # Alternatively, with explicit output file
174 | ./formLang ../examples/registration.form -o ../output/registration.html
175 | ```
176 | 
177 | ### 7. Development Workflow
178 | 
179 | For efficient development, follow this workflow:
180 | 
181 | 1. Start with a simple lexer that recognizes basic tokens
182 | 2. Add a simple parser that handles basic form structure
183 | 3. Incrementally add support for more field types and attributes
184 | 4. Test frequently with example forms to verify functionality
185 | 5. Add HTML generation features as you progress
186 | 6. Refine error handling and recovery mechanisms
187 | 7. Document your grammar and implementation
188 | 
189 | ### 8. Debugging Tips
190 | 
191 | - Use `flex -d` to enable debug mode in your lexer
192 | - Use `bison -v` to generate a verbose output file explaining grammar states
193 | - Use `valgrind` to check for memory leaks
194 | - Add printf statements to trace parsing and AST building
195 | - Check for common issues like uninitialized variables or buffer overflows
196 | 
197 | This comprehensive setup provides you with all the tools and structure needed to successfully implement your FormLang++ DSL project.
198 | 
199 | # Technical Implementation Plan for FormLang++ DSL
200 | 
201 | Here's a detailed 10-milestone plan for building your FormLang++ DSL, starting with the most fundamental components and progressively adding features. Each milestone builds on the previous one and delivers a functional system that you can test and refine.
202 | 
203 | ## Milestone 1: Grammar Definition and Basic Lexer
204 | **Estimated time: 1.5 hours**
205 | 
206 | **Tasks:**
207 | 1. Write the EBNF grammar for the core language elements:
208 |    - Form declaration
209 |    - Section declaration
210 |    - Basic field types (text, email, password)
211 |    - Simple attributes (required, optional)
212 | 
213 | 2. Implement the initial lexer (lexer.l) with:
214 |    - Token definitions for keywords (form, section, field)
215 |    - Basic types and attributes
216 |    - Identifiers and literals (strings, numbers)
217 |    - Symbol tokens (braces, semicolons, colons)
218 | 
219 | 3. Write a test script to verify lexer output:
220 |    - Create a simple input.form file
221 |    - Run the lexer to output token stream
222 |    - Verify correct token identification
223 | 
224 | **Success criteria:** Lexer correctly identifies all tokens in a simple form definition and reports correct line numbers for errors.
225 | 
226 | ## Milestone 2: Basic Parser Structure
227 | **Estimated time: 2 hours**
228 | 
229 | **Tasks:**
230 | 1. Implement a basic parser (parser.y) that can:
231 |    - Parse form declarations
232 |    - Handle section declarations
233 |    - Process basic field declarations with types
234 |    - Report syntax errors with line numbers
235 | 
236 | 2. Add basic semantic checks:
237 |    - Verify field names are unique within sections
238 |    - Ensure required attributes are present for certain field types
239 | 
240 | 3. Create a simple AST (Abstract Syntax Tree) structure:
241 |    - Define node types for forms, sections, fields
242 |    - Build the tree during parsing
243 |    - Add a simple tree printer for debugging
244 | 
245 | **Success criteria:** Parser can successfully parse a simple form definition and build an AST representation.
246 | 
247 | ## Milestone 3: HTML Generator Foundation
248 | **Estimated time: 2 hours**
249 | 
250 | **Tasks:**
251 | 1. Create HTML generation functions:
252 |    - Form header/footer generation
253 |    - Section (fieldset) generation
254 |    - Basic field rendering for text, email, and password types
255 | 
256 | 2. Integrate HTML generation with parser:
257 |    - Call generation functions during parsing
258 |    - Output HTML to a file
259 |    - Add basic CSS for form styling
260 | 
261 | 3. Add command-line options:
262 |    - Input file specification
263 |    - Output file path
264 |    - Verbose mode for debugging
265 | 
266 | **Success criteria:** The system can parse a simple form and generate basic HTML with proper structure.
267 | 
268 | ## Milestone 4: Extended Field Types & Attributes
269 | **Estimated time: 2 hours**
270 | 
271 | **Tasks:**
272 | 1. Extend lexer and parser to support more field types:
273 |    - textarea, number, date, checkbox
274 |    - dropdown, radio, file
275 | 
276 | 2. Add support for field attributes:
277 |    - minLength/maxLength for text fields
278 |    - min/max for number fields
279 |    - rows/cols for textarea
280 |    - pattern for validation
281 |    - default values
282 | 
283 | 3. Update HTML generator to handle new field types:
284 |    - Generate appropriate input elements
285 |    - Add attributes based on field specifications
286 |    - Handle arrays for dropdowns and radio buttons
287 | 
288 | **Success criteria:** Parser can handle all basic field types with their attributes and generate corresponding HTML elements.
289 | 
290 | ## Milestone 5: Registration-Specific Fields
291 | **Estimated time: 2 hours**
292 | 
293 | **Tasks:**
294 | 1. Add specialized field types for registration forms:
295 |    - username field type with pattern validation
296 |    - password field with strength validation
297 |    - confirmable email fields
298 |    - address fields with sub-components
299 | 
300 | 2. Extend the parser to handle the specialized types:
301 |    - Add tokens and grammar rules
302 |    - Process specialized attributes
303 | 
304 | 3. Enhance HTML generation:
305 |    - Generate complex fields with appropriate structure
306 |    - Add client-side validation for specialized fields
307 |    - Implement password strength meters
308 | 
309 | **Success criteria:** The system generates registration-specific field types with appropriate HTML and client-side validation.
310 | 
311 | ## Milestone 6: Validation Rules
312 | **Estimated time: 2 hours**
313 | 
314 | **Tasks:**
315 | 1. Implement the validation block grammar:
316 |    - if statements with conditions
317 |    - error message definitions
318 |    - support for field comparisons
319 | 
320 | 2. Add semantic analysis for validation rules:
321 |    - Check that referenced fields exist
322 |    - Verify field types match operations
323 |    - Ensure error messages are provided
324 | 
325 | 3. Generate client-side validation JavaScript:
326 |    - Form submission event handler
327 |    - Field-specific validation functions
328 |    - Error message display
329 | 
330 | **Success criteria:** Parser can process validation blocks and generate JavaScript for client-side form validation.
331 | 
332 | ## Milestone 7: Advanced Features
333 | **Estimated time: 2 hours**
334 | 
335 | **Tasks:**
336 | 1. Implement progressive disclosure:
337 |    - Add disclosure clauses for sections
338 |    - Support initial state (hidden/visible)
339 |    - Generate JavaScript for toggling sections
340 | 
341 | 2. Add field dependencies:
342 |    - Define syntax for field dependencies
343 |    - Update parser to process dependency rules
344 |    - Generate JavaScript to show/hide fields based on values
345 | 
346 | 3. Implement multi-step forms:
347 |    - Add step attribute to sections
348 |    - Generate navigation between steps
349 |    - Maintain state between steps
350 | 
351 | **Success criteria:** The system supports progressive disclosure, field dependencies, and multi-step forms.
352 | 
353 | ## Milestone 8: Error Handling & Recovery
354 | **Estimated time: 1.5 hours**
355 | 
356 | **Tasks:**
357 | 1. Enhance error reporting:
358 |    - Add descriptive error messages
359 |    - Show error context (line and column)
360 |    - Provide suggestions for common mistakes
361 | 
362 | 2. Implement error recovery:
363 |    - Skip to next semicolon after errors
364 |    - Continue parsing after section errors
365 |    - Maintain partial AST after errors
366 | 
367 | 3. Add warning system:
368 |    - Identify potential issues (missing labels, etc.)
369 |    - Suggest best practices
370 |    - Allow warnings to be disabled
371 | 
372 | **Success criteria:** Parser can recover from common errors and continue parsing, providing helpful error messages.
373 | 
374 | ## Milestone 9: Optimization & Styling
375 | **Estimated time: 1.5 hours**
376 | 
377 | **Tasks:**
378 | 1. Add styling capabilities:
379 |    - Theme selection (light/dark)
380 |    - Custom colors and styling
381 |    - Responsive design options
382 | 
383 | 2. Optimize HTML output:
384 |    - Minify generated HTML
385 |    - Group similar CSS rules
386 |    - Optimize JavaScript for performance
387 | 
388 | 3. Add accessibility features:
389 |    - ARIA attributes
390 |    - Tab index management
391 |    - High contrast mode support
392 | 
393 | **Success criteria:** Generated forms are styled, responsive, and accessible with optimized HTML/CSS/JS.
394 | 
395 | ## Milestone 10: Testing & Documentation
396 | **Estimated time: 1.5 hours**
397 | 
398 | **Tasks:**
399 | 1. Create comprehensive test suite:
400 |    - Test all field types and attributes
401 |    - Test validation rules
402 |    - Test error conditions and recovery
403 |    - Test HTML output in different browsers
404 | 
405 | 2. Write documentation:
406 |    - Complete grammar specification
407 |    - Usage examples
408 |    - Extension guide
409 |    - Command-line options
410 | 
411 | 3. Create demonstration video:
412 |    - Walk through the code structure
413 |    - Show parsing and HTML generation
414 |    - Demonstrate error handling
415 |    - Display the final form in action
416 | 
417 | **Success criteria:** Complete test suite passes, documentation is comprehensive, and demonstration video showcases the system's capabilities.
418 | 
419 | ## Implementation Strategy Notes
420 | 
421 | 1. **Incremental Testing**: After completing each milestone, write tests to verify functionality before moving to the next milestone.
422 | 
423 | 2. **Version Control**: Commit your changes after each milestone, so you can revert if needed.
424 | 
425 | 3. **Focus on Core Features First**: For the registration form focus, prioritize username, email, and password field types early in implementation.
426 | 
427 | 4. **Modular Design**: Structure your code so that adding new field types or attributes is easy.
428 | 
429 | 5. **Don't Overengineer**: For this assignment, focus on demonstrating understanding rather than building an enterprise-grade system.
430 | 
431 | Would you like me to elaborate on any specific milestone or provide code examples for critical components? For example, I could provide more detailed lexer/parser rules for the registration-specific fields in Milestone 5.
```

tips.md
```
1 | # FormLang Usage Guide
2 | 
3 | This guide explains how to create and process your own form definitions using FormLang.
4 | 
5 | ## Creating Form Files
6 | 
7 | 1. Create a new file with `.form` extension
8 | 2. Follow the FormLang syntax:
9 |    ```form
10 |    form FormName {
11 |        section SectionName {
12 |            field fieldName: fieldType attribute;
13 |        }
14 |    }
15 |    ```
16 | 
17 | ### Field Types
18 | - `text`: Text input
19 | - `email`: Email input
20 | - `password`: Password input
21 | - `number`: Number input
22 | 
23 | ### Attributes
24 | - `required`: Field must be filled
25 | - `optional`: Field can be left empty
26 | 
27 | ### Example Form
28 | ```form
29 | form MyForm {
30 |     section Personal {
31 |         field name: text required;
32 |         field email: email required;
33 |         field phone: number optional;
34 |     }
35 | }
36 | ```
37 | 
38 | ## Processing Form Files
39 | 
40 | 1. Make sure the code is compiled:
41 |    ```bash
42 |    make clean
43 |    make
44 |    ```
45 | 
46 | 2. Process your form file:
47 |    ```bash
48 |    ./bin/formLang < your_form.form > output/your_form.html
49 |    ```
50 | 
51 | 3. View the generated HTML:
52 |    ```bash
53 |    cat output/your_form.html
54 |    ```
55 | 
56 | ## Tips
57 | 
58 | 1. **File Location**: Place your `.form` files in the `examples` directory
59 | 2. **Output**: Generated HTML files will be in the `output` directory
60 | 3. **Validation**: The parser will show errors if your form definition is invalid
61 | 4. **Empty Sections**: You can have sections with no fields
62 | 5. **Field Names**: Use descriptive names for better HTML output
63 | 6. **Required Fields**: Mark important fields as `required`
64 | 
65 | ## Common Commands
66 | 
67 | ```bash
68 | # Compile the code
69 | make clean && make
70 | 
71 | # Process a form file
72 | ./bin/formLang < examples/your_form.form > output/your_form.html
73 | 
74 | # View generated HTML
75 | cat output/your_form.html
76 | 
77 | # Process multiple forms
78 | ./bin/formLang < examples/form1.form > output/form1.html
79 | ./bin/formLang < examples/form2.form > output/form2.html
80 | ```
81 | 
82 | ## Error Handling
83 | 
84 | If you get errors:
85 | 1. Check the form syntax
86 | 2. Ensure all fields have proper types
87 | 3. Verify semicolons are present
88 | 4. Check for duplicate field names
89 | 5. Make sure sections are properly nested
90 | 
91 | ## Example Forms
92 | 
93 | Check the `examples` directory for sample form definitions:
94 | - `registration.form`: Basic registration form
95 | - `all_fields.form`: Form with all field types
96 | - `complex_form.form`: Complex form with multiple sections
97 | - `mixed_attributes.form`: Form with required and optional fields 
```

FormLang/Makefile
```
1 | CC = gcc
2 | CFLAGS = -Wall -g
3 | FLEX = flex
4 | BISON = bison
5 | 
6 | SRC_DIR = src
7 | OBJ_DIR = obj
8 | BIN_DIR = bin
9 | 
10 | SRCS = $(SRC_DIR)/parser.tab.c $(SRC_DIR)/lex.yy.c $(SRC_DIR)/html_generator.c
11 | OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
12 | TARGET = $(BIN_DIR)/formLang
13 | 
14 | .PHONY: all clean test
15 | 
16 | all: $(TARGET)
17 | 
18 | $(TARGET): $(OBJS)
19 | 	@mkdir -p $(BIN_DIR)
20 | 	$(CC) $(CFLAGS) -o $@ $^ -lfl
21 | 
22 | $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
23 | 	@mkdir -p $(OBJ_DIR)
24 | 	$(CC) $(CFLAGS) -c -o $@ $<
25 | 
26 | $(SRC_DIR)/parser.tab.c $(SRC_DIR)/parser.tab.h: $(SRC_DIR)/parser.y
27 | 	$(BISON) -d -o $(SRC_DIR)/parser.tab.c $<
28 | 
29 | $(SRC_DIR)/lex.yy.c: $(SRC_DIR)/lexer.l $(SRC_DIR)/parser.tab.h
30 | 	$(FLEX) -o $@ $<
31 | 
32 | test: $(TARGET)
33 | 	@echo "Testing with milestone4 example..."
34 | 	@$(TARGET) examples/test_milestone4.form > output/test_milestone4.html
35 | 	@echo "Generated HTML output in output/test_milestone4.html"
36 | 
37 | clean:
38 | 	rm -rf $(OBJ_DIR) $(BIN_DIR)
39 | 	rm -f $(SRC_DIR)/parser.tab.c $(SRC_DIR)/parser.tab.h $(SRC_DIR)/lex.yy.c 
```

FormLang/parser.output
```
1 | Terminals unused in grammar
2 | 
3 |     NUMBER_LITERAL
4 | 
5 | 
6 | State 32 conflicts: 1 shift/reduce
7 | 
8 | 
9 | Grammar
10 | 
11 |     0 $accept: form $end
12 | 
13 |     1 form: FORM IDENTIFIER '{' section_list '}'
14 | 
15 |     2 section_list: ε
16 |     3             | section_list section
17 | 
18 |     4 section: section_header '{' field_list '}'
19 |     5        | section_header error '}'
20 | 
21 |     6 section_header: SECTION IDENTIFIER
22 | 
23 |     7 field_list: ε
24 |     8           | field_list field
25 |     9           | field_list error ';'
26 | 
27 |    10 field: FIELD IDENTIFIER ':' field_type field_attribute ';'
28 |    11      | FIELD ':' field_type field_attribute ';'
29 |    12      | FIELD IDENTIFIER ':' field_attribute ';'
30 |    13      | FIELD IDENTIFIER ':' field_type error ';'
31 |    14      | FIELD IDENTIFIER ':' field_type field_attribute error
32 | 
33 |    15 field_type: TEXT
34 |    16           | EMAIL
35 |    17           | PASSWORD
36 |    18           | NUMBER
37 |    19           | IDENTIFIER
38 | 
39 |    20 field_attribute: REQUIRED
40 |    21                | OPTIONAL
41 |    22                | ε
42 | 
43 | 
44 | Terminals, with rules where they appear
45 | 
46 |     $end (0) 0
47 |     ':' (58) 10 11 12 13 14
48 |     ';' (59) 9 10 11 12 13
49 |     '{' (123) 1 4
50 |     '}' (125) 1 4 5
51 |     error (256) 5 9 13 14
52 |     FORM (258) 1
53 |     SECTION (259) 6
54 |     FIELD (260) 10 11 12 13 14
55 |     TEXT (261) 15
56 |     EMAIL (262) 16
57 |     PASSWORD (263) 17
58 |     NUMBER (264) 18
59 |     REQUIRED (265) 20
60 |     OPTIONAL (266) 21
61 |     IDENTIFIER <str> (267) 1 6 10 12 13 14 19
62 |     NUMBER_LITERAL (268)
63 | 
64 | 
65 | Nonterminals, with rules where they appear
66 | 
67 |     $accept (18)
68 |         on left: 0
69 |     form <form> (19)
70 |         on left: 1
71 |         on right: 0
72 |     section_list (20)
73 |         on left: 2 3
74 |         on right: 1 3
75 |     section (21)
76 |         on left: 4 5
77 |         on right: 3
78 |     section_header (22)
79 |         on left: 6
80 |         on right: 4 5
81 |     field_list (23)
82 |         on left: 7 8 9
83 |         on right: 4 8 9
84 |     field (24)
85 |         on left: 10 11 12 13 14
86 |         on right: 8
87 |     field_type <field_type> (25)
88 |         on left: 15 16 17 18 19
89 |         on right: 10 11 13 14
90 |     field_attribute <num> (26)
91 |         on left: 20 21 22
92 |         on right: 10 11 12 14
93 | 
94 | 
95 | State 0
96 | 
97 |     0 $accept: • form $end
98 | 
99 |     FORM  shift, and go to state 1
100 | 
101 |     form  go to state 2
102 | 
103 | 
104 | State 1
105 | 
106 |     1 form: FORM • IDENTIFIER '{' section_list '}'
107 | 
108 |     IDENTIFIER  shift, and go to state 3
109 | 
110 | 
111 | State 2
112 | 
113 |     0 $accept: form • $end
114 | 
115 |     $end  shift, and go to state 4
116 | 
117 | 
118 | State 3
119 | 
120 |     1 form: FORM IDENTIFIER • '{' section_list '}'
121 | 
122 |     '{'  shift, and go to state 5
123 | 
124 | 
125 | State 4
126 | 
127 |     0 $accept: form $end •
128 | 
129 |     $default  accept
130 | 
131 | 
132 | State 5
133 | 
134 |     1 form: FORM IDENTIFIER '{' • section_list '}'
135 | 
136 |     $default  reduce using rule 2 (section_list)
137 | 
138 |     section_list  go to state 6
139 | 
140 | 
141 | State 6
142 | 
143 |     1 form: FORM IDENTIFIER '{' section_list • '}'
144 |     3 section_list: section_list • section
145 | 
146 |     SECTION  shift, and go to state 7
147 |     '}'      shift, and go to state 8
148 | 
149 |     section         go to state 9
150 |     section_header  go to state 10
151 | 
152 | 
153 | State 7
154 | 
155 |     6 section_header: SECTION • IDENTIFIER
156 | 
157 |     IDENTIFIER  shift, and go to state 11
158 | 
159 | 
160 | State 8
161 | 
162 |     1 form: FORM IDENTIFIER '{' section_list '}' •
163 | 
164 |     $default  reduce using rule 1 (form)
165 | 
166 | 
167 | State 9
168 | 
169 |     3 section_list: section_list section •
170 | 
171 |     $default  reduce using rule 3 (section_list)
172 | 
173 | 
174 | State 10
175 | 
176 |     4 section: section_header • '{' field_list '}'
177 |     5        | section_header • error '}'
178 | 
179 |     error  shift, and go to state 12
180 |     '{'    shift, and go to state 13
181 | 
182 | 
183 | State 11
184 | 
185 |     6 section_header: SECTION IDENTIFIER •
186 | 
187 |     $default  reduce using rule 6 (section_header)
188 | 
189 | 
190 | State 12
191 | 
192 |     5 section: section_header error • '}'
193 | 
194 |     '}'  shift, and go to state 14
195 | 
196 | 
197 | State 13
198 | 
199 |     4 section: section_header '{' • field_list '}'
200 | 
201 |     $default  reduce using rule 7 (field_list)
202 | 
203 |     field_list  go to state 15
204 | 
205 | 
206 | State 14
207 | 
208 |     5 section: section_header error '}' •
209 | 
210 |     $default  reduce using rule 5 (section)
211 | 
212 | 
213 | State 15
214 | 
215 |     4 section: section_header '{' field_list • '}'
216 |     8 field_list: field_list • field
217 |     9           | field_list • error ';'
218 | 
219 |     error  shift, and go to state 16
220 |     FIELD  shift, and go to state 17
221 |     '}'    shift, and go to state 18
222 | 
223 |     field  go to state 19
224 | 
225 | 
226 | State 16
227 | 
228 |     9 field_list: field_list error • ';'
229 | 
230 |     ';'  shift, and go to state 20
231 | 
232 | 
233 | State 17
234 | 
235 |    10 field: FIELD • IDENTIFIER ':' field_type field_attribute ';'
236 |    11      | FIELD • ':' field_type field_attribute ';'
237 |    12      | FIELD • IDENTIFIER ':' field_attribute ';'
238 |    13      | FIELD • IDENTIFIER ':' field_type error ';'
239 |    14      | FIELD • IDENTIFIER ':' field_type field_attribute error
240 | 
241 |     IDENTIFIER  shift, and go to state 21
242 |     ':'         shift, and go to state 22
243 | 
244 | 
245 | State 18
246 | 
247 |     4 section: section_header '{' field_list '}' •
248 | 
249 |     $default  reduce using rule 4 (section)
250 | 
251 | 
252 | State 19
253 | 
254 |     8 field_list: field_list field •
255 | 
256 |     $default  reduce using rule 8 (field_list)
257 | 
258 | 
259 | State 20
260 | 
261 |     9 field_list: field_list error ';' •
262 | 
263 |     $default  reduce using rule 9 (field_list)
264 | 
265 | 
266 | State 21
267 | 
268 |    10 field: FIELD IDENTIFIER • ':' field_type field_attribute ';'
269 |    12      | FIELD IDENTIFIER • ':' field_attribute ';'
270 |    13      | FIELD IDENTIFIER • ':' field_type error ';'
271 |    14      | FIELD IDENTIFIER • ':' field_type field_attribute error
272 | 
273 |     ':'  shift, and go to state 23
274 | 
275 | 
276 | State 22
277 | 
278 |    11 field: FIELD ':' • field_type field_attribute ';'
279 | 
280 |     TEXT        shift, and go to state 24
281 |     EMAIL       shift, and go to state 25
282 |     PASSWORD    shift, and go to state 26
283 |     NUMBER      shift, and go to state 27
284 |     IDENTIFIER  shift, and go to state 28
285 | 
286 |     field_type  go to state 29
287 | 
288 | 
289 | State 23
290 | 
291 |    10 field: FIELD IDENTIFIER ':' • field_type field_attribute ';'
292 |    12      | FIELD IDENTIFIER ':' • field_attribute ';'
293 |    13      | FIELD IDENTIFIER ':' • field_type error ';'
294 |    14      | FIELD IDENTIFIER ':' • field_type field_attribute error
295 | 
296 |     TEXT        shift, and go to state 24
297 |     EMAIL       shift, and go to state 25
298 |     PASSWORD    shift, and go to state 26
299 |     NUMBER      shift, and go to state 27
300 |     REQUIRED    shift, and go to state 30
301 |     OPTIONAL    shift, and go to state 31
302 |     IDENTIFIER  shift, and go to state 28
303 | 
304 |     $default  reduce using rule 22 (field_attribute)
305 | 
306 |     field_type       go to state 32
307 |     field_attribute  go to state 33
308 | 
309 | 
310 | State 24
311 | 
312 |    15 field_type: TEXT •
313 | 
314 |     $default  reduce using rule 15 (field_type)
315 | 
316 | 
317 | State 25
318 | 
319 |    16 field_type: EMAIL •
320 | 
321 |     $default  reduce using rule 16 (field_type)
322 | 
323 | 
324 | State 26
325 | 
326 |    17 field_type: PASSWORD •
327 | 
328 |     $default  reduce using rule 17 (field_type)
329 | 
330 | 
331 | State 27
332 | 
333 |    18 field_type: NUMBER •
334 | 
335 |     $default  reduce using rule 18 (field_type)
336 | 
337 | 
338 | State 28
339 | 
340 |    19 field_type: IDENTIFIER •
341 | 
342 |     $default  reduce using rule 19 (field_type)
343 | 
344 | 
345 | State 29
346 | 
347 |    11 field: FIELD ':' field_type • field_attribute ';'
348 | 
349 |     REQUIRED  shift, and go to state 30
350 |     OPTIONAL  shift, and go to state 31
351 | 
352 |     $default  reduce using rule 22 (field_attribute)
353 | 
354 |     field_attribute  go to state 34
355 | 
356 | 
357 | State 30
358 | 
359 |    20 field_attribute: REQUIRED •
360 | 
361 |     $default  reduce using rule 20 (field_attribute)
362 | 
363 | 
364 | State 31
365 | 
366 |    21 field_attribute: OPTIONAL •
367 | 
368 |     $default  reduce using rule 21 (field_attribute)
369 | 
370 | 
371 | State 32
372 | 
373 |    10 field: FIELD IDENTIFIER ':' field_type • field_attribute ';'
374 |    13      | FIELD IDENTIFIER ':' field_type • error ';'
375 |    14      | FIELD IDENTIFIER ':' field_type • field_attribute error
376 | 
377 |     error     shift, and go to state 35
378 |     REQUIRED  shift, and go to state 30
379 |     OPTIONAL  shift, and go to state 31
380 | 
381 |     error  [reduce using rule 22 (field_attribute)]
382 |     ';'    reduce using rule 22 (field_attribute)
383 | 
384 |     field_attribute  go to state 36
385 | 
386 | 
387 | State 33
388 | 
389 |    12 field: FIELD IDENTIFIER ':' field_attribute • ';'
390 | 
391 |     ';'  shift, and go to state 37
392 | 
393 | 
394 | State 34
395 | 
396 |    11 field: FIELD ':' field_type field_attribute • ';'
397 | 
398 |     ';'  shift, and go to state 38
399 | 
400 | 
401 | State 35
402 | 
403 |    13 field: FIELD IDENTIFIER ':' field_type error • ';'
404 | 
405 |     ';'  shift, and go to state 39
406 | 
407 | 
408 | State 36
409 | 
410 |    10 field: FIELD IDENTIFIER ':' field_type field_attribute • ';'
411 |    14      | FIELD IDENTIFIER ':' field_type field_attribute • error
412 | 
413 |     error  shift, and go to state 40
414 |     ';'    shift, and go to state 41
415 | 
416 | 
417 | State 37
418 | 
419 |    12 field: FIELD IDENTIFIER ':' field_attribute ';' •
420 | 
421 |     $default  reduce using rule 12 (field)
422 | 
423 | 
424 | State 38
425 | 
426 |    11 field: FIELD ':' field_type field_attribute ';' •
427 | 
428 |     $default  reduce using rule 11 (field)
429 | 
430 | 
431 | State 39
432 | 
433 |    13 field: FIELD IDENTIFIER ':' field_type error ';' •
434 | 
435 |     $default  reduce using rule 13 (field)
436 | 
437 | 
438 | State 40
439 | 
440 |    14 field: FIELD IDENTIFIER ':' field_type field_attribute error •
441 | 
442 |     $default  reduce using rule 14 (field)
443 | 
444 | 
445 | State 41
446 | 
447 |    10 field: FIELD IDENTIFIER ':' field_type field_attribute ';' •
448 | 
449 |     $default  reduce using rule 10 (field)
```

FormLang/parser.tab.c
```
1 | /* A Bison parser, made by GNU Bison 3.8.2.  */
2 | 
3 | /* Bison implementation for Yacc-like parsers in C
4 | 
5 |    Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
6 |    Inc.
7 | 
8 |    This program is free software: you can redistribute it and/or modify
9 |    it under the terms of the GNU General Public License as published by
10 |    the Free Software Foundation, either version 3 of the License, or
11 |    (at your option) any later version.
12 | 
13 |    This program is distributed in the hope that it will be useful,
14 |    but WITHOUT ANY WARRANTY; without even the implied warranty of
15 |    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
16 |    GNU General Public License for more details.
17 | 
18 |    You should have received a copy of the GNU General Public License
19 |    along with this program.  If not, see <https://www.gnu.org/licenses/>.  */
20 | 
21 | /* As a special exception, you may create a larger work that contains
22 |    part or all of the Bison parser skeleton and distribute that work
23 |    under terms of your choice, so long as that work isn't itself a
24 |    parser generator using the skeleton or a modified version thereof
25 |    as a parser skeleton.  Alternatively, if you modify or redistribute
26 |    the parser skeleton itself, you may (at your option) remove this
27 |    special exception, which will cause the skeleton and the resulting
28 |    Bison output files to be licensed under the GNU General Public
29 |    License without this special exception.
30 | 
31 |    This special exception was added by the Free Software Foundation in
32 |    version 2.2 of Bison.  */
33 | 
34 | /* C LALR(1) parser skeleton written by Richard Stallman, by
35 |    simplifying the original so-called "semantic" parser.  */
36 | 
37 | /* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
38 |    especially those whose name start with YY_ or yy_.  They are
39 |    private implementation details that can be changed or removed.  */
40 | 
41 | /* All symbols defined below should begin with yy or YY, to avoid
42 |    infringing on user name space.  This should be done even for local
43 |    variables, as they might otherwise be expanded by user macros.
44 |    There are some unavoidable exceptions within include files to
45 |    define necessary library symbols; they are noted "INFRINGES ON
46 |    USER NAME SPACE" below.  */
47 | 
48 | /* Identify Bison output, and Bison version.  */
49 | #define YYBISON 30802
50 | 
51 | /* Bison version string.  */
52 | #define YYBISON_VERSION "3.8.2"
53 | 
54 | /* Skeleton name.  */
55 | #define YYSKELETON_NAME "yacc.c"
56 | 
57 | /* Pure parsers.  */
58 | #define YYPURE 0
59 | 
60 | /* Push parsers.  */
61 | #define YYPUSH 0
62 | 
63 | /* Pull parsers.  */
64 | #define YYPULL 1
65 | 
66 | 
67 | 
68 | 
69 | /* First part of user prologue.  */
70 | #line 1 "src/parser.y"
71 | 
72 | #include <stdio.h>
73 | #include <stdlib.h>
74 | #include <string.h>
75 | #include "formLang.h"
76 | 
77 | extern int yylex();
78 | extern int yylineno;
79 | void yyerror(const char *s);
80 | 
81 | // Global variables for current form and section
82 | Form *current_form = NULL;
83 | Section *current_section = NULL;
84 | 
85 | // Field name tracking for duplicate detection
86 | typedef struct {
87 |     char* name;
88 |     int line;
89 | } FieldName;
90 | 
91 | FieldName* field_names = NULL;
92 | int field_name_count = 0;
93 | 
94 | // Helper functions
95 | Form* create_form(const char* name) {
96 |     Form* form = malloc(sizeof(Form));
97 |     form->name = strdup(name);
98 |     form->sections = NULL;
99 |     form->section_count = 0;
100 |     return form;
101 | }
102 | 
103 | Section* create_section(const char* name) {
104 |     Section* section = malloc(sizeof(Section));
105 |     section->name = strdup(name);
106 |     section->fields = NULL;
107 |     section->field_count = 0;
108 |     return section;
109 | }
110 | 
111 | void add_section_to_form(Form* form, Section* section) {
112 |     if (!form || !section) return;
113 |     
114 |     form->section_count++;
115 |     form->sections = realloc(form->sections, form->section_count * sizeof(Section*));
116 |     form->sections[form->section_count - 1] = section;
117 | }
118 | 
119 | int check_duplicate_field(const char* name) {
120 |     for (int i = 0; i < field_name_count; i++) {
121 |         if (strcmp(field_names[i].name, name) == 0) {
122 |             return 1;
123 |         }
124 |     }
125 |     return 0;
126 | }
127 | 
128 | void add_field_to_section(Section* section, const char* name, FieldType type, int required) {
129 |     if (!section || !name) return;
130 |     
131 |     // Add field name to tracking
132 |     field_name_count++;
133 |     field_names = realloc(field_names, field_name_count * sizeof(FieldName));
134 |     field_names[field_name_count - 1].name = strdup(name);
135 |     field_names[field_name_count - 1].line = yylineno;
136 |     
137 |     section->field_count++;
138 |     section->fields = realloc(section->fields, section->field_count * sizeof(Field));
139 |     
140 |     Field* field = &section->fields[section->field_count - 1];
141 |     field->name = strdup(name);
142 |     field->type = type;
143 |     field->required = required;
144 | }
145 | 
146 | void cleanup_form(Form* form) {
147 |     if (form) {
148 |         for (int i = 0; i < form->section_count; i++) {
149 |             Section* s = form->sections[i];
150 |             if (s) {
151 |                 for (int j = 0; j < s->field_count; j++) {
152 |                     Field* f = &s->fields[j];
153 |                     if (f->name) free(f->name);
154 |                 }
155 |                 if (s->fields) free(s->fields);
156 |                 if (s->name) free(s->name);
157 |                 free(s);
158 |             }
159 |         }
160 |         if (form->sections) free(form->sections);
161 |         if (form->name) free(form->name);
162 |         free(form);
163 |     }
164 |     
165 |     // Cleanup field name tracking
166 |     for (int i = 0; i < field_name_count; i++) {
167 |         if (field_names[i].name) free(field_names[i].name);
168 |     }
169 |     if (field_names) free(field_names);
170 |     field_name_count = 0;
171 | }
172 | 
173 | #line 174 "parser.tab.c"
174 | 
175 | # ifndef YY_CAST
176 | #  ifdef __cplusplus
177 | #   define YY_CAST(Type, Val) static_cast<Type> (Val)
178 | #   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
179 | #  else
180 | #   define YY_CAST(Type, Val) ((Type) (Val))
181 | #   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
182 | #  endif
183 | # endif
184 | # ifndef YY_NULLPTR
185 | #  if defined __cplusplus
186 | #   if 201103L <= __cplusplus
187 | #    define YY_NULLPTR nullptr
188 | #   else
189 | #    define YY_NULLPTR 0
190 | #   endif
191 | #  else
192 | #   define YY_NULLPTR ((void*)0)
193 | #  endif
194 | # endif
195 | 
196 | 
197 | /* Debug traces.  */
198 | #ifndef YYDEBUG
199 | # define YYDEBUG 0
200 | #endif
201 | #if YYDEBUG
202 | extern int yydebug;
203 | #endif
204 | 
205 | /* Token kinds.  */
206 | #ifndef YYTOKENTYPE
207 | # define YYTOKENTYPE
208 |   enum yytokentype
209 |   {
210 |     YYEMPTY = -2,
211 |     YYEOF = 0,                     /* "end of file"  */
212 |     YYerror = 256,                 /* error  */
213 |     YYUNDEF = 257,                 /* "invalid token"  */
214 |     FORM = 258,                    /* FORM  */
215 |     SECTION = 259,                 /* SECTION  */
216 |     FIELD = 260,                   /* FIELD  */
217 |     TEXT = 261,                    /* TEXT  */
218 |     EMAIL = 262,                   /* EMAIL  */
219 |     PASSWORD = 263,                /* PASSWORD  */
220 |     NUMBER = 264,                  /* NUMBER  */
221 |     REQUIRED = 265,                /* REQUIRED  */
222 |     OPTIONAL = 266,                /* OPTIONAL  */
223 |     IDENTIFIER = 267,              /* IDENTIFIER  */
224 |     NUMBER_LITERAL = 268           /* NUMBER_LITERAL  */
225 |   };
226 |   typedef enum yytokentype yytoken_kind_t;
227 | #endif
228 | 
229 | /* Value type.  */
230 | #if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
231 | union YYSTYPE
232 | {
233 | #line 106 "src/parser.y"
234 | 
235 |     char* str;
236 |     int num;
237 |     Form* form;
238 |     Section* section;
239 |     FieldType field_type;
240 | 
241 | #line 242 "parser.tab.c"
242 | 
243 | };
244 | typedef union YYSTYPE YYSTYPE;
245 | # define YYSTYPE_IS_TRIVIAL 1
246 | # define YYSTYPE_IS_DECLARED 1
247 | #endif
248 | 
249 | 
250 | extern YYSTYPE yylval;
251 | 
252 | 
253 | int yyparse (void);
254 | 
255 | 
256 | 
257 | /* Symbol kind.  */
258 | enum yysymbol_kind_t
259 | {
260 |   YYSYMBOL_YYEMPTY = -2,
261 |   YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
262 |   YYSYMBOL_YYerror = 1,                    /* error  */
263 |   YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
264 |   YYSYMBOL_FORM = 3,                       /* FORM  */
265 |   YYSYMBOL_SECTION = 4,                    /* SECTION  */
266 |   YYSYMBOL_FIELD = 5,                      /* FIELD  */
267 |   YYSYMBOL_TEXT = 6,                       /* TEXT  */
268 |   YYSYMBOL_EMAIL = 7,                      /* EMAIL  */
269 |   YYSYMBOL_PASSWORD = 8,                   /* PASSWORD  */
270 |   YYSYMBOL_NUMBER = 9,                     /* NUMBER  */
271 |   YYSYMBOL_REQUIRED = 10,                  /* REQUIRED  */
272 |   YYSYMBOL_OPTIONAL = 11,                  /* OPTIONAL  */
273 |   YYSYMBOL_IDENTIFIER = 12,                /* IDENTIFIER  */
274 |   YYSYMBOL_NUMBER_LITERAL = 13,            /* NUMBER_LITERAL  */
275 |   YYSYMBOL_14_ = 14,                       /* '{'  */
276 |   YYSYMBOL_15_ = 15,                       /* '}'  */
277 |   YYSYMBOL_16_ = 16,                       /* ';'  */
278 |   YYSYMBOL_17_ = 17,                       /* ':'  */
279 |   YYSYMBOL_YYACCEPT = 18,                  /* $accept  */
280 |   YYSYMBOL_form = 19,                      /* form  */
281 |   YYSYMBOL_section_list = 20,              /* section_list  */
282 |   YYSYMBOL_section = 21,                   /* section  */
283 |   YYSYMBOL_section_header = 22,            /* section_header  */
284 |   YYSYMBOL_field_list = 23,                /* field_list  */
285 |   YYSYMBOL_field = 24,                     /* field  */
286 |   YYSYMBOL_field_type = 25,                /* field_type  */
287 |   YYSYMBOL_field_attribute = 26            /* field_attribute  */
288 | };
289 | typedef enum yysymbol_kind_t yysymbol_kind_t;
290 | 
291 | 
292 | 
293 | 
294 | #ifdef short
295 | # undef short
296 | #endif
297 | 
298 | /* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
299 |    <limits.h> and (if available) <stdint.h> are included
300 |    so that the code can choose integer types of a good width.  */
301 | 
302 | #ifndef __PTRDIFF_MAX__
303 | # include <limits.h> /* INFRINGES ON USER NAME SPACE */
304 | # if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
305 | #  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
306 | #  define YY_STDINT_H
307 | # endif
308 | #endif
309 | 
310 | /* Narrow types that promote to a signed type and that can represent a
311 |    signed or unsigned integer of at least N bits.  In tables they can
312 |    save space and decrease cache pressure.  Promoting to a signed type
313 |    helps avoid bugs in integer arithmetic.  */
314 | 
315 | #ifdef __INT_LEAST8_MAX__
316 | typedef __INT_LEAST8_TYPE__ yytype_int8;
317 | #elif defined YY_STDINT_H
318 | typedef int_least8_t yytype_int8;
319 | #else
320 | typedef signed char yytype_int8;
321 | #endif
322 | 
323 | #ifdef __INT_LEAST16_MAX__
324 | typedef __INT_LEAST16_TYPE__ yytype_int16;
325 | #elif defined YY_STDINT_H
326 | typedef int_least16_t yytype_int16;
327 | #else
328 | typedef short yytype_int16;
329 | #endif
330 | 
331 | /* Work around bug in HP-UX 11.23, which defines these macros
332 |    incorrectly for preprocessor constants.  This workaround can likely
333 |    be removed in 2023, as HPE has promised support for HP-UX 11.23
334 |    (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
335 |    <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
336 | #ifdef __hpux
337 | # undef UINT_LEAST8_MAX
338 | # undef UINT_LEAST16_MAX
339 | # define UINT_LEAST8_MAX 255
340 | # define UINT_LEAST16_MAX 65535
341 | #endif
342 | 
343 | #if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
344 | typedef __UINT_LEAST8_TYPE__ yytype_uint8;
345 | #elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
346 |        && UINT_LEAST8_MAX <= INT_MAX)
347 | typedef uint_least8_t yytype_uint8;
348 | #elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
349 | typedef unsigned char yytype_uint8;
350 | #else
351 | typedef short yytype_uint8;
352 | #endif
353 | 
354 | #if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
355 | typedef __UINT_LEAST16_TYPE__ yytype_uint16;
356 | #elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
357 |        && UINT_LEAST16_MAX <= INT_MAX)
358 | typedef uint_least16_t yytype_uint16;
359 | #elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
360 | typedef unsigned short yytype_uint16;
361 | #else
362 | typedef int yytype_uint16;
363 | #endif
364 | 
365 | #ifndef YYPTRDIFF_T
366 | # if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
367 | #  define YYPTRDIFF_T __PTRDIFF_TYPE__
368 | #  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
369 | # elif defined PTRDIFF_MAX
370 | #  ifndef ptrdiff_t
371 | #   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
372 | #  endif
373 | #  define YYPTRDIFF_T ptrdiff_t
374 | #  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
375 | # else
376 | #  define YYPTRDIFF_T long
377 | #  define YYPTRDIFF_MAXIMUM LONG_MAX
378 | # endif
379 | #endif
380 | 
381 | #ifndef YYSIZE_T
382 | # ifdef __SIZE_TYPE__
383 | #  define YYSIZE_T __SIZE_TYPE__
384 | # elif defined size_t
385 | #  define YYSIZE_T size_t
386 | # elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
387 | #  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
388 | #  define YYSIZE_T size_t
389 | # else
390 | #  define YYSIZE_T unsigned
391 | # endif
392 | #endif
393 | 
394 | #define YYSIZE_MAXIMUM                                  \
395 |   YY_CAST (YYPTRDIFF_T,                                 \
396 |            (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
397 |             ? YYPTRDIFF_MAXIMUM                         \
398 |             : YY_CAST (YYSIZE_T, -1)))
399 | 
400 | #define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))
401 | 
402 | 
403 | /* Stored state numbers (used for stacks). */
404 | typedef yytype_int8 yy_state_t;
405 | 
406 | /* State numbers in computations.  */
407 | typedef int yy_state_fast_t;
408 | 
409 | #ifndef YY_
410 | # if defined YYENABLE_NLS && YYENABLE_NLS
411 | #  if ENABLE_NLS
412 | #   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
413 | #   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
414 | #  endif
415 | # endif
416 | # ifndef YY_
417 | #  define YY_(Msgid) Msgid
418 | # endif
419 | #endif
420 | 
421 | 
422 | #ifndef YY_ATTRIBUTE_PURE
423 | # if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
424 | #  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
425 | # else
426 | #  define YY_ATTRIBUTE_PURE
427 | # endif
428 | #endif
429 | 
430 | #ifndef YY_ATTRIBUTE_UNUSED
431 | # if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
432 | #  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
433 | # else
434 | #  define YY_ATTRIBUTE_UNUSED
435 | # endif
436 | #endif
437 | 
438 | /* Suppress unused-variable warnings by "using" E.  */
439 | #if ! defined lint || defined __GNUC__
440 | # define YY_USE(E) ((void) (E))
441 | #else
442 | # define YY_USE(E) /* empty */
443 | #endif
444 | 
445 | /* Suppress an incorrect diagnostic about yylval being uninitialized.  */
446 | #if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
447 | # if __GNUC__ * 100 + __GNUC_MINOR__ < 407
448 | #  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
449 |     _Pragma ("GCC diagnostic push")                                     \
450 |     _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
451 | # else
452 | #  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
453 |     _Pragma ("GCC diagnostic push")                                     \
454 |     _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
455 |     _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
456 | # endif
457 | # define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
458 |     _Pragma ("GCC diagnostic pop")
459 | #else
460 | # define YY_INITIAL_VALUE(Value) Value
461 | #endif
462 | #ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
463 | # define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
464 | # define YY_IGNORE_MAYBE_UNINITIALIZED_END
465 | #endif
466 | #ifndef YY_INITIAL_VALUE
467 | # define YY_INITIAL_VALUE(Value) /* Nothing. */
468 | #endif
469 | 
470 | #if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
471 | # define YY_IGNORE_USELESS_CAST_BEGIN                          \
472 |     _Pragma ("GCC diagnostic push")                            \
473 |     _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
474 | # define YY_IGNORE_USELESS_CAST_END            \
475 |     _Pragma ("GCC diagnostic pop")
476 | #endif
477 | #ifndef YY_IGNORE_USELESS_CAST_BEGIN
478 | # define YY_IGNORE_USELESS_CAST_BEGIN
479 | # define YY_IGNORE_USELESS_CAST_END
480 | #endif
481 | 
482 | 
483 | #define YY_ASSERT(E) ((void) (0 && (E)))
484 | 
485 | #if 1
486 | 
487 | /* The parser invokes alloca or malloc; define the necessary symbols.  */
488 | 
489 | # ifdef YYSTACK_USE_ALLOCA
490 | #  if YYSTACK_USE_ALLOCA
491 | #   ifdef __GNUC__
492 | #    define YYSTACK_ALLOC __builtin_alloca
493 | #   elif defined __BUILTIN_VA_ARG_INCR
494 | #    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
495 | #   elif defined _AIX
496 | #    define YYSTACK_ALLOC __alloca
497 | #   elif defined _MSC_VER
498 | #    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
499 | #    define alloca _alloca
500 | #   else
501 | #    define YYSTACK_ALLOC alloca
502 | #    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
503 | #     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
504 |       /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
505 | #     ifndef EXIT_SUCCESS
506 | #      define EXIT_SUCCESS 0
507 | #     endif
508 | #    endif
509 | #   endif
510 | #  endif
511 | # endif
512 | 
513 | # ifdef YYSTACK_ALLOC
514 |    /* Pacify GCC's 'empty if-body' warning.  */
515 | #  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
516 | #  ifndef YYSTACK_ALLOC_MAXIMUM
517 |     /* The OS might guarantee only one guard page at the bottom of the stack,
518 |        and a page size can be as small as 4096 bytes.  So we cannot safely
519 |        invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
520 |        to allow for a few compiler-allocated temporary stack slots.  */
521 | #   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
522 | #  endif
523 | # else
524 | #  define YYSTACK_ALLOC YYMALLOC
525 | #  define YYSTACK_FREE YYFREE
526 | #  ifndef YYSTACK_ALLOC_MAXIMUM
527 | #   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
528 | #  endif
529 | #  if (defined __cplusplus && ! defined EXIT_SUCCESS \
530 |        && ! ((defined YYMALLOC || defined malloc) \
531 |              && (defined YYFREE || defined free)))
532 | #   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
533 | #   ifndef EXIT_SUCCESS
534 | #    define EXIT_SUCCESS 0
535 | #   endif
536 | #  endif
537 | #  ifndef YYMALLOC
538 | #   define YYMALLOC malloc
539 | #   if ! defined malloc && ! defined EXIT_SUCCESS
540 | void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
541 | #   endif
542 | #  endif
543 | #  ifndef YYFREE
544 | #   define YYFREE free
545 | #   if ! defined free && ! defined EXIT_SUCCESS
546 | void free (void *); /* INFRINGES ON USER NAME SPACE */
547 | #   endif
548 | #  endif
549 | # endif
550 | #endif /* 1 */
551 | 
552 | #if (! defined yyoverflow \
553 |      && (! defined __cplusplus \
554 |          || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))
555 | 
556 | /* A type that is properly aligned for any stack member.  */
557 | union yyalloc
558 | {
559 |   yy_state_t yyss_alloc;
560 |   YYSTYPE yyvs_alloc;
561 | };
562 | 
563 | /* The size of the maximum gap between one aligned stack and the next.  */
564 | # define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)
565 | 
566 | /* The size of an array large to enough to hold all stacks, each with
567 |    N elements.  */
568 | # define YYSTACK_BYTES(N) \
569 |      ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
570 |       + YYSTACK_GAP_MAXIMUM)
571 | 
572 | # define YYCOPY_NEEDED 1
573 | 
574 | /* Relocate STACK from its old location to the new one.  The
575 |    local variables YYSIZE and YYSTACKSIZE give the old and new number of
576 |    elements in the stack, and YYPTR gives the new location of the
577 |    stack.  Advance YYPTR to a properly aligned location for the next
578 |    stack.  */
579 | # define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
580 |     do                                                                  \
581 |       {                                                                 \
582 |         YYPTRDIFF_T yynewbytes;                                         \
583 |         YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
584 |         Stack = &yyptr->Stack_alloc;                                    \
585 |         yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
586 |         yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
587 |       }                                                                 \
588 |     while (0)
589 | 
590 | #endif
591 | 
592 | #if defined YYCOPY_NEEDED && YYCOPY_NEEDED
593 | /* Copy COUNT objects from SRC to DST.  The source and destination do
594 |    not overlap.  */
595 | # ifndef YYCOPY
596 | #  if defined __GNUC__ && 1 < __GNUC__
597 | #   define YYCOPY(Dst, Src, Count) \
598 |       __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
599 | #  else
600 | #   define YYCOPY(Dst, Src, Count)              \
601 |       do                                        \
602 |         {                                       \
603 |           YYPTRDIFF_T yyi;                      \
604 |           for (yyi = 0; yyi < (Count); yyi++)   \
605 |             (Dst)[yyi] = (Src)[yyi];            \
606 |         }                                       \
607 |       while (0)
608 | #  endif
609 | # endif
610 | #endif /* !YYCOPY_NEEDED */
611 | 
612 | /* YYFINAL -- State number of the termination state.  */
613 | #define YYFINAL  4
614 | /* YYLAST -- Last index in YYTABLE.  */
615 | #define YYLAST   43
616 | 
617 | /* YYNTOKENS -- Number of terminals.  */
618 | #define YYNTOKENS  18
619 | /* YYNNTS -- Number of nonterminals.  */
620 | #define YYNNTS  9
621 | /* YYNRULES -- Number of rules.  */
622 | #define YYNRULES  23
623 | /* YYNSTATES -- Number of states.  */
624 | #define YYNSTATES  42
625 | 
626 | /* YYMAXUTOK -- Last valid token kind.  */
627 | #define YYMAXUTOK   268
628 | 
629 | 
630 | /* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
631 |    as returned by yylex, with out-of-bounds checking.  */
632 | #define YYTRANSLATE(YYX)                                \
633 |   (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
634 |    ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
635 |    : YYSYMBOL_YYUNDEF)
636 | 
637 | /* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
638 |    as returned by yylex.  */
639 | static const yytype_int8 yytranslate[] =
640 | {
641 |        0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
642 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
643 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
644 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
645 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
646 |        2,     2,     2,     2,     2,     2,     2,     2,    17,    16,
647 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
648 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
649 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
650 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
651 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
652 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
653 |        2,     2,     2,    14,     2,    15,     2,     2,     2,     2,
654 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
655 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
656 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
657 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
658 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
659 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
660 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
661 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
662 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
663 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
664 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
665 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
666 |        2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
667 |        5,     6,     7,     8,     9,    10,    11,    12,    13
668 | };
669 | 
670 | #if YYDEBUG
671 | /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
672 | static const yytype_uint8 yyrline[] =
673 | {
674 |        0,   123,   123,   134,   135,   138,   142,   151,   166,   167,
675 |      168,   176,   188,   193,   198,   203,   211,   212,   213,   214,
676 |      215,   222,   223,   224
677 | };
678 | #endif
679 | 
680 | /** Accessing symbol of state STATE.  */
681 | #define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])
682 | 
683 | #if 1
684 | /* The user-facing name of the symbol whose (internal) number is
685 |    YYSYMBOL.  No bounds checking.  */
686 | static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;
687 | 
688 | /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
689 |    First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
690 | static const char *const yytname[] =
691 | {
692 |   "\"end of file\"", "error", "\"invalid token\"", "FORM", "SECTION",
693 |   "FIELD", "TEXT", "EMAIL", "PASSWORD", "NUMBER", "REQUIRED", "OPTIONAL",
694 |   "IDENTIFIER", "NUMBER_LITERAL", "'{'", "'}'", "';'", "':'", "$accept",
695 |   "form", "section_list", "section", "section_header", "field_list",
696 |   "field", "field_type", "field_attribute", YY_NULLPTR
697 | };
698 | 
699 | static const char *
700 | yysymbol_name (yysymbol_kind_t yysymbol)
701 | {
702 |   return yytname[yysymbol];
703 | }
704 | #endif
705 | 
706 | #define YYPACT_NINF (-9)
707 | 
708 | #define yypact_value_is_default(Yyn) \
709 |   ((Yyn) == YYPACT_NINF)
710 | 
711 | #define YYTABLE_NINF (-24)
712 | 
713 | #define yytable_value_is_error(Yyn) \
714 |   0
715 | 
716 | /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
717 |    STATE-NUM.  */
718 | static const yytype_int8 yypact[] =
719 | {
720 |        5,    -8,    12,    17,    -9,    -9,    -2,    25,    -9,    -9,
721 |        4,    -9,    21,    -9,    -9,     2,    22,    -6,    -9,    -9,
722 |       -9,    -3,    20,    13,    -9,    -9,    -9,    -9,    -9,    24,
723 |       -9,    -9,    -1,    23,    26,    27,     0,    -9,    -9,    -9,
724 |       -9,    -9
725 | };
726 | 
727 | /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
728 |    Performed when YYTABLE does not specify something else to do.  Zero
729 |    means the default is an error.  */
730 | static const yytype_int8 yydefact[] =
731 | {
732 |        0,     0,     0,     0,     1,     3,     0,     0,     2,     4,
733 |        0,     7,     0,     8,     6,     0,     0,     0,     5,     9,
734 |       10,     0,     0,    23,    16,    17,    18,    19,    20,    23,
735 |       21,    22,     0,     0,     0,     0,     0,    13,    12,    14,
736 |       15,    11
737 | };
738 | 
739 | /* YYPGOTO[NTERM-NUM].  */
740 | static const yytype_int8 yypgoto[] =
741 | {
742 |       -9,    -9,    -9,    -9,    -9,    -9,    -9,    18,     1
743 | };
744 | 
745 | /* YYDEFGOTO[NTERM-NUM].  */
746 | static const yytype_int8 yydefgoto[] =
747 | {
748 |        0,     2,     6,     9,    10,    15,    19,    29,    33
749 | };
750 | 
751 | /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
752 |    positive, shift that token.  If negative, reduce the rule whose
753 |    number is the opposite.  If YYTABLE_NINF, syntax error.  */
754 | static const yytype_int8 yytable[] =
755 | {
756 |       35,    40,     7,    16,     3,    12,    21,    17,     1,    30,
757 |       31,    22,     4,     8,    23,   -23,    41,    18,    13,    24,
758 |       25,    26,    27,    30,    31,    28,    24,    25,    26,    27,
759 |       34,     5,    28,    36,    30,    31,    14,    11,    20,    37,
760 |        0,    32,    38,    39
761 | };
762 | 
763 | static const yytype_int8 yycheck[] =
764 | {
765 |        1,     1,     4,     1,    12,     1,    12,     5,     3,    10,
766 |       11,    17,     0,    15,    17,    16,    16,    15,    14,     6,
767 |        7,     8,     9,    10,    11,    12,     6,     7,     8,     9,
768 |       29,    14,    12,    32,    10,    11,    15,    12,    16,    16,
769 |       -1,    23,    16,    16
770 | };
771 | 
772 | /* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
773 |    state STATE-NUM.  */
774 | static const yytype_int8 yystos[] =
775 | {
776 |        0,     3,    19,    12,     0,    14,    20,     4,    15,    21,
777 |       22,    12,     1,    14,    15,    23,     1,     5,    15,    24,
778 |       16,    12,    17,    17,     6,     7,     8,     9,    12,    25,
779 |       10,    11,    25,    26,    26,     1,    26,    16,    16,    16,
780 |        1,    16
781 | };
782 | 
783 | /* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
784 | static const yytype_int8 yyr1[] =
785 | {
786 |        0,    18,    19,    20,    20,    21,    21,    22,    23,    23,
787 |       23,    24,    24,    24,    24,    24,    25,    25,    25,    25,
788 |       25,    26,    26,    26
789 | };
790 | 
791 | /* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
792 | static const yytype_int8 yyr2[] =
793 | {
794 |        0,     2,     5,     0,     2,     4,     3,     2,     0,     2,
795 |        3,     6,     5,     5,     6,     6,     1,     1,     1,     1,
796 |        1,     1,     1,     0
797 | };
798 | 
799 | 
800 | enum { YYENOMEM = -2 };
801 | 
802 | #define yyerrok         (yyerrstatus = 0)
803 | #define yyclearin       (yychar = YYEMPTY)
804 | 
805 | #define YYACCEPT        goto yyacceptlab
806 | #define YYABORT         goto yyabortlab
807 | #define YYERROR         goto yyerrorlab
808 | #define YYNOMEM         goto yyexhaustedlab
809 | 
810 | 
811 | #define YYRECOVERING()  (!!yyerrstatus)
812 | 
813 | #define YYBACKUP(Token, Value)                                    \
814 |   do                                                              \
815 |     if (yychar == YYEMPTY)                                        \
816 |       {                                                           \
817 |         yychar = (Token);                                         \
818 |         yylval = (Value);                                         \
819 |         YYPOPSTACK (yylen);                                       \
820 |         yystate = *yyssp;                                         \
821 |         goto yybackup;                                            \
822 |       }                                                           \
823 |     else                                                          \
824 |       {                                                           \
825 |         yyerror (YY_("syntax error: cannot back up")); \
826 |         YYERROR;                                                  \
827 |       }                                                           \
828 |   while (0)
829 | 
830 | /* Backward compatibility with an undocumented macro.
831 |    Use YYerror or YYUNDEF. */
832 | #define YYERRCODE YYUNDEF
833 | 
834 | 
835 | /* Enable debugging if requested.  */
836 | #if YYDEBUG
837 | 
838 | # ifndef YYFPRINTF
839 | #  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
840 | #  define YYFPRINTF fprintf
841 | # endif
842 | 
843 | # define YYDPRINTF(Args)                        \
844 | do {                                            \
845 |   if (yydebug)                                  \
846 |     YYFPRINTF Args;                             \
847 | } while (0)
848 | 
849 | 
850 | 
851 | 
852 | # define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
853 | do {                                                                      \
854 |   if (yydebug)                                                            \
855 |     {                                                                     \
856 |       YYFPRINTF (stderr, "%s ", Title);                                   \
857 |       yy_symbol_print (stderr,                                            \
858 |                   Kind, Value); \
859 |       YYFPRINTF (stderr, "\n");                                           \
860 |     }                                                                     \
861 | } while (0)
862 | 
863 | 
864 | /*-----------------------------------.
865 | | Print this symbol's value on YYO.  |
866 | `-----------------------------------*/
867 | 
868 | static void
869 | yy_symbol_value_print (FILE *yyo,
870 |                        yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
871 | {
872 |   FILE *yyoutput = yyo;
873 |   YY_USE (yyoutput);
874 |   if (!yyvaluep)
875 |     return;
876 |   YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
877 |   YY_USE (yykind);
878 |   YY_IGNORE_MAYBE_UNINITIALIZED_END
879 | }
880 | 
881 | 
882 | /*---------------------------.
883 | | Print this symbol on YYO.  |
884 | `---------------------------*/
885 | 
886 | static void
887 | yy_symbol_print (FILE *yyo,
888 |                  yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
889 | {
890 |   YYFPRINTF (yyo, "%s %s (",
891 |              yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));
892 | 
893 |   yy_symbol_value_print (yyo, yykind, yyvaluep);
894 |   YYFPRINTF (yyo, ")");
895 | }
896 | 
897 | /*------------------------------------------------------------------.
898 | | yy_stack_print -- Print the state stack from its BOTTOM up to its |
899 | | TOP (included).                                                   |
900 | `------------------------------------------------------------------*/
901 | 
902 | static void
903 | yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
904 | {
905 |   YYFPRINTF (stderr, "Stack now");
906 |   for (; yybottom <= yytop; yybottom++)
907 |     {
908 |       int yybot = *yybottom;
909 |       YYFPRINTF (stderr, " %d", yybot);
910 |     }
911 |   YYFPRINTF (stderr, "\n");
912 | }
913 | 
914 | # define YY_STACK_PRINT(Bottom, Top)                            \
915 | do {                                                            \
916 |   if (yydebug)                                                  \
917 |     yy_stack_print ((Bottom), (Top));                           \
918 | } while (0)
919 | 
920 | 
921 | /*------------------------------------------------.
922 | | Report that the YYRULE is going to be reduced.  |
923 | `------------------------------------------------*/
924 | 
925 | static void
926 | yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
927 |                  int yyrule)
928 | {
929 |   int yylno = yyrline[yyrule];
930 |   int yynrhs = yyr2[yyrule];
931 |   int yyi;
932 |   YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
933 |              yyrule - 1, yylno);
934 |   /* The symbols being reduced.  */
935 |   for (yyi = 0; yyi < yynrhs; yyi++)
936 |     {
937 |       YYFPRINTF (stderr, "   $%d = ", yyi + 1);
938 |       yy_symbol_print (stderr,
939 |                        YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
940 |                        &yyvsp[(yyi + 1) - (yynrhs)]);
941 |       YYFPRINTF (stderr, "\n");
942 |     }
943 | }
944 | 
945 | # define YY_REDUCE_PRINT(Rule)          \
946 | do {                                    \
947 |   if (yydebug)                          \
948 |     yy_reduce_print (yyssp, yyvsp, Rule); \
949 | } while (0)
950 | 
951 | /* Nonzero means print parse trace.  It is left uninitialized so that
952 |    multiple parsers can coexist.  */
953 | int yydebug;
954 | #else /* !YYDEBUG */
955 | # define YYDPRINTF(Args) ((void) 0)
956 | # define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
957 | # define YY_STACK_PRINT(Bottom, Top)
958 | # define YY_REDUCE_PRINT(Rule)
959 | #endif /* !YYDEBUG */
960 | 
961 | 
962 | /* YYINITDEPTH -- initial size of the parser's stacks.  */
963 | #ifndef YYINITDEPTH
964 | # define YYINITDEPTH 200
965 | #endif
966 | 
967 | /* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
968 |    if the built-in stack extension method is used).
969 | 
970 |    Do not make this value too large; the results are undefined if
971 |    YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
972 |    evaluated with infinite-precision integer arithmetic.  */
973 | 
974 | #ifndef YYMAXDEPTH
975 | # define YYMAXDEPTH 10000
976 | #endif
977 | 
978 | 
979 | /* Context of a parse error.  */
980 | typedef struct
981 | {
982 |   yy_state_t *yyssp;
983 |   yysymbol_kind_t yytoken;
984 | } yypcontext_t;
985 | 
986 | /* Put in YYARG at most YYARGN of the expected tokens given the
987 |    current YYCTX, and return the number of tokens stored in YYARG.  If
988 |    YYARG is null, return the number of expected tokens (guaranteed to
989 |    be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
990 |    Return 0 if there are more than YYARGN expected tokens, yet fill
991 |    YYARG up to YYARGN. */
992 | static int
993 | yypcontext_expected_tokens (const yypcontext_t *yyctx,
994 |                             yysymbol_kind_t yyarg[], int yyargn)
995 | {
996 |   /* Actual size of YYARG. */
997 |   int yycount = 0;
998 |   int yyn = yypact[+*yyctx->yyssp];
999 |   if (!yypact_value_is_default (yyn))
1000 |     {
1001 |       /* Start YYX at -YYN if negative to avoid negative indexes in
1002 |          YYCHECK.  In other words, skip the first -YYN actions for
1003 |          this state because they are default actions.  */
1004 |       int yyxbegin = yyn < 0 ? -yyn : 0;
1005 |       /* Stay within bounds of both yycheck and yytname.  */
1006 |       int yychecklim = YYLAST - yyn + 1;
1007 |       int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
1008 |       int yyx;
1009 |       for (yyx = yyxbegin; yyx < yyxend; ++yyx)
1010 |         if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
1011 |             && !yytable_value_is_error (yytable[yyx + yyn]))
1012 |           {
1013 |             if (!yyarg)
1014 |               ++yycount;
1015 |             else if (yycount == yyargn)
1016 |               return 0;
1017 |             else
1018 |               yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
1019 |           }
1020 |     }
1021 |   if (yyarg && yycount == 0 && 0 < yyargn)
1022 |     yyarg[0] = YYSYMBOL_YYEMPTY;
1023 |   return yycount;
1024 | }
1025 | 
1026 | 
1027 | 
1028 | 
1029 | #ifndef yystrlen
1030 | # if defined __GLIBC__ && defined _STRING_H
1031 | #  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
1032 | # else
1033 | /* Return the length of YYSTR.  */
1034 | static YYPTRDIFF_T
1035 | yystrlen (const char *yystr)
1036 | {
1037 |   YYPTRDIFF_T yylen;
1038 |   for (yylen = 0; yystr[yylen]; yylen++)
1039 |     continue;
1040 |   return yylen;
1041 | }
1042 | # endif
1043 | #endif
1044 | 
1045 | #ifndef yystpcpy
1046 | # if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
1047 | #  define yystpcpy stpcpy
1048 | # else
1049 | /* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
1050 |    YYDEST.  */
1051 | static char *
1052 | yystpcpy (char *yydest, const char *yysrc)
1053 | {
1054 |   char *yyd = yydest;
1055 |   const char *yys = yysrc;
1056 | 
1057 |   while ((*yyd++ = *yys++) != '\0')
1058 |     continue;
1059 | 
1060 |   return yyd - 1;
1061 | }
1062 | # endif
1063 | #endif
1064 | 
1065 | #ifndef yytnamerr
1066 | /* Copy to YYRES the contents of YYSTR after stripping away unnecessary
1067 |    quotes and backslashes, so that it's suitable for yyerror.  The
1068 |    heuristic is that double-quoting is unnecessary unless the string
1069 |    contains an apostrophe, a comma, or backslash (other than
1070 |    backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
1071 |    null, do not copy; instead, return the length of what the result
1072 |    would have been.  */
1073 | static YYPTRDIFF_T
1074 | yytnamerr (char *yyres, const char *yystr)
1075 | {
1076 |   if (*yystr == '"')
1077 |     {
1078 |       YYPTRDIFF_T yyn = 0;
1079 |       char const *yyp = yystr;
1080 |       for (;;)
1081 |         switch (*++yyp)
1082 |           {
1083 |           case '\'':
1084 |           case ',':
1085 |             goto do_not_strip_quotes;
1086 | 
1087 |           case '\\':
1088 |             if (*++yyp != '\\')
1089 |               goto do_not_strip_quotes;
1090 |             else
1091 |               goto append;
1092 | 
1093 |           append:
1094 |           default:
1095 |             if (yyres)
1096 |               yyres[yyn] = *yyp;
1097 |             yyn++;
1098 |             break;
1099 | 
1100 |           case '"':
1101 |             if (yyres)
1102 |               yyres[yyn] = '\0';
1103 |             return yyn;
1104 |           }
1105 |     do_not_strip_quotes: ;
1106 |     }
1107 | 
1108 |   if (yyres)
1109 |     return yystpcpy (yyres, yystr) - yyres;
1110 |   else
1111 |     return yystrlen (yystr);
1112 | }
1113 | #endif
1114 | 
1115 | 
1116 | static int
1117 | yy_syntax_error_arguments (const yypcontext_t *yyctx,
1118 |                            yysymbol_kind_t yyarg[], int yyargn)
1119 | {
1120 |   /* Actual size of YYARG. */
1121 |   int yycount = 0;
1122 |   /* There are many possibilities here to consider:
1123 |      - If this state is a consistent state with a default action, then
1124 |        the only way this function was invoked is if the default action
1125 |        is an error action.  In that case, don't check for expected
1126 |        tokens because there are none.
1127 |      - The only way there can be no lookahead present (in yychar) is if
1128 |        this state is a consistent state with a default action.  Thus,
1129 |        detecting the absence of a lookahead is sufficient to determine
1130 |        that there is no unexpected or expected token to report.  In that
1131 |        case, just report a simple "syntax error".
1132 |      - Don't assume there isn't a lookahead just because this state is a
1133 |        consistent state with a default action.  There might have been a
1134 |        previous inconsistent state, consistent state with a non-default
1135 |        action, or user semantic action that manipulated yychar.
1136 |      - Of course, the expected token list depends on states to have
1137 |        correct lookahead information, and it depends on the parser not
1138 |        to perform extra reductions after fetching a lookahead from the
1139 |        scanner and before detecting a syntax error.  Thus, state merging
1140 |        (from LALR or IELR) and default reductions corrupt the expected
1141 |        token list.  However, the list is correct for canonical LR with
1142 |        one exception: it will still contain any token that will not be
1143 |        accepted due to an error action in a later state.
1144 |   */
1145 |   if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
1146 |     {
1147 |       int yyn;
1148 |       if (yyarg)
1149 |         yyarg[yycount] = yyctx->yytoken;
1150 |       ++yycount;
1151 |       yyn = yypcontext_expected_tokens (yyctx,
1152 |                                         yyarg ? yyarg + 1 : yyarg, yyargn - 1);
1153 |       if (yyn == YYENOMEM)
1154 |         return YYENOMEM;
1155 |       else
1156 |         yycount += yyn;
1157 |     }
1158 |   return yycount;
1159 | }
1160 | 
1161 | /* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
1162 |    about the unexpected token YYTOKEN for the state stack whose top is
1163 |    YYSSP.
1164 | 
1165 |    Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
1166 |    not large enough to hold the message.  In that case, also set
1167 |    *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
1168 |    required number of bytes is too large to store.  */
1169 | static int
1170 | yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
1171 |                 const yypcontext_t *yyctx)
1172 | {
1173 |   enum { YYARGS_MAX = 5 };
1174 |   /* Internationalized format string. */
1175 |   const char *yyformat = YY_NULLPTR;
1176 |   /* Arguments of yyformat: reported tokens (one for the "unexpected",
1177 |      one per "expected"). */
1178 |   yysymbol_kind_t yyarg[YYARGS_MAX];
1179 |   /* Cumulated lengths of YYARG.  */
1180 |   YYPTRDIFF_T yysize = 0;
1181 | 
1182 |   /* Actual size of YYARG. */
1183 |   int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
1184 |   if (yycount == YYENOMEM)
1185 |     return YYENOMEM;
1186 | 
1187 |   switch (yycount)
1188 |     {
1189 | #define YYCASE_(N, S)                       \
1190 |       case N:                               \
1191 |         yyformat = S;                       \
1192 |         break
1193 |     default: /* Avoid compiler warnings. */
1194 |       YYCASE_(0, YY_("syntax error"));
1195 |       YYCASE_(1, YY_("syntax error, unexpected %s"));
1196 |       YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
1197 |       YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
1198 |       YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
1199 |       YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
1200 | #undef YYCASE_
1201 |     }
1202 | 
1203 |   /* Compute error message size.  Don't count the "%s"s, but reserve
1204 |      room for the terminator.  */
1205 |   yysize = yystrlen (yyformat) - 2 * yycount + 1;
1206 |   {
1207 |     int yyi;
1208 |     for (yyi = 0; yyi < yycount; ++yyi)
1209 |       {
1210 |         YYPTRDIFF_T yysize1
1211 |           = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
1212 |         if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
1213 |           yysize = yysize1;
1214 |         else
1215 |           return YYENOMEM;
1216 |       }
1217 |   }
1218 | 
1219 |   if (*yymsg_alloc < yysize)
1220 |     {
1221 |       *yymsg_alloc = 2 * yysize;
1222 |       if (! (yysize <= *yymsg_alloc
1223 |              && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
1224 |         *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
1225 |       return -1;
1226 |     }
1227 | 
1228 |   /* Avoid sprintf, as that infringes on the user's name space.
1229 |      Don't have undefined behavior even if the translation
1230 |      produced a string with the wrong number of "%s"s.  */
1231 |   {
1232 |     char *yyp = *yymsg;
1233 |     int yyi = 0;
1234 |     while ((*yyp = *yyformat) != '\0')
1235 |       if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
1236 |         {
1237 |           yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
1238 |           yyformat += 2;
1239 |         }
1240 |       else
1241 |         {
1242 |           ++yyp;
1243 |           ++yyformat;
1244 |         }
1245 |   }
1246 |   return 0;
1247 | }
1248 | 
1249 | 
1250 | /*-----------------------------------------------.
1251 | | Release the memory associated to this symbol.  |
1252 | `-----------------------------------------------*/
1253 | 
1254 | static void
1255 | yydestruct (const char *yymsg,
1256 |             yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
1257 | {
1258 |   YY_USE (yyvaluep);
1259 |   if (!yymsg)
1260 |     yymsg = "Deleting";
1261 |   YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);
1262 | 
1263 |   YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
1264 |   YY_USE (yykind);
1265 |   YY_IGNORE_MAYBE_UNINITIALIZED_END
1266 | }
1267 | 
1268 | 
1269 | /* Lookahead token kind.  */
1270 | int yychar;
1271 | 
1272 | /* The semantic value of the lookahead symbol.  */
1273 | YYSTYPE yylval;
1274 | /* Number of syntax errors so far.  */
1275 | int yynerrs;
1276 | 
1277 | 
1278 | 
1279 | 
1280 | /*----------.
1281 | | yyparse.  |
1282 | `----------*/
1283 | 
1284 | int
1285 | yyparse (void)
1286 | {
1287 |     yy_state_fast_t yystate = 0;
1288 |     /* Number of tokens to shift before error messages enabled.  */
1289 |     int yyerrstatus = 0;
1290 | 
1291 |     /* Refer to the stacks through separate pointers, to allow yyoverflow
1292 |        to reallocate them elsewhere.  */
1293 | 
1294 |     /* Their size.  */
1295 |     YYPTRDIFF_T yystacksize = YYINITDEPTH;
1296 | 
1297 |     /* The state stack: array, bottom, top.  */
1298 |     yy_state_t yyssa[YYINITDEPTH];
1299 |     yy_state_t *yyss = yyssa;
1300 |     yy_state_t *yyssp = yyss;
1301 | 
1302 |     /* The semantic value stack: array, bottom, top.  */
1303 |     YYSTYPE yyvsa[YYINITDEPTH];
1304 |     YYSTYPE *yyvs = yyvsa;
1305 |     YYSTYPE *yyvsp = yyvs;
1306 | 
1307 |   int yyn;
1308 |   /* The return value of yyparse.  */
1309 |   int yyresult;
1310 |   /* Lookahead symbol kind.  */
1311 |   yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
1312 |   /* The variables used to return semantic value and location from the
1313 |      action routines.  */
1314 |   YYSTYPE yyval;
1315 | 
1316 |   /* Buffer for error messages, and its allocated size.  */
1317 |   char yymsgbuf[128];
1318 |   char *yymsg = yymsgbuf;
1319 |   YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
1320 | 
1321 | #define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))
1322 | 
1323 |   /* The number of symbols on the RHS of the reduced rule.
1324 |      Keep to zero when no symbol should be popped.  */
1325 |   int yylen = 0;
1326 | 
1327 |   YYDPRINTF ((stderr, "Starting parse\n"));
1328 | 
1329 |   yychar = YYEMPTY; /* Cause a token to be read.  */
1330 | 
1331 |   goto yysetstate;
1332 | 
1333 | 
1334 | /*------------------------------------------------------------.
1335 | | yynewstate -- push a new state, which is found in yystate.  |
1336 | `------------------------------------------------------------*/
1337 | yynewstate:
1338 |   /* In all cases, when you get here, the value and location stacks
1339 |      have just been pushed.  So pushing a state here evens the stacks.  */
1340 |   yyssp++;
1341 | 
1342 | 
1343 | /*--------------------------------------------------------------------.
1344 | | yysetstate -- set current state (the top of the stack) to yystate.  |
1345 | `--------------------------------------------------------------------*/
1346 | yysetstate:
1347 |   YYDPRINTF ((stderr, "Entering state %d\n", yystate));
1348 |   YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
1349 |   YY_IGNORE_USELESS_CAST_BEGIN
1350 |   *yyssp = YY_CAST (yy_state_t, yystate);
1351 |   YY_IGNORE_USELESS_CAST_END
1352 |   YY_STACK_PRINT (yyss, yyssp);
1353 | 
1354 |   if (yyss + yystacksize - 1 <= yyssp)
1355 | #if !defined yyoverflow && !defined YYSTACK_RELOCATE
1356 |     YYNOMEM;
1357 | #else
1358 |     {
1359 |       /* Get the current used size of the three stacks, in elements.  */
1360 |       YYPTRDIFF_T yysize = yyssp - yyss + 1;
1361 | 
1362 | # if defined yyoverflow
1363 |       {
1364 |         /* Give user a chance to reallocate the stack.  Use copies of
1365 |            these so that the &'s don't force the real ones into
1366 |            memory.  */
1367 |         yy_state_t *yyss1 = yyss;
1368 |         YYSTYPE *yyvs1 = yyvs;
1369 | 
1370 |         /* Each stack pointer address is followed by the size of the
1371 |            data in use in that stack, in bytes.  This used to be a
1372 |            conditional around just the two extra args, but that might
1373 |            be undefined if yyoverflow is a macro.  */
1374 |         yyoverflow (YY_("memory exhausted"),
1375 |                     &yyss1, yysize * YYSIZEOF (*yyssp),
1376 |                     &yyvs1, yysize * YYSIZEOF (*yyvsp),
1377 |                     &yystacksize);
1378 |         yyss = yyss1;
1379 |         yyvs = yyvs1;
1380 |       }
1381 | # else /* defined YYSTACK_RELOCATE */
1382 |       /* Extend the stack our own way.  */
1383 |       if (YYMAXDEPTH <= yystacksize)
1384 |         YYNOMEM;
1385 |       yystacksize *= 2;
1386 |       if (YYMAXDEPTH < yystacksize)
1387 |         yystacksize = YYMAXDEPTH;
1388 | 
1389 |       {
1390 |         yy_state_t *yyss1 = yyss;
1391 |         union yyalloc *yyptr =
1392 |           YY_CAST (union yyalloc *,
1393 |                    YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
1394 |         if (! yyptr)
1395 |           YYNOMEM;
1396 |         YYSTACK_RELOCATE (yyss_alloc, yyss);
1397 |         YYSTACK_RELOCATE (yyvs_alloc, yyvs);
1398 | #  undef YYSTACK_RELOCATE
1399 |         if (yyss1 != yyssa)
1400 |           YYSTACK_FREE (yyss1);
1401 |       }
1402 | # endif
1403 | 
1404 |       yyssp = yyss + yysize - 1;
1405 |       yyvsp = yyvs + yysize - 1;
1406 | 
1407 |       YY_IGNORE_USELESS_CAST_BEGIN
1408 |       YYDPRINTF ((stderr, "Stack size increased to %ld\n",
1409 |                   YY_CAST (long, yystacksize)));
1410 |       YY_IGNORE_USELESS_CAST_END
1411 | 
1412 |       if (yyss + yystacksize - 1 <= yyssp)
1413 |         YYABORT;
1414 |     }
1415 | #endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */
1416 | 
1417 | 
1418 |   if (yystate == YYFINAL)
1419 |     YYACCEPT;
1420 | 
1421 |   goto yybackup;
1422 | 
1423 | 
1424 | /*-----------.
1425 | | yybackup.  |
1426 | `-----------*/
1427 | yybackup:
1428 |   /* Do appropriate processing given the current state.  Read a
1429 |      lookahead token if we need one and don't already have one.  */
1430 | 
1431 |   /* First try to decide what to do without reference to lookahead token.  */
1432 |   yyn = yypact[yystate];
1433 |   if (yypact_value_is_default (yyn))
1434 |     goto yydefault;
1435 | 
1436 |   /* Not known => get a lookahead token if don't already have one.  */
1437 | 
1438 |   /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
1439 |   if (yychar == YYEMPTY)
1440 |     {
1441 |       YYDPRINTF ((stderr, "Reading a token\n"));
1442 |       yychar = yylex ();
1443 |     }
1444 | 
1445 |   if (yychar <= YYEOF)
1446 |     {
1447 |       yychar = YYEOF;
1448 |       yytoken = YYSYMBOL_YYEOF;
1449 |       YYDPRINTF ((stderr, "Now at end of input.\n"));
1450 |     }
1451 |   else if (yychar == YYerror)
1452 |     {
1453 |       /* The scanner already issued an error message, process directly
1454 |          to error recovery.  But do not keep the error token as
1455 |          lookahead, it is too special and may lead us to an endless
1456 |          loop in error recovery. */
1457 |       yychar = YYUNDEF;
1458 |       yytoken = YYSYMBOL_YYerror;
1459 |       goto yyerrlab1;
1460 |     }
1461 |   else
1462 |     {
1463 |       yytoken = YYTRANSLATE (yychar);
1464 |       YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
1465 |     }
1466 | 
1467 |   /* If the proper action on seeing token YYTOKEN is to reduce or to
1468 |      detect an error, take that action.  */
1469 |   yyn += yytoken;
1470 |   if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
1471 |     goto yydefault;
1472 |   yyn = yytable[yyn];
1473 |   if (yyn <= 0)
1474 |     {
1475 |       if (yytable_value_is_error (yyn))
1476 |         goto yyerrlab;
1477 |       yyn = -yyn;
1478 |       goto yyreduce;
1479 |     }
1480 | 
1481 |   /* Count tokens shifted since error; after three, turn off error
1482 |      status.  */
1483 |   if (yyerrstatus)
1484 |     yyerrstatus--;
1485 | 
1486 |   /* Shift the lookahead token.  */
1487 |   YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
1488 |   yystate = yyn;
1489 |   YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
1490 |   *++yyvsp = yylval;
1491 |   YY_IGNORE_MAYBE_UNINITIALIZED_END
1492 | 
1493 |   /* Discard the shifted token.  */
1494 |   yychar = YYEMPTY;
1495 |   goto yynewstate;
1496 | 
1497 | 
1498 | /*-----------------------------------------------------------.
1499 | | yydefault -- do the default action for the current state.  |
1500 | `-----------------------------------------------------------*/
1501 | yydefault:
1502 |   yyn = yydefact[yystate];
1503 |   if (yyn == 0)
1504 |     goto yyerrlab;
1505 |   goto yyreduce;
1506 | 
1507 | 
1508 | /*-----------------------------.
1509 | | yyreduce -- do a reduction.  |
1510 | `-----------------------------*/
1511 | yyreduce:
1512 |   /* yyn is the number of a rule to reduce with.  */
1513 |   yylen = yyr2[yyn];
1514 | 
1515 |   /* If YYLEN is nonzero, implement the default value of the action:
1516 |      '$$ = $1'.
1517 | 
1518 |      Otherwise, the following line sets YYVAL to garbage.
1519 |      This behavior is undocumented and Bison
1520 |      users should not rely upon it.  Assigning to YYVAL
1521 |      unconditionally makes the parser a bit smaller, and it avoids a
1522 |      GCC warning that YYVAL may be used uninitialized.  */
1523 |   yyval = yyvsp[1-yylen];
1524 | 
1525 | 
1526 |   YY_REDUCE_PRINT (yyn);
1527 |   switch (yyn)
1528 |     {
1529 |   case 2: /* form: FORM IDENTIFIER '{' section_list '}'  */
1530 | #line 124 "src/parser.y"
1531 |     {
1532 |         current_form = create_form((yyvsp[-3].str));
1533 |         if (!current_form) {
1534 |             yyerror("Failed to create form");
1535 |             YYERROR;
1536 |         }
1537 |         (yyval.form) = current_form;
1538 |     }
1539 | #line 1540 "parser.tab.c"
1540 |     break;
1541 | 
1542 |   case 5: /* section: section_header '{' field_list '}'  */
1543 | #line 139 "src/parser.y"
1544 |     {
1545 |         current_section = NULL;
1546 |     }
1547 | #line 1548 "parser.tab.c"
1548 |     break;
1549 | 
1550 |   case 6: /* section: section_header error '}'  */
1551 | #line 143 "src/parser.y"
1552 |     {
1553 |         yyerror("Invalid section declaration");
1554 |         current_section = NULL;
1555 |         yyclearin;
1556 |         yyerrok;
1557 |     }
1558 | #line 1559 "parser.tab.c"
1559 |     break;
1560 | 
1561 |   case 7: /* section_header: SECTION IDENTIFIER  */
1562 | #line 152 "src/parser.y"
1563 |     {
1564 |         if (current_section != NULL) {
1565 |             yyerror("Nested sections are not allowed");
1566 |             YYERROR;
1567 |         }
1568 |         current_section = create_section((yyvsp[0].str));
1569 |         if (!current_section) {
1570 |             yyerror("Failed to create section");
1571 |             YYERROR;
1572 |         }
1573 |         add_section_to_form(current_form, current_section);
1574 |     }
1575 | #line 1576 "parser.tab.c"
1576 |     break;
1577 | 
1578 |   case 10: /* field_list: field_list error ';'  */
1579 | #line 169 "src/parser.y"
1580 |     {
1581 |         yyerror("Invalid field declaration");
1582 |         yyclearin;
1583 |         yyerrok;
1584 |     }
1585 | #line 1586 "parser.tab.c"
1586 |     break;
1587 | 
1588 |   case 11: /* field: FIELD IDENTIFIER ':' field_type field_attribute ';'  */
1589 | #line 177 "src/parser.y"
1590 |     {
1591 |         if (current_section == NULL) {
1592 |             yyerror("Field must be inside a section");
1593 |             YYERROR;
1594 |         }
1595 |         if (check_duplicate_field((yyvsp[-4].str))) {
1596 |             yyerror("Duplicate field name found");
1597 |             YYERROR;
1598 |         }
1599 |         add_field_to_section(current_section, (yyvsp[-4].str), (yyvsp[-2].field_type), (yyvsp[-1].num));
1600 |     }
1601 | #line 1602 "parser.tab.c"
1602 |     break;
1603 | 
1604 |   case 12: /* field: FIELD ':' field_type field_attribute ';'  */
1605 | #line 189 "src/parser.y"
1606 |     {
1607 |         yyerror("Missing field name");
1608 |         YYERROR;
1609 |     }
1610 | #line 1611 "parser.tab.c"
1611 |     break;
1612 | 
1613 |   case 13: /* field: FIELD IDENTIFIER ':' field_attribute ';'  */
1614 | #line 194 "src/parser.y"
1615 |     {
1616 |         yyerror("Missing field type");
1617 |         YYERROR;
1618 |     }
1619 | #line 1620 "parser.tab.c"
1620 |     break;
1621 | 
1622 |   case 14: /* field: FIELD IDENTIFIER ':' field_type error ';'  */
1623 | #line 199 "src/parser.y"
1624 |     {
1625 |         yyerror("Invalid field attribute");
1626 |         YYERROR;
1627 |     }
1628 | #line 1629 "parser.tab.c"
1629 |     break;
1630 | 
1631 |   case 15: /* field: FIELD IDENTIFIER ':' field_type field_attribute error  */
1632 | #line 204 "src/parser.y"
1633 |     {
1634 |         yyerror("Missing semicolon");
1635 |         YYERROR;
1636 |     }
1637 | #line 1638 "parser.tab.c"
1638 |     break;
1639 | 
1640 |   case 16: /* field_type: TEXT  */
1641 | #line 211 "src/parser.y"
1642 |          { (yyval.field_type) = FIELD_TEXT; }
1643 | #line 1644 "parser.tab.c"
1644 |     break;
1645 | 
1646 |   case 17: /* field_type: EMAIL  */
1647 | #line 212 "src/parser.y"
1648 |             { (yyval.field_type) = FIELD_EMAIL; }
1649 | #line 1650 "parser.tab.c"
1650 |     break;
1651 | 
1652 |   case 18: /* field_type: PASSWORD  */
1653 | #line 213 "src/parser.y"
1654 |                { (yyval.field_type) = FIELD_PASSWORD; }
1655 | #line 1656 "parser.tab.c"
1656 |     break;
1657 | 
1658 |   case 19: /* field_type: NUMBER  */
1659 | #line 214 "src/parser.y"
1660 |              { (yyval.field_type) = FIELD_NUMBER; }
1661 | #line 1662 "parser.tab.c"
1662 |     break;
1663 | 
1664 |   case 20: /* field_type: IDENTIFIER  */
1665 | #line 215 "src/parser.y"
1666 |                  { 
1667 |         yyerror("Invalid field type");
1668 |         YYERROR;
1669 |     }
1670 | #line 1671 "parser.tab.c"
1671 |     break;
1672 | 
1673 |   case 21: /* field_attribute: REQUIRED  */
1674 | #line 222 "src/parser.y"
1675 |              { (yyval.num) = 1; }
1676 | #line 1677 "parser.tab.c"
1677 |     break;
1678 | 
1679 |   case 22: /* field_attribute: OPTIONAL  */
1680 | #line 223 "src/parser.y"
1681 |                { (yyval.num) = 0; }
1682 | #line 1683 "parser.tab.c"
1683 |     break;
1684 | 
1685 |   case 23: /* field_attribute: %empty  */
1686 | #line 224 "src/parser.y"
1687 |       { (yyval.num) = 0; }
1688 | #line 1689 "parser.tab.c"
1689 |     break;
1690 | 
1691 | 
1692 | #line 1693 "parser.tab.c"
1693 | 
1694 |       default: break;
1695 |     }
1696 |   /* User semantic actions sometimes alter yychar, and that requires
1697 |      that yytoken be updated with the new translation.  We take the
1698 |      approach of translating immediately before every use of yytoken.
1699 |      One alternative is translating here after every semantic action,
1700 |      but that translation would be missed if the semantic action invokes
1701 |      YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
1702 |      if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
1703 |      incorrect destructor might then be invoked immediately.  In the
1704 |      case of YYERROR or YYBACKUP, subsequent parser actions might lead
1705 |      to an incorrect destructor call or verbose syntax error message
1706 |      before the lookahead is translated.  */
1707 |   YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);
1708 | 
1709 |   YYPOPSTACK (yylen);
1710 |   yylen = 0;
1711 | 
1712 |   *++yyvsp = yyval;
1713 | 
1714 |   /* Now 'shift' the result of the reduction.  Determine what state
1715 |      that goes to, based on the state we popped back to and the rule
1716 |      number reduced by.  */
1717 |   {
1718 |     const int yylhs = yyr1[yyn] - YYNTOKENS;
1719 |     const int yyi = yypgoto[yylhs] + *yyssp;
1720 |     yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
1721 |                ? yytable[yyi]
1722 |                : yydefgoto[yylhs]);
1723 |   }
1724 | 
1725 |   goto yynewstate;
1726 | 
1727 | 
1728 | /*--------------------------------------.
1729 | | yyerrlab -- here on detecting error.  |
1730 | `--------------------------------------*/
1731 | yyerrlab:
1732 |   /* Make sure we have latest lookahead translation.  See comments at
1733 |      user semantic actions for why this is necessary.  */
1734 |   yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
1735 |   /* If not already recovering from an error, report this error.  */
1736 |   if (!yyerrstatus)
1737 |     {
1738 |       ++yynerrs;
1739 |       {
1740 |         yypcontext_t yyctx
1741 |           = {yyssp, yytoken};
1742 |         char const *yymsgp = YY_("syntax error");
1743 |         int yysyntax_error_status;
1744 |         yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
1745 |         if (yysyntax_error_status == 0)
1746 |           yymsgp = yymsg;
1747 |         else if (yysyntax_error_status == -1)
1748 |           {
1749 |             if (yymsg != yymsgbuf)
1750 |               YYSTACK_FREE (yymsg);
1751 |             yymsg = YY_CAST (char *,
1752 |                              YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
1753 |             if (yymsg)
1754 |               {
1755 |                 yysyntax_error_status
1756 |                   = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
1757 |                 yymsgp = yymsg;
1758 |               }
1759 |             else
1760 |               {
1761 |                 yymsg = yymsgbuf;
1762 |                 yymsg_alloc = sizeof yymsgbuf;
1763 |                 yysyntax_error_status = YYENOMEM;
1764 |               }
1765 |           }
1766 |         yyerror (yymsgp);
1767 |         if (yysyntax_error_status == YYENOMEM)
1768 |           YYNOMEM;
1769 |       }
1770 |     }
1771 | 
1772 |   if (yyerrstatus == 3)
1773 |     {
1774 |       /* If just tried and failed to reuse lookahead token after an
1775 |          error, discard it.  */
1776 | 
1777 |       if (yychar <= YYEOF)
1778 |         {
1779 |           /* Return failure if at end of input.  */
1780 |           if (yychar == YYEOF)
1781 |             YYABORT;
1782 |         }
1783 |       else
1784 |         {
1785 |           yydestruct ("Error: discarding",
1786 |                       yytoken, &yylval);
1787 |           yychar = YYEMPTY;
1788 |         }
1789 |     }
1790 | 
1791 |   /* Else will try to reuse lookahead token after shifting the error
1792 |      token.  */
1793 |   goto yyerrlab1;
1794 | 
1795 | 
1796 | /*---------------------------------------------------.
1797 | | yyerrorlab -- error raised explicitly by YYERROR.  |
1798 | `---------------------------------------------------*/
1799 | yyerrorlab:
1800 |   /* Pacify compilers when the user code never invokes YYERROR and the
1801 |      label yyerrorlab therefore never appears in user code.  */
1802 |   if (0)
1803 |     YYERROR;
1804 |   ++yynerrs;
1805 | 
1806 |   /* Do not reclaim the symbols of the rule whose action triggered
1807 |      this YYERROR.  */
1808 |   YYPOPSTACK (yylen);
1809 |   yylen = 0;
1810 |   YY_STACK_PRINT (yyss, yyssp);
1811 |   yystate = *yyssp;
1812 |   goto yyerrlab1;
1813 | 
1814 | 
1815 | /*-------------------------------------------------------------.
1816 | | yyerrlab1 -- common code for both syntax error and YYERROR.  |
1817 | `-------------------------------------------------------------*/
1818 | yyerrlab1:
1819 |   yyerrstatus = 3;      /* Each real token shifted decrements this.  */
1820 | 
1821 |   /* Pop stack until we find a state that shifts the error token.  */
1822 |   for (;;)
1823 |     {
1824 |       yyn = yypact[yystate];
1825 |       if (!yypact_value_is_default (yyn))
1826 |         {
1827 |           yyn += YYSYMBOL_YYerror;
1828 |           if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
1829 |             {
1830 |               yyn = yytable[yyn];
1831 |               if (0 < yyn)
1832 |                 break;
1833 |             }
1834 |         }
1835 | 
1836 |       /* Pop the current state because it cannot handle the error token.  */
1837 |       if (yyssp == yyss)
1838 |         YYABORT;
1839 | 
1840 | 
1841 |       yydestruct ("Error: popping",
1842 |                   YY_ACCESSING_SYMBOL (yystate), yyvsp);
1843 |       YYPOPSTACK (1);
1844 |       yystate = *yyssp;
1845 |       YY_STACK_PRINT (yyss, yyssp);
1846 |     }
1847 | 
1848 |   YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
1849 |   *++yyvsp = yylval;
1850 |   YY_IGNORE_MAYBE_UNINITIALIZED_END
1851 | 
1852 | 
1853 |   /* Shift the error token.  */
1854 |   YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);
1855 | 
1856 |   yystate = yyn;
1857 |   goto yynewstate;
1858 | 
1859 | 
1860 | /*-------------------------------------.
1861 | | yyacceptlab -- YYACCEPT comes here.  |
1862 | `-------------------------------------*/
1863 | yyacceptlab:
1864 |   yyresult = 0;
1865 |   goto yyreturnlab;
1866 | 
1867 | 
1868 | /*-----------------------------------.
1869 | | yyabortlab -- YYABORT comes here.  |
1870 | `-----------------------------------*/
1871 | yyabortlab:
1872 |   yyresult = 1;
1873 |   goto yyreturnlab;
1874 | 
1875 | 
1876 | /*-----------------------------------------------------------.
1877 | | yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
1878 | `-----------------------------------------------------------*/
1879 | yyexhaustedlab:
1880 |   yyerror (YY_("memory exhausted"));
1881 |   yyresult = 2;
1882 |   goto yyreturnlab;
1883 | 
1884 | 
1885 | /*----------------------------------------------------------.
1886 | | yyreturnlab -- parsing is finished, clean up and return.  |
1887 | `----------------------------------------------------------*/
1888 | yyreturnlab:
1889 |   if (yychar != YYEMPTY)
1890 |     {
1891 |       /* Make sure we have latest lookahead translation.  See comments at
1892 |          user semantic actions for why this is necessary.  */
1893 |       yytoken = YYTRANSLATE (yychar);
1894 |       yydestruct ("Cleanup: discarding lookahead",
1895 |                   yytoken, &yylval);
1896 |     }
1897 |   /* Do not reclaim the symbols of the rule whose action triggered
1898 |      this YYABORT or YYACCEPT.  */
1899 |   YYPOPSTACK (yylen);
1900 |   YY_STACK_PRINT (yyss, yyssp);
1901 |   while (yyssp != yyss)
1902 |     {
1903 |       yydestruct ("Cleanup: popping",
1904 |                   YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
1905 |       YYPOPSTACK (1);
1906 |     }
1907 | #ifndef yyoverflow
1908 |   if (yyss != yyssa)
1909 |     YYSTACK_FREE (yyss);
1910 | #endif
1911 |   if (yymsg != yymsgbuf)
1912 |     YYSTACK_FREE (yymsg);
1913 |   return yyresult;
1914 | }
1915 | 
1916 | #line 227 "src/parser.y"
1917 | 
1918 | 
1919 | void yyerror(const char *s) {
1920 |     fprintf(stderr, "Error: %s at line %d\n", s, yylineno);
1921 | }
1922 | 
1923 | int main() {
1924 |     int result = yyparse();
1925 |     cleanup_form(current_form);
1926 |     return result;
1927 | }
```

FormLang/progress.md
```
1 | # FormLang++ Progress
2 | 
3 | ## Milestone 1: Basic Form Structure ✅
4 | - [x] Form declaration syntax
5 | - [x] Section organization
6 | - [x] Basic field types (text, email, password)
7 | - [x] Required/optional field attributes
8 | 
9 | ## Milestone 2: Parser Implementation ✅
10 | - [x] Lexer for token recognition
11 | - [x] Parser for syntax validation
12 | - [x] Error handling and reporting
13 | - [x] Memory management for form structures
14 | 
15 | ## Milestone 3: HTML Generator Foundation ✅
16 | - [x] HTML Generation Implementation
17 |   - [x] Form header/footer generation
18 |   - [x] Section generation with fieldset elements
19 |   - [x] Field rendering for all types (text, email, password, number)
20 |   - [x] Basic CSS styling
21 | - [x] Integration with Parser
22 |   - [x] Connected HTML generation to parser output
23 |   - [x] Added file output support
24 |   - [x] Implemented error handling for HTML generation
25 | - [x] Testing Infrastructure
26 |   - [x] Created test forms with all field types
27 |   - [x] Implemented test script with color-coded output
28 |   - [x] Added error case testing
29 |   - [x] Automated HTML output generation
30 | 
31 | ## Milestone 4: Extended Field Types (In Progress)
32 | - [ ] Additional field types
33 |   - [ ] Checkbox
34 |   - [ ] Radio buttons
35 |   - [ ] Select dropdown
36 |   - [ ] Textarea
37 | - [ ] Field validation rules
38 |   - [ ] Min/max length
39 |   - [ ] Pattern matching
40 |   - [ ] Custom validation
41 | - [ ] Client-side validation
42 |   - [ ] JavaScript integration
43 |   - [ ] Real-time validation
44 |   - [ ] Error message display
45 | 
46 | ## Current Status
47 | - HTML generator successfully creates styled forms
48 | - All basic field types (text, email, password, number) properly rendered
49 | - Error handling working correctly
50 | - Test infrastructure in place with automated testing
51 | - Ready for extended field types in Milestone 4
52 | 
53 | ## Next Steps
54 | 1. Implement extended field types
55 | 2. Add support for validation rules
56 | 3. Implement client-side validation
57 | 4. Enhance error reporting
58 | 5. Add more comprehensive testing 
```

FormLang/bin/formLang
```
1 | ELF          >     #      @       (#         @ 8  @ ' &       @       @       @       �      �                                                                                        0      0                                           �L      �L                    p       p       p      �$      �$                   ��      ��      ��      �      �                   �      �      �      �      �                   8      8      8      0       0                    h      h      h      D       D              S�td   8      8      8      0       0              P�td   $�      $�      $�      �      �             Q�td                                                  R�td   ��      ��      ��      p      p             /lib64/ld-linux-x86-64.so.2               GNU   �          � �                   GNU ����F��?���KKئ�	�          GNU                                � �          (��e�mfUa9�                                                  z                      �                                            ;                      g                      $                      Q                                            �                      �                      �                      8                      B                      �                      �                      s                      _                      K                                            n                      �                      *                      �                      G                      4                      /                      X      �             �   "                        0�             �     @�              stdin perror __stack_chk_fail free fread exit getc strdup ferror clearerr fopen strlen stdout realloc isatty atoi malloc __libc_start_main stderr fprintf __cxa_finalize sprintf memset memcpy fileno fwrite strcmp __errno_location libc.so.6 GLIBC_2.14 GLIBC_2.4 GLIBC_2.34 GLIBC_2.2.5 _ITM_deregisterTMCloneTable __gmon_start__ _ITM_registerTMCloneTable                                           �          ���   �      ii   �      ���        ui	         ��              $      ��             �#      ��             �r      ��             �r      ��             �r      ��             �r      ��             �r      ȫ             �r      Ы             �r      ث             �r      �             �r      �             �r      �             �r      ��             �r       �             �r      �             s      �             s      �             s       �             s      (�             's      0�             0s      8�             :s      @�             Ds      H�             Hs      P�             Ls      X�             Qs      `�             Vs      h�             ^s      p�             fs      x�             qs      ��             �s      ��             �s      ��             �s      ��             �s      ��             �s      ��             �s      ��             �s      ��             �s      ��             �s      Ȭ             �s      Ь             �s      ج             �s      �             �s      �             �s      �             �s      ��             t      �             �      ȯ                    Я                    د                    �                    �                     �                    0�                    @�                    �                    �                     �                    (�                    0�                    8�                    @�         	           H�         
2 |            P�                    X�                    `�                    h�                    p�                    x�                    ��                    ��                    ��                    ��                    ��                    ��                    ��                    ��                    ��                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    ��H��H�ɏ  H��t��H���     �5ڎ  �%܎  @ ��h    �����f���h   �����f���h   �����f���h   ����f���h   ����f���h   ����f���h   ����f���h   �r���f���h   �b���f���h	   �R���f���h
3 |    �B���f���h   �2���f���h   �"���f���h   ����f���h   ����f���h   �����f���h   �����f���h   �����f���h   �����f���h   ����f���h   ����f���h   ����f���h   ����f����%>�  fD  ���%V�  fD  ���%N�  fD  ���%F�  fD  ���%>�  fD  ���%6�  fD  ���%.�  fD  ���%&�  fD  ���%�  fD  ���%�  fD  ���%�  fD  ���%�  fD  ���%��  fD  ���%��  fD  ���%�  fD  ���%�  fD  ���%ތ  fD  ���%֌  fD  ���%Ό  fD  ���%ƌ  fD  ���%��  fD  ���%��  fD  ���%��  fD  ���%��  fD  ��1�I��^H��H���PTE1�1�H�=P   ���  �f.�     H�=��  H���  H9�tH�f�  H��t	���    ��    H�=��  H�5��  H)�H��H��?H��H�H��tH�5�  H��t��fD  ��    ���=}�   u+UH�=�   H��tH�=&�  �����d����U�  ]� ��    ���w�����UH��H�� H�}�   �]���H�E�H�}� u�    �1H�E�H������H��H�E�H�H�E�H�@    H�E��@    H�E�����UH��H�� H�}�   �����H�E�H�}� u�    �1H�E�H���`���H��H�E�H�H�E�H�@    H�E��@    H�E�����UH��H�� H�}�H�u�H�^�  H���   �   H�*K  H�������H�}� tH�}� u(H�-�  H���   �   H�K  H���������   H��  H���   �   H��J  H������H�E�@��H�H��    H�E�H�@H��H������H�E�H�}� u-H���  H���&   �   H��J  H���D����   �*���H�E�H�U�H�PH�E�H�PH�E�@H�H��H�H�E�H�H�E�@�PH�E�PH�G�  H���   �   H��J  H�����������UH��H�� H�}��E�    �5H�9�  �U�Hc�H��H�H� H�U�H��H���������u�   ��E���  9E�|��    ����UH��H�}�H�}� tfH�E�� ����H�E��@����H�E��@����H�E��@����H�E��@����H�E��@����H�E�H�@    H�E�H�@     H�E��@(    ��]���UH��SH��HH�}�H�u��U�H�M�H�*�  H�U�H��I  H��H�Ǹ    ����H�}� tH�}� tH�}� u(H��  H���   �   H�nI  H�������+  ��  �����  ���  H�H��H��H�݈  H��H�������H�E�H�}� u-H���  H���)   �   H�,I  H���$����   �
4 | ���H�E�H���  H���  ���  Hc�H��H��H�H�E�H�������H�H�]�  �_�  Hc�H��H��H�  �BH�	�  H���   �   H��H  H������H�Eȋ@��H�H��H��H�E�H�@H��H������H�E�H�}� u-H���  H���$   �   H��H  H���I����   �/���H�E�H�U�H�PH�E�H�PH�Eȋ@H�H��H�H�E�H�E�H������H��H�E�H�H�E�U��PH�E�H�HH�E��0   H��H���K���H�E�H�@H��tH�E�H�@H�������H��H�E�H�P(H�E�H�@ H��tH�E�H�@ H������H��H�E�H�P0H�Eȋ@�PH�EȉPH�Æ  H���   �   H��G  H���W���H�]�����UH��H��0H�}�H�}� �V  �E�    ��   H�E�H�@�U�Hc�H��H�H� H�E�H�}� ��   �E�    �rH�E�H�@�U�Hc�H��H�H�E�H�E�H� H��tH�E�H� H������H�E�H�@(H��tH�E�H�@(H���i���H�E�H�@0H��tH�E�H�@0H���L����E�H�E��@9E�|�H�E�H�@H��tH�E�H�@H������H�E�H� H��tH�E�H� H������H�E�H��������E�H�E؋@9E������H�E�H�@H��tH�E�H�@H�������H�E�H� H��tH�E�H� H������H�E�H�������E�    �?H�P�  �U�Hc�H��H�H� H��tH�4�  �U�Hc�H��H�H� H���\����E���  9E�|�H��  H��tH���  H���2������      �����UH��}��E�H�H��    H��  H�]���UH��H�}�H�uЉU��E�    H�E�H� � ��H�H�@H  ����E��}����   �}� y�E�����    �E��2   +E��E��E��!   9�OE��E�E��b�U�E��H�H��H  ���9E�uA�}�t;H�}� u�E��.�E�;E�u�    �K�E�P�U�H�H��    H�E�HE��E��E�;E�|�H�}� t�}� u�}� ~
5 | H�E�� �����E�]���UH��H�}�H�u�H�E�H�E�H�E�H�E���H�U�H�BH�E�H�E�H�HH�M���� ��u�H�E�H��]���UH��H�� H�}�H�u�H�E�� <"��   H�E�    H�E�H�E�H�E�H�E�� ����\t��\'��,ta��,��"t:��'u�PH�E�H�E�� <\uC�H�}� tH�U�H�E�H�H�E�� �H�E��H�}� tH�U�H�E�H��  H�E��2끐��H�}� tH�U�H�E�H��H�������H+E��H�E�H����������UH��H��(H�}�H�u��U��E�    H�E�@���thH�}� t�E�H�H��    H�E�H�H�E�@��E��E܍P�H�}� t
6 | H�E�H���H�E�H�M�H��H���G����E��}��u������	�E�E��E�����UH��H��pH�}�H�u�H�U�dH�%(   H�E�1�H�E�    H�E�    H�M�H�E��   H��H�������E��}��u
7 | �������  �}�w$�E�H��    H��G  �H�H��G  H�>��H��F  H�E��?H��F  H�E��2H��F  H�E��%H�G  H�E��H�%G  H�E��H�PG  H�E�H�E�H������H�E��H�H)�H�BH�E��E�    �X�E�H��D��H�H��    H� |  H�H�ƿ    �X���H�U�H�H�E�H�E�H;E�
8 | H�E�H�E��
9 | �������   �E��E�;E�|�H�E�H� H9E�~7H�E�H� H�E�H�H�E�H� H9E�~H�E�H��������H�������   H�E�H� H�E��E�    �jH�E�� <%uUH�E�H��� <suF�E�;E�}>�E��P�U�H��D��H�H��    H� {  H�H�E�H��H���v���HE�H�E��
10 | H�E�H�E�H�E��H�EЈH�E�� ���z����    H�U�dH+%(   t�3�������UH��H�}��u�H�U�H�}� uH��E  H�E��]���UH��SH��   H�$ H��   H�$ H���  dH�%(   H�E�1�ǅ4���    ǅ8���    Hǅh����   H�� ���H��p���H��p���H��x���H�� ���H������H������H������ǅD�������H������H��X���Hǅ`����   ǅH���    ��~  �����H��x�����4�����H��x����H��h���H�P�H��p���H�H9�x����-  H��x���H+�p���H��H������H��h���'  ��  Hѥh���H��h���'  ~Hǅh���'  H��p���H������H��h���H��H�H�H��H�H��/H�������H������H������ �T  H������H������H��p���H��H��H������H������H��p���H��h���H��/H������H������H��������*H��H��H��H��H��?H)�H��H�H�H��H�����H������H��H�H�H��H��H������H������H��H��H��H������H������H������H��h���H��H�H�H��H��/H������H������H��������*H��H��H��H��H��?H)�H��H�H�H��H�����H�� ���H9�����tH������H�������H������H�P�H��p���H�H��x���H������H��H�H�H��H�P�H������H�H������H��h���H�P�H��p���H�H9�x�����  ��4�����  ���4���H�H��?  �����<�����<������  �	|  ���u��  ��{  ��{  ����{      ǅD���    �`��{  =   u��{    ǅD���   �  ��{  ��x%��{  =  ��{  H�H��<  �����   ��D�����D����<�����<��� ��   ��<���1��   ��<���H�H��?  ���9�D�����   ��<���H�H�f?  �����<�����<��� ��<����   ��8��� t��8�����<�����4���H������0H������H��z  H��z  H�H�XH��z  H��z  H�HH�XH��z  H��z  H�H H�X(��z  ��������������4���H�H�W>  �����<�����<��� �  ���<���H�H��?  �����H����   +�H���Hc�H��H�H�H��H��H������H�H�H�XH������H������H�HH�XH������H������H�P(H�@ H������H��������<���$�/  ��<���H��    H�eA  �H�H�YA  H�>��H������H� H������H�jy  H�cy  H����  H��?  H���B  �	  H��x  H���3  H�0y  H�������  H�!y      �  H�y      �  H��?  H����  H��x      ��x  ����ǅ8���    �]  H��x  H��tH��?  H���  �l  H������H� H������H��x  H��x  H��uH�}?  H���t  �3  H�yx  H�jx  H��H���������  H�d?  H���B  �]x  ����ǅ8���    �  H�3x  H��uH�O?  H���  ��  H������H-�   H� H��������tH�>?  H����
11 |   �  H������H��0H��H������H��`�H������H-�   H�0H��w  H���;���H������H-�   H� H��������  ǅ����    �  ǅ����   ��  ǅ����   ��  ǅ����   ��  ǅ����   ��  ǅ����   �  ǅ����   �  ǅ����   �  ǅ����   �  ǅ����	   �  H������H��������m  H������H��0H�H�XH������H������H�HH�XH������H������H�P(H�@ H������H������H�������@(���tH�������@(������H������� ���tH������� ������H�������@���tH�������@������H�������@���tH�������@������H�������@���tH�������@������H�������@���tH�������@������H�������@���tH�������@������H������H�@H��t5H������H��tH������H�������H������H�@H��� ���H������H������H�@ H����  H������H��tH������H������H������H�@ H�������H�������  H������H���3���ǅ����   �  H������H������ǅ����    �{  H������H�������H������� �������X  H������H�������H������� �������5  H������H������H������� �������  H������H������H������� ��������   H������H���k���H������� ��������   H������H���H���H������� �������   H������H���%���H������H� H������H�������H������H�������H������H� H���r���H�������UH������H�������H�������H������H�;  H��H�Ǹ    ����H������H���$���H��������������H���Hc�H��H�H�H��H��H�������H���H�H��H�x���ǅH���    H������0H������H������H������H�H�XH������H������H�HH�XH������H������H�H H�X(��<���H�H��7  �����!��P�����P���H�H��6  ���H��x���� ��Љ�T�����T��� xB��T���19��T���H�H�7  �H��x���� 8�u��T���H�H��6  ������P���H�H��6  �����4���������Gr  ���t6�<r  ��x%�2r  =  �%r  H�H� 3  �����   ��������D�����8��� �?  �"r  ���r  H��x���H��������D���������H�-7  H������H������H��X���H��`���H��H��������L�����L��� uH��X���H�������   ��L������   H��X���H������H9�tH��X���H������H��`���H���A���H��X���H��X���H��t6H������H��X���H��`���H��H��������L���H��X���H�������#H������H��X���Hǅ`����   ǅL�������H������H���  ��L�����(  ��8�����   ��p  ����p  ����   ��  ��D���H��p  ��H��7  H��������cp  �����`��p  ����p  ��H���Hc�H��H�H�H��H��H�������H���H�H��H�x���ǅH���    H��x���� ����4�����ǅ8���   ��4���H�H��3  �����<�����<����tU��<�����<��� xE��<���1<��<���H�H�-4  �<u%��<���H�H��3  �����<�����<��� jH��x���H;�p�����   ��4���H�H�4  ���H��������H��6  H������H������0H��x���H��x���� ����4��������H������0H������H��n  H� o  H�H�XH��n  H��n  H�HH�XH��n  H��n  H�H H�X(��<�����4��������ǅ@���    �1���ǅ@���   �!�����H��5  H���X  ǅ@���   ��ln  ���tX�an  ��x%�Wn  =  �Jn  H�H�E/  �����   ��D�����D���H�$n  ��H��5  H���r�����H���Hc�H��H�H�H��H��H�������H���H�H��H�x����EH��x���� ��H�H��2  ���H��������H�O5  H���	���H������0H��x���H��x���H;�p���u�H�� ���H9�p���tH��p���H������H��X���H������H9�tH��X���H���y�����@���H�U�dH+%(   t����H�]�����UH��H��H�}���l  H��l  H�M�H�5E5  H�Ǹ    ���������UH��H�� �}�H�u��}�~MH�E�H��H� H�&5  H��H�������H�E�H�}� uH�E�H��H� H��������   �$H�E�H��l  ����H�_l  H�������    ����UH��   ]���UH��H��H�}���k  H�l  H�M�H�5�<  H�Ǹ    ����������UH��SH��8��l  ����   ��l     ��l  ��u
12 | ��l     H�)l  H��uH��k  H�l  H�l  H��uH�ck  H�l  H�=l  H��tH�1l  H�l  H��H�H� H��u2��  H��k  H�l  H��k  H��H�
13 | � @  H���;  H��  H��k  H�E���k  H�E��H�E�H�E��k  �E�H�E�� ��H�H��4  ��EˋE�H�H� H��3  �f��tK�Ẻ�k  H�E�H��k  �5�E�H�H� H��6  ���É}̇   ~�E�H�H�\5  ��EˋE�H�H� H��5  ����E��H�H� H�+9  ��9E�u��E�H�H� H�Q5  ����E��H�H� H�w7  ���E�H�E��E�H�H� H�5  �f=� �������E�H�H� H��2  ���EЃ}� u,H��j  H�E���j  �E̋E�H�H� H�i2  ���E�H�E�H�.j  H�E�H+E� j  H�E�� �Kj  H�E��  H�E�H�Aj  �}�"u��Z�E�H�H��    H��9  ���t��E�    �)H��i  �E�H�H�� <
14 | u��h  ����h  �E���i  9E�|�룃}�#�-  �E�H��    H�&:  �H�H�:  H�>����i  H�E��H��i  H�E���i  �E�������  ��  �  ��  �  ��  �.i     �:   ��  �i      �;   �  �{   �  �}   �  ��h  ��t
15 | �  �  �  �  ��h  ��t
16 | �  �r  �  �h  ��h  ��t
17 | �  �T  �  �J  ��h  ��t
18 | �  �6  �  �,  �~h  ��t
19 | �	  �  �  �  �`h  ��t
20 | �
21 |   ��  �  ��  �Bh  ��t
22 | �  ��  �  ��  �$h  ��t
23 | �  �  �  �  �h  ��t
24 | �  �  �  �  ��g  ��t
25 | �  �  �  �x  �  �n  �  �d  �  �Z  �  �P  �  �F  �  �<  �  �2  �  �(  �  �  �  �  H�Yg  H���y���H��f  �  ��  H�9g  H��������f  �  ��  H�g  H�g  H���3���H��H��  H��f  H��H������H��f  �  �  H��f  � ���  H��f  ��f  Hc�H��f  H�Ѻ   H�������N  �    �I  H��f  H�U�H)Ѓ��E���f  H�E��H��f  H��f  H��H�H� �@8��ubH�|f  H�ef  H��H�H� �@�nf  H�[f  H�Df  H��H�H� H��e  H�H�9f  H�"f  H��H�H� �@8   H�f  H�f  H��H�H� H�P�f  H�H�H�f  H9�rtH��e  �E�H�H�H��e  �  �E̋Ẻ���  �E�H��e  H�E�}� t(H��e  H��H��e  H��e  H�E��E܉E������H��e  H�E��������   ����   ����   ��t>����   �le      H�e  H�Ne  �Te  �����������#�E��S���H��d  �E�H�H�H�e  ��  �E�H�e  H�E�H��d  H�E��-���H��d  H��d  H��H�H� H�P��d  H�H�H��d  �  �E�H��d  H�E�H�pd  H�E������H��4  H���  ����������H�]�����UH��SH��HH�bd  H�Kd  H��H�H� H�@H�E�H�d  H�E�H�7d  H� d  H��H�H� H�@�(d  Hc�H��H�H�d  H9�sH�5  H���  H��c  H��c  H��H�H� �@4��u+H��c  H��c  H)�H��u
26 | �   �  �   �  H��c  H�oc  H)Ѓ��E��E�    �!H�U�H�BH�E�H�E�H�HH�M����E��E�;E�|�H�[c  H�Dc  H��H�H� �@8��u0�Dc      H�1c  H�c  H��H�H� �&c  �P�#  H�c  H��b  H��H�H� �@+Eȃ��E��  H��b  H��b  H��H�H� H�E�H��b  H�E�H�@H)U�H�E�@ ��tqH�E�@��EЃ}� $H�E�PH�E�@�H��H����H�E�P�H�E�@� H�E�PH�E�@��Hc�H�E�H�@H��H���  H�U�H�B�H�E�H�@    H�E�H�@H��uH�\3  H���+  H�E�H�P�E�H�H�H�b  H��a  H��a  H��H�H� �@+Eȃ��E��}� ������}�    ~�E�    H��a  H��a  H��H�H� �@$����   �E�*   �E�    �7H��a  H�na  H��H�H� H�@�U�HcʋU�Hc�H�HЋU���E��E�;E�}H��`  H���F����E��}��t�}�
27 | u��}�
28 | u8H�"a  H�a  H��H�H� H�H�E�Hc��EčP�U�H�H�HȋU���}��u"H��`  H��������tH�=2  H����  �Eĉ�`  �   �n����     �5�a���� ��tH�2  H���  �F����     H�9`  H�������H�*`  �E�H�H�f`  H�5O`  H��H�H�	H�q�M�Hc�H�<H��H�¾   �����=`  �7`  ��uH��_  H����������b���H�	`  H��_  H��H�H� ��_  �P��_  ��uF�}� u�E�   H��_  H����  �/�E�   H��_  H��_  H��H�H� �@8   ��E�    ��_  �EȍH��_  H�n_  H��H�H� �@9���   �o_  �E�d_  ��ЉEԋE�Hc�H�D_  H�-_  H��H�H� H�@H�(_  H�5_  H��H�H�H��H���^  H�CH�_  H��^  H��H�H� H�@H��uH�p0  H����  H��^  H��^  H��H�H� �Uԃ��P��^  �E�Љ�^  H��^  H��^  H��H�H� H�P��^  H�H��  H�u^  H�^^  H��H�H� H�@�f^  Hc�H��H��  H�F^  H�/^  H��H�H� H�@H��]  �E�H�]�����UH��/^  �E�H��]  H�E���   H�E�� ��tH�E�� ��H�H��&  ���   �E�E�H�H� H��%  �f��tK�E��]  H�E�H��]  �5�E�H�H� H�)  ���E�}�   ~�E�H�H��'  ��E�E�H�H� H��'  ����E��H�H� H�^+  ��9E�u��E�H�H� H��'  ����E��H�H� H��)  ���E�H�E�H�]  H9E�������E�]���UH��}�H��\  H�E��E��E�H�H� H��$  �f��tK�E��\  H�E�H��\  �5�E�H�H� H�(  ���E�}�   ~�E�H�H��&  ��E�E�H�H� H��&  ����E��H�H� H�_*  ��9E�u��E�H�H� H��&  ����E��H�H� H��(  ���E�}�   �����E�}� u�E���    ]���UH��SH��H�}�H��[  H��tH��[  H��[  H��H�H� H��u2�w  H�[[  H��[  H��[  H��H�
29 | � @  H����  H�H�v[  H��tH�j[  H�S[  H��H�H� ��    H�U�H��H���  ��   �H�]�����UH��H��H�}���  H�[  H��tH�[  H��Z  H��H�H� ��    H;E���   H��Z  H��tqH��Z  H��Z  H��H�H� H��tTH��Z  ��Z  �H��Z  H��Z  H��H�H� H��Z  H�PH��Z  H�sZ  H��H�H� �Z  �PH�iZ  H�RZ  H��H�H�E�H��   �eZ     ������UH��H�1Z  H�Z  H��H�H� �@�#Z  H�Z  H��Y  H��H�H� H�@H�Z  H��Y  H��Y  H��Y  H��Y  H��H�H� H� H�|Y  H��Y  � ��Y  �]���UH��H�� H�}�u�@   ��	  H�E�H�}� uH�B+  H���  H�E��U�PH�E��@��H�H���	  H�U�H�BH�E�H�@H��uH� +  H���O  H�E��@    H�U�H�E�H��H���   H�E�����UH��H��H�}�H�}� tvH��X  H��tH��X  H��X  H��H�H� ��    H;E�uH��X  H��X  H��H�H�     H�E��@ ��tH�E�H�@H���	  H�E�H���	  ������UH��H�� H�}�H�u��#���� �E�H�E�H���   H�E�H�U�H�H�E��@4   H�=X  H��tH�1X  H�X  H��H�H� ��    H;E�tH�E��@,   H�E��@0    H�}� tH�E�H���R�����������~�   ��    H�E�P$�����U�������UH��H��H�}�H�}� ��   H�E��@    H�E�H�@�  H�E�H�@H���  H�E�H�PH�E�H�PH�E��@(   H�E��@8    H�RW  H��tH�FW  H�/W  H��H�H� ��    H;E�u�����������UH��H��H�}�H�}� ��   ��  H��V  H��tqH��V  H��V  H��H�H� H��tTH��V  ��V  �H��V  H��V  H��H�H� H��V  H�PH��V  H��V  H��H�H� ��V  �PH�zV  H��t/H�nV  H�WV  H��H�H� H��tH�AV  H��H�6V  H�?V  H�(V  H��H�H�E�H�������;V     ������UH��H�V  H����   H��U  H��U  H��H�H� H����   H��U  H��tH��U  H��U  H��H�H� ��    H������H��U  H��U  H��H�H�     H�wU  H��tH�kU  H��H�`U  H�iU  H��t/H�]U  H�FU  H��H�H� H��t�����XU     ��]���UH��H��H� U  H��uuH�E�   H�E�H��H���7  H��T  H��T  H��uH��&  H����  H�E�H��    H��T  �    H�������H�E�H��T  H��T      �   H��T  H��H��T  H9���   H�E�   H�tT  H�E�H�H�E�H�E�H��    H�^T  H��H���  H�LT  H�ET  H��uH�)&  H���H  H�E�H��    H�T  H�T  H��HȾ    H������H�E�H��S  ����UH��H�� H�}�H�u�H�}�v,H�E�H�P�H�E�H�� ��uH�E�H�P�H�E�H�� ��t
30 | �    �   �@   ��  H�E�H�}� uH��%  H���  H�E�����H�E��PH�E�H�U�H�PH�E�H�PH�E�H�PH�E��@     H�E�H�     H�E��PH�E��PH�E��@$    H�E��@(   H�E��@4    H�E��@8    H�E�H�������H�E�����UH��H��H�}�H�E�H���������H�E���H���   ����UH��H��0H�}؉uԋEԃ�H�H�E�H�E�H����  H�E�H�}� uH��$  H���   �E�    �#�E�Hc�H�E�HЋU�Hc�H�U�H�� ��E��E�;E�|ՋE�H�H�PH�E�H��  �U�Hc�H�U�H�� �H�U�H�E�H��H������H�E�H�}� uH��$  H���   H�E��@    H�E�����UH��H��H�}�H�
31 | Q  H�U�H�f$  H��H�Ǹ    ������   ������UH���P  ]���UH��H�FQ  ]���UH��H�=Q  ]���UH��Q  ]���UH��H�,Q  ]���UH��}��E��NP  �]���UH��H�}�H�E�H��P  �]���UH��H�}�H�E�H��P  �]���UH���P  ]���UH��}��E���P  �]���UH����O     H��P      H��P      H��P      H��P      ��P      ��P      H�CP      H�@P      �    ]���UH���TH�hP  H��tH�\P  H�EP  H��H�H� ��    H���(���H�5P  H�P  H��H�H�     ����H�P  H��tH�P  H��O  H��H�H� H��u�H��O  H���^   H��O      ������    ]���UH��H��H�}�H�E�H���(�������UH��H��H�}�H�u�H�U�H�E�H��H����������UH��H��H�}�H�E�H�����������UH��H��H�}�H�E�H���   �   H��!  H������H�E�H���   �   H��!  H�������H�E�H���Z   �   H��!  H�������H�E�H���A   �   H�"  H������H�E�H���W   �   H�6"  H������H�E�H���#   �   H�n"  H���~���H�E�H���.   �   H�v"  H���^���H�E�H��"  H��H�Ǹ    蓿��H�E�H���z   �   H��"  H���#���H�E�H���2   �   H�K#  H������H�E�H���   �   H�^#  H�����������UH��H��H�}�H�E�H���   �   H�D#  H��谿�������UH��H��0H�}�H�u�H��L  H���   �   H�#  H���v���H�}� tH�}� u(H��L  H���   �   H�#  H���E����  H�E�H���
32 |    �   H��"  H��� ���H�E�H�H�E�H��"  H��H�Ǹ    �N���H�EЋPH�@L  H��"  H��H�Ǹ    �)����E�    �O  H�L  �U�H��"  H��H�Ǹ    �����H�E�H�@�U�Hc�H��H�H�E�H�E��@8��t	H��"  �H��"  H�U�H�
33 | H�U�H�H�}�I��H�u"  H�Ƹ    蟽��H�"  H�E�H�E��@��	��   ��H��    H�g%  �H�H�[%  H�>��H�A"  H�E��tH�9"  H�E��gH�2"  H�E��ZH�."  H�E��MH�("  H�E��@H�$"  H�E��3H�"  H�E��&H�"  H�E��H�"  H�E��H�"  H�E�H�E��@����   H�E�H�H�E�H�H�E�H�5�!  H�Ǹ    誼��H�E��@ ��~"H�E��P H�E�H��!  H��H�Ǹ    �}���H�E��@$��~"H�E��P$H�E�H��!  H��H�Ǹ    �P���H�E��@8��t H�E�H���	   �   H��!  H���ռ��H�E�H���   �   H�t!  H��赼���  H�E��@����   H�E�H�H�E�H�H�E�H�5L!  H�Ǹ    �ʻ��H�E��@8��t H�E�H���	   �   H�!  H���O���H�E�H���   �   H�!  H���/���H�E�H���-   �   H��   H������H�E�H���,   �   H�!  H������H�E�H���,   �   H�!  H���ϻ��H�E�H���
34 |    �   H�,!  H��读���  H�E��@���k  H�E�H���   �   H�!  H���z���H�E�H�H�E�H�H�E�H�5!  H�Ǹ    褺��H�E��@8��t H�E�H���	   �   H��  H���)���H�E�H���   �   H��  H���	���H�E�H�H�E�H��   H��H�Ǹ    �7���H�E�H�H�E�H�H�E�H�5�   H�Ǹ    ����H�E��@8��t H�E�H���	   �   H�K  H��薺��H�E�H���   �   H�]  H���v���H�E�H�H�E�H��   H��H�Ǹ    褹��H�E�H���   �   H��   H���4����  H�E�H�0H�E�H�H�U�H�E�I��H�5�   H�Ǹ    �R���H�E��@8��t H�E�H���	   �   H��  H���׹��H�E��@��~"H�E��PH�E�H�]   H��H�Ǹ    �����H�E��@��~"H�E��PH�E�H�@   H��H�Ǹ    �͸��H�E��@��~"H�E��PH�E�H�#   H��H�Ǹ    蠸��H�E��@��~"H�E��PH�E�H�    H��H�Ǹ    �s���H�E�H�@(H��t#H�E�H�P(H�E�H��  H��H�Ǹ    �C���H�E�H�@0H��t#H�E�H�P0H�E�H��  H��H�Ǹ    ����H�E�H���   �   H��  H��裸��H��E  �U�H��  H��H�Ǹ    �ҷ���E�H�EЋ@9E������H�E�H���   �   H�o  H���N���H��E  H���   �   H�X  H���+�������UH��H�� H�}�H�bE  H���   �   H�j  H�������H�_E  H��tH�}� u(H�,E  H���   �   H�N  H��������M  H�E  H���   �   H�;  H��蘷��H�E�H���>���H�E�H���   �   H�"  H���l���H��D  �PH��D  H�
35 |   H��H�Ǹ    蔶���E�    �OH��D  �U�H��  H��H�Ǹ    �j���H��D  H�@�U�Hc�H��H�H�H�E�H��H���C����E�H�UD  �@9E�|�H�E�H���%   �   H��  H��轶��H�E�H���   �   H��  H��蝶��H�E�H������H��C  H���   �   H��  H���n�������H��H���                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             Adding section to form
36 |  Null form or section
37 |  Reallocating sections array
38 |       Memory allocation failed for sections
39 |  Section added successfully
40 |  Adding field %s to section
41 |  Null section, name, or attrs
42 |     Memory allocation failed for field names
43 |  Reallocating fields array
44 |     Memory allocation failed for fields
45 |  Field added successfully
46 |             	
47 | "end of file" error "invalid token" FORM SECTION FIELD TEXT EMAIL PASSWORD NUMBER TEXTAREA DATE CHECKBOX DROPDOWN RADIO FILE_TYPE REQUIRED OPTIONAL MINLENGTH MAXLENGTH MIN MAX ROWS COLS PATTERN DEFAULT IDENTIFIER NUMBER_LITERAL STRING_LITERAL '{' '}' ';' ':' $accept form $@1 section_list section section_header field_list field field_type field_attributes attribute                       �����������������������������������������������             	 
48 |                !"$#      �����������      
49 | #$0     %&'()*+,-.89/ 	 !"1234 56 7               � 	
50 | ��               " #$%&'( 	
51 | )*+       !#"$$%%%&'''())))))))))**+++++++++++                                syntax error syntax error, unexpected %s   syntax error, unexpected %s, expecting %s       syntax error, unexpected %s, expecting %s or %s syntax error, unexpected %s, expecting %s or %s or %s   syntax error, unexpected %s, expecting %s or %s or %s or %s ,���9���F���S���`���m���Deleting Failed to create form Invalid section declaration  Nested sections are not allowed Failed to create section Invalid field declaration      Field must be inside a section Duplicate field name found %d Error: discarding Error: popping memory exhausted Cleanup: discarding lookahead Cleanup: popping   �����������������������������,���_�����������ֿ����������������������������������������,���;���O������#���A���d����������������������=���g���Parse error on line %d: %s
52 |  r                                     "                                                                                      	    
53 |                                                                 	
54 |  !                                     � � � � � � � �     {   r v �   ~ } � � � � �   z s j v m y  h b j j b  p c ] n Z l \ h k \ a ^ c [ f e b Z P N W K L J I Q     F U M S     Q P O E = L B F   E L J @ <     < ; 6 9 7 3   2 4 0 2 , ) 6 5   : ) , 3 * 1    '    & )   (   *     !               � 7 )               �  � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � �   � �                    	 
55 |                              # % 5    $ *  6 & + < = � � ! � � � ,   � �  ~ } | { z y x w v u t s r q p o n m l k j i h g f e d c b a ` _ ^ ] \ [ Z Y X W V U T S R Q P O N M L K J I H G F E D C B A @ ? > ; : 9 8 7 4 3 2 1 0 /   . - ) ( ' "   �  � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � �                                                            #     � #   ) ) �   | z x  � � w v u t r q p o n m l j i h g f e d c a ` _ ^ ] \ Y X W V U S R Q P O N M L I H G F C B A @ ? > = < ; : 9 8 7 6 5 4 3 2 1 0 / . - , + * ( ' & % $ " !                 � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � �                                                                                                                                                           Syntax error at line %d: %s
56 |     fatal flex scanner internal error--no action found  �������������&���0���D���X���b���l���������������������� ���>���\���z��������������������������������������������������;������������������    fatal flex scanner internal error--end of buffer missed fatal error - scanner input buffer overflow input in flex scanner failed        out of dynamic memory in yy_get_next_buffer()   out of dynamic memory in yy_create_buffer()     out of dynamic memory in yyensure_buffer_stack()        out of dynamic memory in yy_scan_buffer()       out of dynamic memory in yy_scan_bytes() bad buffer in yy_scan_bytes() %s
57 |       <!DOCTYPE html>
58 | <html>
59 | <head>
60 |  <style>
61 |  body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }
62 |       form { background: #f5f5f5; padding: 20px; border-radius: 5px; }
63 |        section { margin-bottom: 20px; padding: 15px; background: white; border-radius: 5px; }
64 |  h2 { color: #333; margin-top: 0; }
65 |      label { display: block; margin-bottom: 5px; }
66 |   input, textarea, select { width: 100%%; padding: 8px; margin-bottom: 10px; border: 1px solid #ddd; border-radius: 4px; }
67 |        input[type=submit] { background: #4CAF50; color: white; border: none; padding: 10px 20px; cursor: pointer; width: auto; }
68 |       input[type=submit]:hover { background: #45a049; }
69 |  </style>
70 | </head>
71 | <body>
72 |  </body>
73 | </html>
74 |  Starting section generation
75 |  Null section or output
76 |  <section>
77 |  <h2>%s</h2>
78 |  Processing %d fields
79 |  Generating field %d
80 |   *  <label for="%s">%s%s</label>
81 |  text email password number textarea date checkbox select radio file <textarea id="%s" name="%s"  rows="%d"  cols="%d"  required ></textarea>
82 |  <select id="%s" name="%s" >
83 |          <option value="">Select an option</option>
84 |      <option value="option1">Option 1</option>
85 |       <option value="option2">Option 2</option>
86 |  </select>
87 |  <div class="radio-group">
88 |         <input type="radio" id="%s_1" name="%s" value="option1"         <label for="%s_1">Option 1</label><br>
89 |          <input type="radio" id="%s_2" name="%s" value="option2"         <label for="%s_2">Option 2</label>
90 |  </div>
91 |    <input type="%s" id="%s" name="%s"  minlength="%d"  maxlength="%d"  min="%d"  max="%d"  pattern="%s"  value="%s"        Field %d generated successfully
92 |  </section>
93 |  Section generation complete
94 |    ���������������������������������� ���Starting HTML generation
95 |  Null form or output
96 |  Generating header
97 |  <form>
98 |  Processing %d sections
99 |  Generating section %d
100 |     <input type="submit" value="Submit">
101 |  </form>
102 |  HTML generation complete
103 |     ;�  <   ����  |���D  ����\  ����  ���t  D����  �����  ����  S����  ϛ��  {���8  g���X  ����x  �����  ����  ɢ���  `����  ����  ���8  3���\  k���|  ����  �����  3����  n���   ����$  ����D  ����d  �����  �����  3����  �����  `���  %���(  ����H  ����h  �����  �����  �����  ����  ����  7���$  G���D  X���d  i����  y����  �����  �����  ����  ����$  ����D  ����d  k����  ����  6����  _����  ~���	  ����$	  ���D	  ����d	         zR x�        ���&    D    $   4   ؒ���   FJw� ?9*3$"       \   0���              t   (���p             �   i���_    E�CV     �   ����_    E�CV     �   ���P   E�CG    �   ���`    E�CW       W���|    E�Cs      ,  �����   E�CE��     P  ;����   E�C�    p  ���%    E�C\      �  ���   E�C�     �  ����Q    E�CH     �  %����    E�C�     �  ����    E�C�       `���[   E�CR    0  ����(    E�C_       P  ����P   E�C`�'     t  ϳ��8    E�Co      �  ����    E�Cx     �  H���    E�CF      �  7���8    E�Co       �  O���;   E�CE�-        f���U   E�CE�G     <  ����2   E�C)    \  ����   E�C�      |  �����    E�CE��      �  ����    E�C�     �  �����    E�C�     �  c����    E�C�        �����    E�C�        P����    E�C�     @  �����    E�C�     `  v���   E�C�     �  ^����    E�C�     �  !���=   E�C4    �  >���   E�C�     �  !���.    E�Ce         /����    E�C�        ����<    E�C      <  ���    E�CG      \  ����    E�CH      |  ����    E�CH      �  ����    E�CG      �  ����    E�CH      �  ����    E�CN      �  ����    E�CQ        ����    E�CQ      <  ����    E�CG      \  ����    E�CN      |  ����o    E�Cf     �  �����    E�C�     �  l���    E�CU      �  j���)    E�C`      �  s���    E�CV        r���n   E�Ce    <  ����3    E�Cj      \  �����   E�C{    |  7����   E�C�                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          $      �#      �r      �r      �r      �r      �r      �r      �r      �r      �r      �r      �r      �r      �r      s      s      s      s      's      0s      :s      Ds      Hs      Ls      Qs      Vs      ^s      fs      qs      �s      �s      �s      �s      �s      �s      �s      �s      �s      �s      �s      �s      �s      �s      �s      t                     �                             �l             ��                           ��                    ���o    �             �             �      
104 |        a                                          ��             (                                        �             (      	                            ���o          ���o    �      ���o           ���o    J      ���o    /                                                                                       �                      0       @       P       `       p       �       �       �       �       �       �       �       �        !      !       !      0!      @!      P!      `!      p!      �!      �!                                                                      �         GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0 ,             	$                             ,           D      �                      ,    �*       �a      �
105 |                              /          	$                 �  �:   7  <  0U	  
106 |   W	  �  1int f   �  �	  �r   �
107 |   �r   �   ^	  �   �  �1)  �   3f    4  6	�   \  7	�     8	�   �  9	�    �	  :	�   (�   ;	�   0  <	�   8j   =	�   @3  @	�   H�  A	�   P�  B	�   XF  DB  `x
108 |   FG  h�  Hf   p�
109 |   If   t�  Jy   x�
110 |   MQ   ��  NX   �+   OL  ��  Q\  ��  Y�   ��  [f  ��  \p  ��   ]G  ��  ^	H   ��  _
111 | .   ��  `f   ��
112 |   bu  � �  �   25   +  =  �   	�   \  :     5  �  a  �  k  	�   �  :    �   �  �  )  �  �  ��  G   ��  �  2  	�   �  :    �  34A   	%  �    �	  �  H	  �  �
113 |   -  �    �  	 !   �   0�    	f    i  	f   �  	f   L  	f   �  	f   �   	f   u	  �      �    �   	f   ( �  !1  �  @$�  �  %�    e  &%  �  '�   �  (�  T  *1  �  +�    �  ,1  "  -	f    �  T  .�  �  0w  �  1�    M  2w  %  3	f    |  6  �  4B  h  7f   �  ;�  d
114 |   >�  �  �  ?|  !�  	`�      !�  
115 | 	h�         �  �    p	  	f    	  �  "+	  (  	p�        "  f   	x�      #X
116 |   f   	3"  �  �   �   u  �  ,  �  �   �	  �  N	  �  	�
117 |   
118 | 3    #    �  "  �  	   $MIN $MAX �	  �  �
119 |   2    �	  	   5�  0	Yr  %str ��   %num �	f   �	  ��    �|  _  �%  �  ��   �  	g"  �  	mr  #|   f   ��  �  �   �  l  �  #  �  �   \  4  �  	�  
120 | �    �  A    �    }      :  T  }	  }  �
121 |   )    �	  �  �	  �  .  c	   	  !�	  "�  #�   $v  %�  &   '�   (V  )�  *a  + |   ,�  �  GX   �  N   ��    �f   6�
122 |   08  &�  :�  &=	  ;r   	�    7:      &  �  	�q      	�  A  :   , 1  
123 |   �A  	��      	�  m  :   9 ]  �  �m  	 t      +  �m  	`t      	�  �  :   
124 |  �  �  ��  	�t      �  ��  	�t      	�  �  :   1 �  �  �  	�t      �  �  	 u        m  	@u      	�  M	  :   $ =	  �  &M	  	�u      �  /M	  	�u      'f   8�	     8�	�	  (Y   ��	   (A
125 |   ��   �  �	  ��	  �	  )�  f   	|�      9~  		��      )$  f   	��      *�  n
126 |   �   �  �  9
127 |   �  �     mf   V
128 |   �   �  + :P  Bh
129 |   �   ;�   8f   @   
130 | �.   �
131 |   �   *M  ��
132 |   H    /
133 |   +H   �
134 |   H   �  .    �  ef   �
135 |   �  �  + e  �f   �
136 |   �  �   <G  �  f    S  �H   "  H   .    	
137 |   ��   7  �   �  �H   N  .    =
138 |   uf   D             �,6
139 |   gf   �C      �       ��  <  gf   �\
140 |   g�  �P�C      M       �  i�  �h  �   >�  cWC      8       �  ?s c�  �h ,P
141 |   f   1      P      �I  �  �  ���  !	f   ���k  'r   �ذ�  *I  ��~*
142 |   +�	  ��Y   ,�	  ��;
143 |   /Y  ��O  0i  ��V  1i  ���
144 | yyn 3f   ���S  5f   ���A
145 |   7�  ����   :r  ����  =n  ��}w  >	�   �Ȱy  ?r   �аv   Ef   ����
146 |   Z�1      _   Q�1      �  ��A      �  ��A      G  ��A      �  �D4      �  ��5      J  �|@      A  U/>      �  �$6      �  �@      �  �
147 | B      @   �  t  hr   ���-   �  ��	  ���  �~  ����2      |       �  �  �	r   ��� 3      �       �  �	r   ���   �<      L       �  
148 | buf [�  ��| x=      �         �
149 |   Hm   ���
150 | yyi Im   �İ -'   �  ^�	  ���I
151 |   `�  ���t  af   ���  	�  Y  :   � 	r  i  :   � r  	�   ~  :    �  A�  ��0      (       ��  w  ��  �h   �  �d�    .i  �X �  �f   �.      [      ��  y  ��  ��w  �2�  ���  �%   ��'A   �;  �
152 |    \  ��  ��y  �  �Pt  �r   ��q  �f   ��}/      i       �  
153 | yyi �	f   ���/      T       �  �r   �H  *0      �       
154 | yyp ��   �@
155 | yyi �	f   ��  r   �	  	�    :    ;  uf   �-      �       ��  �  u0   �Xy  v,�  �P  v9f   �Lq  yf   �h.      h       
156 | yyn �f   �l  �  ^  Jr   	-      �       �2  A  J�   �X7	  J%�  �P�	  i�-      q
157 |   ]{-      ,-      �       
158 | yyn Nr   �`
159 | yyp O�  �h  �  4�   �,      Q       ��  �
160 |   4�   �X{  4%�  �P
161 | yyd 6	�   �`
162 | yys 7�  �h �  �f   �+            �Y  �  �1   �Hy  �-�  �@  �:f   ��q  �f   �X
163 | yyn �f   �`�+      �       �  f   �dU  f   �h�  f   �l
164 | yyx f   �\  �  ��  �+      %       ��  �  � �  �l �  ��)      �      �P  �	  ��  �H�)            1  i �f   �T�)      �       s �|  �`�)      �       j �f   �X�)      n       f �1  �h    +      S       i �f   �\  �  T�&      �      ��    T$|  ���  T9�  ��e  TI%  ���  T`�  ��'	  ](  �H�  h1  �P�   o1  �X �  B`  Gw&      |       �  �  G-�  �h .
165 |   >f   &      `       �S  �  >'�  �X'&      I       i ?f   �l    +�$      P      ��  �	  + �  �X  +/|  �PI  3w  �h .j  "
166 | |  h$      _       ��  �  "%�  �X  #|  �h C�  �  	$      _       ��  �  �X�	  �  �h  �   X  &        D      �      �  �  �:   
167 | 7  
168 | <  'H   
169 | U	  
170 | 
171 |   
172 | W	  �  &O   H  '|   
173 | �  G  )�   (int 
174 | �  �	  ��   �
175 |   ��   �   
176 | ^	  �   �  �1M  �   3�    4  6	�   \  7	�     8	�   �  9	�    �	  :	�   (�   ;	�   0  <	�   8j   =	�   @3  @	�   H�  A	�   P�  B	�   XF  Df  `x
177 |   Fk  h�  H�   p�
178 |   I�   t�  J�   x�
179 |   MV   ��  N]   �+   Op  ��  Q�  ��  Y�   ��  [�  ��  \�  ��   ]k  ��  ^	H   ��  _
180 | .   ��  `�   ��
181 |   b�  � �  �   )5   +  a  �   �   �  :     Y  �  �  �  �  �   �  :    �   �  �  ��  M  �  �  ��  G   ��  
182 | �  J  p   I  �   
183 | 2      *�  	d   �  -  b  .�  *  |  0�  ;  �  �!X  ]  u  @�  �  ��   �  ��   m  ��   �  ��   �  ��   �  ��    C  ��   $�  ��   (  �	�   ,o  �	�   0]  ��   4�  ��   8 �  �.   U  ��   �  ��  �  ��  �  .   	��        .   	 �         y  	�      L  H   �   	�      �  !�   	�        "	��        %�   	�      �  &�   	 �      �  '�   	$�      Q  ,�   	(�       �  \      ^	��      ++  ^	Ȱ       �  `�   h  b�   T  c	�      �  e�   6  �  :   � ~  �  ��  	 y         �  :   � �  g  ��  	 z         �  :   ! �  ,  ��  	 {      6    :   � �  ;  �  	`{        �  	�|      6  P  :   � @  "  �P  	�}      y  �P  	       G  �  :   ! �  �  �  	��      w  H  	,�      �  �   	0�      �  �   �  	а      r  &	ذ      ,A   
184 | 	S  �    �	  �  H	  �  �
185 |   -  �    �  	 !   
186 |   -0
187 | 	�    
188 | 	�    i  
189 | 	�   �  
190 | 	�   L  
191 | 	�   �  
192 | 	�   �   
193 | 	�   u	  
194 | �      
195 | �    �  
196 |  	�   ( �  
197 | !_  �  @
198 | $  �  
199 | %�    e  
200 | &S  �  
201 | '�   �  
202 | (�  T  
203 | *`  �  
204 | +�    �  
205 | ,`  "  
206 | -	�      T  
207 | .+  �  
208 | 0�  �  
209 | 1�    M  
210 | 2�  %  
211 | 3	�    �  e  �  
212 | 4q  �  .X
213 |   �   3�	  /�  ~�   �   u  �  ,  �  �   �	  �  N	  �  	�
214 |   
215 | 3    #    �  "  �  	   !MIN !MAX �	  �  �
216 |   2    �	  	   0�  0Y�	  "str ��   "num �	�   �	  ��    ��  _  �S  �  ��   �  g�	  �  m�	  �  �   	�      �  �   	�      (  �   	�      6  �   	�      R  �   	�      #M  ��
217 |   H    S  �H   �
218 |   H   .    �  �H   �
219 |   .    1G  ��
220 |   �    0  =H   �
221 |   H   �   .    4  )�   �
222 |   �    �  s�     �   A  �.   <  J   .   .   �   #p  \N  �   2�  %Z  �   [  `�   v  �   C  @�   �  �   �  �.   �    .   .   �   @   �.   �  �   �  i�   �  �   	
223 |   ��   �  �   �  e�     �  �  3 K  ��a             �A  ptr �H   �h Q  �H   Za      )       ��  ptr �H   �h�  �*  �` �
224 |   �H   <a             ��  �  �  �h 4�  ��   �`      �       �5l  v�    `      o       ��  q	`             �  �  q�   �l   l�   �_             �m  g�_             �j    g�  �h �  b�_             ��  R  b�  �h Z  V�_             ��  �  V�   �l �  M�   �_             ��  D�   �_             ��  <�  |_             ��  4�  k_             �6  +�   [_             �6�  _      <       ��  msg 4�  �h �  �L  C^      �       �     �.�  �H�  �<�   �D	b �L  �h	buf ��   �`	n �  �X	i ��   �T U  �L  ^      .       �2  7	  �.�  �h �  �L  ]            ��  (  �)�   �X�  �:  �P	b �L  �h $;  ��[      =      ��  �  �  �h}\      �       �  �  �`  7�  w�Z      �       ��  Y�Y            �  �  Y+L  �h �  <
225 | IY      �       �D  b <,L  �h $�   �X      �       ��  b  3L  �X�   =�  �P)  #�   �l 7  
226 | �W      �       ��  b -L  �h �  �L  WW      �       �  �  �/�  �X�  �:�   �T	b �L  �h 8x  ��V      �       �"  �
227 | �U      �       �Q  �  �1L  �h A  �
228 | U      �       �  �  ��  �X %\  DH  T            ��  0  D;H  �\�  F�   �d�  G�   �h�  I
229 |   �c %�  $H  �R      2      �>  0  &H  �d�  '�   �hS      �       �  -  �c  9�  ��   �L      U      �w  �
230 |   ��   �H�  ��   �P,  ��   ��	i ��   ��m  ��   ���M      #      U  d  ��   ��N            &  	b �L  �X�  ��   ��[N      o       �  �	�   �@  lO      �       	c ��   ��	n ��   ��  �Q      �       �  �   �D  �   ��   WD      ;      ��  0  �H  ���  ��   �P�  ��   �X!  ��   �@|  'ME      �  ;UF      �  P�F      ME      �       )  �  *  �� �F      =       N  	yyl H�   �D :>   �  �   �HK      t         3H  �L   ;�  D      8       �<msg �  �h  �   O     `     �a      �
231 |       >  �  �:   7  <  U	  
232 |   W	  �  int �  �	  �m   �
233 |   �m   �   ^	  �   �  �1$  �   3f    4  6	�   \  7	�     8	�   �  9	�    �	  :	�   (�   ;	�   0  <	�   8j   =	�   @3  @	�   H�  A	�   P�  B	�   XF  D=  `x
234 |   FB  h�  Hf   p�
235 |   If   t�  Jt   x�
236 |   MQ   ��  NX   �+   OG  ��  QW  ��  Y�   ��  [a  ��  \k  ��   ]B  ��  ^	H   ��  _
237 | .   ��  `f   ��
238 |   bp  � �  �   5   +  8  �   �   W  :     0  �  \  �  f  �   �  :    �   �  $  �  G   ��  �  2  A   	�  �    �	  �  H	  �  �
239 |   -  �    �  	 !   �  0	�    	f    i  	f   �  	f   L  	f   �  	f   �   	f   u	  �      �    �   	f   ( �  !  �  @$�  �  %�    e  &�  �  '�   �  (�  T  *  �  +�    �  ,  "  -	f    �  T  .�  �  0K  �  1�    M  2K  %  3	f    P  
240 |   �  4  d
241 |   >l  U  �  ef   �  �  �   	P  b�j      �      ��    b�  �X
242 | �k      g       i nf   �l  	�  Cc      �      �Z    "�  �H  3P  �@
243 | d      k      i #f   �\
244 | #d      K      �   %  �he  )�  �`   	�  c      3       ��    !�  �h   �a      n      �  !�  �h  (    :;9I8  4 :;9I  (    !I   I   :;9I  
245 |  :!;9  	I  
246 | 4 :;9I  ! I/     :;9I  & I   :!;9I  $ >  4 :;9I?<  .?:;9'I<  4 :!;9I  4 :!;9I   :!;9I    :;9   :!;9I   <  ( !~  .?:!
247 | ;9'I<  .:!;9!'I@|  .:!;9!'I@z  .?:!;9!'@|  7 I   :;9!	  !4 G:!;9  "4 :!;9I?  #>!!I:;9  $(   % :!;9I  & :!;9I  '>!I:!;9  ( :!;9I8  )4 :!;9!I?  *.?:;9!'<  +   ,.?:;9'I@|  -U  ..?:!;9'I@|  /%  0   1$ >  2 :;9  3&   4>I:;9  5:;9  6:;9  7! I/  8:;9  94 G:;9  :.?:;9'<  ;. ?:;9'I<  <.?:;9'�<  =. ?:;9I@z  >.?:;9'@|  ? :;9I  @U  A.:;9'@z  B.?:;9'@z  C.?:;9'I@|    :;9I8  4 :!;9I  (    I   :;9I   :!;9I   !I  (   	4 :!;9I  
248 | $ >  & I  .?:;9'I<  I  ! I/  4 :;9I?<  .?:!;9'I@|  .?:!;9'@|   :!;9I  . ?:!;9'I@z    :;9  4 G;9  4 :!;9!I?  7 I   :!;9I  .?:!;9!'@z     <  4 :!;9I?<  .?:;9'I<  
249 |  :!;9!    :!;9I  !(   " :!;9I  #.?:;9!'<  $.:!;9'@|  %.:!;9!'I@z  &%  '   ($ >  ) :;9  *&   +4 G;  ,>I:;9  -:;9  .>I:;9  /(   0:;9  1.?:;9'�<  2. ?:;9'I<  3   4. ?:;9'I@|  5. :;9'I@z  6.:;9'�@|  7. ?:;9'@|  8. :;9'@z  9.:;9'I@|  :U  ;.?:;9'@|  < :;9I    :;9I8   !I  $ >  (    :;9I   :!;9I  :;9   <  	.?:!;9!'@|  
250 |   I  ! I/  7 I  4 :;9!I?<   I  4 :!;9!I  4 :!;9I  %     $ >  & I   :;9  >I:;9  :;9  .?:;9'I<     .?:;9'@|   �    p   �         =   A   j   �   �      �      �   �   �   �   �   �   �       % 		$      �� tX/ �u��K+0�� tX/ �u��K80=# t	u#[;#KtX*���	u#�	���)t	ut�#-0�t/"<< �K, r J�Y40�u��������w�
251 |  g0�" t t	u#\"�%	u#��.�, �=,��:#HtX(t��	u#��,�$�Ju �u��?�1Y%�# ���7Y+�) ��t�#h��	tY(��u�t"/*��ut( X" t&��B X0 �&��H X6 � ~& J# t^�& X  ��t$ X t�3 u�! J t��& X ��t" X t	��t/<<2 X5 <" <, � J	�t X���<�u�.0utf�g%� f t X>��f/��Yhug�v� �* wX  J� t fg
252 | �=.	��	�/��<.<M�.=t��	�X	��1XtM$u�t/Y1u�=	jf2@ u$ .J0�5htt
253 | [u<t/K � � J
254 | "gv
255 | h=.t���g�*������ �$ <  t
256 |  <�t:14�J����" y� J�th�u
257 | th�	�u/
258 | t" J �- J3�/�)fJ �KxYwXtft
259 | �Y
260 | X0u�<(�	�������	���
261 | ��	.
262 | �
263 | ��J"��
264 | �
265 | uɯ�*	� #Y 6f���<J
266 | J�� .��f[ XifL��fz��\ � �X . Xl� �) � X�.��g]�x�
267 | P�CX%< .��(	.
268 | ��	�A-�u4� �ut��	]��
269 | ��uX�
270 | ��uX�
271 | �	�uX�	���
272 | ��uXtY�3Z� �utY�	Z�
273 | �	�uX��
274 | ��uXtY�)Z-�< �K�_Z	�F<	�5.9�	<��	<�
275 | �1�uX�
276 | �1�uX�
277 | �1�uX�
278 | �1�uX�
279 | �1�uX��1�tX��1�tX��1�tX��1�tX��1�tX��	�tX��%�tX�#A�i XQ �#g�m XU �#g�m XU �#g�k XS �#g�k XS �#g�a XI �#g�a XI �#g�$YtF X. tH�+�) �#v�$�tL X4 tN�1�/ ��t	�tX&���	�tX&���	�tX3�(��f	�tX3�(��f	�tX2�'��f	�tX2�'��f	�tX-�"��f	�tX-�"��f	�tX7�'�% ��t	�t.=�-�+ ��t	�t.�-'+ ��t3�}<�<�  	2�PX�&X���4 �: .* �K/ X .:k�}X� 2f4 X2 f4 J �2 .< . t 
280 | Xh���!�&�/�t�� �vt[&��'�	����
281 | fMf�\��.�	2���m. �.
282 | ��u �3 �) .L.�
283 | �A-���l�` P��{X� �	�{.�<" �	�{.<�<�  ��'f\ � �X . Xg�	21������t�
284 | �g�r��%!>/ g��u��v�Y�Y0�Y J    �   �         =   A   j   �   �   !  *  !  �   �   �   �   �   2  @  �   �   �       O  X  $ 	D      �%�<�f��fK�t	Y�t
285 | Y�t
286 |  X tYZsY�@	X
287 | �	�����<Z�
288 | �$0<K�J�-ff5 %^8ffKZ%<�!
289 | <K
290 | h��<M8
291 | f; v<# fMt/ L! � J�0.
292 | ���
293 | �yX������
294 | ���f JX XXYf JX XXY!f JX XXYf JX XXY!f JX XXYf JX XXY!f JX XXY!f JX XXYf JX XXY"f JX XX
295 | Z���������� �u� �g�t �  t= tJ �u�"'�X0�#�.
296 | i� t<J+t<g,t�/t
297 | t1tJ�t \�v�
298 | ��i�!g]�\ X#��� gX�w���\tJ�w���^�w��f	�} �X
299 | f�t��/t:J�<tY�t<$Lk�'�6X
300 | >t/	��<# - J�t<7\�(t�t*<;	i\Jwt�;
301 | ?tL	tZgt't��t�%t;<�����Y���v*t8<<_f&��w #� 	. 7 �   f 
302 | f f 8 f � J � � Xf . � � X J B � ��(t�fLhuu/t�v(�@t<�@��2Yg%tI2t' �
303 | L"tJY�+t)f?t%J4�=t%J8�>tJ	v=k���Zt" J � � X=<Z�	�#0<K�
304 | J�,ff4 $^7ffB rJ2 X	=6�
305 | �K<Z��"0<K�	J�+ff3 #^6ff K�h f< .Y� .	t	 X t	YZsY�@t X J X X�Y{�Y � � X�t X�t�(t�(t�Ju _n� 1�-t< g8tJt	�!t<u�g	<1�u�1�?t< �
306 | ��Y��	0K5�w � � XgJvtK��x�	 6= XZ��� � � Xg�D�( tD . JX . Xv XYC	����=�J>���� � � Xgot 	.	��[t X�t�(t�(t�t X�!Jw Yl� 5�	t �
307 |  t�t X J X X�JutY"t X�!Yw� 4�t^1� �wtY���7[�t�(�t1� �xtY�.���	.?u L-
308 | M��u�t.u�����tu����	�K.%�	 ��
309 | . 5fg�u
310 | �t/��
311 | <! - J�*�<�<0gu�	�K5�"��g4�u4�u4�g5�u5��	<��?��?�g1��?�������
312 | ���Y2�/t X J X X�JuU ����ZY.��1		</1�� �    \   �         =   A   j   �   �   d  d  �   �   �   �   �   �   ) 	�a      ������������)>��<>=# t	u#[�"%t	Y �(��;v	s J � t)�	t#,-�$//�'/5�%/1�'/5�#/-�'/5�'/3�$//�#/-�#t�"&t- J""t- J""t- J�%t�"&t- J�����%t��"&t- J��""&t- J��"%"-t- J"�t3 J""t3 J""t2 J""t2 J""�, X"#�2 X#	�0 H�  J t;��#"0�	#t X	u#[#�=�t�t	/3�=�	�7 % J �]��# YYSYMBOL_MAXLENGTH default_value FieldType _shortbuf _IO_lock_t strlen stderr yy_state_t yyssp yynewstate _IO_buf_end yylen yysymbol_kind_t yylex FIELD_TEXT yyval _IO_write_end yyvaluep YYSYMBOL_section_list _freeres_list YYSYMBOL_field _flags cols YYSYMBOL_TEXT YYSYMBOL_CHECKBOX YYSYMBOL_OPTIONAL yydefact YYSYMBOL_PASSWORD _markers yyvs YYSYMBOL_MAX YYSYMBOL_attribute yysyntax_error_status YYSYMBOL_35_1 YYSYMBOL_TEXTAREA yytype_int8 yylval YYSYMBOL_YYEOF yystate YYSYMBOL_DROPDOWN rows add_field_to_section GNU C17 13.3.0 -mtune=generic -march=x86-64 -g -fasynchronous-unwind-tables -fstack-protector-strong -fstack-clash-protection -fcf-protection yydefgoto YYSTYPE stdout _IO_save_end field_attrs YYSYMBOL_field_attributes _IO_codecvt malloc YYSYMBOL_YYEMPTY yyabortlab FieldName YYSYMBOL_FILE_TYPE yytranslate long long unsigned int new_sections YYSYMBOL_field_type create_section yymsg_alloc yyerrorlab FIELD_PASSWORD yyin yydestruct yypact _IO_backup_base yyr1 yypgoto FIELD_TEXTAREA fprintf _fileno required yynewbytes yykind min_length yystos _IO_read_base FIELD_CHECKBOX argc yyerrlab yyerrlab1 Section YYSYMBOL_EMAIL yystacksize yymsg YYSYMBOL_MINLENGTH cleanup_form Field yytable yyreduce yysymbol new_fields YYSYMBOL_REQUIRED YYSYMBOL_DATE yychar yycheck _mode FIELD_DROPDOWN _IO_marker yyerrstatus YYSYMBOL_SECTION _IO_read_ptr yyres exit max_value yyvsp yyformat strcmp YYSYMBOL_YYUNDEF YYSYMBOL_COLS current_section yyctx YYSYMBOL_FIELD FieldAttributes yyxbegin _IO_write_base yyreturnlab yysymbol_name long long int YYSYMBOL_field_list field_name_count section_count _IO_save_base YYSYMBOL_RADIO generate_html yytnamerr yylineno yycount yyarg yy_state_fast_t yysyntax_error _freeres_buf YYSYMBOL_section_header Form __pad5 YYSYMBOL_FORM yydefault fopen _vtable_offset yyxend yyargn argv yyptr sprintf FIELD_RADIO YYSYMBOL_DEFAULT YYSYMBOL_MIN yyacceptlab yyresult _IO_read_end max_length yysize yysrc short int yyss1 YYSYMBOL_YYerror min_value YYSYMBOL_30_ yyexhaustedlab yysize1 yyerror _IO_wide_data perror yystpcpy yyssa yybackup add_section_to_form YYENOMEM field_count YYSYMBOL_31_ yy_syntax_error_arguments yychecklim init_field_attributes YYSYMBOL_section FIELD_FILE _lock create_form _old_offset yyr2 _IO_FILE yymsgbuf YYSYMBOL_NUMBER yypcontext_expected_tokens yyss_alloc YYSYMBOL_STRING_LITERAL YYSYMBOL_YYACCEPT new_field_names yystr yyvs_alloc FIELD_NUMBER unsigned char YYSYMBOL_32_ line pattern YYSYMBOL_ROWS _IO_write_ptr yypcontext_t YYSYMBOL_form YYSYMBOL_NUMBER_LITERAL do_not_strip_quotes FIELD_EMAIL YYSYMBOL_29_ __off_t yytname strdup yywrap short unsigned int yyss memcpy main yyvsa yytoken yymsgp yyparse yytokentype current_form append _chain check_duplicate_field _flags2 YYSYMBOL_PATTERN FIELD_DATE YYARGS_MAX yyalloc _cur_column yydest yylhs yysetstate __off64_t _unused2 _IO_buf_base YYSYMBOL_IDENTIFIER yynerrs number_to_move yy_base yy_is_interactive yy_scan_string num_to_read clearerr yy_chk __uint8_t yy_ch_buf atoi yy_last_accepting_cpos yy_n_chars YY_BUFFER_STATE new_buffer yyget_in yy_flex_debug yy_create_buffer yypush_buffer_state _out_str yy_def yy_switch_to_buffer yyget_lineno getc yy_hold_char yyleng yy_try_NUL_trans ret_val yy_buffer_state __errno_location source yyget_leng stdin _line_number yy_rule_can_match_eol yy_state_type yy_get_next_buffer yyset_debug yy_get_previous_state yy_c_buf_p yy_bs_lineno yy_meta isatty yyensure_buffer_stack yyrealloc ferror flex_int16_t yy_bs_column yy_match yy_c_buf_p_offset yy_buf_size YY_CHAR yy_buffer_status after_field after_colon yypop_buffer_state yy_c yy_at_bol yyout yy_is_our_buffer yybytes yyget_debug yy_act after_section after_form yyrestart yyfree after_type yy_fill_buffer yy_init_globals flex_int32_t grow_size yytext new_size yy_scan_bytes num_to_alloc yy_bp yyget_text yy_init_buffer yy_flush_buffer yy_cp yy_is_jam yy_buffer_stack_top yy_next_state yy_buffer_stack memset yy_delete_buffer __int16_t _in_str yyset_lineno yy_ec yyset_out yy_last_accepting_state yy_find_action yy_start flex_uint8_t yy_accept yy_input_file yylex_destroy do_action yyset_in yyget_out yy_init yy_scan_buffer yy_buffer_stack_max yy_nxt oerrno yy_current_state fread __int32_t yy_did_buffer_switch_on_eof yy_buf_pos yy_load_buffer_state yy_size_t yy_fatal_error _bdebug fwrite _yybytes_len yy_amount_of_matched_text generate_html_footer generate_section_html output generate_html_header src/parser.tab.c /home/dinuka/programming-paradigms/FormLang src /usr/lib/gcc/x86_64-linux-gnu/13/include /usr/include/x86_64-linux-gnu/bits /usr/include/x86_64-linux-gnu/bits/types /usr/include parser.y stddef.h types.h struct_FILE.h stdio.h formLang.h parser.tab.h string.h stdlib.h src/lex.yy.c lexer.l stdint-intn.h stdint-uintn.h unistd.h errno.h src/html_generator.c .         �� �;�;�;�; ���;�; �5�7�;�;          ����                                ��                	     �                  ��                     P#                    �#              3     �#              I     H�             U     ��              |      $              �     ��              �    ��                �     �q            �     ��      h      �     �+      %       �      t      :       �     `t      :       �     �t             �     �t             �     �t      2             u      2           @u      :           �u      %           �u      %           �+            4    �,      Q       =    	-      �       G    �-      �       a    �.      [      p    �0      (       {   ��                �    ��             �     �             �    �             �    �             �    �             �    �             �     �             �    $�             �    (�                  y                 z                  {      "       $    `{            ,    �|            3    �}      l      :           l      A    ��      �       W    ,�             o    0�             �    �[      =      �    �V      �       �    �R      2      �    T            �    �L      U      �    _      <       �    �X      �       	     `      o          ��                    ��                *    ��                   ��                8    �              A     $�              T    ��              j    �U      �       ~    U      �       �                     �    �             �    ��             �                     �                     �    |_             �                           �             �      �                                   2                     E                     W    0�             i    &      `           �              �    p�             �    WC      8       �    1      P      �    ��             �   �l              �                     �                     �    �             �    �_             �    ذ             �    h�                 `�                 Za      )       #    WW      �       4    �             =    а             K                     ^    	$      _       j    x�             {    �_             �    <a             �    �a             �    �_             �    ]            �    w&      |       �     �              �    �&      �      �                     �    Ȱ                 �                 ^      .           �_             &                     :    C^      �       H                      W    [_             d   �              q                     �    �_             �                     �     p             �    �Y            �    Cc      �      �    |�             �                     c    D      8       �    �$      P      
313 |     �W      �                            .    �Z      �       A    8�              F    ��             �     #      &       M                     a     �              m    �C      �       r    h$      _       �    WD      ;      �    �             �    IY      �       �                     �                     �                     �    ��      0       �    k_             �    �j      �      �                         �                                  '                     :   �              F                      `    D             g                     z    c      3       �    	`             �    �)      �      �    �_             �    �a      n      �  "                   �                   �                     �    �`      �       	    @�              Scrt1.o __abi_tag crtstuff.c deregister_tm_clones __do_global_dtors_aux completed.0 __do_global_dtors_aux_fini_array_entry frame_dummy __frame_dummy_init_array_entry parser.tab.c yytranslate yytname yysymbol_name yypact yydefact yypgoto yydefgoto yytable yycheck yystos yyr1 yyr2 yypcontext_expected_tokens yystpcpy yytnamerr yy_syntax_error_arguments yysyntax_error yydestruct lex.yy.c yy_buffer_stack_top yy_buffer_stack_max yy_buffer_stack yy_hold_char yy_n_chars yy_c_buf_p yy_init yy_start yy_did_buffer_switch_on_eof yy_accept yy_ec yy_meta yy_base yy_def yy_nxt yy_chk yy_rule_can_match_eol yy_last_accepting_state yy_last_accepting_cpos yyensure_buffer_stack yy_load_buffer_state yy_get_previous_state yy_try_NUL_trans yy_get_next_buffer yy_fatal_error yy_init_buffer yy_init_globals html_generator.c __FRAME_END__ _DYNAMIC __GNU_EH_FRAME_HDR _GLOBAL_OFFSET_TABLE_ yy_switch_to_buffer yyrestart free@GLIBC_2.2.5 after_type yynerrs __libc_start_main@GLIBC_2.34 __errno_location@GLIBC_2.2.5 yyget_out _ITM_deregisterTMCloneTable stdout@GLIBC_2.2.5 ferror@GLIBC_2.2.5 isatty@GLIBC_2.2.5 fread@GLIBC_2.2.5 stdin@GLIBC_2.2.5 check_duplicate_field _edata field_names yyerror yyparse yyin _fini strlen@GLIBC_2.2.5 __stack_chk_fail@GLIBC_2.4 after_section yyget_debug yytext current_section current_form yyrealloc yy_create_buffer yylineno yy_flex_debug memset@GLIBC_2.2.5 create_form field_name_count yyget_text yyalloc yyfree yyset_lineno yy_scan_buffer init_field_attributes __data_start add_field_to_section strcmp@GLIBC_2.2.5 yyout after_colon yy_scan_string yyset_in fprintf@GLIBC_2.2.5 yy_scan_bytes __gmon_start__ yyget_lineno __dso_handle clearerr@GLIBC_2.2.5 yyget_leng memcpy@GLIBC_2.14 _IO_stdin_used yypush_buffer_state generate_section_html yychar fileno@GLIBC_2.2.5 add_section_to_form yy_delete_buffer malloc@GLIBC_2.2.5 yypop_buffer_state _end yyleng realloc@GLIBC_2.2.5 __bss_start main create_section yylex after_field yy_flush_buffer fopen@GLIBC_2.2.5 perror@GLIBC_2.2.5 atoi@GLIBC_2.2.5 yylval yyget_in generate_html sprintf@GLIBC_2.2.5 after_form exit@GLIBC_2.2.5 fwrite@GLIBC_2.2.5 __TMC_END__ _ITM_registerTMCloneTable yywrap strdup@GLIBC_2.2.5 generate_html_footer yyset_debug cleanup_form yyset_out generate_html_header __cxa_finalize@GLIBC_2.2.5 getc@GLIBC_2.2.5 yylex_destroy stderr@GLIBC_2.2.5  .symtab .strtab .shstrtab .interp .note.gnu.property .note.gnu.build-id .note.ABI-tag .gnu.hash .dynsym .dynstr .gnu.version .gnu.version_r .rela.dyn .rela.plt .init .plt.got .plt.sec .text .fini .rodata .eh_frame_hdr .eh_frame .init_array .fini_array .data.rel.ro .dynamic .data .bss .comment .debug_aranges .debug_info .debug_abbrev .debug_line .debug_str .debug_line_str .debug_rnglists                                                                                                                             #             8      8      0                              6             h      h      $                              I             �      �                                     W   ���o       �      �      4                             a             �      �                                 i             �      �      a                             q   ���o       J      J      @                            ~   ���o       �      �      P                            �             �      �      (                           �      B                   (                          �                                                           �                             �                            �             �!      �!                                   �             �!      �!      p                            �              #       #      dI                             �             �l      �l                                    �              p       p      !                              �             $�      $�      �                             �             �      �      �                             �             ��      ��                                   �             ��      ��                                   �             ��      ��      h                              
314 |             �      �      �                           �             ��      ��      �                                          �       �                                                 �      �                                         0               �      +                             '                     ?�      �                              6                     Ϡ      s0                             B                     B�      �	                             P                     �      	                             \     0               �      #                            g     0               7     u                            w                     �     I                                                    �     �      %   A                 	                      �     	                                                   �!     �                             
```

FormLang/examples/all_fields.form
```
1 | form AllFields {
2 |     section TextFields {
3 |         field text1: text required;
4 |         field text2: text optional;
5 |     }
6 |     
7 |     section EmailFields {
8 |         field email1: email required;
9 |         field email2: email optional;
10 |     }
11 |     
12 |     section PasswordFields {
13 |         field pass1: password required;
14 |         field pass2: password optional;
15 |     }
16 |     
17 |     section NumberFields {
18 |         field num1: number required;
19 |         field num2: number optional;
20 |     }
21 | } 
```

FormLang/examples/complex_form.form
```
1 | form ComplexForm {
2 |     section PersonalInfo {
3 |         field fullName: text required;
4 |         field email: email required;
5 |         field phone: number optional;
6 |         field age: number required;
7 |     }
8 |     
9 |     section Security {
10 |         field username: text required;
11 |         field password: password required;
12 |         field confirmPassword: password required;
13 |     }
14 |     
15 |     section Preferences {
16 |         field theme: text optional;
17 |         field notifications: text optional;
18 |     }
19 | } 
```

FormLang/examples/edge_cases.form
```
1 | form EdgeCases {
2 |   section EmptySection {
3 |   }
4 | 
5 |   section SingleField {
6 |     field test: text required;
7 |   }
8 | 
9 |   section MultipleFields {
10 |     field name: text required;
11 |     field email: email required;
12 |     field phone: text optional;
13 |   }
14 | 
15 |   section MixedTypes {
16 |     field text: text required;
17 |     field email: email optional;
18 |     field password: password required;
19 |   }
20 | 
21 |   section NoAttributes {
22 |     field test: text;
23 |   }
24 | 
25 |   section AllOptional {
26 |     field test1: text optional;
27 |     field test2: email optional;
28 |     field test3: password optional;
29 |   }
30 | } 
```

FormLang/examples/empty_section.form
```
1 | form EmptySection {
2 |     section UserInfo {
3 |     }
4 |     
5 |     section Contact {
6 |         field email: email required;
7 |         field phone: number optional;
8 |     }
9 | } 
```

FormLang/examples/invalid.form
```
1 | form Invalid {
2 |   section Test {
3 |     field test: invalid required;
4 |     field test2: text
5 |   }
6 | }
```

FormLang/examples/long_field_names.form
```
1 | form LongFieldNames {
2 |     section UserProfile {
3 |         field firstName: text required;
4 |         field middleName: text optional;
5 |         field lastName: text required;
6 |         field preferredName: text optional;
7 |         field dateOfBirth: text required;
8 |         field primaryEmailAddress: email required;
9 |         field secondaryEmailAddress: email optional;
10 |         field mobilePhoneNumber: number required;
11 |         field homePhoneNumber: number optional;
12 |         field workPhoneNumber: number optional;
13 |     }
14 | } 
```

FormLang/examples/mixed_attributes.form
```
1 | form MixedAttributes {
2 |     section User {
3 |         field name: text required;
4 |         field nickname: text optional;
5 |         field email: email required;
6 |         field secondaryEmail: email optional;
7 |         field password: password required;
8 |         field age: number optional;
9 |         field phone: number required;
10 |     }
11 | } 
```

FormLang/examples/multiple_empty_sections.form
```
1 | form MultipleEmptySections {
2 |     section Personal {
3 |     }
4 |     
5 |     section Contact {
6 |     }
7 |     
8 |     section Preferences {
9 |     }
10 |     
11 |     section Security {
12 |         field password: password required;
13 |     }
14 | } 
```

FormLang/examples/registration.form
```
1 | form Registration {
2 |     section Personal {
3 |         field name: text required;
4 |         field email: email required;
5 |         field phone: number optional;
6 |     }
7 |     
8 |     section Account {
9 |         field username: text required;
10 |         field password: password required;
11 |     }
12 | } 
```

FormLang/examples/single_field_sections.form
```
1 | form SingleFieldSections {
2 |     section Name {
3 |         field fullName: text required;
4 |     }
5 |     
6 |     section Email {
7 |         field email: email required;
8 |     }
9 |     
10 |     section Password {
11 |         field password: password required;
12 |     }
13 |     
14 |     section Phone {
15 |         field phone: number optional;
16 |     }
17 | } 
```

FormLang/examples/single_section.form
```
1 | form SingleSection {
2 |     section UserDetails {
3 |         field name: text required;
4 |         field email: email required;
5 |         field password: password required;
6 |         field age: number optional;
7 |     }
8 | } 
```

FormLang/examples/test_milestone4.form
```
1 | form TestMilestone4 {
2 |     section UserDetails {
3 |         field username: text minLength 5 maxLength 20 pattern "^[a-zA-Z0-9_]+$" required;
4 |         field password: password minLength 8 required;
5 |         field email: email required;
6 |         field age: number min 18 max 99 required;
7 |         field bio: textarea rows 5 cols 40 optional;
8 |         field birth_date: date required;
9 |         field newsletter: checkbox default 1;
10 |         field gender: radio required;
11 |         field country: dropdown required;
12 |         field avatar: file optional;
13 |     }
14 | } 
```

FormLang/output/complex_form.html
```
1 | <!DOCTYPE html>
2 | <html>
3 | <head>
4 | <title>ComplexForm</title>
5 | <style>
6 | body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }
7 | form { background: #f5f5f5; padding: 20px; border-radius: 5px; }
8 | section { margin-bottom: 20px; padding: 15px; background: white; border-radius: 5px; }
9 | h2 { color: #333; margin-top: 0; }
10 | label { display: block; margin-bottom: 5px; }
11 | input { width: 100%; padding: 8px; margin-bottom: 10px; border: 1px solid #ddd; border-radius: 4px; }
12 | input[type=submit] { background: #4CAF50; color: white; border: none; padding: 10px 20px; cursor: pointer; width: auto; }
13 | input[type=submit]:hover { background: #45a049; }
14 | </style>
15 | </head>
16 | <body>
17 | <form>
18 | <section>
19 | <h2>PersonalInfo</h2>
20 | <label for="fullName">fullName *</label>
21 | <input type="text" id="fullName" name="fullName" required>
22 | <label for="email">email *</label>
23 | <input type="email" id="email" name="email" required>
24 | <label for="phone">phone</label>
25 | <input type="number" id="phone" name="phone">
26 | <label for="age">age *</label>
27 | <input type="number" id="age" name="age" required>
28 | </section>
29 | <section>
30 | <h2>Security</h2>
31 | <label for="username">username *</label>
32 | <input type="text" id="username" name="username" required>
33 | <label for="password">password *</label>
34 | <input type="password" id="password" name="password" required>
35 | <label for="confirmPassword">confirmPassword *</label>
36 | <input type="password" id="confirmPassword" name="confirmPassword" required>
37 | </section>
38 | <section>
39 | <h2>Preferences</h2>
40 | <label for="theme">theme</label>
41 | <input type="text" id="theme" name="theme">
42 | <label for="notifications">notifications</label>
43 | <input type="text" id="notifications" name="notifications">
44 | </section>
45 | <input type="submit" value="Submit">
46 | </form>
47 | </body>
48 | </html>
```

FormLang/output/empty_section.html
```
1 | <!DOCTYPE html>
2 | <html>
3 | <head>
4 | <title>EmptySection</title>
5 | <style>
6 | body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }
7 | form { background: #f5f5f5; padding: 20px; border-radius: 5px; }
8 | section { margin-bottom: 20px; padding: 15px; background: white; border-radius: 5px; }
9 | h2 { color: #333; margin-top: 0; }
10 | label { display: block; margin-bottom: 5px; }
11 | input { width: 100%; padding: 8px; margin-bottom: 10px; border: 1px solid #ddd; border-radius: 4px; }
12 | input[type=submit] { background: #4CAF50; color: white; border: none; padding: 10px 20px; cursor: pointer; width: auto; }
13 | input[type=submit]:hover { background: #45a049; }
14 | </style>
15 | </head>
16 | <body>
17 | <form>
18 | <section>
19 | <h2>UserInfo</h2>
20 | </section>
21 | <section>
22 | <h2>Contact</h2>
23 | <label for="email">email *</label>
24 | <input type="email" id="email" name="email" required>
25 | <label for="phone">phone</label>
26 | <input type="number" id="phone" name="phone">
27 | </section>
28 | <input type="submit" value="Submit">
29 | </form>
30 | </body>
31 | </html>
```

FormLang/output/extended.html
```
```

FormLang/output/long_field_names.html
```
1 | <!DOCTYPE html>
2 | <html>
3 | <head>
4 | <title>LongFieldNames</title>
5 | <style>
6 | body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }
7 | form { background: #f5f5f5; padding: 20px; border-radius: 5px; }
8 | section { margin-bottom: 20px; padding: 15px; background: white; border-radius: 5px; }
9 | h2 { color: #333; margin-top: 0; }
10 | label { display: block; margin-bottom: 5px; }
11 | input { width: 100%; padding: 8px; margin-bottom: 10px; border: 1px solid #ddd; border-radius: 4px; }
12 | input[type=submit] { background: #4CAF50; color: white; border: none; padding: 10px 20px; cursor: pointer; width: auto; }
13 | input[type=submit]:hover { background: #45a049; }
14 | </style>
15 | </head>
16 | <body>
17 | <form>
18 | <section>
19 | <h2>UserProfile</h2>
20 | <label for="firstName">firstName *</label>
21 | <input type="text" id="firstName" name="firstName" required>
22 | <label for="middleName">middleName</label>
23 | <input type="text" id="middleName" name="middleName">
24 | <label for="lastName">lastName *</label>
25 | <input type="text" id="lastName" name="lastName" required>
26 | <label for="preferredName">preferredName</label>
27 | <input type="text" id="preferredName" name="preferredName">
28 | <label for="dateOfBirth">dateOfBirth *</label>
29 | <input type="text" id="dateOfBirth" name="dateOfBirth" required>
30 | <label for="primaryEmailAddress">primaryEmailAddress *</label>
31 | <input type="email" id="primaryEmailAddress" name="primaryEmailAddress" required>
32 | <label for="secondaryEmailAddress">secondaryEmailAddress</label>
33 | <input type="email" id="secondaryEmailAddress" name="secondaryEmailAddress">
34 | <label for="mobilePhoneNumber">mobilePhoneNumber *</label>
35 | <input type="number" id="mobilePhoneNumber" name="mobilePhoneNumber" required>
36 | <label for="homePhoneNumber">homePhoneNumber</label>
37 | <input type="number" id="homePhoneNumber" name="homePhoneNumber">
38 | <label for="workPhoneNumber">workPhoneNumber</label>
39 | <input type="number" id="workPhoneNumber" name="workPhoneNumber">
40 | </section>
41 | <input type="submit" value="Submit">
42 | </form>
43 | </body>
44 | </html>
```

FormLang/output/mixed_attributes.html
```
1 | <!DOCTYPE html>
2 | <html>
3 | <head>
4 | <title>MixedAttributes</title>
5 | <style>
6 | body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }
7 | form { background: #f5f5f5; padding: 20px; border-radius: 5px; }
8 | section { margin-bottom: 20px; padding: 15px; background: white; border-radius: 5px; }
9 | h2 { color: #333; margin-top: 0; }
10 | label { display: block; margin-bottom: 5px; }
11 | input { width: 100%; padding: 8px; margin-bottom: 10px; border: 1px solid #ddd; border-radius: 4px; }
12 | input[type=submit] { background: #4CAF50; color: white; border: none; padding: 10px 20px; cursor: pointer; width: auto; }
13 | input[type=submit]:hover { background: #45a049; }
14 | </style>
15 | </head>
16 | <body>
17 | <form>
18 | <section>
19 | <h2>User</h2>
20 | <label for="name">name *</label>
21 | <input type="text" id="name" name="name" required>
22 | <label for="nickname">nickname</label>
23 | <input type="text" id="nickname" name="nickname">
24 | <label for="email">email *</label>
25 | <input type="email" id="email" name="email" required>
26 | <label for="secondaryEmail">secondaryEmail</label>
27 | <input type="email" id="secondaryEmail" name="secondaryEmail">
28 | <label for="password">password *</label>
29 | <input type="password" id="password" name="password" required>
30 | <label for="age">age</label>
31 | <input type="number" id="age" name="age">
32 | <label for="phone">phone *</label>
33 | <input type="number" id="phone" name="phone" required>
34 | </section>
35 | <input type="submit" value="Submit">
36 | </form>
37 | </body>
38 | </html>
```

FormLang/output/multiple_empty_sections.html
```
1 | <!DOCTYPE html>
2 | <html>
3 | <head>
4 | <title>MultipleEmptySections</title>
5 | <style>
6 | body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }
7 | form { background: #f5f5f5; padding: 20px; border-radius: 5px; }
8 | section { margin-bottom: 20px; padding: 15px; background: white; border-radius: 5px; }
9 | h2 { color: #333; margin-top: 0; }
10 | label { display: block; margin-bottom: 5px; }
11 | input { width: 100%; padding: 8px; margin-bottom: 10px; border: 1px solid #ddd; border-radius: 4px; }
12 | input[type=submit] { background: #4CAF50; color: white; border: none; padding: 10px 20px; cursor: pointer; width: auto; }
13 | input[type=submit]:hover { background: #45a049; }
14 | </style>
15 | </head>
16 | <body>
17 | <form>
18 | <section>
19 | <h2>Personal</h2>
20 | </section>
21 | <section>
22 | <h2>Contact</h2>
23 | </section>
24 | <section>
25 | <h2>Preferences</h2>
26 | </section>
27 | <section>
28 | <h2>Security</h2>
29 | <label for="password">password *</label>
30 | <input type="password" id="password" name="password" required>
31 | </section>
32 | <input type="submit" value="Submit">
33 | </form>
34 | </body>
35 | </html>
```

FormLang/output/single_field_sections.html
```
1 | <!DOCTYPE html>
2 | <html>
3 | <head>
4 | <title>SingleFieldSections</title>
5 | <style>
6 | body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }
7 | form { background: #f5f5f5; padding: 20px; border-radius: 5px; }
8 | section { margin-bottom: 20px; padding: 15px; background: white; border-radius: 5px; }
9 | h2 { color: #333; margin-top: 0; }
10 | label { display: block; margin-bottom: 5px; }
11 | input { width: 100%; padding: 8px; margin-bottom: 10px; border: 1px solid #ddd; border-radius: 4px; }
12 | input[type=submit] { background: #4CAF50; color: white; border: none; padding: 10px 20px; cursor: pointer; width: auto; }
13 | input[type=submit]:hover { background: #45a049; }
14 | </style>
15 | </head>
16 | <body>
17 | <form>
18 | <section>
19 | <h2>Name</h2>
20 | <label for="fullName">fullName *</label>
21 | <input type="text" id="fullName" name="fullName" required>
22 | </section>
23 | <section>
24 | <h2>Email</h2>
25 | <label for="email">email *</label>
26 | <input type="email" id="email" name="email" required>
27 | </section>
28 | <section>
29 | <h2>Password</h2>
30 | <label for="password">password *</label>
31 | <input type="password" id="password" name="password" required>
32 | </section>
33 | <section>
34 | <h2>Phone</h2>
35 | <label for="phone">phone</label>
36 | <input type="number" id="phone" name="phone">
37 | </section>
38 | <input type="submit" value="Submit">
39 | </form>
40 | </body>
41 | </html>
```

FormLang/output/single_section.html
```
1 | <!DOCTYPE html>
2 | <html>
3 | <head>
4 | <title>SingleSection</title>
5 | <style>
6 | body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }
7 | form { background: #f5f5f5; padding: 20px; border-radius: 5px; }
8 | section { margin-bottom: 20px; padding: 15px; background: white; border-radius: 5px; }
9 | h2 { color: #333; margin-top: 0; }
10 | label { display: block; margin-bottom: 5px; }
11 | input { width: 100%; padding: 8px; margin-bottom: 10px; border: 1px solid #ddd; border-radius: 4px; }
12 | input[type=submit] { background: #4CAF50; color: white; border: none; padding: 10px 20px; cursor: pointer; width: auto; }
13 | input[type=submit]:hover { background: #45a049; }
14 | </style>
15 | </head>
16 | <body>
17 | <form>
18 | <section>
19 | <h2>UserDetails</h2>
20 | <label for="name">name *</label>
21 | <input type="text" id="name" name="name" required>
22 | <label for="email">email *</label>
23 | <input type="email" id="email" name="email" required>
24 | <label for="password">password *</label>
25 | <input type="password" id="password" name="password" required>
26 | <label for="age">age</label>
27 | <input type="number" id="age" name="age">
28 | </section>
29 | <input type="submit" value="Submit">
30 | </form>
31 | </body>
32 | </html>
```

FormLang/output/test_milestone4.html
```
```

FormLang/src/Makefile
```
1 | CC = gcc
2 | CFLAGS = -Wall -g
3 | FLEX = flex
4 | BISON = bison
5 | 
6 | TARGET = formLang
7 | 
8 | LEX_SRC = lexer.l
9 | YACC_SRC = parser.y
10 | C_SRC = html_generator.c
11 | 
12 | LEX_C = lex.yy.c
13 | YACC_C = y.tab.c
14 | YACC_H = y.tab.h
15 | OBJS = $(LEX_C:.c=.o) $(YACC_C:.c=.o) $(C_SRC:.c=.o)
16 | 
17 | all: $(TARGET)
18 | 
19 | $(TARGET): $(LEX_C) $(YACC_C) $(C_SRC)
20 | 	$(CC) $(CFLAGS) -o $@ $^ -lfl
21 | 
22 | $(YACC_C) $(YACC_H): $(YACC_SRC)
23 | 	$(BISON) -d -y $<
24 | 
25 | $(LEX_C): $(LEX_SRC) $(YACC_H)
26 | 	$(FLEX) $<
27 | 
28 | clean:
29 | 	rm -f $(TARGET) $(LEX_C) $(YACC_C) $(YACC_H) *.o
30 | 
31 | .PHONY: all clean
```

FormLang/src/formLang.h
```
1 | #ifndef FORMLANG_H
2 | #define FORMLANG_H
3 | 
4 | #include <stdio.h>
5 | #include <stdlib.h>
6 | #include <string.h>
7 | 
8 | // Field type definitions
9 | typedef enum {
10 |     FIELD_TEXT,
11 |     FIELD_EMAIL,
12 |     FIELD_PASSWORD,
13 |     FIELD_NUMBER,
14 |     FIELD_TEXTAREA,
15 |     FIELD_DATE,
16 |     FIELD_CHECKBOX,
17 |     FIELD_DROPDOWN,
18 |     FIELD_RADIO,
19 |     FIELD_FILE
20 | } FieldType;
21 | 
22 | // Field attribute structure
23 | typedef struct {
24 |     int min_length;
25 |     int max_length;
26 |     int min_value;
27 |     int max_value;
28 |     int rows;
29 |     int cols;
30 |     char* pattern;
31 |     char* default_value;
32 |     int required;
33 | } FieldAttributes;
34 | 
35 | // Structure definitions
36 | typedef struct Field {
37 |     char *name;
38 |     FieldType type;
39 |     FieldAttributes attributes;
40 | } Field;
41 | 
42 | typedef struct Section {
43 |     char *name;
44 |     Field *fields;
45 |     int field_count;
46 | } Section;
47 | 
48 | typedef struct Form {
49 |     char *name;
50 |     Section **sections;
51 |     int section_count;
52 | } Form;
53 | 
54 | // External declarations
55 | extern int yylineno;
56 | extern int yylex(void);
57 | extern int yyparse(void);
58 | extern void yyerror(const char *s);
59 | extern FILE* yyin;
60 | 
61 | // Global variables
62 | extern Form *current_form;
63 | extern Section *current_section;
64 | 
65 | // Function declarations
66 | void generate_html(FILE* output);
67 | void generate_html_header(FILE* output);
68 | void generate_html_footer(FILE* output);
69 | void generate_section_html(FILE* output, Section* section);
70 | 
71 | // Helper functions
72 | Form* create_form(const char* name);
73 | Section* create_section(const char* name);
74 | void add_section_to_form(Form* form, Section* section);
75 | void add_field_to_section(Section* section, const char* name, FieldType type, FieldAttributes* attrs);
76 | void cleanup_form(Form* form);
77 | 
78 | #endif /* FORMLANG_H */
```

FormLang/src/html_generator.c
```
1 | #include <stdio.h>
2 | #include <stdlib.h>
3 | #include <string.h>
4 | #include "formLang.h"
5 | 
6 | void generate_html_header(FILE* output) {
7 |     fprintf(output, "<!DOCTYPE html>\n<html>\n<head>\n");
8 |     fprintf(output, "<style>\n");
9 |     fprintf(output, "body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }\n");
10 |     fprintf(output, "form { background: #f5f5f5; padding: 20px; border-radius: 5px; }\n");
11 |     fprintf(output, "section { margin-bottom: 20px; padding: 15px; background: white; border-radius: 5px; }\n");
12 |     fprintf(output, "h2 { color: #333; margin-top: 0; }\n");
13 |     fprintf(output, "label { display: block; margin-bottom: 5px; }\n");
14 |     fprintf(output, "input, textarea, select { width: 100%%; padding: 8px; margin-bottom: 10px; border: 1px solid #ddd; border-radius: 4px; }\n");
15 |     fprintf(output, "input[type=submit] { background: #4CAF50; color: white; border: none; padding: 10px 20px; cursor: pointer; width: auto; }\n");
16 |     fprintf(output, "input[type=submit]:hover { background: #45a049; }\n");
17 |     fprintf(output, "</style>\n</head>\n<body>\n");
18 | }
19 | 
20 | void generate_html_footer(FILE* output) {
21 |     fprintf(output, "</body>\n</html>\n");
22 | }
23 | 
24 | void generate_section_html(FILE* output, Section* section) {
25 |     fprintf(stderr, "Starting section generation\n");
26 |     if (!section || !output) {
27 |         fprintf(stderr, "Null section or output\n");
28 |         return;
29 |     }
30 | 
31 |     fprintf(output, "<section>\n");
32 |     fprintf(output, "<h2>%s</h2>\n", section->name);
33 | 
34 |     fprintf(stderr, "Processing %d fields\n", section->field_count);
35 |     for (int i = 0; i < section->field_count; i++) {
36 |         fprintf(stderr, "Generating field %d\n", i);
37 |         Field* field = &section->fields[i];
38 |         fprintf(output, "<label for=\"%s\">%s%s</label>\n", 
39 |                field->name, field->name, field->attributes.required ? " *" : "");
40 | 
41 |         const char* type = "text";
42 |         switch (field->type) {
43 |             case FIELD_TEXT: type = "text"; break;
44 |             case FIELD_EMAIL: type = "email"; break;
45 |             case FIELD_PASSWORD: type = "password"; break;
46 |             case FIELD_NUMBER: type = "number"; break;
47 |             case FIELD_TEXTAREA: type = "textarea"; break;
48 |             case FIELD_DATE: type = "date"; break;
49 |             case FIELD_CHECKBOX: type = "checkbox"; break;
50 |             case FIELD_DROPDOWN: type = "select"; break;
51 |             case FIELD_RADIO: type = "radio"; break;
52 |             case FIELD_FILE: type = "file"; break;
53 |         }
54 | 
55 |         if (field->type == FIELD_TEXTAREA) {
56 |             fprintf(output, "<textarea id=\"%s\" name=\"%s\"", field->name, field->name);
57 |             if (field->attributes.rows > 0) fprintf(output, " rows=\"%d\"", field->attributes.rows);
58 |             if (field->attributes.cols > 0) fprintf(output, " cols=\"%d\"", field->attributes.cols);
59 |             if (field->attributes.required) fprintf(output, " required");
60 |             fprintf(output, "></textarea>\n");
61 |         } else if (field->type == FIELD_DROPDOWN) {
62 |             fprintf(output, "<select id=\"%s\" name=\"%s\"", field->name, field->name);
63 |             if (field->attributes.required) fprintf(output, " required");
64 |             fprintf(output, ">\n");
65 |             fprintf(output, "  <option value=\"\">Select an option</option>\n");
66 |             fprintf(output, "  <option value=\"option1\">Option 1</option>\n");
67 |             fprintf(output, "  <option value=\"option2\">Option 2</option>\n");
68 |             fprintf(output, "</select>\n");
69 |         } else if (field->type == FIELD_RADIO) {
70 |             fprintf(output, "<div class=\"radio-group\">\n");
71 |             fprintf(output, "  <input type=\"radio\" id=\"%s_1\" name=\"%s\" value=\"option1\"", field->name, field->name);
72 |             if (field->attributes.required) fprintf(output, " required");
73 |             fprintf(output, ">\n");
74 |             fprintf(output, "  <label for=\"%s_1\">Option 1</label><br>\n", field->name);
75 |             fprintf(output, "  <input type=\"radio\" id=\"%s_2\" name=\"%s\" value=\"option2\"", field->name, field->name);
76 |             if (field->attributes.required) fprintf(output, " required");
77 |             fprintf(output, ">\n");
78 |             fprintf(output, "  <label for=\"%s_2\">Option 2</label>\n", field->name);
79 |             fprintf(output, "</div>\n");
80 |         } else {
81 |             fprintf(output, "<input type=\"%s\" id=\"%s\" name=\"%s\"", type, field->name, field->name);
82 |             if (field->attributes.required) fprintf(output, " required");
83 |             if (field->attributes.min_length > 0) fprintf(output, " minlength=\"%d\"", field->attributes.min_length);
84 |             if (field->attributes.max_length > 0) fprintf(output, " maxlength=\"%d\"", field->attributes.max_length);
85 |             if (field->attributes.min_value > 0) fprintf(output, " min=\"%d\"", field->attributes.min_value);
86 |             if (field->attributes.max_value > 0) fprintf(output, " max=\"%d\"", field->attributes.max_value);
87 |             if (field->attributes.pattern) fprintf(output, " pattern=\"%s\"", field->attributes.pattern);
88 |             if (field->attributes.default_value) fprintf(output, " value=\"%s\"", field->attributes.default_value);
89 |             fprintf(output, ">\n");
90 |         }
91 |         fprintf(stderr, "Field %d generated successfully\n", i);
92 |     }
93 | 
94 |     fprintf(output, "</section>\n");
95 |     fprintf(stderr, "Section generation complete\n");
96 | }
97 | 
98 | void generate_html(FILE* output) {
99 |     fprintf(stderr, "Starting HTML generation\n");
100 |     if (!current_form || !output) {
101 |         fprintf(stderr, "Null form or output\n");
102 |         return;
103 |     }
104 | 
105 |     fprintf(stderr, "Generating header\n");
106 |     generate_html_header(output);
107 |     fprintf(output, "<form>\n");
108 | 
109 |     fprintf(stderr, "Processing %d sections\n", current_form->section_count);
110 |     for (int i = 0; i < current_form->section_count; i++) {
111 |         fprintf(stderr, "Generating section %d\n", i);
112 |         generate_section_html(output, current_form->sections[i]);
113 |     }
114 | 
115 |     fprintf(output, "<input type=\"submit\" value=\"Submit\">\n");
116 |     fprintf(output, "</form>\n");
117 |     generate_html_footer(output);
118 |     fprintf(stderr, "HTML generation complete\n");
119 | }
```

FormLang/src/lex.yy.c
```
1 | #line 2 "src/lex.yy.c"
2 | 
3 | #line 4 "src/lex.yy.c"
4 | 
5 | #define  YY_INT_ALIGNED short int
6 | 
7 | /* A lexical scanner generated by flex */
8 | 
9 | #define FLEX_SCANNER
10 | #define YY_FLEX_MAJOR_VERSION 2
11 | #define YY_FLEX_MINOR_VERSION 6
12 | #define YY_FLEX_SUBMINOR_VERSION 4
13 | #if YY_FLEX_SUBMINOR_VERSION > 0
14 | #define FLEX_BETA
15 | #endif
16 | 
17 | /* First, we deal with  platform-specific or compiler-specific issues. */
18 | 
19 | /* begin standard C headers. */
20 | #include <stdio.h>
21 | #include <string.h>
22 | #include <errno.h>
23 | #include <stdlib.h>
24 | 
25 | /* end standard C headers. */
26 | 
27 | /* flex integer type definitions */
28 | 
29 | #ifndef FLEXINT_H
30 | #define FLEXINT_H
31 | 
32 | /* C99 systems have <inttypes.h>. Non-C99 systems may or may not. */
33 | 
34 | #if defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
35 | 
36 | /* C99 says to define __STDC_LIMIT_MACROS before including stdint.h,
37 |  * if you want the limit (max/min) macros for int types. 
38 |  */
39 | #ifndef __STDC_LIMIT_MACROS
40 | #define __STDC_LIMIT_MACROS 1
41 | #endif
42 | 
43 | #include <inttypes.h>
44 | typedef int8_t flex_int8_t;
45 | typedef uint8_t flex_uint8_t;
46 | typedef int16_t flex_int16_t;
47 | typedef uint16_t flex_uint16_t;
48 | typedef int32_t flex_int32_t;
49 | typedef uint32_t flex_uint32_t;
50 | #else
51 | typedef signed char flex_int8_t;
52 | typedef short int flex_int16_t;
53 | typedef int flex_int32_t;
54 | typedef unsigned char flex_uint8_t; 
55 | typedef unsigned short int flex_uint16_t;
56 | typedef unsigned int flex_uint32_t;
57 | 
58 | /* Limits of integral types. */
59 | #ifndef INT8_MIN
60 | #define INT8_MIN               (-128)
61 | #endif
62 | #ifndef INT16_MIN
63 | #define INT16_MIN              (-32767-1)
64 | #endif
65 | #ifndef INT32_MIN
66 | #define INT32_MIN              (-2147483647-1)
67 | #endif
68 | #ifndef INT8_MAX
69 | #define INT8_MAX               (127)
70 | #endif
71 | #ifndef INT16_MAX
72 | #define INT16_MAX              (32767)
73 | #endif
74 | #ifndef INT32_MAX
75 | #define INT32_MAX              (2147483647)
76 | #endif
77 | #ifndef UINT8_MAX
78 | #define UINT8_MAX              (255U)
79 | #endif
80 | #ifndef UINT16_MAX
81 | #define UINT16_MAX             (65535U)
82 | #endif
83 | #ifndef UINT32_MAX
84 | #define UINT32_MAX             (4294967295U)
85 | #endif
86 | 
87 | #ifndef SIZE_MAX
88 | #define SIZE_MAX               (~(size_t)0)
89 | #endif
90 | 
91 | #endif /* ! C99 */
92 | 
93 | #endif /* ! FLEXINT_H */
94 | 
95 | /* begin standard C++ headers. */
96 | 
97 | /* TODO: this is always defined, so inline it */
98 | #define yyconst const
99 | 
100 | #if defined(__GNUC__) && __GNUC__ >= 3
101 | #define yynoreturn __attribute__((__noreturn__))
102 | #else
103 | #define yynoreturn
104 | #endif
105 | 
106 | /* Returned upon end-of-file. */
107 | #define YY_NULL 0
108 | 
109 | /* Promotes a possibly negative, possibly signed char to an
110 |  *   integer in range [0..255] for use as an array index.
111 |  */
112 | #define YY_SC_TO_UI(c) ((YY_CHAR) (c))
113 | 
114 | /* Enter a start condition.  This macro really ought to take a parameter,
115 |  * but we do it the disgusting crufty way forced on us by the ()-less
116 |  * definition of BEGIN.
117 |  */
118 | #define BEGIN (yy_start) = 1 + 2 *
119 | /* Translate the current start state into a value that can be later handed
120 |  * to BEGIN to return to the state.  The YYSTATE alias is for lex
121 |  * compatibility.
122 |  */
123 | #define YY_START (((yy_start) - 1) / 2)
124 | #define YYSTATE YY_START
125 | /* Action number for EOF rule of a given start state. */
126 | #define YY_STATE_EOF(state) (YY_END_OF_BUFFER + state + 1)
127 | /* Special action meaning "start processing a new file". */
128 | #define YY_NEW_FILE yyrestart( yyin  )
129 | #define YY_END_OF_BUFFER_CHAR 0
130 | 
131 | /* Size of default input buffer. */
132 | #ifndef YY_BUF_SIZE
133 | #ifdef __ia64__
134 | /* On IA-64, the buffer size is 16k, not 8k.
135 |  * Moreover, YY_BUF_SIZE is 2*YY_READ_BUF_SIZE in the general case.
136 |  * Ditto for the __ia64__ case accordingly.
137 |  */
138 | #define YY_BUF_SIZE 32768
139 | #else
140 | #define YY_BUF_SIZE 16384
141 | #endif /* __ia64__ */
142 | #endif
143 | 
144 | /* The state buf must be large enough to hold one state per character in the main buffer.
145 |  */
146 | #define YY_STATE_BUF_SIZE   ((YY_BUF_SIZE + 2) * sizeof(yy_state_type))
147 | 
148 | #ifndef YY_TYPEDEF_YY_BUFFER_STATE
149 | #define YY_TYPEDEF_YY_BUFFER_STATE
150 | typedef struct yy_buffer_state *YY_BUFFER_STATE;
151 | #endif
152 | 
153 | #ifndef YY_TYPEDEF_YY_SIZE_T
154 | #define YY_TYPEDEF_YY_SIZE_T
155 | typedef size_t yy_size_t;
156 | #endif
157 | 
158 | extern int yyleng;
159 | 
160 | extern FILE *yyin, *yyout;
161 | 
162 | #define EOB_ACT_CONTINUE_SCAN 0
163 | #define EOB_ACT_END_OF_FILE 1
164 | #define EOB_ACT_LAST_MATCH 2
165 |     
166 |     /* Note: We specifically omit the test for yy_rule_can_match_eol because it requires
167 |      *       access to the local variable yy_act. Since yyless() is a macro, it would break
168 |      *       existing scanners that call yyless() from OUTSIDE yylex.
169 |      *       One obvious solution it to make yy_act a global. I tried that, and saw
170 |      *       a 5% performance hit in a non-yylineno scanner, because yy_act is
171 |      *       normally declared as a register variable-- so it is not worth it.
172 |      */
173 |     #define  YY_LESS_LINENO(n) \
174 |             do { \
175 |                 int yyl;\
176 |                 for ( yyl = n; yyl < yyleng; ++yyl )\
177 |                     if ( yytext[yyl] == '\n' )\
178 |                         --yylineno;\
179 |             }while(0)
180 |     #define YY_LINENO_REWIND_TO(dst) \
181 |             do {\
182 |                 const char *p;\
183 |                 for ( p = yy_cp-1; p >= (dst); --p)\
184 |                     if ( *p == '\n' )\
185 |                         --yylineno;\
186 |             }while(0)
187 |     
188 | /* Return all but the first "n" matched characters back to the input stream. */
189 | #define yyless(n) \
190 | 	do \
191 | 		{ \
192 | 		/* Undo effects of setting up yytext. */ \
193 |         int yyless_macro_arg = (n); \
194 |         YY_LESS_LINENO(yyless_macro_arg);\
195 | 		*yy_cp = (yy_hold_char); \
196 | 		YY_RESTORE_YY_MORE_OFFSET \
197 | 		(yy_c_buf_p) = yy_cp = yy_bp + yyless_macro_arg - YY_MORE_ADJ; \
198 | 		YY_DO_BEFORE_ACTION; /* set up yytext again */ \
199 | 		} \
200 | 	while ( 0 )
201 | #define unput(c) yyunput( c, (yytext_ptr)  )
202 | 
203 | #ifndef YY_STRUCT_YY_BUFFER_STATE
204 | #define YY_STRUCT_YY_BUFFER_STATE
205 | struct yy_buffer_state
206 | 	{
207 | 	FILE *yy_input_file;
208 | 
209 | 	char *yy_ch_buf;		/* input buffer */
210 | 	char *yy_buf_pos;		/* current position in input buffer */
211 | 
212 | 	/* Size of input buffer in bytes, not including room for EOB
213 | 	 * characters.
214 | 	 */
215 | 	int yy_buf_size;
216 | 
217 | 	/* Number of characters read into yy_ch_buf, not including EOB
218 | 	 * characters.
219 | 	 */
220 | 	int yy_n_chars;
221 | 
222 | 	/* Whether we "own" the buffer - i.e., we know we created it,
223 | 	 * and can realloc() it to grow it, and should free() it to
224 | 	 * delete it.
225 | 	 */
226 | 	int yy_is_our_buffer;
227 | 
228 | 	/* Whether this is an "interactive" input source; if so, and
229 | 	 * if we're using stdio for input, then we want to use getc()
230 | 	 * instead of fread(), to make sure we stop fetching input after
231 | 	 * each newline.
232 | 	 */
233 | 	int yy_is_interactive;
234 | 
235 | 	/* Whether we're considered to be at the beginning of a line.
236 | 	 * If so, '^' rules will be active on the next match, otherwise
237 | 	 * not.
238 | 	 */
239 | 	int yy_at_bol;
240 | 
241 |     int yy_bs_lineno; /**< The line count. */
242 |     int yy_bs_column; /**< The column count. */
243 | 
244 | 	/* Whether to try to fill the input buffer when we reach the
245 | 	 * end of it.
246 | 	 */
247 | 	int yy_fill_buffer;
248 | 
249 | 	int yy_buffer_status;
250 | 
251 | #define YY_BUFFER_NEW 0
252 | #define YY_BUFFER_NORMAL 1
253 | 	/* When an EOF's been seen but there's still some text to process
254 | 	 * then we mark the buffer as YY_EOF_PENDING, to indicate that we
255 | 	 * shouldn't try reading from the input source any more.  We might
256 | 	 * still have a bunch of tokens to match, though, because of
257 | 	 * possible backing-up.
258 | 	 *
259 | 	 * When we actually see the EOF, we change the status to "new"
260 | 	 * (via yyrestart()), so that the user can continue scanning by
261 | 	 * just pointing yyin at a new input file.
262 | 	 */
263 | #define YY_BUFFER_EOF_PENDING 2
264 | 
265 | 	};
266 | #endif /* !YY_STRUCT_YY_BUFFER_STATE */
267 | 
268 | /* Stack of input buffers. */
269 | static size_t yy_buffer_stack_top = 0; /**< index of top of stack. */
270 | static size_t yy_buffer_stack_max = 0; /**< capacity of stack. */
271 | static YY_BUFFER_STATE * yy_buffer_stack = NULL; /**< Stack as an array. */
272 | 
273 | /* We provide macros for accessing buffer states in case in the
274 |  * future we want to put the buffer states in a more general
275 |  * "scanner state".
276 |  *
277 |  * Returns the top of the stack, or NULL.
278 |  */
279 | #define YY_CURRENT_BUFFER ( (yy_buffer_stack) \
280 |                           ? (yy_buffer_stack)[(yy_buffer_stack_top)] \
281 |                           : NULL)
282 | /* Same as previous macro, but useful when we know that the buffer stack is not
283 |  * NULL or when we need an lvalue. For internal use only.
284 |  */
285 | #define YY_CURRENT_BUFFER_LVALUE (yy_buffer_stack)[(yy_buffer_stack_top)]
286 | 
287 | /* yy_hold_char holds the character lost when yytext is formed. */
288 | static char yy_hold_char;
289 | static int yy_n_chars;		/* number of characters read into yy_ch_buf */
290 | int yyleng;
291 | 
292 | /* Points to current character in buffer. */
293 | static char *yy_c_buf_p = NULL;
294 | static int yy_init = 0;		/* whether we need to initialize */
295 | static int yy_start = 0;	/* start state number */
296 | 
297 | /* Flag which is used to allow yywrap()'s to do buffer switches
298 |  * instead of setting up a fresh yyin.  A bit of a hack ...
299 |  */
300 | static int yy_did_buffer_switch_on_eof;
301 | 
302 | void yyrestart ( FILE *input_file  );
303 | void yy_switch_to_buffer ( YY_BUFFER_STATE new_buffer  );
304 | YY_BUFFER_STATE yy_create_buffer ( FILE *file, int size  );
305 | void yy_delete_buffer ( YY_BUFFER_STATE b  );
306 | void yy_flush_buffer ( YY_BUFFER_STATE b  );
307 | void yypush_buffer_state ( YY_BUFFER_STATE new_buffer  );
308 | void yypop_buffer_state ( void );
309 | 
310 | static void yyensure_buffer_stack ( void );
311 | static void yy_load_buffer_state ( void );
312 | static void yy_init_buffer ( YY_BUFFER_STATE b, FILE *file  );
313 | #define YY_FLUSH_BUFFER yy_flush_buffer( YY_CURRENT_BUFFER )
314 | 
315 | YY_BUFFER_STATE yy_scan_buffer ( char *base, yy_size_t size  );
316 | YY_BUFFER_STATE yy_scan_string ( const char *yy_str  );
317 | YY_BUFFER_STATE yy_scan_bytes ( const char *bytes, int len  );
318 | 
319 | void *yyalloc ( yy_size_t  );
320 | void *yyrealloc ( void *, yy_size_t  );
321 | void yyfree ( void *  );
322 | 
323 | #define yy_new_buffer yy_create_buffer
324 | #define yy_set_interactive(is_interactive) \
325 | 	{ \
326 | 	if ( ! YY_CURRENT_BUFFER ){ \
327 |         yyensure_buffer_stack (); \
328 | 		YY_CURRENT_BUFFER_LVALUE =    \
329 |             yy_create_buffer( yyin, YY_BUF_SIZE ); \
330 | 	} \
331 | 	YY_CURRENT_BUFFER_LVALUE->yy_is_interactive = is_interactive; \
332 | 	}
333 | #define yy_set_bol(at_bol) \
334 | 	{ \
335 | 	if ( ! YY_CURRENT_BUFFER ){\
336 |         yyensure_buffer_stack (); \
337 | 		YY_CURRENT_BUFFER_LVALUE =    \
338 |             yy_create_buffer( yyin, YY_BUF_SIZE ); \
339 | 	} \
340 | 	YY_CURRENT_BUFFER_LVALUE->yy_at_bol = at_bol; \
341 | 	}
342 | #define YY_AT_BOL() (YY_CURRENT_BUFFER_LVALUE->yy_at_bol)
343 | 
344 | /* Begin user sect3 */
345 | 
346 | #define yywrap() (/*CONSTCOND*/1)
347 | #define YY_SKIP_YYWRAP
348 | typedef flex_uint8_t YY_CHAR;
349 | 
350 | FILE *yyin = NULL, *yyout = NULL;
351 | 
352 | typedef int yy_state_type;
353 | 
354 | extern int yylineno;
355 | int yylineno = 1;
356 | 
357 | extern char *yytext;
358 | #ifdef yytext_ptr
359 | #undef yytext_ptr
360 | #endif
361 | #define yytext_ptr yytext
362 | 
363 | static yy_state_type yy_get_previous_state ( void );
364 | static yy_state_type yy_try_NUL_trans ( yy_state_type current_state  );
365 | static int yy_get_next_buffer ( void );
366 | static void yynoreturn yy_fatal_error ( const char* msg  );
367 | 
368 | /* Done after the current pattern has been matched and before the
369 |  * corresponding action - sets up yytext.
370 |  */
371 | #define YY_DO_BEFORE_ACTION \
372 | 	(yytext_ptr) = yy_bp; \
373 | 	yyleng = (int) (yy_cp - yy_bp); \
374 | 	(yy_hold_char) = *yy_cp; \
375 | 	*yy_cp = '\0'; \
376 | 	(yy_c_buf_p) = yy_cp;
377 | #define YY_NUM_RULES 33
378 | #define YY_END_OF_BUFFER 34
379 | /* This struct is not used in this scanner,
380 |    but its presence is necessary. */
381 | struct yy_trans_info
382 | 	{
383 | 	flex_int32_t yy_verify;
384 | 	flex_int32_t yy_nxt;
385 | 	};
386 | static const flex_int16_t yy_accept[136] =
387 |     {   0,
388 |         0,    0,   34,   32,    1,    1,   32,   30,    5,    6,
389 |        29,   29,   29,   29,   29,   29,   29,   29,   29,   29,
390 |        29,   29,    7,    8,    0,   31,   30,   29,   29,   29,
391 |        29,   29,   29,   29,   29,   29,   29,   29,   29,   29,
392 |        29,   29,   29,   29,   29,   29,   29,   29,   29,   29,
393 |        29,   29,   29,   29,   29,   24,   23,   29,   29,   29,
394 |        29,   29,   29,   29,   29,   29,   29,   26,   14,   29,
395 |        29,   29,   29,   18,    2,   29,   29,   29,   29,   29,
396 |        29,   29,   29,   25,   29,    9,   29,   29,   29,   10,
397 |         4,   29,   29,   29,   29,   29,   29,   17,   29,   29,
398 | 
399 |        29,   29,   29,   29,   29,   29,   12,   29,   29,   29,
400 |        29,   29,   29,   29,   28,   29,   29,   29,   29,   29,
401 |        27,   29,    3,   29,   15,   16,   29,   29,   20,   11,
402 |        19,   13,   22,   21,    0
403 |     } ;
404 | 
405 | static const YY_CHAR yy_ec[256] =
406 |     {   0,
407 |         1,    1,    1,    1,    1,    1,    1,    1,    2,    3,
408 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
409 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
410 |         1,    2,    1,    4,    1,    1,    1,    1,    1,    1,
411 |         1,    1,    1,    1,    1,    1,    1,    5,    5,    5,
412 |         5,    5,    5,    5,    5,    5,    5,    6,    7,    1,
413 |         1,    1,    1,    1,    8,    8,    8,    8,    8,    8,
414 |         8,    8,    8,    8,    8,    9,    8,    8,    8,    8,
415 |         8,    8,    8,    8,    8,    8,    8,    8,    8,    8,
416 |         1,    1,    1,    1,    8,    1,   10,   11,   12,   13,
417 | 
418 |        14,   15,   16,   17,   18,    8,   19,   20,   21,   22,
419 |        23,   24,   25,   26,   27,   28,   29,    8,   30,   31,
420 |         8,    8,   32,    1,   33,    1,    1,    1,    1,    1,
421 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
422 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
423 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
424 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
425 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
426 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
427 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
428 | 
429 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
430 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
431 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
432 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
433 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
434 |         1,    1,    1,    1,    1
435 |     } ;
436 | 
437 | static const YY_CHAR yy_meta[34] =
438 |     {   0,
439 |         1,    1,    1,    1,    2,    1,    1,    2,    2,    2,
440 |         2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
441 |         2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
442 |         2,    1,    1
443 |     } ;
444 | 
445 | static const flex_int16_t yy_base[138] =
446 |     {   0,
447 |         0,    0,  147,  148,  148,  148,  142,  140,  148,  148,
448 |         0,   17,   25,  123,   18,   27,  114,  118,  131,   32,
449 |       126,  125,  148,  148,  134,  148,  132,    0,  122,  115,
450 |       106,  118,  109,  121,   24,  104,   98,  106,  106,   98,
451 |        20,  112,   99,   93,  110,   90,  108,   92,  104,  107,
452 |        92,   97,   94,   99,   91,  102,  101,   98,   90,   80,
453 |        78,   87,   75,   76,   74,   73,   81,    0,    0,   70,
454 |        85,   77,   83,    0,    0,   81,   80,   79,   69,   61,
455 |        76,   66,   70,    0,   69,   76,   74,   64,   60,    0,
456 |         0,   60,   59,   54,   57,   55,   51,    0,   50,   52,
457 | 
458 |        48,   50,   44,   41,   54,   53,    0,   58,   41,   44,
459 |        51,   42,   49,   31,    0,   39,   32,   31,   38,   41,
460 |         0,   40,    0,   42,    0,    0,   33,   32,    0,    0,
461 |         0,    0,    0,    0,  148,   55,   41
462 |     } ;
463 | 
464 | static const flex_int16_t yy_def[138] =
465 |     {   0,
466 |       135,    1,  135,  135,  135,  135,  136,  135,  135,  135,
467 |       137,  137,  137,  137,  137,  137,  137,  137,  137,  137,
468 |       137,  137,  135,  135,  136,  135,  135,  137,  137,  137,
469 |       137,  137,  137,  137,  137,  137,  137,  137,  137,  137,
470 |       137,  137,  137,  137,  137,  137,  137,  137,  137,  137,
471 |       137,  137,  137,  137,  137,  137,  137,  137,  137,  137,
472 |       137,  137,  137,  137,  137,  137,  137,  137,  137,  137,
473 |       137,  137,  137,  137,  137,  137,  137,  137,  137,  137,
474 |       137,  137,  137,  137,  137,  137,  137,  137,  137,  137,
475 |       137,  137,  137,  137,  137,  137,  137,  137,  137,  137,
476 | 
477 |       137,  137,  137,  137,  137,  137,  137,  137,  137,  137,
478 |       137,  137,  137,  137,  137,  137,  137,  137,  137,  137,
479 |       137,  137,  137,  137,  137,  137,  137,  137,  137,  137,
480 |       137,  137,  137,  137,    0,  135,  135
481 |     } ;
482 | 
483 | static const flex_int16_t yy_nxt[182] =
484 |     {   0,
485 |         4,    5,    6,    7,    8,    9,   10,   11,   11,   11,
486 |        11,   12,   13,   14,   15,   11,   11,   11,   11,   11,
487 |        16,   17,   18,   19,   11,   20,   21,   22,   11,   11,
488 |        11,   23,   24,   29,   31,   35,   37,   53,   32,   30,
489 |        36,   42,   28,   54,   38,   43,   60,   61,  134,  133,
490 |        33,  132,  131,  130,   44,   25,   25,  129,  128,  127,
491 |       126,  125,  124,  123,  122,  121,  120,  119,  118,  117,
492 |       116,  115,  114,  113,  112,  111,  110,  109,  108,  107,
493 |       106,  105,  104,  103,  102,  101,  100,   99,   98,   97,
494 |        96,   95,   94,   93,   92,   91,   90,   89,   88,   87,
495 | 
496 |        86,   85,   84,   83,   82,   81,   80,   79,   78,   77,
497 |        76,   75,   74,   73,   72,   71,   70,   69,   68,   67,
498 |        66,   65,   64,   63,   62,   59,   58,   57,   56,   55,
499 |        52,   51,   50,   49,   48,   47,   27,   26,   46,   45,
500 |        41,   40,   39,   34,   27,   26,  135,    3,  135,  135,
501 |       135,  135,  135,  135,  135,  135,  135,  135,  135,  135,
502 |       135,  135,  135,  135,  135,  135,  135,  135,  135,  135,
503 |       135,  135,  135,  135,  135,  135,  135,  135,  135,  135,
504 |       135
505 |     } ;
506 | 
507 | static const flex_int16_t yy_chk[182] =
508 |     {   0,
509 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
510 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
511 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
512 |         1,    1,    1,   12,   13,   15,   16,   35,   13,   12,
513 |        15,   20,  137,   35,   16,   20,   41,   41,  128,  127,
514 |        13,  124,  122,  120,   20,  136,  136,  119,  118,  117,
515 |       116,  114,  113,  112,  111,  110,  109,  108,  106,  105,
516 |       104,  103,  102,  101,  100,   99,   97,   96,   95,   94,
517 |        93,   92,   89,   88,   87,   86,   85,   83,   82,   81,
518 |        80,   79,   78,   77,   76,   73,   72,   71,   70,   67,
519 | 
520 |        66,   65,   64,   63,   62,   61,   60,   59,   58,   57,
521 |        56,   55,   54,   53,   52,   51,   50,   49,   48,   47,
522 |        46,   45,   44,   43,   42,   40,   39,   38,   37,   36,
523 |        34,   33,   32,   31,   30,   29,   27,   25,   22,   21,
524 |        19,   18,   17,   14,    8,    7,    3,  135,  135,  135,
525 |       135,  135,  135,  135,  135,  135,  135,  135,  135,  135,
526 |       135,  135,  135,  135,  135,  135,  135,  135,  135,  135,
527 |       135,  135,  135,  135,  135,  135,  135,  135,  135,  135,
528 |       135
529 |     } ;
530 | 
531 | /* Table of booleans, true if rule could match eol. */
532 | static const flex_int32_t yy_rule_can_match_eol[34] =
533 |     {   0,
534 | 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
535 |     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,     };
536 | 
537 | static yy_state_type yy_last_accepting_state;
538 | static char *yy_last_accepting_cpos;
539 | 
540 | extern int yy_flex_debug;
541 | int yy_flex_debug = 0;
542 | 
543 | /* The intent behind this definition is that it'll catch
544 |  * any uses of REJECT which flex missed.
545 |  */
546 | #define REJECT reject_used_but_not_detected
547 | #define yymore() yymore_used_but_not_detected
548 | #define YY_MORE_ADJ 0
549 | #define YY_RESTORE_YY_MORE_OFFSET
550 | char *yytext;
551 | #line 1 "src/lexer.l"
552 | #line 2 "src/lexer.l"
553 | #include <stdio.h>
554 | #include <stdlib.h>
555 | #include <string.h>
556 | #include "formLang.h"
557 | #include "parser.tab.h"
558 | 
559 | extern YYSTYPE yylval;
560 | 
561 | // Context tracking
562 | int after_field = 0;
563 | int after_colon = 0;
564 | int after_section = 0;
565 | int after_form = 0;
566 | int after_type = 0;
567 | 
568 | // Error handling
569 | void syntax_error(const char* msg) {
570 |     fprintf(stderr, "Syntax error at line %d: %s\n", yylineno, msg);
571 | }
572 | #line 573 "src/lex.yy.c"
573 | #define YY_NO_INPUT 1
574 | #line 575 "src/lex.yy.c"
575 | 
576 | #define INITIAL 0
577 | 
578 | #ifndef YY_NO_UNISTD_H
579 | /* Special case for "unistd.h", since it is non-ANSI. We include it way
580 |  * down here because we want the user's section 1 to have been scanned first.
581 |  * The user has a chance to override it with an option.
582 |  */
583 | #include <unistd.h>
584 | #endif
585 | 
586 | #ifndef YY_EXTRA_TYPE
587 | #define YY_EXTRA_TYPE void *
588 | #endif
589 | 
590 | static int yy_init_globals ( void );
591 | 
592 | /* Accessor methods to globals.
593 |    These are made visible to non-reentrant scanners for convenience. */
594 | 
595 | int yylex_destroy ( void );
596 | 
597 | int yyget_debug ( void );
598 | 
599 | void yyset_debug ( int debug_flag  );
600 | 
601 | YY_EXTRA_TYPE yyget_extra ( void );
602 | 
603 | void yyset_extra ( YY_EXTRA_TYPE user_defined  );
604 | 
605 | FILE *yyget_in ( void );
606 | 
607 | void yyset_in  ( FILE * _in_str  );
608 | 
609 | FILE *yyget_out ( void );
610 | 
611 | void yyset_out  ( FILE * _out_str  );
612 | 
613 | 			int yyget_leng ( void );
614 | 
615 | char *yyget_text ( void );
616 | 
617 | int yyget_lineno ( void );
618 | 
619 | void yyset_lineno ( int _line_number  );
620 | 
621 | /* Macros after this point can all be overridden by user definitions in
622 |  * section 1.
623 |  */
624 | 
625 | #ifndef YY_SKIP_YYWRAP
626 | #ifdef __cplusplus
627 | extern "C" int yywrap ( void );
628 | #else
629 | extern int yywrap ( void );
630 | #endif
631 | #endif
632 | 
633 | #ifndef YY_NO_UNPUT
634 |     
635 | #endif
636 | 
637 | #ifndef yytext_ptr
638 | static void yy_flex_strncpy ( char *, const char *, int );
639 | #endif
640 | 
641 | #ifdef YY_NEED_STRLEN
642 | static int yy_flex_strlen ( const char * );
643 | #endif
644 | 
645 | #ifndef YY_NO_INPUT
646 | #ifdef __cplusplus
647 | static int yyinput ( void );
648 | #else
649 | static int input ( void );
650 | #endif
651 | 
652 | #endif
653 | 
654 | /* Amount of stuff to slurp up with each read. */
655 | #ifndef YY_READ_BUF_SIZE
656 | #ifdef __ia64__
657 | /* On IA-64, the buffer size is 16k, not 8k */
658 | #define YY_READ_BUF_SIZE 16384
659 | #else
660 | #define YY_READ_BUF_SIZE 8192
661 | #endif /* __ia64__ */
662 | #endif
663 | 
664 | /* Copy whatever the last rule matched to the standard output. */
665 | #ifndef ECHO
666 | /* This used to be an fputs(), but since the string might contain NUL's,
667 |  * we now use fwrite().
668 |  */
669 | #define ECHO do { if (fwrite( yytext, (size_t) yyleng, 1, yyout )) {} } while (0)
670 | #endif
671 | 
672 | /* Gets input and stuffs it into "buf".  number of characters read, or YY_NULL,
673 |  * is returned in "result".
674 |  */
675 | #ifndef YY_INPUT
676 | #define YY_INPUT(buf,result,max_size) \
677 | 	if ( YY_CURRENT_BUFFER_LVALUE->yy_is_interactive ) \
678 | 		{ \
679 | 		int c = '*'; \
680 | 		int n; \
681 | 		for ( n = 0; n < max_size && \
682 | 			     (c = getc( yyin )) != EOF && c != '\n'; ++n ) \
683 | 			buf[n] = (char) c; \
684 | 		if ( c == '\n' ) \
685 | 			buf[n++] = (char) c; \
686 | 		if ( c == EOF && ferror( yyin ) ) \
687 | 			YY_FATAL_ERROR( "input in flex scanner failed" ); \
688 | 		result = n; \
689 | 		} \
690 | 	else \
691 | 		{ \
692 | 		errno=0; \
693 | 		while ( (result = (int) fread(buf, 1, (yy_size_t) max_size, yyin)) == 0 && ferror(yyin)) \
694 | 			{ \
695 | 			if( errno != EINTR) \
696 | 				{ \
697 | 				YY_FATAL_ERROR( "input in flex scanner failed" ); \
698 | 				break; \
699 | 				} \
700 | 			errno=0; \
701 | 			clearerr(yyin); \
702 | 			} \
703 | 		}\
704 | \
705 | 
706 | #endif
707 | 
708 | /* No semi-colon after return; correct usage is to write "yyterminate();" -
709 |  * we don't want an extra ';' after the "return" because that will cause
710 |  * some compilers to complain about unreachable statements.
711 |  */
712 | #ifndef yyterminate
713 | #define yyterminate() return YY_NULL
714 | #endif
715 | 
716 | /* Number of entries by which start-condition stack grows. */
717 | #ifndef YY_START_STACK_INCR
718 | #define YY_START_STACK_INCR 25
719 | #endif
720 | 
721 | /* Report a fatal error. */
722 | #ifndef YY_FATAL_ERROR
723 | #define YY_FATAL_ERROR(msg) yy_fatal_error( msg )
724 | #endif
725 | 
726 | /* end tables serialization structures and prototypes */
727 | 
728 | /* Default declaration of generated scanner - a define so the user can
729 |  * easily add parameters.
730 |  */
731 | #ifndef YY_DECL
732 | #define YY_DECL_IS_OURS 1
733 | 
734 | extern int yylex (void);
735 | 
736 | #define YY_DECL int yylex (void)
737 | #endif /* !YY_DECL */
738 | 
739 | /* Code executed at the beginning of each rule, after yytext and yyleng
740 |  * have been set up.
741 |  */
742 | #ifndef YY_USER_ACTION
743 | #define YY_USER_ACTION
744 | #endif
745 | 
746 | /* Code executed at the end of each rule. */
747 | #ifndef YY_BREAK
748 | #define YY_BREAK /*LINTED*/break;
749 | #endif
750 | 
751 | #define YY_RULE_SETUP \
752 | 	YY_USER_ACTION
753 | 
754 | /** The main scanner function which does all the work.
755 |  */
756 | YY_DECL
757 | {
758 | 	yy_state_type yy_current_state;
759 | 	char *yy_cp, *yy_bp;
760 | 	int yy_act;
761 |     
762 | 	if ( !(yy_init) )
763 | 		{
764 | 		(yy_init) = 1;
765 | 
766 | #ifdef YY_USER_INIT
767 | 		YY_USER_INIT;
768 | #endif
769 | 
770 | 		if ( ! (yy_start) )
771 | 			(yy_start) = 1;	/* first start state */
772 | 
773 | 		if ( ! yyin )
774 | 			yyin = stdin;
775 | 
776 | 		if ( ! yyout )
777 | 			yyout = stdout;
778 | 
779 | 		if ( ! YY_CURRENT_BUFFER ) {
780 | 			yyensure_buffer_stack ();
781 | 			YY_CURRENT_BUFFER_LVALUE =
782 | 				yy_create_buffer( yyin, YY_BUF_SIZE );
783 | 		}
784 | 
785 | 		yy_load_buffer_state(  );
786 | 		}
787 | 
788 | 	{
789 | #line 28 "src/lexer.l"
790 | 
791 | 
792 | #line 793 "src/lex.yy.c"
793 | 
794 | 	while ( /*CONSTCOND*/1 )		/* loops until end-of-file is reached */
795 | 		{
796 | 		yy_cp = (yy_c_buf_p);
797 | 
798 | 		/* Support of yytext. */
799 | 		*yy_cp = (yy_hold_char);
800 | 
801 | 		/* yy_bp points to the position in yy_ch_buf of the start of
802 | 		 * the current run.
803 | 		 */
804 | 		yy_bp = yy_cp;
805 | 
806 | 		yy_current_state = (yy_start);
807 | yy_match:
808 | 		do
809 | 			{
810 | 			YY_CHAR yy_c = yy_ec[YY_SC_TO_UI(*yy_cp)] ;
811 | 			if ( yy_accept[yy_current_state] )
812 | 				{
813 | 				(yy_last_accepting_state) = yy_current_state;
814 | 				(yy_last_accepting_cpos) = yy_cp;
815 | 				}
816 | 			while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
817 | 				{
818 | 				yy_current_state = (int) yy_def[yy_current_state];
819 | 				if ( yy_current_state >= 136 )
820 | 					yy_c = yy_meta[yy_c];
821 | 				}
822 | 			yy_current_state = yy_nxt[yy_base[yy_current_state] + yy_c];
823 | 			++yy_cp;
824 | 			}
825 | 		while ( yy_base[yy_current_state] != 148 );
826 | 
827 | yy_find_action:
828 | 		yy_act = yy_accept[yy_current_state];
829 | 		if ( yy_act == 0 )
830 | 			{ /* have to back up */
831 | 			yy_cp = (yy_last_accepting_cpos);
832 | 			yy_current_state = (yy_last_accepting_state);
833 | 			yy_act = yy_accept[yy_current_state];
834 | 			}
835 | 
836 | 		YY_DO_BEFORE_ACTION;
837 | 
838 | 		if ( yy_act != YY_END_OF_BUFFER && yy_rule_can_match_eol[yy_act] )
839 | 			{
840 | 			int yyl;
841 | 			for ( yyl = 0; yyl < yyleng; ++yyl )
842 | 				if ( yytext[yyl] == '\n' )
843 | 					
844 |     yylineno++;
845 | ;
846 | 			}
847 | 
848 | do_action:	/* This label is used only to access EOF actions. */
849 | 
850 | 		switch ( yy_act )
851 | 	{ /* beginning of action switch */
852 | 			case 0: /* must back up */
853 | 			/* undo the effects of YY_DO_BEFORE_ACTION */
854 | 			*yy_cp = (yy_hold_char);
855 | 			yy_cp = (yy_last_accepting_cpos);
856 | 			yy_current_state = (yy_last_accepting_state);
857 | 			goto yy_find_action;
858 | 
859 | case 1:
860 | /* rule 1 can match eol */
861 | YY_RULE_SETUP
862 | #line 30 "src/lexer.l"
863 | ; /* Skip whitespace and newlines */
864 | 	YY_BREAK
865 | case 2:
866 | YY_RULE_SETUP
867 | #line 32 "src/lexer.l"
868 | { return FORM; }
869 | 	YY_BREAK
870 | case 3:
871 | YY_RULE_SETUP
872 | #line 33 "src/lexer.l"
873 | { return SECTION; }
874 | 	YY_BREAK
875 | case 4:
876 | YY_RULE_SETUP
877 | #line 34 "src/lexer.l"
878 | { return FIELD; }
879 | 	YY_BREAK
880 | case 5:
881 | YY_RULE_SETUP
882 | #line 35 "src/lexer.l"
883 | { after_colon = 1; return ':'; }
884 | 	YY_BREAK
885 | case 6:
886 | YY_RULE_SETUP
887 | #line 36 "src/lexer.l"
888 | { after_colon = 0; return ';'; }
889 | 	YY_BREAK
890 | case 7:
891 | YY_RULE_SETUP
892 | #line 37 "src/lexer.l"
893 | { return '{'; }
894 | 	YY_BREAK
895 | case 8:
896 | YY_RULE_SETUP
897 | #line 38 "src/lexer.l"
898 | { return '}'; }
899 | 	YY_BREAK
900 | case 9:
901 | YY_RULE_SETUP
902 | #line 40 "src/lexer.l"
903 | { return after_colon ? TEXT : IDENTIFIER; }
904 | 	YY_BREAK
905 | case 10:
906 | YY_RULE_SETUP
907 | #line 41 "src/lexer.l"
908 | { return after_colon ? EMAIL : IDENTIFIER; }
909 | 	YY_BREAK
910 | case 11:
911 | YY_RULE_SETUP
912 | #line 42 "src/lexer.l"
913 | { return after_colon ? PASSWORD : IDENTIFIER; }
914 | 	YY_BREAK
915 | case 12:
916 | YY_RULE_SETUP
917 | #line 43 "src/lexer.l"
918 | { return after_colon ? NUMBER : IDENTIFIER; }
919 | 	YY_BREAK
920 | case 13:
921 | YY_RULE_SETUP
922 | #line 44 "src/lexer.l"
923 | { return after_colon ? TEXTAREA : IDENTIFIER; }
924 | 	YY_BREAK
925 | case 14:
926 | YY_RULE_SETUP
927 | #line 45 "src/lexer.l"
928 | { return after_colon ? DATE : IDENTIFIER; }
929 | 	YY_BREAK
930 | case 15:
931 | YY_RULE_SETUP
932 | #line 46 "src/lexer.l"
933 | { return after_colon ? CHECKBOX : IDENTIFIER; }
934 | 	YY_BREAK
935 | case 16:
936 | YY_RULE_SETUP
937 | #line 47 "src/lexer.l"
938 | { return after_colon ? DROPDOWN : IDENTIFIER; }
939 | 	YY_BREAK
940 | case 17:
941 | YY_RULE_SETUP
942 | #line 48 "src/lexer.l"
943 | { return after_colon ? RADIO : IDENTIFIER; }
944 | 	YY_BREAK
945 | case 18:
946 | YY_RULE_SETUP
947 | #line 49 "src/lexer.l"
948 | { return after_colon ? FILE_TYPE : IDENTIFIER; }
949 | 	YY_BREAK
950 | case 19:
951 | YY_RULE_SETUP
952 | #line 51 "src/lexer.l"
953 | { return REQUIRED; }
954 | 	YY_BREAK
955 | case 20:
956 | YY_RULE_SETUP
957 | #line 52 "src/lexer.l"
958 | { return OPTIONAL; }
959 | 	YY_BREAK
960 | case 21:
961 | YY_RULE_SETUP
962 | #line 53 "src/lexer.l"
963 | { return MINLENGTH; }
964 | 	YY_BREAK
965 | case 22:
966 | YY_RULE_SETUP
967 | #line 54 "src/lexer.l"
968 | { return MAXLENGTH; }
969 | 	YY_BREAK
970 | case 23:
971 | YY_RULE_SETUP
972 | #line 55 "src/lexer.l"
973 | { return MIN; }
974 | 	YY_BREAK
975 | case 24:
976 | YY_RULE_SETUP
977 | #line 56 "src/lexer.l"
978 | { return MAX; }
979 | 	YY_BREAK
980 | case 25:
981 | YY_RULE_SETUP
982 | #line 57 "src/lexer.l"
983 | { return ROWS; }
984 | 	YY_BREAK
985 | case 26:
986 | YY_RULE_SETUP
987 | #line 58 "src/lexer.l"
988 | { return COLS; }
989 | 	YY_BREAK
990 | case 27:
991 | YY_RULE_SETUP
992 | #line 59 "src/lexer.l"
993 | { return PATTERN; }
994 | 	YY_BREAK
995 | case 28:
996 | YY_RULE_SETUP
997 | #line 60 "src/lexer.l"
998 | { return DEFAULT; }
999 | 	YY_BREAK
1000 | case 29:
1001 | YY_RULE_SETUP
1002 | #line 62 "src/lexer.l"
1003 | { 
1004 |     yylval.str = strdup(yytext);
1005 |     return IDENTIFIER;
1006 | }
1007 | 	YY_BREAK
1008 | case 30:
1009 | YY_RULE_SETUP
1010 | #line 67 "src/lexer.l"
1011 | {
1012 |     yylval.num = atoi(yytext);
1013 |     return NUMBER_LITERAL;
1014 | }
1015 | 	YY_BREAK
1016 | case 31:
1017 | /* rule 31 can match eol */
1018 | YY_RULE_SETUP
1019 | #line 72 "src/lexer.l"
1020 | {
1021 |     // Remove quotes and copy the string
1022 |     yytext[strlen(yytext) - 1] = '\0';
1023 |     yylval.str = strdup(yytext + 1);
1024 |     return STRING_LITERAL;
1025 | }
1026 | 	YY_BREAK
1027 | case 32:
1028 | YY_RULE_SETUP
1029 | #line 79 "src/lexer.l"
1030 | { return yytext[0]; }
1031 | 	YY_BREAK
1032 | case 33:
1033 | YY_RULE_SETUP
1034 | #line 81 "src/lexer.l"
1035 | ECHO;
1036 | 	YY_BREAK
1037 | #line 1038 "src/lex.yy.c"
1038 | case YY_STATE_EOF(INITIAL):
1039 | 	yyterminate();
1040 | 
1041 | 	case YY_END_OF_BUFFER:
1042 | 		{
1043 | 		/* Amount of text matched not including the EOB char. */
1044 | 		int yy_amount_of_matched_text = (int) (yy_cp - (yytext_ptr)) - 1;
1045 | 
1046 | 		/* Undo the effects of YY_DO_BEFORE_ACTION. */
1047 | 		*yy_cp = (yy_hold_char);
1048 | 		YY_RESTORE_YY_MORE_OFFSET
1049 | 
1050 | 		if ( YY_CURRENT_BUFFER_LVALUE->yy_buffer_status == YY_BUFFER_NEW )
1051 | 			{
1052 | 			/* We're scanning a new file or input source.  It's
1053 | 			 * possible that this happened because the user
1054 | 			 * just pointed yyin at a new source and called
1055 | 			 * yylex().  If so, then we have to assure
1056 | 			 * consistency between YY_CURRENT_BUFFER and our
1057 | 			 * globals.  Here is the right place to do so, because
1058 | 			 * this is the first action (other than possibly a
1059 | 			 * back-up) that will match for the new input source.
1060 | 			 */
1061 | 			(yy_n_chars) = YY_CURRENT_BUFFER_LVALUE->yy_n_chars;
1062 | 			YY_CURRENT_BUFFER_LVALUE->yy_input_file = yyin;
1063 | 			YY_CURRENT_BUFFER_LVALUE->yy_buffer_status = YY_BUFFER_NORMAL;
1064 | 			}
1065 | 
1066 | 		/* Note that here we test for yy_c_buf_p "<=" to the position
1067 | 		 * of the first EOB in the buffer, since yy_c_buf_p will
1068 | 		 * already have been incremented past the NUL character
1069 | 		 * (since all states make transitions on EOB to the
1070 | 		 * end-of-buffer state).  Contrast this with the test
1071 | 		 * in input().
1072 | 		 */
1073 | 		if ( (yy_c_buf_p) <= &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[(yy_n_chars)] )
1074 | 			{ /* This was really a NUL. */
1075 | 			yy_state_type yy_next_state;
1076 | 
1077 | 			(yy_c_buf_p) = (yytext_ptr) + yy_amount_of_matched_text;
1078 | 
1079 | 			yy_current_state = yy_get_previous_state(  );
1080 | 
1081 | 			/* Okay, we're now positioned to make the NUL
1082 | 			 * transition.  We couldn't have
1083 | 			 * yy_get_previous_state() go ahead and do it
1084 | 			 * for us because it doesn't know how to deal
1085 | 			 * with the possibility of jamming (and we don't
1086 | 			 * want to build jamming into it because then it
1087 | 			 * will run more slowly).
1088 | 			 */
1089 | 
1090 | 			yy_next_state = yy_try_NUL_trans( yy_current_state );
1091 | 
1092 | 			yy_bp = (yytext_ptr) + YY_MORE_ADJ;
1093 | 
1094 | 			if ( yy_next_state )
1095 | 				{
1096 | 				/* Consume the NUL. */
1097 | 				yy_cp = ++(yy_c_buf_p);
1098 | 				yy_current_state = yy_next_state;
1099 | 				goto yy_match;
1100 | 				}
1101 | 
1102 | 			else
1103 | 				{
1104 | 				yy_cp = (yy_c_buf_p);
1105 | 				goto yy_find_action;
1106 | 				}
1107 | 			}
1108 | 
1109 | 		else switch ( yy_get_next_buffer(  ) )
1110 | 			{
1111 | 			case EOB_ACT_END_OF_FILE:
1112 | 				{
1113 | 				(yy_did_buffer_switch_on_eof) = 0;
1114 | 
1115 | 				if ( yywrap(  ) )
1116 | 					{
1117 | 					/* Note: because we've taken care in
1118 | 					 * yy_get_next_buffer() to have set up
1119 | 					 * yytext, we can now set up
1120 | 					 * yy_c_buf_p so that if some total
1121 | 					 * hoser (like flex itself) wants to
1122 | 					 * call the scanner after we return the
1123 | 					 * YY_NULL, it'll still work - another
1124 | 					 * YY_NULL will get returned.
1125 | 					 */
1126 | 					(yy_c_buf_p) = (yytext_ptr) + YY_MORE_ADJ;
1127 | 
1128 | 					yy_act = YY_STATE_EOF(YY_START);
1129 | 					goto do_action;
1130 | 					}
1131 | 
1132 | 				else
1133 | 					{
1134 | 					if ( ! (yy_did_buffer_switch_on_eof) )
1135 | 						YY_NEW_FILE;
1136 | 					}
1137 | 				break;
1138 | 				}
1139 | 
1140 | 			case EOB_ACT_CONTINUE_SCAN:
1141 | 				(yy_c_buf_p) =
1142 | 					(yytext_ptr) + yy_amount_of_matched_text;
1143 | 
1144 | 				yy_current_state = yy_get_previous_state(  );
1145 | 
1146 | 				yy_cp = (yy_c_buf_p);
1147 | 				yy_bp = (yytext_ptr) + YY_MORE_ADJ;
1148 | 				goto yy_match;
1149 | 
1150 | 			case EOB_ACT_LAST_MATCH:
1151 | 				(yy_c_buf_p) =
1152 | 				&YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[(yy_n_chars)];
1153 | 
1154 | 				yy_current_state = yy_get_previous_state(  );
1155 | 
1156 | 				yy_cp = (yy_c_buf_p);
1157 | 				yy_bp = (yytext_ptr) + YY_MORE_ADJ;
1158 | 				goto yy_find_action;
1159 | 			}
1160 | 		break;
1161 | 		}
1162 | 
1163 | 	default:
1164 | 		YY_FATAL_ERROR(
1165 | 			"fatal flex scanner internal error--no action found" );
1166 | 	} /* end of action switch */
1167 | 		} /* end of scanning one token */
1168 | 	} /* end of user's declarations */
1169 | } /* end of yylex */
1170 | 
1171 | /* yy_get_next_buffer - try to read in a new buffer
1172 |  *
1173 |  * Returns a code representing an action:
1174 |  *	EOB_ACT_LAST_MATCH -
1175 |  *	EOB_ACT_CONTINUE_SCAN - continue scanning from current position
1176 |  *	EOB_ACT_END_OF_FILE - end of file
1177 |  */
1178 | static int yy_get_next_buffer (void)
1179 | {
1180 |     	char *dest = YY_CURRENT_BUFFER_LVALUE->yy_ch_buf;
1181 | 	char *source = (yytext_ptr);
1182 | 	int number_to_move, i;
1183 | 	int ret_val;
1184 | 
1185 | 	if ( (yy_c_buf_p) > &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[(yy_n_chars) + 1] )
1186 | 		YY_FATAL_ERROR(
1187 | 		"fatal flex scanner internal error--end of buffer missed" );
1188 | 
1189 | 	if ( YY_CURRENT_BUFFER_LVALUE->yy_fill_buffer == 0 )
1190 | 		{ /* Don't try to fill the buffer, so this is an EOF. */
1191 | 		if ( (yy_c_buf_p) - (yytext_ptr) - YY_MORE_ADJ == 1 )
1192 | 			{
1193 | 			/* We matched a single character, the EOB, so
1194 | 			 * treat this as a final EOF.
1195 | 			 */
1196 | 			return EOB_ACT_END_OF_FILE;
1197 | 			}
1198 | 
1199 | 		else
1200 | 			{
1201 | 			/* We matched some text prior to the EOB, first
1202 | 			 * process it.
1203 | 			 */
1204 | 			return EOB_ACT_LAST_MATCH;
1205 | 			}
1206 | 		}
1207 | 
1208 | 	/* Try to read more data. */
1209 | 
1210 | 	/* First move last chars to start of buffer. */
1211 | 	number_to_move = (int) ((yy_c_buf_p) - (yytext_ptr) - 1);
1212 | 
1213 | 	for ( i = 0; i < number_to_move; ++i )
1214 | 		*(dest++) = *(source++);
1215 | 
1216 | 	if ( YY_CURRENT_BUFFER_LVALUE->yy_buffer_status == YY_BUFFER_EOF_PENDING )
1217 | 		/* don't do the read, it's not guaranteed to return an EOF,
1218 | 		 * just force an EOF
1219 | 		 */
1220 | 		YY_CURRENT_BUFFER_LVALUE->yy_n_chars = (yy_n_chars) = 0;
1221 | 
1222 | 	else
1223 | 		{
1224 | 			int num_to_read =
1225 | 			YY_CURRENT_BUFFER_LVALUE->yy_buf_size - number_to_move - 1;
1226 | 
1227 | 		while ( num_to_read <= 0 )
1228 | 			{ /* Not enough room in the buffer - grow it. */
1229 | 
1230 | 			/* just a shorter name for the current buffer */
1231 | 			YY_BUFFER_STATE b = YY_CURRENT_BUFFER_LVALUE;
1232 | 
1233 | 			int yy_c_buf_p_offset =
1234 | 				(int) ((yy_c_buf_p) - b->yy_ch_buf);
1235 | 
1236 | 			if ( b->yy_is_our_buffer )
1237 | 				{
1238 | 				int new_size = b->yy_buf_size * 2;
1239 | 
1240 | 				if ( new_size <= 0 )
1241 | 					b->yy_buf_size += b->yy_buf_size / 8;
1242 | 				else
1243 | 					b->yy_buf_size *= 2;
1244 | 
1245 | 				b->yy_ch_buf = (char *)
1246 | 					/* Include room in for 2 EOB chars. */
1247 | 					yyrealloc( (void *) b->yy_ch_buf,
1248 | 							 (yy_size_t) (b->yy_buf_size + 2)  );
1249 | 				}
1250 | 			else
1251 | 				/* Can't grow it, we don't own it. */
1252 | 				b->yy_ch_buf = NULL;
1253 | 
1254 | 			if ( ! b->yy_ch_buf )
1255 | 				YY_FATAL_ERROR(
1256 | 				"fatal error - scanner input buffer overflow" );
1257 | 
1258 | 			(yy_c_buf_p) = &b->yy_ch_buf[yy_c_buf_p_offset];
1259 | 
1260 | 			num_to_read = YY_CURRENT_BUFFER_LVALUE->yy_buf_size -
1261 | 						number_to_move - 1;
1262 | 
1263 | 			}
1264 | 
1265 | 		if ( num_to_read > YY_READ_BUF_SIZE )
1266 | 			num_to_read = YY_READ_BUF_SIZE;
1267 | 
1268 | 		/* Read in more data. */
1269 | 		YY_INPUT( (&YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[number_to_move]),
1270 | 			(yy_n_chars), num_to_read );
1271 | 
1272 | 		YY_CURRENT_BUFFER_LVALUE->yy_n_chars = (yy_n_chars);
1273 | 		}
1274 | 
1275 | 	if ( (yy_n_chars) == 0 )
1276 | 		{
1277 | 		if ( number_to_move == YY_MORE_ADJ )
1278 | 			{
1279 | 			ret_val = EOB_ACT_END_OF_FILE;
1280 | 			yyrestart( yyin  );
1281 | 			}
1282 | 
1283 | 		else
1284 | 			{
1285 | 			ret_val = EOB_ACT_LAST_MATCH;
1286 | 			YY_CURRENT_BUFFER_LVALUE->yy_buffer_status =
1287 | 				YY_BUFFER_EOF_PENDING;
1288 | 			}
1289 | 		}
1290 | 
1291 | 	else
1292 | 		ret_val = EOB_ACT_CONTINUE_SCAN;
1293 | 
1294 | 	if (((yy_n_chars) + number_to_move) > YY_CURRENT_BUFFER_LVALUE->yy_buf_size) {
1295 | 		/* Extend the array by 50%, plus the number we really need. */
1296 | 		int new_size = (yy_n_chars) + number_to_move + ((yy_n_chars) >> 1);
1297 | 		YY_CURRENT_BUFFER_LVALUE->yy_ch_buf = (char *) yyrealloc(
1298 | 			(void *) YY_CURRENT_BUFFER_LVALUE->yy_ch_buf, (yy_size_t) new_size  );
1299 | 		if ( ! YY_CURRENT_BUFFER_LVALUE->yy_ch_buf )
1300 | 			YY_FATAL_ERROR( "out of dynamic memory in yy_get_next_buffer()" );
1301 | 		/* "- 2" to take care of EOB's */
1302 | 		YY_CURRENT_BUFFER_LVALUE->yy_buf_size = (int) (new_size - 2);
1303 | 	}
1304 | 
1305 | 	(yy_n_chars) += number_to_move;
1306 | 	YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[(yy_n_chars)] = YY_END_OF_BUFFER_CHAR;
1307 | 	YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[(yy_n_chars) + 1] = YY_END_OF_BUFFER_CHAR;
1308 | 
1309 | 	(yytext_ptr) = &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[0];
1310 | 
1311 | 	return ret_val;
1312 | }
1313 | 
1314 | /* yy_get_previous_state - get the state just before the EOB char was reached */
1315 | 
1316 |     static yy_state_type yy_get_previous_state (void)
1317 | {
1318 | 	yy_state_type yy_current_state;
1319 | 	char *yy_cp;
1320 |     
1321 | 	yy_current_state = (yy_start);
1322 | 
1323 | 	for ( yy_cp = (yytext_ptr) + YY_MORE_ADJ; yy_cp < (yy_c_buf_p); ++yy_cp )
1324 | 		{
1325 | 		YY_CHAR yy_c = (*yy_cp ? yy_ec[YY_SC_TO_UI(*yy_cp)] : 1);
1326 | 		if ( yy_accept[yy_current_state] )
1327 | 			{
1328 | 			(yy_last_accepting_state) = yy_current_state;
1329 | 			(yy_last_accepting_cpos) = yy_cp;
1330 | 			}
1331 | 		while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
1332 | 			{
1333 | 			yy_current_state = (int) yy_def[yy_current_state];
1334 | 			if ( yy_current_state >= 136 )
1335 | 				yy_c = yy_meta[yy_c];
1336 | 			}
1337 | 		yy_current_state = yy_nxt[yy_base[yy_current_state] + yy_c];
1338 | 		}
1339 | 
1340 | 	return yy_current_state;
1341 | }
1342 | 
1343 | /* yy_try_NUL_trans - try to make a transition on the NUL character
1344 |  *
1345 |  * synopsis
1346 |  *	next_state = yy_try_NUL_trans( current_state );
1347 |  */
1348 |     static yy_state_type yy_try_NUL_trans  (yy_state_type yy_current_state )
1349 | {
1350 | 	int yy_is_jam;
1351 |     	char *yy_cp = (yy_c_buf_p);
1352 | 
1353 | 	YY_CHAR yy_c = 1;
1354 | 	if ( yy_accept[yy_current_state] )
1355 | 		{
1356 | 		(yy_last_accepting_state) = yy_current_state;
1357 | 		(yy_last_accepting_cpos) = yy_cp;
1358 | 		}
1359 | 	while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
1360 | 		{
1361 | 		yy_current_state = (int) yy_def[yy_current_state];
1362 | 		if ( yy_current_state >= 136 )
1363 | 			yy_c = yy_meta[yy_c];
1364 | 		}
1365 | 	yy_current_state = yy_nxt[yy_base[yy_current_state] + yy_c];
1366 | 	yy_is_jam = (yy_current_state == 135);
1367 | 
1368 | 		return yy_is_jam ? 0 : yy_current_state;
1369 | }
1370 | 
1371 | #ifndef YY_NO_UNPUT
1372 | 
1373 | #endif
1374 | 
1375 | #ifndef YY_NO_INPUT
1376 | #ifdef __cplusplus
1377 |     static int yyinput (void)
1378 | #else
1379 |     static int input  (void)
1380 | #endif
1381 | 
1382 | {
1383 | 	int c;
1384 |     
1385 | 	*(yy_c_buf_p) = (yy_hold_char);
1386 | 
1387 | 	if ( *(yy_c_buf_p) == YY_END_OF_BUFFER_CHAR )
1388 | 		{
1389 | 		/* yy_c_buf_p now points to the character we want to return.
1390 | 		 * If this occurs *before* the EOB characters, then it's a
1391 | 		 * valid NUL; if not, then we've hit the end of the buffer.
1392 | 		 */
1393 | 		if ( (yy_c_buf_p) < &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[(yy_n_chars)] )
1394 | 			/* This was really a NUL. */
1395 | 			*(yy_c_buf_p) = '\0';
1396 | 
1397 | 		else
1398 | 			{ /* need more input */
1399 | 			int offset = (int) ((yy_c_buf_p) - (yytext_ptr));
1400 | 			++(yy_c_buf_p);
1401 | 
1402 | 			switch ( yy_get_next_buffer(  ) )
1403 | 				{
1404 | 				case EOB_ACT_LAST_MATCH:
1405 | 					/* This happens because yy_g_n_b()
1406 | 					 * sees that we've accumulated a
1407 | 					 * token and flags that we need to
1408 | 					 * try matching the token before
1409 | 					 * proceeding.  But for input(),
1410 | 					 * there's no matching to consider.
1411 | 					 * So convert the EOB_ACT_LAST_MATCH
1412 | 					 * to EOB_ACT_END_OF_FILE.
1413 | 					 */
1414 | 
1415 | 					/* Reset buffer status. */
1416 | 					yyrestart( yyin );
1417 | 
1418 | 					/*FALLTHROUGH*/
1419 | 
1420 | 				case EOB_ACT_END_OF_FILE:
1421 | 					{
1422 | 					if ( yywrap(  ) )
1423 | 						return 0;
1424 | 
1425 | 					if ( ! (yy_did_buffer_switch_on_eof) )
1426 | 						YY_NEW_FILE;
1427 | #ifdef __cplusplus
1428 | 					return yyinput();
1429 | #else
1430 | 					return input();
1431 | #endif
1432 | 					}
1433 | 
1434 | 				case EOB_ACT_CONTINUE_SCAN:
1435 | 					(yy_c_buf_p) = (yytext_ptr) + offset;
1436 | 					break;
1437 | 				}
1438 | 			}
1439 | 		}
1440 | 
1441 | 	c = *(unsigned char *) (yy_c_buf_p);	/* cast for 8-bit char's */
1442 | 	*(yy_c_buf_p) = '\0';	/* preserve yytext */
1443 | 	(yy_hold_char) = *++(yy_c_buf_p);
1444 | 
1445 | 	if ( c == '\n' )
1446 | 		
1447 |     yylineno++;
1448 | ;
1449 | 
1450 | 	return c;
1451 | }
1452 | #endif	/* ifndef YY_NO_INPUT */
1453 | 
1454 | /** Immediately switch to a different input stream.
1455 |  * @param input_file A readable stream.
1456 |  * 
1457 |  * @note This function does not reset the start condition to @c INITIAL .
1458 |  */
1459 |     void yyrestart  (FILE * input_file )
1460 | {
1461 |     
1462 | 	if ( ! YY_CURRENT_BUFFER ){
1463 |         yyensure_buffer_stack ();
1464 | 		YY_CURRENT_BUFFER_LVALUE =
1465 |             yy_create_buffer( yyin, YY_BUF_SIZE );
1466 | 	}
1467 | 
1468 | 	yy_init_buffer( YY_CURRENT_BUFFER, input_file );
1469 | 	yy_load_buffer_state(  );
1470 | }
1471 | 
1472 | /** Switch to a different input buffer.
1473 |  * @param new_buffer The new input buffer.
1474 |  * 
1475 |  */
1476 |     void yy_switch_to_buffer  (YY_BUFFER_STATE  new_buffer )
1477 | {
1478 |     
1479 | 	/* TODO. We should be able to replace this entire function body
1480 | 	 * with
1481 | 	 *		yypop_buffer_state();
1482 | 	 *		yypush_buffer_state(new_buffer);
1483 |      */
1484 | 	yyensure_buffer_stack ();
1485 | 	if ( YY_CURRENT_BUFFER == new_buffer )
1486 | 		return;
1487 | 
1488 | 	if ( YY_CURRENT_BUFFER )
1489 | 		{
1490 | 		/* Flush out information for old buffer. */
1491 | 		*(yy_c_buf_p) = (yy_hold_char);
1492 | 		YY_CURRENT_BUFFER_LVALUE->yy_buf_pos = (yy_c_buf_p);
1493 | 		YY_CURRENT_BUFFER_LVALUE->yy_n_chars = (yy_n_chars);
1494 | 		}
1495 | 
1496 | 	YY_CURRENT_BUFFER_LVALUE = new_buffer;
1497 | 	yy_load_buffer_state(  );
1498 | 
1499 | 	/* We don't actually know whether we did this switch during
1500 | 	 * EOF (yywrap()) processing, but the only time this flag
1501 | 	 * is looked at is after yywrap() is called, so it's safe
1502 | 	 * to go ahead and always set it.
1503 | 	 */
1504 | 	(yy_did_buffer_switch_on_eof) = 1;
1505 | }
1506 | 
1507 | static void yy_load_buffer_state  (void)
1508 | {
1509 |     	(yy_n_chars) = YY_CURRENT_BUFFER_LVALUE->yy_n_chars;
1510 | 	(yytext_ptr) = (yy_c_buf_p) = YY_CURRENT_BUFFER_LVALUE->yy_buf_pos;
1511 | 	yyin = YY_CURRENT_BUFFER_LVALUE->yy_input_file;
1512 | 	(yy_hold_char) = *(yy_c_buf_p);
1513 | }
1514 | 
1515 | /** Allocate and initialize an input buffer state.
1516 |  * @param file A readable stream.
1517 |  * @param size The character buffer size in bytes. When in doubt, use @c YY_BUF_SIZE.
1518 |  * 
1519 |  * @return the allocated buffer state.
1520 |  */
1521 |     YY_BUFFER_STATE yy_create_buffer  (FILE * file, int  size )
1522 | {
1523 | 	YY_BUFFER_STATE b;
1524 |     
1525 | 	b = (YY_BUFFER_STATE) yyalloc( sizeof( struct yy_buffer_state )  );
1526 | 	if ( ! b )
1527 | 		YY_FATAL_ERROR( "out of dynamic memory in yy_create_buffer()" );
1528 | 
1529 | 	b->yy_buf_size = size;
1530 | 
1531 | 	/* yy_ch_buf has to be 2 characters longer than the size given because
1532 | 	 * we need to put in 2 end-of-buffer characters.
1533 | 	 */
1534 | 	b->yy_ch_buf = (char *) yyalloc( (yy_size_t) (b->yy_buf_size + 2)  );
1535 | 	if ( ! b->yy_ch_buf )
1536 | 		YY_FATAL_ERROR( "out of dynamic memory in yy_create_buffer()" );
1537 | 
1538 | 	b->yy_is_our_buffer = 1;
1539 | 
1540 | 	yy_init_buffer( b, file );
1541 | 
1542 | 	return b;
1543 | }
1544 | 
1545 | /** Destroy the buffer.
1546 |  * @param b a buffer created with yy_create_buffer()
1547 |  * 
1548 |  */
1549 |     void yy_delete_buffer (YY_BUFFER_STATE  b )
1550 | {
1551 |     
1552 | 	if ( ! b )
1553 | 		return;
1554 | 
1555 | 	if ( b == YY_CURRENT_BUFFER ) /* Not sure if we should pop here. */
1556 | 		YY_CURRENT_BUFFER_LVALUE = (YY_BUFFER_STATE) 0;
1557 | 
1558 | 	if ( b->yy_is_our_buffer )
1559 | 		yyfree( (void *) b->yy_ch_buf  );
1560 | 
1561 | 	yyfree( (void *) b  );
1562 | }
1563 | 
1564 | /* Initializes or reinitializes a buffer.
1565 |  * This function is sometimes called more than once on the same buffer,
1566 |  * such as during a yyrestart() or at EOF.
1567 |  */
1568 |     static void yy_init_buffer  (YY_BUFFER_STATE  b, FILE * file )
1569 | 
1570 | {
1571 | 	int oerrno = errno;
1572 |     
1573 | 	yy_flush_buffer( b );
1574 | 
1575 | 	b->yy_input_file = file;
1576 | 	b->yy_fill_buffer = 1;
1577 | 
1578 |     /* If b is the current buffer, then yy_init_buffer was _probably_
1579 |      * called from yyrestart() or through yy_get_next_buffer.
1580 |      * In that case, we don't want to reset the lineno or column.
1581 |      */
1582 |     if (b != YY_CURRENT_BUFFER){
1583 |         b->yy_bs_lineno = 1;
1584 |         b->yy_bs_column = 0;
1585 |     }
1586 | 
1587 |         b->yy_is_interactive = file ? (isatty( fileno(file) ) > 0) : 0;
1588 |     
1589 | 	errno = oerrno;
1590 | }
1591 | 
1592 | /** Discard all buffered characters. On the next scan, YY_INPUT will be called.
1593 |  * @param b the buffer state to be flushed, usually @c YY_CURRENT_BUFFER.
1594 |  * 
1595 |  */
1596 |     void yy_flush_buffer (YY_BUFFER_STATE  b )
1597 | {
1598 |     	if ( ! b )
1599 | 		return;
1600 | 
1601 | 	b->yy_n_chars = 0;
1602 | 
1603 | 	/* We always need two end-of-buffer characters.  The first causes
1604 | 	 * a transition to the end-of-buffer state.  The second causes
1605 | 	 * a jam in that state.
1606 | 	 */
1607 | 	b->yy_ch_buf[0] = YY_END_OF_BUFFER_CHAR;
1608 | 	b->yy_ch_buf[1] = YY_END_OF_BUFFER_CHAR;
1609 | 
1610 | 	b->yy_buf_pos = &b->yy_ch_buf[0];
1611 | 
1612 | 	b->yy_at_bol = 1;
1613 | 	b->yy_buffer_status = YY_BUFFER_NEW;
1614 | 
1615 | 	if ( b == YY_CURRENT_BUFFER )
1616 | 		yy_load_buffer_state(  );
1617 | }
1618 | 
1619 | /** Pushes the new state onto the stack. The new state becomes
1620 |  *  the current state. This function will allocate the stack
1621 |  *  if necessary.
1622 |  *  @param new_buffer The new state.
1623 |  *  
1624 |  */
1625 | void yypush_buffer_state (YY_BUFFER_STATE new_buffer )
1626 | {
1627 |     	if (new_buffer == NULL)
1628 | 		return;
1629 | 
1630 | 	yyensure_buffer_stack();
1631 | 
1632 | 	/* This block is copied from yy_switch_to_buffer. */
1633 | 	if ( YY_CURRENT_BUFFER )
1634 | 		{
1635 | 		/* Flush out information for old buffer. */
1636 | 		*(yy_c_buf_p) = (yy_hold_char);
1637 | 		YY_CURRENT_BUFFER_LVALUE->yy_buf_pos = (yy_c_buf_p);
1638 | 		YY_CURRENT_BUFFER_LVALUE->yy_n_chars = (yy_n_chars);
1639 | 		}
1640 | 
1641 | 	/* Only push if top exists. Otherwise, replace top. */
1642 | 	if (YY_CURRENT_BUFFER)
1643 | 		(yy_buffer_stack_top)++;
1644 | 	YY_CURRENT_BUFFER_LVALUE = new_buffer;
1645 | 
1646 | 	/* copied from yy_switch_to_buffer. */
1647 | 	yy_load_buffer_state(  );
1648 | 	(yy_did_buffer_switch_on_eof) = 1;
1649 | }
1650 | 
1651 | /** Removes and deletes the top of the stack, if present.
1652 |  *  The next element becomes the new top.
1653 |  *  
1654 |  */
1655 | void yypop_buffer_state (void)
1656 | {
1657 |     	if (!YY_CURRENT_BUFFER)
1658 | 		return;
1659 | 
1660 | 	yy_delete_buffer(YY_CURRENT_BUFFER );
1661 | 	YY_CURRENT_BUFFER_LVALUE = NULL;
1662 | 	if ((yy_buffer_stack_top) > 0)
1663 | 		--(yy_buffer_stack_top);
1664 | 
1665 | 	if (YY_CURRENT_BUFFER) {
1666 | 		yy_load_buffer_state(  );
1667 | 		(yy_did_buffer_switch_on_eof) = 1;
1668 | 	}
1669 | }
1670 | 
1671 | /* Allocates the stack if it does not exist.
1672 |  *  Guarantees space for at least one push.
1673 |  */
1674 | static void yyensure_buffer_stack (void)
1675 | {
1676 | 	yy_size_t num_to_alloc;
1677 |     
1678 | 	if (!(yy_buffer_stack)) {
1679 | 
1680 | 		/* First allocation is just for 2 elements, since we don't know if this
1681 | 		 * scanner will even need a stack. We use 2 instead of 1 to avoid an
1682 | 		 * immediate realloc on the next call.
1683 |          */
1684 |       num_to_alloc = 1; /* After all that talk, this was set to 1 anyways... */
1685 | 		(yy_buffer_stack) = (struct yy_buffer_state**)yyalloc
1686 | 								(num_to_alloc * sizeof(struct yy_buffer_state*)
1687 | 								);
1688 | 		if ( ! (yy_buffer_stack) )
1689 | 			YY_FATAL_ERROR( "out of dynamic memory in yyensure_buffer_stack()" );
1690 | 
1691 | 		memset((yy_buffer_stack), 0, num_to_alloc * sizeof(struct yy_buffer_state*));
1692 | 
1693 | 		(yy_buffer_stack_max) = num_to_alloc;
1694 | 		(yy_buffer_stack_top) = 0;
1695 | 		return;
1696 | 	}
1697 | 
1698 | 	if ((yy_buffer_stack_top) >= ((yy_buffer_stack_max)) - 1){
1699 | 
1700 | 		/* Increase the buffer to prepare for a possible push. */
1701 | 		yy_size_t grow_size = 8 /* arbitrary grow size */;
1702 | 
1703 | 		num_to_alloc = (yy_buffer_stack_max) + grow_size;
1704 | 		(yy_buffer_stack) = (struct yy_buffer_state**)yyrealloc
1705 | 								((yy_buffer_stack),
1706 | 								num_to_alloc * sizeof(struct yy_buffer_state*)
1707 | 								);
1708 | 		if ( ! (yy_buffer_stack) )
1709 | 			YY_FATAL_ERROR( "out of dynamic memory in yyensure_buffer_stack()" );
1710 | 
1711 | 		/* zero only the new slots.*/
1712 | 		memset((yy_buffer_stack) + (yy_buffer_stack_max), 0, grow_size * sizeof(struct yy_buffer_state*));
1713 | 		(yy_buffer_stack_max) = num_to_alloc;
1714 | 	}
1715 | }
1716 | 
1717 | /** Setup the input buffer state to scan directly from a user-specified character buffer.
1718 |  * @param base the character buffer
1719 |  * @param size the size in bytes of the character buffer
1720 |  * 
1721 |  * @return the newly allocated buffer state object.
1722 |  */
1723 | YY_BUFFER_STATE yy_scan_buffer  (char * base, yy_size_t  size )
1724 | {
1725 | 	YY_BUFFER_STATE b;
1726 |     
1727 | 	if ( size < 2 ||
1728 | 	     base[size-2] != YY_END_OF_BUFFER_CHAR ||
1729 | 	     base[size-1] != YY_END_OF_BUFFER_CHAR )
1730 | 		/* They forgot to leave room for the EOB's. */
1731 | 		return NULL;
1732 | 
1733 | 	b = (YY_BUFFER_STATE) yyalloc( sizeof( struct yy_buffer_state )  );
1734 | 	if ( ! b )
1735 | 		YY_FATAL_ERROR( "out of dynamic memory in yy_scan_buffer()" );
1736 | 
1737 | 	b->yy_buf_size = (int) (size - 2);	/* "- 2" to take care of EOB's */
1738 | 	b->yy_buf_pos = b->yy_ch_buf = base;
1739 | 	b->yy_is_our_buffer = 0;
1740 | 	b->yy_input_file = NULL;
1741 | 	b->yy_n_chars = b->yy_buf_size;
1742 | 	b->yy_is_interactive = 0;
1743 | 	b->yy_at_bol = 1;
1744 | 	b->yy_fill_buffer = 0;
1745 | 	b->yy_buffer_status = YY_BUFFER_NEW;
1746 | 
1747 | 	yy_switch_to_buffer( b  );
1748 | 
1749 | 	return b;
1750 | }
1751 | 
1752 | /** Setup the input buffer state to scan a string. The next call to yylex() will
1753 |  * scan from a @e copy of @a str.
1754 |  * @param yystr a NUL-terminated string to scan
1755 |  * 
1756 |  * @return the newly allocated buffer state object.
1757 |  * @note If you want to scan bytes that may contain NUL values, then use
1758 |  *       yy_scan_bytes() instead.
1759 |  */
1760 | YY_BUFFER_STATE yy_scan_string (const char * yystr )
1761 | {
1762 |     
1763 | 	return yy_scan_bytes( yystr, (int) strlen(yystr) );
1764 | }
1765 | 
1766 | /** Setup the input buffer state to scan the given bytes. The next call to yylex() will
1767 |  * scan from a @e copy of @a bytes.
1768 |  * @param yybytes the byte buffer to scan
1769 |  * @param _yybytes_len the number of bytes in the buffer pointed to by @a bytes.
1770 |  * 
1771 |  * @return the newly allocated buffer state object.
1772 |  */
1773 | YY_BUFFER_STATE yy_scan_bytes  (const char * yybytes, int  _yybytes_len )
1774 | {
1775 | 	YY_BUFFER_STATE b;
1776 | 	char *buf;
1777 | 	yy_size_t n;
1778 | 	int i;
1779 |     
1780 | 	/* Get memory for full buffer, including space for trailing EOB's. */
1781 | 	n = (yy_size_t) (_yybytes_len + 2);
1782 | 	buf = (char *) yyalloc( n  );
1783 | 	if ( ! buf )
1784 | 		YY_FATAL_ERROR( "out of dynamic memory in yy_scan_bytes()" );
1785 | 
1786 | 	for ( i = 0; i < _yybytes_len; ++i )
1787 | 		buf[i] = yybytes[i];
1788 | 
1789 | 	buf[_yybytes_len] = buf[_yybytes_len+1] = YY_END_OF_BUFFER_CHAR;
1790 | 
1791 | 	b = yy_scan_buffer( buf, n );
1792 | 	if ( ! b )
1793 | 		YY_FATAL_ERROR( "bad buffer in yy_scan_bytes()" );
1794 | 
1795 | 	/* It's okay to grow etc. this buffer, and we should throw it
1796 | 	 * away when we're done.
1797 | 	 */
1798 | 	b->yy_is_our_buffer = 1;
1799 | 
1800 | 	return b;
1801 | }
1802 | 
1803 | #ifndef YY_EXIT_FAILURE
1804 | #define YY_EXIT_FAILURE 2
1805 | #endif
1806 | 
1807 | static void yynoreturn yy_fatal_error (const char* msg )
1808 | {
1809 | 			fprintf( stderr, "%s\n", msg );
1810 | 	exit( YY_EXIT_FAILURE );
1811 | }
1812 | 
1813 | /* Redefine yyless() so it works in section 3 code. */
1814 | 
1815 | #undef yyless
1816 | #define yyless(n) \
1817 | 	do \
1818 | 		{ \
1819 | 		/* Undo effects of setting up yytext. */ \
1820 |         int yyless_macro_arg = (n); \
1821 |         YY_LESS_LINENO(yyless_macro_arg);\
1822 | 		yytext[yyleng] = (yy_hold_char); \
1823 | 		(yy_c_buf_p) = yytext + yyless_macro_arg; \
1824 | 		(yy_hold_char) = *(yy_c_buf_p); \
1825 | 		*(yy_c_buf_p) = '\0'; \
1826 | 		yyleng = yyless_macro_arg; \
1827 | 		} \
1828 | 	while ( 0 )
1829 | 
1830 | /* Accessor  methods (get/set functions) to struct members. */
1831 | 
1832 | /** Get the current line number.
1833 |  * 
1834 |  */
1835 | int yyget_lineno  (void)
1836 | {
1837 |     
1838 |     return yylineno;
1839 | }
1840 | 
1841 | /** Get the input stream.
1842 |  * 
1843 |  */
1844 | FILE *yyget_in  (void)
1845 | {
1846 |         return yyin;
1847 | }
1848 | 
1849 | /** Get the output stream.
1850 |  * 
1851 |  */
1852 | FILE *yyget_out  (void)
1853 | {
1854 |         return yyout;
1855 | }
1856 | 
1857 | /** Get the length of the current token.
1858 |  * 
1859 |  */
1860 | int yyget_leng  (void)
1861 | {
1862 |         return yyleng;
1863 | }
1864 | 
1865 | /** Get the current token.
1866 |  * 
1867 |  */
1868 | 
1869 | char *yyget_text  (void)
1870 | {
1871 |         return yytext;
1872 | }
1873 | 
1874 | /** Set the current line number.
1875 |  * @param _line_number line number
1876 |  * 
1877 |  */
1878 | void yyset_lineno (int  _line_number )
1879 | {
1880 |     
1881 |     yylineno = _line_number;
1882 | }
1883 | 
1884 | /** Set the input stream. This does not discard the current
1885 |  * input buffer.
1886 |  * @param _in_str A readable stream.
1887 |  * 
1888 |  * @see yy_switch_to_buffer
1889 |  */
1890 | void yyset_in (FILE *  _in_str )
1891 | {
1892 |         yyin = _in_str ;
1893 | }
1894 | 
1895 | void yyset_out (FILE *  _out_str )
1896 | {
1897 |         yyout = _out_str ;
1898 | }
1899 | 
1900 | int yyget_debug  (void)
1901 | {
1902 |         return yy_flex_debug;
1903 | }
1904 | 
1905 | void yyset_debug (int  _bdebug )
1906 | {
1907 |         yy_flex_debug = _bdebug ;
1908 | }
1909 | 
1910 | static int yy_init_globals (void)
1911 | {
1912 |         /* Initialization is the same as for the non-reentrant scanner.
1913 |      * This function is called from yylex_destroy(), so don't allocate here.
1914 |      */
1915 | 
1916 |     /* We do not touch yylineno unless the option is enabled. */
1917 |     yylineno =  1;
1918 |     
1919 |     (yy_buffer_stack) = NULL;
1920 |     (yy_buffer_stack_top) = 0;
1921 |     (yy_buffer_stack_max) = 0;
1922 |     (yy_c_buf_p) = NULL;
1923 |     (yy_init) = 0;
1924 |     (yy_start) = 0;
1925 | 
1926 | /* Defined in main.c */
1927 | #ifdef YY_STDINIT
1928 |     yyin = stdin;
1929 |     yyout = stdout;
1930 | #else
1931 |     yyin = NULL;
1932 |     yyout = NULL;
1933 | #endif
1934 | 
1935 |     /* For future reference: Set errno on error, since we are called by
1936 |      * yylex_init()
1937 |      */
1938 |     return 0;
1939 | }
1940 | 
1941 | /* yylex_destroy is for both reentrant and non-reentrant scanners. */
1942 | int yylex_destroy  (void)
1943 | {
1944 |     
1945 |     /* Pop the buffer stack, destroying each element. */
1946 | 	while(YY_CURRENT_BUFFER){
1947 | 		yy_delete_buffer( YY_CURRENT_BUFFER  );
1948 | 		YY_CURRENT_BUFFER_LVALUE = NULL;
1949 | 		yypop_buffer_state();
1950 | 	}
1951 | 
1952 | 	/* Destroy the stack itself. */
1953 | 	yyfree((yy_buffer_stack) );
1954 | 	(yy_buffer_stack) = NULL;
1955 | 
1956 |     /* Reset the globals. This is important in a non-reentrant scanner so the next time
1957 |      * yylex() is called, initialization will occur. */
1958 |     yy_init_globals( );
1959 | 
1960 |     return 0;
1961 | }
1962 | 
1963 | /*
1964 |  * Internal utility routines.
1965 |  */
1966 | 
1967 | #ifndef yytext_ptr
1968 | static void yy_flex_strncpy (char* s1, const char * s2, int n )
1969 | {
1970 | 		
1971 | 	int i;
1972 | 	for ( i = 0; i < n; ++i )
1973 | 		s1[i] = s2[i];
1974 | }
1975 | #endif
1976 | 
1977 | #ifdef YY_NEED_STRLEN
1978 | static int yy_flex_strlen (const char * s )
1979 | {
1980 | 	int n;
1981 | 	for ( n = 0; s[n]; ++n )
1982 | 		;
1983 | 
1984 | 	return n;
1985 | }
1986 | #endif
1987 | 
1988 | void *yyalloc (yy_size_t  size )
1989 | {
1990 | 			return malloc(size);
1991 | }
1992 | 
1993 | void *yyrealloc  (void * ptr, yy_size_t  size )
1994 | {
1995 | 		
1996 | 	/* The cast to (char *) in the following accommodates both
1997 | 	 * implementations that use char* generic pointers, and those
1998 | 	 * that use void* generic pointers.  It works with the latter
1999 | 	 * because both ANSI C and C++ allow castless assignment from
2000 | 	 * any pointer type to void*, and deal with argument conversions
2001 | 	 * as though doing an assignment.
2002 | 	 */
2003 | 	return realloc(ptr, size);
2004 | }
2005 | 
2006 | void yyfree (void * ptr )
2007 | {
2008 | 			free( (char *) ptr );	/* see yyrealloc() for (char *) cast */
2009 | }
2010 | 
2011 | #define YYTABLES_NAME "yytables"
2012 | 
2013 | #line 81 "src/lexer.l"
2014 | 
2015 | 
```

FormLang/src/lexer.l
```
1 | %{
2 | #include <stdio.h>
3 | #include <stdlib.h>
4 | #include <string.h>
5 | #include "formLang.h"
6 | #include "parser.tab.h"
7 | 
8 | extern YYSTYPE yylval;
9 | 
10 | // Context tracking
11 | int after_field = 0;
12 | int after_colon = 0;
13 | int after_section = 0;
14 | int after_form = 0;
15 | int after_type = 0;
16 | 
17 | // Error handling
18 | void syntax_error(const char* msg) {
19 |     fprintf(stderr, "Syntax error at line %d: %s\n", yylineno, msg);
20 | }
21 | %}
22 | 
23 | %option nounput
24 | %option noinput
25 | %option yylineno
26 | %option noyywrap
27 | 
28 | %%
29 | 
30 | [ \t\n]     ; /* Skip whitespace and newlines */
31 | 
32 | "form"      { return FORM; }
33 | "section"   { return SECTION; }
34 | "field"     { return FIELD; }
35 | ":"         { after_colon = 1; return ':'; }
36 | ";"         { after_colon = 0; return ';'; }
37 | "{"         { return '{'; }
38 | "}"         { return '}'; }
39 | 
40 | "text"      { return after_colon ? TEXT : IDENTIFIER; }
41 | "email"     { return after_colon ? EMAIL : IDENTIFIER; }
42 | "password"  { return after_colon ? PASSWORD : IDENTIFIER; }
43 | "number"    { return after_colon ? NUMBER : IDENTIFIER; }
44 | "textarea"  { return after_colon ? TEXTAREA : IDENTIFIER; }
45 | "date"      { return after_colon ? DATE : IDENTIFIER; }
46 | "checkbox"  { return after_colon ? CHECKBOX : IDENTIFIER; }
47 | "dropdown"  { return after_colon ? DROPDOWN : IDENTIFIER; }
48 | "radio"     { return after_colon ? RADIO : IDENTIFIER; }
49 | "file"      { return after_colon ? FILE_TYPE : IDENTIFIER; }
50 | 
51 | "required"  { return REQUIRED; }
52 | "optional"  { return OPTIONAL; }
53 | "minLength" { return MINLENGTH; }
54 | "maxLength" { return MAXLENGTH; }
55 | "min"       { return MIN; }
56 | "max"       { return MAX; }
57 | "rows"      { return ROWS; }
58 | "cols"      { return COLS; }
59 | "pattern"   { return PATTERN; }
60 | "default"   { return DEFAULT; }
61 | 
62 | [a-zA-Z_][a-zA-Z0-9_]* { 
63 |     yylval.str = strdup(yytext);
64 |     return IDENTIFIER;
65 | }
66 | 
67 | [0-9]+      {
68 |     yylval.num = atoi(yytext);
69 |     return NUMBER_LITERAL;
70 | }
71 | 
72 | \"[^\"]*\"  {
73 |     // Remove quotes and copy the string
74 |     yytext[strlen(yytext) - 1] = '\0';
75 |     yylval.str = strdup(yytext + 1);
76 |     return STRING_LITERAL;
77 | }
78 | 
79 | .           { return yytext[0]; }
80 | 
81 | %%
```

FormLang/src/parser.tab.c
```
1 | /* A Bison parser, made by GNU Bison 3.8.2.  */
2 | 
3 | /* Bison implementation for Yacc-like parsers in C
4 | 
5 |    Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
6 |    Inc.
7 | 
8 |    This program is free software: you can redistribute it and/or modify
9 |    it under the terms of the GNU General Public License as published by
10 |    the Free Software Foundation, either version 3 of the License, or
11 |    (at your option) any later version.
12 | 
13 |    This program is distributed in the hope that it will be useful,
14 |    but WITHOUT ANY WARRANTY; without even the implied warranty of
15 |    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
16 |    GNU General Public License for more details.
17 | 
18 |    You should have received a copy of the GNU General Public License
19 |    along with this program.  If not, see <https://www.gnu.org/licenses/>.  */
20 | 
21 | /* As a special exception, you may create a larger work that contains
22 |    part or all of the Bison parser skeleton and distribute that work
23 |    under terms of your choice, so long as that work isn't itself a
24 |    parser generator using the skeleton or a modified version thereof
25 |    as a parser skeleton.  Alternatively, if you modify or redistribute
26 |    the parser skeleton itself, you may (at your option) remove this
27 |    special exception, which will cause the skeleton and the resulting
28 |    Bison output files to be licensed under the GNU General Public
29 |    License without this special exception.
30 | 
31 |    This special exception was added by the Free Software Foundation in
32 |    version 2.2 of Bison.  */
33 | 
34 | /* C LALR(1) parser skeleton written by Richard Stallman, by
35 |    simplifying the original so-called "semantic" parser.  */
36 | 
37 | /* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
38 |    especially those whose name start with YY_ or yy_.  They are
39 |    private implementation details that can be changed or removed.  */
40 | 
41 | /* All symbols defined below should begin with yy or YY, to avoid
42 |    infringing on user name space.  This should be done even for local
43 |    variables, as they might otherwise be expanded by user macros.
44 |    There are some unavoidable exceptions within include files to
45 |    define necessary library symbols; they are noted "INFRINGES ON
46 |    USER NAME SPACE" below.  */
47 | 
48 | /* Identify Bison output, and Bison version.  */
49 | #define YYBISON 30802
50 | 
51 | /* Bison version string.  */
52 | #define YYBISON_VERSION "3.8.2"
53 | 
54 | /* Skeleton name.  */
55 | #define YYSKELETON_NAME "yacc.c"
56 | 
57 | /* Pure parsers.  */
58 | #define YYPURE 0
59 | 
60 | /* Push parsers.  */
61 | #define YYPUSH 0
62 | 
63 | /* Pull parsers.  */
64 | #define YYPULL 1
65 | 
66 | 
67 | 
68 | 
69 | /* First part of user prologue.  */
70 | #line 1 "src/parser.y"
71 | 
72 | #include <stdio.h>
73 | #include <stdlib.h>
74 | #include <string.h>
75 | #include "formLang.h"
76 | 
77 | extern int yylex();
78 | extern int yylineno;
79 | void yyerror(const char *s);
80 | 
81 | // Global variables for current form and section
82 | Form *current_form = NULL;
83 | Section *current_section = NULL;
84 | 
85 | // Field name tracking for duplicate detection
86 | typedef struct {
87 |     char* name;
88 |     int line;
89 | } FieldName;
90 | 
91 | FieldName* field_names = NULL;
92 | int field_name_count = 0;
93 | 
94 | // Helper functions
95 | Form* create_form(const char* name) {
96 |     Form* form = malloc(sizeof(Form));
97 |     if (!form) return NULL;
98 |     form->name = strdup(name);
99 |     form->sections = NULL;
100 |     form->section_count = 0;
101 |     return form;
102 | }
103 | 
104 | Section* create_section(const char* name) {
105 |     Section* section = malloc(sizeof(Section));
106 |     if (!section) return NULL;
107 |     section->name = strdup(name);
108 |     section->fields = NULL;
109 |     section->field_count = 0;
110 |     return section;
111 | }
112 | 
113 | void add_section_to_form(Form* form, Section* section) {
114 |     fprintf(stderr, "Adding section to form\n");
115 |     if (!form || !section) {
116 |         fprintf(stderr, "Null form or section\n");
117 |         return;
118 |     }
119 |     
120 |     fprintf(stderr, "Reallocating sections array\n");
121 |     Section** new_sections = realloc(form->sections, (form->section_count + 1) * sizeof(Section*));
122 |     if (!new_sections) {
123 |         fprintf(stderr, "Memory allocation failed for sections\n");
124 |         exit(1);
125 |     }
126 |     form->sections = new_sections;
127 |     form->sections[form->section_count] = section;
128 |     form->section_count++;
129 |     fprintf(stderr, "Section added successfully\n");
130 | }
131 | 
132 | int check_duplicate_field(const char* name) {
133 |     for (int i = 0; i < field_name_count; i++) {
134 |         if (strcmp(field_names[i].name, name) == 0) {
135 |             return 1;
136 |         }
137 |     }
138 |     return 0;
139 | }
140 | 
141 | void init_field_attributes(FieldAttributes* attrs) {
142 |     if (!attrs) return;
143 |     attrs->min_length = -1;
144 |     attrs->max_length = -1;
145 |     attrs->min_value = -1;
146 |     attrs->max_value = -1;
147 |     attrs->rows = -1;
148 |     attrs->cols = -1;
149 |     attrs->pattern = NULL;
150 |     attrs->default_value = NULL;
151 |     attrs->required = 0;
152 | }
153 | 
154 | void add_field_to_section(Section* section, const char* name, FieldType type, FieldAttributes* attrs) {
155 |     fprintf(stderr, "Adding field %s to section\n", name);
156 |     if (!section || !name || !attrs) {
157 |         fprintf(stderr, "Null section, name, or attrs\n");
158 |         return;
159 |     }
160 |     
161 |     // Add field name to tracking
162 |     field_name_count++;
163 |     FieldName* new_field_names = realloc(field_names, field_name_count * sizeof(FieldName));
164 |     if (!new_field_names) {
165 |         fprintf(stderr, "Memory allocation failed for field names\n");
166 |         exit(1);
167 |     }
168 |     field_names = new_field_names;
169 |     field_names[field_name_count - 1].name = strdup(name);
170 |     field_names[field_name_count - 1].line = yylineno;
171 |     
172 |     fprintf(stderr, "Reallocating fields array\n");
173 |     // Allocate memory for the new field
174 |     Field* new_fields = realloc(section->fields, (section->field_count + 1) * sizeof(Field));
175 |     if (!new_fields) {
176 |         fprintf(stderr, "Memory allocation failed for fields\n");
177 |         exit(1);
178 |     }
179 |     section->fields = new_fields;
180 |     
181 |     Field* field = &section->fields[section->field_count];
182 |     field->name = strdup(name);
183 |     field->type = type;
184 |     memcpy(&field->attributes, attrs, sizeof(FieldAttributes));
185 |     
186 |     // If the attributes contain strings, make copies
187 |     if (attrs->pattern) {
188 |         field->attributes.pattern = strdup(attrs->pattern);
189 |     }
190 |     if (attrs->default_value) {
191 |         field->attributes.default_value = strdup(attrs->default_value);
192 |     }
193 |     
194 |     section->field_count++;
195 |     fprintf(stderr, "Field added successfully\n");
196 | }
197 | 
198 | void cleanup_form(Form* form) {
199 |     if (form) {
200 |         for (int i = 0; i < form->section_count; i++) {
201 |             Section* s = form->sections[i];
202 |             if (s) {
203 |                 for (int j = 0; j < s->field_count; j++) {
204 |                     Field* f = &s->fields[j];
205 |                     if (f->name) free(f->name);
206 |                     if (f->attributes.pattern) free(f->attributes.pattern);
207 |                     if (f->attributes.default_value) free(f->attributes.default_value);
208 |                 }
209 |                 if (s->fields) free(s->fields);
210 |                 if (s->name) free(s->name);
211 |                 free(s);
212 |             }
213 |         }
214 |         if (form->sections) free(form->sections);
215 |         if (form->name) free(form->name);
216 |         free(form);
217 |     }
218 |     
219 |     // Cleanup field name tracking
220 |     for (int i = 0; i < field_name_count; i++) {
221 |         if (field_names[i].name) free(field_names[i].name);
222 |     }
223 |     if (field_names) free(field_names);
224 |     field_name_count = 0;
225 | }
226 | 
227 | #line 228 "src/parser.tab.c"
228 | 
229 | # ifndef YY_CAST
230 | #  ifdef __cplusplus
231 | #   define YY_CAST(Type, Val) static_cast<Type> (Val)
232 | #   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
233 | #  else
234 | #   define YY_CAST(Type, Val) ((Type) (Val))
235 | #   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
236 | #  endif
237 | # endif
238 | # ifndef YY_NULLPTR
239 | #  if defined __cplusplus
240 | #   if 201103L <= __cplusplus
241 | #    define YY_NULLPTR nullptr
242 | #   else
243 | #    define YY_NULLPTR 0
244 | #   endif
245 | #  else
246 | #   define YY_NULLPTR ((void*)0)
247 | #  endif
248 | # endif
249 | 
250 | #include "parser.tab.h"
251 | /* Symbol kind.  */
252 | enum yysymbol_kind_t
253 | {
254 |   YYSYMBOL_YYEMPTY = -2,
255 |   YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
256 |   YYSYMBOL_YYerror = 1,                    /* error  */
257 |   YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
258 |   YYSYMBOL_FORM = 3,                       /* FORM  */
259 |   YYSYMBOL_SECTION = 4,                    /* SECTION  */
260 |   YYSYMBOL_FIELD = 5,                      /* FIELD  */
261 |   YYSYMBOL_TEXT = 6,                       /* TEXT  */
262 |   YYSYMBOL_EMAIL = 7,                      /* EMAIL  */
263 |   YYSYMBOL_PASSWORD = 8,                   /* PASSWORD  */
264 |   YYSYMBOL_NUMBER = 9,                     /* NUMBER  */
265 |   YYSYMBOL_TEXTAREA = 10,                  /* TEXTAREA  */
266 |   YYSYMBOL_DATE = 11,                      /* DATE  */
267 |   YYSYMBOL_CHECKBOX = 12,                  /* CHECKBOX  */
268 |   YYSYMBOL_DROPDOWN = 13,                  /* DROPDOWN  */
269 |   YYSYMBOL_RADIO = 14,                     /* RADIO  */
270 |   YYSYMBOL_FILE_TYPE = 15,                 /* FILE_TYPE  */
271 |   YYSYMBOL_REQUIRED = 16,                  /* REQUIRED  */
272 |   YYSYMBOL_OPTIONAL = 17,                  /* OPTIONAL  */
273 |   YYSYMBOL_MINLENGTH = 18,                 /* MINLENGTH  */
274 |   YYSYMBOL_MAXLENGTH = 19,                 /* MAXLENGTH  */
275 |   YYSYMBOL_MIN = 20,                       /* MIN  */
276 |   YYSYMBOL_MAX = 21,                       /* MAX  */
277 |   YYSYMBOL_ROWS = 22,                      /* ROWS  */
278 |   YYSYMBOL_COLS = 23,                      /* COLS  */
279 |   YYSYMBOL_PATTERN = 24,                   /* PATTERN  */
280 |   YYSYMBOL_DEFAULT = 25,                   /* DEFAULT  */
281 |   YYSYMBOL_IDENTIFIER = 26,                /* IDENTIFIER  */
282 |   YYSYMBOL_NUMBER_LITERAL = 27,            /* NUMBER_LITERAL  */
283 |   YYSYMBOL_STRING_LITERAL = 28,            /* STRING_LITERAL  */
284 |   YYSYMBOL_29_ = 29,                       /* '{'  */
285 |   YYSYMBOL_30_ = 30,                       /* '}'  */
286 |   YYSYMBOL_31_ = 31,                       /* ';'  */
287 |   YYSYMBOL_32_ = 32,                       /* ':'  */
288 |   YYSYMBOL_YYACCEPT = 33,                  /* $accept  */
289 |   YYSYMBOL_form = 34,                      /* form  */
290 |   YYSYMBOL_35_1 = 35,                      /* $@1  */
291 |   YYSYMBOL_section_list = 36,              /* section_list  */
292 |   YYSYMBOL_section = 37,                   /* section  */
293 |   YYSYMBOL_section_header = 38,            /* section_header  */
294 |   YYSYMBOL_field_list = 39,                /* field_list  */
295 |   YYSYMBOL_field = 40,                     /* field  */
296 |   YYSYMBOL_field_type = 41,                /* field_type  */
297 |   YYSYMBOL_field_attributes = 42,          /* field_attributes  */
298 |   YYSYMBOL_attribute = 43                  /* attribute  */
299 | };
300 | typedef enum yysymbol_kind_t yysymbol_kind_t;
301 | 
302 | 
303 | 
304 | 
305 | #ifdef short
306 | # undef short
307 | #endif
308 | 
309 | /* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
310 |    <limits.h> and (if available) <stdint.h> are included
311 |    so that the code can choose integer types of a good width.  */
312 | 
313 | #ifndef __PTRDIFF_MAX__
314 | # include <limits.h> /* INFRINGES ON USER NAME SPACE */
315 | # if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
316 | #  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
317 | #  define YY_STDINT_H
318 | # endif
319 | #endif
320 | 
321 | /* Narrow types that promote to a signed type and that can represent a
322 |    signed or unsigned integer of at least N bits.  In tables they can
323 |    save space and decrease cache pressure.  Promoting to a signed type
324 |    helps avoid bugs in integer arithmetic.  */
325 | 
326 | #ifdef __INT_LEAST8_MAX__
327 | typedef __INT_LEAST8_TYPE__ yytype_int8;
328 | #elif defined YY_STDINT_H
329 | typedef int_least8_t yytype_int8;
330 | #else
331 | typedef signed char yytype_int8;
332 | #endif
333 | 
334 | #ifdef __INT_LEAST16_MAX__
335 | typedef __INT_LEAST16_TYPE__ yytype_int16;
336 | #elif defined YY_STDINT_H
337 | typedef int_least16_t yytype_int16;
338 | #else
339 | typedef short yytype_int16;
340 | #endif
341 | 
342 | /* Work around bug in HP-UX 11.23, which defines these macros
343 |    incorrectly for preprocessor constants.  This workaround can likely
344 |    be removed in 2023, as HPE has promised support for HP-UX 11.23
345 |    (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
346 |    <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
347 | #ifdef __hpux
348 | # undef UINT_LEAST8_MAX
349 | # undef UINT_LEAST16_MAX
350 | # define UINT_LEAST8_MAX 255
351 | # define UINT_LEAST16_MAX 65535
352 | #endif
353 | 
354 | #if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
355 | typedef __UINT_LEAST8_TYPE__ yytype_uint8;
356 | #elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
357 |        && UINT_LEAST8_MAX <= INT_MAX)
358 | typedef uint_least8_t yytype_uint8;
359 | #elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
360 | typedef unsigned char yytype_uint8;
361 | #else
362 | typedef short yytype_uint8;
363 | #endif
364 | 
365 | #if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
366 | typedef __UINT_LEAST16_TYPE__ yytype_uint16;
367 | #elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
368 |        && UINT_LEAST16_MAX <= INT_MAX)
369 | typedef uint_least16_t yytype_uint16;
370 | #elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
371 | typedef unsigned short yytype_uint16;
372 | #else
373 | typedef int yytype_uint16;
374 | #endif
375 | 
376 | #ifndef YYPTRDIFF_T
377 | # if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
378 | #  define YYPTRDIFF_T __PTRDIFF_TYPE__
379 | #  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
380 | # elif defined PTRDIFF_MAX
381 | #  ifndef ptrdiff_t
382 | #   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
383 | #  endif
384 | #  define YYPTRDIFF_T ptrdiff_t
385 | #  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
386 | # else
387 | #  define YYPTRDIFF_T long
388 | #  define YYPTRDIFF_MAXIMUM LONG_MAX
389 | # endif
390 | #endif
391 | 
392 | #ifndef YYSIZE_T
393 | # ifdef __SIZE_TYPE__
394 | #  define YYSIZE_T __SIZE_TYPE__
395 | # elif defined size_t
396 | #  define YYSIZE_T size_t
397 | # elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
398 | #  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
399 | #  define YYSIZE_T size_t
400 | # else
401 | #  define YYSIZE_T unsigned
402 | # endif
403 | #endif
404 | 
405 | #define YYSIZE_MAXIMUM                                  \
406 |   YY_CAST (YYPTRDIFF_T,                                 \
407 |            (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
408 |             ? YYPTRDIFF_MAXIMUM                         \
409 |             : YY_CAST (YYSIZE_T, -1)))
410 | 
411 | #define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))
412 | 
413 | 
414 | /* Stored state numbers (used for stacks). */
415 | typedef yytype_int8 yy_state_t;
416 | 
417 | /* State numbers in computations.  */
418 | typedef int yy_state_fast_t;
419 | 
420 | #ifndef YY_
421 | # if defined YYENABLE_NLS && YYENABLE_NLS
422 | #  if ENABLE_NLS
423 | #   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
424 | #   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
425 | #  endif
426 | # endif
427 | # ifndef YY_
428 | #  define YY_(Msgid) Msgid
429 | # endif
430 | #endif
431 | 
432 | 
433 | #ifndef YY_ATTRIBUTE_PURE
434 | # if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
435 | #  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
436 | # else
437 | #  define YY_ATTRIBUTE_PURE
438 | # endif
439 | #endif
440 | 
441 | #ifndef YY_ATTRIBUTE_UNUSED
442 | # if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
443 | #  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
444 | # else
445 | #  define YY_ATTRIBUTE_UNUSED
446 | # endif
447 | #endif
448 | 
449 | /* Suppress unused-variable warnings by "using" E.  */
450 | #if ! defined lint || defined __GNUC__
451 | # define YY_USE(E) ((void) (E))
452 | #else
453 | # define YY_USE(E) /* empty */
454 | #endif
455 | 
456 | /* Suppress an incorrect diagnostic about yylval being uninitialized.  */
457 | #if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
458 | # if __GNUC__ * 100 + __GNUC_MINOR__ < 407
459 | #  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
460 |     _Pragma ("GCC diagnostic push")                                     \
461 |     _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
462 | # else
463 | #  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
464 |     _Pragma ("GCC diagnostic push")                                     \
465 |     _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
466 |     _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
467 | # endif
468 | # define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
469 |     _Pragma ("GCC diagnostic pop")
470 | #else
471 | # define YY_INITIAL_VALUE(Value) Value
472 | #endif
473 | #ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
474 | # define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
475 | # define YY_IGNORE_MAYBE_UNINITIALIZED_END
476 | #endif
477 | #ifndef YY_INITIAL_VALUE
478 | # define YY_INITIAL_VALUE(Value) /* Nothing. */
479 | #endif
480 | 
481 | #if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
482 | # define YY_IGNORE_USELESS_CAST_BEGIN                          \
483 |     _Pragma ("GCC diagnostic push")                            \
484 |     _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
485 | # define YY_IGNORE_USELESS_CAST_END            \
486 |     _Pragma ("GCC diagnostic pop")
487 | #endif
488 | #ifndef YY_IGNORE_USELESS_CAST_BEGIN
489 | # define YY_IGNORE_USELESS_CAST_BEGIN
490 | # define YY_IGNORE_USELESS_CAST_END
491 | #endif
492 | 
493 | 
494 | #define YY_ASSERT(E) ((void) (0 && (E)))
495 | 
496 | #if 1
497 | 
498 | /* The parser invokes alloca or malloc; define the necessary symbols.  */
499 | 
500 | # ifdef YYSTACK_USE_ALLOCA
501 | #  if YYSTACK_USE_ALLOCA
502 | #   ifdef __GNUC__
503 | #    define YYSTACK_ALLOC __builtin_alloca
504 | #   elif defined __BUILTIN_VA_ARG_INCR
505 | #    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
506 | #   elif defined _AIX
507 | #    define YYSTACK_ALLOC __alloca
508 | #   elif defined _MSC_VER
509 | #    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
510 | #    define alloca _alloca
511 | #   else
512 | #    define YYSTACK_ALLOC alloca
513 | #    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
514 | #     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
515 |       /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
516 | #     ifndef EXIT_SUCCESS
517 | #      define EXIT_SUCCESS 0
518 | #     endif
519 | #    endif
520 | #   endif
521 | #  endif
522 | # endif
523 | 
524 | # ifdef YYSTACK_ALLOC
525 |    /* Pacify GCC's 'empty if-body' warning.  */
526 | #  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
527 | #  ifndef YYSTACK_ALLOC_MAXIMUM
528 |     /* The OS might guarantee only one guard page at the bottom of the stack,
529 |        and a page size can be as small as 4096 bytes.  So we cannot safely
530 |        invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
531 |        to allow for a few compiler-allocated temporary stack slots.  */
532 | #   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
533 | #  endif
534 | # else
535 | #  define YYSTACK_ALLOC YYMALLOC
536 | #  define YYSTACK_FREE YYFREE
537 | #  ifndef YYSTACK_ALLOC_MAXIMUM
538 | #   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
539 | #  endif
540 | #  if (defined __cplusplus && ! defined EXIT_SUCCESS \
541 |        && ! ((defined YYMALLOC || defined malloc) \
542 |              && (defined YYFREE || defined free)))
543 | #   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
544 | #   ifndef EXIT_SUCCESS
545 | #    define EXIT_SUCCESS 0
546 | #   endif
547 | #  endif
548 | #  ifndef YYMALLOC
549 | #   define YYMALLOC malloc
550 | #   if ! defined malloc && ! defined EXIT_SUCCESS
551 | void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
552 | #   endif
553 | #  endif
554 | #  ifndef YYFREE
555 | #   define YYFREE free
556 | #   if ! defined free && ! defined EXIT_SUCCESS
557 | void free (void *); /* INFRINGES ON USER NAME SPACE */
558 | #   endif
559 | #  endif
560 | # endif
561 | #endif /* 1 */
562 | 
563 | #if (! defined yyoverflow \
564 |      && (! defined __cplusplus \
565 |          || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))
566 | 
567 | /* A type that is properly aligned for any stack member.  */
568 | union yyalloc
569 | {
570 |   yy_state_t yyss_alloc;
571 |   YYSTYPE yyvs_alloc;
572 | };
573 | 
574 | /* The size of the maximum gap between one aligned stack and the next.  */
575 | # define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)
576 | 
577 | /* The size of an array large to enough to hold all stacks, each with
578 |    N elements.  */
579 | # define YYSTACK_BYTES(N) \
580 |      ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
581 |       + YYSTACK_GAP_MAXIMUM)
582 | 
583 | # define YYCOPY_NEEDED 1
584 | 
585 | /* Relocate STACK from its old location to the new one.  The
586 |    local variables YYSIZE and YYSTACKSIZE give the old and new number of
587 |    elements in the stack, and YYPTR gives the new location of the
588 |    stack.  Advance YYPTR to a properly aligned location for the next
589 |    stack.  */
590 | # define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
591 |     do                                                                  \
592 |       {                                                                 \
593 |         YYPTRDIFF_T yynewbytes;                                         \
594 |         YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
595 |         Stack = &yyptr->Stack_alloc;                                    \
596 |         yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
597 |         yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
598 |       }                                                                 \
599 |     while (0)
600 | 
601 | #endif
602 | 
603 | #if defined YYCOPY_NEEDED && YYCOPY_NEEDED
604 | /* Copy COUNT objects from SRC to DST.  The source and destination do
605 |    not overlap.  */
606 | # ifndef YYCOPY
607 | #  if defined __GNUC__ && 1 < __GNUC__
608 | #   define YYCOPY(Dst, Src, Count) \
609 |       __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
610 | #  else
611 | #   define YYCOPY(Dst, Src, Count)              \
612 |       do                                        \
613 |         {                                       \
614 |           YYPTRDIFF_T yyi;                      \
615 |           for (yyi = 0; yyi < (Count); yyi++)   \
616 |             (Dst)[yyi] = (Src)[yyi];            \
617 |         }                                       \
618 |       while (0)
619 | #  endif
620 | # endif
621 | #endif /* !YYCOPY_NEEDED */
622 | 
623 | /* YYFINAL -- State number of the termination state.  */
624 | #define YYFINAL  4
625 | /* YYLAST -- Last index in YYTABLE.  */
626 | #define YYLAST   49
627 | 
628 | /* YYNTOKENS -- Number of terminals.  */
629 | #define YYNTOKENS  33
630 | /* YYNNTS -- Number of nonterminals.  */
631 | #define YYNNTS  11
632 | /* YYNRULES -- Number of rules.  */
633 | #define YYNRULES  36
634 | /* YYNSTATES -- Number of states.  */
635 | #define YYNSTATES  58
636 | 
637 | /* YYMAXUTOK -- Last valid token kind.  */
638 | #define YYMAXUTOK   283
639 | 
640 | 
641 | /* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
642 |    as returned by yylex, with out-of-bounds checking.  */
643 | #define YYTRANSLATE(YYX)                                \
644 |   (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
645 |    ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
646 |    : YYSYMBOL_YYUNDEF)
647 | 
648 | /* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
649 |    as returned by yylex.  */
650 | static const yytype_int8 yytranslate[] =
651 | {
652 |        0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
653 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
654 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
655 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
656 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
657 |        2,     2,     2,     2,     2,     2,     2,     2,    32,    31,
658 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
659 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
660 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
661 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
662 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
663 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
664 |        2,     2,     2,    29,     2,    30,     2,     2,     2,     2,
665 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
666 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
667 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
668 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
669 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
670 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
671 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
672 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
673 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
674 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
675 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
676 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
677 |        2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
678 |        5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
679 |       15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
680 |       25,    26,    27,    28
681 | };
682 | 
683 | #if YYDEBUG
684 | /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
685 | static const yytype_int16 yyrline[] =
686 | {
687 |        0,   182,   182,   181,   196,   197,   200,   204,   208,   217,
688 |      232,   233,   234,   242,   257,   258,   259,   260,   261,   262,
689 |      263,   264,   265,   266,   270,   273,   294,   299,   304,   309,
690 |      314,   319,   324,   329,   334,   339,   344
691 | };
692 | #endif
693 | 
694 | /** Accessing symbol of state STATE.  */
695 | #define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])
696 | 
697 | #if 1
698 | /* The user-facing name of the symbol whose (internal) number is
699 |    YYSYMBOL.  No bounds checking.  */
700 | static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;
701 | 
702 | /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
703 |    First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
704 | static const char *const yytname[] =
705 | {
706 |   "\"end of file\"", "error", "\"invalid token\"", "FORM", "SECTION",
707 |   "FIELD", "TEXT", "EMAIL", "PASSWORD", "NUMBER", "TEXTAREA", "DATE",
708 |   "CHECKBOX", "DROPDOWN", "RADIO", "FILE_TYPE", "REQUIRED", "OPTIONAL",
709 |   "MINLENGTH", "MAXLENGTH", "MIN", "MAX", "ROWS", "COLS", "PATTERN",
710 |   "DEFAULT", "IDENTIFIER", "NUMBER_LITERAL", "STRING_LITERAL", "'{'",
711 |   "'}'", "';'", "':'", "$accept", "form", "$@1", "section_list", "section",
712 |   "section_header", "field_list", "field", "field_type",
713 |   "field_attributes", "attribute", YY_NULLPTR
714 | };
715 | 
716 | static const char *
717 | yysymbol_name (yysymbol_kind_t yysymbol)
718 | {
719 |   return yytname[yysymbol];
720 | }
721 | #endif
722 | 
723 | #define YYPACT_NINF (-13)
724 | 
725 | #define yypact_value_is_default(Yyn) \
726 |   ((Yyn) == YYPACT_NINF)
727 | 
728 | #define YYTABLE_NINF (-1)
729 | 
730 | #define yytable_value_is_error(Yyn) \
731 |   0
732 | 
733 | /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
734 |    STATE-NUM.  */
735 | static const yytype_int8 yypact[] =
736 | {
737 |        0,    -9,    18,   -13,   -13,   -10,   -13,    -3,    -5,   -13,
738 |      -13,     1,   -13,    -8,    -7,   -13,   -13,    -1,    -6,    -2,
739 |      -13,   -13,   -13,    -4,    25,   -13,   -13,   -13,   -13,   -13,
740 |      -13,   -13,   -13,   -13,   -13,   -13,   -11,   -13,   -13,    14,
741 |       15,    16,    17,    19,    20,    21,   -12,   -13,   -13,   -13,
742 |      -13,   -13,   -13,   -13,   -13,   -13,   -13,   -13
743 | };
744 | 
745 | /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
746 |    Performed when YYTABLE does not specify something else to do.  Zero
747 |    means the default is an error.  */
748 | static const yytype_int8 yydefact[] =
749 | {
750 |        0,     0,     0,     2,     1,     0,     4,     0,     0,     3,
751 |        5,     0,     9,     0,    10,     8,     7,     0,     0,     0,
752 |        6,    11,    12,     0,     0,    14,    15,    16,    17,    18,
753 |       19,    20,    21,    22,    23,    24,     0,    26,    27,     0,
754 |        0,     0,     0,     0,     0,     0,     0,    13,    25,    28,
755 |       29,    30,    31,    32,    33,    34,    36,    35
756 | };
757 | 
758 | /* YYPGOTO[NTERM-NUM].  */
759 | static const yytype_int8 yypgoto[] =
760 | {
761 |      -13,   -13,   -13,   -13,   -13,   -13,   -13,   -13,   -13,   -13,
762 |      -13
763 | };
764 | 
765 | /* YYDEFGOTO[NTERM-NUM].  */
766 | static const yytype_int8 yydefgoto[] =
767 | {
768 |        0,     2,     5,     7,    10,    11,    17,    21,    35,    36,
769 |       48
770 | };
771 | 
772 | /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
773 |    positive, shift that token.  If negative, reduce the rule whose
774 |    number is the opposite.  If YYTABLE_NINF, syntax error.  */
775 | static const yytype_int8 yytable[] =
776 | {
777 |       18,     8,    13,     1,    19,    37,    38,    39,    40,    41,
778 |       42,    43,    44,    45,    46,    56,    57,     3,     4,     6,
779 |       47,    12,    15,    16,    23,    22,     0,     9,    24,    20,
780 |       14,    25,    26,    27,    28,    29,    30,    31,    32,    33,
781 |       34,    49,    50,    51,    52,     0,    53,    54,     0,    55
782 | };
783 | 
784 | static const yytype_int8 yycheck[] =
785 | {
786 |        1,     4,     1,     3,     5,    16,    17,    18,    19,    20,
787 |       21,    22,    23,    24,    25,    27,    28,    26,     0,    29,
788 |       31,    26,    30,    30,    26,    31,    -1,    30,    32,    30,
789 |       29,     6,     7,     8,     9,    10,    11,    12,    13,    14,
790 |       15,    27,    27,    27,    27,    -1,    27,    27,    -1,    28
791 | };
792 | 
793 | /* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
794 |    state STATE-NUM.  */
795 | static const yytype_int8 yystos[] =
796 | {
797 |        0,     3,    34,    26,     0,    35,    29,    36,     4,    30,
798 |       37,    38,    26,     1,    29,    30,    30,    39,     1,     5,
799 |       30,    40,    31,    26,    32,     6,     7,     8,     9,    10,
800 |       11,    12,    13,    14,    15,    41,    42,    16,    17,    18,
801 |       19,    20,    21,    22,    23,    24,    25,    31,    43,    27,
802 |       27,    27,    27,    27,    27,    28,    27,    28
803 | };
804 | 
805 | /* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
806 | static const yytype_int8 yyr1[] =
807 | {
808 |        0,    33,    35,    34,    36,    36,    37,    37,    37,    38,
809 |       39,    39,    39,    40,    41,    41,    41,    41,    41,    41,
810 |       41,    41,    41,    41,    42,    42,    43,    43,    43,    43,
811 |       43,    43,    43,    43,    43,    43,    43
812 | };
813 | 
814 | /* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
815 | static const yytype_int8 yyr2[] =
816 | {
817 |        0,     2,     0,     6,     0,     2,     4,     3,     3,     2,
818 |        0,     2,     3,     6,     1,     1,     1,     1,     1,     1,
819 |        1,     1,     1,     1,     0,     2,     1,     1,     2,     2,
820 |        2,     2,     2,     2,     2,     2,     2
821 | };
822 | 
823 | 
824 | enum { YYENOMEM = -2 };
825 | 
826 | #define yyerrok         (yyerrstatus = 0)
827 | #define yyclearin       (yychar = YYEMPTY)
828 | 
829 | #define YYACCEPT        goto yyacceptlab
830 | #define YYABORT         goto yyabortlab
831 | #define YYERROR         goto yyerrorlab
832 | #define YYNOMEM         goto yyexhaustedlab
833 | 
834 | 
835 | #define YYRECOVERING()  (!!yyerrstatus)
836 | 
837 | #define YYBACKUP(Token, Value)                                    \
838 |   do                                                              \
839 |     if (yychar == YYEMPTY)                                        \
840 |       {                                                           \
841 |         yychar = (Token);                                         \
842 |         yylval = (Value);                                         \
843 |         YYPOPSTACK (yylen);                                       \
844 |         yystate = *yyssp;                                         \
845 |         goto yybackup;                                            \
846 |       }                                                           \
847 |     else                                                          \
848 |       {                                                           \
849 |         yyerror (YY_("syntax error: cannot back up")); \
850 |         YYERROR;                                                  \
851 |       }                                                           \
852 |   while (0)
853 | 
854 | /* Backward compatibility with an undocumented macro.
855 |    Use YYerror or YYUNDEF. */
856 | #define YYERRCODE YYUNDEF
857 | 
858 | 
859 | /* Enable debugging if requested.  */
860 | #if YYDEBUG
861 | 
862 | # ifndef YYFPRINTF
863 | #  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
864 | #  define YYFPRINTF fprintf
865 | # endif
866 | 
867 | # define YYDPRINTF(Args)                        \
868 | do {                                            \
869 |   if (yydebug)                                  \
870 |     YYFPRINTF Args;                             \
871 | } while (0)
872 | 
873 | 
874 | 
875 | 
876 | # define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
877 | do {                                                                      \
878 |   if (yydebug)                                                            \
879 |     {                                                                     \
880 |       YYFPRINTF (stderr, "%s ", Title);                                   \
881 |       yy_symbol_print (stderr,                                            \
882 |                   Kind, Value); \
883 |       YYFPRINTF (stderr, "\n");                                           \
884 |     }                                                                     \
885 | } while (0)
886 | 
887 | 
888 | /*-----------------------------------.
889 | | Print this symbol's value on YYO.  |
890 | `-----------------------------------*/
891 | 
892 | static void
893 | yy_symbol_value_print (FILE *yyo,
894 |                        yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
895 | {
896 |   FILE *yyoutput = yyo;
897 |   YY_USE (yyoutput);
898 |   if (!yyvaluep)
899 |     return;
900 |   YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
901 |   YY_USE (yykind);
902 |   YY_IGNORE_MAYBE_UNINITIALIZED_END
903 | }
904 | 
905 | 
906 | /*---------------------------.
907 | | Print this symbol on YYO.  |
908 | `---------------------------*/
909 | 
910 | static void
911 | yy_symbol_print (FILE *yyo,
912 |                  yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
913 | {
914 |   YYFPRINTF (yyo, "%s %s (",
915 |              yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));
916 | 
917 |   yy_symbol_value_print (yyo, yykind, yyvaluep);
918 |   YYFPRINTF (yyo, ")");
919 | }
920 | 
921 | /*------------------------------------------------------------------.
922 | | yy_stack_print -- Print the state stack from its BOTTOM up to its |
923 | | TOP (included).                                                   |
924 | `------------------------------------------------------------------*/
925 | 
926 | static void
927 | yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
928 | {
929 |   YYFPRINTF (stderr, "Stack now");
930 |   for (; yybottom <= yytop; yybottom++)
931 |     {
932 |       int yybot = *yybottom;
933 |       YYFPRINTF (stderr, " %d", yybot);
934 |     }
935 |   YYFPRINTF (stderr, "\n");
936 | }
937 | 
938 | # define YY_STACK_PRINT(Bottom, Top)                            \
939 | do {                                                            \
940 |   if (yydebug)                                                  \
941 |     yy_stack_print ((Bottom), (Top));                           \
942 | } while (0)
943 | 
944 | 
945 | /*------------------------------------------------.
946 | | Report that the YYRULE is going to be reduced.  |
947 | `------------------------------------------------*/
948 | 
949 | static void
950 | yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
951 |                  int yyrule)
952 | {
953 |   int yylno = yyrline[yyrule];
954 |   int yynrhs = yyr2[yyrule];
955 |   int yyi;
956 |   YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
957 |              yyrule - 1, yylno);
958 |   /* The symbols being reduced.  */
959 |   for (yyi = 0; yyi < yynrhs; yyi++)
960 |     {
961 |       YYFPRINTF (stderr, "   $%d = ", yyi + 1);
962 |       yy_symbol_print (stderr,
963 |                        YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
964 |                        &yyvsp[(yyi + 1) - (yynrhs)]);
965 |       YYFPRINTF (stderr, "\n");
966 |     }
967 | }
968 | 
969 | # define YY_REDUCE_PRINT(Rule)          \
970 | do {                                    \
971 |   if (yydebug)                          \
972 |     yy_reduce_print (yyssp, yyvsp, Rule); \
973 | } while (0)
974 | 
975 | /* Nonzero means print parse trace.  It is left uninitialized so that
976 |    multiple parsers can coexist.  */
977 | int yydebug;
978 | #else /* !YYDEBUG */
979 | # define YYDPRINTF(Args) ((void) 0)
980 | # define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
981 | # define YY_STACK_PRINT(Bottom, Top)
982 | # define YY_REDUCE_PRINT(Rule)
983 | #endif /* !YYDEBUG */
984 | 
985 | 
986 | /* YYINITDEPTH -- initial size of the parser's stacks.  */
987 | #ifndef YYINITDEPTH
988 | # define YYINITDEPTH 200
989 | #endif
990 | 
991 | /* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
992 |    if the built-in stack extension method is used).
993 | 
994 |    Do not make this value too large; the results are undefined if
995 |    YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
996 |    evaluated with infinite-precision integer arithmetic.  */
997 | 
998 | #ifndef YYMAXDEPTH
999 | # define YYMAXDEPTH 10000
1000 | #endif
1001 | 
1002 | 
1003 | /* Context of a parse error.  */
1004 | typedef struct
1005 | {
1006 |   yy_state_t *yyssp;
1007 |   yysymbol_kind_t yytoken;
1008 | } yypcontext_t;
1009 | 
1010 | /* Put in YYARG at most YYARGN of the expected tokens given the
1011 |    current YYCTX, and return the number of tokens stored in YYARG.  If
1012 |    YYARG is null, return the number of expected tokens (guaranteed to
1013 |    be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
1014 |    Return 0 if there are more than YYARGN expected tokens, yet fill
1015 |    YYARG up to YYARGN. */
1016 | static int
1017 | yypcontext_expected_tokens (const yypcontext_t *yyctx,
1018 |                             yysymbol_kind_t yyarg[], int yyargn)
1019 | {
1020 |   /* Actual size of YYARG. */
1021 |   int yycount = 0;
1022 |   int yyn = yypact[+*yyctx->yyssp];
1023 |   if (!yypact_value_is_default (yyn))
1024 |     {
1025 |       /* Start YYX at -YYN if negative to avoid negative indexes in
1026 |          YYCHECK.  In other words, skip the first -YYN actions for
1027 |          this state because they are default actions.  */
1028 |       int yyxbegin = yyn < 0 ? -yyn : 0;
1029 |       /* Stay within bounds of both yycheck and yytname.  */
1030 |       int yychecklim = YYLAST - yyn + 1;
1031 |       int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
1032 |       int yyx;
1033 |       for (yyx = yyxbegin; yyx < yyxend; ++yyx)
1034 |         if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
1035 |             && !yytable_value_is_error (yytable[yyx + yyn]))
1036 |           {
1037 |             if (!yyarg)
1038 |               ++yycount;
1039 |             else if (yycount == yyargn)
1040 |               return 0;
1041 |             else
1042 |               yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
1043 |           }
1044 |     }
1045 |   if (yyarg && yycount == 0 && 0 < yyargn)
1046 |     yyarg[0] = YYSYMBOL_YYEMPTY;
1047 |   return yycount;
1048 | }
1049 | 
1050 | 
1051 | 
1052 | 
1053 | #ifndef yystrlen
1054 | # if defined __GLIBC__ && defined _STRING_H
1055 | #  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
1056 | # else
1057 | /* Return the length of YYSTR.  */
1058 | static YYPTRDIFF_T
1059 | yystrlen (const char *yystr)
1060 | {
1061 |   YYPTRDIFF_T yylen;
1062 |   for (yylen = 0; yystr[yylen]; yylen++)
1063 |     continue;
1064 |   return yylen;
1065 | }
1066 | # endif
1067 | #endif
1068 | 
1069 | #ifndef yystpcpy
1070 | # if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
1071 | #  define yystpcpy stpcpy
1072 | # else
1073 | /* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
1074 |    YYDEST.  */
1075 | static char *
1076 | yystpcpy (char *yydest, const char *yysrc)
1077 | {
1078 |   char *yyd = yydest;
1079 |   const char *yys = yysrc;
1080 | 
1081 |   while ((*yyd++ = *yys++) != '\0')
1082 |     continue;
1083 | 
1084 |   return yyd - 1;
1085 | }
1086 | # endif
1087 | #endif
1088 | 
1089 | #ifndef yytnamerr
1090 | /* Copy to YYRES the contents of YYSTR after stripping away unnecessary
1091 |    quotes and backslashes, so that it's suitable for yyerror.  The
1092 |    heuristic is that double-quoting is unnecessary unless the string
1093 |    contains an apostrophe, a comma, or backslash (other than
1094 |    backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
1095 |    null, do not copy; instead, return the length of what the result
1096 |    would have been.  */
1097 | static YYPTRDIFF_T
1098 | yytnamerr (char *yyres, const char *yystr)
1099 | {
1100 |   if (*yystr == '"')
1101 |     {
1102 |       YYPTRDIFF_T yyn = 0;
1103 |       char const *yyp = yystr;
1104 |       for (;;)
1105 |         switch (*++yyp)
1106 |           {
1107 |           case '\'':
1108 |           case ',':
1109 |             goto do_not_strip_quotes;
1110 | 
1111 |           case '\\':
1112 |             if (*++yyp != '\\')
1113 |               goto do_not_strip_quotes;
1114 |             else
1115 |               goto append;
1116 | 
1117 |           append:
1118 |           default:
1119 |             if (yyres)
1120 |               yyres[yyn] = *yyp;
1121 |             yyn++;
1122 |             break;
1123 | 
1124 |           case '"':
1125 |             if (yyres)
1126 |               yyres[yyn] = '\0';
1127 |             return yyn;
1128 |           }
1129 |     do_not_strip_quotes: ;
1130 |     }
1131 | 
1132 |   if (yyres)
1133 |     return yystpcpy (yyres, yystr) - yyres;
1134 |   else
1135 |     return yystrlen (yystr);
1136 | }
1137 | #endif
1138 | 
1139 | 
1140 | static int
1141 | yy_syntax_error_arguments (const yypcontext_t *yyctx,
1142 |                            yysymbol_kind_t yyarg[], int yyargn)
1143 | {
1144 |   /* Actual size of YYARG. */
1145 |   int yycount = 0;
1146 |   /* There are many possibilities here to consider:
1147 |      - If this state is a consistent state with a default action, then
1148 |        the only way this function was invoked is if the default action
1149 |        is an error action.  In that case, don't check for expected
1150 |        tokens because there are none.
1151 |      - The only way there can be no lookahead present (in yychar) is if
1152 |        this state is a consistent state with a default action.  Thus,
1153 |        detecting the absence of a lookahead is sufficient to determine
1154 |        that there is no unexpected or expected token to report.  In that
1155 |        case, just report a simple "syntax error".
1156 |      - Don't assume there isn't a lookahead just because this state is a
1157 |        consistent state with a default action.  There might have been a
1158 |        previous inconsistent state, consistent state with a non-default
1159 |        action, or user semantic action that manipulated yychar.
1160 |      - Of course, the expected token list depends on states to have
1161 |        correct lookahead information, and it depends on the parser not
1162 |        to perform extra reductions after fetching a lookahead from the
1163 |        scanner and before detecting a syntax error.  Thus, state merging
1164 |        (from LALR or IELR) and default reductions corrupt the expected
1165 |        token list.  However, the list is correct for canonical LR with
1166 |        one exception: it will still contain any token that will not be
1167 |        accepted due to an error action in a later state.
1168 |   */
1169 |   if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
1170 |     {
1171 |       int yyn;
1172 |       if (yyarg)
1173 |         yyarg[yycount] = yyctx->yytoken;
1174 |       ++yycount;
1175 |       yyn = yypcontext_expected_tokens (yyctx,
1176 |                                         yyarg ? yyarg + 1 : yyarg, yyargn - 1);
1177 |       if (yyn == YYENOMEM)
1178 |         return YYENOMEM;
1179 |       else
1180 |         yycount += yyn;
1181 |     }
1182 |   return yycount;
1183 | }
1184 | 
1185 | /* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
1186 |    about the unexpected token YYTOKEN for the state stack whose top is
1187 |    YYSSP.
1188 | 
1189 |    Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
1190 |    not large enough to hold the message.  In that case, also set
1191 |    *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
1192 |    required number of bytes is too large to store.  */
1193 | static int
1194 | yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
1195 |                 const yypcontext_t *yyctx)
1196 | {
1197 |   enum { YYARGS_MAX = 5 };
1198 |   /* Internationalized format string. */
1199 |   const char *yyformat = YY_NULLPTR;
1200 |   /* Arguments of yyformat: reported tokens (one for the "unexpected",
1201 |      one per "expected"). */
1202 |   yysymbol_kind_t yyarg[YYARGS_MAX];
1203 |   /* Cumulated lengths of YYARG.  */
1204 |   YYPTRDIFF_T yysize = 0;
1205 | 
1206 |   /* Actual size of YYARG. */
1207 |   int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
1208 |   if (yycount == YYENOMEM)
1209 |     return YYENOMEM;
1210 | 
1211 |   switch (yycount)
1212 |     {
1213 | #define YYCASE_(N, S)                       \
1214 |       case N:                               \
1215 |         yyformat = S;                       \
1216 |         break
1217 |     default: /* Avoid compiler warnings. */
1218 |       YYCASE_(0, YY_("syntax error"));
1219 |       YYCASE_(1, YY_("syntax error, unexpected %s"));
1220 |       YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
1221 |       YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
1222 |       YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
1223 |       YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
1224 | #undef YYCASE_
1225 |     }
1226 | 
1227 |   /* Compute error message size.  Don't count the "%s"s, but reserve
1228 |      room for the terminator.  */
1229 |   yysize = yystrlen (yyformat) - 2 * yycount + 1;
1230 |   {
1231 |     int yyi;
1232 |     for (yyi = 0; yyi < yycount; ++yyi)
1233 |       {
1234 |         YYPTRDIFF_T yysize1
1235 |           = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
1236 |         if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
1237 |           yysize = yysize1;
1238 |         else
1239 |           return YYENOMEM;
1240 |       }
1241 |   }
1242 | 
1243 |   if (*yymsg_alloc < yysize)
1244 |     {
1245 |       *yymsg_alloc = 2 * yysize;
1246 |       if (! (yysize <= *yymsg_alloc
1247 |              && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
1248 |         *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
1249 |       return -1;
1250 |     }
1251 | 
1252 |   /* Avoid sprintf, as that infringes on the user's name space.
1253 |      Don't have undefined behavior even if the translation
1254 |      produced a string with the wrong number of "%s"s.  */
1255 |   {
1256 |     char *yyp = *yymsg;
1257 |     int yyi = 0;
1258 |     while ((*yyp = *yyformat) != '\0')
1259 |       if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
1260 |         {
1261 |           yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
1262 |           yyformat += 2;
1263 |         }
1264 |       else
1265 |         {
1266 |           ++yyp;
1267 |           ++yyformat;
1268 |         }
1269 |   }
1270 |   return 0;
1271 | }
1272 | 
1273 | 
1274 | /*-----------------------------------------------.
1275 | | Release the memory associated to this symbol.  |
1276 | `-----------------------------------------------*/
1277 | 
1278 | static void
1279 | yydestruct (const char *yymsg,
1280 |             yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
1281 | {
1282 |   YY_USE (yyvaluep);
1283 |   if (!yymsg)
1284 |     yymsg = "Deleting";
1285 |   YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);
1286 | 
1287 |   YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
1288 |   YY_USE (yykind);
1289 |   YY_IGNORE_MAYBE_UNINITIALIZED_END
1290 | }
1291 | 
1292 | 
1293 | /* Lookahead token kind.  */
1294 | int yychar;
1295 | 
1296 | /* The semantic value of the lookahead symbol.  */
1297 | YYSTYPE yylval;
1298 | /* Number of syntax errors so far.  */
1299 | int yynerrs;
1300 | 
1301 | 
1302 | 
1303 | 
1304 | /*----------.
1305 | | yyparse.  |
1306 | `----------*/
1307 | 
1308 | int
1309 | yyparse (void)
1310 | {
1311 |     yy_state_fast_t yystate = 0;
1312 |     /* Number of tokens to shift before error messages enabled.  */
1313 |     int yyerrstatus = 0;
1314 | 
1315 |     /* Refer to the stacks through separate pointers, to allow yyoverflow
1316 |        to reallocate them elsewhere.  */
1317 | 
1318 |     /* Their size.  */
1319 |     YYPTRDIFF_T yystacksize = YYINITDEPTH;
1320 | 
1321 |     /* The state stack: array, bottom, top.  */
1322 |     yy_state_t yyssa[YYINITDEPTH];
1323 |     yy_state_t *yyss = yyssa;
1324 |     yy_state_t *yyssp = yyss;
1325 | 
1326 |     /* The semantic value stack: array, bottom, top.  */
1327 |     YYSTYPE yyvsa[YYINITDEPTH];
1328 |     YYSTYPE *yyvs = yyvsa;
1329 |     YYSTYPE *yyvsp = yyvs;
1330 | 
1331 |   int yyn;
1332 |   /* The return value of yyparse.  */
1333 |   int yyresult;
1334 |   /* Lookahead symbol kind.  */
1335 |   yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
1336 |   /* The variables used to return semantic value and location from the
1337 |      action routines.  */
1338 |   YYSTYPE yyval;
1339 | 
1340 |   /* Buffer for error messages, and its allocated size.  */
1341 |   char yymsgbuf[128];
1342 |   char *yymsg = yymsgbuf;
1343 |   YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
1344 | 
1345 | #define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))
1346 | 
1347 |   /* The number of symbols on the RHS of the reduced rule.
1348 |      Keep to zero when no symbol should be popped.  */
1349 |   int yylen = 0;
1350 | 
1351 |   YYDPRINTF ((stderr, "Starting parse\n"));
1352 | 
1353 |   yychar = YYEMPTY; /* Cause a token to be read.  */
1354 | 
1355 |   goto yysetstate;
1356 | 
1357 | 
1358 | /*------------------------------------------------------------.
1359 | | yynewstate -- push a new state, which is found in yystate.  |
1360 | `------------------------------------------------------------*/
1361 | yynewstate:
1362 |   /* In all cases, when you get here, the value and location stacks
1363 |      have just been pushed.  So pushing a state here evens the stacks.  */
1364 |   yyssp++;
1365 | 
1366 | 
1367 | /*--------------------------------------------------------------------.
1368 | | yysetstate -- set current state (the top of the stack) to yystate.  |
1369 | `--------------------------------------------------------------------*/
1370 | yysetstate:
1371 |   YYDPRINTF ((stderr, "Entering state %d\n", yystate));
1372 |   YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
1373 |   YY_IGNORE_USELESS_CAST_BEGIN
1374 |   *yyssp = YY_CAST (yy_state_t, yystate);
1375 |   YY_IGNORE_USELESS_CAST_END
1376 |   YY_STACK_PRINT (yyss, yyssp);
1377 | 
1378 |   if (yyss + yystacksize - 1 <= yyssp)
1379 | #if !defined yyoverflow && !defined YYSTACK_RELOCATE
1380 |     YYNOMEM;
1381 | #else
1382 |     {
1383 |       /* Get the current used size of the three stacks, in elements.  */
1384 |       YYPTRDIFF_T yysize = yyssp - yyss + 1;
1385 | 
1386 | # if defined yyoverflow
1387 |       {
1388 |         /* Give user a chance to reallocate the stack.  Use copies of
1389 |            these so that the &'s don't force the real ones into
1390 |            memory.  */
1391 |         yy_state_t *yyss1 = yyss;
1392 |         YYSTYPE *yyvs1 = yyvs;
1393 | 
1394 |         /* Each stack pointer address is followed by the size of the
1395 |            data in use in that stack, in bytes.  This used to be a
1396 |            conditional around just the two extra args, but that might
1397 |            be undefined if yyoverflow is a macro.  */
1398 |         yyoverflow (YY_("memory exhausted"),
1399 |                     &yyss1, yysize * YYSIZEOF (*yyssp),
1400 |                     &yyvs1, yysize * YYSIZEOF (*yyvsp),
1401 |                     &yystacksize);
1402 |         yyss = yyss1;
1403 |         yyvs = yyvs1;
1404 |       }
1405 | # else /* defined YYSTACK_RELOCATE */
1406 |       /* Extend the stack our own way.  */
1407 |       if (YYMAXDEPTH <= yystacksize)
1408 |         YYNOMEM;
1409 |       yystacksize *= 2;
1410 |       if (YYMAXDEPTH < yystacksize)
1411 |         yystacksize = YYMAXDEPTH;
1412 | 
1413 |       {
1414 |         yy_state_t *yyss1 = yyss;
1415 |         union yyalloc *yyptr =
1416 |           YY_CAST (union yyalloc *,
1417 |                    YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
1418 |         if (! yyptr)
1419 |           YYNOMEM;
1420 |         YYSTACK_RELOCATE (yyss_alloc, yyss);
1421 |         YYSTACK_RELOCATE (yyvs_alloc, yyvs);
1422 | #  undef YYSTACK_RELOCATE
1423 |         if (yyss1 != yyssa)
1424 |           YYSTACK_FREE (yyss1);
1425 |       }
1426 | # endif
1427 | 
1428 |       yyssp = yyss + yysize - 1;
1429 |       yyvsp = yyvs + yysize - 1;
1430 | 
1431 |       YY_IGNORE_USELESS_CAST_BEGIN
1432 |       YYDPRINTF ((stderr, "Stack size increased to %ld\n",
1433 |                   YY_CAST (long, yystacksize)));
1434 |       YY_IGNORE_USELESS_CAST_END
1435 | 
1436 |       if (yyss + yystacksize - 1 <= yyssp)
1437 |         YYABORT;
1438 |     }
1439 | #endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */
1440 | 
1441 | 
1442 |   if (yystate == YYFINAL)
1443 |     YYACCEPT;
1444 | 
1445 |   goto yybackup;
1446 | 
1447 | 
1448 | /*-----------.
1449 | | yybackup.  |
1450 | `-----------*/
1451 | yybackup:
1452 |   /* Do appropriate processing given the current state.  Read a
1453 |      lookahead token if we need one and don't already have one.  */
1454 | 
1455 |   /* First try to decide what to do without reference to lookahead token.  */
1456 |   yyn = yypact[yystate];
1457 |   if (yypact_value_is_default (yyn))
1458 |     goto yydefault;
1459 | 
1460 |   /* Not known => get a lookahead token if don't already have one.  */
1461 | 
1462 |   /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
1463 |   if (yychar == YYEMPTY)
1464 |     {
1465 |       YYDPRINTF ((stderr, "Reading a token\n"));
1466 |       yychar = yylex ();
1467 |     }
1468 | 
1469 |   if (yychar <= YYEOF)
1470 |     {
1471 |       yychar = YYEOF;
1472 |       yytoken = YYSYMBOL_YYEOF;
1473 |       YYDPRINTF ((stderr, "Now at end of input.\n"));
1474 |     }
1475 |   else if (yychar == YYerror)
1476 |     {
1477 |       /* The scanner already issued an error message, process directly
1478 |          to error recovery.  But do not keep the error token as
1479 |          lookahead, it is too special and may lead us to an endless
1480 |          loop in error recovery. */
1481 |       yychar = YYUNDEF;
1482 |       yytoken = YYSYMBOL_YYerror;
1483 |       goto yyerrlab1;
1484 |     }
1485 |   else
1486 |     {
1487 |       yytoken = YYTRANSLATE (yychar);
1488 |       YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
1489 |     }
1490 | 
1491 |   /* If the proper action on seeing token YYTOKEN is to reduce or to
1492 |      detect an error, take that action.  */
1493 |   yyn += yytoken;
1494 |   if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
1495 |     goto yydefault;
1496 |   yyn = yytable[yyn];
1497 |   if (yyn <= 0)
1498 |     {
1499 |       if (yytable_value_is_error (yyn))
1500 |         goto yyerrlab;
1501 |       yyn = -yyn;
1502 |       goto yyreduce;
1503 |     }
1504 | 
1505 |   /* Count tokens shifted since error; after three, turn off error
1506 |      status.  */
1507 |   if (yyerrstatus)
1508 |     yyerrstatus--;
1509 | 
1510 |   /* Shift the lookahead token.  */
1511 |   YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
1512 |   yystate = yyn;
1513 |   YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
1514 |   *++yyvsp = yylval;
1515 |   YY_IGNORE_MAYBE_UNINITIALIZED_END
1516 | 
1517 |   /* Discard the shifted token.  */
1518 |   yychar = YYEMPTY;
1519 |   goto yynewstate;
1520 | 
1521 | 
1522 | /*-----------------------------------------------------------.
1523 | | yydefault -- do the default action for the current state.  |
1524 | `-----------------------------------------------------------*/
1525 | yydefault:
1526 |   yyn = yydefact[yystate];
1527 |   if (yyn == 0)
1528 |     goto yyerrlab;
1529 |   goto yyreduce;
1530 | 
1531 | 
1532 | /*-----------------------------.
1533 | | yyreduce -- do a reduction.  |
1534 | `-----------------------------*/
1535 | yyreduce:
1536 |   /* yyn is the number of a rule to reduce with.  */
1537 |   yylen = yyr2[yyn];
1538 | 
1539 |   /* If YYLEN is nonzero, implement the default value of the action:
1540 |      '$$ = $1'.
1541 | 
1542 |      Otherwise, the following line sets YYVAL to garbage.
1543 |      This behavior is undocumented and Bison
1544 |      users should not rely upon it.  Assigning to YYVAL
1545 |      unconditionally makes the parser a bit smaller, and it avoids a
1546 |      GCC warning that YYVAL may be used uninitialized.  */
1547 |   yyval = yyvsp[1-yylen];
1548 | 
1549 | 
1550 |   YY_REDUCE_PRINT (yyn);
1551 |   switch (yyn)
1552 |     {
1553 |   case 2: /* $@1: %empty  */
1554 | #line 182 "src/parser.y"
1555 |     {
1556 |         current_form = create_form((yyvsp[0].str));
1557 |         if (!current_form) {
1558 |             yyerror("Failed to create form");
1559 |             YYERROR;
1560 |         }
1561 |     }
1562 | #line 1563 "src/parser.tab.c"
1563 |     break;
1564 | 
1565 |   case 3: /* form: FORM IDENTIFIER $@1 '{' section_list '}'  */
1566 | #line 190 "src/parser.y"
1567 |     {
1568 |         generate_html(stdout);
1569 |         (yyval.form) = current_form;
1570 |     }
1571 | #line 1572 "src/parser.tab.c"
1572 |     break;
1573 | 
1574 |   case 6: /* section: section_header '{' field_list '}'  */
1575 | #line 201 "src/parser.y"
1576 |     {
1577 |         current_section = NULL;
1578 |     }
1579 | #line 1580 "src/parser.tab.c"
1580 |     break;
1581 | 
1582 |   case 7: /* section: section_header '{' '}'  */
1583 | #line 205 "src/parser.y"
1584 |     {
1585 |         current_section = NULL;
1586 |     }
1587 | #line 1588 "src/parser.tab.c"
1588 |     break;
1589 | 
1590 |   case 8: /* section: section_header error '}'  */
1591 | #line 209 "src/parser.y"
1592 |     {
1593 |         yyerror("Invalid section declaration");
1594 |         current_section = NULL;
1595 |         yyclearin;
1596 |         yyerrok;
1597 |     }
1598 | #line 1599 "src/parser.tab.c"
1599 |     break;
1600 | 
1601 |   case 9: /* section_header: SECTION IDENTIFIER  */
1602 | #line 218 "src/parser.y"
1603 |     {
1604 |         if (current_section != NULL) {
1605 |             yyerror("Nested sections are not allowed");
1606 |             YYERROR;
1607 |         }
1608 |         current_section = create_section((yyvsp[0].str));
1609 |         if (!current_section) {
1610 |             yyerror("Failed to create section");
1611 |             YYERROR;
1612 |         }
1613 |         add_section_to_form(current_form, current_section);
1614 |     }
1615 | #line 1616 "src/parser.tab.c"
1616 |     break;
1617 | 
1618 |   case 12: /* field_list: field_list error ';'  */
1619 | #line 235 "src/parser.y"
1620 |     {
1621 |         yyerror("Invalid field declaration");
1622 |         yyclearin;
1623 |         yyerrok;
1624 |     }
1625 | #line 1626 "src/parser.tab.c"
1626 |     break;
1627 | 
1628 |   case 13: /* field: FIELD IDENTIFIER ':' field_type field_attributes ';'  */
1629 | #line 243 "src/parser.y"
1630 |     {
1631 |         if (current_section == NULL) {
1632 |             yyerror("Field must be inside a section");
1633 |             YYERROR;
1634 |         }
1635 |         if (check_duplicate_field((yyvsp[-4].str))) {
1636 |             yyerror("Duplicate field name found");
1637 |             YYERROR;
1638 |         }
1639 |         add_field_to_section(current_section, (yyvsp[-4].str), (yyvsp[-2].field_type), &(yyvsp[-1].field_attrs));
1640 |         free((yyvsp[-4].str)); // Free the identifier after use
1641 |     }
1642 | #line 1643 "src/parser.tab.c"
1643 |     break;
1644 | 
1645 |   case 14: /* field_type: TEXT  */
1646 | #line 257 "src/parser.y"
1647 |                            { (yyval.field_type) = FIELD_TEXT; }
1648 | #line 1649 "src/parser.tab.c"
1649 |     break;
1650 | 
1651 |   case 15: /* field_type: EMAIL  */
1652 | #line 258 "src/parser.y"
1653 |                            { (yyval.field_type) = FIELD_EMAIL; }
1654 | #line 1655 "src/parser.tab.c"
1655 |     break;
1656 | 
1657 |   case 16: /* field_type: PASSWORD  */
1658 | #line 259 "src/parser.y"
1659 |                            { (yyval.field_type) = FIELD_PASSWORD; }
1660 | #line 1661 "src/parser.tab.c"
1661 |     break;
1662 | 
1663 |   case 17: /* field_type: NUMBER  */
1664 | #line 260 "src/parser.y"
1665 |                            { (yyval.field_type) = FIELD_NUMBER; }
1666 | #line 1667 "src/parser.tab.c"
1667 |     break;
1668 | 
1669 |   case 18: /* field_type: TEXTAREA  */
1670 | #line 261 "src/parser.y"
1671 |                            { (yyval.field_type) = FIELD_TEXTAREA; }
1672 | #line 1673 "src/parser.tab.c"
1673 |     break;
1674 | 
1675 |   case 19: /* field_type: DATE  */
1676 | #line 262 "src/parser.y"
1677 |                            { (yyval.field_type) = FIELD_DATE; }
1678 | #line 1679 "src/parser.tab.c"
1679 |     break;
1680 | 
1681 |   case 20: /* field_type: CHECKBOX  */
1682 | #line 263 "src/parser.y"
1683 |                            { (yyval.field_type) = FIELD_CHECKBOX; }
1684 | #line 1685 "src/parser.tab.c"
1685 |     break;
1686 | 
1687 |   case 21: /* field_type: DROPDOWN  */
1688 | #line 264 "src/parser.y"
1689 |                            { (yyval.field_type) = FIELD_DROPDOWN; }
1690 | #line 1691 "src/parser.tab.c"
1691 |     break;
1692 | 
1693 |   case 22: /* field_type: RADIO  */
1694 | #line 265 "src/parser.y"
1695 |                            { (yyval.field_type) = FIELD_RADIO; }
1696 | #line 1697 "src/parser.tab.c"
1697 |     break;
1698 | 
1699 |   case 23: /* field_type: FILE_TYPE  */
1700 | #line 266 "src/parser.y"
1701 |                            { (yyval.field_type) = FIELD_FILE; }
1702 | #line 1703 "src/parser.tab.c"
1703 |     break;
1704 | 
1705 |   case 24: /* field_attributes: %empty  */
1706 | #line 270 "src/parser.y"
1707 |     {
1708 |         init_field_attributes(&(yyval.field_attrs));
1709 |     }
1710 | #line 1711 "src/parser.tab.c"
1711 |     break;
1712 | 
1713 |   case 25: /* field_attributes: field_attributes attribute  */
1714 | #line 274 "src/parser.y"
1715 |     {
1716 |         (yyval.field_attrs) = (yyvsp[-1].field_attrs);
1717 |         if ((yyvsp[0].field_attrs).required != -1) (yyval.field_attrs).required = (yyvsp[0].field_attrs).required;
1718 |         if ((yyvsp[0].field_attrs).min_length != -1) (yyval.field_attrs).min_length = (yyvsp[0].field_attrs).min_length;
1719 |         if ((yyvsp[0].field_attrs).max_length != -1) (yyval.field_attrs).max_length = (yyvsp[0].field_attrs).max_length;
1720 |         if ((yyvsp[0].field_attrs).min_value != -1) (yyval.field_attrs).min_value = (yyvsp[0].field_attrs).min_value;
1721 |         if ((yyvsp[0].field_attrs).max_value != -1) (yyval.field_attrs).max_value = (yyvsp[0].field_attrs).max_value;
1722 |         if ((yyvsp[0].field_attrs).rows != -1) (yyval.field_attrs).rows = (yyvsp[0].field_attrs).rows;
1723 |         if ((yyvsp[0].field_attrs).cols != -1) (yyval.field_attrs).cols = (yyvsp[0].field_attrs).cols;
1724 |         if ((yyvsp[0].field_attrs).pattern) {
1725 |             if ((yyval.field_attrs).pattern) free((yyval.field_attrs).pattern);
1726 |             (yyval.field_attrs).pattern = strdup((yyvsp[0].field_attrs).pattern);
1727 |         }
1728 |         if ((yyvsp[0].field_attrs).default_value) {
1729 |             if ((yyval.field_attrs).default_value) free((yyval.field_attrs).default_value);
1730 |             (yyval.field_attrs).default_value = strdup((yyvsp[0].field_attrs).default_value);
1731 |         }
1732 |     }
1733 | #line 1734 "src/parser.tab.c"
1734 |     break;
1735 | 
1736 |   case 26: /* attribute: REQUIRED  */
1737 | #line 295 "src/parser.y"
1738 |     {
1739 |         init_field_attributes(&(yyval.field_attrs));
1740 |         (yyval.field_attrs).required = 1;
1741 |     }
1742 | #line 1743 "src/parser.tab.c"
1743 |     break;
1744 | 
1745 |   case 27: /* attribute: OPTIONAL  */
1746 | #line 300 "src/parser.y"
1747 |     {
1748 |         init_field_attributes(&(yyval.field_attrs));
1749 |         (yyval.field_attrs).required = 0;
1750 |     }
1751 | #line 1752 "src/parser.tab.c"
1752 |     break;
1753 | 
1754 |   case 28: /* attribute: MINLENGTH NUMBER_LITERAL  */
1755 | #line 305 "src/parser.y"
1756 |     {
1757 |         init_field_attributes(&(yyval.field_attrs));
1758 |         (yyval.field_attrs).min_length = (yyvsp[0].num);
1759 |     }
1760 | #line 1761 "src/parser.tab.c"
1761 |     break;
1762 | 
1763 |   case 29: /* attribute: MAXLENGTH NUMBER_LITERAL  */
1764 | #line 310 "src/parser.y"
1765 |     {
1766 |         init_field_attributes(&(yyval.field_attrs));
1767 |         (yyval.field_attrs).max_length = (yyvsp[0].num);
1768 |     }
1769 | #line 1770 "src/parser.tab.c"
1770 |     break;
1771 | 
1772 |   case 30: /* attribute: MIN NUMBER_LITERAL  */
1773 | #line 315 "src/parser.y"
1774 |     {
1775 |         init_field_attributes(&(yyval.field_attrs));
1776 |         (yyval.field_attrs).min_value = (yyvsp[0].num);
1777 |     }
1778 | #line 1779 "src/parser.tab.c"
1779 |     break;
1780 | 
1781 |   case 31: /* attribute: MAX NUMBER_LITERAL  */
1782 | #line 320 "src/parser.y"
1783 |     {
1784 |         init_field_attributes(&(yyval.field_attrs));
1785 |         (yyval.field_attrs).max_value = (yyvsp[0].num);
1786 |     }
1787 | #line 1788 "src/parser.tab.c"
1788 |     break;
1789 | 
1790 |   case 32: /* attribute: ROWS NUMBER_LITERAL  */
1791 | #line 325 "src/parser.y"
1792 |     {
1793 |         init_field_attributes(&(yyval.field_attrs));
1794 |         (yyval.field_attrs).rows = (yyvsp[0].num);
1795 |     }
1796 | #line 1797 "src/parser.tab.c"
1797 |     break;
1798 | 
1799 |   case 33: /* attribute: COLS NUMBER_LITERAL  */
1800 | #line 330 "src/parser.y"
1801 |     {
1802 |         init_field_attributes(&(yyval.field_attrs));
1803 |         (yyval.field_attrs).cols = (yyvsp[0].num);
1804 |     }
1805 | #line 1806 "src/parser.tab.c"
1806 |     break;
1807 | 
1808 |   case 34: /* attribute: PATTERN STRING_LITERAL  */
1809 | #line 335 "src/parser.y"
1810 |     {
1811 |         init_field_attributes(&(yyval.field_attrs));
1812 |         (yyval.field_attrs).pattern = strdup((yyvsp[0].str));
1813 |     }
1814 | #line 1815 "src/parser.tab.c"
1815 |     break;
1816 | 
1817 |   case 35: /* attribute: DEFAULT STRING_LITERAL  */
1818 | #line 340 "src/parser.y"
1819 |     {
1820 |         init_field_attributes(&(yyval.field_attrs));
1821 |         (yyval.field_attrs).default_value = strdup((yyvsp[0].str));
1822 |     }
1823 | #line 1824 "src/parser.tab.c"
1824 |     break;
1825 | 
1826 |   case 36: /* attribute: DEFAULT NUMBER_LITERAL  */
1827 | #line 345 "src/parser.y"
1828 |     {
1829 |         init_field_attributes(&(yyval.field_attrs));
1830 |         char buf[32];
1831 |         sprintf(buf, "%d", (yyvsp[0].num));
1832 |         (yyval.field_attrs).default_value = strdup(buf);
1833 |     }
1834 | #line 1835 "src/parser.tab.c"
1835 |     break;
1836 | 
1837 | 
1838 | #line 1839 "src/parser.tab.c"
1839 | 
1840 |       default: break;
1841 |     }
1842 |   /* User semantic actions sometimes alter yychar, and that requires
1843 |      that yytoken be updated with the new translation.  We take the
1844 |      approach of translating immediately before every use of yytoken.
1845 |      One alternative is translating here after every semantic action,
1846 |      but that translation would be missed if the semantic action invokes
1847 |      YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
1848 |      if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
1849 |      incorrect destructor might then be invoked immediately.  In the
1850 |      case of YYERROR or YYBACKUP, subsequent parser actions might lead
1851 |      to an incorrect destructor call or verbose syntax error message
1852 |      before the lookahead is translated.  */
1853 |   YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);
1854 | 
1855 |   YYPOPSTACK (yylen);
1856 |   yylen = 0;
1857 | 
1858 |   *++yyvsp = yyval;
1859 | 
1860 |   /* Now 'shift' the result of the reduction.  Determine what state
1861 |      that goes to, based on the state we popped back to and the rule
1862 |      number reduced by.  */
1863 |   {
1864 |     const int yylhs = yyr1[yyn] - YYNTOKENS;
1865 |     const int yyi = yypgoto[yylhs] + *yyssp;
1866 |     yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
1867 |                ? yytable[yyi]
1868 |                : yydefgoto[yylhs]);
1869 |   }
1870 | 
1871 |   goto yynewstate;
1872 | 
1873 | 
1874 | /*--------------------------------------.
1875 | | yyerrlab -- here on detecting error.  |
1876 | `--------------------------------------*/
1877 | yyerrlab:
1878 |   /* Make sure we have latest lookahead translation.  See comments at
1879 |      user semantic actions for why this is necessary.  */
1880 |   yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
1881 |   /* If not already recovering from an error, report this error.  */
1882 |   if (!yyerrstatus)
1883 |     {
1884 |       ++yynerrs;
1885 |       {
1886 |         yypcontext_t yyctx
1887 |           = {yyssp, yytoken};
1888 |         char const *yymsgp = YY_("syntax error");
1889 |         int yysyntax_error_status;
1890 |         yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
1891 |         if (yysyntax_error_status == 0)
1892 |           yymsgp = yymsg;
1893 |         else if (yysyntax_error_status == -1)
1894 |           {
1895 |             if (yymsg != yymsgbuf)
1896 |               YYSTACK_FREE (yymsg);
1897 |             yymsg = YY_CAST (char *,
1898 |                              YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
1899 |             if (yymsg)
1900 |               {
1901 |                 yysyntax_error_status
1902 |                   = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
1903 |                 yymsgp = yymsg;
1904 |               }
1905 |             else
1906 |               {
1907 |                 yymsg = yymsgbuf;
1908 |                 yymsg_alloc = sizeof yymsgbuf;
1909 |                 yysyntax_error_status = YYENOMEM;
1910 |               }
1911 |           }
1912 |         yyerror (yymsgp);
1913 |         if (yysyntax_error_status == YYENOMEM)
1914 |           YYNOMEM;
1915 |       }
1916 |     }
1917 | 
1918 |   if (yyerrstatus == 3)
1919 |     {
1920 |       /* If just tried and failed to reuse lookahead token after an
1921 |          error, discard it.  */
1922 | 
1923 |       if (yychar <= YYEOF)
1924 |         {
1925 |           /* Return failure if at end of input.  */
1926 |           if (yychar == YYEOF)
1927 |             YYABORT;
1928 |         }
1929 |       else
1930 |         {
1931 |           yydestruct ("Error: discarding",
1932 |                       yytoken, &yylval);
1933 |           yychar = YYEMPTY;
1934 |         }
1935 |     }
1936 | 
1937 |   /* Else will try to reuse lookahead token after shifting the error
1938 |      token.  */
1939 |   goto yyerrlab1;
1940 | 
1941 | 
1942 | /*---------------------------------------------------.
1943 | | yyerrorlab -- error raised explicitly by YYERROR.  |
1944 | `---------------------------------------------------*/
1945 | yyerrorlab:
1946 |   /* Pacify compilers when the user code never invokes YYERROR and the
1947 |      label yyerrorlab therefore never appears in user code.  */
1948 |   if (0)
1949 |     YYERROR;
1950 |   ++yynerrs;
1951 | 
1952 |   /* Do not reclaim the symbols of the rule whose action triggered
1953 |      this YYERROR.  */
1954 |   YYPOPSTACK (yylen);
1955 |   yylen = 0;
1956 |   YY_STACK_PRINT (yyss, yyssp);
1957 |   yystate = *yyssp;
1958 |   goto yyerrlab1;
1959 | 
1960 | 
1961 | /*-------------------------------------------------------------.
1962 | | yyerrlab1 -- common code for both syntax error and YYERROR.  |
1963 | `-------------------------------------------------------------*/
1964 | yyerrlab1:
1965 |   yyerrstatus = 3;      /* Each real token shifted decrements this.  */
1966 | 
1967 |   /* Pop stack until we find a state that shifts the error token.  */
1968 |   for (;;)
1969 |     {
1970 |       yyn = yypact[yystate];
1971 |       if (!yypact_value_is_default (yyn))
1972 |         {
1973 |           yyn += YYSYMBOL_YYerror;
1974 |           if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
1975 |             {
1976 |               yyn = yytable[yyn];
1977 |               if (0 < yyn)
1978 |                 break;
1979 |             }
1980 |         }
1981 | 
1982 |       /* Pop the current state because it cannot handle the error token.  */
1983 |       if (yyssp == yyss)
1984 |         YYABORT;
1985 | 
1986 | 
1987 |       yydestruct ("Error: popping",
1988 |                   YY_ACCESSING_SYMBOL (yystate), yyvsp);
1989 |       YYPOPSTACK (1);
1990 |       yystate = *yyssp;
1991 |       YY_STACK_PRINT (yyss, yyssp);
1992 |     }
1993 | 
1994 |   YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
1995 |   *++yyvsp = yylval;
1996 |   YY_IGNORE_MAYBE_UNINITIALIZED_END
1997 | 
1998 | 
1999 |   /* Shift the error token.  */
2000 |   YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);
2001 | 
2002 |   yystate = yyn;
2003 |   goto yynewstate;
2004 | 
2005 | 
2006 | /*-------------------------------------.
2007 | | yyacceptlab -- YYACCEPT comes here.  |
2008 | `-------------------------------------*/
2009 | yyacceptlab:
2010 |   yyresult = 0;
2011 |   goto yyreturnlab;
2012 | 
2013 | 
2014 | /*-----------------------------------.
2015 | | yyabortlab -- YYABORT comes here.  |
2016 | `-----------------------------------*/
2017 | yyabortlab:
2018 |   yyresult = 1;
2019 |   goto yyreturnlab;
2020 | 
2021 | 
2022 | /*-----------------------------------------------------------.
2023 | | yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
2024 | `-----------------------------------------------------------*/
2025 | yyexhaustedlab:
2026 |   yyerror (YY_("memory exhausted"));
2027 |   yyresult = 2;
2028 |   goto yyreturnlab;
2029 | 
2030 | 
2031 | /*----------------------------------------------------------.
2032 | | yyreturnlab -- parsing is finished, clean up and return.  |
2033 | `----------------------------------------------------------*/
2034 | yyreturnlab:
2035 |   if (yychar != YYEMPTY)
2036 |     {
2037 |       /* Make sure we have latest lookahead translation.  See comments at
2038 |          user semantic actions for why this is necessary.  */
2039 |       yytoken = YYTRANSLATE (yychar);
2040 |       yydestruct ("Cleanup: discarding lookahead",
2041 |                   yytoken, &yylval);
2042 |     }
2043 |   /* Do not reclaim the symbols of the rule whose action triggered
2044 |      this YYABORT or YYACCEPT.  */
2045 |   YYPOPSTACK (yylen);
2046 |   YY_STACK_PRINT (yyss, yyssp);
2047 |   while (yyssp != yyss)
2048 |     {
2049 |       yydestruct ("Cleanup: popping",
2050 |                   YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
2051 |       YYPOPSTACK (1);
2052 |     }
2053 | #ifndef yyoverflow
2054 |   if (yyss != yyssa)
2055 |     YYSTACK_FREE (yyss);
2056 | #endif
2057 |   if (yymsg != yymsgbuf)
2058 |     YYSTACK_FREE (yymsg);
2059 |   return yyresult;
2060 | }
2061 | 
2062 | #line 353 "src/parser.y"
2063 | 
2064 | 
2065 | void yyerror(const char *s) {
2066 |     fprintf(stderr, "Parse error on line %d: %s\n", yylineno, s);
2067 | }
2068 | 
2069 | int main(int argc, char **argv) {
2070 |     if (argc > 1) {
2071 |         FILE *file = fopen(argv[1], "r");
2072 |         if (!file) {
2073 |             perror(argv[1]);
2074 |             return 1;
2075 |         }
2076 |         yyin = file;
2077 |     }
2078 |     yyparse();
2079 |     cleanup_form(current_form);
2080 |     return 0;
2081 | }
2082 | 
2083 | int yywrap() {
2084 |     return 1;
2085 | }
```

FormLang/src/parser.tab.h
```
1 | /* A Bison parser, made by GNU Bison 3.8.2.  */
2 | 
3 | /* Bison interface for Yacc-like parsers in C
4 | 
5 |    Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
6 |    Inc.
7 | 
8 |    This program is free software: you can redistribute it and/or modify
9 |    it under the terms of the GNU General Public License as published by
10 |    the Free Software Foundation, either version 3 of the License, or
11 |    (at your option) any later version.
12 | 
13 |    This program is distributed in the hope that it will be useful,
14 |    but WITHOUT ANY WARRANTY; without even the implied warranty of
15 |    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
16 |    GNU General Public License for more details.
17 | 
18 |    You should have received a copy of the GNU General Public License
19 |    along with this program.  If not, see <https://www.gnu.org/licenses/>.  */
20 | 
21 | /* As a special exception, you may create a larger work that contains
22 |    part or all of the Bison parser skeleton and distribute that work
23 |    under terms of your choice, so long as that work isn't itself a
24 |    parser generator using the skeleton or a modified version thereof
25 |    as a parser skeleton.  Alternatively, if you modify or redistribute
26 |    the parser skeleton itself, you may (at your option) remove this
27 |    special exception, which will cause the skeleton and the resulting
28 |    Bison output files to be licensed under the GNU General Public
29 |    License without this special exception.
30 | 
31 |    This special exception was added by the Free Software Foundation in
32 |    version 2.2 of Bison.  */
33 | 
34 | /* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
35 |    especially those whose name start with YY_ or yy_.  They are
36 |    private implementation details that can be changed or removed.  */
37 | 
38 | #ifndef YY_YY_SRC_PARSER_TAB_H_INCLUDED
39 | # define YY_YY_SRC_PARSER_TAB_H_INCLUDED
40 | /* Debug traces.  */
41 | #ifndef YYDEBUG
42 | # define YYDEBUG 0
43 | #endif
44 | #if YYDEBUG
45 | extern int yydebug;
46 | #endif
47 | 
48 | /* Token kinds.  */
49 | #ifndef YYTOKENTYPE
50 | # define YYTOKENTYPE
51 |   enum yytokentype
52 |   {
53 |     YYEMPTY = -2,
54 |     YYEOF = 0,                     /* "end of file"  */
55 |     YYerror = 256,                 /* error  */
56 |     YYUNDEF = 257,                 /* "invalid token"  */
57 |     FORM = 258,                    /* FORM  */
58 |     SECTION = 259,                 /* SECTION  */
59 |     FIELD = 260,                   /* FIELD  */
60 |     TEXT = 261,                    /* TEXT  */
61 |     EMAIL = 262,                   /* EMAIL  */
62 |     PASSWORD = 263,                /* PASSWORD  */
63 |     NUMBER = 264,                  /* NUMBER  */
64 |     TEXTAREA = 265,                /* TEXTAREA  */
65 |     DATE = 266,                    /* DATE  */
66 |     CHECKBOX = 267,                /* CHECKBOX  */
67 |     DROPDOWN = 268,                /* DROPDOWN  */
68 |     RADIO = 269,                   /* RADIO  */
69 |     FILE_TYPE = 270,               /* FILE_TYPE  */
70 |     REQUIRED = 271,                /* REQUIRED  */
71 |     OPTIONAL = 272,                /* OPTIONAL  */
72 |     MINLENGTH = 273,               /* MINLENGTH  */
73 |     MAXLENGTH = 274,               /* MAXLENGTH  */
74 |     MIN = 275,                     /* MIN  */
75 |     MAX = 276,                     /* MAX  */
76 |     ROWS = 277,                    /* ROWS  */
77 |     COLS = 278,                    /* COLS  */
78 |     PATTERN = 279,                 /* PATTERN  */
79 |     DEFAULT = 280,                 /* DEFAULT  */
80 |     IDENTIFIER = 281,              /* IDENTIFIER  */
81 |     NUMBER_LITERAL = 282,          /* NUMBER_LITERAL  */
82 |     STRING_LITERAL = 283           /* STRING_LITERAL  */
83 |   };
84 |   typedef enum yytokentype yytoken_kind_t;
85 | #endif
86 | 
87 | /* Value type.  */
88 | #if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
89 | union YYSTYPE
90 | {
91 | #line 162 "src/parser.y"
92 | 
93 |     char* str;
94 |     int num;
95 |     Form* form;
96 |     Section* section;
97 |     FieldType field_type;
98 |     FieldAttributes field_attrs;
99 | 
100 | #line 101 "src/parser.tab.h"
101 | 
102 | };
103 | typedef union YYSTYPE YYSTYPE;
104 | # define YYSTYPE_IS_TRIVIAL 1
105 | # define YYSTYPE_IS_DECLARED 1
106 | #endif
107 | 
108 | 
109 | extern YYSTYPE yylval;
110 | 
111 | 
112 | int yyparse (void);
113 | 
114 | 
115 | #endif /* !YY_YY_SRC_PARSER_TAB_H_INCLUDED  */
```

FormLang/src/parser.y
```
1 | %{
2 | #include <stdio.h>
3 | #include <stdlib.h>
4 | #include <string.h>
5 | #include "formLang.h"
6 | 
7 | extern int yylex();
8 | extern int yylineno;
9 | void yyerror(const char *s);
10 | 
11 | // Global variables for current form and section
12 | Form *current_form = NULL;
13 | Section *current_section = NULL;
14 | 
15 | // Field name tracking for duplicate detection
16 | typedef struct {
17 |     char* name;
18 |     int line;
19 | } FieldName;
20 | 
21 | FieldName* field_names = NULL;
22 | int field_name_count = 0;
23 | 
24 | // Helper functions
25 | Form* create_form(const char* name) {
26 |     Form* form = malloc(sizeof(Form));
27 |     if (!form) return NULL;
28 |     form->name = strdup(name);
29 |     form->sections = NULL;
30 |     form->section_count = 0;
31 |     return form;
32 | }
33 | 
34 | Section* create_section(const char* name) {
35 |     Section* section = malloc(sizeof(Section));
36 |     if (!section) return NULL;
37 |     section->name = strdup(name);
38 |     section->fields = NULL;
39 |     section->field_count = 0;
40 |     return section;
41 | }
42 | 
43 | void add_section_to_form(Form* form, Section* section) {
44 |     fprintf(stderr, "Adding section to form\n");
45 |     if (!form || !section) {
46 |         fprintf(stderr, "Null form or section\n");
47 |         return;
48 |     }
49 |     
50 |     fprintf(stderr, "Reallocating sections array\n");
51 |     Section** new_sections = realloc(form->sections, (form->section_count + 1) * sizeof(Section*));
52 |     if (!new_sections) {
53 |         fprintf(stderr, "Memory allocation failed for sections\n");
54 |         exit(1);
55 |     }
56 |     form->sections = new_sections;
57 |     form->sections[form->section_count] = section;
58 |     form->section_count++;
59 |     fprintf(stderr, "Section added successfully\n");
60 | }
61 | 
62 | int check_duplicate_field(const char* name) {
63 |     for (int i = 0; i < field_name_count; i++) {
64 |         if (strcmp(field_names[i].name, name) == 0) {
65 |             return 1;
66 |         }
67 |     }
68 |     return 0;
69 | }
70 | 
71 | void init_field_attributes(FieldAttributes* attrs) {
72 |     if (!attrs) return;
73 |     attrs->min_length = -1;
74 |     attrs->max_length = -1;
75 |     attrs->min_value = -1;
76 |     attrs->max_value = -1;
77 |     attrs->rows = -1;
78 |     attrs->cols = -1;
79 |     attrs->pattern = NULL;
80 |     attrs->default_value = NULL;
81 |     attrs->required = 0;
82 | }
83 | 
84 | void add_field_to_section(Section* section, const char* name, FieldType type, FieldAttributes* attrs) {
85 |     fprintf(stderr, "Adding field %s to section\n", name);
86 |     if (!section || !name || !attrs) {
87 |         fprintf(stderr, "Null section, name, or attrs\n");
88 |         return;
89 |     }
90 |     
91 |     // Add field name to tracking
92 |     field_name_count++;
93 |     FieldName* new_field_names = realloc(field_names, field_name_count * sizeof(FieldName));
94 |     if (!new_field_names) {
95 |         fprintf(stderr, "Memory allocation failed for field names\n");
96 |         exit(1);
97 |     }
98 |     field_names = new_field_names;
99 |     field_names[field_name_count - 1].name = strdup(name);
100 |     field_names[field_name_count - 1].line = yylineno;
101 |     
102 |     fprintf(stderr, "Reallocating fields array\n");
103 |     // Allocate memory for the new field
104 |     Field* new_fields = realloc(section->fields, (section->field_count + 1) * sizeof(Field));
105 |     if (!new_fields) {
106 |         fprintf(stderr, "Memory allocation failed for fields\n");
107 |         exit(1);
108 |     }
109 |     section->fields = new_fields;
110 |     
111 |     Field* field = &section->fields[section->field_count];
112 |     field->name = strdup(name);
113 |     field->type = type;
114 |     memcpy(&field->attributes, attrs, sizeof(FieldAttributes));
115 |     
116 |     // If the attributes contain strings, make copies
117 |     if (attrs->pattern) {
118 |         field->attributes.pattern = strdup(attrs->pattern);
119 |     }
120 |     if (attrs->default_value) {
121 |         field->attributes.default_value = strdup(attrs->default_value);
122 |     }
123 |     
124 |     section->field_count++;
125 |     fprintf(stderr, "Field added successfully\n");
126 | }
127 | 
128 | void cleanup_form(Form* form) {
129 |     if (form) {
130 |         for (int i = 0; i < form->section_count; i++) {
131 |             Section* s = form->sections[i];
132 |             if (s) {
133 |                 for (int j = 0; j < s->field_count; j++) {
134 |                     Field* f = &s->fields[j];
135 |                     if (f->name) free(f->name);
136 |                     if (f->attributes.pattern) free(f->attributes.pattern);
137 |                     if (f->attributes.default_value) free(f->attributes.default_value);
138 |                 }
139 |                 if (s->fields) free(s->fields);
140 |                 if (s->name) free(s->name);
141 |                 free(s);
142 |             }
143 |         }
144 |         if (form->sections) free(form->sections);
145 |         if (form->name) free(form->name);
146 |         free(form);
147 |     }
148 |     
149 |     // Cleanup field name tracking
150 |     for (int i = 0; i < field_name_count; i++) {
151 |         if (field_names[i].name) free(field_names[i].name);
152 |     }
153 |     if (field_names) free(field_names);
154 |     field_name_count = 0;
155 | }
156 | %}
157 | 
158 | %token FORM SECTION FIELD TEXT EMAIL PASSWORD NUMBER TEXTAREA DATE CHECKBOX DROPDOWN RADIO FILE_TYPE
159 | %token REQUIRED OPTIONAL MINLENGTH MAXLENGTH MIN MAX ROWS COLS PATTERN DEFAULT
160 | %token IDENTIFIER NUMBER_LITERAL STRING_LITERAL
161 | 
162 | %union {
163 |     char* str;
164 |     int num;
165 |     Form* form;
166 |     Section* section;
167 |     FieldType field_type;
168 |     FieldAttributes field_attrs;
169 | }
170 | 
171 | %type <str> IDENTIFIER STRING_LITERAL
172 | %type <num> NUMBER_LITERAL
173 | %type <form> form
174 | %type <field_type> field_type
175 | %type <field_attrs> field_attributes attribute
176 | 
177 | %define parse.error verbose
178 | 
179 | %%
180 | 
181 | form: FORM IDENTIFIER 
182 |     {
183 |         current_form = create_form($2);
184 |         if (!current_form) {
185 |             yyerror("Failed to create form");
186 |             YYERROR;
187 |         }
188 |     }
189 |     '{' section_list '}'
190 |     {
191 |         generate_html(stdout);
192 |         $$ = current_form;
193 |     }
194 |     ;
195 | 
196 | section_list: 
197 |     | section_list section
198 |     ;
199 | 
200 | section: section_header '{' field_list '}'
201 |     {
202 |         current_section = NULL;
203 |     }
204 |     | section_header '{' '}'
205 |     {
206 |         current_section = NULL;
207 |     }
208 |     | section_header error '}'
209 |     {
210 |         yyerror("Invalid section declaration");
211 |         current_section = NULL;
212 |         yyclearin;
213 |         yyerrok;
214 |     }
215 |     ;
216 | 
217 | section_header: SECTION IDENTIFIER
218 |     {
219 |         if (current_section != NULL) {
220 |             yyerror("Nested sections are not allowed");
221 |             YYERROR;
222 |         }
223 |         current_section = create_section($2);
224 |         if (!current_section) {
225 |             yyerror("Failed to create section");
226 |             YYERROR;
227 |         }
228 |         add_section_to_form(current_form, current_section);
229 |     }
230 |     ;
231 | 
232 | field_list:
233 |     | field_list field
234 |     | field_list error ';'
235 |     {
236 |         yyerror("Invalid field declaration");
237 |         yyclearin;
238 |         yyerrok;
239 |     }
240 |     ;
241 | 
242 | field: FIELD IDENTIFIER ':' field_type field_attributes ';'
243 |     {
244 |         if (current_section == NULL) {
245 |             yyerror("Field must be inside a section");
246 |             YYERROR;
247 |         }
248 |         if (check_duplicate_field($2)) {
249 |             yyerror("Duplicate field name found");
250 |             YYERROR;
251 |         }
252 |         add_field_to_section(current_section, $2, $4, &$5);
253 |         free($2); // Free the identifier after use
254 |     }
255 |     ;
256 | 
257 | field_type: TEXT           { $$ = FIELD_TEXT; }
258 |           | EMAIL          { $$ = FIELD_EMAIL; }
259 |           | PASSWORD       { $$ = FIELD_PASSWORD; }
260 |           | NUMBER         { $$ = FIELD_NUMBER; }
261 |           | TEXTAREA       { $$ = FIELD_TEXTAREA; }
262 |           | DATE           { $$ = FIELD_DATE; }
263 |           | CHECKBOX       { $$ = FIELD_CHECKBOX; }
264 |           | DROPDOWN       { $$ = FIELD_DROPDOWN; }
265 |           | RADIO          { $$ = FIELD_RADIO; }
266 |           | FILE_TYPE      { $$ = FIELD_FILE; }
267 |           ;
268 | 
269 | field_attributes: /* empty */
270 |     {
271 |         init_field_attributes(&$$);
272 |     }
273 |     | field_attributes attribute
274 |     {
275 |         $$ = $1;
276 |         if ($2.required != -1) $$.required = $2.required;
277 |         if ($2.min_length != -1) $$.min_length = $2.min_length;
278 |         if ($2.max_length != -1) $$.max_length = $2.max_length;
279 |         if ($2.min_value != -1) $$.min_value = $2.min_value;
280 |         if ($2.max_value != -1) $$.max_value = $2.max_value;
281 |         if ($2.rows != -1) $$.rows = $2.rows;
282 |         if ($2.cols != -1) $$.cols = $2.cols;
283 |         if ($2.pattern) {
284 |             if ($$.pattern) free($$.pattern);
285 |             $$.pattern = strdup($2.pattern);
286 |         }
287 |         if ($2.default_value) {
288 |             if ($$.default_value) free($$.default_value);
289 |             $$.default_value = strdup($2.default_value);
290 |         }
291 |     }
292 |     ;
293 | 
294 | attribute: REQUIRED
295 |     {
296 |         init_field_attributes(&$$);
297 |         $$.required = 1;
298 |     }
299 |     | OPTIONAL
300 |     {
301 |         init_field_attributes(&$$);
302 |         $$.required = 0;
303 |     }
304 |     | MINLENGTH NUMBER_LITERAL
305 |     {
306 |         init_field_attributes(&$$);
307 |         $$.min_length = $2;
308 |     }
309 |     | MAXLENGTH NUMBER_LITERAL
310 |     {
311 |         init_field_attributes(&$$);
312 |         $$.max_length = $2;
313 |     }
314 |     | MIN NUMBER_LITERAL
315 |     {
316 |         init_field_attributes(&$$);
317 |         $$.min_value = $2;
318 |     }
319 |     | MAX NUMBER_LITERAL
320 |     {
321 |         init_field_attributes(&$$);
322 |         $$.max_value = $2;
323 |     }
324 |     | ROWS NUMBER_LITERAL
325 |     {
326 |         init_field_attributes(&$$);
327 |         $$.rows = $2;
328 |     }
329 |     | COLS NUMBER_LITERAL
330 |     {
331 |         init_field_attributes(&$$);
332 |         $$.cols = $2;
333 |     }
334 |     | PATTERN STRING_LITERAL
335 |     {
336 |         init_field_attributes(&$$);
337 |         $$.pattern = strdup($2);
338 |     }
339 |     | DEFAULT STRING_LITERAL
340 |     {
341 |         init_field_attributes(&$$);
342 |         $$.default_value = strdup($2);
343 |     }
344 |     | DEFAULT NUMBER_LITERAL
345 |     {
346 |         init_field_attributes(&$$);
347 |         char buf[32];
348 |         sprintf(buf, "%d", $2);
349 |         $$.default_value = strdup(buf);
350 |     }
351 |     ;
352 | 
353 | %%
354 | 
355 | void yyerror(const char *s) {
356 |     fprintf(stderr, "Parse error on line %d: %s\n", yylineno, s);
357 | }
358 | 
359 | int main(int argc, char **argv) {
360 |     if (argc > 1) {
361 |         FILE *file = fopen(argv[1], "r");
362 |         if (!file) {
363 |             perror(argv[1]);
364 |             return 1;
365 |         }
366 |         yyin = file;
367 |     }
368 |     yyparse();
369 |     cleanup_form(current_form);
370 |     return 0;
371 | }
372 | 
373 | int yywrap() {
374 |     return 1;
375 | }
```

FormLang/src/y.tab.c
```
1 | /* A Bison parser, made by GNU Bison 3.8.2.  */
2 | 
3 | /* Bison implementation for Yacc-like parsers in C
4 | 
5 |    Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
6 |    Inc.
7 | 
8 |    This program is free software: you can redistribute it and/or modify
9 |    it under the terms of the GNU General Public License as published by
10 |    the Free Software Foundation, either version 3 of the License, or
11 |    (at your option) any later version.
12 | 
13 |    This program is distributed in the hope that it will be useful,
14 |    but WITHOUT ANY WARRANTY; without even the implied warranty of
15 |    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
16 |    GNU General Public License for more details.
17 | 
18 |    You should have received a copy of the GNU General Public License
19 |    along with this program.  If not, see <https://www.gnu.org/licenses/>.  */
20 | 
21 | /* As a special exception, you may create a larger work that contains
22 |    part or all of the Bison parser skeleton and distribute that work
23 |    under terms of your choice, so long as that work isn't itself a
24 |    parser generator using the skeleton or a modified version thereof
25 |    as a parser skeleton.  Alternatively, if you modify or redistribute
26 |    the parser skeleton itself, you may (at your option) remove this
27 |    special exception, which will cause the skeleton and the resulting
28 |    Bison output files to be licensed under the GNU General Public
29 |    License without this special exception.
30 | 
31 |    This special exception was added by the Free Software Foundation in
32 |    version 2.2 of Bison.  */
33 | 
34 | /* C LALR(1) parser skeleton written by Richard Stallman, by
35 |    simplifying the original so-called "semantic" parser.  */
36 | 
37 | /* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
38 |    especially those whose name start with YY_ or yy_.  They are
39 |    private implementation details that can be changed or removed.  */
40 | 
41 | /* All symbols defined below should begin with yy or YY, to avoid
42 |    infringing on user name space.  This should be done even for local
43 |    variables, as they might otherwise be expanded by user macros.
44 |    There are some unavoidable exceptions within include files to
45 |    define necessary library symbols; they are noted "INFRINGES ON
46 |    USER NAME SPACE" below.  */
47 | 
48 | /* Identify Bison output, and Bison version.  */
49 | #define YYBISON 30802
50 | 
51 | /* Bison version string.  */
52 | #define YYBISON_VERSION "3.8.2"
53 | 
54 | /* Skeleton name.  */
55 | #define YYSKELETON_NAME "yacc.c"
56 | 
57 | /* Pure parsers.  */
58 | #define YYPURE 0
59 | 
60 | /* Push parsers.  */
61 | #define YYPUSH 0
62 | 
63 | /* Pull parsers.  */
64 | #define YYPULL 1
65 | 
66 | 
67 | 
68 | 
69 | /* First part of user prologue.  */
70 | #line 1 "parser.y"
71 | 
72 | #include <stdio.h>
73 | #include <stdlib.h>
74 | #include <string.h>
75 | #include "formLang.h"
76 | 
77 | extern int yylex();
78 | extern int yylineno;
79 | extern void generate_html(FILE* output);  // Declare as external
80 | void yyerror(const char *s);
81 | 
82 | // Global variables for current form and section
83 | Form *current_form = NULL;
84 | Section *current_section = NULL;
85 | 
86 | // Field name tracking for duplicate detection
87 | typedef struct {
88 |     char* name;
89 |     int line;
90 | } FieldName;
91 | 
92 | FieldName* field_names = NULL;
93 | int field_name_count = 0;
94 | 
95 | // Helper functions
96 | Form* create_form(const char* name) {
97 |     Form* form = malloc(sizeof(Form));
98 |     form->name = strdup(name);
99 |     form->sections = NULL;
100 |     form->section_count = 0;
101 |     return form;
102 | }
103 | 
104 | Section* create_section(const char* name) {
105 |     Section* section = malloc(sizeof(Section));
106 |     section->name = strdup(name);
107 |     section->fields = NULL;
108 |     section->field_count = 0;
109 |     return section;
110 | }
111 | 
112 | void add_section_to_form(Form* form, Section* section) {
113 |     if (!form || !section) return;
114 |     
115 |     form->section_count++;
116 |     form->sections = realloc(form->sections, form->section_count * sizeof(Section*));
117 |     form->sections[form->section_count - 1] = section;
118 | }
119 | 
120 | int check_duplicate_field(const char* name) {
121 |     for (int i = 0; i < field_name_count; i++) {
122 |         if (strcmp(field_names[i].name, name) == 0) {
123 |             return 1;
124 |         }
125 |     }
126 |     return 0;
127 | }
128 | 
129 | void add_field_to_section(Section* section, const char* name, FieldType type, int required) {
130 |     if (!section || !name) return;
131 |     
132 |     // Add field name to tracking
133 |     field_name_count++;
134 |     field_names = realloc(field_names, field_name_count * sizeof(FieldName));
135 |     field_names[field_name_count - 1].name = strdup(name);
136 |     field_names[field_name_count - 1].line = yylineno;
137 |     
138 |     section->field_count++;
139 |     section->fields = realloc(section->fields, section->field_count * sizeof(Field));
140 |     
141 |     Field* field = &section->fields[section->field_count - 1];
142 |     field->name = strdup(name);
143 |     field->type = type;
144 |     field->required = required;
145 |     field->min_length = -1;
146 |     field->max_length = -1;
147 |     field->min_value = -1;
148 |     field->max_value = -1;
149 |     field->rows = -1;
150 |     field->cols = -1;
151 |     field->pattern = NULL;
152 |     field->default_value = NULL;
153 |     field->options = NULL;
154 |     field->option_count = 0;
155 | }
156 | 
157 | void set_field_attribute(Field* field, AttributeType attribute_type, const char* value) {
158 |     if (!field) return;
159 |     
160 |     switch (attribute_type) {
161 |         case ATTR_MIN_LENGTH:
162 |             field->min_length = atoi(value);
163 |             break;
164 |         case ATTR_MAX_LENGTH:
165 |             field->max_length = atoi(value);
166 |             break;
167 |         case ATTR_MIN_VALUE:
168 |             field->min_value = atoi(value);
169 |             break;
170 |         case ATTR_MAX_VALUE:
171 |             field->max_value = atoi(value);
172 |             break;
173 |         case ATTR_ROWS:
174 |             field->rows = atoi(value);
175 |             break;
176 |         case ATTR_COLS:
177 |             field->cols = atoi(value);
178 |             break;
179 |         case ATTR_PATTERN:
180 |             field->pattern = strdup(value);
181 |             break;
182 |         case ATTR_DEFAULT:
183 |             field->default_value = strdup(value);
184 |             break;
185 |         case ATTR_OPTIONS:
186 |             // Options are handled separately in add_field_option
187 |             break;
188 |     }
189 | }
190 | 
191 | void add_field_option(Field* field, const char* option) {
192 |     if (!field || !option) return;
193 |     
194 |     field->option_count++;
195 |     field->options = realloc(field->options, field->option_count * sizeof(char*));
196 |     field->options[field->option_count - 1] = strdup(option);
197 | }
198 | 
199 | void cleanup_form(Form* form) {
200 |     if (form) {
201 |         for (int i = 0; i < form->section_count; i++) {
202 |             Section* s = form->sections[i];
203 |             if (s) {
204 |                 for (int j = 0; j < s->field_count; j++) {
205 |                     Field* f = &s->fields[j];
206 |                     if (f->name) free(f->name);
207 |                     if (f->pattern) free(f->pattern);
208 |                     if (f->default_value) free(f->default_value);
209 |                     if (f->options) {
210 |                         for (int k = 0; k < f->option_count; k++) {
211 |                             if (f->options[k]) free(f->options[k]);
212 |                         }
213 |                         free(f->options);
214 |                     }
215 |                 }
216 |                 if (s->fields) free(s->fields);
217 |                 if (s->name) free(s->name);
218 |                 free(s);
219 |             }
220 |         }
221 |         if (form->sections) free(form->sections);
222 |         if (form->name) free(form->name);
223 |         free(form);
224 |     }
225 |     
226 |     // Cleanup field name tracking
227 |     for (int i = 0; i < field_name_count; i++) {
228 |         if (field_names[i].name) free(field_names[i].name);
229 |     }
230 |     if (field_names) free(field_names);
231 |     field_name_count = 0;
232 | }
233 | 
234 | #line 235 "y.tab.c"
235 | 
236 | # ifndef YY_CAST
237 | #  ifdef __cplusplus
238 | #   define YY_CAST(Type, Val) static_cast<Type> (Val)
239 | #   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
240 | #  else
241 | #   define YY_CAST(Type, Val) ((Type) (Val))
242 | #   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
243 | #  endif
244 | # endif
245 | # ifndef YY_NULLPTR
246 | #  if defined __cplusplus
247 | #   if 201103L <= __cplusplus
248 | #    define YY_NULLPTR nullptr
249 | #   else
250 | #    define YY_NULLPTR 0
251 | #   endif
252 | #  else
253 | #   define YY_NULLPTR ((void*)0)
254 | #  endif
255 | # endif
256 | 
257 | /* Use api.header.include to #include this header
258 |    instead of duplicating it here.  */
259 | #ifndef YY_YY_Y_TAB_H_INCLUDED
260 | # define YY_YY_Y_TAB_H_INCLUDED
261 | /* Debug traces.  */
262 | #ifndef YYDEBUG
263 | # define YYDEBUG 0
264 | #endif
265 | #if YYDEBUG
266 | extern int yydebug;
267 | #endif
268 | 
269 | /* Token kinds.  */
270 | #ifndef YYTOKENTYPE
271 | # define YYTOKENTYPE
272 |   enum yytokentype
273 |   {
274 |     YYEMPTY = -2,
275 |     YYEOF = 0,                     /* "end of file"  */
276 |     YYerror = 256,                 /* error  */
277 |     YYUNDEF = 257,                 /* "invalid token"  */
278 |     FORM = 258,                    /* FORM  */
279 |     SECTION = 259,                 /* SECTION  */
280 |     FIELD = 260,                   /* FIELD  */
281 |     TEXT = 261,                    /* TEXT  */
282 |     EMAIL = 262,                   /* EMAIL  */
283 |     PASSWORD = 263,                /* PASSWORD  */
284 |     NUMBER = 264,                  /* NUMBER  */
285 |     TEXTAREA = 265,                /* TEXTAREA  */
286 |     DATE = 266,                    /* DATE  */
287 |     CHECKBOX = 267,                /* CHECKBOX  */
288 |     DROPDOWN = 268,                /* DROPDOWN  */
289 |     RADIO = 269,                   /* RADIO  */
290 |     FILE_TYPE = 270,               /* FILE_TYPE  */
291 |     REQUIRED = 271,                /* REQUIRED  */
292 |     OPTIONAL = 272,                /* OPTIONAL  */
293 |     IDENTIFIER = 273,              /* IDENTIFIER  */
294 |     NUMBER_LITERAL = 274,          /* NUMBER_LITERAL  */
295 |     STRING_LITERAL = 275,          /* STRING_LITERAL  */
296 |     MIN_LENGTH = 276,              /* MIN_LENGTH  */
297 |     MAX_LENGTH = 277,              /* MAX_LENGTH  */
298 |     MIN_VALUE = 278,               /* MIN_VALUE  */
299 |     MAX_VALUE = 279,               /* MAX_VALUE  */
300 |     ROWS = 280,                    /* ROWS  */
301 |     COLS = 281,                    /* COLS  */
302 |     PATTERN = 282,                 /* PATTERN  */
303 |     DEFAULT = 283,                 /* DEFAULT  */
304 |     OPTIONS = 284                  /* OPTIONS  */
305 |   };
306 |   typedef enum yytokentype yytoken_kind_t;
307 | #endif
308 | /* Token kinds.  */
309 | #define YYEMPTY -2
310 | #define YYEOF 0
311 | #define YYerror 256
312 | #define YYUNDEF 257
313 | #define FORM 258
314 | #define SECTION 259
315 | #define FIELD 260
316 | #define TEXT 261
317 | #define EMAIL 262
318 | #define PASSWORD 263
319 | #define NUMBER 264
320 | #define TEXTAREA 265
321 | #define DATE 266
322 | #define CHECKBOX 267
323 | #define DROPDOWN 268
324 | #define RADIO 269
325 | #define FILE_TYPE 270
326 | #define REQUIRED 271
327 | #define OPTIONAL 272
328 | #define IDENTIFIER 273
329 | #define NUMBER_LITERAL 274
330 | #define STRING_LITERAL 275
331 | #define MIN_LENGTH 276
332 | #define MAX_LENGTH 277
333 | #define MIN_VALUE 278
334 | #define MAX_VALUE 279
335 | #define ROWS 280
336 | #define COLS 281
337 | #define PATTERN 282
338 | #define DEFAULT 283
339 | #define OPTIONS 284
340 | 
341 | /* Value type.  */
342 | #if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
343 | union YYSTYPE
344 | {
345 | #line 169 "parser.y"
346 | 
347 |     char* str;
348 |     int num;
349 |     Form* form;
350 |     Section* section;
351 |     FieldType field_type;
352 |     int attribute_type;
353 | 
354 | #line 355 "y.tab.c"
355 | 
356 | };
357 | typedef union YYSTYPE YYSTYPE;
358 | # define YYSTYPE_IS_TRIVIAL 1
359 | # define YYSTYPE_IS_DECLARED 1
360 | #endif
361 | 
362 | 
363 | extern YYSTYPE yylval;
364 | 
365 | 
366 | int yyparse (void);
367 | 
368 | 
369 | #endif /* !YY_YY_Y_TAB_H_INCLUDED  */
370 | /* Symbol kind.  */
371 | enum yysymbol_kind_t
372 | {
373 |   YYSYMBOL_YYEMPTY = -2,
374 |   YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
375 |   YYSYMBOL_YYerror = 1,                    /* error  */
376 |   YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
377 |   YYSYMBOL_FORM = 3,                       /* FORM  */
378 |   YYSYMBOL_SECTION = 4,                    /* SECTION  */
379 |   YYSYMBOL_FIELD = 5,                      /* FIELD  */
380 |   YYSYMBOL_TEXT = 6,                       /* TEXT  */
381 |   YYSYMBOL_EMAIL = 7,                      /* EMAIL  */
382 |   YYSYMBOL_PASSWORD = 8,                   /* PASSWORD  */
383 |   YYSYMBOL_NUMBER = 9,                     /* NUMBER  */
384 |   YYSYMBOL_TEXTAREA = 10,                  /* TEXTAREA  */
385 |   YYSYMBOL_DATE = 11,                      /* DATE  */
386 |   YYSYMBOL_CHECKBOX = 12,                  /* CHECKBOX  */
387 |   YYSYMBOL_DROPDOWN = 13,                  /* DROPDOWN  */
388 |   YYSYMBOL_RADIO = 14,                     /* RADIO  */
389 |   YYSYMBOL_FILE_TYPE = 15,                 /* FILE_TYPE  */
390 |   YYSYMBOL_REQUIRED = 16,                  /* REQUIRED  */
391 |   YYSYMBOL_OPTIONAL = 17,                  /* OPTIONAL  */
392 |   YYSYMBOL_IDENTIFIER = 18,                /* IDENTIFIER  */
393 |   YYSYMBOL_NUMBER_LITERAL = 19,            /* NUMBER_LITERAL  */
394 |   YYSYMBOL_STRING_LITERAL = 20,            /* STRING_LITERAL  */
395 |   YYSYMBOL_MIN_LENGTH = 21,                /* MIN_LENGTH  */
396 |   YYSYMBOL_MAX_LENGTH = 22,                /* MAX_LENGTH  */
397 |   YYSYMBOL_MIN_VALUE = 23,                 /* MIN_VALUE  */
398 |   YYSYMBOL_MAX_VALUE = 24,                 /* MAX_VALUE  */
399 |   YYSYMBOL_ROWS = 25,                      /* ROWS  */
400 |   YYSYMBOL_COLS = 26,                      /* COLS  */
401 |   YYSYMBOL_PATTERN = 27,                   /* PATTERN  */
402 |   YYSYMBOL_DEFAULT = 28,                   /* DEFAULT  */
403 |   YYSYMBOL_OPTIONS = 29,                   /* OPTIONS  */
404 |   YYSYMBOL_30_ = 30,                       /* '{'  */
405 |   YYSYMBOL_31_ = 31,                       /* '}'  */
406 |   YYSYMBOL_32_ = 32,                       /* ';'  */
407 |   YYSYMBOL_33_ = 33,                       /* ':'  */
408 |   YYSYMBOL_YYACCEPT = 34,                  /* $accept  */
409 |   YYSYMBOL_form = 35,                      /* form  */
410 |   YYSYMBOL_36_1 = 36,                      /* $@1  */
411 |   YYSYMBOL_section_list = 37,              /* section_list  */
412 |   YYSYMBOL_section = 38,                   /* section  */
413 |   YYSYMBOL_section_header = 39,            /* section_header  */
414 |   YYSYMBOL_field_list = 40,                /* field_list  */
415 |   YYSYMBOL_field = 41,                     /* field  */
416 |   YYSYMBOL_field_type = 42,                /* field_type  */
417 |   YYSYMBOL_field_attribute = 43,           /* field_attribute  */
418 |   YYSYMBOL_attribute_type = 44,            /* attribute_type  */
419 |   YYSYMBOL_option_list = 45                /* option_list  */
420 | };
421 | typedef enum yysymbol_kind_t yysymbol_kind_t;
422 | 
423 | 
424 | 
425 | 
426 | #ifdef short
427 | # undef short
428 | #endif
429 | 
430 | /* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
431 |    <limits.h> and (if available) <stdint.h> are included
432 |    so that the code can choose integer types of a good width.  */
433 | 
434 | #ifndef __PTRDIFF_MAX__
435 | # include <limits.h> /* INFRINGES ON USER NAME SPACE */
436 | # if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
437 | #  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
438 | #  define YY_STDINT_H
439 | # endif
440 | #endif
441 | 
442 | /* Narrow types that promote to a signed type and that can represent a
443 |    signed or unsigned integer of at least N bits.  In tables they can
444 |    save space and decrease cache pressure.  Promoting to a signed type
445 |    helps avoid bugs in integer arithmetic.  */
446 | 
447 | #ifdef __INT_LEAST8_MAX__
448 | typedef __INT_LEAST8_TYPE__ yytype_int8;
449 | #elif defined YY_STDINT_H
450 | typedef int_least8_t yytype_int8;
451 | #else
452 | typedef signed char yytype_int8;
453 | #endif
454 | 
455 | #ifdef __INT_LEAST16_MAX__
456 | typedef __INT_LEAST16_TYPE__ yytype_int16;
457 | #elif defined YY_STDINT_H
458 | typedef int_least16_t yytype_int16;
459 | #else
460 | typedef short yytype_int16;
461 | #endif
462 | 
463 | /* Work around bug in HP-UX 11.23, which defines these macros
464 |    incorrectly for preprocessor constants.  This workaround can likely
465 |    be removed in 2023, as HPE has promised support for HP-UX 11.23
466 |    (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
467 |    <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
468 | #ifdef __hpux
469 | # undef UINT_LEAST8_MAX
470 | # undef UINT_LEAST16_MAX
471 | # define UINT_LEAST8_MAX 255
472 | # define UINT_LEAST16_MAX 65535
473 | #endif
474 | 
475 | #if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
476 | typedef __UINT_LEAST8_TYPE__ yytype_uint8;
477 | #elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
478 |        && UINT_LEAST8_MAX <= INT_MAX)
479 | typedef uint_least8_t yytype_uint8;
480 | #elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
481 | typedef unsigned char yytype_uint8;
482 | #else
483 | typedef short yytype_uint8;
484 | #endif
485 | 
486 | #if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
487 | typedef __UINT_LEAST16_TYPE__ yytype_uint16;
488 | #elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
489 |        && UINT_LEAST16_MAX <= INT_MAX)
490 | typedef uint_least16_t yytype_uint16;
491 | #elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
492 | typedef unsigned short yytype_uint16;
493 | #else
494 | typedef int yytype_uint16;
495 | #endif
496 | 
497 | #ifndef YYPTRDIFF_T
498 | # if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
499 | #  define YYPTRDIFF_T __PTRDIFF_TYPE__
500 | #  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
501 | # elif defined PTRDIFF_MAX
502 | #  ifndef ptrdiff_t
503 | #   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
504 | #  endif
505 | #  define YYPTRDIFF_T ptrdiff_t
506 | #  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
507 | # else
508 | #  define YYPTRDIFF_T long
509 | #  define YYPTRDIFF_MAXIMUM LONG_MAX
510 | # endif
511 | #endif
512 | 
513 | #ifndef YYSIZE_T
514 | # ifdef __SIZE_TYPE__
515 | #  define YYSIZE_T __SIZE_TYPE__
516 | # elif defined size_t
517 | #  define YYSIZE_T size_t
518 | # elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
519 | #  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
520 | #  define YYSIZE_T size_t
521 | # else
522 | #  define YYSIZE_T unsigned
523 | # endif
524 | #endif
525 | 
526 | #define YYSIZE_MAXIMUM                                  \
527 |   YY_CAST (YYPTRDIFF_T,                                 \
528 |            (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
529 |             ? YYPTRDIFF_MAXIMUM                         \
530 |             : YY_CAST (YYSIZE_T, -1)))
531 | 
532 | #define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))
533 | 
534 | 
535 | /* Stored state numbers (used for stacks). */
536 | typedef yytype_int8 yy_state_t;
537 | 
538 | /* State numbers in computations.  */
539 | typedef int yy_state_fast_t;
540 | 
541 | #ifndef YY_
542 | # if defined YYENABLE_NLS && YYENABLE_NLS
543 | #  if ENABLE_NLS
544 | #   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
545 | #   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
546 | #  endif
547 | # endif
548 | # ifndef YY_
549 | #  define YY_(Msgid) Msgid
550 | # endif
551 | #endif
552 | 
553 | 
554 | #ifndef YY_ATTRIBUTE_PURE
555 | # if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
556 | #  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
557 | # else
558 | #  define YY_ATTRIBUTE_PURE
559 | # endif
560 | #endif
561 | 
562 | #ifndef YY_ATTRIBUTE_UNUSED
563 | # if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
564 | #  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
565 | # else
566 | #  define YY_ATTRIBUTE_UNUSED
567 | # endif
568 | #endif
569 | 
570 | /* Suppress unused-variable warnings by "using" E.  */
571 | #if ! defined lint || defined __GNUC__
572 | # define YY_USE(E) ((void) (E))
573 | #else
574 | # define YY_USE(E) /* empty */
575 | #endif
576 | 
577 | /* Suppress an incorrect diagnostic about yylval being uninitialized.  */
578 | #if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
579 | # if __GNUC__ * 100 + __GNUC_MINOR__ < 407
580 | #  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
581 |     _Pragma ("GCC diagnostic push")                                     \
582 |     _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
583 | # else
584 | #  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
585 |     _Pragma ("GCC diagnostic push")                                     \
586 |     _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
587 |     _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
588 | # endif
589 | # define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
590 |     _Pragma ("GCC diagnostic pop")
591 | #else
592 | # define YY_INITIAL_VALUE(Value) Value
593 | #endif
594 | #ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
595 | # define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
596 | # define YY_IGNORE_MAYBE_UNINITIALIZED_END
597 | #endif
598 | #ifndef YY_INITIAL_VALUE
599 | # define YY_INITIAL_VALUE(Value) /* Nothing. */
600 | #endif
601 | 
602 | #if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
603 | # define YY_IGNORE_USELESS_CAST_BEGIN                          \
604 |     _Pragma ("GCC diagnostic push")                            \
605 |     _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
606 | # define YY_IGNORE_USELESS_CAST_END            \
607 |     _Pragma ("GCC diagnostic pop")
608 | #endif
609 | #ifndef YY_IGNORE_USELESS_CAST_BEGIN
610 | # define YY_IGNORE_USELESS_CAST_BEGIN
611 | # define YY_IGNORE_USELESS_CAST_END
612 | #endif
613 | 
614 | 
615 | #define YY_ASSERT(E) ((void) (0 && (E)))
616 | 
617 | #if 1
618 | 
619 | /* The parser invokes alloca or malloc; define the necessary symbols.  */
620 | 
621 | # ifdef YYSTACK_USE_ALLOCA
622 | #  if YYSTACK_USE_ALLOCA
623 | #   ifdef __GNUC__
624 | #    define YYSTACK_ALLOC __builtin_alloca
625 | #   elif defined __BUILTIN_VA_ARG_INCR
626 | #    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
627 | #   elif defined _AIX
628 | #    define YYSTACK_ALLOC __alloca
629 | #   elif defined _MSC_VER
630 | #    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
631 | #    define alloca _alloca
632 | #   else
633 | #    define YYSTACK_ALLOC alloca
634 | #    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
635 | #     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
636 |       /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
637 | #     ifndef EXIT_SUCCESS
638 | #      define EXIT_SUCCESS 0
639 | #     endif
640 | #    endif
641 | #   endif
642 | #  endif
643 | # endif
644 | 
645 | # ifdef YYSTACK_ALLOC
646 |    /* Pacify GCC's 'empty if-body' warning.  */
647 | #  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
648 | #  ifndef YYSTACK_ALLOC_MAXIMUM
649 |     /* The OS might guarantee only one guard page at the bottom of the stack,
650 |        and a page size can be as small as 4096 bytes.  So we cannot safely
651 |        invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
652 |        to allow for a few compiler-allocated temporary stack slots.  */
653 | #   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
654 | #  endif
655 | # else
656 | #  define YYSTACK_ALLOC YYMALLOC
657 | #  define YYSTACK_FREE YYFREE
658 | #  ifndef YYSTACK_ALLOC_MAXIMUM
659 | #   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
660 | #  endif
661 | #  if (defined __cplusplus && ! defined EXIT_SUCCESS \
662 |        && ! ((defined YYMALLOC || defined malloc) \
663 |              && (defined YYFREE || defined free)))
664 | #   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
665 | #   ifndef EXIT_SUCCESS
666 | #    define EXIT_SUCCESS 0
667 | #   endif
668 | #  endif
669 | #  ifndef YYMALLOC
670 | #   define YYMALLOC malloc
671 | #   if ! defined malloc && ! defined EXIT_SUCCESS
672 | void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
673 | #   endif
674 | #  endif
675 | #  ifndef YYFREE
676 | #   define YYFREE free
677 | #   if ! defined free && ! defined EXIT_SUCCESS
678 | void free (void *); /* INFRINGES ON USER NAME SPACE */
679 | #   endif
680 | #  endif
681 | # endif
682 | #endif /* 1 */
683 | 
684 | #if (! defined yyoverflow \
685 |      && (! defined __cplusplus \
686 |          || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))
687 | 
688 | /* A type that is properly aligned for any stack member.  */
689 | union yyalloc
690 | {
691 |   yy_state_t yyss_alloc;
692 |   YYSTYPE yyvs_alloc;
693 | };
694 | 
695 | /* The size of the maximum gap between one aligned stack and the next.  */
696 | # define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)
697 | 
698 | /* The size of an array large to enough to hold all stacks, each with
699 |    N elements.  */
700 | # define YYSTACK_BYTES(N) \
701 |      ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
702 |       + YYSTACK_GAP_MAXIMUM)
703 | 
704 | # define YYCOPY_NEEDED 1
705 | 
706 | /* Relocate STACK from its old location to the new one.  The
707 |    local variables YYSIZE and YYSTACKSIZE give the old and new number of
708 |    elements in the stack, and YYPTR gives the new location of the
709 |    stack.  Advance YYPTR to a properly aligned location for the next
710 |    stack.  */
711 | # define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
712 |     do                                                                  \
713 |       {                                                                 \
714 |         YYPTRDIFF_T yynewbytes;                                         \
715 |         YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
716 |         Stack = &yyptr->Stack_alloc;                                    \
717 |         yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
718 |         yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
719 |       }                                                                 \
720 |     while (0)
721 | 
722 | #endif
723 | 
724 | #if defined YYCOPY_NEEDED && YYCOPY_NEEDED
725 | /* Copy COUNT objects from SRC to DST.  The source and destination do
726 |    not overlap.  */
727 | # ifndef YYCOPY
728 | #  if defined __GNUC__ && 1 < __GNUC__
729 | #   define YYCOPY(Dst, Src, Count) \
730 |       __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
731 | #  else
732 | #   define YYCOPY(Dst, Src, Count)              \
733 |       do                                        \
734 |         {                                       \
735 |           YYPTRDIFF_T yyi;                      \
736 |           for (yyi = 0; yyi < (Count); yyi++)   \
737 |             (Dst)[yyi] = (Src)[yyi];            \
738 |         }                                       \
739 |       while (0)
740 | #  endif
741 | # endif
742 | #endif /* !YYCOPY_NEEDED */
743 | 
744 | /* YYFINAL -- State number of the termination state.  */
745 | #define YYFINAL  4
746 | /* YYLAST -- Last index in YYTABLE.  */
747 | #define YYLAST   70
748 | 
749 | /* YYNTOKENS -- Number of terminals.  */
750 | #define YYNTOKENS  34
751 | /* YYNNTS -- Number of nonterminals.  */
752 | #define YYNNTS  12
753 | /* YYNRULES -- Number of rules.  */
754 | #define YYNRULES  40
755 | /* YYNSTATES -- Number of states.  */
756 | #define YYNSTATES  62
757 | 
758 | /* YYMAXUTOK -- Last valid token kind.  */
759 | #define YYMAXUTOK   284
760 | 
761 | 
762 | /* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
763 |    as returned by yylex, with out-of-bounds checking.  */
764 | #define YYTRANSLATE(YYX)                                \
765 |   (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
766 |    ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
767 |    : YYSYMBOL_YYUNDEF)
768 | 
769 | /* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
770 |    as returned by yylex.  */
771 | static const yytype_int8 yytranslate[] =
772 | {
773 |        0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
774 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
775 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
776 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
777 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
778 |        2,     2,     2,     2,     2,     2,     2,     2,    33,    32,
779 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
780 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
781 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
782 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
783 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
784 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
785 |        2,     2,     2,    30,     2,    31,     2,     2,     2,     2,
786 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
787 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
788 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
789 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
790 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
791 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
792 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
793 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
794 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
795 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
796 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
797 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
798 |        2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
799 |        5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
800 |       15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
801 |       25,    26,    27,    28,    29
802 | };
803 | 
804 | #if YYDEBUG
805 | /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
806 | static const yytype_int16 yyrline[] =
807 | {
808 |        0,   189,   189,   188,   203,   204,   207,   211,   215,   224,
809 |      239,   240,   241,   249,   261,   266,   271,   278,   279,   280,
810 |      281,   282,   283,   284,   285,   286,   287,   290,   291,   292,
811 |      298,   310,   311,   312,   313,   314,   315,   316,   317,   320,
812 |      321
813 | };
814 | #endif
815 | 
816 | /** Accessing symbol of state STATE.  */
817 | #define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])
818 | 
819 | #if 1
820 | /* The user-facing name of the symbol whose (internal) number is
821 |    YYSYMBOL.  No bounds checking.  */
822 | static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;
823 | 
824 | /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
825 |    First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
826 | static const char *const yytname[] =
827 | {
828 |   "\"end of file\"", "error", "\"invalid token\"", "FORM", "SECTION",
829 |   "FIELD", "TEXT", "EMAIL", "PASSWORD", "NUMBER", "TEXTAREA", "DATE",
830 |   "CHECKBOX", "DROPDOWN", "RADIO", "FILE_TYPE", "REQUIRED", "OPTIONAL",
831 |   "IDENTIFIER", "NUMBER_LITERAL", "STRING_LITERAL", "MIN_LENGTH",
832 |   "MAX_LENGTH", "MIN_VALUE", "MAX_VALUE", "ROWS", "COLS", "PATTERN",
833 |   "DEFAULT", "OPTIONS", "'{'", "'}'", "';'", "':'", "$accept", "form",
834 |   "$@1", "section_list", "section", "section_header", "field_list",
835 |   "field", "field_type", "field_attribute", "attribute_type",
836 |   "option_list", YY_NULLPTR
837 | };
838 | 
839 | static const char *
840 | yysymbol_name (yysymbol_kind_t yysymbol)
841 | {
842 |   return yytname[yysymbol];
843 | }
844 | #endif
845 | 
846 | #define YYPACT_NINF (-29)
847 | 
848 | #define yypact_value_is_default(Yyn) \
849 |   ((Yyn) == YYPACT_NINF)
850 | 
851 | #define YYTABLE_NINF (-1)
852 | 
853 | #define yytable_value_is_error(Yyn) \
854 |   0
855 | 
856 | /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
857 |    STATE-NUM.  */
858 | static const yytype_int8 yypact[] =
859 | {
860 |       16,     5,    21,   -29,   -29,    -6,   -29,     3,     7,   -29,
861 |      -29,     0,   -29,    -5,    -4,   -29,   -29,     1,    -3,   -15,
862 |      -29,   -29,   -29,    14,    53,    29,   -29,   -29,   -29,   -29,
863 |      -29,   -29,   -29,   -29,   -29,   -29,   -12,   -29,   -29,   -29,
864 |      -29,   -29,   -29,   -29,   -29,   -29,   -29,    -2,   -12,    -1,
865 |       28,    17,   -29,    37,   -29,   -29,   -29,   -29,     2,   -29,
866 |      -29,   -29
867 | };
868 | 
869 | /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
870 |    Performed when YYTABLE does not specify something else to do.  Zero
871 |    means the default is an error.  */
872 | static const yytype_int8 yydefact[] =
873 | {
874 |        0,     0,     0,     2,     1,     0,     4,     0,     0,     3,
875 |        5,     0,     9,     0,    10,     8,     7,     0,     0,     0,
876 |        6,    11,    12,     0,     0,     0,    17,    18,    19,    20,
877 |       21,    22,    23,    24,    25,    26,     0,    27,    28,    31,
878 |       32,    33,    34,    35,    36,    37,    38,     0,     0,     0,
879 |        0,     0,    39,     0,    16,    15,    29,    14,     0,    13,
880 |       40,    30
881 | };
882 | 
883 | /* YYPGOTO[NTERM-NUM].  */
884 | static const yytype_int8 yypgoto[] =
885 | {
886 |      -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,    45,   -28,
887 |      -29,   -29
888 | };
889 | 
890 | /* YYDEFGOTO[NTERM-NUM].  */
891 | static const yytype_int8 yydefgoto[] =
892 | {
893 |        0,     2,     5,     7,    10,    11,    17,    21,    36,    49,
894 |       50,    58
895 | };
896 | 
897 | /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
898 |    positive, shift that token.  If negative, reduce the rule whose
899 |    number is the opposite.  If YYTABLE_NINF, syntax error.  */
900 | static const yytype_int8 yytable[] =
901 | {
902 |       54,    13,    18,    23,    37,    38,    19,     8,    51,    39,
903 |       40,    41,    42,    43,    44,    45,    46,    47,    24,     1,
904 |       53,     4,    60,     3,     6,    12,    15,    16,    52,    22,
905 |       14,    55,    20,    61,     9,    26,    27,    28,    29,    30,
906 |       31,    32,    33,    34,    35,    37,    38,    25,    56,    57,
907 |       39,    40,    41,    42,    43,    44,    45,    46,    47,    26,
908 |       27,    28,    29,    30,    31,    32,    33,    34,    35,    59,
909 |       48
910 | };
911 | 
912 | static const yytype_int8 yycheck[] =
913 | {
914 |        1,     1,     1,    18,    16,    17,     5,     4,    36,    21,
915 |       22,    23,    24,    25,    26,    27,    28,    29,    33,     3,
916 |       48,     0,    20,    18,    30,    18,    31,    31,    30,    32,
917 |       30,    32,    31,    31,    31,     6,     7,     8,     9,    10,
918 |       11,    12,    13,    14,    15,    16,    17,    33,    20,    32,
919 |       21,    22,    23,    24,    25,    26,    27,    28,    29,     6,
920 |        7,     8,     9,    10,    11,    12,    13,    14,    15,    32,
921 |       25
922 | };
923 | 
924 | /* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
925 |    state STATE-NUM.  */
926 | static const yytype_int8 yystos[] =
927 | {
928 |        0,     3,    35,    18,     0,    36,    30,    37,     4,    31,
929 |       38,    39,    18,     1,    30,    31,    31,    40,     1,     5,
930 |       31,    41,    32,    18,    33,    33,     6,     7,     8,     9,
931 |       10,    11,    12,    13,    14,    15,    42,    16,    17,    21,
932 |       22,    23,    24,    25,    26,    27,    28,    29,    42,    43,
933 |       44,    43,    30,    43,     1,    32,    20,    32,    45,    32,
934 |       20,    31
935 | };
936 | 
937 | /* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
938 | static const yytype_int8 yyr1[] =
939 | {
940 |        0,    34,    36,    35,    37,    37,    38,    38,    38,    39,
941 |       40,    40,    40,    41,    41,    41,    41,    42,    42,    42,
942 |       42,    42,    42,    42,    42,    42,    42,    43,    43,    43,
943 |       43,    44,    44,    44,    44,    44,    44,    44,    44,    45,
944 |       45
945 | };
946 | 
947 | /* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
948 | static const yytype_int8 yyr2[] =
949 | {
950 |        0,     2,     0,     6,     0,     2,     4,     3,     3,     2,
951 |        0,     2,     3,     6,     5,     5,     5,     1,     1,     1,
952 |        1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
953 |        4,     1,     1,     1,     1,     1,     1,     1,     1,     0,
954 |        2
955 | };
956 | 
957 | 
958 | enum { YYENOMEM = -2 };
959 | 
960 | #define yyerrok         (yyerrstatus = 0)
961 | #define yyclearin       (yychar = YYEMPTY)
962 | 
963 | #define YYACCEPT        goto yyacceptlab
964 | #define YYABORT         goto yyabortlab
965 | #define YYERROR         goto yyerrorlab
966 | #define YYNOMEM         goto yyexhaustedlab
967 | 
968 | 
969 | #define YYRECOVERING()  (!!yyerrstatus)
970 | 
971 | #define YYBACKUP(Token, Value)                                    \
972 |   do                                                              \
973 |     if (yychar == YYEMPTY)                                        \
974 |       {                                                           \
975 |         yychar = (Token);                                         \
976 |         yylval = (Value);                                         \
977 |         YYPOPSTACK (yylen);                                       \
978 |         yystate = *yyssp;                                         \
979 |         goto yybackup;                                            \
980 |       }                                                           \
981 |     else                                                          \
982 |       {                                                           \
983 |         yyerror (YY_("syntax error: cannot back up")); \
984 |         YYERROR;                                                  \
985 |       }                                                           \
986 |   while (0)
987 | 
988 | /* Backward compatibility with an undocumented macro.
989 |    Use YYerror or YYUNDEF. */
990 | #define YYERRCODE YYUNDEF
991 | 
992 | 
993 | /* Enable debugging if requested.  */
994 | #if YYDEBUG
995 | 
996 | # ifndef YYFPRINTF
997 | #  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
998 | #  define YYFPRINTF fprintf
999 | # endif
1000 | 
1001 | # define YYDPRINTF(Args)                        \
1002 | do {                                            \
1003 |   if (yydebug)                                  \
1004 |     YYFPRINTF Args;                             \
1005 | } while (0)
1006 | 
1007 | 
1008 | 
1009 | 
1010 | # define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
1011 | do {                                                                      \
1012 |   if (yydebug)                                                            \
1013 |     {                                                                     \
1014 |       YYFPRINTF (stderr, "%s ", Title);                                   \
1015 |       yy_symbol_print (stderr,                                            \
1016 |                   Kind, Value); \
1017 |       YYFPRINTF (stderr, "\n");                                           \
1018 |     }                                                                     \
1019 | } while (0)
1020 | 
1021 | 
1022 | /*-----------------------------------.
1023 | | Print this symbol's value on YYO.  |
1024 | `-----------------------------------*/
1025 | 
1026 | static void
1027 | yy_symbol_value_print (FILE *yyo,
1028 |                        yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
1029 | {
1030 |   FILE *yyoutput = yyo;
1031 |   YY_USE (yyoutput);
1032 |   if (!yyvaluep)
1033 |     return;
1034 |   YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
1035 |   YY_USE (yykind);
1036 |   YY_IGNORE_MAYBE_UNINITIALIZED_END
1037 | }
1038 | 
1039 | 
1040 | /*---------------------------.
1041 | | Print this symbol on YYO.  |
1042 | `---------------------------*/
1043 | 
1044 | static void
1045 | yy_symbol_print (FILE *yyo,
1046 |                  yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
1047 | {
1048 |   YYFPRINTF (yyo, "%s %s (",
1049 |              yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));
1050 | 
1051 |   yy_symbol_value_print (yyo, yykind, yyvaluep);
1052 |   YYFPRINTF (yyo, ")");
1053 | }
1054 | 
1055 | /*------------------------------------------------------------------.
1056 | | yy_stack_print -- Print the state stack from its BOTTOM up to its |
1057 | | TOP (included).                                                   |
1058 | `------------------------------------------------------------------*/
1059 | 
1060 | static void
1061 | yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
1062 | {
1063 |   YYFPRINTF (stderr, "Stack now");
1064 |   for (; yybottom <= yytop; yybottom++)
1065 |     {
1066 |       int yybot = *yybottom;
1067 |       YYFPRINTF (stderr, " %d", yybot);
1068 |     }
1069 |   YYFPRINTF (stderr, "\n");
1070 | }
1071 | 
1072 | # define YY_STACK_PRINT(Bottom, Top)                            \
1073 | do {                                                            \
1074 |   if (yydebug)                                                  \
1075 |     yy_stack_print ((Bottom), (Top));                           \
1076 | } while (0)
1077 | 
1078 | 
1079 | /*------------------------------------------------.
1080 | | Report that the YYRULE is going to be reduced.  |
1081 | `------------------------------------------------*/
1082 | 
1083 | static void
1084 | yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
1085 |                  int yyrule)
1086 | {
1087 |   int yylno = yyrline[yyrule];
1088 |   int yynrhs = yyr2[yyrule];
1089 |   int yyi;
1090 |   YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
1091 |              yyrule - 1, yylno);
1092 |   /* The symbols being reduced.  */
1093 |   for (yyi = 0; yyi < yynrhs; yyi++)
1094 |     {
1095 |       YYFPRINTF (stderr, "   $%d = ", yyi + 1);
1096 |       yy_symbol_print (stderr,
1097 |                        YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
1098 |                        &yyvsp[(yyi + 1) - (yynrhs)]);
1099 |       YYFPRINTF (stderr, "\n");
1100 |     }
1101 | }
1102 | 
1103 | # define YY_REDUCE_PRINT(Rule)          \
1104 | do {                                    \
1105 |   if (yydebug)                          \
1106 |     yy_reduce_print (yyssp, yyvsp, Rule); \
1107 | } while (0)
1108 | 
1109 | /* Nonzero means print parse trace.  It is left uninitialized so that
1110 |    multiple parsers can coexist.  */
1111 | int yydebug;
1112 | #else /* !YYDEBUG */
1113 | # define YYDPRINTF(Args) ((void) 0)
1114 | # define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
1115 | # define YY_STACK_PRINT(Bottom, Top)
1116 | # define YY_REDUCE_PRINT(Rule)
1117 | #endif /* !YYDEBUG */
1118 | 
1119 | 
1120 | /* YYINITDEPTH -- initial size of the parser's stacks.  */
1121 | #ifndef YYINITDEPTH
1122 | # define YYINITDEPTH 200
1123 | #endif
1124 | 
1125 | /* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
1126 |    if the built-in stack extension method is used).
1127 | 
1128 |    Do not make this value too large; the results are undefined if
1129 |    YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
1130 |    evaluated with infinite-precision integer arithmetic.  */
1131 | 
1132 | #ifndef YYMAXDEPTH
1133 | # define YYMAXDEPTH 10000
1134 | #endif
1135 | 
1136 | 
1137 | /* Context of a parse error.  */
1138 | typedef struct
1139 | {
1140 |   yy_state_t *yyssp;
1141 |   yysymbol_kind_t yytoken;
1142 | } yypcontext_t;
1143 | 
1144 | /* Put in YYARG at most YYARGN of the expected tokens given the
1145 |    current YYCTX, and return the number of tokens stored in YYARG.  If
1146 |    YYARG is null, return the number of expected tokens (guaranteed to
1147 |    be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
1148 |    Return 0 if there are more than YYARGN expected tokens, yet fill
1149 |    YYARG up to YYARGN. */
1150 | static int
1151 | yypcontext_expected_tokens (const yypcontext_t *yyctx,
1152 |                             yysymbol_kind_t yyarg[], int yyargn)
1153 | {
1154 |   /* Actual size of YYARG. */
1155 |   int yycount = 0;
1156 |   int yyn = yypact[+*yyctx->yyssp];
1157 |   if (!yypact_value_is_default (yyn))
1158 |     {
1159 |       /* Start YYX at -YYN if negative to avoid negative indexes in
1160 |          YYCHECK.  In other words, skip the first -YYN actions for
1161 |          this state because they are default actions.  */
1162 |       int yyxbegin = yyn < 0 ? -yyn : 0;
1163 |       /* Stay within bounds of both yycheck and yytname.  */
1164 |       int yychecklim = YYLAST - yyn + 1;
1165 |       int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
1166 |       int yyx;
1167 |       for (yyx = yyxbegin; yyx < yyxend; ++yyx)
1168 |         if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
1169 |             && !yytable_value_is_error (yytable[yyx + yyn]))
1170 |           {
1171 |             if (!yyarg)
1172 |               ++yycount;
1173 |             else if (yycount == yyargn)
1174 |               return 0;
1175 |             else
1176 |               yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
1177 |           }
1178 |     }
1179 |   if (yyarg && yycount == 0 && 0 < yyargn)
1180 |     yyarg[0] = YYSYMBOL_YYEMPTY;
1181 |   return yycount;
1182 | }
1183 | 
1184 | 
1185 | 
1186 | 
1187 | #ifndef yystrlen
1188 | # if defined __GLIBC__ && defined _STRING_H
1189 | #  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
1190 | # else
1191 | /* Return the length of YYSTR.  */
1192 | static YYPTRDIFF_T
1193 | yystrlen (const char *yystr)
1194 | {
1195 |   YYPTRDIFF_T yylen;
1196 |   for (yylen = 0; yystr[yylen]; yylen++)
1197 |     continue;
1198 |   return yylen;
1199 | }
1200 | # endif
1201 | #endif
1202 | 
1203 | #ifndef yystpcpy
1204 | # if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
1205 | #  define yystpcpy stpcpy
1206 | # else
1207 | /* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
1208 |    YYDEST.  */
1209 | static char *
1210 | yystpcpy (char *yydest, const char *yysrc)
1211 | {
1212 |   char *yyd = yydest;
1213 |   const char *yys = yysrc;
1214 | 
1215 |   while ((*yyd++ = *yys++) != '\0')
1216 |     continue;
1217 | 
1218 |   return yyd - 1;
1219 | }
1220 | # endif
1221 | #endif
1222 | 
1223 | #ifndef yytnamerr
1224 | /* Copy to YYRES the contents of YYSTR after stripping away unnecessary
1225 |    quotes and backslashes, so that it's suitable for yyerror.  The
1226 |    heuristic is that double-quoting is unnecessary unless the string
1227 |    contains an apostrophe, a comma, or backslash (other than
1228 |    backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
1229 |    null, do not copy; instead, return the length of what the result
1230 |    would have been.  */
1231 | static YYPTRDIFF_T
1232 | yytnamerr (char *yyres, const char *yystr)
1233 | {
1234 |   if (*yystr == '"')
1235 |     {
1236 |       YYPTRDIFF_T yyn = 0;
1237 |       char const *yyp = yystr;
1238 |       for (;;)
1239 |         switch (*++yyp)
1240 |           {
1241 |           case '\'':
1242 |           case ',':
1243 |             goto do_not_strip_quotes;
1244 | 
1245 |           case '\\':
1246 |             if (*++yyp != '\\')
1247 |               goto do_not_strip_quotes;
1248 |             else
1249 |               goto append;
1250 | 
1251 |           append:
1252 |           default:
1253 |             if (yyres)
1254 |               yyres[yyn] = *yyp;
1255 |             yyn++;
1256 |             break;
1257 | 
1258 |           case '"':
1259 |             if (yyres)
1260 |               yyres[yyn] = '\0';
1261 |             return yyn;
1262 |           }
1263 |     do_not_strip_quotes: ;
1264 |     }
1265 | 
1266 |   if (yyres)
1267 |     return yystpcpy (yyres, yystr) - yyres;
1268 |   else
1269 |     return yystrlen (yystr);
1270 | }
1271 | #endif
1272 | 
1273 | 
1274 | static int
1275 | yy_syntax_error_arguments (const yypcontext_t *yyctx,
1276 |                            yysymbol_kind_t yyarg[], int yyargn)
1277 | {
1278 |   /* Actual size of YYARG. */
1279 |   int yycount = 0;
1280 |   /* There are many possibilities here to consider:
1281 |      - If this state is a consistent state with a default action, then
1282 |        the only way this function was invoked is if the default action
1283 |        is an error action.  In that case, don't check for expected
1284 |        tokens because there are none.
1285 |      - The only way there can be no lookahead present (in yychar) is if
1286 |        this state is a consistent state with a default action.  Thus,
1287 |        detecting the absence of a lookahead is sufficient to determine
1288 |        that there is no unexpected or expected token to report.  In that
1289 |        case, just report a simple "syntax error".
1290 |      - Don't assume there isn't a lookahead just because this state is a
1291 |        consistent state with a default action.  There might have been a
1292 |        previous inconsistent state, consistent state with a non-default
1293 |        action, or user semantic action that manipulated yychar.
1294 |      - Of course, the expected token list depends on states to have
1295 |        correct lookahead information, and it depends on the parser not
1296 |        to perform extra reductions after fetching a lookahead from the
1297 |        scanner and before detecting a syntax error.  Thus, state merging
1298 |        (from LALR or IELR) and default reductions corrupt the expected
1299 |        token list.  However, the list is correct for canonical LR with
1300 |        one exception: it will still contain any token that will not be
1301 |        accepted due to an error action in a later state.
1302 |   */
1303 |   if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
1304 |     {
1305 |       int yyn;
1306 |       if (yyarg)
1307 |         yyarg[yycount] = yyctx->yytoken;
1308 |       ++yycount;
1309 |       yyn = yypcontext_expected_tokens (yyctx,
1310 |                                         yyarg ? yyarg + 1 : yyarg, yyargn - 1);
1311 |       if (yyn == YYENOMEM)
1312 |         return YYENOMEM;
1313 |       else
1314 |         yycount += yyn;
1315 |     }
1316 |   return yycount;
1317 | }
1318 | 
1319 | /* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
1320 |    about the unexpected token YYTOKEN for the state stack whose top is
1321 |    YYSSP.
1322 | 
1323 |    Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
1324 |    not large enough to hold the message.  In that case, also set
1325 |    *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
1326 |    required number of bytes is too large to store.  */
1327 | static int
1328 | yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
1329 |                 const yypcontext_t *yyctx)
1330 | {
1331 |   enum { YYARGS_MAX = 5 };
1332 |   /* Internationalized format string. */
1333 |   const char *yyformat = YY_NULLPTR;
1334 |   /* Arguments of yyformat: reported tokens (one for the "unexpected",
1335 |      one per "expected"). */
1336 |   yysymbol_kind_t yyarg[YYARGS_MAX];
1337 |   /* Cumulated lengths of YYARG.  */
1338 |   YYPTRDIFF_T yysize = 0;
1339 | 
1340 |   /* Actual size of YYARG. */
1341 |   int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
1342 |   if (yycount == YYENOMEM)
1343 |     return YYENOMEM;
1344 | 
1345 |   switch (yycount)
1346 |     {
1347 | #define YYCASE_(N, S)                       \
1348 |       case N:                               \
1349 |         yyformat = S;                       \
1350 |         break
1351 |     default: /* Avoid compiler warnings. */
1352 |       YYCASE_(0, YY_("syntax error"));
1353 |       YYCASE_(1, YY_("syntax error, unexpected %s"));
1354 |       YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
1355 |       YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
1356 |       YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
1357 |       YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
1358 | #undef YYCASE_
1359 |     }
1360 | 
1361 |   /* Compute error message size.  Don't count the "%s"s, but reserve
1362 |      room for the terminator.  */
1363 |   yysize = yystrlen (yyformat) - 2 * yycount + 1;
1364 |   {
1365 |     int yyi;
1366 |     for (yyi = 0; yyi < yycount; ++yyi)
1367 |       {
1368 |         YYPTRDIFF_T yysize1
1369 |           = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
1370 |         if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
1371 |           yysize = yysize1;
1372 |         else
1373 |           return YYENOMEM;
1374 |       }
1375 |   }
1376 | 
1377 |   if (*yymsg_alloc < yysize)
1378 |     {
1379 |       *yymsg_alloc = 2 * yysize;
1380 |       if (! (yysize <= *yymsg_alloc
1381 |              && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
1382 |         *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
1383 |       return -1;
1384 |     }
1385 | 
1386 |   /* Avoid sprintf, as that infringes on the user's name space.
1387 |      Don't have undefined behavior even if the translation
1388 |      produced a string with the wrong number of "%s"s.  */
1389 |   {
1390 |     char *yyp = *yymsg;
1391 |     int yyi = 0;
1392 |     while ((*yyp = *yyformat) != '\0')
1393 |       if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
1394 |         {
1395 |           yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
1396 |           yyformat += 2;
1397 |         }
1398 |       else
1399 |         {
1400 |           ++yyp;
1401 |           ++yyformat;
1402 |         }
1403 |   }
1404 |   return 0;
1405 | }
1406 | 
1407 | 
1408 | /*-----------------------------------------------.
1409 | | Release the memory associated to this symbol.  |
1410 | `-----------------------------------------------*/
1411 | 
1412 | static void
1413 | yydestruct (const char *yymsg,
1414 |             yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
1415 | {
1416 |   YY_USE (yyvaluep);
1417 |   if (!yymsg)
1418 |     yymsg = "Deleting";
1419 |   YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);
1420 | 
1421 |   YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
1422 |   YY_USE (yykind);
1423 |   YY_IGNORE_MAYBE_UNINITIALIZED_END
1424 | }
1425 | 
1426 | 
1427 | /* Lookahead token kind.  */
1428 | int yychar;
1429 | 
1430 | /* The semantic value of the lookahead symbol.  */
1431 | YYSTYPE yylval;
1432 | /* Number of syntax errors so far.  */
1433 | int yynerrs;
1434 | 
1435 | 
1436 | 
1437 | 
1438 | /*----------.
1439 | | yyparse.  |
1440 | `----------*/
1441 | 
1442 | int
1443 | yyparse (void)
1444 | {
1445 |     yy_state_fast_t yystate = 0;
1446 |     /* Number of tokens to shift before error messages enabled.  */
1447 |     int yyerrstatus = 0;
1448 | 
1449 |     /* Refer to the stacks through separate pointers, to allow yyoverflow
1450 |        to reallocate them elsewhere.  */
1451 | 
1452 |     /* Their size.  */
1453 |     YYPTRDIFF_T yystacksize = YYINITDEPTH;
1454 | 
1455 |     /* The state stack: array, bottom, top.  */
1456 |     yy_state_t yyssa[YYINITDEPTH];
1457 |     yy_state_t *yyss = yyssa;
1458 |     yy_state_t *yyssp = yyss;
1459 | 
1460 |     /* The semantic value stack: array, bottom, top.  */
1461 |     YYSTYPE yyvsa[YYINITDEPTH];
1462 |     YYSTYPE *yyvs = yyvsa;
1463 |     YYSTYPE *yyvsp = yyvs;
1464 | 
1465 |   int yyn;
1466 |   /* The return value of yyparse.  */
1467 |   int yyresult;
1468 |   /* Lookahead symbol kind.  */
1469 |   yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
1470 |   /* The variables used to return semantic value and location from the
1471 |      action routines.  */
1472 |   YYSTYPE yyval;
1473 | 
1474 |   /* Buffer for error messages, and its allocated size.  */
1475 |   char yymsgbuf[128];
1476 |   char *yymsg = yymsgbuf;
1477 |   YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
1478 | 
1479 | #define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))
1480 | 
1481 |   /* The number of symbols on the RHS of the reduced rule.
1482 |      Keep to zero when no symbol should be popped.  */
1483 |   int yylen = 0;
1484 | 
1485 |   YYDPRINTF ((stderr, "Starting parse\n"));
1486 | 
1487 |   yychar = YYEMPTY; /* Cause a token to be read.  */
1488 | 
1489 |   goto yysetstate;
1490 | 
1491 | 
1492 | /*------------------------------------------------------------.
1493 | | yynewstate -- push a new state, which is found in yystate.  |
1494 | `------------------------------------------------------------*/
1495 | yynewstate:
1496 |   /* In all cases, when you get here, the value and location stacks
1497 |      have just been pushed.  So pushing a state here evens the stacks.  */
1498 |   yyssp++;
1499 | 
1500 | 
1501 | /*--------------------------------------------------------------------.
1502 | | yysetstate -- set current state (the top of the stack) to yystate.  |
1503 | `--------------------------------------------------------------------*/
1504 | yysetstate:
1505 |   YYDPRINTF ((stderr, "Entering state %d\n", yystate));
1506 |   YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
1507 |   YY_IGNORE_USELESS_CAST_BEGIN
1508 |   *yyssp = YY_CAST (yy_state_t, yystate);
1509 |   YY_IGNORE_USELESS_CAST_END
1510 |   YY_STACK_PRINT (yyss, yyssp);
1511 | 
1512 |   if (yyss + yystacksize - 1 <= yyssp)
1513 | #if !defined yyoverflow && !defined YYSTACK_RELOCATE
1514 |     YYNOMEM;
1515 | #else
1516 |     {
1517 |       /* Get the current used size of the three stacks, in elements.  */
1518 |       YYPTRDIFF_T yysize = yyssp - yyss + 1;
1519 | 
1520 | # if defined yyoverflow
1521 |       {
1522 |         /* Give user a chance to reallocate the stack.  Use copies of
1523 |            these so that the &'s don't force the real ones into
1524 |            memory.  */
1525 |         yy_state_t *yyss1 = yyss;
1526 |         YYSTYPE *yyvs1 = yyvs;
1527 | 
1528 |         /* Each stack pointer address is followed by the size of the
1529 |            data in use in that stack, in bytes.  This used to be a
1530 |            conditional around just the two extra args, but that might
1531 |            be undefined if yyoverflow is a macro.  */
1532 |         yyoverflow (YY_("memory exhausted"),
1533 |                     &yyss1, yysize * YYSIZEOF (*yyssp),
1534 |                     &yyvs1, yysize * YYSIZEOF (*yyvsp),
1535 |                     &yystacksize);
1536 |         yyss = yyss1;
1537 |         yyvs = yyvs1;
1538 |       }
1539 | # else /* defined YYSTACK_RELOCATE */
1540 |       /* Extend the stack our own way.  */
1541 |       if (YYMAXDEPTH <= yystacksize)
1542 |         YYNOMEM;
1543 |       yystacksize *= 2;
1544 |       if (YYMAXDEPTH < yystacksize)
1545 |         yystacksize = YYMAXDEPTH;
1546 | 
1547 |       {
1548 |         yy_state_t *yyss1 = yyss;
1549 |         union yyalloc *yyptr =
1550 |           YY_CAST (union yyalloc *,
1551 |                    YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
1552 |         if (! yyptr)
1553 |           YYNOMEM;
1554 |         YYSTACK_RELOCATE (yyss_alloc, yyss);
1555 |         YYSTACK_RELOCATE (yyvs_alloc, yyvs);
1556 | #  undef YYSTACK_RELOCATE
1557 |         if (yyss1 != yyssa)
1558 |           YYSTACK_FREE (yyss1);
1559 |       }
1560 | # endif
1561 | 
1562 |       yyssp = yyss + yysize - 1;
1563 |       yyvsp = yyvs + yysize - 1;
1564 | 
1565 |       YY_IGNORE_USELESS_CAST_BEGIN
1566 |       YYDPRINTF ((stderr, "Stack size increased to %ld\n",
1567 |                   YY_CAST (long, yystacksize)));
1568 |       YY_IGNORE_USELESS_CAST_END
1569 | 
1570 |       if (yyss + yystacksize - 1 <= yyssp)
1571 |         YYABORT;
1572 |     }
1573 | #endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */
1574 | 
1575 | 
1576 |   if (yystate == YYFINAL)
1577 |     YYACCEPT;
1578 | 
1579 |   goto yybackup;
1580 | 
1581 | 
1582 | /*-----------.
1583 | | yybackup.  |
1584 | `-----------*/
1585 | yybackup:
1586 |   /* Do appropriate processing given the current state.  Read a
1587 |      lookahead token if we need one and don't already have one.  */
1588 | 
1589 |   /* First try to decide what to do without reference to lookahead token.  */
1590 |   yyn = yypact[yystate];
1591 |   if (yypact_value_is_default (yyn))
1592 |     goto yydefault;
1593 | 
1594 |   /* Not known => get a lookahead token if don't already have one.  */
1595 | 
1596 |   /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
1597 |   if (yychar == YYEMPTY)
1598 |     {
1599 |       YYDPRINTF ((stderr, "Reading a token\n"));
1600 |       yychar = yylex ();
1601 |     }
1602 | 
1603 |   if (yychar <= YYEOF)
1604 |     {
1605 |       yychar = YYEOF;
1606 |       yytoken = YYSYMBOL_YYEOF;
1607 |       YYDPRINTF ((stderr, "Now at end of input.\n"));
1608 |     }
1609 |   else if (yychar == YYerror)
1610 |     {
1611 |       /* The scanner already issued an error message, process directly
1612 |          to error recovery.  But do not keep the error token as
1613 |          lookahead, it is too special and may lead us to an endless
1614 |          loop in error recovery. */
1615 |       yychar = YYUNDEF;
1616 |       yytoken = YYSYMBOL_YYerror;
1617 |       goto yyerrlab1;
1618 |     }
1619 |   else
1620 |     {
1621 |       yytoken = YYTRANSLATE (yychar);
1622 |       YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
1623 |     }
1624 | 
1625 |   /* If the proper action on seeing token YYTOKEN is to reduce or to
1626 |      detect an error, take that action.  */
1627 |   yyn += yytoken;
1628 |   if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
1629 |     goto yydefault;
1630 |   yyn = yytable[yyn];
1631 |   if (yyn <= 0)
1632 |     {
1633 |       if (yytable_value_is_error (yyn))
1634 |         goto yyerrlab;
1635 |       yyn = -yyn;
1636 |       goto yyreduce;
1637 |     }
1638 | 
1639 |   /* Count tokens shifted since error; after three, turn off error
1640 |      status.  */
1641 |   if (yyerrstatus)
1642 |     yyerrstatus--;
1643 | 
1644 |   /* Shift the lookahead token.  */
1645 |   YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
1646 |   yystate = yyn;
1647 |   YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
1648 |   *++yyvsp = yylval;
1649 |   YY_IGNORE_MAYBE_UNINITIALIZED_END
1650 | 
1651 |   /* Discard the shifted token.  */
1652 |   yychar = YYEMPTY;
1653 |   goto yynewstate;
1654 | 
1655 | 
1656 | /*-----------------------------------------------------------.
1657 | | yydefault -- do the default action for the current state.  |
1658 | `-----------------------------------------------------------*/
1659 | yydefault:
1660 |   yyn = yydefact[yystate];
1661 |   if (yyn == 0)
1662 |     goto yyerrlab;
1663 |   goto yyreduce;
1664 | 
1665 | 
1666 | /*-----------------------------.
1667 | | yyreduce -- do a reduction.  |
1668 | `-----------------------------*/
1669 | yyreduce:
1670 |   /* yyn is the number of a rule to reduce with.  */
1671 |   yylen = yyr2[yyn];
1672 | 
1673 |   /* If YYLEN is nonzero, implement the default value of the action:
1674 |      '$$ = $1'.
1675 | 
1676 |      Otherwise, the following line sets YYVAL to garbage.
1677 |      This behavior is undocumented and Bison
1678 |      users should not rely upon it.  Assigning to YYVAL
1679 |      unconditionally makes the parser a bit smaller, and it avoids a
1680 |      GCC warning that YYVAL may be used uninitialized.  */
1681 |   yyval = yyvsp[1-yylen];
1682 | 
1683 | 
1684 |   YY_REDUCE_PRINT (yyn);
1685 |   switch (yyn)
1686 |     {
1687 |   case 2: /* $@1: %empty  */
1688 | #line 189 "parser.y"
1689 |     {
1690 |         current_form = create_form((yyvsp[0].str));
1691 |         if (!current_form) {
1692 |             yyerror("Failed to create form");
1693 |             YYERROR;
1694 |         }
1695 |     }
1696 | #line 1697 "y.tab.c"
1697 |     break;
1698 | 
1699 |   case 3: /* form: FORM IDENTIFIER $@1 '{' section_list '}'  */
1700 | #line 197 "parser.y"
1701 |     {
1702 |         generate_html(stdout);
1703 |         (yyval.form) = current_form;
1704 |     }
1705 | #line 1706 "y.tab.c"
1706 |     break;
1707 | 
1708 |   case 6: /* section: section_header '{' field_list '}'  */
1709 | #line 208 "parser.y"
1710 |     {
1711 |         current_section = NULL;
1712 |     }
1713 | #line 1714 "y.tab.c"
1714 |     break;
1715 | 
1716 |   case 7: /* section: section_header '{' '}'  */
1717 | #line 212 "parser.y"
1718 |     {
1719 |         current_section = NULL;
1720 |     }
1721 | #line 1722 "y.tab.c"
1722 |     break;
1723 | 
1724 |   case 8: /* section: section_header error '}'  */
1725 | #line 216 "parser.y"
1726 |     {
1727 |         yyerror("Invalid section declaration");
1728 |         current_section = NULL;
1729 |         yyclearin;
1730 |         yyerrok;
1731 |     }
1732 | #line 1733 "y.tab.c"
1733 |     break;
1734 | 
1735 |   case 9: /* section_header: SECTION IDENTIFIER  */
1736 | #line 225 "parser.y"
1737 |     {
1738 |         if (current_section != NULL) {
1739 |             yyerror("Nested sections are not allowed");
1740 |             YYERROR;
1741 |         }
1742 |         current_section = create_section((yyvsp[0].str));
1743 |         if (!current_section) {
1744 |             yyerror("Failed to create section");
1745 |             YYERROR;
1746 |         }
1747 |         add_section_to_form(current_form, current_section);
1748 |     }
1749 | #line 1750 "y.tab.c"
1750 |     break;
1751 | 
1752 |   case 12: /* field_list: field_list error ';'  */
1753 | #line 242 "parser.y"
1754 |     {
1755 |         yyerror("Invalid field declaration");
1756 |         yyclearin;
1757 |         yyerrok;
1758 |     }
1759 | #line 1760 "y.tab.c"
1760 |     break;
1761 | 
1762 |   case 13: /* field: FIELD IDENTIFIER ':' field_type field_attribute ';'  */
1763 | #line 250 "parser.y"
1764 |     {
1765 |         if (current_section == NULL) {
1766 |             yyerror("Field must be inside a section");
1767 |             YYERROR;
1768 |         }
1769 |         if (check_duplicate_field((yyvsp[-4].str))) {
1770 |             yyerror("Duplicate field name found");
1771 |             YYERROR;
1772 |         }
1773 |         add_field_to_section(current_section, (yyvsp[-4].str), (yyvsp[-2].field_type), (yyvsp[-1].num));
1774 |     }
1775 | #line 1776 "y.tab.c"
1776 |     break;
1777 | 
1778 |   case 14: /* field: FIELD ':' field_type field_attribute ';'  */
1779 | #line 262 "parser.y"
1780 |     {
1781 |         yyerror("Missing field name");
1782 |         YYERROR;
1783 |     }
1784 | #line 1785 "y.tab.c"
1785 |     break;
1786 | 
1787 |   case 15: /* field: FIELD IDENTIFIER ':' field_attribute ';'  */
1788 | #line 267 "parser.y"
1789 |     {
1790 |         yyerror("Missing field type");
1791 |         YYERROR;
1792 |     }
1793 | #line 1794 "y.tab.c"
1794 |     break;
1795 | 
1796 |   case 16: /* field: FIELD IDENTIFIER ':' field_attribute error  */
1797 | #line 272 "parser.y"
1798 |     {
1799 |         yyerror("Invalid field attribute or missing semicolon");
1800 |         YYERROR;
1801 |     }
1802 | #line 1803 "y.tab.c"
1803 |     break;
1804 | 
1805 |   case 17: /* field_type: TEXT  */
1806 | #line 278 "parser.y"
1807 |                  { (yyval.field_type) = FIELD_TEXT; }
1808 | #line 1809 "y.tab.c"
1809 |     break;
1810 | 
1811 |   case 18: /* field_type: EMAIL  */
1812 | #line 279 "parser.y"
1813 |             { (yyval.field_type) = FIELD_EMAIL; }
1814 | #line 1815 "y.tab.c"
1815 |     break;
1816 | 
1817 |   case 19: /* field_type: PASSWORD  */
1818 | #line 280 "parser.y"
1819 |                { (yyval.field_type) = FIELD_PASSWORD; }
1820 | #line 1821 "y.tab.c"
1821 |     break;
1822 | 
1823 |   case 20: /* field_type: NUMBER  */
1824 | #line 281 "parser.y"
1825 |              { (yyval.field_type) = FIELD_NUMBER; }
1826 | #line 1827 "y.tab.c"
1827 |     break;
1828 | 
1829 |   case 21: /* field_type: TEXTAREA  */
1830 | #line 282 "parser.y"
1831 |                { (yyval.field_type) = FIELD_TEXTAREA; }
1832 | #line 1833 "y.tab.c"
1833 |     break;
1834 | 
1835 |   case 22: /* field_type: DATE  */
1836 | #line 283 "parser.y"
1837 |            { (yyval.field_type) = FIELD_DATE; }
1838 | #line 1839 "y.tab.c"
1839 |     break;
1840 | 
1841 |   case 23: /* field_type: CHECKBOX  */
1842 | #line 284 "parser.y"
1843 |                { (yyval.field_type) = FIELD_CHECKBOX; }
1844 | #line 1845 "y.tab.c"
1845 |     break;
1846 | 
1847 |   case 24: /* field_type: DROPDOWN  */
1848 | #line 285 "parser.y"
1849 |                { (yyval.field_type) = FIELD_DROPDOWN; }
1850 | #line 1851 "y.tab.c"
1851 |     break;
1852 | 
1853 |   case 25: /* field_type: RADIO  */
1854 | #line 286 "parser.y"
1855 |             { (yyval.field_type) = FIELD_RADIO; }
1856 | #line 1857 "y.tab.c"
1857 |     break;
1858 | 
1859 |   case 26: /* field_type: FILE_TYPE  */
1860 | #line 287 "parser.y"
1861 |                 { (yyval.field_type) = FIELD_FILE; }
1862 | #line 1863 "y.tab.c"
1863 |     break;
1864 | 
1865 |   case 27: /* field_attribute: REQUIRED  */
1866 | #line 290 "parser.y"
1867 |                           { (yyval.num) = 1; }
1868 | #line 1869 "y.tab.c"
1869 |     break;
1870 | 
1871 |   case 28: /* field_attribute: OPTIONAL  */
1872 | #line 291 "parser.y"
1873 |                { (yyval.num) = 0; }
1874 | #line 1875 "y.tab.c"
1875 |     break;
1876 | 
1877 |   case 29: /* field_attribute: attribute_type STRING_LITERAL  */
1878 | #line 293 "parser.y"
1879 |     {
1880 |         if (current_section && current_section->field_count > 0) {
1881 |             set_field_attribute(&current_section->fields[current_section->field_count - 1], (yyvsp[-1].attribute_type), (yyvsp[0].str));
1882 |         }
1883 |     }
1884 | #line 1885 "y.tab.c"
1885 |     break;
1886 | 
1887 |   case 30: /* field_attribute: OPTIONS '{' option_list '}'  */
1888 | #line 299 "parser.y"
1889 |     {
1890 |         if (current_section && current_section->field_count > 0) {
1891 |             Field* field = &current_section->fields[current_section->field_count - 1];
1892 |             if (field->type != FIELD_DROPDOWN && field->type != FIELD_RADIO) {
1893 |                 yyerror("Options can only be specified for dropdown and radio fields");
1894 |                 YYERROR;
1895 |             }
1896 |         }
1897 |     }
1898 | #line 1899 "y.tab.c"
1899 |     break;
1900 | 
1901 |   case 31: /* attribute_type: MIN_LENGTH  */
1902 | #line 310 "parser.y"
1903 |                            { (yyval.attribute_type) = ATTR_MIN_LENGTH; }
1904 | #line 1905 "y.tab.c"
1905 |     break;
1906 | 
1907 |   case 32: /* attribute_type: MAX_LENGTH  */
1908 | #line 311 "parser.y"
1909 |                  { (yyval.attribute_type) = ATTR_MAX_LENGTH; }
1910 | #line 1911 "y.tab.c"
1911 |     break;
1912 | 
1913 |   case 33: /* attribute_type: MIN_VALUE  */
1914 | #line 312 "parser.y"
1915 |                 { (yyval.attribute_type) = ATTR_MIN_VALUE; }
1916 | #line 1917 "y.tab.c"
1917 |     break;
1918 | 
1919 |   case 34: /* attribute_type: MAX_VALUE  */
1920 | #line 313 "parser.y"
1921 |                 { (yyval.attribute_type) = ATTR_MAX_VALUE; }
1922 | #line 1923 "y.tab.c"
1923 |     break;
1924 | 
1925 |   case 35: /* attribute_type: ROWS  */
1926 | #line 314 "parser.y"
1927 |            { (yyval.attribute_type) = ATTR_ROWS; }
1928 | #line 1929 "y.tab.c"
1929 |     break;
1930 | 
1931 |   case 36: /* attribute_type: COLS  */
1932 | #line 315 "parser.y"
1933 |            { (yyval.attribute_type) = ATTR_COLS; }
1934 | #line 1935 "y.tab.c"
1935 |     break;
1936 | 
1937 |   case 37: /* attribute_type: PATTERN  */
1938 | #line 316 "parser.y"
1939 |               { (yyval.attribute_type) = ATTR_PATTERN; }
1940 | #line 1941 "y.tab.c"
1941 |     break;
1942 | 
1943 |   case 38: /* attribute_type: DEFAULT  */
1944 | #line 317 "parser.y"
1945 |               { (yyval.attribute_type) = ATTR_DEFAULT; }
1946 | #line 1947 "y.tab.c"
1947 |     break;
1948 | 
1949 |   case 40: /* option_list: option_list STRING_LITERAL  */
1950 | #line 322 "parser.y"
1951 |     {
1952 |         if (current_section && current_section->field_count > 0) {
1953 |             add_field_option(&current_section->fields[current_section->field_count - 1], (yyvsp[0].str));
1954 |         }
1955 |     }
1956 | #line 1957 "y.tab.c"
1957 |     break;
1958 | 
1959 | 
1960 | #line 1961 "y.tab.c"
1961 | 
1962 |       default: break;
1963 |     }
1964 |   /* User semantic actions sometimes alter yychar, and that requires
1965 |      that yytoken be updated with the new translation.  We take the
1966 |      approach of translating immediately before every use of yytoken.
1967 |      One alternative is translating here after every semantic action,
1968 |      but that translation would be missed if the semantic action invokes
1969 |      YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
1970 |      if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
1971 |      incorrect destructor might then be invoked immediately.  In the
1972 |      case of YYERROR or YYBACKUP, subsequent parser actions might lead
1973 |      to an incorrect destructor call or verbose syntax error message
1974 |      before the lookahead is translated.  */
1975 |   YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);
1976 | 
1977 |   YYPOPSTACK (yylen);
1978 |   yylen = 0;
1979 | 
1980 |   *++yyvsp = yyval;
1981 | 
1982 |   /* Now 'shift' the result of the reduction.  Determine what state
1983 |      that goes to, based on the state we popped back to and the rule
1984 |      number reduced by.  */
1985 |   {
1986 |     const int yylhs = yyr1[yyn] - YYNTOKENS;
1987 |     const int yyi = yypgoto[yylhs] + *yyssp;
1988 |     yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
1989 |                ? yytable[yyi]
1990 |                : yydefgoto[yylhs]);
1991 |   }
1992 | 
1993 |   goto yynewstate;
1994 | 
1995 | 
1996 | /*--------------------------------------.
1997 | | yyerrlab -- here on detecting error.  |
1998 | `--------------------------------------*/
1999 | yyerrlab:
2000 |   /* Make sure we have latest lookahead translation.  See comments at
2001 |      user semantic actions for why this is necessary.  */
2002 |   yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
2003 |   /* If not already recovering from an error, report this error.  */
2004 |   if (!yyerrstatus)
2005 |     {
2006 |       ++yynerrs;
2007 |       {
2008 |         yypcontext_t yyctx
2009 |           = {yyssp, yytoken};
2010 |         char const *yymsgp = YY_("syntax error");
2011 |         int yysyntax_error_status;
2012 |         yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
2013 |         if (yysyntax_error_status == 0)
2014 |           yymsgp = yymsg;
2015 |         else if (yysyntax_error_status == -1)
2016 |           {
2017 |             if (yymsg != yymsgbuf)
2018 |               YYSTACK_FREE (yymsg);
2019 |             yymsg = YY_CAST (char *,
2020 |                              YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
2021 |             if (yymsg)
2022 |               {
2023 |                 yysyntax_error_status
2024 |                   = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
2025 |                 yymsgp = yymsg;
2026 |               }
2027 |             else
2028 |               {
2029 |                 yymsg = yymsgbuf;
2030 |                 yymsg_alloc = sizeof yymsgbuf;
2031 |                 yysyntax_error_status = YYENOMEM;
2032 |               }
2033 |           }
2034 |         yyerror (yymsgp);
2035 |         if (yysyntax_error_status == YYENOMEM)
2036 |           YYNOMEM;
2037 |       }
2038 |     }
2039 | 
2040 |   if (yyerrstatus == 3)
2041 |     {
2042 |       /* If just tried and failed to reuse lookahead token after an
2043 |          error, discard it.  */
2044 | 
2045 |       if (yychar <= YYEOF)
2046 |         {
2047 |           /* Return failure if at end of input.  */
2048 |           if (yychar == YYEOF)
2049 |             YYABORT;
2050 |         }
2051 |       else
2052 |         {
2053 |           yydestruct ("Error: discarding",
2054 |                       yytoken, &yylval);
2055 |           yychar = YYEMPTY;
2056 |         }
2057 |     }
2058 | 
2059 |   /* Else will try to reuse lookahead token after shifting the error
2060 |      token.  */
2061 |   goto yyerrlab1;
2062 | 
2063 | 
2064 | /*---------------------------------------------------.
2065 | | yyerrorlab -- error raised explicitly by YYERROR.  |
2066 | `---------------------------------------------------*/
2067 | yyerrorlab:
2068 |   /* Pacify compilers when the user code never invokes YYERROR and the
2069 |      label yyerrorlab therefore never appears in user code.  */
2070 |   if (0)
2071 |     YYERROR;
2072 |   ++yynerrs;
2073 | 
2074 |   /* Do not reclaim the symbols of the rule whose action triggered
2075 |      this YYERROR.  */
2076 |   YYPOPSTACK (yylen);
2077 |   yylen = 0;
2078 |   YY_STACK_PRINT (yyss, yyssp);
2079 |   yystate = *yyssp;
2080 |   goto yyerrlab1;
2081 | 
2082 | 
2083 | /*-------------------------------------------------------------.
2084 | | yyerrlab1 -- common code for both syntax error and YYERROR.  |
2085 | `-------------------------------------------------------------*/
2086 | yyerrlab1:
2087 |   yyerrstatus = 3;      /* Each real token shifted decrements this.  */
2088 | 
2089 |   /* Pop stack until we find a state that shifts the error token.  */
2090 |   for (;;)
2091 |     {
2092 |       yyn = yypact[yystate];
2093 |       if (!yypact_value_is_default (yyn))
2094 |         {
2095 |           yyn += YYSYMBOL_YYerror;
2096 |           if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
2097 |             {
2098 |               yyn = yytable[yyn];
2099 |               if (0 < yyn)
2100 |                 break;
2101 |             }
2102 |         }
2103 | 
2104 |       /* Pop the current state because it cannot handle the error token.  */
2105 |       if (yyssp == yyss)
2106 |         YYABORT;
2107 | 
2108 | 
2109 |       yydestruct ("Error: popping",
2110 |                   YY_ACCESSING_SYMBOL (yystate), yyvsp);
2111 |       YYPOPSTACK (1);
2112 |       yystate = *yyssp;
2113 |       YY_STACK_PRINT (yyss, yyssp);
2114 |     }
2115 | 
2116 |   YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
2117 |   *++yyvsp = yylval;
2118 |   YY_IGNORE_MAYBE_UNINITIALIZED_END
2119 | 
2120 | 
2121 |   /* Shift the error token.  */
2122 |   YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);
2123 | 
2124 |   yystate = yyn;
2125 |   goto yynewstate;
2126 | 
2127 | 
2128 | /*-------------------------------------.
2129 | | yyacceptlab -- YYACCEPT comes here.  |
2130 | `-------------------------------------*/
2131 | yyacceptlab:
2132 |   yyresult = 0;
2133 |   goto yyreturnlab;
2134 | 
2135 | 
2136 | /*-----------------------------------.
2137 | | yyabortlab -- YYABORT comes here.  |
2138 | `-----------------------------------*/
2139 | yyabortlab:
2140 |   yyresult = 1;
2141 |   goto yyreturnlab;
2142 | 
2143 | 
2144 | /*-----------------------------------------------------------.
2145 | | yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
2146 | `-----------------------------------------------------------*/
2147 | yyexhaustedlab:
2148 |   yyerror (YY_("memory exhausted"));
2149 |   yyresult = 2;
2150 |   goto yyreturnlab;
2151 | 
2152 | 
2153 | /*----------------------------------------------------------.
2154 | | yyreturnlab -- parsing is finished, clean up and return.  |
2155 | `----------------------------------------------------------*/
2156 | yyreturnlab:
2157 |   if (yychar != YYEMPTY)
2158 |     {
2159 |       /* Make sure we have latest lookahead translation.  See comments at
2160 |          user semantic actions for why this is necessary.  */
2161 |       yytoken = YYTRANSLATE (yychar);
2162 |       yydestruct ("Cleanup: discarding lookahead",
2163 |                   yytoken, &yylval);
2164 |     }
2165 |   /* Do not reclaim the symbols of the rule whose action triggered
2166 |      this YYABORT or YYACCEPT.  */
2167 |   YYPOPSTACK (yylen);
2168 |   YY_STACK_PRINT (yyss, yyssp);
2169 |   while (yyssp != yyss)
2170 |     {
2171 |       yydestruct ("Cleanup: popping",
2172 |                   YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
2173 |       YYPOPSTACK (1);
2174 |     }
2175 | #ifndef yyoverflow
2176 |   if (yyss != yyssa)
2177 |     YYSTACK_FREE (yyss);
2178 | #endif
2179 |   if (yymsg != yymsgbuf)
2180 |     YYSTACK_FREE (yymsg);
2181 |   return yyresult;
2182 | }
2183 | 
2184 | #line 329 "parser.y"
2185 | 
2186 | 
2187 | void yyerror(const char *s) {
2188 |     fprintf(stderr, "Error at line %d: %s\n", yylineno, s);
2189 | }
2190 | 
2191 | int main() {
2192 |     int result = yyparse();
2193 |     cleanup_form(current_form);
2194 |     return result;
2195 | }
```

FormLang/src/y.tab.h
```
1 | /* A Bison parser, made by GNU Bison 3.8.2.  */
2 | 
3 | /* Bison interface for Yacc-like parsers in C
4 | 
5 |    Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
6 |    Inc.
7 | 
8 |    This program is free software: you can redistribute it and/or modify
9 |    it under the terms of the GNU General Public License as published by
10 |    the Free Software Foundation, either version 3 of the License, or
11 |    (at your option) any later version.
12 | 
13 |    This program is distributed in the hope that it will be useful,
14 |    but WITHOUT ANY WARRANTY; without even the implied warranty of
15 |    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
16 |    GNU General Public License for more details.
17 | 
18 |    You should have received a copy of the GNU General Public License
19 |    along with this program.  If not, see <https://www.gnu.org/licenses/>.  */
20 | 
21 | /* As a special exception, you may create a larger work that contains
22 |    part or all of the Bison parser skeleton and distribute that work
23 |    under terms of your choice, so long as that work isn't itself a
24 |    parser generator using the skeleton or a modified version thereof
25 |    as a parser skeleton.  Alternatively, if you modify or redistribute
26 |    the parser skeleton itself, you may (at your option) remove this
27 |    special exception, which will cause the skeleton and the resulting
28 |    Bison output files to be licensed under the GNU General Public
29 |    License without this special exception.
30 | 
31 |    This special exception was added by the Free Software Foundation in
32 |    version 2.2 of Bison.  */
33 | 
34 | /* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
35 |    especially those whose name start with YY_ or yy_.  They are
36 |    private implementation details that can be changed or removed.  */
37 | 
38 | #ifndef YY_YY_Y_TAB_H_INCLUDED
39 | # define YY_YY_Y_TAB_H_INCLUDED
40 | /* Debug traces.  */
41 | #ifndef YYDEBUG
42 | # define YYDEBUG 0
43 | #endif
44 | #if YYDEBUG
45 | extern int yydebug;
46 | #endif
47 | 
48 | /* Token kinds.  */
49 | #ifndef YYTOKENTYPE
50 | # define YYTOKENTYPE
51 |   enum yytokentype
52 |   {
53 |     YYEMPTY = -2,
54 |     YYEOF = 0,                     /* "end of file"  */
55 |     YYerror = 256,                 /* error  */
56 |     YYUNDEF = 257,                 /* "invalid token"  */
57 |     FORM = 258,                    /* FORM  */
58 |     SECTION = 259,                 /* SECTION  */
59 |     FIELD = 260,                   /* FIELD  */
60 |     TEXT = 261,                    /* TEXT  */
61 |     EMAIL = 262,                   /* EMAIL  */
62 |     PASSWORD = 263,                /* PASSWORD  */
63 |     NUMBER = 264,                  /* NUMBER  */
64 |     TEXTAREA = 265,                /* TEXTAREA  */
65 |     DATE = 266,                    /* DATE  */
66 |     CHECKBOX = 267,                /* CHECKBOX  */
67 |     DROPDOWN = 268,                /* DROPDOWN  */
68 |     RADIO = 269,                   /* RADIO  */
69 |     FILE_TYPE = 270,               /* FILE_TYPE  */
70 |     REQUIRED = 271,                /* REQUIRED  */
71 |     OPTIONAL = 272,                /* OPTIONAL  */
72 |     IDENTIFIER = 273,              /* IDENTIFIER  */
73 |     NUMBER_LITERAL = 274,          /* NUMBER_LITERAL  */
74 |     STRING_LITERAL = 275,          /* STRING_LITERAL  */
75 |     MIN_LENGTH = 276,              /* MIN_LENGTH  */
76 |     MAX_LENGTH = 277,              /* MAX_LENGTH  */
77 |     MIN_VALUE = 278,               /* MIN_VALUE  */
78 |     MAX_VALUE = 279,               /* MAX_VALUE  */
79 |     ROWS = 280,                    /* ROWS  */
80 |     COLS = 281,                    /* COLS  */
81 |     PATTERN = 282,                 /* PATTERN  */
82 |     DEFAULT = 283,                 /* DEFAULT  */
83 |     OPTIONS = 284                  /* OPTIONS  */
84 |   };
85 |   typedef enum yytokentype yytoken_kind_t;
86 | #endif
87 | /* Token kinds.  */
88 | #define YYEMPTY -2
89 | #define YYEOF 0
90 | #define YYerror 256
91 | #define YYUNDEF 257
92 | #define FORM 258
93 | #define SECTION 259
94 | #define FIELD 260
95 | #define TEXT 261
96 | #define EMAIL 262
97 | #define PASSWORD 263
98 | #define NUMBER 264
99 | #define TEXTAREA 265
100 | #define DATE 266
101 | #define CHECKBOX 267
102 | #define DROPDOWN 268
103 | #define RADIO 269
104 | #define FILE_TYPE 270
105 | #define REQUIRED 271
106 | #define OPTIONAL 272
107 | #define IDENTIFIER 273
108 | #define NUMBER_LITERAL 274
109 | #define STRING_LITERAL 275
110 | #define MIN_LENGTH 276
111 | #define MAX_LENGTH 277
112 | #define MIN_VALUE 278
113 | #define MAX_VALUE 279
114 | #define ROWS 280
115 | #define COLS 281
116 | #define PATTERN 282
117 | #define DEFAULT 283
118 | #define OPTIONS 284
119 | 
120 | /* Value type.  */
121 | #if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
122 | union YYSTYPE
123 | {
124 | #line 169 "parser.y"
125 | 
126 |     char* str;
127 |     int num;
128 |     Form* form;
129 |     Section* section;
130 |     FieldType field_type;
131 |     int attribute_type;
132 | 
133 | #line 134 "y.tab.h"
134 | 
135 | };
136 | typedef union YYSTYPE YYSTYPE;
137 | # define YYSTYPE_IS_TRIVIAL 1
138 | # define YYSTYPE_IS_DECLARED 1
139 | #endif
140 | 
141 | 
142 | extern YYSTYPE yylval;
143 | 
144 | 
145 | int yyparse (void);
146 | 
147 | 
148 | #endif /* !YY_YY_Y_TAB_H_INCLUDED  */
```

FormLang/tests/test.sh
```
1 | #!/bin/bash
2 | 
3 | # Test script for FormLang++
4 | 
5 | # Colors for output
6 | GREEN='\033[0;32m'
7 | RED='\033[0;31m'
8 | YELLOW='\033[1;33m'
9 | NC='\033[0m' # No Color
10 | 
11 | # Function to run a test
12 | run_test() {
13 |     local input_file=$1
14 |     local expected_output=$2
15 |     local test_name=$3
16 |     local output_file="../output/$(basename $input_file .form).html"
17 |     local error_file="../output/$(basename $input_file .form).err"
18 | 
19 |     echo -e "${YELLOW}Running test: $test_name${NC}"
20 |     echo "Input file: $input_file"
21 |     echo "Output file: $output_file"
22 | 
23 |     # Run the parser and save output to file
24 |     ../bin/formLang < $input_file > $output_file 2>$error_file
25 |     result=$?
26 | 
27 |     if [ $result -eq 0 ]; then
28 |         if [ "$expected_output" = "success" ]; then
29 |             echo -e "${GREEN}Test passed: $test_name${NC}"
30 |             echo "HTML output saved to: $output_file"
31 |             return 0
32 |         else
33 |             echo -e "${RED}Test failed: $test_name (Expected error but got success)${NC}"
34 |             return 1
35 |         fi
36 |     else
37 |         if [ "$expected_output" = "error" ]; then
38 |             echo -e "${GREEN}Test passed: $test_name (Expected error)${NC}"
39 |             echo "Error output:"
40 |             cat $error_file
41 |             return 0
42 |         else
43 |             echo -e "${RED}Test failed: $test_name${NC}"
44 |             echo "Error output:"
45 |             cat $error_file
46 |             return 1
47 |         fi
48 |     fi
49 | }
50 | 
51 | # Create output directory if it doesn't exist
52 | mkdir -p ../output
53 | 
54 | # Test cases
55 | echo "Starting FormLang++ tests..."
56 | 
57 | # Test 1: Basic form with text fields
58 | run_test "../examples/registration.form" "success" "Basic Registration Form"
59 | 
60 | # Test 2: Form with all field types
61 | run_test "../examples/all_fields.form" "success" "All Field Types"
62 | 
63 | # Test 3: Edge cases
64 | run_test "../examples/edge_cases.form" "success" "Edge Cases"
65 | 
66 | # Test 4: Invalid form syntax
67 | cat > ../examples/invalid.form << 'EOF'
68 | form Invalid {
69 |   section Test {
70 |     field test: invalid required;
71 |     field test2: text
72 |   }
73 | }
74 | EOF
75 | run_test "../examples/invalid.form" "error" "Invalid Syntax"
76 | 
77 | # Test 5: Empty form
78 | cat > ../examples/empty.form << 'EOF'
79 | form Empty {}
80 | EOF
81 | run_test "../examples/empty.form" "success" "Empty Form"
82 | 
83 | # Test 6: Form with duplicate field names
84 | cat > ../examples/duplicate.form << 'EOF'
85 | form Duplicate {
86 |   section Test {
87 |     field test: text required;
88 |     field test: text required;
89 |   }
90 | }
91 | EOF
92 | run_test "../examples/duplicate.form" "error" "Duplicate Field Names"
93 | 
94 | # Test 7: Form with invalid field type
95 | cat > ../examples/invalid_type.form << 'EOF'
96 | form InvalidType {
97 |   section Test {
98 |     field test: invalid required;
99 |   }
100 | }
101 | EOF
102 | run_test "../examples/invalid_type.form" "error" "Invalid Field Type"
103 | 
104 | # Test 8: Form with missing semicolon
105 | cat > ../examples/missing_semicolon.form << 'EOF'
106 | form MissingSemicolon {
107 |   section Test {
108 |     field test: text required
109 |   }
110 | }
111 | EOF
112 | run_test "../examples/missing_semicolon.form" "error" "Missing Semicolon"
113 | 
114 | # Test 9: Form with invalid section nesting
115 | cat > ../examples/invalid_nesting.form << 'EOF'
116 | form InvalidNesting {
117 |   section Outer {
118 |     section Inner {
119 |       field test: text required;
120 |     }
121 |   }
122 | }
123 | EOF
124 | run_test "../examples/invalid_nesting.form" "error" "Invalid Section Nesting"
125 | 
126 | # Test 10: Form with invalid field attribute
127 | cat > ../examples/invalid_attribute.form << 'EOF'
128 | form InvalidAttribute {
129 |   section Test {
130 |     field test: text invalid;
131 |   }
132 | }
133 | EOF
134 | run_test "../examples/invalid_attribute.form" "error" "Invalid Field Attribute"
135 | 
136 | # Test 11: Form with missing field type
137 | cat > ../examples/missing_type.form << 'EOF'
138 | form MissingType {
139 |   section Test {
140 |     field test: required;
141 |   }
142 | }
143 | EOF
144 | run_test "../examples/missing_type.form" "error" "Missing Field Type"
145 | 
146 | # Test 12: Form with missing field name
147 | cat > ../examples/missing_name.form << 'EOF'
148 | form MissingName {
149 |   section Test {
150 |     field : text required;
151 |   }
152 | }
153 | EOF
154 | run_test "../examples/missing_name.form" "error" "Missing Field Name"
155 | 
156 | # Cleanup temporary test files
157 | rm -f ../examples/empty.form ../examples/duplicate.form ../examples/invalid_type.form \
158 |       ../examples/missing_semicolon.form ../examples/invalid_nesting.form \
159 |       ../examples/invalid_attribute.form ../examples/missing_type.form \
160 |       ../examples/missing_name.form
161 | 
162 | echo "Tests completed." 
```
