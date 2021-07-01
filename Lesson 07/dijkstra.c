
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

bool *S;

//Inizializza l'array dei predecessori (p) e delle distanze minime (d) dalla radice s
void initialize(int n, int s, int *p, int *d)
{
	for (int i = 0; i < n; i++)
	{
		d[i] = INT_MAX;
		//indice vertice che precede l'elemento
		p[i] = -1;
	}
	//distanza vertice corrente da se stesso
	d[s] = 0;
}

//Restitusice l'indice del vertice con distanza minima dalla radice il cui cammino minimo non è ancora stato individuato 
int extractMin(int *d,int n)
{
	int vmin = -1;
	int dmin = INT_MAX;

	//sicuri di aver selezionato il nodo che si trova ad una distanza minore
	for (int i = 0; i < n; i++)
	{
		if (S[i] == false)
		{
			if (d[i] < dmin)
			{
				vmin = i;
				dmin = d[i];
			}
		}
	}

	return vmin;
}

//Se la distanza per raggiungere v passando da u è inferiore a quella attuale, aggiorno la distanza minima e il predecessore di v
void relax(int u, int v,int w,int *p,int *d)
{
	//int newDist = d[u] + w; - - - si può usare questa variabile per ottimizzazione
	//w è il peso associato all'arco tra u e v
	//fedele allo pseudocodice
	if (d[v] > d[u] + w)
	{
		d[v] = d[u] + w;
		p[v] = u;
	}
}

void dijkstra(int **M,int n,int s,int *p,int *d)
{
	int i, u, v;
	
	//Inizializzazione degli array dei predecessori e dei costi dei cammini
	initialize(n,s,p,d);
	
	//allocazione dell'insieme risultato S contenente l'elenco dei vertici il cui costo minimo è già stato determinato 
	//in ExtracMin quindi non c'è bisogno di usare l'istruzione di inserimento nella coda
	S = (bool*)calloc(n, sizeof(bool));

	for (i = 0; i < n; i++)
	{
		u = extractMin(d,n);
		if (u == -1)
			break; //solo nel caso di grafi con più componenti connesse o nodi irraggiungibili

		S[u] = true;

		//effettua il rilassamento degli archi in base alla lista di adiacenza del nodo u
		//dato che implementiamo con matrice di adiacenza, tale lista coincide con la
		//riga u-esima della matrice M (per valori diversi da 0)
		for (v = 0; v < n; v++)
		{
			//verifico che l'arco u-v esista e che v non sia già nell'insieme soluzione
			if (M[u][v] != 0 && S[v]==false)
				relax(u, v, M[u][v],p,d);
		}
	}
	
	free(S);
}