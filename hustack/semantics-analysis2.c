#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ================= HEADERS ================= */
/*
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#ifndef __CHARCODE_H__
#define __CHARCODE_H__

typedef enum
{
  CHAR_SPACE,
  CHAR_LETTER,
  CHAR_DIGIT,
  CHAR_PLUS,
  CHAR_MINUS,
  CHAR_TIMES,
  CHAR_SLASH,
  CHAR_LT,
  CHAR_GT,
  CHAR_EXCLAIMATION,
  CHAR_EQ,
  CHAR_COMMA,
  CHAR_PERIOD,
  CHAR_COLON,
  CHAR_SEMICOLON,
  CHAR_SINGLEQUOTE,
  CHAR_LPAR,
  CHAR_RPAR,
  CHAR_UNKNOWN
} CharCode;

#endif

/*
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#ifndef __TOKEN_H__
#define __TOKEN_H__

#define MAX_IDENT_LEN 15
#define KEYWORDS_COUNT 20

typedef enum
{
  TK_NONE,
  TK_IDENT,
  TK_NUMBER,
  TK_CHAR,
  TK_EOF,

  KW_PROGRAM,
  KW_CONST,
  KW_TYPE,
  KW_VAR,
  KW_INTEGER,
  KW_CHAR,
  KW_ARRAY,
  KW_OF,
  KW_FUNCTION,
  KW_PROCEDURE,
  KW_BEGIN,
  KW_END,
  KW_CALL,
  KW_IF,
  KW_THEN,
  KW_ELSE,
  KW_WHILE,
  KW_DO,
  KW_FOR,
  KW_TO,

  SB_SEMICOLON,
  SB_COLON,
  SB_PERIOD,
  SB_COMMA,
  SB_ASSIGN,
  SB_EQ,
  SB_NEQ,
  SB_LT,
  SB_LE,
  SB_GT,
  SB_GE,
  SB_PLUS,
  SB_MINUS,
  SB_TIMES,
  SB_SLASH,
  SB_LPAR,
  SB_RPAR,
  SB_LSEL,
  SB_RSEL
} TokenType;

typedef struct
{
  char string[MAX_IDENT_LEN + 1];
  int lineNo, colNo;
  TokenType tokenType;
  int value;
} Token;

TokenType checkKeyword(char *string);
Token *makeToken(TokenType tokenType, int lineNo, int colNo);
char *tokenToString(TokenType tokenType);

#endif

/*
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#ifndef __ERROR_H__
#define __ERROR_H__

typedef enum
{
  ERR_END_OF_COMMENT,
  ERR_IDENT_TOO_LONG,
  ERR_INVALID_CONSTANT_CHAR,
  ERR_INVALID_SYMBOL,
  ERR_INVALID_IDENT,
  ERR_INVALID_CONSTANT,
  ERR_INVALID_TYPE,
  ERR_INVALID_BASICTYPE,
  ERR_INVALID_VARIABLE,
  ERR_INVALID_FUNCTION,
  ERR_INVALID_PROCEDURE,
  ERR_INVALID_PARAMETER,
  ERR_INVALID_STATEMENT,
  ERR_INVALID_COMPARATOR,
  ERR_INVALID_EXPRESSION,
  ERR_INVALID_TERM,
  ERR_INVALID_FACTOR,
  ERR_INVALID_LVALUE,
  ERR_INVALID_ARGUMENTS,
  ERR_UNDECLARED_IDENT,
  ERR_UNDECLARED_CONSTANT,
  ERR_UNDECLARED_INT_CONSTANT,
  ERR_UNDECLARED_TYPE,
  ERR_UNDECLARED_VARIABLE,
  ERR_UNDECLARED_FUNCTION,
  ERR_UNDECLARED_PROCEDURE,
  ERR_DUPLICATE_IDENT,
  ERR_TYPE_INCONSISTENCY,
  ERR_PARAMETERS_ARGUMENTS_INCONSISTENCY
} ErrorCode;

void error(ErrorCode err, int lineNo, int colNo);
void missingToken(TokenType tokenType, int lineNo, int colNo);
void assert(char *msg);

#endif

/*
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#ifndef __READER_H__
#define __READER_H__

#define IO_ERROR 0
#define IO_SUCCESS 1

int readChar(void);
int openInputStream(char *fileName);
void closeInputStream(void);

#endif

/* Scanner
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#ifndef __SCANNER_H__
#define __SCANNER_H__

Token *getToken(void);
Token *getValidToken(void);
void printToken(Token *token);

#endif

/*
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#ifndef __SYMTAB_H__
#define __SYMTAB_H__

enum TypeClass
{
  TP_INT,
  TP_CHAR,
  TP_ARRAY
};

enum ObjectKind
{
  OBJ_CONSTANT,
  OBJ_VARIABLE,
  OBJ_TYPE,
  OBJ_FUNCTION,
  OBJ_PROCEDURE,
  OBJ_PARAMETER,
  OBJ_PROGRAM
};

enum ParamKind
{
  PARAM_VALUE,
  PARAM_REFERENCE
};

struct Type_
{
  enum TypeClass typeClass;
  int arraySize;
  struct Type_ *elementType;
};

typedef struct Type_ Type;
typedef struct Type_ BasicType;

struct ConstantValue_
{
  enum TypeClass type;
  union
  {
    int intValue;
    char charValue;
  };
};

typedef struct ConstantValue_ ConstantValue;

struct Scope_;
struct ObjectNode_;
struct Object_;

struct ConstantAttributes_
{
  ConstantValue *value;
};

struct VariableAttributes_
{
  Type *type;
  struct Scope_ *scope;
};

struct TypeAttributes_
{
  Type *actualType;
};

struct ProcedureAttributes_
{
  struct ObjectNode_ *paramList;
  struct Scope_ *scope;
};

struct FunctionAttributes_
{
  struct ObjectNode_ *paramList;
  Type *returnType;
  struct Scope_ *scope;
};

struct ProgramAttributes_
{
  struct Scope_ *scope;
};

struct ParameterAttributes_
{
  enum ParamKind kind;
  Type *type;
  struct Object_ *function;
};

typedef struct ConstantAttributes_ ConstantAttributes;
typedef struct TypeAttributes_ TypeAttributes;
typedef struct VariableAttributes_ VariableAttributes;
typedef struct FunctionAttributes_ FunctionAttributes;
typedef struct ProcedureAttributes_ ProcedureAttributes;
typedef struct ProgramAttributes_ ProgramAttributes;
typedef struct ParameterAttributes_ ParameterAttributes;

struct Object_
{
  char name[MAX_IDENT_LEN];
  enum ObjectKind kind;
  union
  {
    ConstantAttributes *constAttrs;
    VariableAttributes *varAttrs;
    TypeAttributes *typeAttrs;
    FunctionAttributes *funcAttrs;
    ProcedureAttributes *procAttrs;
    ProgramAttributes *progAttrs;
    ParameterAttributes *paramAttrs;
  };
};

typedef struct Object_ Object;

struct ObjectNode_
{
  Object *object;
  struct ObjectNode_ *next;
};

typedef struct ObjectNode_ ObjectNode;

struct Scope_
{
  ObjectNode *objList;
  Object *owner;
  struct Scope_ *outer;
};

typedef struct Scope_ Scope;

struct SymTab_
{
  Object *program;
  Scope *currentScope;
  ObjectNode *globalObjectList;
};

typedef struct SymTab_ SymTab;

Type *makeIntType(void);
Type *makeCharType(void);
Type *makeArrayType(int arraySize, Type *elementType);
Type *duplicateType(Type *type);
int compareType(Type *type1, Type *type2);
void freeType(Type *type);

ConstantValue *makeIntConstant(int i);
ConstantValue *makeCharConstant(char ch);
ConstantValue *duplicateConstantValue(ConstantValue *v);

Scope *createScope(Object *owner, Scope *outer);

Object *createProgramObject(char *programName);
Object *createConstantObject(char *name);
Object *createTypeObject(char *name);
Object *createVariableObject(char *name);
Object *createFunctionObject(char *name);
Object *createProcedureObject(char *name);
Object *createParameterObject(char *name, enum ParamKind kind, Object *owner);

Object *findObject(ObjectNode *objList, char *name);

void initSymTab(void);
void cleanSymTab(void);
void enterBlock(Scope *scope);
void exitBlock(void);
Object *lookupObject(char *name);
void declareObject(Object *obj);

#endif

/*
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */
#ifndef __PARSER_H__
#define __PARSER_H__

