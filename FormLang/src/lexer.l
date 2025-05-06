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
%}

%option nounput
%option noinput
%option yylineno
%option noyywrap

%%

[ \t\n]     ; /* Skip whitespace and newlines */

"form"      { return FORM; }
"section"   { return SECTION; }
"field"     { after_field = 1; return FIELD; }
":"         { after_field = 0; after_colon = 1; return ':'; }
";"         { after_colon = 0; return ';'; }
"{"         { return '{'; }
"}"         { return '}'; }

"text"      { 
    if (after_colon) {
        return TEXT;
    } else {
        yylval.str = strdup(yytext);
        return IDENTIFIER;
    }
}

"email"     { 
    if (after_colon) {
        return EMAIL;
    } else {
        yylval.str = strdup(yytext);
        return IDENTIFIER;
    }
}

"password"  { 
    if (after_colon) {
        return PASSWORD;
    } else {
        yylval.str = strdup(yytext);
        return IDENTIFIER;
    }
}

"number"    {
    if (after_colon) {
        return NUMBER;
    } else {
        yylval.str = strdup(yytext);
        return IDENTIFIER;
    }
}

"required"  { return REQUIRED; }
"optional"  { return OPTIONAL; }

[a-zA-Z_][a-zA-Z0-9_]* { 
    yylval.str = strdup(yytext);
    return IDENTIFIER;
}

[0-9]+      {
    yylval.str = strdup(yytext);
    return NUMBER_LITERAL;
}

.           { 
    fprintf(stderr, "Error: Unexpected character '%c' at line %d\n", yytext[0], yylineno);
    return yytext[0];
}

%%
