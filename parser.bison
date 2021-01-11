/***** Tokens *****/
%token
  BRLEFT     // {
  BRRIGHT    // }
  PLEFT      // (
  PRIGHT     // )
  INTEIRO    // int
  STRING     // string
  MAIN       // main
  IF         // if
  ELSE       // else
  WHILE      // while
  SC         // ;
  CM         // ,
  STR        // strings
  PRINT      // print_int
  PRINTS     // print_str
  SCAN       // scan_int
  EQUALVAR   // =
  INT        // inteiros
  INCR       // ++
  DECR       // --
  PLUS       // +
  MINUS      // -
  MULT       // *
  DIV        // /
  MOD        // %
  EQUAL      // ==
  DIFF       // !=
  LT         // <
  GT         // >
  LTEQ       // <=
  GTEQ       // >=
  AND        // &&
  OR         // ||
  BOOL       // bool
  TRUE       // true
  FALSE      // false
  NAME       // nome de variavel
  RETURN     // return
  FOR        // for
  BREAK      // break
  CONTINUE   // continue

/***** Operadores: precedencia e associatividade *****/
// 1 + 2 + 3 usando o %left: (1 + 2) + 3
// 1 + 2 + 3 usando o %right: 1 + (2 + 3)
// O primeiro %left ou %right declaro os operadores com menor precedencia, o seguinte declara o com menor relativamente aos restantes e sempre assim
%left
  INCR
  DECR
%left
  DIV
  MULT
  MOD
%left
  PLUS
  MINUS
%left
  LT
  GT
  LTEQ
  GTEQ
%left
  EQUAL
  DIFF
%left
  AND
  OR

/***** Simbolo da gramatica do nivel Root *****/
// O Bison assume como default que o simbolo inicial da gramatica é o primeiro não-terminal especificado na secção de especidifação gramatical
// Podemos alterar o simbolo inicial com o %start
%start program;

/***** Tipos/Valores em associação com os simbolos da gramatica *****/
%union {
  int intValue;
  char* stringValue;
  char* nameValue;
  Expression* expressionValue;
  Command* command;
  CommandList* commandList;
}

/***** Para especificar tipos de valores *****/
%type <intValue> INT
%type <stringValue> STR
%type <nameValue> NAME
%type <expressionValue> expression
%type <command> command
%type <commandList> command_list

// Uso do %code requires para fazer as declarações irem para o parser.c e para o parser.h
%code requires {
  #include <stdio.h>
  #include <stdlib.h>
  #include "ast.h"

  extern int yylex();
  extern int yyline;
  extern char* yytext;
  extern FILE* yyin;
  extern void yyerror(const char* err);
  CommandList* root;
}

%%
// $1, $2, $3, ... refere-se ao 1º simbolo, 2º simbolo, 3º simbolo, ...
// O resultado é guardado no $$.
program:
  INTEIRO MAIN PLEFT PRIGHT BRLEFT command_list BRRIGHT {
    root = $6;
  }
  ;

command_list:
  command {
    $$ = ast_CommandList($1, NULL);
  }
  |
  command command_list {
    $$ = ast_CommandList($1, $2);
  }
  ;

command:
  BREAK SC {
    $$ = ast_Break();
  }
  |
  CONTINUE SC {
    $$ = ast_Continue();
  }
  |
  INTEIRO NAME SC {
    $$ = ast_DeclareIntVar($2);
  }
  |
  BOOL NAME SC {
    $$ = ast_DeclareBoolVar($2);
  }
  |
  STRING NAME SC {
    $$ = ast_DeclareStringVar($2);
  }
  |
  BOOL NAME EQUALVAR expression SC {
    $$ = ast_BoolVarInit($2, $4);
  }
  |
  BOOL NAME EQUALVAR NAME SC {
    $$ = ast_BoolVarsInit($2, $4);
  }
  |
  STRING NAME EQUALVAR expression SC {
    $$ = ast_StringVarInit($2, $4);
  }
  |
  STRING NAME EQUALVAR NAME SC {
    $$ = ast_StringVarsInit($2, $4);
  }
  |
  NAME EQUALVAR expression SC {
    $$ = ast_VarAttribute($1, $3);
  }
  |
  NAME EQUALVAR NAME SC {
    $$ = ast_VarAttributes($1, $3);
  }
  |
  INTEIRO NAME EQUALVAR expression SC {
    $$ = ast_IntVarInit($2, $4);
  }
  |
  INTEIRO NAME EQUALVAR NAME SC {
    $$ = ast_IntVarsInit($2, $4);
  }
  |
  INTEIRO NAME EQUALVAR SCAN PLEFT PRIGHT SC {
    $$ = ast_Scan($2);
  }
  |
  BOOL NAME EQUALVAR SCAN PLEFT PRIGHT SC {
    $$ = ast_Scan($2);
  }
  |
  NAME EQUALVAR SCAN PLEFT PRIGHT SC {
    $$ = ast_Scan($1);
  }
  |
  PRINT PLEFT expression PRIGHT SC {
    $$ = ast_Print($3);
  }
  |
  PRINT PLEFT NAME PRIGHT SC {
    $$ = ast_PrintVar($3);
  }
  |
  PRINTS PLEFT expression PRIGHT SC {
    $$ = ast_Print($3);
  }
  |
  PRINTS PLEFT NAME PRIGHT SC {
    $$ = ast_PrintVar($3);
  }
  |
  IF PLEFT expression PRIGHT BRLEFT command_list BRRIGHT {
    $$ = ast_If($3, $6);
  }
  |
  IF PLEFT expression PRIGHT BRLEFT command_list BRRIGHT ELSE BRLEFT command_list BRRIGHT {
    $$ = ast_IfElse($3, $6, $10);
  }
  |
  WHILE PLEFT expression PRIGHT BRLEFT command_list BRRIGHT {
    $$ = ast_While($3, $6);
  }
  |
  FOR PLEFT INTEIRO NAME EQUALVAR expression SC expression SC NAME EQUALVAR expression PRIGHT BRLEFT command_list BRRIGHT {
    $$ = ast_For1($4, $6, $8, $12, $15);
  }
  |
  FOR PLEFT INTEIRO NAME EQUALVAR NAME SC expression SC NAME EQUALVAR expression PRIGHT BRLEFT command_list BRRIGHT {
    $$ = ast_For2($4, $6, $8, $12, $15);
  }
  |
  FOR PLEFT NAME EQUALVAR expression SC expression SC NAME EQUALVAR expression PRIGHT BRLEFT command_list BRRIGHT {
    $$ = ast_For1($3, $5, $7, $11, $14);
  }
  |
  FOR PLEFT NAME EQUALVAR NAME SC expression SC NAME EQUALVAR expression PRIGHT BRLEFT command_list BRRIGHT {
    $$ = ast_For2($3, $5, $7, $11, $14);
  }
  |
  RETURN NAME  {
    $$ = ast_Return1($2);
  }
  |
  RETURN expression SC {
    $$ = ast_Return2($2);
  }
  ;