void scan(void);
void eat(TokenType tokenType);

void compileProgram(void);
void compileBlock(void);
void compileBlock2(void);
void compileBlock3(void);
void compileBlock4(void);
void compileBlock5(void);
void compileConstDecls(void);
void compileConstDecl(void);
void compileTypeDecls(void);
void compileTypeDecl(void);
void compileVarDecls(void);
void compileVarDecl(void);
void compileSubDecls(void);
void compileFuncDecl(void);
void compileProcDecl(void);
ConstantValue *compileUnsignedConstant(void);
ConstantValue *compileConstant(void);
ConstantValue *compileConstant2(void);
Type *compileType(void);
Type *compileBasicType(void);
void compileParams(void);
void compileParam(void);
void compileStatements(void);
void compileStatement(void);
void compileLValue(void);
void compileAssignSt(void);
void compileCallSt(void);
void compileGroupSt(void);
void compileIfSt(void);
void compileElseSt(void);
void compileWhileSt(void);
void compileForSt(void);
void compileArgument(void);
void compileArguments(void);
void compileCondition(void);
void compileExpression(void);
void compileExpression2(void);
void compileExpression3(void);
void compileTerm(void);
void compileTerm2(void);
void compileFactor(void);
void compileIndexes(void);

int compile(char *fileName);

#endif

/*
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#ifndef __DEBUG_H__
#define __DEBUG_H_

void printType(Type *type);
void printConstantValue(ConstantValue *value);
void printObject(Object *obj, int indent);
void printObjectList(ObjectNode *objList, int indent);
void printScope(Scope *scope, int indent);

#endif

/* ================= SOURCES ================= */
/*
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

CharCode charCodes[256] = {
    CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN,
    CHAR_UNKNOWN, CHAR_SPACE, CHAR_SPACE, CHAR_SPACE, CHAR_SPACE, CHAR_SPACE, CHAR_UNKNOWN, CHAR_UNKNOWN,
    CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN,
    CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN,

    CHAR_SPACE, CHAR_EXCLAIMATION, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_SINGLEQUOTE,
    CHAR_LPAR, CHAR_RPAR, CHAR_TIMES, CHAR_PLUS, CHAR_COMMA, CHAR_MINUS, CHAR_PERIOD, CHAR_SLASH,
    CHAR_DIGIT, CHAR_DIGIT, CHAR_DIGIT, CHAR_DIGIT, CHAR_DIGIT, CHAR_DIGIT, CHAR_DIGIT, CHAR_DIGIT,
    CHAR_DIGIT, CHAR_DIGIT, CHAR_COLON, CHAR_SEMICOLON, CHAR_LT, CHAR_EQ, CHAR_GT, CHAR_UNKNOWN,

    CHAR_UNKNOWN, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER,
    CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER,
    CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER,
    CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN,

    CHAR_UNKNOWN, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER,
    CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER,
    CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_LETTER,
    CHAR_LETTER, CHAR_LETTER, CHAR_LETTER, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN,

    CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN,
    CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN,
    CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN,
    CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN,

    CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN,
    CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN,
    CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN,
    CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN,

    CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN,
    CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN,
    CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN,
    CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN,

    CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN,
    CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN,
    CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN,
    CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN, CHAR_UNKNOWN};

/*
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

struct
{
  char string[MAX_IDENT_LEN + 1];
  TokenType tokenType;
} keywords[KEYWORDS_COUNT] = {
    {"PROGRAM", KW_PROGRAM},
    {"CONST", KW_CONST},
    {"TYPE", KW_TYPE},
    {"VAR", KW_VAR},
    {"INTEGER", KW_INTEGER},
    {"CHAR", KW_CHAR},
    {"ARRAY", KW_ARRAY},
    {"OF", KW_OF},
    {"FUNCTION", KW_FUNCTION},
    {"PROCEDURE", KW_PROCEDURE},
    {"BEGIN", KW_BEGIN},
    {"END", KW_END},
    {"CALL", KW_CALL},
    {"IF", KW_IF},
    {"THEN", KW_THEN},
    {"ELSE", KW_ELSE},
    {"WHILE", KW_WHILE},
    {"DO", KW_DO},
    {"FOR", KW_FOR},
    {"TO", KW_TO}};

int keywordEq(char *kw, char *string)
{
  while ((*kw != '\0') && (*string != '\0'))
  {
    if (*kw != *string)
      break;
    kw++;
    string++;
  }
  return ((*kw == '\0') && (*string == '\0'));
}

TokenType checkKeyword(char *string)
{
  int i;
  for (i = 0; i < KEYWORDS_COUNT; i++)
    if (keywordEq(keywords[i].string, string))
      return keywords[i].tokenType;
  return TK_NONE;
}

Token *makeToken(TokenType tokenType, int lineNo, int colNo)
{
  Token *token = (Token *)malloc(sizeof(Token));
  token->tokenType = tokenType;
  token->lineNo = lineNo;
  token->colNo = colNo;
  return token;
}

char *tokenToString(TokenType tokenType)
{
  switch (tokenType)
  {
  case TK_NONE:
    return "None";
  case TK_IDENT:
    return "an identification";
  case TK_NUMBER:
    return "a number";
  case TK_CHAR:
    return "a constant char";
  case TK_EOF:
    return "end of file";

  case KW_PROGRAM:
    return "keyword PROGRAM";
  case KW_CONST:
    return "keyword CONST";
  case KW_TYPE:
    return "keyword TYPE";
  case KW_VAR:
    return "keyword VAR";
  case KW_INTEGER:
    return "keyword INTEGER";
  case KW_CHAR:
    return "keyword CHAR";
  case KW_ARRAY:
    return "keyword ARRAY";
  case KW_OF:
    return "keyword OF";
  case KW_FUNCTION:
    return "keyword FUNCTION";
  case KW_PROCEDURE:
    return "keyword PROCEDURE";
  case KW_BEGIN:
    return "keyword BEGIN";
  case KW_END:
    return "keyword END";
  case KW_CALL:
    return "keyword CALL";
  case KW_IF:
    return "keyword IF";
  case KW_THEN:
    return "keyword THEN";
  case KW_ELSE:
    return "keyword ELSE";
  case KW_WHILE:
    return "keyword WHILE";
  case KW_DO:
    return "keyword DO";
  case KW_FOR:
    return "keyword FOR";
  case KW_TO:
    return "keyword TO";

  case SB_SEMICOLON:
    return "\';\'";
  case SB_COLON:
    return "\':\'";
  case SB_PERIOD:
    return "\'.\'";
  case SB_COMMA:
    return "\',\'";
  case SB_ASSIGN:
    return "\':=\'";
  case SB_EQ:
    return "\'=\'";
  case SB_NEQ:
    return "\'!=\'";
  case SB_LT:
    return "\'<\'";
  case SB_LE:
    return "\'<=\'";
  case SB_GT:
    return "\'>\'";
  case SB_GE:
    return "\'>=\'";
  case SB_PLUS:
    return "\'+\'";
  case SB_MINUS:
    return "\'-\'";
  case SB_TIMES:
    return "\'*\'";
  case SB_SLASH:
    return "\'/\'";
  case SB_LPAR:
    return "\'(\'";
  case SB_RPAR:
    return "\')\'";
  case SB_LSEL:
    return "\'(.\'";
  case SB_RSEL:
    return "\'.)\'";
  default:
    return "";
  }
}

/*
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#define NUM_OF_ERRORS 29

struct ErrorMessage
{
  ErrorCode errorCode;
  char *message;
};

struct ErrorMessage errors[29] = {
    {ERR_END_OF_COMMENT, "End of comment expected."},
    {ERR_IDENT_TOO_LONG, "Identifier too long."},
    {ERR_INVALID_CONSTANT_CHAR, "Invalid char constant."},
    {ERR_INVALID_SYMBOL, "Invalid symbol."},
    {ERR_INVALID_IDENT, "An identifier expected."},
    {ERR_INVALID_CONSTANT, "A constant expected."},
    {ERR_INVALID_TYPE, "A type expected."},
    {ERR_INVALID_BASICTYPE, "A basic type expected."},
    {ERR_INVALID_VARIABLE, "A variable expected."},
    {ERR_INVALID_FUNCTION, "A function identifier expected."},
    {ERR_INVALID_PROCEDURE, "A procedure identifier expected."},
    {ERR_INVALID_PARAMETER, "A parameter expected."},
    {ERR_INVALID_STATEMENT, "Invalid statement."},
    {ERR_INVALID_COMPARATOR, "A comparator expected."},
    {ERR_INVALID_EXPRESSION, "Invalid expression."},
    {ERR_INVALID_TERM, "Invalid term."},
    {ERR_INVALID_FACTOR, "Invalid factor."},
    {ERR_INVALID_LVALUE, "Invalid lvalue in assignment."},
    {ERR_INVALID_ARGUMENTS, "Wrong arguments."},
    {ERR_UNDECLARED_IDENT, "Undeclared identifier."},
    {ERR_UNDECLARED_CONSTANT, "Undeclared constant."},
    {ERR_UNDECLARED_INT_CONSTANT, "Undeclared integer constant."},
    {ERR_UNDECLARED_TYPE, "Undeclared type."},
    {ERR_UNDECLARED_VARIABLE, "Undeclared variable."},
    {ERR_UNDECLARED_FUNCTION, "Undeclared function."},
    {ERR_UNDECLARED_PROCEDURE, "Undeclared procedure."},
    {ERR_DUPLICATE_IDENT, "Duplicate identifier."},
    {ERR_TYPE_INCONSISTENCY, "Type inconsistency"},
    {ERR_PARAMETERS_ARGUMENTS_INCONSISTENCY, "The number of arguments and the number of parameters are inconsistent."}};

void error(ErrorCode err, int lineNo, int colNo)
{
  int i;
  for (i = 0; i < NUM_OF_ERRORS; i++)
    if (errors[i].errorCode == err)
    {
      printf("%d-%d:%s\n", lineNo, colNo, errors[i].message);
      exit(0);
    }
}

void missingToken(TokenType tokenType, int lineNo, int colNo)
{
  printf("%d-%d:Missing %s\n", lineNo, colNo, tokenToString(tokenType));
  exit(0);
}

void assert(char *msg)
{
  printf("%s\n", msg);
}

/*
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

FILE *inputStream;
int lineNo, colNo;
int currentChar;

int readChar(void)
{
  currentChar = getc(inputStream);
  colNo++;
  if (currentChar == '\n')
  {
    lineNo++;
    colNo = 0;
  }
  return currentChar;
}

int openInputStream(char *fileName)
{
  inputStream = stdin;  
  if (fileName) {
    inputStream = fopen(fileName, "rt");
    if (inputStream == NULL)
        return IO_ERROR;
  }

  lineNo = 1;
  colNo = 0;
  readChar();
  return IO_SUCCESS;
}

void closeInputStream()
{
  fclose(inputStream);
}

/* Scanner
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

extern int lineNo;
extern int colNo;
extern int currentChar;

extern CharCode charCodes[];

/***************************************************************/

