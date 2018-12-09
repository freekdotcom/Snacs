#pragma once
#ifndef STRATEGY_H
#define STRATEGY_H
#include "Landmarks.h"


//  Function    : Random Strategy
//  Description :
//	@Param		  : int nmbrLandmarks
//	@Param		  : std::list<Node*>* nodes
//  @Pre        :
//  @Post       :
std::vector<int>* RandomStrategy(Graph* G, int nmbrLandmarks, std::vector<Node*>* nodes)
{
	std::vector<int>* nmbrs = new std::vector<int>();
	for (int i = 0; i < nmbrLandmarks; i++)
	{
		nmbrs->push_back(rand() % nodes->size());
	}
	return nmbrs;
}

//  Function    : Degree Strategy
//  Description :
//	@Param		  : int nmbrLandmarks
//	@Param		  : std::list<Node*>* nodes
//  @Pre        :
//  @Post       :
std::vector<int>* DegreeStrategy(Graph* G, int nmbrLandmarks, std::vector<Node*>* nodes)
{
	std::vector<int>* nmbrs = new std::vector<int>();
	for (int i = 0; i < nmbrLandmarks; i++)
	{
		
	}
	return nmbrs;
}
#endif

