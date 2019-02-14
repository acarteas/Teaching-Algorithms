#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include "StringGraphNode.h"
#include <unordered_map>
#include <string>
#include <queue>
using namespace std;

class PairComparer
{
public:
   bool operator()(pair<StringGraphNode*, int> first, pair<StringGraphNode*, int> second)
   {
      return first.second > second.second;
   }
};

class CampusGraph
{
private:
	unordered_map<string, StringGraphNode*> _graph;

public:
	void addVertex(const string& key)
	{
		_graph[key] = new StringGraphNode(key);
	}

	void addVertex(StringGraphNode* node)
	{
		_graph[node->getKey()] = node;
	}

	void connectVertex(
		const string& source,
		const string& sink,
		const int& weight,
		bool is_bidirectional = false)
	{
		_graph[source]->addEdge(_graph[sink], weight);
		if (is_bidirectional == true)
		{
			connectVertex(sink, source, weight, false);
		}
	}

	unordered_map<string, int> computeShortestPath(const string& start)
	{
		//return value
		unordered_map<string, int> distances{};

		//make sure we received a valid starting point
		if (_graph.find(start) != _graph.end())
		{
			//define PQ
			priority_queue < pair<StringGraphNode*, int>,
				vector<pair<StringGraphNode*, int>>,
				PairComparer> to_visit{};

			//prime PQ with starting location
			to_visit.push(make_pair(_graph[start], 0));

			while (to_visit.empty() == false)
			{
				auto top = to_visit.top();
				string key = top.first->getKey();
				int weight = top.second;
				to_visit.pop();

				//have we seen top before?
				if (distances.find(key) == distances.end())
				{
					//mark as visited
					distances[key] = weight;

					//push all unknown outoing edges into PQ
					for (auto edge : top.first->getEdges())
					{
						StringGraphNode* node = dynamic_cast<StringGraphNode*>(edge.first);
						if (distances.find(node->getKey()) == distances.end())
						{
							to_visit.push(make_pair(node, weight + edge.second));
						}
					}
				}
			}
		}
		return distances;
	}
};

#endif // !GRAPH_H
