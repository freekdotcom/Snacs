#include "Landmarks.h"
#include <climits>

Landmarks::Landmarks(const Node* G = NULL,int k)
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

void Landmarks::ConvertGraph(const Node* G)
{
	landmarks = PickLandmarks();
	list<list<Node*>*>* newGraph = new list<list<Node*>*>();
	for(int i = 0; i < nmbrLandmarks;i++)
	{
		list<Node*>* distanceLandmark = new list<Node*>();
		/*foreach node(k) in G that is not a landmark
			distanceLandmark.insert(DistanceGraph(k,landmarks(i)))
		*/
		newGraph.insert(distanceLandmark);
	}
	graph = newGraph;
}

std::list<Node*> Landmarks::PickLandmarks(const Node* G)
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

int Landmarks::DistanceGraph(const Node* s, const Node* t, const Node* G)
{
	return G.distance(s,t)
}
