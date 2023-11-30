#include "stacks.h"

typedef struct stack {
	 size_t size;
	 size_t index;
	 void** entrys;
} stack;

#define GROW_FACTOR 4

stack* st_create(void){
    stack * st = (stack *) malloc(sizeof(stack));
    if(st == NULL){
      exit(0);
    }
    st->size = GROW_FACTOR;
    st->index = 0;
    st->entrys = (void**) malloc(sizeof(void*) * st->size);
    return st;
}


stack* growStack(stack* st){
    st->size *= GROW_FACTOR;
    st->entrys = realloc(st->entrys  ,sizeof(void*) * st->size);

    return st;
}
void* st_pop(stack* st){
    if (st->index == 0)
        return st->entrys[st->index];
    st->index--;
    return st->entrys[st->index+1];
}

void* st_push(stack* st, void* value){
    if(st->index + 1 >= st->size){
        growStack(st);
    }

    st->index++;
    // void* cpValue = malloc(sizeof(value));
    // memcpy(cpValue, value, sizeof(value));
    st->entrys[st->index] = value;
    return value;
}

int st_clean(stack* st){
    for (size_t i = 0; i < st->size; i++){
        free(st->entrys[i]);
    }

    st->index = 0;

    return 1;
    
}

int st_destroy(stack* st){
    for (size_t i = 0; i < st->size; i++){
        free(st->entrys[i]);
    }
    free(st);
    return 1;
}