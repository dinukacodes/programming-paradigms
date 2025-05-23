%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formLang.h"
#include "y.tab.h"

extern YYSTYPE yylval;

// Context tracking
int after_colon = 0;

// Error handling
void syntax_error(const char* msg) {
    fprintf(stderr, "Syntax error at line %d: %s\n", yylineno, msg);
}

// String handling
char* process_string(const char* input) {
    char* output = malloc(strlen(input) + 1);
    int i = 0, j = 0;
    
    while (input[i] != '\0') {
        if (input[i] == '\\') {
            i++;
            switch (input[i]) {
                case 'n': output[j++] = '\n'; break;
                case 't': output[j++] = '\t'; break;
                case 'r': output[j++] = '\r'; break;
                case '\\': output[j++] = '\\'; break;
                case '"': output[j++] = '"'; break;
                default: output[j++] = input[i]; break;
            }
        } else {
            output[j++] = input[i];
        }
        i++;
    }
    output[j] = '\0';
    return output;
}
%}

%option nounput
%option noinput
%option yylineno
%option noyywrap

%%

[ \t\n]     ; /* Skip whitespace and newlines */

"form"      { return FORM; }
"section"   { return SECTION; }
"field"     { return FIELD; }
"validate"  { return VALIDATE; }
"meta"      { return META; }
"if"        { return IF; }
"error"     { return ERROR; }
":"         { after_colon = 1; return ':'; }
";"         { after_colon = 0; return ';'; }
"{"         { return '{'; }
"}"         { return '}'; }
"="         { return '='; }
"<"         { return LT; }
">"         { return GT; }
"<="        { return LTE; }
">="        { return GTE; }
"=="        { return EQ; }
"!="        { return NEQ; }
"&&"        { return AND; }
"||"        { return OR; }

"text"      { 
    if (after_colon) {
        after_colon = 0;
        return TEXT;
    }
    yylval.str = strdup(yytext);
    return IDENTIFIER;
}
"email"     { 
    if (after_colon) {
        after_colon = 0;
        return EMAIL;
    }
    yylval.str = strdup(yytext);
    return IDENTIFIER;
}
"password"  { 
    if (after_colon) {
        after_colon = 0;
        return PASSWORD;
    }
    yylval.str = strdup(yytext);
    return IDENTIFIER;
}
"number"    { 
    if (after_colon) {
        after_colon = 0;
        return NUMBER;
    }
    yylval.str = strdup(yytext);
    return IDENTIFIER;
}
"textarea"  { 
    if (after_colon) {
        after_colon = 0;
        return TEXTAREA;
    }
    yylval.str = strdup(yytext);
    return IDENTIFIER;
}
"date"      { 
    if (after_colon) {
        after_colon = 0;
        return DATE;
    }
    yylval.str = strdup(yytext);
    return IDENTIFIER;
}
"checkbox"  { 
    if (after_colon) {
        after_colon = 0;
        return CHECKBOX;
    }
    yylval.str = strdup(yytext);
    return IDENTIFIER;
}
"dropdown"  { 
    if (after_colon) {
        after_colon = 0;
        return DROPDOWN;
    }
    yylval.str = strdup(yytext);
    return IDENTIFIER;
}
"radio"     { 
    if (after_colon) {
        after_colon = 0;
        return RADIO;
    }
    yylval.str = strdup(yytext);
    return IDENTIFIER;
}
"file"      { 
    if (after_colon) {
        after_colon = 0;
        return FILE_TYPE;
    }
    yylval.str = strdup(yytext);
    return IDENTIFIER;
}

"required"  { return REQUIRED; }
"optional"  { return OPTIONAL; }
"minLength" { return MINLENGTH; }
"maxLength" { return MAXLENGTH; }
"min"       { return MIN; }
"max"       { return MAX; }
"rows"      { return ROWS; }
"cols"      { return COLS; }
"pattern"   { return PATTERN; }
"default"   { return DEFAULT; }

"username"  {
    if (after_colon) {
        after_colon = 0;
        return USERNAME;
    }
    yylval.str = strdup(yytext);
    return IDENTIFIER;
}
"confirm"   { return CONFIRM; }
"strength"  { return STRENGTH; }
"address"   {
    if (after_colon) {
        after_colon = 0;
        return ADDRESS;
    }
    yylval.str = strdup(yytext);
    return IDENTIFIER;
}

[a-zA-Z_][a-zA-Z0-9_]* { 
    yylval.str = strdup(yytext);
    return IDENTIFIER;
}

[0-9]+      {
    yylval.num = atoi(yytext);
    return NUMBER_LITERAL;
}

\"([^"\\]|\\.)*\"  {
    // Remove quotes and process escaped characters
    yytext[strlen(yytext) - 1] = '\0';
    yylval.str = process_string(yytext + 1);
    return STRING_LITERAL;
}

.           { 
    syntax_error("Unexpected character");
    return yytext[0]; 
}

%%
