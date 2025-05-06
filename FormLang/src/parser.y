%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formLang.h"

void yyerror(const char *s);
extern int yylex();
extern int yylineno;
extern FILE *yyin;

// Global variables
Form current_form;
Section current_section;
Field current_field;

void init_form(const char *name) {
    current_form.name = strdup(name);
    current_form.sections = NULL;
    current_form.section_count = 0;
    printf("Creating form: %s\n", name);
}

void add_section(const char *name) {
    Section section;
    section.name = strdup(name);
    section.fields = NULL;
    section.field_count = 0;
    
    current_form.sections = realloc(current_form.sections, 
                                  (current_form.section_count + 1) * sizeof(Section));
    current_form.sections[current_form.section_count++] = section;
    printf("Adding section: %s\n", name);
}

void add_field(const char *name, const char *type, int required) {
    if (current_form.section_count == 0) {
        yyerror("Field declared outside of section");
        return;
    }

    Section *current_section = &current_form.sections[current_form.section_count - 1];
    
    Field field;
    field.name = strdup(name);
    field.type = strdup(type);
    field.required = required;
    
    current_section->fields = realloc(current_section->fields,
                                    (current_section->field_count + 1) * sizeof(Field));
    current_section->fields[current_section->field_count++] = field;
    printf("Adding field: %s (type: %s, required: %s)\n", 
           name, type, required ? "yes" : "no");
}

void print_form() {
    printf("\nForm Structure:\n");
    printf("Form: %s\n", current_form.name);
    for (int i = 0; i < current_form.section_count; i++) {
        printf("  Section: %s\n", current_form.sections[i].name);
        for (int j = 0; j < current_form.sections[i].field_count; j++) {
            printf("    Field: %s (%s) %s\n", 
                   current_form.sections[i].fields[j].name,
                   current_form.sections[i].fields[j].type,
                   current_form.sections[i].fields[j].required ? "required" : "optional");
        }
    }
    printf("\n");
}
%}

%union {
    int num;
    char *str;
    struct {
        char *type;
        int required;
    } field_info;
}

%token FORM SECTION FIELD TEXT EMAIL PASSWORD REQUIRED OPTIONAL
%token <str> IDENTIFIER STRING_LITERAL
%token <num> NUMBER

%type <field_info> field_type field_attributes
%type <str> field_name field_type_name

%start form

%%

form: FORM IDENTIFIER '{' { init_form($2); } sections '}' { print_form(); }
    ;

sections: /* empty */
        | sections section
        ;

section: SECTION IDENTIFIER '{' { add_section($2); } fields '}'
       ;

fields: /* empty */
      | fields field
      ;

field: FIELD field_name ':' field_type field_attributes ';'
     {
         add_field($2, $4.type, $5.required);
     }
     ;

field_name: IDENTIFIER { $$ = $1; }
          | EMAIL { $$ = "email"; }
          | PASSWORD { $$ = "password"; }
          ;

field_type: field_type_name { $$.type = $1; $$.required = 0; }
          ;

field_type_name: TEXT { $$ = "text"; }
               | EMAIL { $$ = "email"; }
               | PASSWORD { $$ = "password"; }
               ;

field_attributes: /* empty */ { $$.required = 0; }
                | REQUIRED { $$.required = 1; }
                | OPTIONAL { $$.required = 0; }
                ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error at line %d: %s\n", yylineno, s);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            fprintf(stderr, "Error: Cannot open file %s\n", argv[1]);
            return 1;
        }
        yyin = file;
    }
    
    printf("Starting parser...\n");
    int result = yyparse();
    printf("Parser finished with result: %d\n", result);
    
    if (argc > 1) {
        fclose(yyin);
    }
    
    return result;
}
