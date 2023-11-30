%{
 
 #include "Cmin.h"



extern int linha;
extern int coluna;
extern int yyleng;



%}

%token INT MAIN ABRE_PARENTESES FECHA_PARENTESES ABRE_CHAVES FECHA_CHAVES RETURN  PONTO_E_VIRGULA MAIS MENOS DIVIDIR MULTIPLICA IF ELSE MAIORQUE MENORQUE INGUAL VIRGULA NAO AND OR WHILE

%union 
{
        int number;
        char *string;
}

%token <number> NUM
%token <string> VARIAVEL 

%right  MULTIPLICA DIVIDIR  MENOS MAIS 
%left AND OR

%%
programa: INT MAIN ABRE_PARENTESES FECHA_PARENTESES ABRE_CHAVES  {inicia_codigo(); } corpo FECHA_CHAVES {finaliza_cod(); }
 ;

corpo:  corpoLinha corpo
    | 
 ;  

corpoLinha: defVar
    | ifStatement
    | final
;
final: RETURN  expr  PONTO_E_VIRGULA {monta_retorno(); }
    | RETURN cond  PONTO_E_VIRGULA {printf("KRL4 "); monta_retorno(); }
 ;
expr: ABRE_PARENTESES expr FECHA_PARENTESES
    | expr MULTIPLICA expr {monta_mult();}
    | expr DIVIDIR expr {monta_div();}
    | expr MAIS expr  {monta_add();}
    | expr MENOS expr {monta_sub();}
    | NUM {empilha_num($1);}
    | VARIAVEL {empilha_var($1);}
 ;

multVar:  VARIAVEL {monta_var($1);} PONTO_E_VIRGULA
    | VARIAVEL {monta_var($1);} VIRGULA multVar
;
defVar:  INT  multVar 
    | VARIAVEL INGUAL expr {atribui_var($1);} PONTO_E_VIRGULA
;

ifStatement:  IF ABRE_PARENTESES cond FECHA_PARENTESES ABRE_CHAVES {monta_if();} corpo  FECHA_CHAVES  ElseStatment  { monta_label(); } 
;



ElseStatment: ELSE ABRE_CHAVES {monta_else();} corpo FECHA_CHAVES 
    |  
;

cond: ABRE_PARENTESES cond FECHA_PARENTESES
    | expr MAIORQUE expr {monta_maior();} 
    | expr MAIORQUE INGUAL expr {monta_maior_igual();} 
    | expr MENORQUE expr {monta_menor();}
    | expr MENORQUE INGUAL expr {monta_menor_igual();}
    | expr INGUAL INGUAL expr {monta_igual();}
    | expr NAO INGUAL expr {monta_diferente();}
    | cond AND cond {monta_AND();}
    | cond OR cond {monta_OR();}
;

%%

int main(){
  yyparse();
  printf("programa valido \n");
}

