%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formLang.h"

extern int yylex();
extern int yylineno;
void yyerror(const char *s);

// Global variables for current form and section
Form *current_form = NULL;
Section *current_section = NULL;

// Field name tracking for duplicate detection
typedef struct {
    char* name;
    int line;
} FieldName;

FieldName* field_names = NULL;
int field_name_count = 0;

// Helper functions
Form* create_form(const char* name) {
    Form* form = malloc(sizeof(Form));
    if (!form) return NULL;
    form->name = strdup(name);
    form->sections = NULL;
    form->section_count = 0;
    form->validation_rules = NULL;
    form->metadata = NULL;
    return form;
}

Section* create_section(const char* name) {
    Section* section = malloc(sizeof(Section));
    if (!section) return NULL;
    section->name = strdup(name);
    section->fields = NULL;
    section->field_count = 0;
    return section;
}

void add_section_to_form(Form* form, Section* section) {
    if (!form || !section) {
        fprintf(stderr, "Null form or section\n");
        return;
    }
    
    Section** new_sections = realloc(form->sections, (form->section_count + 1) * sizeof(Section*));
    if (!new_sections) {
        fprintf(stderr, "Memory allocation failed for sections\n");
        exit(1);
    }
    form->sections = new_sections;
    form->sections[form->section_count] = section;
    form->section_count++;
}

int check_duplicate_field(const char* name) {
    for (int i = 0; i < field_name_count; i++) {
        if (strcmp(field_names[i].name, name) == 0) {
            return 1;
        }
    }
    return 0;
}

void init_field_attributes(FieldAttributes* attrs) {
    if (!attrs) return;
    attrs->min_length = -1;
    attrs->max_length = -1;
    attrs->min_value = -1;
    attrs->max_value = -1;
    attrs->rows = -1;
    attrs->cols = -1;
    attrs->pattern = NULL;
    attrs->default_value = NULL;
    attrs->required = 0;
}

void add_field_to_section(Section* section, const char* name, FieldType type, FieldAttributes* attrs) {
    if (!section || !name || !attrs) {
        fprintf(stderr, "Null section, name, or attrs\n");
        return;
    }
    
    // Add field name to tracking
    field_name_count++;
    FieldName* new_field_names = realloc(field_names, field_name_count * sizeof(FieldName));
    if (!new_field_names) {
        fprintf(stderr, "Memory allocation failed for field names\n");
        exit(1);
    }
    field_names = new_field_names;
    field_names[field_name_count - 1].name = strdup(name);
    field_names[field_name_count - 1].line = yylineno;
    
    // Allocate memory for the new field
    Field* new_fields = realloc(section->fields, (section->field_count + 1) * sizeof(Field));
    if (!new_fields) {
        fprintf(stderr, "Memory allocation failed for fields\n");
        exit(1);
    }
    section->fields = new_fields;
    
    Field* field = &section->fields[section->field_count];
    field->name = strdup(name);
    field->type = type;
    init_field_attributes(&field->attributes);
    
    // Copy attributes
    field->attributes.min_length = attrs->min_length;
    field->attributes.max_length = attrs->max_length;
    field->attributes.min_value = attrs->min_value;
    field->attributes.max_value = attrs->max_value;
    field->attributes.rows = attrs->rows;
    field->attributes.cols = attrs->cols;
    field->attributes.required = attrs->required;
    
    if (attrs->pattern) {
        field->attributes.pattern = strdup(attrs->pattern);
    }
    if (attrs->default_value) {
        field->attributes.default_value = strdup(attrs->default_value);
    }
    
    section->field_count++;
}

void add_metadata(Form* form, const char* key, const char* value) {
    Metadata* meta = malloc(sizeof(Metadata));
    if (!meta) {
        fprintf(stderr, "Memory allocation failed for metadata\n");
        return;
    }
    meta->key = strdup(key);
    meta->value = strdup(value);
    meta->next = form->metadata;
    form->metadata = meta;
}

void cleanup_metadata(Metadata* metadata) {
    while (metadata) {
        Metadata* next = metadata->next;
        if (metadata->key) free(metadata->key);
        if (metadata->value) free(metadata->value);
        free(metadata);
        metadata = next;
    }
}

