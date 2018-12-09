#ifndef LANDMARKS_H
#define LANDMARKS_H
#include "Node.h"

#include <climits>
#include <algorithm>

#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <tuple>


#include <boost/function.hpp>
#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <boost/graph/graphviz.hpp>


typedef boost::adjacency_list <boost::listS, boost::vecS, boost::directedS, boost::no_property, boost::property<boost::edge_weight_t, int> > Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;


typedef std::pair<int, int> Edge;

typedef std::function<std::vector<int>*(Graph*,int,std::vector<Node*>*)> Delegate;

class Landmarks
{
	public:
		Landmarks(const Graph* G, std::vector<Node*>* nodes, Delegate _strategy, int _landmarks = 2);//, selecting strategy meegeven);
		~Landmarks();

		boost::tuple<int,int,int,int> DistanceLandmarks(Node* s, Node* t);
		
	private:
		std::vector<Node*>* landmarks;
		std::vector<std::map<Node*,int>*>* graph;
		int nmbrLandmarks;
		Delegate strategy;
	
		bool ConvertGraph(const Graph* G, std::vector<Node*>* nodes);
		std::vector<Node*>* PickLandmarks(const Graph* G, std::vector<Node*>* nodes);
		std::map<Node*, int>* DijkstraDistance(const Graph* G, Node * s, std::vector<Node*>* nodes); 
};

#endif