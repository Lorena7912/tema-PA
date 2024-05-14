#include <stdio.h>
#include <stdlib.h>
#include "./headers/tipuri_de_date.h"
#include "./headers/functii_cerinte.h"
#define NR_CERINTE 5
int main(int argc, char *argv[])
{
    FILE *cerinte, *date, *rezultate;
    // poate faci o functie separata pentru deschiderea fisierelor;
    cerinte = fopen(argv[1], "rt");
    if (cerinte == NULL)
        {  printf("1");
            eroare();
        }
    date = fopen(argv[2], "rt");
    if (date == NULL)
        {printf("2");
        eroare();
        }
    rezultate = fopen(argv[3], "wt");
    if (rezultate == NULL)
        {printf("3");
        eroare();
        }
    int c[NR_CERINTE];
    for (int i = 0; i < NR_CERINTE; i++)
        fscanf(cerinte, "%d", &c[i]);
    int nr_echipe=0;
    Echipa *lista_echipe= citeste_echipele(&date,&nr_echipe);
    if(c[0]==1)
     Task1(&rezultate,lista_echipe);
     /*for (Echipa *p=lista_Echipa;p!=NULL;p=p->next)
    { 

     printf("%s",p->nume_echipa);
     printf("%s %d\n",p->jucatori[2].nume,p->nr_jucatori);
     
    }*/

    
    return 0;
}