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

        //contains list of nodes to visit along with depth
        queue<pair<string, int>> to_visit{};
        
        //find tier 0 nodes
        for (auto kvp : frequencies) 
        {
            if (kvp.second == 0)
            {
                to_visit.push(make_pair(kvp.first, 0));
            }
        }

        while (to_visit.empty() == false)
        {
            auto front = to_visit.front();
            to_visit.pop();

            //add to correct result tier
            result.resize(front.second + 1);
            result[front.second].push_back(front.first);

            //decrement all outgoing nodes
            for (auto vertex : _graph[front.first]->getEdges())
            {
                string key = vertex.first->getKey();
                frequencies[key]--;
                if (frequencies[key] == 0)
                {
                    to_visit.push(make_pair(key, front.second + 1));
                }
            }
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
