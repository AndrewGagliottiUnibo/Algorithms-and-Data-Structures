#include <stdio.h>  
#include <string.h>  
#define LINE_LENGTH 120

void main(int argc, char* argv[])
{
	char *buf, *separator = ",", line[LINE_LENGTH];  int n, *arr;
	printf("Lettura del file %s\n", argv[1]);

	//apertura del file il cui nome è passato in linea di comando
	FILE* fin = fopen(argv[1] ,"r");
	if (fin == NULL)
		return;
	
	//conteggio delle righe presenti nel file
	n = 0;
	while (fgets(line, LINE_LENGTH, fin) != NULL)
		n++;
	
	//allocazione delle memoria (con valori azzerati) 
	arr = (int*) calloc(n, sizeof(int));

	//riposiziona il cursore a inizio file e legge i valori  
	rewind(fin);
	n = 0;
	while (fgets(line, LINE_LENGTH, fin) != NULL)
	{
		//legge la chiave (parte che precede il separatore)
		buf = strtok(line, separator);
		//legge il valore (parte che segue il separatore) e lo salva
		arr[n]=atoi( strtok(NULL, separator) );
		printf("%s->%d\n", buf, arr[n]);  n++;
	}
	fclose(fin);  
	free(arr);
}
