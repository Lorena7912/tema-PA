#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/tipuri_de_date.h"
#include "../headers/functii_liste.h"
#define LUNGIME_MAXIMA 50
void eroare()
{ /// revenit la aceasta functie
    printf("Eroare");
    exit(1);
}
Echipa *citeste_echipele(FILE **date, int *nr_echipe)
{   Echipa *lista_echipe=NULL;
    fscanf(*date, "%d",nr_echipe);
    for (int i = 0; i < *nr_echipe; i++)
    { int nr_jucatori;
      char nume_echipa[LUNGIME_MAXIMA];
      fscanf(*date,"%d ",&nr_jucatori);
      Jucator *aux=(Jucator*)malloc(nr_jucatori*sizeof(Jucator));
      if(aux==NULL)
         {printf("4");
         eroare();
         }
      fgets(nume_echipa,LUNGIME_MAXIMA,*date);
      for (int j=0;j<nr_jucatori;j++)
      { char linie[LUNGIME_MAXIMA];
        aux[j].nume=(char*)malloc(LUNGIME_MAXIMA*sizeof(char));
        aux[j].prenume=(char*)malloc(LUNGIME_MAXIMA*sizeof(char));
        if(aux[j].nume==NULL||aux[j].prenume==NULL)
          {printf("5");
          eroare();
          }
        fscanf(*date,"%s ",aux[j].nume);
        fscanf(*date,"%s ",aux[j].prenume);
        fscanf(*date,"%d",&aux[j].puncte);
        /*getc(*date);*/
      } 
      getc(*date); //posibil bug: numele echipelor au la sfarsit '\n'
      /*nume_echipa[strlen(nume_echipa)-1]=NULL; ///da peste cap citirea/afisarea cu printf si habar nu am unde*/
      addAtBeginning(&lista_echipe,nume_echipa,nr_jucatori,0.0,aux);
      free(aux);//momentan; plan:creezi o functie care elibereaza spatiul pentru tot, inclusiv memoria alocata pentru nume si prenume;
    }
        return lista_echipe;
}

void Task1(FILE **rezultate,Echipa *lista_echipe)
{ for (Echipa *p=lista_echipe;p!=NULL;p=p->next)
  { p->nume_echipa[strlen(p->nume_echipa)-1]=NULL;
    fprintf(*rezultate,"%s\n",p->nume_echipa);
  }
}