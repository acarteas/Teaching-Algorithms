#include "CampusGraph.h";

int main(void)
{
   CampusGraph graph{};
   graph.addVertex("a");
   graph.addVertex("b");
   graph.addVertex("c");
   graph.connectVertex("a", "b", 3, true);
   graph.connectVertex("a", "c", 10);
   graph.connectVertex("b", "c", 5, true);
   graph.computeShortestPath("a");

   return 0;
}