void skipBlank()
{
  while ((currentChar != EOF) && (charCodes[currentChar] == CHAR_SPACE))
    readChar();
}

void skipComment()
{
  int state = 0;
  while ((currentChar != EOF) && (state < 2))
  {
    switch (charCodes[currentChar])
    {
    case CHAR_TIMES:
      state = 1;
      break;
    case CHAR_RPAR:
      if (state == 1)
        state = 2;
      else
        state = 0;
      break;
    default:
      state = 0;
    }
    readChar();
  }
  if (state != 2)
    error(ERR_END_OF_COMMENT, lineNo, colNo);
}

Token *readIdentKeyword(void)
{
  Token *token = makeToken(TK_NONE, lineNo, colNo);
  int count = 1;

  token->string[0] = toupper((char)currentChar);
  readChar();

  while ((currentChar != EOF) &&
         ((charCodes[currentChar] == CHAR_LETTER) || (charCodes[currentChar] == CHAR_DIGIT)))
  {
    if (count <= MAX_IDENT_LEN)
      token->string[count++] = toupper((char)currentChar);
    readChar();
  }

  if (count > MAX_IDENT_LEN)
  {
    error(ERR_IDENT_TOO_LONG, token->lineNo, token->colNo);
    return token;
  }

  token->string[count] = '\0';
  token->tokenType = checkKeyword(token->string);

  if (token->tokenType == TK_NONE)
    token->tokenType = TK_IDENT;

  return token;
}

Token *readNumber(void)
{
  Token *token = makeToken(TK_NUMBER, lineNo, colNo);
  int count = 0;

  while ((currentChar != EOF) && (charCodes[currentChar] == CHAR_DIGIT))
  {
    token->string[count++] = (char)currentChar;
    readChar();
  }

  token->string[count] = '\0';
  token->value = atoi(token->string);
  return token;
}

Token *readConstChar(void)
{
  Token *token = makeToken(TK_CHAR, lineNo, colNo);

  readChar();
  if (currentChar == EOF)
  {
    token->tokenType = TK_NONE;
    error(ERR_INVALID_CONSTANT_CHAR, token->lineNo, token->colNo);
    return token;
  }

  token->string[0] = currentChar;
  token->string[1] = '\0';

  readChar();
  if (currentChar == EOF)
  {
    token->tokenType = TK_NONE;
    error(ERR_INVALID_CONSTANT_CHAR, token->lineNo, token->colNo);
    return token;
  }

  if (charCodes[currentChar] == CHAR_SINGLEQUOTE)
  {
    readChar();
    return token;
  }
  else
  {
    token->tokenType = TK_NONE;
    error(ERR_INVALID_CONSTANT_CHAR, token->lineNo, token->colNo);
    return token;
  }
}

