typedef struct Jucator Jucator;
typedef struct Echipa Echipa;
typedef struct Queue Queue;
typedef struct BiTree BiTree;
typedef struct AVLTree AVLTree;
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

struct Queue
{
    struct Echipa *front, *rear;
};

struct BiTree
{ Echipa *echipa;
 struct BiTree *left, *right;
};

struct AVLTree
{ Echipa *echipa;
  int height;
 struct AVLTree *left,*right;
};