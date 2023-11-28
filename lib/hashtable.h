#include<stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct ht ht;




ht* ht_create(void);

void ht_destroy(ht* table);

void* ht_get(ht * table, const char* key);

const char* ht_set_copy(ht* table, char* key, void * value);

const char* ht_set(ht* table, char * key, void * value);

size_t ht_lenght(ht *);

typedef struct {
	const char * key;
	void * value;

	ht* _table;
	size_t _index;

} hti;

hti ht_interator(ht * table);

int ht_next(hti* it);
