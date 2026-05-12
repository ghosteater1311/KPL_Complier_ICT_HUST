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

#ifndef __SYMTAB_H__
#define __SYMTAB_H__

#define MAX_IDENT_LEN 15

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
void declareObject(Object *obj);

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
/* * @copyright (c) 2008, Hedspi, Hanoi University of Technology
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

Type* duplicateType(Type* type) {
    // TODO
    Type* resultType = (Type*) malloc(sizeof(Type));
    resultType->typeClass = type->typeClass;
    if(type->typeClass == TP_ARRAY) 
    {
        resultType->arraySize = type->arraySize;
        resultType->elementType = duplicateType(type->elementType);
    }
    return resultType;
}

int compareType(Type* type1, Type* type2) {
  // TODO
    if(type1->typeClass == type2->typeClass) 
    {
        if(type1->typeClass == TP_ARRAY) 
        {
            if(type1->arraySize == type2->arraySize)
            return compareType(type1->elementType, type2->elementType);
            else return 0;
        } 
        else return 1;
    } 
    else return 0;
}

void freeType(Type* type) {
  // TODO
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

ConstantValue* makeIntConstant(int i) {
  // TODO
    ConstantValue* value = (ConstantValue*) malloc(sizeof(ConstantValue));
    value->type = TP_INT;
    value->intValue = i;
    return value;
}

ConstantValue* makeCharConstant(char ch) {
  // TODO
    ConstantValue* value = (ConstantValue*) malloc(sizeof(ConstantValue));
    value->type = TP_CHAR;
    value->charValue = ch;
    return value;
}

ConstantValue* duplicateConstantValue(ConstantValue* v) {
  // TODO
    ConstantValue* value = (ConstantValue*) malloc(sizeof(ConstantValue));
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

Object* createConstantObject(char *name) {
  // TODO
    Object* obj = (Object*) malloc(sizeof(Object));
    strcpy(obj->name, name);
    obj->kind = OBJ_CONSTANT;
    obj->constAttrs = (ConstantAttributes*) malloc(sizeof(ConstantAttributes));
    return obj;
}

Object* createTypeObject(char *name) {
  // TODO
    Object* obj = (Object*) malloc(sizeof(Object));
    strcpy(obj->name, name);
    obj->kind = OBJ_TYPE;
    obj->typeAttrs = (TypeAttributes*) malloc(sizeof(TypeAttributes));
    return obj;
}

Object* createVariableObject(char *name) {
  // TODO
    Object* obj = (Object*) malloc(sizeof(Object));
    strcpy(obj->name, name);
    obj->kind = OBJ_VARIABLE;
    obj->varAttrs = (VariableAttributes*) malloc(sizeof(VariableAttributes));
    obj->varAttrs->scope = symtab->currentScope;
    return obj;
}

Object* createFunctionObject(char *name) {
  // TODO
    Object* obj = (Object*) malloc(sizeof(Object));
    strcpy(obj->name, name);
    obj->kind = OBJ_FUNCTION;
    obj->funcAttrs = (FunctionAttributes*) malloc(sizeof(FunctionAttributes));
    obj->funcAttrs->paramList = NULL;
    obj->funcAttrs->scope = createScope(obj, symtab->currentScope);
    return obj;
}

Object* createProcedureObject(char *name) {
  // TODO
    Object* obj = (Object*) malloc(sizeof(Object));
    strcpy(obj->name, name);
    obj->kind = OBJ_PROCEDURE;
    obj->procAttrs = (ProcedureAttributes*) malloc(sizeof(ProcedureAttributes));
    obj->procAttrs->paramList = NULL;
    obj->procAttrs->scope = createScope(obj, symtab->currentScope);
    return obj;
}

Object* createParameterObject(char *name, enum ParamKind kind, Object* owner) {
  // TODO
    Object* obj = (Object*) malloc(sizeof(Object));
    strcpy(obj->name, name);
    obj->kind = OBJ_PARAMETER;
    obj->paramAttrs = (ParameterAttributes*) malloc(sizeof(ParameterAttributes));
    obj->paramAttrs->kind = kind;
    obj->paramAttrs->function = owner;
    return obj;
}

void freeObject(Object* obj) {
  // TODO
    switch (obj->kind) {
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

void freeScope(Scope* scope) {
  // TODO
    freeObjectList(scope->objList);
    free(scope);
}

void freeObjectList(ObjectNode *objList) {
  // TODO
    ObjectNode* list = objList;

    while(list != NULL) 
    {
        ObjectNode* node = list;
        list = list->next;
        freeObject(node->object);
        free(node);
    }
}

void freeReferenceList(ObjectNode *objList) {
  // TODO
    ObjectNode* list = objList;

    while(list != NULL) 
    {
        ObjectNode* node = list;
        list = list->next;
        free(node);
    }
}

Object* findObject(ObjectNode *objList, char *name) {
  // TODO
    ObjectNode *node = objList;

    while (node != NULL)
    {
        if (strcmp(node->object->name, name) == 0)
            return node->object;
        node = node->next;
    }

    return NULL;
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

extern SymTab *symtab;
/******************************************************************/

int main()
{
  Object *obj;

  initSymTab();

  obj = createProgramObject("PRG");
  enterBlock(obj->progAttrs->scope);

  obj = createConstantObject("c1");
  obj->constAttrs->value = makeIntConstant(10);
  declareObject(obj);

  obj = createConstantObject("c2");
  obj->constAttrs->value = makeCharConstant('a');
  declareObject(obj);

  obj = createTypeObject("t1");
  obj->typeAttrs->actualType = makeArrayType(10, makeIntType());
  declareObject(obj);

  obj = createVariableObject("v1");
  obj->varAttrs->type = makeIntType();
  declareObject(obj);

  obj = createVariableObject("v2");
  obj->varAttrs->type = makeArrayType(10, makeArrayType(10, makeIntType()));
  declareObject(obj);

  obj = createFunctionObject("f");
  obj->funcAttrs->returnType = makeIntType();
  declareObject(obj);

  enterBlock(obj->funcAttrs->scope);

  obj = createParameterObject("p1", PARAM_VALUE, symtab->currentScope->owner);
  obj->paramAttrs->type = makeIntType();
  declareObject(obj);

  obj = createParameterObject("p2", PARAM_REFERENCE, symtab->currentScope->owner);
  obj->paramAttrs->type = makeCharType();
  declareObject(obj);

  exitBlock();

  obj = createProcedureObject("p");
  declareObject(obj);

  enterBlock(obj->procAttrs->scope);

  obj = createParameterObject("v1", PARAM_VALUE, symtab->currentScope->owner);
  obj->paramAttrs->type = makeIntType();
  declareObject(obj);

  obj = createConstantObject("c1");
  obj->constAttrs->value = makeCharConstant('a');
  declareObject(obj);

  obj = createConstantObject("c3");
  obj->constAttrs->value = makeIntConstant(10);
  declareObject(obj);

  obj = createTypeObject("t1");
  obj->typeAttrs->actualType = makeIntType();
  declareObject(obj);

  obj = createTypeObject("t2");
  obj->typeAttrs->actualType = makeArrayType(10, makeIntType());
  declareObject(obj);

  obj = createVariableObject("v2");
  obj->varAttrs->type = makeArrayType(10, makeIntType());
  declareObject(obj);

  obj = createVariableObject("v3");
  obj->varAttrs->type = makeCharType();
  declareObject(obj);

  exitBlock();

  exitBlock();
  printObject(symtab->program, 0);
  cleanSymTab();

  return 0;
}