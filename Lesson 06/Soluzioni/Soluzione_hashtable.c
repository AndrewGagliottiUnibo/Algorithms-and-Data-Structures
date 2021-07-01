
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "hashtable.h"

unsigned int hashMurmur(const char* key, unsigned int len, unsigned int seed);

// Creazione nuova tabella hash
HashTable createHashTable(int m, int hashSeed)
{
	HashTable hashTable;
	hashTable.m = m;
	hashTable.hashSeed = hashSeed;
	hashTable.n = 0;
	hashTable.buckets =(Node**) malloc(m * sizeof(Node *));

	for (int i = 0; i < m; i++)
		hashTable.buckets[i] = NULL;

	return hashTable;
}

// Libera la memoria allocata per un nodo di una lista
void freeNode(Node* nodePointer)
{
	free(nodePointer->key);
	free(nodePointer);
}

// Libera tutta la memoria allocata per la tabella hash
void freeHashTable(HashTable hashTable)
{
	Node *L, *Lnext;

	for (int i = 0; i < hashTable.m; i++)
	{
		L = hashTable.buckets[i];
		while (L)
		{
			Lnext = L->next;
			freeNode(L);
			L = Lnext;
		}
	}
	free(hashTable.buckets);
}

// Applicazione funzione hash
int hashFunction(HashTable hashTable, const char* key, int keyLen)
{
	return hashMurmur(key, keyLen, hashTable.hashSeed) % hashTable.m;
}

// Inserimento di un nuovo elemento dentro la tabella hash
// (si suppone che l'elemento non sia già presente all'interno della tabella)
void insert(HashTable* hashTable, const char* key,int keyLen,int value)
{
	Node *L,*Lnew;
	int h;  

	h = hashFunction(*hashTable,key,keyLen);
	L = hashTable->buckets[h];

	if ((Lnew = malloc(sizeof(Node))) == 0)
	{
		printf("Out of memory (insertNode)\n");
		return;
	}
	
	Lnew->key = (char*)malloc(keyLen*sizeof(char));
	memcpy(Lnew->key,key, keyLen * sizeof(char));
	Lnew->keyLen = keyLen;
	Lnew->value = value;
	Lnew->next = L;

	hashTable->buckets[h] = Lnew;
	hashTable->n++;
}

//Ricerca per chiave di un elemento all'interno della tabella hash
SearchResult search(HashTable hashTable, const char* key, int keyLen)
{
	SearchResult searchRes;
	Node *L;
	int h,i = 0;

	h = hashFunction(hashTable, key, keyLen);
	L = hashTable.buckets[h];
	
	searchRes.h = h;
	searchRes.i = -1;
	while (L)
	{
		if (keyLen == L->keyLen &&
			memcmp(key, L->key, keyLen) == 0)
		{
			searchRes.i = i;
			searchRes.value = L->value;
			break;
		}
		else
			L = L->next;
		i++;
	}

	return searchRes;
}

// Cancellazione per chiave di un elemento all'interno della tabella hash
void delete(HashTable* hashTable, const char* key, int keyLen)
{
	SearchResult searchResult;
	Node *L,*L2=NULL;
	
	searchResult = search(*hashTable, key, keyLen);

	if (searchResult.i == -1)
		return;

	L = hashTable->buckets[searchResult.h];
	
	// L'elemento è l'unico nodo della lista
	if (L->next == NULL)
	{
		freeNode(L);
		hashTable->buckets[searchResult.h] = NULL;
	}
	// Lista composta da più elementi
	else
	{
		// L'elemento è in testa alla lista
		if (searchResult.i == 0)
		{
			hashTable->buckets[searchResult.h] = L->next;
			freeNode(L);
		}
		// L'elemento non è in testa alla lista
		else
		{
			for (int j = 0; j < searchResult.i; j++)
			{
				L2 = L;
				L = L->next;
			}
			
			L2->next = L->next;
			freeNode(L);
		}
	}

	hashTable->n--;
}

// stampa a video la tabella hash
void printTable(HashTable hashTable,bool printStats)
{
	Node *p;
	int i, j, chainLength, maxChainLength, nullBuckets;
	chainLength = 0;
	maxChainLength = 0;
	nullBuckets = 0;
	printf("m=%d\n", hashTable.m);
	printf("hashSeed=%d\n", hashTable.hashSeed);
	printf("n=%d\n", hashTable.n);
	for (i = 0; i < hashTable.m; i++)
	{
		p = hashTable.buckets[i];
		printf("\n[Bucket %d]: ", i);
		j = 0;
		while (p)
		{
			j++;
			printf("(Nodo %d: k='%.*s' v=%d)-->", j,p->keyLen, p->key,p->value);
			p = p->next;
		}
		if (j == 0) 
			nullBuckets++;
		if (j > maxChainLength)
			maxChainLength = j;
		chainLength += j;
	}

	if (printStats)
	{
		printf("\n");
		printf("\nFattore di carico: %.2f", (double)hashTable.n / hashTable.m);
		printf("\nLunghezza massima delle catene di overflow: %d", maxChainLength);
		printf("\nLunghezza media delle catene di overflow: %.2f\n", (double)chainLength / (hashTable.m - nullBuckets));
	}
}