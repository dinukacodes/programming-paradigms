/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formLang.h"

extern int yylex();
extern int yylineno;
void yyerror(const char *s);

// Global variables for current form and section
Form *current_form = NULL;
Section *current_section = NULL;

// Field name tracking for duplicate detection
typedef struct {
    char* name;
    int line;
} FieldName;

FieldName* field_names = NULL;
int field_name_count = 0;

// Helper functions
Form* create_form(const char* name) {
    Form* form = malloc(sizeof(Form));
    if (!form) return NULL;
    form->name = strdup(name);
    form->sections = NULL;
    form->section_count = 0;
    form->validation_rules = NULL;
    form->metadata = NULL;
    return form;
}

Section* create_section(const char* name) {
    Section* section = malloc(sizeof(Section));
    if (!section) return NULL;
    section->name = strdup(name);
    section->fields = NULL;
    section->field_count = 0;
    return section;
}

void add_section_to_form(Form* form, Section* section) {
    if (!form || !section) {
        fprintf(stderr, "Null form or section\n");
        return;
    }
    
    Section** new_sections = realloc(form->sections, (form->section_count + 1) * sizeof(Section*));
    if (!new_sections) {
        fprintf(stderr, "Memory allocation failed for sections\n");
        exit(1);
    }
    form->sections = new_sections;
    form->sections[form->section_count] = section;
    form->section_count++;
}

int check_duplicate_field(const char* name) {
    for (int i = 0; i < field_name_count; i++) {
        if (strcmp(field_names[i].name, name) == 0) {
            return 1;
        }
    }
    return 0;
}

void init_field_attributes(FieldAttributes* attrs) {
    if (!attrs) return;
    attrs->min_length = -1;
    attrs->max_length = -1;
    attrs->min_value = -1;
    attrs->max_value = -1;
    attrs->rows = -1;
    attrs->cols = -1;
    attrs->pattern = NULL;
    attrs->default_value = NULL;
    attrs->required = 0;
}

void add_field_to_section(Section* section, const char* name, FieldType type, FieldAttributes* attrs) {
    if (!section || !name || !attrs) {
        fprintf(stderr, "Null section, name, or attrs\n");
        return;
    }
    
    // Add field name to tracking
    field_name_count++;
    FieldName* new_field_names = realloc(field_names, field_name_count * sizeof(FieldName));
    if (!new_field_names) {
        fprintf(stderr, "Memory allocation failed for field names\n");
        exit(1);
    }
    field_names = new_field_names;
    field_names[field_name_count - 1].name = strdup(name);
    field_names[field_name_count - 1].line = yylineno;
    
    // Allocate memory for the new field
    Field* new_fields = realloc(section->fields, (section->field_count + 1) * sizeof(Field));
    if (!new_fields) {
        fprintf(stderr, "Memory allocation failed for fields\n");
        exit(1);
    }
    section->fields = new_fields;
    
    Field* field = &section->fields[section->field_count];
    field->name = strdup(name);
    field->type = type;
    init_field_attributes(&field->attributes);
    
    // Copy attributes
    field->attributes.min_length = attrs->min_length;
    field->attributes.max_length = attrs->max_length;
    field->attributes.min_value = attrs->min_value;
    field->attributes.max_value = attrs->max_value;
    field->attributes.rows = attrs->rows;
    field->attributes.cols = attrs->cols;
    field->attributes.required = attrs->required;
    
    if (attrs->pattern) {
        field->attributes.pattern = strdup(attrs->pattern);
    }
    if (attrs->default_value) {
        field->attributes.default_value = strdup(attrs->default_value);
    }
    
    section->field_count++;
}

void add_metadata(Form* form, const char* key, const char* value) {
    Metadata* meta = malloc(sizeof(Metadata));
    if (!meta) {
        fprintf(stderr, "Memory allocation failed for metadata\n");
        return;
    }
    meta->key = strdup(key);
    meta->value = strdup(value);
    meta->next = form->metadata;
    form->metadata = meta;
}

void cleanup_metadata(Metadata* metadata) {
    while (metadata) {
        Metadata* next = metadata->next;
        if (metadata->key) free(metadata->key);
        if (metadata->value) free(metadata->value);
        free(metadata);
        metadata = next;
    }
}

