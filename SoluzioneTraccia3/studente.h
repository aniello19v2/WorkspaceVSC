#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct studente{
  char nome[256];
  char cognome[256];
  int matricola;
  char esame[256];
  int voto;
  struct studente *next;
};

void gestioneErrore();
struct studente *leggiFile(FILE *fp, struct studente *lista);
void scriviLista(struct studente *lista);
struct studente *rimuovi18(struct studente *lista);
void scriviFile(FILE *fp, struct studente *lista);
void freeLista(struct studente *lista);


