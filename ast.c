#include <stdlib.h>
#include "ast.h"

// Expressoes
Expression* ast_Integer(int value) {
  Expression* node = (Expression*)malloc(sizeof(Expression));

  node->kind = expressionINTEGER;
  node->attribute.value = value;

  return node;
}
Expression* ast_String(char* name) {
  Expression* node = (Expression*)malloc(sizeof(Expression));

  node->kind = expressionSTRING;
  node->attribute.name = name;

  return node;
}
Expression* ast_Name(char* name) {
  Expression* node = (Expression*)malloc(sizeof(Expression));

  node->kind = expressionNAME;
  node->attribute.name = name;

  return node;
}
Expression* ast_Operation(int operator, Expression* left, Expression* right) {
  Expression* node = (Expression*)malloc(sizeof(Expression));

  node->kind = expressionOPERATION;
  node->attribute.expression_operator.operator = operator;
  node->attribute.expression_operator.left = left;
  node->attribute.expression_operator.right = right;

  return node;
}
Expression* ast_IncrementOperation(Expression* expression) {
  Expression* node = (Expression*)malloc(sizeof(Expression));

  node->kind = expressionINCREMENT_OPERATION;
  node->attribute.expression_ioperator.expression = expression;

  return node;
}
Expression* ast_DecrementOperation(Expression* expression) {
  Expression* node = (Expression*)malloc(sizeof(Expression));

  node->kind = expressionDECREMENT_OPERATION;
  node->attribute.expression_ioperator.expression = expression;

  return node;
}
Expression* ast_BooleanOperation(int operator, Expression* left, Expression* right) {
  Expression* node = (Expression*)malloc(sizeof(Expression));

  node->kind = expressionBOOLEAN;
  node->attribute.expression_operator.operator = operator;
  node->attribute.expression_operator.left = left;
  node->attribute.expression_operator.right = right;

  return node;
}
Expression* ast_Boolean(int value) {
  Expression* node = (Expression*)malloc(sizeof(Expression));

  node->kind = expressionBOOLEAN_VALUE;
  node->attribute.value = value;

  return node;
}

CommandList* ast_CommandList(Command* command, CommandList* list) {
  CommandList* node = (CommandList*)malloc(sizeof(CommandList));

  node->head = command;
  node->tail = list;

  return node;
}