Token *getToken(void)
{
  Token *token;
  int ln, cn;

  if (currentChar == EOF)
    return makeToken(TK_EOF, lineNo, colNo);

  switch (charCodes[currentChar])
  {
  case CHAR_SPACE:
    skipBlank();
    return getToken();
  case CHAR_LETTER:
    return readIdentKeyword();
  case CHAR_DIGIT:
    return readNumber();
  case CHAR_PLUS:
    token = makeToken(SB_PLUS, lineNo, colNo);
    readChar();
    return token;
  case CHAR_MINUS:
    token = makeToken(SB_MINUS, lineNo, colNo);
    readChar();
    return token;
  case CHAR_TIMES:
    token = makeToken(SB_TIMES, lineNo, colNo);
    readChar();
    return token;
  case CHAR_SLASH:
    token = makeToken(SB_SLASH, lineNo, colNo);
    readChar();
    return token;
  case CHAR_LT:
    ln = lineNo;
    cn = colNo;
    readChar();
    if ((currentChar != EOF) && (charCodes[currentChar] == CHAR_EQ))
    {
      readChar();
      return makeToken(SB_LE, ln, cn);
    }
    else
      return makeToken(SB_LT, ln, cn);
  case CHAR_GT:
    ln = lineNo;
    cn = colNo;
    readChar();
    if ((currentChar != EOF) && (charCodes[currentChar] == CHAR_EQ))
    {
      readChar();
      return makeToken(SB_GE, ln, cn);
    }
    else
      return makeToken(SB_GT, ln, cn);
  case CHAR_EQ:
    token = makeToken(SB_EQ, lineNo, colNo);
    readChar();
    return token;
  case CHAR_EXCLAIMATION:
    ln = lineNo;
    cn = colNo;
    readChar();
    if ((currentChar != EOF) && (charCodes[currentChar] == CHAR_EQ))
    {
      readChar();
      return makeToken(SB_NEQ, ln, cn);
    }
    else
    {
      token = makeToken(TK_NONE, ln, cn);
      error(ERR_INVALID_SYMBOL, ln, cn);
      return token;
    }
  case CHAR_COMMA:
    token = makeToken(SB_COMMA, lineNo, colNo);
    readChar();
    return token;
  case CHAR_PERIOD:
    ln = lineNo;
    cn = colNo;
    readChar();
    if ((currentChar != EOF) && (charCodes[currentChar] == CHAR_RPAR))
    {
      readChar();
      return makeToken(SB_RSEL, ln, cn);
    }
    else
      return makeToken(SB_PERIOD, ln, cn);
  case CHAR_SEMICOLON:
    token = makeToken(SB_SEMICOLON, lineNo, colNo);
    readChar();
    return token;
  case CHAR_COLON:
    ln = lineNo;
    cn = colNo;
    readChar();
    if ((currentChar != EOF) && (charCodes[currentChar] == CHAR_EQ))
    {
      readChar();
      return makeToken(SB_ASSIGN, ln, cn);
    }
    else
      return makeToken(SB_COLON, ln, cn);
  case CHAR_SINGLEQUOTE:
    return readConstChar();
  case CHAR_LPAR:
    ln = lineNo;
    cn = colNo;
    readChar();

    if (currentChar == EOF)
      return makeToken(SB_LPAR, ln, cn);

    switch (charCodes[currentChar])
    {
    case CHAR_PERIOD:
      readChar();
      return makeToken(SB_LSEL, ln, cn);
    case CHAR_TIMES:
      readChar();
      skipComment();
      return getToken();
    default:
      return makeToken(SB_LPAR, ln, cn);
    }
  case CHAR_RPAR:
    token = makeToken(SB_RPAR, lineNo, colNo);
    readChar();
    return token;
  default:
    token = makeToken(TK_NONE, lineNo, colNo);
    error(ERR_INVALID_SYMBOL, lineNo, colNo);
    readChar();
    return token;
  }
}

Token *getValidToken(void)
{
  Token *token = getToken();
  while (token->tokenType == TK_NONE)
  {
    free(token);
    token = getToken();
  }
  return token;
}

/******************************************************************/

void printToken(Token *token)
{

  printf("%d-%d:", token->lineNo, token->colNo);

  switch (token->tokenType)
  {
  case TK_NONE:
    printf("TK_NONE\n");
    break;
  case TK_IDENT:
    printf("TK_IDENT(%s)\n", token->string);
    break;
  case TK_NUMBER:
    printf("TK_NUMBER(%s)\n", token->string);
    break;
  case TK_CHAR:
    printf("TK_CHAR(\'%s\')\n", token->string);
    break;
  case TK_EOF:
    printf("TK_EOF\n");
    break;

  case KW_PROGRAM:
    printf("KW_PROGRAM\n");
    break;
  case KW_CONST:
    printf("KW_CONST\n");
    break;
  case KW_TYPE:
    printf("KW_TYPE\n");
    break;
  case KW_VAR:
    printf("KW_VAR\n");
    break;
  case KW_INTEGER:
    printf("KW_INTEGER\n");
    break;
  case KW_CHAR:
    printf("KW_CHAR\n");
    break;
  case KW_ARRAY:
    printf("KW_ARRAY\n");
    break;
  case KW_OF:
    printf("KW_OF\n");
    break;
  case KW_FUNCTION:
    printf("KW_FUNCTION\n");
    break;
  case KW_PROCEDURE:
    printf("KW_PROCEDURE\n");
    break;
  case KW_BEGIN:
    printf("KW_BEGIN\n");
    break;
  case KW_END:
    printf("KW_END\n");
    break;
  case KW_CALL:
    printf("KW_CALL\n");
    break;
  case KW_IF:
    printf("KW_IF\n");
    break;
  case KW_THEN:
    printf("KW_THEN\n");
    break;
  case KW_ELSE:
    printf("KW_ELSE\n");
    break;
  case KW_WHILE:
    printf("KW_WHILE\n");
    break;
  case KW_DO:
    printf("KW_DO\n");
    break;
  case KW_FOR:
    printf("KW_FOR\n");
    break;
  case KW_TO:
    printf("KW_TO\n");
    break;

  case SB_SEMICOLON:
    printf("SB_SEMICOLON\n");
    break;
  case SB_COLON:
    printf("SB_COLON\n");
    break;
  case SB_PERIOD:
    printf("SB_PERIOD\n");
    break;
  case SB_COMMA:
    printf("SB_COMMA\n");
    break;
  case SB_ASSIGN:
    printf("SB_ASSIGN\n");
    break;
  case SB_EQ:
    printf("SB_EQ\n");
    break;
  case SB_NEQ:
    printf("SB_NEQ\n");
    break;
  case SB_LT:
    printf("SB_LT\n");
    break;
  case SB_LE:
    printf("SB_LE\n");
    break;
  case SB_GT:
    printf("SB_GT\n");
    break;
  case SB_GE:
    printf("SB_GE\n");
    break;
  case SB_PLUS:
    printf("SB_PLUS\n");
    break;
  case SB_MINUS:
    printf("SB_MINUS\n");
    break;
  case SB_TIMES:
    printf("SB_TIMES\n");
    break;
  case SB_SLASH:
    printf("SB_SLASH\n");
    break;
  case SB_LPAR:
    printf("SB_LPAR\n");
    break;
  case SB_RPAR:
    printf("SB_RPAR\n");
    break;
  case SB_LSEL:
    printf("SB_LSEL\n");
    break;
  case SB_RSEL:
    printf("SB_RSEL\n");
    break;
  }
}

/*
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

void freeObject(Object *obj);
void freeScope(Scope *scope);
void freeObjectList(ObjectNode *objList);
void freeReferenceList(ObjectNode *objList);

SymTab *symtab;
Type *intType;
Type *charType;

/******************* Type utilities ******************************/

Type *makeIntType(void)
{
  Type *type = (Type *)malloc(sizeof(Type));
  type->typeClass = TP_INT;
  return type;
}

