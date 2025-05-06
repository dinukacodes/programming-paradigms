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

// Helper functions
Form* create_form(const char* name) {
    Form* form = malloc(sizeof(Form));
    form->name = strdup(name);
    form->sections = NULL;
    form->section_count = 0;
    return form;
}

Section* create_section(const char* name) {
    Section* section = malloc(sizeof(Section));
    section->name = strdup(name);
    section->fields = NULL;
    section->field_count = 0;
    return section;
}

void add_section_to_form(Form* form, Section* section) {
    form->section_count++;
    form->sections = realloc(form->sections, form->section_count * sizeof(Section*));
    form->sections[form->section_count - 1] = section;
}

void add_field_to_section(Section* section, const char* name, FieldType type, int required) {
    section->field_count++;
    section->fields = realloc(section->fields, section->field_count * sizeof(Field));
    
    Field* field = &section->fields[section->field_count - 1];
    field->name = strdup(name);
    field->type = type;
    field->required = required;
}

void cleanup_form(Form* form) {
    if (form) {
        for (int i = 0; i < form->section_count; i++) {
            Section* s = form->sections[i];
            for (int j = 0; j < s->field_count; j++) {
                Field* f = &s->fields[j];
                free(f->name);
            }
            free(s->fields);
            free(s->name);
            free(s);
        }
        free(form->sections);
        free(form->name);
        free(form);
    }
}
%}

%union {
    char *str;
    int required;
    FieldType field_type;
}

%token FORM SECTION FIELD TEXT EMAIL PASSWORD NUMBER REQUIRED OPTIONAL
%token IDENTIFIER NUMBER_LITERAL

%type <str> IDENTIFIER
%type <field_type> field_type
%type <required> field_attribute

%%

form: FORM IDENTIFIER {
        current_form = create_form($2);
        free($2);
    } '{' section_list '}' {
        generate_html(stdout);
        cleanup_form(current_form);
        current_form = NULL;
    }
    ;

section_list: section
    | section_list section
    ;

section: SECTION IDENTIFIER {
        current_section = create_section($2);
        free($2);
    } '{' field_list '}' {
        if (current_form && current_section) {
            add_section_to_form(current_form, current_section);
            current_section = NULL;
        }
    }
    | error '}' {
        fprintf(stderr, "Error: Invalid section declaration\n");
        yyerrok;
    }
    ;

field_list: field
    | field_list field
    ;

field: FIELD IDENTIFIER ':' field_type field_attribute ';' {
        if (current_section) {
            add_field_to_section(current_section, $2, $4, $5);
        }
        free($2);
    }
    | error ';' {
        fprintf(stderr, "Error: Invalid field declaration\n");
        yyerrok;
    }
    ;

field_type: TEXT { $$ = FIELD_TEXT; }
    | EMAIL { $$ = FIELD_EMAIL; }
    | PASSWORD { $$ = FIELD_PASSWORD; }
    | NUMBER { $$ = FIELD_NUMBER; }
    ;

field_attribute: REQUIRED { $$ = 1; }
    | OPTIONAL { $$ = 0; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error at line %d: %s\n", yylineno, s);
}

int main() {
    yyparse();
    return 0;
}
