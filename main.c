#include <stdio.h>
#include <stdlib.h>
#include "./headers/tipuri_de_date.h"
#include "./headers/functii_cerinte.h"
#include "./headers/functii_liste.h"
#include "./headers/altele.h"
#include "./headers/functii_cozi.h"
#define NR_CERINTE 5
int main(int argc, char *argv[])
{
    FILE *cerinte, *date;
    cerinte = fopen(argv[1], "rt");
    if (cerinte == NULL)
        eroare();
    date = fopen(argv[2], "rt");
    if (date == NULL)
        eroare();
    int c[NR_CERINTE];
    for (int i = 0; i < NR_CERINTE; i++)
        fscanf(cerinte, "%d", &c[i]);
    int nr_echipe = 0;
    Echipa *lista_echipe = citeste_echipele(&date, &nr_echipe);
    if (c[0] == 1)
        Task1(argv[3], lista_echipe);
    if (c[1] == 1)
        Task2(argv[3], &lista_echipe, &nr_echipe);
    Echipa *ultimele8=NULL;
    if (c[2] == 1)
        Task3(argv[3], lista_echipe, nr_echipe, &ultimele8);
    BiTree *BTS=NULL;
    if (c[3]==1)
    Task4(argv[3],ultimele8,&BTS);
    AVLTree *AVL=NULL;
    if (c[4]==1)
    Task5(argv[3],ultimele8,&AVL);
    return 0;
}