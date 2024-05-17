#include "../headers/tipuri_de_date.h"
#include <stdio.h>
#include <string.h>
#include "../headers/functii_cozi.h"
#define LUNGIME_LINIE 67
void afisare_echipe (Echipa *lista_echipa,int nr)
{ Echipa *p=lista_echipa;
  for (int i=0;p!=NULL&&i<nr;i++) ///p!=NULL pentru a se opri in cazul in care se apeleaza un nr > nr_echipe
    { printf("Echipa %d:\n",i+1);
      printf("%s\n",p->nume_echipa);
      printf("Punctaj total:%f\n",p->punctaj_total);
      printf("Nr jucatori: %d\n",p->nr_jucatori);
      for (int j=0;j<p->nr_jucatori;j++)
         printf("%s|%s %d\n",p->jucatori[j].nume, p->jucatori[j].prenume,p->jucatori[j].puncte);
     p=p->next;


    }

}

