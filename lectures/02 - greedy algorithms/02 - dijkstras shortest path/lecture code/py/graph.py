#PQ functions in Python
from heapq import *
class Graph:

    #constructor in Python
    def __init__(self):
        self._graph = {} #HT in python

    def add_vertex(self, node):
        self._graph[node] = {}

    def connect_vertex(self, source, sink, weight, is_bidirectional = False):
        self._graph[source][sink] = weight
        if is_bidirectional == True:
            self.connect_vertex(sink, source, weight, False)
    
    def compute_shortest_path(self, start):

        #tracks known distances
        distances = {}

        #make sure start is in graph
        if start in self._graph:

            #define PQ
            to_visit = []

            #push on starting location.
            #By default, python will sort PQ by first value in Tuple
            heappush(to_visit, (0, start))

            #while PQ is not empty
            while len(to_visit) > 0:

                #pop returns item in Python
                top = heappop(to_visit)

                #2nd item is our key
                key = top[1]

                if not key in distances:

                    #record distance
                    distances[key] = top[0]

                    #push on children
                    for edge, weight in self._graph[key].items():
                        if not edge in distances:
                            heappush(to_visit, (weight + top[0], edge))
        return distances
