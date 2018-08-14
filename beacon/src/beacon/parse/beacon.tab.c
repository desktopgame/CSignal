/* A Bison parser, made by GNU Bison 3.0.5.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "beacon.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include "../ast/ast_new_factor.h"
#include "../ast/ast_new_operator.h"
#include "../ast/ast_new_stmt.h"
#include "../ast/ast_new_decl.h"
#include "../ast/constructor_chain_type.h"
#include "../ast/assign_operator_type.h"
#include "../ast/modifier_type.h"
#include "../ast/access_level.h"
#include "../util/string_pool.h"

#define YYDEBUG 1
#define YYERROR_VERBOSE 1

#line 83 "beacon.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "beacon.tab.h".  */
#ifndef YY_YY_BEACON_TAB_H_INCLUDED
# define YY_YY_BEACON_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CHAR_LITERAL = 258,
    STRING_LITERAL = 259,
    INT = 260,
    DOUBLE = 261,
    IDENT = 262,
    DOT = 263,
    COMMA = 264,
    COLON = 265,
    COLO_COLO = 266,
    LINE = 267,
    ADD = 268,
    SUB = 269,
    MUL = 270,
    DIV = 271,
    MOD = 272,
    NOT = 273,
    LSHIFT = 274,
    RSHIFT = 275,
    CHILDA = 276,
    EQUAL = 277,
    NOTEQUAL = 278,
    GT = 279,
    GE = 280,
    LT = 281,
    LE = 282,
    LGEN = 283,
    RGEN = 284,
    BIT_AND = 285,
    LOGIC_AND = 286,
    BIT_OR = 287,
    LOGIC_OR = 288,
    FINAL = 289,
    ASSIGN = 290,
    ADD_ASSIGN = 291,
    SUB_ASSIGN = 292,
    MUL_ASSIGN = 293,
    DIV_ASSIGN = 294,
    MOD_ASSIGN = 295,
    AND_ASSIGN = 296,
    OR_ASSIGN = 297,
    LSHIFT_ASSIGN = 298,
    RSHIFT_ASSIGN = 299,
    EXC_OR_ASSIGN = 300,
    INC = 301,
    DEC = 302,
    EXC_OR = 303,
    LCB = 304,
    RCB = 305,
    LRB = 306,
    RRB = 307,
    LSB = 308,
    RSB = 309,
    SEMI = 310,
    IMPORT = 311,
    VAR = 312,
    PROPERTY = 313,
    DEFSET = 314,
    DEFGET = 315,
    THIS_TOK = 316,
    SUPER_TOK = 317,
    TRUE_TOK = 318,
    FALSE_TOK = 319,
    NULL_TOK = 320,
    AS = 321,
    ABSTRACT = 322,
    OVERRIDE = 323,
    INTERFACE = 324,
    CLASS = 325,
    ENUM = 326,
    PUBLIC = 327,
    PRIVATE = 328,
    PROTECTED = 329,
    STATIC = 330,
    NATIVE = 331,
    NEW = 332,
    DEF = 333,
    ARROW = 334,
    NAMESPACE = 335,
    RETURN = 336,
    YIELD = 337,
    IF = 338,
    ELIF = 339,
    ELSE = 340,
    WHILE = 341,
    BREAK = 342,
    CONTINUE = 343,
    TRY = 344,
    CATCH = 345,
    THROW = 346,
    ASSERT_T = 347,
    DEFER = 348,
    INSTANCEOF = 349,
    OPERATOR = 350,
    BOUNDS_EXTENDS = 351,
    BOUNDS_SUPER = 352,
    PRE_INC = 353,
    PRE_DEC = 354,
    QUOTE = 355,
    FUNCCALL = 356,
    POST_INC = 357,
    POST_DEC = 358,
    NEGATIVE = 359,
    POSITIVE = 360,
    REF = 361,
    FORM_TYPE = 362
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 17 "beacon.y" /* yacc.c:355  */

	char char_value;
	string_view stringv_value;
	ast* ast_value;
	assign_operator_type assign_otype_value;
	constructor_chain_type chain_type_value;
	access_level access_level_value;

#line 240 "beacon.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_BEACON_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 271 "beacon.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2622

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  109
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  73
/* YYNRULES -- Number of rules.  */
#define YYNRULES  246
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  644

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   362

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     108,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   147,   147,   148,   149,   155,   157,   163,   167,   171,
     177,   184,   191,   195,   196,   197,   198,   202,   206,   214,
     217,   221,   225,   232,   233,   240,   247,   255,   258,   265,
     269,   276,   282,   286,   292,   296,   303,   307,   314,   318,
     326,   329,   333,   334,   341,   348,   352,   359,   360,   361,
     362,   363,   367,   371,   378,   382,   389,   393,   401,   404,
     408,   412,   419,   423,   427,   431,   438,   442,   446,   450,
     454,   458,   462,   466,   470,   475,   479,   484,   488,   493,
     497,   502,   506,   511,   516,   521,   525,   532,   536,   540,
     544,   551,   555,   559,   563,   570,   574,   578,   582,   589,
     593,   600,   604,   611,   615,   619,   623,   627,   634,   638,
     642,   649,   653,   660,   664,   671,   675,   679,   687,   690,
     697,   701,   708,   715,   719,   728,   732,   733,   736,   740,
     744,   748,   752,   756,   760,   764,   768,   772,   776,   780,
     784,   788,   792,   796,   800,   804,   808,   812,   816,   820,
     824,   828,   832,   836,   840,   844,   848,   852,   856,   860,
     864,   868,   872,   876,   880,   884,   888,   892,   896,   900,
     903,   907,   911,   915,   919,   923,   927,   931,   935,   939,
     943,   947,   951,   955,   959,   963,   967,   971,   975,   979,
     983,   987,   991,   997,   998,   999,  1000,  1001,  1005,  1009,
    1018,  1022,  1028,  1032,  1033,  1034,  1035,  1036,  1037,  1038,
    1039,  1040,  1041,  1042,  1043,  1044,  1045,  1048,  1054,  1060,
    1066,  1070,  1074,  1078,  1084,  1085,  1091,  1097,  1103,  1109,
    1115,  1119,  1125,  1131,  1137,  1141,  1147,  1153,  1157,  1163,
    1169,  1175,  1181,  1185,  1191,  1195,  1198
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CHAR_LITERAL", "STRING_LITERAL", "INT",
  "DOUBLE", "IDENT", "DOT", "COMMA", "COLON", "COLO_COLO", "LINE", "ADD",
  "SUB", "MUL", "DIV", "MOD", "NOT", "LSHIFT", "RSHIFT", "CHILDA", "EQUAL",
  "NOTEQUAL", "GT", "GE", "LT", "LE", "LGEN", "RGEN", "BIT_AND",
  "LOGIC_AND", "BIT_OR", "LOGIC_OR", "FINAL", "ASSIGN", "ADD_ASSIGN",
  "SUB_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "AND_ASSIGN",
  "OR_ASSIGN", "LSHIFT_ASSIGN", "RSHIFT_ASSIGN", "EXC_OR_ASSIGN", "INC",
  "DEC", "EXC_OR", "LCB", "RCB", "LRB", "RRB", "LSB", "RSB", "SEMI",
  "IMPORT", "VAR", "PROPERTY", "DEFSET", "DEFGET", "THIS_TOK", "SUPER_TOK",
  "TRUE_TOK", "FALSE_TOK", "NULL_TOK", "AS", "ABSTRACT", "OVERRIDE",
  "INTERFACE", "CLASS", "ENUM", "PUBLIC", "PRIVATE", "PROTECTED", "STATIC",
  "NATIVE", "NEW", "DEF", "ARROW", "NAMESPACE", "RETURN", "YIELD", "IF",
  "ELIF", "ELSE", "WHILE", "BREAK", "CONTINUE", "TRY", "CATCH", "THROW",
  "ASSERT_T", "DEFER", "INSTANCEOF", "OPERATOR", "BOUNDS_EXTENDS",
  "BOUNDS_SUPER", "PRE_INC", "PRE_DEC", "QUOTE", "FUNCCALL", "POST_INC",
  "POST_DEC", "NEGATIVE", "POSITIVE", "REF", "FORM_TYPE", "'\\n'",
  "$accept", "compilation_unit", "init_decl", "body_decl",
  "namespace_decl", "namespace_body", "namespace_member_decl",
  "namespace_member_decl_list", "namespace_member_decl_optional",
  "namespace_path", "import_list", "import", "parameterized_typename",
  "type_parameter_group", "type_parameter_list", "type_parameter",
  "abstract_class_decl", "class_decl", "enum_decl", "interface_decl",
  "access_member_tree_opt", "access_member_tree", "access_member_list",
  "member_define_list", "member_define", "constructor_define",
  "constructor_chain", "constructor_chain_type_T",
  "constructor_chain_optional", "function_define", "method_define",
  "operator_define", "field_define", "prop_set", "prop_get", "prop_define",
  "modifier_type_T_list", "modifier_type_T", "access_level_T",
  "ident_list", "parameter_list", "argument_list", "typename_group",
  "typename_list", "typename_T", "fqcn_part", "expression",
  "expression_nobrace", "lhs", "primary", "stmt_list", "stmt",
  "variable_decl_stmt", "variable_init_stmt", "inferenced_type_init_stmt",
  "if_stmt", "elif_list", "elif", "while_stmt", "break_stmt",
  "continue_stmt", "return_stmt", "throw_stmt", "try_stmt",
  "catch_stmt_list", "catch_stmt", "assert_stmt", "defer_stmt",
  "yield_return_stmt", "yield_break_stmt", "scope", "scope_optional",
  "stmt_term", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,    10
};
# endif

