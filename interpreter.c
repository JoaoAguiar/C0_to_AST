#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include "ast.h"

int printCommand(Command* command, int nTab);
void printExpression(Expression* expression, int nTab);

int main(int argc, char* argv[]) {
  --argc;
  ++argv;

  if(argc != 0) {
    // yyin é uma variavel to tipo FILE* que aponta para o ficheiro input que vai ser scanned ou tokenized
    // yyin é definido automaticamente pelo FLEX (ferramenta usada para gerar uma analizador lexical)
    yyin = fopen(*argv, "r");

    if(yyin == NULL) {
      printf("'%s': could not open file\n", *argv);

      return 1;
    }
  }

  // yyparse() é 0 se o parsing correr bem de acordo com as regras da gramatica, 1 se houver uma falhar no parsing por causa de um input invalido ou 2 se falhar o parsing devido a exaustão da memoria
  if(yyparse() == 0) {
    CommandList* list1 = root;
    CommandList* list2 = root;

    while(list1 != NULL){
      int jumpCommand1 = printCommand(list1->head, 0);

      list1 = list1->tail;

      printf("\n");
    }
  }

  return 0;
}

int printCommand(Command* command, int nTab) {
  int i;

  for(i=0; i<nTab; i++) {
    printf(" ");
  }

  switch(command->kind) {
    case commandDECLARE_INT: {
      printf("INT: ");
      printf("%s\n", command->attribute.attribute_var.var_name);
    } break;
    case commandDECLARE_BOOL: {
      printf("BOOL: ");
      printf("%s\n", command->attribute.attribute_var.var_name);
    } break;
    case commandDECLARE_STRING: {
      printf("STRING: %s\n", command->attribute.attribute_var.var_name);
    } break;
    case commandATTRIBUTE: {
      printf("%s =", command->attribute.attribute_var.var_name);
      printExpression(command->attribute.attribute_var.expression, nTab+1);
      printf("\n");
    } break;
    case commandATTRIBUTE_2: {
      printf("%s = %s\n", command->attribute.attribute_vars.var_name0, command->attribute.attribute_vars.var_name1);
    } break;
    case commandINIT_INT: {
      printf("INT: ");
      printf("%s =", command->attribute.var_init.var_name);
      printExpression(command->attribute.var_init.expression, nTab+1);
      printf("\n");
    } break;
    case commandINIT_INT2: {
      printf("INT: ");
      printf("%s = %s\n", command->attribute.vars_init.var_name0, command->attribute.vars_init.var_name1);
    } break;
    case commandINIT_BOOL: {
      printf("BOOL: ");
      printf("%s =", command->attribute.var_init.var_name);
      printExpression(command->attribute.var_init.expression, nTab+1);
      printf("\n");
    } break;
    case commandINIT_BOOL2: {
      printf("BOOL: ");
      printf("%s = %s\n", command->attribute.vars_init.var_name0, command->attribute.vars_init.var_name1);
    } break;
    case commandINIT_STRING: {
      printf("STRING: ");
      printf("%s =", command->attribute.var_init.var_name);
      printExpression(command->attribute.var_init.expression, nTab+1);
      printf("\n");
    } break;
    case commandINIT_STRING2: {
      printf("STRING: %s = %s\n", command->attribute.vars_init.var_name0, command->attribute.vars_init.var_name1);
    } break;
    case commandSCAN: {
      printf("SCAN: ");
      printf("%s\n", command->attribute.scan_function.var_name);
    } break;
    case commandPRINT: {
      printf("PRINT:");
      printExpression(command->attribute.print_function.expression, nTab+1);
      printf("\n");
    } break;
    case commandPRINT_VAR: {
      printf("PRINT: %s\n", command->attribute.print_var.var_name);
    } break;
    case commandIF: {
      printf("IF");

      printExpression(command->attribute.if_function.expression, nTab+1);
      printf("{\n");

      CommandList* command_list = command->attribute.if_function.command_list;

      while(command_list != NULL) {
        int jumpCommand2 = printCommand(command_list->head, nTab+4);

        if(jumpCommand2 == 1) {
          command_list = command_list->tail;
        }

        command_list = command_list->tail;
      }

      printf("}\n");
    } break;
    case commandIF_ELSE: {
      printf("IF");

      printExpression(command->attribute.if_else_function.expression, nTab+1);
      printf("{\n");

      CommandList* command_list_if = command->attribute.if_else_function.command_list_if;

      while(command_list_if != NULL) {
        int jumpCommand2 = printCommand(command_list_if->head, nTab+4);

        if(jumpCommand2 == 1) {
          command_list_if = command_list_if->tail;
        }

        command_list_if = command_list_if->tail;
      }

      printf("}\n");
      printf("ELSE\n{\n");

      CommandList* command_list_else = command->attribute.if_else_function.command_list_else;

      while(command_list_else != NULL) {
        int jumpCommand2 = printCommand(command_list_else->head, nTab+4);

        if(jumpCommand2 == 1) {
          command_list_else = command_list_else->tail;
        }

        command_list_else = command_list_else->tail;
      }

      printf("}\n");
    } break;
    case commandWHILE: {
      printf("WHILE");

      printExpression(command->attribute.while_function.expression, nTab+1);
      printf("{");

      CommandList* command_list = command->attribute.while_function.command_list;

      while(command_list != NULL) {
        printf("\n");
        int jumpCommand2 = printCommand(command_list->head, nTab);

        if(jumpCommand2 == 1) {
          command_list = command_list->tail;
        }

        command_list = command_list->tail;
      }

      printf("}\n");
    } break;
    case commandFOR1: {
      printf("FOR ");
      printf("%s =", command->attribute.for1_function.var_name);
      printExpression(command->attribute.for1_function.expression1, nTab+1);
      printf("\n");
      printExpression(command->attribute.for1_function.expression2, nTab+1);
      printf("  %s =", command->attribute.for1_function.var_name);
      printExpression(command->attribute.for1_function.expression3, nTab+1);
      printf("\n{\n");

      CommandList* command_list = command->attribute.for1_function.command_list;

      while(command_list != NULL) {
        int jumpCommand2 = printCommand(command_list->head, nTab+4);

        if(jumpCommand2 == 1) {
          command_list = command_list->tail;
        }

        command_list = command_list->tail;
      }

      printf("}\n");
    } break;
    case commandFOR2: {
      printf("FOR ");
      printf("%s = %s\n", command->attribute.for2_function.var1_name, command->attribute.for2_function.var2_name);
      printExpression(command->attribute.for2_function.expression1, nTab+1);
      printf("  %s =", command->attribute.for2_function.var1_name);
      printExpression(command->attribute.for2_function.expression2, nTab+1);
      printf("\n{\n");

      CommandList* command_list = command->attribute.for2_function.command_list;

      while(command_list != NULL) {
        int jumpCommand2 = printCommand(command_list->head, nTab+4);

        if(jumpCommand2 == 1) {
          command_list = command_list->tail;
        }

        command_list = command_list->tail;
      }

      printf("}\n");
    } break;
    case commandBREAK: {
      printf("BREAK\n");

      return 1;
    } break;
    case commandCONTINUE: {
      printf("CONTINUE\n");
    } break;
    case commandRETURN_VAR: {
      printf("RETURN: %s\n", command->attribute.return_var.var_name);
    } break;
    case commandRETURN: {
      printf("RETURN:");
      printExpression(command->attribute.return_function.expression, nTab+1);
      printf("\n");
    } break;
    default: yyerror("Unknown Operator!!");
  }

  return 0;
}

