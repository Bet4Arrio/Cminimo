%{
 
 #include "Cmin.h"



extern int linha;
extern int coluna;
extern int yyleng;



%}

%token INT MAIN ABRE_PARENTESES FECHA_PARENTESES ABRE_CHAVES FECHA_CHAVES RETURN  PONTO_E_VIRGULA MAIS MENOS DIVIDIR MULTIPLICA IF ELSE MAIORQUE MENORQUE INGUAL

%union 
{
        int number;
        char *string;
}

%token <number> NUM
%token <string> VARIAVEL 

%left  MENOS MAIS DIVIDIR MULTIPLICA

%%
programa: INT MAIN ABRE_PARENTESES FECHA_PARENTESES ABRE_CHAVES  {inicia_codigo(); } corpo FECHA_CHAVES {finaliza_cod(); }
 ;
corpo:  final corpo
    | defVar corpo
    | ifStatement  corpo
    |
 ;  
final: RETURN expr {monta_retorno(); } PONTO_E_VIRGULA
 ;
expr: expr MAIS expr  {monta_add();}
    | expr MENOS expr {monta_sub();}
    | expr DIVIDIR expr {monta_div();}
    | expr MULTIPLICA expr {monta_mult();}
    | NUM {empilha_num($1);}
    | VARIAVEL {empilha_var($1);}
 ;

defVar:  INT VARIAVEL  {monta_var($2);} PONTO_E_VIRGULA
    | VARIAVEL INGUAL expr {atribui_var($1);} PONTO_E_VIRGULA
;

ifStatement:  IF ABRE_PARENTESES cond FECHA_PARENTESES ABRE_CHAVES corpo FECHA_CHAVES ElseStatment
;
ElseStatment: ELSE ABRE_CHAVES corpo FECHA_CHAVES 
    |
;

cond: expr MAIORQUE expr | expr MENORQUE expr | expr INGUAL INGUAL expr
;

%%

int main(){
  yyparse();
  printf("programa valido \n");
}

