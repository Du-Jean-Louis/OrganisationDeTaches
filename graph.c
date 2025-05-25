#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"

// Création d'un graphique avec nv Nodes et ne Edge, condition si nv=0 alors ne=0, sinon ne < nv! (factorielle) 

Graph* create_graph(){  // On commence par crée un graphe vide, 0 sommets, 0 côtés
	
	Graph* g = (Graph*)malloc(sizeof(Graph));  // On crée un graphe
	
	g->nb_nodes = 0;
	g->nb_edges = 0;
	
	g->edges = NULL;
	g->nodes = NULL;
	
	// printf("Graphe cree\n\n");
	
	return g;
}

// Ajouter un sommet

void add_node(Graph* g, int value){
	
	// On crée le nouveau sommet
	
	Node* n = (Node*)malloc(sizeof(Node));
	n->value = value;
	n->nextnode = NULL;
	
	// On l'insère ensuite dans la liste chainée de Node
	
	if (g->nb_nodes == 0){  // Si c'est la première node, on dit que le début de la liste commence ici
		g->nodes = n;
	} else {                // Sinon on parcourt la liste chainée jusqu'au dernier élément et on l'insère
		Node* current_node = g->nodes;  // On se crée une node temporaire pour parcourir la liste
		while (current_node->nextnode != NULL){
			current_node = current_node->nextnode;
		}
		current_node->nextnode = n;
	}
	g->nb_nodes += 1;      // On ajoute un au nombre de nodes
}

// Trouver l'adresse d'un sommet étant donné une value

Node* find_node(Graph* g, int value){
	
	// Puisque les nodes sont stockes dans une liste chaines, on ne peux pas y avoir accès directement
	// C'est pour cela que l'on se crée une fonction permettant de retrouver l'adresse d'une node étant donné sa valeur
	
	if (g->nodes == NULL){
		printf("Erreur\n");
		return(NULL);
	} else {     // Sinon comme pour l'insertion d'une node on parcourt la liste
		Node* current_node = g->nodes;
		while (current_node->nextnode != NULL){     // Cette boucle va jusqu'à l'avant dernier element
			if (current_node->value == value){
				return (current_node);
			}
			current_node = current_node->nextnode;
		}
		if (current_node->value == value){          // Ce if traite le dernier élément
			return (current_node);
		} else {
			printf("Erreur\n");
			return(NULL);
		}
	}
}	

// Ajouter un coté

void add_edge(Graph* g, int src, int dest){
	
	// On vérifie que la valeur de la source et la valeur de la destination existe bien dans la liste de nodes
	
	if (find_node(g, src) != NULL && find_node(g,dest) != NULL){
	
		// Si c'est le cas on crée le edge
	
		Edge* e = (Edge*)malloc(sizeof(Edge));
		e->src = find_node(g,src);
		e->dest = find_node(g,dest);
		e->nextedge = NULL;
	
		if (g->nb_edges == 0){    // Comme pour les nodes, on démarre la liste chainée ici si c'est le premier élément
			g->edges = e;
		} else {                  // Sinon on parcourt la liste et on l'insère à la fin
			Edge* current_edge = g->edges;
			while (current_edge->nextedge != NULL){
				current_edge = current_edge->nextedge;
			}
			current_edge->nextedge = e;
		}
		g->nb_edges += 1;
	}
}

// Voir le graphe

void print_graph(Graph* g){  

	printf("Graph : \n\n");

	printf("Nombre de Nodes : %d\n", g->nb_nodes);
	printf("Nombre de Edges : %d\n", g->nb_edges);
	
	printf("Node List :\n");
	if (g->nb_nodes == 0){
		printf("Pas de nodes\n");
	} else {    // Si il y a des nodes, on parcourt la liste en affichant la valeur (ou l'identifiant) de la node
		Node* current_node = g->nodes;  
		while (current_node != NULL){
			printf("%d\t",current_node->value);
			current_node = current_node->nextnode;
		}
		free(current_node);
	}
	printf("\n");
	
	
	printf("Edge List :\n");
	if (g->nb_edges == 0){
		printf("Pas d'edges\n");
	} else {  // Si il y a des edges, on parcourt la liste en affichant la node source et la node destinataire
		Edge* current_edge = g->edges;
		while (current_edge != NULL){
			printf("(%d,%d)\t",current_edge->src->value, current_edge->dest->value);
			current_edge = current_edge->nextedge;
		}
		free(current_edge);
	}
	printf("\n\n");
}

// Libérer le graphe

void free_graph(Graph* g){
		
	if (g->nb_nodes>0){   // Si il y a des nodes on les libères, sinon il n'y a rien à faire
		Node* current_node = g->nodes;
		Node* temp = current_node->nextnode;
		while (current_node != NULL){
			temp = current_node->nextnode;
			free(current_node);
			current_node = temp;
		}
		free(current_node);
		free(temp);
	}
	free(g);
	// printf("Graph vide\n\n");
}

