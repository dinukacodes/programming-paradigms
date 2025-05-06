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
    if (!form || !section) return;
    
    form->section_count++;
    form->sections = realloc(form->sections, form->section_count * sizeof(Section*));
    form->sections[form->section_count - 1] = section;
}

int check_duplicate_field(const char* name) {
    for (int i = 0; i < field_name_count; i++) {
        if (strcmp(field_names[i].name, name) == 0) {
            return 1;
        }
    }
    return 0;
}

void add_field_to_section(Section* section, const char* name, FieldType type, int required) {
    if (!section || !name) return;
    
    // Add field name to tracking
    field_name_count++;
    field_names = realloc(field_names, field_name_count * sizeof(FieldName));
    field_names[field_name_count - 1].name = strdup(name);
    field_names[field_name_count - 1].line = yylineno;
    
    section->field_count++;
    section->fields = realloc(section->fields, section->field_count * sizeof(Field));
    
    Field* field = &section->fields[section->field_count - 1];
    field->name = strdup(name);
    field->type = type;
    field->required = required;
}

void generate_html(FILE* output) {
    if (!current_form || !output) return;
    
    fprintf(output, "<!DOCTYPE html>\n<html>\n<head>\n");
    fprintf(output, "<title>%s</title>\n", current_form->name);
    fprintf(output, "<style>\n");
    fprintf(output, "body { font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto; padding: 20px; }\n");
    fprintf(output, "form { background: #f5f5f5; padding: 20px; border-radius: 5px; }\n");
    fprintf(output, "section { margin-bottom: 20px; padding: 15px; background: white; border-radius: 5px; }\n");
    fprintf(output, "h2 { color: #333; margin-top: 0; }\n");
    fprintf(output, "label { display: block; margin-bottom: 5px; }\n");
    fprintf(output, "input { width: 100%%; padding: 8px; margin-bottom: 10px; border: 1px solid #ddd; border-radius: 4px; }\n");
    fprintf(output, "input[type=submit] { background: #4CAF50; color: white; border: none; padding: 10px 20px; cursor: pointer; width: auto; }\n");
    fprintf(output, "input[type=submit]:hover { background: #45a049; }\n");
    fprintf(output, "</style>\n</head>\n<body>\n");
    fprintf(output, "<form>\n");
    
    for (int i = 0; i < current_form->section_count; i++) {
        Section* section = current_form->sections[i];
        fprintf(output, "<section>\n");
        fprintf(output, "<h2>%s</h2>\n", section->name);
        
        for (int j = 0; j < section->field_count; j++) {
            Field* field = &section->fields[j];
            fprintf(output, "<label for=\"%s\">%s%s</label>\n", 
                   field->name, field->name, field->required ? " *" : "");
            
            const char* type = "text";
            switch (field->type) {
                case FIELD_TEXT: type = "text"; break;
                case FIELD_EMAIL: type = "email"; break;
                case FIELD_PASSWORD: type = "password"; break;
                case FIELD_NUMBER: type = "number"; break;
            }
            
            fprintf(output, "<input type=\"%s\" id=\"%s\" name=\"%s\"%s>\n",
                   type, field->name, field->name, field->required ? " required" : "");
        }
        fprintf(output, "</section>\n");
    }
    
    fprintf(output, "<input type=\"submit\" value=\"Submit\">\n");
    fprintf(output, "</form>\n</body>\n</html>\n");
}

void cleanup_form(Form* form) {
    if (form) {
        for (int i = 0; i < form->section_count; i++) {
            Section* s = form->sections[i];
            if (s) {
                for (int j = 0; j < s->field_count; j++) {
                    Field* f = &s->fields[j];
                    if (f->name) free(f->name);
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

%token FORM SECTION FIELD TEXT EMAIL PASSWORD NUMBER REQUIRED OPTIONAL IDENTIFIER NUMBER_LITERAL

%union {
    char* str;
    int num;
    Form* form;
    Section* section;
    FieldType field_type;
}

%type <str> IDENTIFIER
%type <form> form
%type <field_type> field_type
%type <num> field_attribute

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

field: FIELD IDENTIFIER ':' field_type field_attribute ';'
    {
        if (current_section == NULL) {
            yyerror("Field must be inside a section");
            YYERROR;
        }
        if (check_duplicate_field($2)) {
            yyerror("Duplicate field name found");
            YYERROR;
        }
        add_field_to_section(current_section, $2, $4, $5);
    }
    | FIELD ':' field_type field_attribute ';'
    {
        yyerror("Missing field name");
        YYERROR;
    }
    | FIELD IDENTIFIER ':' field_attribute ';'
    {
        yyerror("Missing field type");
        YYERROR;
    }
    | FIELD IDENTIFIER ':' field_type error
    {
        yyerror("Invalid field attribute or missing semicolon");
        YYERROR;
    }
    ;

field_type: 
    TEXT { $$ = FIELD_TEXT; }
    | EMAIL { $$ = FIELD_EMAIL; }
    | PASSWORD { $$ = FIELD_PASSWORD; }
    | NUMBER { $$ = FIELD_NUMBER; }
    | IDENTIFIER { 
        yyerror("Invalid field type");
        YYERROR;
    }
    ;

field_attribute:
    REQUIRED { $$ = 1; }
    | OPTIONAL { $$ = 0; }
    | { $$ = 0; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s at line %d\n", s, yylineno);
}

int main() {
    int result = yyparse();
    cleanup_form(current_form);
    return result;
}
