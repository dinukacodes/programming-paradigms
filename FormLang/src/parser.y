%{
#include <stdio.h>
#include <stdlib.h>
#include "formLang.h"

void yyerror(const char *s);
%}

%union {
    int num;
    char *str;
}

%token FORM SECTION FIELD TEXT EMAIL PASSWORD REQUIRED OPTIONAL
%token IDENTIFIER STRING_LITERAL NUMBER

%%

form_declaration: FORM IDENTIFIER '{' '}'
                ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