#define YYPACT_NINF -469

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-469)))

#define YYTABLE_NINF -123

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     989,   -96,    77,   896,  1080,    53,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  2545,  2545,  2545,  2545,  2545,
      41,  -469,  -469,  -469,  -469,  -469,   106,   109,   121,  2506,
     -48,  2545,  2545,    70,    70,   122,  2545,  2545,  1354,  -469,
    -469,  -469,   173,    35,  1275,   190,   380,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,    35,   126,   126,   126,   126,
    1436,   147,    35,   269,  -469,   215,  -469,  1275,  -469,  2545,
      70,  1484,   574,  -469,  -469,  1171,   245,  1275,   829,  -469,
      60,   344,   106,   351,  1090,  2545,  2545,  2545,  2545,  2545,
    2545,  2545,  2545,  2545,  2545,  2545,  2545,  2545,  2545,  2545,
    2545,  2545,  2545,   106,   106,  -469,    72,  2545,  2545,  2545,
    2545,  2545,  2545,  2545,  2545,  2545,  2545,  2545,  -469,  -469,
    2545,   309,   361,   318,   367,   241,  -469,  -469,  1275,  -469,
     155,  -469,  -469,  -469,  -469,  1263,  -469,   324,   245,  -469,
    -469,  2545,  -469,  2545,  -469,  -469,     7,  -469,    35,   323,
     326,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     341,   342,   343,   345,   346,   348,   349,   350,   352,   353,
      26,    26,     2,     2,     2,   254,   254,     5,     5,   183,
     183,   183,   183,   468,  2470,  1008,  2450,   635,  -469,  -469,
    -469,   355,    17,  2413,  2413,  2413,  2413,  2413,  2413,  2413,
    2413,  2413,  2413,  2413,  2413,  1275,   160,  -469,     8,  -469,
      42,  -469,   325,   395,   395,   400,   121,  -469,   241,   358,
    -469,  -469,  -469,  -469,  -469,  2545,   122,   188,  -469,  -469,
    -469,   106,  -469,  1275,  1275,   106,  -469,  -469,  -469,  2545,
    2525,  2545,  2545,  2545,   357,  2545,  2545,   359,  2545,  2545,
    2545,  2545,  2545,  2545,  2545,  2545,  2545,  2545,  2545,   106,
    2545,  -469,  -469,  -469,    28,   361,  -469,   347,    54,   403,
     395,   269,    34,   112,   363,   215,  -469,  -469,  1484,  -469,
     122,  -469,   406,  -469,  -469,  -469,  1521,  -469,  1566,  1611,
    1656,  1701,  -469,  1746,  1791,  -469,  1836,  1881,  1926,  1971,
    2016,  2061,  2106,  2151,  2196,  2241,  2286,    55,  2413,  -469,
    -469,   106,   106,   354,  -469,   169,  -469,   106,   293,   106,
     293,   420,  -469,  -469,  -469,   376,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,   356,   199,   422,   106,   106,   293,
      56,  -469,  -469,  -469,   381,   293,  -469,   424,   120,   382,
    -469,   159,   122,   106,  -469,  -469,   199,   197,   386,   293,
    -469,  -469,    63,   293,  -469,     4,  -469,  -469,   122,  -469,
     293,  -469,   389,  -469,    84,  -469,  -469,  -469,  -469,    80,
    1181,    63,  -469,  -469,  -469,  -469,  -469,  -469,    84,  -469,
     423,   390,  -469,  -469,  -469,   391,  -469,    84,   435,   269,
     393,   119,   396,   398,   404,   407,   419,   421,   426,   427,
     428,   429,   445,   446,   449,   450,   451,   452,   453,   454,
     455,   456,  -469,  -469,   439,   210,  -469,  -469,   464,   437,
     457,    44,   269,   106,    46,   106,   106,   106,   459,   106,
     106,   460,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   221,  2545,  -469,   465,   231,    48,   499,
      65,   467,    94,   440,   118,   123,   131,   136,   442,   141,
     153,   443,   167,   175,   180,   181,   198,   201,   206,   207,
     211,   222,   225,  2545,  -469,  2331,   231,   202,   242,   466,
     447,   226,   310,  -469,   199,   499,    52,   448,   106,   458,
     461,   462,   463,   106,   469,   470,   106,   471,   472,   473,
     475,   480,   496,   497,   498,   500,   501,   502,  2368,  -469,
     242,  -469,  -469,   258,   478,   476,   268,   106,   505,  -469,
    -469,   479,  -469,   199,   506,   227,   106,   199,   106,   106,
     106,   106,   199,   106,   106,   199,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,  -469,   481,  -469,
    -469,  -469,   307,  -469,  -469,   199,   106,   806,  -469,   106,
     513,   199,  -469,   199,   199,   199,   199,  -469,   199,   199,
    -469,   199,   199,   199,   199,   199,   199,   199,   199,   199,
     199,   199,  -469,  -469,  -469,  -469,   199,  -469,   235,   199,
     106,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,   199,  -469
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     6,    23,     4,    25,     1,
     195,   196,   193,   194,   123,     0,     0,     0,     0,     0,
       0,   167,   168,   197,   198,   199,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     3,
       8,     9,     0,   118,     0,   127,   169,   126,     7,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,     2,    24,   118,   128,   129,   162,   161,
       0,     0,   118,    27,    21,     0,   246,     0,   231,     0,
       0,     0,     0,   228,   229,     0,     0,     0,     0,   239,
       0,     0,     0,   170,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   202,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   170,   125,
       0,     0,     0,     0,     0,    19,    10,   230,     0,   241,
     220,   244,   245,   227,   243,     0,   200,     0,   233,   234,
     232,     0,   238,     0,   217,   124,     0,   120,   118,   118,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     130,   131,   132,   133,   134,   157,   158,   136,   137,   153,
     154,   155,   156,   138,   141,   135,   140,   139,   160,   159,
     164,     0,     0,   115,   142,   143,   144,   145,   146,   147,
     148,   149,   151,   152,   150,     0,     0,    31,     0,    29,
       0,    22,     0,     0,     0,     0,     0,    17,    20,     0,
      13,    14,    16,    15,   240,     0,     0,   222,   224,   242,
     201,     0,   235,     0,     0,     0,   119,   122,   171,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   163,   219,   166,     0,     0,    28,     0,     0,     0,
       0,    27,     0,     0,     0,     0,    18,    11,     0,   221,
       0,   225,     0,   237,   218,   121,     0,   192,     0,     0,
       0,     0,   190,     0,     0,   191,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   117,   165,
      30,     0,     0,     0,   113,     0,    26,     0,    40,     0,
      40,     0,    12,   226,   223,     0,   172,   173,   174,   175,
     176,   187,   188,   181,   182,   177,   178,   179,   180,   184,
     186,   183,   185,   189,     0,     0,     0,     0,     0,    40,
       0,   108,   109,   110,     0,    41,    42,     0,     0,     0,
     111,     0,     0,     0,    61,   114,     0,     0,     0,    40,
      38,    43,     0,    40,    34,     0,    36,   236,     0,    60,
      40,    32,     0,   107,     0,   105,   106,   103,   104,     0,
       0,    44,    45,    47,    48,    49,    50,    51,     0,   101,
       0,     0,   112,    37,   116,     0,    39,     0,     0,    27,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    46,   102,     0,     0,    35,    33,     0,     0,
       0,     0,    27,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    88,     0,     0,     0,    58,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    87,     0,     0,     0,     0,     0,
       0,     0,     0,    59,     0,    58,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    90,
       0,    91,    92,     0,     0,     0,     0,     0,     0,    57,
      56,     0,    53,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    89,     0,    95,
      96,   100,     0,    93,    94,     0,     0,     0,    52,     0,
       0,     0,    86,     0,     0,     0,     0,    84,     0,     0,
      85,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    99,    97,    98,    65,     0,    55,     0,     0,
       0,    66,    67,    68,    69,    70,    81,    82,    75,    76,
      71,    72,    73,    74,    78,    80,    77,    79,    83,    64,
      54,    63,     0,    62
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -469,  -469,  -469,   512,  -469,   244,   304,  -469,  -469,   313,
    -469,   538,  -196,  -275,  -469,   270,  -469,  -469,  -469,  -469,
    -323,  -469,   182,  -469,   145,  -469,  -469,  -469,    87,  -469,
    -469,  -469,  -469,    89,    38,  -469,   -46,   -58,  -468,  -469,
    -126,  -214,   -57,    20,   116,    -3,   678,  -469,  -469,  -469,
    -469,   -33,  -469,  -469,  -469,  -469,  -469,   366,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,   477,  -469,  -469,  -469,  -469,
      -8,  -310,   -30
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,    39,    40,   136,   227,   228,   229,    75,
       5,     6,   282,   133,   218,   219,   230,   231,   232,   233,
     364,   365,   366,   401,   402,   403,   513,   551,   514,    41,
     404,   405,   406,   508,   544,   407,   408,   409,   367,   371,
     278,   202,    93,   156,   279,    65,    44,    45,    46,    47,
     145,    48,    49,    50,    51,    52,   237,   238,    53,    54,
      55,    56,    57,    58,   148,   149,    59,    60,    61,    62,
     142,   143,    78
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      43,    43,   274,    83,    84,    89,   326,   369,   128,   509,
      94,   412,     7,    94,   115,   131,   245,   275,    95,    96,
      97,    98,    99,    72,   100,   101,   270,    86,   283,   104,
     105,   106,   107,    79,    94,    43,   378,   270,   509,    80,
     545,    97,    98,    99,   327,   374,    91,   137,    71,    14,
     139,    14,   146,    14,   413,    14,   392,   150,   152,    14,
     411,   246,   276,   322,   322,   245,   389,   415,   113,   271,
      14,   113,   545,   140,   322,    10,    11,    12,    13,    14,
     319,     8,    43,   328,   325,    15,    16,   419,    92,   158,
      17,    14,   113,    18,   277,   153,   479,   393,   483,   114,
     510,   247,   248,   322,   554,   379,   323,   354,   234,     2,
     158,   158,   240,    14,   393,   154,    73,   515,   393,    42,
      42,   394,   329,    19,   200,    76,   452,   322,    74,   245,
     395,   396,   322,    21,    22,    23,    24,    25,   397,   398,
     322,   399,    43,   317,   450,   322,   517,   395,   396,    26,
     322,   395,   396,   393,    42,   397,   398,   420,   400,   397,
     398,   330,   322,    10,    11,    12,    13,    14,   385,   383,
     519,    85,   201,    15,    16,   520,   322,   481,    17,   358,
      90,    18,   130,   521,   322,   272,   395,   396,   522,   322,
     322,    94,   113,   524,   397,   398,    95,    96,    97,    98,
      99,    42,   100,   101,   552,   525,   245,   322,   157,   386,
     322,    19,   273,   293,   294,   322,   322,   158,   359,   527,
     322,    21,    22,    23,    24,    25,   134,   528,   289,   198,
     199,   322,   529,   530,   322,   322,   322,    26,   158,   235,
     236,   116,   158,   588,   270,   474,   390,   592,    85,   113,
     531,    85,   597,   532,   141,   600,   503,   541,   533,   534,
     201,    42,    94,   535,   135,   475,   158,    95,    96,    97,
      98,    99,   235,   290,   536,   615,   504,   537,   548,   590,
     333,   621,   334,   622,   623,   624,   625,   640,   626,   627,
     507,   628,   629,   630,   631,   632,   633,   634,   635,   636,
     637,   638,   543,   361,   362,   363,   639,    85,   222,   641,
     223,   224,   225,   579,   361,   362,   363,    85,   158,   158,
     113,   226,   132,   583,   158,   480,   158,   482,   484,   485,
     486,   487,   643,   489,   490,   147,   492,   493,   494,   495,
     496,   497,   498,   499,   500,   501,   502,   360,   417,   368,
     443,   155,   511,   421,   158,   158,    85,   292,  -122,   443,
     216,   295,   613,   443,   387,   361,   362,   363,   217,   220,
     158,   549,   550,   618,   221,   241,    92,   249,   377,   158,
     414,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     555,   158,   259,   260,   261,   280,   262,   263,   158,   264,
     265,   266,   281,   267,   268,   158,   269,   284,   287,   302,
     324,   305,   331,   335,   158,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   321,   370,   372,   375,
     445,   380,   384,   357,   382,   373,   391,   355,   356,   416,
     446,   447,   449,   157,   451,   157,   473,   453,   158,   454,
     158,   158,   158,   158,   158,   455,   158,   158,   456,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     457,   476,   458,   376,   157,   158,    94,   459,   460,   461,
     462,    95,    96,    97,    98,    99,   477,   100,   101,   388,
     102,   103,   104,   105,   106,   107,   463,   464,   410,   542,
     465,   466,   467,   468,   469,   470,   471,   472,   478,   512,
     418,   488,   491,   158,   506,   158,    63,   410,   516,   518,
     158,   523,   526,   158,   444,   546,   547,   556,   581,   332,
     587,   612,   286,   448,   113,   580,   582,   558,   584,   285,
     559,   560,   561,    64,   158,   320,   442,   381,   563,   564,
     566,   567,   568,   158,   569,   158,   158,   158,   158,   570,
     158,   158,   114,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   614,   571,   572,   573,   578,   574,
     575,   576,    94,   158,   586,   589,   158,    95,    96,    97,
      98,    99,   620,   100,   101,   540,   102,   103,   104,   105,
     106,   107,   553,   291,   108,   109,   110,   111,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   158,     0,     0,
       0,     0,   112,    85,     0,   242,     0,     0,     0,   141,
       0,     0,     0,     0,   557,     0,     0,     0,     0,   562,
     113,     0,   565,    94,     0,     0,     0,     0,    95,    96,
      97,    98,    99,     0,   100,   101,     0,   102,   103,   104,
     105,   106,   107,   585,     0,   108,     0,     0,   114,     0,
       0,     0,   591,     0,   593,   594,   595,   596,     0,   598,
     599,     0,   601,   602,   603,   604,   605,   606,   607,   608,
     609,   610,   611,    66,    67,    68,    69,    70,     0,     0,
       0,   113,   616,     0,     0,   619,     0,    77,     0,    81,
      82,     0,     0,     0,    87,    88,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   114,
       0,     0,     0,     0,     0,     0,   642,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   138,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,     0,     0,     0,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,     0,     0,   215,    10,
      11,    12,    13,    14,     0,     0,     0,     0,     0,    15,
      16,     0,     0,     0,    17,     0,     0,    18,     0,   243,
       0,   244,     0,     0,     0,     0,     0,    94,     0,   151,
       0,     0,    95,    96,    97,    98,    99,     0,   100,   101,
       0,   102,   103,   104,   105,   106,   107,    19,   617,   108,
     109,   110,   111,     0,     0,     0,     0,    21,    22,    23,
      24,    25,     0,     0,     0,     0,     0,   112,     0,     0,
       0,     0,     0,    26,    76,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   203,   113,     9,     0,     0,    10,
      11,    12,    13,    14,     0,     0,   201,     0,     0,    15,
      16,     0,     0,   288,    17,     0,     0,    18,     0,     0,
       0,     0,     0,   114,     0,     0,     0,   296,   298,   299,
     300,   301,     0,   303,   304,     0,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,    19,   318,     0,
       0,     0,     0,    20,     0,     0,     0,    21,    22,    23,
      24,    25,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    26,    27,     0,    28,    29,    30,    31,
       0,     0,    32,    33,    34,    35,     0,    36,    37,    38,
       1,     0,    -5,    -5,    -5,    -5,    -5,     0,     0,     0,
       0,     0,    -5,    -5,     0,     0,     0,    -5,     0,     0,
      -5,     0,     0,     0,     0,     0,    94,     0,     0,     0,
       0,    95,    96,    97,    98,    99,     0,   100,   101,     0,
     102,   103,   104,   105,   106,   107,     0,     0,   108,     0,
      -5,     0,     0,     0,     0,     2,    -5,     0,     0,     0,
      -5,    -5,    -5,    -5,    -5,     0,   112,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    -5,    -5,     0,    -5,
      -5,    -5,    -5,     0,   113,    -5,    -5,    -5,    -5,     0,
      -5,    -5,    -5,    10,    11,    12,    13,    14,     0,     0,
       0,     0,     0,    15,    16,     0,     0,   159,    17,     0,
       0,    18,   114,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,     0,     0,
     175,   176,   177,   178,     0,     0,     0,     0,     0,     0,
       0,    19,     0,     0,     0,     0,     0,    20,   179,     0,
       0,    21,    22,    23,    24,    25,     0,     0,     0,     0,
       0,     0,   505,     0,     0,     0,     0,    26,    27,     0,
      28,    29,    30,    31,     0,     0,    32,    33,    34,    35,
       0,    36,    37,    38,    10,    11,    12,    13,    14,     0,
       0,   538,     0,     0,    15,    16,     0,     0,     0,    17,
       0,     0,    18,     0,   422,   423,   424,   425,   426,   427,
     428,   429,   430,   431,   432,   433,   434,   435,   436,     0,
       0,   437,   438,   439,   440,     0,     0,     0,     0,     0,
       0,   144,    19,     0,     0,     0,     0,     0,    20,   441,
       0,     0,    21,    22,    23,    24,    25,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    26,     0,
       0,     0,    29,    30,    31,     0,     0,    32,    33,    34,
      35,     0,    36,    37,    38,   203,    10,    11,    12,    13,
      14,     0,     0,     0,     0,     0,    15,    16,     0,     0,
       0,    17,     0,    94,    18,     0,     0,     0,    95,    96,
      97,    98,    99,     0,   100,   101,     0,   102,   103,   104,
     105,   106,   107,     0,     0,   108,   109,   110,   111,     0,
       0,     0,     0,   239,    19,     0,     0,     0,     0,     0,
      20,     0,     0,   112,    21,    22,    23,    24,    25,     0,
      76,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      26,   113,     0,     0,    29,    30,    31,     0,     0,    32,
      33,    34,    35,     0,    36,    37,    38,    10,    11,    12,
      13,    14,     0,     0,     0,     0,     0,    15,    16,   114,
       0,     0,    17,     0,     0,    18,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    19,     0,     0,     0,     0,
       0,    20,     0,     0,     0,    21,    22,    23,    24,    25,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    26,     0,     0,     0,    29,    30,    31,     0,     0,
      32,    33,    34,    35,    94,    36,    37,    38,     0,    95,
      96,    97,    98,    99,     0,   100,   101,     0,   102,   103,
     104,   105,   106,   107,     0,     0,   108,   109,   110,   111,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   112,     0,     0,     0,   129,     0,
       0,     0,    94,     0,     0,     0,     0,    95,    96,    97,
      98,    99,   113,   100,   101,     0,   102,   103,   104,   105,
     106,   107,     0,     0,   108,   109,   110,   111,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    94,
     114,     0,   112,    85,    95,    96,    97,    98,    99,     0,
     100,   101,     0,   102,   103,   104,   105,   106,   107,     0,
     113,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   112,
       0,     0,     0,   336,    94,     0,     0,     0,   114,    95,
      96,    97,    98,    99,     0,   100,   101,   113,   102,   103,
     104,   105,   106,   107,     0,     0,   108,   109,   110,   111,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   112,   114,     0,     0,   337,    94,
       0,     0,     0,     0,    95,    96,    97,    98,    99,     0,
     100,   101,   113,   102,   103,   104,   105,   106,   107,     0,
       0,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   112,
     114,     0,     0,   338,    94,     0,     0,     0,     0,    95,
      96,    97,    98,    99,     0,   100,   101,   113,   102,   103,
     104,   105,   106,   107,     0,     0,   108,   109,   110,   111,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   112,   114,     0,     0,   339,    94,
       0,     0,     0,     0,    95,    96,    97,    98,    99,     0,
     100,   101,   113,   102,   103,   104,   105,   106,   107,     0,
       0,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   112,
     114,     0,     0,   340,    94,     0,     0,     0,     0,    95,
      96,    97,    98,    99,     0,   100,   101,   113,   102,   103,
     104,   105,   106,   107,     0,     0,   108,   109,   110,   111,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   112,   114,     0,     0,   341,    94,
       0,     0,     0,     0,    95,    96,    97,    98,    99,     0,
     100,   101,   113,   102,   103,   104,   105,   106,   107,     0,
       0,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   112,
     114,     0,     0,   342,    94,     0,     0,     0,     0,    95,
      96,    97,    98,    99,     0,   100,   101,   113,   102,   103,
     104,   105,   106,   107,     0,     0,   108,   109,   110,   111,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   112,   114,     0,     0,   343,    94,
       0,     0,     0,     0,    95,    96,    97,    98,    99,     0,
     100,   101,   113,   102,   103,   104,   105,   106,   107,     0,
       0,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   112,
     114,     0,     0,   344,    94,     0,     0,     0,     0,    95,
      96,    97,    98,    99,     0,   100,   101,   113,   102,   103,
     104,   105,   106,   107,     0,     0,   108,   109,   110,   111,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   112,   114,     0,     0,   345,    94,
       0,     0,     0,     0,    95,    96,    97,    98,    99,     0,
     100,   101,   113,   102,   103,   104,   105,   106,   107,     0,
       0,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   112,
     114,     0,     0,   346,    94,     0,     0,     0,     0,    95,
      96,    97,    98,    99,     0,   100,   101,   113,   102,   103,
     104,   105,   106,   107,     0,     0,   108,   109,   110,   111,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   112,   114,     0,     0,   347,    94,
       0,     0,     0,     0,    95,    96,    97,    98,    99,     0,
     100,   101,   113,   102,   103,   104,   105,   106,   107,     0,
       0,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   112,
     114,     0,     0,   348,    94,     0,     0,     0,     0,    95,
      96,    97,    98,    99,     0,   100,   101,   113,   102,   103,
     104,   105,   106,   107,     0,     0,   108,   109,   110,   111,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   112,   114,     0,     0,   349,    94,
       0,     0,     0,     0,    95,    96,    97,    98,    99,     0,
     100,   101,   113,   102,   103,   104,   105,   106,   107,     0,
       0,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   112,
     114,     0,     0,   350,    94,     0,     0,     0,     0,    95,
      96,    97,    98,    99,     0,   100,   101,   113,   102,   103,
     104,   105,   106,   107,     0,     0,   108,   109,   110,   111,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   112,   114,     0,     0,   351,    94,
       0,     0,     0,     0,    95,    96,    97,    98,    99,     0,
     100,   101,   113,   102,   103,   104,   105,   106,   107,     0,
       0,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   112,
     114,     0,     0,   352,    94,     0,     0,     0,     0,    95,
      96,    97,    98,    99,     0,   100,   101,   113,   102,   103,
     104,   105,   106,   107,     0,     0,   108,   109,   110,   111,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   112,   114,     0,     0,   353,    94,
       0,     0,     0,     0,    95,    96,    97,    98,    99,     0,
     100,   101,   113,   102,   103,   104,   105,   106,   107,     0,
       0,   108,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    94,     0,     0,   112,
     114,    95,    96,    97,    98,    99,   539,   100,   101,     0,
     102,   103,   104,   105,   106,   107,     0,   113,   108,   109,
     110,   111,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   112,     0,     0,     0,
       0,    94,     0,   577,     0,   114,    95,    96,    97,    98,
      99,     0,   100,   101,   113,   102,   103,   104,   105,   106,
     107,     0,     0,   108,   109,   110,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    94,     0,
       0,   112,   114,    95,    96,    97,    98,    99,     0,   100,
     101,     0,   102,   103,   104,   105,   106,   107,    94,   113,
     108,   109,   110,    95,    96,    97,    98,    99,     0,   100,
     101,     0,   102,   103,   104,   105,   106,   107,   112,     0,
     108,     0,   110,     0,     0,     0,     0,   114,     0,    10,
      11,    12,    13,    14,     0,     0,   113,     0,   112,    15,
      16,     0,     0,     0,    17,     0,     0,    18,    10,    11,
      12,    13,    14,     0,     0,     0,   113,     0,    15,    16,
       0,     0,     0,    17,   114,     0,    18,     0,    10,    11,
      12,    13,    14,     0,     0,     0,     0,    19,    15,    16,
       0,    76,     0,    17,   114,     0,    18,    21,    22,    23,
      24,    25,     0,     0,     0,     0,    19,   297,     0,     0,
       0,     0,     0,    26,     0,     0,    21,    22,    23,    24,
      25,     0,     0,     0,     0,     0,    19,     0,     0,     0,
       0,     0,    26,     0,     0,     0,    21,    22,    23,    24,
      25,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    26
};

