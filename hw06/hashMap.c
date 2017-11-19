#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hashMap.h"

struct hashLink {
   KeyType key; /*the key is what you use to look up a hashLink*/
   ValueType value; /*the value stored with the hashLink, a pointer to int in the case of concordance*/
   struct hashLink * next; /*notice how these are like linked list nodes*/
};
typedef struct hashLink hashLink;

struct hashMap {
    hashLink ** table; /*array of pointers to hashLinks*/
    int tableSize; /*number of buckets in the table*/
    int count; /*number of hashLinks in the table*/
};
typedef struct hashMap hashMap;

/*the first hashing function you can use*/
int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

/*the second hashing function you can use*/
int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; // the difference between 1&2
	return r;
}

/* initialize the supplied hashMap struct*/
void _initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

/* allocate memory and initialize a hash map*/
hashMap *createMap(int tableSize) {
	assert(tableSize > 0);
	hashMap *ht;
	ht = malloc(sizeof(hashMap));
	assert(ht != 0);
	_initMap(ht, tableSize);
	return ht;
}

/*
 Free all memory used by the buckets.
 Note: Before freeing up a hashLink, free the memory occupied by key and value
 */
 void _freeMap (struct hashMap * ht)
 {
 	int i;
 	struct hashLink *temp;
 	struct hashLink *temp2;
 	for(i=0; i<ht->tableSize; i++){
 		temp=ht->table[i];
 		while(temp!=0){
 			temp2=temp->next;
 			free(temp->key);
 			free(temp->value); /* also free the memory pointed by value*/
 			free(temp);
 			temp=temp2;
 		}
 	}
 	free(ht->table);
 	ht->count=0;
 	ht->table=0;
 	ht->tableSize=0;
 }

/* Deallocate buckets and the hash map.*/
void deleteMap(hashMap *ht) {
	assert(ht!= 0);
	/* Free all memory used by the buckets */
	_freeMap(ht);
	/* free the hashMap struct */
	free(ht);
}

/*
Resizes the hash table to be the size newTableSize
Remember what you had to do for the dynamic array!
This isn't elegant. Values have to be moved.
*/
void _setTableSize(struct hashMap * ht, int newTableSize)
{
	/*TODO*/
  hashMap* tmpMap = createMap(newTableSize);

	for (int i = 0; i < ht->tableSize; i++) {
		if (ht->table[i] == NULL)
			continue;

		hashLink* currentLink = ht->table[i];

		do {
			insertMap(tmpMap, currentLink->key, currentLink->value);
			currentLink = currentLink->next;
		}
    while (currentLink != NULL);
	}

	_freeMap(ht);
	ht->count = tmpMap->count;
	ht->table = tmpMap->table;
	ht->tableSize = tmpMap->tableSize;

	/* We don't want to free the table here, as it is the new table being used by our hash table */
	tmpMap->table = NULL;
free(tmpMap);
}

/*
 insert the following values into a hashLink, you must create this hashLink but
 only after you confirm that this key does not already exist in the table. For example, you
 cannot have two hashLinks for the word "taco".

 if a hashLink already exists in the table for the key provided you should
 replace that hashLink--this requires freeing up the old memory pointed by hashLink->value
 and then pointing hashLink->value to value v.

 also, you must monitor the load factor and resize when the load factor is greater than
 or equal LOAD_FACTOR_THRESHOLD (defined in hashMap.h).
 */
void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{
	/*TODO*/

int hash;
struct hashLink * link = (struct hashLink *) malloc(sizeof(struct hashLink));
char * newKey = (char *) malloc(strlen(k) + 1);

if(HASHING_FUNCTION == 1) {
    hash = stringHash1(k) % ht->tableSize;
  } else {
    hash = stringHash2(k) % ht->tableSize;
  }

if(hash < 0) {
    hash += ht->tableSize;
}

if(containsKey(ht, k)) {
    removeKey(ht, k);
}

strcpy(newKey, k);
if(tableLoad(ht) >= LOAD_FACTOR_THRESHOLD) {
    _setTableSize(ht, ht->tableSize * 2);
}

ht->table[hash] = link;
link->key = newKey;
link->next = ht->table[hash];
link->value = v;

ht->count++;

}