void cleanup_form(Form* form) {
    if (form) {
        for (int i = 0; i < form->section_count; i++) {
            Section* s = form->sections[i];
            if (s) {
                for (int j = 0; j < s->field_count; j++) {
                    Field* f = &s->fields[j];
                    if (f->name) free(f->name);
                    if (f->attributes.pattern) free(f->attributes.pattern);
                    if (f->attributes.default_value) free(f->attributes.default_value);
                }
                if (s->fields) free(s->fields);
                if (s->name) free(s->name);
                free(s);
            }
        }
        if (form->sections) free(form->sections);
        if (form->name) free(form->name);
        
        // Cleanup validation rules
        ValidationRule* rule = form->validation_rules;
        while (rule) {
            ValidationRule* next = rule->next;
            if (rule->condition) free(rule->condition);
            if (rule->error_message) free(rule->error_message);
            free(rule);
            rule = next;
        }
        
        // Cleanup metadata
        cleanup_metadata(form->metadata);
        
        free(form);
    }
    
    // Cleanup field name tracking
    for (int i = 0; i < field_name_count; i++) {
        if (field_names[i].name) free(field_names[i].name);
    }
    if (field_names) free(field_names);
    field_name_count = 0;
}

void merge_field_attributes(FieldAttributes* dest, FieldAttributes* src) {
    if (src->required != -1) dest->required = src->required;
    if (src->min_length != -1) dest->min_length = src->min_length;
    if (src->max_length != -1) dest->max_length = src->max_length;
    if (src->min_value != -1) dest->min_value = src->min_value;
    if (src->max_value != -1) dest->max_value = src->max_value;
    if (src->rows != -1) dest->rows = src->rows;
    if (src->cols != -1) dest->cols = src->cols;
    if (src->pattern) { if (dest->pattern) free(dest->pattern); dest->pattern = strdup(src->pattern); }
    if (src->default_value) { if (dest->default_value) free(dest->default_value); dest->default_value = strdup(src->default_value); }
}

#line 280 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
    META = 285,                    /* META  */
    IDENTIFIER = 286,              /* IDENTIFIER  */
    NUMBER_LITERAL = 287,          /* NUMBER_LITERAL  */
    STRING_LITERAL = 288,          /* STRING_LITERAL  */
    VALIDATE = 289,                /* VALIDATE  */
    IF = 290,                      /* IF  */
    ERROR = 291,                   /* ERROR  */
    LT = 292,                      /* LT  */
    GT = 293,                      /* GT  */
    LTE = 294,                     /* LTE  */
    GTE = 295,                     /* GTE  */
    EQ = 296,                      /* EQ  */
    NEQ = 297,                     /* NEQ  */
    AND = 298,                     /* AND  */
    OR = 299                       /* OR  */
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
#define USERNAME 271
#define ADDRESS 272
#define REQUIRED 273
#define OPTIONAL 274
#define MINLENGTH 275
#define MAXLENGTH 276
#define MIN 277
#define MAX 278
#define ROWS 279
#define COLS 280
#define PATTERN 281
#define DEFAULT 282
#define CONFIRM 283
#define STRENGTH 284
#define META 285
#define IDENTIFIER 286
#define NUMBER_LITERAL 287
#define STRING_LITERAL 288
#define VALIDATE 289
#define IF 290
#define ERROR 291
#define LT 292
#define GT 293
#define LTE 294
#define GTE 295
#define EQ 296
#define NEQ 297
#define AND 298
#define OR 299

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 215 "parser.y"

    char* str;
    int num;
    Form* form;
    Section* section;
    FieldType field_type;
    FieldAttributes field_attrs;
    ValidationRule* validation_rule;

