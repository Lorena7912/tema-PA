#include "../headers/tipuri_de_date.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../headers/functii_cozi.h"
#define TOP_FINAL 8
BiTree *newNode(Echipa *echipa)
{
    BiTree *node = (BiTree *)malloc(sizeof(BiTree));
    node->echipa = echipa; ///!
    node->left = node->right = NULL;
    return node;
}

int mai_mic(Echipa *echipa1, Echipa *echipa2)
{
    return (echipa1->punctaj_total < echipa2->punctaj_total ||
            (fabs(echipa1->punctaj_total - echipa2->punctaj_total) < 0.001 && strcmp(echipa1->nume_echipa, echipa2->nume_echipa) < 0));
}

int mai_mare(Echipa *echipa1, Echipa *echipa2)
{
    return (echipa1->punctaj_total > echipa2->punctaj_total ||
            (fabs(echipa1->punctaj_total - echipa2->punctaj_total) < 0.001 && strcmp(echipa1->nume_echipa, echipa2->nume_echipa) > 0));
}
BiTree *insert(BiTree *node, Echipa *echipa)
{
    if (node == NULL)
        return newNode(echipa);
    if (mai_mic(echipa, node->echipa))
        node->left = insert(node->left, echipa);

    if (mai_mare(echipa, node->echipa))
        node->right = insert(node->right, echipa);

    return node;
}

void afisare_BTS(FILE **rezultate, BiTree *node)
{
    if (node != NULL)
    {
        afisare_BTS(&*rezultate, node->right);
        fprintf(*rezultate, "%-34s-  %.2f\n", node->echipa->nume_echipa, node->echipa->punctaj_total);
        afisare_BTS(&*rezultate, node->left);
    }
}

int nodeHeight(AVLTree *root)
{
    if (root == NULL)
        return -1;
    else
        return root->height;
}

int max(int a, int b)
{
    return ((a > b) ? a : b);
}
AVLTree *rightRotation(AVLTree *z)
{
    AVLTree *y = z->left;
    AVLTree *T3 = y->right;
    // roteste
    y->right = z;
    z->left = T3;
    // modifica inaltimile pentru z si y
    z->height = max(nodeHeight(z->left), nodeHeight(z->right)) + 1;
    y->height = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;
    return y;
}

AVLTree *leftRotation(AVLTree *z)
{
    AVLTree *y = z->right;
    AVLTree *T2 = y->left;
    y->left = z;
    z->right = T2;
    z->height = max(nodeHeight(z->left), nodeHeight(z->right)) + 1;
    y->height = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;
    return y;
}
AVLTree *LRRotation(AVLTree *Z)
{
    Z->left = leftRotation(Z->left);
    return rightRotation(Z);
}
AVLTree *RLRotation(AVLTree *Z)
{
    Z->right = rightRotation(Z->right);
    return leftRotation(Z);
}
AVLTree *insert_AVL(AVLTree *node, Echipa *echipa)
{
   
    if (node == NULL)
    {
        node = (AVLTree *)malloc(sizeof(AVLTree));
        node->echipa = echipa;
        node->height = 0;
        node->left = node->right = NULL;
        return node;
    }
    if (mai_mic(echipa, node->echipa))
    {
        node->left = insert_AVL(node->left, echipa);
        
    }
    else if (mai_mare(echipa, node->echipa))
        node->right = insert_AVL(node->right, echipa);
    else
        return node;
    node->height = 1 + max(nodeHeight(node->left), nodeHeight(node->right));

    int k = (nodeHeight(node->left) - nodeHeight(node->right));
    /// echilibrare
    if (k > 1 && mai_mic(echipa, node->left->echipa))
        return rightRotation(node);

    if (k < -1 && mai_mare(echipa, node->right->echipa))
        return leftRotation(node);

    if (k > 1 && mai_mare(echipa, node->left->echipa))
        return LRRotation(node);

    if (k < -1 && mai_mic(echipa, node->right->echipa))
        return RLRotation(node);

    return node;
}

void afisare_nivel2(FILE **rezultate, AVLTree *root)
{ ///!momentan
    AVLTree *aux1, *aux2;
    aux1 = root->left;
    aux2 = root->right;
    if (aux2->right != NULL)
        fprintf(*rezultate, "%s\n", aux2->right->echipa->nume_echipa);
    if (aux2->left != NULL)
        fprintf(*rezultate, "%s\n", aux2->left->echipa->nume_echipa);
    if (aux1->right != NULL)
        fprintf(*rezultate, "%s\n", aux1->right->echipa->nume_echipa);
    if (aux1->left != NULL)
        fprintf(*rezultate, "%s\n", aux1->left->echipa->nume_echipa);
}