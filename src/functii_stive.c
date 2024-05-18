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

    newNode->next = *top;
    *top = newNode;
}

// deleteStack si pop
Echipa *pop(Echipa **top)
{
    if ((*top)==NULL)
        return NULL; ///!
    Echipa *temp = (*top);
    Echipa *aux = (Echipa *)malloc(sizeof(Echipa));
    aux->nume_echipa = (char *)malloc(LUNGIME_MAXIMA * sizeof(char));
    strcpy(aux->nume_echipa, temp->nume_echipa);
    aux->nr_jucatori = temp->nr_jucatori;
    aux->punctaj_total = temp->punctaj_total;
    aux->jucatori = (Jucator *)malloc(temp->nr_jucatori * sizeof(Jucator));
    aux->jucatori = temp->jucatori;
    aux->next = NULL; /// pentru a "izola elementul"
    (*top) = (*top)->next;
    free(temp);
    return aux;
}

void deleteStack(Echipa **top)
{
    Echipa *temp;
    while ((*top) != NULL)
    {
        temp = *top;
        (*top) = (*top)->next;
        free(temp);
    }
}