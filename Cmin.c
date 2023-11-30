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
stack* labelStack;

unsigned int lastLabel = 0;
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
  labelStack = st_create();
  f = fopen("out.s","w+");
	fprintf(f, ".text\n");
	fprintf(f, "    .global _start\n\n");
    fprintf(f, "_start:\n\n");
    fprintf(f, "    pushq	%%rbp\n");
    fprintf(f, "    movq %%rsp, %%rbp\n");

}


char* cria_label(){
    char buffer[125];
    snprintf(buffer, sizeof(buffer),".L%d", lastLabel++);
    char* result = (char*) malloc(strlen(buffer));;
    strcpy(result, buffer);
    return result;
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
    if(ht_get(tabVars, Varname) != NULL){
        yyerror("Variavel ja declarada");
    }
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

void monta_maior(){
    fprintf(f, "# maior que  \n");
    fprintf(f, "	popq %%rbx\n"); 
    fprintf(f, "	popq %%rax\n");
    fprintf(f, "	cmpq %%rbx, %%rax\n");
    fprintf(f, "	setg	%%al\n");
    fprintf(f, "	movzbq	%%al, %%rax\n");
    fprintf(f, "    pushq %%rax\n");
    fprintf(f, "\n");
}

void monta_maior_igual(){
    fprintf(f, "# maior igual\n");

    fprintf(f, "	popq %%rbx\n"); 
    fprintf(f, "	popq %%rax\n");
    fprintf(f, "	cmpq %%rbx, %%rax\n");
    fprintf(f, "	setge	%%al\n");
    fprintf(f, "	movzbq	%%al, %%rax\n");
    fprintf(f, "    pushq %%rax\n");
    fprintf(f, "\n");

}

void monta_menor(){
    fprintf(f, "#menor \n");
    fprintf(f, "	popq %%rbx\n"); 
    fprintf(f, "	popq %%rax\n");
    fprintf(f, "	cmpq %%rbx, %%rax\n");
    fprintf(f, "	setl	%%al\n");
    fprintf(f, "	movzbq	%%al, %%rax\n");
    fprintf(f, "    pushq %%rax\n");
    fprintf(f, "\n");

}

void monta_menor_igual(){
    fprintf(f, "#menor igual\n");

    fprintf(f, "	popq %%rbx\n"); 
    fprintf(f, "	popq %%rax\n");
    fprintf(f, "	cmpq %%rbx, %%rax\n");
    fprintf(f, "	setle	%%al\n");
    fprintf(f, "	movzbq	%%al, %%rax\n");
    fprintf(f, "    pushq %%rax\n");
    fprintf(f, "\n");

}

void monta_igual(){
    fprintf(f, "#igual\n");

    fprintf(f, "	popq %%rbx\n"); 
    fprintf(f, "	popq %%rax\n");
    fprintf(f, "	cmpq %%rbx, %%rax\n");
    fprintf(f, "	sete	%%al\n");
    fprintf(f, "	movzbq	%%al, %%rax\n");
    fprintf(f, "    pushq %%rax\n");
    fprintf(f, "\n");

}

void monta_diferente(){
    fprintf(f, "#diferente \n");

    fprintf(f, "	popq %%rbx\n"); 
    fprintf(f, "	popq %%rax\n");
    fprintf(f, "	cmpq %%rbx, %%rax\n");
    fprintf(f, "	setne	%%al\n");
    fprintf(f, "	movzbq	%%al, %%rax\n");
    fprintf(f, "    pushq %%rax\n");
    fprintf(f, "\n");

}

void monta_AND(){
    fprintf(f, "#&&\n");

    fprintf(f, "	popq %%rbx\n"); 
    fprintf(f, "	popq %%rax\n");
    fprintf(f, "	addq %%rbx, %%rax\n");
    fprintf(f, "	cmpq $2, %%rax\n");
    fprintf(f, "	sete	%%al\n");
    fprintf(f, "	movzbq	%%al, %%rax\n");
    fprintf(f, "    pushq %%rax\n");
    fprintf(f, "\n");

}

void monta_OR(){
    fprintf(f, "# || \n");

    fprintf(f, "	popq %%rbx\n"); 
    fprintf(f, "	popq %%rax\n");
    fprintf(f, "	addq %%rbx, %%rax\n");
    fprintf(f, "	cmpq $0, %%rax\n");
    fprintf(f, "	setne	%%al\n");
    fprintf(f, "	movzbq	%%al, %%rax\n");
    fprintf(f, "    pushq %%rax\n");
    fprintf(f, "\n");
}


void monta_start_while(){
    
    fprintf(f, "#label do while \n");
    char* label = (char *) st_push(labelStack, cria_label());
    fprintf(f, "%s:\n", label);
    
}

void monta_end_while(){
    char* label = (char *) st_pop(labelStack);
    monta_if();
    st_push(labelStack, label);
}


void monta_label(){
    char* label = (char *) st_pop(labelStack);
    fprintf(f, "%s:\n", label);
    free(label);
}

void monta_jmp(){
    char* label = (char *) st_pop(labelStack);
    fprintf(f, "jmp %s\n", label);
    free(label);
}

void monta_if(){
    char* label = (char *) st_push(labelStack, cria_label());
    fprintf(f, "	popq %%rbx\n");
    fprintf(f, "	cmpq $1, %%rbx\n"); // ver se eh verdade soh 
    // lhedar com stacks 
    fprintf(f, "	jne %s\n", label); //  se for falso 
}

void monta_else(){
    char* label =  cria_label();
    fprintf(f, "	jmp %s\n", label);
    monta_label();
    st_push(labelStack, label);
}


void finaliza_cod(){
    fclose(f);
	system("as out.s -o out.o");
	system("ld out.o -o out");
	system("rm out.o ");
	printf("Arquivo \"out.s\" e \"out.o\"  gerado.\n\n");
}