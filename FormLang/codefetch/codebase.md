Project Structure:
├── Makefile
├── bin
│   └── formLang
├── docs
│   └── syntax.md
├── examples
│   ├── address_edge.form
│   ├── address_validation.form
│   ├── all_fields.form
│   ├── attribute_edge_cases.form
│   ├── complex_form.form
│   ├── comprehensive_test.form
│   ├── edge_cases.form
│   ├── empty_section.form
│   ├── field_name_edge_cases.form
│   ├── full_feature_test.form
│   ├── invalid.form
│   ├── invalid_syntax.form
│   ├── long_field_names.form
│   ├── metadata_test.form
│   ├── milestone5_simple.form
│   ├── milestone5_test.form
│   ├── minimal_validation.form
│   ├── mixed_attributes.form
│   ├── multiple_empty_sections.form
│   ├── options_test.form
│   ├── password_strength.form
│   ├── registration.form
│   ├── section_edge_cases.form
│   ├── single_field_sections.form
│   ├── single_section.form
│   ├── test.form
│   ├── test_milestone4.form
│   ├── username_password.form
│   └── validation_test.form
├── obj
│   ├── html_generator.o
│   ├── lex.yy.o
│   └── parser.tab.o
├── output
│   ├── address_edge.html
│   ├── address_validation.html
│   ├── comprehensive_test.html
│   ├── edge_cases.html
│   ├── invalid_syntax.html
│   ├── metadata_edge_test.html
│   ├── metadata_test.html
│   ├── milestone5_simple.html
│   ├── milestone5_test.html
│   ├── minimal_validation.html
│   ├── options_test.html
│   ├── password_strength.html
│   ├── registration.html
│   ├── test.html
│   ├── username_password.html
│   └── validation_test.html
├── parser.output
├── parser.tab.c
├── progress.md
├── src
│   ├── Makefile
│   ├── debug.log
│   ├── formLang
│   ├── formLang.h
│   ├── html_generator.c
│   ├── lex.yy.c
│   ├── lexer.l
│   ├── parser.output
│   ├── parser.tab.c
│   ├── parser.tab.h
│   ├── parser.y
│   ├── y.tab.c
│   └── y.tab.h
└── tests
    └── test.sh


Makefile
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

parser.output
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

parser.tab.c
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

progress.md
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
31 | ## Milestone 4: Extended Field Types ✅
32 | - [x] Additional field types
33 |   - [x] Checkbox
34 |   - [x] Radio buttons
35 |   - [x] Select dropdown
36 |   - [x] Textarea
37 |   - [x] File upload
38 |   - [x] Date picker
39 | - [x] Field validation rules
40 |   - [x] Min/max length
41 |   - [x] Pattern matching
42 |   - [x] Custom validation
43 |   - [x] Default values
44 | - [x] Client-side validation
45 |   - [x] Real-time validation
46 |   - [x] Error message display
47 |   - [x] Password strength validation
48 |   - [x] Email format validation
49 | 
50 | ## Milestone 5: Registration-Specific Fields 🟡
51 | - [x] Specialized field types
52 |   - [x] Username field with pattern validation
53 |   - [x] Password field with strength validation
54 |   - [x] Confirmable email fields
55 |   - [x] Address fields with sub-components
56 | - [x] Enhanced validation
57 |   - [x] Password strength checking
58 |   - [x] Field confirmation logic
59 |   - [x] Custom error messages
60 |   - [x] Address subfield validation
61 | - [ ] Parser improvements needed
62 |   - [ ] Complex validation expressions
63 |   - [ ] Specialized field type handling
64 |   - [ ] Address subfield validation
65 |   - [x] Error handling for validation blocks
66 | 
67 | ## Current Status
68 | - Basic and extended field types implemented and tested
69 | - Comprehensive validation system in place
70 | - Client-side validation working with real-time feedback
71 | - Test suite covers all implemented features
72 | - Error handling and recovery mechanisms working
73 | - Documentation updated with latest features
74 | 
```

examples/address_edge.form
```
1 | form AddressEdge {
2 |     section Addr {
3 |         field address: address required;
4 |     }
5 |     validate {
6 |         if address_street == 0 { error "Street required!"; }
7 |         if address_zip < 10000 { error "ZIP too short!"; }
8 |     }
9 | } 
```

examples/address_validation.form
```
1 | form AddressForm {
2 |     section AddressInfo {
3 |         field address: address required;
4 |         field zip: number required min 10000 max 99999;
5 |     }
6 |     validate {
7 |         if zip < 10000 { error "ZIP must be at least 5 digits."; }
8 |         if zip > 99999 { error "ZIP must be at most 5 digits."; }
9 |     }
10 | } 
```

examples/all_fields.form
```
1 | form AllFieldsTest {
2 |     section FieldTypes {
3 |         field text_field: text minLength 3 maxLength 50 pattern "^[A-Za-z ]+$" required;
4 |         field email_field: email required;
5 |         field password_field: password minLength 8 required;
6 |         field number_field: number min 0 max 100 default 50;
7 |         field textarea_field: textarea rows 10 cols 50 required;
8 |         field date_field: date required;
9 |         field checkbox_field: checkbox default 1;
10 |         field radio_field: radio required;
11 |         field dropdown_field: dropdown required;
12 |         field file_field: file optional;
13 |     }
14 | } 
```

examples/attribute_edge_cases.form
```
1 | form AttributeEdgeCases {
2 |     section PatternEdgeCases {
3 |         field empty_pattern: text pattern "" required;
4 |         field complex_pattern: text pattern "^[A-Za-z0-9!@#$%^&*()_+\\-=\\[\\]{};':\"\\\\|,.<>\\/? ]+$" required;
5 |         field email_pattern: text pattern "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$" required;
6 |         field url_pattern: text pattern "^(https?:\\/\\/)?([\\da-z\\.-]+)\\.([a-z\\.]{2,6})([\\/\\w \\.-]*)*\\/?$" required;
7 |     }
8 | 
9 |     section LengthEdgeCases {
10 |         field zero_length: text minLength 0 maxLength 0 required;
11 |         field max_length: text minLength 1 maxLength 1000 required;
12 |         field min_length: text minLength 1 maxLength 10 required;
13 |     }
14 | 
15 |     section NumberEdgeCases {
16 |         field zero_range: number min 0 max 0 required;
17 |         field negative_range: number min -1000 max -1 required;
18 |         field large_range: number min 0 max 1000000 required;
19 |         field decimal_range: number min 0 max 1 required;
20 |     }
21 | 
22 |     section DefaultValueEdgeCases {
23 |         field empty_default: text default "" required;
24 |         field space_default: text default " " required;
25 |         field special_chars_default: text default "!@#$%^&*()" required;
26 |         field unicode_default: text default "测试" required;
27 |         field zero_default: number default 0 required;
28 |         field negative_default: number default -1 required;
29 |     }
30 | 
31 |     section MixedAttributes {
32 |         field complex_field: text minLength 1 maxLength 100 pattern "^[A-Za-z]+$" default "test" required;
33 |         field all_optional: text minLength 0 maxLength 1000 pattern ".*" default "" optional;
34 |     }
35 | } 
```

examples/complex_form.form
```
1 | form ComplexForm {
2 |     section PersonalInfo {
3 |         field full_name: text minLength 5 maxLength 100 pattern "^[A-Za-z ]+$" required;
4 |         field birth_date: date required;
5 |         field age: number min 18 max 120 required;
6 |         field gender: radio required;
7 |     }
8 | 
9 |     section ContactInfo {
10 |         field email: email required;
11 |         field phone: text pattern "^[0-9]{10}$" required;
12 |         field address: textarea rows 3 cols 50 required;
13 |     }
14 |     
15 |     section AccountInfo {
16 |         field username: text minLength 5 maxLength 20 pattern "^[a-zA-Z0-9_]+$" required;
17 |         field password: password minLength 8 required;
18 |         field confirm_password: password minLength 8 required;
19 |     }
20 |     
21 |     section Preferences {
22 |         field newsletter: checkbox default 1;
23 |         field theme: dropdown required;
24 |         field bio: textarea rows 5 cols 40 optional;
25 |         field avatar: file optional;
26 |     }
27 | } 
```

examples/comprehensive_test.form
```
1 | form ComprehensiveTest {
2 |     meta author = "SE2062 Team";
3 |     meta version = "2.0";
4 |     meta description = "Comprehensive test form demonstrating all FormLang++ features";
5 |     meta created = "2024-03-20";
6 |     meta category = "Registration";
7 | 
8 |     section PersonalInfo {
9 |         field fullName: text {
10 |             required;
11 |             pattern = "^[a-zA-Z ]{2,50}$";
12 |             minLength = 2;
13 |             maxLength = 50;
14 |         }
15 | 
16 |         field email: email {
17 |             required;
18 |             pattern = "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$";
19 |         }
20 | 
21 |         field phone: text {
22 |             required;
23 |             pattern = "^\\+?[1-9]\\d{1,14}$";
24 |         }
25 | 
26 |         field age: number {
27 |             required;
28 |             min = 18;
29 |             max = 120;
30 |         }
31 | 
32 |         field birthDate: date {
33 |             required;
34 |         }
35 |     }
36 | 
37 |     section AccountSecurity {
38 |         field username: username {
39 |             required;
40 |             pattern = "^[a-zA-Z0-9_]{3,20}$";
41 |             minLength = 3;
42 |             maxLength = 20;
43 |         }
44 | 
45 |         field password: password {
46 |             required;
47 |             pattern = "^(?=.*[A-Za-z])(?=.*\\d)(?=.*[@$!%*#?&])[A-Za-z\\d@$!%*#?&]{8,}$";
48 |             minLength = 8;
49 |             strength = 3;
50 |         }
51 | 
52 |         field confirmPassword: password {
53 |             required;
54 |             confirm = "password";
55 |         }
56 |     }
57 | 
58 |     section AddressInfo {
59 |         field homeAddress: address {
60 |             required;
61 |         }
62 | 
63 |         field shippingAddress: address {
64 |             optional;
65 |         }
66 |     }
67 | 
68 |     section Preferences {
69 |         field newsletter: checkbox {
70 |             default = "true";
71 |         }
72 | 
73 |         field subscriptionType: dropdown {
74 |             required;
75 |             default = "monthly";
76 |         }
77 | 
78 |         field preferredContact: radio {
79 |             required;
80 |             default = "email";
81 |         }
82 | 
83 |         field profilePicture: file {
84 |             optional;
85 |         }
86 | 
87 |         field bio: textarea {
88 |             optional;
89 |             rows = 5;
90 |             cols = 50;
91 |             maxLength = 500;
92 |         }
93 |     }
94 | 
95 |     validate {
96 |         if age < 18 {
97 |             error "You must be at least 18 years old to register.";
98 |         }
99 |         if password == username {
100 |             error "Password cannot be the same as username.";
101 |         }
102 |     }
103 | } 
```

examples/edge_cases.form
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
30 | 
31 |   section SpecialFields {
32 |     field empty_field: text optional;
33 |     field long_field_name_with_special_chars_and_numbers_123: text optional;
34 |     field field_with_underscores_and_hyphens: text optional;
35 |     field field_with_unicode_测试: text optional;
36 |   }
37 | 
38 |   section ValidationTests {
39 |     field min_length_test: text minLength 1 required;
40 |     field max_length_test: text maxLength 5 required;
41 |     field pattern_test: text pattern "^[A-Za-z0-9!@#$%^&*()_+]+$" required;
42 |     field number_range: number min -100 max 100 default 0;
43 |     field date_range: date required;
44 |   }
45 | 
46 |   section OptionalFields {
47 |     field optional_text: text optional;
48 |     field optional_email: email optional;
49 |     field optional_number: number optional;
50 |     field optional_checkbox: checkbox optional;
51 |   }
52 | 
53 |   section DefaultValues {
54 |     field text_default: text default "Hello World" optional;
55 |     field number_default: number default 42 optional;
56 |     field checkbox_default: checkbox default 1 optional;
57 |   }
58 | 
59 |   section Numbers {
60 |     field min_only: number min 5;
61 |     field max_only: number max 10;
62 |     field min_max: number min 1 max 3;
63 |   }
64 | 
65 |   section Texts {
66 |     field pattern_only: text pattern "abc.*";
67 |     field required_only: text required;
68 |     field all: text required minLength 2 maxLength 4 pattern "^[A-Z]+$";
69 |   }
70 | 
71 |   validate {
72 |     if min_only < 5 { error "Below min!"; }
73 |     if max_only > 10 { error "Above max!"; }
74 |     if min_max < 1 { error "Too small!"; }
75 |     if min_max > 3 { error "Too big!"; }
76 |     if required_only == 0 { error "Required!"; }
77 |   }
78 | } 
```

examples/empty_section.form
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

examples/field_name_edge_cases.form
```
1 | form FieldNameEdgeCases {
2 |     section SpecialCharacters {
3 |         field field_with_dots: text required;
4 |         field field_with_at_symbol: text required;
5 |         field field_with_dollar: text required;
6 |         field field_with_hash: text required;
7 |         field field_with_percent: text required;
8 |         field field_with_ampersand: text required;
9 |         field field_with_star: text required;
10 |         field field_with_plus: text required;
11 |         field field_with_hyphen: text required;
12 |         field field_with_equals: text required;
13 |     }
14 | 
15 |     section UnicodeNames {
16 |         field unicode_chinese: text required;
17 |         field unicode_japanese: text required;
18 |         field unicode_korean: text required;
19 |         field unicode_hindi: text required;
20 |         field unicode_arabic: text required;
21 |     }
22 | 
23 |     section ReservedKeywords {
24 |         field form_field: text required;
25 |         field section_field: text required;
26 |         field field_field: text required;
27 |         field required_field: text required;
28 |         field optional_field: text required;
29 |     }
30 | 
31 |     section LengthEdgeCases {
32 |         field a: text required;
33 |         field very_long_field_name_that_exceeds_normal_length_but_should_still_work_properly: text required;
34 |     }
35 | } 
```

examples/full_feature_test.form
```
1 | form FullFeatureTest {
2 |     section TextFields {
3 |         field username: text pattern "^[A-Za-z0-9_]{3,20}$" minLength 3 maxLength 20 default "user123" required;
4 |         field nickname: text optional;
5 |         field bio: textarea minLength 10 maxLength 200 rows 4 cols 40 default "Hello!" required;
6 |     }
7 |     section EmailPassword {
8 |         field email: email pattern "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$" required;
9 |         field work_email: email default "user@company.com" optional;
10 |         field password: password pattern "^(?=.*[A-Za-z])(?=.*\d)[A-Za-z\d]{8,}$" minLength 8 maxLength 32 required;
11 |         field confirm_password: password required;
12 |     }
13 |     section NumbersAndDates {
14 |         field age: number min 18 max 120 default "25" required;
15 |         field price: number min 0.01 max 999.99 required;
16 |         field quantity: number default 1 min 1 max 100 required;
17 |         field birth_date: date required;
18 |         field appointment: date default "2024-12-31" optional;
19 |     }
20 |     section Choices {
21 |         field gender: radio default "other" required;
22 |         field subscription: radio optional;
23 |         field country: dropdown required;
24 |         field language: dropdown default "en" optional;
25 |     }
26 |     section Files {
27 |         field document: file accept "*.pdf,*.docx" required;
28 |         field image: file accept "image/*" optional;
29 |         field attachment: file accept "*/*" optional;
30 |     }
31 |     section Checkboxes {
32 |         field terms: checkbox required;
33 |         field newsletter: checkbox default "true" optional;
34 |     }
35 |     section Patterns {
36 |         field phone: text pattern "^\+?[\d\s-]{10,}$" required;
37 |         field postal_code: text pattern "^[A-Z]{2}\d{2}\s?\d{2}[A-Z]{2}$" required;
38 |         field url: text pattern "^(https?:\/\/)?([\da-z\.-]+)\.([a-z\.]{2,6})([\/\w \.-]*)*\/?$" optional;
39 |         field password_strong: password pattern "^(?=.*[A-Za-z])(?=.*\d)(?=.*[@$!%*#?&])[A-Za-z\d@$!%*#?&]{8,}$" required;
40 |     }
41 | } 
```

examples/invalid.form
```
1 | form Invalid {
2 |   section Test {
3 |     field test: invalid required;
4 |     field test2: text
5 |   }
6 | }
```

examples/invalid_syntax.form
```
1 | form InvalidSyntax {
2 |     section Bad {
3 |         field missing_type;
4 |         field no_colon text;
5 |         field bad: number min "abc";
6 |     }
7 |     validate {
8 |         if missing_type < 0 { error "Should not parse!"; }
9 |     }
10 | } 
```

examples/long_field_names.form
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

examples/metadata_test.form
```
1 | form MetadataTest {
2 |     meta author = "SE2062 Team";
3 |     meta version = "1.0";
4 |     meta description = "Test form for metadata and pattern support";
5 | 
6 |     section UserInfo {
7 |         field username: username {
8 |             required;
9 |             pattern = "^[a-zA-Z0-9_]{3,20}$";
10 |             minLength = 3;
11 |             maxLength = 20;
12 |         }
13 | 
14 |         field email: email {
15 |             required;
16 |             pattern = "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$";
17 |         }
18 | 
19 |         field password: password {
20 |             required;
21 |             pattern = "^(?=.*[A-Za-z])(?=.*\\d)[A-Za-z\\d]{8,}$";
22 |             minLength = 8;
23 |         }
24 |     }
25 | } 
```

examples/milestone5_simple.form
```
1 | form Milestone5Simple {
2 |     section UserInfo {
3 |         field username: username required minLength 4 maxLength 16;
4 |         field password: password required strength 3;
5 |         field confirmPassword: password required confirm password;
6 |     }
7 | 
8 |     section AddressInfo {
9 |         field homeAddress: address required;
10 |     }
11 | 
12 |     validate {
13 |         if username == 0 { error "Username is required."; }
14 |         if password == 0 { error "Password is required."; }
15 |         if confirmPassword != password { error "Passwords do not match."; }
16 |     }
17 | } 
```

examples/milestone5_test.form
```
1 | form Milestone5Test {
2 |     section UserInfo {
3 |         field username: username required minLength 4 maxLength 16 pattern "^[a-zA-Z0-9_]+$";
4 |         field password: password required strength 3;
5 |         field confirmPassword: password required confirm password;
6 |         field email: email required;
7 |         field confirmEmail: email required confirm email;
8 |     }
9 | 
10 |     section AddressInfo {
11 |         field homeAddress: address required;
12 |         field workAddress: address optional;
13 |     }
14 | 
15 |     validate {
16 |         if username == 0 { error "Username is required."; }
17 |         if password == 0 { error "Password is required."; }
18 |         if confirmPassword != password { error "Passwords do not match."; }
19 |         if email == 0 { error "Email is required."; }
20 |         if confirmEmail != email { error "Email addresses do not match."; }
21 |         if homeAddress_street == 0 { error "Home address street is required."; }
22 |         if homeAddress_zip < 10000 { error "Home address ZIP must be at least 5 digits."; }
23 |     }
24 | } 
```

examples/minimal_validation.form
```
1 | form MinimalValidation {
2 |     section Main {
3 |         field age: number required min 0 max 120;
4 |     }
5 |     validate {
6 |         if age < 18 { error "You must be at least 18."; }
7 |         if age > 100 { error "Age cannot exceed 100."; }
8 |     }
9 | } 
```

examples/mixed_attributes.form
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

examples/multiple_empty_sections.form
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

examples/options_test.form
```
1 | form OptionsTest {
2 |     meta author = "Test User";
3 |     meta version = "1.0";
4 | 
5 |     section TestSection {
6 |         field country: dropdown {
7 |             required;
8 |             options = ["USA", "UK", "Canada", "Australia", "Germany"];
9 |         }
10 | 
11 |         field gender: radio {
12 |             required;
13 |             options = ["Male", "Female", "Other", "Prefer not to say"];
14 |         }
15 | 
16 |         field favorite_color: dropdown {
17 |             options = ["Red", "Blue", "Green", "Yellow", "Purple"];
18 |         }
19 |     }
20 | } 
```

examples/registration.form
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

examples/section_edge_cases.form
```
1 | form SectionEdgeCases {
2 |     section EmptySection {
3 |     }
4 | 
5 |     section SingleFieldSection {
6 |         field test: text required;
7 |     }
8 | 
9 |     section UnicodeSectionName {
10 |         field test: text required;
11 |     }
12 | 
13 |     section SectionWithSpecialChars {
14 |         field test: text required;
15 |     }
16 | 
17 |     section VeryLongSectionNameThatExceedsNormalLengthButShouldStillWorkProperly {
18 |         field test: text required;
19 |     }
20 | 
21 |     section MultipleEmptySections {
22 |     }
23 | 
24 |     section AnotherEmptySection {
25 |     }
26 | 
27 |     section FinalSectionWithAllFieldTypes {
28 |         field text_field: text required;
29 |         field email_field: email required;
30 |         field password_field: password required;
31 |         field number_field: number required;
32 |         field textarea_field: textarea required;
33 |         field date_field: date required;
34 |         field checkbox_field: checkbox required;
35 |         field radio_field: radio required;
36 |         field dropdown_field: dropdown required;
37 |         field file_field: file required;
38 |     }
39 | } 
```

examples/single_field_sections.form
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

examples/single_section.form
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

examples/test.form
```
1 | form TestForm {
2 |     section UserInfo {
3 |         field username: username required minLength 3 maxLength 20 pattern "[a-zA-Z0-9_]+";
4 |         field email: email required;
5 |         field password: password required strength 3;
6 |         field confirmPassword: password required confirm password;
7 |         field fullName: text required minLength 2 maxLength 50;
8 |         field age: number required min 18 max 120;
9 |         field address: address required;
10 |         field bio: textarea rows 4 cols 50;
11 |         field gender: radio required;
12 |         field country: dropdown required;
13 |         field terms: checkbox required;
14 |     }
15 | } 
```

examples/test_milestone4.form
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

examples/validation_test.form
```
1 | form ValidationTest {
2 |     section UserInfo {
3 |         field username: username required minLength 3 maxLength 20 pattern "[a-zA-Z0-9_]+";
4 |         field email: email required;
5 |         field password: password required strength 3;
6 |         field confirmPassword: password required confirm password;
7 |         field age: number required min 18 max 120;
8 |         field score: number required min 0 max 100;
9 |     }
10 | 
11 |     validate {
12 |         if age < 18 { error "You must be at least 18 years old."; }
13 |         if score < 60 { error "Score must be at least 60 to pass."; }
14 |         if score > 100 { error "Score cannot exceed 100."; }
15 |     }
16 | 
17 |     section PatternTests {
18 |         field empty_pattern: text pattern ".*" required;
19 |         field complex_pattern: text pattern "^[A-Za-z0-9!@#$%^&*()_+\-=\[\]{};':\"\\|,.<>\/? ]+$" required;
20 |         field email_pattern: text pattern "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$" required;
21 |         field url_pattern: text pattern "^(https?:\/\/)?([\da-z\.-]+)\.([a-z\.]{2,6})([\/\w \.-]*)*\/?$" required;
22 |     }
23 | 
24 |     section RequiredTests {
25 |         field required_no_validation: text required;
26 |         field required_with_pattern: text pattern ".*" required;
27 |         field required_with_length: text minLength 1 maxLength 10 required;
28 |         field required_with_default: text default "test" required;
29 |     }
30 | 
31 |     section DropdownTests {
32 |         field required_dropdown: dropdown required;
33 |         field optional_dropdown: dropdown optional;
34 |         field dropdown_with_default: dropdown default "option1" required;
35 |     }
36 | 
37 |     section RadioTests {
38 |         field required_radio: radio required;
39 |         field optional_radio: radio optional;
40 |         field radio_with_default: radio default "option1" required;
41 |     }
42 | 
43 |     section FileTests {
44 |         field required_file: file required;
45 |         field optional_file: file optional;
46 |         field file_with_accept: file accept "image/*" required;
47 |     }
48 | 
49 |     section NumberTests {
50 |         field zero_range: number required;
51 |         field negative_range: number min -10 max -1 required;
52 |         field positive_range: number min 1 max 10 required;
53 |         field decimal_range: number min 0.1 max 1.0 required;
54 |     }
55 | 
56 |     section DefaultValueTests {
57 |         field empty_default: text default "" required;
58 |         field space_default: text default " " required;
59 |         field special_chars: text default "!@#$%^&*()" required;
60 |         field unicode_default: text default "测试" required;
61 |         field zero_default: number default "0" required;
62 |     }
63 | 
64 |     section MixedAttributes {
65 |         field complex_field: text pattern "^[A-Za-z]+$" minLength 1 maxLength 100 default "test" required;
66 |         field all_optional: text pattern ".*" maxLength 1000 default "" optional;
67 |     }
68 | } 
```

bin/formLang
```
1 | ELF          >    @#      @       �S         @ 8  @ ' &       @       @       @       �      �                                                                                        h      h                                           �_      �_                    �       �       �      /      /                   �      �      �      $      P                   �      �      �      �      �                   8      8      8      0       0                    h      h      h      D       D              S�td   8      8      8      0       0              P�td   ��      ��      ��                         Q�td                                                  R�td   �      �      �                         /lib64/ld-linux-x86-64.so.2               GNU   �          � �                   GNU �!��i�Z?F�.p�Qk6         GNU                                � �          (��e�mfUa9�                                                  �                      �                      4                      ;                      u                      $                      Q                                            �                      �                      �                      P                      B                      �                      �                      �                      m                      K                                            |                      �                      *                      �                      _                      4                      /                      X                      f      �             �   "                        0�             �     @�              stdin perror __stack_chk_fail free fread exit getc strdup ferror clearerr fopen strlen __ctype_b_loc stdout realloc isatty atoi malloc __libc_start_main stderr fprintf __cxa_finalize sprintf memset memcpy fileno fwrite strcmp __errno_location libc.so.6 GLIBC_2.3 GLIBC_2.14 GLIBC_2.4 GLIBC_2.34 GLIBC_2.2.5 _ITM_deregisterTMCloneTable __gmon_start__ _ITM_registerTMCloneTable                                          �          ii   �      ���        ii        ���        ui	   (      �              $      ��             �#       �             �      �             �      �             �      �             /�       �             4�      (�             <�      0�             B�      8�             G�      @�             M�      H�             V�      P�             ]�      X�             f�      `�             k�      h�             t�      p�             }�      x�             ��      ��             ��      ��             ��      ��             ��      ��             ��      ��             ��      ��             ��      ��             Ă      ��             Ȃ      ��             ̂      Ȼ             т      л             ւ      ػ             ނ      �             �      �             �      �             ��      ��             �       �             �      �              �      �             )�      �             ,�       �             2�      (�             5�      0�             8�      8�             <�      @�             @�      H�             C�      P�             G�      X�             K�      `�             N�      h�             R�      p�             V�      x�             Z�      ��             ^�      ��             f�      ��             k�      ��             o�      ��             y�      ��             ��      ��             ��      ��             ��      ��             ��      ȼ             ��      м             ��      ؼ             ǃ      �             у      �             �      �             �      ��             �      �             �      п                    ؿ                    �                    �                    �                     �                    0�                    @�                     �                    �                     �                    (�                    0�                    8�                    @�         	           H�         
2 |            P�                    X�                    `�                    h�                    p�                    x�                    ��                    ��                    ��                    ��                    ��                    ��                    ��                    ��                    ��                    ȿ                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            ��H��H�џ  H��t��H���     �5ڞ  �%ܞ  @ ��h    �����f���h   �����f���h   �����f���h   ����f���h   ����f���h   ����f���h   ����f���h   �r���f���h   �b���f���h	   �R���f���h
3 |    �B���f���h   �2���f���h   �"���f���h   ����f���h   ����f���h   �����f���h   �����f���h   �����f���h   �����f���h   ����f���h   ����f���h   ����f���h   ����f���h   �r���f����%6�  fD  ���%F�  fD  ���%>�  fD  ���%6�  fD  ���%.�  fD  ���%&�  fD  ���%�  fD  ���%�  fD  ���%�  fD  ���%�  fD  ���%��  fD  ���%��  fD  ���%�  fD  ���%�  fD  ���%ޜ  fD  ���%֜  fD  ���%Μ  fD  ���%Ɯ  fD  ���%��  fD  ���%��  fD  ���%��  fD  ���%��  fD  ���%��  fD  ���%��  fD  ���%��  fD  ��1�I��^H��H���PTE1�1�H�=�#  �k�  �f.�     H�=��  H���  H9�tH�N�  H��t	���    ��    H�=q�  H�5j�  H)�H��H��?H��H�H��tH��  H��t��fD  ��    ���=]�   u+UH�=��   H��tH�=�  �����d����5�  ]� ��    ���w�����UH��H�� H�}�    �M���H�E�H�}� u�    �=H�E�H������H��H�E�H�H�E�H�@    H�E��@    H�E�H�@    H�E�����UH��H�� H�}�   �����H�E�H�}� u�    �1H�E�H���D���H��H�E�H�H�E�H�@    H�E��@    H�E�����UH��H�� H�}�H�u�H�}� tH�}� u(H�$�  H���   �   H��Z  H��������   H�E�@��H�H��    H�E�H�@H��H���<���H�E�H�}� u-H�ʚ  H���&   �   H��Z  H���n����   �T���H�E�H�U�H�PH�E�H�PH�E�@H�H��H�H�E�H�H�E�@�PH�E�P����UH��H�� H�}��E�    �5H�v�  �U�Hc�H��H�H� H�U�H��H���'�����u�   ��E��J�  9E�|��    ����UH��H�}�H�}� tfH�E�� ����H�E��@����H�E��@����H�E��@����H�E��@����H�E��@����H�E�H�@    H�E�H�@     H�E��@(    ��]���UH��SH��HH�}�H�u��U�H�M�H�}� tH�}� tH�}� u(H�R�  H���   �   H�]Y  H��������\  �c�  ���Z�  �T�  H�H��H��H�<�  H��H���a���H�E�H�}� u-H��  H���)   �   H�Y  H�������   �y���H�E�H��  H��  ��  Hc�H��H��H�H�E�H���f���H�H���  ���  Hc�H��H��HB�  �BH�Eȋ@��Hc�H��H��H�H�H�H��H��H�E�H�@H��H������H�E�H�}� u-H�&�  H���$   �   H��X  H��������   ����H�E�H�U�H�PH�E�H�HH�Eȋ@Hc�H��H��H�H�H�H��H�H�E�H�E�H������H��H�E�H�H�E�U��PH�E�H��H������H�E��H�E�PH�E��PH�E�PH�E��PH�E�PH�E��PH�E�PH�E��PH�E�P H�E��PH�E�P$H�E��P(H�E�P8H�E�H�@H��tH�E�H�@H�������H��H�E�H�P(H�E�H�@ H��tH�E�H�@ H�������H��H�E�H�P0H�Eȋ@�PH�EȉPH�]�����UH��H��@H�}�H�}� ��  �E�    �  H�E�H�@�U�Hc�H��H�H� H�E�H�}� ��   �E�    �   H�E�H�H�E�Hc�H��H��H�H�H�H��H�H�E�H�E�H� H��tH�E�H� H������H�E�H�@(H��tH�E�H�@(H������H�E�H�@0H��tH�E�H�@0H���w����E�H�E��@9E��n���H�E�H�@H��tH�E�H�@H���F���H�E�H� H��tH�E�H� H���+���H�E�H�������E�H�Eȋ@9E������H�E�H�@H��tH�E�H�@H�������H�E�H� H��tH�E�H� H�������H�E�H�@H�E��XH�E�H�@H�E�H�E�H� H��tH�E�H� H������H�E�H�@H��tH�E�H�@H������H�E�H���u���H�E�H�E�H�}� u�H�E�H���Z����E�    �?H���  �U�Hc�H��H�H� H��tH�ޔ  �U�Hc�H��H�H� H�������E��Ĕ  9E�|�H���  H��tH���  H����������      �����UH��}��E�H�H��    H� �  H�]���UH��H�}�H�uЉU��E�    H�E�H� � ��H�H��W  ����E��}����   �}� y�E�����    �E��N   +E��E��E��0   9�OE��E�E��b�U�E��H�H��X  ���9E�uA�}�t;H�}� u�E��.�E�;E�u�    �K�E�P�U�H�H��    H�E�HE��E��E�;E�|�H�}� t�}� u�}� ~
4 | H�E�� �����E�]���UH��H�}�H�u�H�E�H�E�H�E�H�E���H�U�H�BH�E�H�E�H�HH�M���� ��u�H�E�H��]���UH��H�� H�}�H�u�H�E�� <"��   H�E�    H�E�H�E�H�E�H�E�� ����\t��\'��,ta��,��"t:��'u�PH�E�H�E�� <\uC�H�}� tH�U�H�E�H�H�E�� �H�E��H�}� tH�U�H�E�H��  H�E��2끐��H�}� tH�U�H�E�H��H�������H+E��H�E�H�����������UH��H��(H�}�H�u��U��E�    H�E�@���thH�}� t�E�H�H��    H�E�H�H�E�@��E��E܍P�H�}� t
5 | H�E�H���H�E�H�M�H��H���G����E��}��u������	�E�E��E�����UH��H��pH�}�H�u�H�U�dH�%(   H�E�1�H�E�    H�E�    H�M�H�E��   H��H�������E��}��u
6 | �������  �}�w$�E�H��    H�@X  �H�H�4X  H�>��H�(W  H�E��?H�(W  H�E��2H�9W  H�E��%H�\W  H�E��H�W  H�E��H��W  H�E�H�E�H���R���H�E��H�H)�H�BH�E��E�    �X�E�H��D��H�H��    H�
7 | �  H�H�ƿ    �X���H�U�H�H�E�H�E�H;E�
8 | H�E�H�E��
9 | �������   �E��E�;E�|�H�E�H� H9E�~7H�E�H� H�E�H�H�E�H� H9E�~H�E�H��������H�������   H�E�H� H�E��E�    �jH�E�� <%uUH�E�H��� <suF�E�;E�}>�E��P�U�H��D��H�H��    H�*�  H�H�E�H��H���v���HE�H�E��
10 | H�E�H�E�H�E��H�EЈH�E�� ���z����    H�U�dH+%(   t���������UH��H�}��u�H�U�H�}� uH�VV  H�E��]���UH��SH��   H�$ H��   H�$ H��   H�$ H���
11 |   dH�%(   H�E�1�ǅ���    ǅ ���    HǅP����   H�� ���H��X���H��X���H��`���H��@���H��h���H��h���H��p���ǅ,�������H������H��@���HǅH����   ǅ0���    �N�  �����H��`����������H��`����H��P���H�P�H��X���H�H9�`����3  H��`���H+�X���H��H������H��P���'  ��  HѥP���H��P���'  ~HǅP���'  H��X���H������H��P���H��H��H�H��H�H��GH������H������H������ �b  H������H������H��X���H��H��H���R���H������H��X���H��P���H��GH������H������H�9��8��8H��H��H��H��H��?H)�H��H��H�H��H�����H������H��H��H�H��H��H������H��h���H��H��H��H�������H������H��h���H��P���H��H��H�H��H��GH������H������H�9��8��8H��H��H��H��H��?H)�H��H��H�H��H�����H�� ���H9�����tH������H������H������H�P�H��X���H�H��`���H������H��H��H�H��H�P�H��h���H�H��p���H��P���H�P�H��X���H�H9�`�����  �������  ������H�H�eO  �����$�����$������  ���  ���u�  ���  ���  ���}�      ǅ,���    �`�k�  =   u�Z�    ǅ,���   �  �E�  ��x%�;�  =*  �.�  H�H��K  �����   ��,�����,����$�����$��� ��   ��$���M��   ��$���H�H��O  ���9�,�����   ��$���H�H�>O  �����$�����$��� ��$�����   �� ��� t�� �����$��������H��p���HH��p���H�k�  H�l�  H�H�XH�f�  H�g�  H�HH�XH�`�  H�a�  H�H H�X(H�Z�  H�[�  H�H0H�X8H�T�  H�P@��  ����������������H�H��M  �����$�����$��� ��
12 |   ���$���H�H��O  �����0����   +�0���Hc�H��H��H�H��H��H��p���H�H�H�XH������H������H�HH�XH�� ���H�����H�H H�X(H�����H�����H�H0H�X8H�� ���H��(���H�@@H��0�����$���4��  ��$���H��    H��Q  �H�H��Q  H�>��H��p���H� H������H���  H���  H���d  H��O  H���	  �  H�T�  H���1F  H���  H�������2  H�v�      �"  H�f�      �  H��O  H���  H�G�      �Q�  ����ǅ ���    ��  H�'�  H��tH��O  H���t  �  H��p���H� H���(���H���  H��  H��uH��O  H���;  ��
13 |   H�·  H���  H��H���G����h  H�iO  H���	  ���  ����ǅ ���    �@  H���  H��uH�TO  H����  �q
14 |   H��p���H-   H� H���������tH�CO  H���  �A
15 |   H��p���H��HH��H��p���H-�   �H��p���H-   H�0H��  H���Q���H��p���H-   H� H���C����  ǅ����    �  ǅ����   �y  ǅ����   �j  ǅ����   �[  ǅ����   �L  ǅ����   �=  ǅ����   �.  ǅ����   �  ǅ����   �  ǅ����	   �  ǅ����
16 |    ��  ǅ����   ��  H������H���������  H��p����@(���tH��p����@(�����H��p���� ���tH��p���� ������H��p����@���tH��p����@������H��p����@���tH��p����@������H��p����@���tH��p����@������H��p����@���tH��p����@�� ���H��p����@���tH��p����@�����H��p���H�@H��t-H�����H��tH�����H���t���H��p���H�@H�����H��p���H�@ H����  H�����H��tH�����H���3���H��p���H�@ H������t  H������H������ǅ���   �W  H������H���i���ǅ���    �9  H������H���K���H��p���H� H������  H������H���&���H��p���H� H�������  H������H������H��p����H������H�*L  H��H�Ǹ    ����H������H������H������  H������H������H��p���� �������{  H������H������H��p���� �������X  H������H���j���H��p���� �������5  H������H���G���H��p���� �������  H������H���$���H��p���� �� �����  H������H������H��p���� �������  H������H�������H��p���H� H�� ����  H������H������H��p���� ��(����  �   �����H������H��p���H-h  H�H������H�H��p���H-�   H�H������H�PH�~�  H�PH������H�PH�h�  H������H�P�  �2   �~���H������H��p����H��p���H-�   H�H������H�5=J  H�Ǹ    ����H������H�������  �2   �&���H������H��p����H��p���H-�   H�H������H�5�I  H�Ǹ    �;���H������H�������a  �2   �����H������H��p����H��p���H-�   H�H������H�5�I  H�Ǹ    �����H������H�������	  �2   �v���H������H��p����H��p���H-�   H�H������H�5NI  H�Ǹ    ����H������H�������   �2   ����H������H��p����H��p���H-�   H�H������H�5�H  H�Ǹ    �3���H������H�������\�2   �����H������H��p����H��p���H-�   H�H������H�5�H  H�Ǹ    �����H������H��������������0���Hc�H��H��H�H��H��H�p�����0���H�H��H�`���ǅ0���    H��p���HH��p���H������H������H�H�XH�� ���H�����H�HH�XH�����H�����H�H H�X(H�� ���H��(���H�H0H�X8H��0���H�P@��$���H�H�JE  �����0��8�����8���H�H��C  ���H��`���� ��Љ�<�����<��� xB��<���M9��<���H�H�.D  �H��`���� 8�u��<���H�H��C  ������8���H�H��C  ���������������~  ���t6��~  ��x%��~  =*  ��~  H�H�1?  �����   ��������,����� ��� �?  ��~  ����~  H��`���H��������,���������H��D  H��x���H������H��@���H��H���H��H��������4�����4��� uH��@���H��x����   ��4������   H��@���H������H9�tH��@���H���A���H��H���H������H��@���H��@���H��t6H������H��@���H��H���H��H��������4���H��@���H��x����#H������H��@���HǅH����   ǅ4�������H��x���H����  ��4�����J  �� �����   �S}  ���I}  ����   �  ��,���H�3}  ��H�[E  H��������}  �����a�X}  ���O}  ��0���Hc�H��H��H�H��H��H�p�����0���H�H��H�`���ǅ0���    H��`���� ���������ǅ ���   �����H�H�;@  �����$�����$����tU��$�����$��� xE��$���M<��$���H�H�=A  �<u%��$���H�H��@  �����$�����$��� jH��`���H;�X�����   �����H�H�MA  ���H��p�����H�9D  H������H��p���HH��`���H��`���� ������������H��p���HH��p���H��{  H��{  H�H�XH��{  H��{  H�HH�XH��{  H��{  H�H H�X(H��{  H��{  H�H0H�X8H��{  H�P@��$��������������ǅ(���    �1���ǅ(���   �!�����H�jC  H���Y  ǅ(���   ���z  ���tX��z  ��x%��z  =*  ��z  H�H�4;  �����   ��,�����,���H��z  ��H�C  H���W�����0���Hc�H��H��H�H��H��H�p�����0���H�H��H�`����EH��`���� ��H�H��?  ���H��p�����H��B  H�������H��p���HH��`���H��`���H;�X���u�H�� ���H9�X���tH��X���H���9���H��@���H������H9�tH��@���H��������(���H�U�dH+%(   t�]���H�]�����UH��H��H�}��1y  H�Zy  H�U�H�5�B  H�Ǹ    �R��������UH��H�� �}�H�u��}�~MH�E�H��H� H��B  H��H���y���H�E�H�}� uH�E�H��H� H���k����   �$H�E�H�qy  �����H��x  H��������    ����UH��   ]���UH��H��H�}��ix  H��x  H�M�H�5�L  H�Ǹ    ���������UH��H�� H�}�H�E�H���+���H��H������H�E��E�    �E�    �5  �E�Hc�H�E�H�� <\��   �E��E�Hc�H�E�H�� ����ttL��t��   ��rtY��r��   ��nt��n��   ��"tm��\tP�~�E�P�U�Hc�H�E�H�� 
17 | �   �E�P�U�Hc�H�E�H�� 	�   �E�P�U�Hc�H�E�H�� �~�E�P�U�Hc�H�E�H�� \�f�E�P�U�Hc�H�E�H�� "�N�E�Hc�H�E�H��E�P�U�Hc�H�E�H����&�E�Hc�H�E�H��E�P�U�Hc�H�E�H����E��E�Hc�H�E�H�� ��������E�Hc�H�E�H��  H�E�����UH��SH��8��w  ����   ��w     ��w  ��u
18 | ��w     H�-w  H��uH�yv  H�w  H�w  H��uH�Ov  H�w  H�1w  H��tH�%w  H�w  H��H�H� H��u2�0  H��v  H��v  H��v  H��H�
19 | � @  H���  H���  H��v  H�E���v  H�E��H�E�H�E��v  �E�H�E�� ��H�H�,A  ��EˋE�H�H� H��?  �f��tK�Ẻ�v  H�E�H��v  �5�E�H�H� H��C  ���É}̽   ~�E�H�H��A  ��EˋE�H�H� H��A  ����E��H�H� H��F  ��9E�u��E�H�H� H��A  ����E��H�H� H��D  ���E�H�E��E�H�H� H��A  �f=� �������E�H�H� H��>  ���EЃ}� u,H��u  H�E���u  �E̋E�H�H� H�u>  ���E�H�E�H�2u  H�E�H+E�u  H�E�� �?u  H�E��  H�E�H�5u  �}�1u��Z�E�H�H��    H��G  ���t��E�    �)H��t  �E�H�H�� <
20 | u��s  ����s  �E���t  9E�|�룃}�2�z  �E�H��    H��H  �H�H��H  H�>����t  H�E��H��t  H�E���t  �E�������  �A  �  �7  �  �-  �   �#  �!  �  �"  �  �t     �:   ��  ��s      �;   ��  �{   ��  �}   ��  �#  ��  �$  �  �%  �  �&  �  �'  �  �(  �  �)  �  �*  �  ��s  ��t�zs      �  �e  H�as  H���y���H��r  �  �E  �Js  ��t�<s      �  �'  H�#s  H���;���H��r  �  �  �s  ��t��r      �  ��  H��r  H�������H�fr  �  ��  ��r  ��t��r      �  �  H��r  H������H�(r  �  �  ��r  ��t��r      �	  �m  H�ir  H������H��q  �  �M  �Rr  ��t�Dr      �
21 |   �/  H�+r  H���C���H��q  �  �  �r  ��t�r      �  ��  H��q  H������H�nq  �  ��  ��q  ��t��q      �  �  H��q  H�������H�0q  �  �  ��q  ��t��q      �  �u  H�qq  H������H��p  �  �U  �Zq  ��t�Lq      �  �7  H�3q  H���K���H��p  �  �  �  �  �  �  �  ��  �  ��  �  ��  �  ��  �  ��  �  ��  �  �  �  �  ��p  ��t��p      �  �  H��p  H������H�p  �  �u  �  �k  �  �a  �fp  ��t�Xp      �  �C  H�?p  H���W���H��o  �  �#  H�p  H���7���H��o  �  �  H��o  H���������o  �  ��  H��o  H��o  H�������H��H��  H��o  H��H������H�=o  �  �  H�mC  H���5���H��o  � ���  H�ko  �Uo  Hc�H�ko  H�Ѻ   H���k����N  �    �I  H�Eo  H�U�H)Ѓ��E��Wo  H�E��H�Bo  H�+o  H��H�H� �@8��ubH�#o  H�o  H��H�H� �@�o  H�o  H��n  H��H�H� H��n  H�H��n  H��n  H��H�H� �@8   H��n  H��n  H��H�H� H�P��n  H�H�H��n  H9�rtH�nn  �E�H�H�H��n  �  �E̋Ẻ���  �E�H�Cn  H�E�}� t(H�bn  H��H�Wn  H�Pn  H�E��E܉E�����H�:n  H�E��z�����   ����   ����   ��t>����   �n      H��m  H��m  ��m  �����������2�E�����H��m  �E�H�H�H��m  ��  �E�H��m  H�E�H�xm  H�E������H��m  H�qm  H��H�H� H�P�ym  H�H�H�qm  �  �E�H�bm  H�E�H�'m  H�E�����H��@  H���  ��Q�����K���H�]�����UH��SH��HH�	m  H��l  H��H�H� H�@H�E�H��l  H�E�H��l  H��l  H��H�H� H�@��l  Hc�H��H�H��l  H9�sH�nA  H���  H��l  H��l  H��H�H� �@4��u+H��l  H�Ql  H)�H��u
22 | �   �  �   �  H�]l  H�&l  H)Ѓ��E��E�    �!H�U�H�BH�E�H�E�H�HH�M����E��E�;E�|�H�l  H��k  H��H�H� �@8��u0��k      H��k  H��k  H��H�H� ��k  �P�#  H��k  H��k  H��H�H� �@+Eȃ��E��  H��k  H�rk  H��H�H� H�E�H�}k  H�E�H�@H)U�H�E�@ ��tqH�E�@��EЃ}� $H�E�PH�E�@�H��H����H�E�P�H�E�@� H�E�PH�E�@��Hc�H�E�H�@H��H���  H�U�H�B�H�E�H�@    H�E�H�@H��uH��?  H���+  H�E�H�P�E�H�H�H��j  H��j  H��j  H��H�H� �@+Eȃ��E��}� ������}�    ~�E�    H�_j  H�Hj  H��H�H� �@$����   �E�*   �E�    �7H�,j  H�j  H��H�H� H�@�U�HcʋU�Hc�H�HЋU���E��E�;E�}H��i  H��������E��}��t�}�
23 | u��}�
24 | u8H��i  H��i  H��H�H� H�H�E�Hc��EčP�U�H�H�HȋU���}��u"H�Si  H���S�����tH��>  H����  �Eĉsi  �   �����     �5����� ��tH�n>  H���  ������     H��h  H���p���H��h  �E�H�H�i  H�5�h  H��H�H�	H�q�M�Hc�H�<H��H�¾   �������h  ��h  ��uH��h  H���������b���H��h  H��h  H��H�H� ��h  �P��h  ��uF�}� u�E�   H�@h  H����  �/�E�   H�`h  H�Ih  H��H�H� �@8   ��E�    �Eh  �EȍH�,h  H�h  H��H�H� �@9���   �h  �E�h  ��ЉEԋE�Hc�H��g  H��g  H��H�H� H�@H��g  H�5�g  H��H�H�H��H���^  H�CH��g  H��g  H��H�H� H�@H��uH��<  H����  H�xg  H�ag  H��H�H� �Uԃ��P�dg  �E�ЉYg  H�Fg  H�/g  H��H�H� H�P�7g  H�H��  H�g  H�g  H��H�H� H�@�g  Hc�H��H��  H��f  H��f  H��H�H� H�@H��f  �E�H�]�����UH���f  �E�H��f  H�E���   H�E�� ��tH�E�� ��H�H�1  ���   �E�E�H�H� H�{/  �f��tK�E�}f  H�E�H�vf  �5�E�H�H� H��3  ���E�}��   ~�E�H�H��1  ��E�E�H�H� H��1  ����E��H�H� H��6  ��9E�u��E�H�H� H��1  ����E��H�H� H��4  ���E�H�E�H��e  H9E�������E�]���UH��}�H��e  H�E��E��E�H�H� H�|.  �f��tK�E�~e  H�E�H�we  �5�E�H�H� H��2  ���E�}�   ~�E�H�H��0  ��E�E�H�H� H��0  ����E��H�H� H��5  ��9E�u��E�H�H� H��0  ����E��H�H� H��3  ���E�}�   �����E�}� u�E���    ]���UH��SH��H�}�H�xd  H��tH�ld  H�Ud  H��H�H� H��u2�w  H�d  H�Cd  H�,d  H��H�
25 | � @  H����  H�H�d  H��tH�d  H��c  H��H�H� ��    H�U�H��H���  ��   �H�]�����UH��H��H�}���  H��c  H��tH��c  H��c  H��H�H� ��    H;E���   H��c  H��tqH��c  H�jc  H��H�H� H��tTH�tc  �ec  �H�Tc  H�=c  H��H�H� H�Lc  H�PH�1c  H�c  H��H�H� �&c  �PH�c  H��b  H��H�H�E�H��   �c     ������UH��H��b  H��b  H��H�H� �@��b  H��b  H��b  H��H�H� H�@H��b  H��b  H�mb  H��b  H�ob  H��H�H� H� H�3b  H�tb  � �cb  �]���UH��H�� H�}�u�@   ��	  H�E�H�}� uH��7  H���  H�E��U�PH�E��@��H�H���	  H�U�H�BH�E�H�@H��uH�g7  H���O  H�E��@    H�U�H�E�H��H���   H�E�����UH��H��H�}�H�}� tvH��a  H��tH��a  H�za  H��H�H� ��    H;E�uH�la  H�Ua  H��H�H�     H�E��@ ��tH�E�H�@H���	  H�E�H���	  ������UH��H�� H�}�H�u������� �E�H�E�H���   H�E�H�U�H�H�E��@4   H��`  H��tH��`  H��`  H��H�H� ��    H;E�tH�E��@,   H�E��@0    H�}� tH�E�H���������j�����~�   ��    H�E�P$�.����U�������UH��H��H�}�H�}� ��   H�E��@    H�E�H�@�  H�E�H�@H���  H�E�H�PH�E�H�PH�E��@(   H�E��@8    H��_  H��tH��_  H��_  H��H�H� ��    H;E�u�����������UH��H��H�}�H�}� ��   ��  H��_  H��tqH��_  H�{_  H��H�H� H��tTH��_  �v_  �H�e_  H�N_  H��H�H� H�]_  H�PH�B_  H�+_  H��H�H� �7_  �PH�!_  H��t/H�_  H��^  H��H�H� H��tH��^  H��H��^  H��^  H��^  H��H�H�E�H��������^     ������UH��H��^  H����   H��^  H��^  H��H�H� H����   H�}^  H��tH�q^  H�Z^  H��H�H� ��    H������H�J^  H�3^  H��H�H�     H�^  H��tH�^  H��H�^  H�^  H��t/H�^  H��]  H��H�H� H��t������]     ��]���UH��H��H��]  H��uuH�E�   H�E�H��H���7  H��]  H��]  H��uH�@3  H����  H�E�H��    H�u]  �    H��舾��H�E�H�U]  H�B]      �   H�>]  H��H�+]  H9���   H�E�   H�]  H�E�H�H�E�H�E�H��    H�]  H��H���  H��\  H��\  H��uH��2  H���H  H�E�H��    H��\  H��\  H��HȾ    H���ʽ��H�E�H��\  ����UH��H�� H�}�H�u�H�}�v,H�E�H�P�H�E�H�� ��uH�E�H�P�H�E�H�� ��t
26 | �    �   �@   ��  H�E�H�}� uH�2  H���  H�E�����H�E��PH�E�H�U�H�PH�E�H�PH�E�H�PH�E��@     H�E�H�     H�E��PH�E��PH�E��@$    H�E��@(   H�E��@4    H�E��@8    H�E�H�������H�E�����UH��H��H�}�H�E�H���~�����H�E���H���   ����UH��H��0H�}؉uԋEԃ�H�H�E�H�E�H����  H�E�H�}� uH�G1  H���   �E�    �#�E�Hc�H�E�HЋU�Hc�H�U�H�� ��E��E�;E�|ՋE�H�H�PH�E�H��  �U�Hc�H�U�H�� �H�U�H�E�H��H������H�E�H�}� uH��0  H���   H�E��@    H�E�����UH��H��H�}�H��Y  H�U�H��0  H��H�Ǹ    螻���   �4�����UH��FY  ]���UH��H��Y  ]���UH��H��Y  ]���UH���Y  ]���UH��H��Y  ]���UH��}��E���X  �]���UH��H�}�H�E�H��Y  �]���UH��H�}�H�E�H��Y  �]���UH���Y  ]���UH��}��E��jY  �]���UH���}X     H�rY      H�WY      H�TY      H�aY      �_Y      �YY      H��X      H��X      �    ]���UH���TH�Y  H��tH�Y  H��X  H��H�H� ��    H���(���H��X  H��X  H��H�H�     ����H��X  H��tH��X  H��X  H��H�H� H��u�H��X  H���^   H�X      ������    ]���UH��H��H�}�H�E�H���׹������UH��H��H�}�H�u�H�U�H�E�H��H��边������UH��H��H�}�H�E�H������������UH��H��H�}�H�E�H���   �   H�M.  H���͹��H�E�H���   �   H�L.  H��譹��H�E�H���Z   �   H�5.  H��荹��H�E�H���A   �   H�u.  H���m���H�E�H���W   �   H��.  H���M���H�E�H���#   �   H��.  H���-���H�E�H���.   �   H��.  H������H�E�H��.  H��H�Ǹ    �B���H�E�H���z   �   H�R/  H���Ҹ��H�E�H���2   �   H��/  H��貸��H�E�H���&   �   H��/  H��蒸��H�E�H���:   �   H��/  H���r���H�E�H���   �   H��/  H���R��������UH��H��H�}�H�E�H���   �   H��/  H�����������UH��H�� H�}�H�}� uH��/  H�������A  H�E�H�������H�H��H���f���H�E��E�    �E�    ��   �E�Hc�H�E�H�� ����>��   ��>��   ��<tU��<��   ��"t'��&u|�E�Hc�H�E�H�� &ampf�@; �E��   �E�Hc�H�E�H�� &quo�@ot; �E��`�E�Hc�H�E�H�� &lt;�@ �E��C�E�Hc�H�E�H�� &gt;�@ �E��&�E�Hc�H�E�H��E��P�U�Hc�H�E�H����E��E�Hc�H�E�H�� �������E�Hc�H�E�H��  H�E�����UH��H��@H�}�H�u�H��S  H���   �   H�=.  H���w���H�}� tH�}� u(H��S  H���   �   H�).  H���F�����	  H�E��@����	  H�E�H���
27 |    �   H�.  H������H�E�H�H�E�H��-  H��H�Ǹ    �@���H�E��PH�"S  H��-  H��H�Ǹ    �����E�    ��  H��R  �U�H��-  H��H�Ǹ    ����H�E�H�H�E�Hc�H��H��H�H�H�H��H�H�E�H�E�H� H���J���H�E�H�E��@8��t	H��-  �H�-  H�M�H�U�H�}�I��H�j-  H�Ƹ    �t���H�E�H���س��H�h-  H�E�H�E��@����   ��H��    H�P2  �H�H�D2  H�>��H�*-  H�E��   H�-  H�E��   H�-  H�E��tH�-  H�E��gH�-  H�E��ZH�-  H�E��MH��,  H�E��@H��,  H�E��3H��,  H�E��&H��,  H�E��H��,  H�E��H��,  H�EؐH�E��@����   H�E�H�H�E�H�H�E�H�5�,  H�Ǹ    �S���H�E��@ ��~"H�E��P H�E�H��,  H��H�Ǹ    �&���H�E��@$��~"H�E��P$H�E�H�{,  H��H�Ǹ    �����H�E��@8��t H�E�H���	   �   H�S,  H���~���H�E�H���   �   H�=,  H���^����h  H�E��@���  H�E�H�H�E�H�H�E�H�5,  H�Ǹ    �s���H�E��@8��t H�E�H���	   �   H��+  H�������H�E�H���   �   H��+  H���ز��H�E��@8��u H�E�H���-   �   H��+  H��譲��H�E�H���,   �   H��+  H��荲��H�E�H���,   �   H��+  H���m���H�E�H���
28 |    �   H��+  H���M����W  H�E��@���g  H�E�H���   �   H��+  H������H�E�H�H�E�H�H�E�H�5�+  H�Ǹ    �B���H�E��@8��t H�E�H���	   �   H��*  H���Ǳ��H�E�H���   �   H��*  H��觱��H�E�H���   �   H��+  H��臱��H�E�H�H�E�H�H�E�H�5�+  H�Ǹ    豰��H�E��@8��t H�E�H���	   �   H�*  H���6���H�E�H���   �   H�*  H������H�E�H���   �   H�P+  H�������H�E�H���   �   H�I+  H���ְ����  H�E��@���  H�E�H���   �   H�+  H��衰��H�E�H�H�E�H�H�E�H�5+  H�Ǹ    �˯��H�E�H�H�E�H�H�E�H�5J+  H�Ǹ    襯��H�E�H�H�E�H�H�E�H�5t+  H�Ǹ    ����H�E�H�H�E�H�H�E�H�5�+  H�Ǹ    �Y���H�E�H�H�E�H�H�E�H�5�+  H�Ǹ    �3���H�E�H���   �   H�6*  H���ï����  H�E�H�0H�E�H�H�U�H�E�I��H�5�+  H�Ǹ    ����H�E��@8��t H�E�H���	   �   H�;(  H���f���H�E��@��~"H�E��PH�E�H��+  H��H�Ǹ    艮��H�E��@��~"H�E��PH�E�H�+  H��H�Ǹ    �\���H�E��@��u\H�E��@���t"H�E��PH�E�H�U+  H��H�Ǹ    �"���H�E��@���t"H�E��PH�E�H�1+  H��H�Ǹ    �����H�E�H�@(H��t?H�E�H�@(H���k���H�E�H�U�H�E�H��*  H��H�Ǹ    购��H�E�H������H�E�H�@0H��t?H�E�H�@0H������H�E�H�U�H�E�H��*  H��H�Ǹ    �h���H�E�H���̬��H�E��@��	u H�E�H���   �   H��*  H������H�E��@��u-H�E�H�@0H��t H�E�H���   �   H�^*  H��觭��H�E�H�@@H��t#H�E�H�P@H�E�H�?*  H��H�Ǹ    �Ǭ��H�E��@H��~"H�E��PHH�E�H�%*  H��H�Ǹ    蚬��H�E�H���   �   H�1&  H���*���H�E��@��u-H�E��@H��~"H�E�H�H�E�H��)  H��H�Ǹ    �A���H�*J  �U�H��)  H��H�Ǹ    � ����E�H�E��@9E������H�E�H���   �   H��)  H��蜬��H��I  H���   �   H��)  H���y���������UH��H��@H�}�H�u�H�U�H�M�H�E�H�E��H�E�H�E�� ��t(�i���H�H�E�� H��H�H�� ��%    ��u��E�    �$H�E�H�PH�U��U�J�M�Hc�H�U�H�� �H�E�� ��tX�	���H�H�E�� H��H�H�� ��%    ��u0H�E�� <<t%H�E�� <>tH�E�� <=tH�E�� <!�y����E�Hc�H�E�H��  �H�E�H�E�� ��t(菫��H�H�E�� H��H�H�� ��%    ��u��E�    H�E�� <<t!H�E�� <>tH�E�� <=tH�E�� <!umH�E�H�PH�U��U��J�M�Hc�H�U�H�� �H�E�� <=tH�E�H��� <<u/H�E�� <>u$H�E�H�PH�U��U��J�M�Hc�H�U�H�� ��E�Hc�H�E�H��  �H�E�H�E�� ��t(襪��H�H�E�� H��H�H�� ��%    ��u��E�    �$H�E�H�PH�U��U�J�M�Hc�H�U�H�� �H�E�� ��uыE�Hc�H�E�H��  �����UH��H��   H��X���H��P���dH�%(   H�E�1�H��X���H���	   �   H�T'  H��踩��H��X���H���;   �   H�='  H��蕩��H��X���H���/   �   H�Z'  H���r���H��X���H���2   �   H�g'  H���O���H��X���H���    �   H�|'  H���,���H��X���H���(   �   H��'  H���	���H��X���H���1   �   H��'  H������H��X���H���0   �   H��'  H���è��H��X���H���   �   H��'  H��蠨��H��X���H���   �   H��'  H���}���H��X���H���   �   H��'  H���Z���H��P���H�@H��`�����  H��`���H� H�M�H��l���H��p���H������H��X���H���   �   H�V'  H�������H��p���H��p���H��X���H�5@'  H�Ǹ    �#���H��p���H��p���H��p���H��X���I��H�5='  H�Ǹ    ����H��p���H��p���H��X���H�5<'  H�Ǹ    �Ǧ��H��p���H��X���H�B'  H��H�Ǹ    袦��H��X���H���   �   H�H'  H���/���H�u�H��l���H��p���H��X���I��H�5<'  H�Ǹ    �O���H��`���H�PH��X���H�C'  H��H�Ǹ    �&���H��X���H���   �   H��&  H��賦��H��X���H���   �   H�'  H��萦��H��X���H���   �   H��&  H���m���H��`���H�@H��`���H��`��� �
29 | ���H��X���H���   �   H��&  H���*���H��X���H���0   �   H��&  H������H��X���H���   �   H��&  H������H��X���H���   �   H��&  H�������H��X���H���   �   H��&  H��螥��H��X���H���   �   H�&  H���{���H��X���H���   �   H�v&  H���X���H��X���H���   �   H�Z&  H���5���H��X���H���
30 |    �   H�<&  H�������H�E�dH+%(   t��������UH��H�� H�}�H�$B  H���   �   H��%  H���Ȥ��H�!B  H��tH�}� u(H��A  H���   �   H��%  H��蒤���c  H��A  H���   �   H��%  H���j���H�E�H���a���H�E�H���   �   H��%  H���>���H��A  �PH�mA  H��%  H��H�Ǹ    �f����E�    �OH�FA  �U�H��%  H��H�Ǹ    �<���H�EA  H�@�U�Hc�H��H�H�H�E�H��H�������E�H�A  �@9E�|�H�E�H���%   �   H�?%  H��菣��H�E�H���   �   H�E%  H���o���H�E�H������H��@  H�E�H��H���F���H��@  H���   �   H�	%  H���*�������H��H���                                                         Null form or section
31 |    Memory allocation failed for sections
32 |  Null section, name, or attrs
33 |     Memory allocation failed for field names
34 |        Memory allocation failed for fields
35 |              /.,-	
36 |  !"#$%&'()*+"end of file" error "invalid token" FORM SECTION FIELD TEXT EMAIL PASSWORD NUMBER TEXTAREA DATE CHECKBOX DROPDOWN RADIO FILE_TYPE USERNAME ADDRESS REQUIRED OPTIONAL MINLENGTH MAXLENGTH MIN MAX ROWS COLS PATTERN DEFAULT CONFIRM STRENGTH IDENTIFIER NUMBER_LITERAL STRING_LITERAL VALIDATE IF ERROR LT GT LTE GTE EQ NEQ AND OR '{' '}' ';' ':' $accept form $@1 form_body form_item section section_header field_list field field_type field_attributes attribute validation_block validation_rules validation_rule condition                    &�+�������������������
37 | ������� ����������������"$%'()* -.��������������             ,  
38 | 	  +-             /01234              .#$%&'( "!)*     ���������������� =?NABCDEFGHIJKL123456789:;<	WXM"#$%&'
39 | ! ()*+,-./@O>P0QR STU VY Z                  	
40 | "! .$%&'()-- -,,,--.,/.- #�� �                   1 2,3!-456<,,=--7"->-8?.$%&'(),/#	
41 | 9 :..;-        021334455567778999999999999::;;;;;;;;;;;;;<==>??????                 syntax error syntax error, unexpected %s   syntax error, unexpected %s, expecting %s       syntax error, unexpected %s, expecting %s or %s syntax error, unexpected %s, expecting %s or %s or %s   syntax error, unexpected %s, expecting %s or %s or %s or %s ҧ��ߧ���������������Deleting Failed to create form Invalid section declaration  Nested sections are not allowed Failed to create section Invalid field declaration      Field must be inside a section Duplicate field name found %d %s < %d %s > %d %s <= %d %s >= %d %s == %d %s != %d Error: discarding Error: popping memory exhausted Cleanup: discarding lookahead Cleanup: popping   ��������t�����������������������Ӯ��������&���������������ů��n���}�������������������Ȱ��װ���������������"���6�����������̲��������g�����������г��������9���^�����������������������L�����������T�������Parser Error: %s at line %d
42 |  r                                1 /   / / / -  	  /  , , , , , , , , , , , , , , , , 
43 |  /     .    -    , , , , , , , , , , ,  , , , , , , , , , , , , ,  , , , , , , , , , , , , # " , , , , , , , , , , , , , , % ,  , , , , ,   , , , , , , , , $ , ,  , , , , , , ,    , , , , , ,  , , , , , , , , , , , , ,  , , , , , , , , , + , ) ' , , , , , & ,  , , , ,   , ,    *  (  !          	
44 |  !"#$%&'()                             � � � � � % � � � � � � �   �     �  � � � % " � � � � � � � 6 � � � � � � �   � �  � � � � � ) �   � � � �  � � � � � � � � � � � � � � �  � ~ � � } � � � | r p y m n l y j k r u o   o   c r j c o     m l k a X h ^ b   a \ g Z b S b R W S       S R M P N J   I K Q F U T B E F > : H G   L ; > E < 5 B : 2   -     6 / . 5 ;   :   5 ; 6 5     1 *                   � E >   �  � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � �   � �        	 
45 |                                   ! " % . 0 3 5 8 1 / 4 6 & = @ 9 H > I % 2 O V W , � ? P A & $ $ � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � �  ~ } | { z y x w v u t s r q p o n m l k j i h g f e d c b a ` _ ^ ] \ [ Z Y X U T S R Q N M L K J G F ( � E D C B < ; : 7 - + * ) ( ' # �  � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � �                                                                                  /  / $  5 < < � �  5  $ � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � ~ } | { z y x w v u s r q p o n m l i h g f e c a ` _ ^ ] \ [ Z Y X W V U T S R Q P O N M L K J I H G F D C B A @ ? > = ; : 9 8 6 4 3 2 1 0 . - ( & !            
46 |  	   � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � �                                                                                                                                                                                                                           Syntax error at line %d: %s
47 |  Unexpected character   fatal flex scanner internal error--no action found  p���վ����������������������ȷ��ҷ������������������"���,���6���@���J���T���^�������ڸ�����V�������ҹ�����N�������ʺ��Ժ��޺���������������������$���.���l���v�����������޻������A���b�����������fatal flex scanner internal error--end of buffer missed fatal error - scanner input buffer overflow input in flex scanner failed        out of dynamic memory in yy_get_next_buffer()   out of dynamic memory in yy_create_buffer()     out of dynamic memory in yyensure_buffer_stack()        out of dynamic memory in yy_scan_buffer()       out of dynamic memory in yy_scan_bytes() bad buffer in yy_scan_bytes() %s
48 |       <!DOCTYPE html>
49 | <html>
50 | <head>
51 |  <style>
52 |  body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }
53 |       form { background: #f5f5f5; padding: 20px; border-radius: 5px; }
54 |        section { margin-bottom: 20px; padding: 15px; background: white; border-radius: 5px; }
55 |  h2 { color: #333; margin-top: 0; }
56 |      label { display: block; margin-bottom: 5px; }
57 |   input, textarea, select { width: 100%%; padding: 8px; margin-bottom: 10px; border: 1px solid #ddd; border-radius: 4px; }
58 |        input[type=submit] { background: #4CAF50; color: white; border: none; padding: 10px 20px; cursor: pointer; width: auto; }
59 |       input[type=submit]:hover { background: #45a049; }
60 |       .radio-group { margin-bottom: 10px; }
61 |   .radio-group label { display: inline; margin-left: 5px; }
62 |  </style>
63 | </head>
64 | <body>
65 |  </body>
66 | </html>
67 |   Starting section generation
68 |  Null section or output
69 |  <section>
70 |  <h2>%s</h2>
71 |  Processing %d fields
72 |  Generating field %d
73 |   * <label for="%s">%s%s</label>
74 |  text email password number textarea date checkbox select radio file <textarea id="%s" name="%s"  rows="%d"  cols="%d"  required ></textarea>
75 |  <select id="%s" name="%s" >
76 |          <option value="">Select an option</option>
77 |      <option value="option1">Option 1</option>
78 |       <option value="option2">Option 2</option>
79 |  </select>
80 |  <div class="radio-group">
81 |         <input type="radio" id="%s_1" name="%s" value="option1"   <span>Option 1</span><br>
82 |     <input type="radio" id="%s_2" name="%s" value="option2"   <span>Option 2</span>
83 |  </div>
84 |  <div class="address-group">
85 |  <input type="text" id="%s_street" name="%s_street" placeholder="Street" required>
86 |       <input type="text" id="%s_city" name="%s_city" placeholder="City" required>
87 |     <input type="text" id="%s_state" name="%s_state" placeholder="State" required>
88 |  <input type="text" id="%s_zip" name="%s_zip" placeholder="ZIP" required>
89 |        <input type="text" id="%s_country" name="%s_country" placeholder="Country" required>
90 |    <input type="%s" id="%s" name="%s"  minlength="%d"  maxlength="%d"  min="%d"  max="%d"  pattern="%s"  value="%s"  accept="*/*"  checked  data-confirm="%s"  data-strength="%d"  <meter id="%s_strength" min="0" max="4"></meter>
91 |        Field %d generated successfully
92 |  </section>
93 |  Section generation complete
94 |    ��������������������	������#���0���=���J���W���<script>
95 |    document.addEventListener('DOMContentLoaded', function() {
96 |        const form = document.querySelector('form');
97 |    const errorDiv = document.createElement('div');
98 |         errorDiv.style.color = 'red';
99 |           errorDiv.style.marginBottom = '10px';
100 |           form.insertBefore(errorDiv, form.firstChild);
101 | 
102 |          form.addEventListener('submit', function(e) {
103 |      e.preventDefault();
104 |      let valid = true;
105 |      const errors = [];
106 | 
107 |      {
108 |               var %s = document.getElementById('%s');
109 |         var %sVal = %s ? %s.value : '';
110 |         if (!%s || %sVal === '') {
111 |                errors.push("Field '%s' is required.");
112 |          valid = false;
113 |               } else if (parseFloat(%sVal) %s %s) {
114 |          errors.push("%s");
115 |        }
116 |      }
117 |      if (!valid) {
118 |            errorDiv.innerHTML = errors.join('<br>');
119 |      } else {
120 |         errorDiv.innerHTML = '';
121 |        form.submit();
122 |    });
123 |  });
124 |  </script>
125 |  Starting HTML generation
126 |  Null form or output
127 |  Generating header
128 |  <form>
129 |  Processing %d sections
130 |  Generating section %d
131 |    <input type="submit" value="Submit">
132 |  </form>
133 |  HTML generation complete
134 |     ;  @   ,{��<  �|��d  �|��|  L~��$  5���  ����  ����  ����  F���  ��4  }���X  ���x  ����  ����  k����  O����  ���  A���8  i���X  ա��|  ����  �����  �����  բ���  w���  ����@  T���d  �����  �����  >����  5����  Ĺ��  a���(  ���H  ����h  W����  _����  B����  ����  ����  ����(  ����H  ����d  �����  �����  �����  
135 | ����  ���  2���$  L���D  f���d  v����  �����  �����  �����  ����	  ����$	  ���D	  ����d	  �����	  ^����	  �����	  ����	  ���
136 |          zR x�         |��&    D    $   4   �x���   FJw� ?9*3$"       \   Pz��              t   Hz���             �   �|��k    E�Cb     �   �|��_    E�CV     �   #}���    E�C�     �   �}��`    E�CW       *~��|    E�Cs      ,  �~���   E�CE��     P  ���p   E�Cg    p  m���%    E�C\      �  r���   E�C�     �  Z���Q    E�CH     �  �����    E�C�     �  O����    E�C�       ƅ��[   E�CR    0  ���(    E�C_       P  	���l   E�Cl�7     t  Q���8    E�Co      �  i����    E�Cx     �  ʝ��    E�CF      �  ����8    E�Co      �  ѝ���   E�C�       S����
137 |    E�CE�z
138 |       8  ����U   E�CE�G     \  ���2   E�C)    |  ����   E�C�      �  ����    E�CE��      �  n����    E�C�     �  E����    E�C�        �����    E�C�        1����    E�C�     @  �����    E�C�     `  F����    E�C�     �  ǵ��   E�C�     �  �����    E�C�     �  r���=   E�C4    �  ����   E�C�        r���.    E�Ce         �����    E�C�     @  <���<    E�C      \  \���    E�CG      |  L���    E�CH      �  =���    E�CH      �  .���    E�CG      �  ���    E�CH      �  ���    E�CN        ���    E�CQ      <   ���    E�CQ      \  ����    E�CG      |  ���    E�CN      �  ���o    E�Cf     �  0����    E�C�     �  ����    E�CU      �  ����)    E�C`        ĺ��    E�CV      <  ú���   E�C�    \  Q���3    E�Cj      |  d���n   E�Ce    �  ����:
139 |    E�C1
140 |     �  ����m   E�Cd    �  ���   E�C    �  ����   E�C�                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          $      �#      �      �      �      /�      4�      <�      B�      G�      M�      V�      ]�      f�      k�      t�      }�      ��      ��      ��      ��      ��      ��      ��      Ă      Ȃ      ̂      т      ւ      ނ      �      �      ��      �      �       �      )�      ,�      2�      5�      8�      <�      @�      C�      G�      K�      N�      R�      V�      Z�      ^�      f�      k�      o�      y�      ��      ��      ��      ��      ��      ��      ǃ      у      �      �      �                     �                             �             �                           ��                    ���o    �                           �      
141 |        y                                          ��             @                           (              	                   	                            ���o          ���o    �      ���o           ���o    z      ���o    C                                                                                       �                      0       @       P       `       p       �       �       �       �       �       �       �       �        !      !       !      0!      @!      P!      `!      p!      �!      �!      �!                                                              �         GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0 ,             )$      h#                      ,           �G      r!                      ,    �-       i      �                             .2         )$      h#          	A  �:   �  �  /�
142 |   �  �
143 |   �  0int f   �  	�  �r   	�  �r   �   �
144 |   �   $
145 |   �1)    3f      6	�   �  7	�   �  8	�   �  9	�    �
146 |   :	�   (�   ;	�   0�  <	�   8w   =	�   @6  @	�   H  A	�   P�  B	�   Xs  DB  `  FG  hO  Hf   p2  If   t
147 |   Jy   xi  MQ   �-  NX   �+   OL  ��	  Q\  �
148 |   Y�   �.  [f  �%	  \p  ��   ]G  ��  ^	H   ��  _
149 | .   ��  `f   ��  bu  � 	�	  �   1B   +�  =  �   
150 | �   \  :     5  +  a  "	  k  
151 | �   �  :    �   �   �  )   �  �  ��  T   ��  �  �  
152 | �   �  :    �  		  b  
153 | �      �   �   	   �  	�  �  2A   q  �    �  �  �
154 |   8  K  �  �  ]  �	  	�  
155 | O	   	!     ( �    !�    �   "�   :  #�   3zip $�   �  %�     	5   &}  H)x  w  *	f    �  +	f   �  ,	f   (  -	f     .	f     /	f   -  0�      1�    e  2	f   (T  3�   0\  4	f   8
156 |   5x  @ �  	�  6�  <   X9�  =  :�    �  ;q     <}   	<   =�  �  ?�  =  @�    y  A�  z	  B	f    �  	�  C�  �   ER  =  F�    �  GR  (  H	f   �   I\   W      	�  J  k  Mf     Q�    T�  a  �  UW  !�  	`�      !�  
157 | 	h�      �  =  �    �
158 |   	f    	r  �  "�
159 |     	p�      �  "  f   	x�      4�  f   	3h  G  �   �   k  
160 |     �  �   �  �  �
161 |   >  	S  
162 | �  �  c  �  �  U	  �  =    	   MIN MAX �
163 |   |  C  r    -  �  M  X  O   IF !0  "LT #GT $LTE %GTE &EQ 'NEQ (AND )OR * 5�  H	h�  #str ��   #num �	f   ?  ��  �  �W  �  �q    �}  ~  �\   	�  	wh  �  	}�  6�   f   
164 | t	  >  �   �  b    �  �    �  a  6
165 |   	�  
166 | �  "    D  |  F
167 |   �  �  4  �      z  �  �
168 |   s  :  i    $  �  D  O   F  !H  "'  #�  $�  %s
169 |   &
170 |   '�  (�	  )�  *�
171 |   +�  ,�  -�  .�  /�
172 |   06  1b  2	  3�	  4�  5�  6  7�   8�  9  :�  ;6  <�   =u  >Y  ? �   N�  �  iX   �	  [   ��	  �  �f   7a  HZ�	  $�
173 |   \�	  $�
174 |   ]�   
175 | �	  �	  8:   * �	  �  ��	  	��      
176 | �  
177 |   :   @ �	  �  �
178 |   	 �      
179 | �	  9
180 |   :   Z )
181 |     9
182 |   	 �      X  9
183 |   	��      
184 | �	  |
185 |   :    l
186 |   0  '|
187 |   	��      �  .|
188 |   	��      
189 | �	  �
190 |   :   M �
191 |     7�
192 |   	 �      �  C�
193 |   	`�      �  Q9
194 |   	��      
195 | �	    :   4 	  +  `  	 �      �	  k  	`�      %f   v_  q	   9*	�  &f   ,�   &�  -t	   �	    ._  �  '�  Lf   	|�      :�  O		��      '�  Qf   	��      (0	  n�  �   '  �    �  �   G  ef   "  �  �  ) U  mf   ?  �   �  ) ;S  XQ  �   <�   Nf   M   
196 | �.   t  �   (�  ��  H    *A  �f   �  �  �   =#  ��  f      �H   �  H   .    *�  ��   �  �   7  �H   �  .    >�  �f   �G             �+�  �f   G      �       ��  �  �f   �\J  ��  �PG      M       x  ��  �h  �   ?	  ��F      8       ��  @s ��  �h +�  [f   ]1      l      �  �  ]�	  ����  _	f   ����  er   ���@	  h  ��~�  i�  �Ȋf   j�  �Њ�  m  ���|  n.  �؊2  o.  ���yyn qf   ����  sf   ����  ut	  ����   x�  ���-
197 |   {3  ��}�  |	�   ����  }r   ����   �f   ����  �82      l   �02      �  �aE      g  �NE      �  }>E      F	  ��4        3�6      �  P�C      �  �~A      P  =�6      �  =jC      �  �{E      A   X  �  �r   ���,   �  ��  ���O  �C  ����2      }       2  W  �	r   ��� x3      �       W  �	r   ���   *<      L         buf Y�  ��| �=      n       �  �  �\  �ȋ >      S       �  �  ��   ��� `>      S       �  �  ��   ��� �>      S         �  ��   ��� ?      S       G  �  ��   ��� h?      S       o  �  ��   ��� �?      S       �  �  ��   ��� �@      �       �  �  �m   ���yyi �m   ��� ,'   �  �  �Ћ�  �  ���  f   ���  
198 | �	    :   � 
199 | �  .  :   � �  
200 | �   C  :    �	  B�  =51      (       ��  �  =�  �hp  >t	  �d�   >..  �X �  �f   �.      [      ��  �  ��  ���  �2�  ���  �%�  ��%A   �   V   8  ��  ��|  ��  �P�  �r   ��t  �f   ���/      i       �  yyi 	f   ���/      T       �  r   �H  �0      �       yyp &�   �@yyi '	f   ��  r   �  
201 | t	  �  :    �	  �f   C.      �       �^  �  �0�  �X|  �,^  �PC  �9f   �Lt  �f   �hm.      h       yyn �f   �l  t	  a  �r   _-      �       ��    ��   �X�
202 |   �%�  �Pn  �.        ��-      �-      �       yyn �r   �`yyp ��  �h  7	  r�   -      Q       �Y  �  r�   �X�  r%�  �Pyyd t	�   �`yys u�  �h X
203 |   7f   ,            �  �  71�  �H|  8-^  �@C  8:f   ��t  ;f   �Xyyn <f   �`J,      �       �  Bf   �d�	  Df   �h<  Ef   �lyyx Ff   �\  �  ��  �+      %       �P  l  � t	  �l   �q)      p      �Z  ?  ��  ���)      �      ;  �  �\  �P�)      )        i �f   �D�)      	      s �W  �`�)      �       j �f   �H�)      ~       f ��  �h    �*      X       �   �\  �X  f+      S       i �f   �L    R�&      �      ��  �  R$W  ��=  R9�  ���  RIq  ��  R`�  ���
204 |   Z  �Hu  d�  �P  k�  �X }  C�	  E:&      |       �    E-�  �h -  <f   �%      `       �]  =  <'�  �X�%      I       i =f   �l  ]	  ,�$      �       ��  ?  , �  �X�  ,/W  �P�  2R  �h -�  #
205 | W  �$      _       ��  =  #%�  �X�  $W  �h D�	  �  )$      k       �=  �  �X?  �  �h  �   w  %2       �G      r!      A  A  �:   	�  	�  &H   	�
206 |   	�  	�
207 |   6  &O   �  '|   	�  �  )�   'int 	�  �  ��   �  ��   �   	�
208 |   
209 | �   $
210 |   �1M    3�      6	�   �  7	�   �  8	�   �  9	�    �
211 |   :	�   (�   ;	�   0�  <	�   8w   =	�   @6  @	�   H  A	�   P�  B	�   Xs  Df  `  Fk  hO  H�   p2  I�   t
212 |   J�   xi  MV   �-  N]   �+   Op  ��	  Q�  �
213 |   Y�   �.  [�  �%	  \�  ��   ]k  ��  ^	H   ��  _
214 | .   ��  `�   ��  b�  � �	  �   (B   +�  a  �   �   �  :     Y  +  �  "	  �  �   �  :    �   �  e  ��  M  �  �  ��  T   ��  	�  �  p   �  �   	�      )8  	d   X  -  %  .�  
215 | *  -  0�  
216 | ;  q  �!X  ]  2  @�  o  ��   @  ��     ��   Z  ��   f  ��   �  ��    �  ��   $�  ��   (�  �	�   ,2  �	�   0�  ��   4n  ��   8 >  �.     ��     ��  �  ��  �  .   	 �      �  .   	�      �  y  	�      L     �   	�      f  !�   	�        "	��      �  %�   	 �      �  &�   	(�      O  '�   	,�        ,�   	0�      f  \  
217 |     ^	��      *+  ^	��      �  `�   k  b�   T  c	�      D  e�   6  �  :   � 
218 | ~  e  ��  	 �         �  :   � 
219 | �    ��  	��         �  :   ) 
220 | �  �  ��  	��      6    :   � 
221 | �  �  �  	��      �  �  	`�      6  P  :   � 
222 | @  �  �P  	��      /  P  	��      G  �  :   0 
223 | �  ~  6�  	��      (  <H  	4�      O  =�   	8�      �  ?�   �  @	��      r  I	��      �  
224 | 	=  b  
225 | 
226 | �      
227 | �   �   
228 | =     �  
229 |   +A   
230 | �  �    �  �  �
231 |   8  K  �  �  ]  �	  	�  
232 | O	   !   
233 | N  ( �    
234 | !�    �   
235 | "�   :  
236 | #�   ,zip 
237 | $�   �  
238 | %�     5   
239 | &�  H)�  w  
240 | *	�    �  
241 | +	�   �  
242 | ,	�   (  
243 | -	�     
244 | .	�     
245 | /	�   -  
246 | 0�      
247 | 1�    e  
248 | 2	�   (T  
249 | 3�   0\  
250 | 4	�   8
251 |   
252 | 5�  @ �  �  
253 | 6  <   X
254 | 9�  =  
255 | :�    �  
256 | ;�     
257 | <�   <   
258 | =�  �  
259 | ?1	  =  
260 | @�    y  
261 | A1	  z	  
262 | B	�    �  �  
263 | C�  �   
264 | E�	  =  
265 | F�    �  
266 | G�	  (  
267 | H	�   �   
268 | I�	   �	  6	  B  �  
269 | JB	  �	  -�  H��	   str ��    num �	�   ?  ��	  �  ��	  �  ��    ��  ~  ��	   �  ��	  �  ��	  .  �   	��      !�  �?
270 |   H      �H   [
271 |   H   .    /#  �n
272 |   �    �  =H   �
273 |   H   �   .    �  )�   �
274 |   �    P  s�   �
275 |   �   �  �.   �
276 |   J   .   .   �   !&  \�
277 |   �   0B  %   �     `�     �      @�   3  �   P  �.   Y    .   .   �   J  i�   o  �   �  ��   �  �   7  �H   �  .    M   �.   �  �   G  e�   �  �  �  1 �  ��h             ��  ptr �H   �h   �H   �h      )       �?  ptr �H   �ha  �*  �` a  �H   �h             �q  a  �  �h 2}  p�   �g      �       �3  P�   �g      o       ��  Kjg             ��  H  K�   �l �  F�   Zg             �  A@g             �'  �  A�  �h �  <&g             �T    <�  �h   0g             ��  q  0�   �l u  '�   �f             �Z  �   �f             ��  �  �f             ��  �  �f             ��  �   �f             �4�  ��f      <       �F  msg �4�  �h T  �L  �e      �       ��  �  �.�  �HW  �<�   �Db �L  �hbuf ��   �`n �  �Xi ��   �T   �L  ve      .       ��  �
278 |   �.�  �h �  �L  sd            �=  �  �)�   �Xa  �:  �Pb �L  �h "�  d6c      =      ��  b  f  �h�c      �       :    �`  5�  QSb      �       ��  3Ka            ��  �  3+L  �h �  
279 | �`      �       �  b ,L  �h "�  ��_      �       �K  b �3L  �Xx  �=�  �P�  ��   �l �  �
280 | U_      �       �w  b �-L  �h �  �L  �^      �       ��  x  �/�  �Xa  �:�   �Tb �L  �h 6)  �)^      �       ��  �
281 | 2]      �       �  �  �1L  �h �  �
282 | �\      �       �<  r  ��  �X #  H  z[            ��  �  ;H  �\�   �   �d�  !�   �h�  #
283 |   �c #�  �H  HZ      2      ��  �   H  �d�  �   �hiZ      �       �    �c  7�  t�   �S      U      �4  �  v�   �HS  w�   �P�  x�   ��i x�   ��*  y�   ��WU      #          ��   ���U            �  b �L  �XH  ��   ���U      o       K  �	�   �@  �V      �       c ��   ��n ��   ��   Y      �       K  ��   �D  �   ,�   kI      �
284 |       �B  �  .H  ���  /�   �Po  /�   �X�  0�   �@?  _aJ      @  siK      �  ��K      aJ      �       �  �  b  �� L      =         yyl ��   �D 8>   d  ��   �H{R      t       �  H  �L   9  �   �G      �      ��  :k  "�  �X;�  �   �h$i 	�   �`$j �   �d <�  �G      8       �=msg �  �h  K	   �  2  h     i      �      �  A  �:   �  �  �
285 |   �  Q   �
286 |   �  int �  �  �r   �  �r   �   �
287 |   �   �   �   :    $
288 |   �19    3k      6	�   �  7	�   �  8	�   �  9	�    �
289 |   :	�   (�   ;	�   0�  <	�   8w   =	�   @6  @	�   H  A	�   P�  B	�   Xs  DR  `  FW  hO  Hk   p2  Ik   t
290 |   Jy   xi  MQ   �-  N]   �+   O\  ��	  Ql  �
291 |   Y�   �.  [v  �%	  \�  ��   ]W  ��  ^	H   ��  _
292 | .   ��  `k   ��  b�  � �	  �   B   +�  M  �   �   l  :     E  +  q  "	  {  �   �  :    �   �  9  �  T   ��  �  �  X   A   /$  	u   	c   	�   	�   	Y   	�    	�   @	~   ��  P  �  l   �  	Y  b  
293 | �      �   �   Y   $  �  $  A   �  �    �  �  �
294 |   8  K  �  �  ]  �	  	�  
295 | O	   !   j  (     !�    �   "�   :  #�   zip $�   �  %�     5   &�  H)�  w  *	k    �  +	k   �  ,	k   (  -	k     .	k     /	k   -  0�      1�    e  2	k   (T  3�   0\  4	k   8
296 |   5�  @   �  6   <   X9
297 |   =  :�    �  ;�     <�   <   =�  �  ?K  =  @�    y  AK  z	  B	k    
298 |   �  C  �   E�  =  F�    �  G�  (  H	k   �   I�   �  P  ^  �  J\    T�  �  B  O#�  �  �  	��  
299 | H    7  	�H     
300 | .    M   
301 | �.     
302 | �   �  
303 | ��   1  
304 | �   G  ek   N  
305 | �  
306 | �   S  �~      �      ��  �  ��  �X�~      g       i �k   �l  �  ��x            �  �  �#�  ��~?  �1�  ��~�  ��  ��~�z      �        �  ��~op ��   ��~  �   ��  �   /  :   ?    ��v      m      ��  �  �)�  �H  �5�   �@!op �B�   ��  �L�   ��p ��  �hi �	k   �\j �	k   �`k �	k   �d �  .Rl      :
307 |       ��  �  ."�  ���  .3�  ��5m      	      i >k   �DAm      �        @K  �P5  C�   �X�  H�  �H"it      ?       n  %  ��   �` �t      ?         ��   �h    #�  �   �j      n      ��  k  $�  �X�  �   �hj 	k   �`5k            i !k   �d  �  �j      3       �%	  �  !�  �h $~  i      �      ��  !�  �h  (    :;9I8  4 :;9I  (    !I   :;9I   I  
308 |  :!;9  	 :;9I  
309 | I    4 :;9I    ! I/  & I  (    :!;9I  $ >  4 :!;9I  4 :;9I?<  .?:;9'I<  4 :!;9I  :;9   :!;9I   :!;9I   <  :;9!	  ( !~  .:!;9!'I@|  .:!;9!'I@z  .?:!;9!'@|   7 I  !4 G:!;9  "4 :!;9I?  # :!;9I  $ :!;9I  %>!I:!;9  & :!;9I8  '4 :!;9!I?  (.?:;9!'<  )   *.?:!
310 | ;9'I<  +.?:;9'I@|  ,U  -.?:!;9'I@|  .%  /   0$ >  1 :;9  2>I:;9  3 :;9I8  4>I:;9  5:;9  6>I:;9  7:;9  8! I/  9:;9  :4 G:;9  ;.?:;9'<  <. ?:;9'I<  =.?:;9'�<  >. ?:;9I@z  ?.?:;9'@|  @ :;9I  AU  B.:;9'@z  C.?:;9'@z  D.?:;9'I@|    :;9I8  4 :!;9I   I   :;9I   !I   :!;9I  (   4 :!;9I  	$ >  
311 | & I  .?:;9'I<  I  ! I/  4 :;9I?<  .?:!;9'I@|  :;9  .?:!;9'@|   :!;9I  . ?:!;9'I@z    4 G;9   :!;9I  7 I  .?:!;9!'@z     <  4 :!;9I?<  .?:;9'I<  
312 |  :!;9!   :!;9I  :!
313 | ;9!	    :!;9I  !.?:;9!'<  ".:!;9'@|  #.:!;9!'I@z  $4 :!;!9I  %%  &   '$ >  ( :;9  )&   *4 G;  +>I:;9  , :;9I8  -:;9  .4 :;9I?  /.?:;9'�<  0. ?:;9'I<  1   2. ?:;9'I@|  3. :;9'I@z  4.:;9'�@|  5. ?:;9'@|  6. :;9'@z  7.:;9'I@|  8U  9.?:;9'I@|  : :;9I  ;4 :;9I  <.?:;9'@|  = :;9I    :;9I8   !I  (    :;9I   :!;9I  $ >  4 :!;9I  4 :!;9I  	(   
314 |  I    :;9  I  ! I/  .?:!;9!'@|   <  .?:;9'I<  & I  7 I  4 :;9!I?<  >!!I:;9  :!;9!	  %     $ >   :;9   :;9I8  . ?:;9'I<  .?:;9'<  .?:;9'I<      .:;9'@|  ! :;9I  "  #.?:;9'I@|  $.?:;9'@|   =    p   �         =   A   j   �   �      �      �   �   �   �   �   �   �       % 	)$      �� tX/ �u���K+0�� tX/ �u��K80= t	u#;[KtX*���	u#�	���)t	ut�-0�t/"<< �K, r J�Y40�u��������w�
315 |  g0� t t	u#\"�%	u#��.�, �=,�:�Htf(f��	u#��,�$�<u �u�)�"f)u"t(u!t(u!t#ut#ut'u tv�1Y%�# ���7Y+�) ��t�h��	tY(��u�t"Y*��ut( X" t&��B X0 �&��H X6 � ~& J# t��& X  ��t$ X t�3 u�! J t��& X ��t" X t��/�t+ X" t��/ X& ���}	|�t/<<2 X5 <" <, � J	�t X���<�u�.0utf�g%� f t X>��f/��Yhug�v� �* wX  J� t fg
316 | �=.	��	�/��<.<M�.=t��	�X	��1XtM$u�t/Y1u�=	jf2@ u$ .J0�5htt
317 | [u<t/K � � J
318 | "gv
319 | h=.t���g�*������ �$ <  t
320 |  <�t:14�J����" y� J�th�u
321 | th�	�u/
322 | t" J �- J3�/�)fJ �KxYwXtft
323 | �Y
324 | X0u�<4�	�������	���
325 | ��	.
326 | �
327 | ��J"��
328 | �
329 | uɯ�+	� #Z 7h���JJ
330 | J�� .��f[ XifL��fz��\ � �X . Xl� �) � X�.��g]�x�
331 | q�CX%< .��(	.
332 | ��	�b-�t4� �ut��	]����uX���tX��	�tX�	�����tXtY�3Z� �utY�	Z��	�tX����tXtY�)Z-�< �K�_Z	�F<	�5.9�	<��	<��+�tX��+�tX��+�tX��+�tX��+�tX��+�tX��+�tX��+�tX��+�tX��,�tX��+�tX��+�tX��	�tX��#�tX�i XQ �#g�m XU �#g�m XU �#g�k XS �#g�k XS �#g�a XI �#g�a XI �#g�$YtF X. tA�)�#v�$�tL X4 tG�/��t	�tX&���	�tX&���	�tX0�%��t	�tX6�+��t	�tX�-'+ ��t	�tX3�(��f	�tX3�(��f	�tX2�'��f	�tX2�'��f	�tX-�"��f	�tX-�"��f	�tX6�+��t	�tX:�/��f �tX!%�<%�)�<"���(t���tX	(�	�!����tX	(�	�!����tX	)�	�!����sX	)�	�!����sX	)�	�!����s.	)�	�!���3�}<�<� 	3�qX�&X���4 �: .* �K/ X .:k�|X� 2f4 X2 f4 J �2 .< . t 
333 | Xh���!�&�/�t�� �vt[&��'�	����
334 | fMf�\��.�	3���m. �.
335 | ��u �3 �) .L.�
336 | �A-���l�` q��zX� �	�z.�<" �	�z.<�<�  ��'f\ � �X . Xg�	31������t�
337 | �g�r��%!>/ g��u��v�Y�Y0�Y c    �   �         =   A   j   �   �   !  *  !  �   �   �   �   �   2  @  �   �    O       W  O  `  $ 	�G      �%)?� �	�tvY��K.#6!�'t/<#Y!�'t/<#Y!�'t/<$/"�(t0<#/!�'t.<-/"� �-t&<2. 1�� t<
338 | 0rJ���=K�.�f��fK�t	Y�t
339 | Y�t
340 |  X tYZsY�@	X
341 | �	�����<Z�
342 | �$0<K�J�-ff5 %^8ffKZ%<�!
343 | <K
344 | h��<M8
345 | f; v<# fMt/ L! � J�0.
346 | ���
347 | �yX���������
348 | ����������	�fK�� �u	�fK�� �u	�fK�� �u	�fK�� �u	�fK�� �u	�fK�� �u	�fK�� �u	�fK�� �u	�fK�� �u	�fK�� �u
349 | ����������	�fK�� �u
350 | ��	�fK�� �u� �u� �g�t �  t=(tJ �u��#'�X0�#�.
351 | i� t<J+t<g,t�/t
352 | t1tJ�t \�v�
353 | ��i�!g]�\ X#��� gX�w���\tJ�w���^�u��
354 | f	�{ �X
355 | f�t��/t:J�<tY�t<$Lk�'�6X
356 | >t/	��<# - J�t<7\�(t�t*<;	i\Jwt�;
357 | ?tL	tZgt't��t�%t;<�����Y���v*t8<<_f&��w #� 	. 7 �   f 
358 | f f 8 f � J � � Xf . � � X J B � ��(t�fLhuu/t�v(�@t<�@��2Yg%tI2t' �
359 | L"tJY�+t)f?t%J4�=t%J8�>tJ	v=k���Zt" J � � X=<Z�	�#0<K�
360 | J�,ff4 $^7ffB rJ2 X	=6�
361 | �K<Z��"0<K�	J�+ff3 #^6ff K�h f< .Y� .	t	 X t	YZsY�@t X J X X�Y{�Y � � X�t X�t�(t�(t�Ju _n� 1�-t< g8tJt	�!t<u�g	<1�u�1�?t< �
362 | ��Y��	0K5�w � � XgJvtK��x�	 6= XZ��� � � Xg�D�( tD . JX . Xv XYC	����=�J>���� � � Xgot 	.	��[t X�t�(t�(t�t X�!Jw Yl� 5�	t �
363 |  t�t X J X X�JutY"t X�!Yw� 4�t^1� �wtY���7[�t�(�t1� �xtY�.���	.?u L-
364 | M��u�t.u�����tu����	�K.%�	 ��
365 | . 5fg�u
366 | �t/��
367 | <! - J�*�<�<0gu�	�K5�"��g4�u4�u4�g5�u5��	<��?��?�g1��?�������
368 | ���Y2�/t X J X X�JuU ����ZY.��1		</1�� �    k   �         =   A   j   �   �   l  l  �   �   �   �   �   }  �       ) 	i      ��������������)>��+>� t�Z) � <	�vtY	.*6 �<JY7 �=J/5 f;J/5 f;J)/��)t"<( z. J �	��=K<0=# t	u#\t��"%t	Y �(��4wt=�	s J � t#��	t#,-�$Y/�'Y5�%/1�'/5�#/-�'/5�'/3�$//�#/-�'/1�&/0�#t�"&t- J""t- J""t- J�%t�"&t- J�#�tK���%t��"&t- J���"&t- J���%t��&&&&&%"-t- J"�t3 J""t3 J"t&Yt8 X&"t8 X""�KY)���"��IY'����t, X�tC X/ �S X"��2 X"#t: J"�tC X/ tK	"0 ��  J t� ��	�%�  S0��  . X t J X �	Kuc .[ �Y �a t_ < .F t J X �" J t/ J, t< J9 tI JF t
369 | ��=  . X t J X �	Kut J t# J  t0 J- tK��t</t J � <, J) tD J< �: �B t@ <0�=  . X t J X �	Ku . � � t < .
370 | ��=7>��###########!Z	��#)3)%#0)###r �#########"h�	#t X	u#[#�=�t�t	/3�=�	�7 % J �]��Z# YYSYMBOL_MAXLENGTH default_value FieldType _shortbuf AddressField _IO_lock_t strlen stderr yy_state_t yyssp yynewstate _IO_buf_end YYSYMBOL_validation_rules yylen yysymbol_kind_t city yylex FIELD_TEXT yyval _IO_write_end next yyvaluep _freeres_list YYSYMBOL_field _flags cols YYSYMBOL_TEXT YYSYMBOL_CHECKBOX YYSYMBOL_OPTIONAL YYSYMBOL_VALIDATE yydefact YYSYMBOL_PASSWORD _markers yyvs YYSYMBOL_MAX YYSYMBOL_attribute yysyntax_error_status YYSYMBOL_TEXTAREA yydestruct yytype_int8 yylval country YYSYMBOL_YYEOF yystate YYSYMBOL_DROPDOWN rows add_field_to_section GNU C17 13.3.0 -mtune=generic -march=x86-64 -g -fasynchronous-unwind-tables -fstack-protector-strong -fstack-clash-protection -fcf-protection yydefgoto YYSTYPE YYSYMBOL_AND YYSYMBOL_EQ stdout _IO_save_end yymsg field_attrs YYSYMBOL_field_attributes _IO_codecvt malloc YYSYMBOL_YYEMPTY YYSYMBOL_STRING_LITERAL yyabortlab FieldName YYSYMBOL_FILE_TYPE yytranslate long long unsigned int new_sections YYSYMBOL_field_type create_section yymsg_alloc yyerrorlab FIELD_PASSWORD yyin street yypact _IO_backup_base yyr1 yypgoto FIELD_TEXTAREA fprintf _fileno yynewbytes YYSYMBOL_50_1 yykind min_length yystos cond YYSYMBOL_GT _IO_read_base FIELD_CHECKBOX argc yyerrlab yyerrlab1 Section YYSYMBOL_EMAIL yystacksize YYSYMBOL_44_ YYSYMBOL_MINLENGTH cleanup_form yytable YYSYMBOL_ERROR YYSYMBOL_validation_block yyreduce YYSYMBOL_condition yysymbol new_fields YYSYMBOL_REQUIRED YYSYMBOL_DATE yychar yycheck _mode ValidationRule FIELD_DROPDOWN yysize1 YYSYMBOL_45_ _IO_marker yyerrstatus YYSYMBOL_SECTION _IO_read_ptr yyres exit max_value yyvsp yyformat strcmp YYSYMBOL_IF confirm_field YYSYMBOL_YYUNDEF YYSYMBOL_COLS current_section yyctx YYSYMBOL_FIELD FieldAttributes yyxbegin _IO_write_base yyreturnlab yysymbol_name YYSYMBOL_46_ long long int YYSYMBOL_field_list field_name_count section_count _IO_save_base YYSYMBOL_RADIO generate_html yytnamerr yylineno yycount yyarg yy_state_fast_t yysyntax_error YYSYMBOL_47_ _freeres_buf YYSYMBOL_section_header Form YYSYMBOL_ADDRESS YYSYMBOL_section __pad5 YYSYMBOL_FORM yydefault error_message fopen _vtable_offset yyxend yyargn argv yyptr sprintf FIELD_RADIO YYSYMBOL_DEFAULT YYSYMBOL_MIN yyacceptlab yyresult YYSYMBOL_LT _IO_read_end max_length yysize yysrc short int yyss1 YYSYMBOL_YYerror min_value yyexhaustedlab YYSYMBOL_form_body yyerror _IO_wide_data perror yystpcpy yyssa yybackup FIELD_ADDRESS add_section_to_form YYENOMEM field_count yyr2 yy_syntax_error_arguments yychecklim init_field_attributes YYSYMBOL_NEQ FIELD_FILE _lock create_form YYSYMBOL_form_item address _old_offset YYSYMBOL_GTE _IO_FILE yymsgbuf YYSYMBOL_NUMBER YYSYMBOL_USERNAME yypcontext_expected_tokens YYSYMBOL_LTE yyss_alloc YYSYMBOL_YYACCEPT new_field_names yystr yyvs_alloc FIELD_NUMBER unsigned char line YYSYMBOL_ROWS _IO_write_ptr YYSYMBOL_OR yypcontext_t YYSYMBOL_CONFIRM YYSYMBOL_STRENGTH YYSYMBOL_form YYSYMBOL_NUMBER_LITERAL strength_required do_not_strip_quotes FIELD_EMAIL __off_t yytname strdup yywrap short unsigned int yyss main yyvsa yytoken yymsgp FIELD_USERNAME yyparse yytokentype current_form append _chain check_duplicate_field _flags2 YYSYMBOL_PATTERN FIELD_DATE YYARGS_MAX yyalloc _cur_column YYSYMBOL_validation_rule yydest yylhs yysetstate __off64_t _unused2 _IO_buf_base YYSYMBOL_IDENTIFIER yynerrs number_to_move yy_base yy_is_interactive yy_scan_string num_to_read clearerr yy_chk __uint8_t yy_ch_buf atoi yy_last_accepting_cpos yy_n_chars YY_BUFFER_STATE new_buffer yyget_in yy_flex_debug yy_create_buffer yypush_buffer_state _out_str yy_def yy_switch_to_buffer yyget_lineno output getc yy_hold_char yyleng yy_try_NUL_trans ret_val yy_buffer_state __errno_location source yyget_leng stdin input _line_number yy_rule_can_match_eol yy_state_type yy_get_next_buffer yyset_debug yy_get_previous_state yy_c_buf_p yy_bs_lineno yy_meta isatty yyensure_buffer_stack yyrealloc ferror flex_int16_t yy_bs_column yy_match yy_c_buf_p_offset yy_buf_size YY_CHAR yy_buffer_status after_colon yypop_buffer_state yy_c yy_at_bol yyout yy_is_our_buffer yybytes yyget_debug yy_act yy_fatal_error yyrestart yyfree yy_fill_buffer yy_init_globals process_string flex_int32_t grow_size yytext new_size yy_scan_bytes num_to_alloc yy_bp yyget_text yy_init_buffer yy_flush_buffer yy_cp yy_is_jam yy_buffer_stack_top yy_next_state yy_buffer_stack memset yy_delete_buffer __int16_t _in_str yyset_lineno yy_ec yyset_out yy_last_accepting_state yy_find_action yy_start flex_uint8_t yy_accept yy_input_file yylex_destroy do_action yyset_in yyget_out yy_init yy_scan_buffer yy_buffer_stack_max yy_nxt oerrno yy_current_state fread __int32_t yy_did_buffer_switch_on_eof yy_buf_pos yy_load_buffer_state yy_size_t _bdebug fwrite _yybytes_len yy_amount_of_matched_text _ISgraph _ISspace generate_validation_js _ISalpha _ISdigit generate_html_footer _ISblank _ISpunct generate_section_html escape_html_attr parse_condition escaped_value escaped_pattern escaped_name __ctype_b_loc _IScntrl _ISxdigit _ISlower _ISalnum _ISupper generate_html_header _ISprint src/parser.tab.c /home/dinuka/programming-paradigms/FormLang src /usr/lib/gcc/x86_64-linux-gnu/13/include /usr/include/x86_64-linux-gnu/bits /usr/include/x86_64-linux-gnu/bits/types /usr/include parser.y stddef.h types.h struct_FILE.h stdio.h formLang.h parser.tab.h string.h stdlib.h src/lex.yy.c lexer.l stdint-intn.h stdint-uintn.h y.tab.h unistd.h errno.h src/html_generator.c ctype.h .         �� �B�B�B�B �� �B�B �;�=�B�B          ����                             ��                	     �                  ��                     p#                    �#              3     �#              I     H�             U     ��              |      $              �     �              �    ��                �     ��      +      �      �            �     �+      %       �      �      [       �     ��      [       �     ��             �     ��             �      �      N            `�      N           ��      [            �      5           `�      5           ,            4    -      Q       =    _-      �       G    C.      �       a    �.      [      p    51      (       {   ��                �     �             �    �             �    �             �    �             �    �             �     �             �    (�             �    ,�             �    0�                  �      |          ��                 ��      *       $    ��      �      ,    `�      �      3    ��      �      :    ��      �      A    ��      �       W    4�             o    8�             �    6c      =      �    )^      �       �    HZ      2      �    z[            �    �S      U      �    �f      <       �    �_      �       	    �g      o          ��                *    �v      m          ��                :    �                   ��                H    �              Q     ��              d    ��              z    2]      �       �    �\      �       �                     �    ��             �                     �                     �    �f             �                           �             $    �x            �      �              ;                     N                     a                     s    0�             �    �%      `       �    �              �    p�             �    �F      8       �    ]1      l      �    ��             �   �              �                     �                     �    Zg                 ��             
371 |     h�                 `�             '    �h      )       1    �^      �       B    �             K    ��             Y                     l    )$      k       x    x�             �    �f             �    �h             �    �h             �    g             �    sd            �    :&      |       �     �              �    �&      �      �                     
372 |     ��                 ��                 ve      .       +    &g             4    �G      �      C                     W    �e      �       e                      t    �f             �   �              �                     �    �f             �                     �     �             �    Ka            �    Rl      :
373 |       �    |�                  �j      n                           c    �G      8       $    �$      �       8    U_      �       I                     \    Sb      �       o    @�              t    ��             �    @#      &       {                     �     �              �    G      �       �    �$      _       �    kI      �
374 |       �    �`      �       �                     �                     �                     �    ��      H           �f                 ~      �                           -                     >                     Q   �              ]                      w    �G             ~                     �    �j      3       �    jg             �    q)      p      �    @g             �    i      �      �  "                   �                   �                     
375 | 	    �g      �       	                     0	    @�              Scrt1.o __abi_tag crtstuff.c deregister_tm_clones __do_global_dtors_aux completed.0 __do_global_dtors_aux_fini_array_entry frame_dummy __frame_dummy_init_array_entry parser.tab.c yytranslate yytname yysymbol_name yypact yydefact yypgoto yydefgoto yytable yycheck yystos yyr1 yyr2 yypcontext_expected_tokens yystpcpy yytnamerr yy_syntax_error_arguments yysyntax_error yydestruct lex.yy.c yy_buffer_stack_top yy_buffer_stack_max yy_buffer_stack yy_hold_char yy_n_chars yy_c_buf_p yy_init yy_start yy_did_buffer_switch_on_eof yy_accept yy_ec yy_meta yy_base yy_def yy_nxt yy_chk yy_rule_can_match_eol yy_last_accepting_state yy_last_accepting_cpos yyensure_buffer_stack yy_load_buffer_state yy_get_previous_state yy_try_NUL_trans yy_get_next_buffer yy_fatal_error yy_init_buffer yy_init_globals html_generator.c parse_condition __FRAME_END__ _DYNAMIC __GNU_EH_FRAME_HDR _GLOBAL_OFFSET_TABLE_ yy_switch_to_buffer yyrestart free@GLIBC_2.2.5 yynerrs __libc_start_main@GLIBC_2.34 __errno_location@GLIBC_2.2.5 yyget_out _ITM_deregisterTMCloneTable stdout@GLIBC_2.2.5 generate_validation_js ferror@GLIBC_2.2.5 isatty@GLIBC_2.2.5 fread@GLIBC_2.2.5 stdin@GLIBC_2.2.5 check_duplicate_field _edata field_names yyerror yyparse yyin _fini strlen@GLIBC_2.2.5 __stack_chk_fail@GLIBC_2.4 yyget_debug yytext current_section current_form yyrealloc yy_create_buffer yylineno yy_flex_debug memset@GLIBC_2.2.5 create_form field_name_count yyget_text yyalloc yyfree yyset_lineno yy_scan_buffer init_field_attributes __data_start add_field_to_section strcmp@GLIBC_2.2.5 yyout after_colon yy_scan_string yyset_in process_string fprintf@GLIBC_2.2.5 yy_scan_bytes __gmon_start__ yyget_lineno __dso_handle clearerr@GLIBC_2.2.5 yyget_leng memcpy@GLIBC_2.14 _IO_stdin_used yypush_buffer_state generate_section_html yychar escape_html_attr fileno@GLIBC_2.2.5 add_section_to_form yy_delete_buffer malloc@GLIBC_2.2.5 yypop_buffer_state _end yyleng realloc@GLIBC_2.2.5 __bss_start main create_section yylex yy_flush_buffer fopen@GLIBC_2.2.5 perror@GLIBC_2.2.5 atoi@GLIBC_2.2.5 yylval yyget_in generate_html sprintf@GLIBC_2.2.5 exit@GLIBC_2.2.5 fwrite@GLIBC_2.2.5 __TMC_END__ _ITM_registerTMCloneTable yywrap strdup@GLIBC_2.2.5 generate_html_footer yyset_debug cleanup_form yyset_out generate_html_header __cxa_finalize@GLIBC_2.2.5 getc@GLIBC_2.2.5 yylex_destroy __ctype_b_loc@GLIBC_2.3 stderr@GLIBC_2.2.5  .symtab .strtab .shstrtab .interp .note.gnu.property .note.gnu.build-id .note.ABI-tag .gnu.hash .dynsym .dynstr .gnu.version .gnu.version_r .rela.dyn .rela.plt .init .plt.got .plt.sec .text .fini .rodata .eh_frame_hdr .eh_frame .init_array .fini_array .data.rel.ro .dynamic .data .bss .comment .debug_aranges .debug_info .debug_abbrev .debug_line .debug_str .debug_line_str .debug_rnglists                                                                                                                              #             8      8      0                              6             h      h      $                              I             �      �                                     W   ���o       �      �      4                             a             �      �                                i                           y                             q   ���o       z      z      B                            ~   ���o       �      �      `                            �              	       	                                 �      B       (      (      @                          �                                                           �                             �                            �             �!      �!                                   �             �!      �!      �                            �             @#      @#      �\                             �             �      �                                    �              �       �      �$                              �             ��      ��                                   �              �       �                                   �             �      �                                   �             ��      ��                                   �              �       �                                    
376 |             �      �      �                           �             ��      ��                                                �       �                                                 �      �                                          0               �      +                             '                     ?�      �                              6                     ��      17                             B                      �      �
377 |                              P                     �     C!                             \     0               $     �                            g     0               �7     �                            w                     /9     I                                                    x9     �      %   B                 	                       I     C	                                                   cR     �                             
```

docs/syntax.md
```
1 | # FormLang++ Syntax Guide
2 | 
3 | ## Metadata Declarations
4 | 
5 | Metadata allows you to attach key-value information to a form. Metadata is declared at the top level of a form, before any sections or fields. Each metadata entry uses the `meta` keyword, a key, an equals sign, and a string value, ending with a semicolon.
6 | 
7 | **Syntax:**
8 | 
9 | ```
10 | meta <key> = <string>;
11 | ```
12 | 
13 | - `<key>`: An identifier for the metadata entry (e.g., `author`, `version`, `description`).
14 | - `<string>`: The value for the metadata, enclosed in double quotes.
15 | 
16 | **Where:**
17 | - Metadata declarations must appear inside the form block, before any section or field declarations.
18 | 
19 | **Example:**
20 | 
21 | ```
22 | form ExampleForm {
23 |     meta author = "SE2062 Team";
24 |     meta version = "1.0";
25 |     meta description = "A sample form with metadata support.";
26 | 
27 |     section Info {
28 |         field name: text {
29 |             required;
30 |         }
31 |     }
32 | }
33 | ```
34 | 
35 | **Effect:**
36 | - Metadata is included in the generated HTML as comments in the `<head>` section.
37 | - You can add any number of metadata entries to a form. 
```

output/address_edge.html
```
1 | <!DOCTYPE html>
2 | <html>
3 | <head>
4 | <style>
5 | body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }
6 | form { background: #f5f5f5; padding: 20px; border-radius: 5px; }
7 | section { margin-bottom: 20px; padding: 15px; background: white; border-radius: 5px; }
8 | h2 { color: #333; margin-top: 0; }
9 | label { display: block; margin-bottom: 5px; }
10 | input, textarea, select { width: 100%; padding: 8px; margin-bottom: 10px; border: 1px solid #ddd; border-radius: 4px; }
11 | input[type=submit] { background: #4CAF50; color: white; border: none; padding: 10px 20px; cursor: pointer; width: auto; }
12 | input[type=submit]:hover { background: #45a049; }
13 | .radio-group { margin-bottom: 10px; }
14 | .radio-group label { display: inline; margin-left: 5px; }
15 | </style>
16 | </head>
17 | <body>
18 | <form>
19 | <section>
20 | <h2>Addr</h2>
21 | <label for="address">address *</label>
22 | <div class="address-group">
23 | <input type="text" id="address_street" name="address_street" placeholder="Street" required>
24 | <input type="text" id="address_city" name="address_city" placeholder="City" required>
25 | <input type="text" id="address_state" name="address_state" placeholder="State" required>
26 | <input type="text" id="address_zip" name="address_zip" placeholder="ZIP" required>
27 | <input type="text" id="address_country" name="address_country" placeholder="Country" required>
28 | </div>
29 | </section>
30 | <input type="submit" value="Submit">
31 | </form>
32 | </body>
33 | </html>
34 | <script>
35 | document.addEventListener('DOMContentLoaded', function() {
36 |   const form = document.querySelector('form');
37 |   const errorDiv = document.createElement('div');
38 |   errorDiv.style.color = 'red';
39 |   errorDiv.style.marginBottom = '10px';
40 |   form.insertBefore(errorDiv, form.firstChild);
41 | 
42 |   function checkPasswordStrength(password) {
43 |     let strength = 0;
44 |     if (password.length >= 8) strength++;
45 |     if (/[A-Z]/.test(password)) strength++;
46 |     if (/[a-z]/.test(password)) strength++;
47 |     if (/[0-9]/.test(password)) strength++;
48 |     if (/[^A-Za-z0-9]/.test(password)) strength++;
49 |     return strength;
50 |   }
51 | 
52 |   const passwordFields = form.querySelectorAll('input[type="password"]');
53 |   passwordFields.forEach(field => {
54 |     if (field.dataset.strength) {
55 |       field.addEventListener('input', function() {
56 |         const strength = checkPasswordStrength(this.value);
57 |         const meter = document.getElementById(this.id + '_strength');
58 |         if (meter) meter.value = strength;
59 |       });
60 |     }
61 |   });
62 | 
63 |   form.addEventListener('submit', function(e) {
64 |     e.preventDefault();
65 |     let valid = true;
66 |     const errors = [];
67 | 
68 |     const passwordFields = form.querySelectorAll('input[type="password"]');
69 |     passwordFields.forEach(field => {
70 |       if (field.dataset.strength) {
71 |         const strength = checkPasswordStrength(field.value);
72 |         if (strength < parseInt(field.dataset.strength)) {
73 |           errors.push(`Password strength must be at least ${field.dataset.strength}`);
74 |           valid = false;
75 |         }
76 |       }
77 |       if (field.dataset.confirm) {
78 |         const confirmField = document.getElementById(field.dataset.confirm);
79 |         if (confirmField && field.value !== confirmField.value) {
80 |           errors.push('Passwords do not match');
81 |           valid = false;
82 |         }
83 |       }
84 |     });
85 | 
86 |     {
87 |       var address_zip = document.getElementById('address_zip');
88 |       var address_zipVal = address_zip ? address_zip.value : '';
89 |       if (!address_zip || address_zipVal === '') {
90 |         errors.push("Field 'address_zip' is required.");
91 |         valid = false;
92 |       } else if (parseFloat(address_zipVal) < 10000) {
93 |         errors.push("ZIP too short!");
94 |         valid = false;
95 |       }
96 |     }
97 |     {
98 |       var address_street = document.getElementById('address_street');
99 |       var address_streetVal = address_street ? address_street.value : '';
100 |       if (!address_street || address_streetVal === '') {
101 |         errors.push("Field 'address_street' is required.");
102 |         valid = false;
103 |       } else if (parseFloat(address_streetVal) == 0) {
104 |         errors.push("Street required!");
105 |         valid = false;
106 |       }
107 |     }
108 |     if (!valid) {
109 |       errorDiv.innerHTML = errors.join('<br>');
110 |     } else {
111 |       errorDiv.innerHTML = '';
112 |       form.submit();
113 |     }
114 |   });
115 | });
116 | </script>
```

output/address_validation.html
```
1 | <!DOCTYPE html>
2 | <html>
3 | <head>
4 | <style>
5 | body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }
6 | form { background: #f5f5f5; padding: 20px; border-radius: 5px; }
7 | section { margin-bottom: 20px; padding: 15px; background: white; border-radius: 5px; }
8 | h2 { color: #333; margin-top: 0; }
9 | label { display: block; margin-bottom: 5px; }
10 | input, textarea, select { width: 100%; padding: 8px; margin-bottom: 10px; border: 1px solid #ddd; border-radius: 4px; }
11 | input[type=submit] { background: #4CAF50; color: white; border: none; padding: 10px 20px; cursor: pointer; width: auto; }
12 | input[type=submit]:hover { background: #45a049; }
13 | .radio-group { margin-bottom: 10px; }
14 | .radio-group label { display: inline; margin-left: 5px; }
15 | </style>
16 | </head>
17 | <body>
18 | <form>
19 | <section>
20 | <h2>AddressInfo</h2>
21 | <label for="address">address *</label>
22 | <div class="address-group">
23 | <input type="text" id="address_street" name="address_street" placeholder="Street" required>
24 | <input type="text" id="address_city" name="address_city" placeholder="City" required>
25 | <input type="text" id="address_state" name="address_state" placeholder="State" required>
26 | <input type="text" id="address_zip" name="address_zip" placeholder="ZIP" required>
27 | <input type="text" id="address_country" name="address_country" placeholder="Country" required>
28 | </div>
29 | <label for="zip">zip</label>
30 | <input type="number" id="zip" name="zip" min="10000" max="99999">
31 | </section>
32 | <input type="submit" value="Submit">
33 | </form>
34 | </body>
35 | </html>
36 | <script>
37 | document.addEventListener('DOMContentLoaded', function() {
38 |   const form = document.querySelector('form');
39 |   form.addEventListener('submit', function(e) {
40 |     let valid = true;
41 |     const errors = [];
42 | 
43 |     {
44 |       var zip = document.getElementById('zip');
45 |       var zipVal = zip ? zip.value : '';
46 |       if (zip && zipVal !== '' && parseFloat(zipVal) > 99999) {
47 |         errors.push("ZIP must be at most 5 digits.");
48 |         valid = false;
49 |       }
50 |     }
51 |     {
52 |       var zip = document.getElementById('zip');
53 |       var zipVal = zip ? zip.value : '';
54 |       if (zip && zipVal !== '' && parseFloat(zipVal) < 10000) {
55 |         errors.push("ZIP must be at least 5 digits.");
56 |         valid = false;
57 |       }
58 |     }
59 |     if (!valid) {
60 |       e.preventDefault();
61 |       alert(errors.join('\n'));
62 |     }
63 |   });
64 | });
65 | </script>
```

output/comprehensive_test.html
```
1 | <!DOCTYPE html>
2 | <html>
3 | <head>
4 |   <meta charset="UTF-8">
5 |   <meta name="viewport" content="width=device-width, initial-scale=1.0">
6 |   <title>ComprehensiveTest</title>
7 |   <style>
8 |     body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }
9 |     fieldset { margin-bottom: 20px; padding: 15px; border: 1px solid #ccc; }
10 |     legend { font-weight: bold; padding: 0 10px; }
11 |     .field { margin-bottom: 15px; }
12 |     label { display: block; margin-bottom: 5px; }
13 |     input, textarea, select { width: 100%; padding: 8px; margin-bottom: 5px; }
14 |     .error { color: red; font-size: 0.9em; margin-top: 5px; }
15 |   </style>
16 | </head>
17 | <body>
18 | <form id="ComprehensiveTest" onsubmit="return validateForm()">
19 | <form>
20 | <input type="submit" value="Submit">
21 | </form>
22 | </body>
23 | </html>
24 | <script>
25 | document.addEventListener('DOMContentLoaded', function() {
26 |   const form = document.querySelector('form');
27 |   form.addEventListener('submit', function(e) {
28 |     let valid = true;
29 |     const errors = [];
30 | 
31 |     if (!valid) {
32 |       e.preventDefault();
33 |       alert(errors.join('\n'));
34 |     }
35 |   });
36 | });
37 | </script>
```

output/edge_cases.html
```
```

output/invalid_syntax.html
```
1 | <!DOCTYPE html>
2 | <html>
3 | <head>
4 | <style>
5 | body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }
6 | form { background: #f5f5f5; padding: 20px; border-radius: 5px; }
7 | section { margin-bottom: 20px; padding: 15px; background: white; border-radius: 5px; }
8 | h2 { color: #333; margin-top: 0; }
9 | label { display: block; margin-bottom: 5px; }
10 | input, textarea, select { width: 100%; padding: 8px; margin-bottom: 10px; border: 1px solid #ddd; border-radius: 4px; }
11 | input[type=submit] { background: #4CAF50; color: white; border: none; padding: 10px 20px; cursor: pointer; width: auto; }
12 | input[type=submit]:hover { background: #45a049; }
13 | .radio-group { margin-bottom: 10px; }
14 | .radio-group label { display: inline; margin-left: 5px; }
15 | </style>
16 | </head>
17 | <body>
18 | <form>
19 | <input type="submit" value="Submit">
20 | </form>
21 | </body>
22 | </html>
23 | <script>
24 | document.addEventListener('DOMContentLoaded', function() {
25 |   const form = document.querySelector('form');
26 |   const errorDiv = document.createElement('div');
27 |   errorDiv.style.color = 'red';
28 |   errorDiv.style.marginBottom = '10px';
29 |   form.insertBefore(errorDiv, form.firstChild);
30 | 
31 |   function checkPasswordStrength(password) {
32 |     let strength = 0;
33 |     if (password.length >= 8) strength++;
34 |     if (/[A-Z]/.test(password)) strength++;
35 |     if (/[a-z]/.test(password)) strength++;
36 |     if (/[0-9]/.test(password)) strength++;
37 |     if (/[^A-Za-z0-9]/.test(password)) strength++;
38 |     return strength;
39 |   }
40 | 
41 |   const passwordFields = form.querySelectorAll('input[type="password"]');
42 |   passwordFields.forEach(field => {
43 |     if (field.dataset.strength) {
44 |       field.addEventListener('input', function() {
45 |         const strength = checkPasswordStrength(this.value);
46 |         const meter = document.getElementById(this.id + '_strength');
47 |         if (meter) meter.value = strength;
48 |       });
49 |     }
50 |   });
51 | 
52 |   form.addEventListener('submit', function(e) {
53 |     e.preventDefault();
54 |     let valid = true;
55 |     const errors = [];
56 | 
57 |     const passwordFields = form.querySelectorAll('input[type="password"]');
58 |     passwordFields.forEach(field => {
59 |       if (field.dataset.strength) {
60 |         const strength = checkPasswordStrength(field.value);
61 |         if (strength < parseInt(field.dataset.strength)) {
62 |           errors.push(`Password strength must be at least ${field.dataset.strength}`);
63 |           valid = false;
64 |         }
65 |       }
66 |       if (field.dataset.confirm) {
67 |         const confirmField = document.getElementById(field.dataset.confirm);
68 |         if (confirmField && field.value !== confirmField.value) {
69 |           errors.push('Passwords do not match');
70 |           valid = false;
71 |         }
72 |       }
73 |     });
74 | 
75 |     {
76 |       var missing_type = document.getElementById('missing_type');
77 |       var missing_typeVal = missing_type ? missing_type.value : '';
78 |       if (!missing_type || missing_typeVal === '') {
79 |         errors.push("Field 'missing_type' is required.");
80 |         valid = false;
81 |       } else if (parseFloat(missing_typeVal) < 0) {
82 |         errors.push("Should not parse!");
83 |         valid = false;
84 |       }
85 |     }
86 |     if (!valid) {
87 |       errorDiv.innerHTML = errors.join('<br>');
88 |     } else {
89 |       errorDiv.innerHTML = '';
90 |       form.submit();
91 |     }
92 |   });
93 | });
94 | </script>
```

output/metadata_edge_test.html
```
1 | <!DOCTYPE html>
2 | <html>
3 | <head>
4 |   <meta charset="UTF-8">
5 |   <meta name="viewport" content="width=device-width, initial-scale=1.0">
6 |   <title>MetadataEdgeTest</title>
7 |   <style>
8 |     body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }
9 |     fieldset { margin-bottom: 20px; padding: 15px; border: 1px solid #ccc; }
10 |     legend { font-weight: bold; padding: 0 10px; }
11 |     .field { margin-bottom: 15px; }
12 |     label { display: block; margin-bottom: 5px; }
13 |     input, textarea, select { width: 100%; padding: 8px; margin-bottom: 5px; }
14 |     .error { color: red; font-size: 0.9em; margin-top: 5px; }
15 |   </style>
16 | </head>
17 | <body>
18 | <form id="MetadataEdgeTest" onsubmit="return validateForm()">
19 | <form>
20 | <input type="submit" value="Submit">
21 | </form>
22 | </body>
23 | </html>
24 | <script>
25 | document.addEventListener('DOMContentLoaded', function() {
26 |   const form = document.querySelector('form');
27 |   form.addEventListener('submit', function(e) {
28 |     let valid = true;
29 |     const errors = [];
30 | 
31 |     if (!valid) {
32 |       e.preventDefault();
33 |       alert(errors.join('\n'));
34 |     }
35 |   });
36 | });
37 | </script>
```

output/metadata_test.html
```
1 | <!DOCTYPE html>
2 | <html>
3 | <head>
4 |   <meta charset="UTF-8">
5 |   <meta name="viewport" content="width=device-width, initial-scale=1.0">
6 |   <title>MetadataTest</title>
7 |   <style>
8 |     body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }
9 |     fieldset { margin-bottom: 20px; padding: 15px; border: 1px solid #ccc; }
10 |     legend { font-weight: bold; padding: 0 10px; }
11 |     .field { margin-bottom: 15px; }
12 |     label { display: block; margin-bottom: 5px; }
13 |     input, textarea, select { width: 100%; padding: 8px; margin-bottom: 5px; }
14 |     .error { color: red; font-size: 0.9em; margin-top: 5px; }
15 |   </style>
16 | </head>
17 | <body>
18 | <form id="MetadataTest" onsubmit="return validateForm()">
19 | <form>
20 | <input type="submit" value="Submit">
21 | </form>
22 | </body>
23 | </html>
24 | <script>
25 | document.addEventListener('DOMContentLoaded', function() {
26 |   const form = document.querySelector('form');
27 |   form.addEventListener('submit', function(e) {
28 |     let valid = true;
29 |     const errors = [];
30 | 
31 |     if (!valid) {
32 |       e.preventDefault();
33 |       alert(errors.join('\n'));
34 |     }
35 |   });
36 | });
37 | </script>
```

output/milestone5_simple.html
```
```

output/milestone5_test.html
```
```

output/minimal_validation.html
```
1 | <!DOCTYPE html>
2 | <html>
3 | <head>
4 | <style>
5 | body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }
6 | form { background: #f5f5f5; padding: 20px; border-radius: 5px; }
7 | section { margin-bottom: 20px; padding: 15px; background: white; border-radius: 5px; }
8 | h2 { color: #333; margin-top: 0; }
9 | label { display: block; margin-bottom: 5px; }
10 | input, textarea, select { width: 100%; padding: 8px; margin-bottom: 10px; border: 1px solid #ddd; border-radius: 4px; }
11 | input[type=submit] { background: #4CAF50; color: white; border: none; padding: 10px 20px; cursor: pointer; width: auto; }
12 | input[type=submit]:hover { background: #45a049; }
13 | .radio-group { margin-bottom: 10px; }
14 | .radio-group label { display: inline; margin-left: 5px; }
15 | </style>
16 | </head>
17 | <body>
18 | <form>
19 | <section>
20 | <h2>Main</h2>
21 | <label for="age">age</label>
22 | <input type="number" id="age" name="age" min="0" max="120">
23 | </section>
24 | <input type="submit" value="Submit">
25 | </form>
26 | </body>
27 | </html>
28 | <script>
29 | document.addEventListener('DOMContentLoaded', function() {
30 |   const form = document.querySelector('form');
31 |   const errorDiv = document.createElement('div');
32 |   errorDiv.style.color = 'red';
33 |   errorDiv.style.marginBottom = '10px';
34 |   form.insertBefore(errorDiv, form.firstChild);
35 | 
36 |   function checkPasswordStrength(password) {
37 |     let strength = 0;
38 |     if (password.length >= 8) strength++;
39 |     if (/[A-Z]/.test(password)) strength++;
40 |     if (/[a-z]/.test(password)) strength++;
41 |     if (/[0-9]/.test(password)) strength++;
42 |     if (/[^A-Za-z0-9]/.test(password)) strength++;
43 |     return strength;
44 |   }
45 | 
46 |   const passwordFields = form.querySelectorAll('input[type="password"]');
47 |   passwordFields.forEach(field => {
48 |     if (field.dataset.strength) {
49 |       field.addEventListener('input', function() {
50 |         const strength = checkPasswordStrength(this.value);
51 |         const meter = document.getElementById(this.id + '_strength');
52 |         if (meter) meter.value = strength;
53 |       });
54 |     }
55 |   });
56 | 
57 |   form.addEventListener('submit', function(e) {
58 |     e.preventDefault();
59 |     let valid = true;
60 |     const errors = [];
61 | 
62 |     const passwordFields = form.querySelectorAll('input[type="password"]');
63 |     passwordFields.forEach(field => {
64 |       if (field.dataset.strength) {
65 |         const strength = checkPasswordStrength(field.value);
66 |         if (strength < parseInt(field.dataset.strength)) {
67 |           errors.push(`Password strength must be at least ${field.dataset.strength}`);
68 |           valid = false;
69 |         }
70 |       }
71 |       if (field.dataset.confirm) {
72 |         const confirmField = document.getElementById(field.dataset.confirm);
73 |         if (confirmField && field.value !== confirmField.value) {
74 |           errors.push('Passwords do not match');
75 |           valid = false;
76 |         }
77 |       }
78 |     });
79 | 
80 |     {
81 |       var age = document.getElementById('age');
82 |       var ageVal = age ? age.value : '';
83 |       if (!age || ageVal === '') {
84 |         errors.push("Field 'age' is required.");
85 |         valid = false;
86 |       } else if (parseFloat(ageVal) > 100) {
87 |         errors.push("Age cannot exceed 100.");
88 |         valid = false;
89 |       }
90 |     }
91 |     {
92 |       var age = document.getElementById('age');
93 |       var ageVal = age ? age.value : '';
94 |       if (!age || ageVal === '') {
95 |         errors.push("Field 'age' is required.");
96 |         valid = false;
97 |       } else if (parseFloat(ageVal) < 18) {
98 |         errors.push("You must be at least 18.");
99 |         valid = false;
100 |       }
101 |     }
102 |     if (!valid) {
103 |       errorDiv.innerHTML = errors.join('<br>');
104 |     } else {
105 |       errorDiv.innerHTML = '';
106 |       form.submit();
107 |     }
108 |   });
109 | });
110 | </script>
```

output/options_test.html
```
```

output/registration.html
```
```

output/test.html
```
```

output/validation_test.html
```
1 | <!DOCTYPE html>
2 | <html>
3 | <head>
4 | <style>
5 | body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }
6 | form { background: #f5f5f5; padding: 20px; border-radius: 5px; }
7 | section { margin-bottom: 20px; padding: 15px; background: white; border-radius: 5px; }
8 | h2 { color: #333; margin-top: 0; }
9 | label { display: block; margin-bottom: 5px; }
10 | input, textarea, select { width: 100%; padding: 8px; margin-bottom: 10px; border: 1px solid #ddd; border-radius: 4px; }
11 | input[type=submit] { background: #4CAF50; color: white; border: none; padding: 10px 20px; cursor: pointer; width: auto; }
12 | input[type=submit]:hover { background: #45a049; }
13 | .radio-group { margin-bottom: 10px; }
14 | .radio-group label { display: inline; margin-left: 5px; }
15 | </style>
16 | </head>
17 | <body>
18 | <form>
19 | <section>
20 | <h2>UserInfo</h2>
21 | <label for="username">username</label>
22 | <input type="text" id="username" name="username" minlength="3" maxlength="20" pattern="[a-zA-Z0-9_]+">
23 | <label for="email">email *</label>
24 | <input type="email" id="email" name="email" required>
25 | <label for="password">password</label>
26 | <input type="password" id="password" name="password">
27 | <label for="confirmPassword">confirmPassword</label>
28 | <input type="password" id="confirmPassword" name="confirmPassword">
29 | <label for="age">age</label>
30 | <input type="number" id="age" name="age" min="18" max="120">
31 | <label for="score">score</label>
32 | <input type="number" id="score" name="score" max="100">
33 | </section>
34 | <section>
35 | <h2>PatternTests</h2>
36 | <label for="empty_pattern">empty_pattern *</label>
37 | <input type="text" id="empty_pattern" name="empty_pattern" required pattern=".*" data-confirm="age" data-strength="7">
38 | <label for="complex_pattern">complex_pattern *</label>
39 | <input type="text" id="complex_pattern" name="complex_pattern" required pattern="^[A-Za-z0-9!@#$%^&amp;*()_+-=[]{};':&quot;\|,.&lt;&gt;/? ]+$">
40 | <label for="email_pattern">email_pattern *</label>
41 | <input type="text" id="email_pattern" name="email_pattern" required pattern="^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+.[a-zA-Z]{2,}$">
42 | <label for="url_pattern">url_pattern *</label>
43 | <input type="text" id="url_pattern" name="url_pattern" required pattern="^(https?://)?([da-z.-]+).([a-z.]{2,6})([/w .-]*)*/?$">
44 | </section>
45 | <section>
46 | <h2>RequiredTests</h2>
47 | <label for="required_no_validation">required_no_validation *</label>
48 | <input type="text" id="required_no_validation" name="required_no_validation" required data-confirm="age" data-strength="7">
49 | <label for="required_with_pattern">required_with_pattern *</label>
50 | <input type="text" id="required_with_pattern" name="required_with_pattern" required pattern=".*">
51 | <label for="required_with_length">required_with_length *</label>
52 | <input type="text" id="required_with_length" name="required_with_length" required minlength="1" maxlength="10">
53 | <label for="required_with_default">required_with_default *</label>
54 | <input type="text" id="required_with_default" name="required_with_default" required value="test">
55 | </section>
56 | <section>
57 | <h2>DropdownTests</h2>
58 | <label for="required_dropdown">required_dropdown *</label>
59 | <select id="required_dropdown" name="required_dropdown" required>
60 |   <option value="option1">Option 1</option>
61 |   <option value="option2">Option 2</option>
62 | </select>
63 | <label for="optional_dropdown">optional_dropdown</label>
64 | <select id="optional_dropdown" name="optional_dropdown">
65 |   <option value="">Select an option</option>
66 |   <option value="option1">Option 1</option>
67 |   <option value="option2">Option 2</option>
68 | </select>
69 | <label for="dropdown_with_default">dropdown_with_default *</label>
70 | <select id="dropdown_with_default" name="dropdown_with_default" required>
71 |   <option value="option1">Option 1</option>
72 |   <option value="option2">Option 2</option>
73 | </select>
74 | </section>
75 | <section>
76 | <h2>RadioTests</h2>
77 | <label for="required_radio">required_radio *</label>
78 | <div class="radio-group">
79 |   <input type="radio" id="required_radio_1" name="required_radio" value="option1" required>
80 |   <span>Option 1</span><br>
81 |   <input type="radio" id="required_radio_2" name="required_radio" value="option2" required>
82 |   <span>Option 2</span>
83 | </div>
84 | <label for="optional_radio">optional_radio</label>
85 | <div class="radio-group">
86 |   <input type="radio" id="optional_radio_1" name="optional_radio" value="option1">
87 |   <span>Option 1</span><br>
88 |   <input type="radio" id="optional_radio_2" name="optional_radio" value="option2">
89 |   <span>Option 2</span>
90 | </div>
91 | <label for="radio_with_default">radio_with_default *</label>
92 | <div class="radio-group">
93 |   <input type="radio" id="radio_with_default_1" name="radio_with_default" value="option1" required>
94 |   <span>Option 1</span><br>
95 |   <input type="radio" id="radio_with_default_2" name="radio_with_default" value="option2" required>
96 |   <span>Option 2</span>
97 | </div>
98 | </section>
99 | <section>
100 | <h2>FileTests</h2>
101 | <label for="required_file">required_file *</label>
102 | <input type="file" id="required_file" name="required_file" required accept="*/*" data-confirm="age" data-strength="7">
103 | <label for="optional_file">optional_file</label>
104 | <input type="file" id="optional_file" name="optional_file" accept="*/*">
105 | </section>
106 | <section>
107 | <h2>NumberTests</h2>
108 | <label for="zero_range">zero_range *</label>
109 | <input type="number" id="zero_range" name="zero_range" required min="-1" max="-1" data-confirm="age" data-strength="7">
110 | <label for="positive_range">positive_range *</label>
111 | <input type="number" id="positive_range" name="positive_range" required min="1" max="10">
112 | </section>
113 | <section>
114 | <h2>DefaultValueTests</h2>
115 | <label for="empty_default">empty_default *</label>
116 | <input type="text" id="empty_default" name="empty_default" required value="" data-confirm="age" data-strength="7">
117 | <label for="space_default">space_default *</label>
118 | <input type="text" id="space_default" name="space_default" required value=" ">
119 | <label for="special_chars">special_chars *</label>
120 | <input type="text" id="special_chars" name="special_chars" required value="!@#$%^&amp;*()">
121 | <label for="unicode_default">unicode_default *</label>
122 | <input type="text" id="unicode_default" name="unicode_default" required value="测试">
123 | <label for="zero_default">zero_default *</label>
124 | <input type="number" id="zero_default" name="zero_default" required min="-1" max="-1" value="0">
125 | </section>
126 | <section>
127 | <h2>MixedAttributes</h2>
128 | <label for="complex_field">complex_field *</label>
129 | <input type="text" id="complex_field" name="complex_field" required minlength="1" maxlength="100" pattern="^[A-Za-z]+$" value="test" data-confirm="age" data-strength="7">
130 | <label for="all_optional">all_optional</label>
131 | <input type="text" id="all_optional" name="all_optional" maxlength="1000" pattern=".*" value="">
132 | </section>
133 | <input type="submit" value="Submit">
134 | </form>
135 | </body>
136 | </html>
137 | <script>
138 | document.addEventListener('DOMContentLoaded', function() {
139 |   const form = document.querySelector('form');
140 |   form.addEventListener('submit', function(e) {
141 |     let valid = true;
142 |     const errors = [];
143 | 
144 |     {
145 |       var score = document.getElementById('score');
146 |       var scoreVal = score ? score.value : '';
147 |       if (score && scoreVal !== '' && parseFloat(scoreVal) > 100) {
148 |         errors.push("Score cannot exceed 100.");
149 |         valid = false;
150 |       }
151 |     }
152 |     {
153 |       var score = document.getElementById('score');
154 |       var scoreVal = score ? score.value : '';
155 |       if (score && scoreVal !== '' && parseFloat(scoreVal) < 60) {
156 |         errors.push("Score must be at least 60 to pass.");
157 |         valid = false;
158 |       }
159 |     }
160 |     {
161 |       var age = document.getElementById('age');
162 |       var ageVal = age ? age.value : '';
163 |       if (age && ageVal !== '' && parseFloat(ageVal) < 18) {
164 |         errors.push("You must be at least 18 years old.");
165 |         valid = false;
166 |       }
167 |     }
168 |     if (!valid) {
169 |       e.preventDefault();
170 |       alert(errors.join('\n'));
171 |     }
172 |   });
173 | });
174 | </script>
```

src/Makefile
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

src/formLang
```
1 | ELF          >    @#      @       �l         @ 8  @ ' &       @       @       @       �      �                                                                                        (      (                                           �l      �l                    �       �       �      /      /                   ��      ��      ��      d      �                   �      �      �      �      �                   8      8      8      0       0                    h      h      h      D       D              S�td   8      8      8      0       0              P�td   |�      |�      |�      $      $             Q�td                                                  R�td   ��      ��      ��      P      P             /lib64/ld-linux-x86-64.so.2               GNU   �          � �                   GNU �u�ep��zR�`h��r         GNU                                � �          (��e�mfUa9�                                                  �                      �                      4                      ;                      u                      $                      Q                                            �                      �                      �                      P                      B                      �                      �                      �                      m                      K                                            |                      �                      *                      �                      _                      4                      /                      X                      f      �             �   "                        0�             �     @�              stdin perror __stack_chk_fail free fread exit getc strdup ferror clearerr fopen strlen __ctype_b_loc stdout realloc isatty atoi malloc __libc_start_main stderr fprintf __cxa_finalize sprintf memset memcpy fileno fwrite strcmp __errno_location libc.so.6 GLIBC_2.3 GLIBC_2.14 GLIBC_2.4 GLIBC_2.34 GLIBC_2.2.5 _ITM_deregisterTMCloneTable __gmon_start__ _ITM_registerTMCloneTable                                          �          ii   �      ���        ii        ���        ui	   (      ��              $      ��             �#      ��             �      ��             �      ��             !�      ��             1�      ��             6�      ��             >�      ��             D�      ��             I�       �             O�      �             X�      �             _�      �             h�       �             m�      (�             v�      0�             �      8�             ��      @�             ��      H�             ��      P�             ��      X�             ��      `�             ��      h�             ��      p�             Ơ      x�             ʠ      ��             Π      ��             Ӡ      ��             ؠ      ��             �      ��             �      ��             �      ��             ��      ��             ��      ��             	�      ��             �      ��             '�      ��             0�      ��             3�      ��             9�      ��             <�      ��             ?�       �             C�      �             G�      �             J�      �             N�       �             R�      (�             U�      0�             ]�      8�             a�      @�             e�      H�             i�      P�             m�      X�             q�      `�             u�      h�             y�      p�             }�      x�             ��      ��             ��      ��             ��      ��             ��      ��             ��      ��             ��      ��             ��      ��             ǡ      ��             ҡ      ��             �      ��             ��      ��             �      ��             �      ��             '�      ��             7�      ��             A�      ��             V�      �             �      ��                    ��                    ��                    ��                    ��                     �                    0�                    @�                     �                    �                     �                    (�                    0�                    8�                    @�         	           H�         
2 |            P�                    X�                    `�                    h�                    p�                    x�                    ��                    ��                    ��                    ��                    ��                    ��                    ��                    ��                    ��                    ��                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            ��H��H�ѯ  H��t��H���     �5ڮ  �%ܮ  @ ��h    �����f���h   �����f���h   �����f���h   ����f���h   ����f���h   ����f���h   ����f���h   �r���f���h   �b���f���h	   �R���f���h
3 |    �B���f���h   �2���f���h   �"���f���h   ����f���h   ����f���h   �����f���h   �����f���h   �����f���h   �����f���h   ����f���h   ����f���h   ����f���h   ����f���h   �r���f����%6�  fD  ���%F�  fD  ���%>�  fD  ���%6�  fD  ���%.�  fD  ���%&�  fD  ���%�  fD  ���%�  fD  ���%�  fD  ���%�  fD  ���%��  fD  ���%��  fD  ���%�  fD  ���%�  fD  ���%ެ  fD  ���%֬  fD  ���%ά  fD  ���%Ƭ  fD  ���%��  fD  ���%��  fD  ���%��  fD  ���%��  fD  ���%��  fD  ���%��  fD  ���%��  fD  ��1�I��^H��H���PTE1�1�H�=RR  �k�  �f.�     H�=��  H���  H9�tH�N�  H��t	���    ��    H�=q�  H�5j�  H)�H��H��?H��H�H��tH��  H��t��fD  ��    ���=]�   u+UH�=��   H��tH�=�  �����d����5�  ]� ��    ���w�����UH��H��H�}��ѫ  H���  H�M�H�5�v  H�Ǹ    ����������UH��H�� H�}�H�E�H������H��H������H�E��E�    �E�    �5  �E�Hc�H�E�H�� <\��   �E��E�Hc�H�E�H�� ����ttL��t��   ��rtY��r��   ��nt��n��   ��"tm��\tP�~�E�P�U�Hc�H�E�H�� 
4 | �   �E�P�U�Hc�H�E�H�� 	�   �E�P�U�Hc�H�E�H�� �~�E�P�U�Hc�H�E�H�� \�f�E�P�U�Hc�H�E�H�� "�N�E�Hc�H�E�H��E�P�U�Hc�H�E�H����&�E�Hc�H�E�H��E�P�U�Hc�H�E�H����E��E�Hc�H�E�H�� ��������E�Hc�H�E�H��  H�E�����UH��SH��8���  ����   ���     �~�  ��u
5 | �p�     H��  H��uH��  H��  H��  H��uH���  H��  H��  H��tH��  H���  H��H�H� H��u2�D  H���  H��  H�ͩ  H��H�
6 | � @  H���  H��  H�ɩ  H�E����  H�E��H�E�H�E���  �E�H�E�� ��H�H��j  ��EˋE�H�H� H��h  �f��tK�Ẻ�  H�E�H�x�  �5�E�H�H� H�Nm  ���É}��   ~�E�H�H�Pk  ��EˋE�H�H� H�yk  ����E��H�H� H��p  ��9E�u��E�H�H� H�Ek  ����E��H�H� H�kn  ���E�H�E��E�H�H� H�k  �f=� �������E�H�H� H�h  ���EЃ}� u,H���  H�E����  �E̋E�H�H� H��g  ���E�H�E�H��  H�E�H+E��  H�E�� �'�  H�E��  H�E�H��  �}�3u��Z�E�H�H��    H��q  ���t��E�    �)H���  �E�H�H�� <
7 | u�D�  ���;�  �E��q�  9E�|�룃}�4��  �E�H��    H�rr  �H�H�fr  H�>���}�  H�E��H���  H�E����  �E�������  �U  �  �K  �  �A  �!  �7  �  �-  �"  �#  �#  �  ��     �:   �  �ڦ      �;   ��  �{   ��  �}   ��  �=   ��  �$  ��  �%  �  �&  �  �'  �  �(  �  �)  �  �*  �  �+  �  �\�  ��t�N�      �  �e  H�5�  H�������H���  �  �E  ��  ��t��      �  �'  H���  H������H�X�  �  �  ��  ��t�ҥ      �  ��  H���  H���Q���H��  �  ��  ���  ��t���      �  �  H�{�  H������H�ܥ  �  �  �d�  ��t�V�      �	  �m  H�=�  H�������H���  �  �M  �&�  ��t��      �
8 |   �/  H���  H������H�`�  �  �  ��  ��t�ڤ      �  ��  H���  H���Y���H�"�  �  ��  ���  ��t���      �  �  H���  H������H��  �  �  �l�  ��t�^�      �  �u  H�E�  H�������H���  �  �U  �.�  ��t� �      �  �7  H��  H������H�h�  �  �  �  �  �  �  �  ��  �  ��  �  ��  �  ��  �  ��  �  ��  �  �  �  �  ���  ��t�~�      �  �  H�e�  H�������H�ƣ  �  �u  �  �k  �  �a  �:�  ��t�,�      �  �C  H��  H������H�t�  �  �#  H��  H������H�T�  �  �  H�Ӣ  H���+����5�  �  ��  H���  H���  H���E���H��H��  H���  H��H���y���H��  �   �  H�)m  H���!���H�a�  � ���  H�?�  �)�  Hc�H�?�  H�Ѻ   H�������N  �    �I  H��  H�U�H)Ѓ��E��+�  H�E��H��  H���  H��H�H� �@8��ubH���  H��  H��H�H� �@��  H�֡  H���  H��H�H� H���  H�H���  H���  H��H�H� �@8   H���  H�~�  H��H�H� H�P���  H�H�H�~�  H9�rtH�B�  �E�H�H�H�c�  �  �E̋Ẻ���  �E�H��  H�E�}� t(H�6�  H��H�+�  H�$�  H�E��E܉E��n���H��  H�E��f�����   ����   ����   ��t>����   ��      H���  H�ɠ  �Ϡ  �����������4�E������H�u�  �E�H�H�H���  ��  �E�H���  H�E�H�L�  H�E������H�\�  H�E�  H��H�H� H�P�M�  H�H�H�E�  �  �E�H�6�  H�E�H���  H�E�����H��j  H���  ��=�����7���H�]�����UH��SH��HH�ݟ  H�Ɵ  H��H�H� H�@H�E�H���  H�E�H���  H���  H��H�H� H�@���  Hc�H��H�H���  H9�sH�2k  H���  H�k�  H�T�  H��H�H� �@4��u+H�\�  H�%�  H)�H��u
9 | �   �  �   �  H�1�  H���  H)Ѓ��E��E�    �!H�U�H�BH�E�H�E�H�HH�M����E��E�;E�|�H�֞  H���  H��H�H� �@8��u0���      H���  H���  H��H�H� ���  �P�#  H���  H�o�  H��H�H� �@+Eȃ��E��  H�]�  H�F�  H��H�H� H�E�H�Q�  H�E�H�@H)U�H�E�@ ��tqH�E�@��EЃ}� $H�E�PH�E�@�H��H����H�E�P�H�E�@� H�E�PH�E�@��Hc�H�E�H�@H��H���  H�U�H�B�H�E�H�@    H�E�H�@H��uH��i  H���+  H�E�H�P�E�H�H�H���  H�q�  H�Z�  H��H�H� �@+Eȃ��E��}� ������}�    ~�E�    H�3�  H��  H��H�H� �@$����   �E�*   �E�    �7H� �  H��  H��H�H� H�@�U�HcʋU�Hc�H�HЋU���E��E�;E�}H���  H���I����E��}��t�}�
10 | u��}�
11 | u8H���  H���  H��H�H� H�H�E�Hc��EčP�U�H�H�HȋU���}��u"H�'�  H��������tH�hh  H����  �EĉG�  �   �q����     �5�d���� ��tH�2h  H���  �I����     H�ě  H�������H���  �E�H�H��  H�5ʛ  H��H�H�	H�q�M�Hc�H�<H��H�¾   �"������  ���  ��uH�c�  H����������b���H���  H�m�  H��H�H� �y�  �P�p�  ��uF�}� u�E�   H��  H����  �/�E�   H�4�  H��  H��H�H� �@8   ��E�    ��  �EȍH� �  H��  H��H�H� �@9���   ��  �E�ߚ  ��ЉEԋE�Hc�H���  H���  H��H�H� H�@H���  H�5��  H��H�H�H��H���^  H�CH�|�  H�e�  H��H�H� H�@H��uH��f  H����  H�L�  H�5�  H��H�H� �Uԃ��P�8�  �E�Љ-�  H��  H��  H��H�H� H�P��  H�H��  H��  H�ٙ  H��H�H� H�@��  Hc�H��H��  H���  H���  H��H�H� H�@H���  �E�H�]�����UH����  �E�H�d�  H�E���   H�E�� ��tH�E�� ��H�H��Z  ���   �E�E�H�H� H��X  �f��tK�E�Q�  H�E�H�J�  �5�E�H�H� H� ]  ���E�}��   ~�E�H�H�"[  ��E�E�H�H� H�K[  ����E��H�H� H�q`  ��9E�u��E�H�H� H�[  ����E��H�H� H�=^  ���E�H�E�H���  H9E�������E�]���UH��}�H�h�  H�E��E��E�H�H� H��W  �f��tK�E�R�  H�E�H�K�  �5�E�H�H� H�!\  ���E�}��   ~�E�H�H�#Z  ��E�E�H�H� H�LZ  ����E��H�H� H�r_  ��9E�u��E�H�H� H�Z  ����E��H�H� H�>]  ���E�}��   �����E�}� u�E���    ]���UH��SH��H�}�H�L�  H��tH�@�  H�)�  H��H�H� H��u2�w  H��  H��  H� �  H��H�
12 | � @  H����  H�H��  H��tH��  H�Ζ  H��H�H� ��    H�U�H��H���  ��   �H�]�����UH��H��H�}���  H���  H��tH���  H�s�  H��H�H� ��    H;E���   H�a�  H��tqH�U�  H�>�  H��H�H� H��tTH�H�  �9�  �H�(�  H��  H��H�H� H� �  H�PH��  H��  H��H�H� ���  �PH��  H�͕  H��H�H�E�H��   ���     ������UH��H���  H���  H��H�H� �@���  H���  H�t�  H��H�H� H�@H��  H�x�  H�A�  H�Z�  H�C�  H��H�H� H� H��  H�H�  � �7�  �]���UH��H�� H�}�u�@   ��	  H�E�H�}� uH�ma  H���  H�E��U�PH�E��@��H�H���	  H�U�H�BH�E�H�@H��uH�+a  H���O  H�E��@    H�U�H�E�H��H���   H�E�����UH��H��H�}�H�}� tvH�q�  H��tH�e�  H�N�  H��H�H� ��    H;E�uH�@�  H�)�  H��H�H�     H�E��@ ��tH�E�H�@H���	  H�E�H���	  ������UH��H�� H�}�H�u��&���� �E�H�E�H���   H�E�H�U�H�H�E��@4   H���  H��tH���  H���  H��H�H� ��    H;E�tH�E��@,   H�E��@0    H�}� tH�E�H���U�����������~�   ��    H�E�P$�����U�������UH��H��H�}�H�}� ��   H�E��@    H�E�H�@�  H�E�H�@H���  H�E�H�PH�E�H�PH�E��@(   H�E��@8    H�͒  H��tH���  H���  H��H�H� ��    H;E�u�����������UH��H��H�}�H�}� ��   ��  H�r�  H��tqH�f�  H�O�  H��H�H� H��tTH�Y�  �J�  �H�9�  H�"�  H��H�H� H�1�  H�PH��  H���  H��H�H� ��  �PH���  H��t/H��  H�ґ  H��H�H� H��tH���  H��H���  H���  H���  H��H�H�E�H���������     ������UH��H���  H����   H�r�  H�[�  H��H�H� H����   H�Q�  H��tH�E�  H�.�  H��H�H� ��    H������H��  H��  H��H�H�     H��  H��tH��  H��H�ې  H��  H��t/H�ؐ  H���  H��H�H� H��t�����Ӑ     ��]���UH��H��H���  H��uuH�E�   H�E�H��H���7  H�w�  H�p�  H��uH�]  H����  H�E�H��    H�I�  �    H�������H�E�H�)�  H��      �   H��  H��H���  H9���   H�E�   H��  H�E�H�H�E�H�E�H��    H�ُ  H��H���  H�Ǐ  H���  H��uH�T\  H���H  H�E�H��    H���  H���  H��HȾ    H������H�E�H�k�  ����UH��H�� H�}�H�u�H�}�v,H�E�H�P�H�E�H�� ��uH�E�H�P�H�E�H�� ��t
13 | �    �   �@   ��  H�E�H�}� uH��[  H���  H�E�����H�E��PH�E�H�U�H�PH�E�H�PH�E�H�PH�E��@     H�E�H�     H�E��PH�E��PH�E��@$    H�E��@(   H�E��@4    H�E��@8    H�E�H�������H�E�����UH��H��H�}�H�E�H���������H�E���H���   ����UH��H��0H�}؉uԋEԃ�H�H�E�H�E�H����  H�E�H�}� uH�[  H���   �E�    �#�E�Hc�H�E�HЋU�Hc�H�U�H�� ��E��E�;E�|ՋE�H�H�PH�E�H��  �U�Hc�H�U�H�� �H�U�H�E�H��H������H�E�H�}� uH��Z  H���   H�E��@    H�E�����UH��H��H�}�H���  H�U�H��Z  H��H�Ǹ    ������   ������UH����  ]���UH��H�ь  ]���UH��H�Ȍ  ]���UH����  ]���UH��H���  ]���UH��}��E��A�  �]���UH��H�}�H�E�H�o�  �]���UH��H�}�H�E�H�]�  �]���UH��T�  ]���UH��}��E��>�  �]���UH���ы     H�F�      H�+�      H�(�      H�5�      �3�      �-�      H�΋      H�ˋ      �    ]���UH���TH��  H��tH�׋  H���  H��H�H� ��    H���(���H���  H���  H��H�H�     ����H���  H��tH���  H�l�  H��H�H� H��u�H�f�  H���^   H�S�      ������    ]���UH��H��H�}�H�E�H���+�������UH��H��H�}�H�u�H�U�H�E�H��H����������UH��H��H�}�H�E�H�����������UH��H�� H�}�(   �����H�E�H�}� u�    �=H�E�H���)���H��H�E�H�H�E�H�@    H�E��@    H�E�H�@    H�E�����UH��H�� H�}�   �\���H�E�H�}� u�    �1H�E�H������H��H�E�H�H�E�H�@    H�E��@    H�E�����UH��H�� H�}�H�u�H�}� tH�}� u(H���  H���   �   H�JW  H���B����   H�E�@��H�H��    H�E�H�@H��H������H�E�H�}� u-H�D�  H���&   �   H�W  H��������   �����H�E�H�U�H�PH�E�H�PH�E�@H�H��H�H�E�H�H�E�@�PH�E�P����UH��H�� H�}��E�    �5H�P�  �U�Hc�H��H�H� H�U�H��H��������u�   ��E��$�  9E�|��    ����UH��H�}�H�}� tfH�E��@����H�E��@����H�E��@����H�E��@����H�E��@����H�E��@����H�E�H�@     H�E�H�@(    H�E��     ��]���UH��SH��HH�}�H�u��U�H�M�H�}� tH�}� tH�}� u(H�̇  H���   �   H��U  H���p����\  �=�  ���4�  �.�  H�H��H��H��  H��H�������H�E�H�}� u-H�i�  H���)   �   H�uU  H�������   �����H�E�H�ȇ  H���  �Ç  Hc�H��H��H�H�E�H�������H�H���  ���  Hc�H��H��H��  �BH�Eȋ@��Hc�H��H�H�H��H�H��H��H�E�H�@H��H������H�E�H�}� u-H���  H���$   �   H��T  H���D����   �*���H�E�H�U�H�PH�E�H�HH�Eȋ@Hc�H��H�H�H��H�H��H�H�E�H�E�H������H��H�E�H�H�E�U��PH�E�H��H������H�E��PH�E�PH�E��PH�E�PH�E��PH�E�P H�E��PH�E�P$H�E��PH�E�P(H�E��PH�E�P,H�E��H�E�PH�E�H�@ H��tH�E�H�@ H���c���H��H�E�H�P0H�E�H�@(H��tH�E�H�@(H���;���H��H�E�H�P8H�Eȋ@�PH�EȉPH�]�����UH��H��0H�}�H�u�H�Uؿ   �w���H�E�H�}� u%H��  H���&   �   H�yS  H�������IH�E�H������H��H�E�H�H�E�H������H��H�E�H�PH�E�H�P H�E�H�PH�E�H�U�H�P ����UH��H�� H�}��XH�E�H�@H�E�H�E�H� H��tH�E�H� H�������H�E�H�@H��tH�E�H�@H�������H�E�H�������H�E�H�E�H�}� u�������UH��H��@H�}�H�}� ��  �E�    �  H�E�H�@�U�Hc�H��H�H� H�E�H�}� ��   �E�    �   H�E�H�H�E�Hc�H��H�H�H��H�H��H�H�E�H�E�H� H��tH�E�H� H������H�E�H�@0H��tH�E�H�@0H�������H�E�H�@8H��tH�E�H�@8H��������E�H�E��@9E��n���H�E�H�@H��tH�E�H�@H������H�E�H� H��tH�E�H� H������H�E�H�������E�H�Eȋ@9E������H�E�H�@H��tH�E�H�@H���V���H�E�H� H��tH�E�H� H���;���H�E�H�@H�E��XH�E�H�@H�E�H�E�H� H��tH�E�H� H������H�E�H�@H��tH�E�H�@H�������H�E�H�������H�E�H�E�H�}� u�H�E�H�@ H������H�E�H�������E�    �?H���  �U�Hc�H��H�H� H��tH���  �U�Hc�H��H�H� H���n����E��|�  9E�|�H�h�  H��tH�\�  H���D����R�      �����UH��H��H�}�H�u�H�E�� ���tH�E��H�E��H�E��@���tH�E��PH�E��PH�E��@���tH�E��PH�E��PH�E��@���tH�E��PH�E��PH�E��@���tH�E��PH�E��PH�E��@���tH�E��PH�E��PH�E��@���tH�E��PH�E��PH�E�H�@ H��t8H�E�H�@ H��tH�E�H�@ H���F���H�E�H�@ H������H��H�E�H�P H�E�H�@(H��t8H�E�H�@(H��tH�E�H�@(H������H�E�H�@(H���A���H��H�E�H�P(�����UH��}��E�H�H��    H��z  H�]���UH��H�}�H�uЉU��E�    H�E�H� � ��H�H�NR  ����E��}����   �}� y�E�����    �E��i   +E��E��E��6   9�OE��E�E��b�U�E��H�H��S  ���9E�uA�}�t;H�}� u�E��.�E�;E�u�    �K�E�P�U�H�H��    H�E�HE��E��E�;E�|�H�}� t�}� u�}� ~
14 | H�E�� �����E�]���UH��H�}�H�u�H�E�H�E�H�E�H�E���H�U�H�BH�E�H�E�H�HH�M���� ��u�H�E�H��]���UH��H�� H�}�H�u�H�E�� <"��   H�E�    H�E�H�E�H�E�H�E�� ����\t��\'��,ta��,��"t:��'u�PH�E�H�E�� <\uC�H�}� tH�U�H�E�H�H�E�� �H�E��H�}� tH�U�H�E�H��  H�E��2끐��H�}� tH�U�H�E�H��H�������H+E��H�E�H�����������UH��H��(H�}�H�u��U��E�    H�E�@���thH�}� t�E�H�H��    H�E�H�H�E�@��E��E܍P�H�}� t
15 | H�E�H���H�E�H�M�H��H���G����E��}��u������	�E�E��E�����UH��H��pH�}�H�u�H�U�dH�%(   H�E�1�H�E�    H�E�    H�M�H�E��   H��H�������E��}��u
16 | �������  �}�w$�E�H��    H�lS  �H�H�`S  H�>��H�SR  H�E��?H�SR  H�E��2H�eR  H�E��%H��R  H�E��H��R  H�E��H��R  H�E�H�E�H���V���H�E��H�H)�H�BH�E��E�    �X�E�H��D��H�H��    H��v  H�H�ƿ    �X���H�U�H�H�E�H�E�H;E�
17 | H�E�H�E��
18 | �������   �E��E�;E�|�H�E�H� H9E�~7H�E�H� H�E�H�H�E�H� H9E�~H�E�H��������H�������   H�E�H� H�E��E�    �jH�E�� <%uUH�E�H��� <suF�E�;E�}>�E��P�U�H��D��H�H��    H��u  H�H�E�H��H���v���HE�H�E��
19 | H�E�H�E�H�E��H�EЈH�E�� ���z����    H�U�dH+%(   t���������UH��H�}��u�H�U�H�}� uH��Q  H�E��]���UH��SL��$ ���H��   H�$ L9�u�H��  dH�%(   H�E�1�ǅT���    ǅX���    Hǅ�����   H�� ���H������H������H������H�����H������H������H������ǅd�������H������H��x���Hǅ�����   ǅh���    ��z  �����H��������T�����H�������H������H�P�H������H�H9������W  H������H+�����H��H������H������'  �~  Hѥ����H������'  ~Hǅ����'  H������H������H������H��H��H�H�H�H��H�H��WH������H��ȸ��H��ȸ�� �  H������H��ȸ��H������H��H��H���[���H��ȸ��H������H������H��WH��и��H��и��H���.�袋.H��H��H��H��H��?H)�H��H��H�H�H�H��H�ȸ��H������H��H��H�H�H�H��H��H��ȸ��H������H��H��H��H������H��ȸ��H������H������H��H��H�H�H�H��H��WH��ظ��H��ظ��H���.�袋.H��H��H��H��H��?H)�H��H��H�H�H�H��H�ȸ��H�� ���H9�����tH������H���{���H������H�P�H������H�H������H������H��H��H�H�H�H��H�P�H������H�H������H������H�P�H������H�H9������A  ��T����'  ���T���H�H��I  �����\�����\������  ��w  ���u�	�����w  ��w  ����w      ǅd���    �`��w  =   u��w    ǅd���   �  ��w  ��x%��w  =,  �yw  H�H�tE  �����   ��d�����d����\�����\��� �  ��\���h�  ��\���H�H��J  ���9�d�����   ��\���H�H��I  �����\�����\��� ��\�����   ��X��� t��X�����\�����T���H������XH������H��v  H��v  H�H�XH��v  H��v  H�HH�XH��v  H��v  H�H H�X(H��v  H��v  H�H0H�X8H��v  H��v  H�H@H�XHH��v  H�PP�7v  �����w��������T���H�H�CH  �����\�����\��� �4  ���\���H�H��J  �����h����   +�h���Hc�H��H��H�H�H�H��H��H������H�H�H�XH�� ���H��(���H�HH�XH��0���H��8���H�H H�X(H��@���H��H���H�H0H�X8H��P���H��X���H�H@H�XHH��`���H��h���H�@PH��p�����\���;��  ��\���H��    H�L  �H�H�sL  H�>��H������H-  H� H�������H��t  H��t  H��uH��J  H���p  ��  H�t  H����.  H��t  H�� ����[  H������H��XH� H�������H�{t  �9  H�ot  H�`t  H��H������H�Rt      �  H�Bt      �   H�aJ  H����  H�#t      �-t  ����ǅX���    ��  H�JJ  H���  �t  ����ǅX���    �  H��s  H��uH�7J  H���x  ��  H������H-�  H� H���B�����tH�&J  H���H  ��  H������H��XH��H������H-  �H������H-�  H�0H�^s  H�������H������H-�  H� H���6�����  ǅ ���    ��  ǅ ���   ��  ǅ ���   ��  ǅ ���   ��  ǅ ���   �  ǅ ���   �  ǅ ���   �  ǅ ���   �  ǅ ���   �u  ǅ ���	   �f  ǅ ���
20 |    �W  ǅ ���   �H  H�� ���H���n����4  H������H��XH�H�XH�� ���H��(���H�HH�XH��0���H��8���H�H H�X(H��@���H��H���H�H0H�X8H��P���H��X���H�H@H�XHH��`���H��h���H�@PH��p���H������H�� ���H��H�������  H������H��XH�H�XH�� ���H��(���H�HH�XH��0���H��8���H�H H�X(H��@���H��H���H�H0H�X8H��P���H��X���H�H@H�XHH��`���H��h���H�@PH��p����  H������H�H�XH�� ���H��(���H�HH�XH��0���H��8���H�H H�X(H��@���H��H���H�H0H�X8H��P���H��X���H�H@H�XHH��`���H��h���H�@PH��p����  H������H������ǅ����   H������H������H�� ���H��(���H������H������H��0���H��8���H������H������H��@���H��H���H������H������H��P���H��X���H������H��ȹ��H��`���H��h���H��й��H��p�����  H������H�������ǅ����    H������H������H�� ���H��(���H������H������H��0���H��8���H������H������H��@���H��H���H������H������H��P���H��X���H������H��ȹ��H��`���H��h���H��й��H��p����  H������H���=���H������� ������H������H������H�� ���H��(���H������H������H��0���H��8���H������H������H��@���H��H���H������H������H��P���H��X���H������H��ȹ��H��`���H��h���H��й��H��p����Z  H������H������H������� ������H������H������H�� ���H��(���H������H������H��0���H��8���H������H������H��@���H��H���H������H������H��P���H��X���H������H��ȹ��H��`���H��h���H��й��H��p����  H������H�������H������� ������H������H������H�� ���H��(���H������H������H��0���H��8���H������H������H��@���H��H���H������H������H��P���H��X���H������H��ȹ��H��`���H��h���H��й��H��p�����
21 |   H������H������H������� ������H������H������H�� ���H��(���H������H������H��0���H��8���H������H������H��@���H��H���H������H������H��P���H��X���H������H��ȹ��H��`���H��h���H��й��H��p����#
22 |   H������H���I���H������� ������H������H������H�� ���H��(���H������H������H��0���H��8���H������H������H��@���H��H���H������H������H��P���H��X���H������H��ȹ��H��`���H��h���H��й��H��p����f	  H������H������H������� ������H������H������H�� ���H��(���H������H������H��0���H��8���H������H������H��@���H��H���H������H������H��P���H��X���H������H��ȹ��H��`���H��h���H��й��H��p����  H������H�������H������H� H������H������H������H�� ���H��(���H������H������H��0���H��8���H������H������H��@���H��H���H������H������H��P���H��X���H������H��ȹ��H��`���H��h���H��й��H��p�����  H������H������H������H� H������H������H������H�� ���H��(���H������H������H��0���H��8���H������H������H��@���H��H���H������H������H��P���H��X���H������H��ȹ��H��`���H��h���H��й��H��p����+  H������H���Q���H������H� H��菻��H������H������H������H�� ���H��(���H������H������H��0���H��8���H������H������H��@���H��H���H������H������H��P���H��X���H������H��ȹ��H��`���H��h���H��й��H��p����d  H������H������H������� ������H������H������H�� ���H��(���H������H������H��0���H��8���H������H������H��@���H��H���H������H������H��P���H��X���H������H��ȹ��H��`���H��h���H��й��H��p����  H������H�������H������H� H������H������H������H�� ���H��(���H������H������H��0���H��8���H������H������H��@���H��H���H������H������H��P���H��X���H������H��ȹ��H��`���H��h���H��й��H��p�����  H������H������H������H��XH� H������H������H��X�@��ȹ��H������H������H�� ���H��(���H������H������H��0���H��8���H������H������H��@���H��H���H������H������H��P���H��X���H������H��ȹ��H��`���H��h���H��й��H��p����  �   ����H�����H����� uH��<  H����
23 |   �O  H������H-�  H�H�����H�H������H-�   H�H�����H�PH��e  H�PH�����H�PH��e  H�����H�P�  �2   �{���H�����H�������H������H-�   H�H�����H�5Z<  H�Ǹ    萷��H�����H�� ����(  �2   �#���H�����H�������H������H-�   H�H�����H�5
24 | <  H�Ǹ    �8���H�����H�� �����  �2   �˶��H�� ���H�������H������H-�   H�H�� ���H�5�;  H�Ǹ    ����H�� ���H�� ����x  �2   �s���H������H�������H������H-�   H�H������H�5k;  H�Ǹ    舶��H������H�� ����   �2   ����H�����H�������H������H-�   H�H�����H�5;  H�Ǹ    �0���H�����H�� �����  �2   �õ��H�����H�������H������H-�   H�H�����H�5�:  H�Ǹ    �ص��H�����H�� ����p  �2   �k���H�����H������H�H������H-�   H�H�����H�5}:  H�Ǹ    ����H�����H�� ����  H�Ec  H���  H������H��XH�H������H-  H�H�c  H��H���C�����   �   �ʹ��H�� ���H������H� H�� ���H���-���H�ǅ(���   �   H������H-�   �@��H�H��    H������H-�   H� H��H���s���H�� ���H������H� H�� ���H������H��   �IHc�H��H�
25 | H��觴��H�H������H-�   �@����(���������h���Hc�H��H��H�H�H�H��H��H�������h���H�H��H�����ǅh���    H������XH������H�� ���H��(���H�H�XH��0���H��8���H�HH�XH��@���H��H���H�H H�X(H��P���H��X���H�H0H�X8H��`���H��h���H�H@H�XHH��p���H�PP��\���H�H��5  �����6��p�����p���H�H��3  ���H������� ��Љ�t�����t��� xB��t���h9��t���H�H��4  �H������� 8�u��t���H�H��3  ������p���H�H��3  �����T����������`  ���t6��`  ��x%��`  =,  ��`  H�H��.  �����   ��������d�����X��� �?  ��`  ����`  H������H��������d���������H�'5  H������H������H��x���H������H��H��������l�����l��� uH��x���H�������   ��l������   H��x���H������H9�tH��x���H��賰��H������H���t���H��x���H��x���H��t6H������H��x���H������H��H��������l���H��x���H�������#H������H��x���Hǅ�����   ǅl�������H������H����  ��l�����f  ��X�����   �%_  ���_  ����   �*  ��d���H�_  ��H��5  H���E�����^  �����g�:_  ���1_  ��h���Hc�H��H��H�H�H�H��H��H�������h���H�H��H�����ǅh���    H������� ����T�����ǅX���   ��T���H�H�0  �����\�����\����tU��\�����\��� xE��\���h<��\���H�H��1  �<u%��\���H�H��0  �����\�����\��� jH������H;�������   ��T���H�H��1  ���H��������H��4  H������H������XH������H������� ����T��������H������XH������H�{]  H�|]  H�H�XH�v]  H�w]  H�HH�XH�p]  H�q]  H�H H�X(H�j]  H�k]  H�H0H�X8H�d]  H�e]  H�H@H�XHH�^]  H�PP��\�����T����:����ǅ`���    �1���ǅ`���   �!�����H��3  H���_  ǅ`���   ���\  ���tX��\  ��x%��\  =,  ��\  H�H��*  �����   ��d�����d���H�i\  ��H��3  H��������h���Hc�H��H��H�H�H�H��H��H�������h���H�H��H������EH������� ��H�H��/  ���H��������H�:3  H���9���H������XH������H������H;�����u�H�� ���H9�����tH������H��艬��H��x���H������H9�tH��x���H���g�����`���H�U�dH+%(   t譬��H�]�����UH��H��H�}���Z  H��Z  H�U�H�5�3  H�Ǹ    袬�������UH��H�� �}�H�u��}�~MH�E�H��H� H�m3  H��H���ɬ��H�E�H�}� uH�E�H��H� H��軬���   �$H�E�H�AZ  �=���H��Z  H��������    ����UH��   ]���UH��H�� H�}�H�E�H���   �   H��2  H��菬��H�E�H���   �   H��2  H���o���H�E�H���I   �   H��2  H���O���H�Z  H�H�E�H�3  H��H�Ǹ    �z���H��Y  H�@ H�E��3H�E�H�HH�E�H�H�E�H�5�2  H�Ǹ    �B���H�E�H�@H�E�H�}� u�H�E�H���
26 |    �   H��2  H��迫��H�E�H���^   �   H��2  H��蟫��H�E�H���M   �   H��2  H������H�E�H���3   �   H�'3  H���_���H�E�H���$   �   H�?3  H���?���H�E�H���2   �   H�G3  H������H�E�H�l3  H��H�Ǹ    �T���H�E�H���>   �   H��3  H������H�E�H���   �   H��3  H���Ī��H�E�H���   �   H��3  H��褪��H�]X  H�H�E�H��3  H��H�Ǹ    �ϩ�������UH��H��H�}�H�E�H���   �   H��3  H���L��������UH��H�� H�}�H�}� uH�}3  H���3����A  H�E�H���"���H�H��H��蓩��H�E��E�    �E�    ��   �E�Hc�H�E�H�� ����>��   ��>��   ��<tU��<��   ��"t'��&u|�E�Hc�H�E�H�� &ampf�@; �E��   �E�Hc�H�E�H�� &quo�@ot; �E��`�E�Hc�H�E�H�� &lt;�@ �E��C�E�Hc�H�E�H�� &gt;�@ �E��&�E�Hc�H�E�H��E��P�U�Hc�H�E�H����E��E�Hc�H�E�H�� �������E�Hc�H�E�H��  H�E�����UH��H��`H�}�H�u�H� V  H���   �   H��1  H��褨��H�}� tH�}� u(H��U  H���   �   H��1  H���s����
27 |   H�E��@���
28 |   H�E�H���
29 |    �   H��1  H���?���H�E�H�H�E�H��1  H��H�Ǹ    �m���H�E��PH�OU  H��1  H��H�Ǹ    �H����E�    �D	  H�%U  �U�H��1  H��H�Ǹ    ����H�E�H�H�E�Hc�H��H�H�H��H�H��H�H�E�H�E�H� H���J���H�E�H�EЋ@��t	H�H1  �H��0  H�M�H�U�H�}�I��H�,1  H�Ƹ    衦��H�E�H������H�*1  H�E�H�EЋ@����   ��H��    H�u5  �H�H�i5  H�>��H��0  H�E��   H��0  H�E��   H��0  H�E��tH��0  H�E��gH��0  H�E��ZH��0  H�E��MH��0  H�E��@H��0  H�E��3H��0  H�E��&H��0  H�E��H�d0  H�E��H�W0  H�E��H�EЋ@����   H�E�H�H�E�H�H�E�H�5m0  H�Ǹ    耥��H�EЋ@(��~"H�EЋP(H�E�H�_0  H��H�Ǹ    �S���H�EЋ@,��~"H�EЋP,H�E�H�=0  H��H�Ǹ    �&���H�EЋ@��t H�E�H���	   �   H�0  H��諥��H�E�H���   �   H��/  H��若���  H�EЋ@���*  H�E�H�H�E�H�H�E�H�5�/  H�Ǹ    蠤��H�EЋ@��t H�E�H���	   �   H��/  H���%���H�E�H���   �   H��/  H������H�EЋ@��u H�E�H���-   �   H�z/  H���ڤ���E�    �TH�E�H�@P�U�Hc�H��H�H� H���h���H�E�H�M�H�U�H�E�H�5b/  H�Ǹ    �ݣ��H�E�H���A����E�H�EЋ@X9E�|�H�E�H���
30 |    �   H�C/  H���Q����  H�EЋ@���5  H�E�H���   �   H�/  H�������E�    ��   H�E�H�@P�U�Hc�H��H�H� H������H�E�H�E�H�0�E��HH�E�H�H�}�H�E�I��I��H�5�.  H�Ǹ    ����H�EЋ@��t H�E�H���	   �   H��-  H��苣��H�E�H���   �   H�.  H���k���H�U�H�E�H��.  H��H�Ǹ    蜢��H�E�H��� ����E�H�EЋ@X9E�����H�E�H���   �   H�q.  H�������:  H�EЋ@���  H�E�H���   �   H�D.  H���ע��H�E�H�H�E�H�H�E�H�5F.  H�Ǹ    ����H�E�H�H�E�H�H�E�H�5x.  H�Ǹ    �ۡ��H�E�H�H�E�H�H�E�H�5�.  H�Ǹ    赡��H�E�H�H�E�H�H�E�H�5�.  H�Ǹ    菡��H�E�H�H�E�H�H�E�H�5�.  H�Ǹ    �i���H�E�H���   �   H�^-  H��������'  H�E�H�E�H�EЋ@��
31 | uH��+  H�E�H�EЋ@��uH��+  H�E�H�EЋ@��uH��+  H�E�H�E�H�0H�E�H�H�U�H�E�I��H�5�.  H�Ǹ    �ʠ��H�EЋ@��t H�E�H���	   �   H��+  H���O���H�EЋ@��~"H�EЋPH�E�H�}.  H��H�Ǹ    �r���H�EЋ@��~"H�EЋPH�E�H�`.  H��H�Ǹ    �E���H�EЋ@��uZH�EЋ@ ��t"H�EЋP H�E�H�7.  H��H�Ǹ    ����H�EЋ@$��t"H�EЋP$H�E�H�.  H��H�Ǹ    �ߟ��H�E�H�@0H��tNH�E�H�@0� ��t?H�E�H�@0H������H�E�H�U�H�E�H��-  H��H�Ǹ    萟��H�E�H�������H�E�H�@8H��t?H�E�H�@8H�������H�E�H�U�H�E�H��-  H��H�Ǹ    �D���H�E�H��訞��H�EЋ@��	u H�E�H���   �   H�]-  H��輟��H�EЋ@��u-H�E�H�@8H��t H�E�H���   �   H�2-  H��胟��H�E�H�@@H��t#H�E�H�P@H�E�H�-  H��H�Ǹ    裞��H�EЋ@H��~"H�EЋPHH�E�H��,  H��H�Ǹ    �v���H�E�H���   �   H��)  H������H�EЋ@��u-H�EЋ@H��~"H�E�H�H�E�H��,  H��H�Ǹ    ����H�L  �U�H��,  H��H�Ǹ    ������E�H�E��@9E������H�E�H���   �   H��,  H���x���H��K  H���   �   H��,  H���U���������UH��H��@H�}�H�u�H�U�H�M�H�E�H�E��H�E�H�E�� ��t(�E���H�H�E�� H��H�H�� ��%    ��u��E�    �$H�E�H�PH�U��U�J�M�Hc�H�U�H�� �H�E�� ��tX����H�H�E�� H��H�H�� ��%    ��u0H�E�� <<t%H�E�� <>tH�E�� <=tH�E�� <!�y����E�Hc�H�E�H��  �H�E�H�E�� ��t(�k���H�H�E�� H��H�H�� ��%    ��u��E�    H�E�� <<t!H�E�� <>tH�E�� <=tH�E�� <!umH�E�H�PH�U��U��J�M�Hc�H�U�H�� �H�E�� <=tH�E�H��� <<u/H�E�� <>u$H�E�H�PH�U��U��J�M�Hc�H�U�H�� ��E�Hc�H�E�H��  �H�E�H�E�� ��t(聜��H�H�E�� H��H�H�� ��%    ��u��E�    �$H�E�H�PH�U��U�J�M�Hc�H�U�H�� �H�E�� ��uыE�Hc�H�E�H��  �����UH��H��   H��X���H��P���dH�%(   H�E�1�H��X���H���	   �   H�(*  H��蔛��H��X���H���;   �   H�*  H���q���H��X���H���/   �   H�.*  H���N���H��X���H���0   �   H�;*  H���+���H��X���H���   �   H�I*  H������H��X���H���   �   H�=*  H������H��P���H�@H��`����  H��`���H� H�M�H��l���H��p���H���Z���H��X���H���   �   H��)  H��臚��H��p���H��p���H��X���H�5�)  H�Ǹ    讙��H��p���H��p���H��p���H��X���I��H�5�)  H�Ǹ    �{���L��l���H��p���H��p���H��p���H��X���H��H�u�VM��I��H�5�)  H�Ǹ    �5���H��H��`���H�PH��X���H��)  H��H�Ǹ    ����H��X���H���   �   H��)  H��蕙��H��X���H���   �   H��)  H���r���H��X���H���   �   H��)  H���O���H��`���H�@H��`���H��`��� �a���H��X���H���   �   H�\)  H������H��X���H���   �   H�L)  H������H��X���H���    �   H�F)  H���Ƙ��H��X���H���   �   H��(  H��裘��H��X���H���   �   H�!)  H��耘��H��X���H���   �   H�)  H���]���H��X���H���
32 |    �   H��(  H���:����H�E�dH+%(   t�E�������UH��H�� H�}�H�LE  H���   �   H��(  H������H��E  H��tH�}� u(H�E  H���   �   H��(  H��躗���c  H��D  H���   �   H�y(  H��蒗��H�E�H�������H�E�H���   �   H�`(  H���f���H�E  �PH��D  H�H(  H��H�Ǹ    莖���E�    �OH�nD  �U�H�6(  H��H�Ǹ    �d���H��D  H�@�U�Hc�H��H�H�H�E�H��H�������E�H��D  �@9E�|�H�E�H���%   �   H��'  H��跖��H�E�H���   �   H��'  H��藖��H�E�H������H�DD  H�E�H��H������H��C  H���   �   H��'  H���R�������H��H���                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       3 1   1 1 1 / 	 
33 |     . . . . . . . . . . . . . . . .  1     0    /    . . . . . . . . . . .  . . . . . . . . . . . . . .  . . . . . . . . . . . . % . $ . . . . . . . . . . . . . . ' .  . . . . .   .  . . . . . . . & . .  . . . . . . .    . . . . . .  . . . . . . . . . . . . .  . . . . . . . . . - . + ) . . . . . ( .  . . . .   . . !    ,  *  # "                                  	
34 |  !"#$%&'()                             � � � � � % � � � � � � �   �     � % � � � & # � � � � � � � 3 � � � � � � �   � � $ � � � � � ' �   � � � � � % � � � � � � � � � � � � � � � � � � � �  � � � � } s q z n o m z k l s v p   p   d s k d p     n   m l b Y i _ c   b ] h [ c T c S X T       T S N Q O K   J L R G V U C F G ? ; I H   M < ? F = 6 C ; 3   .     7 0 / 6 <   ;   6 < 7 6     - (                   � G -                             �  � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � �   � �                                  	 
35 |                                   ! " % . 0 3 5 , 1 / 4 6 & 8 > A % 9 ? P 2 : I � J Q & @ � B X Y $ $ � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � �  ~ } | { z y x w v u t s r q p o n m l k j i h g f e d c b a ` _ ^ ] \ [ Z W V U T S R O N M L K H G ( � F E D C = < ; 7 - + * ) ( ' # �  � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � �                                                                   �         $   5   / � / 5 $  �  = = � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � �  ~ } | { z y x v u t s r q p n k j i h g e c b a ` _ ^ ] \ [ Z Y X W V U T S R Q P O N M L K J I H G E D C B A @ ? > < ; : 9 8 6 4 3 2 1 0 . - ( & !            
36 |  	   � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � �                                                                                                                                                                                                                             Syntax error at line %d: %s
37 |  Unexpected character   fatal flex scanner internal error--no action found  �������ƍ��Ѝ��ڍ������������������ ���4���>���H���R���\���f���p���z��������������������������\�������؏�����T�������А��������"���,���6���@���J���T���^���h���r�����������đ�����"���A�����������ܒ��Ғ��fatal flex scanner internal error--end of buffer missed fatal error - scanner input buffer overflow input in flex scanner failed        out of dynamic memory in yy_get_next_buffer()   out of dynamic memory in yy_create_buffer()     out of dynamic memory in yyensure_buffer_stack()        out of dynamic memory in yy_scan_buffer()       out of dynamic memory in yy_scan_bytes() bad buffer in yy_scan_bytes() %s
38 |                               Null form or section
39 |    Memory allocation failed for sections
40 |  Null section, name, or attrs
41 |     Memory allocation failed for field names
42 |        Memory allocation failed for fields
43 |     Memory allocation failed for metadata
44 |    510234./	
45 |  !"#$%&'()*+,-"end of file" error "invalid token" FORM SECTION FIELD TEXT EMAIL PASSWORD NUMBER TEXTAREA DATE CHECKBOX DROPDOWN RADIO FILE_TYPE USERNAME ADDRESS REQUIRED OPTIONAL MINLENGTH MAXLENGTH MIN MAX ROWS COLS PATTERN DEFAULT CONFIRM STRENGTH META IDENTIFIER NUMBER_LITERAL STRING_LITERAL VALIDATE IF ERROR LT GT LTE GTE EQ NEQ AND OR OPTIONS '{' '}' ';' ':' '=' '[' ']' ',' $accept form form_body form_item section $@1 field_list field_declaration field_type field_attributes attribute_opt_semicolon attribute validation_block validation_rules validation_rule condition metadata_declaration options_list                               ���������������	���������!��"#$%&��������'*����������������� ()+,-./01��4356789;�2E������������F���G�                    /   
46 |   .0 9    	        2345867     1  !                      "#$%&'(*),+ : - ;          ������������������               $DHWX r              !"IJKLMNOPQRST%&'()*lm	UV23st
47 | #89:;<=>?@ABC+,-5./01467EGpYF   nZe fghij[\k]^_`abcdo qu                       #%&'()*! /."-/ 452.!////.	
48 | 0.0$     1!0/32.���2 �     22!22222220 �!!                        7 .8"/9:BF..2C//;!#/D<0E/=%&'()*.0      $1!	
49 | >0./?-/@A222222222220      !! 3!G45!           6788999;:::<<<=>>>>>>>>>>>>??@@AAAAAAAAAAAAAABCCDEEEEEEEFGG          syntax error syntax error, unexpected %s    syntax error, unexpected %s, expecting %s       syntax error, unexpected %s, expecting %s or %s syntax error, unexpected %s, expecting %s or %s or %s   syntax error, unexpected %s, expecting %s or %s or %s or %s ������������ͬ��ڬ�����Deleting Failed to create form Invalid section declaration Invalid field declaration        Field must be inside a section Duplicate field name found       Memory allocation failed for validation rule %s < %d %s > %d %s <= %d %s >= %d %s == %d %s != %d %s == %s Error: discarding Error: popping memory exhausted Cleanup: discarding lookahead Cleanup: popping  K���K�������K���K���K���K���K����������?���O���K���K�����������S���b���q�����������������������˵��ڵ�������������������D���ȷ������8�����������o���,����������e���$����������g���K���K���K���>�������'����������/�����������8���}�������Parser Error: %s at line %d
50 |  r      <!DOCTYPE html>
51 | <html>
52 | <head>
53 |    <meta charset="UTF-8">
54 |           <meta name="viewport" content="width=device-width, initial-scale=1.0">
55 |    <title>%s</title>
56 |    <!-- %s: %s -->
57 |    <style>
58 |         body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }
59 |       fieldset { margin-bottom: 20px; padding: 15px; border: 1px solid #ccc; }
60 |        legend { font-weight: bold; padding: 0 10px; }
61 |          .field { margin-bottom: 15px; }
62 |         label { display: block; margin-bottom: 5px; }
63 |           input, textarea, select { width: 100%%; padding: 8px; margin-bottom: 5px; }
64 |             .error { color: red; font-size: 0.9em; margin-top: 5px; }
65 |    </style>
66 |  </head>
67 | <body>
68 |       <form id="%s" onsubmit="return validateForm()">
69 |  </body>
70 | </html>
71 |   Starting section generation
72 |  Null section or output
73 |  <section>
74 |  <h2>%s</h2>
75 |  Processing %d fields
76 |  Generating field %d
77 |   * <label for="%s">%s%s</label>
78 |  text email password number textarea date checkbox select radio file <textarea id="%s" name="%s"  rows="%d"  cols="%d"  required ></textarea>
79 |  <select id="%s" name="%s" >
80 |     <option value="">Select an option</option>
81 |      <option value="%s">%s</option>
82 |  </select>
83 |  <div class="radio-group">
84 |    <input type="radio" id="%s_%d" name="%s" value="%s"   <span>%s</span><br>
85 |  </div>
86 |  <div class="address-group">
87 |        <input type="text" id="%s_street" name="%s_street" placeholder="Street" required>
88 |       <input type="text" id="%s_city" name="%s_city" placeholder="City" required>
89 |     <input type="text" id="%s_state" name="%s_state" placeholder="State" required>
90 |  <input type="text" id="%s_zip" name="%s_zip" placeholder="ZIP" required>
91 |        <input type="text" id="%s_country" name="%s_country" placeholder="Country" required>
92 |    <input type="%s" id="%s" name="%s"  minlength="%d"  maxlength="%d"  min="%d"  max="%d"  pattern="%s"  value="%s"  accept="*/*"  checked  data-confirm="%s"  data-strength="%d"  <meter id="%s_strength" min="0" max="4"></meter>
93 |        Field %d generated successfully
94 |  </section>
95 |  Section generation complete
96 |    ��������������������������������������%���2���<script>
97 |    document.addEventListener('DOMContentLoaded', function() {
98 |        const form = document.querySelector('form');
99 |    form.addEventListener('submit', function(e) {
100 |      let valid = true;
101 |      const errors = [];
102 | 
103 |      {
104 |        var %s = document.getElementById('%s');
105 |         var %sVal = %s ? %s.value : '';
106 |         if (%s && %sVal !== '' && parseFloat(%sVal) %s %s) {
107 |          errors.push("%s");
108 |          valid = false;
109 |        }
110 |      }
111 |      if (!valid) {
112 |        e.preventDefault();
113 |          alert(errors.join('\n'));
114 |    });
115 |  });
116 |  </script>
117 |  Starting HTML generation
118 |  Null form or output
119 |  Generating header
120 |  <form>
121 |  Processing %d sections
122 |  Generating section %d
123 |         <input type="submit" value="Submit">
124 |  </form>
125 |  HTML generation complete
126 |     ;   C   �k��T  4m��|  Dm���  �n��<  �o���  �o���  �q���  #|��  x���4  ����T  ����t  b����  Y����  ����  �����  ���  ڈ��8  {���X  ����x  f����  �����  �����  ԍ���  ����  ���4  ����T  ���t  ����  .����  ?����  V����  p���  ����4  ����T  ����t   ����  ͐���  ����  ����  3���  ����4  ����T  ���t  D����  �����  {����  ����  ����  ���8  a���X  ����x  �����  ߜ���  Ý���  Z����  ����	  ݠ��8	  ����\	  5���|	  �����	  �����	  ����	  ;����	  ����
127 |   4���<
128 |   ����\
129 |   a���|
130 |          zR x�        �l��&    D    $   4   Hi���   FJw� ?9*3$"       \   �j��              t   �j���             �   �l��8    E�Co      �   m���   E�C�     �   �n���
131 |    E�CE��
132 |       �   y��U   E�CE�G       <��2   E�C)    4  N���   E�C�      T  4����    E�CE��      x  ���    E�C�     �  �����    E�C�     �  ����    E�C�     �  �����    E�C�     �  �����    E�C�       �����    E�C�     8  ���   E�C�     X  ����    E�C�     x  Ɔ��=   E�C4    �  ���   E�C�     �  ƈ��.    E�Ce      �  Ԉ���    E�C�     �  ����<    E�C        ����    E�CG      4  ����    E�CH      T  ����    E�CH      t  ����    E�CG      �  r���    E�CH      �  c���    E�CN      �  Z���    E�CQ      �  T���    E�CQ        N���    E�CG      4  >���    E�CN      T  5���o    E�Cf     t  �����    E�C�     �  ���    E�CU      �  ���)    E�C`      �  ���    E�CV      �  ���k    E�Cb       b���_    E�CV     4  �����    E�C�     T  h���`    E�CW     t  ����|    E�Cs      �  ����   E�CE��     �  �����    E�C�     �  ���u    E�Cl     �  m����   E�Cw      ͑��T   E�CK    8  ���%    E�C\      X  ���   E�C�     x  ���Q    E�CH     �  ����    E�C�     �  ����    E�C�     �  Z���[   E�CR    �  ����(    E�C_         ����     E�Ca��     <  ����8    E�Co      \  �����    E�Cx     |  ���    E�CF      �  ���C   E�C:    �  $���3    E�Cj      �  7���n   E�Ce    �  �����
133 |    E�C�
134 |       ����m   E�Cd    <  =����   E�C�    \  �����   E�C�                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          $      �#      �      �      !�      1�      6�      >�      D�      I�      O�      X�      _�      h�      m�      v�      �      ��      ��      ��      ��      ��      ��      ��      Ơ      ʠ      Π      Ӡ      ؠ      �      �      �      ��      ��      	�      �      '�      0�      3�      9�      <�      ?�      C�      G�      J�      N�      R�      U�      ]�      a�      e�      i�      m�      q�      u�      y�      }�      ��      ��      ��      ��      ��      ��      ��      ǡ      ҡ      �      ��      �      �      '�      7�      A�      V�                     �                             ��             ��                           ��                    ���o    �                           �      
135 |        y                                          ��             @                           �              	             �      	                            ���o          ���o    �      ���o           ���o    z      ���o    K                                                                                       �                      0       @       P       `       p       �       �       �       �       �       �       �       �        !      !       !      0!      @!      P!      `!      p!      �!      �!      �!                                                              �         GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0 ,             )$      �!                      ,    �       �E      �0                      ,    A1       Av      o                      �       &�      	   )$      �!          �	  �:   	�  	�  'H   	�  	)	  	�  �   &O   `  '|   	,  e	  )�   (int 	�  �  ��   �  ��   �   	�  
136 | �   �  �1M    3�    3  6	�   �  7	�   R  8	�   e   9	�    I	  :	�   (J  ;	�   0�  <	�   8�  =	�   @z   @	�   Hj  A	�   P(   B	�   XL  Df  `�   Fk  h�  H�   p*  I�   t�  J�   x�   MV   �k  N]   �z  Op  �t   Q�  ��  Y�   �   [�  ��  \�  ��  ]k  ��  ^	H   ��  _
137 | .   �  `�   ��  b�  � �	  �   )�  +  a  �   �   �  :     Y     �  �  �  �   �  :    �   �  @  ��  M  �  <	  ��  %  ��  	�  b  p   g	  �   	�      *�   	d     ,  r  -�  
138 | *  =  /�  
139 | ;  �   �!X  ]  �  @�  O  ��   �   ��   �	  ��   �  ��   �   ��   w  ��    5   ��   $X  ��   (�  �	�   ,�  �	�   0�  ��   4�  ��   8 �	  �.   �  ��   �  ��  q  ��  
140 |   .   	��      �  .   	��      8  y  	��      L  �  �   	��      �    �   	��        !	P�      �  $�   	��      �  %�   	��        &�   	��      o	  +�   	��       �  [  
141 |     ]	X�      ++  ]	`�       �  _�   �  a�   T  b	�      g  d�   6  �  :   � 
142 | ~  6  ��  	 �         �  :   � 
143 | �  �  ��  	��         �  :   ) 
144 | �    ��  	��      6    :   � 
145 | �     �  	 �      �  �  	��      6  P  :   � 
146 | @  �  �P  	@�      �   P  	@�      G  �  :   2 
147 | �  q  7�  	@�      �  =H  	��      �   >�   	��      <  @�   �  A	h�      r  J	p�        
148 | 	=  key 
149 | 
150 | �    �  
151 | �   �	  
152 | =       
153 |   b  
154 | �  U  
155 | �    <  
156 | �   �	  
157 | �   N  b  
158 | N  ,A   
159 | �  J   w  	  �      b  V   s  �	  	@  
160 | W	   �  
161 | $�  (
162 | '	B  �  
163 | (�    �   
164 | )�   �  
165 | *�   zip 
166 | +�   �   
167 | ,�       
168 | -�  X
169 | 0		  �  
170 | 1	�    %  
171 | 2	�   �  
172 | 3	�   g  
173 | 4	�   �  
174 | 5	�   �  
175 | 6	�     
176 | 7	�   #   
177 | 8	�   �  
178 | 9�    �	  
179 | :�   (D  
180 | ;�   0�  
181 | <	�   8�	  
182 | =	  @.  
183 | >	�   H<  
184 | ? 	  P �   B  R  
185 | @N  �  h
186 | Cf	  H  
187 | D�    8  
188 | E�  �  
189 | F%	   �  
190 | G1	  J  
191 | I�	  H  
192 | J�    l  
193 | K�	    
194 | L	�    f	  J  
195 | Mr	  �  (
196 | O
197 |   H  
198 | P�       
199 | Q
200 |   �  
201 | R	�   U
202 |   
203 | S
204 |   -
205 |   
206 | T
207 |     
208 |   �	  �  B  �  
209 | U�	  
210 |   �P
211 |   arr �	   $  ��    -�  X��
212 |   6  �'
213 |   E  �
214 |   �  ��	    �%	    �
215 |   !str ��   !num �	�   2  ��  �  �,
216 |    �  �P
217 |   �  ��
218 |   .  �   	x�      "�  �  H    4  �H     H   .    /�	  �0  �    H  =H   P  H   �   .      )�   g  �    �  s�   ~  �   C	  �.   �  J   .   .   �   "�   \�  �   0�  %�  �   `  `�   �  �   �  @�   �  �   �	  �.       .   .   �   �   i�   1  �   �  ��   G  �   �  �H   ^  .    �  �.   u  �     e�   �  �  �  1 �  ��E             ��  ptr �H   �h 2  �H   gE      )       �  ptr �H   �h�  �*  �` U  �H   IE             �3  �  �  �h 2]  {�   �D      �       �3�  [�   -D      o       ��  VD             ��  �	  V�   �l �  Q�   D             ��  L�C             ��  �  L�  �h �  G�C             �  �  G�  �h �  ;�C             �C  U  ;�   �l �  2�   �C             �(  )�   �C             ��  !�  �C             �%  �  xC             ��  �   hC             �4�  �,C      <       �  msg �4�  �h �  �L  PB      �       �  �  �.�  �H�	  �<�   �Db �L  �hbuf ��   �`n �  �Xi ��   �T G   �L  "B      .       ��  "  �.�  �h �  �L  A            ��  [  �)�   �X�  �:  �Pb �L  �h #  o�?      =      �N  �  q  �h�@      �       ]  �  �`  5$  \�>      �       �  >�=            ��    >+L  �h �  !
219 | V=      �       ��  b !,L  �h #�  �<      �       �  b 3L  �XX  =�  �P	  �   �l O  �
220 | <      �       �9  b �-L  �h b  �L  d;      �       ��  X  �/�  �X�  �:�   �Tb �L  �h 6�	  ��:      �       ��  �
221 | �9      �       ��    �1L  �h �  �
222 | ,9      �       ��  R  ��  �X $�  )H  &8            �\  		  );H  �\   +�   �d�  ,�   �h7  .
223 |   �c $�  	H  �6      2      ��  		  H  �d�  �   �h7      �       7    �c  7�  �   �0      U      ��  '  ��   �H  ��   �P    ��   ��i ��   ���  ��   ��2      #      �  �   ��   ��,2            �  b �L  �X�  ��   ��h2      o       n  �	�   �@  y3      �       c ��   ��n ��   ��  �5      �       n  ��   �D  �  -�   &      �
224 |       �  		  /H  ���  0�   �P�  0�   �X�  1�   �@�  `�&      �  t(      z  ��(      �&      �       �  7  c  �� �(      =       �  yyl ��   �D 8   �	  ��   �H'/      t       *  H  �L   9.  �   a$      �      �[  :F  "�  �X;�  �   �h%i 	�   �`%j �   �d <  )$      8       �=msg �  �h  �   (  /�  F  	   �E      �0      `  �	  �:   �  �  0�  )	  �  ,  1int f   �  �  �r   �  �r   �   �  �   �  �1)    3f    3  6	�   �  7	�   R  8	�   e   9	�    I	  :	�   (J  ;	�   0�  <	�   8�  =	�   @z   @	�   Hj  A	�   P(   B	�   XL  DB  `�   FG  h�  Hf   p*  If   t�  Jy   x�   MQ   �k  NX   �z  OL  �t   Q\  ��  Y�   �   [f  ��  \p  ��  ]G  ��  ^	H   ��  _
225 | .   �  `f   ��  bu  � �	  �   2�  +  =  �   �   \  :     5     a  �  k  �   �  :    �   �  �  )  �  <	  ��  %  ��  �  �    	�  key 
226 | �    �  �   �	  �   �    �  b  ?  U  �    <  �   �	  ?   
227 |   b  
228 |   3A   �  J   w  	  �      b  V   s  �	  	@  
229 | W	   �  $P  ('	�  �  (�    �   )�   �  *�   zip +�   �   ,�       -�  X0	�  �  1	f    %  2	f   �  3	f   g  4	f   �  5	f   �  6	f     7	f   #   8	f   �  9�    �	  :�   (D  ;�   0�  <	f   8�	  =�  @.  >	f   H<  ?�  P �   �  R  @
230 |   �  hC"  H  D�    8  E�  �  F�   �  G�  J  Ic  H  J�    l  Kc    L	f    "  J  M.  �  (O�  H  P�       Q�  �  R	f   U
231 |   S�  -
232 |   T�    �  h  D  �  �  Ut  �  Xf   �  \�    _  �  3  `�  �  	��        
233 | 	��      	^  H  �    �  	f    �  :   �    	��      ^   �  f   	��      ��  arr ��   $  �f    !�  X�-  6  �  E  ��  �  �c    ��    ��  "str ��   "num �	f   2  ��  �  ��   �  ��  4�  �-  5l
234 |   f   �	  #�  N   :    M  �  I  �
235 |   �  �
236 |   J  	%  
237 | �  �
238 |   e  �  �  Z  +  �  �
239 |   �  
240 |   �  �
241 |   �  %  �  �  
242 |     �  X  ;   �  !�
243 |   "�  #4  $  %�  &�  '4  (�  )  *�  +�  ,�  -�  .  /�  0   1�  2�  3�  4-  5s  6-  7Z  8!  9<  :�  ;�  <g  =)  >�  ?,  @�
244 |   Aa  BL
245 |   C  DL  Ek  Fp  G l
246 |   F  B  ,X   	  6
247 |   �	  �  �f   !U  Xi	  $�  ,	  $�   -   '	  z	  6:   , i	    oz	  	��      �  �	  :   H �	  �  ��	  	��      '	  �	  :   u �	  i  ��	  	��      �
248 |   ��	  	 �      '	  
249 |   :    
250 |   �  �
251 |   	��      �  �
252 |   	��      '	  X
253 |   :   h H
254 |   ,  X
255 |   	��      �  X
256 |   	@�      �  !�	  	��      '	  �
257 |   :   ; �
258 |   �  2�
259 |   	@�      �  =�
260 |   	��      %f   H�
261 |   #�   7�	  &�  �   &�  �	   ,	  �   �
262 |   "  '�  f   	��      89  !		��      'l  #f   	8�      (}  n�  �   e  �  �  �  �     ef   �  �  �  ) �  mf   �  �   �  ) 9�  c�  �   :�  Yf   �  	�.     �   (�  
263 | �  H    *�  �f   8  �  �   ;�	  
264 | �K  f    4  
265 | �H   g  H   .    *�  ��   |  �   �  
266 | �H   �  .    <�  �f   2v             �+�  �f   �u      �       �  �  �f   �\�  ��  �P
267 | �u      M       X  ��  �h  =u  �yu      8       �F  >s ��  �h +�  -f   YU              ��  ]  /8	  ���~�  1	f   ���~�  7r   ���~�  :�  ��~�  ;  ���~�  <  ���~�  ?�  ���~�
268 |   @�  ���~�  A�  ���~yyn Cf   ���~�  Ef   ���~�  G	  ���~|
269 |   J-  ���~A  M�  ��}�  N	�   ���~L  Or   ���~f
270 |   Uf   ���~M  j)V      A
271 |   a!V      K  W	t      �  O	�s      �  G	�s      �  ��X      [  �Z      �  	`r      �  �p      C  �Z      X  	�q      {  `	%t      ?#   �    xr   ���~,3     �  ���~�  �  ���~�V      �       �  �  �	r   ���~ 
272 | uW      �       �  �	r   ���~   `      �         tmp [%�  ���~ �`      �       ;  tmp \%�  ���~ ta      �       c  tmp ]6�  ���~ 1b      �       �  tmp ^6�  ���~ �b      �       �  tmp _0�  ���~ �c      �       �  tmp `0�  ���~ hd      �         tmp a1�  ���~ %e      �       +  tmp b1�  ���~ �e      �       S  tmp c4�  ���~ �f      �       {  tmp d4�  ���~ `g      �       �  tmp e0�  ���~ 'h      �       �  tmp f5�  ���~ �h      �       �  tmp g0�  ���~ �i      �         tmp i�  ���~ zj      �       C     ��  ���~ k      S       k  �  ��   ���~ ck      S       �  �  ��   ���~ �k      S       �  �  ��   ���~ l      S       �  �  ��   ���~ kl      S         �  ��   ���~ �l      S       3  �  ��   ���~ m      T       [  �  ��   ���~ Uo      �       �  c  �m   ���~yyi �m   ���~ ,>   C  �"  ���~�  ��  ���~  �f   ���~  ,	  �  :   � -  �  :   � -  �     :    D	  @7  1U      (       �\  �  �  �h�  	  �d�
273 |   .�  �X   �f   �R      [      ��  L  ��  ���  �2�  ��C  �%�  ��%A   ��     �  ��  ���  ��  �P  �r   ���  �f   ���S      i       P  yyi �	f   ��
274 | �S      T       m  �r   �H  
275 | |T      �       yyp ��   �@yyi �	f   ��  r   .  	  �  :    �  �f   ?R      �       �"  C  �0�  �X�  �,"  �P�  �9f   �L�  �f   �h
276 | iR      h       yyn �f   �l  	  �  Zr   [Q      �       ��  �  Z�   �X"  Z%�  �PS  yR      �  m�Q      
277 | ~Q      �       yyn ^r   �`yyp _�  �h  �  D�   
278 | Q      Q       �  %  D�   �X  D%�  �Pyyd F	�   �`yys G�  �h l  	f   P            ��  C  	1�  �H�  
279 | -"  �@�  
280 | :f   ���  f   �Xyyn f   �`
281 | FP      �       X  f   �d�  f   �h�  f   �lyyx f   �\  �  ��  �O      %       �  _  � 	  �l �  ĉN      T      �M  	'  �.M  �h-src �EM  �` �    �	L      �      �\  	6  �  ��$L      �      =     ��  �P$L      )        i �f   �D
282 | 0L      	      s ��  �`
283 | WL      �       j �f   �H
284 | cL      ~       f �c  �h    
285 | �M      X       �	  ��  �X  
286 | N      S       i �f   �L    ��K      u       ��  	-
287 |   �!�  �X
288 | �K      X       �	  ��  �h  )
289 |   ��J      �       ��  	6  �  �X-key �+�  �P	�  �<�  �H  ��  �h w  R<H      �      �  	E  R$�  ��	H  R9�  ��	8  RI�  ��		  R`M  ���  Z  �Hh  dc  �P�  kc  �X A�  E�G      |       ��  		  E-M  �h .�  <f   `G      `       ��  	H  <'�  �X
290 | pG      I       i =f   �l  �  ,yF      �       �A  	6  ,   �X	E  ,/�  �P  2�  �h .=  #
291 | �  F      _       �  	H  #%�  �XE  $�  �h B    �E      k       �	H  �  �X6    �h  �
292 |    �  �  N  	   Av      o      J  �	  �:   �  �  �  )	  Q   �  ,  int �  �  �r   �  �r   �   �  �   �   �   :    �  �19    3k    3  6	�   �  7	�   R  8	�   e   9	�    I	  :	�   (J  ;	�   0�  <	�   8�  =	�   @z   @	�   Hj  A	�   P(   B	�   XL  DR  `�   FW  h�  Hk   p*  Ik   t�  Jy   x�   MQ   �k  N]   �z  O\  �t   Ql  ��  Y�   �   [v  ��  \�  ��  ]W  ��  ^	H   ��  _
293 | .   �  `k   ��  b�  � �	  �   �  +  M  �   �   l  :     E     q  �  {  �   �  :    �   �  9  �  %  ��  �  �  X   A   /$  
294 | �   
295 | �   
296 | y   
297 |    
298 | �   
299 | 7    
300 | g   @
301 | p   ��  �  ^  �     	W  key 
302 | �    �  �   �	  W   $    $  b  �  U  �    <  �   �	  �   h  b  h  A     J   w  	  �      b  V   s  �	  	@  
303 | W	   �  $�  ('V  �  (�    �   )�   �  *�   zip +�   �   ,�       -  X0-  �  1	k    %  2	k   �  3	k   g  4	k   �  5	k   �  6	k     7	k   #   8	k   �  9�    �	  :�   (D  ;�   0�  <	k   8�	  =-  @.  >	k   H<  ?2  P �   V  R  @b  �  hCx  H  D�    8  E  �  F7   �  GC  J  I�  H  J�    l  K�    L	k    x  J  M�  �  (O  H  P�       Q  �  R	k   U
304 |   S#  -
305 |   T(      �  �  \  �  U�    _D  -  �  O#U  �  �  	�m  H    �  	�H   �  .    �  
306 | �.   �  �   �  
307 | ��   �  �     ek   �  �  �    �  �݊      �      �  �  ��  �X	      g       i �k   �l  t  ��      �      ��  �  �#�  ��~6  �1D  ��~   �#  ��~	2�      �      �  ��  ��~op ��   ��~�  � �  ��  �   �  :   ? !�  ���      m      �8  �  �)�  �H�  �5�   �@"op �B�   ���  �L�   ��p ��  �hi �	k   �\j �	k   �`k �	k   �d �  8%z      �
308 |       ��	  �  8"�  ��E  83  ��	{      `	      i Hk   ��	{      @	      �  J�  �@@  M�   �H8  R�  ��&~      i       	  i ok   ��	/~      P       �  p�   �h  �~      �       R	  i wk   ��	�~      �       �  x�   �`  	�      '      �  ��  ����      ?       �	  �  ��   �P 	ق      ?       �  ��   �X     #M  %�   �x      n      �#
309 |   F  %$�  �X�  (�   �hj )	k   �`	y            i +k   �d    !�x      3       �N
310 |   �  !!�  �h $"  Av      C      ��  !�  �X  (  �h   :;9I8  4 :!;9I   I   :;9I   !I   :!;9I  (   4 :!;9I  	$ >  
311 | & I  .?:;9'I<  I  ! I/  :;9  4 :;9I?<   :!;9I  .?:!;9'I@|  .?:!;9'@|   :!;9I  . ?:!;9'I@z    4 G;9  7 I  .?:!;9!'@z     <  4 :!;9I?<   :;9I8  :;9  .?:;9'I<  
312 |  :!;9!    :!;9I  ! :!;9I  ".?:;9!'<  #.:!;9'@|  $.:!;9!'I@z  %4 :!;!9I  &%  '   ($ >  ) :;9  *&   +4 G;  ,>I:;9  -:;9  .4 :;9I?  /.?:;9'�<  0. ?:;9'I<  1   2. ?:;9'I@|  3. :;9'I@z  4.:;9'�@|  5. ?:;9'@|  6. :;9'@z  7.:;9'I@|  8U  9.?:;9'I@|  : :;9I  ;4 :;9I  <.?:;9'@|  = :;9I   (    :;9I8  4 :;9I     !I  4 :;9I   :;9I   I  	 :!;9I  
313 |   
314 |  :!;9   :;9I  I  & I  ! I/  $ >  4 :!;9I   :!;9I  :;9  4 :;9I?<   :!;9I  .?:;9'I<  .?:!;9!'@|  4 :!;9I  :;9   <   :;9I8  .:!;9!'I@|  .:!;9!'I@z  7 I  4 G:!;9   4 :!;9I?  !:!;9!  " :!;9I  #( !~  $ :!;9I  %>!I:!;9  & :!;9I8  '4 :!;9!I?  (.?:;9!'<  )   *.?:!	;9'I<  +.?:;9'I@|  ,U  - :!;9I  ..?:!;9'I@|  /%  0   1$ >  2 :;9  3>I:;9  44 :;9I?<  5>I:;9  6! I/  7:;9  84 G;9  9.?:;9'<  :. ?:;9'I<  ;.?:;9'�<  <. ?:;9I@z  =.?:;9'@|  > :;9I  ?U  @.:;9'@z  A.?:;9'@z  B.?:;9'I@|    :;9I8   !I  (   4 :!;9I   :;9I   :!;9I  4 :!;9I  $ >  	  
315 | (   :;9   I  I  ! I/  .?:!;9!'@|   <  .?:;9'I<    & I  7 I  4 :;9!I?<  >!!I:;9   :!;9!I8  :!;9!	  %     $ >   :;9  . ?:;9'I<  .?:;9'<  .?:;9'I<      !.:;9'@|  " :;9I  #.?:;9'I@|  $.?:;9'@|   \    �   �      	   9   b   �   �        �         �   �   �   �   �   �   �            #  ,  5  >  $ 	)$      �%)?� �	�tvY��K.#6!�'t/<#Y!�'t/<#Y!�'t/<$/"�(t0<#/!�'t.<-/"� �-t&<2. 1�� t<
316 | 0rJ���=K�.�f��fK�t	Y�t
317 | Y�t
318 |  X tYZsY�@	X
319 | �	�����<Z�
320 | �$0<K�J�-ff5 %^8ffKZ%<�!
321 | <K
322 | h��<M8
323 | f; v<# fMt/ L! � J�0.
324 | ���
325 | �yX����������
326 | �����������	�fK�� �u	�fK�� �u	�fK�� �u	�fK�� �u	�fK�� �u	�fK�� �u	�fK�� �u	�fK�� �u	�fK�� �u	�fK�� �u
327 | ����������	�fK�� �u
328 | ��	�fK�� �u� �u� �g�t �  t=(tJ �u��#'�X0�#�.
329 | i� t<J+t<g,t�/t
330 | t1tJ�t \�v�
331 | ��i�!g]�\ X#��� gX�w���\tJ�w���^�u��
332 | f	�{ �X
333 | f�t��/t:J�<tY�t<$Lk�'�6X
334 | >t/	��<# - J�t<7\�(t�t*<;	i\Jwt�;
335 | ?tL	tZgt't��t�%t;<�����Y���v*t8<<_f&��w #� 	. 7 �   f 
336 | f f 8 f � J � � Xf . � � X J B � ��(t�fLhuu/t�v(�@t<�@��2Yg%tI2t' �
337 | L"tJY�+t)f?t%J4�=t%J8�>tJ	v=k���Zt" J � � X=<Z�	�#0<K�
338 | J�,ff4 $^7ffB rJ2 X	=6�
339 | �K<Z��"0<K�	J�+ff3 #^6ff K�h f< .Y� .	t	 X t	YZsY�@t X J X X�Y{�Y � � X�t X�t�(t�(t�Ju _n� 1�-t< g8tJt	�!t<u�g	<1�u�1�?t< �
340 | ��Y��	0K5�w � � XgJvtK��x�	 6= XZ��� � � Xg�D�( tD . JX . Xv XYC	����=�J>���� � � Xgot 	.	��[t X�t�(t�(t�t X�!Jw Yl� 5�	t �
341 |  t�t X J X X�JutY"t X�!Yw� 4�t^1� �wtY���7[�t�(�t1� �xtY�.���	.?u L-
342 | M��u�t.u�����tu����	�K.%�	 ��
343 | . 5fg�u
344 | �t/��
345 | <! - J�*�<�<0gu�	�K5�"��g4�u4�u4�g5�u5��	<��?��?�g1��?�������
346 | ���Y2�/t X J X X�JuU ����ZY.��1		</1�� �    g   �      	   9   b   �   �   F      F   �   �   �   �   �      ,  #  % 	�E      �� tX/ �u���K+0�� tX/ �u��K80= t	u#;[KtX*���	u#�	���)t	ut�-0�t/"<< �K, r J�Y40�u��������w�
347 |  g0� t t	u#\"�%	u#��.�, �=,�:�Htf(f��	u#��,�$�<u �u�)�"t)u"t(u!t(u!t#ut#ut'u fv�1Y%�# ���7Y+�) ��t�Chu�	u#0 �u �����+0�/�t) X t��+ X �	��}{L��	tY(��u�t"Y*��ut( X" t&��B X0 �&��H X6 � ~& J# t��& X  ��t$ X t�3 u�! J t��& X ��t" X t��/�t+ X" t��/ X& ���}		t��t/<<2 X5 <" <, � J	�t X��J>=f2 X- fgt6 X1 tut6 X1 tut4 X/ tut4 X/ tut* X% tut* X% tu�! X �5 X, �[ �Q �O ���' X" �A X8 �s �i �g ���<�u�.0utf�g%� f t X>��f/��Yhug�v� �* wX  J� t fg
348 | �=.	��	�/��<.<M�.=t��	�X	��1XtM$u�t/Y1u�=	jf2@ u$ .J0�5htt
349 | [u<t/K � � J
350 | "gv
351 | h=.t���g�*������ �$ <  t
352 |  <�t:14�J����" y� J�th�u
353 | th�	�u/
354 | t" J �- J3�/�)fJ �KxYwXtft
355 | �Y
356 | X0u�<)�	�������	���
357 | ��	.
358 | �
359 | ��J"��
360 | �
361 | uɯ�1	� #` =t����J
362 | J�� .��f[ XifL��fz��\ � �X . Xl� �) � X�.��g]�x�
363 | ��CX%< .��(	.
364 | ��	�x*�s4.�< �utY�	Z���J�sXN�5<3 ��t\�sX� ����sX��	�sX�	����	�sX����sXtY�)Z-�< �K�_Z	�F<	�5.9�	<��	<��+�sX��+�sX��+�sX��+�sX��+�sX��+�sX��+�sX��+�sX��+�sX��,�sX��+�sX��+�sX���sX��N�sXF�ax��3�sX+��x+�sX�*�sXT �m ���*�sXT �m ���;�sXr �g �� f��;�sXr �g �� f��5�sXk �` �� f��5�rXk �` �� f��6�rXg �\ �� f��6�rXg �\ �� f��9�rXm �b �� t��9�rXs �h �� t��5�rXv �f �d �� t��:�rXx �m �� f��5�rXo �d �� t��	�rX�+�<#u1�<g�� �rX��!Z%�<%�)�<"���(t���rX	(�	�!����rX	(�	�!����rX	)�	�!����rX	)�	�!����rX	)�	�!����rX	)�	�!����rX	)�	�!����rXt?�C�.<2�<� /�rX- �p tV �` t^ �� <��I�rXW�^< X.�<� < �Lu�$t2�f<�: �(=6�=< <�f3k<$ 	9��X�&X���4 �: .* �K/ X .:k�|X� 2f4 X2 f4 J �2 .< . t 
365 | Xh���!�&�/�t�� �vt[&��'�	����
366 | fMf�\��.�	9���m. �.
367 | ��u �3 �) .L.�
368 | �A-���l�` ���zX� �	�z.�<" �	�z.<�<�  ��'f\ � �X . Xg�	91������t�
369 | �g�p��%!>/ g��u��v�Y�Y0�Y     g   �      	   9   b   �   �   N   N   �   �   �   �      _  �   #  ,  ) 	Av      ���:�t"�t�	/'�y���������Z�t�)>��+>� t�Z) � <	�vtY	.*6 �<JY7 �=J/5 f;J/5 f;J)/��)t"<( z. J �	��=K<0=# t	u#\t��"%t	Y �(��4wt=�	s J � t#��	t#,-�$Y/�'Y5�%/1�'/5�#/-�'/5�'/3�$//�#/-�'/1�&/0�#t�"&t- J""t- J""t- J�%t�"&t- J�#�tK�tI/Q�'���C �2 J t]%t��tIYQ�'��&6t1 J���C y�2 J t	�%t��&&&&&%�t; X�t; X�t8 X�"-t- J"�t3 J""t3 J"t&Yt7 J&"t7 J""�F XP �+ <KK)���"��IY'����t, X�tC X/ �S X"��2 X"#t: J"�tC X/ tK	"0 ��  J t� ��	�%�  S0��  . X t J X �	Kuc .[ �Y �a t_ < .F t J X �" J t/ J, t< J9 tI JF t
370 | ��=  . X t J X �	Kut J t# J  t0 J- tK��t</t J � <, J) tD J< �: �B t@ <0�=  . X t J X �	Ku . � � t < .
371 | ��=7>��######!Z	��#)3J)###u �#######"h�	#t X	u#[#�=�t�t	/3�=�	�7 % J �]��Z# number_to_move yy_base _IO_codecvt cols _IO_save_end yy_is_interactive yy_scan_string FIELD_DROPDOWN _IO_write_base _lock _IO_save_base city country num_to_read _chain clearerr _cur_column yy_chk __uint8_t yy_ch_buf atoi yy_last_accepting_cpos yy_n_chars YY_BUFFER_STATE new_buffer _IO_marker yyget_in options_count yy_flex_debug Section FieldAttributes yy_create_buffer FIELD_RADIO yypush_buffer_state _IO_FILE _out_str _IO_wide_data yy_def unsigned char _freeres_list yy_switch_to_buffer yyget_lineno GNU C17 13.3.0 -mtune=generic -march=x86-64 -g -fasynchronous-unwind-tables -fstack-protector-strong -fstack-clash-protection -fcf-protection output getc yy_hold_char _IO_lock_t yyleng yy_try_NUL_trans yylval ret_val yy_buffer_state __errno_location yylineno FIELD_NUMBER source rows FIELD_TEXTAREA yystr yyget_leng _IO_read_ptr stdin input _markers _line_number ValidationRule yy_rule_can_match_eol FieldType yy_state_type yy_get_next_buffer yyset_debug yyin yy_get_previous_state yy_c_buf_p section_count yy_bs_lineno yylex yy_meta isatty yyensure_buffer_stack _flags2 yyrealloc address confirm_field _IO_read_base ferror max_length flex_int16_t AddressField _unused2 street yy_bs_column _old_offset yy_match yy_c_buf_p_offset yy_buf_size YY_CHAR yy_buffer_status long long int field_attrs Metadata after_colon yypop_buffer_state yy_c error_message _IO_write_end yy_at_bol FIELD_CHECKBOX yyout yy_is_our_buffer yybytes yyget_debug _IO_buf_base yy_act strength_required yy_fatal_error yyrestart __pad5 yyfree yy_fill_buffer Form yy_init_globals _flags _mode FIELD_DATE optional process_string flex_int32_t FIELD_TEXT yyalloc grow_size yytext new_size FIELD_EMAIL yy_scan_bytes num_to_alloc yy_bp yyget_text long long unsigned int yy_init_buffer __off_t yy_flush_buffer yy_cp _freeres_buf yy_is_jam yy_buffer_stack_top field_count yy_next_state yy_buffer_stack memset yy_delete_buffer __int16_t _IO_backup_base _shortbuf _in_str str_list malloc __off64_t yyset_lineno yy_ec yyset_out yy_last_accepting_state strdup min_value yy_find_action _IO_buf_end fprintf yy_start flex_uint8_t stderr short int yy_accept FIELD_USERNAME yy_input_file yylex_destroy _vtable_offset do_action YYSTYPE yyset_in yyget_out yy_init yy_scan_buffer yy_buffer_stack_max yy_nxt strlen max_value _IO_read_end _fileno min_length oerrno yy_current_state FIELD_PASSWORD short unsigned int stdout fread _IO_write_ptr FIELD_ADDRESS __int32_t yy_did_buffer_switch_on_eof options exit default_value yy_buf_pos yy_load_buffer_state yy_size_t FIELD_FILE next _bdebug fwrite _yybytes_len yy_amount_of_matched_text YYSYMBOL_MAXLENGTH add_metadata yy_state_t yynewstate YYSYMBOL_validation_rules yylen yysymbol_kind_t yyval yyvaluep YYSYMBOL_TEXT YYSYMBOL_CHECKBOX YYSYMBOL_OPTIONAL YYSYMBOL_VALIDATE yydefact YYSYMBOL_PASSWORD yyvs YYSYMBOL_MAX YYSYMBOL_attribute yysyntax_error_status YYSYMBOL_TEXTAREA yydestruct yytype_int8 YYSYMBOL_YYEOF yystate YYSYMBOL_DROPDOWN add_field_to_section yydefgoto YYSYMBOL_AND YYSYMBOL_EQ YYSYMBOL_field_attributes append YYSYMBOL_STRING_LITERAL yyabortlab FieldName YYSYMBOL_FILE_TYPE yytranslate new_sections YYSYMBOL_field_type create_section yymsg_alloc yyerrorlab yylhs yypact YYSYMBOL_options_list yyr1 yyr2 yypgoto yynewbytes yykind yystos cond YYSYMBOL_GT argc yyerrlab yyerrlab1 YYSYMBOL_EMAIL yystacksize yymsg YYSYMBOL_MINLENGTH cleanup_form cleanup_metadata yytable YYSYMBOL_ERROR yyreduce YYSYMBOL_condition yysymbol new_fields YYSYMBOL_YYACCEPT YYSYMBOL_REQUIRED YYSYMBOL_DATE yychar yycheck YYSYMBOL_59_1 yyerrstatus YYSYMBOL_SECTION yyres yyvsp yyformat strcmp YYSYMBOL_IF YYSYMBOL_NEQ YYSYMBOL_YYUNDEF YYSYMBOL_COLS current_section yyctx YYSYMBOL_FIELD yyxbegin YYSYMBOL_validation_block yyreturnlab yysymbol_name YYSYMBOL_46_ YYSYMBOL_50_ YYSYMBOL_field_list field_name_count YYSYMBOL_RADIO generate_html yycount yyarg yy_state_fast_t yysyntax_error YYSYMBOL_47_ YYSYMBOL_ADDRESS YYSYMBOL_section YYSYMBOL_FORM yydefault fopen YYSYMBOL_metadata_declaration yyxend yyargn argv YYSYMBOL_48_ YYSYMBOL_52_ yyptr sprintf YYSYMBOL_DEFAULT YYSYMBOL_MIN yyacceptlab yyresult yytnamerr YYSYMBOL_LT yysize yysrc yyss1 YYSYMBOL_49_ YYSYMBOL_53_ YYSYMBOL_YYerror yyexhaustedlab YYSYMBOL_form_body yysize1 yyerror perror yystpcpy yyssa yybackup yyssp add_section_to_form YYENOMEM yy_syntax_error_arguments yychecklim init_field_attributes YYSYMBOL_META current_form create_form YYSYMBOL_form_item YYSYMBOL_GTE yymsgbuf YYSYMBOL_NUMBER YYSYMBOL_USERNAME yypcontext_expected_tokens YYSYMBOL_LTE yyss_alloc YYSYMBOL_51_ new_field_names merge_field_attributes yyvs_alloc line YYSYMBOL_ROWS YYSYMBOL_OR yypcontext_t YYSYMBOL_CONFIRM YYSYMBOL_STRENGTH YYSYMBOL_form YYSYMBOL_NUMBER_LITERAL do_not_strip_quotes YYSYMBOL_field_declaration yytname yywrap yyss main yyvsa YYSYMBOL_OPTIONS yytoken yymsgp yyparse YYSYMBOL_YYEMPTY check_duplicate_field YYSYMBOL_PATTERN YYARGS_MAX YYSYMBOL_validation_rule yydest YYSYMBOL_attribute_opt_semicolon yysetstate YYSYMBOL_IDENTIFIER yynerrs generate_validation_js escaped_value escaped_pattern __ctype_b_loc input_type generate_section_html parse_condition _ISlower _ISxdigit _IScntrl generate_html_footer _ISdigit generate_html_header _ISspace escaped_name escape_html_attr _ISpunct _ISprint _ISgraph _ISalpha _ISalnum _ISblank _ISupper lex.yy.c /home/dinuka/programming-paradigms/FormLang/src /usr/lib/gcc/x86_64-linux-gnu/13/include /usr/include/x86_64-linux-gnu/bits /usr/include/x86_64-linux-gnu/bits/types /usr/include lexer.l stddef.h types.h struct_FILE.h stdio.h stdint-intn.h stdint-uintn.h formLang.h parser.y y.tab.h stdlib.h string.h unistd.h errno.h y.tab.c html_generator.c ctype.h          ���� .         �!�&�\�\�\�\ �!�%�\�\ �U�W�\�\                                ��                	     �                  ��                     p#                    �#              3     �#              I     H�             U     ��              |      $              �     ��              �    ��                �     ��             �     ��             �     ��             �     ��             �     ��                  ��                 ��                 ��                 ��             8     �      �      B    ��             H    ��      *       P     �      �      X    ��      �      _    @�      �      f    @�      �      m    @�      �       �    ��             �    ��             �    �?      =      �    �:      �       �    �6      2      �    &8                �0      U          ,C      <       &    �<      �       5    -D      o       E   ��                M    ��      -      Y    ��      H      a    �O      %       o    ��      v       v     �      v           ��             �    ��             �    ��      i       �    @�      i       �    ��      v       �    @�      <       �    ��      <       �    P            �    
372 | Q      Q       �    [Q      �       �    ?R      �       �    �R      [      	    1U      (          ��                %    ��      m          ��                5    �                   ��                C    �              L     |�              _    ��              u    �9      �       �    ,9      �       �                     �    8�             �                     �                     �    �C             �                           �                 �      �      �      �              6                     I                     \                     n    0�             �    `G      `       �    �              �    ��             �    yu      8       �    YU              �    X�             �    �K      u       �   ��              �                     �                         D                 p�                 ��             &    ��             3    gE      )       =    d;      �       N    �             W    h�             e                     x    �E      k       �    ��             �    �C             �    IE             �    �E             �    �C             �    A            �    �G      |       �     �              �    <H      �                               `�                 x�             (    "B      .       7    �C             @    a$      �      O                     c    PB      �       q    �J      �       ~                      �    hC             �   �              �                     �    �C             �                     �     �             �    �=            �    %z      �
373 |           ��                 �x      n      *                     �    )$      8       =    yF      �       Q    <      �       b                     u    �>      �       �    @�              �    P�             �    @#      &       �                     �     �              �    �u      �       �    F      _       �    �N      T      �    &      �
374 |       �    V=      �       �                                                               +    ��      X       2    xC             ;    ݊      �      I                     ]                     n                     �   �              �                      �    2v             �                     �    �x      3       �    D             �    	L      �      �    �C             �    Av      C      	  "                                      )	                     :	    �D      �       H	                     `	    @�              Scrt1.o __abi_tag crtstuff.c deregister_tm_clones __do_global_dtors_aux completed.0 __do_global_dtors_aux_fini_array_entry frame_dummy __frame_dummy_init_array_entry lex.yy.c yy_buffer_stack_top yy_buffer_stack_max yy_buffer_stack yy_hold_char yy_n_chars yy_c_buf_p yy_init yy_start yy_did_buffer_switch_on_eof yy_accept yy_ec yy_meta yy_base yy_def yy_nxt yy_chk yy_rule_can_match_eol yy_last_accepting_state yy_last_accepting_cpos yyensure_buffer_stack yy_load_buffer_state yy_get_previous_state yy_try_NUL_trans yy_get_next_buffer yy_fatal_error yy_init_buffer yy_init_globals y.tab.c yytranslate yytname yysymbol_name yypact yydefact yypgoto yydefgoto yytable yycheck yystos yyr1 yyr2 yypcontext_expected_tokens yystpcpy yytnamerr yy_syntax_error_arguments yysyntax_error yydestruct html_generator.c parse_condition __FRAME_END__ _DYNAMIC __GNU_EH_FRAME_HDR _GLOBAL_OFFSET_TABLE_ yy_switch_to_buffer yyrestart free@GLIBC_2.2.5 yynerrs __libc_start_main@GLIBC_2.34 __errno_location@GLIBC_2.2.5 yyget_out _ITM_deregisterTMCloneTable stdout@GLIBC_2.2.5 generate_validation_js ferror@GLIBC_2.2.5 isatty@GLIBC_2.2.5 fread@GLIBC_2.2.5 stdin@GLIBC_2.2.5 check_duplicate_field _edata field_names yyerror yyparse yyin cleanup_metadata _fini strlen@GLIBC_2.2.5 __stack_chk_fail@GLIBC_2.4 yyget_debug yytext current_section current_form yyrealloc yy_create_buffer yylineno yy_flex_debug memset@GLIBC_2.2.5 create_form field_name_count yyget_text yyalloc yyfree yyset_lineno yy_scan_buffer init_field_attributes __data_start add_field_to_section strcmp@GLIBC_2.2.5 yyout after_colon yy_scan_string yyset_in process_string fprintf@GLIBC_2.2.5 yy_scan_bytes add_metadata __gmon_start__ yyget_lineno __dso_handle clearerr@GLIBC_2.2.5 yyget_leng memcpy@GLIBC_2.14 _IO_stdin_used yypush_buffer_state generate_section_html yychar escape_html_attr fileno@GLIBC_2.2.5 add_section_to_form yy_delete_buffer malloc@GLIBC_2.2.5 yypop_buffer_state _end yyleng realloc@GLIBC_2.2.5 __bss_start main create_section merge_field_attributes yylex yy_flush_buffer fopen@GLIBC_2.2.5 perror@GLIBC_2.2.5 atoi@GLIBC_2.2.5 yylval yyget_in generate_html sprintf@GLIBC_2.2.5 exit@GLIBC_2.2.5 fwrite@GLIBC_2.2.5 __TMC_END__ _ITM_registerTMCloneTable yywrap strdup@GLIBC_2.2.5 generate_html_footer yyset_debug cleanup_form yyset_out generate_html_header __cxa_finalize@GLIBC_2.2.5 getc@GLIBC_2.2.5 yylex_destroy __ctype_b_loc@GLIBC_2.3 stderr@GLIBC_2.2.5  .symtab .strtab .shstrtab .interp .note.gnu.property .note.gnu.build-id .note.ABI-tag .gnu.hash .dynsym .dynstr .gnu.version .gnu.version_r .rela.dyn .rela.plt .init .plt.got .plt.sec .text .fini .rodata .eh_frame_hdr .eh_frame .init_array .fini_array .data.rel.ro .dynamic .data .bss .comment .debug_aranges .debug_info .debug_abbrev .debug_line .debug_str .debug_line_str .debug_rnglists                                                                                                                              #             8      8      0                              6             h      h      $                              I             �      �                                     W   ���o       �      �      4                             a             �      �                                i                           y                             q   ���o       z      z      B                            ~   ���o       �      �      `                            �              	       	      �                           �      B       �      �      @                          �                                                           �                             �                            �             �!      �!                                   �             �!      �!      �                            �             @#      @#      pi                             �             ��      ��                                    �              �       �      y$                              �             |�      |�      $                             �             ��      ��      |                             �             ��      ��                                   �             ��      ��                                   �             ��      ��      H                              
375 |             �      �      �                           �             ��      ��                                                �       �                                                 �      �                                          0               �      +                             '                     ?�      �                              6                     ��      �;                             B                     �     �
376 |                              P                     M     c$                             \     0               �;     �                            g     0               MP     g                            w                     �Q     I                                                     R     �      %   B                 	                      �a     s	                                                   ck     �                             
```

src/formLang.h
```
1 | #ifndef FORMLANG_H
2 | #define FORMLANG_H
3 | 
4 | #include <stdio.h>
5 | #include <stdlib.h>
6 | #include <string.h>
7 | 
8 | // Metadata structure
9 | typedef struct Metadata {
10 |     char* key;
11 |     char* value;
12 |     struct Metadata* next;
13 | } Metadata;
14 | 
15 | // Validation structure
16 | typedef struct ValidationRule {
17 |     char* condition;
18 |     char* error_message;
19 |     struct ValidationRule* next;
20 | } ValidationRule;
21 | 
22 | // Field type definitions
23 | typedef enum {
24 |     FIELD_TEXT,
25 |     FIELD_EMAIL,
26 |     FIELD_PASSWORD,
27 |     FIELD_NUMBER,
28 |     FIELD_TEXTAREA,
29 |     FIELD_DATE,
30 |     FIELD_CHECKBOX,
31 |     FIELD_DROPDOWN,
32 |     FIELD_RADIO,
33 |     FIELD_FILE,
34 |     FIELD_USERNAME,
35 |     FIELD_ADDRESS
36 | } FieldType;
37 | 
38 | // Address subfields
39 | typedef struct {
40 |     char* street;
41 |     char* city;
42 |     char* state;
43 |     char* zip;
44 |     char* country;
45 | } AddressField;
46 | 
47 | // Field attribute structure
48 | typedef struct {
49 |     int required;
50 |     int optional;
51 |     int min_length;
52 |     int max_length;
53 |     int min_value;
54 |     int max_value;
55 |     int rows;
56 |     int cols;
57 |     char* pattern;
58 |     char* default_value;
59 |     char* confirm_field;
60 |     int strength_required;
61 |     char** options;
62 |     int options_count;
63 |     AddressField* address;
64 | } FieldAttributes;
65 | 
66 | // Structure definitions
67 | typedef struct Field {
68 |     char *name;
69 |     FieldType type;
70 |     FieldAttributes attributes;
71 | } Field;
72 | 
73 | typedef struct Section {
74 |     char *name;
75 |     Field *fields;
76 |     int field_count;
77 | } Section;
78 | 
79 | typedef struct Form {
80 |     char *name;
81 |     Section **sections;
82 |     int section_count;
83 |     ValidationRule* validation_rules;
84 |     Metadata* metadata;
85 | } Form;
86 | 
87 | // External declarations
88 | extern int yylineno;
89 | extern int yylex(void);
90 | extern int yyparse(void);
91 | extern void yyerror(const char *s);
92 | extern FILE* yyin;
93 | 
94 | // Global variables
95 | extern Form *current_form;
96 | extern Section *current_section;
97 | 
98 | // Function declarations
99 | void generate_html(FILE* output);
100 | void generate_html_header(FILE* output);
101 | void generate_html_footer(FILE* output);
102 | void generate_section_html(FILE* output, Section* section);
103 | void generate_validation_js(FILE* output, Form* form);
104 | void add_metadata(Form* form, const char* key, const char* value);
105 | void cleanup_metadata(Metadata* metadata);
106 | 
107 | // Helper functions
108 | Form* create_form(const char* name);
109 | Section* create_section(const char* name);
110 | void add_section_to_form(Form* form, Section* section);
111 | void add_field_to_section(Section* section, const char* name, FieldType type, FieldAttributes* attrs);
112 | void cleanup_form(Form* form);
113 | 
114 | #endif /* FORMLANG_H */
```

src/html_generator.c
```
1 | #include <stdio.h>
2 | #include <stdlib.h>
3 | #include <string.h>
4 | #include <ctype.h>
5 | #include "formLang.h"
6 | 
7 | void generate_html_header(FILE* output) {
8 |     fprintf(output, "<!DOCTYPE html>\n<html>\n<head>\n");
9 |     fprintf(output, "  <meta charset=\"UTF-8\">\n");
10 |     fprintf(output, "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n");
11 |     fprintf(output, "  <title>%s</title>\n", current_form->name);
12 |     
13 |     // Add metadata as HTML comments
14 |     Metadata* meta = current_form->metadata;
15 |     while (meta) {
16 |         fprintf(output, "  <!-- %s: %s -->\n", meta->key, meta->value);
17 |         meta = meta->next;
18 |     }
19 |     
20 |     fprintf(output, "  <style>\n");
21 |     fprintf(output, "    body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }\n");
22 |     fprintf(output, "    fieldset { margin-bottom: 20px; padding: 15px; border: 1px solid #ccc; }\n");
23 |     fprintf(output, "    legend { font-weight: bold; padding: 0 10px; }\n");
24 |     fprintf(output, "    .field { margin-bottom: 15px; }\n");
25 |     fprintf(output, "    label { display: block; margin-bottom: 5px; }\n");
26 |     fprintf(output, "    input, textarea, select { width: 100%%; padding: 8px; margin-bottom: 5px; }\n");
27 |     fprintf(output, "    .error { color: red; font-size: 0.9em; margin-top: 5px; }\n");
28 |     fprintf(output, "  </style>\n");
29 |     fprintf(output, "</head>\n<body>\n");
30 |     fprintf(output, "<form id=\"%s\" onsubmit=\"return validateForm()\">\n", current_form->name);
31 | }
32 | 
33 | void generate_html_footer(FILE* output) {
34 |     fprintf(output, "</body>\n</html>\n");
35 | }
36 | 
37 | char* escape_html_attr(const char* input) {
38 |     if (!input) return strdup("");
39 |     
40 |     char* output = malloc(strlen(input) * 2 + 1);
41 |     int j = 0;
42 |     
43 |     for (int i = 0; input[i] != '\0'; i++) {
44 |         switch (input[i]) {
45 |             case '&': strcpy(output + j, "&amp;"); j += 5; break;
46 |             case '"': strcpy(output + j, "&quot;"); j += 6; break;
47 |             case '<': strcpy(output + j, "&lt;"); j += 4; break;
48 |             case '>': strcpy(output + j, "&gt;"); j += 4; break;
49 |             default: output[j++] = input[i];
50 |         }
51 |     }
52 |     output[j] = '\0';
53 |     return output;
54 | }
55 | 
56 | void generate_section_html(FILE* output, Section* section) {
57 |     fprintf(stderr, "Starting section generation\n");
58 |     if (!section || !output) {
59 |         fprintf(stderr, "Null section or output\n");
60 |         return;
61 |     }
62 | 
63 |     // Skip empty sections
64 |     if (section->field_count == 0) {
65 |         return;
66 |     }
67 | 
68 |     fprintf(output, "<section>\n");
69 |     fprintf(output, "<h2>%s</h2>\n", section->name);
70 | 
71 |     fprintf(stderr, "Processing %d fields\n", section->field_count);
72 |     for (int i = 0; i < section->field_count; i++) {
73 |         fprintf(stderr, "Generating field %d\n", i);
74 |         Field* field = &section->fields[i];
75 |         
76 |         // Generate label
77 |         char* escaped_name = escape_html_attr(field->name);
78 |         fprintf(output, "<label for=\"%s\">%s%s</label>\n", 
79 |                escaped_name, escaped_name, field->attributes.required ? " *" : "");
80 |         free(escaped_name);
81 | 
82 |         const char* type = "text";
83 |         switch (field->type) {
84 |             case FIELD_TEXT: type = "text"; break;
85 |             case FIELD_EMAIL: type = "email"; break;
86 |             case FIELD_PASSWORD: type = "password"; break;
87 |             case FIELD_NUMBER: type = "number"; break;
88 |             case FIELD_TEXTAREA: type = "textarea"; break;
89 |             case FIELD_DATE: type = "date"; break;
90 |             case FIELD_CHECKBOX: type = "checkbox"; break;
91 |             case FIELD_DROPDOWN: type = "select"; break;
92 |             case FIELD_RADIO: type = "radio"; break;
93 |             case FIELD_FILE: type = "file"; break;
94 |             case FIELD_USERNAME: type = "text"; break;
95 |             case FIELD_ADDRESS: type = "text"; break;
96 |         }
97 | 
98 |         if (field->type == FIELD_TEXTAREA) {
99 |             fprintf(output, "<textarea id=\"%s\" name=\"%s\"", field->name, field->name);
100 |             if (field->attributes.rows > 0) fprintf(output, " rows=\"%d\"", field->attributes.rows);
101 |             if (field->attributes.cols > 0) fprintf(output, " cols=\"%d\"", field->attributes.cols);
102 |             if (field->attributes.required) fprintf(output, " required");
103 |             fprintf(output, "></textarea>\n");
104 |         } else if (field->type == FIELD_DROPDOWN) {
105 |             fprintf(output, "<select id=\"%s\" name=\"%s\"", field->name, field->name);
106 |             if (field->attributes.required) fprintf(output, " required");
107 |             fprintf(output, ">\n");
108 |             if (!field->attributes.required) {
109 |                 fprintf(output, "  <option value=\"\">Select an option</option>\n");
110 |             }
111 |             for (int i = 0; i < field->attributes.options_count; i++) {
112 |                 char* escaped_value = escape_html_attr(field->attributes.options[i]);
113 |                 fprintf(output, "  <option value=\"%s\">%s</option>\n", escaped_value, escaped_value);
114 |                 free(escaped_value);
115 |             }
116 |             fprintf(output, "</select>\n");
117 |         } else if (field->type == FIELD_RADIO) {
118 |             fprintf(output, "<div class=\"radio-group\">\n");
119 |             for (int i = 0; i < field->attributes.options_count; i++) {
120 |                 char* escaped_value = escape_html_attr(field->attributes.options[i]);
121 |                 fprintf(output, "  <input type=\"radio\" id=\"%s_%d\" name=\"%s\" value=\"%s\"", 
122 |                        field->name, i + 1, field->name, escaped_value);
123 |                 if (field->attributes.required) fprintf(output, " required");
124 |                 fprintf(output, ">\n");
125 |                 fprintf(output, "  <span>%s</span><br>\n", escaped_value);
126 |                 free(escaped_value);
127 |             }
128 |             fprintf(output, "</div>\n");
129 |         } else if (field->type == FIELD_ADDRESS) {
130 |             fprintf(output, "<div class=\"address-group\">\n");
131 |             fprintf(output, "<input type=\"text\" id=\"%s_street\" name=\"%s_street\" placeholder=\"Street\" required>\n", field->name, field->name);
132 |             fprintf(output, "<input type=\"text\" id=\"%s_city\" name=\"%s_city\" placeholder=\"City\" required>\n", field->name, field->name);
133 |             fprintf(output, "<input type=\"text\" id=\"%s_state\" name=\"%s_state\" placeholder=\"State\" required>\n", field->name, field->name);
134 |             fprintf(output, "<input type=\"text\" id=\"%s_zip\" name=\"%s_zip\" placeholder=\"ZIP\" required>\n", field->name, field->name);
135 |             fprintf(output, "<input type=\"text\" id=\"%s_country\" name=\"%s_country\" placeholder=\"Country\" required>\n", field->name, field->name);
136 |             fprintf(output, "</div>\n");
137 |         } else {
138 |             const char* input_type = type;
139 |             if (field->type == FIELD_USERNAME) input_type = "text";
140 |             if (field->type == FIELD_PASSWORD) input_type = "password";
141 |             if (field->type == FIELD_EMAIL) input_type = "email";
142 |             fprintf(output, "<input type=\"%s\" id=\"%s\" name=\"%s\"", input_type, field->name, field->name);
143 |             if (field->attributes.required) fprintf(output, " required");
144 |             if (field->attributes.min_length > 0) fprintf(output, " minlength=\"%d\"", field->attributes.min_length);
145 |             if (field->attributes.max_length > 0) fprintf(output, " maxlength=\"%d\"", field->attributes.max_length);
146 |             if (field->type == FIELD_NUMBER) {
147 |                 if (field->attributes.min_value != 0) fprintf(output, " min=\"%d\"", field->attributes.min_value);
148 |                 if (field->attributes.max_value != 0) fprintf(output, " max=\"%d\"", field->attributes.max_value);
149 |             }
150 |             if (field->attributes.pattern && strlen(field->attributes.pattern) > 0) {
151 |                 char* escaped_pattern = escape_html_attr(field->attributes.pattern);
152 |                 fprintf(output, " pattern=\"%s\"", escaped_pattern);
153 |                 free(escaped_pattern);
154 |             }
155 |             if (field->attributes.default_value) {
156 |                 char* escaped_value = escape_html_attr(field->attributes.default_value);
157 |                 fprintf(output, " value=\"%s\"", escaped_value);
158 |                 free(escaped_value);
159 |             }
160 |             if (field->type == FIELD_FILE) fprintf(output, " accept=\"*/*\"");
161 |             if (field->type == FIELD_CHECKBOX && field->attributes.default_value) fprintf(output, " checked");
162 |             if (field->attributes.confirm_field) fprintf(output, " data-confirm=\"%s\"", field->attributes.confirm_field);
163 |             if (field->attributes.strength_required > 0) fprintf(output, " data-strength=\"%d\"", field->attributes.strength_required);
164 |             fprintf(output, ">\n");
165 |             if (field->type == FIELD_PASSWORD && field->attributes.strength_required > 0) {
166 |                 fprintf(output, "<meter id=\"%s_strength\" min=\"0\" max=\"4\"></meter>\n", field->name);
167 |             }
168 |         }
169 |         fprintf(stderr, "Field %d generated successfully\n", i);
170 |     }
171 | 
172 |     fprintf(output, "</section>\n");
173 |     fprintf(stderr, "Section generation complete\n");
174 | }
175 | 
176 | static void parse_condition(const char* cond, char* field, char* op, char* value) {
177 |     // cond is like "score > 100" or "age < 18"
178 |     // Extract field, op, value
179 |     const char* p = cond;
180 |     while (*p && isspace(*p)) p++;
181 |     int i = 0;
182 |     while (*p && !isspace(*p) && *p != '<' && *p != '>' && *p != '=' && *p != '!') field[i++] = *p++;
183 |     field[i] = '\0';
184 |     while (*p && isspace(*p)) p++;
185 |     int j = 0;
186 |     if (*p == '<' || *p == '>' || *p == '=' || *p == '!') {
187 |         op[j++] = *p++;
188 |         if (*p == '=' || (*(p-1) == '<' && *p == '>')) op[j++] = *p++;
189 |     }
190 |     op[j] = '\0';
191 |     while (*p && isspace(*p)) p++;
192 |     int k = 0;
193 |     while (*p) value[k++] = *p++;
194 |     value[k] = '\0';
195 | }
196 | 
197 | void generate_validation_js(FILE* output, Form* form) {
198 |     fprintf(output, "<script>\n");
199 |     fprintf(output, "document.addEventListener('DOMContentLoaded', function() {\n");
200 |     fprintf(output, "  const form = document.querySelector('form');\n");
201 |     fprintf(output, "  form.addEventListener('submit', function(e) {\n");
202 |     fprintf(output, "    let valid = true;\n");
203 |     fprintf(output, "    const errors = [];\n\n");
204 | 
205 |     ValidationRule* rule = form->validation_rules;
206 |     while (rule) {
207 |         char field[64], op[4], value[64];
208 |         parse_condition(rule->condition, field, op, value);
209 |         fprintf(output, "    {\n");
210 |         fprintf(output, "      var %s = document.getElementById('%s');\n", field, field);
211 |         fprintf(output, "      var %sVal = %s ? %s.value : '';\n", field, field, field);
212 |         fprintf(output, "      if (%s && %sVal !== '' && parseFloat(%sVal) %s %s) {\n", field, field, field, op, value);
213 |         fprintf(output, "        errors.push(\"%s\");\n", rule->error_message);
214 |         fprintf(output, "        valid = false;\n");
215 |         fprintf(output, "      }\n");
216 |         fprintf(output, "    }\n");
217 |         rule = rule->next;
218 |     }
219 | 
220 |     fprintf(output, "    if (!valid) {\n");
221 |     fprintf(output, "      e.preventDefault();\n");
222 |     fprintf(output, "      alert(errors.join('\\n'));\n");
223 |     fprintf(output, "    }\n");
224 |     fprintf(output, "  });\n");
225 |     fprintf(output, "});\n");
226 |     fprintf(output, "</script>\n");
227 | }
228 | 
229 | void generate_html(FILE* output) {
230 |     fprintf(stderr, "Starting HTML generation\n");
231 |     if (!current_form || !output) {
232 |         fprintf(stderr, "Null form or output\n");
233 |         return;
234 |     }
235 | 
236 |     fprintf(stderr, "Generating header\n");
237 |     generate_html_header(output);
238 |     fprintf(output, "<form>\n");
239 | 
240 |     fprintf(stderr, "Processing %d sections\n", current_form->section_count);
241 |     for (int i = 0; i < current_form->section_count; i++) {
242 |         fprintf(stderr, "Generating section %d\n", i);
243 |         generate_section_html(output, current_form->sections[i]);
244 |     }
245 | 
246 |     fprintf(output, "<input type=\"submit\" value=\"Submit\">\n");
247 |     fprintf(output, "</form>\n");
248 |     generate_html_footer(output);
249 |     
250 |     // Generate validation JavaScript
251 |     generate_validation_js(output, current_form);
252 |     
253 |     fprintf(stderr, "HTML generation complete\n");
254 | }
```

src/lex.yy.c
```
1 | 
2 | #line 3 "lex.yy.c"
3 | 
4 | #define  YY_INT_ALIGNED short int
5 | 
6 | /* A lexical scanner generated by flex */
7 | 
8 | #define FLEX_SCANNER
9 | #define YY_FLEX_MAJOR_VERSION 2
10 | #define YY_FLEX_MINOR_VERSION 6
11 | #define YY_FLEX_SUBMINOR_VERSION 4
12 | #if YY_FLEX_SUBMINOR_VERSION > 0
13 | #define FLEX_BETA
14 | #endif
15 | 
16 | /* First, we deal with  platform-specific or compiler-specific issues. */
17 | 
18 | /* begin standard C headers. */
19 | #include <stdio.h>
20 | #include <string.h>
21 | #include <errno.h>
22 | #include <stdlib.h>
23 | 
24 | /* end standard C headers. */
25 | 
26 | /* flex integer type definitions */
27 | 
28 | #ifndef FLEXINT_H
29 | #define FLEXINT_H
30 | 
31 | /* C99 systems have <inttypes.h>. Non-C99 systems may or may not. */
32 | 
33 | #if defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
34 | 
35 | /* C99 says to define __STDC_LIMIT_MACROS before including stdint.h,
36 |  * if you want the limit (max/min) macros for int types. 
37 |  */
38 | #ifndef __STDC_LIMIT_MACROS
39 | #define __STDC_LIMIT_MACROS 1
40 | #endif
41 | 
42 | #include <inttypes.h>
43 | typedef int8_t flex_int8_t;
44 | typedef uint8_t flex_uint8_t;
45 | typedef int16_t flex_int16_t;
46 | typedef uint16_t flex_uint16_t;
47 | typedef int32_t flex_int32_t;
48 | typedef uint32_t flex_uint32_t;
49 | #else
50 | typedef signed char flex_int8_t;
51 | typedef short int flex_int16_t;
52 | typedef int flex_int32_t;
53 | typedef unsigned char flex_uint8_t; 
54 | typedef unsigned short int flex_uint16_t;
55 | typedef unsigned int flex_uint32_t;
56 | 
57 | /* Limits of integral types. */
58 | #ifndef INT8_MIN
59 | #define INT8_MIN               (-128)
60 | #endif
61 | #ifndef INT16_MIN
62 | #define INT16_MIN              (-32767-1)
63 | #endif
64 | #ifndef INT32_MIN
65 | #define INT32_MIN              (-2147483647-1)
66 | #endif
67 | #ifndef INT8_MAX
68 | #define INT8_MAX               (127)
69 | #endif
70 | #ifndef INT16_MAX
71 | #define INT16_MAX              (32767)
72 | #endif
73 | #ifndef INT32_MAX
74 | #define INT32_MAX              (2147483647)
75 | #endif
76 | #ifndef UINT8_MAX
77 | #define UINT8_MAX              (255U)
78 | #endif
79 | #ifndef UINT16_MAX
80 | #define UINT16_MAX             (65535U)
81 | #endif
82 | #ifndef UINT32_MAX
83 | #define UINT32_MAX             (4294967295U)
84 | #endif
85 | 
86 | #ifndef SIZE_MAX
87 | #define SIZE_MAX               (~(size_t)0)
88 | #endif
89 | 
90 | #endif /* ! C99 */
91 | 
92 | #endif /* ! FLEXINT_H */
93 | 
94 | /* begin standard C++ headers. */
95 | 
96 | /* TODO: this is always defined, so inline it */
97 | #define yyconst const
98 | 
99 | #if defined(__GNUC__) && __GNUC__ >= 3
100 | #define yynoreturn __attribute__((__noreturn__))
101 | #else
102 | #define yynoreturn
103 | #endif
104 | 
105 | /* Returned upon end-of-file. */
106 | #define YY_NULL 0
107 | 
108 | /* Promotes a possibly negative, possibly signed char to an
109 |  *   integer in range [0..255] for use as an array index.
110 |  */
111 | #define YY_SC_TO_UI(c) ((YY_CHAR) (c))
112 | 
113 | /* Enter a start condition.  This macro really ought to take a parameter,
114 |  * but we do it the disgusting crufty way forced on us by the ()-less
115 |  * definition of BEGIN.
116 |  */
117 | #define BEGIN (yy_start) = 1 + 2 *
118 | /* Translate the current start state into a value that can be later handed
119 |  * to BEGIN to return to the state.  The YYSTATE alias is for lex
120 |  * compatibility.
121 |  */
122 | #define YY_START (((yy_start) - 1) / 2)
123 | #define YYSTATE YY_START
124 | /* Action number for EOF rule of a given start state. */
125 | #define YY_STATE_EOF(state) (YY_END_OF_BUFFER + state + 1)
126 | /* Special action meaning "start processing a new file". */
127 | #define YY_NEW_FILE yyrestart( yyin  )
128 | #define YY_END_OF_BUFFER_CHAR 0
129 | 
130 | /* Size of default input buffer. */
131 | #ifndef YY_BUF_SIZE
132 | #ifdef __ia64__
133 | /* On IA-64, the buffer size is 16k, not 8k.
134 |  * Moreover, YY_BUF_SIZE is 2*YY_READ_BUF_SIZE in the general case.
135 |  * Ditto for the __ia64__ case accordingly.
136 |  */
137 | #define YY_BUF_SIZE 32768
138 | #else
139 | #define YY_BUF_SIZE 16384
140 | #endif /* __ia64__ */
141 | #endif
142 | 
143 | /* The state buf must be large enough to hold one state per character in the main buffer.
144 |  */
145 | #define YY_STATE_BUF_SIZE   ((YY_BUF_SIZE + 2) * sizeof(yy_state_type))
146 | 
147 | #ifndef YY_TYPEDEF_YY_BUFFER_STATE
148 | #define YY_TYPEDEF_YY_BUFFER_STATE
149 | typedef struct yy_buffer_state *YY_BUFFER_STATE;
150 | #endif
151 | 
152 | #ifndef YY_TYPEDEF_YY_SIZE_T
153 | #define YY_TYPEDEF_YY_SIZE_T
154 | typedef size_t yy_size_t;
155 | #endif
156 | 
157 | extern int yyleng;
158 | 
159 | extern FILE *yyin, *yyout;
160 | 
161 | #define EOB_ACT_CONTINUE_SCAN 0
162 | #define EOB_ACT_END_OF_FILE 1
163 | #define EOB_ACT_LAST_MATCH 2
164 |     
165 |     /* Note: We specifically omit the test for yy_rule_can_match_eol because it requires
166 |      *       access to the local variable yy_act. Since yyless() is a macro, it would break
167 |      *       existing scanners that call yyless() from OUTSIDE yylex.
168 |      *       One obvious solution it to make yy_act a global. I tried that, and saw
169 |      *       a 5% performance hit in a non-yylineno scanner, because yy_act is
170 |      *       normally declared as a register variable-- so it is not worth it.
171 |      */
172 |     #define  YY_LESS_LINENO(n) \
173 |             do { \
174 |                 int yyl;\
175 |                 for ( yyl = n; yyl < yyleng; ++yyl )\
176 |                     if ( yytext[yyl] == '\n' )\
177 |                         --yylineno;\
178 |             }while(0)
179 |     #define YY_LINENO_REWIND_TO(dst) \
180 |             do {\
181 |                 const char *p;\
182 |                 for ( p = yy_cp-1; p >= (dst); --p)\
183 |                     if ( *p == '\n' )\
184 |                         --yylineno;\
185 |             }while(0)
186 |     
187 | /* Return all but the first "n" matched characters back to the input stream. */
188 | #define yyless(n) \
189 | 	do \
190 | 		{ \
191 | 		/* Undo effects of setting up yytext. */ \
192 |         int yyless_macro_arg = (n); \
193 |         YY_LESS_LINENO(yyless_macro_arg);\
194 | 		*yy_cp = (yy_hold_char); \
195 | 		YY_RESTORE_YY_MORE_OFFSET \
196 | 		(yy_c_buf_p) = yy_cp = yy_bp + yyless_macro_arg - YY_MORE_ADJ; \
197 | 		YY_DO_BEFORE_ACTION; /* set up yytext again */ \
198 | 		} \
199 | 	while ( 0 )
200 | #define unput(c) yyunput( c, (yytext_ptr)  )
201 | 
202 | #ifndef YY_STRUCT_YY_BUFFER_STATE
203 | #define YY_STRUCT_YY_BUFFER_STATE
204 | struct yy_buffer_state
205 | 	{
206 | 	FILE *yy_input_file;
207 | 
208 | 	char *yy_ch_buf;		/* input buffer */
209 | 	char *yy_buf_pos;		/* current position in input buffer */
210 | 
211 | 	/* Size of input buffer in bytes, not including room for EOB
212 | 	 * characters.
213 | 	 */
214 | 	int yy_buf_size;
215 | 
216 | 	/* Number of characters read into yy_ch_buf, not including EOB
217 | 	 * characters.
218 | 	 */
219 | 	int yy_n_chars;
220 | 
221 | 	/* Whether we "own" the buffer - i.e., we know we created it,
222 | 	 * and can realloc() it to grow it, and should free() it to
223 | 	 * delete it.
224 | 	 */
225 | 	int yy_is_our_buffer;
226 | 
227 | 	/* Whether this is an "interactive" input source; if so, and
228 | 	 * if we're using stdio for input, then we want to use getc()
229 | 	 * instead of fread(), to make sure we stop fetching input after
230 | 	 * each newline.
231 | 	 */
232 | 	int yy_is_interactive;
233 | 
234 | 	/* Whether we're considered to be at the beginning of a line.
235 | 	 * If so, '^' rules will be active on the next match, otherwise
236 | 	 * not.
237 | 	 */
238 | 	int yy_at_bol;
239 | 
240 |     int yy_bs_lineno; /**< The line count. */
241 |     int yy_bs_column; /**< The column count. */
242 | 
243 | 	/* Whether to try to fill the input buffer when we reach the
244 | 	 * end of it.
245 | 	 */
246 | 	int yy_fill_buffer;
247 | 
248 | 	int yy_buffer_status;
249 | 
250 | #define YY_BUFFER_NEW 0
251 | #define YY_BUFFER_NORMAL 1
252 | 	/* When an EOF's been seen but there's still some text to process
253 | 	 * then we mark the buffer as YY_EOF_PENDING, to indicate that we
254 | 	 * shouldn't try reading from the input source any more.  We might
255 | 	 * still have a bunch of tokens to match, though, because of
256 | 	 * possible backing-up.
257 | 	 *
258 | 	 * When we actually see the EOF, we change the status to "new"
259 | 	 * (via yyrestart()), so that the user can continue scanning by
260 | 	 * just pointing yyin at a new input file.
261 | 	 */
262 | #define YY_BUFFER_EOF_PENDING 2
263 | 
264 | 	};
265 | #endif /* !YY_STRUCT_YY_BUFFER_STATE */
266 | 
267 | /* Stack of input buffers. */
268 | static size_t yy_buffer_stack_top = 0; /**< index of top of stack. */
269 | static size_t yy_buffer_stack_max = 0; /**< capacity of stack. */
270 | static YY_BUFFER_STATE * yy_buffer_stack = NULL; /**< Stack as an array. */
271 | 
272 | /* We provide macros for accessing buffer states in case in the
273 |  * future we want to put the buffer states in a more general
274 |  * "scanner state".
275 |  *
276 |  * Returns the top of the stack, or NULL.
277 |  */
278 | #define YY_CURRENT_BUFFER ( (yy_buffer_stack) \
279 |                           ? (yy_buffer_stack)[(yy_buffer_stack_top)] \
280 |                           : NULL)
281 | /* Same as previous macro, but useful when we know that the buffer stack is not
282 |  * NULL or when we need an lvalue. For internal use only.
283 |  */
284 | #define YY_CURRENT_BUFFER_LVALUE (yy_buffer_stack)[(yy_buffer_stack_top)]
285 | 
286 | /* yy_hold_char holds the character lost when yytext is formed. */
287 | static char yy_hold_char;
288 | static int yy_n_chars;		/* number of characters read into yy_ch_buf */
289 | int yyleng;
290 | 
291 | /* Points to current character in buffer. */
292 | static char *yy_c_buf_p = NULL;
293 | static int yy_init = 0;		/* whether we need to initialize */
294 | static int yy_start = 0;	/* start state number */
295 | 
296 | /* Flag which is used to allow yywrap()'s to do buffer switches
297 |  * instead of setting up a fresh yyin.  A bit of a hack ...
298 |  */
299 | static int yy_did_buffer_switch_on_eof;
300 | 
301 | void yyrestart ( FILE *input_file  );
302 | void yy_switch_to_buffer ( YY_BUFFER_STATE new_buffer  );
303 | YY_BUFFER_STATE yy_create_buffer ( FILE *file, int size  );
304 | void yy_delete_buffer ( YY_BUFFER_STATE b  );
305 | void yy_flush_buffer ( YY_BUFFER_STATE b  );
306 | void yypush_buffer_state ( YY_BUFFER_STATE new_buffer  );
307 | void yypop_buffer_state ( void );
308 | 
309 | static void yyensure_buffer_stack ( void );
310 | static void yy_load_buffer_state ( void );
311 | static void yy_init_buffer ( YY_BUFFER_STATE b, FILE *file  );
312 | #define YY_FLUSH_BUFFER yy_flush_buffer( YY_CURRENT_BUFFER )
313 | 
314 | YY_BUFFER_STATE yy_scan_buffer ( char *base, yy_size_t size  );
315 | YY_BUFFER_STATE yy_scan_string ( const char *yy_str  );
316 | YY_BUFFER_STATE yy_scan_bytes ( const char *bytes, int len  );
317 | 
318 | void *yyalloc ( yy_size_t  );
319 | void *yyrealloc ( void *, yy_size_t  );
320 | void yyfree ( void *  );
321 | 
322 | #define yy_new_buffer yy_create_buffer
323 | #define yy_set_interactive(is_interactive) \
324 | 	{ \
325 | 	if ( ! YY_CURRENT_BUFFER ){ \
326 |         yyensure_buffer_stack (); \
327 | 		YY_CURRENT_BUFFER_LVALUE =    \
328 |             yy_create_buffer( yyin, YY_BUF_SIZE ); \
329 | 	} \
330 | 	YY_CURRENT_BUFFER_LVALUE->yy_is_interactive = is_interactive; \
331 | 	}
332 | #define yy_set_bol(at_bol) \
333 | 	{ \
334 | 	if ( ! YY_CURRENT_BUFFER ){\
335 |         yyensure_buffer_stack (); \
336 | 		YY_CURRENT_BUFFER_LVALUE =    \
337 |             yy_create_buffer( yyin, YY_BUF_SIZE ); \
338 | 	} \
339 | 	YY_CURRENT_BUFFER_LVALUE->yy_at_bol = at_bol; \
340 | 	}
341 | #define YY_AT_BOL() (YY_CURRENT_BUFFER_LVALUE->yy_at_bol)
342 | 
343 | /* Begin user sect3 */
344 | 
345 | #define yywrap() (/*CONSTCOND*/1)
346 | #define YY_SKIP_YYWRAP
347 | typedef flex_uint8_t YY_CHAR;
348 | 
349 | FILE *yyin = NULL, *yyout = NULL;
350 | 
351 | typedef int yy_state_type;
352 | 
353 | extern int yylineno;
354 | int yylineno = 1;
355 | 
356 | extern char *yytext;
357 | #ifdef yytext_ptr
358 | #undef yytext_ptr
359 | #endif
360 | #define yytext_ptr yytext
361 | 
362 | static yy_state_type yy_get_previous_state ( void );
363 | static yy_state_type yy_try_NUL_trans ( yy_state_type current_state  );
364 | static int yy_get_next_buffer ( void );
365 | static void yynoreturn yy_fatal_error ( const char* msg  );
366 | 
367 | /* Done after the current pattern has been matched and before the
368 |  * corresponding action - sets up yytext.
369 |  */
370 | #define YY_DO_BEFORE_ACTION \
371 | 	(yytext_ptr) = yy_bp; \
372 | 	yyleng = (int) (yy_cp - yy_bp); \
373 | 	(yy_hold_char) = *yy_cp; \
374 | 	*yy_cp = '\0'; \
375 | 	(yy_c_buf_p) = yy_cp;
376 | #define YY_NUM_RULES 50
377 | #define YY_END_OF_BUFFER 51
378 | /* This struct is not used in this scanner,
379 |    but its presence is necessary. */
380 | struct yy_trans_info
381 | 	{
382 | 	flex_int32_t yy_verify;
383 | 	flex_int32_t yy_nxt;
384 | 	};
385 | static const flex_int16_t yy_accept[193] =
386 |     {   0,
387 |         0,    0,   51,   49,    1,    1,   49,   49,   49,   47,
388 |         9,   10,   14,   13,   15,   46,   46,   46,   46,   46,
389 |        46,   46,   46,   46,   46,   46,   46,   46,   46,   46,
390 |        46,   11,   49,   12,   19,    0,   48,    0,   20,   47,
391 |        16,   18,   17,   46,   46,   46,   46,   46,   46,   46,
392 |        46,   46,   46,   46,    7,   46,   46,   46,   46,   46,
393 |        46,   46,   46,   46,   46,   46,   46,   46,   46,   21,
394 |        46,   46,   46,   46,   46,   46,   46,   46,   46,   46,
395 |        46,   46,   37,   46,   36,   46,   46,   46,   46,   46,
396 |        46,   46,   46,   46,   46,   46,   46,   46,   46,   39,
397 | 
398 |        46,   27,   46,   46,   46,   46,   46,   31,    2,   46,
399 |         6,   46,   46,   46,   46,   46,   46,   46,   38,   46,
400 |        46,   22,   46,   46,   46,   46,   46,   46,   46,   23,
401 |         8,    4,   46,   46,   46,   46,   46,   46,   30,   46,
402 |        46,   46,   46,   46,   46,   46,   46,   46,   46,   46,
403 |        46,   46,   25,   46,   46,   46,   46,   46,   46,   46,
404 |        46,   46,   45,   46,   43,   41,   46,   46,   46,   46,
405 |        46,   40,   46,    3,   46,   46,   46,   46,   28,   29,
406 |        46,   46,   33,   24,   32,   44,   26,   42,    5,   35,
407 |        34,    0
408 | 
409 |     } ;
410 | 
411 | static const YY_CHAR yy_ec[256] =
412 |     {   0,
413 |         1,    1,    1,    1,    1,    1,    1,    1,    2,    3,
414 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
415 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
416 |         1,    2,    4,    5,    1,    1,    1,    6,    1,    1,
417 |         1,    1,    1,    1,    1,    1,    1,    7,    7,    7,
418 |         7,    7,    7,    7,    7,    7,    7,    8,    9,   10,
419 |        11,   12,    1,    1,   13,   13,   13,   13,   13,   13,
420 |        13,   13,   13,   13,   13,   14,   13,   13,   13,   13,
421 |        13,   13,   13,   13,   13,   13,   13,   13,   13,   13,
422 |         1,   15,    1,    1,   13,    1,   16,   17,   18,   19,
423 | 
424 |        20,   21,   22,   23,   24,   13,   25,   26,   27,   28,
425 |        29,   30,   31,   32,   33,   34,   35,   36,   37,   38,
426 |        13,   13,   39,   40,   41,    1,    1,    1,    1,    1,
427 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
428 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
429 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
430 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
431 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
432 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
433 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
434 | 
435 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
436 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
437 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
438 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
439 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
440 |         1,    1,    1,    1,    1
441 |     } ;
442 | 
443 | static const YY_CHAR yy_meta[42] =
444 |     {   0,
445 |         1,    1,    1,    1,    1,    1,    2,    1,    1,    1,
446 |         1,    1,    2,    2,    1,    2,    2,    2,    2,    2,
447 |         2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
448 |         2,    2,    2,    2,    2,    2,    2,    2,    1,    1,
449 |         1
450 |     } ;
451 | 
452 | static const flex_int16_t yy_base[195] =
453 |     {   0,
454 |         0,    0,  204,  205,  205,  205,  192,   37,  196,  194,
455 |       205,  205,  189,  188,  187,    0,  178,   20,   28,   18,
456 |        22,  175,   37,  160,  164,  177,   38,   35,  172,  158,
457 |       174,  205,  149,  205,  205,   51,  205,  185,  205,  180,
458 |       205,  205,  205,    0,  167,  165,   36,  150,  162,  153,
459 |       165,  148,   39,  147,    0,  140,  143,  148,  148,  140,
460 |        37,  154,  141,  134,  152,  137,  130,  147,  140,  205,
461 |       133,  146,  130,  141,  141,  144,  129,  134,  128,  130,
462 |       135,  127,  139,  136,  137,  133,  125,  115,  113,  122,
463 |       110,  111,  109,  122,  107,  108,  115,  118,  112,    0,
464 | 
465 |       112,    0,  100,  115,  107,  100,  112,    0,    0,  110,
466 |         0,  109,  108,   98,   89,  105,   95,   99,    0,   98,
467 |        93,  104,   91,   99,   84,   99,   83,   88,   84,    0,
468 |         0,    0,   84,   83,   78,   81,   79,   75,    0,   74,
469 |        76,   82,   71,   86,   85,   67,   70,   71,   63,   59,
470 |        73,   72,    0,   77,   60,   63,   70,   61,   54,   67,
471 |        59,   51,    0,   46,    0,    0,   55,   48,   47,   54,
472 |        60,    0,   59,    0,   54,   60,   55,   54,    0,    0,
473 |        45,   40,    0,    0,    0,    0,    0,    0,    0,    0,
474 |         0,  205,   71,   45
475 | 
476 |     } ;
477 | 
478 | static const flex_int16_t yy_def[195] =
479 |     {   0,
480 |       192,    1,  192,  192,  192,  192,  192,  193,  192,  192,
481 |       192,  192,  192,  192,  192,  194,  194,  194,  194,  194,
482 |       194,  194,  194,  194,  194,  194,  194,  194,  194,  194,
483 |       194,  192,  192,  192,  192,  193,  192,  193,  192,  192,
484 |       192,  192,  192,  194,  194,  194,  194,  194,  194,  194,
485 |       194,  194,  194,  194,  194,  194,  194,  194,  194,  194,
486 |       194,  194,  194,  194,  194,  194,  194,  194,  194,  192,
487 |       194,  194,  194,  194,  194,  194,  194,  194,  194,  194,
488 |       194,  194,  194,  194,  194,  194,  194,  194,  194,  194,
489 |       194,  194,  194,  194,  194,  194,  194,  194,  194,  194,
490 | 
491 |       194,  194,  194,  194,  194,  194,  194,  194,  194,  194,
492 |       194,  194,  194,  194,  194,  194,  194,  194,  194,  194,
493 |       194,  194,  194,  194,  194,  194,  194,  194,  194,  194,
494 |       194,  194,  194,  194,  194,  194,  194,  194,  194,  194,
495 |       194,  194,  194,  194,  194,  194,  194,  194,  194,  194,
496 |       194,  194,  194,  194,  194,  194,  194,  194,  194,  194,
497 |       194,  194,  194,  194,  194,  194,  194,  194,  194,  194,
498 |       194,  194,  194,  194,  194,  194,  194,  194,  194,  194,
499 |       194,  194,  194,  194,  194,  194,  194,  194,  194,  194,
500 |       194,    0,  192,  192
501 | 
502 |     } ;
503 | 
504 | static const flex_int16_t yy_nxt[247] =
505 |     {   0,
506 |         4,    5,    6,    7,    8,    9,   10,   11,   12,   13,
507 |        14,   15,   16,   16,    4,   17,   16,   18,   19,   20,
508 |        21,   16,   16,   22,   16,   16,   23,   24,   25,   26,
509 |        16,   27,   28,   29,   30,   31,   16,   16,   32,   33,
510 |        34,   37,   46,   48,   51,   53,   44,   49,   47,   52,
511 |        54,   38,   56,   62,   65,   37,   57,   63,   80,   50,
512 |        58,   73,  191,   74,   81,   38,   64,  190,   66,   88,
513 |        89,   36,   36,  189,  188,  187,  186,  185,  184,  183,
514 |       182,  181,  180,  179,  178,  177,  176,  175,  174,  173,
515 |       172,  171,  170,  169,  168,  167,  166,  165,  164,  163,
516 | 
517 |       162,  161,  160,  159,  158,  157,  156,  155,  154,  153,
518 |       152,  151,  150,  149,  148,  147,  146,  145,  144,  143,
519 |       142,  141,  140,  139,  138,  137,  136,  135,  134,  133,
520 |       132,  131,  130,  129,  128,  127,  126,  125,  124,  123,
521 |       122,  121,  120,  119,  118,  117,  116,  115,  114,  113,
522 |       112,  111,  110,  109,  108,  107,  106,  105,  104,  103,
523 |       102,  101,  100,   99,   98,   97,   96,   95,   94,   93,
524 |        92,   91,   90,   87,   86,   85,   84,   83,   82,   79,
525 |        78,   77,   76,   75,   72,   71,   40,  192,   70,   69,
526 |        68,   67,   61,   60,   59,   55,   45,   43,   42,   41,
527 | 
528 |        40,   39,   35,  192,    3,  192,  192,  192,  192,  192,
529 |       192,  192,  192,  192,  192,  192,  192,  192,  192,  192,
530 |       192,  192,  192,  192,  192,  192,  192,  192,  192,  192,
531 |       192,  192,  192,  192,  192,  192,  192,  192,  192,  192,
532 |       192,  192,  192,  192,  192,  192
533 |     } ;
534 | 
535 | static const flex_int16_t yy_chk[247] =
536 |     {   0,
537 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
538 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
539 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
540 |         1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
541 |         1,    8,   18,   19,   20,   21,  194,   19,   18,   20,
542 |        21,    8,   23,   27,   28,   36,   23,   27,   53,   19,
543 |        23,   47,  182,   47,   53,   36,   27,  181,   28,   61,
544 |        61,  193,  193,  178,  177,  176,  175,  173,  171,  170,
545 |       169,  168,  167,  164,  162,  161,  160,  159,  158,  157,
546 |       156,  155,  154,  152,  151,  150,  149,  148,  147,  146,
547 | 
548 |       145,  144,  143,  142,  141,  140,  138,  137,  136,  135,
549 |       134,  133,  129,  128,  127,  126,  125,  124,  123,  122,
550 |       121,  120,  118,  117,  116,  115,  114,  113,  112,  110,
551 |       107,  106,  105,  104,  103,  101,   99,   98,   97,   96,
552 |        95,   94,   93,   92,   91,   90,   89,   88,   87,   86,
553 |        85,   84,   83,   82,   81,   80,   79,   78,   77,   76,
554 |        75,   74,   73,   72,   71,   69,   68,   67,   66,   65,
555 |        64,   63,   62,   60,   59,   58,   57,   56,   54,   52,
556 |        51,   50,   49,   48,   46,   45,   40,   38,   33,   31,
557 |        30,   29,   26,   25,   24,   22,   17,   15,   14,   13,
558 | 
559 |        10,    9,    7,    3,  192,  192,  192,  192,  192,  192,
560 |       192,  192,  192,  192,  192,  192,  192,  192,  192,  192,
561 |       192,  192,  192,  192,  192,  192,  192,  192,  192,  192,
562 |       192,  192,  192,  192,  192,  192,  192,  192,  192,  192,
563 |       192,  192,  192,  192,  192,  192
564 |     } ;
565 | 
566 | /* Table of booleans, true if rule could match eol. */
567 | static const flex_int32_t yy_rule_can_match_eol[51] =
568 |     {   0,
569 | 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
570 |     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
571 |     0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,     };
572 | 
573 | static yy_state_type yy_last_accepting_state;
574 | static char *yy_last_accepting_cpos;
575 | 
576 | extern int yy_flex_debug;
577 | int yy_flex_debug = 0;
578 | 
579 | /* The intent behind this definition is that it'll catch
580 |  * any uses of REJECT which flex missed.
581 |  */
582 | #define REJECT reject_used_but_not_detected
583 | #define yymore() yymore_used_but_not_detected
584 | #define YY_MORE_ADJ 0
585 | #define YY_RESTORE_YY_MORE_OFFSET
586 | char *yytext;
587 | #line 1 "lexer.l"
588 | #line 2 "lexer.l"
589 | #include <stdio.h>
590 | #include <stdlib.h>
591 | #include <string.h>
592 | #include "formLang.h"
593 | #include "y.tab.h"
594 | 
595 | extern YYSTYPE yylval;
596 | 
597 | // Context tracking
598 | int after_colon = 0;
599 | 
600 | // Error handling
601 | void syntax_error(const char* msg) {
602 |     fprintf(stderr, "Syntax error at line %d: %s\n", yylineno, msg);
603 | }
604 | 
605 | // String handling
606 | char* process_string(const char* input) {
607 |     char* output = malloc(strlen(input) + 1);
608 |     int i = 0, j = 0;
609 |     
610 |     while (input[i] != '\0') {
611 |         if (input[i] == '\\') {
612 |             i++;
613 |             switch (input[i]) {
614 |                 case 'n': output[j++] = '\n'; break;
615 |                 case 't': output[j++] = '\t'; break;
616 |                 case 'r': output[j++] = '\r'; break;
617 |                 case '\\': output[j++] = '\\'; break;
618 |                 case '"': output[j++] = '"'; break;
619 |                 default: output[j++] = input[i]; break;
620 |             }
621 |         } else {
622 |             output[j++] = input[i];
623 |         }
624 |         i++;
625 |     }
626 |     output[j] = '\0';
627 |     return output;
628 | }
629 | #line 630 "lex.yy.c"
630 | #define YY_NO_INPUT 1
631 | #line 632 "lex.yy.c"
632 | 
633 | #define INITIAL 0
634 | 
635 | #ifndef YY_NO_UNISTD_H
636 | /* Special case for "unistd.h", since it is non-ANSI. We include it way
637 |  * down here because we want the user's section 1 to have been scanned first.
638 |  * The user has a chance to override it with an option.
639 |  */
640 | #include <unistd.h>
641 | #endif
642 | 
643 | #ifndef YY_EXTRA_TYPE
644 | #define YY_EXTRA_TYPE void *
645 | #endif
646 | 
647 | static int yy_init_globals ( void );
648 | 
649 | /* Accessor methods to globals.
650 |    These are made visible to non-reentrant scanners for convenience. */
651 | 
652 | int yylex_destroy ( void );
653 | 
654 | int yyget_debug ( void );
655 | 
656 | void yyset_debug ( int debug_flag  );
657 | 
658 | YY_EXTRA_TYPE yyget_extra ( void );
659 | 
660 | void yyset_extra ( YY_EXTRA_TYPE user_defined  );
661 | 
662 | FILE *yyget_in ( void );
663 | 
664 | void yyset_in  ( FILE * _in_str  );
665 | 
666 | FILE *yyget_out ( void );
667 | 
668 | void yyset_out  ( FILE * _out_str  );
669 | 
670 | 			int yyget_leng ( void );
671 | 
672 | char *yyget_text ( void );
673 | 
674 | int yyget_lineno ( void );
675 | 
676 | void yyset_lineno ( int _line_number  );
677 | 
678 | /* Macros after this point can all be overridden by user definitions in
679 |  * section 1.
680 |  */
681 | 
682 | #ifndef YY_SKIP_YYWRAP
683 | #ifdef __cplusplus
684 | extern "C" int yywrap ( void );
685 | #else
686 | extern int yywrap ( void );
687 | #endif
688 | #endif
689 | 
690 | #ifndef YY_NO_UNPUT
691 |     
692 | #endif
693 | 
694 | #ifndef yytext_ptr
695 | static void yy_flex_strncpy ( char *, const char *, int );
696 | #endif
697 | 
698 | #ifdef YY_NEED_STRLEN
699 | static int yy_flex_strlen ( const char * );
700 | #endif
701 | 
702 | #ifndef YY_NO_INPUT
703 | #ifdef __cplusplus
704 | static int yyinput ( void );
705 | #else
706 | static int input ( void );
707 | #endif
708 | 
709 | #endif
710 | 
711 | /* Amount of stuff to slurp up with each read. */
712 | #ifndef YY_READ_BUF_SIZE
713 | #ifdef __ia64__
714 | /* On IA-64, the buffer size is 16k, not 8k */
715 | #define YY_READ_BUF_SIZE 16384
716 | #else
717 | #define YY_READ_BUF_SIZE 8192
718 | #endif /* __ia64__ */
719 | #endif
720 | 
721 | /* Copy whatever the last rule matched to the standard output. */
722 | #ifndef ECHO
723 | /* This used to be an fputs(), but since the string might contain NUL's,
724 |  * we now use fwrite().
725 |  */
726 | #define ECHO do { if (fwrite( yytext, (size_t) yyleng, 1, yyout )) {} } while (0)
727 | #endif
728 | 
729 | /* Gets input and stuffs it into "buf".  number of characters read, or YY_NULL,
730 |  * is returned in "result".
731 |  */
732 | #ifndef YY_INPUT
733 | #define YY_INPUT(buf,result,max_size) \
734 | 	if ( YY_CURRENT_BUFFER_LVALUE->yy_is_interactive ) \
735 | 		{ \
736 | 		int c = '*'; \
737 | 		int n; \
738 | 		for ( n = 0; n < max_size && \
739 | 			     (c = getc( yyin )) != EOF && c != '\n'; ++n ) \
740 | 			buf[n] = (char) c; \
741 | 		if ( c == '\n' ) \
742 | 			buf[n++] = (char) c; \
743 | 		if ( c == EOF && ferror( yyin ) ) \
744 | 			YY_FATAL_ERROR( "input in flex scanner failed" ); \
745 | 		result = n; \
746 | 		} \
747 | 	else \
748 | 		{ \
749 | 		errno=0; \
750 | 		while ( (result = (int) fread(buf, 1, (yy_size_t) max_size, yyin)) == 0 && ferror(yyin)) \
751 | 			{ \
752 | 			if( errno != EINTR) \
753 | 				{ \
754 | 				YY_FATAL_ERROR( "input in flex scanner failed" ); \
755 | 				break; \
756 | 				} \
757 | 			errno=0; \
758 | 			clearerr(yyin); \
759 | 			} \
760 | 		}\
761 | \
762 | 
763 | #endif
764 | 
765 | /* No semi-colon after return; correct usage is to write "yyterminate();" -
766 |  * we don't want an extra ';' after the "return" because that will cause
767 |  * some compilers to complain about unreachable statements.
768 |  */
769 | #ifndef yyterminate
770 | #define yyterminate() return YY_NULL
771 | #endif
772 | 
773 | /* Number of entries by which start-condition stack grows. */
774 | #ifndef YY_START_STACK_INCR
775 | #define YY_START_STACK_INCR 25
776 | #endif
777 | 
778 | /* Report a fatal error. */
779 | #ifndef YY_FATAL_ERROR
780 | #define YY_FATAL_ERROR(msg) yy_fatal_error( msg )
781 | #endif
782 | 
783 | /* end tables serialization structures and prototypes */
784 | 
785 | /* Default declaration of generated scanner - a define so the user can
786 |  * easily add parameters.
787 |  */
788 | #ifndef YY_DECL
789 | #define YY_DECL_IS_OURS 1
790 | 
791 | extern int yylex (void);
792 | 
793 | #define YY_DECL int yylex (void)
794 | #endif /* !YY_DECL */
795 | 
796 | /* Code executed at the beginning of each rule, after yytext and yyleng
797 |  * have been set up.
798 |  */
799 | #ifndef YY_USER_ACTION
800 | #define YY_USER_ACTION
801 | #endif
802 | 
803 | /* Code executed at the end of each rule. */
804 | #ifndef YY_BREAK
805 | #define YY_BREAK /*LINTED*/break;
806 | #endif
807 | 
808 | #define YY_RULE_SETUP \
809 | 	YY_USER_ACTION
810 | 
811 | /** The main scanner function which does all the work.
812 |  */
813 | YY_DECL
814 | {
815 | 	yy_state_type yy_current_state;
816 | 	char *yy_cp, *yy_bp;
817 | 	int yy_act;
818 |     
819 | 	if ( !(yy_init) )
820 | 		{
821 | 		(yy_init) = 1;
822 | 
823 | #ifdef YY_USER_INIT
824 | 		YY_USER_INIT;
825 | #endif
826 | 
827 | 		if ( ! (yy_start) )
828 | 			(yy_start) = 1;	/* first start state */
829 | 
830 | 		if ( ! yyin )
831 | 			yyin = stdin;
832 | 
833 | 		if ( ! yyout )
834 | 			yyout = stdout;
835 | 
836 | 		if ( ! YY_CURRENT_BUFFER ) {
837 | 			yyensure_buffer_stack ();
838 | 			YY_CURRENT_BUFFER_LVALUE =
839 | 				yy_create_buffer( yyin, YY_BUF_SIZE );
840 | 		}
841 | 
842 | 		yy_load_buffer_state(  );
843 | 		}
844 | 
845 | 	{
846 | #line 49 "lexer.l"
847 | 
848 | 
849 | #line 850 "lex.yy.c"
850 | 
851 | 	while ( /*CONSTCOND*/1 )		/* loops until end-of-file is reached */
852 | 		{
853 | 		yy_cp = (yy_c_buf_p);
854 | 
855 | 		/* Support of yytext. */
856 | 		*yy_cp = (yy_hold_char);
857 | 
858 | 		/* yy_bp points to the position in yy_ch_buf of the start of
859 | 		 * the current run.
860 | 		 */
861 | 		yy_bp = yy_cp;
862 | 
863 | 		yy_current_state = (yy_start);
864 | yy_match:
865 | 		do
866 | 			{
867 | 			YY_CHAR yy_c = yy_ec[YY_SC_TO_UI(*yy_cp)] ;
868 | 			if ( yy_accept[yy_current_state] )
869 | 				{
870 | 				(yy_last_accepting_state) = yy_current_state;
871 | 				(yy_last_accepting_cpos) = yy_cp;
872 | 				}
873 | 			while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
874 | 				{
875 | 				yy_current_state = (int) yy_def[yy_current_state];
876 | 				if ( yy_current_state >= 193 )
877 | 					yy_c = yy_meta[yy_c];
878 | 				}
879 | 			yy_current_state = yy_nxt[yy_base[yy_current_state] + yy_c];
880 | 			++yy_cp;
881 | 			}
882 | 		while ( yy_base[yy_current_state] != 205 );
883 | 
884 | yy_find_action:
885 | 		yy_act = yy_accept[yy_current_state];
886 | 		if ( yy_act == 0 )
887 | 			{ /* have to back up */
888 | 			yy_cp = (yy_last_accepting_cpos);
889 | 			yy_current_state = (yy_last_accepting_state);
890 | 			yy_act = yy_accept[yy_current_state];
891 | 			}
892 | 
893 | 		YY_DO_BEFORE_ACTION;
894 | 
895 | 		if ( yy_act != YY_END_OF_BUFFER && yy_rule_can_match_eol[yy_act] )
896 | 			{
897 | 			int yyl;
898 | 			for ( yyl = 0; yyl < yyleng; ++yyl )
899 | 				if ( yytext[yyl] == '\n' )
900 | 					
901 |     yylineno++;
902 | ;
903 | 			}
904 | 
905 | do_action:	/* This label is used only to access EOF actions. */
906 | 
907 | 		switch ( yy_act )
908 | 	{ /* beginning of action switch */
909 | 			case 0: /* must back up */
910 | 			/* undo the effects of YY_DO_BEFORE_ACTION */
911 | 			*yy_cp = (yy_hold_char);
912 | 			yy_cp = (yy_last_accepting_cpos);
913 | 			yy_current_state = (yy_last_accepting_state);
914 | 			goto yy_find_action;
915 | 
916 | case 1:
917 | /* rule 1 can match eol */
918 | YY_RULE_SETUP
919 | #line 51 "lexer.l"
920 | ; /* Skip whitespace and newlines */
921 | 	YY_BREAK
922 | case 2:
923 | YY_RULE_SETUP
924 | #line 53 "lexer.l"
925 | { return FORM; }
926 | 	YY_BREAK
927 | case 3:
928 | YY_RULE_SETUP
929 | #line 54 "lexer.l"
930 | { return SECTION; }
931 | 	YY_BREAK
932 | case 4:
933 | YY_RULE_SETUP
934 | #line 55 "lexer.l"
935 | { return FIELD; }
936 | 	YY_BREAK
937 | case 5:
938 | YY_RULE_SETUP
939 | #line 56 "lexer.l"
940 | { return VALIDATE; }
941 | 	YY_BREAK
942 | case 6:
943 | YY_RULE_SETUP
944 | #line 57 "lexer.l"
945 | { return META; }
946 | 	YY_BREAK
947 | case 7:
948 | YY_RULE_SETUP
949 | #line 58 "lexer.l"
950 | { return IF; }
951 | 	YY_BREAK
952 | case 8:
953 | YY_RULE_SETUP
954 | #line 59 "lexer.l"
955 | { return ERROR; }
956 | 	YY_BREAK
957 | case 9:
958 | YY_RULE_SETUP
959 | #line 60 "lexer.l"
960 | { after_colon = 1; return ':'; }
961 | 	YY_BREAK
962 | case 10:
963 | YY_RULE_SETUP
964 | #line 61 "lexer.l"
965 | { after_colon = 0; return ';'; }
966 | 	YY_BREAK
967 | case 11:
968 | YY_RULE_SETUP
969 | #line 62 "lexer.l"
970 | { return '{'; }
971 | 	YY_BREAK
972 | case 12:
973 | YY_RULE_SETUP
974 | #line 63 "lexer.l"
975 | { return '}'; }
976 | 	YY_BREAK
977 | case 13:
978 | YY_RULE_SETUP
979 | #line 64 "lexer.l"
980 | { return '='; }
981 | 	YY_BREAK
982 | case 14:
983 | YY_RULE_SETUP
984 | #line 65 "lexer.l"
985 | { return LT; }
986 | 	YY_BREAK
987 | case 15:
988 | YY_RULE_SETUP
989 | #line 66 "lexer.l"
990 | { return GT; }
991 | 	YY_BREAK
992 | case 16:
993 | YY_RULE_SETUP
994 | #line 67 "lexer.l"
995 | { return LTE; }
996 | 	YY_BREAK
997 | case 17:
998 | YY_RULE_SETUP
999 | #line 68 "lexer.l"
1000 | { return GTE; }
1001 | 	YY_BREAK
1002 | case 18:
1003 | YY_RULE_SETUP
1004 | #line 69 "lexer.l"
1005 | { return EQ; }
1006 | 	YY_BREAK
1007 | case 19:
1008 | YY_RULE_SETUP
1009 | #line 70 "lexer.l"
1010 | { return NEQ; }
1011 | 	YY_BREAK
1012 | case 20:
1013 | YY_RULE_SETUP
1014 | #line 71 "lexer.l"
1015 | { return AND; }
1016 | 	YY_BREAK
1017 | case 21:
1018 | YY_RULE_SETUP
1019 | #line 72 "lexer.l"
1020 | { return OR; }
1021 | 	YY_BREAK
1022 | case 22:
1023 | YY_RULE_SETUP
1024 | #line 74 "lexer.l"
1025 | { 
1026 |     if (after_colon) {
1027 |         after_colon = 0;
1028 |         return TEXT;
1029 |     }
1030 |     yylval.str = strdup(yytext);
1031 |     return IDENTIFIER;
1032 | }
1033 | 	YY_BREAK
1034 | case 23:
1035 | YY_RULE_SETUP
1036 | #line 82 "lexer.l"
1037 | { 
1038 |     if (after_colon) {
1039 |         after_colon = 0;
1040 |         return EMAIL;
1041 |     }
1042 |     yylval.str = strdup(yytext);
1043 |     return IDENTIFIER;
1044 | }
1045 | 	YY_BREAK
1046 | case 24:
1047 | YY_RULE_SETUP
1048 | #line 90 "lexer.l"
1049 | { 
1050 |     if (after_colon) {
1051 |         after_colon = 0;
1052 |         return PASSWORD;
1053 |     }
1054 |     yylval.str = strdup(yytext);
1055 |     return IDENTIFIER;
1056 | }
1057 | 	YY_BREAK
1058 | case 25:
1059 | YY_RULE_SETUP
1060 | #line 98 "lexer.l"
1061 | { 
1062 |     if (after_colon) {
1063 |         after_colon = 0;
1064 |         return NUMBER;
1065 |     }
1066 |     yylval.str = strdup(yytext);
1067 |     return IDENTIFIER;
1068 | }
1069 | 	YY_BREAK
1070 | case 26:
1071 | YY_RULE_SETUP
1072 | #line 106 "lexer.l"
1073 | { 
1074 |     if (after_colon) {
1075 |         after_colon = 0;
1076 |         return TEXTAREA;
1077 |     }
1078 |     yylval.str = strdup(yytext);
1079 |     return IDENTIFIER;
1080 | }
1081 | 	YY_BREAK
1082 | case 27:
1083 | YY_RULE_SETUP
1084 | #line 114 "lexer.l"
1085 | { 
1086 |     if (after_colon) {
1087 |         after_colon = 0;
1088 |         return DATE;
1089 |     }
1090 |     yylval.str = strdup(yytext);
1091 |     return IDENTIFIER;
1092 | }
1093 | 	YY_BREAK
1094 | case 28:
1095 | YY_RULE_SETUP
1096 | #line 122 "lexer.l"
1097 | { 
1098 |     if (after_colon) {
1099 |         after_colon = 0;
1100 |         return CHECKBOX;
1101 |     }
1102 |     yylval.str = strdup(yytext);
1103 |     return IDENTIFIER;
1104 | }
1105 | 	YY_BREAK
1106 | case 29:
1107 | YY_RULE_SETUP
1108 | #line 130 "lexer.l"
1109 | { 
1110 |     if (after_colon) {
1111 |         after_colon = 0;
1112 |         return DROPDOWN;
1113 |     }
1114 |     yylval.str = strdup(yytext);
1115 |     return IDENTIFIER;
1116 | }
1117 | 	YY_BREAK
1118 | case 30:
1119 | YY_RULE_SETUP
1120 | #line 138 "lexer.l"
1121 | { 
1122 |     if (after_colon) {
1123 |         after_colon = 0;
1124 |         return RADIO;
1125 |     }
1126 |     yylval.str = strdup(yytext);
1127 |     return IDENTIFIER;
1128 | }
1129 | 	YY_BREAK
1130 | case 31:
1131 | YY_RULE_SETUP
1132 | #line 146 "lexer.l"
1133 | { 
1134 |     if (after_colon) {
1135 |         after_colon = 0;
1136 |         return FILE_TYPE;
1137 |     }
1138 |     yylval.str = strdup(yytext);
1139 |     return IDENTIFIER;
1140 | }
1141 | 	YY_BREAK
1142 | case 32:
1143 | YY_RULE_SETUP
1144 | #line 155 "lexer.l"
1145 | { return REQUIRED; }
1146 | 	YY_BREAK
1147 | case 33:
1148 | YY_RULE_SETUP
1149 | #line 156 "lexer.l"
1150 | { return OPTIONAL; }
1151 | 	YY_BREAK
1152 | case 34:
1153 | YY_RULE_SETUP
1154 | #line 157 "lexer.l"
1155 | { return MINLENGTH; }
1156 | 	YY_BREAK
1157 | case 35:
1158 | YY_RULE_SETUP
1159 | #line 158 "lexer.l"
1160 | { return MAXLENGTH; }
1161 | 	YY_BREAK
1162 | case 36:
1163 | YY_RULE_SETUP
1164 | #line 159 "lexer.l"
1165 | { return MIN; }
1166 | 	YY_BREAK
1167 | case 37:
1168 | YY_RULE_SETUP
1169 | #line 160 "lexer.l"
1170 | { return MAX; }
1171 | 	YY_BREAK
1172 | case 38:
1173 | YY_RULE_SETUP
1174 | #line 161 "lexer.l"
1175 | { return ROWS; }
1176 | 	YY_BREAK
1177 | case 39:
1178 | YY_RULE_SETUP
1179 | #line 162 "lexer.l"
1180 | { return COLS; }
1181 | 	YY_BREAK
1182 | case 40:
1183 | YY_RULE_SETUP
1184 | #line 163 "lexer.l"
1185 | { return PATTERN; }
1186 | 	YY_BREAK
1187 | case 41:
1188 | YY_RULE_SETUP
1189 | #line 164 "lexer.l"
1190 | { return DEFAULT; }
1191 | 	YY_BREAK
1192 | case 42:
1193 | YY_RULE_SETUP
1194 | #line 166 "lexer.l"
1195 | {
1196 |     if (after_colon) {
1197 |         after_colon = 0;
1198 |         return USERNAME;
1199 |     }
1200 |     yylval.str = strdup(yytext);
1201 |     return IDENTIFIER;
1202 | }
1203 | 	YY_BREAK
1204 | case 43:
1205 | YY_RULE_SETUP
1206 | #line 174 "lexer.l"
1207 | { return CONFIRM; }
1208 | 	YY_BREAK
1209 | case 44:
1210 | YY_RULE_SETUP
1211 | #line 175 "lexer.l"
1212 | { return STRENGTH; }
1213 | 	YY_BREAK
1214 | case 45:
1215 | YY_RULE_SETUP
1216 | #line 176 "lexer.l"
1217 | {
1218 |     if (after_colon) {
1219 |         after_colon = 0;
1220 |         return ADDRESS;
1221 |     }
1222 |     yylval.str = strdup(yytext);
1223 |     return IDENTIFIER;
1224 | }
1225 | 	YY_BREAK
1226 | case 46:
1227 | YY_RULE_SETUP
1228 | #line 185 "lexer.l"
1229 | { 
1230 |     yylval.str = strdup(yytext);
1231 |     return IDENTIFIER;
1232 | }
1233 | 	YY_BREAK
1234 | case 47:
1235 | YY_RULE_SETUP
1236 | #line 190 "lexer.l"
1237 | {
1238 |     yylval.num = atoi(yytext);
1239 |     return NUMBER_LITERAL;
1240 | }
1241 | 	YY_BREAK
1242 | case 48:
1243 | /* rule 48 can match eol */
1244 | YY_RULE_SETUP
1245 | #line 195 "lexer.l"
1246 | {
1247 |     // Remove quotes and process escaped characters
1248 |     yytext[strlen(yytext) - 1] = '\0';
1249 |     yylval.str = process_string(yytext + 1);
1250 |     return STRING_LITERAL;
1251 | }
1252 | 	YY_BREAK
1253 | case 49:
1254 | YY_RULE_SETUP
1255 | #line 202 "lexer.l"
1256 | { 
1257 |     syntax_error("Unexpected character");
1258 |     return yytext[0]; 
1259 | }
1260 | 	YY_BREAK
1261 | case 50:
1262 | YY_RULE_SETUP
1263 | #line 207 "lexer.l"
1264 | ECHO;
1265 | 	YY_BREAK
1266 | #line 1267 "lex.yy.c"
1267 | case YY_STATE_EOF(INITIAL):
1268 | 	yyterminate();
1269 | 
1270 | 	case YY_END_OF_BUFFER:
1271 | 		{
1272 | 		/* Amount of text matched not including the EOB char. */
1273 | 		int yy_amount_of_matched_text = (int) (yy_cp - (yytext_ptr)) - 1;
1274 | 
1275 | 		/* Undo the effects of YY_DO_BEFORE_ACTION. */
1276 | 		*yy_cp = (yy_hold_char);
1277 | 		YY_RESTORE_YY_MORE_OFFSET
1278 | 
1279 | 		if ( YY_CURRENT_BUFFER_LVALUE->yy_buffer_status == YY_BUFFER_NEW )
1280 | 			{
1281 | 			/* We're scanning a new file or input source.  It's
1282 | 			 * possible that this happened because the user
1283 | 			 * just pointed yyin at a new source and called
1284 | 			 * yylex().  If so, then we have to assure
1285 | 			 * consistency between YY_CURRENT_BUFFER and our
1286 | 			 * globals.  Here is the right place to do so, because
1287 | 			 * this is the first action (other than possibly a
1288 | 			 * back-up) that will match for the new input source.
1289 | 			 */
1290 | 			(yy_n_chars) = YY_CURRENT_BUFFER_LVALUE->yy_n_chars;
1291 | 			YY_CURRENT_BUFFER_LVALUE->yy_input_file = yyin;
1292 | 			YY_CURRENT_BUFFER_LVALUE->yy_buffer_status = YY_BUFFER_NORMAL;
1293 | 			}
1294 | 
1295 | 		/* Note that here we test for yy_c_buf_p "<=" to the position
1296 | 		 * of the first EOB in the buffer, since yy_c_buf_p will
1297 | 		 * already have been incremented past the NUL character
1298 | 		 * (since all states make transitions on EOB to the
1299 | 		 * end-of-buffer state).  Contrast this with the test
1300 | 		 * in input().
1301 | 		 */
1302 | 		if ( (yy_c_buf_p) <= &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[(yy_n_chars)] )
1303 | 			{ /* This was really a NUL. */
1304 | 			yy_state_type yy_next_state;
1305 | 
1306 | 			(yy_c_buf_p) = (yytext_ptr) + yy_amount_of_matched_text;
1307 | 
1308 | 			yy_current_state = yy_get_previous_state(  );
1309 | 
1310 | 			/* Okay, we're now positioned to make the NUL
1311 | 			 * transition.  We couldn't have
1312 | 			 * yy_get_previous_state() go ahead and do it
1313 | 			 * for us because it doesn't know how to deal
1314 | 			 * with the possibility of jamming (and we don't
1315 | 			 * want to build jamming into it because then it
1316 | 			 * will run more slowly).
1317 | 			 */
1318 | 
1319 | 			yy_next_state = yy_try_NUL_trans( yy_current_state );
1320 | 
1321 | 			yy_bp = (yytext_ptr) + YY_MORE_ADJ;
1322 | 
1323 | 			if ( yy_next_state )
1324 | 				{
1325 | 				/* Consume the NUL. */
1326 | 				yy_cp = ++(yy_c_buf_p);
1327 | 				yy_current_state = yy_next_state;
1328 | 				goto yy_match;
1329 | 				}
1330 | 
1331 | 			else
1332 | 				{
1333 | 				yy_cp = (yy_c_buf_p);
1334 | 				goto yy_find_action;
1335 | 				}
1336 | 			}
1337 | 
1338 | 		else switch ( yy_get_next_buffer(  ) )
1339 | 			{
1340 | 			case EOB_ACT_END_OF_FILE:
1341 | 				{
1342 | 				(yy_did_buffer_switch_on_eof) = 0;
1343 | 
1344 | 				if ( yywrap(  ) )
1345 | 					{
1346 | 					/* Note: because we've taken care in
1347 | 					 * yy_get_next_buffer() to have set up
1348 | 					 * yytext, we can now set up
1349 | 					 * yy_c_buf_p so that if some total
1350 | 					 * hoser (like flex itself) wants to
1351 | 					 * call the scanner after we return the
1352 | 					 * YY_NULL, it'll still work - another
1353 | 					 * YY_NULL will get returned.
1354 | 					 */
1355 | 					(yy_c_buf_p) = (yytext_ptr) + YY_MORE_ADJ;
1356 | 
1357 | 					yy_act = YY_STATE_EOF(YY_START);
1358 | 					goto do_action;
1359 | 					}
1360 | 
1361 | 				else
1362 | 					{
1363 | 					if ( ! (yy_did_buffer_switch_on_eof) )
1364 | 						YY_NEW_FILE;
1365 | 					}
1366 | 				break;
1367 | 				}
1368 | 
1369 | 			case EOB_ACT_CONTINUE_SCAN:
1370 | 				(yy_c_buf_p) =
1371 | 					(yytext_ptr) + yy_amount_of_matched_text;
1372 | 
1373 | 				yy_current_state = yy_get_previous_state(  );
1374 | 
1375 | 				yy_cp = (yy_c_buf_p);
1376 | 				yy_bp = (yytext_ptr) + YY_MORE_ADJ;
1377 | 				goto yy_match;
1378 | 
1379 | 			case EOB_ACT_LAST_MATCH:
1380 | 				(yy_c_buf_p) =
1381 | 				&YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[(yy_n_chars)];
1382 | 
1383 | 				yy_current_state = yy_get_previous_state(  );
1384 | 
1385 | 				yy_cp = (yy_c_buf_p);
1386 | 				yy_bp = (yytext_ptr) + YY_MORE_ADJ;
1387 | 				goto yy_find_action;
1388 | 			}
1389 | 		break;
1390 | 		}
1391 | 
1392 | 	default:
1393 | 		YY_FATAL_ERROR(
1394 | 			"fatal flex scanner internal error--no action found" );
1395 | 	} /* end of action switch */
1396 | 		} /* end of scanning one token */
1397 | 	} /* end of user's declarations */
1398 | } /* end of yylex */
1399 | 
1400 | /* yy_get_next_buffer - try to read in a new buffer
1401 |  *
1402 |  * Returns a code representing an action:
1403 |  *	EOB_ACT_LAST_MATCH -
1404 |  *	EOB_ACT_CONTINUE_SCAN - continue scanning from current position
1405 |  *	EOB_ACT_END_OF_FILE - end of file
1406 |  */
1407 | static int yy_get_next_buffer (void)
1408 | {
1409 |     	char *dest = YY_CURRENT_BUFFER_LVALUE->yy_ch_buf;
1410 | 	char *source = (yytext_ptr);
1411 | 	int number_to_move, i;
1412 | 	int ret_val;
1413 | 
1414 | 	if ( (yy_c_buf_p) > &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[(yy_n_chars) + 1] )
1415 | 		YY_FATAL_ERROR(
1416 | 		"fatal flex scanner internal error--end of buffer missed" );
1417 | 
1418 | 	if ( YY_CURRENT_BUFFER_LVALUE->yy_fill_buffer == 0 )
1419 | 		{ /* Don't try to fill the buffer, so this is an EOF. */
1420 | 		if ( (yy_c_buf_p) - (yytext_ptr) - YY_MORE_ADJ == 1 )
1421 | 			{
1422 | 			/* We matched a single character, the EOB, so
1423 | 			 * treat this as a final EOF.
1424 | 			 */
1425 | 			return EOB_ACT_END_OF_FILE;
1426 | 			}
1427 | 
1428 | 		else
1429 | 			{
1430 | 			/* We matched some text prior to the EOB, first
1431 | 			 * process it.
1432 | 			 */
1433 | 			return EOB_ACT_LAST_MATCH;
1434 | 			}
1435 | 		}
1436 | 
1437 | 	/* Try to read more data. */
1438 | 
1439 | 	/* First move last chars to start of buffer. */
1440 | 	number_to_move = (int) ((yy_c_buf_p) - (yytext_ptr) - 1);
1441 | 
1442 | 	for ( i = 0; i < number_to_move; ++i )
1443 | 		*(dest++) = *(source++);
1444 | 
1445 | 	if ( YY_CURRENT_BUFFER_LVALUE->yy_buffer_status == YY_BUFFER_EOF_PENDING )
1446 | 		/* don't do the read, it's not guaranteed to return an EOF,
1447 | 		 * just force an EOF
1448 | 		 */
1449 | 		YY_CURRENT_BUFFER_LVALUE->yy_n_chars = (yy_n_chars) = 0;
1450 | 
1451 | 	else
1452 | 		{
1453 | 			int num_to_read =
1454 | 			YY_CURRENT_BUFFER_LVALUE->yy_buf_size - number_to_move - 1;
1455 | 
1456 | 		while ( num_to_read <= 0 )
1457 | 			{ /* Not enough room in the buffer - grow it. */
1458 | 
1459 | 			/* just a shorter name for the current buffer */
1460 | 			YY_BUFFER_STATE b = YY_CURRENT_BUFFER_LVALUE;
1461 | 
1462 | 			int yy_c_buf_p_offset =
1463 | 				(int) ((yy_c_buf_p) - b->yy_ch_buf);
1464 | 
1465 | 			if ( b->yy_is_our_buffer )
1466 | 				{
1467 | 				int new_size = b->yy_buf_size * 2;
1468 | 
1469 | 				if ( new_size <= 0 )
1470 | 					b->yy_buf_size += b->yy_buf_size / 8;
1471 | 				else
1472 | 					b->yy_buf_size *= 2;
1473 | 
1474 | 				b->yy_ch_buf = (char *)
1475 | 					/* Include room in for 2 EOB chars. */
1476 | 					yyrealloc( (void *) b->yy_ch_buf,
1477 | 							 (yy_size_t) (b->yy_buf_size + 2)  );
1478 | 				}
1479 | 			else
1480 | 				/* Can't grow it, we don't own it. */
1481 | 				b->yy_ch_buf = NULL;
1482 | 
1483 | 			if ( ! b->yy_ch_buf )
1484 | 				YY_FATAL_ERROR(
1485 | 				"fatal error - scanner input buffer overflow" );
1486 | 
1487 | 			(yy_c_buf_p) = &b->yy_ch_buf[yy_c_buf_p_offset];
1488 | 
1489 | 			num_to_read = YY_CURRENT_BUFFER_LVALUE->yy_buf_size -
1490 | 						number_to_move - 1;
1491 | 
1492 | 			}
1493 | 
1494 | 		if ( num_to_read > YY_READ_BUF_SIZE )
1495 | 			num_to_read = YY_READ_BUF_SIZE;
1496 | 
1497 | 		/* Read in more data. */
1498 | 		YY_INPUT( (&YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[number_to_move]),
1499 | 			(yy_n_chars), num_to_read );
1500 | 
1501 | 		YY_CURRENT_BUFFER_LVALUE->yy_n_chars = (yy_n_chars);
1502 | 		}
1503 | 
1504 | 	if ( (yy_n_chars) == 0 )
1505 | 		{
1506 | 		if ( number_to_move == YY_MORE_ADJ )
1507 | 			{
1508 | 			ret_val = EOB_ACT_END_OF_FILE;
1509 | 			yyrestart( yyin  );
1510 | 			}
1511 | 
1512 | 		else
1513 | 			{
1514 | 			ret_val = EOB_ACT_LAST_MATCH;
1515 | 			YY_CURRENT_BUFFER_LVALUE->yy_buffer_status =
1516 | 				YY_BUFFER_EOF_PENDING;
1517 | 			}
1518 | 		}
1519 | 
1520 | 	else
1521 | 		ret_val = EOB_ACT_CONTINUE_SCAN;
1522 | 
1523 | 	if (((yy_n_chars) + number_to_move) > YY_CURRENT_BUFFER_LVALUE->yy_buf_size) {
1524 | 		/* Extend the array by 50%, plus the number we really need. */
1525 | 		int new_size = (yy_n_chars) + number_to_move + ((yy_n_chars) >> 1);
1526 | 		YY_CURRENT_BUFFER_LVALUE->yy_ch_buf = (char *) yyrealloc(
1527 | 			(void *) YY_CURRENT_BUFFER_LVALUE->yy_ch_buf, (yy_size_t) new_size  );
1528 | 		if ( ! YY_CURRENT_BUFFER_LVALUE->yy_ch_buf )
1529 | 			YY_FATAL_ERROR( "out of dynamic memory in yy_get_next_buffer()" );
1530 | 		/* "- 2" to take care of EOB's */
1531 | 		YY_CURRENT_BUFFER_LVALUE->yy_buf_size = (int) (new_size - 2);
1532 | 	}
1533 | 
1534 | 	(yy_n_chars) += number_to_move;
1535 | 	YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[(yy_n_chars)] = YY_END_OF_BUFFER_CHAR;
1536 | 	YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[(yy_n_chars) + 1] = YY_END_OF_BUFFER_CHAR;
1537 | 
1538 | 	(yytext_ptr) = &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[0];
1539 | 
1540 | 	return ret_val;
1541 | }
1542 | 
1543 | /* yy_get_previous_state - get the state just before the EOB char was reached */
1544 | 
1545 |     static yy_state_type yy_get_previous_state (void)
1546 | {
1547 | 	yy_state_type yy_current_state;
1548 | 	char *yy_cp;
1549 |     
1550 | 	yy_current_state = (yy_start);
1551 | 
1552 | 	for ( yy_cp = (yytext_ptr) + YY_MORE_ADJ; yy_cp < (yy_c_buf_p); ++yy_cp )
1553 | 		{
1554 | 		YY_CHAR yy_c = (*yy_cp ? yy_ec[YY_SC_TO_UI(*yy_cp)] : 1);
1555 | 		if ( yy_accept[yy_current_state] )
1556 | 			{
1557 | 			(yy_last_accepting_state) = yy_current_state;
1558 | 			(yy_last_accepting_cpos) = yy_cp;
1559 | 			}
1560 | 		while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
1561 | 			{
1562 | 			yy_current_state = (int) yy_def[yy_current_state];
1563 | 			if ( yy_current_state >= 193 )
1564 | 				yy_c = yy_meta[yy_c];
1565 | 			}
1566 | 		yy_current_state = yy_nxt[yy_base[yy_current_state] + yy_c];
1567 | 		}
1568 | 
1569 | 	return yy_current_state;
1570 | }
1571 | 
1572 | /* yy_try_NUL_trans - try to make a transition on the NUL character
1573 |  *
1574 |  * synopsis
1575 |  *	next_state = yy_try_NUL_trans( current_state );
1576 |  */
1577 |     static yy_state_type yy_try_NUL_trans  (yy_state_type yy_current_state )
1578 | {
1579 | 	int yy_is_jam;
1580 |     	char *yy_cp = (yy_c_buf_p);
1581 | 
1582 | 	YY_CHAR yy_c = 1;
1583 | 	if ( yy_accept[yy_current_state] )
1584 | 		{
1585 | 		(yy_last_accepting_state) = yy_current_state;
1586 | 		(yy_last_accepting_cpos) = yy_cp;
1587 | 		}
1588 | 	while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
1589 | 		{
1590 | 		yy_current_state = (int) yy_def[yy_current_state];
1591 | 		if ( yy_current_state >= 193 )
1592 | 			yy_c = yy_meta[yy_c];
1593 | 		}
1594 | 	yy_current_state = yy_nxt[yy_base[yy_current_state] + yy_c];
1595 | 	yy_is_jam = (yy_current_state == 192);
1596 | 
1597 | 		return yy_is_jam ? 0 : yy_current_state;
1598 | }
1599 | 
1600 | #ifndef YY_NO_UNPUT
1601 | 
1602 | #endif
1603 | 
1604 | #ifndef YY_NO_INPUT
1605 | #ifdef __cplusplus
1606 |     static int yyinput (void)
1607 | #else
1608 |     static int input  (void)
1609 | #endif
1610 | 
1611 | {
1612 | 	int c;
1613 |     
1614 | 	*(yy_c_buf_p) = (yy_hold_char);
1615 | 
1616 | 	if ( *(yy_c_buf_p) == YY_END_OF_BUFFER_CHAR )
1617 | 		{
1618 | 		/* yy_c_buf_p now points to the character we want to return.
1619 | 		 * If this occurs *before* the EOB characters, then it's a
1620 | 		 * valid NUL; if not, then we've hit the end of the buffer.
1621 | 		 */
1622 | 		if ( (yy_c_buf_p) < &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[(yy_n_chars)] )
1623 | 			/* This was really a NUL. */
1624 | 			*(yy_c_buf_p) = '\0';
1625 | 
1626 | 		else
1627 | 			{ /* need more input */
1628 | 			int offset = (int) ((yy_c_buf_p) - (yytext_ptr));
1629 | 			++(yy_c_buf_p);
1630 | 
1631 | 			switch ( yy_get_next_buffer(  ) )
1632 | 				{
1633 | 				case EOB_ACT_LAST_MATCH:
1634 | 					/* This happens because yy_g_n_b()
1635 | 					 * sees that we've accumulated a
1636 | 					 * token and flags that we need to
1637 | 					 * try matching the token before
1638 | 					 * proceeding.  But for input(),
1639 | 					 * there's no matching to consider.
1640 | 					 * So convert the EOB_ACT_LAST_MATCH
1641 | 					 * to EOB_ACT_END_OF_FILE.
1642 | 					 */
1643 | 
1644 | 					/* Reset buffer status. */
1645 | 					yyrestart( yyin );
1646 | 
1647 | 					/*FALLTHROUGH*/
1648 | 
1649 | 				case EOB_ACT_END_OF_FILE:
1650 | 					{
1651 | 					if ( yywrap(  ) )
1652 | 						return 0;
1653 | 
1654 | 					if ( ! (yy_did_buffer_switch_on_eof) )
1655 | 						YY_NEW_FILE;
1656 | #ifdef __cplusplus
1657 | 					return yyinput();
1658 | #else
1659 | 					return input();
1660 | #endif
1661 | 					}
1662 | 
1663 | 				case EOB_ACT_CONTINUE_SCAN:
1664 | 					(yy_c_buf_p) = (yytext_ptr) + offset;
1665 | 					break;
1666 | 				}
1667 | 			}
1668 | 		}
1669 | 
1670 | 	c = *(unsigned char *) (yy_c_buf_p);	/* cast for 8-bit char's */
1671 | 	*(yy_c_buf_p) = '\0';	/* preserve yytext */
1672 | 	(yy_hold_char) = *++(yy_c_buf_p);
1673 | 
1674 | 	if ( c == '\n' )
1675 | 		
1676 |     yylineno++;
1677 | ;
1678 | 
1679 | 	return c;
1680 | }
1681 | #endif	/* ifndef YY_NO_INPUT */
1682 | 
1683 | /** Immediately switch to a different input stream.
1684 |  * @param input_file A readable stream.
1685 |  * 
1686 |  * @note This function does not reset the start condition to @c INITIAL .
1687 |  */
1688 |     void yyrestart  (FILE * input_file )
1689 | {
1690 |     
1691 | 	if ( ! YY_CURRENT_BUFFER ){
1692 |         yyensure_buffer_stack ();
1693 | 		YY_CURRENT_BUFFER_LVALUE =
1694 |             yy_create_buffer( yyin, YY_BUF_SIZE );
1695 | 	}
1696 | 
1697 | 	yy_init_buffer( YY_CURRENT_BUFFER, input_file );
1698 | 	yy_load_buffer_state(  );
1699 | }
1700 | 
1701 | /** Switch to a different input buffer.
1702 |  * @param new_buffer The new input buffer.
1703 |  * 
1704 |  */
1705 |     void yy_switch_to_buffer  (YY_BUFFER_STATE  new_buffer )
1706 | {
1707 |     
1708 | 	/* TODO. We should be able to replace this entire function body
1709 | 	 * with
1710 | 	 *		yypop_buffer_state();
1711 | 	 *		yypush_buffer_state(new_buffer);
1712 |      */
1713 | 	yyensure_buffer_stack ();
1714 | 	if ( YY_CURRENT_BUFFER == new_buffer )
1715 | 		return;
1716 | 
1717 | 	if ( YY_CURRENT_BUFFER )
1718 | 		{
1719 | 		/* Flush out information for old buffer. */
1720 | 		*(yy_c_buf_p) = (yy_hold_char);
1721 | 		YY_CURRENT_BUFFER_LVALUE->yy_buf_pos = (yy_c_buf_p);
1722 | 		YY_CURRENT_BUFFER_LVALUE->yy_n_chars = (yy_n_chars);
1723 | 		}
1724 | 
1725 | 	YY_CURRENT_BUFFER_LVALUE = new_buffer;
1726 | 	yy_load_buffer_state(  );
1727 | 
1728 | 	/* We don't actually know whether we did this switch during
1729 | 	 * EOF (yywrap()) processing, but the only time this flag
1730 | 	 * is looked at is after yywrap() is called, so it's safe
1731 | 	 * to go ahead and always set it.
1732 | 	 */
1733 | 	(yy_did_buffer_switch_on_eof) = 1;
1734 | }
1735 | 
1736 | static void yy_load_buffer_state  (void)
1737 | {
1738 |     	(yy_n_chars) = YY_CURRENT_BUFFER_LVALUE->yy_n_chars;
1739 | 	(yytext_ptr) = (yy_c_buf_p) = YY_CURRENT_BUFFER_LVALUE->yy_buf_pos;
1740 | 	yyin = YY_CURRENT_BUFFER_LVALUE->yy_input_file;
1741 | 	(yy_hold_char) = *(yy_c_buf_p);
1742 | }
1743 | 
1744 | /** Allocate and initialize an input buffer state.
1745 |  * @param file A readable stream.
1746 |  * @param size The character buffer size in bytes. When in doubt, use @c YY_BUF_SIZE.
1747 |  * 
1748 |  * @return the allocated buffer state.
1749 |  */
1750 |     YY_BUFFER_STATE yy_create_buffer  (FILE * file, int  size )
1751 | {
1752 | 	YY_BUFFER_STATE b;
1753 |     
1754 | 	b = (YY_BUFFER_STATE) yyalloc( sizeof( struct yy_buffer_state )  );
1755 | 	if ( ! b )
1756 | 		YY_FATAL_ERROR( "out of dynamic memory in yy_create_buffer()" );
1757 | 
1758 | 	b->yy_buf_size = size;
1759 | 
1760 | 	/* yy_ch_buf has to be 2 characters longer than the size given because
1761 | 	 * we need to put in 2 end-of-buffer characters.
1762 | 	 */
1763 | 	b->yy_ch_buf = (char *) yyalloc( (yy_size_t) (b->yy_buf_size + 2)  );
1764 | 	if ( ! b->yy_ch_buf )
1765 | 		YY_FATAL_ERROR( "out of dynamic memory in yy_create_buffer()" );
1766 | 
1767 | 	b->yy_is_our_buffer = 1;
1768 | 
1769 | 	yy_init_buffer( b, file );
1770 | 
1771 | 	return b;
1772 | }
1773 | 
1774 | /** Destroy the buffer.
1775 |  * @param b a buffer created with yy_create_buffer()
1776 |  * 
1777 |  */
1778 |     void yy_delete_buffer (YY_BUFFER_STATE  b )
1779 | {
1780 |     
1781 | 	if ( ! b )
1782 | 		return;
1783 | 
1784 | 	if ( b == YY_CURRENT_BUFFER ) /* Not sure if we should pop here. */
1785 | 		YY_CURRENT_BUFFER_LVALUE = (YY_BUFFER_STATE) 0;
1786 | 
1787 | 	if ( b->yy_is_our_buffer )
1788 | 		yyfree( (void *) b->yy_ch_buf  );
1789 | 
1790 | 	yyfree( (void *) b  );
1791 | }
1792 | 
1793 | /* Initializes or reinitializes a buffer.
1794 |  * This function is sometimes called more than once on the same buffer,
1795 |  * such as during a yyrestart() or at EOF.
1796 |  */
1797 |     static void yy_init_buffer  (YY_BUFFER_STATE  b, FILE * file )
1798 | 
1799 | {
1800 | 	int oerrno = errno;
1801 |     
1802 | 	yy_flush_buffer( b );
1803 | 
1804 | 	b->yy_input_file = file;
1805 | 	b->yy_fill_buffer = 1;
1806 | 
1807 |     /* If b is the current buffer, then yy_init_buffer was _probably_
1808 |      * called from yyrestart() or through yy_get_next_buffer.
1809 |      * In that case, we don't want to reset the lineno or column.
1810 |      */
1811 |     if (b != YY_CURRENT_BUFFER){
1812 |         b->yy_bs_lineno = 1;
1813 |         b->yy_bs_column = 0;
1814 |     }
1815 | 
1816 |         b->yy_is_interactive = file ? (isatty( fileno(file) ) > 0) : 0;
1817 |     
1818 | 	errno = oerrno;
1819 | }
1820 | 
1821 | /** Discard all buffered characters. On the next scan, YY_INPUT will be called.
1822 |  * @param b the buffer state to be flushed, usually @c YY_CURRENT_BUFFER.
1823 |  * 
1824 |  */
1825 |     void yy_flush_buffer (YY_BUFFER_STATE  b )
1826 | {
1827 |     	if ( ! b )
1828 | 		return;
1829 | 
1830 | 	b->yy_n_chars = 0;
1831 | 
1832 | 	/* We always need two end-of-buffer characters.  The first causes
1833 | 	 * a transition to the end-of-buffer state.  The second causes
1834 | 	 * a jam in that state.
1835 | 	 */
1836 | 	b->yy_ch_buf[0] = YY_END_OF_BUFFER_CHAR;
1837 | 	b->yy_ch_buf[1] = YY_END_OF_BUFFER_CHAR;
1838 | 
1839 | 	b->yy_buf_pos = &b->yy_ch_buf[0];
1840 | 
1841 | 	b->yy_at_bol = 1;
1842 | 	b->yy_buffer_status = YY_BUFFER_NEW;
1843 | 
1844 | 	if ( b == YY_CURRENT_BUFFER )
1845 | 		yy_load_buffer_state(  );
1846 | }
1847 | 
1848 | /** Pushes the new state onto the stack. The new state becomes
1849 |  *  the current state. This function will allocate the stack
1850 |  *  if necessary.
1851 |  *  @param new_buffer The new state.
1852 |  *  
1853 |  */
1854 | void yypush_buffer_state (YY_BUFFER_STATE new_buffer )
1855 | {
1856 |     	if (new_buffer == NULL)
1857 | 		return;
1858 | 
1859 | 	yyensure_buffer_stack();
1860 | 
1861 | 	/* This block is copied from yy_switch_to_buffer. */
1862 | 	if ( YY_CURRENT_BUFFER )
1863 | 		{
1864 | 		/* Flush out information for old buffer. */
1865 | 		*(yy_c_buf_p) = (yy_hold_char);
1866 | 		YY_CURRENT_BUFFER_LVALUE->yy_buf_pos = (yy_c_buf_p);
1867 | 		YY_CURRENT_BUFFER_LVALUE->yy_n_chars = (yy_n_chars);
1868 | 		}
1869 | 
1870 | 	/* Only push if top exists. Otherwise, replace top. */
1871 | 	if (YY_CURRENT_BUFFER)
1872 | 		(yy_buffer_stack_top)++;
1873 | 	YY_CURRENT_BUFFER_LVALUE = new_buffer;
1874 | 
1875 | 	/* copied from yy_switch_to_buffer. */
1876 | 	yy_load_buffer_state(  );
1877 | 	(yy_did_buffer_switch_on_eof) = 1;
1878 | }
1879 | 
1880 | /** Removes and deletes the top of the stack, if present.
1881 |  *  The next element becomes the new top.
1882 |  *  
1883 |  */
1884 | void yypop_buffer_state (void)
1885 | {
1886 |     	if (!YY_CURRENT_BUFFER)
1887 | 		return;
1888 | 
1889 | 	yy_delete_buffer(YY_CURRENT_BUFFER );
1890 | 	YY_CURRENT_BUFFER_LVALUE = NULL;
1891 | 	if ((yy_buffer_stack_top) > 0)
1892 | 		--(yy_buffer_stack_top);
1893 | 
1894 | 	if (YY_CURRENT_BUFFER) {
1895 | 		yy_load_buffer_state(  );
1896 | 		(yy_did_buffer_switch_on_eof) = 1;
1897 | 	}
1898 | }
1899 | 
1900 | /* Allocates the stack if it does not exist.
1901 |  *  Guarantees space for at least one push.
1902 |  */
1903 | static void yyensure_buffer_stack (void)
1904 | {
1905 | 	yy_size_t num_to_alloc;
1906 |     
1907 | 	if (!(yy_buffer_stack)) {
1908 | 
1909 | 		/* First allocation is just for 2 elements, since we don't know if this
1910 | 		 * scanner will even need a stack. We use 2 instead of 1 to avoid an
1911 | 		 * immediate realloc on the next call.
1912 |          */
1913 |       num_to_alloc = 1; /* After all that talk, this was set to 1 anyways... */
1914 | 		(yy_buffer_stack) = (struct yy_buffer_state**)yyalloc
1915 | 								(num_to_alloc * sizeof(struct yy_buffer_state*)
1916 | 								);
1917 | 		if ( ! (yy_buffer_stack) )
1918 | 			YY_FATAL_ERROR( "out of dynamic memory in yyensure_buffer_stack()" );
1919 | 
1920 | 		memset((yy_buffer_stack), 0, num_to_alloc * sizeof(struct yy_buffer_state*));
1921 | 
1922 | 		(yy_buffer_stack_max) = num_to_alloc;
1923 | 		(yy_buffer_stack_top) = 0;
1924 | 		return;
1925 | 	}
1926 | 
1927 | 	if ((yy_buffer_stack_top) >= ((yy_buffer_stack_max)) - 1){
1928 | 
1929 | 		/* Increase the buffer to prepare for a possible push. */
1930 | 		yy_size_t grow_size = 8 /* arbitrary grow size */;
1931 | 
1932 | 		num_to_alloc = (yy_buffer_stack_max) + grow_size;
1933 | 		(yy_buffer_stack) = (struct yy_buffer_state**)yyrealloc
1934 | 								((yy_buffer_stack),
1935 | 								num_to_alloc * sizeof(struct yy_buffer_state*)
1936 | 								);
1937 | 		if ( ! (yy_buffer_stack) )
1938 | 			YY_FATAL_ERROR( "out of dynamic memory in yyensure_buffer_stack()" );
1939 | 
1940 | 		/* zero only the new slots.*/
1941 | 		memset((yy_buffer_stack) + (yy_buffer_stack_max), 0, grow_size * sizeof(struct yy_buffer_state*));
1942 | 		(yy_buffer_stack_max) = num_to_alloc;
1943 | 	}
1944 | }
1945 | 
1946 | /** Setup the input buffer state to scan directly from a user-specified character buffer.
1947 |  * @param base the character buffer
1948 |  * @param size the size in bytes of the character buffer
1949 |  * 
1950 |  * @return the newly allocated buffer state object.
1951 |  */
1952 | YY_BUFFER_STATE yy_scan_buffer  (char * base, yy_size_t  size )
1953 | {
1954 | 	YY_BUFFER_STATE b;
1955 |     
1956 | 	if ( size < 2 ||
1957 | 	     base[size-2] != YY_END_OF_BUFFER_CHAR ||
1958 | 	     base[size-1] != YY_END_OF_BUFFER_CHAR )
1959 | 		/* They forgot to leave room for the EOB's. */
1960 | 		return NULL;
1961 | 
1962 | 	b = (YY_BUFFER_STATE) yyalloc( sizeof( struct yy_buffer_state )  );
1963 | 	if ( ! b )
1964 | 		YY_FATAL_ERROR( "out of dynamic memory in yy_scan_buffer()" );
1965 | 
1966 | 	b->yy_buf_size = (int) (size - 2);	/* "- 2" to take care of EOB's */
1967 | 	b->yy_buf_pos = b->yy_ch_buf = base;
1968 | 	b->yy_is_our_buffer = 0;
1969 | 	b->yy_input_file = NULL;
1970 | 	b->yy_n_chars = b->yy_buf_size;
1971 | 	b->yy_is_interactive = 0;
1972 | 	b->yy_at_bol = 1;
1973 | 	b->yy_fill_buffer = 0;
1974 | 	b->yy_buffer_status = YY_BUFFER_NEW;
1975 | 
1976 | 	yy_switch_to_buffer( b  );
1977 | 
1978 | 	return b;
1979 | }
1980 | 
1981 | /** Setup the input buffer state to scan a string. The next call to yylex() will
1982 |  * scan from a @e copy of @a str.
1983 |  * @param yystr a NUL-terminated string to scan
1984 |  * 
1985 |  * @return the newly allocated buffer state object.
1986 |  * @note If you want to scan bytes that may contain NUL values, then use
1987 |  *       yy_scan_bytes() instead.
1988 |  */
1989 | YY_BUFFER_STATE yy_scan_string (const char * yystr )
1990 | {
1991 |     
1992 | 	return yy_scan_bytes( yystr, (int) strlen(yystr) );
1993 | }
1994 | 
1995 | /** Setup the input buffer state to scan the given bytes. The next call to yylex() will
1996 |  * scan from a @e copy of @a bytes.
1997 |  * @param yybytes the byte buffer to scan
1998 |  * @param _yybytes_len the number of bytes in the buffer pointed to by @a bytes.
1999 |  * 
2000 |  * @return the newly allocated buffer state object.
2001 |  */
2002 | YY_BUFFER_STATE yy_scan_bytes  (const char * yybytes, int  _yybytes_len )
2003 | {
2004 | 	YY_BUFFER_STATE b;
2005 | 	char *buf;
2006 | 	yy_size_t n;
2007 | 	int i;
2008 |     
2009 | 	/* Get memory for full buffer, including space for trailing EOB's. */
2010 | 	n = (yy_size_t) (_yybytes_len + 2);
2011 | 	buf = (char *) yyalloc( n  );
2012 | 	if ( ! buf )
2013 | 		YY_FATAL_ERROR( "out of dynamic memory in yy_scan_bytes()" );
2014 | 
2015 | 	for ( i = 0; i < _yybytes_len; ++i )
2016 | 		buf[i] = yybytes[i];
2017 | 
2018 | 	buf[_yybytes_len] = buf[_yybytes_len+1] = YY_END_OF_BUFFER_CHAR;
2019 | 
2020 | 	b = yy_scan_buffer( buf, n );
2021 | 	if ( ! b )
2022 | 		YY_FATAL_ERROR( "bad buffer in yy_scan_bytes()" );
2023 | 
2024 | 	/* It's okay to grow etc. this buffer, and we should throw it
2025 | 	 * away when we're done.
2026 | 	 */
2027 | 	b->yy_is_our_buffer = 1;
2028 | 
2029 | 	return b;
2030 | }
2031 | 
2032 | #ifndef YY_EXIT_FAILURE
2033 | #define YY_EXIT_FAILURE 2
2034 | #endif
2035 | 
2036 | static void yynoreturn yy_fatal_error (const char* msg )
2037 | {
2038 | 			fprintf( stderr, "%s\n", msg );
2039 | 	exit( YY_EXIT_FAILURE );
2040 | }
2041 | 
2042 | /* Redefine yyless() so it works in section 3 code. */
2043 | 
2044 | #undef yyless
2045 | #define yyless(n) \
2046 | 	do \
2047 | 		{ \
2048 | 		/* Undo effects of setting up yytext. */ \
2049 |         int yyless_macro_arg = (n); \
2050 |         YY_LESS_LINENO(yyless_macro_arg);\
2051 | 		yytext[yyleng] = (yy_hold_char); \
2052 | 		(yy_c_buf_p) = yytext + yyless_macro_arg; \
2053 | 		(yy_hold_char) = *(yy_c_buf_p); \
2054 | 		*(yy_c_buf_p) = '\0'; \
2055 | 		yyleng = yyless_macro_arg; \
2056 | 		} \
2057 | 	while ( 0 )
2058 | 
2059 | /* Accessor  methods (get/set functions) to struct members. */
2060 | 
2061 | /** Get the current line number.
2062 |  * 
2063 |  */
2064 | int yyget_lineno  (void)
2065 | {
2066 |     
2067 |     return yylineno;
2068 | }
2069 | 
2070 | /** Get the input stream.
2071 |  * 
2072 |  */
2073 | FILE *yyget_in  (void)
2074 | {
2075 |         return yyin;
2076 | }
2077 | 
2078 | /** Get the output stream.
2079 |  * 
2080 |  */
2081 | FILE *yyget_out  (void)
2082 | {
2083 |         return yyout;
2084 | }
2085 | 
2086 | /** Get the length of the current token.
2087 |  * 
2088 |  */
2089 | int yyget_leng  (void)
2090 | {
2091 |         return yyleng;
2092 | }
2093 | 
2094 | /** Get the current token.
2095 |  * 
2096 |  */
2097 | 
2098 | char *yyget_text  (void)
2099 | {
2100 |         return yytext;
2101 | }
2102 | 
2103 | /** Set the current line number.
2104 |  * @param _line_number line number
2105 |  * 
2106 |  */
2107 | void yyset_lineno (int  _line_number )
2108 | {
2109 |     
2110 |     yylineno = _line_number;
2111 | }
2112 | 
2113 | /** Set the input stream. This does not discard the current
2114 |  * input buffer.
2115 |  * @param _in_str A readable stream.
2116 |  * 
2117 |  * @see yy_switch_to_buffer
2118 |  */
2119 | void yyset_in (FILE *  _in_str )
2120 | {
2121 |         yyin = _in_str ;
2122 | }
2123 | 
2124 | void yyset_out (FILE *  _out_str )
2125 | {
2126 |         yyout = _out_str ;
2127 | }
2128 | 
2129 | int yyget_debug  (void)
2130 | {
2131 |         return yy_flex_debug;
2132 | }
2133 | 
2134 | void yyset_debug (int  _bdebug )
2135 | {
2136 |         yy_flex_debug = _bdebug ;
2137 | }
2138 | 
2139 | static int yy_init_globals (void)
2140 | {
2141 |         /* Initialization is the same as for the non-reentrant scanner.
2142 |      * This function is called from yylex_destroy(), so don't allocate here.
2143 |      */
2144 | 
2145 |     /* We do not touch yylineno unless the option is enabled. */
2146 |     yylineno =  1;
2147 |     
2148 |     (yy_buffer_stack) = NULL;
2149 |     (yy_buffer_stack_top) = 0;
2150 |     (yy_buffer_stack_max) = 0;
2151 |     (yy_c_buf_p) = NULL;
2152 |     (yy_init) = 0;
2153 |     (yy_start) = 0;
2154 | 
2155 | /* Defined in main.c */
2156 | #ifdef YY_STDINIT
2157 |     yyin = stdin;
2158 |     yyout = stdout;
2159 | #else
2160 |     yyin = NULL;
2161 |     yyout = NULL;
2162 | #endif
2163 | 
2164 |     /* For future reference: Set errno on error, since we are called by
2165 |      * yylex_init()
2166 |      */
2167 |     return 0;
2168 | }
2169 | 
2170 | /* yylex_destroy is for both reentrant and non-reentrant scanners. */
2171 | int yylex_destroy  (void)
2172 | {
2173 |     
2174 |     /* Pop the buffer stack, destroying each element. */
2175 | 	while(YY_CURRENT_BUFFER){
2176 | 		yy_delete_buffer( YY_CURRENT_BUFFER  );
2177 | 		YY_CURRENT_BUFFER_LVALUE = NULL;
2178 | 		yypop_buffer_state();
2179 | 	}
2180 | 
2181 | 	/* Destroy the stack itself. */
2182 | 	yyfree((yy_buffer_stack) );
2183 | 	(yy_buffer_stack) = NULL;
2184 | 
2185 |     /* Reset the globals. This is important in a non-reentrant scanner so the next time
2186 |      * yylex() is called, initialization will occur. */
2187 |     yy_init_globals( );
2188 | 
2189 |     return 0;
2190 | }
2191 | 
2192 | /*
2193 |  * Internal utility routines.
2194 |  */
2195 | 
2196 | #ifndef yytext_ptr
2197 | static void yy_flex_strncpy (char* s1, const char * s2, int n )
2198 | {
2199 | 		
2200 | 	int i;
2201 | 	for ( i = 0; i < n; ++i )
2202 | 		s1[i] = s2[i];
2203 | }
2204 | #endif
2205 | 
2206 | #ifdef YY_NEED_STRLEN
2207 | static int yy_flex_strlen (const char * s )
2208 | {
2209 | 	int n;
2210 | 	for ( n = 0; s[n]; ++n )
2211 | 		;
2212 | 
2213 | 	return n;
2214 | }
2215 | #endif
2216 | 
2217 | void *yyalloc (yy_size_t  size )
2218 | {
2219 | 			return malloc(size);
2220 | }
2221 | 
2222 | void *yyrealloc  (void * ptr, yy_size_t  size )
2223 | {
2224 | 		
2225 | 	/* The cast to (char *) in the following accommodates both
2226 | 	 * implementations that use char* generic pointers, and those
2227 | 	 * that use void* generic pointers.  It works with the latter
2228 | 	 * because both ANSI C and C++ allow castless assignment from
2229 | 	 * any pointer type to void*, and deal with argument conversions
2230 | 	 * as though doing an assignment.
2231 | 	 */
2232 | 	return realloc(ptr, size);
2233 | }
2234 | 
2235 | void yyfree (void * ptr )
2236 | {
2237 | 			free( (char *) ptr );	/* see yyrealloc() for (char *) cast */
2238 | }
2239 | 
2240 | #define YYTABLES_NAME "yytables"
2241 | 
2242 | #line 207 "lexer.l"
2243 | 
2244 | 
```

src/lexer.l
```
1 | %{
2 | #include <stdio.h>
3 | #include <stdlib.h>
4 | #include <string.h>
5 | #include "formLang.h"
6 | #include "y.tab.h"
7 | 
8 | extern YYSTYPE yylval;
9 | 
10 | // Context tracking
11 | int after_colon = 0;
12 | 
13 | // Error handling
14 | void syntax_error(const char* msg) {
15 |     fprintf(stderr, "Syntax error at line %d: %s\n", yylineno, msg);
16 | }
17 | 
18 | // String handling
19 | char* process_string(const char* input) {
20 |     char* output = malloc(strlen(input) + 1);
21 |     int i = 0, j = 0;
22 |     
23 |     while (input[i] != '\0') {
24 |         if (input[i] == '\\') {
25 |             i++;
26 |             switch (input[i]) {
27 |                 case 'n': output[j++] = '\n'; break;
28 |                 case 't': output[j++] = '\t'; break;
29 |                 case 'r': output[j++] = '\r'; break;
30 |                 case '\\': output[j++] = '\\'; break;
31 |                 case '"': output[j++] = '"'; break;
32 |                 default: output[j++] = input[i]; break;
33 |             }
34 |         } else {
35 |             output[j++] = input[i];
36 |         }
37 |         i++;
38 |     }
39 |     output[j] = '\0';
40 |     return output;
41 | }
42 | %}
43 | 
44 | %option nounput
45 | %option noinput
46 | %option yylineno
47 | %option noyywrap
48 | 
49 | %%
50 | 
51 | [ \t\n]     ; /* Skip whitespace and newlines */
52 | 
53 | "form"      { return FORM; }
54 | "section"   { return SECTION; }
55 | "field"     { return FIELD; }
56 | "validate"  { return VALIDATE; }
57 | "meta"      { return META; }
58 | "if"        { return IF; }
59 | "error"     { return ERROR; }
60 | ":"         { after_colon = 1; return ':'; }
61 | ";"         { after_colon = 0; return ';'; }
62 | "{"         { return '{'; }
63 | "}"         { return '}'; }
64 | "="         { return '='; }
65 | "<"         { return LT; }
66 | ">"         { return GT; }
67 | "<="        { return LTE; }
68 | ">="        { return GTE; }
69 | "=="        { return EQ; }
70 | "!="        { return NEQ; }
71 | "&&"        { return AND; }
72 | "||"        { return OR; }
73 | 
74 | "text"      { 
75 |     if (after_colon) {
76 |         after_colon = 0;
77 |         return TEXT;
78 |     }
79 |     yylval.str = strdup(yytext);
80 |     return IDENTIFIER;
81 | }
82 | "email"     { 
83 |     if (after_colon) {
84 |         after_colon = 0;
85 |         return EMAIL;
86 |     }
87 |     yylval.str = strdup(yytext);
88 |     return IDENTIFIER;
89 | }
90 | "password"  { 
91 |     if (after_colon) {
92 |         after_colon = 0;
93 |         return PASSWORD;
94 |     }
95 |     yylval.str = strdup(yytext);
96 |     return IDENTIFIER;
97 | }
98 | "number"    { 
99 |     if (after_colon) {
100 |         after_colon = 0;
101 |         return NUMBER;
102 |     }
103 |     yylval.str = strdup(yytext);
104 |     return IDENTIFIER;
105 | }
106 | "textarea"  { 
107 |     if (after_colon) {
108 |         after_colon = 0;
109 |         return TEXTAREA;
110 |     }
111 |     yylval.str = strdup(yytext);
112 |     return IDENTIFIER;
113 | }
114 | "date"      { 
115 |     if (after_colon) {
116 |         after_colon = 0;
117 |         return DATE;
118 |     }
119 |     yylval.str = strdup(yytext);
120 |     return IDENTIFIER;
121 | }
122 | "checkbox"  { 
123 |     if (after_colon) {
124 |         after_colon = 0;
125 |         return CHECKBOX;
126 |     }
127 |     yylval.str = strdup(yytext);
128 |     return IDENTIFIER;
129 | }
130 | "dropdown"  { 
131 |     if (after_colon) {
132 |         after_colon = 0;
133 |         return DROPDOWN;
134 |     }
135 |     yylval.str = strdup(yytext);
136 |     return IDENTIFIER;
137 | }
138 | "radio"     { 
139 |     if (after_colon) {
140 |         after_colon = 0;
141 |         return RADIO;
142 |     }
143 |     yylval.str = strdup(yytext);
144 |     return IDENTIFIER;
145 | }
146 | "file"      { 
147 |     if (after_colon) {
148 |         after_colon = 0;
149 |         return FILE_TYPE;
150 |     }
151 |     yylval.str = strdup(yytext);
152 |     return IDENTIFIER;
153 | }
154 | 
155 | "required"  { return REQUIRED; }
156 | "optional"  { return OPTIONAL; }
157 | "minLength" { return MINLENGTH; }
158 | "maxLength" { return MAXLENGTH; }
159 | "min"       { return MIN; }
160 | "max"       { return MAX; }
161 | "rows"      { return ROWS; }
162 | "cols"      { return COLS; }
163 | "pattern"   { return PATTERN; }
164 | "default"   { return DEFAULT; }
165 | 
166 | "username"  {
167 |     if (after_colon) {
168 |         after_colon = 0;
169 |         return USERNAME;
170 |     }
171 |     yylval.str = strdup(yytext);
172 |     return IDENTIFIER;
173 | }
174 | "confirm"   { return CONFIRM; }
175 | "strength"  { return STRENGTH; }
176 | "address"   {
177 |     if (after_colon) {
178 |         after_colon = 0;
179 |         return ADDRESS;
180 |     }
181 |     yylval.str = strdup(yytext);
182 |     return IDENTIFIER;
183 | }
184 | 
185 | [a-zA-Z_][a-zA-Z0-9_]* { 
186 |     yylval.str = strdup(yytext);
187 |     return IDENTIFIER;
188 | }
189 | 
190 | [0-9]+      {
191 |     yylval.num = atoi(yytext);
192 |     return NUMBER_LITERAL;
193 | }
194 | 
195 | \"([^"\\]|\\.)*\"  {
196 |     // Remove quotes and process escaped characters
197 |     yytext[strlen(yytext) - 1] = '\0';
198 |     yylval.str = process_string(yytext + 1);
199 |     return STRING_LITERAL;
200 | }
201 | 
202 | .           { 
203 |     syntax_error("Unexpected character");
204 |     return yytext[0]; 
205 | }
206 | 
207 | %%
```

src/parser.output
```
1 | State 14 conflicts: 1 shift/reduce
2 | 
3 | 
4 | Grammar
5 | 
6 |     0 $accept: form $end
7 | 
8 |     1 $@1: ε
9 | 
10 |     2 form: FORM IDENTIFIER $@1 '{' section_list '}'
11 | 
12 |     3 section_list: ε
13 |     4             | section_list section
14 | 
15 |     5 section: section_header '{' field_list '}'
16 |     6        | section_header '{' '}'
17 |     7        | section_header error '}'
18 | 
19 |     8 section_header: SECTION IDENTIFIER
20 | 
21 |     9 field_list: ε
22 |    10           | field_list field
23 |    11           | field_list error ';'
24 | 
25 |    12 field: FIELD IDENTIFIER ':' field_type field_attributes ';'
26 | 
27 |    13 field_type: TEXT
28 |    14           | EMAIL
29 |    15           | PASSWORD
30 |    16           | NUMBER
31 |    17           | TEXTAREA
32 |    18           | DATE
33 |    19           | CHECKBOX
34 |    20           | DROPDOWN
35 |    21           | RADIO
36 |    22           | FILE_TYPE
37 | 
38 |    23 field_attributes: ε
39 |    24                 | field_attributes attribute
40 | 
41 |    25 attribute: REQUIRED
42 |    26          | OPTIONAL
43 |    27          | PATTERN STRING_LITERAL
44 |    28          | DEFAULT STRING_LITERAL
45 |    29          | DEFAULT NUMBER_LITERAL
46 |    30          | MINLENGTH NUMBER_LITERAL
47 |    31          | MAXLENGTH NUMBER_LITERAL
48 |    32          | MIN NUMBER_LITERAL
49 |    33          | MAX NUMBER_LITERAL
50 |    34          | ROWS NUMBER_LITERAL
51 |    35          | COLS NUMBER_LITERAL
52 | 
53 | 
54 | Terminals, with rules where they appear
55 | 
56 |     $end (0) 0
57 |     ':' (58) 12
58 |     ';' (59) 11 12
59 |     '{' (123) 2 5 6
60 |     '}' (125) 2 5 6 7
61 |     error (256) 7 11
62 |     FORM (258) 2
63 |     SECTION (259) 8
64 |     FIELD (260) 12
65 |     TEXT (261) 13
66 |     EMAIL (262) 14
67 |     PASSWORD (263) 15
68 |     NUMBER (264) 16
69 |     TEXTAREA (265) 17
70 |     DATE (266) 18
71 |     CHECKBOX (267) 19
72 |     DROPDOWN (268) 20
73 |     RADIO (269) 21
74 |     FILE_TYPE (270) 22
75 |     REQUIRED (271) 25
76 |     OPTIONAL (272) 26
77 |     MINLENGTH (273) 30
78 |     MAXLENGTH (274) 31
79 |     MIN (275) 32
80 |     MAX (276) 33
81 |     ROWS (277) 34
82 |     COLS (278) 35
83 |     PATTERN (279) 27
84 |     DEFAULT (280) 28 29
85 |     IDENTIFIER <str> (281) 2 8 12
86 |     NUMBER_LITERAL <num> (282) 29 30 31 32 33 34 35
87 |     STRING_LITERAL <str> (283) 27 28
88 | 
89 | 
90 | Nonterminals, with rules where they appear
91 | 
92 |     $accept (33)
93 |         on left: 0
94 |     form <form> (34)
95 |         on left: 2
96 |         on right: 0
97 |     $@1 (35)
98 |         on left: 1
99 |         on right: 2
100 |     section_list (36)
101 |         on left: 3 4
102 |         on right: 2 4
103 |     section (37)
104 |         on left: 5 6 7
105 |         on right: 4
106 |     section_header (38)
107 |         on left: 8
108 |         on right: 5 6 7
109 |     field_list (39)
110 |         on left: 9 10 11
111 |         on right: 5 10 11
112 |     field (40)
113 |         on left: 12
114 |         on right: 10
115 |     field_type <field_type> (41)
116 |         on left: 13 14 15 16 17 18 19 20 21 22
117 |         on right: 12
118 |     field_attributes <field_attrs> (42)
119 |         on left: 23 24
120 |         on right: 12 24
121 |     attribute <field_attrs> (43)
122 |         on left: 25 26 27 28 29 30 31 32 33 34 35
123 |         on right: 24
124 | 
125 | 
126 | State 0
127 | 
128 |     0 $accept: • form $end
129 | 
130 |     FORM  shift, and go to state 1
131 | 
132 |     form  go to state 2
133 | 
134 | 
135 | State 1
136 | 
137 |     2 form: FORM • IDENTIFIER $@1 '{' section_list '}'
138 | 
139 |     IDENTIFIER  shift, and go to state 3
140 | 
141 | 
142 | State 2
143 | 
144 |     0 $accept: form • $end
145 | 
146 |     $end  shift, and go to state 4
147 | 
148 | 
149 | State 3
150 | 
151 |     2 form: FORM IDENTIFIER • $@1 '{' section_list '}'
152 | 
153 |     $default  reduce using rule 1 ($@1)
154 | 
155 |     $@1  go to state 5
156 | 
157 | 
158 | State 4
159 | 
160 |     0 $accept: form $end •
161 | 
162 |     $default  accept
163 | 
164 | 
165 | State 5
166 | 
167 |     2 form: FORM IDENTIFIER $@1 • '{' section_list '}'
168 | 
169 |     '{'  shift, and go to state 6
170 | 
171 | 
172 | State 6
173 | 
174 |     2 form: FORM IDENTIFIER $@1 '{' • section_list '}'
175 | 
176 |     $default  reduce using rule 3 (section_list)
177 | 
178 |     section_list  go to state 7
179 | 
180 | 
181 | State 7
182 | 
183 |     2 form: FORM IDENTIFIER $@1 '{' section_list • '}'
184 |     4 section_list: section_list • section
185 | 
186 |     SECTION  shift, and go to state 8
187 |     '}'      shift, and go to state 9
188 | 
189 |     section         go to state 10
190 |     section_header  go to state 11
191 | 
192 | 
193 | State 8
194 | 
195 |     8 section_header: SECTION • IDENTIFIER
196 | 
197 |     IDENTIFIER  shift, and go to state 12
198 | 
199 | 
200 | State 9
201 | 
202 |     2 form: FORM IDENTIFIER $@1 '{' section_list '}' •
203 | 
204 |     $default  reduce using rule 2 (form)
205 | 
206 | 
207 | State 10
208 | 
209 |     4 section_list: section_list section •
210 | 
211 |     $default  reduce using rule 4 (section_list)
212 | 
213 | 
214 | State 11
215 | 
216 |     5 section: section_header • '{' field_list '}'
217 |     6        | section_header • '{' '}'
218 |     7        | section_header • error '}'
219 | 
220 |     error  shift, and go to state 13
221 |     '{'    shift, and go to state 14
222 | 
223 | 
224 | State 12
225 | 
226 |     8 section_header: SECTION IDENTIFIER •
227 | 
228 |     $default  reduce using rule 8 (section_header)
229 | 
230 | 
231 | State 13
232 | 
233 |     7 section: section_header error • '}'
234 | 
235 |     '}'  shift, and go to state 15
236 | 
237 | 
238 | State 14
239 | 
240 |     5 section: section_header '{' • field_list '}'
241 |     6        | section_header '{' • '}'
242 | 
243 |     '}'  shift, and go to state 16
244 | 
245 |     '}'       [reduce using rule 9 (field_list)]
246 |     $default  reduce using rule 9 (field_list)
247 | 
248 |     field_list  go to state 17
249 | 
250 | 
251 | State 15
252 | 
253 |     7 section: section_header error '}' •
254 | 
255 |     $default  reduce using rule 7 (section)
256 | 
257 | 
258 | State 16
259 | 
260 |     6 section: section_header '{' '}' •
261 | 
262 |     $default  reduce using rule 6 (section)
263 | 
264 | 
265 | State 17
266 | 
267 |     5 section: section_header '{' field_list • '}'
268 |    10 field_list: field_list • field
269 |    11           | field_list • error ';'
270 | 
271 |     error  shift, and go to state 18
272 |     FIELD  shift, and go to state 19
273 |     '}'    shift, and go to state 20
274 | 
275 |     field  go to state 21
276 | 
277 | 
278 | State 18
279 | 
280 |    11 field_list: field_list error • ';'
281 | 
282 |     ';'  shift, and go to state 22
283 | 
284 | 
285 | State 19
286 | 
287 |    12 field: FIELD • IDENTIFIER ':' field_type field_attributes ';'
288 | 
289 |     IDENTIFIER  shift, and go to state 23
290 | 
291 | 
292 | State 20
293 | 
294 |     5 section: section_header '{' field_list '}' •
295 | 
296 |     $default  reduce using rule 5 (section)
297 | 
298 | 
299 | State 21
300 | 
301 |    10 field_list: field_list field •
302 | 
303 |     $default  reduce using rule 10 (field_list)
304 | 
305 | 
306 | State 22
307 | 
308 |    11 field_list: field_list error ';' •
309 | 
310 |     $default  reduce using rule 11 (field_list)
311 | 
312 | 
313 | State 23
314 | 
315 |    12 field: FIELD IDENTIFIER • ':' field_type field_attributes ';'
316 | 
317 |     ':'  shift, and go to state 24
318 | 
319 | 
320 | State 24
321 | 
322 |    12 field: FIELD IDENTIFIER ':' • field_type field_attributes ';'
323 | 
324 |     TEXT       shift, and go to state 25
325 |     EMAIL      shift, and go to state 26
326 |     PASSWORD   shift, and go to state 27
327 |     NUMBER     shift, and go to state 28
328 |     TEXTAREA   shift, and go to state 29
329 |     DATE       shift, and go to state 30
330 |     CHECKBOX   shift, and go to state 31
331 |     DROPDOWN   shift, and go to state 32
332 |     RADIO      shift, and go to state 33
333 |     FILE_TYPE  shift, and go to state 34
334 | 
335 |     field_type  go to state 35
336 | 
337 | 
338 | State 25
339 | 
340 |    13 field_type: TEXT •
341 | 
342 |     $default  reduce using rule 13 (field_type)
343 | 
344 | 
345 | State 26
346 | 
347 |    14 field_type: EMAIL •
348 | 
349 |     $default  reduce using rule 14 (field_type)
350 | 
351 | 
352 | State 27
353 | 
354 |    15 field_type: PASSWORD •
355 | 
356 |     $default  reduce using rule 15 (field_type)
357 | 
358 | 
359 | State 28
360 | 
361 |    16 field_type: NUMBER •
362 | 
363 |     $default  reduce using rule 16 (field_type)
364 | 
365 | 
366 | State 29
367 | 
368 |    17 field_type: TEXTAREA •
369 | 
370 |     $default  reduce using rule 17 (field_type)
371 | 
372 | 
373 | State 30
374 | 
375 |    18 field_type: DATE •
376 | 
377 |     $default  reduce using rule 18 (field_type)
378 | 
379 | 
380 | State 31
381 | 
382 |    19 field_type: CHECKBOX •
383 | 
384 |     $default  reduce using rule 19 (field_type)
385 | 
386 | 
387 | State 32
388 | 
389 |    20 field_type: DROPDOWN •
390 | 
391 |     $default  reduce using rule 20 (field_type)
392 | 
393 | 
394 | State 33
395 | 
396 |    21 field_type: RADIO •
397 | 
398 |     $default  reduce using rule 21 (field_type)
399 | 
400 | 
401 | State 34
402 | 
403 |    22 field_type: FILE_TYPE •
404 | 
405 |     $default  reduce using rule 22 (field_type)
406 | 
407 | 
408 | State 35
409 | 
410 |    12 field: FIELD IDENTIFIER ':' field_type • field_attributes ';'
411 | 
412 |     $default  reduce using rule 23 (field_attributes)
413 | 
414 |     field_attributes  go to state 36
415 | 
416 | 
417 | State 36
418 | 
419 |    12 field: FIELD IDENTIFIER ':' field_type field_attributes • ';'
420 |    24 field_attributes: field_attributes • attribute
421 | 
422 |     REQUIRED   shift, and go to state 37
423 |     OPTIONAL   shift, and go to state 38
424 |     MINLENGTH  shift, and go to state 39
425 |     MAXLENGTH  shift, and go to state 40
426 |     MIN        shift, and go to state 41
427 |     MAX        shift, and go to state 42
428 |     ROWS       shift, and go to state 43
429 |     COLS       shift, and go to state 44
430 |     PATTERN    shift, and go to state 45
431 |     DEFAULT    shift, and go to state 46
432 |     ';'        shift, and go to state 47
433 | 
434 |     attribute  go to state 48
435 | 
436 | 
437 | State 37
438 | 
439 |    25 attribute: REQUIRED •
440 | 
441 |     $default  reduce using rule 25 (attribute)
442 | 
443 | 
444 | State 38
445 | 
446 |    26 attribute: OPTIONAL •
447 | 
448 |     $default  reduce using rule 26 (attribute)
449 | 
450 | 
451 | State 39
452 | 
453 |    30 attribute: MINLENGTH • NUMBER_LITERAL
454 | 
455 |     NUMBER_LITERAL  shift, and go to state 49
456 | 
457 | 
458 | State 40
459 | 
460 |    31 attribute: MAXLENGTH • NUMBER_LITERAL
461 | 
462 |     NUMBER_LITERAL  shift, and go to state 50
463 | 
464 | 
465 | State 41
466 | 
467 |    32 attribute: MIN • NUMBER_LITERAL
468 | 
469 |     NUMBER_LITERAL  shift, and go to state 51
470 | 
471 | 
472 | State 42
473 | 
474 |    33 attribute: MAX • NUMBER_LITERAL
475 | 
476 |     NUMBER_LITERAL  shift, and go to state 52
477 | 
478 | 
479 | State 43
480 | 
481 |    34 attribute: ROWS • NUMBER_LITERAL
482 | 
483 |     NUMBER_LITERAL  shift, and go to state 53
484 | 
485 | 
486 | State 44
487 | 
488 |    35 attribute: COLS • NUMBER_LITERAL
489 | 
490 |     NUMBER_LITERAL  shift, and go to state 54
491 | 
492 | 
493 | State 45
494 | 
495 |    27 attribute: PATTERN • STRING_LITERAL
496 | 
497 |     STRING_LITERAL  shift, and go to state 55
498 | 
499 | 
500 | State 46
501 | 
502 |    28 attribute: DEFAULT • STRING_LITERAL
503 |    29          | DEFAULT • NUMBER_LITERAL
504 | 
505 |     NUMBER_LITERAL  shift, and go to state 56
506 |     STRING_LITERAL  shift, and go to state 57
507 | 
508 | 
509 | State 47
510 | 
511 |    12 field: FIELD IDENTIFIER ':' field_type field_attributes ';' •
512 | 
513 |     $default  reduce using rule 12 (field)
514 | 
515 | 
516 | State 48
517 | 
518 |    24 field_attributes: field_attributes attribute •
519 | 
520 |     $default  reduce using rule 24 (field_attributes)
521 | 
522 | 
523 | State 49
524 | 
525 |    30 attribute: MINLENGTH NUMBER_LITERAL •
526 | 
527 |     $default  reduce using rule 30 (attribute)
528 | 
529 | 
530 | State 50
531 | 
532 |    31 attribute: MAXLENGTH NUMBER_LITERAL •
533 | 
534 |     $default  reduce using rule 31 (attribute)
535 | 
536 | 
537 | State 51
538 | 
539 |    32 attribute: MIN NUMBER_LITERAL •
540 | 
541 |     $default  reduce using rule 32 (attribute)
542 | 
543 | 
544 | State 52
545 | 
546 |    33 attribute: MAX NUMBER_LITERAL •
547 | 
548 |     $default  reduce using rule 33 (attribute)
549 | 
550 | 
551 | State 53
552 | 
553 |    34 attribute: ROWS NUMBER_LITERAL •
554 | 
555 |     $default  reduce using rule 34 (attribute)
556 | 
557 | 
558 | State 54
559 | 
560 |    35 attribute: COLS NUMBER_LITERAL •
561 | 
562 |     $default  reduce using rule 35 (attribute)
563 | 
564 | 
565 | State 55
566 | 
567 |    27 attribute: PATTERN STRING_LITERAL •
568 | 
569 |     $default  reduce using rule 27 (attribute)
570 | 
571 | 
572 | State 56
573 | 
574 |    29 attribute: DEFAULT NUMBER_LITERAL •
575 | 
576 |     $default  reduce using rule 29 (attribute)
577 | 
578 | 
579 | State 57
580 | 
581 |    28 attribute: DEFAULT STRING_LITERAL •
582 | 
583 |     $default  reduce using rule 28 (attribute)
```

src/parser.tab.c
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
101 |     form->validation_rules = NULL;
102 |     return form;
103 | }
104 | 
105 | Section* create_section(const char* name) {
106 |     Section* section = malloc(sizeof(Section));
107 |     if (!section) return NULL;
108 |     section->name = strdup(name);
109 |     section->fields = NULL;
110 |     section->field_count = 0;
111 |     return section;
112 | }
113 | 
114 | void add_section_to_form(Form* form, Section* section) {
115 |     if (!form || !section) {
116 |         fprintf(stderr, "Null form or section\n");
117 |         return;
118 |     }
119 |     
120 |     Section** new_sections = realloc(form->sections, (form->section_count + 1) * sizeof(Section*));
121 |     if (!new_sections) {
122 |         fprintf(stderr, "Memory allocation failed for sections\n");
123 |         exit(1);
124 |     }
125 |     form->sections = new_sections;
126 |     form->sections[form->section_count] = section;
127 |     form->section_count++;
128 | }
129 | 
130 | int check_duplicate_field(const char* name) {
131 |     for (int i = 0; i < field_name_count; i++) {
132 |         if (strcmp(field_names[i].name, name) == 0) {
133 |             return 1;
134 |         }
135 |     }
136 |     return 0;
137 | }
138 | 
139 | void init_field_attributes(FieldAttributes* attrs) {
140 |     if (!attrs) return;
141 |     attrs->min_length = -1;
142 |     attrs->max_length = -1;
143 |     attrs->min_value = -1;
144 |     attrs->max_value = -1;
145 |     attrs->rows = -1;
146 |     attrs->cols = -1;
147 |     attrs->pattern = NULL;
148 |     attrs->default_value = NULL;
149 |     attrs->required = 0;
150 | }
151 | 
152 | void add_field_to_section(Section* section, const char* name, FieldType type, FieldAttributes* attrs) {
153 |     if (!section || !name || !attrs) {
154 |         fprintf(stderr, "Null section, name, or attrs\n");
155 |         return;
156 |     }
157 |     
158 |     // Add field name to tracking
159 |     field_name_count++;
160 |     FieldName* new_field_names = realloc(field_names, field_name_count * sizeof(FieldName));
161 |     if (!new_field_names) {
162 |         fprintf(stderr, "Memory allocation failed for field names\n");
163 |         exit(1);
164 |     }
165 |     field_names = new_field_names;
166 |     field_names[field_name_count - 1].name = strdup(name);
167 |     field_names[field_name_count - 1].line = yylineno;
168 |     
169 |     // Allocate memory for the new field
170 |     Field* new_fields = realloc(section->fields, (section->field_count + 1) * sizeof(Field));
171 |     if (!new_fields) {
172 |         fprintf(stderr, "Memory allocation failed for fields\n");
173 |         exit(1);
174 |     }
175 |     section->fields = new_fields;
176 |     
177 |     Field* field = &section->fields[section->field_count];
178 |     field->name = strdup(name);
179 |     field->type = type;
180 |     init_field_attributes(&field->attributes);
181 |     
182 |     // Copy attributes
183 |     field->attributes.min_length = attrs->min_length;
184 |     field->attributes.max_length = attrs->max_length;
185 |     field->attributes.min_value = attrs->min_value;
186 |     field->attributes.max_value = attrs->max_value;
187 |     field->attributes.rows = attrs->rows;
188 |     field->attributes.cols = attrs->cols;
189 |     field->attributes.required = attrs->required;
190 |     
191 |     if (attrs->pattern) {
192 |         field->attributes.pattern = strdup(attrs->pattern);
193 |     }
194 |     if (attrs->default_value) {
195 |         field->attributes.default_value = strdup(attrs->default_value);
196 |     }
197 |     
198 |     section->field_count++;
199 | }
200 | 
201 | void cleanup_form(Form* form) {
202 |     if (form) {
203 |         for (int i = 0; i < form->section_count; i++) {
204 |             Section* s = form->sections[i];
205 |             if (s) {
206 |                 for (int j = 0; j < s->field_count; j++) {
207 |                     Field* f = &s->fields[j];
208 |                     if (f->name) free(f->name);
209 |                     if (f->attributes.pattern) free(f->attributes.pattern);
210 |                     if (f->attributes.default_value) free(f->attributes.default_value);
211 |                 }
212 |                 if (s->fields) free(s->fields);
213 |                 if (s->name) free(s->name);
214 |                 free(s);
215 |             }
216 |         }
217 |         if (form->sections) free(form->sections);
218 |         if (form->name) free(form->name);
219 |         
220 |         // Cleanup validation rules
221 |         ValidationRule* rule = form->validation_rules;
222 |         while (rule) {
223 |             ValidationRule* next = rule->next;
224 |             if (rule->condition) free(rule->condition);
225 |             if (rule->error_message) free(rule->error_message);
226 |             free(rule);
227 |             rule = next;
228 |         }
229 |         
230 |         free(form);
231 |     }
232 |     
233 |     // Cleanup field name tracking
234 |     for (int i = 0; i < field_name_count; i++) {
235 |         if (field_names[i].name) free(field_names[i].name);
236 |     }
237 |     if (field_names) free(field_names);
238 |     field_name_count = 0;
239 | }
240 | 
241 | #line 242 "src/parser.tab.c"
242 | 
243 | # ifndef YY_CAST
244 | #  ifdef __cplusplus
245 | #   define YY_CAST(Type, Val) static_cast<Type> (Val)
246 | #   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
247 | #  else
248 | #   define YY_CAST(Type, Val) ((Type) (Val))
249 | #   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
250 | #  endif
251 | # endif
252 | # ifndef YY_NULLPTR
253 | #  if defined __cplusplus
254 | #   if 201103L <= __cplusplus
255 | #    define YY_NULLPTR nullptr
256 | #   else
257 | #    define YY_NULLPTR 0
258 | #   endif
259 | #  else
260 | #   define YY_NULLPTR ((void*)0)
261 | #  endif
262 | # endif
263 | 
264 | #include "parser.tab.h"
265 | /* Symbol kind.  */
266 | enum yysymbol_kind_t
267 | {
268 |   YYSYMBOL_YYEMPTY = -2,
269 |   YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
270 |   YYSYMBOL_YYerror = 1,                    /* error  */
271 |   YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
272 |   YYSYMBOL_FORM = 3,                       /* FORM  */
273 |   YYSYMBOL_SECTION = 4,                    /* SECTION  */
274 |   YYSYMBOL_FIELD = 5,                      /* FIELD  */
275 |   YYSYMBOL_TEXT = 6,                       /* TEXT  */
276 |   YYSYMBOL_EMAIL = 7,                      /* EMAIL  */
277 |   YYSYMBOL_PASSWORD = 8,                   /* PASSWORD  */
278 |   YYSYMBOL_NUMBER = 9,                     /* NUMBER  */
279 |   YYSYMBOL_TEXTAREA = 10,                  /* TEXTAREA  */
280 |   YYSYMBOL_DATE = 11,                      /* DATE  */
281 |   YYSYMBOL_CHECKBOX = 12,                  /* CHECKBOX  */
282 |   YYSYMBOL_DROPDOWN = 13,                  /* DROPDOWN  */
283 |   YYSYMBOL_RADIO = 14,                     /* RADIO  */
284 |   YYSYMBOL_FILE_TYPE = 15,                 /* FILE_TYPE  */
285 |   YYSYMBOL_USERNAME = 16,                  /* USERNAME  */
286 |   YYSYMBOL_ADDRESS = 17,                   /* ADDRESS  */
287 |   YYSYMBOL_REQUIRED = 18,                  /* REQUIRED  */
288 |   YYSYMBOL_OPTIONAL = 19,                  /* OPTIONAL  */
289 |   YYSYMBOL_MINLENGTH = 20,                 /* MINLENGTH  */
290 |   YYSYMBOL_MAXLENGTH = 21,                 /* MAXLENGTH  */
291 |   YYSYMBOL_MIN = 22,                       /* MIN  */
292 |   YYSYMBOL_MAX = 23,                       /* MAX  */
293 |   YYSYMBOL_ROWS = 24,                      /* ROWS  */
294 |   YYSYMBOL_COLS = 25,                      /* COLS  */
295 |   YYSYMBOL_PATTERN = 26,                   /* PATTERN  */
296 |   YYSYMBOL_DEFAULT = 27,                   /* DEFAULT  */
297 |   YYSYMBOL_CONFIRM = 28,                   /* CONFIRM  */
298 |   YYSYMBOL_STRENGTH = 29,                  /* STRENGTH  */
299 |   YYSYMBOL_IDENTIFIER = 30,                /* IDENTIFIER  */
300 |   YYSYMBOL_NUMBER_LITERAL = 31,            /* NUMBER_LITERAL  */
301 |   YYSYMBOL_STRING_LITERAL = 32,            /* STRING_LITERAL  */
302 |   YYSYMBOL_VALIDATE = 33,                  /* VALIDATE  */
303 |   YYSYMBOL_IF = 34,                        /* IF  */
304 |   YYSYMBOL_ERROR = 35,                     /* ERROR  */
305 |   YYSYMBOL_LT = 36,                        /* LT  */
306 |   YYSYMBOL_GT = 37,                        /* GT  */
307 |   YYSYMBOL_LTE = 38,                       /* LTE  */
308 |   YYSYMBOL_GTE = 39,                       /* GTE  */
309 |   YYSYMBOL_EQ = 40,                        /* EQ  */
310 |   YYSYMBOL_NEQ = 41,                       /* NEQ  */
311 |   YYSYMBOL_AND = 42,                       /* AND  */
312 |   YYSYMBOL_OR = 43,                        /* OR  */
313 |   YYSYMBOL_44_ = 44,                       /* '{'  */
314 |   YYSYMBOL_45_ = 45,                       /* '}'  */
315 |   YYSYMBOL_46_ = 46,                       /* ';'  */
316 |   YYSYMBOL_47_ = 47,                       /* ':'  */
317 |   YYSYMBOL_YYACCEPT = 48,                  /* $accept  */
318 |   YYSYMBOL_form = 49,                      /* form  */
319 |   YYSYMBOL_50_1 = 50,                      /* $@1  */
320 |   YYSYMBOL_form_body = 51,                 /* form_body  */
321 |   YYSYMBOL_form_item = 52,                 /* form_item  */
322 |   YYSYMBOL_section = 53,                   /* section  */
323 |   YYSYMBOL_section_header = 54,            /* section_header  */
324 |   YYSYMBOL_field_list = 55,                /* field_list  */
325 |   YYSYMBOL_field = 56,                     /* field  */
326 |   YYSYMBOL_field_type = 57,                /* field_type  */
327 |   YYSYMBOL_field_attributes = 58,          /* field_attributes  */
328 |   YYSYMBOL_attribute = 59,                 /* attribute  */
329 |   YYSYMBOL_validation_block = 60,          /* validation_block  */
330 |   YYSYMBOL_validation_rules = 61,          /* validation_rules  */
331 |   YYSYMBOL_validation_rule = 62,           /* validation_rule  */
332 |   YYSYMBOL_condition = 63                  /* condition  */
333 | };
334 | typedef enum yysymbol_kind_t yysymbol_kind_t;
335 | 
336 | 
337 | 
338 | 
339 | #ifdef short
340 | # undef short
341 | #endif
342 | 
343 | /* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
344 |    <limits.h> and (if available) <stdint.h> are included
345 |    so that the code can choose integer types of a good width.  */
346 | 
347 | #ifndef __PTRDIFF_MAX__
348 | # include <limits.h> /* INFRINGES ON USER NAME SPACE */
349 | # if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
350 | #  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
351 | #  define YY_STDINT_H
352 | # endif
353 | #endif
354 | 
355 | /* Narrow types that promote to a signed type and that can represent a
356 |    signed or unsigned integer of at least N bits.  In tables they can
357 |    save space and decrease cache pressure.  Promoting to a signed type
358 |    helps avoid bugs in integer arithmetic.  */
359 | 
360 | #ifdef __INT_LEAST8_MAX__
361 | typedef __INT_LEAST8_TYPE__ yytype_int8;
362 | #elif defined YY_STDINT_H
363 | typedef int_least8_t yytype_int8;
364 | #else
365 | typedef signed char yytype_int8;
366 | #endif
367 | 
368 | #ifdef __INT_LEAST16_MAX__
369 | typedef __INT_LEAST16_TYPE__ yytype_int16;
370 | #elif defined YY_STDINT_H
371 | typedef int_least16_t yytype_int16;
372 | #else
373 | typedef short yytype_int16;
374 | #endif
375 | 
376 | /* Work around bug in HP-UX 11.23, which defines these macros
377 |    incorrectly for preprocessor constants.  This workaround can likely
378 |    be removed in 2023, as HPE has promised support for HP-UX 11.23
379 |    (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
380 |    <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
381 | #ifdef __hpux
382 | # undef UINT_LEAST8_MAX
383 | # undef UINT_LEAST16_MAX
384 | # define UINT_LEAST8_MAX 255
385 | # define UINT_LEAST16_MAX 65535
386 | #endif
387 | 
388 | #if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
389 | typedef __UINT_LEAST8_TYPE__ yytype_uint8;
390 | #elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
391 |        && UINT_LEAST8_MAX <= INT_MAX)
392 | typedef uint_least8_t yytype_uint8;
393 | #elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
394 | typedef unsigned char yytype_uint8;
395 | #else
396 | typedef short yytype_uint8;
397 | #endif
398 | 
399 | #if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
400 | typedef __UINT_LEAST16_TYPE__ yytype_uint16;
401 | #elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
402 |        && UINT_LEAST16_MAX <= INT_MAX)
403 | typedef uint_least16_t yytype_uint16;
404 | #elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
405 | typedef unsigned short yytype_uint16;
406 | #else
407 | typedef int yytype_uint16;
408 | #endif
409 | 
410 | #ifndef YYPTRDIFF_T
411 | # if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
412 | #  define YYPTRDIFF_T __PTRDIFF_TYPE__
413 | #  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
414 | # elif defined PTRDIFF_MAX
415 | #  ifndef ptrdiff_t
416 | #   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
417 | #  endif
418 | #  define YYPTRDIFF_T ptrdiff_t
419 | #  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
420 | # else
421 | #  define YYPTRDIFF_T long
422 | #  define YYPTRDIFF_MAXIMUM LONG_MAX
423 | # endif
424 | #endif
425 | 
426 | #ifndef YYSIZE_T
427 | # ifdef __SIZE_TYPE__
428 | #  define YYSIZE_T __SIZE_TYPE__
429 | # elif defined size_t
430 | #  define YYSIZE_T size_t
431 | # elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
432 | #  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
433 | #  define YYSIZE_T size_t
434 | # else
435 | #  define YYSIZE_T unsigned
436 | # endif
437 | #endif
438 | 
439 | #define YYSIZE_MAXIMUM                                  \
440 |   YY_CAST (YYPTRDIFF_T,                                 \
441 |            (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
442 |             ? YYPTRDIFF_MAXIMUM                         \
443 |             : YY_CAST (YYSIZE_T, -1)))
444 | 
445 | #define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))
446 | 
447 | 
448 | /* Stored state numbers (used for stacks). */
449 | typedef yytype_int8 yy_state_t;
450 | 
451 | /* State numbers in computations.  */
452 | typedef int yy_state_fast_t;
453 | 
454 | #ifndef YY_
455 | # if defined YYENABLE_NLS && YYENABLE_NLS
456 | #  if ENABLE_NLS
457 | #   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
458 | #   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
459 | #  endif
460 | # endif
461 | # ifndef YY_
462 | #  define YY_(Msgid) Msgid
463 | # endif
464 | #endif
465 | 
466 | 
467 | #ifndef YY_ATTRIBUTE_PURE
468 | # if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
469 | #  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
470 | # else
471 | #  define YY_ATTRIBUTE_PURE
472 | # endif
473 | #endif
474 | 
475 | #ifndef YY_ATTRIBUTE_UNUSED
476 | # if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
477 | #  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
478 | # else
479 | #  define YY_ATTRIBUTE_UNUSED
480 | # endif
481 | #endif
482 | 
483 | /* Suppress unused-variable warnings by "using" E.  */
484 | #if ! defined lint || defined __GNUC__
485 | # define YY_USE(E) ((void) (E))
486 | #else
487 | # define YY_USE(E) /* empty */
488 | #endif
489 | 
490 | /* Suppress an incorrect diagnostic about yylval being uninitialized.  */
491 | #if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
492 | # if __GNUC__ * 100 + __GNUC_MINOR__ < 407
493 | #  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
494 |     _Pragma ("GCC diagnostic push")                                     \
495 |     _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
496 | # else
497 | #  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
498 |     _Pragma ("GCC diagnostic push")                                     \
499 |     _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
500 |     _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
501 | # endif
502 | # define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
503 |     _Pragma ("GCC diagnostic pop")
504 | #else
505 | # define YY_INITIAL_VALUE(Value) Value
506 | #endif
507 | #ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
508 | # define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
509 | # define YY_IGNORE_MAYBE_UNINITIALIZED_END
510 | #endif
511 | #ifndef YY_INITIAL_VALUE
512 | # define YY_INITIAL_VALUE(Value) /* Nothing. */
513 | #endif
514 | 
515 | #if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
516 | # define YY_IGNORE_USELESS_CAST_BEGIN                          \
517 |     _Pragma ("GCC diagnostic push")                            \
518 |     _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
519 | # define YY_IGNORE_USELESS_CAST_END            \
520 |     _Pragma ("GCC diagnostic pop")
521 | #endif
522 | #ifndef YY_IGNORE_USELESS_CAST_BEGIN
523 | # define YY_IGNORE_USELESS_CAST_BEGIN
524 | # define YY_IGNORE_USELESS_CAST_END
525 | #endif
526 | 
527 | 
528 | #define YY_ASSERT(E) ((void) (0 && (E)))
529 | 
530 | #if 1
531 | 
532 | /* The parser invokes alloca or malloc; define the necessary symbols.  */
533 | 
534 | # ifdef YYSTACK_USE_ALLOCA
535 | #  if YYSTACK_USE_ALLOCA
536 | #   ifdef __GNUC__
537 | #    define YYSTACK_ALLOC __builtin_alloca
538 | #   elif defined __BUILTIN_VA_ARG_INCR
539 | #    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
540 | #   elif defined _AIX
541 | #    define YYSTACK_ALLOC __alloca
542 | #   elif defined _MSC_VER
543 | #    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
544 | #    define alloca _alloca
545 | #   else
546 | #    define YYSTACK_ALLOC alloca
547 | #    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
548 | #     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
549 |       /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
550 | #     ifndef EXIT_SUCCESS
551 | #      define EXIT_SUCCESS 0
552 | #     endif
553 | #    endif
554 | #   endif
555 | #  endif
556 | # endif
557 | 
558 | # ifdef YYSTACK_ALLOC
559 |    /* Pacify GCC's 'empty if-body' warning.  */
560 | #  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
561 | #  ifndef YYSTACK_ALLOC_MAXIMUM
562 |     /* The OS might guarantee only one guard page at the bottom of the stack,
563 |        and a page size can be as small as 4096 bytes.  So we cannot safely
564 |        invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
565 |        to allow for a few compiler-allocated temporary stack slots.  */
566 | #   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
567 | #  endif
568 | # else
569 | #  define YYSTACK_ALLOC YYMALLOC
570 | #  define YYSTACK_FREE YYFREE
571 | #  ifndef YYSTACK_ALLOC_MAXIMUM
572 | #   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
573 | #  endif
574 | #  if (defined __cplusplus && ! defined EXIT_SUCCESS \
575 |        && ! ((defined YYMALLOC || defined malloc) \
576 |              && (defined YYFREE || defined free)))
577 | #   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
578 | #   ifndef EXIT_SUCCESS
579 | #    define EXIT_SUCCESS 0
580 | #   endif
581 | #  endif
582 | #  ifndef YYMALLOC
583 | #   define YYMALLOC malloc
584 | #   if ! defined malloc && ! defined EXIT_SUCCESS
585 | void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
586 | #   endif
587 | #  endif
588 | #  ifndef YYFREE
589 | #   define YYFREE free
590 | #   if ! defined free && ! defined EXIT_SUCCESS
591 | void free (void *); /* INFRINGES ON USER NAME SPACE */
592 | #   endif
593 | #  endif
594 | # endif
595 | #endif /* 1 */
596 | 
597 | #if (! defined yyoverflow \
598 |      && (! defined __cplusplus \
599 |          || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))
600 | 
601 | /* A type that is properly aligned for any stack member.  */
602 | union yyalloc
603 | {
604 |   yy_state_t yyss_alloc;
605 |   YYSTYPE yyvs_alloc;
606 | };
607 | 
608 | /* The size of the maximum gap between one aligned stack and the next.  */
609 | # define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)
610 | 
611 | /* The size of an array large to enough to hold all stacks, each with
612 |    N elements.  */
613 | # define YYSTACK_BYTES(N) \
614 |      ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
615 |       + YYSTACK_GAP_MAXIMUM)
616 | 
617 | # define YYCOPY_NEEDED 1
618 | 
619 | /* Relocate STACK from its old location to the new one.  The
620 |    local variables YYSIZE and YYSTACKSIZE give the old and new number of
621 |    elements in the stack, and YYPTR gives the new location of the
622 |    stack.  Advance YYPTR to a properly aligned location for the next
623 |    stack.  */
624 | # define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
625 |     do                                                                  \
626 |       {                                                                 \
627 |         YYPTRDIFF_T yynewbytes;                                         \
628 |         YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
629 |         Stack = &yyptr->Stack_alloc;                                    \
630 |         yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
631 |         yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
632 |       }                                                                 \
633 |     while (0)
634 | 
635 | #endif
636 | 
637 | #if defined YYCOPY_NEEDED && YYCOPY_NEEDED
638 | /* Copy COUNT objects from SRC to DST.  The source and destination do
639 |    not overlap.  */
640 | # ifndef YYCOPY
641 | #  if defined __GNUC__ && 1 < __GNUC__
642 | #   define YYCOPY(Dst, Src, Count) \
643 |       __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
644 | #  else
645 | #   define YYCOPY(Dst, Src, Count)              \
646 |       do                                        \
647 |         {                                       \
648 |           YYPTRDIFF_T yyi;                      \
649 |           for (yyi = 0; yyi < (Count); yyi++)   \
650 |             (Dst)[yyi] = (Src)[yyi];            \
651 |         }                                       \
652 |       while (0)
653 | #  endif
654 | # endif
655 | #endif /* !YYCOPY_NEEDED */
656 | 
657 | /* YYFINAL -- State number of the termination state.  */
658 | #define YYFINAL  4
659 | /* YYLAST -- Last index in YYTABLE.  */
660 | #define YYLAST   77
661 | 
662 | /* YYNTOKENS -- Number of terminals.  */
663 | #define YYNTOKENS  48
664 | /* YYNNTS -- Number of nonterminals.  */
665 | #define YYNNTS  16
666 | /* YYNRULES -- Number of rules.  */
667 | #define YYNRULES  52
668 | /* YYNSTATES -- Number of states.  */
669 | #define YYNSTATES  91
670 | 
671 | /* YYMAXUTOK -- Last valid token kind.  */
672 | #define YYMAXUTOK   298
673 | 
674 | 
675 | /* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
676 |    as returned by yylex, with out-of-bounds checking.  */
677 | #define YYTRANSLATE(YYX)                                \
678 |   (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
679 |    ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
680 |    : YYSYMBOL_YYUNDEF)
681 | 
682 | /* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
683 |    as returned by yylex.  */
684 | static const yytype_int8 yytranslate[] =
685 | {
686 |        0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
687 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
688 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
689 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
690 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
691 |        2,     2,     2,     2,     2,     2,     2,     2,    47,    46,
692 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
693 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
694 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
695 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
696 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
697 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
698 |        2,     2,     2,    44,     2,    45,     2,     2,     2,     2,
699 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
700 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
701 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
702 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
703 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
704 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
705 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
706 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
707 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
708 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
709 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
710 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
711 |        2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
712 |        5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
713 |       15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
714 |       25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
715 |       35,    36,    37,    38,    39,    40,    41,    42,    43
716 | };
717 | 
718 | #if YYDEBUG
719 | /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
720 | static const yytype_int16 yyrline[] =
721 | {
722 |        0,   199,   199,   198,   213,   214,   218,   219,   226,   230,
723 |      234,   243,   258,   259,   260,   268,   283,   284,   285,   286,
724 |      287,   288,   289,   290,   291,   292,   293,   294,   298,   301,
725 |      322,   327,   332,   337,   342,   349,   354,   359,   364,   369,
726 |      374,   379,   384,   395,   398,   399,   402,   412,   418,   424,
727 |      430,   436,   442
728 | };
729 | #endif
730 | 
731 | /** Accessing symbol of state STATE.  */
732 | #define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])
733 | 
734 | #if 1
735 | /* The user-facing name of the symbol whose (internal) number is
736 |    YYSYMBOL.  No bounds checking.  */
737 | static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;
738 | 
739 | /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
740 |    First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
741 | static const char *const yytname[] =
742 | {
743 |   "\"end of file\"", "error", "\"invalid token\"", "FORM", "SECTION",
744 |   "FIELD", "TEXT", "EMAIL", "PASSWORD", "NUMBER", "TEXTAREA", "DATE",
745 |   "CHECKBOX", "DROPDOWN", "RADIO", "FILE_TYPE", "USERNAME", "ADDRESS",
746 |   "REQUIRED", "OPTIONAL", "MINLENGTH", "MAXLENGTH", "MIN", "MAX", "ROWS",
747 |   "COLS", "PATTERN", "DEFAULT", "CONFIRM", "STRENGTH", "IDENTIFIER",
748 |   "NUMBER_LITERAL", "STRING_LITERAL", "VALIDATE", "IF", "ERROR", "LT",
749 |   "GT", "LTE", "GTE", "EQ", "NEQ", "AND", "OR", "'{'", "'}'", "';'", "':'",
750 |   "$accept", "form", "$@1", "form_body", "form_item", "section",
751 |   "section_header", "field_list", "field", "field_type",
752 |   "field_attributes", "attribute", "validation_block", "validation_rules",
753 |   "validation_rule", "condition", YY_NULLPTR
754 | };
755 | 
756 | static const char *
757 | yysymbol_name (yysymbol_kind_t yysymbol)
758 | {
759 |   return yytname[yysymbol];
760 | }
761 | #endif
762 | 
763 | #define YYPACT_NINF (-28)
764 | 
765 | #define yypact_value_is_default(Yyn) \
766 |   ((Yyn) == YYPACT_NINF)
767 | 
768 | #define YYTABLE_NINF (-1)
769 | 
770 | #define yytable_value_is_error(Yyn) \
771 |   0
772 | 
773 | /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
774 |    STATE-NUM.  */
775 | static const yytype_int8 yypact[] =
776 | {
777 |       38,   -27,    43,   -28,   -28,     2,   -28,    -3,    17,     4,
778 |      -28,   -28,   -28,     1,   -28,   -28,   -28,     5,     6,    -5,
779 |      -28,   -28,    -1,    19,   -28,   -28,     7,    22,   -28,   -28,
780 |       -2,    10,   -28,     8,    25,    26,    27,    28,    29,    30,
781 |       31,    11,   -28,   -28,   -28,   -28,   -28,   -28,    32,   -28,
782 |      -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,
783 |      -28,   -28,    16,   -13,    18,   -28,   -28,    34,    36,    37,
784 |       39,    40,    41,    42,     0,    45,    46,   -28,   -28,   -28,
785 |      -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,
786 |      -28
787 | };
788 | 
789 | /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
790 |    Performed when YYTABLE does not specify something else to do.  Zero
791 |    means the default is an error.  */
792 | static const yytype_int8 yydefact[] =
793 | {
794 |        0,     0,     0,     2,     1,     0,     4,     0,     0,     0,
795 |        3,     5,     6,     0,     7,    11,    44,     0,    12,     0,
796 |       10,     9,     0,     0,    43,    45,     0,     0,     8,    13,
797 |        0,     0,    14,     0,     0,     0,     0,     0,     0,     0,
798 |        0,     0,    47,    48,    49,    50,    51,    52,     0,    16,
799 |       17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
800 |       27,    28,     0,     0,     0,    30,    31,     0,     0,     0,
801 |        0,     0,     0,     0,     0,     0,     0,    15,    29,    46,
802 |       35,    36,    37,    38,    39,    40,    32,    34,    33,    41,
803 |       42
804 | };
805 | 
806 | /* YYPGOTO[NTERM-NUM].  */
807 | static const yytype_int8 yypgoto[] =
808 | {
809 |      -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,
810 |      -28,   -28,   -28,   -28,   -28,   -28
811 | };
812 | 
813 | /* YYDEFGOTO[NTERM-NUM].  */
814 | static const yytype_int8 yydefgoto[] =
815 | {
816 |        0,     2,     5,     7,    11,    12,    13,    22,    29,    61,
817 |       63,    78,    14,    19,    25,    31
818 | };
819 | 
820 | /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
821 |    positive, shift that token.  If negative, reduce the rule whose
822 |    number is the opposite.  If YYTABLE_NINF, syntax error.  */
823 | static const yytype_int8 yytable[] =
824 | {
825 |       26,     8,    17,     3,    27,    65,    66,    67,    68,    69,
826 |       70,    71,    72,    73,    74,    75,    76,    49,    50,    51,
827 |       52,    53,    54,    55,    56,    57,    58,    59,    60,    23,
828 |        9,    87,    88,    77,    34,    35,    36,    37,    38,    39,
829 |       24,     1,    10,     4,    28,    18,     6,    15,    16,    30,
830 |       20,    21,    33,    32,    40,    41,    42,    43,    44,    45,
831 |       46,    47,    64,    79,    62,    80,    48,    81,    82,     0,
832 |       83,    84,    85,     0,    86,    89,     0,    90
833 | };
834 | 
835 | static const yytype_int8 yycheck[] =
836 | {
837 |        1,     4,     1,    30,     5,    18,    19,    20,    21,    22,
838 |       23,    24,    25,    26,    27,    28,    29,     6,     7,     8,
839 |        9,    10,    11,    12,    13,    14,    15,    16,    17,    34,
840 |       33,    31,    32,    46,    36,    37,    38,    39,    40,    41,
841 |       45,     3,    45,     0,    45,    44,    44,    30,    44,    30,
842 |       45,    45,    30,    46,    44,    47,    31,    31,    31,    31,
843 |       31,    31,    46,    45,    32,    31,    35,    31,    31,    -1,
844 |       31,    31,    31,    -1,    32,    30,    -1,    31
845 | };
846 | 
847 | /* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
848 |    state STATE-NUM.  */
849 | static const yytype_int8 yystos[] =
850 | {
851 |        0,     3,    49,    30,     0,    50,    44,    51,     4,    33,
852 |       45,    52,    53,    54,    60,    30,    44,     1,    44,    61,
853 |       45,    45,    55,    34,    45,    62,     1,     5,    45,    56,
854 |       30,    63,    46,    30,    36,    37,    38,    39,    40,    41,
855 |       44,    47,    31,    31,    31,    31,    31,    31,    35,     6,
856 |        7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
857 |       17,    57,    32,    58,    46,    18,    19,    20,    21,    22,
858 |       23,    24,    25,    26,    27,    28,    29,    46,    59,    45,
859 |       31,    31,    31,    31,    31,    31,    32,    31,    32,    30,
860 |       31
861 | };
862 | 
863 | /* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
864 | static const yytype_int8 yyr1[] =
865 | {
866 |        0,    48,    50,    49,    51,    51,    52,    52,    53,    53,
867 |       53,    54,    55,    55,    55,    56,    57,    57,    57,    57,
868 |       57,    57,    57,    57,    57,    57,    57,    57,    58,    58,
869 |       59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
870 |       59,    59,    59,    60,    61,    61,    62,    63,    63,    63,
871 |       63,    63,    63
872 | };
873 | 
874 | /* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
875 | static const yytype_int8 yyr2[] =
876 | {
877 |        0,     2,     0,     6,     0,     2,     1,     1,     4,     3,
878 |        3,     2,     0,     2,     3,     6,     1,     1,     1,     1,
879 |        1,     1,     1,     1,     1,     1,     1,     1,     0,     2,
880 |        1,     1,     2,     2,     2,     2,     2,     2,     2,     2,
881 |        2,     2,     2,     4,     0,     2,     7,     3,     3,     3,
882 |        3,     3,     3
883 | };
884 | 
885 | 
886 | enum { YYENOMEM = -2 };
887 | 
888 | #define yyerrok         (yyerrstatus = 0)
889 | #define yyclearin       (yychar = YYEMPTY)
890 | 
891 | #define YYACCEPT        goto yyacceptlab
892 | #define YYABORT         goto yyabortlab
893 | #define YYERROR         goto yyerrorlab
894 | #define YYNOMEM         goto yyexhaustedlab
895 | 
896 | 
897 | #define YYRECOVERING()  (!!yyerrstatus)
898 | 
899 | #define YYBACKUP(Token, Value)                                    \
900 |   do                                                              \
901 |     if (yychar == YYEMPTY)                                        \
902 |       {                                                           \
903 |         yychar = (Token);                                         \
904 |         yylval = (Value);                                         \
905 |         YYPOPSTACK (yylen);                                       \
906 |         yystate = *yyssp;                                         \
907 |         goto yybackup;                                            \
908 |       }                                                           \
909 |     else                                                          \
910 |       {                                                           \
911 |         yyerror (YY_("syntax error: cannot back up")); \
912 |         YYERROR;                                                  \
913 |       }                                                           \
914 |   while (0)
915 | 
916 | /* Backward compatibility with an undocumented macro.
917 |    Use YYerror or YYUNDEF. */
918 | #define YYERRCODE YYUNDEF
919 | 
920 | 
921 | /* Enable debugging if requested.  */
922 | #if YYDEBUG
923 | 
924 | # ifndef YYFPRINTF
925 | #  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
926 | #  define YYFPRINTF fprintf
927 | # endif
928 | 
929 | # define YYDPRINTF(Args)                        \
930 | do {                                            \
931 |   if (yydebug)                                  \
932 |     YYFPRINTF Args;                             \
933 | } while (0)
934 | 
935 | 
936 | 
937 | 
938 | # define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
939 | do {                                                                      \
940 |   if (yydebug)                                                            \
941 |     {                                                                     \
942 |       YYFPRINTF (stderr, "%s ", Title);                                   \
943 |       yy_symbol_print (stderr,                                            \
944 |                   Kind, Value); \
945 |       YYFPRINTF (stderr, "\n");                                           \
946 |     }                                                                     \
947 | } while (0)
948 | 
949 | 
950 | /*-----------------------------------.
951 | | Print this symbol's value on YYO.  |
952 | `-----------------------------------*/
953 | 
954 | static void
955 | yy_symbol_value_print (FILE *yyo,
956 |                        yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
957 | {
958 |   FILE *yyoutput = yyo;
959 |   YY_USE (yyoutput);
960 |   if (!yyvaluep)
961 |     return;
962 |   YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
963 |   YY_USE (yykind);
964 |   YY_IGNORE_MAYBE_UNINITIALIZED_END
965 | }
966 | 
967 | 
968 | /*---------------------------.
969 | | Print this symbol on YYO.  |
970 | `---------------------------*/
971 | 
972 | static void
973 | yy_symbol_print (FILE *yyo,
974 |                  yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
975 | {
976 |   YYFPRINTF (yyo, "%s %s (",
977 |              yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));
978 | 
979 |   yy_symbol_value_print (yyo, yykind, yyvaluep);
980 |   YYFPRINTF (yyo, ")");
981 | }
982 | 
983 | /*------------------------------------------------------------------.
984 | | yy_stack_print -- Print the state stack from its BOTTOM up to its |
985 | | TOP (included).                                                   |
986 | `------------------------------------------------------------------*/
987 | 
988 | static void
989 | yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
990 | {
991 |   YYFPRINTF (stderr, "Stack now");
992 |   for (; yybottom <= yytop; yybottom++)
993 |     {
994 |       int yybot = *yybottom;
995 |       YYFPRINTF (stderr, " %d", yybot);
996 |     }
997 |   YYFPRINTF (stderr, "\n");
998 | }
999 | 
1000 | # define YY_STACK_PRINT(Bottom, Top)                            \
1001 | do {                                                            \
1002 |   if (yydebug)                                                  \
1003 |     yy_stack_print ((Bottom), (Top));                           \
1004 | } while (0)
1005 | 
1006 | 
1007 | /*------------------------------------------------.
1008 | | Report that the YYRULE is going to be reduced.  |
1009 | `------------------------------------------------*/
1010 | 
1011 | static void
1012 | yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
1013 |                  int yyrule)
1014 | {
1015 |   int yylno = yyrline[yyrule];
1016 |   int yynrhs = yyr2[yyrule];
1017 |   int yyi;
1018 |   YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
1019 |              yyrule - 1, yylno);
1020 |   /* The symbols being reduced.  */
1021 |   for (yyi = 0; yyi < yynrhs; yyi++)
1022 |     {
1023 |       YYFPRINTF (stderr, "   $%d = ", yyi + 1);
1024 |       yy_symbol_print (stderr,
1025 |                        YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
1026 |                        &yyvsp[(yyi + 1) - (yynrhs)]);
1027 |       YYFPRINTF (stderr, "\n");
1028 |     }
1029 | }
1030 | 
1031 | # define YY_REDUCE_PRINT(Rule)          \
1032 | do {                                    \
1033 |   if (yydebug)                          \
1034 |     yy_reduce_print (yyssp, yyvsp, Rule); \
1035 | } while (0)
1036 | 
1037 | /* Nonzero means print parse trace.  It is left uninitialized so that
1038 |    multiple parsers can coexist.  */
1039 | int yydebug;
1040 | #else /* !YYDEBUG */
1041 | # define YYDPRINTF(Args) ((void) 0)
1042 | # define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
1043 | # define YY_STACK_PRINT(Bottom, Top)
1044 | # define YY_REDUCE_PRINT(Rule)
1045 | #endif /* !YYDEBUG */
1046 | 
1047 | 
1048 | /* YYINITDEPTH -- initial size of the parser's stacks.  */
1049 | #ifndef YYINITDEPTH
1050 | # define YYINITDEPTH 200
1051 | #endif
1052 | 
1053 | /* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
1054 |    if the built-in stack extension method is used).
1055 | 
1056 |    Do not make this value too large; the results are undefined if
1057 |    YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
1058 |    evaluated with infinite-precision integer arithmetic.  */
1059 | 
1060 | #ifndef YYMAXDEPTH
1061 | # define YYMAXDEPTH 10000
1062 | #endif
1063 | 
1064 | 
1065 | /* Context of a parse error.  */
1066 | typedef struct
1067 | {
1068 |   yy_state_t *yyssp;
1069 |   yysymbol_kind_t yytoken;
1070 | } yypcontext_t;
1071 | 
1072 | /* Put in YYARG at most YYARGN of the expected tokens given the
1073 |    current YYCTX, and return the number of tokens stored in YYARG.  If
1074 |    YYARG is null, return the number of expected tokens (guaranteed to
1075 |    be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
1076 |    Return 0 if there are more than YYARGN expected tokens, yet fill
1077 |    YYARG up to YYARGN. */
1078 | static int
1079 | yypcontext_expected_tokens (const yypcontext_t *yyctx,
1080 |                             yysymbol_kind_t yyarg[], int yyargn)
1081 | {
1082 |   /* Actual size of YYARG. */
1083 |   int yycount = 0;
1084 |   int yyn = yypact[+*yyctx->yyssp];
1085 |   if (!yypact_value_is_default (yyn))
1086 |     {
1087 |       /* Start YYX at -YYN if negative to avoid negative indexes in
1088 |          YYCHECK.  In other words, skip the first -YYN actions for
1089 |          this state because they are default actions.  */
1090 |       int yyxbegin = yyn < 0 ? -yyn : 0;
1091 |       /* Stay within bounds of both yycheck and yytname.  */
1092 |       int yychecklim = YYLAST - yyn + 1;
1093 |       int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
1094 |       int yyx;
1095 |       for (yyx = yyxbegin; yyx < yyxend; ++yyx)
1096 |         if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
1097 |             && !yytable_value_is_error (yytable[yyx + yyn]))
1098 |           {
1099 |             if (!yyarg)
1100 |               ++yycount;
1101 |             else if (yycount == yyargn)
1102 |               return 0;
1103 |             else
1104 |               yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
1105 |           }
1106 |     }
1107 |   if (yyarg && yycount == 0 && 0 < yyargn)
1108 |     yyarg[0] = YYSYMBOL_YYEMPTY;
1109 |   return yycount;
1110 | }
1111 | 
1112 | 
1113 | 
1114 | 
1115 | #ifndef yystrlen
1116 | # if defined __GLIBC__ && defined _STRING_H
1117 | #  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
1118 | # else
1119 | /* Return the length of YYSTR.  */
1120 | static YYPTRDIFF_T
1121 | yystrlen (const char *yystr)
1122 | {
1123 |   YYPTRDIFF_T yylen;
1124 |   for (yylen = 0; yystr[yylen]; yylen++)
1125 |     continue;
1126 |   return yylen;
1127 | }
1128 | # endif
1129 | #endif
1130 | 
1131 | #ifndef yystpcpy
1132 | # if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
1133 | #  define yystpcpy stpcpy
1134 | # else
1135 | /* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
1136 |    YYDEST.  */
1137 | static char *
1138 | yystpcpy (char *yydest, const char *yysrc)
1139 | {
1140 |   char *yyd = yydest;
1141 |   const char *yys = yysrc;
1142 | 
1143 |   while ((*yyd++ = *yys++) != '\0')
1144 |     continue;
1145 | 
1146 |   return yyd - 1;
1147 | }
1148 | # endif
1149 | #endif
1150 | 
1151 | #ifndef yytnamerr
1152 | /* Copy to YYRES the contents of YYSTR after stripping away unnecessary
1153 |    quotes and backslashes, so that it's suitable for yyerror.  The
1154 |    heuristic is that double-quoting is unnecessary unless the string
1155 |    contains an apostrophe, a comma, or backslash (other than
1156 |    backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
1157 |    null, do not copy; instead, return the length of what the result
1158 |    would have been.  */
1159 | static YYPTRDIFF_T
1160 | yytnamerr (char *yyres, const char *yystr)
1161 | {
1162 |   if (*yystr == '"')
1163 |     {
1164 |       YYPTRDIFF_T yyn = 0;
1165 |       char const *yyp = yystr;
1166 |       for (;;)
1167 |         switch (*++yyp)
1168 |           {
1169 |           case '\'':
1170 |           case ',':
1171 |             goto do_not_strip_quotes;
1172 | 
1173 |           case '\\':
1174 |             if (*++yyp != '\\')
1175 |               goto do_not_strip_quotes;
1176 |             else
1177 |               goto append;
1178 | 
1179 |           append:
1180 |           default:
1181 |             if (yyres)
1182 |               yyres[yyn] = *yyp;
1183 |             yyn++;
1184 |             break;
1185 | 
1186 |           case '"':
1187 |             if (yyres)
1188 |               yyres[yyn] = '\0';
1189 |             return yyn;
1190 |           }
1191 |     do_not_strip_quotes: ;
1192 |     }
1193 | 
1194 |   if (yyres)
1195 |     return yystpcpy (yyres, yystr) - yyres;
1196 |   else
1197 |     return yystrlen (yystr);
1198 | }
1199 | #endif
1200 | 
1201 | 
1202 | static int
1203 | yy_syntax_error_arguments (const yypcontext_t *yyctx,
1204 |                            yysymbol_kind_t yyarg[], int yyargn)
1205 | {
1206 |   /* Actual size of YYARG. */
1207 |   int yycount = 0;
1208 |   /* There are many possibilities here to consider:
1209 |      - If this state is a consistent state with a default action, then
1210 |        the only way this function was invoked is if the default action
1211 |        is an error action.  In that case, don't check for expected
1212 |        tokens because there are none.
1213 |      - The only way there can be no lookahead present (in yychar) is if
1214 |        this state is a consistent state with a default action.  Thus,
1215 |        detecting the absence of a lookahead is sufficient to determine
1216 |        that there is no unexpected or expected token to report.  In that
1217 |        case, just report a simple "syntax error".
1218 |      - Don't assume there isn't a lookahead just because this state is a
1219 |        consistent state with a default action.  There might have been a
1220 |        previous inconsistent state, consistent state with a non-default
1221 |        action, or user semantic action that manipulated yychar.
1222 |      - Of course, the expected token list depends on states to have
1223 |        correct lookahead information, and it depends on the parser not
1224 |        to perform extra reductions after fetching a lookahead from the
1225 |        scanner and before detecting a syntax error.  Thus, state merging
1226 |        (from LALR or IELR) and default reductions corrupt the expected
1227 |        token list.  However, the list is correct for canonical LR with
1228 |        one exception: it will still contain any token that will not be
1229 |        accepted due to an error action in a later state.
1230 |   */
1231 |   if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
1232 |     {
1233 |       int yyn;
1234 |       if (yyarg)
1235 |         yyarg[yycount] = yyctx->yytoken;
1236 |       ++yycount;
1237 |       yyn = yypcontext_expected_tokens (yyctx,
1238 |                                         yyarg ? yyarg + 1 : yyarg, yyargn - 1);
1239 |       if (yyn == YYENOMEM)
1240 |         return YYENOMEM;
1241 |       else
1242 |         yycount += yyn;
1243 |     }
1244 |   return yycount;
1245 | }
1246 | 
1247 | /* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
1248 |    about the unexpected token YYTOKEN for the state stack whose top is
1249 |    YYSSP.
1250 | 
1251 |    Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
1252 |    not large enough to hold the message.  In that case, also set
1253 |    *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
1254 |    required number of bytes is too large to store.  */
1255 | static int
1256 | yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
1257 |                 const yypcontext_t *yyctx)
1258 | {
1259 |   enum { YYARGS_MAX = 5 };
1260 |   /* Internationalized format string. */
1261 |   const char *yyformat = YY_NULLPTR;
1262 |   /* Arguments of yyformat: reported tokens (one for the "unexpected",
1263 |      one per "expected"). */
1264 |   yysymbol_kind_t yyarg[YYARGS_MAX];
1265 |   /* Cumulated lengths of YYARG.  */
1266 |   YYPTRDIFF_T yysize = 0;
1267 | 
1268 |   /* Actual size of YYARG. */
1269 |   int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
1270 |   if (yycount == YYENOMEM)
1271 |     return YYENOMEM;
1272 | 
1273 |   switch (yycount)
1274 |     {
1275 | #define YYCASE_(N, S)                       \
1276 |       case N:                               \
1277 |         yyformat = S;                       \
1278 |         break
1279 |     default: /* Avoid compiler warnings. */
1280 |       YYCASE_(0, YY_("syntax error"));
1281 |       YYCASE_(1, YY_("syntax error, unexpected %s"));
1282 |       YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
1283 |       YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
1284 |       YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
1285 |       YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
1286 | #undef YYCASE_
1287 |     }
1288 | 
1289 |   /* Compute error message size.  Don't count the "%s"s, but reserve
1290 |      room for the terminator.  */
1291 |   yysize = yystrlen (yyformat) - 2 * yycount + 1;
1292 |   {
1293 |     int yyi;
1294 |     for (yyi = 0; yyi < yycount; ++yyi)
1295 |       {
1296 |         YYPTRDIFF_T yysize1
1297 |           = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
1298 |         if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
1299 |           yysize = yysize1;
1300 |         else
1301 |           return YYENOMEM;
1302 |       }
1303 |   }
1304 | 
1305 |   if (*yymsg_alloc < yysize)
1306 |     {
1307 |       *yymsg_alloc = 2 * yysize;
1308 |       if (! (yysize <= *yymsg_alloc
1309 |              && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
1310 |         *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
1311 |       return -1;
1312 |     }
1313 | 
1314 |   /* Avoid sprintf, as that infringes on the user's name space.
1315 |      Don't have undefined behavior even if the translation
1316 |      produced a string with the wrong number of "%s"s.  */
1317 |   {
1318 |     char *yyp = *yymsg;
1319 |     int yyi = 0;
1320 |     while ((*yyp = *yyformat) != '\0')
1321 |       if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
1322 |         {
1323 |           yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
1324 |           yyformat += 2;
1325 |         }
1326 |       else
1327 |         {
1328 |           ++yyp;
1329 |           ++yyformat;
1330 |         }
1331 |   }
1332 |   return 0;
1333 | }
1334 | 
1335 | 
1336 | /*-----------------------------------------------.
1337 | | Release the memory associated to this symbol.  |
1338 | `-----------------------------------------------*/
1339 | 
1340 | static void
1341 | yydestruct (const char *yymsg,
1342 |             yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
1343 | {
1344 |   YY_USE (yyvaluep);
1345 |   if (!yymsg)
1346 |     yymsg = "Deleting";
1347 |   YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);
1348 | 
1349 |   YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
1350 |   YY_USE (yykind);
1351 |   YY_IGNORE_MAYBE_UNINITIALIZED_END
1352 | }
1353 | 
1354 | 
1355 | /* Lookahead token kind.  */
1356 | int yychar;
1357 | 
1358 | /* The semantic value of the lookahead symbol.  */
1359 | YYSTYPE yylval;
1360 | /* Number of syntax errors so far.  */
1361 | int yynerrs;
1362 | 
1363 | 
1364 | 
1365 | 
1366 | /*----------.
1367 | | yyparse.  |
1368 | `----------*/
1369 | 
1370 | int
1371 | yyparse (void)
1372 | {
1373 |     yy_state_fast_t yystate = 0;
1374 |     /* Number of tokens to shift before error messages enabled.  */
1375 |     int yyerrstatus = 0;
1376 | 
1377 |     /* Refer to the stacks through separate pointers, to allow yyoverflow
1378 |        to reallocate them elsewhere.  */
1379 | 
1380 |     /* Their size.  */
1381 |     YYPTRDIFF_T yystacksize = YYINITDEPTH;
1382 | 
1383 |     /* The state stack: array, bottom, top.  */
1384 |     yy_state_t yyssa[YYINITDEPTH];
1385 |     yy_state_t *yyss = yyssa;
1386 |     yy_state_t *yyssp = yyss;
1387 | 
1388 |     /* The semantic value stack: array, bottom, top.  */
1389 |     YYSTYPE yyvsa[YYINITDEPTH];
1390 |     YYSTYPE *yyvs = yyvsa;
1391 |     YYSTYPE *yyvsp = yyvs;
1392 | 
1393 |   int yyn;
1394 |   /* The return value of yyparse.  */
1395 |   int yyresult;
1396 |   /* Lookahead symbol kind.  */
1397 |   yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
1398 |   /* The variables used to return semantic value and location from the
1399 |      action routines.  */
1400 |   YYSTYPE yyval;
1401 | 
1402 |   /* Buffer for error messages, and its allocated size.  */
1403 |   char yymsgbuf[128];
1404 |   char *yymsg = yymsgbuf;
1405 |   YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
1406 | 
1407 | #define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))
1408 | 
1409 |   /* The number of symbols on the RHS of the reduced rule.
1410 |      Keep to zero when no symbol should be popped.  */
1411 |   int yylen = 0;
1412 | 
1413 |   YYDPRINTF ((stderr, "Starting parse\n"));
1414 | 
1415 |   yychar = YYEMPTY; /* Cause a token to be read.  */
1416 | 
1417 |   goto yysetstate;
1418 | 
1419 | 
1420 | /*------------------------------------------------------------.
1421 | | yynewstate -- push a new state, which is found in yystate.  |
1422 | `------------------------------------------------------------*/
1423 | yynewstate:
1424 |   /* In all cases, when you get here, the value and location stacks
1425 |      have just been pushed.  So pushing a state here evens the stacks.  */
1426 |   yyssp++;
1427 | 
1428 | 
1429 | /*--------------------------------------------------------------------.
1430 | | yysetstate -- set current state (the top of the stack) to yystate.  |
1431 | `--------------------------------------------------------------------*/
1432 | yysetstate:
1433 |   YYDPRINTF ((stderr, "Entering state %d\n", yystate));
1434 |   YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
1435 |   YY_IGNORE_USELESS_CAST_BEGIN
1436 |   *yyssp = YY_CAST (yy_state_t, yystate);
1437 |   YY_IGNORE_USELESS_CAST_END
1438 |   YY_STACK_PRINT (yyss, yyssp);
1439 | 
1440 |   if (yyss + yystacksize - 1 <= yyssp)
1441 | #if !defined yyoverflow && !defined YYSTACK_RELOCATE
1442 |     YYNOMEM;
1443 | #else
1444 |     {
1445 |       /* Get the current used size of the three stacks, in elements.  */
1446 |       YYPTRDIFF_T yysize = yyssp - yyss + 1;
1447 | 
1448 | # if defined yyoverflow
1449 |       {
1450 |         /* Give user a chance to reallocate the stack.  Use copies of
1451 |            these so that the &'s don't force the real ones into
1452 |            memory.  */
1453 |         yy_state_t *yyss1 = yyss;
1454 |         YYSTYPE *yyvs1 = yyvs;
1455 | 
1456 |         /* Each stack pointer address is followed by the size of the
1457 |            data in use in that stack, in bytes.  This used to be a
1458 |            conditional around just the two extra args, but that might
1459 |            be undefined if yyoverflow is a macro.  */
1460 |         yyoverflow (YY_("memory exhausted"),
1461 |                     &yyss1, yysize * YYSIZEOF (*yyssp),
1462 |                     &yyvs1, yysize * YYSIZEOF (*yyvsp),
1463 |                     &yystacksize);
1464 |         yyss = yyss1;
1465 |         yyvs = yyvs1;
1466 |       }
1467 | # else /* defined YYSTACK_RELOCATE */
1468 |       /* Extend the stack our own way.  */
1469 |       if (YYMAXDEPTH <= yystacksize)
1470 |         YYNOMEM;
1471 |       yystacksize *= 2;
1472 |       if (YYMAXDEPTH < yystacksize)
1473 |         yystacksize = YYMAXDEPTH;
1474 | 
1475 |       {
1476 |         yy_state_t *yyss1 = yyss;
1477 |         union yyalloc *yyptr =
1478 |           YY_CAST (union yyalloc *,
1479 |                    YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
1480 |         if (! yyptr)
1481 |           YYNOMEM;
1482 |         YYSTACK_RELOCATE (yyss_alloc, yyss);
1483 |         YYSTACK_RELOCATE (yyvs_alloc, yyvs);
1484 | #  undef YYSTACK_RELOCATE
1485 |         if (yyss1 != yyssa)
1486 |           YYSTACK_FREE (yyss1);
1487 |       }
1488 | # endif
1489 | 
1490 |       yyssp = yyss + yysize - 1;
1491 |       yyvsp = yyvs + yysize - 1;
1492 | 
1493 |       YY_IGNORE_USELESS_CAST_BEGIN
1494 |       YYDPRINTF ((stderr, "Stack size increased to %ld\n",
1495 |                   YY_CAST (long, yystacksize)));
1496 |       YY_IGNORE_USELESS_CAST_END
1497 | 
1498 |       if (yyss + yystacksize - 1 <= yyssp)
1499 |         YYABORT;
1500 |     }
1501 | #endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */
1502 | 
1503 | 
1504 |   if (yystate == YYFINAL)
1505 |     YYACCEPT;
1506 | 
1507 |   goto yybackup;
1508 | 
1509 | 
1510 | /*-----------.
1511 | | yybackup.  |
1512 | `-----------*/
1513 | yybackup:
1514 |   /* Do appropriate processing given the current state.  Read a
1515 |      lookahead token if we need one and don't already have one.  */
1516 | 
1517 |   /* First try to decide what to do without reference to lookahead token.  */
1518 |   yyn = yypact[yystate];
1519 |   if (yypact_value_is_default (yyn))
1520 |     goto yydefault;
1521 | 
1522 |   /* Not known => get a lookahead token if don't already have one.  */
1523 | 
1524 |   /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
1525 |   if (yychar == YYEMPTY)
1526 |     {
1527 |       YYDPRINTF ((stderr, "Reading a token\n"));
1528 |       yychar = yylex ();
1529 |     }
1530 | 
1531 |   if (yychar <= YYEOF)
1532 |     {
1533 |       yychar = YYEOF;
1534 |       yytoken = YYSYMBOL_YYEOF;
1535 |       YYDPRINTF ((stderr, "Now at end of input.\n"));
1536 |     }
1537 |   else if (yychar == YYerror)
1538 |     {
1539 |       /* The scanner already issued an error message, process directly
1540 |          to error recovery.  But do not keep the error token as
1541 |          lookahead, it is too special and may lead us to an endless
1542 |          loop in error recovery. */
1543 |       yychar = YYUNDEF;
1544 |       yytoken = YYSYMBOL_YYerror;
1545 |       goto yyerrlab1;
1546 |     }
1547 |   else
1548 |     {
1549 |       yytoken = YYTRANSLATE (yychar);
1550 |       YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
1551 |     }
1552 | 
1553 |   /* If the proper action on seeing token YYTOKEN is to reduce or to
1554 |      detect an error, take that action.  */
1555 |   yyn += yytoken;
1556 |   if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
1557 |     goto yydefault;
1558 |   yyn = yytable[yyn];
1559 |   if (yyn <= 0)
1560 |     {
1561 |       if (yytable_value_is_error (yyn))
1562 |         goto yyerrlab;
1563 |       yyn = -yyn;
1564 |       goto yyreduce;
1565 |     }
1566 | 
1567 |   /* Count tokens shifted since error; after three, turn off error
1568 |      status.  */
1569 |   if (yyerrstatus)
1570 |     yyerrstatus--;
1571 | 
1572 |   /* Shift the lookahead token.  */
1573 |   YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
1574 |   yystate = yyn;
1575 |   YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
1576 |   *++yyvsp = yylval;
1577 |   YY_IGNORE_MAYBE_UNINITIALIZED_END
1578 | 
1579 |   /* Discard the shifted token.  */
1580 |   yychar = YYEMPTY;
1581 |   goto yynewstate;
1582 | 
1583 | 
1584 | /*-----------------------------------------------------------.
1585 | | yydefault -- do the default action for the current state.  |
1586 | `-----------------------------------------------------------*/
1587 | yydefault:
1588 |   yyn = yydefact[yystate];
1589 |   if (yyn == 0)
1590 |     goto yyerrlab;
1591 |   goto yyreduce;
1592 | 
1593 | 
1594 | /*-----------------------------.
1595 | | yyreduce -- do a reduction.  |
1596 | `-----------------------------*/
1597 | yyreduce:
1598 |   /* yyn is the number of a rule to reduce with.  */
1599 |   yylen = yyr2[yyn];
1600 | 
1601 |   /* If YYLEN is nonzero, implement the default value of the action:
1602 |      '$$ = $1'.
1603 | 
1604 |      Otherwise, the following line sets YYVAL to garbage.
1605 |      This behavior is undocumented and Bison
1606 |      users should not rely upon it.  Assigning to YYVAL
1607 |      unconditionally makes the parser a bit smaller, and it avoids a
1608 |      GCC warning that YYVAL may be used uninitialized.  */
1609 |   yyval = yyvsp[1-yylen];
1610 | 
1611 | 
1612 |   YY_REDUCE_PRINT (yyn);
1613 |   switch (yyn)
1614 |     {
1615 |   case 2: /* $@1: %empty  */
1616 | #line 199 "src/parser.y"
1617 |     {
1618 |         current_form = create_form((yyvsp[0].str));
1619 |         if (!current_form) {
1620 |             yyerror("Failed to create form");
1621 |             YYERROR;
1622 |         }
1623 |     }
1624 | #line 1625 "src/parser.tab.c"
1625 |     break;
1626 | 
1627 |   case 3: /* form: FORM IDENTIFIER $@1 '{' form_body '}'  */
1628 | #line 207 "src/parser.y"
1629 |     {
1630 |         generate_html(stdout);
1631 |         (yyval.form) = current_form;
1632 |     }
1633 | #line 1634 "src/parser.tab.c"
1634 |     break;
1635 | 
1636 |   case 8: /* section: section_header '{' field_list '}'  */
1637 | #line 227 "src/parser.y"
1638 |     {
1639 |         current_section = NULL;
1640 |     }
1641 | #line 1642 "src/parser.tab.c"
1642 |     break;
1643 | 
1644 |   case 9: /* section: section_header '{' '}'  */
1645 | #line 231 "src/parser.y"
1646 |     {
1647 |         current_section = NULL;
1648 |     }
1649 | #line 1650 "src/parser.tab.c"
1650 |     break;
1651 | 
1652 |   case 10: /* section: section_header error '}'  */
1653 | #line 235 "src/parser.y"
1654 |     {
1655 |         yyerror("Invalid section declaration");
1656 |         current_section = NULL;
1657 |         yyclearin;
1658 |         yyerrok;
1659 |     }
1660 | #line 1661 "src/parser.tab.c"
1661 |     break;
1662 | 
1663 |   case 11: /* section_header: SECTION IDENTIFIER  */
1664 | #line 244 "src/parser.y"
1665 |     {
1666 |         if (current_section != NULL) {
1667 |             yyerror("Nested sections are not allowed");
1668 |             YYERROR;
1669 |         }
1670 |         current_section = create_section((yyvsp[0].str));
1671 |         if (!current_section) {
1672 |             yyerror("Failed to create section");
1673 |             YYERROR;
1674 |         }
1675 |         add_section_to_form(current_form, current_section);
1676 |     }
1677 | #line 1678 "src/parser.tab.c"
1678 |     break;
1679 | 
1680 |   case 14: /* field_list: field_list error ';'  */
1681 | #line 261 "src/parser.y"
1682 |     {
1683 |         yyerror("Invalid field declaration");
1684 |         yyclearin;
1685 |         yyerrok;
1686 |     }
1687 | #line 1688 "src/parser.tab.c"
1688 |     break;
1689 | 
1690 |   case 15: /* field: FIELD IDENTIFIER ':' field_type field_attributes ';'  */
1691 | #line 269 "src/parser.y"
1692 |     {
1693 |         if (current_section == NULL) {
1694 |             yyerror("Field must be inside a section");
1695 |             YYERROR;
1696 |         }
1697 |         if (check_duplicate_field((yyvsp[-4].str))) {
1698 |             yyerror("Duplicate field name found");
1699 |             YYERROR;
1700 |         }
1701 |         add_field_to_section(current_section, (yyvsp[-4].str), (yyvsp[-2].field_type), &(yyvsp[-1].field_attrs));
1702 |         free((yyvsp[-4].str)); // Free the field name
1703 |     }
1704 | #line 1705 "src/parser.tab.c"
1705 |     break;
1706 | 
1707 |   case 16: /* field_type: TEXT  */
1708 | #line 283 "src/parser.y"
1709 |                      { (yyval.field_type) = FIELD_TEXT; }
1710 | #line 1711 "src/parser.tab.c"
1711 |     break;
1712 | 
1713 |   case 17: /* field_type: EMAIL  */
1714 | #line 284 "src/parser.y"
1715 |                      { (yyval.field_type) = FIELD_EMAIL; }
1716 | #line 1717 "src/parser.tab.c"
1717 |     break;
1718 | 
1719 |   case 18: /* field_type: PASSWORD  */
1720 | #line 285 "src/parser.y"
1721 |                      { (yyval.field_type) = FIELD_PASSWORD; }
1722 | #line 1723 "src/parser.tab.c"
1723 |     break;
1724 | 
1725 |   case 19: /* field_type: NUMBER  */
1726 | #line 286 "src/parser.y"
1727 |                      { (yyval.field_type) = FIELD_NUMBER; }
1728 | #line 1729 "src/parser.tab.c"
1729 |     break;
1730 | 
1731 |   case 20: /* field_type: TEXTAREA  */
1732 | #line 287 "src/parser.y"
1733 |                      { (yyval.field_type) = FIELD_TEXTAREA; }
1734 | #line 1735 "src/parser.tab.c"
1735 |     break;
1736 | 
1737 |   case 21: /* field_type: DATE  */
1738 | #line 288 "src/parser.y"
1739 |                      { (yyval.field_type) = FIELD_DATE; }
1740 | #line 1741 "src/parser.tab.c"
1741 |     break;
1742 | 
1743 |   case 22: /* field_type: CHECKBOX  */
1744 | #line 289 "src/parser.y"
1745 |                      { (yyval.field_type) = FIELD_CHECKBOX; }
1746 | #line 1747 "src/parser.tab.c"
1747 |     break;
1748 | 
1749 |   case 23: /* field_type: DROPDOWN  */
1750 | #line 290 "src/parser.y"
1751 |                      { (yyval.field_type) = FIELD_DROPDOWN; }
1752 | #line 1753 "src/parser.tab.c"
1753 |     break;
1754 | 
1755 |   case 24: /* field_type: RADIO  */
1756 | #line 291 "src/parser.y"
1757 |                      { (yyval.field_type) = FIELD_RADIO; }
1758 | #line 1759 "src/parser.tab.c"
1759 |     break;
1760 | 
1761 |   case 25: /* field_type: FILE_TYPE  */
1762 | #line 292 "src/parser.y"
1763 |                       { (yyval.field_type) = FIELD_FILE; }
1764 | #line 1765 "src/parser.tab.c"
1765 |     break;
1766 | 
1767 |   case 26: /* field_type: USERNAME  */
1768 | #line 293 "src/parser.y"
1769 |                      { (yyval.field_type) = FIELD_USERNAME; }
1770 | #line 1771 "src/parser.tab.c"
1771 |     break;
1772 | 
1773 |   case 27: /* field_type: ADDRESS  */
1774 | #line 294 "src/parser.y"
1775 |                      { (yyval.field_type) = FIELD_ADDRESS; }
1776 | #line 1777 "src/parser.tab.c"
1777 |     break;
1778 | 
1779 |   case 28: /* field_attributes: %empty  */
1780 | #line 298 "src/parser.y"
1781 |     {
1782 |         init_field_attributes(&(yyval.field_attrs));
1783 |     }
1784 | #line 1785 "src/parser.tab.c"
1785 |     break;
1786 | 
1787 |   case 29: /* field_attributes: field_attributes attribute  */
1788 | #line 302 "src/parser.y"
1789 |     {
1790 |         // Merge attributes
1791 |         if ((yyvsp[0].field_attrs).required != -1) (yyval.field_attrs).required = (yyvsp[0].field_attrs).required;
1792 |         if ((yyvsp[0].field_attrs).min_length != -1) (yyval.field_attrs).min_length = (yyvsp[0].field_attrs).min_length;
1793 |         if ((yyvsp[0].field_attrs).max_length != -1) (yyval.field_attrs).max_length = (yyvsp[0].field_attrs).max_length;
1794 |         if ((yyvsp[0].field_attrs).min_value != -1) (yyval.field_attrs).min_value = (yyvsp[0].field_attrs).min_value;
1795 |         if ((yyvsp[0].field_attrs).max_value != -1) (yyval.field_attrs).max_value = (yyvsp[0].field_attrs).max_value;
1796 |         if ((yyvsp[0].field_attrs).rows != -1) (yyval.field_attrs).rows = (yyvsp[0].field_attrs).rows;
1797 |         if ((yyvsp[0].field_attrs).cols != -1) (yyval.field_attrs).cols = (yyvsp[0].field_attrs).cols;
1798 |         if ((yyvsp[0].field_attrs).pattern) {
1799 |             if ((yyval.field_attrs).pattern) free((yyval.field_attrs).pattern);
1800 |             (yyval.field_attrs).pattern = (yyvsp[0].field_attrs).pattern;
1801 |         }
1802 |         if ((yyvsp[0].field_attrs).default_value) {
1803 |             if ((yyval.field_attrs).default_value) free((yyval.field_attrs).default_value);
1804 |             (yyval.field_attrs).default_value = (yyvsp[0].field_attrs).default_value;
1805 |         }
1806 |     }
1807 | #line 1808 "src/parser.tab.c"
1808 |     break;
1809 | 
1810 |   case 30: /* attribute: REQUIRED  */
1811 | #line 323 "src/parser.y"
1812 |     {
1813 |         init_field_attributes(&(yyval.field_attrs));
1814 |         (yyval.field_attrs).required = 1;
1815 |     }
1816 | #line 1817 "src/parser.tab.c"
1817 |     break;
1818 | 
1819 |   case 31: /* attribute: OPTIONAL  */
1820 | #line 328 "src/parser.y"
1821 |     {
1822 |         init_field_attributes(&(yyval.field_attrs));
1823 |         (yyval.field_attrs).required = 0;
1824 |     }
1825 | #line 1826 "src/parser.tab.c"
1826 |     break;
1827 | 
1828 |   case 32: /* attribute: PATTERN STRING_LITERAL  */
1829 | #line 333 "src/parser.y"
1830 |     {
1831 |         init_field_attributes(&(yyval.field_attrs));
1832 |         (yyval.field_attrs).pattern = (yyvsp[0].str);
1833 |     }
1834 | #line 1835 "src/parser.tab.c"
1835 |     break;
1836 | 
1837 |   case 33: /* attribute: DEFAULT STRING_LITERAL  */
1838 | #line 338 "src/parser.y"
1839 |     {
1840 |         init_field_attributes(&(yyval.field_attrs));
1841 |         (yyval.field_attrs).default_value = (yyvsp[0].str);
1842 |     }
1843 | #line 1844 "src/parser.tab.c"
1844 |     break;
1845 | 
1846 |   case 34: /* attribute: DEFAULT NUMBER_LITERAL  */
1847 | #line 343 "src/parser.y"
1848 |     {
1849 |         init_field_attributes(&(yyval.field_attrs));
1850 |         char buf[32];
1851 |         sprintf(buf, "%d", (yyvsp[0].num));
1852 |         (yyval.field_attrs).default_value = strdup(buf);
1853 |     }
1854 | #line 1855 "src/parser.tab.c"
1855 |     break;
1856 | 
1857 |   case 35: /* attribute: MINLENGTH NUMBER_LITERAL  */
1858 | #line 350 "src/parser.y"
1859 |     {
1860 |         init_field_attributes(&(yyval.field_attrs));
1861 |         (yyval.field_attrs).min_length = (yyvsp[0].num);
1862 |     }
1863 | #line 1864 "src/parser.tab.c"
1864 |     break;
1865 | 
1866 |   case 36: /* attribute: MAXLENGTH NUMBER_LITERAL  */
1867 | #line 355 "src/parser.y"
1868 |     {
1869 |         init_field_attributes(&(yyval.field_attrs));
1870 |         (yyval.field_attrs).max_length = (yyvsp[0].num);
1871 |     }
1872 | #line 1873 "src/parser.tab.c"
1873 |     break;
1874 | 
1875 |   case 37: /* attribute: MIN NUMBER_LITERAL  */
1876 | #line 360 "src/parser.y"
1877 |     {
1878 |         init_field_attributes(&(yyval.field_attrs));
1879 |         (yyval.field_attrs).min_value = (yyvsp[0].num);
1880 |     }
1881 | #line 1882 "src/parser.tab.c"
1882 |     break;
1883 | 
1884 |   case 38: /* attribute: MAX NUMBER_LITERAL  */
1885 | #line 365 "src/parser.y"
1886 |     {
1887 |         init_field_attributes(&(yyval.field_attrs));
1888 |         (yyval.field_attrs).max_value = (yyvsp[0].num);
1889 |     }
1890 | #line 1891 "src/parser.tab.c"
1891 |     break;
1892 | 
1893 |   case 39: /* attribute: ROWS NUMBER_LITERAL  */
1894 | #line 370 "src/parser.y"
1895 |     {
1896 |         init_field_attributes(&(yyval.field_attrs));
1897 |         (yyval.field_attrs).rows = (yyvsp[0].num);
1898 |     }
1899 | #line 1900 "src/parser.tab.c"
1900 |     break;
1901 | 
1902 |   case 40: /* attribute: COLS NUMBER_LITERAL  */
1903 | #line 375 "src/parser.y"
1904 |     {
1905 |         init_field_attributes(&(yyval.field_attrs));
1906 |         (yyval.field_attrs).cols = (yyvsp[0].num);
1907 |     }
1908 | #line 1909 "src/parser.tab.c"
1909 |     break;
1910 | 
1911 |   case 41: /* attribute: CONFIRM IDENTIFIER  */
1912 | #line 380 "src/parser.y"
1913 |     {
1914 |         init_field_attributes(&(yyval.field_attrs));
1915 |         (yyval.field_attrs).confirm_field = (yyvsp[0].str);
1916 |     }
1917 | #line 1918 "src/parser.tab.c"
1918 |     break;
1919 | 
1920 |   case 42: /* attribute: STRENGTH NUMBER_LITERAL  */
1921 | #line 385 "src/parser.y"
1922 |     {
1923 |         init_field_attributes(&(yyval.field_attrs));
1924 |         (yyval.field_attrs).strength_required = (yyvsp[0].num);
1925 |     }
1926 | #line 1927 "src/parser.tab.c"
1927 |     break;
1928 | 
1929 |   case 46: /* validation_rule: IF condition '{' ERROR STRING_LITERAL ';' '}'  */
1930 | #line 403 "src/parser.y"
1931 |     {
1932 |         ValidationRule* rule = malloc(sizeof(ValidationRule));
1933 |         rule->condition = (yyvsp[-5].validation_rule);
1934 |         rule->error_message = (yyvsp[-2].str);
1935 |         rule->next = current_form->validation_rules;
1936 |         current_form->validation_rules = rule;
1937 |     }
1938 | #line 1939 "src/parser.tab.c"
1939 |     break;
1940 | 
1941 |   case 47: /* condition: IDENTIFIER LT NUMBER_LITERAL  */
1942 | #line 413 "src/parser.y"
1943 |     {
1944 |         char* cond = malloc(50);
1945 |         sprintf(cond, "%s < %d", (yyvsp[-2].str), (yyvsp[0].num));
1946 |         (yyval.validation_rule) = cond;
1947 |     }
1948 | #line 1949 "src/parser.tab.c"
1949 |     break;
1950 | 
1951 |   case 48: /* condition: IDENTIFIER GT NUMBER_LITERAL  */
1952 | #line 419 "src/parser.y"
1953 |     {
1954 |         char* cond = malloc(50);
1955 |         sprintf(cond, "%s > %d", (yyvsp[-2].str), (yyvsp[0].num));
1956 |         (yyval.validation_rule) = cond;
1957 |     }
1958 | #line 1959 "src/parser.tab.c"
1959 |     break;
1960 | 
1961 |   case 49: /* condition: IDENTIFIER LTE NUMBER_LITERAL  */
1962 | #line 425 "src/parser.y"
1963 |     {
1964 |         char* cond = malloc(50);
1965 |         sprintf(cond, "%s <= %d", (yyvsp[-2].str), (yyvsp[0].num));
1966 |         (yyval.validation_rule) = cond;
1967 |     }
1968 | #line 1969 "src/parser.tab.c"
1969 |     break;
1970 | 
1971 |   case 50: /* condition: IDENTIFIER GTE NUMBER_LITERAL  */
1972 | #line 431 "src/parser.y"
1973 |     {
1974 |         char* cond = malloc(50);
1975 |         sprintf(cond, "%s >= %d", (yyvsp[-2].str), (yyvsp[0].num));
1976 |         (yyval.validation_rule) = cond;
1977 |     }
1978 | #line 1979 "src/parser.tab.c"
1979 |     break;
1980 | 
1981 |   case 51: /* condition: IDENTIFIER EQ NUMBER_LITERAL  */
1982 | #line 437 "src/parser.y"
1983 |     {
1984 |         char* cond = malloc(50);
1985 |         sprintf(cond, "%s == %d", (yyvsp[-2].str), (yyvsp[0].num));
1986 |         (yyval.validation_rule) = cond;
1987 |     }
1988 | #line 1989 "src/parser.tab.c"
1989 |     break;
1990 | 
1991 |   case 52: /* condition: IDENTIFIER NEQ NUMBER_LITERAL  */
1992 | #line 443 "src/parser.y"
1993 |     {
1994 |         char* cond = malloc(50);
1995 |         sprintf(cond, "%s != %d", (yyvsp[-2].str), (yyvsp[0].num));
1996 |         (yyval.validation_rule) = cond;
1997 |     }
1998 | #line 1999 "src/parser.tab.c"
1999 |     break;
2000 | 
2001 | 
2002 | #line 2003 "src/parser.tab.c"
2003 | 
2004 |       default: break;
2005 |     }
2006 |   /* User semantic actions sometimes alter yychar, and that requires
2007 |      that yytoken be updated with the new translation.  We take the
2008 |      approach of translating immediately before every use of yytoken.
2009 |      One alternative is translating here after every semantic action,
2010 |      but that translation would be missed if the semantic action invokes
2011 |      YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
2012 |      if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
2013 |      incorrect destructor might then be invoked immediately.  In the
2014 |      case of YYERROR or YYBACKUP, subsequent parser actions might lead
2015 |      to an incorrect destructor call or verbose syntax error message
2016 |      before the lookahead is translated.  */
2017 |   YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);
2018 | 
2019 |   YYPOPSTACK (yylen);
2020 |   yylen = 0;
2021 | 
2022 |   *++yyvsp = yyval;
2023 | 
2024 |   /* Now 'shift' the result of the reduction.  Determine what state
2025 |      that goes to, based on the state we popped back to and the rule
2026 |      number reduced by.  */
2027 |   {
2028 |     const int yylhs = yyr1[yyn] - YYNTOKENS;
2029 |     const int yyi = yypgoto[yylhs] + *yyssp;
2030 |     yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
2031 |                ? yytable[yyi]
2032 |                : yydefgoto[yylhs]);
2033 |   }
2034 | 
2035 |   goto yynewstate;
2036 | 
2037 | 
2038 | /*--------------------------------------.
2039 | | yyerrlab -- here on detecting error.  |
2040 | `--------------------------------------*/
2041 | yyerrlab:
2042 |   /* Make sure we have latest lookahead translation.  See comments at
2043 |      user semantic actions for why this is necessary.  */
2044 |   yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
2045 |   /* If not already recovering from an error, report this error.  */
2046 |   if (!yyerrstatus)
2047 |     {
2048 |       ++yynerrs;
2049 |       {
2050 |         yypcontext_t yyctx
2051 |           = {yyssp, yytoken};
2052 |         char const *yymsgp = YY_("syntax error");
2053 |         int yysyntax_error_status;
2054 |         yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
2055 |         if (yysyntax_error_status == 0)
2056 |           yymsgp = yymsg;
2057 |         else if (yysyntax_error_status == -1)
2058 |           {
2059 |             if (yymsg != yymsgbuf)
2060 |               YYSTACK_FREE (yymsg);
2061 |             yymsg = YY_CAST (char *,
2062 |                              YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
2063 |             if (yymsg)
2064 |               {
2065 |                 yysyntax_error_status
2066 |                   = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
2067 |                 yymsgp = yymsg;
2068 |               }
2069 |             else
2070 |               {
2071 |                 yymsg = yymsgbuf;
2072 |                 yymsg_alloc = sizeof yymsgbuf;
2073 |                 yysyntax_error_status = YYENOMEM;
2074 |               }
2075 |           }
2076 |         yyerror (yymsgp);
2077 |         if (yysyntax_error_status == YYENOMEM)
2078 |           YYNOMEM;
2079 |       }
2080 |     }
2081 | 
2082 |   if (yyerrstatus == 3)
2083 |     {
2084 |       /* If just tried and failed to reuse lookahead token after an
2085 |          error, discard it.  */
2086 | 
2087 |       if (yychar <= YYEOF)
2088 |         {
2089 |           /* Return failure if at end of input.  */
2090 |           if (yychar == YYEOF)
2091 |             YYABORT;
2092 |         }
2093 |       else
2094 |         {
2095 |           yydestruct ("Error: discarding",
2096 |                       yytoken, &yylval);
2097 |           yychar = YYEMPTY;
2098 |         }
2099 |     }
2100 | 
2101 |   /* Else will try to reuse lookahead token after shifting the error
2102 |      token.  */
2103 |   goto yyerrlab1;
2104 | 
2105 | 
2106 | /*---------------------------------------------------.
2107 | | yyerrorlab -- error raised explicitly by YYERROR.  |
2108 | `---------------------------------------------------*/
2109 | yyerrorlab:
2110 |   /* Pacify compilers when the user code never invokes YYERROR and the
2111 |      label yyerrorlab therefore never appears in user code.  */
2112 |   if (0)
2113 |     YYERROR;
2114 |   ++yynerrs;
2115 | 
2116 |   /* Do not reclaim the symbols of the rule whose action triggered
2117 |      this YYERROR.  */
2118 |   YYPOPSTACK (yylen);
2119 |   yylen = 0;
2120 |   YY_STACK_PRINT (yyss, yyssp);
2121 |   yystate = *yyssp;
2122 |   goto yyerrlab1;
2123 | 
2124 | 
2125 | /*-------------------------------------------------------------.
2126 | | yyerrlab1 -- common code for both syntax error and YYERROR.  |
2127 | `-------------------------------------------------------------*/
2128 | yyerrlab1:
2129 |   yyerrstatus = 3;      /* Each real token shifted decrements this.  */
2130 | 
2131 |   /* Pop stack until we find a state that shifts the error token.  */
2132 |   for (;;)
2133 |     {
2134 |       yyn = yypact[yystate];
2135 |       if (!yypact_value_is_default (yyn))
2136 |         {
2137 |           yyn += YYSYMBOL_YYerror;
2138 |           if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
2139 |             {
2140 |               yyn = yytable[yyn];
2141 |               if (0 < yyn)
2142 |                 break;
2143 |             }
2144 |         }
2145 | 
2146 |       /* Pop the current state because it cannot handle the error token.  */
2147 |       if (yyssp == yyss)
2148 |         YYABORT;
2149 | 
2150 | 
2151 |       yydestruct ("Error: popping",
2152 |                   YY_ACCESSING_SYMBOL (yystate), yyvsp);
2153 |       YYPOPSTACK (1);
2154 |       yystate = *yyssp;
2155 |       YY_STACK_PRINT (yyss, yyssp);
2156 |     }
2157 | 
2158 |   YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
2159 |   *++yyvsp = yylval;
2160 |   YY_IGNORE_MAYBE_UNINITIALIZED_END
2161 | 
2162 | 
2163 |   /* Shift the error token.  */
2164 |   YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);
2165 | 
2166 |   yystate = yyn;
2167 |   goto yynewstate;
2168 | 
2169 | 
2170 | /*-------------------------------------.
2171 | | yyacceptlab -- YYACCEPT comes here.  |
2172 | `-------------------------------------*/
2173 | yyacceptlab:
2174 |   yyresult = 0;
2175 |   goto yyreturnlab;
2176 | 
2177 | 
2178 | /*-----------------------------------.
2179 | | yyabortlab -- YYABORT comes here.  |
2180 | `-----------------------------------*/
2181 | yyabortlab:
2182 |   yyresult = 1;
2183 |   goto yyreturnlab;
2184 | 
2185 | 
2186 | /*-----------------------------------------------------------.
2187 | | yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
2188 | `-----------------------------------------------------------*/
2189 | yyexhaustedlab:
2190 |   yyerror (YY_("memory exhausted"));
2191 |   yyresult = 2;
2192 |   goto yyreturnlab;
2193 | 
2194 | 
2195 | /*----------------------------------------------------------.
2196 | | yyreturnlab -- parsing is finished, clean up and return.  |
2197 | `----------------------------------------------------------*/
2198 | yyreturnlab:
2199 |   if (yychar != YYEMPTY)
2200 |     {
2201 |       /* Make sure we have latest lookahead translation.  See comments at
2202 |          user semantic actions for why this is necessary.  */
2203 |       yytoken = YYTRANSLATE (yychar);
2204 |       yydestruct ("Cleanup: discarding lookahead",
2205 |                   yytoken, &yylval);
2206 |     }
2207 |   /* Do not reclaim the symbols of the rule whose action triggered
2208 |      this YYABORT or YYACCEPT.  */
2209 |   YYPOPSTACK (yylen);
2210 |   YY_STACK_PRINT (yyss, yyssp);
2211 |   while (yyssp != yyss)
2212 |     {
2213 |       yydestruct ("Cleanup: popping",
2214 |                   YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
2215 |       YYPOPSTACK (1);
2216 |     }
2217 | #ifndef yyoverflow
2218 |   if (yyss != yyssa)
2219 |     YYSTACK_FREE (yyss);
2220 | #endif
2221 |   if (yymsg != yymsgbuf)
2222 |     YYSTACK_FREE (yymsg);
2223 |   return yyresult;
2224 | }
2225 | 
2226 | #line 450 "src/parser.y"
2227 | 
2228 | 
2229 | void yyerror(const char *s) {
2230 |     fprintf(stderr, "Parser Error: %s at line %d\n", s, yylineno);
2231 | }
2232 | 
2233 | int main(int argc, char **argv) {
2234 |     if (argc > 1) {
2235 |         FILE *file = fopen(argv[1], "r");
2236 |         if (!file) {
2237 |             perror(argv[1]);
2238 |             return 1;
2239 |         }
2240 |         yyin = file;
2241 |     }
2242 |     yyparse();
2243 |     cleanup_form(current_form);
2244 |     return 0;
2245 | }
2246 | 
2247 | int yywrap() {
2248 |     return 1;
2249 | }
```

src/parser.tab.h
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
70 |     USERNAME = 271,                /* USERNAME  */
71 |     ADDRESS = 272,                 /* ADDRESS  */
72 |     REQUIRED = 273,                /* REQUIRED  */
73 |     OPTIONAL = 274,                /* OPTIONAL  */
74 |     MINLENGTH = 275,               /* MINLENGTH  */
75 |     MAXLENGTH = 276,               /* MAXLENGTH  */
76 |     MIN = 277,                     /* MIN  */
77 |     MAX = 278,                     /* MAX  */
78 |     ROWS = 279,                    /* ROWS  */
79 |     COLS = 280,                    /* COLS  */
80 |     PATTERN = 281,                 /* PATTERN  */
81 |     DEFAULT = 282,                 /* DEFAULT  */
82 |     CONFIRM = 283,                 /* CONFIRM  */
83 |     STRENGTH = 284,                /* STRENGTH  */
84 |     IDENTIFIER = 285,              /* IDENTIFIER  */
85 |     NUMBER_LITERAL = 286,          /* NUMBER_LITERAL  */
86 |     STRING_LITERAL = 287,          /* STRING_LITERAL  */
87 |     VALIDATE = 288,                /* VALIDATE  */
88 |     IF = 289,                      /* IF  */
89 |     ERROR = 290,                   /* ERROR  */
90 |     LT = 291,                      /* LT  */
91 |     GT = 292,                      /* GT  */
92 |     LTE = 293,                     /* LTE  */
93 |     GTE = 294,                     /* GTE  */
94 |     EQ = 295,                      /* EQ  */
95 |     NEQ = 296,                     /* NEQ  */
96 |     AND = 297,                     /* AND  */
97 |     OR = 298                       /* OR  */
98 |   };
99 |   typedef enum yytokentype yytoken_kind_t;
100 | #endif
101 | 
102 | /* Value type.  */
103 | #if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
104 | union YYSTYPE
105 | {
106 | #line 177 "src/parser.y"
107 | 
108 |     char* str;
109 |     int num;
110 |     Form* form;
111 |     Section* section;
112 |     FieldType field_type;
113 |     FieldAttributes field_attrs;
114 |     ValidationRule* validation_rule;
115 | 
116 | #line 117 "src/parser.tab.h"
117 | 
118 | };
119 | typedef union YYSTYPE YYSTYPE;
120 | # define YYSTYPE_IS_TRIVIAL 1
121 | # define YYSTYPE_IS_DECLARED 1
122 | #endif
123 | 
124 | 
125 | extern YYSTYPE yylval;
126 | 
127 | 
128 | int yyparse (void);
129 | 
130 | 
131 | #endif /* !YY_YY_SRC_PARSER_TAB_H_INCLUDED  */
```

src/parser.y
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
31 |     form->validation_rules = NULL;
32 |     return form;
33 | }
34 | 
35 | Section* create_section(const char* name) {
36 |     Section* section = malloc(sizeof(Section));
37 |     if (!section) return NULL;
38 |     section->name = strdup(name);
39 |     section->fields = NULL;
40 |     section->field_count = 0;
41 |     return section;
42 | }
43 | 
44 | void add_section_to_form(Form* form, Section* section) {
45 |     if (!form || !section) {
46 |         fprintf(stderr, "Null form or section\n");
47 |         return;
48 |     }
49 |     
50 |     Section** new_sections = realloc(form->sections, (form->section_count + 1) * sizeof(Section*));
51 |     if (!new_sections) {
52 |         fprintf(stderr, "Memory allocation failed for sections\n");
53 |         exit(1);
54 |     }
55 |     form->sections = new_sections;
56 |     form->sections[form->section_count] = section;
57 |     form->section_count++;
58 | }
59 | 
60 | int check_duplicate_field(const char* name) {
61 |     for (int i = 0; i < field_name_count; i++) {
62 |         if (strcmp(field_names[i].name, name) == 0) {
63 |             return 1;
64 |         }
65 |     }
66 |     return 0;
67 | }
68 | 
69 | void init_field_attributes(FieldAttributes* attrs) {
70 |     if (!attrs) return;
71 |     attrs->min_length = -1;
72 |     attrs->max_length = -1;
73 |     attrs->min_value = -1;
74 |     attrs->max_value = -1;
75 |     attrs->rows = -1;
76 |     attrs->cols = -1;
77 |     attrs->pattern = NULL;
78 |     attrs->default_value = NULL;
79 |     attrs->required = 0;
80 | }
81 | 
82 | void add_field_to_section(Section* section, const char* name, FieldType type, FieldAttributes* attrs) {
83 |     if (!section || !name || !attrs) {
84 |         fprintf(stderr, "Null section, name, or attrs\n");
85 |         return;
86 |     }
87 |     
88 |     // Add field name to tracking
89 |     field_name_count++;
90 |     FieldName* new_field_names = realloc(field_names, field_name_count * sizeof(FieldName));
91 |     if (!new_field_names) {
92 |         fprintf(stderr, "Memory allocation failed for field names\n");
93 |         exit(1);
94 |     }
95 |     field_names = new_field_names;
96 |     field_names[field_name_count - 1].name = strdup(name);
97 |     field_names[field_name_count - 1].line = yylineno;
98 |     
99 |     // Allocate memory for the new field
100 |     Field* new_fields = realloc(section->fields, (section->field_count + 1) * sizeof(Field));
101 |     if (!new_fields) {
102 |         fprintf(stderr, "Memory allocation failed for fields\n");
103 |         exit(1);
104 |     }
105 |     section->fields = new_fields;
106 |     
107 |     Field* field = &section->fields[section->field_count];
108 |     field->name = strdup(name);
109 |     field->type = type;
110 |     init_field_attributes(&field->attributes);
111 |     
112 |     // Copy attributes
113 |     field->attributes.min_length = attrs->min_length;
114 |     field->attributes.max_length = attrs->max_length;
115 |     field->attributes.min_value = attrs->min_value;
116 |     field->attributes.max_value = attrs->max_value;
117 |     field->attributes.rows = attrs->rows;
118 |     field->attributes.cols = attrs->cols;
119 |     field->attributes.required = attrs->required;
120 |     
121 |     if (attrs->pattern) {
122 |         field->attributes.pattern = strdup(attrs->pattern);
123 |     }
124 |     if (attrs->default_value) {
125 |         field->attributes.default_value = strdup(attrs->default_value);
126 |     }
127 |     
128 |     section->field_count++;
129 | }
130 | 
131 | void add_metadata(Form* form, const char* key, const char* value) {
132 |     Metadata* meta = malloc(sizeof(Metadata));
133 |     if (!meta) {
134 |         fprintf(stderr, "Memory allocation failed for metadata\n");
135 |         return;
136 |     }
137 |     meta->key = strdup(key);
138 |     meta->value = strdup(value);
139 |     meta->next = form->metadata;
140 |     form->metadata = meta;
141 | }
142 | 
143 | void cleanup_metadata(Metadata* metadata) {
144 |     while (metadata) {
145 |         Metadata* next = metadata->next;
146 |         if (metadata->key) free(metadata->key);
147 |         if (metadata->value) free(metadata->value);
148 |         free(metadata);
149 |         metadata = next;
150 |     }
151 | }
152 | 
153 | void cleanup_form(Form* form) {
154 |     if (form) {
155 |         for (int i = 0; i < form->section_count; i++) {
156 |             Section* s = form->sections[i];
157 |             if (s) {
158 |                 for (int j = 0; j < s->field_count; j++) {
159 |                     Field* f = &s->fields[j];
160 |                     if (f->name) free(f->name);
161 |                     if (f->attributes.pattern) free(f->attributes.pattern);
162 |                     if (f->attributes.default_value) free(f->attributes.default_value);
163 |                 }
164 |                 if (s->fields) free(s->fields);
165 |                 if (s->name) free(s->name);
166 |                 free(s);
167 |             }
168 |         }
169 |         if (form->sections) free(form->sections);
170 |         if (form->name) free(form->name);
171 |         
172 |         // Cleanup validation rules
173 |         ValidationRule* rule = form->validation_rules;
174 |         while (rule) {
175 |             ValidationRule* next = rule->next;
176 |             if (rule->condition) free(rule->condition);
177 |             if (rule->error_message) free(rule->error_message);
178 |             free(rule);
179 |             rule = next;
180 |         }
181 |         
182 |         // Cleanup metadata
183 |         cleanup_metadata(form->metadata);
184 |         
185 |         free(form);
186 |     }
187 |     
188 |     // Cleanup field name tracking
189 |     for (int i = 0; i < field_name_count; i++) {
190 |         if (field_names[i].name) free(field_names[i].name);
191 |     }
192 |     if (field_names) free(field_names);
193 |     field_name_count = 0;
194 | }
195 | 
196 | void merge_field_attributes(FieldAttributes* dest, FieldAttributes* src) {
197 |     if (src->required != -1) dest->required = src->required;
198 |     if (src->min_length != -1) dest->min_length = src->min_length;
199 |     if (src->max_length != -1) dest->max_length = src->max_length;
200 |     if (src->min_value != -1) dest->min_value = src->min_value;
201 |     if (src->max_value != -1) dest->max_value = src->max_value;
202 |     if (src->rows != -1) dest->rows = src->rows;
203 |     if (src->cols != -1) dest->cols = src->cols;
204 |     if (src->pattern) { if (dest->pattern) free(dest->pattern); dest->pattern = strdup(src->pattern); }
205 |     if (src->default_value) { if (dest->default_value) free(dest->default_value); dest->default_value = strdup(src->default_value); }
206 | }
207 | %}
208 | 
209 | %token FORM SECTION FIELD TEXT EMAIL PASSWORD NUMBER TEXTAREA DATE CHECKBOX DROPDOWN RADIO FILE_TYPE USERNAME ADDRESS
210 | %token REQUIRED OPTIONAL MINLENGTH MAXLENGTH MIN MAX ROWS COLS PATTERN DEFAULT CONFIRM STRENGTH META
211 | %token IDENTIFIER NUMBER_LITERAL STRING_LITERAL
212 | %token VALIDATE IF ERROR LT GT LTE GTE EQ NEQ AND OR
213 | %token <str> OPTIONS
214 | 
215 | %union {
216 |     Form* form;
217 |     Section* section;
218 |     Field* field;
219 |     FieldAttributes field_attrs;
220 |     ValidationRule* validation_rule;
221 |     char* str;
222 |     int num;
223 |     FieldType field_type;
224 |     struct {
225 |         char** arr;
226 |         int count;
227 |     } str_list;
228 | }
229 | 
230 | %type <str> IDENTIFIER STRING_LITERAL
231 | %type <num> NUMBER_LITERAL
232 | %type <form> form
233 | %type <field_type> field_type
234 | %type <field_attrs> field_attributes attribute attribute_opt_semicolon
235 | %type <validation_rule> validation_block validation_rule condition
236 | %type <str_list> options_list
237 | 
238 | %define parse.error verbose
239 | 
240 | %%
241 | 
242 | form: FORM IDENTIFIER '{' form_body '}'
243 |     {
244 |         current_form = create_form($2);
245 |         if (!current_form) {
246 |             yyerror("Failed to create form");
247 |             YYERROR;
248 |         }
249 |         generate_html(stdout);
250 |         $$ = current_form;
251 |     }
252 |     ;
253 | 
254 | form_body:
255 |     | form_body form_item
256 |     ;
257 | 
258 | form_item:
259 |       section
260 |     | validation_block
261 |     | metadata_declaration
262 |     ;
263 | 
264 | section_list: 
265 |     | section_list section
266 |     ;
267 | 
268 | section: SECTION IDENTIFIER '{' { current_section = create_section($2); } field_list '}' { add_section_to_form(current_form, current_section); current_section = NULL; }
269 |     | SECTION IDENTIFIER '{' '}'
270 |     {
271 |         current_section = NULL;
272 |     }
273 |     | SECTION IDENTIFIER error '}'
274 |     {
275 |         yyerror("Invalid section declaration");
276 |         current_section = NULL;
277 |         yyclearin;
278 |         yyerrok;
279 |     }
280 |     ;
281 | 
282 | section_header: SECTION IDENTIFIER
283 |     {
284 |         if (current_section != NULL) {
285 |             yyerror("Nested sections are not allowed");
286 |             YYERROR;
287 |         }
288 |         current_section = create_section($2);
289 |         if (!current_section) {
290 |             yyerror("Failed to create section");
291 |             YYERROR;
292 |         }
293 |         add_section_to_form(current_form, current_section);
294 |     }
295 |     ;
296 | 
297 | field_list:
298 |     | field_list field_declaration
299 |     | field_list error ';'
300 |     {
301 |         yyerror("Invalid field declaration");
302 |         yyclearin;
303 |         yyerrok;
304 |     }
305 |     ;
306 | 
307 | field_declaration: FIELD IDENTIFIER ':' field_type '{' field_attributes '}'
308 |     {
309 |         if (current_section == NULL) {
310 |             yyerror("Field must be inside a section");
311 |             YYERROR;
312 |         }
313 |         if (check_duplicate_field($2)) {
314 |             yyerror("Duplicate field name found");
315 |             YYERROR;
316 |         }
317 |         add_field_to_section(current_section, $2, $4, &$6);
318 |         free($2); // Free the field name
319 |     }
320 |     ;
321 | 
322 | field_type: TEXT     { $$ = FIELD_TEXT; }
323 |           | EMAIL    { $$ = FIELD_EMAIL; }
324 |           | PASSWORD { $$ = FIELD_PASSWORD; }
325 |           | NUMBER   { $$ = FIELD_NUMBER; }
326 |           | TEXTAREA { $$ = FIELD_TEXTAREA; }
327 |           | DATE     { $$ = FIELD_DATE; }
328 |           | CHECKBOX { $$ = FIELD_CHECKBOX; }
329 |           | DROPDOWN { $$ = FIELD_DROPDOWN; }
330 |           | RADIO    { $$ = FIELD_RADIO; }
331 |           | FILE_TYPE { $$ = FIELD_FILE; }
332 |           | USERNAME { $$ = FIELD_USERNAME; }
333 |           | ADDRESS  { $$ = FIELD_ADDRESS; }
334 |           ;
335 | 
336 | field_attributes:
337 |       /* empty */ { init_field_attributes(&$$); }
338 |     | field_attributes attribute_opt_semicolon { $$ = $1; merge_field_attributes(&$$, &$2); }
339 |     ;
340 | 
341 | attribute_opt_semicolon:
342 |       attribute ';' { $$ = $1; }
343 |     | attribute     { $$ = $1; }
344 |     ;
345 | 
346 | attribute:
347 |       REQUIRED    { FieldAttributes tmp; init_field_attributes(&tmp); tmp.required = 1; $$ = tmp; }
348 |     | OPTIONAL    { FieldAttributes tmp; init_field_attributes(&tmp); tmp.required = 0; $$ = tmp; }
349 |     | MINLENGTH '=' NUMBER_LITERAL { FieldAttributes tmp; init_field_attributes(&tmp); tmp.min_length = $3; $$ = tmp; }
350 |     | MAXLENGTH '=' NUMBER_LITERAL { FieldAttributes tmp; init_field_attributes(&tmp); tmp.max_length = $3; $$ = tmp; }
351 |     | MIN '=' NUMBER_LITERAL { FieldAttributes tmp; init_field_attributes(&tmp); tmp.min_value = $3; $$ = tmp; }
352 |     | MAX '=' NUMBER_LITERAL { FieldAttributes tmp; init_field_attributes(&tmp); tmp.max_value = $3; $$ = tmp; }
353 |     | ROWS '=' NUMBER_LITERAL { FieldAttributes tmp; init_field_attributes(&tmp); tmp.rows = $3; $$ = tmp; }
354 |     | COLS '=' NUMBER_LITERAL { FieldAttributes tmp; init_field_attributes(&tmp); tmp.cols = $3; $$ = tmp; }
355 |     | PATTERN '=' STRING_LITERAL { FieldAttributes tmp; init_field_attributes(&tmp); tmp.pattern = $3; $$ = tmp; }
356 |     | DEFAULT '=' STRING_LITERAL { FieldAttributes tmp; init_field_attributes(&tmp); tmp.default_value = $3; $$ = tmp; }
357 |     | DEFAULT '=' IDENTIFIER { FieldAttributes tmp; init_field_attributes(&tmp); tmp.default_value = strdup($3); $$ = tmp; }
358 |     | STRENGTH '=' NUMBER_LITERAL { FieldAttributes tmp; init_field_attributes(&tmp); tmp.strength_required = $3; $$ = tmp; }
359 |     | CONFIRM '=' IDENTIFIER { FieldAttributes tmp; init_field_attributes(&tmp); tmp.confirm_field = $3; $$ = tmp; }
360 |     | OPTIONS '=' '[' options_list ']' {
361 |         FieldAttributes tmp;
362 |         init_field_attributes(&tmp);
363 |         tmp.options = $4.arr;
364 |         tmp.options_count = $4.count;
365 |         $$ = tmp;
366 |     }
367 |     ;
368 | 
369 | validation_blocks:
370 |     | validation_blocks validation_block
371 |     ;
372 | 
373 | validation_block: VALIDATE '{' validation_rules '}'
374 |     {
375 |         // Validation block is already processed by the rules
376 |     }
377 |     ;
378 | 
379 | validation_rules:
380 |     | validation_rules validation_rule
381 |     ;
382 | 
383 | validation_rule: IF condition '{' ERROR STRING_LITERAL ';' '}'
384 |     {
385 |         ValidationRule* rule = malloc(sizeof(ValidationRule));
386 |         if (!rule) {
387 |             yyerror("Memory allocation failed for validation rule");
388 |             YYERROR;
389 |         }
390 |         rule->condition = $2;
391 |         rule->error_message = $5;
392 |         rule->next = current_form->validation_rules;
393 |         current_form->validation_rules = rule;
394 |     }
395 |     ;
396 | 
397 | condition: IDENTIFIER LT NUMBER_LITERAL
398 |     {
399 |         char* cond = malloc(50);
400 |         sprintf(cond, "%s < %d", $1, $3);
401 |         $$ = cond;
402 |     }
403 |     | IDENTIFIER GT NUMBER_LITERAL
404 |     {
405 |         char* cond = malloc(50);
406 |         sprintf(cond, "%s > %d", $1, $3);
407 |         $$ = cond;
408 |     }
409 |     | IDENTIFIER LTE NUMBER_LITERAL
410 |     {
411 |         char* cond = malloc(50);
412 |         sprintf(cond, "%s <= %d", $1, $3);
413 |         $$ = cond;
414 |     }
415 |     | IDENTIFIER GTE NUMBER_LITERAL
416 |     {
417 |         char* cond = malloc(50);
418 |         sprintf(cond, "%s >= %d", $1, $3);
419 |         $$ = cond;
420 |     }
421 |     | IDENTIFIER EQ NUMBER_LITERAL
422 |     {
423 |         char* cond = malloc(50);
424 |         sprintf(cond, "%s == %d", $1, $3);
425 |         $$ = cond;
426 |     }
427 |     | IDENTIFIER NEQ NUMBER_LITERAL
428 |     {
429 |         char* cond = malloc(50);
430 |         sprintf(cond, "%s != %d", $1, $3);
431 |         $$ = cond;
432 |     }
433 |     | IDENTIFIER EQ IDENTIFIER
434 |     {
435 |         char* cond = malloc(50);
436 |         sprintf(cond, "%s == %s", $1, $3);
437 |         $$ = cond;
438 |     }
439 |     ;
440 | 
441 | metadata_declaration: META IDENTIFIER '=' STRING_LITERAL ';'
442 |     {
443 |         if (current_form) {
444 |             add_metadata(current_form, $2, $4);
445 |         }
446 |     }
447 |     ;
448 | 
449 | options_list:
450 |       STRING_LITERAL { $$.arr = malloc(sizeof(char*)); $$.arr[0] = strdup($1); $$.count = 1; }
451 |     | options_list ',' STRING_LITERAL {
452 |         $$.arr = realloc($1.arr, ($1.count + 1) * sizeof(char*));
453 |         $$.arr[$1.count] = strdup($3);
454 |         $$.count = $1.count + 1;
455 |     }
456 |     ;
457 | 
458 | %%
459 | 
460 | void yyerror(const char *s) {
461 |     fprintf(stderr, "Parser Error: %s at line %d\n", s, yylineno);
462 | }
463 | 
464 | int main(int argc, char **argv) {
465 |     if (argc > 1) {
466 |         FILE *file = fopen(argv[1], "r");
467 |         if (!file) {
468 |             perror(argv[1]);
469 |             return 1;
470 |         }
471 |         yyin = file;
472 |     }
473 |     yyparse();
474 |     cleanup_form(current_form);
475 |     return 0;
476 | }
477 | 
478 | int yywrap() {
479 |     return 1;
480 | }
```

src/y.tab.c
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
101 |     form->validation_rules = NULL;
102 |     return form;
103 | }
104 | 
105 | Section* create_section(const char* name) {
106 |     Section* section = malloc(sizeof(Section));
107 |     if (!section) return NULL;
108 |     section->name = strdup(name);
109 |     section->fields = NULL;
110 |     section->field_count = 0;
111 |     return section;
112 | }
113 | 
114 | void add_section_to_form(Form* form, Section* section) {
115 |     if (!form || !section) {
116 |         fprintf(stderr, "Null form or section\n");
117 |         return;
118 |     }
119 |     
120 |     Section** new_sections = realloc(form->sections, (form->section_count + 1) * sizeof(Section*));
121 |     if (!new_sections) {
122 |         fprintf(stderr, "Memory allocation failed for sections\n");
123 |         exit(1);
124 |     }
125 |     form->sections = new_sections;
126 |     form->sections[form->section_count] = section;
127 |     form->section_count++;
128 | }
129 | 
130 | int check_duplicate_field(const char* name) {
131 |     for (int i = 0; i < field_name_count; i++) {
132 |         if (strcmp(field_names[i].name, name) == 0) {
133 |             return 1;
134 |         }
135 |     }
136 |     return 0;
137 | }
138 | 
139 | void init_field_attributes(FieldAttributes* attrs) {
140 |     if (!attrs) return;
141 |     attrs->min_length = -1;
142 |     attrs->max_length = -1;
143 |     attrs->min_value = -1;
144 |     attrs->max_value = -1;
145 |     attrs->rows = -1;
146 |     attrs->cols = -1;
147 |     attrs->pattern = NULL;
148 |     attrs->default_value = NULL;
149 |     attrs->required = 0;
150 | }
151 | 
152 | void add_field_to_section(Section* section, const char* name, FieldType type, FieldAttributes* attrs) {
153 |     if (!section || !name || !attrs) {
154 |         fprintf(stderr, "Null section, name, or attrs\n");
155 |         return;
156 |     }
157 |     
158 |     // Add field name to tracking
159 |     field_name_count++;
160 |     FieldName* new_field_names = realloc(field_names, field_name_count * sizeof(FieldName));
161 |     if (!new_field_names) {
162 |         fprintf(stderr, "Memory allocation failed for field names\n");
163 |         exit(1);
164 |     }
165 |     field_names = new_field_names;
166 |     field_names[field_name_count - 1].name = strdup(name);
167 |     field_names[field_name_count - 1].line = yylineno;
168 |     
169 |     // Allocate memory for the new field
170 |     Field* new_fields = realloc(section->fields, (section->field_count + 1) * sizeof(Field));
171 |     if (!new_fields) {
172 |         fprintf(stderr, "Memory allocation failed for fields\n");
173 |         exit(1);
174 |     }
175 |     section->fields = new_fields;
176 |     
177 |     Field* field = &section->fields[section->field_count];
178 |     field->name = strdup(name);
179 |     field->type = type;
180 |     init_field_attributes(&field->attributes);
181 |     
182 |     // Copy attributes
183 |     field->attributes.min_length = attrs->min_length;
184 |     field->attributes.max_length = attrs->max_length;
185 |     field->attributes.min_value = attrs->min_value;
186 |     field->attributes.max_value = attrs->max_value;
187 |     field->attributes.rows = attrs->rows;
188 |     field->attributes.cols = attrs->cols;
189 |     field->attributes.required = attrs->required;
190 |     
191 |     if (attrs->pattern) {
192 |         field->attributes.pattern = strdup(attrs->pattern);
193 |     }
194 |     if (attrs->default_value) {
195 |         field->attributes.default_value = strdup(attrs->default_value);
196 |     }
197 |     
198 |     section->field_count++;
199 | }
200 | 
201 | void add_metadata(Form* form, const char* key, const char* value) {
202 |     Metadata* meta = malloc(sizeof(Metadata));
203 |     if (!meta) {
204 |         fprintf(stderr, "Memory allocation failed for metadata\n");
205 |         return;
206 |     }
207 |     meta->key = strdup(key);
208 |     meta->value = strdup(value);
209 |     meta->next = form->metadata;
210 |     form->metadata = meta;
211 | }
212 | 
213 | void cleanup_metadata(Metadata* metadata) {
214 |     while (metadata) {
215 |         Metadata* next = metadata->next;
216 |         if (metadata->key) free(metadata->key);
217 |         if (metadata->value) free(metadata->value);
218 |         free(metadata);
219 |         metadata = next;
220 |     }
221 | }
222 | 
223 | void cleanup_form(Form* form) {
224 |     if (form) {
225 |         for (int i = 0; i < form->section_count; i++) {
226 |             Section* s = form->sections[i];
227 |             if (s) {
228 |                 for (int j = 0; j < s->field_count; j++) {
229 |                     Field* f = &s->fields[j];
230 |                     if (f->name) free(f->name);
231 |                     if (f->attributes.pattern) free(f->attributes.pattern);
232 |                     if (f->attributes.default_value) free(f->attributes.default_value);
233 |                 }
234 |                 if (s->fields) free(s->fields);
235 |                 if (s->name) free(s->name);
236 |                 free(s);
237 |             }
238 |         }
239 |         if (form->sections) free(form->sections);
240 |         if (form->name) free(form->name);
241 |         
242 |         // Cleanup validation rules
243 |         ValidationRule* rule = form->validation_rules;
244 |         while (rule) {
245 |             ValidationRule* next = rule->next;
246 |             if (rule->condition) free(rule->condition);
247 |             if (rule->error_message) free(rule->error_message);
248 |             free(rule);
249 |             rule = next;
250 |         }
251 |         
252 |         // Cleanup metadata
253 |         cleanup_metadata(form->metadata);
254 |         
255 |         free(form);
256 |     }
257 |     
258 |     // Cleanup field name tracking
259 |     for (int i = 0; i < field_name_count; i++) {
260 |         if (field_names[i].name) free(field_names[i].name);
261 |     }
262 |     if (field_names) free(field_names);
263 |     field_name_count = 0;
264 | }
265 | 
266 | void merge_field_attributes(FieldAttributes* dest, FieldAttributes* src) {
267 |     if (src->required != -1) dest->required = src->required;
268 |     if (src->min_length != -1) dest->min_length = src->min_length;
269 |     if (src->max_length != -1) dest->max_length = src->max_length;
270 |     if (src->min_value != -1) dest->min_value = src->min_value;
271 |     if (src->max_value != -1) dest->max_value = src->max_value;
272 |     if (src->rows != -1) dest->rows = src->rows;
273 |     if (src->cols != -1) dest->cols = src->cols;
274 |     if (src->pattern) { if (dest->pattern) free(dest->pattern); dest->pattern = strdup(src->pattern); }
275 |     if (src->default_value) { if (dest->default_value) free(dest->default_value); dest->default_value = strdup(src->default_value); }
276 | }
277 | 
278 | #line 279 "y.tab.c"
279 | 
280 | # ifndef YY_CAST
281 | #  ifdef __cplusplus
282 | #   define YY_CAST(Type, Val) static_cast<Type> (Val)
283 | #   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
284 | #  else
285 | #   define YY_CAST(Type, Val) ((Type) (Val))
286 | #   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
287 | #  endif
288 | # endif
289 | # ifndef YY_NULLPTR
290 | #  if defined __cplusplus
291 | #   if 201103L <= __cplusplus
292 | #    define YY_NULLPTR nullptr
293 | #   else
294 | #    define YY_NULLPTR 0
295 | #   endif
296 | #  else
297 | #   define YY_NULLPTR ((void*)0)
298 | #  endif
299 | # endif
300 | 
301 | /* Use api.header.include to #include this header
302 |    instead of duplicating it here.  */
303 | #ifndef YY_YY_Y_TAB_H_INCLUDED
304 | # define YY_YY_Y_TAB_H_INCLUDED
305 | /* Debug traces.  */
306 | #ifndef YYDEBUG
307 | # define YYDEBUG 0
308 | #endif
309 | #if YYDEBUG
310 | extern int yydebug;
311 | #endif
312 | 
313 | /* Token kinds.  */
314 | #ifndef YYTOKENTYPE
315 | # define YYTOKENTYPE
316 |   enum yytokentype
317 |   {
318 |     YYEMPTY = -2,
319 |     YYEOF = 0,                     /* "end of file"  */
320 |     YYerror = 256,                 /* error  */
321 |     YYUNDEF = 257,                 /* "invalid token"  */
322 |     FORM = 258,                    /* FORM  */
323 |     SECTION = 259,                 /* SECTION  */
324 |     FIELD = 260,                   /* FIELD  */
325 |     TEXT = 261,                    /* TEXT  */
326 |     EMAIL = 262,                   /* EMAIL  */
327 |     PASSWORD = 263,                /* PASSWORD  */
328 |     NUMBER = 264,                  /* NUMBER  */
329 |     TEXTAREA = 265,                /* TEXTAREA  */
330 |     DATE = 266,                    /* DATE  */
331 |     CHECKBOX = 267,                /* CHECKBOX  */
332 |     DROPDOWN = 268,                /* DROPDOWN  */
333 |     RADIO = 269,                   /* RADIO  */
334 |     FILE_TYPE = 270,               /* FILE_TYPE  */
335 |     USERNAME = 271,                /* USERNAME  */
336 |     ADDRESS = 272,                 /* ADDRESS  */
337 |     REQUIRED = 273,                /* REQUIRED  */
338 |     OPTIONAL = 274,                /* OPTIONAL  */
339 |     MINLENGTH = 275,               /* MINLENGTH  */
340 |     MAXLENGTH = 276,               /* MAXLENGTH  */
341 |     MIN = 277,                     /* MIN  */
342 |     MAX = 278,                     /* MAX  */
343 |     ROWS = 279,                    /* ROWS  */
344 |     COLS = 280,                    /* COLS  */
345 |     PATTERN = 281,                 /* PATTERN  */
346 |     DEFAULT = 282,                 /* DEFAULT  */
347 |     CONFIRM = 283,                 /* CONFIRM  */
348 |     STRENGTH = 284,                /* STRENGTH  */
349 |     META = 285,                    /* META  */
350 |     IDENTIFIER = 286,              /* IDENTIFIER  */
351 |     NUMBER_LITERAL = 287,          /* NUMBER_LITERAL  */
352 |     STRING_LITERAL = 288,          /* STRING_LITERAL  */
353 |     VALIDATE = 289,                /* VALIDATE  */
354 |     IF = 290,                      /* IF  */
355 |     ERROR = 291,                   /* ERROR  */
356 |     LT = 292,                      /* LT  */
357 |     GT = 293,                      /* GT  */
358 |     LTE = 294,                     /* LTE  */
359 |     GTE = 295,                     /* GTE  */
360 |     EQ = 296,                      /* EQ  */
361 |     NEQ = 297,                     /* NEQ  */
362 |     AND = 298,                     /* AND  */
363 |     OR = 299,                      /* OR  */
364 |     OPTIONS = 300                  /* OPTIONS  */
365 |   };
366 |   typedef enum yytokentype yytoken_kind_t;
367 | #endif
368 | /* Token kinds.  */
369 | #define YYEMPTY -2
370 | #define YYEOF 0
371 | #define YYerror 256
372 | #define YYUNDEF 257
373 | #define FORM 258
374 | #define SECTION 259
375 | #define FIELD 260
376 | #define TEXT 261
377 | #define EMAIL 262
378 | #define PASSWORD 263
379 | #define NUMBER 264
380 | #define TEXTAREA 265
381 | #define DATE 266
382 | #define CHECKBOX 267
383 | #define DROPDOWN 268
384 | #define RADIO 269
385 | #define FILE_TYPE 270
386 | #define USERNAME 271
387 | #define ADDRESS 272
388 | #define REQUIRED 273
389 | #define OPTIONAL 274
390 | #define MINLENGTH 275
391 | #define MAXLENGTH 276
392 | #define MIN 277
393 | #define MAX 278
394 | #define ROWS 279
395 | #define COLS 280
396 | #define PATTERN 281
397 | #define DEFAULT 282
398 | #define CONFIRM 283
399 | #define STRENGTH 284
400 | #define META 285
401 | #define IDENTIFIER 286
402 | #define NUMBER_LITERAL 287
403 | #define STRING_LITERAL 288
404 | #define VALIDATE 289
405 | #define IF 290
406 | #define ERROR 291
407 | #define LT 292
408 | #define GT 293
409 | #define LTE 294
410 | #define GTE 295
411 | #define EQ 296
412 | #define NEQ 297
413 | #define AND 298
414 | #define OR 299
415 | #define OPTIONS 300
416 | 
417 | /* Value type.  */
418 | #if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
419 | union YYSTYPE
420 | {
421 | #line 215 "parser.y"
422 | 
423 |     Form* form;
424 |     Section* section;
425 |     Field* field;
426 |     FieldAttributes field_attrs;
427 |     ValidationRule* validation_rule;
428 |     char* str;
429 |     int num;
430 |     FieldType field_type;
431 |     struct {
432 |         char** arr;
433 |         int count;
434 |     } str_list;
435 | 
436 | #line 437 "y.tab.c"
437 | 
438 | };
439 | typedef union YYSTYPE YYSTYPE;
440 | # define YYSTYPE_IS_TRIVIAL 1
441 | # define YYSTYPE_IS_DECLARED 1
442 | #endif
443 | 
444 | 
445 | extern YYSTYPE yylval;
446 | 
447 | 
448 | int yyparse (void);
449 | 
450 | 
451 | #endif /* !YY_YY_Y_TAB_H_INCLUDED  */
452 | /* Symbol kind.  */
453 | enum yysymbol_kind_t
454 | {
455 |   YYSYMBOL_YYEMPTY = -2,
456 |   YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
457 |   YYSYMBOL_YYerror = 1,                    /* error  */
458 |   YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
459 |   YYSYMBOL_FORM = 3,                       /* FORM  */
460 |   YYSYMBOL_SECTION = 4,                    /* SECTION  */
461 |   YYSYMBOL_FIELD = 5,                      /* FIELD  */
462 |   YYSYMBOL_TEXT = 6,                       /* TEXT  */
463 |   YYSYMBOL_EMAIL = 7,                      /* EMAIL  */
464 |   YYSYMBOL_PASSWORD = 8,                   /* PASSWORD  */
465 |   YYSYMBOL_NUMBER = 9,                     /* NUMBER  */
466 |   YYSYMBOL_TEXTAREA = 10,                  /* TEXTAREA  */
467 |   YYSYMBOL_DATE = 11,                      /* DATE  */
468 |   YYSYMBOL_CHECKBOX = 12,                  /* CHECKBOX  */
469 |   YYSYMBOL_DROPDOWN = 13,                  /* DROPDOWN  */
470 |   YYSYMBOL_RADIO = 14,                     /* RADIO  */
471 |   YYSYMBOL_FILE_TYPE = 15,                 /* FILE_TYPE  */
472 |   YYSYMBOL_USERNAME = 16,                  /* USERNAME  */
473 |   YYSYMBOL_ADDRESS = 17,                   /* ADDRESS  */
474 |   YYSYMBOL_REQUIRED = 18,                  /* REQUIRED  */
475 |   YYSYMBOL_OPTIONAL = 19,                  /* OPTIONAL  */
476 |   YYSYMBOL_MINLENGTH = 20,                 /* MINLENGTH  */
477 |   YYSYMBOL_MAXLENGTH = 21,                 /* MAXLENGTH  */
478 |   YYSYMBOL_MIN = 22,                       /* MIN  */
479 |   YYSYMBOL_MAX = 23,                       /* MAX  */
480 |   YYSYMBOL_ROWS = 24,                      /* ROWS  */
481 |   YYSYMBOL_COLS = 25,                      /* COLS  */
482 |   YYSYMBOL_PATTERN = 26,                   /* PATTERN  */
483 |   YYSYMBOL_DEFAULT = 27,                   /* DEFAULT  */
484 |   YYSYMBOL_CONFIRM = 28,                   /* CONFIRM  */
485 |   YYSYMBOL_STRENGTH = 29,                  /* STRENGTH  */
486 |   YYSYMBOL_META = 30,                      /* META  */
487 |   YYSYMBOL_IDENTIFIER = 31,                /* IDENTIFIER  */
488 |   YYSYMBOL_NUMBER_LITERAL = 32,            /* NUMBER_LITERAL  */
489 |   YYSYMBOL_STRING_LITERAL = 33,            /* STRING_LITERAL  */
490 |   YYSYMBOL_VALIDATE = 34,                  /* VALIDATE  */
491 |   YYSYMBOL_IF = 35,                        /* IF  */
492 |   YYSYMBOL_ERROR = 36,                     /* ERROR  */
493 |   YYSYMBOL_LT = 37,                        /* LT  */
494 |   YYSYMBOL_GT = 38,                        /* GT  */
495 |   YYSYMBOL_LTE = 39,                       /* LTE  */
496 |   YYSYMBOL_GTE = 40,                       /* GTE  */
497 |   YYSYMBOL_EQ = 41,                        /* EQ  */
498 |   YYSYMBOL_NEQ = 42,                       /* NEQ  */
499 |   YYSYMBOL_AND = 43,                       /* AND  */
500 |   YYSYMBOL_OR = 44,                        /* OR  */
501 |   YYSYMBOL_OPTIONS = 45,                   /* OPTIONS  */
502 |   YYSYMBOL_46_ = 46,                       /* '{'  */
503 |   YYSYMBOL_47_ = 47,                       /* '}'  */
504 |   YYSYMBOL_48_ = 48,                       /* ';'  */
505 |   YYSYMBOL_49_ = 49,                       /* ':'  */
506 |   YYSYMBOL_50_ = 50,                       /* '='  */
507 |   YYSYMBOL_51_ = 51,                       /* '['  */
508 |   YYSYMBOL_52_ = 52,                       /* ']'  */
509 |   YYSYMBOL_53_ = 53,                       /* ','  */
510 |   YYSYMBOL_YYACCEPT = 54,                  /* $accept  */
511 |   YYSYMBOL_form = 55,                      /* form  */
512 |   YYSYMBOL_form_body = 56,                 /* form_body  */
513 |   YYSYMBOL_form_item = 57,                 /* form_item  */
514 |   YYSYMBOL_section = 58,                   /* section  */
515 |   YYSYMBOL_59_1 = 59,                      /* $@1  */
516 |   YYSYMBOL_field_list = 60,                /* field_list  */
517 |   YYSYMBOL_field_declaration = 61,         /* field_declaration  */
518 |   YYSYMBOL_field_type = 62,                /* field_type  */
519 |   YYSYMBOL_field_attributes = 63,          /* field_attributes  */
520 |   YYSYMBOL_attribute_opt_semicolon = 64,   /* attribute_opt_semicolon  */
521 |   YYSYMBOL_attribute = 65,                 /* attribute  */
522 |   YYSYMBOL_validation_block = 66,          /* validation_block  */
523 |   YYSYMBOL_validation_rules = 67,          /* validation_rules  */
524 |   YYSYMBOL_validation_rule = 68,           /* validation_rule  */
525 |   YYSYMBOL_condition = 69,                 /* condition  */
526 |   YYSYMBOL_metadata_declaration = 70,      /* metadata_declaration  */
527 |   YYSYMBOL_options_list = 71               /* options_list  */
528 | };
529 | typedef enum yysymbol_kind_t yysymbol_kind_t;
530 | 
531 | 
532 | 
533 | 
534 | #ifdef short
535 | # undef short
536 | #endif
537 | 
538 | /* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
539 |    <limits.h> and (if available) <stdint.h> are included
540 |    so that the code can choose integer types of a good width.  */
541 | 
542 | #ifndef __PTRDIFF_MAX__
543 | # include <limits.h> /* INFRINGES ON USER NAME SPACE */
544 | # if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
545 | #  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
546 | #  define YY_STDINT_H
547 | # endif
548 | #endif
549 | 
550 | /* Narrow types that promote to a signed type and that can represent a
551 |    signed or unsigned integer of at least N bits.  In tables they can
552 |    save space and decrease cache pressure.  Promoting to a signed type
553 |    helps avoid bugs in integer arithmetic.  */
554 | 
555 | #ifdef __INT_LEAST8_MAX__
556 | typedef __INT_LEAST8_TYPE__ yytype_int8;
557 | #elif defined YY_STDINT_H
558 | typedef int_least8_t yytype_int8;
559 | #else
560 | typedef signed char yytype_int8;
561 | #endif
562 | 
563 | #ifdef __INT_LEAST16_MAX__
564 | typedef __INT_LEAST16_TYPE__ yytype_int16;
565 | #elif defined YY_STDINT_H
566 | typedef int_least16_t yytype_int16;
567 | #else
568 | typedef short yytype_int16;
569 | #endif
570 | 
571 | /* Work around bug in HP-UX 11.23, which defines these macros
572 |    incorrectly for preprocessor constants.  This workaround can likely
573 |    be removed in 2023, as HPE has promised support for HP-UX 11.23
574 |    (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
575 |    <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
576 | #ifdef __hpux
577 | # undef UINT_LEAST8_MAX
578 | # undef UINT_LEAST16_MAX
579 | # define UINT_LEAST8_MAX 255
580 | # define UINT_LEAST16_MAX 65535
581 | #endif
582 | 
583 | #if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
584 | typedef __UINT_LEAST8_TYPE__ yytype_uint8;
585 | #elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
586 |        && UINT_LEAST8_MAX <= INT_MAX)
587 | typedef uint_least8_t yytype_uint8;
588 | #elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
589 | typedef unsigned char yytype_uint8;
590 | #else
591 | typedef short yytype_uint8;
592 | #endif
593 | 
594 | #if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
595 | typedef __UINT_LEAST16_TYPE__ yytype_uint16;
596 | #elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
597 |        && UINT_LEAST16_MAX <= INT_MAX)
598 | typedef uint_least16_t yytype_uint16;
599 | #elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
600 | typedef unsigned short yytype_uint16;
601 | #else
602 | typedef int yytype_uint16;
603 | #endif
604 | 
605 | #ifndef YYPTRDIFF_T
606 | # if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
607 | #  define YYPTRDIFF_T __PTRDIFF_TYPE__
608 | #  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
609 | # elif defined PTRDIFF_MAX
610 | #  ifndef ptrdiff_t
611 | #   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
612 | #  endif
613 | #  define YYPTRDIFF_T ptrdiff_t
614 | #  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
615 | # else
616 | #  define YYPTRDIFF_T long
617 | #  define YYPTRDIFF_MAXIMUM LONG_MAX
618 | # endif
619 | #endif
620 | 
621 | #ifndef YYSIZE_T
622 | # ifdef __SIZE_TYPE__
623 | #  define YYSIZE_T __SIZE_TYPE__
624 | # elif defined size_t
625 | #  define YYSIZE_T size_t
626 | # elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
627 | #  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
628 | #  define YYSIZE_T size_t
629 | # else
630 | #  define YYSIZE_T unsigned
631 | # endif
632 | #endif
633 | 
634 | #define YYSIZE_MAXIMUM                                  \
635 |   YY_CAST (YYPTRDIFF_T,                                 \
636 |            (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
637 |             ? YYPTRDIFF_MAXIMUM                         \
638 |             : YY_CAST (YYSIZE_T, -1)))
639 | 
640 | #define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))
641 | 
642 | 
643 | /* Stored state numbers (used for stacks). */
644 | typedef yytype_int8 yy_state_t;
645 | 
646 | /* State numbers in computations.  */
647 | typedef int yy_state_fast_t;
648 | 
649 | #ifndef YY_
650 | # if defined YYENABLE_NLS && YYENABLE_NLS
651 | #  if ENABLE_NLS
652 | #   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
653 | #   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
654 | #  endif
655 | # endif
656 | # ifndef YY_
657 | #  define YY_(Msgid) Msgid
658 | # endif
659 | #endif
660 | 
661 | 
662 | #ifndef YY_ATTRIBUTE_PURE
663 | # if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
664 | #  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
665 | # else
666 | #  define YY_ATTRIBUTE_PURE
667 | # endif
668 | #endif
669 | 
670 | #ifndef YY_ATTRIBUTE_UNUSED
671 | # if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
672 | #  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
673 | # else
674 | #  define YY_ATTRIBUTE_UNUSED
675 | # endif
676 | #endif
677 | 
678 | /* Suppress unused-variable warnings by "using" E.  */
679 | #if ! defined lint || defined __GNUC__
680 | # define YY_USE(E) ((void) (E))
681 | #else
682 | # define YY_USE(E) /* empty */
683 | #endif
684 | 
685 | /* Suppress an incorrect diagnostic about yylval being uninitialized.  */
686 | #if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
687 | # if __GNUC__ * 100 + __GNUC_MINOR__ < 407
688 | #  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
689 |     _Pragma ("GCC diagnostic push")                                     \
690 |     _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
691 | # else
692 | #  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
693 |     _Pragma ("GCC diagnostic push")                                     \
694 |     _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
695 |     _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
696 | # endif
697 | # define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
698 |     _Pragma ("GCC diagnostic pop")
699 | #else
700 | # define YY_INITIAL_VALUE(Value) Value
701 | #endif
702 | #ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
703 | # define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
704 | # define YY_IGNORE_MAYBE_UNINITIALIZED_END
705 | #endif
706 | #ifndef YY_INITIAL_VALUE
707 | # define YY_INITIAL_VALUE(Value) /* Nothing. */
708 | #endif
709 | 
710 | #if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
711 | # define YY_IGNORE_USELESS_CAST_BEGIN                          \
712 |     _Pragma ("GCC diagnostic push")                            \
713 |     _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
714 | # define YY_IGNORE_USELESS_CAST_END            \
715 |     _Pragma ("GCC diagnostic pop")
716 | #endif
717 | #ifndef YY_IGNORE_USELESS_CAST_BEGIN
718 | # define YY_IGNORE_USELESS_CAST_BEGIN
719 | # define YY_IGNORE_USELESS_CAST_END
720 | #endif
721 | 
722 | 
723 | #define YY_ASSERT(E) ((void) (0 && (E)))
724 | 
725 | #if 1
726 | 
727 | /* The parser invokes alloca or malloc; define the necessary symbols.  */
728 | 
729 | # ifdef YYSTACK_USE_ALLOCA
730 | #  if YYSTACK_USE_ALLOCA
731 | #   ifdef __GNUC__
732 | #    define YYSTACK_ALLOC __builtin_alloca
733 | #   elif defined __BUILTIN_VA_ARG_INCR
734 | #    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
735 | #   elif defined _AIX
736 | #    define YYSTACK_ALLOC __alloca
737 | #   elif defined _MSC_VER
738 | #    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
739 | #    define alloca _alloca
740 | #   else
741 | #    define YYSTACK_ALLOC alloca
742 | #    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
743 | #     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
744 |       /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
745 | #     ifndef EXIT_SUCCESS
746 | #      define EXIT_SUCCESS 0
747 | #     endif
748 | #    endif
749 | #   endif
750 | #  endif
751 | # endif
752 | 
753 | # ifdef YYSTACK_ALLOC
754 |    /* Pacify GCC's 'empty if-body' warning.  */
755 | #  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
756 | #  ifndef YYSTACK_ALLOC_MAXIMUM
757 |     /* The OS might guarantee only one guard page at the bottom of the stack,
758 |        and a page size can be as small as 4096 bytes.  So we cannot safely
759 |        invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
760 |        to allow for a few compiler-allocated temporary stack slots.  */
761 | #   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
762 | #  endif
763 | # else
764 | #  define YYSTACK_ALLOC YYMALLOC
765 | #  define YYSTACK_FREE YYFREE
766 | #  ifndef YYSTACK_ALLOC_MAXIMUM
767 | #   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
768 | #  endif
769 | #  if (defined __cplusplus && ! defined EXIT_SUCCESS \
770 |        && ! ((defined YYMALLOC || defined malloc) \
771 |              && (defined YYFREE || defined free)))
772 | #   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
773 | #   ifndef EXIT_SUCCESS
774 | #    define EXIT_SUCCESS 0
775 | #   endif
776 | #  endif
777 | #  ifndef YYMALLOC
778 | #   define YYMALLOC malloc
779 | #   if ! defined malloc && ! defined EXIT_SUCCESS
780 | void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
781 | #   endif
782 | #  endif
783 | #  ifndef YYFREE
784 | #   define YYFREE free
785 | #   if ! defined free && ! defined EXIT_SUCCESS
786 | void free (void *); /* INFRINGES ON USER NAME SPACE */
787 | #   endif
788 | #  endif
789 | # endif
790 | #endif /* 1 */
791 | 
792 | #if (! defined yyoverflow \
793 |      && (! defined __cplusplus \
794 |          || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))
795 | 
796 | /* A type that is properly aligned for any stack member.  */
797 | union yyalloc
798 | {
799 |   yy_state_t yyss_alloc;
800 |   YYSTYPE yyvs_alloc;
801 | };
802 | 
803 | /* The size of the maximum gap between one aligned stack and the next.  */
804 | # define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)
805 | 
806 | /* The size of an array large to enough to hold all stacks, each with
807 |    N elements.  */
808 | # define YYSTACK_BYTES(N) \
809 |      ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
810 |       + YYSTACK_GAP_MAXIMUM)
811 | 
812 | # define YYCOPY_NEEDED 1
813 | 
814 | /* Relocate STACK from its old location to the new one.  The
815 |    local variables YYSIZE and YYSTACKSIZE give the old and new number of
816 |    elements in the stack, and YYPTR gives the new location of the
817 |    stack.  Advance YYPTR to a properly aligned location for the next
818 |    stack.  */
819 | # define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
820 |     do                                                                  \
821 |       {                                                                 \
822 |         YYPTRDIFF_T yynewbytes;                                         \
823 |         YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
824 |         Stack = &yyptr->Stack_alloc;                                    \
825 |         yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
826 |         yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
827 |       }                                                                 \
828 |     while (0)
829 | 
830 | #endif
831 | 
832 | #if defined YYCOPY_NEEDED && YYCOPY_NEEDED
833 | /* Copy COUNT objects from SRC to DST.  The source and destination do
834 |    not overlap.  */
835 | # ifndef YYCOPY
836 | #  if defined __GNUC__ && 1 < __GNUC__
837 | #   define YYCOPY(Dst, Src, Count) \
838 |       __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
839 | #  else
840 | #   define YYCOPY(Dst, Src, Count)              \
841 |       do                                        \
842 |         {                                       \
843 |           YYPTRDIFF_T yyi;                      \
844 |           for (yyi = 0; yyi < (Count); yyi++)   \
845 |             (Dst)[yyi] = (Src)[yyi];            \
846 |         }                                       \
847 |       while (0)
848 | #  endif
849 | # endif
850 | #endif /* !YYCOPY_NEEDED */
851 | 
852 | /* YYFINAL -- State number of the termination state.  */
853 | #define YYFINAL  4
854 | /* YYLAST -- Last index in YYTABLE.  */
855 | #define YYLAST   104
856 | 
857 | /* YYNTOKENS -- Number of terminals.  */
858 | #define YYNTOKENS  54
859 | /* YYNNTS -- Number of nonterminals.  */
860 | #define YYNNTS  18
861 | /* YYNRULES -- Number of rules.  */
862 | #define YYNRULES  59
863 | /* YYNSTATES -- Number of states.  */
864 | #define YYNSTATES  118
865 | 
866 | /* YYMAXUTOK -- Last valid token kind.  */
867 | #define YYMAXUTOK   300
868 | 
869 | 
870 | /* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
871 |    as returned by yylex, with out-of-bounds checking.  */
872 | #define YYTRANSLATE(YYX)                                \
873 |   (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
874 |    ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
875 |    : YYSYMBOL_YYUNDEF)
876 | 
877 | /* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
878 |    as returned by yylex.  */
879 | static const yytype_int8 yytranslate[] =
880 | {
881 |        0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
882 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
883 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
884 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
885 |        2,     2,     2,     2,    53,     2,     2,     2,     2,     2,
886 |        2,     2,     2,     2,     2,     2,     2,     2,    49,    48,
887 |        2,    50,     2,     2,     2,     2,     2,     2,     2,     2,
888 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
889 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
890 |        2,    51,     2,    52,     2,     2,     2,     2,     2,     2,
891 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
892 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
893 |        2,     2,     2,    46,     2,    47,     2,     2,     2,     2,
894 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
895 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
896 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
897 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
898 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
899 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
900 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
901 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
902 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
903 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
904 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
905 |        2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
906 |        2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
907 |        5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
908 |       15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
909 |       25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
910 |       35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
911 |       45
912 | };
913 | 
914 | #if YYDEBUG
915 | /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
916 | static const yytype_int16 yyrline[] =
917 | {
918 |        0,   242,   242,   254,   255,   259,   260,   261,   268,   268,
919 |      269,   273,   297,   298,   299,   307,   322,   323,   324,   325,
920 |      326,   327,   328,   329,   330,   331,   332,   333,   337,   338,
921 |      342,   343,   347,   348,   349,   350,   351,   352,   353,   354,
922 |      355,   356,   357,   358,   359,   360,   373,   379,   380,   383,
923 |      397,   403,   409,   415,   421,   427,   433,   441,   450,   451
924 | };
925 | #endif
926 | 
927 | /** Accessing symbol of state STATE.  */
928 | #define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])
929 | 
930 | #if 1
931 | /* The user-facing name of the symbol whose (internal) number is
932 |    YYSYMBOL.  No bounds checking.  */
933 | static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;
934 | 
935 | /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
936 |    First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
937 | static const char *const yytname[] =
938 | {
939 |   "\"end of file\"", "error", "\"invalid token\"", "FORM", "SECTION",
940 |   "FIELD", "TEXT", "EMAIL", "PASSWORD", "NUMBER", "TEXTAREA", "DATE",
941 |   "CHECKBOX", "DROPDOWN", "RADIO", "FILE_TYPE", "USERNAME", "ADDRESS",
942 |   "REQUIRED", "OPTIONAL", "MINLENGTH", "MAXLENGTH", "MIN", "MAX", "ROWS",
943 |   "COLS", "PATTERN", "DEFAULT", "CONFIRM", "STRENGTH", "META",
944 |   "IDENTIFIER", "NUMBER_LITERAL", "STRING_LITERAL", "VALIDATE", "IF",
945 |   "ERROR", "LT", "GT", "LTE", "GTE", "EQ", "NEQ", "AND", "OR", "OPTIONS",
946 |   "'{'", "'}'", "';'", "':'", "'='", "'['", "']'", "','", "$accept",
947 |   "form", "form_body", "form_item", "section", "$@1", "field_list",
948 |   "field_declaration", "field_type", "field_attributes",
949 |   "attribute_opt_semicolon", "attribute", "validation_block",
950 |   "validation_rules", "validation_rule", "condition",
951 |   "metadata_declaration", "options_list", YY_NULLPTR
952 | };
953 | 
954 | static const char *
955 | yysymbol_name (yysymbol_kind_t yysymbol)
956 | {
957 |   return yytname[yysymbol];
958 | }
959 | #endif
960 | 
961 | #define YYPACT_NINF (-20)
962 | 
963 | #define yypact_value_is_default(Yyn) \
964 |   ((Yyn) == YYPACT_NINF)
965 | 
966 | #define YYTABLE_NINF (-1)
967 | 
968 | #define yytable_value_is_error(Yyn) \
969 |   0
970 | 
971 | /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
972 |    STATE-NUM.  */
973 | static const yytype_int8 yypact[] =
974 | {
975 |        0,    -6,    28,   -16,   -20,   -20,    -3,     2,     8,    -5,
976 |      -20,   -20,   -20,   -20,   -20,     1,   -10,   -20,    -4,    -2,
977 |        9,   -18,   -20,   -20,   -20,    12,    30,   -20,   -20,    -1,
978 |      -20,   -19,    16,    15,    33,   -20,   -20,    34,    35,    36,
979 |       37,     4,    38,    29,   -20,    22,   -20,   -20,   -20,   -20,
980 |      -20,   -20,   -20,    39,    42,    25,   -20,   -20,   -20,   -20,
981 |      -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,    31,    27,
982 |      -20,   -20,   -13,   -20,   -20,    26,    32,    40,    41,    43,
983 |       44,    45,    46,    47,    48,    49,   -20,   -20,    52,    51,
984 |       53,    54,    55,    56,    57,    59,    -7,    50,    69,    24,
985 |      -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,
986 |      -20,   -20,    70,   -20,   -15,   -20,    71,   -20
987 | };
988 | 
989 | /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
990 |    Performed when YYTABLE does not specify something else to do.  Zero
991 |    means the default is an error.  */
992 | static const yytype_int8 yydefact[] =
993 | {
994 |        0,     0,     0,     0,     1,     3,     0,     0,     0,     0,
995 |        2,     4,     5,     6,     7,     0,     0,    47,     0,     8,
996 |        0,     0,    11,    10,    12,     0,     0,    46,    48,     0,
997 |       57,     0,     0,     0,     0,     9,    13,     0,     0,     0,
998 |        0,     0,     0,     0,    14,     0,    50,    51,    52,    53,
999 |       56,    54,    55,     0,     0,     0,    16,    17,    18,    19,
1000 |       20,    21,    22,    23,    24,    25,    26,    27,     0,     0,
1001 |       28,    49,     0,    32,    33,     0,     0,     0,     0,     0,
1002 |        0,     0,     0,     0,     0,     0,    15,    29,    31,     0,
1003 |        0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
1004 |       30,    34,    35,    36,    37,    38,    39,    40,    42,    41,
1005 |       44,    43,     0,    58,     0,    45,     0,    59
1006 | };
1007 | 
1008 | /* YYPGOTO[NTERM-NUM].  */
1009 | static const yytype_int8 yypgoto[] =
1010 | {
1011 |      -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20,
1012 |      -20,   -20,   -20,   -20,   -20,   -20,   -20,   -20
1013 | };
1014 | 
1015 | /* YYDEFGOTO[NTERM-NUM].  */
1016 | static const yytype_int8 yydefgoto[] =
1017 | {
1018 |        0,     2,     6,    11,    12,    24,    29,    36,    68,    72,
1019 |       87,    88,    13,    21,    28,    32,    14,   114
1020 | };
1021 | 
1022 | /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
1023 |    positive, shift that token.  If negative, reduce the rule whose
1024 |    number is the opposite.  If YYTABLE_NINF, syntax error.  */
1025 | static const yytype_int8 yytable[] =
1026 | {
1027 |       33,     7,    18,     1,    34,    73,    74,    75,    76,    77,
1028 |       78,    79,    80,    81,    82,    83,    84,    26,    37,    38,
1029 |       39,    40,    41,    42,   108,     3,   109,     8,     4,    27,
1030 |        5,     9,    85,    15,    86,    50,    51,   115,   116,    16,
1031 |       20,    17,    25,    22,    10,    23,    35,    19,    56,    57,
1032 |       58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
1033 |       30,    31,    43,    44,    45,    53,    46,    47,    48,    49,
1034 |       52,    54,    55,    69,    71,   112,    89,    70,     0,     0,
1035 |        0,   110,    90,   101,     0,   102,   103,   104,   105,   106,
1036 |       91,    92,   107,    93,    94,    95,    96,    97,    98,    99,
1037 |      100,   111,     0,   113,   117
1038 | };
1039 | 
1040 | static const yytype_int8 yycheck[] =
1041 | {
1042 |        1,     4,     1,     3,     5,    18,    19,    20,    21,    22,
1043 |       23,    24,    25,    26,    27,    28,    29,    35,    37,    38,
1044 |       39,    40,    41,    42,    31,    31,    33,    30,     0,    47,
1045 |       46,    34,    45,    31,    47,    31,    32,    52,    53,    31,
1046 |       50,    46,    33,    47,    47,    47,    47,    46,     6,     7,
1047 |        8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
1048 |       48,    31,    46,    48,    31,    36,    32,    32,    32,    32,
1049 |       32,    49,    33,    48,    47,    51,    50,    46,    -1,    -1,
1050 |       -1,    31,    50,    32,    -1,    32,    32,    32,    32,    32,
1051 |       50,    50,    33,    50,    50,    50,    50,    50,    50,    50,
1052 |       48,    32,    -1,    33,    33
1053 | };
1054 | 
1055 | /* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
1056 |    state STATE-NUM.  */
1057 | static const yytype_int8 yystos[] =
1058 | {
1059 |        0,     3,    55,    31,     0,    46,    56,     4,    30,    34,
1060 |       47,    57,    58,    66,    70,    31,    31,    46,     1,    46,
1061 |       50,    67,    47,    47,    59,    33,    35,    47,    68,    60,
1062 |       48,    31,    69,     1,     5,    47,    61,    37,    38,    39,
1063 |       40,    41,    42,    46,    48,    31,    32,    32,    32,    32,
1064 |       31,    32,    32,    36,    49,    33,     6,     7,     8,     9,
1065 |       10,    11,    12,    13,    14,    15,    16,    17,    62,    48,
1066 |       46,    47,    63,    18,    19,    20,    21,    22,    23,    24,
1067 |       25,    26,    27,    28,    29,    45,    47,    64,    65,    50,
1068 |       50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
1069 |       48,    32,    32,    32,    32,    32,    32,    33,    31,    33,
1070 |       31,    32,    51,    33,    71,    52,    53,    33
1071 | };
1072 | 
1073 | /* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
1074 | static const yytype_int8 yyr1[] =
1075 | {
1076 |        0,    54,    55,    56,    56,    57,    57,    57,    59,    58,
1077 |       58,    58,    60,    60,    60,    61,    62,    62,    62,    62,
1078 |       62,    62,    62,    62,    62,    62,    62,    62,    63,    63,
1079 |       64,    64,    65,    65,    65,    65,    65,    65,    65,    65,
1080 |       65,    65,    65,    65,    65,    65,    66,    67,    67,    68,
1081 |       69,    69,    69,    69,    69,    69,    69,    70,    71,    71
1082 | };
1083 | 
1084 | /* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
1085 | static const yytype_int8 yyr2[] =
1086 | {
1087 |        0,     2,     5,     0,     2,     1,     1,     1,     0,     6,
1088 |        4,     4,     0,     2,     3,     7,     1,     1,     1,     1,
1089 |        1,     1,     1,     1,     1,     1,     1,     1,     0,     2,
1090 |        2,     1,     1,     1,     3,     3,     3,     3,     3,     3,
1091 |        3,     3,     3,     3,     3,     5,     4,     0,     2,     7,
1092 |        3,     3,     3,     3,     3,     3,     3,     5,     1,     3
1093 | };
1094 | 
1095 | 
1096 | enum { YYENOMEM = -2 };
1097 | 
1098 | #define yyerrok         (yyerrstatus = 0)
1099 | #define yyclearin       (yychar = YYEMPTY)
1100 | 
1101 | #define YYACCEPT        goto yyacceptlab
1102 | #define YYABORT         goto yyabortlab
1103 | #define YYERROR         goto yyerrorlab
1104 | #define YYNOMEM         goto yyexhaustedlab
1105 | 
1106 | 
1107 | #define YYRECOVERING()  (!!yyerrstatus)
1108 | 
1109 | #define YYBACKUP(Token, Value)                                    \
1110 |   do                                                              \
1111 |     if (yychar == YYEMPTY)                                        \
1112 |       {                                                           \
1113 |         yychar = (Token);                                         \
1114 |         yylval = (Value);                                         \
1115 |         YYPOPSTACK (yylen);                                       \
1116 |         yystate = *yyssp;                                         \
1117 |         goto yybackup;                                            \
1118 |       }                                                           \
1119 |     else                                                          \
1120 |       {                                                           \
1121 |         yyerror (YY_("syntax error: cannot back up")); \
1122 |         YYERROR;                                                  \
1123 |       }                                                           \
1124 |   while (0)
1125 | 
1126 | /* Backward compatibility with an undocumented macro.
1127 |    Use YYerror or YYUNDEF. */
1128 | #define YYERRCODE YYUNDEF
1129 | 
1130 | 
1131 | /* Enable debugging if requested.  */
1132 | #if YYDEBUG
1133 | 
1134 | # ifndef YYFPRINTF
1135 | #  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
1136 | #  define YYFPRINTF fprintf
1137 | # endif
1138 | 
1139 | # define YYDPRINTF(Args)                        \
1140 | do {                                            \
1141 |   if (yydebug)                                  \
1142 |     YYFPRINTF Args;                             \
1143 | } while (0)
1144 | 
1145 | 
1146 | 
1147 | 
1148 | # define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
1149 | do {                                                                      \
1150 |   if (yydebug)                                                            \
1151 |     {                                                                     \
1152 |       YYFPRINTF (stderr, "%s ", Title);                                   \
1153 |       yy_symbol_print (stderr,                                            \
1154 |                   Kind, Value); \
1155 |       YYFPRINTF (stderr, "\n");                                           \
1156 |     }                                                                     \
1157 | } while (0)
1158 | 
1159 | 
1160 | /*-----------------------------------.
1161 | | Print this symbol's value on YYO.  |
1162 | `-----------------------------------*/
1163 | 
1164 | static void
1165 | yy_symbol_value_print (FILE *yyo,
1166 |                        yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
1167 | {
1168 |   FILE *yyoutput = yyo;
1169 |   YY_USE (yyoutput);
1170 |   if (!yyvaluep)
1171 |     return;
1172 |   YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
1173 |   YY_USE (yykind);
1174 |   YY_IGNORE_MAYBE_UNINITIALIZED_END
1175 | }
1176 | 
1177 | 
1178 | /*---------------------------.
1179 | | Print this symbol on YYO.  |
1180 | `---------------------------*/
1181 | 
1182 | static void
1183 | yy_symbol_print (FILE *yyo,
1184 |                  yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
1185 | {
1186 |   YYFPRINTF (yyo, "%s %s (",
1187 |              yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));
1188 | 
1189 |   yy_symbol_value_print (yyo, yykind, yyvaluep);
1190 |   YYFPRINTF (yyo, ")");
1191 | }
1192 | 
1193 | /*------------------------------------------------------------------.
1194 | | yy_stack_print -- Print the state stack from its BOTTOM up to its |
1195 | | TOP (included).                                                   |
1196 | `------------------------------------------------------------------*/
1197 | 
1198 | static void
1199 | yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
1200 | {
1201 |   YYFPRINTF (stderr, "Stack now");
1202 |   for (; yybottom <= yytop; yybottom++)
1203 |     {
1204 |       int yybot = *yybottom;
1205 |       YYFPRINTF (stderr, " %d", yybot);
1206 |     }
1207 |   YYFPRINTF (stderr, "\n");
1208 | }
1209 | 
1210 | # define YY_STACK_PRINT(Bottom, Top)                            \
1211 | do {                                                            \
1212 |   if (yydebug)                                                  \
1213 |     yy_stack_print ((Bottom), (Top));                           \
1214 | } while (0)
1215 | 
1216 | 
1217 | /*------------------------------------------------.
1218 | | Report that the YYRULE is going to be reduced.  |
1219 | `------------------------------------------------*/
1220 | 
1221 | static void
1222 | yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
1223 |                  int yyrule)
1224 | {
1225 |   int yylno = yyrline[yyrule];
1226 |   int yynrhs = yyr2[yyrule];
1227 |   int yyi;
1228 |   YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
1229 |              yyrule - 1, yylno);
1230 |   /* The symbols being reduced.  */
1231 |   for (yyi = 0; yyi < yynrhs; yyi++)
1232 |     {
1233 |       YYFPRINTF (stderr, "   $%d = ", yyi + 1);
1234 |       yy_symbol_print (stderr,
1235 |                        YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
1236 |                        &yyvsp[(yyi + 1) - (yynrhs)]);
1237 |       YYFPRINTF (stderr, "\n");
1238 |     }
1239 | }
1240 | 
1241 | # define YY_REDUCE_PRINT(Rule)          \
1242 | do {                                    \
1243 |   if (yydebug)                          \
1244 |     yy_reduce_print (yyssp, yyvsp, Rule); \
1245 | } while (0)
1246 | 
1247 | /* Nonzero means print parse trace.  It is left uninitialized so that
1248 |    multiple parsers can coexist.  */
1249 | int yydebug;
1250 | #else /* !YYDEBUG */
1251 | # define YYDPRINTF(Args) ((void) 0)
1252 | # define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
1253 | # define YY_STACK_PRINT(Bottom, Top)
1254 | # define YY_REDUCE_PRINT(Rule)
1255 | #endif /* !YYDEBUG */
1256 | 
1257 | 
1258 | /* YYINITDEPTH -- initial size of the parser's stacks.  */
1259 | #ifndef YYINITDEPTH
1260 | # define YYINITDEPTH 200
1261 | #endif
1262 | 
1263 | /* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
1264 |    if the built-in stack extension method is used).
1265 | 
1266 |    Do not make this value too large; the results are undefined if
1267 |    YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
1268 |    evaluated with infinite-precision integer arithmetic.  */
1269 | 
1270 | #ifndef YYMAXDEPTH
1271 | # define YYMAXDEPTH 10000
1272 | #endif
1273 | 
1274 | 
1275 | /* Context of a parse error.  */
1276 | typedef struct
1277 | {
1278 |   yy_state_t *yyssp;
1279 |   yysymbol_kind_t yytoken;
1280 | } yypcontext_t;
1281 | 
1282 | /* Put in YYARG at most YYARGN of the expected tokens given the
1283 |    current YYCTX, and return the number of tokens stored in YYARG.  If
1284 |    YYARG is null, return the number of expected tokens (guaranteed to
1285 |    be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
1286 |    Return 0 if there are more than YYARGN expected tokens, yet fill
1287 |    YYARG up to YYARGN. */
1288 | static int
1289 | yypcontext_expected_tokens (const yypcontext_t *yyctx,
1290 |                             yysymbol_kind_t yyarg[], int yyargn)
1291 | {
1292 |   /* Actual size of YYARG. */
1293 |   int yycount = 0;
1294 |   int yyn = yypact[+*yyctx->yyssp];
1295 |   if (!yypact_value_is_default (yyn))
1296 |     {
1297 |       /* Start YYX at -YYN if negative to avoid negative indexes in
1298 |          YYCHECK.  In other words, skip the first -YYN actions for
1299 |          this state because they are default actions.  */
1300 |       int yyxbegin = yyn < 0 ? -yyn : 0;
1301 |       /* Stay within bounds of both yycheck and yytname.  */
1302 |       int yychecklim = YYLAST - yyn + 1;
1303 |       int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
1304 |       int yyx;
1305 |       for (yyx = yyxbegin; yyx < yyxend; ++yyx)
1306 |         if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
1307 |             && !yytable_value_is_error (yytable[yyx + yyn]))
1308 |           {
1309 |             if (!yyarg)
1310 |               ++yycount;
1311 |             else if (yycount == yyargn)
1312 |               return 0;
1313 |             else
1314 |               yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
1315 |           }
1316 |     }
1317 |   if (yyarg && yycount == 0 && 0 < yyargn)
1318 |     yyarg[0] = YYSYMBOL_YYEMPTY;
1319 |   return yycount;
1320 | }
1321 | 
1322 | 
1323 | 
1324 | 
1325 | #ifndef yystrlen
1326 | # if defined __GLIBC__ && defined _STRING_H
1327 | #  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
1328 | # else
1329 | /* Return the length of YYSTR.  */
1330 | static YYPTRDIFF_T
1331 | yystrlen (const char *yystr)
1332 | {
1333 |   YYPTRDIFF_T yylen;
1334 |   for (yylen = 0; yystr[yylen]; yylen++)
1335 |     continue;
1336 |   return yylen;
1337 | }
1338 | # endif
1339 | #endif
1340 | 
1341 | #ifndef yystpcpy
1342 | # if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
1343 | #  define yystpcpy stpcpy
1344 | # else
1345 | /* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
1346 |    YYDEST.  */
1347 | static char *
1348 | yystpcpy (char *yydest, const char *yysrc)
1349 | {
1350 |   char *yyd = yydest;
1351 |   const char *yys = yysrc;
1352 | 
1353 |   while ((*yyd++ = *yys++) != '\0')
1354 |     continue;
1355 | 
1356 |   return yyd - 1;
1357 | }
1358 | # endif
1359 | #endif
1360 | 
1361 | #ifndef yytnamerr
1362 | /* Copy to YYRES the contents of YYSTR after stripping away unnecessary
1363 |    quotes and backslashes, so that it's suitable for yyerror.  The
1364 |    heuristic is that double-quoting is unnecessary unless the string
1365 |    contains an apostrophe, a comma, or backslash (other than
1366 |    backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
1367 |    null, do not copy; instead, return the length of what the result
1368 |    would have been.  */
1369 | static YYPTRDIFF_T
1370 | yytnamerr (char *yyres, const char *yystr)
1371 | {
1372 |   if (*yystr == '"')
1373 |     {
1374 |       YYPTRDIFF_T yyn = 0;
1375 |       char const *yyp = yystr;
1376 |       for (;;)
1377 |         switch (*++yyp)
1378 |           {
1379 |           case '\'':
1380 |           case ',':
1381 |             goto do_not_strip_quotes;
1382 | 
1383 |           case '\\':
1384 |             if (*++yyp != '\\')
1385 |               goto do_not_strip_quotes;
1386 |             else
1387 |               goto append;
1388 | 
1389 |           append:
1390 |           default:
1391 |             if (yyres)
1392 |               yyres[yyn] = *yyp;
1393 |             yyn++;
1394 |             break;
1395 | 
1396 |           case '"':
1397 |             if (yyres)
1398 |               yyres[yyn] = '\0';
1399 |             return yyn;
1400 |           }
1401 |     do_not_strip_quotes: ;
1402 |     }
1403 | 
1404 |   if (yyres)
1405 |     return yystpcpy (yyres, yystr) - yyres;
1406 |   else
1407 |     return yystrlen (yystr);
1408 | }
1409 | #endif
1410 | 
1411 | 
1412 | static int
1413 | yy_syntax_error_arguments (const yypcontext_t *yyctx,
1414 |                            yysymbol_kind_t yyarg[], int yyargn)
1415 | {
1416 |   /* Actual size of YYARG. */
1417 |   int yycount = 0;
1418 |   /* There are many possibilities here to consider:
1419 |      - If this state is a consistent state with a default action, then
1420 |        the only way this function was invoked is if the default action
1421 |        is an error action.  In that case, don't check for expected
1422 |        tokens because there are none.
1423 |      - The only way there can be no lookahead present (in yychar) is if
1424 |        this state is a consistent state with a default action.  Thus,
1425 |        detecting the absence of a lookahead is sufficient to determine
1426 |        that there is no unexpected or expected token to report.  In that
1427 |        case, just report a simple "syntax error".
1428 |      - Don't assume there isn't a lookahead just because this state is a
1429 |        consistent state with a default action.  There might have been a
1430 |        previous inconsistent state, consistent state with a non-default
1431 |        action, or user semantic action that manipulated yychar.
1432 |      - Of course, the expected token list depends on states to have
1433 |        correct lookahead information, and it depends on the parser not
1434 |        to perform extra reductions after fetching a lookahead from the
1435 |        scanner and before detecting a syntax error.  Thus, state merging
1436 |        (from LALR or IELR) and default reductions corrupt the expected
1437 |        token list.  However, the list is correct for canonical LR with
1438 |        one exception: it will still contain any token that will not be
1439 |        accepted due to an error action in a later state.
1440 |   */
1441 |   if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
1442 |     {
1443 |       int yyn;
1444 |       if (yyarg)
1445 |         yyarg[yycount] = yyctx->yytoken;
1446 |       ++yycount;
1447 |       yyn = yypcontext_expected_tokens (yyctx,
1448 |                                         yyarg ? yyarg + 1 : yyarg, yyargn - 1);
1449 |       if (yyn == YYENOMEM)
1450 |         return YYENOMEM;
1451 |       else
1452 |         yycount += yyn;
1453 |     }
1454 |   return yycount;
1455 | }
1456 | 
1457 | /* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
1458 |    about the unexpected token YYTOKEN for the state stack whose top is
1459 |    YYSSP.
1460 | 
1461 |    Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
1462 |    not large enough to hold the message.  In that case, also set
1463 |    *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
1464 |    required number of bytes is too large to store.  */
1465 | static int
1466 | yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
1467 |                 const yypcontext_t *yyctx)
1468 | {
1469 |   enum { YYARGS_MAX = 5 };
1470 |   /* Internationalized format string. */
1471 |   const char *yyformat = YY_NULLPTR;
1472 |   /* Arguments of yyformat: reported tokens (one for the "unexpected",
1473 |      one per "expected"). */
1474 |   yysymbol_kind_t yyarg[YYARGS_MAX];
1475 |   /* Cumulated lengths of YYARG.  */
1476 |   YYPTRDIFF_T yysize = 0;
1477 | 
1478 |   /* Actual size of YYARG. */
1479 |   int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
1480 |   if (yycount == YYENOMEM)
1481 |     return YYENOMEM;
1482 | 
1483 |   switch (yycount)
1484 |     {
1485 | #define YYCASE_(N, S)                       \
1486 |       case N:                               \
1487 |         yyformat = S;                       \
1488 |         break
1489 |     default: /* Avoid compiler warnings. */
1490 |       YYCASE_(0, YY_("syntax error"));
1491 |       YYCASE_(1, YY_("syntax error, unexpected %s"));
1492 |       YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
1493 |       YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
1494 |       YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
1495 |       YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
1496 | #undef YYCASE_
1497 |     }
1498 | 
1499 |   /* Compute error message size.  Don't count the "%s"s, but reserve
1500 |      room for the terminator.  */
1501 |   yysize = yystrlen (yyformat) - 2 * yycount + 1;
1502 |   {
1503 |     int yyi;
1504 |     for (yyi = 0; yyi < yycount; ++yyi)
1505 |       {
1506 |         YYPTRDIFF_T yysize1
1507 |           = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
1508 |         if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
1509 |           yysize = yysize1;
1510 |         else
1511 |           return YYENOMEM;
1512 |       }
1513 |   }
1514 | 
1515 |   if (*yymsg_alloc < yysize)
1516 |     {
1517 |       *yymsg_alloc = 2 * yysize;
1518 |       if (! (yysize <= *yymsg_alloc
1519 |              && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
1520 |         *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
1521 |       return -1;
1522 |     }
1523 | 
1524 |   /* Avoid sprintf, as that infringes on the user's name space.
1525 |      Don't have undefined behavior even if the translation
1526 |      produced a string with the wrong number of "%s"s.  */
1527 |   {
1528 |     char *yyp = *yymsg;
1529 |     int yyi = 0;
1530 |     while ((*yyp = *yyformat) != '\0')
1531 |       if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
1532 |         {
1533 |           yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
1534 |           yyformat += 2;
1535 |         }
1536 |       else
1537 |         {
1538 |           ++yyp;
1539 |           ++yyformat;
1540 |         }
1541 |   }
1542 |   return 0;
1543 | }
1544 | 
1545 | 
1546 | /*-----------------------------------------------.
1547 | | Release the memory associated to this symbol.  |
1548 | `-----------------------------------------------*/
1549 | 
1550 | static void
1551 | yydestruct (const char *yymsg,
1552 |             yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
1553 | {
1554 |   YY_USE (yyvaluep);
1555 |   if (!yymsg)
1556 |     yymsg = "Deleting";
1557 |   YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);
1558 | 
1559 |   YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
1560 |   YY_USE (yykind);
1561 |   YY_IGNORE_MAYBE_UNINITIALIZED_END
1562 | }
1563 | 
1564 | 
1565 | /* Lookahead token kind.  */
1566 | int yychar;
1567 | 
1568 | /* The semantic value of the lookahead symbol.  */
1569 | YYSTYPE yylval;
1570 | /* Number of syntax errors so far.  */
1571 | int yynerrs;
1572 | 
1573 | 
1574 | 
1575 | 
1576 | /*----------.
1577 | | yyparse.  |
1578 | `----------*/
1579 | 
1580 | int
1581 | yyparse (void)
1582 | {
1583 |     yy_state_fast_t yystate = 0;
1584 |     /* Number of tokens to shift before error messages enabled.  */
1585 |     int yyerrstatus = 0;
1586 | 
1587 |     /* Refer to the stacks through separate pointers, to allow yyoverflow
1588 |        to reallocate them elsewhere.  */
1589 | 
1590 |     /* Their size.  */
1591 |     YYPTRDIFF_T yystacksize = YYINITDEPTH;
1592 | 
1593 |     /* The state stack: array, bottom, top.  */
1594 |     yy_state_t yyssa[YYINITDEPTH];
1595 |     yy_state_t *yyss = yyssa;
1596 |     yy_state_t *yyssp = yyss;
1597 | 
1598 |     /* The semantic value stack: array, bottom, top.  */
1599 |     YYSTYPE yyvsa[YYINITDEPTH];
1600 |     YYSTYPE *yyvs = yyvsa;
1601 |     YYSTYPE *yyvsp = yyvs;
1602 | 
1603 |   int yyn;
1604 |   /* The return value of yyparse.  */
1605 |   int yyresult;
1606 |   /* Lookahead symbol kind.  */
1607 |   yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
1608 |   /* The variables used to return semantic value and location from the
1609 |      action routines.  */
1610 |   YYSTYPE yyval;
1611 | 
1612 |   /* Buffer for error messages, and its allocated size.  */
1613 |   char yymsgbuf[128];
1614 |   char *yymsg = yymsgbuf;
1615 |   YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
1616 | 
1617 | #define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))
1618 | 
1619 |   /* The number of symbols on the RHS of the reduced rule.
1620 |      Keep to zero when no symbol should be popped.  */
1621 |   int yylen = 0;
1622 | 
1623 |   YYDPRINTF ((stderr, "Starting parse\n"));
1624 | 
1625 |   yychar = YYEMPTY; /* Cause a token to be read.  */
1626 | 
1627 |   goto yysetstate;
1628 | 
1629 | 
1630 | /*------------------------------------------------------------.
1631 | | yynewstate -- push a new state, which is found in yystate.  |
1632 | `------------------------------------------------------------*/
1633 | yynewstate:
1634 |   /* In all cases, when you get here, the value and location stacks
1635 |      have just been pushed.  So pushing a state here evens the stacks.  */
1636 |   yyssp++;
1637 | 
1638 | 
1639 | /*--------------------------------------------------------------------.
1640 | | yysetstate -- set current state (the top of the stack) to yystate.  |
1641 | `--------------------------------------------------------------------*/
1642 | yysetstate:
1643 |   YYDPRINTF ((stderr, "Entering state %d\n", yystate));
1644 |   YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
1645 |   YY_IGNORE_USELESS_CAST_BEGIN
1646 |   *yyssp = YY_CAST (yy_state_t, yystate);
1647 |   YY_IGNORE_USELESS_CAST_END
1648 |   YY_STACK_PRINT (yyss, yyssp);
1649 | 
1650 |   if (yyss + yystacksize - 1 <= yyssp)
1651 | #if !defined yyoverflow && !defined YYSTACK_RELOCATE
1652 |     YYNOMEM;
1653 | #else
1654 |     {
1655 |       /* Get the current used size of the three stacks, in elements.  */
1656 |       YYPTRDIFF_T yysize = yyssp - yyss + 1;
1657 | 
1658 | # if defined yyoverflow
1659 |       {
1660 |         /* Give user a chance to reallocate the stack.  Use copies of
1661 |            these so that the &'s don't force the real ones into
1662 |            memory.  */
1663 |         yy_state_t *yyss1 = yyss;
1664 |         YYSTYPE *yyvs1 = yyvs;
1665 | 
1666 |         /* Each stack pointer address is followed by the size of the
1667 |            data in use in that stack, in bytes.  This used to be a
1668 |            conditional around just the two extra args, but that might
1669 |            be undefined if yyoverflow is a macro.  */
1670 |         yyoverflow (YY_("memory exhausted"),
1671 |                     &yyss1, yysize * YYSIZEOF (*yyssp),
1672 |                     &yyvs1, yysize * YYSIZEOF (*yyvsp),
1673 |                     &yystacksize);
1674 |         yyss = yyss1;
1675 |         yyvs = yyvs1;
1676 |       }
1677 | # else /* defined YYSTACK_RELOCATE */
1678 |       /* Extend the stack our own way.  */
1679 |       if (YYMAXDEPTH <= yystacksize)
1680 |         YYNOMEM;
1681 |       yystacksize *= 2;
1682 |       if (YYMAXDEPTH < yystacksize)
1683 |         yystacksize = YYMAXDEPTH;
1684 | 
1685 |       {
1686 |         yy_state_t *yyss1 = yyss;
1687 |         union yyalloc *yyptr =
1688 |           YY_CAST (union yyalloc *,
1689 |                    YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
1690 |         if (! yyptr)
1691 |           YYNOMEM;
1692 |         YYSTACK_RELOCATE (yyss_alloc, yyss);
1693 |         YYSTACK_RELOCATE (yyvs_alloc, yyvs);
1694 | #  undef YYSTACK_RELOCATE
1695 |         if (yyss1 != yyssa)
1696 |           YYSTACK_FREE (yyss1);
1697 |       }
1698 | # endif
1699 | 
1700 |       yyssp = yyss + yysize - 1;
1701 |       yyvsp = yyvs + yysize - 1;
1702 | 
1703 |       YY_IGNORE_USELESS_CAST_BEGIN
1704 |       YYDPRINTF ((stderr, "Stack size increased to %ld\n",
1705 |                   YY_CAST (long, yystacksize)));
1706 |       YY_IGNORE_USELESS_CAST_END
1707 | 
1708 |       if (yyss + yystacksize - 1 <= yyssp)
1709 |         YYABORT;
1710 |     }
1711 | #endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */
1712 | 
1713 | 
1714 |   if (yystate == YYFINAL)
1715 |     YYACCEPT;
1716 | 
1717 |   goto yybackup;
1718 | 
1719 | 
1720 | /*-----------.
1721 | | yybackup.  |
1722 | `-----------*/
1723 | yybackup:
1724 |   /* Do appropriate processing given the current state.  Read a
1725 |      lookahead token if we need one and don't already have one.  */
1726 | 
1727 |   /* First try to decide what to do without reference to lookahead token.  */
1728 |   yyn = yypact[yystate];
1729 |   if (yypact_value_is_default (yyn))
1730 |     goto yydefault;
1731 | 
1732 |   /* Not known => get a lookahead token if don't already have one.  */
1733 | 
1734 |   /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
1735 |   if (yychar == YYEMPTY)
1736 |     {
1737 |       YYDPRINTF ((stderr, "Reading a token\n"));
1738 |       yychar = yylex ();
1739 |     }
1740 | 
1741 |   if (yychar <= YYEOF)
1742 |     {
1743 |       yychar = YYEOF;
1744 |       yytoken = YYSYMBOL_YYEOF;
1745 |       YYDPRINTF ((stderr, "Now at end of input.\n"));
1746 |     }
1747 |   else if (yychar == YYerror)
1748 |     {
1749 |       /* The scanner already issued an error message, process directly
1750 |          to error recovery.  But do not keep the error token as
1751 |          lookahead, it is too special and may lead us to an endless
1752 |          loop in error recovery. */
1753 |       yychar = YYUNDEF;
1754 |       yytoken = YYSYMBOL_YYerror;
1755 |       goto yyerrlab1;
1756 |     }
1757 |   else
1758 |     {
1759 |       yytoken = YYTRANSLATE (yychar);
1760 |       YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
1761 |     }
1762 | 
1763 |   /* If the proper action on seeing token YYTOKEN is to reduce or to
1764 |      detect an error, take that action.  */
1765 |   yyn += yytoken;
1766 |   if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
1767 |     goto yydefault;
1768 |   yyn = yytable[yyn];
1769 |   if (yyn <= 0)
1770 |     {
1771 |       if (yytable_value_is_error (yyn))
1772 |         goto yyerrlab;
1773 |       yyn = -yyn;
1774 |       goto yyreduce;
1775 |     }
1776 | 
1777 |   /* Count tokens shifted since error; after three, turn off error
1778 |      status.  */
1779 |   if (yyerrstatus)
1780 |     yyerrstatus--;
1781 | 
1782 |   /* Shift the lookahead token.  */
1783 |   YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
1784 |   yystate = yyn;
1785 |   YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
1786 |   *++yyvsp = yylval;
1787 |   YY_IGNORE_MAYBE_UNINITIALIZED_END
1788 | 
1789 |   /* Discard the shifted token.  */
1790 |   yychar = YYEMPTY;
1791 |   goto yynewstate;
1792 | 
1793 | 
1794 | /*-----------------------------------------------------------.
1795 | | yydefault -- do the default action for the current state.  |
1796 | `-----------------------------------------------------------*/
1797 | yydefault:
1798 |   yyn = yydefact[yystate];
1799 |   if (yyn == 0)
1800 |     goto yyerrlab;
1801 |   goto yyreduce;
1802 | 
1803 | 
1804 | /*-----------------------------.
1805 | | yyreduce -- do a reduction.  |
1806 | `-----------------------------*/
1807 | yyreduce:
1808 |   /* yyn is the number of a rule to reduce with.  */
1809 |   yylen = yyr2[yyn];
1810 | 
1811 |   /* If YYLEN is nonzero, implement the default value of the action:
1812 |      '$$ = $1'.
1813 | 
1814 |      Otherwise, the following line sets YYVAL to garbage.
1815 |      This behavior is undocumented and Bison
1816 |      users should not rely upon it.  Assigning to YYVAL
1817 |      unconditionally makes the parser a bit smaller, and it avoids a
1818 |      GCC warning that YYVAL may be used uninitialized.  */
1819 |   yyval = yyvsp[1-yylen];
1820 | 
1821 | 
1822 |   YY_REDUCE_PRINT (yyn);
1823 |   switch (yyn)
1824 |     {
1825 |   case 2: /* form: FORM IDENTIFIER '{' form_body '}'  */
1826 | #line 243 "parser.y"
1827 |     {
1828 |         current_form = create_form((yyvsp[-3].str));
1829 |         if (!current_form) {
1830 |             yyerror("Failed to create form");
1831 |             YYERROR;
1832 |         }
1833 |         generate_html(stdout);
1834 |         (yyval.form) = current_form;
1835 |     }
1836 | #line 1837 "y.tab.c"
1837 |     break;
1838 | 
1839 |   case 8: /* $@1: %empty  */
1840 | #line 268 "parser.y"
1841 |                                 { current_section = create_section((yyvsp[-1].str)); }
1842 | #line 1843 "y.tab.c"
1843 |     break;
1844 | 
1845 |   case 9: /* section: SECTION IDENTIFIER '{' $@1 field_list '}'  */
1846 | #line 268 "parser.y"
1847 |                                                                                          { add_section_to_form(current_form, current_section); current_section = NULL; }
1848 | #line 1849 "y.tab.c"
1849 |     break;
1850 | 
1851 |   case 10: /* section: SECTION IDENTIFIER '{' '}'  */
1852 | #line 270 "parser.y"
1853 |     {
1854 |         current_section = NULL;
1855 |     }
1856 | #line 1857 "y.tab.c"
1857 |     break;
1858 | 
1859 |   case 11: /* section: SECTION IDENTIFIER error '}'  */
1860 | #line 274 "parser.y"
1861 |     {
1862 |         yyerror("Invalid section declaration");
1863 |         current_section = NULL;
1864 |         yyclearin;
1865 |         yyerrok;
1866 |     }
1867 | #line 1868 "y.tab.c"
1868 |     break;
1869 | 
1870 |   case 14: /* field_list: field_list error ';'  */
1871 | #line 300 "parser.y"
1872 |     {
1873 |         yyerror("Invalid field declaration");
1874 |         yyclearin;
1875 |         yyerrok;
1876 |     }
1877 | #line 1878 "y.tab.c"
1878 |     break;
1879 | 
1880 |   case 15: /* field_declaration: FIELD IDENTIFIER ':' field_type '{' field_attributes '}'  */
1881 | #line 308 "parser.y"
1882 |     {
1883 |         if (current_section == NULL) {
1884 |             yyerror("Field must be inside a section");
1885 |             YYERROR;
1886 |         }
1887 |         if (check_duplicate_field((yyvsp[-5].str))) {
1888 |             yyerror("Duplicate field name found");
1889 |             YYERROR;
1890 |         }
1891 |         add_field_to_section(current_section, (yyvsp[-5].str), (yyvsp[-3].field_type), &(yyvsp[-1].field_attrs));
1892 |         free((yyvsp[-5].str)); // Free the field name
1893 |     }
1894 | #line 1895 "y.tab.c"
1895 |     break;
1896 | 
1897 |   case 16: /* field_type: TEXT  */
1898 | #line 322 "parser.y"
1899 |                      { (yyval.field_type) = FIELD_TEXT; }
1900 | #line 1901 "y.tab.c"
1901 |     break;
1902 | 
1903 |   case 17: /* field_type: EMAIL  */
1904 | #line 323 "parser.y"
1905 |                      { (yyval.field_type) = FIELD_EMAIL; }
1906 | #line 1907 "y.tab.c"
1907 |     break;
1908 | 
1909 |   case 18: /* field_type: PASSWORD  */
1910 | #line 324 "parser.y"
1911 |                      { (yyval.field_type) = FIELD_PASSWORD; }
1912 | #line 1913 "y.tab.c"
1913 |     break;
1914 | 
1915 |   case 19: /* field_type: NUMBER  */
1916 | #line 325 "parser.y"
1917 |                      { (yyval.field_type) = FIELD_NUMBER; }
1918 | #line 1919 "y.tab.c"
1919 |     break;
1920 | 
1921 |   case 20: /* field_type: TEXTAREA  */
1922 | #line 326 "parser.y"
1923 |                      { (yyval.field_type) = FIELD_TEXTAREA; }
1924 | #line 1925 "y.tab.c"
1925 |     break;
1926 | 
1927 |   case 21: /* field_type: DATE  */
1928 | #line 327 "parser.y"
1929 |                      { (yyval.field_type) = FIELD_DATE; }
1930 | #line 1931 "y.tab.c"
1931 |     break;
1932 | 
1933 |   case 22: /* field_type: CHECKBOX  */
1934 | #line 328 "parser.y"
1935 |                      { (yyval.field_type) = FIELD_CHECKBOX; }
1936 | #line 1937 "y.tab.c"
1937 |     break;
1938 | 
1939 |   case 23: /* field_type: DROPDOWN  */
1940 | #line 329 "parser.y"
1941 |                      { (yyval.field_type) = FIELD_DROPDOWN; }
1942 | #line 1943 "y.tab.c"
1943 |     break;
1944 | 
1945 |   case 24: /* field_type: RADIO  */
1946 | #line 330 "parser.y"
1947 |                      { (yyval.field_type) = FIELD_RADIO; }
1948 | #line 1949 "y.tab.c"
1949 |     break;
1950 | 
1951 |   case 25: /* field_type: FILE_TYPE  */
1952 | #line 331 "parser.y"
1953 |                       { (yyval.field_type) = FIELD_FILE; }
1954 | #line 1955 "y.tab.c"
1955 |     break;
1956 | 
1957 |   case 26: /* field_type: USERNAME  */
1958 | #line 332 "parser.y"
1959 |                      { (yyval.field_type) = FIELD_USERNAME; }
1960 | #line 1961 "y.tab.c"
1961 |     break;
1962 | 
1963 |   case 27: /* field_type: ADDRESS  */
1964 | #line 333 "parser.y"
1965 |                      { (yyval.field_type) = FIELD_ADDRESS; }
1966 | #line 1967 "y.tab.c"
1967 |     break;
1968 | 
1969 |   case 28: /* field_attributes: %empty  */
1970 | #line 337 "parser.y"
1971 |                   { init_field_attributes(&(yyval.field_attrs)); }
1972 | #line 1973 "y.tab.c"
1973 |     break;
1974 | 
1975 |   case 29: /* field_attributes: field_attributes attribute_opt_semicolon  */
1976 | #line 338 "parser.y"
1977 |                                                { (yyval.field_attrs) = (yyvsp[-1].field_attrs); merge_field_attributes(&(yyval.field_attrs), &(yyvsp[0].field_attrs)); }
1978 | #line 1979 "y.tab.c"
1979 |     break;
1980 | 
1981 |   case 30: /* attribute_opt_semicolon: attribute ';'  */
1982 | #line 342 "parser.y"
1983 |                     { (yyval.field_attrs) = (yyvsp[-1].field_attrs); }
1984 | #line 1985 "y.tab.c"
1985 |     break;
1986 | 
1987 |   case 31: /* attribute_opt_semicolon: attribute  */
1988 | #line 343 "parser.y"
1989 |                     { (yyval.field_attrs) = (yyvsp[0].field_attrs); }
1990 | #line 1991 "y.tab.c"
1991 |     break;
1992 | 
1993 |   case 32: /* attribute: REQUIRED  */
1994 | #line 347 "parser.y"
1995 |                   { FieldAttributes tmp; init_field_attributes(&tmp); tmp.required = 1; (yyval.field_attrs) = tmp; }
1996 | #line 1997 "y.tab.c"
1997 |     break;
1998 | 
1999 |   case 33: /* attribute: OPTIONAL  */
2000 | #line 348 "parser.y"
2001 |                   { FieldAttributes tmp; init_field_attributes(&tmp); tmp.required = 0; (yyval.field_attrs) = tmp; }
2002 | #line 2003 "y.tab.c"
2003 |     break;
2004 | 
2005 |   case 34: /* attribute: MINLENGTH '=' NUMBER_LITERAL  */
2006 | #line 349 "parser.y"
2007 |                                    { FieldAttributes tmp; init_field_attributes(&tmp); tmp.min_length = (yyvsp[0].num); (yyval.field_attrs) = tmp; }
2008 | #line 2009 "y.tab.c"
2009 |     break;
2010 | 
2011 |   case 35: /* attribute: MAXLENGTH '=' NUMBER_LITERAL  */
2012 | #line 350 "parser.y"
2013 |                                    { FieldAttributes tmp; init_field_attributes(&tmp); tmp.max_length = (yyvsp[0].num); (yyval.field_attrs) = tmp; }
2014 | #line 2015 "y.tab.c"
2015 |     break;
2016 | 
2017 |   case 36: /* attribute: MIN '=' NUMBER_LITERAL  */
2018 | #line 351 "parser.y"
2019 |                              { FieldAttributes tmp; init_field_attributes(&tmp); tmp.min_value = (yyvsp[0].num); (yyval.field_attrs) = tmp; }
2020 | #line 2021 "y.tab.c"
2021 |     break;
2022 | 
2023 |   case 37: /* attribute: MAX '=' NUMBER_LITERAL  */
2024 | #line 352 "parser.y"
2025 |                              { FieldAttributes tmp; init_field_attributes(&tmp); tmp.max_value = (yyvsp[0].num); (yyval.field_attrs) = tmp; }
2026 | #line 2027 "y.tab.c"
2027 |     break;
2028 | 
2029 |   case 38: /* attribute: ROWS '=' NUMBER_LITERAL  */
2030 | #line 353 "parser.y"
2031 |                               { FieldAttributes tmp; init_field_attributes(&tmp); tmp.rows = (yyvsp[0].num); (yyval.field_attrs) = tmp; }
2032 | #line 2033 "y.tab.c"
2033 |     break;
2034 | 
2035 |   case 39: /* attribute: COLS '=' NUMBER_LITERAL  */
2036 | #line 354 "parser.y"
2037 |                               { FieldAttributes tmp; init_field_attributes(&tmp); tmp.cols = (yyvsp[0].num); (yyval.field_attrs) = tmp; }
2038 | #line 2039 "y.tab.c"
2039 |     break;
2040 | 
2041 |   case 40: /* attribute: PATTERN '=' STRING_LITERAL  */
2042 | #line 355 "parser.y"
2043 |                                  { FieldAttributes tmp; init_field_attributes(&tmp); tmp.pattern = (yyvsp[0].str); (yyval.field_attrs) = tmp; }
2044 | #line 2045 "y.tab.c"
2045 |     break;
2046 | 
2047 |   case 41: /* attribute: DEFAULT '=' STRING_LITERAL  */
2048 | #line 356 "parser.y"
2049 |                                  { FieldAttributes tmp; init_field_attributes(&tmp); tmp.default_value = (yyvsp[0].str); (yyval.field_attrs) = tmp; }
2050 | #line 2051 "y.tab.c"
2051 |     break;
2052 | 
2053 |   case 42: /* attribute: DEFAULT '=' IDENTIFIER  */
2054 | #line 357 "parser.y"
2055 |                              { FieldAttributes tmp; init_field_attributes(&tmp); tmp.default_value = strdup((yyvsp[0].str)); (yyval.field_attrs) = tmp; }
2056 | #line 2057 "y.tab.c"
2057 |     break;
2058 | 
2059 |   case 43: /* attribute: STRENGTH '=' NUMBER_LITERAL  */
2060 | #line 358 "parser.y"
2061 |                                   { FieldAttributes tmp; init_field_attributes(&tmp); tmp.strength_required = (yyvsp[0].num); (yyval.field_attrs) = tmp; }
2062 | #line 2063 "y.tab.c"
2063 |     break;
2064 | 
2065 |   case 44: /* attribute: CONFIRM '=' IDENTIFIER  */
2066 | #line 359 "parser.y"
2067 |                              { FieldAttributes tmp; init_field_attributes(&tmp); tmp.confirm_field = (yyvsp[0].str); (yyval.field_attrs) = tmp; }
2068 | #line 2069 "y.tab.c"
2069 |     break;
2070 | 
2071 |   case 45: /* attribute: OPTIONS '=' '[' options_list ']'  */
2072 | #line 360 "parser.y"
2073 |                                        {
2074 |         FieldAttributes tmp;
2075 |         init_field_attributes(&tmp);
2076 |         tmp.options = (yyvsp[-1].str_list).arr;
2077 |         tmp.options_count = (yyvsp[-1].str_list).count;
2078 |         (yyval.field_attrs) = tmp;
2079 |     }
2080 | #line 2081 "y.tab.c"
2081 |     break;
2082 | 
2083 |   case 46: /* validation_block: VALIDATE '{' validation_rules '}'  */
2084 | #line 374 "parser.y"
2085 |     {
2086 |         // Validation block is already processed by the rules
2087 |     }
2088 | #line 2089 "y.tab.c"
2089 |     break;
2090 | 
2091 |   case 49: /* validation_rule: IF condition '{' ERROR STRING_LITERAL ';' '}'  */
2092 | #line 384 "parser.y"
2093 |     {
2094 |         ValidationRule* rule = malloc(sizeof(ValidationRule));
2095 |         if (!rule) {
2096 |             yyerror("Memory allocation failed for validation rule");
2097 |             YYERROR;
2098 |         }
2099 |         rule->condition = (yyvsp[-5].validation_rule);
2100 |         rule->error_message = (yyvsp[-2].str);
2101 |         rule->next = current_form->validation_rules;
2102 |         current_form->validation_rules = rule;
2103 |     }
2104 | #line 2105 "y.tab.c"
2105 |     break;
2106 | 
2107 |   case 50: /* condition: IDENTIFIER LT NUMBER_LITERAL  */
2108 | #line 398 "parser.y"
2109 |     {
2110 |         char* cond = malloc(50);
2111 |         sprintf(cond, "%s < %d", (yyvsp[-2].str), (yyvsp[0].num));
2112 |         (yyval.validation_rule) = cond;
2113 |     }
2114 | #line 2115 "y.tab.c"
2115 |     break;
2116 | 
2117 |   case 51: /* condition: IDENTIFIER GT NUMBER_LITERAL  */
2118 | #line 404 "parser.y"
2119 |     {
2120 |         char* cond = malloc(50);
2121 |         sprintf(cond, "%s > %d", (yyvsp[-2].str), (yyvsp[0].num));
2122 |         (yyval.validation_rule) = cond;
2123 |     }
2124 | #line 2125 "y.tab.c"
2125 |     break;
2126 | 
2127 |   case 52: /* condition: IDENTIFIER LTE NUMBER_LITERAL  */
2128 | #line 410 "parser.y"
2129 |     {
2130 |         char* cond = malloc(50);
2131 |         sprintf(cond, "%s <= %d", (yyvsp[-2].str), (yyvsp[0].num));
2132 |         (yyval.validation_rule) = cond;
2133 |     }
2134 | #line 2135 "y.tab.c"
2135 |     break;
2136 | 
2137 |   case 53: /* condition: IDENTIFIER GTE NUMBER_LITERAL  */
2138 | #line 416 "parser.y"
2139 |     {
2140 |         char* cond = malloc(50);
2141 |         sprintf(cond, "%s >= %d", (yyvsp[-2].str), (yyvsp[0].num));
2142 |         (yyval.validation_rule) = cond;
2143 |     }
2144 | #line 2145 "y.tab.c"
2145 |     break;
2146 | 
2147 |   case 54: /* condition: IDENTIFIER EQ NUMBER_LITERAL  */
2148 | #line 422 "parser.y"
2149 |     {
2150 |         char* cond = malloc(50);
2151 |         sprintf(cond, "%s == %d", (yyvsp[-2].str), (yyvsp[0].num));
2152 |         (yyval.validation_rule) = cond;
2153 |     }
2154 | #line 2155 "y.tab.c"
2155 |     break;
2156 | 
2157 |   case 55: /* condition: IDENTIFIER NEQ NUMBER_LITERAL  */
2158 | #line 428 "parser.y"
2159 |     {
2160 |         char* cond = malloc(50);
2161 |         sprintf(cond, "%s != %d", (yyvsp[-2].str), (yyvsp[0].num));
2162 |         (yyval.validation_rule) = cond;
2163 |     }
2164 | #line 2165 "y.tab.c"
2165 |     break;
2166 | 
2167 |   case 56: /* condition: IDENTIFIER EQ IDENTIFIER  */
2168 | #line 434 "parser.y"
2169 |     {
2170 |         char* cond = malloc(50);
2171 |         sprintf(cond, "%s == %s", (yyvsp[-2].str), (yyvsp[0].str));
2172 |         (yyval.validation_rule) = cond;
2173 |     }
2174 | #line 2175 "y.tab.c"
2175 |     break;
2176 | 
2177 |   case 57: /* metadata_declaration: META IDENTIFIER '=' STRING_LITERAL ';'  */
2178 | #line 442 "parser.y"
2179 |     {
2180 |         if (current_form) {
2181 |             add_metadata(current_form, (yyvsp[-3].str), (yyvsp[-1].str));
2182 |         }
2183 |     }
2184 | #line 2185 "y.tab.c"
2185 |     break;
2186 | 
2187 |   case 58: /* options_list: STRING_LITERAL  */
2188 | #line 450 "parser.y"
2189 |                      { (yyval.str_list).arr = malloc(sizeof(char*)); (yyval.str_list).arr[0] = strdup((yyvsp[0].str)); (yyval.str_list).count = 1; }
2190 | #line 2191 "y.tab.c"
2191 |     break;
2192 | 
2193 |   case 59: /* options_list: options_list ',' STRING_LITERAL  */
2194 | #line 451 "parser.y"
2195 |                                       {
2196 |         (yyval.str_list).arr = realloc((yyvsp[-2].str_list).arr, ((yyvsp[-2].str_list).count + 1) * sizeof(char*));
2197 |         (yyval.str_list).arr[(yyvsp[-2].str_list).count] = strdup((yyvsp[0].str));
2198 |         (yyval.str_list).count = (yyvsp[-2].str_list).count + 1;
2199 |     }
2200 | #line 2201 "y.tab.c"
2201 |     break;
2202 | 
2203 | 
2204 | #line 2205 "y.tab.c"
2205 | 
2206 |       default: break;
2207 |     }
2208 |   /* User semantic actions sometimes alter yychar, and that requires
2209 |      that yytoken be updated with the new translation.  We take the
2210 |      approach of translating immediately before every use of yytoken.
2211 |      One alternative is translating here after every semantic action,
2212 |      but that translation would be missed if the semantic action invokes
2213 |      YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
2214 |      if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
2215 |      incorrect destructor might then be invoked immediately.  In the
2216 |      case of YYERROR or YYBACKUP, subsequent parser actions might lead
2217 |      to an incorrect destructor call or verbose syntax error message
2218 |      before the lookahead is translated.  */
2219 |   YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);
2220 | 
2221 |   YYPOPSTACK (yylen);
2222 |   yylen = 0;
2223 | 
2224 |   *++yyvsp = yyval;
2225 | 
2226 |   /* Now 'shift' the result of the reduction.  Determine what state
2227 |      that goes to, based on the state we popped back to and the rule
2228 |      number reduced by.  */
2229 |   {
2230 |     const int yylhs = yyr1[yyn] - YYNTOKENS;
2231 |     const int yyi = yypgoto[yylhs] + *yyssp;
2232 |     yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
2233 |                ? yytable[yyi]
2234 |                : yydefgoto[yylhs]);
2235 |   }
2236 | 
2237 |   goto yynewstate;
2238 | 
2239 | 
2240 | /*--------------------------------------.
2241 | | yyerrlab -- here on detecting error.  |
2242 | `--------------------------------------*/
2243 | yyerrlab:
2244 |   /* Make sure we have latest lookahead translation.  See comments at
2245 |      user semantic actions for why this is necessary.  */
2246 |   yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
2247 |   /* If not already recovering from an error, report this error.  */
2248 |   if (!yyerrstatus)
2249 |     {
2250 |       ++yynerrs;
2251 |       {
2252 |         yypcontext_t yyctx
2253 |           = {yyssp, yytoken};
2254 |         char const *yymsgp = YY_("syntax error");
2255 |         int yysyntax_error_status;
2256 |         yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
2257 |         if (yysyntax_error_status == 0)
2258 |           yymsgp = yymsg;
2259 |         else if (yysyntax_error_status == -1)
2260 |           {
2261 |             if (yymsg != yymsgbuf)
2262 |               YYSTACK_FREE (yymsg);
2263 |             yymsg = YY_CAST (char *,
2264 |                              YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
2265 |             if (yymsg)
2266 |               {
2267 |                 yysyntax_error_status
2268 |                   = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
2269 |                 yymsgp = yymsg;
2270 |               }
2271 |             else
2272 |               {
2273 |                 yymsg = yymsgbuf;
2274 |                 yymsg_alloc = sizeof yymsgbuf;
2275 |                 yysyntax_error_status = YYENOMEM;
2276 |               }
2277 |           }
2278 |         yyerror (yymsgp);
2279 |         if (yysyntax_error_status == YYENOMEM)
2280 |           YYNOMEM;
2281 |       }
2282 |     }
2283 | 
2284 |   if (yyerrstatus == 3)
2285 |     {
2286 |       /* If just tried and failed to reuse lookahead token after an
2287 |          error, discard it.  */
2288 | 
2289 |       if (yychar <= YYEOF)
2290 |         {
2291 |           /* Return failure if at end of input.  */
2292 |           if (yychar == YYEOF)
2293 |             YYABORT;
2294 |         }
2295 |       else
2296 |         {
2297 |           yydestruct ("Error: discarding",
2298 |                       yytoken, &yylval);
2299 |           yychar = YYEMPTY;
2300 |         }
2301 |     }
2302 | 
2303 |   /* Else will try to reuse lookahead token after shifting the error
2304 |      token.  */
2305 |   goto yyerrlab1;
2306 | 
2307 | 
2308 | /*---------------------------------------------------.
2309 | | yyerrorlab -- error raised explicitly by YYERROR.  |
2310 | `---------------------------------------------------*/
2311 | yyerrorlab:
2312 |   /* Pacify compilers when the user code never invokes YYERROR and the
2313 |      label yyerrorlab therefore never appears in user code.  */
2314 |   if (0)
2315 |     YYERROR;
2316 |   ++yynerrs;
2317 | 
2318 |   /* Do not reclaim the symbols of the rule whose action triggered
2319 |      this YYERROR.  */
2320 |   YYPOPSTACK (yylen);
2321 |   yylen = 0;
2322 |   YY_STACK_PRINT (yyss, yyssp);
2323 |   yystate = *yyssp;
2324 |   goto yyerrlab1;
2325 | 
2326 | 
2327 | /*-------------------------------------------------------------.
2328 | | yyerrlab1 -- common code for both syntax error and YYERROR.  |
2329 | `-------------------------------------------------------------*/
2330 | yyerrlab1:
2331 |   yyerrstatus = 3;      /* Each real token shifted decrements this.  */
2332 | 
2333 |   /* Pop stack until we find a state that shifts the error token.  */
2334 |   for (;;)
2335 |     {
2336 |       yyn = yypact[yystate];
2337 |       if (!yypact_value_is_default (yyn))
2338 |         {
2339 |           yyn += YYSYMBOL_YYerror;
2340 |           if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
2341 |             {
2342 |               yyn = yytable[yyn];
2343 |               if (0 < yyn)
2344 |                 break;
2345 |             }
2346 |         }
2347 | 
2348 |       /* Pop the current state because it cannot handle the error token.  */
2349 |       if (yyssp == yyss)
2350 |         YYABORT;
2351 | 
2352 | 
2353 |       yydestruct ("Error: popping",
2354 |                   YY_ACCESSING_SYMBOL (yystate), yyvsp);
2355 |       YYPOPSTACK (1);
2356 |       yystate = *yyssp;
2357 |       YY_STACK_PRINT (yyss, yyssp);
2358 |     }
2359 | 
2360 |   YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
2361 |   *++yyvsp = yylval;
2362 |   YY_IGNORE_MAYBE_UNINITIALIZED_END
2363 | 
2364 | 
2365 |   /* Shift the error token.  */
2366 |   YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);
2367 | 
2368 |   yystate = yyn;
2369 |   goto yynewstate;
2370 | 
2371 | 
2372 | /*-------------------------------------.
2373 | | yyacceptlab -- YYACCEPT comes here.  |
2374 | `-------------------------------------*/
2375 | yyacceptlab:
2376 |   yyresult = 0;
2377 |   goto yyreturnlab;
2378 | 
2379 | 
2380 | /*-----------------------------------.
2381 | | yyabortlab -- YYABORT comes here.  |
2382 | `-----------------------------------*/
2383 | yyabortlab:
2384 |   yyresult = 1;
2385 |   goto yyreturnlab;
2386 | 
2387 | 
2388 | /*-----------------------------------------------------------.
2389 | | yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
2390 | `-----------------------------------------------------------*/
2391 | yyexhaustedlab:
2392 |   yyerror (YY_("memory exhausted"));
2393 |   yyresult = 2;
2394 |   goto yyreturnlab;
2395 | 
2396 | 
2397 | /*----------------------------------------------------------.
2398 | | yyreturnlab -- parsing is finished, clean up and return.  |
2399 | `----------------------------------------------------------*/
2400 | yyreturnlab:
2401 |   if (yychar != YYEMPTY)
2402 |     {
2403 |       /* Make sure we have latest lookahead translation.  See comments at
2404 |          user semantic actions for why this is necessary.  */
2405 |       yytoken = YYTRANSLATE (yychar);
2406 |       yydestruct ("Cleanup: discarding lookahead",
2407 |                   yytoken, &yylval);
2408 |     }
2409 |   /* Do not reclaim the symbols of the rule whose action triggered
2410 |      this YYABORT or YYACCEPT.  */
2411 |   YYPOPSTACK (yylen);
2412 |   YY_STACK_PRINT (yyss, yyssp);
2413 |   while (yyssp != yyss)
2414 |     {
2415 |       yydestruct ("Cleanup: popping",
2416 |                   YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
2417 |       YYPOPSTACK (1);
2418 |     }
2419 | #ifndef yyoverflow
2420 |   if (yyss != yyssa)
2421 |     YYSTACK_FREE (yyss);
2422 | #endif
2423 |   if (yymsg != yymsgbuf)
2424 |     YYSTACK_FREE (yymsg);
2425 |   return yyresult;
2426 | }
2427 | 
2428 | #line 458 "parser.y"
2429 | 
2430 | 
2431 | void yyerror(const char *s) {
2432 |     fprintf(stderr, "Parser Error: %s at line %d\n", s, yylineno);
2433 | }
2434 | 
2435 | int main(int argc, char **argv) {
2436 |     if (argc > 1) {
2437 |         FILE *file = fopen(argv[1], "r");
2438 |         if (!file) {
2439 |             perror(argv[1]);
2440 |             return 1;
2441 |         }
2442 |         yyin = file;
2443 |     }
2444 |     yyparse();
2445 |     cleanup_form(current_form);
2446 |     return 0;
2447 | }
2448 | 
2449 | int yywrap() {
2450 |     return 1;
2451 | }
```

src/y.tab.h
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
70 |     USERNAME = 271,                /* USERNAME  */
71 |     ADDRESS = 272,                 /* ADDRESS  */
72 |     REQUIRED = 273,                /* REQUIRED  */
73 |     OPTIONAL = 274,                /* OPTIONAL  */
74 |     MINLENGTH = 275,               /* MINLENGTH  */
75 |     MAXLENGTH = 276,               /* MAXLENGTH  */
76 |     MIN = 277,                     /* MIN  */
77 |     MAX = 278,                     /* MAX  */
78 |     ROWS = 279,                    /* ROWS  */
79 |     COLS = 280,                    /* COLS  */
80 |     PATTERN = 281,                 /* PATTERN  */
81 |     DEFAULT = 282,                 /* DEFAULT  */
82 |     CONFIRM = 283,                 /* CONFIRM  */
83 |     STRENGTH = 284,                /* STRENGTH  */
84 |     META = 285,                    /* META  */
85 |     IDENTIFIER = 286,              /* IDENTIFIER  */
86 |     NUMBER_LITERAL = 287,          /* NUMBER_LITERAL  */
87 |     STRING_LITERAL = 288,          /* STRING_LITERAL  */
88 |     VALIDATE = 289,                /* VALIDATE  */
89 |     IF = 290,                      /* IF  */
90 |     ERROR = 291,                   /* ERROR  */
91 |     LT = 292,                      /* LT  */
92 |     GT = 293,                      /* GT  */
93 |     LTE = 294,                     /* LTE  */
94 |     GTE = 295,                     /* GTE  */
95 |     EQ = 296,                      /* EQ  */
96 |     NEQ = 297,                     /* NEQ  */
97 |     AND = 298,                     /* AND  */
98 |     OR = 299,                      /* OR  */
99 |     OPTIONS = 300                  /* OPTIONS  */
100 |   };
101 |   typedef enum yytokentype yytoken_kind_t;
102 | #endif
103 | /* Token kinds.  */
104 | #define YYEMPTY -2
105 | #define YYEOF 0
106 | #define YYerror 256
107 | #define YYUNDEF 257
108 | #define FORM 258
109 | #define SECTION 259
110 | #define FIELD 260
111 | #define TEXT 261
112 | #define EMAIL 262
113 | #define PASSWORD 263
114 | #define NUMBER 264
115 | #define TEXTAREA 265
116 | #define DATE 266
117 | #define CHECKBOX 267
118 | #define DROPDOWN 268
119 | #define RADIO 269
120 | #define FILE_TYPE 270
121 | #define USERNAME 271
122 | #define ADDRESS 272
123 | #define REQUIRED 273
124 | #define OPTIONAL 274
125 | #define MINLENGTH 275
126 | #define MAXLENGTH 276
127 | #define MIN 277
128 | #define MAX 278
129 | #define ROWS 279
130 | #define COLS 280
131 | #define PATTERN 281
132 | #define DEFAULT 282
133 | #define CONFIRM 283
134 | #define STRENGTH 284
135 | #define META 285
136 | #define IDENTIFIER 286
137 | #define NUMBER_LITERAL 287
138 | #define STRING_LITERAL 288
139 | #define VALIDATE 289
140 | #define IF 290
141 | #define ERROR 291
142 | #define LT 292
143 | #define GT 293
144 | #define LTE 294
145 | #define GTE 295
146 | #define EQ 296
147 | #define NEQ 297
148 | #define AND 298
149 | #define OR 299
150 | #define OPTIONS 300
151 | 
152 | /* Value type.  */
153 | #if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
154 | union YYSTYPE
155 | {
156 | #line 215 "parser.y"
157 | 
158 |     Form* form;
159 |     Section* section;
160 |     Field* field;
161 |     FieldAttributes field_attrs;
162 |     ValidationRule* validation_rule;
163 |     char* str;
164 |     int num;
165 |     FieldType field_type;
166 |     struct {
167 |         char** arr;
168 |         int count;
169 |     } str_list;
170 | 
171 | #line 172 "y.tab.h"
172 | 
173 | };
174 | typedef union YYSTYPE YYSTYPE;
175 | # define YYSTYPE_IS_TRIVIAL 1
176 | # define YYSTYPE_IS_DECLARED 1
177 | #endif
178 | 
179 | 
180 | extern YYSTYPE yylval;
181 | 
182 | 
183 | int yyparse (void);
184 | 
185 | 
186 | #endif /* !YY_YY_Y_TAB_H_INCLUDED  */
```

tests/test.sh
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