// Commandos
Command* ast_DeclareIntVar(char* var) {
  Command* node = (Command*)malloc(sizeof(Command));

  node->kind = commandDECLARE_INT;
  node->attribute.declare_var.var_name = var;

  return node;
}
Command* ast_DeclareBoolVar(char* var) {
  Command* node = (Command*)malloc(sizeof(Command));

  node->kind = commandDECLARE_BOOL;
  node->attribute.declare_var.var_name = var;

  return node;
}
Command* ast_DeclareStringVar(char* var) {
  Command* node = (Command*)malloc(sizeof(Command));

  node->kind = commandDECLARE_STRING;
  node->attribute.declare_var.var_name = var;

  return node;
}
Command* ast_VarAttribute(char* var, Expression* expression) {
  Command* node = (Command*)malloc(sizeof(Command));

  node->kind = commandATTRIBUTE;
  node->attribute.attribute_var.var_name = var;
  node->attribute.attribute_var.expression = expression;

  return node;
}
Command* ast_VarAttributes(char* var0, char* var1) {
  Command* node = (Command*)malloc(sizeof(Command));

  node->kind = commandATTRIBUTE_2;
  node->attribute.attribute_vars.var_name0 = var0;
  node->attribute.attribute_vars.var_name1 = var1;

  return node;
}
Command* ast_IntVarInit(char* var, Expression* expression) {
  Command* node = (Command*)malloc(sizeof(Command));

  node->kind = commandINIT_INT;
  node->attribute.var_init.var_name = var;
  node->attribute.var_init.expression = expression;

  return node;
}
Command* ast_IntVarsInit(char* var0, char* var1) {
  Command* node = (Command*)malloc(sizeof(Command));

  node->kind = commandINIT_INT2;
  node->attribute.vars_init.var_name0 = var0;
  node->attribute.vars_init.var_name1 = var1;

  return node;
}
Command* ast_BoolVarInit(char* var, Expression* expression) {
  Command* node = (Command*)malloc(sizeof(Command));

  node->kind = commandINIT_BOOL;
  node->attribute.var_init.var_name = var;
  node->attribute.var_init.expression = expression;

  return node;
}
Command* ast_BoolVarsInit(char* var0, char* var1) {
  Command* node = (Command*)malloc(sizeof(Command));

  node->kind = commandINIT_BOOL2;
  node->attribute.vars_init.var_name0 = var0;
  node->attribute.vars_init.var_name1 = var1;

  return node;
}
Command* ast_StringVarInit(char* var, Expression* expression) {
  Command* node = (Command*)malloc(sizeof(Command));

  node->kind = commandINIT_STRING;
  node->attribute.var_init.var_name = var;
  node->attribute.var_init.expression = expression;

  return node;
}
Command* ast_StringVarsInit(char* var0, char* var1) {
  Command* node = (Command*)malloc(sizeof(Command));

  node->kind = commandINIT_STRING2;
  node->attribute.vars_init.var_name0 = var0;
  node->attribute.vars_init.var_name1 = var1;

  return node;
}
Command* ast_Scan(char* var) {
  Command* node = (Command*)malloc(sizeof(Command));

  node->kind = commandSCAN;
  node->attribute.scan_function.var_name = var;

  return node;
}
Command* ast_Print(Expression* expression) {
  Command* node = (Command*)malloc(sizeof(Command));

  node->kind = commandPRINT;
  node->attribute.print_function.expression = expression;

  return node;
}
Command* ast_PrintVar(char* var) {
  Command* node = (Command*)malloc(sizeof(Command));

  node->kind = commandPRINT_VAR;
  node->attribute.print_var.var_name = var;

  return node;
}
Command* ast_If(Expression* expression, CommandList* command_list) {
  Command* node = (Command*)malloc(sizeof(Command));

  node->kind = commandIF;
  node->attribute.if_function.expression = expression;
  node->attribute.if_function.command_list = command_list;

  return node;
}
Command* ast_IfElse(Expression* expression, CommandList* command_list_if, CommandList* command_list_else) {
  Command* node = (Command*)malloc(sizeof(Command));

  node->kind = commandIF_ELSE;
  node->attribute.if_else_function.expression = expression;
  node->attribute.if_else_function.command_list_if = command_list_if;
  node->attribute.if_else_function.command_list_else = command_list_else;

  return node;
}
Command* ast_While(Expression* expression, CommandList* command_list) {
  Command* node = (Command*)malloc(sizeof(Command));

  node->kind = commandWHILE;
  node->attribute.while_function.expression = expression;
  node->attribute.while_function.command_list = command_list;

  return node;
}
Command* ast_For1(char* var, Expression* expression1, Expression* expression2, Expression* expression3, CommandList* command_list) {
  Command* node = (Command*)malloc(sizeof(Command));

  node->kind = commandFOR1;
  node->attribute.for1_function.var_name = var;
  node->attribute.for1_function.expression1 = expression1;
  node->attribute.for1_function.expression2 = expression2;
  node->attribute.for1_function.expression3 = expression3;
  node->attribute.for1_function.command_list = command_list;

  return node;
}
Command* ast_For2(char* var1, char* var2, Expression* expression1, Expression* expression2, CommandList* command_list) {
  Command* node = (Command*)malloc(sizeof(Command));

  node->kind = commandFOR2;
  node->attribute.for2_function.var1_name = var1;
  node->attribute.for2_function.var2_name = var2;
  node->attribute.for2_function.expression1 = expression1;
  node->attribute.for2_function.expression2 = expression2;
  node->attribute.for2_function.command_list = command_list;

  return node;
}
Command* ast_Break() {
  Command* node = (Command*)malloc(sizeof(Command));

  node->kind = commandBREAK;

  return node;
}
Command* ast_Continue() {
  Command* node = (Command*)malloc(sizeof(Command));

  node->kind = commandCONTINUE;

  return node;
}
Command* ast_Return1(char* var) {
  Command* node = (Command*)malloc(sizeof(Command));

  node->kind = commandRETURN_VAR;
  node->attribute.return_var.var_name = var;

  return node;
}
Command* ast_Return2(Expression* expression) {
  Command* node = (Command*)malloc(sizeof(Command));

  node->kind = commandRETURN;
  node->attribute.return_function.expression = expression;

  return node;
}
