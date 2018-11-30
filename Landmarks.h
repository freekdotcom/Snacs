#ifndef LANDMARKS_H
#define LANDMARKS_H
#include "Node.h"

#include <climits>
#include <algorithm>

#include <list>
#include <iostream>
#include <fstream>

#include <boost/function.hpp>
#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/bind.hpp>


typedef boost::adjacency_list <boost::listS, boost::vecS, boost::directedS, boost::no_property, boost::property<boost::edge_weight_t, int> > Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;

typedef std::pair<int, int> Edge;

//typedef std::function<std::list<int>*(int,std::list<Node*>*)> Delegate;

#endif

class Landmarks
{
	public:
		Landmarks(const Graph* G, std::list<Node*>* nodes, int k = 2);//, selecting strategy meegeven);
		~Landmarks();

		int DistanceLandmarks(const Node* s, const Node* t);
		
	private:
		std::list<Node*>* landmarks;
		std::list<std::map<Node*,int>*>* graph;
		int nmbrLandmarks;
		//Delegate strategy;
		

		bool ConvertGraph(const Graph* G, std::list<Node*>* nodes);
		std::list<Node*>* PickLandmarks(const Graph* G, std::list<Node*>* nodes);
		int DistanceGraph(Node* s, Node* t, const Graph* G);
};

