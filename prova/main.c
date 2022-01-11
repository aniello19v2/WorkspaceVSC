#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct persona{
    
    char Nome[30];
    char Cognome[30];
    int Peso;
    int Altezza;
    int Eta;
    struct persona *next;

}persona;

void gestioneErrore();
persona *nuovoNodo(char *nome, char *cognome, int peso, int altezza, int eta);
persona *leggiFile(FILE *fp, persona *lista);
void scriviLista(persona *lista);
persona *rimuoviPersona(persona *lista, int soglia);
void scriviFile(FILE *fp, persona *lista);
void freeLista(persona *lista);

int main(void){

    FILE *fp;
    persona *lista=NULL;

    fp = fopen("dati.txt","r");
    if (fp == NULL) gestioneErrore();
    lista = leggiFile(fp, lista);
    fclose(fp);

    scriviLista(lista);

    printf("\n");

    lista = rimuoviPersona(lista,12);
    scriviLista(lista);
 
    fp = fopen("dati2.txt","w");
    scriviFile(fp, lista);
    fclose(fp);

    freeLista(lista);

    return 0;
}

persona *nuovoNodo(char *nome, char *cognome, int peso, int altezza, int eta)
{
  persona *nodo;

  nodo = (persona *) malloc(sizeof(persona));
  if (nodo == NULL) return NULL;
  
  strcpy(nodo->Nome, nome);
  strcpy(nodo->Cognome, cognome);
  nodo->Peso = peso;
  nodo->Altezza = altezza;
  nodo->Eta = eta;
  nodo->next = NULL;

  return nodo;
}

static void freeNodo(persona *nodo)
{

    free((void *) nodo);

}

persona *inserisciLista(persona *nodo, persona *lista)
{
  if (lista==NULL) return nodo;
  lista->next = inserisciLista(nodo, lista->next);
  return lista;
}

persona *rimuoviNodo(persona *lista, persona *nodo)
{
  persona *tmp;
  
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

void freeLista(persona *lista)
{
  if (lista != NULL) {
    freeLista(lista->next);
    freeNodo(lista);
  }
}


void scriviLista(persona *lista)
{
  int i;
  
  while (lista!=NULL) {
    printf("%s %s %d %d %d ",lista->Nome,lista->Cognome, lista->Peso, lista->Altezza, lista->Eta);
    printf("\n");
    lista = lista->next;
  }
}

persona *leggiFile(FILE *fp, persona *lista)
{
  char nome[30], cognome[30];
  int peso, altezza, eta;
  persona *nodo;

  while(fscanf(fp,"%s%s%d%d%d",nome,cognome,&peso,&altezza,&eta)==5){
    nodo = nuovoNodo(nome,cognome,peso,altezza,eta);
    if (nodo==NULL) gestioneErrore();
    lista = inserisciLista(nodo, lista);
  }
  return lista;
}


void scriviFile(FILE *fp, persona *lista)
{
  int *buffer, eta, peso, altezza, i, j, count;
  persona*ptr1, *ptr2;

  while (lista!=NULL) {
    eta = lista->Eta;
    peso = lista->Peso;
    altezza = lista->Altezza;
    fprintf(fp,"%s %s %d %d %d ", lista->Nome, lista->Cognome, peso, altezza, eta);

    fprintf(fp,"\n");
    lista = lista->next;
  }
}
persona *rimuoviPersona(persona *lista, int soglia)
{
  if (lista==NULL) return lista;
  if (lista->Peso<soglia) {
    lista = rimuoviNodo(lista, lista);
    lista = rimuoviPersona(lista, soglia);
  } else lista->next = rimuoviPersona(lista->next, soglia);
  
  return lista;
}