static const yytype_int16 yycheck[] =
{
       3,     4,   216,    33,    34,    38,   281,   330,    65,   477,
       8,     7,   108,     8,    44,    72,     9,     9,    13,    14,
      15,    16,    17,    26,    19,    20,     9,    35,   224,    24,
      25,    26,    27,    81,     8,    38,   359,     9,   506,    87,
     508,    15,    16,    17,    10,   355,    11,    77,     7,     7,
      80,     7,    85,     7,    50,     7,   379,    87,    88,     7,
     383,    54,    54,     9,     9,     9,   376,   390,    66,    52,
       7,    66,   540,    81,     9,     3,     4,     5,     6,     7,
      52,     4,    85,    49,   280,    13,    14,     7,    53,    92,
      18,     7,    66,    21,    52,    35,    52,    34,    52,    94,
      52,   158,   159,     9,    52,    49,    52,    52,   138,    56,
     113,   114,   145,     7,    34,    55,     7,    52,    34,     3,
       4,    58,    10,    51,    52,    55,     7,     9,     7,     9,
      67,    68,     9,    61,    62,    63,    64,    65,    75,    76,
       9,    78,   145,   269,   419,     9,    52,    67,    68,    77,
       9,    67,    68,    34,    38,    75,    76,    77,    95,    75,
      76,    49,     9,     3,     4,     5,     6,     7,     9,    49,
      52,    49,   100,    13,    14,    52,     9,   452,    18,    10,
       7,    21,    35,    52,     9,   215,    67,    68,    52,     9,
       9,     8,    66,    52,    75,    76,    13,    14,    15,    16,
      17,    85,    19,    20,   514,    52,     9,     9,    92,    50,
       9,    51,    52,   243,   244,     9,     9,   220,    49,    52,
       9,    61,    62,    63,    64,    65,    11,    52,   236,   113,
     114,     9,    52,    52,     9,     9,     9,    77,   241,    84,
      85,    51,   245,   553,     9,    35,    49,   557,    49,    66,
      52,    49,   562,    52,    55,   565,    35,    55,    52,    52,
     100,   145,     8,    52,    49,    55,   269,    13,    14,    15,
      16,    17,    84,    85,    52,   585,    55,    52,    52,    52,
     288,   591,   290,   593,   594,   595,   596,    52,   598,   599,
      59,   601,   602,   603,   604,   605,   606,   607,   608,   609,
     610,   611,    60,    72,    73,    74,   616,    49,    67,   619,
      69,    70,    71,    55,    72,    73,    74,    49,   321,   322,
      66,    80,    53,    55,   327,   451,   329,   453,   454,   455,
     456,   457,   642,   459,   460,    90,   462,   463,   464,   465,
     466,   467,   468,   469,   470,   471,   472,   327,   394,   329,
     408,     7,   478,   399,   357,   358,    49,   241,     7,   417,
      51,   245,    55,   421,   372,    72,    73,    74,     7,    51,
     373,    61,    62,   587,     7,    51,    53,    51,   358,   382,
     388,    51,    51,    51,    51,    51,    51,    51,    51,    51,
     516,   394,    51,    51,    51,    70,    51,    51,   401,    51,
      51,    51,     7,    51,    51,   408,    51,     7,    50,    52,
       7,    52,    49,     7,   417,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    79,     7,    52,     7,
       7,    50,    50,    79,    10,    79,    50,   321,   322,    50,
      50,    50,     7,   327,    51,   329,     7,    51,   451,    51,
     453,   454,   455,   456,   457,    51,   459,   460,    51,   462,
     463,   464,   465,   466,   467,   468,   469,   470,   471,   472,
      51,     7,    51,   357,   358,   478,     8,    51,    51,    51,
      51,    13,    14,    15,    16,    17,    49,    19,    20,   373,
      22,    23,    24,    25,    26,    27,    51,    51,   382,   507,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    10,
     394,    52,    52,   516,    49,   518,     4,   401,    51,    79,
     523,    79,    79,   526,   408,    59,    79,    79,    50,   285,
      51,    50,   228,   417,    66,   543,    60,    79,   546,   226,
      79,    79,    79,     5,   547,   275,   401,   365,    79,    79,
      79,    79,    79,   556,    79,   558,   559,   560,   561,    79,
     563,   564,    94,   566,   567,   568,   569,   570,   571,   572,
     573,   574,   575,   576,   582,    79,    79,    79,   540,    79,
      79,    79,     8,   586,    79,    79,   589,    13,    14,    15,
      16,    17,    79,    19,    20,   506,    22,    23,    24,    25,
      26,    27,   515,   237,    30,    31,    32,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   620,    -1,    -1,
      -1,    -1,    48,    49,    -1,   148,    -1,    -1,    -1,    55,
      -1,    -1,    -1,    -1,   518,    -1,    -1,    -1,    -1,   523,
      66,    -1,   526,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    -1,    22,    23,    24,
      25,    26,    27,   547,    -1,    30,    -1,    -1,    94,    -1,
      -1,    -1,   556,    -1,   558,   559,   560,   561,    -1,   563,
     564,    -1,   566,   567,   568,   569,   570,   571,   572,   573,
     574,   575,   576,    15,    16,    17,    18,    19,    -1,    -1,
      -1,    66,   586,    -1,    -1,   589,    -1,    29,    -1,    31,
      32,    -1,    -1,    -1,    36,    37,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,
      -1,    -1,    -1,    -1,    -1,    -1,   620,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,    -1,    -1,    -1,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,    -1,    -1,   130,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    -1,    -1,    13,
      14,    -1,    -1,    -1,    18,    -1,    -1,    21,    -1,   151,
      -1,   153,    -1,    -1,    -1,    -1,    -1,     8,    -1,    10,
      -1,    -1,    13,    14,    15,    16,    17,    -1,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,    51,    52,    30,
      31,    32,    33,    -1,    -1,    -1,    -1,    61,    62,    63,
      64,    65,    -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,
      -1,    -1,    -1,    77,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   216,    66,     0,    -1,    -1,     3,
       4,     5,     6,     7,    -1,    -1,   100,    -1,    -1,    13,
      14,    -1,    -1,   235,    18,    -1,    -1,    21,    -1,    -1,
      -1,    -1,    -1,    94,    -1,    -1,    -1,   249,   250,   251,
     252,   253,    -1,   255,   256,    -1,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,    51,   270,    -1,
      -1,    -1,    -1,    57,    -1,    -1,    -1,    61,    62,    63,
      64,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    78,    -1,    80,    81,    82,    83,
      -1,    -1,    86,    87,    88,    89,    -1,    91,    92,    93,
       1,    -1,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      -1,    -1,    13,    14,    -1,    -1,    -1,    18,    -1,    -1,
      21,    -1,    -1,    -1,    -1,    -1,     8,    -1,    -1,    -1,
      -1,    13,    14,    15,    16,    17,    -1,    19,    20,    -1,
      22,    23,    24,    25,    26,    27,    -1,    -1,    30,    -1,
      51,    -1,    -1,    -1,    -1,    56,    57,    -1,    -1,    -1,
      61,    62,    63,    64,    65,    -1,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    77,    78,    -1,    80,
      81,    82,    83,    -1,    66,    86,    87,    88,    89,    -1,
      91,    92,    93,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    -1,    -1,    13,    14,    -1,    -1,     7,    18,    -1,
      -1,    21,    94,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    -1,    -1,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    57,    48,    -1,
      -1,    61,    62,    63,    64,    65,    -1,    -1,    -1,    -1,
      -1,    -1,   474,    -1,    -1,    -1,    -1,    77,    78,    -1,
      80,    81,    82,    83,    -1,    -1,    86,    87,    88,    89,
      -1,    91,    92,    93,     3,     4,     5,     6,     7,    -1,
      -1,   503,    -1,    -1,    13,    14,    -1,    -1,    -1,    18,
      -1,    -1,    21,    -1,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    51,    -1,    -1,    -1,    -1,    -1,    57,    48,
      -1,    -1,    61,    62,    63,    64,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,
      -1,    -1,    81,    82,    83,    -1,    -1,    86,    87,    88,
      89,    -1,    91,    92,    93,   587,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    -1,    -1,    13,    14,    -1,    -1,
      -1,    18,    -1,     8,    21,    -1,    -1,    -1,    13,    14,
      15,    16,    17,    -1,    19,    20,    -1,    22,    23,    24,
      25,    26,    27,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,    -1,    -1,    50,    51,    -1,    -1,    -1,    -1,    -1,
      57,    -1,    -1,    48,    61,    62,    63,    64,    65,    -1,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      77,    66,    -1,    -1,    81,    82,    83,    -1,    -1,    86,
      87,    88,    89,    -1,    91,    92,    93,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    -1,    -1,    13,    14,    94,
      -1,    -1,    18,    -1,    -1,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,
      -1,    57,    -1,    -1,    -1,    61,    62,    63,    64,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    -1,    -1,    -1,    81,    82,    83,    -1,    -1,
      86,    87,    88,    89,     8,    91,    92,    93,    -1,    13,
      14,    15,    16,    17,    -1,    19,    20,    -1,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,    52,    -1,
      -1,    -1,     8,    -1,    -1,    -1,    -1,    13,    14,    15,
      16,    17,    66,    19,    20,    -1,    22,    23,    24,    25,
      26,    27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,
      94,    -1,    48,    49,    13,    14,    15,    16,    17,    -1,
      19,    20,    -1,    22,    23,    24,    25,    26,    27,    -1,
      66,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      -1,    -1,    -1,    52,     8,    -1,    -1,    -1,    94,    13,
      14,    15,    16,    17,    -1,    19,    20,    66,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    94,    -1,    -1,    52,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,
      19,    20,    66,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      94,    -1,    -1,    52,     8,    -1,    -1,    -1,    -1,    13,
      14,    15,    16,    17,    -1,    19,    20,    66,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    94,    -1,    -1,    52,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,
      19,    20,    66,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      94,    -1,    -1,    52,     8,    -1,    -1,    -1,    -1,    13,
      14,    15,    16,    17,    -1,    19,    20,    66,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    94,    -1,    -1,    52,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,
      19,    20,    66,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      94,    -1,    -1,    52,     8,    -1,    -1,    -1,    -1,    13,
      14,    15,    16,    17,    -1,    19,    20,    66,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    94,    -1,    -1,    52,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,
      19,    20,    66,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      94,    -1,    -1,    52,     8,    -1,    -1,    -1,    -1,    13,
      14,    15,    16,    17,    -1,    19,    20,    66,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    94,    -1,    -1,    52,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,
      19,    20,    66,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      94,    -1,    -1,    52,     8,    -1,    -1,    -1,    -1,    13,
      14,    15,    16,    17,    -1,    19,    20,    66,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    94,    -1,    -1,    52,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,
      19,    20,    66,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      94,    -1,    -1,    52,     8,    -1,    -1,    -1,    -1,    13,
      14,    15,    16,    17,    -1,    19,    20,    66,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    94,    -1,    -1,    52,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,
      19,    20,    66,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      94,    -1,    -1,    52,     8,    -1,    -1,    -1,    -1,    13,
      14,    15,    16,    17,    -1,    19,    20,    66,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    94,    -1,    -1,    52,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,
      19,    20,    66,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      94,    -1,    -1,    52,     8,    -1,    -1,    -1,    -1,    13,
      14,    15,    16,    17,    -1,    19,    20,    66,    22,    23,
      24,    25,    26,    27,    -1,    -1,    30,    31,    32,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    94,    -1,    -1,    52,     8,
      -1,    -1,    -1,    -1,    13,    14,    15,    16,    17,    -1,
      19,    20,    66,    22,    23,    24,    25,    26,    27,    -1,
      -1,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     8,    -1,    -1,    48,
      94,    13,    14,    15,    16,    17,    55,    19,    20,    -1,
      22,    23,    24,    25,    26,    27,    -1,    66,    30,    31,
      32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,
      -1,     8,    -1,    55,    -1,    94,    13,    14,    15,    16,
      17,    -1,    19,    20,    66,    22,    23,    24,    25,    26,
      27,    -1,    -1,    30,    31,    32,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,    -1,
      -1,    48,    94,    13,    14,    15,    16,    17,    -1,    19,
      20,    -1,    22,    23,    24,    25,    26,    27,     8,    66,
      30,    31,    32,    13,    14,    15,    16,    17,    -1,    19,
      20,    -1,    22,    23,    24,    25,    26,    27,    48,    -1,
      30,    -1,    32,    -1,    -1,    -1,    -1,    94,    -1,     3,
       4,     5,     6,     7,    -1,    -1,    66,    -1,    48,    13,
      14,    -1,    -1,    -1,    18,    -1,    -1,    21,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    66,    -1,    13,    14,
      -1,    -1,    -1,    18,    94,    -1,    21,    -1,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    -1,    51,    13,    14,
      -1,    55,    -1,    18,    94,    -1,    21,    61,    62,    63,
      64,    65,    -1,    -1,    -1,    -1,    51,    52,    -1,    -1,
      -1,    -1,    -1,    77,    -1,    -1,    61,    62,    63,    64,
      65,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    77,    -1,    -1,    -1,    61,    62,    63,    64,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    77
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    56,   110,   111,   119,   120,   108,     4,     0,
       3,     4,     5,     6,     7,    13,    14,    18,    21,    51,
      57,    61,    62,    63,    64,    65,    77,    78,    80,    81,
      82,    83,    86,    87,    88,    89,    91,    92,    93,   112,
     113,   138,   153,   154,   155,   156,   157,   158,   160,   161,
     162,   163,   164,   167,   168,   169,   170,   171,   172,   175,
     176,   177,   178,   112,   120,   154,   155,   155,   155,   155,
     155,     7,   154,     7,     7,   118,    55,   155,   181,    81,
      87,   155,   155,   181,   181,    49,   179,   155,   155,   160,
       7,    11,    53,   151,     8,    13,    14,    15,    16,    17,
      19,    20,    22,    23,    24,    25,    26,    27,    30,    31,
      32,    33,    48,    66,    94,   181,    51,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,   151,    52,
      35,   151,    53,   122,    11,    49,   114,   181,   155,   181,
     179,    55,   179,   180,    50,   159,   160,    90,   173,   174,
     181,    10,   181,    35,    55,     7,   152,   153,   154,     7,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    30,    31,    32,    33,    48,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   153,   153,
      52,   100,   150,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,    51,     7,   123,   124,
      51,     7,    67,    69,    70,    71,    80,   115,   116,   117,
     125,   126,   127,   128,   181,    84,    85,   165,   166,    50,
     160,    51,   174,   155,   155,     9,    54,   151,   151,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
       9,    52,   181,    52,   150,     9,    54,    52,   149,   153,
      70,     7,   121,   121,     7,   118,   115,    50,   155,   179,
      85,   166,   153,   181,   181,   153,   155,    52,   155,   155,
     155,   155,    52,   155,   155,    52,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   149,   155,    52,
     124,    79,     9,    52,     7,   121,   122,    10,    49,    10,
      49,    49,   114,   179,   179,     7,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,   153,   153,    79,    10,    49,
     152,    72,    73,    74,   129,   130,   131,   147,   152,   129,
       7,   148,    52,    79,   180,     7,   153,   152,   129,    49,
      50,   131,    10,    49,    50,     9,    50,   179,   153,   180,
      49,    50,   129,    34,    58,    67,    68,    75,    76,    78,
      95,   132,   133,   134,   139,   140,   141,   144,   145,   146,
     153,   129,     7,    50,   179,   129,    50,   145,   153,     7,
      77,   145,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    30,    31,    32,
      33,    48,   133,   146,   153,     7,    50,    50,   153,     7,
     122,    51,     7,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,     7,    35,    55,     7,    49,    51,    52,
     149,   122,   149,    52,   149,   149,   149,   149,    52,   149,
     149,    52,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,    35,    55,   155,    49,    59,   142,   147,
      52,   149,    10,   135,   137,    52,    51,    52,    79,    52,
      52,    52,    52,    79,    52,    52,    79,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,   155,    55,
     142,    55,   179,    60,   143,   147,    59,    79,    52,    61,
      62,   136,   180,   137,    52,   149,    79,   153,    79,    79,
      79,    79,   153,    79,    79,   153,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    55,   143,    55,
     179,    50,    60,    55,   179,   153,    79,    51,   180,    79,
      52,   153,   180,   153,   153,   153,   153,   180,   153,   153,
     180,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,    50,    55,   179,   180,   153,    52,   150,   153,
      79,   180,   180,   180,   180,   180,   180,   180,   180,   180,
     180,   180,   180,   180,   180,   180,   180,   180,   180,   180,
      52,   180,   153,   180
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   109,   110,   110,   110,   111,   111,   112,   112,   112,
     113,   114,   115,   115,   115,   115,   115,   116,   116,   117,
     117,   118,   118,   119,   119,   120,   121,   122,   122,   123,
     123,   124,   125,   125,   126,   126,   127,   127,   128,   128,
     129,   129,   130,   130,   131,   132,   132,   133,   133,   133,
     133,   133,   134,   134,   135,   135,   136,   136,   137,   137,
     138,   138,   139,   139,   139,   139,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   141,   141,   141,
     141,   142,   142,   142,   142,   143,   143,   143,   143,   144,
     144,   145,   145,   146,   146,   146,   146,   146,   147,   147,
     147,   148,   148,   149,   149,   150,   150,   150,   151,   151,
     152,   152,   153,   154,   154,   155,   155,   155,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   158,   158,   158,   158,   158,   158,   158,
     159,   159,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   161,   162,   163,
     164,   164,   164,   164,   165,   165,   166,   167,   168,   169,
     170,   170,   171,   172,   173,   173,   174,   175,   175,   176,
     177,   178,   179,   179,   180,   180,   181
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     2,     0,     1,     1,     1,     1,
       3,     3,     3,     1,     1,     1,     1,     1,     2,     0,
       1,     1,     3,     1,     2,     2,     2,     0,     3,     1,
       3,     1,     6,     8,     5,     7,     5,     6,     5,     7,
       0,     1,     1,     2,     3,     1,     2,     1,     1,     1,
       1,     1,     7,     6,     5,     4,     1,     1,     0,     1,
       9,     8,    10,     9,     9,     8,     8,     8,     8,     8,
       8,     8,     8,     8,     8,     8,     8,     8,     8,     8,
       8,     8,     8,     8,     7,     7,     7,     4,     3,     6,
       5,     2,     2,     3,     3,     2,     2,     3,     3,     8,
       7,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     2,     4,     1,     7,     3,     0,     3,
       1,     3,     2,     1,     3,     3,     1,     1,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     4,     3,     6,     5,     1,     1,     1,
       2,     4,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       5,     5,     5,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     5,     5,
       3,     5,     4,     6,     1,     2,     3,     3,     2,     2,
       3,     2,     3,     3,     1,     2,     6,     5,     3,     2,
       4,     3,     3,     2,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
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
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
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
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
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
| yyreduce -- Do a reduction.  |
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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:
#line 150 "beacon.y" /* yacc.c:1663  */
    {
		yyclearin;
	}
#line 2293 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 6:
#line 158 "beacon.y" /* yacc.c:1663  */
    {
		ast_compile_entry((yyvsp[0].ast_value));
	}
#line 2301 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 7:
#line 164 "beacon.y" /* yacc.c:1663  */
    {
		ast_compile_entry((yyvsp[0].ast_value));
	}
#line 2309 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 8:
#line 168 "beacon.y" /* yacc.c:1663  */
    {
		ast_compile_entry((yyvsp[0].ast_value));
	}
#line 2317 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 9:
#line 172 "beacon.y" /* yacc.c:1663  */
    {
		ast_compile_entry((yyvsp[0].ast_value));
	}
#line 2325 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 10:
#line 178 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_namespace_decl((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2333 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 11:
#line 185 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[-1].ast_value);
	}