// La structure implémenter précedemment marche bien pour la gestion du Graph
// Mais n'est pas adapté pour trouver l'ordre
// On va donc la convertir dans une nouvelle structure à base de tableaux maintenant qu'on a la taille finale

// Fonction pour convertir le Graph dans une OrderTab

OrderTab* convertion(Graph* g){
	
	OrderTab* tab = (OrderTab*) malloc(sizeof(OrderTab));   // On se cree la structure pour stocker les donnees
	
	tab->nb_nodes = g->nb_nodes;    // On recopie le nombre de nodes et d'edges
	tab->nb_edges = g->nb_edges;
	
	if (g->nb_nodes == 0){
		tab->tab_nodes = NULL;    // Si il n'y a pas de node, on n'alloue pas de mémoire
	} else {
	
		tab->tab_nodes = (int*) malloc(tab->nb_nodes*sizeof(int));
		
		Node* current_node = g->nodes;
		int compteur_node = 0;
		while (current_node != NULL){    // On rentre les valeurs des nodes dans un tableau un par un
			tab->tab_nodes[compteur_node] = current_node->value;
			current_node = current_node->nextnode;
			compteur_node++;
		}
		free(current_node);
	}
	
	if (g->nb_edges == 0){
		tab->tab_edges = NULL;   // Pareil que pour les nodes
	} else {
		
		tab->tab_edges = (EdgeTab*)malloc(tab->nb_edges*sizeof(EdgeTab));
	
		Edge* current_edge = g->edges;
		int compteur_edge = 0;
		EdgeTab e;              // On cree la structure qui va etre insérée dans le tableau
		while (current_edge != NULL){
			e.src = current_edge->src->value;
			e.dest = current_edge->dest->value;     // On y stocke les données nécessaire, valeur source, valeur destination
			tab->tab_edges[compteur_edge] = e;
			current_edge = current_edge->nextedge;
			compteur_edge ++;
		}
		free(current_edge);
	}
	// printf("OrderTab cree\n\n");
	return tab;
}

// Fonction pour afficher le tableau, il donne renvoie la même chose que print_graph 

void print_tab(OrderTab* tab){
	
	printf("Valeurs du tableau\n");
	
	printf("Nombres de Node : %d\n", tab->nb_nodes);
	printf("Nombres de Edge : %d\n", tab->nb_edges);
	printf("Node List :\n");
	for (int i = 0; i<tab->nb_nodes; i++){    // On parcourt les tableaux au lieu des listes chainées cette fois
		printf("%d\t", tab->tab_nodes[i]);
	}
	printf("\n");
	printf("Edge List :\n");
	for (int j = 0; j<tab->nb_edges; j++){
		printf("(%d,%d)\t", tab->tab_edges[j].src, tab->tab_edges[j].dest);
	}
	printf("\n\n");
}

// Fonction pour libérer l'order tab

void free_tab(OrderTab* tab){
	
	free(tab->tab_nodes);
	free(tab->tab_edges);
	free(tab);
	
	// printf("OrderTab vide\n\n");
	
}

// Fonction pour vérifier si une node a des sources

bool no_src(OrderTab* tab, int value){
	
	for (int i = 0; i < tab->nb_edges; i++){
		if (tab->tab_edges[i].dest == value){
			return false;
		}
	}
	return true;
}

// Fonctions pour donner l'ordre souhaité

void sort(Graph* g){
	
	OrderTab* tab = convertion(g);   // On convertit le graphe en une structure pour trouver l'ordre
	
	int nodes_traites = 0;          // Pour compter le nombre de fois qu'on reste dans la boucle
	
	bool flag = true;               // Pour vérifier que le probleme est correctement posé
	
	// On se crée un edge qui représente un edge vide
	
	EdgeTab edge_vide;
	edge_vide.src = -1;
	edge_vide.dest = -1;
	
	// On va maintenant donner l'ordre, dès que une node n'est plus une destination on peut l'effectuer, cela veut dire qu'elle n'a plus de pré-requis a effectué
	
	printf("Nombre de Nodes a arranger : %d\nOrdre possible :\n", g->nb_nodes);
	
	while (nodes_traites<g->nb_nodes && flag){
		flag = false;
		for (int i = 0; i<g->nb_nodes; i++){
			if (tab->tab_nodes[i] != -1 && no_src(tab, tab->tab_nodes[i])){
				printf("%d\t",tab->tab_nodes[i]);
				flag = true;
				for (int j = 0; j<g->nb_edges; j++){
					if (tab->tab_edges[j].src == tab->tab_nodes[i]){
						tab->tab_edges[j] = edge_vide;
					}
				}
				tab->tab_nodes[i] = -1;
				nodes_traites++;
				printf("\n");
				break;
			}
		}
	}
	if (!flag){
		printf("Pas possible\n");
	}
	
	free_tab(tab);
	
}