#line 431 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_FORM = 3,                       /* FORM  */
  YYSYMBOL_SECTION = 4,                    /* SECTION  */
  YYSYMBOL_FIELD = 5,                      /* FIELD  */
  YYSYMBOL_TEXT = 6,                       /* TEXT  */
  YYSYMBOL_EMAIL = 7,                      /* EMAIL  */
  YYSYMBOL_PASSWORD = 8,                   /* PASSWORD  */
  YYSYMBOL_NUMBER = 9,                     /* NUMBER  */
  YYSYMBOL_TEXTAREA = 10,                  /* TEXTAREA  */
  YYSYMBOL_DATE = 11,                      /* DATE  */
  YYSYMBOL_CHECKBOX = 12,                  /* CHECKBOX  */
  YYSYMBOL_DROPDOWN = 13,                  /* DROPDOWN  */
  YYSYMBOL_RADIO = 14,                     /* RADIO  */
  YYSYMBOL_FILE_TYPE = 15,                 /* FILE_TYPE  */
  YYSYMBOL_USERNAME = 16,                  /* USERNAME  */
  YYSYMBOL_ADDRESS = 17,                   /* ADDRESS  */
  YYSYMBOL_REQUIRED = 18,                  /* REQUIRED  */
  YYSYMBOL_OPTIONAL = 19,                  /* OPTIONAL  */
  YYSYMBOL_MINLENGTH = 20,                 /* MINLENGTH  */
  YYSYMBOL_MAXLENGTH = 21,                 /* MAXLENGTH  */
  YYSYMBOL_MIN = 22,                       /* MIN  */
  YYSYMBOL_MAX = 23,                       /* MAX  */
  YYSYMBOL_ROWS = 24,                      /* ROWS  */
  YYSYMBOL_COLS = 25,                      /* COLS  */
  YYSYMBOL_PATTERN = 26,                   /* PATTERN  */
  YYSYMBOL_DEFAULT = 27,                   /* DEFAULT  */
  YYSYMBOL_CONFIRM = 28,                   /* CONFIRM  */
  YYSYMBOL_STRENGTH = 29,                  /* STRENGTH  */
  YYSYMBOL_META = 30,                      /* META  */
  YYSYMBOL_IDENTIFIER = 31,                /* IDENTIFIER  */
  YYSYMBOL_NUMBER_LITERAL = 32,            /* NUMBER_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 33,            /* STRING_LITERAL  */
  YYSYMBOL_VALIDATE = 34,                  /* VALIDATE  */
  YYSYMBOL_IF = 35,                        /* IF  */
  YYSYMBOL_ERROR = 36,                     /* ERROR  */
  YYSYMBOL_LT = 37,                        /* LT  */
  YYSYMBOL_GT = 38,                        /* GT  */
  YYSYMBOL_LTE = 39,                       /* LTE  */
  YYSYMBOL_GTE = 40,                       /* GTE  */
  YYSYMBOL_EQ = 41,                        /* EQ  */
  YYSYMBOL_NEQ = 42,                       /* NEQ  */
  YYSYMBOL_AND = 43,                       /* AND  */
  YYSYMBOL_OR = 44,                        /* OR  */
  YYSYMBOL_45_ = 45,                       /* '{'  */
  YYSYMBOL_46_ = 46,                       /* '}'  */
  YYSYMBOL_47_ = 47,                       /* ';'  */
  YYSYMBOL_48_ = 48,                       /* ':'  */
  YYSYMBOL_49_ = 49,                       /* '='  */
  YYSYMBOL_YYACCEPT = 50,                  /* $accept  */
  YYSYMBOL_form = 51,                      /* form  */
  YYSYMBOL_52_1 = 52,                      /* $@1  */
  YYSYMBOL_form_body = 53,                 /* form_body  */
  YYSYMBOL_form_item = 54,                 /* form_item  */
  YYSYMBOL_section = 55,                   /* section  */
  YYSYMBOL_56_2 = 56,                      /* $@2  */
  YYSYMBOL_field_list = 57,                /* field_list  */
  YYSYMBOL_field_declaration = 58,         /* field_declaration  */
  YYSYMBOL_field_type = 59,                /* field_type  */
  YYSYMBOL_field_attributes = 60,          /* field_attributes  */
  YYSYMBOL_attribute_opt_semicolon = 61,   /* attribute_opt_semicolon  */
  YYSYMBOL_attribute = 62,                 /* attribute  */
  YYSYMBOL_validation_block = 63,          /* validation_block  */
  YYSYMBOL_validation_rules = 64,          /* validation_rules  */
  YYSYMBOL_validation_rule = 65,           /* validation_rule  */
  YYSYMBOL_condition = 66,                 /* condition  */
  YYSYMBOL_metadata_declaration = 67       /* metadata_declaration  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   82

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  57
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  99

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   299


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    48,    47,
       2,    49,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    45,     2,    46,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   236,   236,   236,   247,   248,   252,   253,   254,   261,
     261,   262,   266,   290,   291,   292,   300,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   328,
     329,   330,   334,   335,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   357,   363,   364,   367,
     381,   387,   393,   399,   405,   411,   417,   425
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "FORM", "SECTION",
  "FIELD", "TEXT", "EMAIL", "PASSWORD", "NUMBER", "TEXTAREA", "DATE",
  "CHECKBOX", "DROPDOWN", "RADIO", "FILE_TYPE", "USERNAME", "ADDRESS",
  "REQUIRED", "OPTIONAL", "MINLENGTH", "MAXLENGTH", "MIN", "MAX", "ROWS",
  "COLS", "PATTERN", "DEFAULT", "CONFIRM", "STRENGTH", "META",
  "IDENTIFIER", "NUMBER_LITERAL", "STRING_LITERAL", "VALIDATE", "IF",
  "ERROR", "LT", "GT", "LTE", "GTE", "EQ", "NEQ", "AND", "OR", "'{'",
  "'}'", "';'", "':'", "'='", "$accept", "form", "$@1", "form_body",
  "form_item", "section", "$@2", "field_list", "field_declaration",
  "field_type", "field_attributes", "attribute_opt_semicolon", "attribute",
  "validation_block", "validation_rules", "validation_rule", "condition",
  "metadata_declaration", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-29)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       2,   -28,    28,   -15,   -29,   -29,   -29,    -3,     3,     4,
     -13,   -29,   -29,   -29,   -29,   -29,     1,   -16,   -29,   -10,
      -9,     5,   -17,   -29,   -29,   -29,    -8,     9,   -29,   -29,
      -1,   -29,   -18,    -4,    -5,    13,   -29,   -29,    27,    30,
      31,    32,    -6,    33,    24,   -29,    18,   -29,   -29,   -29,
     -29,   -29,   -29,   -29,    34,     0,    14,   -29,   -29,   -29,
     -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,    29,
      22,   -29,   -29,    37,    38,    39,    40,    41,    42,    43,
      44,    47,    48,    29,   -29,    35,   -29,   -29,   -29,   -29,
     -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     2,     4,     0,     0,     0,
       0,     3,     5,     6,     7,     8,     0,     0,    47,     0,
       9,     0,     0,    12,    11,    13,     0,     0,    46,    48,
       0,    57,     0,     0,     0,     0,    10,    14,     0,     0,
       0,     0,     0,     0,     0,    15,     0,    50,    51,    52,
      53,    56,    54,    55,     0,     0,     0,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
       0,    34,    35,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    16,    30,    33,    49,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    31,    32
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,
     -29,    -2,   -29,   -29,   -29,   -29,   -29,   -29
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     6,     7,    12,    13,    25,    30,    37,    69,
      83,    84,    85,    14,    22,    29,    33,    15
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      34,     8,    19,     3,    35,     1,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    27,    38,
      39,    40,    41,    42,    43,    51,    52,     9,     4,    28,
       5,    10,    18,    21,    16,    17,    23,    24,    26,    31,
      32,    44,    45,    11,    46,    36,    20,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    47,
      54,    70,    48,    49,    50,    53,    55,    56,    86,    87,
      88,    89,    90,    91,    92,     0,    93,    94,    95,     0,
      96,    97,    98
};

static const yytype_int8 yycheck[] =
{
       1,     4,     1,    31,     5,     3,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    35,    37,
      38,    39,    40,    41,    42,    31,    32,    30,     0,    46,
      45,    34,    45,    49,    31,    31,    46,    46,    33,    47,
      31,    45,    47,    46,    31,    46,    45,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    32,
      36,    47,    32,    32,    32,    32,    48,    33,    46,    32,
      32,    32,    32,    32,    32,    -1,    33,    33,    31,    -1,
      32,    83,    47
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    51,    31,     0,    45,    52,    53,     4,    30,
      34,    46,    54,    55,    63,    67,    31,    31,    45,     1,
      45,    49,    64,    46,    46,    56,    33,    35,    46,    65,
      57,    47,    31,    66,     1,     5,    46,    58,    37,    38,
      39,    40,    41,    42,    45,    47,    31,    32,    32,    32,
      32,    31,    32,    32,    36,    48,    33,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    59,
      47,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    60,    61,    62,    46,    32,    32,    32,
      32,    32,    32,    33,    33,    31,    32,    61,    47
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    50,    52,    51,    53,    53,    54,    54,    54,    56,
      55,    55,    55,    57,    57,    57,    58,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    60,
      60,    60,    61,    61,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    63,    64,    64,    65,
      66,    66,    66,    66,    66,    66,    66,    67
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     6,     0,     2,     1,     1,     1,     0,
       6,     4,     4,     0,     2,     3,     5,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       1,     2,     2,     1,     1,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     4,     0,     2,     7,
       3,     3,     3,     3,     3,     3,     3,     5
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 236 "parser.y"
                          { current_form = create_form((yyvsp[-1].str)); }
#line 1807 "y.tab.c"
    break;

  case 3: /* form: FORM IDENTIFIER '{' $@1 form_body '}'  */
