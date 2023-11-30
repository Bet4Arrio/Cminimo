#include "lib/DSTs.h"
#include<stdio.h>

int yylex(void);
int yyerror(char * msg);

void inicia_codigo();

void empilha_num(int num);
void empilha_var(char* varName);
void atribui_var(char* Varname);
void monta_var(char* Varname);

void monta_add();
void monta_sub();
void monta_mult();
void monta_div();

void monta_maior();
void monta_maior_igual();
void monta_menor();
void monta_menor_igual();
void monta_igual();
void monta_diferente();

void monta_OR();
void monta_AND();

void monta_if();
void monta_else();
void monta_label();
void  monta_start_while();
void  monta_end_while();
void monta_jmp();

void monta_retorno();
void finaliza_cod();