#line 2341 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 12:
#line 192 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_namespace_namespace_decl((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2349 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 17:
#line 203 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[0].ast_value);
	}
#line 2357 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 18:
#line 207 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_namespace_member_decl_list((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2365 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 19:
#line 214 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_blank();
	}
#line 2373 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 21:
#line 222 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_namespace_path((yyvsp[0].stringv_value));
	}
#line 2381 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 22:
#line 226 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_namespace_path_list((yyvsp[-2].ast_value), (yyvsp[0].stringv_value));
	}
#line 2389 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 24:
#line 234 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_import_decl_list((yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2397 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 25:
#line 241 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_import_decl(ast_new_import_path((yyvsp[0].ast_value)));
	}
#line 2405 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 26:
#line 248 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_parameterized_typename((yyvsp[-1].stringv_value), (yyvsp[0].ast_value));
	}
#line 2413 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 27:
#line 255 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_blank();
	}
#line 2421 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 28:
#line 259 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[-1].ast_value);
	}
#line 2429 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 29:
#line 266 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[0].ast_value);
	}
#line 2437 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 30:
#line 270 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_type_parameter_list((yyvsp[0].ast_value), (yyvsp[-2].ast_value));
	}
#line 2445 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 31:
#line 277 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_type_parameter((yyvsp[0].stringv_value), ast_new_blank());
	}
