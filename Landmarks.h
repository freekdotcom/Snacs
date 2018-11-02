#include <list>
#include "Node.h"

class Landmarks
{
	public:
		Landmarks(const Node* G = NULL);//, selecting strategy meegeven);
		~Landmarks();

		int DistanceLandmarks(const Node s, const Node t);
		
	private:
		std::list<Node*>* landmarks;
		std::list<std::list<Node*>*>* graph;
		int nmbrLandmarks;

		void ConvertGraph(const Node* G);
		std::list<Node> PickLandmarks();	
		int DistanceGraph(const Node* s, const Node* t, const Node* G);
}

