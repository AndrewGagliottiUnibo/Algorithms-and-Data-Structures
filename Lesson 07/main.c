#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define PRINT_OUTPUT 1
#define PRINT_MATRIX 1
#define LINE_LENGTH 120

void dijkstra(int** M, int n, int s, int* p, int* d);

void printPath(int node, int* p);
void printSolution(int n, int s, int* p, int* d);

// Main
// argv[1] = nome del dataset da processare
// argv[2] = indice (1-based) del vertice sorgente per il calcolo dei cammini minimi con l'algoritmo di Dijkstra. 
//           Se argv[2] non è fornito verrà solamente caricato e visualizzato il grafo sotto forma di matrice di adiacenza.
void main(int argc, char* argv[])
{
	char *buf, line[LINE_LENGTH], *separator = ",";

	int w, start_node, end_node, i, j, max_node_label, **M, s, *p, *d;
	clock_t start, end;

	if (argc != 2 && argc != 3)
	{
		printf("Errore: numero di parametri errato");
		return;
	}

	printf("\nLettura del file %s\n\n", argv[1]);

	FILE* fin = fopen(argv[1], "r");
	if (fin == NULL)
		return;

	//Calcola il numero di nodi del grafo considerando l'etichetta di massimo valore presente
	//tra i nodi sorgente e i nodi destinazione
	max_node_label = -1;
	while (fgets(line, LINE_LENGTH, fin) != NULL)
	{
		// legge la chiave (parte che precede il separatore), indica il nodo di partenza
		buf = strtok(line, separator);
		start_node = atoi(buf);
		if (start_node > max_node_label)
			max_node_label = start_node;

		//legge il prossimo valore (nodo di destinazione)
		buf = strtok(NULL, separator);
		end_node = atoi(buf);
		if (end_node > max_node_label)
			max_node_label = end_node;
	}
	//---

	//Allocazione e inizializzazione della matrice di adiacenza
	M = (int**)malloc(max_node_label * sizeof(int*));
	for (i = 0; i < max_node_label; i++)
	{
		M[i] = (int*)calloc(max_node_label, sizeof(int));
	}
	//---

	//Memorizzazione nella matrice di adiacenza del grafo presente su file
	rewind(fin);
	while (fgets(line, LINE_LENGTH, fin) != NULL)
	{
		// legge la chiave (parte che precede il separatore), indica il nodo di partenza
		buf = strtok(line, separator);
		start_node = atoi(buf);

		//legge il prossimo valore (nodo di destinazione)
		buf = strtok(NULL, separator);
		end_node = atoi(buf);

		//legge il prossimo valore (peso dell'arco)
		buf = strtok(NULL, separator);
		w = atoi(buf);

		//i vertici nei dataset partono da 1, la matrice chiaramente da 0
		M[start_node - 1][end_node - 1] = w;
	}
	fclose(fin);
	//---

	//stampa la matrice di adiacenza
	if (PRINT_MATRIX)
	{
		printf("Matrice di adiacenza:\n");
		for (i = 0; i < max_node_label; i++)
		{
			printf("\t[%d]", i + 1);
		}
		printf("\n");

		for (i = 0; i < max_node_label; i++)
		{
			printf("[%d]", i + 1);
			for (j = 0; j < max_node_label; j++)
			{
				printf("\t %d", M[i][j]);
			}
			printf("\n");
		}
	}
	//---

	if (argc == 3)
	{
		//Esegue l'algoritmo di Dijkstra
		s = atoi(argv[2]);

		//allocazione dell'array dei predecessori
		p = (int*)malloc(max_node_label * sizeof(int));
		//allocazione dell'array delle distanze
		d = (int*)malloc(max_node_label * sizeof(int));

		start = clock();

		dijkstra(M, max_node_label, s - 1, p, d); //Internamente gli indici sono 0-based

		end = clock();
		//---

		if (PRINT_OUTPUT)
		{
			printf("\n\nTempo di esecuzione: %f sec\n", (double)(end - start) / CLOCKS_PER_SEC / max_node_label);
			printSolution(max_node_label, s - 1, p, d);
		}

		free(p);
		free(d);
	}

	free(M);
}

//funzione ricorsiva per stampare il cammino "al dritto"
//diversamente stamperebbe il percorso a ritroso
//la stampa è posta dopo la chiamata ricorsiva in modo che la prima stampa
//parta alla prima chiusura di chiamata
void printPath(int node, int* p)
{
	if (p[node] != -1)
		printPath(p[node], p);

	printf("%d->", node + 1);
}

void printSolution(int n, int s, int* p, int* d)
{
	int i;

	printf("\nSrc \tNodo \tCosto\t Percorso ottimo\n\n");

	for (i = 0; i < n; i++)
	{
		if (i == s) continue;
		if (d[i] != INT_MAX)
		{
			printf("%d\t", s + 1);
			printf("%d\t", i + 1);
			printf("%d\t", d[i]);
			printPath(i, p);
		}
		else
		{
			printf("%d\t", s + 1);
			printf("%d\t\t", i + 1);
			printf("non raggiungibile");
		}
		printf("\n");
	}
}
