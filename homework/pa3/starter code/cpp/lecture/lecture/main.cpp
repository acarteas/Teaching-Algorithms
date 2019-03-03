#include "CityGraph.h";
#include "CsvParser.h"

int main(void)
{
	//Example of how to parse a CSV file for graph building
	CsvStateMachine csm{ "data.csv" };
	vector<vector<string>> data = csm.processFile();

	CityGraph graph{};
	graph.addVertex("a");
	graph.addVertex("b");
	graph.addVertex("c");
	graph.addVertex("d");
	graph.addVertex("e");
	graph.addVertex("f");
	graph.addVertex("g");
	graph.addVertex("h");
	graph.connectVertex("a", "b", 3, true);
	graph.connectVertex("a", "c", 15, true);
	graph.connectVertex("a", "d", 6, true);
	graph.connectVertex("e", "a", 4, true);
	graph.connectVertex("h", "f", 4, true);
	graph.connectVertex("f", "e", 12, true);
	graph.connectVertex("h", "g", 3, true);
	graph.connectVertex("a", "g", 11, true);
	graph.connectVertex("b", "g", 6, true);
	graph.connectVertex("c", "f", 2, true);
	graph.connectVertex("d", "g", 6, true);
	graph.connectVertex("e", "d", 7, true);
	graph.connectVertex("f", "c", 4, true);
	graph.connectVertex("g", "b", 9, true);
	graph.connectVertex("h", "a", 7, true);
	auto distances = graph.computeShortestPath("a");
	auto mst = graph.computeMinimumSpanningTree("a");
	return 0;
}