
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "src\\parser.y"

	#include "common.h"
	#define YYSTYPE TreeNode *

	TreeNode* root = new TreeNode(0, NODE_PROG);
	extern int lineno;

	extern bool parserError;

	// max_scope_id 是堆栈下一层结点的最大编号
	unsigned char max_scope_id = SCOPT_ID_BASE;
	string presentScope = "1";
	unsigned int top = 0;

	// multimap <标识符名称， 作用域> 变量名列表
	extern multimap<string, string> idNameList;
	// map <<标识符名称， 作用域>, 结点指针> 变量列表
	extern map<pair<string, string>, TreeNode*> idList;

	// 用于检查continue和break是否在循环内部
	bool inCycle = false;

	int yylex();
	int yyerror( char const * );
	int scopeCmp(string preScope, string varScope);
	void scopePush();
	void scopePop();


/* Line 189 of yacc.c  */
#line 103 "src\\parser.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_CHAR = 258,
     T_INT = 259,
     T_STRING = 260,
     T_BOOL = 261,
     T_VOID = 262,
     ADDR = 263,
     ASSIGN = 264,
     PLUSASSIGN = 265,
     MINUSASSIGN = 266,
     MULASSIGN = 267,
     DIVASSIGN = 268,
     SEMICOLON = 269,
     COMMA = 270,
     LPAREN = 271,
     RPAREN = 272,
     LBRACE = 273,
     RBRACE = 274,
     LBRACKET = 275,
     RBRACKET = 276,
     CONST = 277,
     IF_ = 278,
     ELSE = 279,
     WHILE_ = 280,
     FOR_ = 281,
     BREAK = 282,
     CONTINUE = 283,
     RETURN = 284,
     EQ = 285,
     GRAEQ = 286,
     LESEQ = 287,
     NEQ = 288,
     GRA = 289,
     LES = 290,
     PLUS = 291,
     MINUS = 292,
     MUL = 293,
     DIV = 294,
     MOD = 295,
     AND = 296,
     OR = 297,
     NOT = 298,
     INC = 299,
     DEC = 300,
     IDENTIFIER = 301,
     INTEGER = 302,
     CHAR = 303,
     BOOL = 304,
     STRING = 305
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 195 "src\\parser.cpp"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   529

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  114
/* YYNRULES -- Number of states.  */
#define YYNSTATES  220

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   305

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    13,    15,    17,    19,
      21,    23,    25,    27,    29,    31,    33,    35,    38,    41,
      46,    51,    53,    55,    57,    59,    62,    65,    70,    75,
      77,    79,    81,    86,    88,    92,    96,   102,   104,   108,
     112,   114,   118,   120,   124,   130,   139,   147,   149,   151,
     155,   158,   162,   164,   166,   168,   171,   173,   175,   179,
     181,   183,   186,   188,   196,   202,   208,   219,   229,   232,
     235,   238,   242,   244,   246,   248,   250,   254,   258,   262,
     266,   270,   272,   274,   278,   282,   284,   288,   292,   296,
     298,   301,   304,   307,   310,   313,   315,   319,   323,   328,
     332,   334,   336,   340,   342,   346,   348,   352,   354,   358,
     362,   364,   368,   372,   376
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      52,     0,    -1,    63,    -1,    71,    -1,    52,    63,    -1,
      52,    71,    -1,     4,    -1,     3,    -1,     6,    -1,     7,
      -1,    47,    -1,    49,    -1,    48,    -1,    50,    -1,    56,
      -1,    57,    -1,    58,    -1,    38,    56,    -1,     8,    56,
      -1,    56,    20,    85,    21,    -1,    57,    20,    85,    21,
      -1,    46,    -1,    60,    -1,    61,    -1,    62,    -1,    38,
      60,    -1,     8,    60,    -1,    60,    20,    47,    21,    -1,
      61,    20,    47,    21,    -1,    46,    -1,    64,    -1,    68,
      -1,    22,    53,    65,    14,    -1,    66,    -1,    65,    15,
      66,    -1,    60,     9,    54,    -1,    61,     9,    18,    67,
      19,    -1,    54,    -1,    67,    15,    54,    -1,    53,    69,
      14,    -1,    70,    -1,    69,    15,    70,    -1,    59,    -1,
      59,     9,    85,    -1,    61,     9,    18,    67,    19,    -1,
      53,    60,    72,    73,    17,    18,    78,    19,    -1,    53,
      60,    72,    17,    18,    78,    19,    -1,    16,    -1,    74,
      -1,    73,    15,    74,    -1,    53,    60,    -1,    76,    78,
      77,    -1,    18,    -1,    19,    -1,    79,    -1,    78,    79,
      -1,    63,    -1,    81,    -1,    18,    78,    19,    -1,    81,
      -1,    14,    -1,    85,    14,    -1,    75,    -1,    82,    16,
      86,    17,    80,    24,    80,    -1,    82,    16,    86,    17,
      80,    -1,    83,    16,    86,    17,    80,    -1,    84,    16,
      53,    69,    14,    86,    14,    85,    17,    80,    -1,    84,
      16,    85,    14,    86,    14,    85,    17,    80,    -1,    27,
      14,    -1,    28,    14,    -1,    29,    14,    -1,    29,    85,
      14,    -1,    23,    -1,    25,    -1,    26,    -1,    87,    -1,
      55,     9,    85,    -1,    55,    10,    85,    -1,    55,    11,
      85,    -1,    55,    12,    85,    -1,    55,    13,    85,    -1,
      92,    -1,    88,    -1,    87,    36,    88,    -1,    87,    37,
      88,    -1,    89,    -1,    88,    38,    89,    -1,    88,    39,
      89,    -1,    88,    40,    89,    -1,    90,    -1,    43,    86,
      -1,    36,    90,    -1,    37,    90,    -1,    56,    44,    -1,
      56,    45,    -1,    54,    -1,    16,    85,    17,    -1,    16,
      86,    17,    -1,    56,    16,    91,    17,    -1,    56,    16,
      17,    -1,    55,    -1,    85,    -1,    91,    15,    85,    -1,
      93,    -1,    93,    42,    92,    -1,    94,    -1,    94,    41,
      93,    -1,    95,    -1,    95,    30,    94,    -1,    95,    33,
      94,    -1,    85,    -1,    95,    34,    85,    -1,    95,    35,
      85,    -1,    95,    31,    85,    -1,    95,    32,    85,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    59,    59,    60,    61,    62,    68,    69,    70,    71,
      75,    76,    77,    78,    83,    84,    93,    94,    95,   106,
     136,   170,   199,   200,   204,   205,   206,   211,   218,   226,
     245,   246,   250,   266,   267,   271,   277,   287,   288,   292,
     317,   318,   322,   323,   329,   340,   362,   378,   381,   382,
     386,   397,   403,   404,   407,   408,   412,   413,   417,   422,
     426,   427,   428,   429,   440,   450,   461,   485,   496,   504,
     512,   513,   516,   517,   518,   523,   524,   534,   540,   546,
     552,   561,   565,   566,   567,   572,   573,   574,   575,   580,
     581,   582,   583,   584,   585,   590,   591,   592,   593,   601,
     609,   614,   615,   620,   621,   626,   627,   632,   633,   634,
     639,   640,   641,   642,   643
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_CHAR", "T_INT", "T_STRING", "T_BOOL",
  "T_VOID", "ADDR", "ASSIGN", "PLUSASSIGN", "MINUSASSIGN", "MULASSIGN",
  "DIVASSIGN", "SEMICOLON", "COMMA", "LPAREN", "RPAREN", "LBRACE",
  "RBRACE", "LBRACKET", "RBRACKET", "CONST", "IF_", "ELSE", "WHILE_",
  "FOR_", "BREAK", "CONTINUE", "RETURN", "EQ", "GRAEQ", "LESEQ", "NEQ",
  "GRA", "LES", "PLUS", "MINUS", "MUL", "DIV", "MOD", "AND", "OR", "NOT",
  "INC", "DEC", "IDENTIFIER", "INTEGER", "CHAR", "BOOL", "STRING",
  "$accept", "program", "basicType", "literalConst", "compIdentifier",
  "pIdentifier", "arrayIdentifier", "identifier", "declCompIdentifier",
  "pDeclIdentifier", "arrayDeclIdentifier", "declIdentifier", "decl",
  "constDecl", "constDefs", "constDef", "ArrayInitVal", "varDecl",
  "varDefs", "varDef", "funcDef", "funcLPAREN", "funcFParams",
  "funcFParam", "block", "blockLBRACE", "blockRBRACE", "blockItems",
  "blockItem", "stmt_", "stmt", "IF", "WHILE", "FOR", "expr", "cond",
  "addExpr", "mulExpr", "unaryExpr", "primaryExpr", "funcRParams",
  "LOrExpr", "LAndExpr", "eqExpr", "relExpr", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    51,    52,    52,    52,    52,    53,    53,    53,    53,
      54,    54,    54,    54,    55,    55,    56,    56,    56,    57,
      57,    58,    59,    59,    60,    60,    60,    61,    61,    62,
      63,    63,    64,    65,    65,    66,    66,    67,    67,    68,
      69,    69,    70,    70,    70,    71,    71,    72,    73,    73,
      74,    75,    76,    77,    78,    78,    79,    79,    80,    80,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    82,    83,    84,    85,    85,    85,    85,    85,
      85,    86,    87,    87,    87,    88,    88,    88,    88,    89,
      89,    89,    89,    89,    89,    90,    90,    90,    90,    90,
      90,    91,    91,    92,    92,    93,    93,    94,    94,    94,
      95,    95,    95,    95,    95
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     4,
       4,     1,     1,     1,     1,     2,     2,     4,     4,     1,
       1,     1,     4,     1,     3,     3,     5,     1,     3,     3,
       1,     3,     1,     3,     5,     8,     7,     1,     1,     3,
       2,     3,     1,     1,     1,     2,     1,     1,     3,     1,
       1,     2,     1,     7,     5,     5,    10,     9,     2,     2,
       2,     3,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     1,     1,     3,     3,     1,     3,     3,     3,     1,
       2,     2,     2,     2,     2,     1,     3,     3,     4,     3,
       1,     1,     3,     1,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     7,     6,     8,     9,     0,     0,     0,     2,    30,
      31,     3,     0,     1,     4,     5,     0,     0,    29,    42,
      22,    23,    24,     0,    40,     0,     0,     0,    33,    26,
      25,     0,    47,     0,     0,     0,     0,    39,     0,     0,
       0,    32,     0,     0,     0,     0,     0,     0,     0,    21,
      10,    12,    11,    13,    95,   100,    14,    15,    16,    43,
      75,    82,    85,    89,     0,     0,     0,     0,    48,     0,
       0,    22,    41,    35,     0,    34,    18,   110,     0,    81,
     103,   105,   107,   100,    14,    91,    92,    17,   110,    90,
       0,     0,     0,     0,     0,     0,     0,    93,    94,     0,
       0,     0,     0,     0,     0,    27,     0,    50,     0,     0,
      37,     0,    28,     0,    96,    97,     0,     0,     0,     0,
       0,     0,     0,     0,    76,    77,    78,    79,    80,    99,
     101,     0,     0,     0,    83,    84,    86,    87,    88,    60,
      52,    72,    73,    74,     0,     0,     0,     0,    56,    62,
       0,     0,    54,    57,     0,     0,     0,     0,    49,     0,
       0,    44,    36,   104,   106,   108,   113,   114,   109,   111,
     112,     0,    98,    19,    20,    68,    69,    70,     0,     0,
      46,    55,     0,     0,     0,    61,     0,    38,   102,    71,
      53,    51,     0,     0,     0,     0,    45,     0,     0,     0,
       0,     0,    64,    59,    65,     0,     0,     0,     0,     0,
       0,    58,    63,     0,     0,     0,     0,     0,    67,    66
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,   147,    54,    55,    56,    57,    58,    19,    71,
      21,    22,   148,     9,    27,    28,   111,    10,    23,    24,
      11,    34,    67,    68,   149,   150,   191,   151,   152,   202,
     153,   154,   155,   156,   157,    78,    60,    61,    62,    63,
     131,    79,    80,    81,    82
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -173
static const yytype_int16 yypact[] =
{
     103,  -173,  -173,  -173,  -173,   155,    76,     2,  -173,  -173,
    -173,  -173,     2,  -173,  -173,  -173,     2,     2,  -173,    -2,
      27,    11,  -173,    43,  -173,    13,    21,    70,  -173,  -173,
    -173,   479,  -173,   -26,   114,    17,    64,  -173,     2,   124,
      97,  -173,     2,     4,   479,   119,   119,     4,   479,  -173,
    -173,  -173,  -173,  -173,  -173,   138,     7,    99,  -173,  -173,
     127,   139,  -173,  -173,   101,   106,     2,    53,  -173,   124,
     115,   120,  -173,  -173,   124,  -173,  -173,   159,   170,  -173,
     164,   156,   451,  -173,    33,  -173,  -173,  -173,  -173,  -173,
     479,   479,   479,   479,   479,   427,   479,  -173,  -173,   479,
     479,   479,   479,   479,   479,  -173,   374,  -173,   155,   181,
    -173,    62,  -173,    82,  -173,  -173,   479,   479,   479,   479,
     479,   479,   479,   479,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,    79,   135,   191,   139,   139,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,   199,   200,   464,     2,  -173,  -173,
     374,   182,  -173,  -173,   201,   205,   206,   202,  -173,   374,
     124,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,   479,  -173,  -173,  -173,  -173,  -173,  -173,   209,   230,
    -173,  -173,   479,   479,    96,  -173,   278,  -173,  -173,  -173,
    -173,  -173,   198,   207,     2,   212,  -173,   411,   411,   167,
     479,   374,   203,  -173,  -173,   479,   221,   326,   411,   225,
     479,  -173,  -173,   479,   223,   224,   411,   411,  -173,  -173
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -173,  -173,     0,   -37,   -29,    83,  -173,  -173,  -173,    12,
      -4,  -173,     9,  -173,  -173,   208,   168,  -173,    49,   213,
     239,  -173,  -173,   146,  -173,  -173,  -173,  -146,  -140,  -103,
    -172,  -173,  -173,  -173,   -30,   -45,  -173,    94,    89,   157,
    -173,   131,   143,   -62,  -173
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
       7,    59,    73,    89,   179,    12,     7,    31,    26,     8,
      16,   181,    43,   186,    77,    14,    83,    83,    88,    20,
      35,    64,    39,    95,    25,   203,   203,    96,    29,    30,
      40,    36,   110,    33,    66,    69,   203,   110,    26,   181,
      17,    36,    47,    32,   203,   203,   181,    33,    18,    95,
      49,    97,    98,    96,    25,   207,   165,    37,    38,   168,
     124,   125,   126,   127,   128,   130,   132,   181,   108,   133,
     109,    83,    83,    83,    83,    83,    13,   160,   107,     1,
       2,   161,     3,     4,    41,    42,    88,    88,    88,   166,
     167,    88,   169,   170,   171,   204,   172,   160,     5,     1,
       2,   162,     3,     4,    43,   212,     1,     2,    66,     3,
       4,    70,    44,   218,   219,    74,   178,     1,     2,    99,
       3,     4,   105,   187,   106,     5,    76,    43,    84,    84,
      87,    65,    45,    46,    47,    44,   112,   192,   193,    48,
      33,   188,    49,    50,    51,    52,    53,    90,    91,    92,
      93,    94,    88,    88,   195,   206,   173,    47,     1,     2,
     209,     3,     4,   100,   101,    49,    50,    51,    52,    53,
      88,    50,    51,    52,    53,    88,   114,   102,   103,   104,
     214,   205,    38,   215,   194,     1,     2,   115,     3,     4,
      43,   136,   137,   138,   134,   135,   139,   117,    44,   159,
     140,   180,    85,    86,     5,   141,   116,   142,   143,   144,
     145,   146,   174,   175,   176,   197,   185,   182,    45,    46,
      47,   183,   184,   189,   198,    48,   200,   208,    49,    50,
      51,    52,    53,     1,     2,   210,     3,     4,    43,   213,
     216,   217,   113,   199,   139,    15,    44,   163,   140,   190,
      75,    72,     5,   141,   158,   142,   143,   144,   145,   146,
     164,     0,     0,     0,     0,     0,    45,    46,    47,     0,
       0,     0,     0,    48,     0,     0,    49,    50,    51,    52,
      53,     1,     2,     0,     3,     4,    43,     0,     0,     0,
       0,     0,   139,     0,    44,     0,   140,   196,     0,     0,
       5,   141,     0,   142,   143,   144,   145,   146,     0,     0,
       0,     0,     0,     0,    45,    46,    47,     0,     0,     0,
       0,    48,     0,     0,    49,    50,    51,    52,    53,     1,
       2,     0,     3,     4,    43,     0,     0,     0,     0,     0,
     139,     0,    44,     0,   140,   211,     0,     0,     5,   141,
       0,   142,   143,   144,   145,   146,     0,     0,     0,     0,
       0,     0,    45,    46,    47,     0,     0,     0,     0,    48,
       0,     0,    49,    50,    51,    52,    53,     1,     2,     0,
       3,     4,    43,     0,     0,     0,     0,     0,   139,     0,
      44,     0,   140,     0,     0,     0,     5,   141,     0,   142,
     143,   144,   145,   146,     0,     0,     0,     0,     0,     0,
      45,    46,    47,     0,     0,     0,     0,    48,     0,    43,
      49,    50,    51,    52,    53,   139,     0,    44,     0,   201,
       0,     0,     0,     0,   141,    43,   142,   143,   144,   145,
     146,     0,     0,    44,   129,     0,     0,    45,    46,    47,
       0,     0,     0,     0,    48,     0,     0,    49,    50,    51,
      52,    53,     0,    45,    46,    47,     0,     0,     0,     0,
      48,     0,    43,    49,    50,    51,    52,    53,   177,     0,
      44,   118,   119,   120,   121,   122,   123,    43,     0,     0,
       0,     0,     0,     0,     0,    44,     0,     0,     0,     0,
      45,    46,    47,     0,     0,     0,     0,    48,     0,     0,
      49,    50,    51,    52,    53,    45,    46,    47,     0,     0,
       0,     0,    48,     0,     0,    49,    50,    51,    52,    53
};

