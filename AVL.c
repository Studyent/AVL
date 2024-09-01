#include <stdio.h>
#include <stdlib.h>
#include "AVL.h"


int main(int argc,char**argv){

noeud*racine = NULL;
insertion(&racine,10);
insertion(&racine,8);
insertion(&racine,50);
insertion(&racine,56);
insertion(&racine,3);

printf("Affichage infixe \n\n");
infixe(racine);
printf("Affichage Prefixe \n\n");
prefixe(racine);
printf("Affichage Postfixe \n\n");
postfixe(racine);

free(racine);



return 0;
}


noeud*create_n(int cle){

noeud*new_node = (noeud*)malloc(sizeof(noeud));
new_node->cle = cle;
new_node->gauche = NULL;
new_node->droit = NULL;
new_node->parent = NULL;


return new_node;
}

void afficher(noeud*x){

    printf("Valeur du noeud : [%d]\n",x->cle);

}


void infixe(noeud*x){

if(x == NULL){
    return;
}
    infixe(x->gauche);
    afficher(x);
    infixe(x->droit);

}
void prefixe(noeud*x){

if(x == NULL){
    return;
}
afficher(x);
prefixe(x->gauche);
prefixe(x->droit);


}

void postfixe(noeud*x){
    if(x == NULL){
        return;
    }
    postfixe(x->gauche);
    postfixe(x->droit);
    afficher(x);

}

noeud*recherche_r(noeud*x,int k){
    if( (x == NULL) || (k == x->cle )){
        return x;
    }
    if( k < x->cle)
        return recherche_r(x->gauche,k);
    else
        return recherche_r(x->droit,k);
}


noeud*recherche_i(noeud*x,int k){

    while(x != NULL && k != x->cle){

        if(k < x->cle)
            x = x->gauche;
        else    
            x = x->droit;

    }
    return x;

}


noeud*min_b(noeud*x){

    if(x == NULL){
        printf("Arbre vide\n");
        return NULL;
    }

    if(x->gauche != NULL){
        return min_b(x->gauche);
    }else
        return x;
    
}

noeud*max_b(noeud*x){

    if(x== NULL){
        printf("Arbre vide\n");
        return NULL;
    }

    if(x->droit != NULL){
        return max_b(x->droit);
    }else
        return x;

}

int hauteur(noeud*x){
    
    if(x == NULL){
        printf("Arbre vide\n");
        return -1;
    }

    int h_g = hauteur(x->gauche);
    int h_d = hauteur(x->droit);

    return 1 + (h_g > h_d ? h_g : h_d);

}


noeud*successor(noeud*x){

noeud*parent = NULL;

if(x== NULL){
    printf("Arbre vide\n");
    return NULL;
}

if(x->droit != NULL)
{
    return min_b(x->droit);
}
else
{
    parent = x->parent;
    
    while(parent != NULL && x == parent->droit){
        x = parent;
        parent = parent->parent;
    }
    return parent;
    }
}


noeud*predecessor(noeud*x){

    noeud*parent = NULL;
    if(x==NULL){
        printf("Arbre vide\n");
        return NULL;
    }

    if(x->gauche != NULL){
        return max_b(x->gauche);
    }
    parent = x->parent;
    while(parent != NULL && x == parent->gauche){
        x = parent;
        parent = parent->parent;

    }
    return parent;    


}

void insertion(noeud**racine,int valeur){


    noeud*x = *racine;
    noeud*parent = NULL;

    noeud*nouveau = create_n(valeur);

    if(x == NULL){
        *racine = nouveau;
        return;
    }

    while(x != NULL){
        parent = x;
        if(x->cle > valeur){
            x = x->gauche;
        }
        else{
            x = x->droit;
        }

    }

    nouveau->parent = parent;

    if(parent->cle > valeur){
        parent->gauche = nouveau;
        
    }else{
        parent->droit = nouveau;
        
    }

   
}


void insertion_rec(noeud**racine,int valeur){



    if(*racine == NULL){
        *racine = create_n(valeur);
        return;
    }


    if(valeur < (*racine)->cle){
        return insertion(&(*racine)->gauche,valeur);
    }else{

        return insertion(&(*racine)->droit,valeur);

    }



}

noeud*successor(noeud*x){

    noeud*parent = NULL;

    if(x == NULL){
        return NULL;
    }

    if(x->droit != NULL){
        min_b(x->droit);
    }


    parent = x->parent;

    while(parent != NULL && x == x->droit){
        x = parent;
        parent = parent->parent;
    }




    return parent;
}


// Cas aucun fils, ou au plus un fils droit ou gauche


