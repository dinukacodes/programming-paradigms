%{
#include <stdio.h>
#include <stdlib.h>
#include "formLang.h"

void yyerror(const char *s);
%}

%option noyywrap
%option yylineno

DIGIT       [0-9]
LETTER      [a-zA-Z]
ID          {LETTER}({LETTER}|{DIGIT}|_)*
WHITESPACE  [ \t\n]
STRING      \"([^\"\\]|\\.)*\"

%%

"form"      { printf("FORM\n"); }
"section"   { printf("SECTION\n"); }
"field"     { printf("FIELD\n"); }
"text"      { printf("TEXT\n"); }
"email"     { printf("EMAIL\n"); }
"password"  { printf("PASSWORD\n"); }
"required"  { printf("REQUIRED\n"); }
"optional"  { printf("OPTIONAL\n"); }

{ID}        { printf("IDENTIFIER: %s\n", yytext); }
{STRING}    { printf("STRING: %s\n", yytext); }
{DIGIT}+    { printf("NUMBER: %s\n", yytext); }

"{"         { printf("{\n"); }
"}"         { printf("}\n"); }
";"         { printf(";\n"); }
":"         { printf(":\n"); }
","         { printf(",\n"); }

{WHITESPACE}    { /* ignore whitespace */ }
.           { yyerror("Invalid character"); }

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error at line %d: %s\n", yylineno, s);
}

int main() {
    yylex();
    return 0;
}
