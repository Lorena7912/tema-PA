#include "../headers/tipuri_de_date.h"
#include "../headers/functii_cerinte.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define LUNGIME_MAXIMA 50
void addAtBeginning(Echipa **lista_echipe, char nume_echipa[], int nr_jucatori, int punctaj, Jucator *aux)
{
  Echipa *newNode = (Echipa *)malloc(sizeof(Echipa));

  newNode->nume_echipa = (char *)malloc(strlen(nume_echipa) * sizeof(char));
  strcpy(newNode->nume_echipa, nume_echipa);
  newNode->nr_jucatori = nr_jucatori;
  newNode->punctaj_total = punctaj;
  newNode->jucatori = (Jucator *)malloc(nr_jucatori * sizeof(Jucator));
  for (int i = 0; i < nr_jucatori; i++)
    newNode->jucatori[i] = aux[i];

  newNode->next = *lista_echipe;
  *lista_echipe = newNode;
}

void punctaj_echipe(Echipa **lista_echipa)  ///Problema nu este aici!
{
  for (Echipa *p = *lista_echipa; p != NULL; p = p->next)
  { /*printf("Nr jucatori:%d |",p->nr_jucatori);*/
    for (int i = 0; i < p->nr_jucatori; i++)
      p->punctaj_total = p->punctaj_total+p->jucatori[i].puncte;
    /*printf(" suma: %f\n ",p->punctaj_total);*/
    p->punctaj_total = p->punctaj_total / p->nr_jucatori;
    /*printf("%f\n",p->punctaj_total);*/
  }
}

void eliminare_echipa(Echipa **lista_echipe,int min1)
{
  /// 3 cazuri+caz 0 : 0. lista e goala (caz in care nu facem nimic)
  /// 1. head este minim 2. min se afla intre head si ultimul element 3. min este ultimul element +eliberare memorie
  if ((*lista_echipe) == NULL)
    return;
  Echipa *p = *lista_echipe;
  if (fabs((*lista_echipe)->punctaj_total-min1)<0.01)
  {
    *lista_echipe = (*lista_echipe)->next;
    free(p); /// sau free_echipa (cu totul (inclusiv tabloul unidimensional de jucatori+nume_echipa))
    return;
  }
  Echipa  *prev=*lista_echipe;
  while (p->next!=NULL)
   if (fabs(p->punctaj_total-min1)>0.01)
   { prev=p;
     p=p->next;
   }
   else
   {
    prev->next=p->next;
    free(p); ///sau free_echipa
    return ;
   }
  if (fabs(p->punctaj_total - min1) < 0.01) {
        prev->next = NULL;
        free(p); // sau free_echipa
    }
}