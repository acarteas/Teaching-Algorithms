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
g.connect_vertex("a", "b", 3, True)
g.connect_vertex("a", "c", 15)
g.connect_vertex("b", "c", 7, True)
distances = g.compute_shortest_path("a")

print("done")