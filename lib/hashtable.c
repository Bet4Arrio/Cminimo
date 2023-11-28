#include"hashtable.h"
#include <stdio.h>

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL
#define TABLE_INCREMENT 2

typedef struct ht_entry {
	char * key;
	void * value;
} ht_entry;

typedef struct ht {
	 size_t size;
	 ht_entry* table;
} ht;



int check(ht* table, const char * key, size_t index){
	int a =  (table->table[index].value != NULL && strcmp(key, table->table[index].key) != 0);
	return a;
}

ht* ht_create (){
	ht * hashtable;
	
	hashtable = (ht*) malloc(sizeof(ht));
	if(hashtable == NULL){
		exit(0);
	}
	
	hashtable->size = TABLE_INCREMENT;
	hashtable->table = (ht_entry*) malloc(sizeof(ht_entry)*TABLE_INCREMENT);
	for (size_t i = 0; i < hashtable->size ; i++){
		hashtable->table[i].value = NULL;
	}
	
	return hashtable;
}



static uint64_t hash_key(const char * key){
	uint64_t hash = FNV_OFFSET; 
	
	for(const char* p = key; *p; p++){
		hash ^= (uint64_t)(unsigned char)(*p);
		hash *= FNV_PRIME;
	}
	
	return hash;
}


size_t hashfunction(ht* table, const char * key){
	return  hash_key(key)%table->size;
}

void* ht_get(ht* table, const char * key){
	size_t index = hashfunction(table, key);
	if(check(table, key, index))
		return NULL;
	return table->table[index].value;
	
}


void  growTable(ht* table){
	size_t old_size = table->size;
	table->size = old_size*TABLE_INCREMENT;
	ht_entry* old_table = table->table;
	table->table = (ht_entry*) malloc(sizeof(ht_entry)*table->size);
	for (size_t i = 0; i < table->size ; i++){
		table->table[i].value = NULL;
	}

	for(size_t i = 0; i < old_size; i++){
		if( old_table[i].key != NULL)
			ht_set(table, old_table[i].key, old_table[i].value);
	}
	free(old_table);

}



const char* ht_set(ht* table, char* key, void * value){
	size_t index = hashfunction(table, key);
	while (check(table, key, index)){
        growTable(table);
        index = hashfunction(table, key);
    }
	table->table[index].key = key;
	table->table[index].value = value;
	return key;
}

const char* ht_set_copy(ht* table, char* key, void * value){
	char* cpkey = (char*) malloc(strlen(key));
	void* cpValue = malloc(sizeof(value));
	strcpy(cpkey, key);
	memcpy(cpValue, value, sizeof(value));

	ht_set(table, cpkey, cpValue);
	
	return key;
}

size_t ht_lenght(ht* table){
	return table->size;
}


void ht_destroy(ht* table){
	for (size_t i = 0; i < table->size; i++){
		if (table->table[i].value){
			free(table->table[i].key);
			free(table->table[i].value);
		}
	}
	free(table->table);
	free(table);
	
}

hti ht_interator(ht* table){
	hti it;
	it.key = NULL;
	it.value = NULL;
	it._index = -1;
	it._table = table;

	return it;
}

int ht_next(hti* it){
	if(++(it->_index) >= it->_table->size){
		return -1;
	}
	for (; it->_index < it->_table->size; it->_index++){
		if(it->_table->table[it->_index].value){
			break;
		}
	}

	if(it->_index >= it->_table->size){
		return -1;
	}

	it->key = it->_table->table[it->_index].key;
	it->value = it->_table->table[it->_index].value;
	return it->_index;
}