#line 237 "parser.y"
    {
        if (!current_form) {
            yyerror("Failed to create form");
            YYERROR;
        }
        generate_html(stdout);
        (yyval.form) = current_form;
    }
#line 1820 "y.tab.c"
    break;

  case 9: /* $@2: %empty  */
#line 261 "parser.y"
                                { current_section = create_section((yyvsp[-1].str)); }
#line 1826 "y.tab.c"
    break;

  case 10: /* section: SECTION IDENTIFIER '{' $@2 field_list '}'  */
#line 261 "parser.y"
                                                                                         { add_section_to_form(current_form, current_section); current_section = NULL; }
#line 1832 "y.tab.c"
    break;

  case 11: /* section: SECTION IDENTIFIER '{' '}'  */
#line 263 "parser.y"
    {
        current_section = NULL;
    }
#line 1840 "y.tab.c"
    break;

  case 12: /* section: SECTION IDENTIFIER error '}'  */
#line 267 "parser.y"
    {
        yyerror("Invalid section declaration");
        current_section = NULL;
        yyclearin;
        yyerrok;
    }
#line 1851 "y.tab.c"
    break;

  case 15: /* field_list: field_list error ';'  */
#line 293 "parser.y"
    {
        yyerror("Invalid field declaration");
        yyclearin;
        yyerrok;
    }
