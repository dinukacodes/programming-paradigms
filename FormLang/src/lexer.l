%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"

extern YYSTYPE yylval;

#define DEBUG_LEXER 1

void print_token(const char *token_name, const char *value) {
    if (DEBUG_LEXER) {
        if (value) {
            fprintf(stderr, "Token: %s (%s)\n", token_name, value);
        } else {
            fprintf(stderr, "Token: %s\n", token_name);
        }
    }
}

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

"form"      { print_token("FORM", NULL); return FORM; }
"section"   { print_token("SECTION", NULL); return SECTION; }
"field"     { after_field = 1; print_token("FIELD", NULL); return FIELD; }
":"         { after_field = 0; after_colon = 1; print_token("SYMBOL", ":"); return ':'; }
";"         { after_colon = 0; print_token("SYMBOL", ";"); return ';'; }

"text"      { 
    if (after_colon) {
        print_token("TEXT", NULL); 
        return TEXT;
    } else {
        yylval.str = strdup(yytext);
        print_token("IDENTIFIER", yytext);
        return IDENTIFIER;
    }
}

"email"     { 
    if (after_colon) {
        print_token("EMAIL_TYPE", NULL); 
        return EMAIL;
    } else {
        yylval.str = strdup(yytext);
        print_token("IDENTIFIER", yytext);
        return IDENTIFIER;
    }
}

"password"  { 
    if (after_colon) {
        print_token("PASSWORD", NULL); 
        return PASSWORD;
    } else {
        yylval.str = strdup(yytext);
        print_token("IDENTIFIER", yytext);
        return IDENTIFIER;
    }
}

"required"  { print_token("REQUIRED", NULL); return REQUIRED; }
"optional"  { print_token("OPTIONAL", NULL); return OPTIONAL; }

[a-zA-Z_][a-zA-Z0-9_]* { 
    yylval.str = strdup(yytext);
    print_token("IDENTIFIER", yytext);
    return IDENTIFIER;
}

\"[^\"]*\"  {
    yylval.str = strdup(yytext + 1);
    yylval.str[strlen(yylval.str) - 1] = '\0';
    print_token("STRING_LITERAL", yytext);
    return STRING_LITERAL;
}

[0-9]+      {
    yylval.num = atoi(yytext);
    print_token("NUMBER", yytext);
    return NUMBER;
}

[{}:;,]     { print_token("SYMBOL", yytext); return yytext[0]; }

.           { 
    fprintf(stderr, "Error: Unexpected character '%c' at line %d\n", yytext[0], yylineno);
    return yytext[0];
}

%%
