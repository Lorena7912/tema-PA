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

    newNode->nume_echipa = (char *)malloc((strlen(echipa->nume_echipa) + 1) * sizeof(char));
    strcpy(newNode->nume_echipa, echipa->nume_echipa);
    newNode->nr_jucatori = echipa->nr_jucatori;
    newNode->punctaj_total = echipa->punctaj_total;
    newNode->jucatori = (Jucator *)malloc(echipa->nr_jucatori * sizeof(Jucator));
    newNode->jucatori = echipa->jucatori;
    newNode->next = NULL;

    if (q->rear == NULL)
        q->rear = newNode;
    else
    {
        (q->rear)->next = newNode;
        q->rear = newNode;
    }

    if (q->front == NULL)
    {
        q->front = q->rear;
    }
}
int isEmpty(Queue *q)
{
    return (q->front == NULL);
}

Echipa *deQueue(Queue *q)
{
    if (isEmpty(q))
        return NULL; ///!
    Echipa *aux = q->front;

    Echipa *val = (Echipa *)malloc(sizeof(Echipa));
    val->nume_echipa = (char *)malloc((strlen(aux->nume_echipa) + 1) * sizeof(char));
    strcpy(val->nume_echipa, aux->nume_echipa);
    val->nr_jucatori = aux->nr_jucatori;
    val->punctaj_total = aux->punctaj_total;
    val->jucatori = (Jucator *)malloc(aux->nr_jucatori * sizeof(Jucator));
    val->jucatori = aux->jucatori;
    val->next = NULL;

    q->front = (q->front)->next;
    free(aux);
    return val;
}
