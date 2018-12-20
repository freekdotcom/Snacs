#ifndef STRATEGY_H
#define STRATEGY_H
#include "Landmarks.h"

///			Created By	
///	E. Janssen	&	F. v.d. Meulen
///--------------------------------------
///	Project	:	Landmark System
/// Course	:	Social Network Analysis
/// Date	  :	10/12/2018
/// Classe	:	Strategies
///---------------------------------------

//  Function    : Compare Map 
//  Description :
//	@Param		: std::pair<int, int> elem1
//	@Param		: std::pair<int, int> elem2
//  @Pre        :
//  @Post       :
bool Compare(std::pair<int, int> elem1, std::pair<int, int> elem2)
{
	return (elem1.second < elem2.second);
};

//  Function    : Random Strategy
//  Description :
//	@Param		: Graph * G
//	@Param		: int nmbrLandmarks
//	@Param		: std::list<Node*>* nodes
//  @Pre        :
//  @Post       :
std::vector<int>* RandomStrategy(const Graph* G, int nmbrLandmarks, std::vector<Node*>* nodes)
{
	std::vector<int>* nmbrs = new std::vector<int>();
	int added = 0;
	while(added < nmbrLandmarks)
	{
		int newIndex = rand() % nodes->size();
		if (find(nmbrs->begin(), nmbrs->end(),newIndex) == nmbrs->end())
		{
      nmbrs->push_back(rand() % nodes->size());
      added++;
		}
	}
	return nmbrs;
}

//  Function    : Degree Strategy
//  Description :
//	@Param		: Graph * G
//	@Param		: int nmbrLandmarks
//	@Param		: std::list<Node*>* nodes
//  @Pre        :
//  @Post       :
std::vector<int>* DegreeStrategy(const Graph* G, int nmbrLandmarks, std::vector<Node*>* nodes)
{
	std::vector<int>* nmbrs = new std::vector<int>();
	
	std::vector<std::pair<float, int>>* degree = new std::vector<std::pair<float, int>>();

	boost::graph_traits<Graph>::vertex_iterator vi, vi_end, next;


	boost::tie(vi, vi_end) = boost::vertices(*G);
	for (next = vi; vi != vi_end; vi = next) {
		++next;
		degree->push_back(std::pair<int, int>(*vi, boost::out_degree(*vi, *G)));
	}
  
  std::cout << "Map sorted" << std::endl;
	sort(degree->begin(), degree->end());

	for (int k = 1; k <= nmbrLandmarks; k++)
	{
		nmbrs->push_back(degree->at(degree->size() - k).second);
	}
	std::cout<<"Found: " << nmbrs->size() << " landmarks" <<std::endl;
	return nmbrs;
}

//  Function    : Closeness Strategy
//  Description :
//	@Param		: Graph * G
//	@Param		: int nmbrLandmarks
//	@Param		: std::list<Node*>* nodes
//  @Pre        :
//  @Post       :
std::vector<int>* ClosenessStrategy(const Graph* G, int nmbrLandmarks, std::vector<Node*>* nodes)
{
	std::vector<int>* nmbrs = new std::vector<int>();

	std::vector<std::pair<float, int>>* closeness = new std::vector<std::pair<float, int>>();
  
	DistanceMatrix distances(num_vertices(*G));
	DistanceMatrixMap dm(distances, *G);
	WeightMap wm(1);
	floyd_warshall_all_pairs_shortest_paths(*G, dm, weight_map(wm));

	// Compute the closeness centrality for graph.
	ClosenessContainer cents(num_vertices(*G));
	ClosenessMap cm(cents, *G);
	all_closeness_centralities(*G, dm, cm);

	
	boost::graph_traits<Graph>::vertex_iterator i, end;
	for (boost::tie(i, end) = boost::vertices(*G); i != end; ++i) {
		closeness->push_back(std::pair<float,int>(get(cm,*i),*i));
	}
  
  std::cout << "Map sorted" << std::endl;
	sort(closeness->begin(), closeness->end());

	for (int k = 1; k <= nmbrLandmarks; k++)
	{
		nmbrs->push_back(closeness->at(closeness->size() - k).second);
	}
	return nmbrs;

}

//  Function    : Cluserting Strategy
//  Description :
//	@Param		: Graph * G
//	@Param		: int nmbrLandmarks
//	@Param		: std::list<Node*>* nodes
//  @Pre        :
//  @Post       :
std::vector<int>* ClusteringStrategy(const Graph* G, int nmbrLandmarks, std::vector<Node*>* nodes)
{
	std::vector<int>* nmbrs = new std::vector<int>();

	std::vector<std::pair<float,int>>* cluster = new std::vector<std::pair<float,int>>();

  std::cout << "Calculating Clustering Coefficient" << std::endl;
	ClusteringContainer coefs(boost::num_vertices(*G));
	ClusteringMap cm(coefs,*G);

  std::cout << "Pairing Clustering Coefficient" << std::endl;
	// Print the clustering coefficient of each vertex.
	boost::graph_traits<Graph>::vertex_iterator i, end;
	for (boost::tie(i, end) = boost::vertices(*G); i != end; ++i) {
		cluster->push_back(std::pair<float,int>(get(cm,*i),*i));
	}
  std::cout << "Map sorted" << std::endl;
	sort(cluster->begin(), cluster->end());

	for (int k = 1; k <= nmbrLandmarks; k++)
	{
		nmbrs->push_back(cluster->at(cluster->size() - k  ).second);
	}
	return nmbrs;
}
#endif
