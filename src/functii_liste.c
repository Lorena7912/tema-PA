#include "../headers/tipuri_de_date.h"
#include "../headers/functii_cerinte.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LUNGIME_MAXIMA 50
void addAtBeginning(Echipa **lista_echipe,char nume_echipa[],int nr_jucatori,int punctaj,Jucator *aux)
{ Echipa *newNode=(Echipa *)malloc(sizeof(Echipa));

  newNode->nume_echipa=(char*)malloc(strlen(nume_echipa)*sizeof(char));
  strcpy(newNode->nume_echipa,nume_echipa);
  newNode->nr_jucatori=nr_jucatori;
  newNode->punctaj_total=punctaj;
  newNode->jucatori=(Jucator*)malloc(nr_jucatori*sizeof(Jucator));
  for (int i=0;i<nr_jucatori;i++)
  newNode->jucatori[i]=aux[i];

  newNode->next=*lista_echipe;
  *lista_echipe=newNode;
}