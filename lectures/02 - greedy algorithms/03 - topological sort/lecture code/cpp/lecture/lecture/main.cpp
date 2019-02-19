#include "CampusGraph.h";
#include "CsvParser.h"

int main(void)
{
	//Example of how to parse a CSV file for graph building
	CsvStateMachine csm{ "data.csv" };
	vector<vector<string>> data = csm.processFile();

	CampusGraph graph{};
	graph.addVertex("a");
	graph.addVertex("b");
	graph.addVertex("c");
	graph.addVertex("d");
	graph.addVertex("e");
	graph.addVertex("f");
	graph.addVertex("g");
	graph.connectVertex("a", "b", 1);
	graph.connectVertex("a", "c", 1);
	graph.connectVertex("b", "d", 1);
	graph.connectVertex("c", "g", 1);
	graph.connectVertex("e", "a", 1);
	graph.connectVertex("f", "b", 1);
	graph.connectVertex("f", "e", 1);
	auto distances = graph.computeShortestPath("a");
	auto adjacency_matrix = graph.toAdjacencyMatrix();
	auto sorted = graph.topologicalSort();
	return 0;
}