expression:
  INT {
    $$ = ast_Integer($1);
  }
  |
  STR {
    $$ = ast_String($1);
  }
  |
  NAME {
    $$ = ast_Name($1);
  }
  |
  TRUE {
    $$ = ast_Boolean(1);
  }
  |
  FALSE {
    $$ = ast_Boolean(0);
  }
  |
  expression INCR {
    $$ = ast_IncrementOperation($1);
  }
  |
  expression DECR {
    $$ = ast_DecrementOperation($1);
  }
  |
  expression PLUS expression {
    $$ = ast_Operation(PLUS, $1, $3);
  }
  |
  expression MINUS expression {
    $$ = ast_Operation(MINUS, $1, $3);
  }
  |
  expression MULT expression {
    $$ = ast_Operation(MULT, $1, $3);
  }
  |
  expression DIV expression {
    $$ = ast_Operation(DIV, $1, $3);
  }
  |
  expression MOD expression {
    $$ = ast_Operation(MOD, $1, $3);
  }
  |
  expression EQUAL expression {
    $$ = ast_BooleanOperation(EQUAL, $1, $3);
  }
  |
  expression DIFF expression {
    $$ = ast_BooleanOperation(DIFF, $1, $3);
  }
  |
  expression LT expression {
    $$ = ast_BooleanOperation(LT, $1, $3);
  }
  |
  expression GT expression {
    $$ = ast_BooleanOperation(GT, $1, $3);
  }
  |
  expression LTEQ expression {
    $$ = ast_BooleanOperation(LTEQ, $1, $3);
  }
  |
  expression GTEQ expression {
    $$ = ast_BooleanOperation(GTEQ, $1, $3);
  }
  |
  expression AND expression {
    $$ = ast_BooleanOperation(AND, $1, $3);
  }
  |
  expression OR expression {
    $$ = ast_BooleanOperation(OR, $1, $3);
  }
  |
  PLEFT expression EQUAL expression PRIGHT {
    $$ = ast_BooleanOperation(EQUAL, $2, $4);
  }
  |
  PLEFT expression DIFF expression PRIGHT {
    $$ = ast_BooleanOperation(DIFF, $2, $4);
  }
  |
  PLEFT expression LT expression PRIGHT {
    $$ = ast_BooleanOperation(LT, $2, $4);
  }
  |
  PLEFT expression GT expression PRIGHT {
    $$ = ast_BooleanOperation(GT, $2, $4);
  }
  |
  PLEFT expression LTEQ expression PRIGHT {
    $$ = ast_BooleanOperation(LTEQ, $2, $4);
  }
  |
  PLEFT expression GTEQ expression PRIGHT {
    $$ = ast_BooleanOperation(GTEQ, $2, $4);
  }
  |
  PLEFT INT PRIGHT {
    $$ = ast_Integer($2);
  }
  |
  PLEFT expression PLUS expression PRIGHT {
    $$ = ast_Operation(PLUS, $2, $4);
  }
  |
  PLEFT expression MINUS expression PRIGHT {
    $$ = ast_Operation(MINUS, $2, $4);
  }
  |
  PLEFT expression MULT expression PRIGHT {
    $$ = ast_Operation(MULT, $2, $4);
  }
  |
  PLEFT expression DIV expression PRIGHT {
    $$ = ast_Operation(DIV, $2, $4);
  }
  |
  PLEFT expression MOD expression PRIGHT {
    $$ = ast_Operation(MOD, $2, $4);
  }
  ;
%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext);
}
