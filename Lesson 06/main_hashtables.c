
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

#define LINE_LENGTH 120
#define PRINT_OUTPUT 1

// Main
// argv[1] = nome del file da caricare
// argv[2] = dimensione della tabella hash (m)
// argv[3] = seed della tabella hash
void main(int argc, char* argv[])
{
	char* line[LINE_LENGTH];
	char *key, *val, *keyToSearch = NULL, *keyToDelete=NULL;
	const char *separator = ",";
	HashTable hashTable;
	int m, hashSeed, n = 0;

	if (argc != 4)
	{
		printf("Errore: numero di parametri errato");
		return;
	}

	m = atoi(argv[2]);
	hashSeed = atoi(argv[3]);

	printf("Creazione della tabella hash...\n");

	hashTable = createHashTable(m, hashSeed);

	printf("\nLettura del file %s\n\n", argv[1]);

	FILE* fin = fopen(argv[1], "r");
	if (fin == NULL)
		return;

	printf("\nInserimento elementi nella tabella hash...\n");

	// Lettura chiave\valore da file e inserimento dei dati nella tabella hash
	while (fgets((char*)line, LINE_LENGTH, fin) != NULL)
	{
		// legge la chiave (parte che precede il separatore)
		key = (char*)strtok((char*)line, separator);
		// legge il valore (parte che segue il separatore)
		val = (char*)strtok(NULL, separator);
		// inserisce l'elemento nella tabella hash
		insert(&hashTable, key, strlen(key), atoi(val));
		n++;
	}

	fclose(fin);

	if (PRINT_OUTPUT)
		printTable(hashTable, true);

	// Ricerca di una chiave all'interno della tabella hash
	//keyToSearch = "048473280";
	if (keyToSearch != NULL)
	{
		SearchResult searchResult = search(hashTable, keyToSearch, strlen(keyToSearch));

		if (PRINT_OUTPUT)
		{
			printf("\nRicerca chiave: %s\n", keyToSearch);
			if (searchResult.i == -1)
			{
				printf("Chiave non trovata");
			}
			else
			{
				printf("h=%d i=%d v=%d", searchResult.h, searchResult.i, searchResult.value);
			}
		}
	}
	//---

	// Cancellazione di una chiave dalla tabella hash
	keyToDelete = "048473280";
	if (keyToDelete != NULL)
	{
		delete(&hashTable, keyToDelete, strlen(keyToDelete));
		
		if (PRINT_OUTPUT)
		{
			printf("\nCancellazione chiave: %s\n", keyToDelete);
			printTable(hashTable, true);
		}
	}
	//---

	freeHashTable(hashTable); 
}