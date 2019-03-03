#for CSV parsing
import csv
from graph import Graph

def process_csv(file_name):
    data = []
    with open(file_name, 'r') as some_file:
        csv_file = csv.reader(some_file, 
                            delimiter=',', 
                            quotechar='"'
                            )
        for row in csv_file:
            data.append(row)
    return data

#example of getting data from CSV
result = process_csv("data.csv")

g = Graph() 
g.add_vertex("a")
g.add_vertex("b")
g.add_vertex("c")
g.add_vertex("d")
g.add_vertex("e")
g.add_vertex("f")
g.add_vertex("g")
g.add_vertex("h")
g.connect_vertex("a", "b", 3, True)
g.connect_vertex("a", "c", 15, True)
g.connect_vertex("a", "d", 6, True)
g.connect_vertex("e", "a", 4, True)
g.connect_vertex("h", "f", 4, True)
g.connect_vertex("f", "e", 12, True)
g.connect_vertex("h", "g", 3, True)
g.connect_vertex("a", "g", 11, True)
g.connect_vertex("b", "g", 6, True)
g.connect_vertex("c", "f", 2, True)
g.connect_vertex("d", "g", 6, True)
g.connect_vertex("e", "d", 7, True)
g.connect_vertex("f", "c", 4, True)
g.connect_vertex("g", "b", 9, True)
g.connect_vertex("h", "a", 7, True)
distances = g.compute_shortest_path("a")
mst = g.compute_minimum_spanning_tree("a")
print("done")