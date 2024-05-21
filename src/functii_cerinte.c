#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/tipuri_de_date.h"
#include "../headers/functii_liste.h"
#include "../headers/functii_cozi.h"
#include "../headers/altele.h"
#include "../headers/functii_stive.h"
#include "../headers/functii_BiT.h"
#include <math.h>
#define LUNGIME_MAXIMA 50
#define TOP_FINAL 8
void eroare()
{ /// revenit la aceasta functie
  printf("Eroare");
  exit(1);
}
void elim_c(char *s)
{
  int i = strlen(s);
  i--;
  while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\r') && i >= 0) ///!elimin si \r (cr),daca exista,altfel afecteaza afisarea meciurilor
  {
    s[i] = '\0';
    i--;
  }
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
    elim_c(nume_echipa); ///! linie importanta!
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
    /*p->nume_echipa[strlen(p->nume_echipa) - 1] = '\0';*/ ///!sa nu fie stearsa!!!! duce la picarea tuturor testelor prin neafisarea corecta!*/
    /*elim_c(p->nume_echipa);///sau cu aceasta functie*/
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

void meciuri(FILE **rezultate, Queue *q, Echipa **castigatori, Echipa **invinsi, int nr_echipe) /// pare sa  mearga(mai putin afisarea si eliminarea spatiilor)
{
  Echipa *echipa1;
  Echipa *echipa2;
  for (int i = 0; i < nr_echipe / 2; i++)
  {
    echipa1 = deQueue(q);
    echipa2 = deQueue(q);
    if (echipa1->nume_echipa[strlen(echipa1->nume_echipa) - 1] == '\n')
      echipa1->nume_echipa[strlen(echipa1->nume_echipa) - 1] = '\n';
    fprintf(*rezultate, "%-33s-", echipa1->nume_echipa);
    fprintf(*rezultate, "%33s\n", echipa2->nume_echipa); /// de revenit aici ///Afisarea

    if (echipa1->punctaj_total > echipa2->punctaj_total)
    {
      echipa1->punctaj_total += 1.0;
      push(castigatori, echipa1);
      push(invinsi, echipa2);
    }
    else
    {
      echipa2->punctaj_total += 1.0;
      push(castigatori, echipa2);
      push(invinsi, echipa1);
    }
  }
}

void Task3(char *argv, Echipa *lista_echipe, int nr_echipe, Echipa **ultimele8)
{
  FILE *rezultate = fopen(argv, "at");
  if (rezultate == NULL)
    eroare();
  Queue *q = createQueue();
  Echipa *invinsi = NULL, *castigatori = NULL;
  for (Echipa *p = lista_echipe; p != NULL; p = p->next)
    enQueue(q, p);
  int cnt_runda = 1;
  while (nr_echipe > 1)
  {
    fprintf(rezultate, "\n--- ROUND NO:%d\n", cnt_runda);
    meciuri(&rezultate, q, &castigatori, &invinsi, nr_echipe);
    deleteStack(&invinsi);
    nr_echipe = nr_echipe / 2;
    fprintf(rezultate, "\nWINNERS OF ROUND NO:%d\n", cnt_runda);
    int i = 0;
    Echipa *copie = castigatori;
    while (i < nr_echipe) /// bug vechi SEGMENTATION FAULT
    {
      fprintf(rezultate, "%-34s-  %.2f\n", copie->nume_echipa, copie->punctaj_total);
      if (nr_echipe == TOP_FINAL)
        addAtBeginning(ultimele8, copie->nume_echipa, copie->nr_jucatori, copie->punctaj_total, copie->jucatori);
      copie = copie->next;
      i++;
    }
    for (int i = 0; i < nr_echipe; i++)
    {
      Echipa *aux = pop(&castigatori);
      enQueue(q, aux);
    }
    cnt_runda++;
  }
  fclose(rezultate);
}

void Task4(char *argv, Echipa *ultimele8, BiTree **BTS)
{
  FILE *rezultate = fopen(argv, "at");
  if (rezultate == NULL)
    eroare();
  while (ultimele8 != NULL)
  {
    *BTS = insert(*BTS, ultimele8);
    ultimele8 = ultimele8->next;
  }
  fprintf(rezultate, "\nTOP 8 TEAMS:\n");
  afisare_BTS(&rezultate, *BTS);
  fclose(rezultate);
}

void Task5(char *argv,Echipa *ultimele8,AVLTree **AVL)
{
  FILE *rezultate = fopen(argv, "at");
  if (rezultate == NULL)
    eroare();
  for (Echipa *p=ultimele8;p!=NULL;p=p->next)
     *AVL=insert_AVL(*AVL,p);

  fprintf(rezultate, "\nTHE LEVEL 2 TEAMS ARE:\n");
  afisare_nivel2(&rezultate,*AVL);
  fclose(rezultate);
}