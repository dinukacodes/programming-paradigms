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
#line 1 "src/parser.y"

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
        
        free(form);
    }
    
    // Cleanup field name tracking
    for (int i = 0; i < field_name_count; i++) {
        if (field_names[i].name) free(field_names[i].name);
    }
    if (field_names) free(field_names);
    field_name_count = 0;
}

#line 242 "src/parser.tab.c"

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

#include "parser.tab.h"
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
  YYSYMBOL_IDENTIFIER = 30,                /* IDENTIFIER  */
  YYSYMBOL_NUMBER_LITERAL = 31,            /* NUMBER_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 32,            /* STRING_LITERAL  */
  YYSYMBOL_VALIDATE = 33,                  /* VALIDATE  */
  YYSYMBOL_IF = 34,                        /* IF  */
  YYSYMBOL_ERROR = 35,                     /* ERROR  */
  YYSYMBOL_LT = 36,                        /* LT  */
  YYSYMBOL_GT = 37,                        /* GT  */
  YYSYMBOL_LTE = 38,                       /* LTE  */
  YYSYMBOL_GTE = 39,                       /* GTE  */
  YYSYMBOL_EQ = 40,                        /* EQ  */
  YYSYMBOL_NEQ = 41,                       /* NEQ  */
  YYSYMBOL_AND = 42,                       /* AND  */
  YYSYMBOL_OR = 43,                        /* OR  */
  YYSYMBOL_44_ = 44,                       /* '{'  */
  YYSYMBOL_45_ = 45,                       /* '}'  */
  YYSYMBOL_46_ = 46,                       /* ';'  */
  YYSYMBOL_47_ = 47,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 48,                  /* $accept  */
  YYSYMBOL_form = 49,                      /* form  */
  YYSYMBOL_50_1 = 50,                      /* $@1  */
  YYSYMBOL_form_body = 51,                 /* form_body  */
  YYSYMBOL_form_item = 52,                 /* form_item  */
  YYSYMBOL_section = 53,                   /* section  */
  YYSYMBOL_section_header = 54,            /* section_header  */
  YYSYMBOL_field_list = 55,                /* field_list  */
  YYSYMBOL_field = 56,                     /* field  */
  YYSYMBOL_field_type = 57,                /* field_type  */
  YYSYMBOL_field_attributes = 58,          /* field_attributes  */
  YYSYMBOL_attribute = 59,                 /* attribute  */
  YYSYMBOL_validation_block = 60,          /* validation_block  */
  YYSYMBOL_validation_rules = 61,          /* validation_rules  */
  YYSYMBOL_validation_rule = 62,           /* validation_rule  */
  YYSYMBOL_condition = 63                  /* condition  */
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
#define YYLAST   77

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  16
/* YYNRULES -- Number of rules.  */
#define YYNRULES  52
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  91

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   298


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
       2,     2,     2,     2,     2,     2,     2,     2,    47,    46,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    44,     2,    45,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   199,   199,   198,   213,   214,   218,   219,   226,   230,
     234,   243,   258,   259,   260,   268,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   298,   301,
     322,   327,   332,   337,   342,   349,   354,   359,   364,   369,
     374,   379,   384,   395,   398,   399,   402,   412,   418,   424,
     430,   436,   442
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
  "COLS", "PATTERN", "DEFAULT", "CONFIRM", "STRENGTH", "IDENTIFIER",
  "NUMBER_LITERAL", "STRING_LITERAL", "VALIDATE", "IF", "ERROR", "LT",
  "GT", "LTE", "GTE", "EQ", "NEQ", "AND", "OR", "'{'", "'}'", "';'", "':'",
  "$accept", "form", "$@1", "form_body", "form_item", "section",
  "section_header", "field_list", "field", "field_type",
  "field_attributes", "attribute", "validation_block", "validation_rules",
  "validation_rule", "condition", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-28)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      38,   -27,    43,   -28,   -28,     2,   -28,    -3,    17,     4,
     -28,   -28,   -28,     1,   -28,   -28,   -28,     5,     6,    -5,
     -28,   -28,    -1,    19,   -28,   -28,     7,    22,   -28,   -28,
      -2,    10,   -28,     8,    25,    26,    27,    28,    29,    30,
      31,    11,   -28,   -28,   -28,   -28,   -28,   -28,    32,   -28,
     -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,
     -28,   -28,    16,   -13,    18,   -28,   -28,    34,    36,    37,
      39,    40,    41,    42,     0,    45,    46,   -28,   -28,   -28,
     -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,
     -28
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     1,     0,     4,     0,     0,     0,
       3,     5,     6,     0,     7,    11,    44,     0,    12,     0,
      10,     9,     0,     0,    43,    45,     0,     0,     8,    13,
       0,     0,    14,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    47,    48,    49,    50,    51,    52,     0,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,     0,     0,     0,    30,    31,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    15,    29,    46,
      35,    36,    37,    38,    39,    40,    32,    34,    33,    41,
      42
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,
     -28,   -28,   -28,   -28,   -28,   -28
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     5,     7,    11,    12,    13,    22,    29,    61,
      63,    78,    14,    19,    25,    31
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      26,     8,    17,     3,    27,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    23,
       9,    87,    88,    77,    34,    35,    36,    37,    38,    39,
      24,     1,    10,     4,    28,    18,     6,    15,    16,    30,
      20,    21,    33,    32,    40,    41,    42,    43,    44,    45,
      46,    47,    64,    79,    62,    80,    48,    81,    82,     0,
      83,    84,    85,     0,    86,    89,     0,    90
};