Type *makeCharType(void)
{
  Type *type = (Type *)malloc(sizeof(Type));
  type->typeClass = TP_CHAR;
  return type;
}

Type *makeArrayType(int arraySize, Type *elementType)
{
  Type *type = (Type *)malloc(sizeof(Type));
  type->typeClass = TP_ARRAY;
  type->arraySize = arraySize;
  type->elementType = elementType;
  return type;
}

Type *duplicateType(Type *type)
{
  Type *resultType = (Type *)malloc(sizeof(Type));
  resultType->typeClass = type->typeClass;
  if (type->typeClass == TP_ARRAY)
  {
    resultType->arraySize = type->arraySize;
    resultType->elementType = duplicateType(type->elementType);
  }
  return resultType;
}

int compareType(Type *type1, Type *type2)
{
  if (type1->typeClass == type2->typeClass)
  {
    if (type1->typeClass == TP_ARRAY)
    {
      if (type1->arraySize == type2->arraySize)
        return compareType(type1->elementType, type2->elementType);
      else
        return 0;
    }
    else
      return 1;
  }
  else
    return 0;
}

void freeType(Type *type)
{
  switch (type->typeClass)
  {
  case TP_INT:
  case TP_CHAR:
    free(type);
    break;
  case TP_ARRAY:
    freeType(type->elementType);
    freeType(type);
    break;
  }
}

/******************* Constant utility ******************************/

ConstantValue *makeIntConstant(int i)
{
  ConstantValue *value = (ConstantValue *)malloc(sizeof(ConstantValue));
  value->type = TP_INT;
  value->intValue = i;
  return value;
}

ConstantValue *makeCharConstant(char ch)
{
  ConstantValue *value = (ConstantValue *)malloc(sizeof(ConstantValue));
  value->type = TP_CHAR;
  value->charValue = ch;
  return value;
}

ConstantValue *duplicateConstantValue(ConstantValue *v)
{
  ConstantValue *value = (ConstantValue *)malloc(sizeof(ConstantValue));
  value->type = v->type;
  if (v->type == TP_INT)
    value->intValue = v->intValue;
  else
    value->charValue = v->charValue;
  return value;
}

/******************* Object utilities ******************************/

Scope *createScope(Object *owner, Scope *outer)
{
  Scope *scope = (Scope *)malloc(sizeof(Scope));
  scope->objList = NULL;
  scope->owner = owner;
  scope->outer = outer;
  return scope;
}

Object *createProgramObject(char *programName)
{
  Object *program = (Object *)malloc(sizeof(Object));
  strcpy(program->name, programName);
  program->kind = OBJ_PROGRAM;
  program->progAttrs = (ProgramAttributes *)malloc(sizeof(ProgramAttributes));
  program->progAttrs->scope = createScope(program, NULL);
  symtab->program = program;

  return program;
}

Object *createConstantObject(char *name)
{
  Object *obj = (Object *)malloc(sizeof(Object));
  strcpy(obj->name, name);
  obj->kind = OBJ_CONSTANT;
  obj->constAttrs = (ConstantAttributes *)malloc(sizeof(ConstantAttributes));
  return obj;
}

Object *createTypeObject(char *name)
{
  Object *obj = (Object *)malloc(sizeof(Object));
  strcpy(obj->name, name);
  obj->kind = OBJ_TYPE;
  obj->typeAttrs = (TypeAttributes *)malloc(sizeof(TypeAttributes));
  return obj;
}

Object *createVariableObject(char *name)
{
  Object *obj = (Object *)malloc(sizeof(Object));
  strcpy(obj->name, name);
  obj->kind = OBJ_VARIABLE;
  obj->varAttrs = (VariableAttributes *)malloc(sizeof(VariableAttributes));
  obj->varAttrs->scope = symtab->currentScope;
  return obj;
}

Object *createFunctionObject(char *name)
{
  Object *obj = (Object *)malloc(sizeof(Object));
  strcpy(obj->name, name);
  obj->kind = OBJ_FUNCTION;
  obj->funcAttrs = (FunctionAttributes *)malloc(sizeof(FunctionAttributes));
  obj->funcAttrs->paramList = NULL;
  obj->funcAttrs->scope = createScope(obj, symtab->currentScope);
  return obj;
}

Object *createProcedureObject(char *name)
{
  Object *obj = (Object *)malloc(sizeof(Object));
  strcpy(obj->name, name);
  obj->kind = OBJ_PROCEDURE;
  obj->procAttrs = (ProcedureAttributes *)malloc(sizeof(ProcedureAttributes));
  obj->procAttrs->paramList = NULL;
  obj->procAttrs->scope = createScope(obj, symtab->currentScope);
  return obj;
}

Object *createParameterObject(char *name, enum ParamKind kind, Object *owner)
{
  Object *obj = (Object *)malloc(sizeof(Object));
  strcpy(obj->name, name);
  obj->kind = OBJ_PARAMETER;
  obj->paramAttrs = (ParameterAttributes *)malloc(sizeof(ParameterAttributes));
  obj->paramAttrs->kind = kind;
  obj->paramAttrs->function = owner;
  return obj;
}

void freeObject(Object *obj)
{
  switch (obj->kind)
  {
  case OBJ_CONSTANT:
    free(obj->constAttrs->value);
    free(obj->constAttrs);
    break;
  case OBJ_TYPE:
    free(obj->typeAttrs->actualType);
    free(obj->typeAttrs);
    break;
  case OBJ_VARIABLE:
    free(obj->varAttrs->type);
    free(obj->varAttrs);
    break;
  case OBJ_FUNCTION:
    freeReferenceList(obj->funcAttrs->paramList);
    freeType(obj->funcAttrs->returnType);
    freeScope(obj->funcAttrs->scope);
    free(obj->funcAttrs);
    break;
  case OBJ_PROCEDURE:
    freeReferenceList(obj->procAttrs->paramList);
    freeScope(obj->procAttrs->scope);
    free(obj->procAttrs);
    break;
  case OBJ_PROGRAM:
    freeScope(obj->progAttrs->scope);
    free(obj->progAttrs);
    break;
  case OBJ_PARAMETER:
    freeType(obj->paramAttrs->type);
    free(obj->paramAttrs);
  }
  free(obj);
}

void freeScope(Scope *scope)
{
  freeObjectList(scope->objList);
  free(scope);
}

void freeObjectList(ObjectNode *objList)
{
  ObjectNode *list = objList;

  while (list != NULL)
  {
    ObjectNode *node = list;
    list = list->next;
    freeObject(node->object);
    free(node);
  }
}

void freeReferenceList(ObjectNode *objList)
{
  ObjectNode *list = objList;

  while (list != NULL)
  {
    ObjectNode *node = list;
    list = list->next;
    free(node);
  }
}

void addObject(ObjectNode **objList, Object *obj)
{
  ObjectNode *node = (ObjectNode *)malloc(sizeof(ObjectNode));
  node->object = obj;
  node->next = NULL;
  if ((*objList) == NULL)
    *objList = node;
  else
  {
    ObjectNode *n = *objList;
    while (n->next != NULL)
      n = n->next;
    n->next = node;
  }
}

Object *findObject(ObjectNode *objList, char *name)
{
  while (objList != NULL)
  {
    if (strcmp(objList->object->name, name) == 0)
      return objList->object;
    else
      objList = objList->next;
  }
  return NULL;
}

/******************* others ******************************/

