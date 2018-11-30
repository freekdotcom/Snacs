#include "Landmarks.h"

///			Created By	
///	E. Janssen	&	F. v.d. Meulen
///--------------------------------------
///	Project	:	Landmark System
/// Course	:	Social Network Analysis
/// Date	  :	30/11/2018
/// Classe	:	Main
///---------------------------------------

 
int main(int, char *[])
{
	const int num_nodes = 4;
	const int num_landmarks = 1;
  
	enum node { A, B, C, D} ;
	Node* Anode = new Node(A);
	Node* Bnode = new Node(B);
	Node* Cnode = new Node(C);
	Node* Dnode = new Node(D);
	std::list<Node*>* nodes = new std::list<Node*>();
	nodes->push_back(Anode);
	nodes->push_back(Bnode);
	nodes->push_back(Cnode);
	nodes->push_back(Dnode);

	Edge edge_array[] = { Edge(A, B), Edge(B, C), Edge(C,D), Edge(D,C), Edge(C, B), Edge(B, A) };
 
	int weights[] = { 1, 1, 1, 1, 1, 1 };
	int num_arcs = sizeof(edge_array) / sizeof(Edge);
 
	// Graph created from the list of edges
	Graph* G = new Graph(edge_array, edge_array + num_arcs, weights, num_nodes);
   
	Landmarks* system = new Landmarks(G, nodes,num_landmarks);
   
	std::cout << "Distance between A - D: \t" << system->DistanceLandmarks(Anode, Dnode) << std::endl;

	return 0;
}
