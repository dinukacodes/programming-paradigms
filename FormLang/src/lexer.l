%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formLang.h"
#include "parser.tab.h"

extern YYSTYPE yylval;

// Context tracking
int after_field = 0;
int after_colon = 0;
int after_section = 0;
int after_form = 0;
int after_type = 0;

// Error handling
void syntax_error(const char* msg) {
    fprintf(stderr, "Syntax error at line %d: %s\n", yylineno, msg);
}
%}

%option nounput
%option noinput
%option yylineno
%option noyywrap

%%

[ \t\n]     ; /* Skip whitespace and newlines */

"form"      { 
    if (after_form) {
        syntax_error("Nested form declarations are not allowed");
        return -1;
    }
    after_form = 1;
    after_section = 0;
    return FORM;
}
"section"   { 
    if (!after_form) {
        syntax_error("Section must be inside a form");
        return -1;
    }
    after_section = 1;
    return SECTION;
}
"field"     { 
    if (!after_section) {
        syntax_error("Field must be inside a section");
        return -1;
    }
    after_field = 1; 
    return FIELD; 
}
":"         { 
    if (!after_field) {
        syntax_error("Colon must follow field name");
        return -1;
    }
    after_field = 0; 
    after_colon = 1; 
    return ':'; 
}
";"         { 
    if (!after_colon && !after_type) {
        syntax_error("Semicolon must follow field type and attributes");
        return -1;
    }
    after_colon = 0;
    after_type = 0;
    return ';'; 
}
"{"         { return '{'; }
"}"         { 
    if (after_section) {
        after_section = 0;
    } else if (after_form) {
        after_form = 0;
    }
    return '}';
}

"text"      { 
    if (after_colon) {
        after_type = 1;
        return TEXT;
    } else {
        yylval.str = strdup(yytext);
        return IDENTIFIER;
    }
}

"email"     { 
    if (after_colon) {
        after_type = 1;
        return EMAIL;
    } else {
        yylval.str = strdup(yytext);
        return IDENTIFIER;
    }
}

"password"  { 
    if (after_colon) {
        after_type = 1;
        return PASSWORD;
    } else {
        yylval.str = strdup(yytext);
        return IDENTIFIER;
    }
}

"number"    {
    if (after_colon) {
        after_type = 1;
        return NUMBER;
    } else {
        yylval.str = strdup(yytext);
        return IDENTIFIER;
    }
}

"required"  { 
    if (!after_colon && !after_type) {
        syntax_error("Field attributes must follow field type");
        return -1;
    }
    return REQUIRED; 
}
"optional"  { 
    if (!after_colon && !after_type) {
        syntax_error("Field attributes must follow field type");
        return -1;
    }
    return OPTIONAL; 
}

[a-zA-Z_][a-zA-Z0-9_]* { 
    if (after_colon) {
        syntax_error("Invalid field type");
        return -1;
    }
    yylval.str = strdup(yytext);
    return IDENTIFIER;
}

[0-9]+      {
    yylval.str = strdup(yytext);
    return NUMBER_LITERAL;
}

.           { 
    syntax_error("Unexpected character");
    return -1;
}

%%