void cleanup_form(Form* form) {
    if (form) {
        for (int i = 0; i < form->section_count; i++) {
            Section* s = form->sections[i];
            if (s) {
                for (int j = 0; j < s->field_count; j++) {
                    Field* f = &s->fields[j];
                    if (f->name) free(f->name);
                    if (f->attributes.pattern) free(f->attributes.pattern);
                    if (f->attributes.default_value) free(f->attributes.default_value);
                }
                if (s->fields) free(s->fields);
                if (s->name) free(s->name);
                free(s);
            }
        }
        if (form->sections) free(form->sections);
        if (form->name) free(form->name);
        
        // Cleanup validation rules
        ValidationRule* rule = form->validation_rules;
        while (rule) {
            ValidationRule* next = rule->next;
            if (rule->condition) free(rule->condition);
            if (rule->error_message) free(rule->error_message);
            free(rule);
            rule = next;
        }
        
        // Cleanup metadata
        cleanup_metadata(form->metadata);
        
        free(form);
    }
    
    // Cleanup field name tracking
    for (int i = 0; i < field_name_count; i++) {
        if (field_names[i].name) free(field_names[i].name);
    }
    if (field_names) free(field_names);
    field_name_count = 0;
}

void merge_field_attributes(FieldAttributes* dest, FieldAttributes* src) {
    if (src->required != -1) dest->required = src->required;
    if (src->min_length != -1) dest->min_length = src->min_length;
    if (src->max_length != -1) dest->max_length = src->max_length;
    if (src->min_value != -1) dest->min_value = src->min_value;
    if (src->max_value != -1) dest->max_value = src->max_value;
    if (src->rows != -1) dest->rows = src->rows;
    if (src->cols != -1) dest->cols = src->cols;
    if (src->pattern) { if (dest->pattern) free(dest->pattern); dest->pattern = strdup(src->pattern); }
    if (src->default_value) { if (dest->default_value) free(dest->default_value); dest->default_value = strdup(src->default_value); }
}
%}

%token FORM SECTION FIELD TEXT EMAIL PASSWORD NUMBER TEXTAREA DATE CHECKBOX DROPDOWN RADIO FILE_TYPE USERNAME ADDRESS
%token REQUIRED OPTIONAL MINLENGTH MAXLENGTH MIN MAX ROWS COLS PATTERN DEFAULT CONFIRM STRENGTH META
%token IDENTIFIER NUMBER_LITERAL STRING_LITERAL
%token VALIDATE IF ERROR LT GT LTE GTE EQ NEQ AND OR

%union {
    char* str;
    int num;
    Form* form;
    Section* section;
    FieldType field_type;
    FieldAttributes field_attrs;
    ValidationRule* validation_rule;
}

%type <str> IDENTIFIER STRING_LITERAL
%type <num> NUMBER_LITERAL
%type <form> form
%type <field_type> field_type
%type <field_attrs> field_attributes attribute attribute_opt_semicolon
%type <validation_rule> validation_block validation_rule condition

%define parse.error verbose

%%

form: FORM IDENTIFIER '{' { current_form = create_form($2); } form_body '}'
    {
        if (!current_form) {
            yyerror("Failed to create form");
            YYERROR;
        }
        generate_html(stdout);
        $$ = current_form;
    }
    ;

form_body:
    | form_body form_item
    ;

form_item:
      section
    | validation_block
    | metadata_declaration
    ;

section_list: 
    | section_list section
    ;

section: SECTION IDENTIFIER '{' { current_section = create_section($2); } field_list '}' { add_section_to_form(current_form, current_section); current_section = NULL; }
    | SECTION IDENTIFIER '{' '}'
    {
        current_section = NULL;
    }
    | SECTION IDENTIFIER error '}'
    {
        yyerror("Invalid section declaration");
        current_section = NULL;
        yyclearin;
        yyerrok;
    }
    ;

section_header: SECTION IDENTIFIER
    {
        if (current_section != NULL) {
            yyerror("Nested sections are not allowed");
            YYERROR;
        }
        current_section = create_section($2);
        if (!current_section) {
            yyerror("Failed to create section");
            YYERROR;
        }
        add_section_to_form(current_form, current_section);
    }
    ;

field_list:
    | field_list field_declaration
    | field_list error ';'
    {
        yyerror("Invalid field declaration");
        yyclearin;
        yyerrok;
    }
    ;

field_declaration: FIELD IDENTIFIER ':' field_type field_attributes
    {
        if (current_section == NULL) {
            yyerror("Field must be inside a section");
            YYERROR;
        }
        if (check_duplicate_field($2)) {
            yyerror("Duplicate field name");
            YYERROR;
        }
        add_field_to_section(current_section, $2, $4, &$5);
    }
    ;

