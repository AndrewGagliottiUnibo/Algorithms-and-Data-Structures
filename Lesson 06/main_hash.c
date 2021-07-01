
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 120
#define PRINT_OUTPUT 1

unsigned int hashModulus(unsigned int k, unsigned int m);
unsigned int hashMurmur(const char* key, unsigned int len, unsigned int seed);

// Main
// argv[1] = nome del file da caricare
// argv[2] = parametro m della funzione modulo/seed della funzione Murmur
void main(int argc, char* argv[])
{
	char *line[LINE_LENGTH];
	char *key;
	const char *separator = ",";
	int m,digestModulus,digestMurmur;
		
	if (argc != 3)
	{
		printf("Errore: numero di parametri errato");
		return;
	}

	m = atoi(argv[2]);

	printf("\nLettura del file %s\n\n", argv[1]);

	FILE* fin = fopen(argv[1], "r");
	if (fin == NULL) 
		return;
	
	// Lettura chiavi da file e esecuzione funzioni hash
	while (fgets((char*)line, LINE_LENGTH, fin) != NULL)
	{
		// legge la chiave (parte che precede il separatore)
		key = (char*)strtok((char*)line, separator); 
		int keyLen = strlen(key);
		int intKey = atoi(key);
		
		// calcola l'hash digest della key letta (considerata come numero intero) utilizzando la funzione modulo
		digestModulus = hashModulus(intKey, m);
		if (PRINT_OUTPUT)
			printf("hashModulus(%d,%d)->\tDigest: %lu", intKey,m, (long unsigned int)digestModulus);
			
		// calcola l'hash digest della key letta utilizzando la funzione Murmur
		digestMurmur = hashMurmur(key, keyLen, m);
		if (PRINT_OUTPUT)
			printf("\thashMurmur('%s',%d,%d)->\tDigest: %lu", key, keyLen, m, (long unsigned int)digestMurmur);

		if (PRINT_OUTPUT)
			printf("\n");
	}
}