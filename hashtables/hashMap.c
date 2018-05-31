#include <stdlib.h>
#include "hashMap.h"
#include "structs.h"
#include <string.h>
#include <assert.h>

int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
	r += (i+1) * str[i]; /*the difference between 1 and 2 is on this line*/
	return r;
}

void initMap (struct hashMap * ht, int tableSize)
{

  /* FIX ME */

	int i;
	if (ht == NULL) { return; }

	ht->tableSize = tableSize;
	ht->count = 0;
	ht->table = (hashLink**) malloc(sizeof(hashLink*)*tableSize);
	assert(ht->table);
	for(i = 0; i < tableSize; i++) {
		ht->table[i] = 0;
	}

}

void freeMap (struct hashMap * ht)
{
	int i;
	struct hashLink *temp;
	struct hashLink *temp2;
	for(i = 0; i < ht->tableSize; i++){
		temp = ht->table[i];
		while(temp != NULL){
			temp2 = temp->next;
			free(temp);
			temp = temp2;
		}
	}
	free(ht->table);
	ht->count=0;
	ht->table=0;
	ht->tableSize=0;
}

/* Add an element to the Hash Table */
void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{

    /* FIX ME */

		int hash;
		int hashIndex;
		hashLink* newLink;
		assert(ht);
		hash = stringHash1(k);
		hashIndex = hash % ht->tableSize;
		if (containtsKey(ht,k) != 0) {
			*atMap(ht,k) = v;
		}
		else {
			newLink = (hashLink*) malloc(sizeof(hashLink));
			assert(newLink);
			newLink->value = v;
			newLink->key = k;
			newLink->next = ht->table[hashIndex];
			ht->table[hashIndex] = newLink;
			(ht->count)++;
		}
}



/* Returns a pointer to the value of element with key k in the Hash Table
   If the element is not in the Hash Table, returns NULL */
ValueType* atMap (struct hashMap * ht, KeyType k)
{

    /* FIX ME */
		int hash, hashIndex;
		hashLink *temp;
		assert(ht);
		hash = stringHash1(k);
		hashIndex = hash % ht->tableSize;
		temp = ht->table[hashIndex];
		while (temp != NULL) {
			if (!strcmp(temp->key, k)) {
				return (&(temp->value));
			}
			temp = temp->next;
		}
		return NULL;
}

int containsKey (struct hashMap * ht, KeyType k)
{
	if (atMap(ht,k)==0){
		return 0;
	}else{
		return 1;
	}
}

void removeKey (struct hashMap * ht, KeyType k)
{
	int bucket = stringHash2(k)%ht->tableSize;
	struct hashLink *cur;
	struct hashLink *prev;
	if(ht->table[bucket] == 0){
		return;
	}else{
		cur=ht->table[bucket];
		prev=ht->table[bucket];
		while(cur!=0){
			if(strcmp(cur->key,k)==0){
				if(cur==ht->table[bucket]){
					ht->table[bucket]=cur->next;

				}else{
				prev->next=cur->next;
				}
				free(cur);
				ht->count--;
				return;
			}else{
				prev=cur;
				cur=cur->next;
			}
		}
	}
}

int sizeMap (struct hashMap *ht)
{
	return ht->count;
}

int capacityMap(struct hashMap *ht)
{
	return ht->tableSize;
}

int emptyBuckets(struct hashMap *ht)
{
	int runner = 0;
	int i;
	for(i=0; i<ht->tableSize; i++){
		if(ht->table[i]==0){
			runner++;
		}
	}
	return runner;
}

float tableLoad(struct hashMap *ht)
{
   return (float)sizeMap(ht)/(float)capacityMap(ht);
}
