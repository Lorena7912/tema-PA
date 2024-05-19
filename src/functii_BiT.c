#include "../headers/tipuri_de_date.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define TOP_FINAL 8
BiTree *newNode(Echipa *echipa)
{
    BiTree *node = (BiTree *)malloc(sizeof(BiTree));
    node->echipa = echipa; ///!
    node->left = node->right = NULL;
    return node;
}
BiTree *insert(BiTree *node, Echipa *echipa)
{
    if (node == NULL)
        return newNode(echipa);
    if (echipa->punctaj_total < node->echipa->punctaj_total ||
        (fabs(echipa->punctaj_total - node->echipa->punctaj_total) < 0.01 && strcmp(echipa->nume_echipa, node->echipa->nume_echipa) < 0))
        node->left = insert(node->left, echipa);

    if (echipa->punctaj_total > node->echipa->punctaj_total ||
       (fabs(echipa->punctaj_total - node->echipa->punctaj_total) < 0.01 && strcmp(echipa->nume_echipa, node->echipa->nume_echipa) > 0))
        node->right = insert(node->right, echipa);

    return node;
}

void afisare_BTS(FILE **rezultate,BiTree *node)
{
    if (node!=NULL)
    {  afisare_BTS(&*rezultate,node->right);
       fprintf(*rezultate, "%-34s-  %.2f\n", node->echipa->nume_echipa, node->echipa->punctaj_total);
       afisare_BTS(&*rezultate,node->left);
    }

}