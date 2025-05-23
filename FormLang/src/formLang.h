#ifndef FORMLANG_H
#define FORMLANG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Metadata structure
typedef struct Metadata {
    char* key;
    char* value;
    struct Metadata* next;
} Metadata;

// Validation structure
typedef struct ValidationRule {
    char* condition;
    char* error_message;
    struct ValidationRule* next;
} ValidationRule;

// Field type definitions
typedef enum {
    FIELD_TEXT,
    FIELD_EMAIL,
    FIELD_PASSWORD,
    FIELD_NUMBER,
    FIELD_TEXTAREA,
    FIELD_DATE,
    FIELD_CHECKBOX,
    FIELD_DROPDOWN,
    FIELD_RADIO,
    FIELD_FILE,
    FIELD_USERNAME,
    FIELD_ADDRESS
} FieldType;

// Address subfields
typedef struct {
    char* street;
    char* city;
    char* state;
    char* zip;
    char* country;
} AddressField;

// Field attribute structure
typedef struct {
    int min_length;
    int max_length;
    int min_value;
    int max_value;
    int rows;
    int cols;
    char* pattern;
    char* default_value;
    int required;
    char* confirm_field;
    int strength_required;
    AddressField* address;
} FieldAttributes;

// Structure definitions
typedef struct Field {
    char *name;
    FieldType type;
    FieldAttributes attributes;
} Field;

typedef struct Section {
    char *name;
    Field *fields;
    int field_count;
} Section;

typedef struct Form {
    char *name;
    Section **sections;
    int section_count;
    ValidationRule* validation_rules;
    Metadata* metadata;
} Form;

// External declarations
extern int yylineno;
extern int yylex(void);
extern int yyparse(void);
extern void yyerror(const char *s);
extern FILE* yyin;

// Global variables
extern Form *current_form;
extern Section *current_section;

// Function declarations
void generate_html(FILE* output);
void generate_html_header(FILE* output);
void generate_html_footer(FILE* output);
void generate_section_html(FILE* output, Section* section);
void generate_validation_js(FILE* output, Form* form);
void add_metadata(Form* form, const char* key, const char* value);
void cleanup_metadata(Metadata* metadata);

// Helper functions
Form* create_form(const char* name);
Section* create_section(const char* name);
void add_section_to_form(Form* form, Section* section);
void add_field_to_section(Section* section, const char* name, FieldType type, FieldAttributes* attrs);
void cleanup_form(Form* form);

#endif /* FORMLANG_H */