static const yytype_int8 yycheck[] =
{
       1,     4,     1,    30,     5,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    34,
      33,    31,    32,    46,    36,    37,    38,    39,    40,    41,
      45,     3,    45,     0,    45,    44,    44,    30,    44,    30,
      45,    45,    30,    46,    44,    47,    31,    31,    31,    31,
      31,    31,    46,    45,    32,    31,    35,    31,    31,    -1,
      31,    31,    31,    -1,    32,    30,    -1,    31
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    49,    30,     0,    50,    44,    51,     4,    33,
      45,    52,    53,    54,    60,    30,    44,     1,    44,    61,
      45,    45,    55,    34,    45,    62,     1,     5,    45,    56,
      30,    63,    46,    30,    36,    37,    38,    39,    40,    41,
      44,    47,    31,    31,    31,    31,    31,    31,    35,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    57,    32,    58,    46,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    46,    59,    45,
      31,    31,    31,    31,    31,    31,    32,    31,    32,    30,
      31
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    48,    50,    49,    51,    51,    52,    52,    53,    53,
      53,    54,    55,    55,    55,    56,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    58,    58,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    60,    61,    61,    62,    63,    63,    63,
      63,    63,    63
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     6,     0,     2,     1,     1,     4,     3,
       3,     2,     0,     2,     3,     6,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     2,
       1,     1,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     4,     0,     2,     7,     3,     3,     3,
       3,     3,     3
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
#line 199 "src/parser.y"
    {
        current_form = create_form((yyvsp[0].str));
        if (!current_form) {
            yyerror("Failed to create form");
            YYERROR;
        }
    }
#line 1625 "src/parser.tab.c"
    break;

  case 3: /* form: FORM IDENTIFIER $@1 '{' form_body '}'  */
#line 207 "src/parser.y"
    {
        generate_html(stdout);
        (yyval.form) = current_form;
    }
#line 1634 "src/parser.tab.c"
    break;

  case 8: /* section: section_header '{' field_list '}'  */
#line 227 "src/parser.y"
    {
        current_section = NULL;
    }
#line 1642 "src/parser.tab.c"
    break;

  case 9: /* section: section_header '{' '}'  */
#line 231 "src/parser.y"
    {
        current_section = NULL;
    }
#line 1650 "src/parser.tab.c"
    break;

  case 10: /* section: section_header error '}'  */
#line 235 "src/parser.y"
    {
        yyerror("Invalid section declaration");
        current_section = NULL;
        yyclearin;
        yyerrok;
    }
#line 1661 "src/parser.tab.c"
    break;

  case 11: /* section_header: SECTION IDENTIFIER  */
#line 244 "src/parser.y"
    {
        if (current_section != NULL) {
            yyerror("Nested sections are not allowed");
            YYERROR;
        }
        current_section = create_section((yyvsp[0].str));
        if (!current_section) {
            yyerror("Failed to create section");
            YYERROR;
        }
        add_section_to_form(current_form, current_section);
    }
#line 1678 "src/parser.tab.c"
    break;

  case 14: /* field_list: field_list error ';'  */
#line 261 "src/parser.y"
    {
        yyerror("Invalid field declaration");
        yyclearin;
        yyerrok;
    }
#line 1688 "src/parser.tab.c"
    break;

  case 15: /* field: FIELD IDENTIFIER ':' field_type field_attributes ';'  */
#line 269 "src/parser.y"
    {
        if (current_section == NULL) {
            yyerror("Field must be inside a section");
            YYERROR;
        }
        if (check_duplicate_field((yyvsp[-4].str))) {
            yyerror("Duplicate field name found");
            YYERROR;
        }
        add_field_to_section(current_section, (yyvsp[-4].str), (yyvsp[-2].field_type), &(yyvsp[-1].field_attrs));
        free((yyvsp[-4].str)); // Free the field name
    }
#line 1705 "src/parser.tab.c"
    break;

  case 16: /* field_type: TEXT  */
#line 283 "src/parser.y"
                     { (yyval.field_type) = FIELD_TEXT; }
#line 1711 "src/parser.tab.c"
    break;

  case 17: /* field_type: EMAIL  */
#line 284 "src/parser.y"
                     { (yyval.field_type) = FIELD_EMAIL; }
#line 1717 "src/parser.tab.c"
    break;

  case 18: /* field_type: PASSWORD  */
#line 285 "src/parser.y"
                     { (yyval.field_type) = FIELD_PASSWORD; }
#line 1723 "src/parser.tab.c"
    break;

  case 19: /* field_type: NUMBER  */
#line 286 "src/parser.y"
                     { (yyval.field_type) = FIELD_NUMBER; }
#line 1729 "src/parser.tab.c"
    break;

  case 20: /* field_type: TEXTAREA  */
#line 287 "src/parser.y"
                     { (yyval.field_type) = FIELD_TEXTAREA; }
#line 1735 "src/parser.tab.c"
    break;

  case 21: /* field_type: DATE  */
#line 288 "src/parser.y"
                     { (yyval.field_type) = FIELD_DATE; }
#line 1741 "src/parser.tab.c"
    break;

  case 22: /* field_type: CHECKBOX  */
#line 289 "src/parser.y"
                     { (yyval.field_type) = FIELD_CHECKBOX; }
#line 1747 "src/parser.tab.c"
    break;

  case 23: /* field_type: DROPDOWN  */
#line 290 "src/parser.y"
                     { (yyval.field_type) = FIELD_DROPDOWN; }
#line 1753 "src/parser.tab.c"
    break;

  case 24: /* field_type: RADIO  */
#line 291 "src/parser.y"
                     { (yyval.field_type) = FIELD_RADIO; }
#line 1759 "src/parser.tab.c"
    break;

  case 25: /* field_type: FILE_TYPE  */
#line 292 "src/parser.y"
                      { (yyval.field_type) = FIELD_FILE; }
#line 1765 "src/parser.tab.c"
    break;

  case 26: /* field_type: USERNAME  */
#line 293 "src/parser.y"
                     { (yyval.field_type) = FIELD_USERNAME; }
#line 1771 "src/parser.tab.c"
    break;

  case 27: /* field_type: ADDRESS  */
#line 294 "src/parser.y"
                     { (yyval.field_type) = FIELD_ADDRESS; }
#line 1777 "src/parser.tab.c"
    break;

  case 28: /* field_attributes: %empty  */
#line 298 "src/parser.y"
    {
        init_field_attributes(&(yyval.field_attrs));
    }
#line 1785 "src/parser.tab.c"
    break;

  case 29: /* field_attributes: field_attributes attribute  */
#line 302 "src/parser.y"
    {
        // Merge attributes
        if ((yyvsp[0].field_attrs).required != -1) (yyval.field_attrs).required = (yyvsp[0].field_attrs).required;
        if ((yyvsp[0].field_attrs).min_length != -1) (yyval.field_attrs).min_length = (yyvsp[0].field_attrs).min_length;
        if ((yyvsp[0].field_attrs).max_length != -1) (yyval.field_attrs).max_length = (yyvsp[0].field_attrs).max_length;
        if ((yyvsp[0].field_attrs).min_value != -1) (yyval.field_attrs).min_value = (yyvsp[0].field_attrs).min_value;
        if ((yyvsp[0].field_attrs).max_value != -1) (yyval.field_attrs).max_value = (yyvsp[0].field_attrs).max_value;
        if ((yyvsp[0].field_attrs).rows != -1) (yyval.field_attrs).rows = (yyvsp[0].field_attrs).rows;
        if ((yyvsp[0].field_attrs).cols != -1) (yyval.field_attrs).cols = (yyvsp[0].field_attrs).cols;
        if ((yyvsp[0].field_attrs).pattern) {
            if ((yyval.field_attrs).pattern) free((yyval.field_attrs).pattern);
            (yyval.field_attrs).pattern = (yyvsp[0].field_attrs).pattern;
        }
        if ((yyvsp[0].field_attrs).default_value) {
            if ((yyval.field_attrs).default_value) free((yyval.field_attrs).default_value);
            (yyval.field_attrs).default_value = (yyvsp[0].field_attrs).default_value;
        }
    }
#line 1808 "src/parser.tab.c"
    break;

  case 30: /* attribute: REQUIRED  */
#line 323 "src/parser.y"
    {
        init_field_attributes(&(yyval.field_attrs));
        (yyval.field_attrs).required = 1;
    }
#line 1817 "src/parser.tab.c"
    break;

  case 31: /* attribute: OPTIONAL  */
#line 328 "src/parser.y"
    {
        init_field_attributes(&(yyval.field_attrs));
        (yyval.field_attrs).required = 0;
    }
#line 1826 "src/parser.tab.c"
    break;

  case 32: /* attribute: PATTERN STRING_LITERAL  */
#line 333 "src/parser.y"
    {
        init_field_attributes(&(yyval.field_attrs));
        (yyval.field_attrs).pattern = (yyvsp[0].str);
    }
#line 1835 "src/parser.tab.c"
    break;

  case 33: /* attribute: DEFAULT STRING_LITERAL  */
#line 338 "src/parser.y"
    {
        init_field_attributes(&(yyval.field_attrs));
        (yyval.field_attrs).default_value = (yyvsp[0].str);
    }
#line 1844 "src/parser.tab.c"
    break;

  case 34: /* attribute: DEFAULT NUMBER_LITERAL  */
#line 343 "src/parser.y"
    {
        init_field_attributes(&(yyval.field_attrs));
        char buf[32];
        sprintf(buf, "%d", (yyvsp[0].num));
        (yyval.field_attrs).default_value = strdup(buf);
    }
#line 1855 "src/parser.tab.c"
    break;

  case 35: /* attribute: MINLENGTH NUMBER_LITERAL  */
#line 350 "src/parser.y"
    {
        init_field_attributes(&(yyval.field_attrs));
        (yyval.field_attrs).min_length = (yyvsp[0].num);
    }
#line 1864 "src/parser.tab.c"
    break;

  case 36: /* attribute: MAXLENGTH NUMBER_LITERAL  */
#line 355 "src/parser.y"
    {
        init_field_attributes(&(yyval.field_attrs));
        (yyval.field_attrs).max_length = (yyvsp[0].num);
    }
#line 1873 "src/parser.tab.c"
    break;

  case 37: /* attribute: MIN NUMBER_LITERAL  */
#line 360 "src/parser.y"
    {
        init_field_attributes(&(yyval.field_attrs));
        (yyval.field_attrs).min_value = (yyvsp[0].num);
    }
#line 1882 "src/parser.tab.c"
    break;

  case 38: /* attribute: MAX NUMBER_LITERAL  */
#line 365 "src/parser.y"
    {
        init_field_attributes(&(yyval.field_attrs));
        (yyval.field_attrs).max_value = (yyvsp[0].num);
    }
#line 1891 "src/parser.tab.c"
    break;

  case 39: /* attribute: ROWS NUMBER_LITERAL  */
#line 370 "src/parser.y"
    {
        init_field_attributes(&(yyval.field_attrs));
        (yyval.field_attrs).rows = (yyvsp[0].num);
    }
#line 1900 "src/parser.tab.c"
    break;

  case 40: /* attribute: COLS NUMBER_LITERAL  */
#line 375 "src/parser.y"
    {
        init_field_attributes(&(yyval.field_attrs));
        (yyval.field_attrs).cols = (yyvsp[0].num);
    }
#line 1909 "src/parser.tab.c"
    break;

  case 41: /* attribute: CONFIRM IDENTIFIER  */
#line 380 "src/parser.y"
    {
        init_field_attributes(&(yyval.field_attrs));
        (yyval.field_attrs).confirm_field = (yyvsp[0].str);
    }
#line 1918 "src/parser.tab.c"
    break;

  case 42: /* attribute: STRENGTH NUMBER_LITERAL  */
#line 385 "src/parser.y"
    {
        init_field_attributes(&(yyval.field_attrs));
        (yyval.field_attrs).strength_required = (yyvsp[0].num);
    }
#line 1927 "src/parser.tab.c"
    break;

  case 46: /* validation_rule: IF condition '{' ERROR STRING_LITERAL ';' '}'  */
#line 403 "src/parser.y"
    {
        ValidationRule* rule = malloc(sizeof(ValidationRule));
        rule->condition = (yyvsp[-5].validation_rule);
        rule->error_message = (yyvsp[-2].str);
        rule->next = current_form->validation_rules;
        current_form->validation_rules = rule;
    }
#line 1939 "src/parser.tab.c"
    break;

  case 47: /* condition: IDENTIFIER LT NUMBER_LITERAL  */
#line 413 "src/parser.y"
    {
        char* cond = malloc(50);
        sprintf(cond, "%s < %d", (yyvsp[-2].str), (yyvsp[0].num));
        (yyval.validation_rule) = cond;
    }
#line 1949 "src/parser.tab.c"
    break;

  case 48: /* condition: IDENTIFIER GT NUMBER_LITERAL  */
#line 419 "src/parser.y"
    {
        char* cond = malloc(50);
        sprintf(cond, "%s > %d", (yyvsp[-2].str), (yyvsp[0].num));
        (yyval.validation_rule) = cond;
    }
#line 1959 "src/parser.tab.c"
    break;

  case 49: /* condition: IDENTIFIER LTE NUMBER_LITERAL  */
#line 425 "src/parser.y"
    {
        char* cond = malloc(50);
        sprintf(cond, "%s <= %d", (yyvsp[-2].str), (yyvsp[0].num));
        (yyval.validation_rule) = cond;
    }
#line 1969 "src/parser.tab.c"
    break;

  case 50: /* condition: IDENTIFIER GTE NUMBER_LITERAL  */
#line 431 "src/parser.y"
    {
        char* cond = malloc(50);
        sprintf(cond, "%s >= %d", (yyvsp[-2].str), (yyvsp[0].num));
        (yyval.validation_rule) = cond;
    }
#line 1979 "src/parser.tab.c"
    break;

  case 51: /* condition: IDENTIFIER EQ NUMBER_LITERAL  */
#line 437 "src/parser.y"
    {
        char* cond = malloc(50);
        sprintf(cond, "%s == %d", (yyvsp[-2].str), (yyvsp[0].num));
        (yyval.validation_rule) = cond;
    }
#line 1989 "src/parser.tab.c"
    break;

  case 52: /* condition: IDENTIFIER NEQ NUMBER_LITERAL  */
#line 443 "src/parser.y"
    {
        char* cond = malloc(50);
        sprintf(cond, "%s != %d", (yyvsp[-2].str), (yyvsp[0].num));
        (yyval.validation_rule) = cond;
    }
#line 1999 "src/parser.tab.c"
    break;


#line 2003 "src/parser.tab.c"

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

#line 450 "src/parser.y"


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
