/*
21212724 - RACHID KARA MOSTEFA
28726079 - THEO GROSS

PROJET COMPLEX 2024

*/
#include <stdio.h>
#include <stdlib.h>

// Structure de données d'un noeud
typedef struct Node {
    char cle;                  
    int priorite;             
    struct Node* gauche;        
    struct Node* droit;       
} Node;

// Structure de données d'un arbre cartésien
typedef struct arbre_cartesien {
    Node* racine;               
} arbre_cartesien;

// Creation d'un noeud
Node* creer_node(char cle, int priorite) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Erreur : impossible d'allouer l'espace memoire !!!\n");
        exit(EXIT_FAILURE);
    }
    newNode->cle = cle;
    newNode->priorite = priorite;
    newNode->gauche = NULL;
    newNode->droit = NULL;
    return newNode;
}

// Iinitialisation de l'arbre cartésien 
arbre_cartesien* creer_arbre_cartesien() {
    arbre_cartesien* arbre = (arbre_cartesien*)malloc(sizeof(arbre_cartesien));
    if (arbre == NULL) {
        printf("Erreur : allocation mémoire échouée.\n");
        exit(EXIT_FAILURE);
    }
    arbre->racine = NULL;
    return arbre;
}

// Vérifier si l'arbre est vide
int arbre_vide(arbre_cartesien* arbre) {
    return arbre->racine == NULL;
}

//  Rotation à droite pour respecter les priorites des nodes
Node* rotation_droite(Node* racine) {
    Node* newRacine = racine->gauche;
    racine->gauche = newRacine->droit;
    newRacine->droit = racine;
    return newRacine;
}

//  Rotation à gauche pour respecter les priorites des nodes
Node* rotation_gauche(Node* racine) {
    Node* newRacine = racine->droit;
    racine->droit = newRacine->gauche;
    newRacine->gauche = racine;
    return newRacine;
}

// Insérer un node dans l'arbre cartésien
Node* inserer_node(Node* racine, char cle, int priorite) {
    if (racine == NULL) {
        return creer_node(cle, priorite);
    }

    // Insertion suivant les propriétés de l'arbre binaire de recherche
    if (cle < racine->cle) {
        racine->gauche = inserer_node(racine->gauche, cle, priorite);

        // Rotation pour respecter les propriétés du tas
        if (racine->gauche->priorite < racine->priorite) {
            racine = rotation_droite(racine);
        }
    } else if (cle > racine->cle) {
        racine->droit = inserer_node(racine->droit, cle, priorite);

        // Rotation pour respecter les propriétés du tas
        if (racine->droit->priorite < racine->priorite) {
            racine = rotation_gauche(racine);
        }
    }

    return racine;
}

// Insertion du noeud dans l'arbre cartésien
void inserer_dans_arbre(arbre_cartesien* arbre, char cle, int priorite) {
    arbre->racine = inserer_node(arbre->racine, cle, priorite);
}


// Afficher l'arbre resultant par ordre de priorité des nodes
void afficher_arbre(Node* racine) {
    if (racine != NULL) {

        // Afficher le noeud
        printf("(Cle: %c, Priorite: %d)\n ", racine->cle, racine->priorite);

        // Parcourir le sous-arbre gauche 
        afficher_arbre(racine->gauche);    

        // Parcourir le sous-arbre droit
        afficher_arbre(racine->droit);
    }
}

Node* supprimer_node(Node* racine, char cle) {
    if (racine == NULL) {
        return NULL; // Nœud non trouvé
    }

    // Recherche du nœud à supprimer
    if (cle < racine->cle) {
        racine->gauche = supprimer_node(racine->gauche, cle);
    } else if (cle > racine->cle) {
        racine->droit = supprimer_node(racine->droit, cle);
    } else {
        // Nœud trouvé : appliquer des rotations pour l'amener à une feuille
        if (racine->gauche == NULL && racine->droit == NULL) {
            free(racine); // Suppression si feuille
            return NULL;
        } else if (racine->gauche == NULL || 
                   (racine->droit != NULL && racine->droit->priorite < racine->gauche->priorite)) {
            racine = rotation_gauche(racine);
            racine->gauche = supprimer_node(racine->gauche, cle);
        } else {
            racine = rotation_droite(racine);
            racine->droit = supprimer_node(racine->droit, cle);
        }
    }
    return racine;
}

