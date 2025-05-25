#include "graph.h"
#include "graph_time.h"

void main(){
	
	printf("Partie sans le temps\n\n");
	
	printf("Etude d'un premier graphe\n\n");
	
	Graph* g = create_graph();
	add_node(g,1);
	add_node(g,2);
	add_node(g,3);
	add_node(g,4);
	
	add_edge(g,1,2);
	add_edge(g,1,3);
	add_edge(g,1,4);
	add_edge(g,2,3);
	add_edge(g,4,3);
	
	print_graph(g);
	
	sort(g);
	
	printf("\n");
	printf("On enrichi le graphe avec de nouveaux Edges et Nodes\n\n");
	
	add_node(g,5);
	add_node(g,6);
	
	add_edge(g,2,5);
	add_edge(g,4,6);
	add_edge(g,5,6);
	
	print_graph(g);
	
	sort(g);
	
	free_graph(g);
	
	
	// Avec le temps
	
	printf("\n\nPartie avec le temps\n\n");
	
	Graph2* g2 = create_graph2();
	
	add_node2(g2,1,2);
	add_node2(g2,2,1);
	add_node2(g2,3,8);
	add_node2(g2,4,9);
	add_node2(g2,5,11);
	add_node2(g2,6,2);
	add_node2(g2,7,7);
	add_node2(g2,8,6);
	
	add_edge2(g2,1,3);
	add_edge2(g2,1,4);
	add_edge2(g2,2,4);
	add_edge2(g2,2,5);
	add_edge2(g2,3,6);
	add_edge2(g2,4,5);
	add_edge2(g2,5,8);
	add_edge2(g2,6,8);
	add_edge2(g2,6,7);
	
	print_graph2(g2);
	
	sort2(g2);
	
	free_graph2(g2);

}
