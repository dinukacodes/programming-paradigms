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
        free(form);
    }
    
    // Cleanup field name tracking
    for (int i = 0; i < field_name_count; i++) {
        if (field_names[i].name) free(field_names[i].name);
    }
    if (field_names) free(field_names);
    field_name_count = 0;
}
%}

%token FORM SECTION FIELD TEXT EMAIL PASSWORD NUMBER TEXTAREA DATE CHECKBOX DROPDOWN RADIO FILE_TYPE
%token REQUIRED OPTIONAL MINLENGTH MAXLENGTH MIN MAX ROWS COLS PATTERN DEFAULT
%token IDENTIFIER NUMBER_LITERAL STRING_LITERAL

%union {
    char* str;
    int num;
    Form* form;
    Section* section;
    FieldType field_type;
    FieldAttributes field_attrs;
}

%type <str> IDENTIFIER STRING_LITERAL
%type <num> NUMBER_LITERAL
%type <form> form
%type <field_type> field_type
%type <field_attrs> field_attributes attribute

%define parse.error verbose

%%

form: FORM IDENTIFIER 
    {
        current_form = create_form($2);
        if (!current_form) {
            yyerror("Failed to create form");
            YYERROR;
        }
    }
    '{' section_list '}'
    {
        generate_html(stdout);
        $$ = current_form;
    }
    ;

section_list: 
    | section_list section
    ;

section: section_header '{' field_list '}'
    {
        current_section = NULL;
    }
    | section_header '{' '}'
    {
        current_section = NULL;
    }
    | section_header error '}'
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
    | field_list field
    | field_list error ';'
    {
        yyerror("Invalid field declaration");
        yyclearin;
        yyerrok;
    }
    ;

field: FIELD IDENTIFIER ':' field_type field_attributes ';'
    {
        if (current_section == NULL) {
            yyerror("Field must be inside a section");
            YYERROR;
        }
        if (check_duplicate_field($2)) {
            yyerror("Duplicate field name found");
            YYERROR;
        }
        add_field_to_section(current_section, $2, $4, &$5);
        free($2); // Free the field name
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
          ;

field_attributes: /* empty */
    {
        init_field_attributes(&$$);
    }
    | field_attributes attribute
    {
        // Merge attributes
        if ($2.required != -1) $$.required = $2.required;
        if ($2.min_length != -1) $$.min_length = $2.min_length;
        if ($2.max_length != -1) $$.max_length = $2.max_length;
        if ($2.min_value != -1) $$.min_value = $2.min_value;
        if ($2.max_value != -1) $$.max_value = $2.max_value;
        if ($2.rows != -1) $$.rows = $2.rows;
        if ($2.cols != -1) $$.cols = $2.cols;
        if ($2.pattern) {
            if ($$.pattern) free($$.pattern);
            $$.pattern = $2.pattern;
        }
        if ($2.default_value) {
            if ($$.default_value) free($$.default_value);
            $$.default_value = $2.default_value;
        }
    }
    ;

attribute: REQUIRED
    {
        init_field_attributes(&$$);
        $$.required = 1;
    }
    | OPTIONAL
    {
        init_field_attributes(&$$);
        $$.required = 0;
    }
    | PATTERN STRING_LITERAL
    {
        init_field_attributes(&$$);
        $$.pattern = $2;
    }
    | DEFAULT STRING_LITERAL
    {
        init_field_attributes(&$$);
        $$.default_value = $2;
    }
    | DEFAULT NUMBER_LITERAL
    {
        init_field_attributes(&$$);
        char buf[32];
        sprintf(buf, "%d", $2);
        $$.default_value = strdup(buf);
    }
    | MINLENGTH NUMBER_LITERAL
    {
        init_field_attributes(&$$);
        $$.min_length = $2;
    }
    | MAXLENGTH NUMBER_LITERAL
    {
        init_field_attributes(&$$);
        $$.max_length = $2;
    }
    | MIN NUMBER_LITERAL
    {
        init_field_attributes(&$$);
        $$.min_value = $2;
    }
    | MAX NUMBER_LITERAL
    {
        init_field_attributes(&$$);
        $$.max_value = $2;
    }
    | ROWS NUMBER_LITERAL
    {
        init_field_attributes(&$$);
        $$.rows = $2;
    }
    | COLS NUMBER_LITERAL
    {
        init_field_attributes(&$$);
        $$.cols = $2;
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