#line 2453 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 32:
#line 283 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_abstract_class_decl((yyvsp[-3].ast_value), ast_new_blank(), (yyvsp[-1].ast_value));
	}
#line 2461 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 33:
#line 287 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_abstract_class_decl((yyvsp[-5].ast_value), (yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 2469 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 34:
#line 293 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_class_decl((yyvsp[-3].ast_value), ast_new_blank(), (yyvsp[-1].ast_value));
	}
#line 2477 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 35:
#line 297 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_class_decl((yyvsp[-5].ast_value), (yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 2485 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 36:
#line 304 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_enum_decl((yyvsp[-3].stringv_value), (yyvsp[-1].ast_value));
	}
#line 2493 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 37:
#line 308 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_enum_decl((yyvsp[-4].stringv_value), (yyvsp[-2].ast_value));
	}
#line 2501 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 38:
#line 315 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_interface_decl((yyvsp[-3].ast_value), ast_new_blank(), (yyvsp[-1].ast_value));
	}
#line 2509 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 39:
#line 319 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_interface_decl((yyvsp[-5].ast_value), (yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 2517 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 40:
#line 326 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_blank();
	}
#line 2525 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 43:
#line 335 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_access_member_tree((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2533 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 44:
#line 342 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_access_member_list((yyvsp[-2].access_level_value), (yyvsp[0].ast_value));
	}
