#ifndef GRAPH_TIME_H
#define GRAPH_TIME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Définition d'un sommet

typedef struct Node2{
	int value;          // Valeur du sommet (Node)
	double time;        // Temps requis pour effectuer la tâche
	struct Node2* nextnode;  // Pointeur vers le sommet suivant, NULL si il n'existe pas
}Node2;  

// Définition d'un côté

typedef struct Edge2{  
	Node2 *src;    // Pointeur vers le sommet source
	Node2 *dest;   // Pointeur vers le sommet destination
	struct Edge2* nextedge;   // Pointeur sur l'edge suivant
}Edge2;

// Définition du graph

typedef struct Graph2{
	int nb_nodes;
	int nb_edges; 
	Node2* nodes;  // Pointeur vers la première node
	Edge2* edges;  // Pointeur vers le premier edge
}Graph2;

// Définition pour le edge d'un tableau

typedef struct EdgeTab2{
	int src;          // Valeur de la Node source
	int dest;         // Valeur de la Node destination
}EdgeTab2;

// Définition pour le node d'un tableau

typedef struct NodeTab2{
	int value;
	double time;
}NodeTab2;

// Définition d'une structure pour construire l'ordre

typedef struct OrderTab2{
	int nb_nodes;
	int nb_edges;
	NodeTab2* tab_nodes;
	EdgeTab2* tab_edges;
}OrderTab2;

// -------------------------------------------------- //

// Création d'un graphique avec nv Nodes et ne Edge, condition si nv=0 alors ne=0, sinon ne < nv! (factorielle) 

Graph2* create_graph2();

// Ajouter un sommet

void add_node2(Graph2* g, int value, double time);

// Trouver l'adresse d'un sommet étant donné une value

Node2* find_node2(Graph2* g, int value);

// Ajouter un coté

void add_edge2(Graph2* g, int src, int dest);

// Voir le graphe

void print_graph2(Graph2* g);

// Libérer le graphe

void free_graph2(Graph2* g);

// La structure implémenter précedemment marche bien pour la gestion du Graph
// Mais n'est pas adapté pour trouver l'ordre
// On va donc la convertir dans une nouvelle structure à base de tableaux maintenant qu'on a la taille finale

// Fonction pour convertir le Graph dans une OrderTab

OrderTab2* convertion2(Graph2* g);

// Fonction pour afficher le tableau, il donne renvoie la même chose que print_graph 

void print_tab2(OrderTab2* tab);

// Fonction pour libérer l'order tab

void free_tab2(OrderTab2* tab);

// Fonction pour vérifier si une node a des sources

bool no_src2(OrderTab2* tab, int value);

// Fonction pour trier un tableau en fonction de time_max

void insertion_sort(NodeTab2* tab_nt, int nbr_elements);

// Ainsi on crée un tableau tmax qui est comme un dictionnaire, à la i-ème position on retrouve le temps maximum de la node i

double* create_tmin(OrderTab2* tab);

// Fonction qui importe les valeurs du dictionnaire dans un tableau (value, time_max) et affiche le temps optimal (qui correspond à la plus grande valeur)

NodeTab2* create_tab_nt(OrderTab2* tab, double* tmax);

// Fonctions pour donner l'ordre souhaité

void sort2(Graph2* g);









#endif
