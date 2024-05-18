#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/tipuri_de_date.h"
#include "../headers/functii_liste.h"
#include "../headers/functii_cozi.h"
#include "../headers/altele.h"
#include "../headers/functii_stive.h"
#include <math.h>
#define LUNGIME_MAXIMA 50
#define TOP_FINAL 8
void eroare()
{ /// revenit la aceasta functie
  printf("Eroare");
  exit(1);
}

Echipa *citeste_echipele(FILE **date, int *nr_echipe)
{
  Echipa *lista_echipe = NULL;
  fscanf(*date, "%d", nr_echipe);
  for (int i = 0; i < *nr_echipe; i++)
  {
    int nr_jucatori;
    char nume_echipa[LUNGIME_MAXIMA];
    fscanf(*date, "%d ", &nr_jucatori);
    Jucator *aux = (Jucator *)malloc(nr_jucatori * sizeof(Jucator));
    if (aux == NULL)
    {
      printf("4");
      eroare();
    }
    fgets(nume_echipa, LUNGIME_MAXIMA, *date);
    for (int j = 0; j < nr_jucatori; j++)
    {
      char linie[LUNGIME_MAXIMA];
      aux[j].nume = (char *)malloc(LUNGIME_MAXIMA * sizeof(char));
      aux[j].prenume = (char *)malloc(LUNGIME_MAXIMA * sizeof(char));
      if (aux[j].nume == NULL || aux[j].prenume == NULL)
      {
        printf("5");
        eroare();
      }
      fscanf(*date, "%s ", aux[j].nume);
      fscanf(*date, "%s ", aux[j].prenume);
      fscanf(*date, "%d", &aux[j].puncte);
      /*getc(*date);*/
    }
    getc(*date); // posibil bug: numele echipelor au la sfarsit '\n'

    addAtBeginning(&lista_echipe, nume_echipa, nr_jucatori, 0.0, aux);
    free(aux); // momentan; plan:creezi o functie care elibereaza spatiul pentru tot, inclusiv memoria alocata pentru nume si prenume;
  }
  return lista_echipe;
}

void Task1(char *argv, Echipa *lista_echipe)
{
  FILE *rezultate = fopen(argv, "wt");
  if (rezultate == NULL)
    eroare();
  for (Echipa *p = lista_echipe; p != NULL; p = p->next)
  {
    p->nume_echipa[strlen(p->nume_echipa) - 1] = '\0';
    fprintf(rezultate, "%s\n", p->nume_echipa);
  }
  fclose(rezultate);
}
float punctaj_minim(Echipa *lista_echipe, int nr_echipe)
{
  float min1 = lista_echipe->punctaj_total;
  Echipa *p = lista_echipe;
  for (int i = 0; i < nr_echipe; i++)
  {
    if (min1 > p->punctaj_total)
      min1 = p->punctaj_total;
    p = p->next;
  }
  return min1;
}
int putere2_max(int nr_echipe)
{
  int p2_max = 1;
  while (p2_max * 2 <= nr_echipe)
    p2_max = p2_max * 2;
  return p2_max;
}

void punctaj_total(Echipa **lista_echipa)
{
  for (Echipa *p = *lista_echipa; p != NULL; p = p->next)
  {
    for (int i = 0; i < p->nr_jucatori; i++)
      p->punctaj_total += p->jucatori[i].puncte;
    p->punctaj_total /= p->nr_jucatori;
  }
}

void Task2(char *argv, Echipa **lista_echipa, int *nr_echipe)
{
  FILE *rezultate = fopen(argv, "wt");
  if (rezultate == NULL)
    eroare();
  punctaj_total(lista_echipa);
  int nr_ramase = putere2_max(*nr_echipe);
  while (*nr_echipe > nr_ramase)
  {
    float min1 = punctaj_minim(*lista_echipa, *nr_echipe);
    eliminare_echipa(lista_echipa, min1);
    (*nr_echipe)--;
  }

  for (Echipa *p = *lista_echipa; p != NULL; p = p->next)
  {
    fprintf(rezultate, "%s\n", p->nume_echipa);
  }
  fclose(rezultate); /// foarte important!
}
void spatii(FILE **rezultate, int nr)
{
  for (int i = 0; i < nr; i++)
    fprintf(*rezultate, " ");
}
void meciuri(FILE **rezultate, Queue *q, Echipa **castigatori, Echipa **invinsi, int nr_echipe) /// pare sa  mearga(mai putin afisarea si eliminarea spatiilor)
{
  Echipa *echipa1;
  Echipa *echipa2;
  for (int i = 0; i < nr_echipe / 2; i++)
  {
    echipa1 = deQueue(q);
    echipa2 = deQueue(q);
    /// verifica daca mai exista vreun spatiu la sfarsit si daca exista, elimina-l!
   /**if (echipa1->nume_echipa[strlen(echipa1->nume_echipa) - 1] == ' ') ///'\n' a fost eliminat in Task1
      echipa1->nume_echipa[strlen(echipa1->nume_echipa) - 1] = '\0';

    if (echipa2->nume_echipa[strlen(echipa2->nume_echipa) - 1] == ' ') ///'\n' a fost eliminat in Task1
      echipa2->nume_echipa[strlen(echipa2->nume_echipa) - 1] = '\0';
*/
    fprintf(*rezultate, "%s - %s\n", echipa1->nume_echipa, echipa2->nume_echipa); /// de revenit aici ///Afisarea

    if (echipa1->punctaj_total > echipa2->punctaj_total || fabs(echipa1->punctaj_total-echipa2->punctaj_total)<0.001)
    {
      echipa1->punctaj_total += 1.0;
      push(castigatori, echipa1);
    }
    else
    {
      
      push(invinsi, echipa2); // invinsi/castigatori sunt de de tip Echipa **
    }
  }
}

