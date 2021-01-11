%{
// Headers
#include <stdlib.h>
#include "parser.h"

// Variáveis mantidas pelo analisador lexical
int yyline = 1;
%}

%option noyywrap

/***** Scan dos tokens *****/
%%
[ \t]+ {  }

#.*\n { yyline++; }

\n { yyline++; }

"{" { return BRLEFT; }
"}" { return BRRIGHT; }
"(" { return PLEFT; }
")" { return PRIGHT; }
";" { return SC; }
"," { return CM; }
"=" { return EQUALVAR; }

"int" { return INTEIRO; }
"bool" { return BOOL; }
"string" { return STRING; }
"true" { return TRUE; }
"false" { return FALSE; }

"main" { return MAIN; }
"print_int" { return PRINT; }
"scan_int" { return SCAN; }
"print_str" { return PRINTS; }
"if" { return IF; }
"else" { return ELSE; }
"while" { return WHILE; }
"for" { return FOR; }
"break" { return BREAK; }
"continue" { return CONTINUE; }
"return" { return RETURN; }

[a-zA-Z][0-9a-zA-Z\_\!]* {
   yylval.nameValue = strdup(yytext);
   return NAME;
}

\".*\" {
   yylval.stringValue = strdup(yytext);
   return STR;
}

\-?[0-9]+ {
   yylval.intValue = atoi(yytext);
   return INT;
}

"++" { return INCR; }
"--" { return DECR; }

"+" { return PLUS; }
"-" { return MINUS; }
"*" { return MULT; }
"/" { return DIV; }
"%" { return MOD; }

"==" { return EQUAL; }
"!=" { return DIFF; }
"<" { return LT; }
">" { return GT; }
"<=" { return LTEQ; }
">=" { return GTEQ; }
"&&" { return AND; }
"||" { return OR; }

.  { yyerror("unexpected character"); }
%%
