%{
 #include<stdio.h>
 #include<stdlib.h>
 #include "hashtable.h"
 #include "Cmin.h"

FILE *f;
ht* tabVars;

extern int linha;
extern int coluna;
extern int yyleng;

int yylex(void);
int yyerror(char * msg){
printf("(%d, %d) Error: %s", linha, coluna-yyleng, msg);
exit(0);
}

void inicia_codigo(){
  tabVars = ht_create();

  f = fopen("out.s","w+");
	fprintf(f, ".text\n");
	fprintf(f, "    .global _start\n\n");
    	fprintf(f, "_start:\n\n");
}

void corpo(int num){

}

void teste(){

}

void finaliza_cod(){
  fclose(f);
	system("as out.s -o out.o");
	system("ld out.o -o out");
	system("rm out.o ");
	printf("Arquivo \"out.s\" e \"out.o\"  gerado.\n\n");
}
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
programa: INT MAIN ABRE_PARENTESES FECHA_PARENTESES ABRE_CHAVES corpo FECHA_CHAVES
 ;
corpo:  final corpo
    | defVar corpo
    | ifStatement  corpo
    |
 ;  
final: RETURN expr PONTO_E_VIRGULA
 ;
expr: expr MAIS expr 
    | expr MENOS expr
    | expr DIVIDIR expr
    | expr MULTIPLICA expr
    | NUM
    | VARIAVEL
 ;

defVar:  INT VARIAVEL PONTO_E_VIRGULA
    | VARIAVEL INGUAL expr PONTO_E_VIRGULA
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