void initSymTab(void)
{
  Object *obj;
  Object *param;

  symtab = (SymTab *)malloc(sizeof(SymTab));
  symtab->globalObjectList = NULL;

  obj = createFunctionObject("READC");
  obj->funcAttrs->returnType = makeCharType();
  addObject(&(symtab->globalObjectList), obj);

  obj = createFunctionObject("READI");
  obj->funcAttrs->returnType = makeIntType();
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITEI");
  param = createParameterObject("i", PARAM_VALUE, obj);
  param->paramAttrs->type = makeIntType();
  addObject(&(obj->procAttrs->paramList), param);
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITEC");
  param = createParameterObject("ch", PARAM_VALUE, obj);
  param->paramAttrs->type = makeCharType();
  addObject(&(obj->procAttrs->paramList), param);
  addObject(&(symtab->globalObjectList), obj);

  obj = createProcedureObject("WRITELN");
  addObject(&(symtab->globalObjectList), obj);

  intType = makeIntType();
  charType = makeCharType();
}

void cleanSymTab(void)
{
  freeObject(symtab->program);
  freeObjectList(symtab->globalObjectList);
  free(symtab);
  freeType(intType);
  freeType(charType);
}

void enterBlock(Scope *scope)
{
  symtab->currentScope = scope;
}

void exitBlock(void)
{
  symtab->currentScope = symtab->currentScope->outer;
}


void declareObject(Object *obj)
{
  if (obj->kind == OBJ_PARAMETER)
  {
    Object *owner = symtab->currentScope->owner;
    switch (owner->kind)
    {
    case OBJ_FUNCTION:
      addObject(&(owner->funcAttrs->paramList), obj);
      break;
    case OBJ_PROCEDURE:
      addObject(&(owner->procAttrs->paramList), obj);
      break;
    default:
      break;
    }
  }

  addObject(&(symtab->currentScope->objList), obj);
}

/* * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

Token *currentToken;
Token *lookAhead;

extern Type *intType;
extern Type *charType;
extern SymTab *symtab;

void scan(void)
{
  Token *tmp = currentToken;
  currentToken = lookAhead;
  lookAhead = getValidToken();
  free(tmp);
}

void eat(TokenType tokenType)
{
  if (lookAhead->tokenType == tokenType)
  {
    scan();
  }
  else
    missingToken(tokenType, lookAhead->lineNo, lookAhead->colNo);
}

/*********************************************************/

Object* lookupObject(char *name) {
  // TODO
  Scope *scope = symtab->currentScope;
    Object *obj;

    while (scope != NULL)
    {
        obj = findObject(scope->objList, name);
        if (obj != NULL)
            return obj;
        scope = scope->outer;
    }
    obj = findObject(symtab->globalObjectList, name);
    if (obj != NULL)
        return obj;
    return NULL;
}

void checkFreshIdent(char *name) {
  if (findObject(symtab->currentScope->objList, name) != NULL)
    error(ERR_DUPLICATE_IDENT, currentToken->lineNo, currentToken->colNo);
}

Object* checkDeclaredConstant(char *name) {
  Object *obj = lookupObject(name);
  if (obj == NULL)
    error(ERR_UNDECLARED_CONSTANT, currentToken->lineNo, currentToken->colNo);
  if (obj->kind != OBJ_CONSTANT)
    error(ERR_INVALID_CONSTANT, currentToken->lineNo, currentToken->colNo);
  return obj;
}

Object* checkDeclaredType(char *name) {
  Object *obj = lookupObject(name);
  if (obj == NULL)
    error(ERR_UNDECLARED_TYPE, currentToken->lineNo, currentToken->colNo);
  if (obj->kind != OBJ_TYPE)
    error(ERR_INVALID_TYPE, currentToken->lineNo, currentToken->colNo);
  return obj;
}

void compileProgram(void) {
  // TODO: create, enter, and exit program block
    Object* program;

    eat(KW_PROGRAM);
    eat(TK_IDENT);

    program = createProgramObject(currentToken->string);
    enterBlock(program->progAttrs->scope);

    eat(SB_SEMICOLON);

    compileBlock();
    eat(SB_PERIOD);

    exitBlock();
}

void compileBlock(void) {
  // TODO: create and declare constant objects
  Object* constObj;
    ConstantValue* constValue;
    if (lookAhead->tokenType == KW_CONST) {
        eat(KW_CONST);
        do {
        eat(TK_IDENT);
        // Check if a constant identifier is fresh in the block
        checkFreshIdent(currentToken->string);
        // Create a constant object
        constObj = createConstantObject(currentToken->string);   
        eat(SB_EQ);
        // Get the constant value
        constValue = compileConstant();
        constObj->constAttrs->value = constValue;
        // Declare the constant object 
        declareObject(constObj);
        
        eat(SB_SEMICOLON);
        } while (lookAhead->tokenType == TK_IDENT);

        compileBlock2();
    } 
    else compileBlock2();
}

void compileBlock2(void) {
  // TODO: create and declare type objects
  Object* typeObj;
    Type* actualType;

    if (lookAhead->tokenType == KW_TYPE) {
        eat(KW_TYPE);

        do {
        eat(TK_IDENT);
        // Check if a type identifier is fresh in the block
        checkFreshIdent(currentToken->string);
        // create a type object
        typeObj = createTypeObject(currentToken->string);
        
        eat(SB_EQ);
        // Get the actual type
        actualType = compileType();
        typeObj->typeAttrs->actualType = actualType;
        // Declare the type object
        declareObject(typeObj);
        
        eat(SB_SEMICOLON);
        } while (lookAhead->tokenType == TK_IDENT);

        compileBlock3();
    } 
    else compileBlock3();
}

void compileBlock3(void) {
  // TODO: create and declare variable objects
  Object* varObj;
    Type* varType;

    if (lookAhead->tokenType == KW_VAR) {
        eat(KW_VAR);

        do {
        eat(TK_IDENT);
        // Check if a variable identifier is fresh in the block
        checkFreshIdent(currentToken->string);
        // Create a variable object      
        varObj = createVariableObject(currentToken->string);

        eat(SB_COLON);
        // Get the variable type
        varType = compileType();
        varObj->varAttrs->type = varType;
        // Declare the variable object
        declareObject(varObj);
        
        eat(SB_SEMICOLON);
        } while (lookAhead->tokenType == TK_IDENT);

        compileBlock4();
    } 
    else compileBlock4();
}

void compileBlock4(void) {
  compileSubDecls();
  compileBlock5();
}

void compileBlock5(void) {
  eat(KW_BEGIN);
  compileStatements();
  eat(KW_END);
}

void compileSubDecls(void) {
  while ((lookAhead->tokenType == KW_FUNCTION) || (lookAhead->tokenType == KW_PROCEDURE)) {
    if (lookAhead->tokenType == KW_FUNCTION)
      compileFuncDecl();
    else compileProcDecl();
  }
}

void compileFuncDecl(void) {
  // TODO: create and declare a function object
  Object* funcObj;
    Type* returnType;

    eat(KW_FUNCTION);
    eat(TK_IDENT);
    // Check if a function identifier is fresh in the block
    checkFreshIdent(currentToken->string);
    // create the function object
    funcObj = createFunctionObject(currentToken->string);
    // declare the function object
    declareObject(funcObj);
    // enter the function's block
    enterBlock(funcObj->funcAttrs->scope);
    // parse the function's parameters
    compileParams();
    eat(SB_COLON);
    // get the funtion's return type
    returnType = compileBasicType();
    funcObj->funcAttrs->returnType = returnType;

    eat(SB_SEMICOLON);
    compileBlock();
    eat(SB_SEMICOLON);
    // exit the function block
    exitBlock();
}

