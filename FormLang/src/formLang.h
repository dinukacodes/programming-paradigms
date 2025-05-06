#ifndef FORMLANG_H
#define FORMLANG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Type definitions
typedef struct {
    char *name;
    char *type;
    int required;
} Field;

typedef struct {
    char *name;
    Field *fields;
    int field_count;
} Section;

typedef struct {
    char *name;
    Section *sections;
    int section_count;
} Form;

// External declarations
extern int yylineno;
extern int yylex(void);
extern int yyparse(void);
extern void yyerror(const char *s);

// Global variables
extern Form current_form;
extern Section current_section;
extern Field current_field;

// Function declarations
void generate_html();
void init_form(const char *name);
void add_section(const char *name);
void add_field(const char *name, const char *type, int required);
void print_form();

#endif /* FORMLANG_H */
