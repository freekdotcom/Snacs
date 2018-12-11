#include "Landmarks.h"

///			Created By	
///	E. Janssen	&	F. v.d. Meulen
///--------------------------------------
///	Project	:	Landmark System
/// Course	:	Social Network Analysis
/// Date	  :	10/12/2018
/// Classe	:	Landmarks
///---------------------------------------

//  Function    : Constructor
//  Description :
//  @Param      : const Graph * G
//	@Param		  : std::list<Node*>* nodes
//	@Param		  : int _landmarks
//  @Pre        :
//  @Post       :
Landmarks::Landmarks(const Graph* G, std::vector<Node*>* nodes, Delegate _strategy, int _landmarks)
{
	strategy = _strategy;

	if(G == NULL)
		throw "No valid input - Landmarks::Landmarks";
	nmbrLandmarks = _landmarks;

  landmarks = NULL;
  graph = NULL;

	std::cout	<< "Converting Graph to Landmark System"	<< std::endl
				<< "Status: Starting"						<< std::endl;
	if (ConvertGraph(G, nodes) == false)
		throw "Converting Graph Error - Landmarks::Landmarks";
	else
		std::cout << "Status: Completed"	<< std::endl	<< std::endl;
}

//  Function    : Destructor
//  Description :
//  @Pre        :
//  @Post       :
Landmarks::~Landmarks()
{
	delete landmarks;
	graph = NULL;
}

//  Function    : Distance Landmarks 
//  Description :
//  @Param      : const Node* s
//	@Param		: const Node* t
//  @Pre        :
//  @Post       : Tuple with the Lowerbound, Upperbound, the middle point and the geometric mean
boost::tuple<int,int,int,int> Landmarks::DistanceLandmarks(Node* s, Node* t)
{
	int LowerBound = 0;
	int UpperBound = INT_MAX;
	for(int i = 0; i < nmbrLandmarks;i++)
	{
		std::map<Node*,int>* landmark = graph->at(i);

		int si = landmark->find(s)->second;
		int ti = landmark->find(t)->second;

		//Calculate lower bound from this landmark.
		int L = abs(ti - si);
		if (L > LowerBound)
			LowerBound = L;

		//Calculate upper bound from this landmark.
		int U = si + ti;
		if (U != 0 && U < UpperBound)
			UpperBound = U;
	}
	//Calculate middle point and geometric mean.
	int mPoint = floor((UpperBound + LowerBound) / 2);
	int gMean = floor(sqrt(UpperBound * LowerBound));

	return boost::make_tuple(UpperBound, LowerBound, mPoint, gMean);
}

//  Function    : Convert Graph
//  Description :
//  @Param      : const Graph * G
//	@Param		: std::list<Node*>* nodes
//  @Pre        :
//  @Post       :
bool Landmarks::ConvertGraph(const Graph* G, std::vector<Node*>* nodes)
{
	if (nodes == NULL || nodes->size() == 0)
		throw "Invallid node structure - Landmark::ConvertGraph";
	std::cout << "Finding Landmarks" << std::endl;
	landmarks = PickLandmarks(G,nodes);
	if (landmarks == NULL || landmarks->size() == 0)
		return false;
    std::cout << "Found Landmarks" << std::endl;
	//Create Graph Representation
	std::vector<std::map<Node*,int>*>* newGraph = new std::vector<std::map<Node*,int>*>();
	for (std::vector<Node *>::iterator source = landmarks->begin(); source != landmarks->end(); ++source)
	{
		newGraph->push_back(DijkstraDistance(G,*source,nodes));
	}
	graph = newGraph;
	return true;
}

//  Function    : Pick Landmarks
//  Description :
//  @Param      : const Graph * G
//	@Param		: std::vector<Node*>* nodes
//  @Pre        :
//  @Post       :
std::vector<Node*>* Landmarks::PickLandmarks(const Graph* G, std::vector<Node*>* nodes)
{
	std::vector<Node*>* newLandmarks = new std::vector<Node*>();

	std::vector<int>* nmbrs = strategy(G,nmbrLandmarks,nodes);
	
	//Node Selection By Index
	for (int i = 0; i < nmbrs->size(); i++)
	{
		newLandmarks->push_back(nodes->at(nmbrs->at(i)));
	}

	if(newLandmarks->size() != nmbrLandmarks)
		throw "Not enough Landmarks selected - Landmark::PickLandmarks";
	else
		return newLandmarks;
}

//  Function    : Dijkstra Distance Landmarks
//  Description :
//  @Param      : const Graph * G
//	@Param		: Node * s
//	@Param		: std::vector<Node*>* nodes
//  @Pre        :
//  @Post       :
std::map<Node*, int>* Landmarks::DijkstraDistance(const Graph* G, Node * s, std::vector<Node*>* nodes)
{
	// Create things for Dijkstra
	std::vector<Vertex> parents(boost::num_vertices(*G));	// To store parents
	std::vector<int> distances(boost::num_vertices(*G));	// To store distances

	Vertex begin = vertex(s->GetInfo(), *G);

	// Compute shortest paths from begin to all vertices, and store the output in parents and distances
	boost::dijkstra_shortest_paths(*G, begin, boost::predecessor_map(&parents[0]).distance_map(&distances[0]));

	std::map<Node*, int>* returnValue = new std::map<Node*, int>();

	boost::graph_traits < Graph >::vertex_iterator vertexIterator, vend;
	for (boost::tie(vertexIterator, vend) = boost::vertices(*G); vertexIterator != vend; ++vertexIterator)
	{
		Node* target = nodes->at(*vertexIterator);
		returnValue->insert(std::pair<Node*, int>(target, distances[*vertexIterator]));
	}
	return returnValue;
}