void compileProcDecl(void) {
  // TODO: create and declare a procedure object
  Object* procObj;

    eat(KW_PROCEDURE);
    eat(TK_IDENT);
    // Check if a procedure identifier is fresh in the block
    checkFreshIdent(currentToken->string);
    // create a procedure object
    procObj = createProcedureObject(currentToken->string);
    // declare the procedure object
    declareObject(procObj);
    // enter the procedure's block
    enterBlock(procObj->procAttrs->scope);
    // parse the procedure's parameters
    compileParams();

    eat(SB_SEMICOLON);
    compileBlock();
    eat(SB_SEMICOLON);
    // exit the block
    exitBlock();
}

ConstantValue* compileUnsignedConstant(void) {
  // TODO: create and return an unsigned constant value
  ConstantValue* constValue;
    Object* obj;

    switch (lookAhead->tokenType) {
    case TK_NUMBER:
        eat(TK_NUMBER);
        constValue = makeIntConstant(currentToken->value);
        break;
    case TK_IDENT:
        eat(TK_IDENT);
        // check if the constant identifier is declared
        obj = checkDeclaredConstant(currentToken->string);
        constValue = duplicateConstantValue(obj->constAttrs->value);

        break;
    case TK_CHAR:
        eat(TK_CHAR);
        constValue = makeCharConstant(currentToken->string[0]);
        break;
    default:
        error(ERR_INVALID_CONSTANT, lookAhead->lineNo, lookAhead->colNo);
        break;
    }
    return constValue;
}

ConstantValue* compileConstant(void) {
  // TODO: create and return a constant
  ConstantValue* constValue;

    switch (lookAhead->tokenType) {
    case SB_PLUS:
        eat(SB_PLUS);
        constValue = compileConstant2();
        break;
    case SB_MINUS:
        eat(SB_MINUS);
        constValue = compileConstant2();
        constValue->intValue = - constValue->intValue;
        break;
    case TK_CHAR:
        eat(TK_CHAR);
        constValue = makeCharConstant(currentToken->string[0]);
        break;
    default:
        constValue = compileConstant2();
        break;
    }
    return constValue;
}

ConstantValue* compileConstant2(void) {
  // TODO: create and return a constant value
  ConstantValue* constValue;
    Object* obj;

    switch (lookAhead->tokenType) {
    case TK_NUMBER:
        eat(TK_NUMBER);
        constValue = makeIntConstant(currentToken->value);
        break;
    case TK_IDENT:
        eat(TK_IDENT);
        // check if the integer constant identifier is declared
        obj = checkDeclaredConstant(currentToken->string);
        if (obj->constAttrs->value->type == TP_INT)
        constValue = duplicateConstantValue(obj->constAttrs->value);
        else
        error(ERR_UNDECLARED_INT_CONSTANT,currentToken->lineNo, currentToken->colNo);
        break;
    default:
        error(ERR_INVALID_CONSTANT, lookAhead->lineNo, lookAhead->colNo);
        break;
    }
    return constValue;
}

Type* compileType(void) {
  // TODO: create and return a type
  Type* type;
    Type* elementType;
    int arraySize;
    Object* obj;

    switch (lookAhead->tokenType) {
    case KW_INTEGER: 
        eat(KW_INTEGER);
        type =  makeIntType();
        break;
    case KW_CHAR: 
        eat(KW_CHAR); 
        type = makeCharType();
        break;
    case KW_ARRAY:
        eat(KW_ARRAY);
        eat(SB_LSEL);
        eat(TK_NUMBER);

        arraySize = currentToken->value;

        eat(SB_RSEL);
        eat(KW_OF);
        elementType = compileType();
        type = makeArrayType(arraySize, elementType);
        break;
    case TK_IDENT:
        eat(TK_IDENT);
        // check if the type idntifier is declared
        obj = checkDeclaredType(currentToken->string);
        type = duplicateType(obj->typeAttrs->actualType);
        break;
    default:
        error(ERR_INVALID_TYPE, lookAhead->lineNo, lookAhead->colNo);
        break;
    }
    return type;
}

Type* compileBasicType(void) {
  // TODO: create and return a basic type
  Type* type;

    switch (lookAhead->tokenType) {
    case KW_INTEGER: 
        eat(KW_INTEGER); 
        type = makeIntType();
        break;
    case KW_CHAR: 
        eat(KW_CHAR); 
        type = makeCharType();
        break;
    default:
        error(ERR_INVALID_BASICTYPE, lookAhead->lineNo, lookAhead->colNo);
        break;
    }
    return type;
}

void compileParams(void) {
  if (lookAhead->tokenType == SB_LPAR) {
    eat(SB_LPAR);
    compileParam();
    while (lookAhead->tokenType == SB_SEMICOLON) {
      eat(SB_SEMICOLON);
      compileParam();
    }
    eat(SB_RPAR);
  }
}

void compileParam(void) {
  // TODO: create and declare a parameter
  Object* param;
    Type* type;
    enum ParamKind paramKind;

    switch (lookAhead->tokenType) {
    case TK_IDENT:
        paramKind = PARAM_VALUE;
        break;
    case KW_VAR:
        eat(KW_VAR);
        paramKind = PARAM_REFERENCE;
        break;
    default:
        error(ERR_INVALID_PARAMETER, lookAhead->lineNo, lookAhead->colNo);
        break;
    }

    eat(TK_IDENT);
    // check if the parameter identifier is fresh in the block
    checkFreshIdent(currentToken->string);
    param = createParameterObject(currentToken->string, paramKind, symtab->currentScope->owner);
    eat(SB_COLON);
    type = compileBasicType();
    param->paramAttrs->type = type;
    declareObject(param);
}

/*****************************************************/
void compileStatements(void)
{
  compileStatement();
  while (lookAhead->tokenType == SB_SEMICOLON)
  {
    eat(SB_SEMICOLON);
    compileStatement();
  }
}

void compileStatement(void)
{
  switch (lookAhead->tokenType)
  {
  case TK_IDENT:
    compileAssignSt();
    break;
  case KW_CALL:
    compileCallSt();
    break;
  case KW_BEGIN:
    compileGroupSt();
    break;
  case KW_IF:
    compileIfSt();
    break;
  case KW_WHILE:
    compileWhileSt();
    break;
  case KW_FOR:
    compileForSt();
    break;
  case SB_SEMICOLON:
  case KW_END:
  case KW_ELSE:
    break;
  default:
    error(ERR_INVALID_STATEMENT, lookAhead->lineNo, lookAhead->colNo);
    break;
  }
}

void compileLValue(void)
{
  eat(TK_IDENT);
  compileIndexes();
}

void compileAssignSt(void)
{
  compileLValue();
  eat(SB_ASSIGN);
  compileExpression();
}

void compileCallSt(void)
{
  eat(KW_CALL);
  eat(TK_IDENT);
  compileArguments();
}

void compileGroupSt(void)
{
  eat(KW_BEGIN);
  compileStatements();
  eat(KW_END);
}

void compileIfSt(void)
{
  eat(KW_IF);
  compileCondition();
  eat(KW_THEN);
  compileStatement();
  if (lookAhead->tokenType == KW_ELSE)
    compileElseSt();
}

void compileElseSt(void)
{
  eat(KW_ELSE);
  compileStatement();
}

void compileWhileSt(void)
{
  eat(KW_WHILE);
  compileCondition();
  eat(KW_DO);
  compileStatement();
}

void compileForSt(void)
{
  eat(KW_FOR);
  eat(TK_IDENT);
  eat(SB_ASSIGN);
  compileExpression();
  eat(KW_TO);
  compileExpression();
  eat(KW_DO);
  compileStatement();
}

