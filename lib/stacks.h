#include<stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct stack stack;

stack* st_create(void);

void* st_pop(stack*);

void* st_push(stack*, void*);

int st_clean(stack*);

int st_destroy(stack*);