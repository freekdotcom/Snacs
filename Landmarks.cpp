#include "Landmarks.h"

///			Created By	
///	E. Janssen	&	F. v.d. Meulen
///--------------------------------------
///	Project	:	Landmark System
/// Course	:	Social Network Analysis
/// Date	  :	30/11/2018
/// Classe	:	Landmarks
///---------------------------------------

//TODO: EXTRACT TO OTHER FILE
//  Function    : Random Strategy
//  Description :
//	@Param		  : int nmbrLandmarks
//	@Param		  : std::list<Node*>* nodes
//  @Pre        :
//  @Post       :
std::list<int>* RandomStrategy(int nmbrLandmarks,std::list<Node*>* nodes)
{
	std::list<int>* nmbrs = new std::list<int>();
	for (int i = 0; i < nmbrLandmarks; i++)
	{
		nmbrs->push_back(rand() % nodes->size());
	}
	return nmbrs;
}

//  Function    : Constructor
//  Description :
//  @Param      : const Graph * G
//	@Param		  : std::list<Node*>* nodes
//	@Param		  : int _landmarks
//  @Pre        :
//  @Post       :
Landmarks::Landmarks(const Graph* G, std::list<Node*>* nodes, int _landmarks)
{
	//strategy = RandomStrategy;

	if(G == NULL)
		throw "No valid input - Landmarks::Landmarks";
	nmbrLandmarks = _landmarks;
	
	if ( ConvertGraph(G,nodes)  == false)
		throw "Converting Graph Error - Landmarks::Landmarks";
}

//  Function    : Destructor
//  Description :
//  @Pre        :
//  @Post       :
Landmarks::~Landmarks()
{
	delete landmarks;
	delete graph;
}

//  Function    : Convert Graph
//  Description :
//  @Param      : const Graph * G
//	@Param		: std::list<Node*>* nodes
//  @Pre        :
//  @Post       :
bool Landmarks::ConvertGraph(const Graph* G, std::list<Node*>* nodes)
{
	if (nodes == NULL || nodes->size() == 0)
		throw "Invallid node structure - Landmark::ConvertGraph";
	landmarks = PickLandmarks(G,nodes);
	if (landmarks == NULL || landmarks->size() == 0)
		return false;

	//Create Graph Representation
	std::list<std::map<Node*,int>*>* newGraph = new std::list<std::map<Node*,int>*>();;
	for (std::list<Node *>::iterator source = landmarks->begin(); source != landmarks->end(); ++source)
	{
		std::map<Node*, int>* distanceLandmark = new std::map<Node*, int>();
		for (std::list<Node *>::iterator target = nodes->begin(); target != nodes->end(); ++target)
		{
			//Distance from each node to this landmark
			//REMARK Landmark -> Landmark ? 
			if (*source != *target)
				distanceLandmark->insert(std::pair<Node*, int>(*target, DistanceGraph(*source, *target, G)));
		}
		newGraph->push_back(distanceLandmark);
	}
	graph = newGraph;
	return true;
}

//  Function    : Pick Landmarks
//  Description :
//  @Param      : const Graph * G
//	@Param		: std::list<Node*>* nodes
//  @Pre        :
//  @Post       :
std::list<Node*>* Landmarks::PickLandmarks(const Graph* G, std::list<Node*>* nodes)
{
	std::list<Node*>* newLandmarks = new std::list<Node*>();

	//std::list<Node*>* copy = new std::list<Node*>();
	
	//Random Index Selection
	//TODO: #FIXIT Can select twice #FIXIT
	//TODO: Make it a delegate
	std::list<int>* nmbrs = RandomStrategy(nmbrLandmarks,nodes);
	
	//Node Selection By Index
	for (std::list<Node*>::iterator it = nodes->begin(); it != nodes->end(); ++it)
	{
		Node * getNode = *it;
		if (std::find(nmbrs->begin(), nmbrs->end(), getNode->GetInfo()) != nmbrs->end())
			newLandmarks->push_back(getNode);
	}

	if(newLandmarks->size() != nmbrLandmarks)
		throw "Not enough Landmarks selected - Landmark::PickLandmarks";
	else
		return newLandmarks;
}


//  Function    : Distance Landmarks 
//  Description :
//  @Param      : const Node* s
//	@Param		: const Node* t
//  @Pre        :
//  @Post       :
int Landmarks::DistanceLandmarks(const Node* s, const Node* t)
{
	/*
	shortestPath = INT_MAX;
	landmarkIndex = 0
	for(int i = 0; i < nmbrLandmarks;i++)
	{
		int distanceS = graph[i][s.GetInt()]
		int distanceT = graph[i][t.GetInt()]
		int distance = int + int;
		if(distance < shortestPath)
		{
			shortestPath = distance;
			landmarkIndex = i;
		}	
	}
	*/
	return 0;
}

//  Function    : Distance Graph 
//  Description :
//  @Param      : Node * s
//  @Param      : Node * t
//  @Param      : constante Graph * G
//  @Pre        : 
//  @Post       :
int Landmarks::DistanceGraph(Node* s, Node* t, const Graph* G)
{
	// Create property_map from edges to weights
	//boost::property_map<const Graph, boost::edge_weight_t>::type weightmap = get(boost::edge_weight, *G);
 
	// Create vectors to store the predecessors (p) and the distances from the root (d)
	std::vector<Vertex> p(num_vertices(*G));
	std::vector<int> d(num_vertices(*G));
 
	// Create descriptor for the source node
	Vertex begin = vertex(s->GetInfo(), *G);
	Vertex goal = vertex(t->GetInfo(), *G);
 
	// Evaluate Dijkstra on graph g with source s, predecessor_map p and distance_map d
	boost::dijkstra_shortest_paths(*G, begin, boost::predecessor_map(&p[0]).distance_map(&d[0]));
 
	//Create Vector to store the traversal path.
	std::vector<boost::graph_traits<Graph>::vertex_descriptor > path;
	boost::graph_traits<Graph>::vertex_descriptor current = goal;

	while(current!=begin) 
	{
		path.push_back(current);
		current = p[current];
	}
	path.push_back(begin);

	//Find Length of Shortest Path
	//TODO: Does not take into account weights of graph yet
	std::vector<boost::graph_traits<Graph>::vertex_descriptor >::reverse_iterator it;

	int length = 0;
	int previous = -1;
	std::cout << *path.rbegin() << " - " << *path.rend() << std::endl;
	for (it = path.rbegin(); it != path.rend(); ++it) 
	{
		if(it != path.rbegin())
		{      
			length += 1;
			previous = *it;
		}
	}
	std::cout << "Length of path: " << length << std::endl; 
	return length;
}