void printExpression(Expression* expression, int nTab) {
  int i;

  for(i=0; i<nTab; i++) {
    printf(" ");
  }

  if(expression == 0) {
    yyerror("Null expression!!");
  }
  else if(expression->kind == expressionINTEGER) {
    printf("%d", expression->attribute.value);
  }
  else if(expression->kind == expressionSTRING) {
    printf("%s", expression->attribute.string);
  }
  else if(expression->kind == expressionNAME) {
    printf("%s", expression->attribute.name);
  }
  else if(expression->kind == expressionOPERATION) {
    switch(expression->attribute.expression_operator.operator) {
      case PLUS: {
        printf("+");
      } break;
      case MINUS: {
        printf("-");
      } break;
      case MULT: {
        printf("*");
      } break;
      case DIV: {
        printf("/");
      } break;
      case MOD: {
        printf("%%");
      } break;
      default: yyerror("Unknown Operator!!");
    }

    printf("\n");
    printExpression(expression->attribute.expression_operator.left, nTab+1);
    printExpression(expression->attribute.expression_operator.right, nTab+1);
  }
  else if(expression->kind == expressionINCREMENT_OPERATION) {
    printExpression(expression->attribute.expression_ioperator.expression, nTab+1);

    printf("++\n");
  }
  else if(expression->kind == expressionDECREMENT_OPERATION) {
    printExpression(expression->attribute.expression_ioperator.expression, nTab+1);

    printf("--\n");
  }
  else if(expression->kind == expressionBOOLEAN) {
    switch(expression->attribute.expression_operator.operator) {
      case EQUAL: {
        printf("==");
      } break;
      case DIFF: {
        printf("!=");
      } break;
      case LT: {
        printf("<");
      } break;
      case GT: {
        printf(">");
      } break;
      case LTEQ: {
        printf("<=");
      } break;
      case GTEQ: {
        printf(">=");
      } break;
      case AND: {
        printf("&&");
      } break;
      case OR: {
        printf("||");
      } break;
      default: yyerror("Unknown Operator!!");
    }

    printf("\n");
    printExpression(expression->attribute.expression_operator.left, nTab+1);
    printExpression(expression->attribute.expression_operator.right, nTab+1);
    printf("\n");
  }
  else if(expression->kind == expressionBOOLEAN_VALUE) {
    switch(expression->attribute.value) {
      case 0: {
        printf("FALSE\n");
      } break;
      case 1: {
        printf("TRUE\n");
      } break;
      default: yyerror("Unknown Operator!!");
    }
  }
}