void supprimer_dans_arbre(arbre_cartesien* arbre, char cle) {
    arbre->racine = supprimer_node(arbre->racine, cle);
}

// Recherche d'un noeud contenant une clé donnée
Node* rechercher_node(Node* racine, char cle) {
    if (racine == NULL) {
        printf("La cle %c n'existe pas dans l'arbre.\n", cle);
        return NULL;
    }

    if (cle == racine->cle) {
        printf("Noeud trouve : (Cle: %c, Priorite: %d)\n", racine->cle, racine->priorite);
        return racine;
    }

    if (cle < racine->cle) {
        return rechercher_node(racine->gauche, cle);
    } else {
        return rechercher_node(racine->droit, cle);
    }
}

// Recherche dans l'arbre cartésien
void rechercher_dans_arbre(arbre_cartesien* arbre, char cle) {
    rechercher_node(arbre->racine, cle);
}


int main() {
    arbre_cartesien* arbre = creer_arbre_cartesien();

    inserer_dans_arbre(arbre, 'H', 1);
    inserer_dans_arbre(arbre, 'G', 9);
    inserer_dans_arbre(arbre, 'A', 5);
    inserer_dans_arbre(arbre, 'B', 3);
    inserer_dans_arbre(arbre, 'D', 2);
    inserer_dans_arbre(arbre, 'F', 7);
    inserer_dans_arbre(arbre, 'C', 8);
    inserer_dans_arbre(arbre, 'J', 12);
    inserer_dans_arbre(arbre, 'I', 10);
    inserer_dans_arbre(arbre, 'E', 6);


/*

    inserer_dans_arbre(arbre, 'H', 1);
    inserer_dans_arbre(arbre, 'D', 2);
    inserer_dans_arbre(arbre, 'B', 3);
    inserer_dans_arbre(arbre, 'A', 5);
    inserer_dans_arbre(arbre, 'E', 6);
    inserer_dans_arbre(arbre, 'F', 7);
    inserer_dans_arbre(arbre, 'C', 8);
    inserer_dans_arbre(arbre, 'G', 9);
    inserer_dans_arbre(arbre, 'I', 10);
    inserer_dans_arbre(arbre, 'J', 12);

    inserer_dans_arbre(arbre, 'A', 5);
    inserer_dans_arbre(arbre, 'B', 3);
    inserer_dans_arbre(arbre, 'C', 8);
    inserer_dans_arbre(arbre, 'D', 2);
    inserer_dans_arbre(arbre, 'E', 6);
    inserer_dans_arbre(arbre, 'F', 7);
    inserer_dans_arbre(arbre, 'H', 1);
    inserer_dans_arbre(arbre, 'I', 10);
    inserer_dans_arbre(arbre, 'J', 12);
*/
    // Afficher l'arbre
    printf("Arbre cartesien :\n");
    afficher_arbre(arbre->racine);
       
        //*-------------*//

    // Recherche de nœuds
    printf("\nRecherche du noeud avec la cle 'A' :\n");
    rechercher_dans_arbre(arbre, 'A');

    printf("\nRecherche du noeud avec la cle 'H' :\n");
    rechercher_dans_arbre(arbre, 'H');

    printf("\nRecherche du noeud avec la cle 'Z' :\n");
    rechercher_dans_arbre(arbre, 'Z');

    // Suppression de noeud
    printf("\nSuppression de (A : 5) :\n");
    supprimer_dans_arbre(arbre, 'A');
    afficher_arbre(arbre->racine);

    printf("\nSuppression de (J : 12) :\n");
    supprimer_dans_arbre(arbre, 'J');
    afficher_arbre(arbre->racine);

    printf("\nSuppression de (H : 1) :\n");
    supprimer_dans_arbre(arbre, 'H');
    afficher_arbre(arbre->racine);


    return 0;
}