#line 2541 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 45:
#line 349 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_member_decl((yyvsp[0].ast_value));
	}
#line 2549 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 46:
#line 353 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_member_decl_list((yyvsp[-1].ast_value), ast_new_member_decl((yyvsp[0].ast_value)));
	}
#line 2557 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 52:
#line 368 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_constructor_decl((yyvsp[-3].ast_value), (yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2565 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 53:
#line 372 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_constructor_decl(ast_new_blank(), (yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 2573 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 54:
#line 379 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[-3].chain_type_value), (yyvsp[-1].ast_value));
	}
#line 2581 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 55:
#line 383 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_constructor_chain((yyvsp[-2].chain_type_value), ast_new_blank());
	}
#line 2589 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 56:
#line 390 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.chain_type_value) = chain_type_super;
	}
#line 2597 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 57:
#line 394 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.chain_type_value) = chain_type_this;
	}
#line 2605 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 58:
#line 401 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_blank();
	}
#line 2613 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 60:
#line 409 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_function_decl((yyvsp[-7].stringv_value), (yyvsp[-6].ast_value), (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2621 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 61:
#line 413 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_function_decl_empty_params((yyvsp[-6].stringv_value), (yyvsp[-5].ast_value), 8, (yyvsp[-1].ast_value));
	}
