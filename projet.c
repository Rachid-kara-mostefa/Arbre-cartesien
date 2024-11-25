#include <stdio.h>
#include <stdlib.h>

// Structure de données d'un noeud
typedef struct Node {
    int key;                  
    int priority;             
    struct Node* left;        
    struct Node* right;       
} Node;

// Structure d'un arbre cartésien
typedef struct CartesianTree {
    Node* root;               // Racine de l'arbre
} CartesianTree;

// Fonction pour créer un nœud
Node* createNode(int key, int priority) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Erreur : impossible d'allouer l'espace memoire !!!\n");
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->priority = priority;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Fonction pour initialiser un arbre cartésien vide
CartesianTree* createCartesianTree() {
    CartesianTree* tree = (CartesianTree*)malloc(sizeof(CartesianTree));
    if (tree == NULL) {
        printf("Erreur : allocation mémoire échouée.\n");
        exit(EXIT_FAILURE);
    }
    tree->root = NULL;
    return tree;
}

// Fonction pour vérifier si l'arbre est vide
int isTreeEmpty(CartesianTree* tree) {
    return tree->root == NULL;
}

// Fonction pour effectuer une rotation à droite
Node* rotateRight(Node* root) {
    Node* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    return newRoot;
}

// Fonction pour effectuer une rotation à gauche
Node* rotateLeft(Node* root) {
    Node* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    return newRoot;
}

// Fonction pour insérer un nœud tout en respectant les propriétés de l'arbre cartésien
Node* insertNode(Node* root, int key, int priority) {
    if (root == NULL) {
        return createNode(key, priority);
    }

    // Insertion selon l'arbre binaire de recherche
    if (key < root->key) {
        root->left = insertNode(root->left, key, priority);

        // Rééquilibrage pour respecter la propriété du tas
        if (root->left->priority < root->priority) {
            root = rotateRight(root);
        }
    } else if (key > root->key) {
        root->right = insertNode(root->right, key, priority);

        // Rééquilibrage pour respecter la propriété du tas
        if (root->right->priority < root->priority) {
            root = rotateLeft(root);
        }
    }

    return root;
}

// Fonction pour insérer un nœud dans l'arbre cartésien
void insertIntoTree(CartesianTree* tree, int key, int priority) {
    tree->root = insertNode(tree->root, key, priority);
}


// Fonction pour afficher l'arbre par ordre de priorité
void priorityOrderTraversal(Node* root) {
    if (root != NULL) {
        // Affiche d'abord la racine (propriété de tas : plus haute priorité)
        printf("(Cle: %d, Priorite: %d) ", root->key, root->priority);

        // Parcours des sous-arbres gauche et droit
        priorityOrderTraversal(root->left);
        priorityOrderTraversal(root->right);
    }
}
// Exemple d'utilisation
int main() {
    CartesianTree* tree = createCartesianTree();

    // Insertion de nœuds
    insertIntoTree(tree, 8, 100);
    insertIntoTree(tree, 2, 300);
    insertIntoTree(tree, 3, 800);
    insertIntoTree(tree, 4, 200);
    insertIntoTree(tree, 7, 900);
    insertIntoTree(tree, 9, 1000);
    insertIntoTree(tree, 10, 1200);
    insertIntoTree(tree, 1, 500);
    insertIntoTree(tree, 5, 600);
    insertIntoTree(tree, 6, 700);



    // Affichage de l'arbre
    printf("Arbre cartesien en parcours infixe :\n");
    priorityOrderTraversal(tree->root);

    // Libération de mémoire omise pour simplification
    return 0;
}
