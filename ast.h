// Definições das Abstract Syntax Trees
// O #ifndef verifica se o token foi definido (#define), se não, inclui o codigo entre ele e o #endif
// #ifndef é usado para tornar os ficheiros de cabeçalho idempotentes
#ifndef __ast_h__
#define __ast_h__

// Abstract Syntax Trees para expressoes
typedef struct _Expression {
  enum {
    expressionINTEGER,
    expressionSTRING, // "teste"
    expressionNAME, // ?? as
    expressionOPERATION, //a + bteste
    expressionINCREMENT_OPERATION, //a++
    expressionDECREMENT_OPERATION, //a--
    expressionBOOLEAN, // a < b
    expressionBOOLEAN_VALUE, // true
  } kind;

  union {
    int value;
    char* name;
    char* string;

    struct {
      int operator;
      struct _Expression* left;
      struct _Expression* right;
    } expression_operator;
    struct {
      struct _Expression* expression;
    } expression_ioperator;
  } attribute;
} Expression;
// Abstract Syntax Trees para comandos
typedef struct _Command {
  enum {
    commandLIST,
    commandDECLARE_INT,
    commandDECLARE_STRING,
    commandDECLARE_BOOL,
    commandATTRIBUTE,
    commandATTRIBUTE_2,
    commandINIT_INT,
    commandINIT_INT2,
    commandINIT_BOOL,
    commandINIT_BOOL2,
    commandINIT_STRING,
    commandINIT_STRING2,
    commandSCAN,
    commandPRINT,
    commandPRINT_VAR,
    commandIF,
    commandIF_ELSE,
    commandWHILE,
    commandFOR1,
    commandFOR2,
    commandBREAK,
    commandCONTINUE,
    commandRETURN_VAR,
    commandRETURN
  } kind;

  union {
    struct{
      struct _Command* next_command;
    } command_list;
    struct {
      char *var_name;
    } declare_var;
    struct {
      char *var_name;
      struct _Expression* expression;
    } attribute_var;
    struct {
      char *var_name0;
      char *var_name1;
    } attribute_vars;
    struct {
      char *var_name;
      struct _Expression* expression;
    } var_init;
    struct {
      char *var_name0;
      char *var_name1;
    } vars_init;
    struct {
      char *var_name;
    } scan_function;
    struct {
      struct _Expression* expression;
    } print_function;
    struct {
      char* var_name;
    } print_var;
    struct {
      struct _Expression* expression;
      struct _CommandList* command_list;
    } if_function;
    struct {
      struct _Expression* expression;
      struct _CommandList* command_list_if;
      struct _CommandList* command_list_else;
    } if_else_function;
    struct {
      struct _Expression* expression;
      struct _CommandList* command_list;
    } while_function;
    struct {
      char* var_name;
      struct _Expression* expression1;
      struct _Expression* expression2;
      struct _Expression* expression3;
      struct _CommandList* command_list;
    } for1_function;
    struct {
      char* var1_name;
      char* var2_name;
      struct _Expression* expression1;
      struct _Expression* expression2;
      struct _CommandList* command_list;
    } for2_function;
    struct {
      char* var_name;
    } return_var;
    struct {
      struct _Expression* expression;
    } return_function;
  } attribute;
} Command;
// Lista de Comandos
typedef struct _CommandList {
  struct _Command* head;
  struct _CommandList* tail;
} CommandList;

Expression* ast_Integer(int value);
Expression* ast_Name(char* name);
Expression* ast_String(char* string);
Expression* ast_Operation(int operator, Expression* left, Expression* right);
Expression* ast_IncrementOperation(Expression* expression);
Expression* ast_DecrementOperation(Expression* expression);
Expression* ast_BooleanOperation(int operator, Expression* left, Expression* right);
Expression* ast_Boolean(int value);
CommandList* ast_CommandList(Command* command, CommandList* list);
Command* ast_DeclareIntVar(char* var);
Command* ast_DeclareBoolVar(char* var);
Command* ast_DeclareStringVar(char* var);
Command* ast_VarAttribute(char* var, Expression* expression);
Command* ast_VarAttributes(char* var0, char* var1);
Command* ast_IntVarInit(char *var, Expression* expression);
Command* ast_IntVarsInit(char* var0, char* var1);
Command* ast_BoolVarInit(char* var, Expression* expression);
Command* ast_BoolVarsInit(char* var0, char* var1);
Command* ast_StringVarInit(char* var, Expression* expression);
Command* ast_StringVarsInit(char* var0, char* var1);
Command* ast_Scan(char* var);
Command* ast_Print(Expression* expression);
Command* ast_PrintVar(char* var);
Command* ast_If(Expression* expression, CommandList* command_list);
Command* ast_IfElse(Expression* expression, CommandList* command_list_if, CommandList* command_list_else);
Command* ast_While(Expression* expression, CommandList* command_list);
Command* ast_For1(char* var, Expression* expression1, Expression* expression2, Expression* expression3, CommandList* command_list_else);
Command* ast_For2(char* var1, char* var2, Expression* expression1, Expression* expression2, CommandList* command_list);
Command* ast_Break();
Command* ast_Continue();
Command* ast_Return1(char* var);
Command* ast_Return2(Expression* expression);

// Fechar a diretiva ifndef
#endif
