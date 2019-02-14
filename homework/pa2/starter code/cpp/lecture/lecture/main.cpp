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
	graph.connectVertex("a", "b", 3, true);
	graph.connectVertex("a", "c", 15);
	graph.connectVertex("b", "c", 7, true);
	auto distances = graph.computeShortestPath("a");
	return 0;
}