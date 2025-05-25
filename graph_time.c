#include "graph_time.h"

// Création d'un graphique avec nv Nodes et ne Edge, condition si nv=0 alors ne=0, sinon ne < nv! (factorielle) 

Graph2* create_graph2(){  // On commence par crée un graphe vide, 0 sommets, 0 côtés
	
	Graph2* g = (Graph2*)malloc(sizeof(Graph2));  // On crée un graphe
	
	g->nb_nodes = 0;
	g->nb_edges = 0;
	
	g->edges = NULL;
	g->nodes = NULL;
	
	// printf("Graphe cree\n\n");
	
	return g;
}


// Ajouter un sommet

void add_node2(Graph2* g, int value, double time){
	
	// On crée le nouveau sommet
	
	Node2* n = (Node2*)malloc(sizeof(Node2));
	n->value = value;
	n->time = time;
	n->nextnode = NULL;
	
	// On l'insère ensuite dans la liste chainée de Node
	
	if (g->nb_nodes == 0){  // Si c'est la première node, on dit que le début de la liste commence ici
		g->nodes = n;
	} else {                // Sinon on parcourt la liste chainée jusqu'au dernier élément et on l'insère
		Node2* current_node = g->nodes;    // On se crée une node temporaire pour parcourir la liste
		while (current_node->nextnode != NULL){
			current_node = current_node->nextnode;
		}
		current_node->nextnode = n;
	}
	g->nb_nodes += 1;  // On ajoute un au nombre de nodes
}

// Trouver l'adresse d'un sommet étant donné une value

Node2* find_node2(Graph2* g, int value){
	
	// Puisque les nodes sont stockes dans une liste chaines, on ne peux pas y avoir accès directement
	// C'est pour cela que l'on se crée une fonction permettant de retrouver l'adresse d'une node étant donné sa valeur
	
	if (g->nodes == NULL){   // Si il n'y a pas de node, erreur
		printf("Erreur\n");
		return(NULL);
	} else {                 // Sinon comme pour l'insertion d'une node on parcourt la liste
		Node2* current_node = g->nodes;
		while (current_node->nextnode != NULL){    // Cette boucle va jusqu'à l'avant dernier element
			if (current_node->value == value){
				return (current_node);
			}
			current_node = current_node->nextnode;
		}
		if (current_node->value == value){     // Ce if traite le dernier élément
			return (current_node);
		} else {
			printf("Erreur\n");
			return(NULL);
		}
	}
}	

// Ajouter un coté

void add_edge2(Graph2* g, int src, int dest){
	
	// On vérifie que la valeur de la source et la valeur de la destination existe bien dans la liste de nodes
	
	if (find_node2(g, src) != NULL && find_node2(g,dest) != NULL){
		
		// Si c'est le cas on crée le edge
		
		Edge2* e = (Edge2*)malloc(sizeof(Edge2));
		e->src = find_node2(g,src);
		e->dest = find_node2(g,dest);
		e->nextedge = NULL;
	
		if (g->nb_edges == 0){   // Comme pour les nodes, on démarre la liste chainée ici si c'est le premier élément
			g->edges = e;
		} else {                 // Sinon on parcourt la liste et on l'insère à la fin
			Edge2* current_edge = g->edges;
			while (current_edge->nextedge != NULL){
				current_edge = current_edge->nextedge;
			}
			current_edge->nextedge = e;
		}
		g->nb_edges += 1;
	}
}

// Voir le graphe

void print_graph2(Graph2* g){  

	printf("Graph : \n\n");

	printf("Nombre de Nodes : %d\n", g->nb_nodes);
	printf("Nombre de Edges : %d\n\n", g->nb_edges);
	
	printf("Node List :\n");
	if (g->nb_nodes == 0){
		printf("Pas de nodes\n");
	} else {   // Si il y a des nodes, on parcourt la liste en affichant la valeur (ou l'identifiant) de la node
		Node2* current_node = g->nodes;
		while (current_node != NULL){
			printf("%d : ",current_node->value);
			printf("%f\n",current_node->time);
			current_node = current_node->nextnode;
		}
		free(current_node);
	}
	printf("\n");
	
	
	printf("Edge List :\n");
	if (g->nb_edges == 0){
		printf("Pas d'edges\n");
	} else {  // Si il y a des edges, on parcourt la liste en affichant la node source et la node destinataire avec le temps associé
		Edge2* current_edge = g->edges;
		while (current_edge != NULL){
			printf("(%d,%d)\t",current_edge->src->value, current_edge->dest->value);
			current_edge = current_edge->nextedge;
		}
		free(current_edge);
	}
	printf("\n\n");
}

// Libérer le graphe

