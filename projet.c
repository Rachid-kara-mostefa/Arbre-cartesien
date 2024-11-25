#include<stdlib.h>
#include<stdio.h>
#include<math.h>


// Définition de la structure d'un nœud
typedef struct Noeud {
    char key;                  
    int priorite;              
    struct Noeud* gauche;      // pointeur vers le noeud gauche
    struct Noeud* droit;       // pointeur vers le noeud droit
} Noeud;

// Fonction pour créer un nouveau nœud
Noeud* creerNoeud(char key, int priorite) {
    Noeud* newNoeud = (Noeud*)malloc(sizeof(Noeud));
    if (!newNoeud) {
        perror("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }
    newNoeud->key = key;
    newNoeud->priorite = priorite;
    newNoeud->gauche = NULL;
    newNoeud->droit = NULL;
    return newNoeud;
}

// Fonction pour effectuer une rotation à droite
Noeud* rotateRight(Noeud* y) {
    Noeud* x = y->gauche;
    Noeud* T = x->droit;

    x->droit = y;
    y->gauche = T;

    return x; // Nouvelle racine après la rotation
}

// Fonction pour effectuer une rotation à gauche
Noeud* rotateLeft(Noeud* y) {
    Noeud* x = y->droit;
    Noeud* T = x->gauche;

    x->gauche = y;
    y->droit = T;

    return x; // Nouvelle racine après la rotation
}

// Fonction pour insérer un nœud dans l'arbre cartésien
Noeud* insererNoeud(Noeud* racine, char key, int priorite) {
    // Cas de base : l'arbre est vide
    if (racine == NULL)
        return creerNoeud(key, priorite);

    // Insertion selon l'ordre des clés (ABR)
    if (key < racine->key)
        racine->gauche = insererNoeud(racine->gauche, key, priorite);
    else if (key > racine->key)
        racine->droit = insererNoeud(racine->droit, key, priorite);
    else
        return racine; // Pas de clés dupliquées

    // Ajustement pour maintenir la propriété du tas
    if (racine->gauche && racine->gauche->priorite < racine->priorite)
        racine = rotateRight(racine);
    if (racine->droit && racine->droit->priorite < racine->priorite)
        racine = rotateLeft(racine);

    return racine;
}

// Fonction pour afficher l'arbre en ordre (parcours infixe)
void afficherArbre(Noeud* racine) {
    if (racine != NULL) {
        afficherArbre(racine->gauche);
        printf("(%c, %d) ", racine->key, racine->priorite);
        afficherArbre(racine->droit);
    }
}

// Fonction pour libérer la mémoire de l'arbre
void freeTree(Noeud* racine) {
    if (racine != NULL) {
        freeTree(racine->gauche);
        freeTree(racine->droit);
        free(racine);
    }
}

// Exemple d'utilisation
int main() {
    Noeud* racine = NULL;

    // Insertion de nœuds
    racine = insererNoeud(racine, 'A', 5);
    racine = insererNoeud(racine, 'B', 3);
    racine = insererNoeud(racine, 'C', 8);
    racine = insererNoeud(racine, 'D', 2);
    racine = insererNoeud(racine, 'E', 6);
    racine = insererNoeud(racine, 'F', 7);
    racine = insererNoeud(racine, 'G', 9);
    racine = insererNoeud(racine, 'H', 1);
    racine = insererNoeud(racine, 'I', 10);
    racine = insererNoeud(racine, 'J', 12);

    // Affichage de l'arbre
    printf("Parcours infixe de l'arbre cartésien :\n");
    afficherArbre(racine);
    printf("\n");

    // Libération de la mémoire
    freeTree(racine);

    return 0;
}
