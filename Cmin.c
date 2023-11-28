#include "Cmin.h"

#define INT_TAM 8
extern int linha;   
extern int coluna;
extern int yyleng;

int yyerror(char * msg){
printf("(%d, %d) Error: %s  \n", linha, coluna-yyleng, msg);
exit(0);
}

FILE *f;
ht* tabVars;
int totaloffset = 0;

typedef struct {
    char * nome; 
    size_t offset;
    int valor_atual;
} VarStruct;


VarStruct* pegaVar(const char * VarName){
    VarStruct* va = ht_get(tabVars, VarName);
    if( va == NULL){
        char msg[125];
        snprintf(msg, sizeof(msg),"Variavel Nao declarada  %s \n", VarName);
        yyerror(msg);
        exit(-1);
    }

}

void printaTabela(){
    hti it = ht_interator(tabVars);
    printf("PRITANDO TABELa \n");
    for (;ht_next(&it) >= 0;){
        VarStruct *va = (VarStruct *) it.value;
        char *k = (char *) it.key;
        printf("%s e %s \n", k, va->nome);
    }
    
}

void inicia_codigo(){
  tabVars = ht_create();

  f = fopen("out.s","w+");
	fprintf(f, ".text\n");
	fprintf(f, "    .global _start\n\n");
    fprintf(f, "_start:\n\n");
    fprintf(f, "    pushq	%%rbp\n");
    fprintf(f, "    movq %%rsp, %%rbp\n");

}


void monta_retorno(){
    fprintf(f, "    popq    %%rbx\n");
	fprintf(f, "    movq    $1, %%rax\n"); // finaliza programa 
	fprintf(f, "    int     $0x80\n\n");
}

void empilha_num(int num){
    fprintf(f, "	pushq $%d\n\n", num);
}

void empilha_var(char* Varname){
    fprintf(f, "#  empilhando Var %s \n", Varname);
    VarStruct* va = pegaVar(Varname);
    fprintf(f, "	pushq -%ld(%%rbp)\n\n", va->offset);
}


void monta_add(){
    fprintf(f, "	popq %%rbx\n");
	fprintf(f, "	popq %%rax\n");
	fprintf(f, "	addq %%rax, %%rbx\n");
	fprintf(f, "	pushq %%rbx\n");
}

void monta_sub(){
    fprintf(f, "	popq %%rax\n");
	fprintf(f, "	popq %%rbx\n");
	fprintf(f, "	subq %%rax, %%rbx\n");
	fprintf(f, "	pushq %%rbx\n");
}

void monta_mult(){
    fprintf(f, "	popq %%rbx\n");
	fprintf(f, "	popq %%rax\n");
	fprintf(f, "	imul %%rax, %%rbx\n");
	fprintf(f, "	pushq %%rbx\n");
}

void monta_div(){
	fprintf(f, "	popq %%rbx\n"); // divisor
    fprintf(f, "	popq %%rax\n"); // parte inteira
    fprintf(f, "	movq $0, %%rdx\n"); // rola

	fprintf(f, "	divq %%rbx\n");
	fprintf(f, "	pushq %%rax\n");
}

void monta_var(char* Varname){
    fprintf(f, "#definindo Var %s \n", Varname);
    VarStruct *  va = (VarStruct*) malloc(sizeof(VarStruct));
    va->nome = (char*) malloc(sizeof(Varname));
    totaloffset += INT_TAM;
    va->offset = totaloffset;
    strcpy(va->nome, Varname);
    ht_set(tabVars, va->nome, va);
    fprintf(f, "	subq $%d, %%rsp\n\n", INT_TAM); // aloca espaco variavel
    fprintf(f, "	movq $0,  -%ld(%%rbp)\n\n", va->offset); // inicia com 0 (fuck C)
    
}

void atribui_var(char* Varname){
    fprintf(f, "# atribuindo Var %s \n", Varname);
    VarStruct* va = pegaVar(Varname);
    fprintf(f, "	popq -%ld(%%rbp)\n\n", va->offset);
}


void finaliza_cod(){
  fclose(f);
	system("as out.s -o out.o");
	system("ld out.o -o out");
	system("rm out.o ");
	printf("Arquivo \"out.s\" e \"out.o\"  gerado.\n\n");
}