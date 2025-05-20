/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    FORM = 258,                    /* FORM  */
    SECTION = 259,                 /* SECTION  */
    FIELD = 260,                   /* FIELD  */
    TEXT = 261,                    /* TEXT  */
    EMAIL = 262,                   /* EMAIL  */
    PASSWORD = 263,                /* PASSWORD  */
    NUMBER = 264,                  /* NUMBER  */
    TEXTAREA = 265,                /* TEXTAREA  */
    DATE = 266,                    /* DATE  */
    CHECKBOX = 267,                /* CHECKBOX  */
    DROPDOWN = 268,                /* DROPDOWN  */
    RADIO = 269,                   /* RADIO  */
    FILE_TYPE = 270,               /* FILE_TYPE  */
    REQUIRED = 271,                /* REQUIRED  */
    OPTIONAL = 272,                /* OPTIONAL  */
    MINLENGTH = 273,               /* MINLENGTH  */
    MAXLENGTH = 274,               /* MAXLENGTH  */
    MIN = 275,                     /* MIN  */
    MAX = 276,                     /* MAX  */
    ROWS = 277,                    /* ROWS  */
    COLS = 278,                    /* COLS  */
    PATTERN = 279,                 /* PATTERN  */
    DEFAULT = 280,                 /* DEFAULT  */
    IDENTIFIER = 281,              /* IDENTIFIER  */
    NUMBER_LITERAL = 282,          /* NUMBER_LITERAL  */
    STRING_LITERAL = 283           /* STRING_LITERAL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define FORM 258
#define SECTION 259
#define FIELD 260
#define TEXT 261
#define EMAIL 262
#define PASSWORD 263
#define NUMBER 264
#define TEXTAREA 265
#define DATE 266
#define CHECKBOX 267
#define DROPDOWN 268
#define RADIO 269
#define FILE_TYPE 270
#define REQUIRED 271
#define OPTIONAL 272
#define MINLENGTH 273
#define MAXLENGTH 274
#define MIN 275
#define MAX 276
#define ROWS 277
#define COLS 278
#define PATTERN 279
#define DEFAULT 280
#define IDENTIFIER 281
#define NUMBER_LITERAL 282
#define STRING_LITERAL 283

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 164 "parser.y"

    char* str;
    int num;
    Form* form;
    Section* section;
    FieldType field_type;
    FieldAttributes field_attrs;

#line 132 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
