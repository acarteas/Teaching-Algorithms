#pragma once
#ifndef EDGE_H
#define EDGE_H

#include "StringGraphNode.h"

class Edge
{
public:
	StringGraphNode* source = nullptr;
	StringGraphNode* sink = nullptr;
	int weight = 0;

	Edge(StringGraphNode* source = nullptr, StringGraphNode* sink = nullptr,
		int weight = 0)
	{
		this->sink = sink;
		this->source = source;
		this->weight = weight;
	}

	bool operator()(const Edge& lhs, const Edge& rhs)
	{
		return lhs.weight > rhs.weight;
	}
};


#endif