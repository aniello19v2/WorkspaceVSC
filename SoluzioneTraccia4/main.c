#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "studente.h"
  
int main()
{
  struct studente *lista=NULL;
  FILE *fp;

  fp = fopen("dati.txt","r");
  lista = leggiFile(fp, lista);
  fclose(fp);
  
  scriviLista(lista);

  lista = rimuovi18(lista);
  scriviLista(lista);

  fp = fopen("dati2.txt","w");
  scriviFile(fp, lista);
  fclose(fp);

  freeLista(lista);
}