void Task3(char *argv, Echipa *lista_echipe, int nr_echipe, Echipa **ultimele8)
{ FILE *rezultate = fopen(argv, "at");
printf("salut!");
    if (rezultate == NULL)
      eroare();
  Queue *q = createQueue();
  Echipa *invinsi = NULL;
  Echipa *castigatori = NULL;
  for (Echipa *p = lista_echipe; p != NULL; p = p->next)
    {enQueue(q, p);
     printf("buna!");
    }
  for (Echipa *p=q->front;p!=NULL;p=p->next)
   printf("%s\n",p->nume_echipa);
   ///pana aici e ok, functioneaza
   ///de aici nu mai functioneaza
  int cnt_runda = 1;
  while (nr_echipe > 1)
  {
    printf("Nr echipe: %d\n",nr_echipe);
    fprintf(rezultate, "Runda: %d", cnt_runda);
    meciuri(&rezultate, q, &castigatori, &invinsi, nr_echipe);
    printf("buna!2");
    if(invinsi==NULL)
    printf("Stiva de invinsi este NULL!"); ///Stiva INVINSI NU ESTE NULL dupa apelul functiei meciuri
    else 
    for (Echipa *p=invinsi;p!=NULL;p=p->next) 
    printf("I: %s\n",p->nume_echipa); ///dar de ce imi afiseaza doar 11, cand ar trebui sa fie 16
    if (castigatori==NULL)
    printf("Stiva de castigatori este NULL!"); 
    else
    for (Echipa *p=castigatori;p!=NULL;p=p->next)
    printf("C: %s\n",p->nume_echipa); ///Stiva CASTIGATORI NU ESTE NULL dupa apelul functiei meciuri
    ///dar de ce imi afiseaza doar 5, cand ar trebui sa fie 16;
    deleteStack(&invinsi);
    nr_echipe = nr_echipe / 2;
    ///---afisarea
    fprintf(rezultate, "---WINNERS OF ROUND NO:%d:\n", cnt_runda);
    int i = 0;
    Echipa *copie = castigatori;
    while (i < nr_echipe)
    {  
        if (copie==NULL)
          {printf("\n%d %d\n",cnt_runda,nr_echipe);
          exit(100);
          }
      fprintf(rezultate, "%s -%f\n", copie->nume_echipa, copie->punctaj_total); ///bug: atunci cand nr_echipe devine 16 
      ///(prima runda) in test7 copie este NULL, ceea ce cauzeaza atunci cand se incearca accesarea membrilor 
      ///SEGMENTATION FAULT 
      ///copie nu ar trebui sa fie NULL, deoarece asta inseamna ca stiva de castigatori este NULL...
      ///ceea ce indica posibile probleme cu punerea in stive, trasmitere a parametrilor...dar stivele INVINSI si CASTIGATORI
      ///NU SUNT NULL dupa iesirea din functia meciuri (care, de altfel, nu face bine castigatorii,chiar daca compara echipele
      ///care trebuie) 
      ///(chiar daca nu au in total 16 cu 16 elemente, alt bug...)
     /*if (nr_echipe == TOP_FINAL)
        addAtBeginning(ultimele8, copie->nume_echipa, copie->nr_jucatori, copie->punctaj_total, copie->jucatori);*/
      copie = copie->next;
      i++;
    }
    /// partea in care dai enQueue inapoi
    printf("buna!");
    for (int i = 0; i < nr_echipe; i++)
    {
      Echipa *aux = pop(&castigatori);
      enQueue(q, aux);
    }
    
    cnt_runda++;
  }
  fclose(rezultate);
}