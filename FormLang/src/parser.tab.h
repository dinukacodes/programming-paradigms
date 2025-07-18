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

#ifndef YY_YY_SRC_PARSER_TAB_H_INCLUDED
# define YY_YY_SRC_PARSER_TAB_H_INCLUDED
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
    USERNAME = 271,                /* USERNAME  */
    ADDRESS = 272,                 /* ADDRESS  */
    REQUIRED = 273,                /* REQUIRED  */
    OPTIONAL = 274,                /* OPTIONAL  */
    MINLENGTH = 275,               /* MINLENGTH  */
    MAXLENGTH = 276,               /* MAXLENGTH  */
    MIN = 277,                     /* MIN  */
    MAX = 278,                     /* MAX  */
    ROWS = 279,                    /* ROWS  */
    COLS = 280,                    /* COLS  */
    PATTERN = 281,                 /* PATTERN  */
    DEFAULT = 282,                 /* DEFAULT  */
    CONFIRM = 283,                 /* CONFIRM  */
    STRENGTH = 284,                /* STRENGTH  */
    IDENTIFIER = 285,              /* IDENTIFIER  */
    NUMBER_LITERAL = 286,          /* NUMBER_LITERAL  */
    STRING_LITERAL = 287,          /* STRING_LITERAL  */
    VALIDATE = 288,                /* VALIDATE  */
    IF = 289,                      /* IF  */
    ERROR = 290,                   /* ERROR  */
    LT = 291,                      /* LT  */
    GT = 292,                      /* GT  */
    LTE = 293,                     /* LTE  */
    GTE = 294,                     /* GTE  */
    EQ = 295,                      /* EQ  */
    NEQ = 296,                     /* NEQ  */
    AND = 297,                     /* AND  */
    OR = 298                       /* OR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 177 "src/parser.y"

    char* str;
    int num;
    Form* form;
    Section* section;
    FieldType field_type;
    FieldAttributes field_attrs;
    ValidationRule* validation_rule;

#line 117 "src/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SRC_PARSER_TAB_H_INCLUDED  */
