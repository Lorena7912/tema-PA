#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/tipuri_de_date.h"
#define LUNGIME_MAXIMA 50
void push(Echipa **top, Echipa *echipa) 
{
    Echipa *newNode = (Echipa *)malloc(sizeof(Echipa));
    newNode->nume_echipa = (char *)malloc(LUNGIME_MAXIMA * sizeof(char));
    strcpy(newNode->nume_echipa, echipa->nume_echipa);
    newNode->nr_jucatori = echipa->nr_jucatori;
    newNode->punctaj_total = echipa->punctaj_total;
    newNode->jucatori = (Jucator *)malloc(echipa->nr_jucatori * sizeof(Jucator));
    newNode->jucatori = echipa->jucatori;

    newNode->next=*top;
    *top=newNode;
}