#line 2629 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 62:
#line 420 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_method_decl((yyvsp[-8].ast_value), (yyvsp[-7].stringv_value), (yyvsp[-6].ast_value), (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2637 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 63:
#line 424 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_method_decl_empty_params((yyvsp[-7].ast_value), (yyvsp[-6].stringv_value), (yyvsp[-5].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2645 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 64:
#line 428 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_method_decl(ast_new_modifier(modifier_none), (yyvsp[-7].stringv_value), (yyvsp[-6].ast_value), (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2653 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 65:
#line 432 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_method_decl_empty_params(ast_new_modifier(modifier_none), (yyvsp[-6].stringv_value), (yyvsp[-5].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2661 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 66:
#line 439 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_add, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2669 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 67:
#line 443 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_sub, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2677 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 68:
#line 447 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_mul, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2685 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 69:
#line 451 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_div, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2693 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 70:
#line 455 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_mod, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2701 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 71:
#line 459 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_gt, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2709 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 72:
#line 463 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_ge, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2717 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 73:
#line 467 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_lt, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2725 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 74:
#line 471 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_le, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2733 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 75:
#line 476 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_eq, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2741 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 76:
#line 480 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_noteq, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2749 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 77:
#line 485 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_bit_or, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2757 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 78:
#line 489 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_bit_and, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2765 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 79:
#line 494 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_logic_or, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2773 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 80:
#line 498 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_logic_and, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2781 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 81:
#line 503 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_lshift, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2789 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 82:
#line 507 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_rshift, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2797 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 83:
#line 512 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_excor, (yyvsp[-4].ast_value), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2805 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 84:
#line 517 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_not, ast_new_blank(), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2813 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 85:
#line 522 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_childa, ast_new_blank(), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2821 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 86:
#line 526 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_operator_overload(operator_negative, ast_new_blank(), (yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2829 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 87:
#line 533 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_field_decl((yyvsp[-3].ast_value), (yyvsp[-2].ast_value), (yyvsp[-1].stringv_value), ast_new_blank());
	}
#line 2837 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 88:
#line 537 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_field_decl(ast_new_modifier(modifier_none), (yyvsp[-2].ast_value), (yyvsp[-1].stringv_value), ast_new_blank());
	}
#line 2845 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 89:
#line 541 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_field_decl((yyvsp[-5].ast_value), (yyvsp[-4].ast_value), (yyvsp[-3].stringv_value), (yyvsp[-1].ast_value));
	}
#line 2853 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 90:
#line 545 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_field_decl(ast_new_modifier(modifier_none), (yyvsp[-4].ast_value), (yyvsp[-3].stringv_value), (yyvsp[-1].ast_value));
	}
#line 2861 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 91:
#line 552 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_set(ast_new_blank(), ast_new_blank());
	}
#line 2869 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 92:
#line 556 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_set(ast_new_blank(), (yyvsp[0].ast_value));
	}
#line 2877 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 93:
#line 560 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_set(ast_new_access((yyvsp[-2].access_level_value)), ast_new_blank());
	}
#line 2885 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 94:
#line 564 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_set(ast_new_access((yyvsp[-2].access_level_value)), ast_new_blank());
	}
#line 2893 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 95:
#line 571 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_get(ast_new_blank(), ast_new_blank());
	}
#line 2901 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 96:
#line 575 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_get(ast_new_blank(), (yyvsp[0].ast_value));
	}
#line 2909 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 97:
#line 579 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_get(ast_new_access((yyvsp[-2].access_level_value)), ast_new_blank());
	}
#line 2917 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 98:
#line 583 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_get(ast_new_access((yyvsp[-2].access_level_value)), ast_new_blank());
	}
#line 2925 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 99:
#line 590 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_decl((yyvsp[-6].ast_value), (yyvsp[-5].ast_value), (yyvsp[-4].stringv_value), (yyvsp[-2].ast_value), (yyvsp[-1].ast_value));
	}
#line 2933 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 100:
#line 594 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_prop_decl(ast_new_modifier(modifier_none), (yyvsp[-5].ast_value), (yyvsp[-4].stringv_value), (yyvsp[-2].ast_value), (yyvsp[-1].ast_value));
	}
#line 2941 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 101:
#line 601 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[0].ast_value);
	}
#line 2949 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 102:
#line 605 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_modifier_list((yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 2957 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 103:
#line 612 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_modifier(modifier_static);
	}
#line 2965 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 104:
#line 616 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_modifier(modifier_native);
	}
#line 2973 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 105:
#line 620 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_modifier(modifier_abstract);
	}
#line 2981 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 106:
#line 624 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_modifier(modifier_override);
	}
#line 2989 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 107:
#line 628 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_modifier(modifier_final);
	}
#line 2997 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 108:
#line 635 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.access_level_value) = access_public;
	}
#line 3005 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 109:
#line 639 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.access_level_value) = access_private;
	}
#line 3013 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 110:
#line 643 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.access_level_value) = access_protected;
	}
#line 3021 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 111:
#line 650 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_identifier((yyvsp[0].stringv_value));
	}
#line 3029 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 112:
#line 654 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_identifier_list((yyvsp[0].stringv_value), (yyvsp[-2].ast_value));
	}
#line 3037 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 113:
#line 661 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_parameter((yyvsp[-1].ast_value), (yyvsp[0].stringv_value));
	}
#line 3045 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 114:
#line 665 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_parameter_list((yyvsp[-1].ast_value), (yyvsp[0].stringv_value), (yyvsp[-3].ast_value));
	}
#line 3053 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 115:
#line 672 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_argument((yyvsp[0].ast_value));
	}
#line 3061 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 116:
#line 676 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_lambda((yyvsp[-4].ast_value), (yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3069 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 117:
#line 680 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_argument_list(ast_new_argument((yyvsp[0].ast_value)), (yyvsp[-2].ast_value));
	}
#line 3077 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 118:
#line 687 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_blank();
	}
#line 3085 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 119:
#line 691 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[-1].ast_value);
	}