void free_graph2(Graph2* g){
		
	if (g->nb_nodes>0){  // Si il y a des nodes on les libères, sinon il n'y a rien à faire
		Node2* current_node = g->nodes;
		Node2* temp = current_node->nextnode;
		while (current_node != NULL){
			temp = current_node->nextnode;
			free(current_node);
			current_node = temp;
		}
		free(current_node);
		free(temp);
	}
	free(g);
	// printf("Graphe vide\n\n");
}

// La structure implémenter précedemment marche bien pour la gestion du Graph
// Mais n'est pas adapté pour trouver l'ordre
// On va donc la convertir dans une nouvelle structure à base de tableaux maintenant qu'on a la taille finale

// Fonction pour convertir le Graph dans une OrderTab

OrderTab2* convertion2(Graph2* g){
	
	OrderTab2* tab = (OrderTab2*) malloc(sizeof(OrderTab2));  // On se cree la structure pour stocker les donnees
	
	tab->nb_nodes = g->nb_nodes;  // On recopie le nombre de nodes et d'edges
	tab->nb_edges = g->nb_edges;
	
	if (g->nb_nodes == 0){
		tab->tab_nodes = NULL;    // Si il n'y a pas de node, on n'alloue pas de mémoire
	} else {
	
		tab->tab_nodes = (NodeTab2*) malloc(tab->nb_nodes*sizeof(NodeTab2));
		
		Node2* current_node = g->nodes;
		int compteur_node = 0;
		NodeTab2 n;
		while (current_node != NULL){
			n.value = current_node->value;
			n.time = current_node->time;
			tab->tab_nodes[compteur_node] = n;  // On rentre les valeurs des nodes dans un tableau un par un
			current_node = current_node->nextnode;
			compteur_node++;
		}
		free(current_node);
	}
	
	if (g->nb_edges == 0){
		tab->tab_edges = NULL;   // Pareil que pour les nodes
	} else {
		
		tab->tab_edges = (EdgeTab2*)malloc(tab->nb_edges*sizeof(EdgeTab2));
	
		Edge2* current_edge = g->edges;
		int compteur_edge = 0;
		EdgeTab2 e;              // On cree la structure qui va etre insérée dans le tableau
		while (current_edge != NULL){
			e.src = current_edge->src->value;   
			e.dest = current_edge->dest->value; 
			tab->tab_edges[compteur_edge] = e;// On y stocke les données nécessaire, valeur source, valeur destination
			current_edge = current_edge->nextedge;
			compteur_edge ++;
		}
		free(current_edge);
	}
	// printf("OrderTab cree\n\n");
	return tab;
}

// Fonction pour afficher le tableau, il donne renvoie la même chose que print_graph 

void print_tab2(OrderTab2* tab){
	
	printf("Valeurs du tableau\n");
	
	printf("Nombres de Nodes : %d\n", tab->nb_nodes);
	printf("Nombres de Edges : %d\n", tab->nb_edges);
	
	printf("Node List :\n");
	for (int i = 0; i<tab->nb_nodes; i++){   // On parcourt les tableaux au lieu des listes chainées cette fois
		printf("%d : ", tab->tab_nodes[i].value);
		printf("%f\n", tab->tab_nodes[i].time);
	}
	printf("\n\n");
	
	printf("Edge List :\n");
	for (int j = 0; j<tab->nb_edges; j++){
		printf("(%d,%d)\t", tab->tab_edges[j].src, tab->tab_edges[j].dest);
	}
	printf("\n\n");
}

// Fonction pour libérer l'order tab

void free_tab2(OrderTab2* tab){
	
	free(tab->tab_nodes);
	free(tab->tab_edges);
	free(tab);
	
	// printf("OrderTab vide\n\n");
}

// Fonction pour vérifier si une node a des sources

bool no_src2(OrderTab2* tab, int value){
	
	for (int i = 0; i < tab->nb_edges; i++){
		if (tab->tab_edges[i].dest == value){
			return false;
		}
	}
	return true;
}

// Fonction pour trier un tableau en fonction de time_max

void insertion_sort(NodeTab2* tab_nt, int nbr_elements){   // Variante de la fonction insertion_sort du TP2
	
	for (int i = 1; i<nbr_elements; i++){
		for (int j = i-1; j>=0; j--){
			if (tab_nt[j+1].time < tab_nt[j].time){   // On compare les composantes time_max
				NodeTab2 temp = tab_nt[j];
				tab_nt[j] = tab_nt[j+1];
				tab_nt[j+1] = temp;
			}
		}
	}
}

// Pour trouver l'ordre, on va avoir besoin d'avoir un tableau qui associe la valeur d'une Node et son temps associé
// On va donc créer une sorte de dictionnaire, pour cela on se dit que les value sont des entiers compris entre 0 et 100
// Ainsi on crée un tableau tmax qui est comme un dictionnaire, à la i-ème position on retrouve le temps maximum de la node i

