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
#include <algorithm>
#include <functional>


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
#include <boost/graph/exterior_property.hpp>
#include <boost/graph/clustering_coefficient.hpp>
#include <boost/graph/floyd_warshall_shortest.hpp>
#include <boost/graph/closeness_centrality.hpp>
#include <boost/graph/property_maps/constant_property_map.hpp>



typedef boost::adjacency_list <boost::listS, boost::vecS, boost::directedS, boost::no_property, boost::property<boost::edge_weight_t, int> > Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;

typedef std::function<bool(std::pair<int, int>, std::pair<int, int>)> Comparator;

typedef std::pair<int, int> Edge;

typedef std::function<std::vector<int>*(const Graph*,int,std::vector<Node*>*)> Delegate;

//CLOSENESS DEFINITIONS
typedef boost::exterior_vertex_property<Graph, int> DistanceProperty;
typedef DistanceProperty::matrix_type DistanceMatrix;
typedef DistanceProperty::matrix_map_type DistanceMatrixMap;

typedef boost::graph_traits<Graph>::edge_descriptor Edge2;

// Declare the weight map so that each edge returns the same value.
typedef boost::constant_property_map<Edge2, int> WeightMap;

// Declare a container and its corresponding property map that
// will contain the resulting closeness centralities of each
// vertex in the graph.
typedef boost::exterior_vertex_property<Graph, float> ClosenessProperty;
typedef ClosenessProperty::container_type ClosenessContainer;
typedef ClosenessProperty::map_type ClosenessMap;

//CLUSTERING DEFINITIONS
typedef boost::exterior_vertex_property<Graph, float> ClusteringProperty;
typedef ClusteringProperty::container_type ClusteringContainer;
typedef ClusteringProperty::map_type ClusteringMap;

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