#ifndef __AVL__
#define __AVL__


typedef struct noeud{

int cle;
struct noeud*gauche;
struct noeud*droit;
struct noeud*parent;
int hauteur;

}noeud;



noeud*create_n(int cle);
void infixe(noeud*x);
void prefixe(noeud*x);
void postfixe(noeud*x);
noeud*recherche_r(noeud*x,int k);
noeud*recherche_i(noeud*x,int k);
void afficher(noeud*x);

noeud*min_b(noeud*x);
noeud*max_b(noeud*x);
int hauteur(noeud*x);

noeud*successor(noeud*x);
noeud*predecessor(noeud*x);

void insertion(noeud**racine,int valeur);
void insertion_rec(noeud**racine,int valeur);
void suppression_n(noeud*x);
noeud*rotation_G(noeud*x);
noeud*rotation_D(noeud*x);

void insertion_racine(noeud**racine,int valeur);
int facteur_balance(noeud*x);
int hauteur_noeud(noeud*x);
void update_hauteur(noeud*x);
void free_arbre(noeud*x);
#endif
