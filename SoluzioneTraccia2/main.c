#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STRINGLENGTH 256

struct azienda {
  char nome[STRINGLENGTH];
  int N;
  char **citta;
  struct azienda *next;
};

void gestioneErrore();
struct azienda *leggiFile(FILE *fp, struct azienda *lista);
void scriviLista(struct azienda *lista);
struct azienda *rimuoviAzienda(struct azienda *lista, int soglia);
void scriviFile(FILE *fp, struct azienda *lista);
void freeLista(struct azienda*lista);

int main()
{
  struct azienda *lista=NULL;
  FILE *fp;


  fp = fopen("dati.txt","r");
  if (fp == NULL) gestioneErrore();
  lista = leggiFile(fp, lista);
  fclose(fp);

  scriviLista(lista);

  lista = rimuoviAzienda(lista,2);
  scriviLista(lista);

 
  fp = fopen("dati2.txt","w");
  scriviFile(fp, lista);
  fclose(fp);



  freeLista(lista);

}

static struct azienda *nuovoNodo(char *nome, int N)
{
  struct azienda *nodo;
  int i;

  nodo = (struct azienda *) malloc(sizeof(struct azienda));
  if (nodo == NULL) return NULL;
  
  strcpy(nodo->nome, nome);
  nodo->N = N;
  nodo->citta = (char **) malloc(N*sizeof(char *));
  for (i=0; i<N; i++)
    nodo->citta[i] = (char *) malloc(STRINGLENGTH*sizeof(char));
  nodo->next = NULL;
    
  return nodo;
}

static void freeNodo(struct azienda *nodo)
{
  int i;

  for (i=0; i<nodo->N; i++)
    free((void *) nodo->citta[i]);
  free((void *) nodo->citta);

  free((void *) nodo);
}

static struct azienda *inserisciLista(struct azienda *nodo, struct azienda *lista)
{
  if (lista==NULL) return nodo;
  lista->next = inserisciLista(nodo, lista->next);
  return lista;
}

static struct azienda *rimuoviNodo(struct azienda *lista, struct azienda *nodo)
{
  struct azienda *tmp;
  
  if (lista == nodo) {
    tmp = lista->next;
    freeNodo(lista);
    return tmp;
  }

  lista->next = rimuoviNodo(lista->next,nodo);
}


void gestioneErrore()
{
  printf("Errore\n");

  exit(0);
}

void freeLista(struct azienda *lista)
{
  if (lista != NULL) {
    freeLista(lista->next);
    freeNodo(lista);
  }
}


void scriviLista(struct azienda *lista)
{
  int i;
  
  while (lista!=NULL) {
    printf("%s %d ",lista->nome,lista->N);
    for (i=0; i<lista->N; i++) {
      printf("%s ",lista->citta[i]);
    }
    printf("\n");
    lista = lista->next;
  }
  printf("\n");
}

struct azienda *leggiFile(FILE *fp, struct azienda *lista)
{
  char nome[STRINGLENGTH], citta[STRINGLENGTH];
  int N, i;
  struct azienda *nodo;

  while(fscanf(fp,"%s%d",nome,&N)==2){
    nodo = nuovoNodo(nome,N);
    if (nodo==NULL) gestioneErrore();
    for (i=0; i<N; i++) {
      fscanf(fp,"%s",nodo->citta[i]);
    }
    lista = inserisciLista(nodo, lista);
  }
  return lista;
}


void scriviFile(FILE *fp, struct azienda *lista)
{
  int *buffer, n, i, j, count;
  struct azienda*ptr1, *ptr2;

  while (lista!=NULL) {
    n = lista->N;
    fprintf(fp,"%s %d ", lista->nome, n);
    buffer = (int *) calloc(n,sizeof(int));

    for (i=0; i<n; i++) {
      count = 0;
      if (!buffer[i]) {
	buffer[i] = 1;
	count++;
	fprintf(fp,"%s ",lista->citta[i]);
	for (j=i+1; j<n; j++) {
	  if (strcmp(lista->citta[i],lista->citta[j])==0) {
	    buffer[j] = 1;
	    count++;
	  }
	}
	fprintf(fp,"%d ",count);
      }
    }
    fprintf(fp,"\n");
    free((void *) buffer);
    lista = lista->next;
  }
}
struct azienda *rimuoviAzienda(struct azienda *lista, int soglia)
{
  if (lista==NULL) return lista;
  if (lista->N<soglia) {
    lista = rimuoviNodo(lista, lista);
    lista = rimuoviAzienda(lista, soglia);
  } else lista->next = rimuoviAzienda(lista->next, soglia);
  
  return lista;
}
