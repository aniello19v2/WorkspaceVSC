#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "persona.h"

int main()
{
  struct persona *lista=NULL;
  FILE *fp;


  fp = fopen("dati.txt","r");
  if (fp == NULL) gestioneErrore();
  lista = leggiFile(fp, lista);
  fclose(fp);

  scriviLista(lista);

  lista = rimuoviPesoMinore(lista,12);
  scriviLista(lista);

  lista = duplicaElementi(lista);
  scriviLista(lista);

  fp = fopen("dati2.txt","w");
  scriviFile(fp, lista);
  fclose(fp);



  freeLista(lista);

}