/*
 this returns the value (which is void*) stored in a hashLink specified by the key k.

 if the user supplies the key "taco" you should find taco in the hashTable, then
 return the value member of the hashLink that represents taco.

 if the supplied key is not in the hashtable return NULL.
 */
ValueType atMap (struct hashMap * ht, KeyType k)
{
	/*TODO*/
  int hashIndex;
  struct hashLink *currLink;

  if(HASHING_FUNCTION == 1) {
    hashIndex = stringHash1(k) % ht->tableSize;
  } else {
    hashIndex = stringHash2(k) % ht->tableSize;
  }

  currLink = ht->table[hashIndex];

  while (currLink != 0) {
    if (strcmp(k, currLink->key) == 0) {
      return currLink->value;
    }
    currLink = currLink->next;
}
	return 0;
}

/*
 a simple yes/no if the key is in the hashtable.
 0 is no, all other values are yes.
 */
int containsKey (struct hashMap * ht, KeyType k)
{
	/*TODO*/
int hash;
if (HASHING_FUNCTION == 1) {
	hash = stringHash1(k) % ht->tableSize;
}else if (HASHING_FUNCTION == 2) {
	hash = stringHash2(k) % ht->tableSize;
}
	hashLink* currentLink = ht->table[hash];

	while (currentLink != NULL) {
		if (strcmp(currentLink->key, k) == 0)
			return 1;
		currentLink = currentLink->next;
	}
return 0;
}

/*
 find the hashlink for the supplied key and remove it, also freeing the memory
 for that hashlink. it is not an error to be unable to find the hashlink, if it
 cannot be found do nothing (or print a message) but do not use an assert which
 will end your program.
 */
void removeKey (struct hashMap * ht, KeyType k)
{
	/*TODO*/
  int hashIndex;
    hashIndex = stringHash2(k) % ht->tableSize;
  	if (hashIndex < 0){
  		hashIndex += ht->tableSize;
  	}

  	struct hashLink *curLink = ht->table[hashIndex];
  	struct hashLink *prevLink = ht->table[hashIndex];
  	while (curLink != 0) {
  		if (curLink->key == k) {
  			prevLink->next = curLink->next;
  			free(curLink);
  			return;
  		}
  		prevLink = curLink;
  		curLink = curLink->next;
  }
}
/*
 returns the number of hashLinks in the table
 */
int size (struct hashMap *ht)
{
	/*TODO*/
	return ht->count;

}

/*
 returns the number of buckets in the table
 */
int capacity(struct hashMap *ht)
{
	/*TODO*/
	return ht->tableSize;
}

/*
 returns the number of empty buckets in the table, these are buckets which have
 no hashlinks hanging off of them.
 */
int emptyBuckets(struct hashMap *ht)
{
	/*TODO*/
  int empty = 0;
    for (int i = 0; i < ht->tableSize; i++) {
  		if (ht->table[i] == NULL){
  			empty++;
      }
  	}
  return empty;
}

/*
 returns the ratio of: (number of hashlinks) / (number of buckets)

 this value can range anywhere from zero (an empty table) to more then 1, which
 would mean that there are more hashlinks then buckets (but remember hashlinks
 are like linked list nodes so they can hang from each other)
 */
float tableLoad(struct hashMap *ht)
{
	/*TODO*/
  float loadUp;
    loadUp = (float)size(ht) / capacity(ht);
    return loadUp;
}

/* print the hashMap */
void printMap (struct hashMap * ht)
{
	int i;
	struct hashLink *temp;
	for(i = 0;i < capacity(ht); i++){
		temp = ht->table[i];
		if(temp != 0) {
			printf("\nBucket Index %d -> ", i);
		}
		while(temp != 0){
			printf("Key:%s|", temp->key);
			printValue(temp->value);
			printf(" -> ");
			temp=temp->next;
		}
	}
}