void compileArgument(void)
{
  compileExpression();
}

void compileArguments(void)
{
  switch (lookAhead->tokenType)
  {
  case SB_LPAR:
    eat(SB_LPAR);
    compileArgument();

    while (lookAhead->tokenType == SB_COMMA)
    {
      eat(SB_COMMA);
      compileArgument();
    }

    eat(SB_RPAR);
    break;
  case SB_TIMES:
  case SB_SLASH:
  case SB_PLUS:
  case SB_MINUS:
  case KW_TO:
  case KW_DO:
  case SB_RPAR:
  case SB_COMMA:
  case SB_EQ:
  case SB_NEQ:
  case SB_LE:
  case SB_LT:
  case SB_GE:
  case SB_GT:
  case SB_RSEL:
  case SB_SEMICOLON:
  case KW_END:
  case KW_ELSE:
  case KW_THEN:
    break;
  default:
    error(ERR_INVALID_ARGUMENTS, lookAhead->lineNo, lookAhead->colNo);
  }
}

void compileCondition(void)
{
  compileExpression();
  switch (lookAhead->tokenType)
  {
  case SB_EQ:
    eat(SB_EQ);
    break;
  case SB_NEQ:
    eat(SB_NEQ);
    break;
  case SB_LE:
    eat(SB_LE);
    break;
  case SB_LT:
    eat(SB_LT);
    break;
  case SB_GE:
    eat(SB_GE);
    break;
  case SB_GT:
    eat(SB_GT);
    break;
  default:
    error(ERR_INVALID_COMPARATOR, lookAhead->lineNo, lookAhead->colNo);
  }
  compileExpression();
}

void compileExpression(void)
{
  switch (lookAhead->tokenType)
  {
  case SB_PLUS:
    eat(SB_PLUS);
    compileExpression2();
    break;
  case SB_MINUS:
    eat(SB_MINUS);
    compileExpression2();
    break;
  default:
    compileExpression2();
  }
}

void compileExpression2(void)
{
  compileTerm();
  compileExpression3();
}

void compileExpression3(void)
{
  switch (lookAhead->tokenType)
  {
  case SB_PLUS:
    eat(SB_PLUS);
    compileTerm();
    compileExpression3();
    break;
  case SB_MINUS:
    eat(SB_MINUS);
    compileTerm();
    compileExpression3();
    break;
  case KW_TO:
  case KW_DO:
  case SB_RPAR:
  case SB_COMMA:
  case SB_EQ:
  case SB_NEQ:
  case SB_LE:
  case SB_LT:
  case SB_GE:
  case SB_GT:
  case SB_RSEL:
  case SB_SEMICOLON:
  case KW_END:
  case KW_ELSE:
  case KW_THEN:
    break;
  default:
    error(ERR_INVALID_EXPRESSION, lookAhead->lineNo, lookAhead->colNo);
  }
}

void compileTerm(void)
{
  compileFactor();
  compileTerm2();
}

void compileTerm2(void)
{
  switch (lookAhead->tokenType)
  {
  case SB_TIMES:
    eat(SB_TIMES);
    compileFactor();
    compileTerm2();
    break;
  case SB_SLASH:
    eat(SB_SLASH);
    compileFactor();
    compileTerm2();
    break;
  case SB_PLUS:
  case SB_MINUS:
  case KW_TO:
  case KW_DO:
  case SB_RPAR:
  case SB_COMMA:
  case SB_EQ:
  case SB_NEQ:
  case SB_LE:
  case SB_LT:
  case SB_GE:
  case SB_GT:
  case SB_RSEL:
  case SB_SEMICOLON:
  case KW_END:
  case KW_ELSE:
  case KW_THEN:
    break;
  default:
    error(ERR_INVALID_TERM, lookAhead->lineNo, lookAhead->colNo);
  }
}

void compileFactor(void)
{
  switch (lookAhead->tokenType)
  {
  case TK_NUMBER:
    eat(TK_NUMBER);
    break;
  case TK_CHAR:
    eat(TK_CHAR);
    break;
  case TK_IDENT:
    eat(TK_IDENT);
    switch (lookAhead->tokenType)
    {
    case SB_LPAR:
      compileArguments();
      break;
    case SB_LSEL:
      compileIndexes();
      break;
    default:
      break;
    }
    break;
  default:
    error(ERR_INVALID_FACTOR, lookAhead->lineNo, lookAhead->colNo);
  }
}

void compileIndexes(void)
{
  while (lookAhead->tokenType == SB_LSEL)
  {
    eat(SB_LSEL);
    compileExpression();
    eat(SB_RSEL);
  }
}

int compile(char *fileName)
{
  if (openInputStream(fileName) == IO_ERROR)
    return IO_ERROR;
  
  currentToken = NULL;
  lookAhead = getValidToken();

  initSymTab();

  compileProgram();

  // Đây là LỆNH IN RA BẢNG KÝ HIỆU (Thành quả của Day 2)
  printObject(symtab->program, 0);

  cleanSymTab();

  free(currentToken);
  free(lookAhead);
  closeInputStream();
  return IO_SUCCESS;
}



/*
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

void pad(int n)
{
  int i;
  for (i = 0; i < n; i++)
    printf(" ");
}

void printType(Type *type)
{
  switch (type->typeClass)
  {
  case TP_INT:
    printf("Int");
    break;
  case TP_CHAR:
    printf("Char");
    break;
  case TP_ARRAY:
    printf("Arr(%d,", type->arraySize);
    printType(type->elementType);
    printf(")");
    break;
  }
}

void printConstantValue(ConstantValue *value)
{
  switch (value->type)
  {
  case TP_INT:
    printf("%d", value->intValue);
    break;
  case TP_CHAR:
    printf("\'%c\'", value->charValue);
    break;
  default:
    break;
  }
}

void printObject(Object *obj, int indent)
{
  switch (obj->kind)
  {
  case OBJ_CONSTANT:
    pad(indent);
    printf("Const %s = ", obj->name);
    printConstantValue(obj->constAttrs->value);
    break;
  case OBJ_TYPE:
    pad(indent);
    printf("Type %s = ", obj->name);
    printType(obj->typeAttrs->actualType);
    break;
  case OBJ_VARIABLE:
    pad(indent);
    printf("Var %s : ", obj->name);
    printType(obj->varAttrs->type);
    break;
  case OBJ_PARAMETER:
    pad(indent);
    if (obj->paramAttrs->kind == PARAM_VALUE)
      printf("Param %s : ", obj->name);
    else
      printf("Param VAR %s : ", obj->name);
    printType(obj->paramAttrs->type);
    break;
  case OBJ_FUNCTION:
    pad(indent);
    printf("Function %s : ", obj->name);
    printType(obj->funcAttrs->returnType);
    printf("\n");
    printScope(obj->funcAttrs->scope, indent + 4);
    break;
  case OBJ_PROCEDURE:
    pad(indent);
    printf("Procedure %s\n", obj->name);
    printScope(obj->procAttrs->scope, indent + 4);
    break;
  case OBJ_PROGRAM:
    pad(indent);
    printf("Program %s\n", obj->name);
    printScope(obj->progAttrs->scope, indent + 4);
    break;
  }
}

void printObjectList(ObjectNode *objList, int indent)
{
  ObjectNode *node = objList;
  while (node != NULL)
  {
    printObject(node->object, indent);
    printf("\n");
    node = node->next;
  }
}

void printScope(Scope *scope, int indent)
{
  printObjectList(scope->objList, indent);
}

/*
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

/******************************************************************/

int main(int argc, char *argv[])
{
  compile(NULL);
  return 0;
}