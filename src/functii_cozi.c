#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/tipuri_de_date.h"
#define LUNGIME_MAXIMA 50
Queue *createQueue()
{
    Queue *q;
    q = (Queue *)malloc(sizeof(Queue));
    if (q == NULL)
        return NULL;
    q->front = q->rear = NULL;
    return q;
}

void enQueue(Queue *q, Echipa *echipa)
{
    Echipa *newNode = (Echipa *)malloc(sizeof(Echipa));
    /// valori nou nod + next NULL
    /// daca nu exista niciun element in coada: q->rear (respecta FIFO ); altfel, (q->rear)->next primeste newNode si newnode devine q->rear
    /// daca exista un singur element in coada (q->front==NULL) q->front=q->rear (va intra mai intai pe else niciun element)
    newNode->nume_echipa = (char *)malloc(LUNGIME_MAXIMA * sizeof(char));
    strcpy(newNode->nume_echipa, echipa->nume_echipa);
    newNode->nr_jucatori = newNode->nr_jucatori;
    newNode->punctaj_total = echipa->punctaj_total;
    newNode->jucatori = (Jucator *)malloc(echipa->nr_jucatori * sizeof(Jucator));
    newNode->jucatori = echipa->jucatori;
    newNode->next = NULL;

    if (q->rear == NULL)
        q->rear = newNode;
    else
    {   (q->rear)->next=newNode;
        q->rear=newNode;
    }

    if(q->front==NULL)
    {
        q->front=q->rear;

    }
}