double* create_tmin(OrderTab2* tab){
	
	double* tmin = (double*) malloc(101*sizeof(double));
	
	// Initialisation de tmax
	
	for (int i = 0; i < 101; i++){
		tmin[i] = -1;
	}
	
	for (int j = 0; j<tab->nb_nodes; j++){
		tmin[tab->tab_nodes[j].value] = 0;
	}

	return tmin;
}

// Après avoir mise à jour les temps maximum de chaque node, pour l'ordre il suffit de les afficher dans l'ordre croissant
// Fonction qui importe les valeurs du dictionnaire dans un tableau (value, time_max) et affiche le temps optimal (qui correspond à la plus grande valeur)

NodeTab2* create_tab_nt(OrderTab2* tab, double* tmin){
	
	int compteur_nt = 0;
	NodeTab2* tab_nt = (NodeTab2*) malloc(tab->nb_nodes*sizeof(NodeTab2));  // On crée le tableau de (value, time_max)
	NodeTab2 nt;
	
	double Temps_Opti = 0;
	
	for (int i = 0; i < 101; i++){
		if (tmin[i]!=-1){  // On vérifie que la valeur est prise par l'une des nodes
			if (tmin[i] > Temps_Opti){  // Cette condition sert à trouver la plus grande valeur
				Temps_Opti = tmin[i];
			}
			nt.value = i;
			nt.time = tmin[i];
			tab_nt[compteur_nt] = nt;   // On insère les valeurs qui correspondent à des nodes dans le nouveau tableau
			compteur_nt++;
		}
	}
	
	printf("Le temps optimal pour effectuer les taches est %f\n", Temps_Opti);
	
	return tab_nt;
	
}

// Fonction qui donne l'ordre en fonction du temps

void sort2(Graph2* g){
	
	OrderTab2* tab = convertion2(g);   // On convertit le graphe en une structure pour trouver l'ordre

	double* tmin = create_tmin(tab);   // On crée un dictionnaire utile pour l'ordre
	
	int nodes_traites = 0;  // Pour compter le nombre de fois qu'on reste dans la boucle
	
	bool flag = true;       // Pour vérifier que le probleme est correctement posé
	
	// On se crée un edge qui représente un edge vide
	
	EdgeTab2 edge_vide;
	edge_vide.src = -1;
	edge_vide.dest = -1;
	
	// On va mettre à jour tmax en mettant le plus long temps à chaque fois
	
	while (nodes_traites<g->nb_nodes && flag){  // On rentre dans la boucle si l'on a pas encore traités toutes les nodes et que le problème et bien posé
		flag = false;
		for (int i = 0; i<g->nb_nodes; i++){    // On parcourt les nodes, on cherche une node qui n'a pas de source, c'est à dire que les pré conditions pour cette tâche ont déjà été remplites
			if (tab->tab_nodes[i].value >= 0 && no_src2(tab, tab->tab_nodes[i].value)){  // On vérifie que la node n'a pas été traité et qu'elle n'a pas de sources
				flag = true;
				tmin[tab->tab_nodes[i].value] += tab->tab_nodes[i].time;
				for (int j = 0; j<g->nb_edges; j++){  
					// Ensuite on parcourt toutes les edges pour trouver les nodes qui dépendent de celle-ci est ainsi
					// Mettre à jour le temps maximum pour y parvenir
					// Et supprimer la pré-condition puisque cette tâche a été réalisé
					if (tab->tab_edges[j].src == tab->tab_nodes[i].value){ 
						if (tmin[tab->tab_edges[j].dest] < tmin[tab->tab_edges[j].src]){  // On mets à jour seulement si le chemin est plus long
							tmin[tab->tab_edges[j].dest] = tmin[tab->tab_edges[j].src];
						}
						tab->tab_edges[j] = edge_vide;  // On supprime l'edge, on la marque comme étant traité, la condition a été levé
					}
				}
				tab->tab_nodes[i].value = -1;  // On supprime la node, on la marque comme étant traité
				nodes_traites++;
				break;
			}
		}
	}
	if (!flag){
		printf("Pas possible de trouver un ordre\n");
	}
	
	NodeTab2* tab_nt = create_tab_nt(tab, tmin);  // On cree un tableau qui va permettre d'afficher le temps optimal ainsi que permettre de trouver l'ordre a effectue
	
	insertion_sort(tab_nt, tab->nb_nodes);  // On trie pour avoir le bon ordre
	
	printf("L'ordre optimal pour executer les taches est le suivant :\n");
	
	for (int i = 0; i<tab->nb_nodes; i++){  // On affiche l'ordre
		printf("%d\t", tab_nt[i].value);
		printf("%f\n", tab_nt[i].time);
	}
	printf("\n");
	
	free(tab_nt);
	free_tab2(tab);
}