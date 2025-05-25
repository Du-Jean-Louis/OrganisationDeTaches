#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Définition d'un sommet

typedef struct Node{
	int value;          // Valeur du sommet
	struct Node* nextnode;  // Pointeur vers le sommet suivant, NULL si il n'existe pas
}Node;  

// Définition d'un côté

typedef struct Edge{  
	Node *src;    // Pointeur vers le sommet source
	Node *dest;   // Pointeur vers le sommet destination
	struct Edge* nextedge;   // Pointeur sur l'edge suivant
}Edge;

// Définition pour le edge d'un tableau

typedef struct EdgeTab{
	int src;           // Valeur de la Node source
	int dest;          // Valeur de la Node destination
}EdgeTab;

// Définition d'une structure pour construire l'ordre

typedef struct OrderTab{
	int nb_nodes;
	int nb_edges;
	int* tab_nodes;
	EdgeTab* tab_edges;
}OrderTab;

// Définition du graph

typedef struct Graph{
	int nb_nodes;
	int nb_edges; 
	Node* nodes;  // Pointeur vers la première node
	Edge* edges;  // Pointeur vers le premier edge
}Graph;

// -------------------------------------------------- //

// Création d'un graphique avec nv Nodes et ne Edge, condition si nv=0 alors ne=0, sinon ne < nv! (factorielle) 

Graph* create_graph();

// Ajouter un sommet

void add_node(Graph* g, int value);

// Trouver l'adresse d'un sommet étant donné une value

Node* find_node(Graph* g, int value);

// Ajouter un coté

void add_edge(Graph* g, int src, int dest);

// Voir le graphe

void print_graph(Graph* g);

// Libérer le graphe

void free_graph(Graph* g);

// La structure implémenter précedemment marche bien pour la gestion du Graph
// Mais n'est pas adapté pour trouver l'ordre
// On va donc la convertir dans une nouvelle structure à base de tableaux maintenant qu'on a la taille finale

// Fonction pour convertir le Graph dans une OrderTab

OrderTab* convertion(Graph* g);

// Fonction pour afficher le tableau, il donne renvoie la même chose que print_graph 

void print_tab(OrderTab* tab);

// Fonction pour libérer l'order tab

void free_tab(OrderTab* tab);

// Fonction pour vérifier si une node a des sources

bool no_src(OrderTab* tab, int value);

// Fonctions pour donner l'ordre souhaité

void sort(Graph* g);

#endif