#line 1861 "y.tab.c"
    break;

  case 16: /* field_declaration: FIELD IDENTIFIER ':' field_type field_attributes  */
#line 301 "parser.y"
    {
        if (current_section == NULL) {
            yyerror("Field must be inside a section");
            YYERROR;
        }
        if (check_duplicate_field((yyvsp[-3].str))) {
            yyerror("Duplicate field name");
            YYERROR;
        }
        add_field_to_section(current_section, (yyvsp[-3].str), (yyvsp[-1].field_type), &(yyvsp[0].field_attrs));
    }
#line 1877 "y.tab.c"
    break;

  case 17: /* field_type: TEXT  */
#line 314 "parser.y"
                     { (yyval.field_type) = FIELD_TEXT; }
#line 1883 "y.tab.c"
    break;

  case 18: /* field_type: EMAIL  */
#line 315 "parser.y"
                     { (yyval.field_type) = FIELD_EMAIL; }
#line 1889 "y.tab.c"
    break;

  case 19: /* field_type: PASSWORD  */
#line 316 "parser.y"
                     { (yyval.field_type) = FIELD_PASSWORD; }
#line 1895 "y.tab.c"
    break;

  case 20: /* field_type: NUMBER  */
#line 317 "parser.y"
                     { (yyval.field_type) = FIELD_NUMBER; }
#line 1901 "y.tab.c"
    break;

  case 21: /* field_type: TEXTAREA  */
