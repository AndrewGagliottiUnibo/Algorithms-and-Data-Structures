
#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#include <stdbool.h>

typedef struct Node_
{
	char* key;		// chiave contenuta nel nodo
	int keyLen;		// lunghezza della chiave (in byte)
	int value;		// valore contenuto nel nodo
	struct Node_ *next; // puntatore al nodo successivo
} Node;

typedef struct 
{
	int hashSeed;		// seme iniziale per la funziona has (Murmur)
	int m;				// numero di buckets
	int n;				// numero di chiavi memorizzate all'interno della tabella
	Node** buckets;		// puntatore all'array di bucket
} HashTable;

typedef struct
{
	int h;				// indice del bucket corrispondente alla chiave della ricerca
	int i;				// indice posizionale del nodo all'interno della lista del bucket (-1 se non presente) 
	int value;			// valore trovato corrispondente alla chiave (indefinito se i=-1)
} SearchResult;

HashTable createHashTable(int m, int hashSeed);
void freeHashTable(HashTable hashTable);
void insert(HashTable* hashTable, const char* key, int keyLen, int value);
SearchResult search(HashTable hashTable, const char* key, int keyLen);
void delete(HashTable* hashTable, const char* key, int keyLen);

void printTable(HashTable hashTable, bool printStats);

#endif // HASHTABLE_H_INCLUDED