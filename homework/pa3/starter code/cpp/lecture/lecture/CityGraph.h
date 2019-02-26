#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include "StringGraphNode.h"
#include "Edge.h"
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

class CityGraph
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

	vector<Edge> computeMinimumSpanningTree(const string& start_key)
	{
		//where all of the edges should go
		priority_queue<Edge, vector<Edge>, Edge> mst_queue{};

		//tracks whether or not we've seen a given node in the MST
		unordered_map<string, int> discoveries{};
		discoveries[start_key] = 1;

		//constructs final end product
		vector<Edge> accepted_edges{};

		//grab starting vertex.  Construct all edges from start
		//add as primer to PQ.
		StringGraphNode* start = _graph[start_key];
		for (auto vertex : start->getEdges())
		{
			Edge e{ 
				start, 
				dynamic_cast<StringGraphNode*>(vertex.first), 
				vertex.second 
			};
			mst_queue.push(e);
		}

		//use PQ to construct MST
		while (mst_queue.empty() == false && discoveries.size() < _graph.size())
		{
			Edge top = mst_queue.top();
			mst_queue.pop();

			//have we NOT seen the top before
			if (discoveries.find(top.sink->getKey()) == discoveries.end())
			{
				//mark discovered
				discoveries[top.sink->getKey()] ++;

				//accept edge
				accepted_edges.push_back(top);

				//add in outgoing edges
				for (auto vertex : top.sink->getEdges())
				{
					Edge e{
						top.sink,
						dynamic_cast<StringGraphNode*>(vertex.first),
						vertex.second
					};
					mst_queue.push(e);
				}
			}
		}
		return accepted_edges;
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
