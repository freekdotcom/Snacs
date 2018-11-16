#include "Landmarks.h"
#include <climits>

Landmarks::Landmarks(const Graph* G = NULL,int k = 2)
{
	if(G == NULL)
		throw new Exception("No valid input - Landmarks::Landmarks".);
	nmbrLandmarks = k;
	ConvertGraph(G);
}

Landmarks::~Landmarks()
{
	delete landmarks;
	delete graph;
}

void Landmarks::ConvertGraph(const Graph* G)
{
	landmarks = PickLandmarks();
	map<Node*,map<Node*,int>*>* newGraph = new map<Node*,map<Node*,int>*>();

	list<Node*> notLandmarks;
	
	for(int i = 0; i < nmbrLandmarks;i++)
	{
		map<Node*,int>* distanceLandmark = new map<Node*,int>();
		Node* landmark = landmarks[i];

		bfs_time_visitor

		boost::breadth_first_search(G,vertex(landmark->GetIndex(),G),visitor(vis)

		for(int j = 0; j < notLandmarks.size(); j++)
		{
			Node* target = notLandmarks[j];
			
		}

		/*foreach node(k) in G that is not a landmark
			value = DistanceGraph(k,landmark))
			distanceLandmark(k,value)		//Voeg Toe
		*/
		// newGraph(landmark,distanceLandmark);
	}
	graph = newGraph;
}

std::list<Node*> Landmarks::PickLandmarks(const Graph* G)
{
	std::list<Node*> newLandmarks = new std::list<Node*>();
	for(int i = 0; i < nmbrLandmarks;i++)
	{
		
	}
	if(newLandmarks.size() != nmbrLandmarks)
		return NULL;
	else
		return newLandmarks;
}

int Landmarks::DistanceLandmarks(const Node* s, const Node* t)
{
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
	return 0;
}

int Landmarks::DistanceGraph(const Node* s, const Node* t, const Graph* G)
{
	return G.distance(s,t)
}
