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

	unordered_map<string, unordered_map<string, int>> toAdjacencyMatrix()
	{
		unordered_map<string, unordered_map<string, int>> result{};

		//O(V^2)
		for (auto graph_key : _graph)
		{
			//prime adjacency matrix with a bunch of -1 values
			for (auto second_key : _graph)
			{
				result[graph_key.first][second_key.first] = -1;
			}

			//represents single row inside of adjacency matrix
			for (auto edge : graph_key.second->getEdges())
			{
				result[graph_key.first][edge.first->getKey()] = edge.second;
			}
		}
		return result;
	}

	vector<vector<string>> topologicalSort()
	{
		vector<vector<string>> result{};

		//step #1: build frequency distribution
		unordered_map<string, int> frequencies{};
		for (auto item : _graph)
		{
			frequencies[item.first] = 0;
		}
		for (auto item : _graph)
		{
			for (auto outgoing_vertex : item.second->getEdges())
			{
				frequencies[outgoing_vertex.first->getKey()]++;
			}
		}

		bool keep_going = true;

		while (keep_going == true)
		{
			keep_going = false;

			//find all vertieces with zero incoming edges
			vector<string> current_tier{};
			for (auto kvp : frequencies)
			{
				if (kvp.second == 0)
				{
					keep_going = true;

					//decrement frequency count to prevent rediscover later
					frequencies[kvp.first]--;

					//ready to be processed
					current_tier.push_back(kvp.first);

					//decrement incoming edge count for connected vertices
					for (auto vertex : _graph[kvp.first]->getEdges())
					{
						frequencies[vertex.first->getKey()]--;
					}
				}
			}
			result.push_back(current_tier);
			current_tier = vector<string>{};
		}
		return result;
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

			//O(E)
			while (to_visit.empty() == false)
			{
				auto top = to_visit.top();
				string key = top.first->getKey();
				int weight = top.second;

				//Log(V)
				to_visit.pop();

				//have we seen top before?
				if (distances.find(key) == distances.end())
				{
					//mark as visited
					distances[key] = weight;

					//push all unknown outoing edges into PQ
					//O(V)
					for (auto edge : top.first->getEdges())
					{
						StringGraphNode* node = dynamic_cast<StringGraphNode*>(edge.first);
						if (distances.find(node->getKey()) == distances.end())
						{
							//Log(V)
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