#line 318 "parser.y"
                     { (yyval.field_type) = FIELD_TEXTAREA; }
#line 1907 "y.tab.c"
    break;

  case 22: /* field_type: DATE  */
#line 319 "parser.y"
                     { (yyval.field_type) = FIELD_DATE; }
#line 1913 "y.tab.c"
    break;

  case 23: /* field_type: CHECKBOX  */
#line 320 "parser.y"
                     { (yyval.field_type) = FIELD_CHECKBOX; }
#line 1919 "y.tab.c"
    break;

  case 24: /* field_type: DROPDOWN  */
#line 321 "parser.y"
                     { (yyval.field_type) = FIELD_DROPDOWN; }
#line 1925 "y.tab.c"
    break;

  case 25: /* field_type: RADIO  */
#line 322 "parser.y"
                     { (yyval.field_type) = FIELD_RADIO; }
#line 1931 "y.tab.c"
    break;

  case 26: /* field_type: FILE_TYPE  */
#line 323 "parser.y"
                      { (yyval.field_type) = FIELD_FILE; }
#line 1937 "y.tab.c"
    break;

  case 27: /* field_type: USERNAME  */
#line 324 "parser.y"
                     { (yyval.field_type) = FIELD_USERNAME; }
#line 1943 "y.tab.c"
    break;

  case 28: /* field_type: ADDRESS  */
#line 325 "parser.y"
                     { (yyval.field_type) = FIELD_ADDRESS; }
#line 1949 "y.tab.c"
    break;

  case 34: /* attribute: REQUIRED  */
#line 339 "parser.y"
             { (yyval.field_attrs).required = 1; }
#line 1955 "y.tab.c"
    break;

  case 35: /* attribute: OPTIONAL  */
#line 340 "parser.y"
               { (yyval.field_attrs).required = 0; }
#line 1961 "y.tab.c"
    break;

  case 36: /* attribute: MINLENGTH NUMBER_LITERAL  */
#line 341 "parser.y"
                               { (yyval.field_attrs).min_length = (yyvsp[0].num); }
#line 1967 "y.tab.c"
    break;

  case 37: /* attribute: MAXLENGTH NUMBER_LITERAL  */
#line 342 "parser.y"
                               { (yyval.field_attrs).max_length = (yyvsp[0].num); }
#line 1973 "y.tab.c"
    break;

  case 38: /* attribute: MIN NUMBER_LITERAL  */
#line 343 "parser.y"
                         { (yyval.field_attrs).min_value = (yyvsp[0].num); }
#line 1979 "y.tab.c"
    break;

  case 39: /* attribute: MAX NUMBER_LITERAL  */
#line 344 "parser.y"
                         { (yyval.field_attrs).max_value = (yyvsp[0].num); }
#line 1985 "y.tab.c"
    break;

  case 40: /* attribute: ROWS NUMBER_LITERAL  */
#line 345 "parser.y"
                          { (yyval.field_attrs).rows = (yyvsp[0].num); }
#line 1991 "y.tab.c"
    break;

  case 41: /* attribute: COLS NUMBER_LITERAL  */
#line 346 "parser.y"
                          { (yyval.field_attrs).cols = (yyvsp[0].num); }
#line 1997 "y.tab.c"
    break;

  case 42: /* attribute: PATTERN STRING_LITERAL  */
#line 347 "parser.y"
                             { (yyval.field_attrs).pattern = (yyvsp[0].str); }
#line 2003 "y.tab.c"
    break;

  case 43: /* attribute: DEFAULT STRING_LITERAL  */
#line 348 "parser.y"
                             { (yyval.field_attrs).default_value = (yyvsp[0].str); }
#line 2009 "y.tab.c"
    break;

  case 44: /* attribute: CONFIRM IDENTIFIER  */
#line 349 "parser.y"
                         { (yyval.field_attrs).confirm_field = (yyvsp[0].str); }
#line 2015 "y.tab.c"
    break;

  case 45: /* attribute: STRENGTH NUMBER_LITERAL  */
#line 350 "parser.y"
                              { (yyval.field_attrs).strength_required = (yyvsp[0].num); }
