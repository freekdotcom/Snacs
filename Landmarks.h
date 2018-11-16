#include <list>
#include "Node.h"
#include "boost/graph/"

typedef boost::undirected_graph<> Graph;

class Landmarks
{
	public:
		Landmarks(const Graph* G = NULL, int k = 2);//, selecting strategy meegeven);
		~Landmarks();

		int DistanceLandmarks(const Node s, const Node t);
		
	private:
		std::list<Node*>* landmarks;
		std::map<Node*,std::map<Node*,int>*>* landmarkRepresentation;
		int nmbrLandmarks;

		void ConvertGraph(const Graph* G);
		std::list<Node> PickLandmarks(const Graph* G);	
		int DistanceGraph(const Node* s, const Node* t, const Graph* G);
}