static const yytype_int16 yycheck[] =
{
       0,    31,    39,    48,   150,     5,     6,     9,    12,     0,
       8,   151,     8,   159,    44,     6,    45,    46,    48,     7,
       9,    47,     9,    16,    12,   197,   198,    20,    16,    17,
       9,    20,    69,    20,    34,    18,   208,    74,    42,   179,
      38,    20,    38,    16,   216,   217,   186,    20,    46,    16,
      46,    44,    45,    20,    42,   201,   118,    14,    15,   121,
      90,    91,    92,    93,    94,    95,    96,   207,    15,    99,
      17,   100,   101,   102,   103,   104,     0,    15,    66,     3,
       4,    19,     6,     7,    14,    15,   116,   117,   118,   119,
     120,   121,   122,   123,    15,   198,    17,    15,    22,     3,
       4,    19,     6,     7,     8,   208,     3,     4,   108,     6,
       7,    47,    16,   216,   217,    18,   146,     3,     4,    20,
       6,     7,    21,   160,    18,    22,    43,     8,    45,    46,
      47,    17,    36,    37,    38,    16,    21,   182,   183,    43,
      20,   171,    46,    47,    48,    49,    50,     9,    10,    11,
      12,    13,   182,   183,   184,   200,    21,    38,     3,     4,
     205,     6,     7,    36,    37,    46,    47,    48,    49,    50,
     200,    47,    48,    49,    50,   205,    17,    38,    39,    40,
     210,    14,    15,   213,   184,     3,     4,    17,     6,     7,
       8,   102,   103,   104,   100,   101,    14,    41,    16,    18,
      18,    19,    45,    46,    22,    23,    42,    25,    26,    27,
      28,    29,    21,    14,    14,    17,    14,    16,    36,    37,
      38,    16,    16,    14,    17,    43,    14,    24,    46,    47,
      48,    49,    50,     3,     4,    14,     6,     7,     8,    14,
      17,    17,    74,   194,    14,     6,    16,   116,    18,    19,
      42,    38,    22,    23,   108,    25,    26,    27,    28,    29,
     117,    -1,    -1,    -1,    -1,    -1,    36,    37,    38,    -1,
      -1,    -1,    -1,    43,    -1,    -1,    46,    47,    48,    49,
      50,     3,     4,    -1,     6,     7,     8,    -1,    -1,    -1,
      -1,    -1,    14,    -1,    16,    -1,    18,    19,    -1,    -1,
      22,    23,    -1,    25,    26,    27,    28,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    37,    38,    -1,    -1,    -1,
      -1,    43,    -1,    -1,    46,    47,    48,    49,    50,     3,
       4,    -1,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,
      14,    -1,    16,    -1,    18,    19,    -1,    -1,    22,    23,
      -1,    25,    26,    27,    28,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    37,    38,    -1,    -1,    -1,    -1,    43,
      -1,    -1,    46,    47,    48,    49,    50,     3,     4,    -1,
       6,     7,     8,    -1,    -1,    -1,    -1,    -1,    14,    -1,
      16,    -1,    18,    -1,    -1,    -1,    22,    23,    -1,    25,
      26,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    37,    38,    -1,    -1,    -1,    -1,    43,    -1,     8,
      46,    47,    48,    49,    50,    14,    -1,    16,    -1,    18,
      -1,    -1,    -1,    -1,    23,     8,    25,    26,    27,    28,
      29,    -1,    -1,    16,    17,    -1,    -1,    36,    37,    38,
      -1,    -1,    -1,    -1,    43,    -1,    -1,    46,    47,    48,
      49,    50,    -1,    36,    37,    38,    -1,    -1,    -1,    -1,
      43,    -1,     8,    46,    47,    48,    49,    50,    14,    -1,
      16,    30,    31,    32,    33,    34,    35,     8,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    16,    -1,    -1,    -1,    -1,
      36,    37,    38,    -1,    -1,    -1,    -1,    43,    -1,    -1,
      46,    47,    48,    49,    50,    36,    37,    38,    -1,    -1,
      -1,    -1,    43,    -1,    -1,    46,    47,    48,    49,    50
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     6,     7,    22,    52,    53,    63,    64,
      68,    71,    53,     0,    63,    71,     8,    38,    46,    59,
      60,    61,    62,    69,    70,    60,    61,    65,    66,    60,
      60,     9,    16,    20,    72,     9,    20,    14,    15,     9,
       9,    14,    15,     8,    16,    36,    37,    38,    43,    46,
      47,    48,    49,    50,    54,    55,    56,    57,    58,    85,
      87,    88,    89,    90,    47,    17,    53,    73,    74,    18,
      47,    60,    70,    54,    18,    66,    56,    85,    86,    92,
      93,    94,    95,    55,    56,    90,    90,    56,    85,    86,
       9,    10,    11,    12,    13,    16,    20,    44,    45,    20,
      36,    37,    38,    39,    40,    21,    18,    60,    15,    17,
      54,    67,    21,    67,    17,    17,    42,    41,    30,    31,
      32,    33,    34,    35,    85,    85,    85,    85,    85,    17,
      85,    91,    85,    85,    88,    88,    89,    89,    89,    14,
      18,    23,    25,    26,    27,    28,    29,    53,    63,    75,
      76,    78,    79,    81,    82,    83,    84,    85,    74,    18,
      15,    19,    19,    92,    93,    94,    85,    85,    94,    85,
      85,    15,    17,    21,    21,    14,    14,    14,    85,    78,
      19,    79,    16,    16,    16,    14,    78,    54,    85,    14,
      19,    77,    86,    86,    53,    85,    19,    17,    17,    69,
      14,    18,    80,    81,    80,    14,    86,    78,    24,    86,
      14,    19,    80,    14,    85,    85,    17,    17,    80,    80
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

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
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 59 "src\\parser.y"
    {root->addChild((yyvsp[(1) - (1)]));;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 60 "src\\parser.y"
    {root->addChild((yyvsp[(1) - (1)]));;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 61 "src\\parser.y"
    {root->addChild((yyvsp[(2) - (2)]));;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 62 "src\\parser.y"
    {root->addChild((yyvsp[(2) - (2)]));;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 68 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_TYPE); (yyval)->type = TYPE_INT;;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 69 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_TYPE); (yyval)->type = TYPE_CHAR;;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 70 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_TYPE); (yyval)->type = TYPE_BOOL;;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 71 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_TYPE); (yyval)->type = TYPE_VOID;;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 75 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_EXPR); (yyval)->addChild((yyvsp[(1) - (1)]));;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 76 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_EXPR); (yyval)->addChild((yyvsp[(1) - (1)]));;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 77 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_EXPR); (yyval)->addChild((yyvsp[(1) - (1)]));;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 78 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_EXPR); (yyval)->addChild((yyvsp[(1) - (1)]));;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 83 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 84 "src\\parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	// 归约完成，清除下标计数器，为下一次做准备
	(yyval)->child->type->visitDim = 0;
  ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 93 "src\\parser.y"
    {(yyval) = new TreeNode((yyvsp[(1) - (1)]));;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 94 "src\\parser.y"
    {(yyval) = (yyvsp[(2) - (2)]); (yyval)->pointLevel++;;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 95 "src\\parser.y"
    {
	(yyval) = (yyvsp[(2) - (2)]); 
	(yyval)->pointLevel--;
	if ((yyval)->pointLevel < -2) {
		yyerror("Continuous addr operator");
	}
  ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 106 "src\\parser.y"
    {
	(yyval) = new TreeNode(lineno, NODE_OP);
	(yyval)->optype = OP_INDEX;
	(yyval)->addChild((yyvsp[(1) - (4)]));

	// 计算数组偏移量倍数
	int biasRate = 1;
	for (unsigned int i = (yyvsp[(1) - (4)])->type->visitDim + 1; i < (yyvsp[(1) - (4)])->type->dim; i++) {
		biasRate *= (yyvsp[(1) - (4)])->type->dimSize[i];
	}
	TreeNode* biasNode;
	if (biasRate == 1) {
		// 偏移倍数为1时省略乘法结点
		biasNode = (yyvsp[(3) - (4)]);
	}
	else {
		biasNode = new TreeNode(lineno, NODE_OP);
		biasNode->optype = OP_MUL;
		biasNode->addChild((yyvsp[(3) - (4)]));
		TreeNode* biasRateExpr = new TreeNode(lineno, NODE_EXPR);
		TreeNode* biasRateConst = new TreeNode(lineno, NODE_CONST);
		biasRateConst->type = TYPE_INT;
		biasRateConst->int_val = biasRate;
		biasRateExpr->addChild(biasRateConst);
		biasNode->addChild(biasRateExpr);
	}
	(yyvsp[(1) - (4)])->type->visitDim++;

	(yyval)->addChild(biasNode);
  ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 136 "src\\parser.y"
    {
	(yyval) = (yyvsp[(1) - (4)]);
	TreeNode* newBiasNode = new TreeNode(lineno, NODE_OP);
	newBiasNode->optype = OP_ADD;
	newBiasNode->addChild((yyval)->child->sibling);
	(yyval)->child->sibling = newBiasNode;

	// 计算数组偏移量倍数
	int biasRate = 1;
	for (unsigned int i = (yyval)->child->type->visitDim + 1; i < (yyval)->child->type->dim; i++) {
		biasRate *= (yyval)->child->type->dimSize[i];
	}

	TreeNode* biasNode;
	if (biasRate == 1) {
		// 偏移倍数为1时省略乘法结点
		biasNode = (yyvsp[(3) - (4)]);
	}
	else {
		biasNode->optype = OP_MUL;
		biasNode->addChild((yyvsp[(3) - (4)]));
		TreeNode* biasRateExpr = new TreeNode(lineno, NODE_EXPR);
		TreeNode* biasRateConst = new TreeNode(lineno, NODE_CONST);
		biasRateConst->type = TYPE_INT;
		biasRateConst->int_val = biasRate;
		biasRateExpr->addChild(biasRateConst);
		biasNode->addChild(biasRateExpr);
	}
	(yyval)->child->type->visitDim++;
	newBiasNode->addChild(biasNode);
  ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 170 "src\\parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	int idNameCount = idNameList.count((yyval)->var_name);
	int declCnt = 0;
	int minDefDis = MAX_SCOPE_STACK;

	// 搜索变量是否已经声明
	auto it = idNameList.find((yyval)->var_name);
	int resScoptCmp;
	while (idNameCount--) {
		resScoptCmp = scopeCmp(presentScope, it->second);
		if (resScoptCmp >= 0){
			// 寻找最近的定义
			if (resScoptCmp < minDefDis) {
				minDefDis = resScoptCmp;
				(yyval) = idList[make_pair(it->first, it->second)];
			}
			declCnt++;
		}
		it++;
	}
	if (declCnt == 0) {
		string t = "Undeclared identifier :'" + (yyvsp[(1) - (1)])->var_name + "', scope : " + to_string(resScoptCmp);
		yyerror(t.c_str());
	}
;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 199 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 200 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 204 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 205 "src\\parser.y"
    {(yyval) = (yyvsp[(2) - (2)]); (yyval)->type->pointLevel++;;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 206 "src\\parser.y"
    {(yyval) = (yyvsp[(2) - (2)]); (yyval)->type->pointLevel--;;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 211 "src\\parser.y"
    {
  (yyval) = (yyvsp[(1) - (4)]);
  (yyval)->type->type = VALUE_ARRAY;
  (yyval)->type->elementType = (yyvsp[(1) - (4)])->type->type;
  (yyval)->type->dimSize[(yyval)->type->dim] = (yyvsp[(3) - (4)])->int_val;
  (yyval)->type->dim++;
;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 218 "src\\parser.y"
    {
  (yyval) = (yyvsp[(1) - (4)]);
  (yyval)->type->dimSize[(yyval)->type->dim] = (yyvsp[(3) - (4)])->int_val;
  (yyval)->type->dim++;
;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 226 "src\\parser.y"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	(yyval)->var_scope = presentScope;
	(yyval)->type = new Type(NOTYPE);
	#ifdef ID_REDUCE_DEBUG
		cout<<"# $ reduce declIdentifier : "<<(yyval)->var_name<<", at scope :"<<presentScope<<endl;
	#endif
	if (idList.count(make_pair((yyval)->var_name, (yyval)->var_scope)) != 0) {
		string t = "Redeclared identifier : " + (yyval)->var_name;
		yyerror(t.c_str());
	}
	idNameList.insert(make_pair((yyval)->var_name, (yyval)->var_scope));
	idList[make_pair((yyval)->var_name, (yyval)->var_scope)] = (yyval);
;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 245 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 246 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 250 "src\\parser.y"
    {
  (yyval) = new TreeNode(lineno, NODE_STMT);
  (yyval)->stype = STMT_CONSTDECL;
  (yyval)->type = TYPE_NONE;
  (yyval)->addChild((yyvsp[(2) - (4)]));
  (yyval)->addChild((yyvsp[(3) - (4)]));  
  TreeNode* p = (yyvsp[(3) - (4)])->child;
  while(p != nullptr) {
	  p->child->type->copy((yyvsp[(2) - (4)])->type);
	  p->child->type->constvar = true;
	  p = p->sibling;
  }
;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 266 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_VARLIST); (yyval)->addChild((yyvsp[(1) - (1)]));;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 267 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (3)]); (yyval)->addChild((yyvsp[(3) - (3)]));;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 271 "src\\parser.y"
    {
	(yyval) = new TreeNode(lineno, NODE_OP); 
	(yyval)->optype = OP_DECLASSIGN;
	(yyval)->addChild((yyvsp[(1) - (3)])); 
	(yyval)->addChild((yyvsp[(3) - (3)]));
  ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 277 "src\\parser.y"
    {
	(yyval) = new TreeNode(lineno, NODE_OP);
	(yyval)->optype = OP_DECLASSIGN;
	(yyval)->addChild((yyvsp[(1) - (5)])); 
	(yyval)->addChild((yyvsp[(4) - (5)]));
  ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 287 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_VARLIST); (yyval)->addChild((yyvsp[(1) - (1)]));;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 288 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (3)]); (yyval)->addChild((yyvsp[(3) - (3)]));;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 292 "src\\parser.y"
    {
  (yyval) = new TreeNode(lineno, NODE_STMT);
  (yyval)->stype = STMT_DECL;
  (yyval)->type = TYPE_NONE;
  (yyval)->addChild((yyvsp[(1) - (3)]));
  (yyval)->addChild((yyvsp[(2) - (3)]));
  TreeNode* p = (yyvsp[(2) - (3)])->child;
  while(p != nullptr) {
	  if (p->nodeType == NODE_OP) {
		  p->child->type->copy((yyvsp[(1) - (3)])->type);
	  }
	  else {
	  	p->type->copy((yyvsp[(1) - (3)])->type);
	  }
	  p = p->sibling;
  }
  #ifdef DECL_DEBUG
	cout << "# $ reduce varDecl type = " << (yyvsp[(1) - (3)])->type->getTypeInfo() << endl;
	// $$->printAST();
  #endif
;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 317 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_VARLIST); (yyval)->addChild((yyvsp[(1) - (1)]));;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 318 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (3)]); (yyval)->addChild((yyvsp[(3) - (3)]));;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 322 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 323 "src\\parser.y"
    {
	(yyval) = new TreeNode(lineno, NODE_OP);
	(yyval)->optype = OP_DECLASSIGN;
	(yyval)->addChild((yyvsp[(1) - (3)]));
	(yyval)->addChild((yyvsp[(3) - (3)]));
  ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 329 "src\\parser.y"
    {
	(yyval) = new TreeNode(lineno, NODE_OP);
	(yyval)->optype = OP_DECLASSIGN;
	(yyval)->addChild((yyvsp[(1) - (5)]));
	(yyval)->addChild((yyvsp[(4) - (5)]));
  ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 340 "src\\parser.y"
    {
	(yyval) = new TreeNode(lineno, NODE_STMT);
	(yyval)->stype = STMT_FUNCDECL;
	(yyvsp[(2) - (8)])->type->type = COMPOSE_FUNCTION;
	TreeNode* param = (yyvsp[(4) - (8)]);
	while (param != nullptr) {
		(yyvsp[(2) - (8)])->type->paramType[(yyvsp[(2) - (8)])->type->paramNum] = param->child->type;
		(yyvsp[(2) - (8)])->type->paramNum++;
		param = param->sibling;
	}
	(yyvsp[(2) - (8)])->type->retType = (yyvsp[(1) - (8)])->type;
	(yyval)->addChild((yyvsp[(1) - (8)]));
	(yyval)->addChild((yyvsp[(2) - (8)]));
	TreeNode* params = new TreeNode(lineno, NODE_VARLIST);
	params->addChild((yyvsp[(4) - (8)]));
	(yyval)->addChild(params);
	TreeNode* funcBlock = new TreeNode(lineno, NODE_STMT);
	funcBlock->stype = STMT_BLOCK;
	funcBlock->addChild((yyvsp[(7) - (8)]));
	(yyval)->addChild(funcBlock);
	scopePop();
  ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 362 "src\\parser.y"
    {
	(yyval) = new TreeNode(lineno, NODE_STMT);
	(yyval)->stype = STMT_FUNCDECL;
	(yyvsp[(2) - (7)])->type->type = COMPOSE_FUNCTION;
	(yyvsp[(2) - (7)])->type->retType = (yyvsp[(1) - (7)])->type;
	(yyval)->addChild((yyvsp[(1) - (7)]));
	(yyval)->addChild((yyvsp[(2) - (7)]));
	(yyval)->addChild(new TreeNode(lineno, NODE_VARLIST));
	TreeNode* funcBlock = new TreeNode(lineno, NODE_STMT);
	funcBlock->stype = STMT_BLOCK;
	funcBlock->addChild((yyvsp[(6) - (7)]));
	(yyval)->addChild(funcBlock);
	scopePop();
  ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 378 "src\\parser.y"
    {scopePush();;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 381 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 382 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (3)]); (yyval)->addSibling((yyvsp[(3) - (3)]));;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 386 "src\\parser.y"
    {
	(yyval) = new TreeNode(lineno, NODE_PARAM); 
	(yyval)->addChild((yyvsp[(1) - (2)])); 
	(yyval)->addChild((yyvsp[(2) - (2)]));
	(yyvsp[(2) - (2)])->type->copy((yyvsp[(1) - (2)])->type);
  ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 397 "src\\parser.y"
    {
	(yyval) = new TreeNode(lineno, NODE_STMT);
	(yyval)->stype = STMT_BLOCK;
	(yyval)->addChild((yyvsp[(2) - (3)]));
;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 403 "src\\parser.y"
    {scopePush();;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 404 "src\\parser.y"
    {scopePop();;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 407 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 408 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (2)]); (yyval)->addSibling((yyvsp[(2) - (2)]));;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 412 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 413 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 417 "src\\parser.y"
    {
	(yyval) = new TreeNode(lineno, NODE_STMT);
	(yyval)->stype = STMT_BLOCK;
	(yyval)->addChild((yyvsp[(2) - (3)]));
  ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 422 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 426 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_STMT); (yyval)->stype = STMT_SKIP;;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 427 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (2)]);;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 428 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 429 "src\\parser.y"
    {
	(yyval) = new TreeNode(lineno, NODE_STMT);
	(yyval)->stype = STMT_IFELSE;
	(yyval)->addChild((yyvsp[(3) - (7)]));
	(yyval)->addChild((yyvsp[(5) - (7)]));
	(yyval)->addChild((yyvsp[(7) - (7)]));
	scopePop();
	#ifdef IFELSE_DEBUG
		cout << "# $ reduce IF-ELSE at scope : " << presentScope << ", at line " << lineno << endl;
	#endif
  ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 440 "src\\parser.y"
    {
	(yyval) = new TreeNode(lineno, NODE_STMT);
	(yyval)->stype = STMT_IF;
	(yyval)->addChild((yyvsp[(3) - (5)]));
	(yyval)->addChild((yyvsp[(5) - (5)]));
	scopePop();
	#ifdef IF_DEBUG
		cout << "% # $ reduce IF at scope : " << presentScope << ", at line " << lineno << endl;
	#endif
  ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 450 "src\\parser.y"
    {
	(yyval) = new TreeNode(lineno, NODE_STMT);
	(yyval)->stype = STMT_WHILE;
	(yyval)->addChild((yyvsp[(3) - (5)]));
	(yyval)->addChild((yyvsp[(5) - (5)]));
	inCycle = false;
	scopePop();
	#ifdef WHILE
		cout << "# $ reduce WHILE at scope : " << presentScope << ", at line " << lineno << endl;
	#endif
  ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 461 "src\\parser.y"
    {
	(yyval) = new TreeNode(lineno, NODE_STMT);
	(yyval)->stype = STMT_FOR;
	TreeNode* forDecl = new TreeNode(lineno, NODE_STMT);
	forDecl->stype = STMT_DECL;
	forDecl->addChild((yyvsp[(3) - (10)]));
	TreeNode* p = (yyvsp[(4) - (10)])->child;
	while (p) {
		if (p->nodeType == NODE_OP) {
			p->child->type->copy((yyvsp[(3) - (10)])->type);
		}
		else {
			p->type->copy((yyvsp[(3) - (10)])->type);
		}
		p = p->sibling;
	}
	forDecl->addChild((yyvsp[(4) - (10)]));
	(yyval)->addChild(forDecl);
	(yyval)->addChild((yyvsp[(6) - (10)]));
	(yyval)->addChild((yyvsp[(8) - (10)]));
	(yyval)->addChild((yyvsp[(10) - (10)]));
	inCycle = false;
	scopePop();
  ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 485 "src\\parser.y"
    {
	(yyval) = new TreeNode(lineno, NODE_STMT);
	(yyval)->stype = STMT_FOR;
	(yyval)->addChild((yyvsp[(3) - (9)]));
	(yyval)->addChild((yyvsp[(5) - (9)]));
	(yyval)->addChild((yyvsp[(7) - (9)]));
	(yyval)->addChild((yyvsp[(9) - (9)]));
	inCycle = false;
	scopePop();
  ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 496 "src\\parser.y"
    {
	if (!inCycle) {
		yyerror("break statement outside loop");
	}
	(yyval) = new TreeNode(lineno, NODE_STMT); 
	(yyval)->stype = STMT_BREAK; 
	(yyval)->type = TYPE_NONE;
  ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 504 "src\\parser.y"
    {
	if (!inCycle) {
		yyerror("continue statement outside loop");
	}
	(yyval) = new TreeNode(lineno, NODE_STMT); 
	(yyval)->stype = STMT_CONTINUE; 
	(yyval)->type = TYPE_NONE;
  ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 512 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_STMT); (yyval)->stype = STMT_RETURN; (yyval)->type = TYPE_NONE;;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 513 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_STMT); (yyval)->stype = STMT_RETURN; (yyval)->addChild((yyvsp[(2) - (3)])); (yyval)->type = TYPE_NONE;;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 516 "src\\parser.y"
    {scopePush();;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 517 "src\\parser.y"
    {inCycle = true; scopePush();;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 518 "src\\parser.y"
    {inCycle = true; scopePush();;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 523 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 524 "src\\parser.y"
    {
	(yyval) = new TreeNode(lineno, NODE_OP);
	(yyval)->optype = OP_ASSIGN;
	(yyval)->addChild((yyvsp[(1) - (3)]));
	(yyval)->addChild((yyvsp[(3) - (3)]));
	#ifdef ASSIGN_DEBUG
		cout << "# $ reduce ASSIGN at scope : " << presentScope << ", at line " << lineno << endl;
		// $$->printAST();
	#endif
  ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 534 "src\\parser.y"
    {
	(yyval) = new TreeNode(lineno, NODE_OP);
	(yyval)->optype = OP_ADDASSIGN;
	(yyval)->addChild((yyvsp[(1) - (3)]));
	(yyval)->addChild((yyvsp[(3) - (3)]));
  ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 540 "src\\parser.y"
    {
	(yyval) = new TreeNode(lineno, NODE_OP);
	(yyval)->optype = OP_SUBASSIGN;
	(yyval)->addChild((yyvsp[(1) - (3)]));
	(yyval)->addChild((yyvsp[(3) - (3)]));
  ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 546 "src\\parser.y"
    {
	(yyval) = new TreeNode(lineno, NODE_OP);
	(yyval)->optype = OP_MULASSIGN;
	(yyval)->addChild((yyvsp[(1) - (3)]));
	(yyval)->addChild((yyvsp[(3) - (3)]));
  ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 552 "src\\parser.y"
    {
	(yyval) = new TreeNode(lineno, NODE_OP);
	(yyval)->optype = OP_DIVASSIGN;
	(yyval)->addChild((yyvsp[(1) - (3)]));
	(yyval)->addChild((yyvsp[(3) - (3)]));
  ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 561 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 565 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 566 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_ADD; (yyval)->addChild((yyvsp[(1) - (3)])); (yyval)->addChild((yyvsp[(3) - (3)]));;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 567 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_SUB; (yyval)->addChild((yyvsp[(1) - (3)])); (yyval)->addChild((yyvsp[(3) - (3)]));;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 572 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 573 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_MUL; (yyval)->addChild((yyvsp[(1) - (3)])); (yyval)->addChild((yyvsp[(3) - (3)]));;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 574 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_DIV; (yyval)->addChild((yyvsp[(1) - (3)])); (yyval)->addChild((yyvsp[(3) - (3)]));;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 575 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_MOD; (yyval)->addChild((yyvsp[(1) - (3)])); (yyval)->addChild((yyvsp[(3) - (3)]));;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 580 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 581 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_NOT; (yyval)->addChild((yyvsp[(2) - (2)]));;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 582 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_POS; (yyval)->addChild((yyvsp[(2) - (2)]));;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 583 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_NAG; (yyval)->addChild((yyvsp[(2) - (2)]));;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 584 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_INC; (yyval)->addChild((yyvsp[(1) - (2)]));;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 585 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_DEC; (yyval)->addChild((yyvsp[(1) - (2)]));;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 590 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 591 "src\\parser.y"
    {(yyval) = (yyvsp[(2) - (3)]);;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 592 "src\\parser.y"
    {(yyval) = (yyvsp[(2) - (3)]);;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 593 "src\\parser.y"
    {
	(yyval) = new TreeNode(lineno, NODE_FUNCALL);
	(yyval)->addChild((yyvsp[(1) - (4)]));
	(yyval)->addChild((yyvsp[(3) - (4)]));
	#ifdef FUNCALL_DEBUG
		cout << "# $ reduce function call at scope : " << presentScope << ", at line " << lineno << endl;
	#endif
  ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 601 "src\\parser.y"
    {
	(yyval) = new TreeNode(lineno, NODE_FUNCALL);
	(yyval)->addChild((yyvsp[(1) - (3)]));
	(yyval)->addChild(new TreeNode(lineno, NODE_VARLIST));
	#ifdef FUNCALL_DEBUG
		cout << "# $ reduce function call at scope : " << presentScope << ", at line " << lineno << endl;
	#endif
  ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 609 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_EXPR); (yyval)->addChild((yyvsp[(1) - (1)]));;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 614 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_VARLIST); (yyval)->addChild((yyvsp[(1) - (1)]));;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 615 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (3)]); (yyval)->addChild((yyvsp[(3) - (3)]));;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 620 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 621 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_OR; (yyval)->addChild((yyvsp[(1) - (3)])); (yyval)->addChild((yyvsp[(3) - (3)]));;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 626 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 627 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_AND; (yyval)->addChild((yyvsp[(1) - (3)])); (yyval)->addChild((yyvsp[(3) - (3)]));;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 632 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 633 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_EQ; (yyval)->addChild((yyvsp[(1) - (3)])); (yyval)->addChild((yyvsp[(3) - (3)]));;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 634 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_NEQ; (yyval)->addChild((yyvsp[(1) - (3)])); (yyval)->addChild((yyvsp[(3) - (3)]));;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 639 "src\\parser.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 640 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_GRA; (yyval)->addChild((yyvsp[(1) - (3)])); (yyval)->addChild((yyvsp[(3) - (3)]));;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 641 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_LES; (yyval)->addChild((yyvsp[(1) - (3)])); (yyval)->addChild((yyvsp[(3) - (3)]));;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 642 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_GRAEQ; (yyval)->addChild((yyvsp[(1) - (3)])); (yyval)->addChild((yyvsp[(3) - (3)]));;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 643 "src\\parser.y"
    {(yyval) = new TreeNode(lineno, NODE_OP); (yyval)->optype = OP_LESEQ; (yyval)->addChild((yyvsp[(1) - (3)])); (yyval)->addChild((yyvsp[(3) - (3)]));;}
    break;



/* Line 1455 of yacc.c  */
#line 2777 "src\\parser.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 646 "src\\parser.y"


int yyerror(char const * message)
{
	cout << "error: " << message << ", at line " << lineno << endl;
	parserError = true;
#ifdef EXIT_AT_GRAMMA_ERROR
	exit(0);
#else
	return 0;
#endif
}

/*
 *	作用域比较函数 int scopeCmp (string, string)
 *
 *  输入参数： 
 *    presScope： 当前变量所处的作用域
 *    varScope:   希望进行比较的已声明变量作用域
 *
 *  返回值：
 *    0： 作用域相同，
 *          若为变量声明语句，为变量重定义。
 *   >0： 已声明变量作用域在当前作用域外层，返回作用域距离（堆栈层数）
 *          若为声明语句，不产生冲突，当前变量为新定义变量，
 *          若为使用语句，当前变量为新定义变量。
 *   -1：已声明变量作用域在当前作用域内层，
 *          若为声明语句，不可能出现这种情况，
 *          若为使用语句，不产生冲突。
 *   -2：两个作用域互不包含，任何情况下都不会互相干扰
 */
int scopeCmp(string presScope, string varScope) {
	unsigned int plen = presScope.length(), vlen = varScope.length();
	unsigned int minlen = min(plen, vlen);
	if (presScope.substr(0, minlen) == varScope.substr(0, minlen)) {
		if (plen >= vlen)
			return plen - vlen;
		else
			return -1;
	}
	return -2;
}

void scopePush() {
	presentScope += max_scope_id;
	max_scope_id = SCOPT_ID_BASE;
	top++;
#ifdef SCOPE_DEBUG
	cout << "* push -> " << presentScope << ", at line " << lineno << endl;
#endif
}

void scopePop() {
	max_scope_id = presentScope[top] + 1;
	presentScope = presentScope.substr(0, presentScope.length() - 1);
	top--;
#ifdef SCOPE_DEBUG
	cout << "* pop -> " << presentScope << ", at line " << lineno << endl;
#endif
}

/*
 *	变量作用域切换只会发生在以下地方：
 *
 *		函数体		type funcName ( params ) block
 *								  ↑ push		  ↑ pop
 *
 *		block块		{ stmts }
 *					↑ push	↑ pop
 *
 *		if语句		IF ( cond ) block
 *					↑ push			  ↑ pop
 *
 *					IF ( cond ) block ELSE block
 *					↑ push						 ↑ pop
 *
 *		while语句	WHILE ( cond ) block
 *					↑ push				 ↑ pop
 *
 *		for语句		FOR ( expr ; cond ; expr ) block
 *					↑ push							 ↑ pop
 *
 *					FOR ( decl ; cond ; expr ) block
 *					↑ push							 ↑ pop
 *
 * 	可得作用域推进表：
 *
 *		push:
 *			IF
 *			WHILE
 *			FOR
 *			funcLPAREN
 *		pop:
 *			ifStmt(代码段尾部)
 *			whileStmt(代码段尾部)
 *			forStmt(代码段尾部)
 *			funcDef(代码段尾部)
 */

