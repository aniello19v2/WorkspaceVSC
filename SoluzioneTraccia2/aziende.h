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


