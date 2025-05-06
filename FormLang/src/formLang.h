#ifndef FORMLANG_H
#define FORMLANG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Token types */
#define FORM 1000
#define SECTION 1001
#define FIELD 1002
#define TEXT 1003
#define EMAIL 1004
#define PASSWORD 1005
#define REQUIRED 1006
#define OPTIONAL 1007
#define IDENTIFIER 1008
#define STRING_LITERAL 1009
#define NUMBER 1010

/* Union for yylval */
typedef union {
    int num;
    char *str;
} YYSTYPE;

extern YYSTYPE yylval;

/* Basic structures for the AST */
typedef struct {
    char *name;
    char *type;
    int is_required;
} Field;

typedef struct {
    char *name;
    Field *fields;
    int field_count;
} Section;

typedef struct {
    char *name;
    Section *sections;
    int section_count;
} Form;

/* Function declarations */
void yyerror(const char *s);
int yylex(void);
int yyparse(void);

#endif /* FORMLANG_H */
