typedef struct Jucator Jucator;
typedef struct Echipa Echipa;

struct  Jucator
{
    char *prenume;
    char *nume;
    int puncte;

};

struct Echipa
{  char *nume_echipa;
   int nr_jucatori;
   float punctaj_total;
   Jucator *jucatori;
   struct Echipa *next;
};
