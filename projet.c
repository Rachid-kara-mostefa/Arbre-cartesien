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
Node* creer_node(int cle, int priorite) {
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
Node* inserer_node(Node* racine, int cle, int priorite) {
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
void inserer_dans_arbre(arbre_cartesien* arbre, int cle, int priorite) {
    arbre->racine = inserer_node(arbre->racine, cle, priorite);
}


// Afficher l'arbre resultant par ordre de priorité des nodes
void afficher_arbre(Node* racine) {
    if (racine != NULL) {
        // Afficher la racine (propriété de tas : plus haute priorité)
        printf("(Cle: %d, Priorite: %d) ", racine->cle, racine->priorite);

        // Parcourir les sous-arbres gauche et droit
        afficher_arbre(racine->gauche);
        afficher_arbre(racine->droit);
    }
}

int main() {
    arbre_cartesien* arbre = creer_arbre_cartesien();

    inserer_dans_arbre(arbre, 8, 100);
    inserer_dans_arbre(arbre, 2, 300);
    inserer_dans_arbre(arbre, 3, 800);
    inserer_dans_arbre(arbre, 4, 200);
    inserer_dans_arbre(arbre, 7, 900);
    inserer_dans_arbre(arbre, 9, 1000);
    inserer_dans_arbre(arbre, 10, 1200);
    inserer_dans_arbre(arbre, 1, 500);
    inserer_dans_arbre(arbre, 5, 600);
    inserer_dans_arbre(arbre, 6, 700);



    // Afficher l'arbre
    printf("Arbre cartesien :\n");
    afficher_arbre(arbre->racine);
        //*-------------*//
    // Libération de mémoire omise pour simplification
    return 0;
}