#line 3093 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 120:
#line 698 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[0].ast_value);
	}
#line 3101 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 121:
#line 702 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_typename_list((yyvsp[0].ast_value), (yyvsp[-2].ast_value));
	}
#line 3109 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 122:
#line 709 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_typename((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3117 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 123:
#line 716 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_fqcn_part((yyvsp[0].stringv_value));
	}
#line 3125 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 124:
#line 720 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_fqcn_part_list(ast_new_fqcn_part((yyvsp[0].stringv_value)), (yyvsp[-2].ast_value));
	}
#line 3133 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 125:
#line 729 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[-1].ast_value);
	}
#line 3141 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 128:
#line 737 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_unary(ast_pos, (yyvsp[0].ast_value));
	}
#line 3149 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 129:
#line 741 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_unary(ast_neg, (yyvsp[0].ast_value));
	}
#line 3157 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 130:
#line 745 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_add, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3165 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 131:
#line 749 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_sub, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3173 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 132:
#line 753 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_mul, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3181 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 133:
#line 757 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_div, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3189 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 134:
#line 761 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_mod, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3197 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 135:
#line 765 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_bit_or, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3205 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 136:
#line 769 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_equal, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3213 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 137:
#line 773 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_notequal, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3221 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 138:
#line 777 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_bit_and, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3229 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 139:
#line 781 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_exc_or, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3237 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 140:
#line 785 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_logic_or, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3245 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 141:
#line 789 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_logic_and, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3253 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 142:
#line 793 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_assign, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3261 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 143:
#line 797 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_add_assign, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3269 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 144:
#line 801 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_sub_assign, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3277 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 145:
#line 805 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_mul_assign, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3285 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 146:
#line 809 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_div_assign, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3293 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 147:
#line 813 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_mod_assign, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3301 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 148:
#line 817 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_and_assign, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3309 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 149:
#line 821 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_or_assign, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3317 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 150:
#line 825 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_exc_or_assign, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3325 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 151:
#line 829 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_lshift_assign, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3333 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 152:
#line 833 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_rshift_assign, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3341 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 153:
#line 837 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_gt, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3349 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 154:
#line 841 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_ge, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3357 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 155:
#line 845 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_lt, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3365 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 156:
#line 849 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_le, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3373 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 157:
#line 853 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_lshift, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3381 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 158:
#line 857 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_binary(ast_rshift, (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3389 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 159:
#line 861 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_instanceof((yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3397 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 160:
#line 865 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_as((yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3405 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 161:
#line 869 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_unary(ast_childa, (yyvsp[0].ast_value));
	}
#line 3413 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 162:
#line 873 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_unary(ast_not, (yyvsp[0].ast_value));
	}
#line 3421 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 163:
#line 877 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_op_call((yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 3429 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 164:
#line 881 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_op_call((yyvsp[-2].ast_value), ast_new_blank());
	}
#line 3437 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 165:
#line 885 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[-4].ast_value), (yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 3445 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 166:
#line 889 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_new_instance((yyvsp[-3].ast_value), (yyvsp[-2].ast_value), ast_new_blank());
	}
#line 3453 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 167:
#line 893 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_this();
	}
#line 3461 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 168:
#line 897 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_super();
	}
#line 3469 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 170:
#line 904 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_variable((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3477 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 171:
#line 908 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_field_access((yyvsp[-3].ast_value), (yyvsp[-1].stringv_value), (yyvsp[0].ast_value));
	}
#line 3485 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 172:
#line 912 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_add, (yyvsp[-1].ast_value));
	}
#line 3493 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 173:
#line 916 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_sub, (yyvsp[-1].ast_value));
	}
#line 3501 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 174:
#line 920 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_mul, (yyvsp[-1].ast_value));
	}
#line 3509 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 175:
#line 924 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_div, (yyvsp[-1].ast_value));
	}
#line 3517 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 176:
#line 928 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_mod, (yyvsp[-1].ast_value));
	}
#line 3525 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 177:
#line 932 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_gt, (yyvsp[-1].ast_value));
	}
#line 3533 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 178:
#line 936 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_ge, (yyvsp[-1].ast_value));
	}
#line 3541 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 179:
#line 940 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_lt, (yyvsp[-1].ast_value));
	}
#line 3549 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 180:
#line 944 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_le, (yyvsp[-1].ast_value));
	}
#line 3557 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 181:
#line 948 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_eq, (yyvsp[-1].ast_value));
	}
#line 3565 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 182:
#line 952 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_noteq, (yyvsp[-1].ast_value));
	}
#line 3573 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 183:
#line 956 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_bit_or, (yyvsp[-1].ast_value));
	}
#line 3581 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 184:
#line 960 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_bit_and, (yyvsp[-1].ast_value));
	}
#line 3589 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 185:
#line 964 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_logic_or, (yyvsp[-1].ast_value));
	}
#line 3597 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 186:
#line 968 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_logic_and, (yyvsp[-1].ast_value));
	}
#line 3605 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 187:
#line 972 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_lshift, (yyvsp[-1].ast_value));
	}
#line 3613 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 188:
#line 976 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_rshift, (yyvsp[-1].ast_value));
	}
#line 3621 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 189:
#line 980 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_bioperator((yyvsp[-5].ast_value), operator_excor, (yyvsp[-1].ast_value));
	}
#line 3629 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 190:
#line 984 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_uoperator((yyvsp[-4].ast_value), operator_not);
	}
#line 3637 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 191:
#line 988 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_uoperator((yyvsp[-4].ast_value), operator_childa);
	}
#line 3645 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 192:
#line 992 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_explicit_uoperator((yyvsp[-4].ast_value), operator_negative);
	}
#line 3653 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 197:
#line 1002 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_true();
	}
#line 3661 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 198:
#line 1006 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_false();
	}
#line 3669 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 199:
#line 1010 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_null();
	}
#line 3677 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 200:
#line 1019 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_stmt((yyvsp[0].ast_value));
	}
#line 3685 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 201:
#line 1023 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_stmt_list((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3693 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 202:
#line 1029 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_proc((yyvsp[-1].ast_value));
	}
#line 3701 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 217:
#line 1049 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_variable_decl((yyvsp[-2].ast_value), (yyvsp[-1].stringv_value));
	}
#line 3709 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 218:
#line 1055 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_variable_init((yyvsp[-4].ast_value), (yyvsp[-3].stringv_value), (yyvsp[-1].ast_value));
	}
#line 3717 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 219:
#line 1061 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_inferenced_type_init((yyvsp[-3].stringv_value), (yyvsp[-1].ast_value));
	}
#line 3725 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 220:
#line 1067 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_if((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3733 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 221:
#line 1071 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_if_else((yyvsp[-3].ast_value), (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3741 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 222:
#line 1075 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_if_elif_list((yyvsp[-2].ast_value), (yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3749 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 223:
#line 1079 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_if_elif_list_else((yyvsp[-4].ast_value), (yyvsp[-3].ast_value), (yyvsp[-2].ast_value), (yyvsp[0].ast_value));
	}
#line 3757 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 225:
#line 1086 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_elif_list((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3765 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 226:
#line 1092 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_elif((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3773 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 227:
#line 1098 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_while((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3781 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 228:
#line 1104 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_break();
	}
#line 3789 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 229:
#line 1110 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_continue();
	}
#line 3797 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 230:
#line 1116 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_return((yyvsp[-1].ast_value));
	}
#line 3805 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 231:
#line 1120 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_return_empty();
	}
#line 3813 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 232:
#line 1126 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_throw((yyvsp[-1].ast_value));
	}
#line 3821 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 233:
#line 1132 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_try((yyvsp[-1].ast_value), (yyvsp[0].ast_value));
	}
#line 3829 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 234:
#line 1138 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = (yyvsp[0].ast_value);
	}
#line 3837 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 235:
#line 1142 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_catch_list((yyvsp[0].ast_value), (yyvsp[-1].ast_value));
	}
#line 3845 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 236:
#line 1148 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_catch((yyvsp[-3].ast_value), (yyvsp[-2].stringv_value), (yyvsp[0].ast_value));
	}
#line 3853 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 237:
#line 1154 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_assert((yyvsp[-3].ast_value), (yyvsp[-1].ast_value));
	}
#line 3861 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 238:
#line 1158 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_assert((yyvsp[-1].ast_value), ast_new_blank());
	}
#line 3869 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 239:
#line 1164 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_defer((yyvsp[0].ast_value));
	}
#line 3877 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 240:
#line 1170 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_yield_return((yyvsp[-1].ast_value));
	}
#line 3885 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 241:
#line 1176 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_yield_break();
	}
#line 3893 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 242:
#line 1182 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_scope((yyvsp[-1].ast_value));
	}
#line 3901 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 243:
#line 1186 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_scope_empty();
	}
#line 3909 "beacon.tab.c" /* yacc.c:1663  */
    break;

  case 244:
#line 1192 "beacon.y" /* yacc.c:1663  */
    {
		(yyval.ast_value) = ast_new_blank();
	}
#line 3917 "beacon.tab.c" /* yacc.c:1663  */
    break;


#line 3921 "beacon.tab.c" /* yacc.c:1663  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1200 "beacon.y" /* yacc.c:1907  */




