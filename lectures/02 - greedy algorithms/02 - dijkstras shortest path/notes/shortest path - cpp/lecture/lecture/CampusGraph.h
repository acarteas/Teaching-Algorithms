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

   void connectVertex(const string& source, const string& sink, const int& weight, bool is_bidirectional = false)
   {
      _graph[source]->addEdge(_graph[sink], weight);
      if (is_bidirectional == true)
      {
         connectVertex(sink, source, weight, false);
      }
   }

   unordered_map<string, int> computeShortestPath(const string& start)
   {
      unordered_map<string, int> distances;

      //make sure that the startin vertex is in the graph
      if (_graph.find(start) != _graph.end())
      {
         priority_queue<pair<StringGraphNode*, int>, vector<pair<StringGraphNode*, int>>, PairComparer> to_visit;
         pair<StringGraphNode*, int> base{ _graph[start], 0 };
         to_visit.push(base);

         while (to_visit.empty() == false)
         {
            auto top = to_visit.top();
            to_visit.pop();

            //do we not already have this location marked down?
            if (distances.find(top.first->getKey()) == distances.end())
            {
               //add the current vertex to our list of computed destinations 
               distances[top.first->getKey()] = top.second;

               //go through each child and add them to the list of places to visit
               for (auto edge : top.first->getEdges()) 
               {
                  StringGraphNode* node = dynamic_cast<StringGraphNode*>(edge.first);
                  if (distances.find(node->getKey()) == distances.end())
                  {
                     to_visit.push(make_pair(node, top.second + edge.second));
                  }
               }
            }
         }
      }

      return distances;
   }
};

#endif // !GRAPH_H