#line 2021 "y.tab.c"
    break;

  case 46: /* validation_block: VALIDATE '{' validation_rules '}'  */
#line 358 "parser.y"
    {
        // Validation block is already processed by the rules
    }
#line 2029 "y.tab.c"
    break;

  case 49: /* validation_rule: IF condition '{' ERROR STRING_LITERAL ';' '}'  */
#line 368 "parser.y"
    {
        ValidationRule* rule = malloc(sizeof(ValidationRule));
        if (!rule) {
            yyerror("Memory allocation failed for validation rule");
            YYERROR;
        }
        rule->condition = (yyvsp[-5].validation_rule);
        rule->error_message = (yyvsp[-2].str);
        rule->next = current_form->validation_rules;
        current_form->validation_rules = rule;
    }
#line 2045 "y.tab.c"
    break;

  case 50: /* condition: IDENTIFIER LT NUMBER_LITERAL  */
#line 382 "parser.y"
    {
        char* cond = malloc(50);
        sprintf(cond, "%s < %d", (yyvsp[-2].str), (yyvsp[0].num));
        (yyval.validation_rule) = cond;
    }
#line 2055 "y.tab.c"
    break;

  case 51: /* condition: IDENTIFIER GT NUMBER_LITERAL  */
#line 388 "parser.y"
    {
        char* cond = malloc(50);
        sprintf(cond, "%s > %d", (yyvsp[-2].str), (yyvsp[0].num));
        (yyval.validation_rule) = cond;
    }
#line 2065 "y.tab.c"
    break;

  case 52: /* condition: IDENTIFIER LTE NUMBER_LITERAL  */
#line 394 "parser.y"
    {
        char* cond = malloc(50);
        sprintf(cond, "%s <= %d", (yyvsp[-2].str), (yyvsp[0].num));
        (yyval.validation_rule) = cond;
    }
#line 2075 "y.tab.c"
    break;

  case 53: /* condition: IDENTIFIER GTE NUMBER_LITERAL  */
#line 400 "parser.y"
    {
        char* cond = malloc(50);
        sprintf(cond, "%s >= %d", (yyvsp[-2].str), (yyvsp[0].num));
        (yyval.validation_rule) = cond;
    }
#line 2085 "y.tab.c"
    break;

  case 54: /* condition: IDENTIFIER EQ NUMBER_LITERAL  */
#line 406 "parser.y"
    {
        char* cond = malloc(50);
        sprintf(cond, "%s == %d", (yyvsp[-2].str), (yyvsp[0].num));
        (yyval.validation_rule) = cond;
    }
#line 2095 "y.tab.c"
    break;

  case 55: /* condition: IDENTIFIER NEQ NUMBER_LITERAL  */
#line 412 "parser.y"
    {
        char* cond = malloc(50);
        sprintf(cond, "%s != %d", (yyvsp[-2].str), (yyvsp[0].num));
        (yyval.validation_rule) = cond;
    }
#line 2105 "y.tab.c"
    break;

  case 56: /* condition: IDENTIFIER EQ IDENTIFIER  */
#line 418 "parser.y"
    {
        char* cond = malloc(50);
        sprintf(cond, "%s == %s", (yyvsp[-2].str), (yyvsp[0].str));
        (yyval.validation_rule) = cond;
    }
#line 2115 "y.tab.c"
    break;

  case 57: /* metadata_declaration: META IDENTIFIER '=' STRING_LITERAL ';'  */
#line 426 "parser.y"
    {
        if (!current_form) {
            yyerror("Metadata must be inside a form");
            YYERROR;
        }
        add_metadata(current_form, (yyvsp[-3].str), (yyvsp[-1].str));
        free((yyvsp[-3].str));  // Free the key
        free((yyvsp[-1].str));  // Free the value
    }
#line 2129 "y.tab.c"
    break;


#line 2133 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 437 "parser.y"


void yyerror(const char *s) {
    fprintf(stderr, "Parser Error: %s at line %d\n", s, yylineno);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror(argv[1]);
            return 1;
        }
        yyin = file;
    }
    yyparse();
    cleanup_form(current_form);
    return 0;
}

int yywrap() {
    return 1;
}