field_type: TEXT     { $$ = FIELD_TEXT; }
          | EMAIL    { $$ = FIELD_EMAIL; }
          | PASSWORD { $$ = FIELD_PASSWORD; }
          | NUMBER   { $$ = FIELD_NUMBER; }
          | TEXTAREA { $$ = FIELD_TEXTAREA; }
          | DATE     { $$ = FIELD_DATE; }
          | CHECKBOX { $$ = FIELD_CHECKBOX; }
          | DROPDOWN { $$ = FIELD_DROPDOWN; }
          | RADIO    { $$ = FIELD_RADIO; }
          | FILE_TYPE { $$ = FIELD_FILE; }
          | USERNAME { $$ = FIELD_USERNAME; }
          | ADDRESS  { $$ = FIELD_ADDRESS; }
          ;

field_attributes:
    | attribute_opt_semicolon
    | field_attributes attribute_opt_semicolon
    ;

attribute_opt_semicolon:
    attribute ';'
    | attribute
    ;

attribute:
    REQUIRED { $$.required = 1; }
    | OPTIONAL { $$.required = 0; }
    | MINLENGTH NUMBER_LITERAL { $$.min_length = $2; }
    | MAXLENGTH NUMBER_LITERAL { $$.max_length = $2; }
    | MIN NUMBER_LITERAL { $$.min_value = $2; }
    | MAX NUMBER_LITERAL { $$.max_value = $2; }
    | ROWS NUMBER_LITERAL { $$.rows = $2; }
    | COLS NUMBER_LITERAL { $$.cols = $2; }
    | PATTERN STRING_LITERAL { $$.pattern = $2; }
    | DEFAULT STRING_LITERAL { $$.default_value = $2; }
    | CONFIRM IDENTIFIER { $$.confirm_field = $2; }
    | STRENGTH NUMBER_LITERAL { $$.strength_required = $2; }
    ;

validation_blocks:
    | validation_blocks validation_block
    ;

validation_block: VALIDATE '{' validation_rules '}'
    {
        // Validation block is already processed by the rules
    }
    ;

validation_rules:
    | validation_rules validation_rule
    ;

validation_rule: IF condition '{' ERROR STRING_LITERAL ';' '}'
    {
        ValidationRule* rule = malloc(sizeof(ValidationRule));
        if (!rule) {
            yyerror("Memory allocation failed for validation rule");
            YYERROR;
        }
        rule->condition = $2;
        rule->error_message = $5;
        rule->next = current_form->validation_rules;
        current_form->validation_rules = rule;
    }
    ;

condition: IDENTIFIER LT NUMBER_LITERAL
    {
        char* cond = malloc(50);
        sprintf(cond, "%s < %d", $1, $3);
        $$ = cond;
    }
    | IDENTIFIER GT NUMBER_LITERAL
    {
        char* cond = malloc(50);
        sprintf(cond, "%s > %d", $1, $3);
        $$ = cond;
    }
    | IDENTIFIER LTE NUMBER_LITERAL
    {
        char* cond = malloc(50);
        sprintf(cond, "%s <= %d", $1, $3);
        $$ = cond;
    }
    | IDENTIFIER GTE NUMBER_LITERAL
    {
        char* cond = malloc(50);
        sprintf(cond, "%s >= %d", $1, $3);
        $$ = cond;
    }
    | IDENTIFIER EQ NUMBER_LITERAL
    {
        char* cond = malloc(50);
        sprintf(cond, "%s == %d", $1, $3);
        $$ = cond;
    }
    | IDENTIFIER NEQ NUMBER_LITERAL
    {
        char* cond = malloc(50);
        sprintf(cond, "%s != %d", $1, $3);
        $$ = cond;
    }
    | IDENTIFIER EQ IDENTIFIER
    {
        char* cond = malloc(50);
        sprintf(cond, "%s == %s", $1, $3);
        $$ = cond;
    }
    ;

metadata_declaration: META IDENTIFIER '=' STRING_LITERAL ';'
    {
        if (!current_form) {
            yyerror("Metadata must be inside a form");
            YYERROR;
        }
        add_metadata(current_form, $2, $4);
        free($2);  // Free the key
        free($4);  // Free the value
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parser Error: %s at line %d\n", s, yylineno);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror(argv[1]);
            return 1;
        }
        yyin = file;
    }
    yyparse();
    cleanup_form(current_form);
    return 0;
}

int yywrap() {
    return 1;
}