void suppression_n(noeud*x){


    // recherche du noeud


    noeud*temp = recherche_r(x,x->cle);


    // Nous sommes à la racine

    if(temp != NULL){

        if(temp->parent == NULL){
            printf("Nous sommes à la racine");
            free(temp);
            return;
        }
        // fils de gauche et vérification ou placer le fils du parent(x)
        if( (temp->gauche != NULL) && (temp->droit == NULL) ){

            if(temp->parent->gauche == temp){

                temp->gauche->parent = temp->parent;
                temp->parent->gauche = temp->gauche;
               
                free(temp);
                return;

            }else if(temp->parent->droit == temp){

                temp->gauche->parent = temp->parent;
                temp->parent->droit = temp->gauche;
               

                free(temp);
                return;

            }  
        
        // De meme mais pour le fils droit

        }else if( (temp->droit != NULL) && (temp->gauche == NULL) ){

            if(temp->parent->droit == temp){

                temp->droit->parent = temp->parent;
                temp->parent->droit = temp->droit;


            }else if(temp->parent->gauche == temp){

                temp->droit->parent = temp->parent;
                temp->parent->gauche = temp->droit;


            }  

                free(temp);
                update_hauteur(x);

                return;
        }
 

    }else{
        // Le noeud n'a pas été trouvé
        printf("Noeud non trouvé");
        return;

    }

    
}

/*

Courte explication:

    x
    \
     y
    / \
  F_G F_D

Une rotation gauche s'effectue lorsque le sous_arbre droit de x est trop
profond, ainsi x:

puisque F_G < y mais > x

x deviendra le fils gauche
F_G sera le fils droit de x


*/

noeud*rotation_G(noeud*x){


noeud*y = NULL;
noeud*parent = NULL;
noeud*F_G = NULL;

//Sauvegarde avant rotation des sous-arbres
parent = x->parent;

y = x->droit;
F_G = y->gauche;

// rotation gauche à x

y->gauche = x;
x->droit = F_G;

// mise à jour des parents

if(F_G != NULL){

    F_G->parent = x;

}

y->parent = parent;

x->parent = y;


if(parent != NULL){

    if(parent->gauche == x){

        parent->gauche = y;

    }else{

        parent->droit = y;
    }

}

if(parent == NULL){
    return y;
}

update_hauteur(x);
update_hauteur(y);
return y;

}


noeud*rotation_D(noeud*x){

noeud*parent = NULL;
noeud*F_D = NULL;
noeud*y = NULL;

y = x->gauche;

F_D = y->droit;

parent = x->parent;


if(F_D != NULL){

    F_D->parent = x;

}

// rotation effectué
   /* [ CAS GAUCHE DROITE ]
    30       30       25
    /        /        / \
   20       25       20  30
    \       /      
    25     20
    
    */


y->droit = x;
x->gauche = F_D;


//mise à jour des parents

y->parent = parent;
x->parent = y;

if(parent != NULL){
    if(parent->droit == x){
        parent->droit = y;
    }else{
        parent->gauche = y;
    }
}


if(parent == NULL){
    return y;
}

update_hauteur(x);
update_hauteur(y);


return y;


}


void insertion_racine(noeud**racine,int valeur){

    // insertion feuille basique avant rééquilibrage

    noeud*nouveau = create_n(valeur);


    if(*racine == NULL){
        *racine = nouveau;
        return;
    }


    noeud*parent = NULL;
    noeud*courant = *racine;

    while(courant != NULL){
        parent = courant;
        if(valeur < courant->cle){
            courant = courant->gauche;
        }else{
            courant = courant->droit;
        }   
    }


    nouveau->parent = parent;

    if(parent->cle < valeur){
        parent->droit = nouveau;
    }else{
        parent->gauche = nouveau;
    }


    // rééquilibrage


    courant = parent;

    while(courant != NULL){

        update_hauteur(courant);
        int fac_e = hauteur(courant->gauche) - hauteur(courant->droit);

        if(fac_e > 1 && courant->gauche->cle < valeur){ // GG
            courant = rotation_D(courant);
        }
        else if(fac_e > 1 && courant->gauche->cle > valeur){
            courant->gauche = rotation_G(courant->gauche);
            courant = rotation_D(courant);
            
        }
        else if(fac_e < -1 && courant->droit->cle < valeur){ // GG

            courant = rotation_G(courant);
            
        }
        else if(fac_e < -1 && courant->droit->cle > valeur){
            courant->droit = rotation_D(courant->droit);
            courant = rotation_G(courant);
            
        }

         if(courant->parent == NULL){
            *racine = courant;
        }else{
        if(courant->parent->gauche == parent){
            courant->parent->gauche = courant;
        }else{
            courant->parent->droit = courant;
        }
        }
        parent = courant->parent;
        courant = parent;



    }


}

int hauteur_noeud(noeud*x){

return (x == NULL) ? -1 : x->hauteur;


}


void update_hauteur(noeud*x){

    if(x != NULL){

        x->hauteur = 1 + max(hauteur(x->gauche),hauteur(x->droit) );

    }


}


int facteur_balance(noeud*x){

    return hauteur(x->gauche) - hauteur(x->droit);

}


void free_arbre(noeud*x){

    if(x == NULL){
        return;
    }

    free_arbre(x->gauche);
    free_arbre(x->droit);
    free(x);


}