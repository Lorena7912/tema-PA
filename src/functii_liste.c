#include "../headers/tipuri_de_date.h"
#include "../headers/functii_cerinte.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LUNGIME_MAXIMA 50
void addAtBeginning(Echipa **lista_echipe,char nume_echipa[],int nr_jucatori,float punctaj,Jucator *aux)
{ Echipa *newNode=(Echipa *)malloc(sizeof(Echipa));

  newNode->nume_echipa=(char*)malloc(LUNGIME_MAXIMA*sizeof(char));
  strcpy(newNode->nume_echipa,nume_echipa);
  newNode->nr_jucatori=nr_jucatori;
  newNode->punctaj_total=punctaj;
  newNode->jucatori=(Jucator*)malloc(nr_jucatori*sizeof(Jucator));
  for (int i=0;i<nr_jucatori;i++)
  newNode->jucatori[i]=aux[i];

  newNode->next=*lista_echipe;
  *lista_echipe=newNode;
}

void eliminare_echipa (Echipa **lista_echipe,float min1)
{ 
  if (lista_echipe==NULL)
      return;
  Echipa *p=*lista_echipe;
  if ((*lista_echipe)->punctaj_total==min1)
  { *lista_echipe=(*lista_echipe)->next;
    free(p);
    return;
  }
  Echipa *prev=*lista_echipe;
  while (p!=NULL)
  if (p->punctaj_total!=min1)
  { prev=p;
   p=p->next;
  }
  else
  { prev->next=p->next;
    free(p);
    return;

  }


}