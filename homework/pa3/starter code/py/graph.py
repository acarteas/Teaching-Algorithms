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
    
    def compute_minimum_spanning_tree(self, start):

        #our PQ
        mst_queue = []

        #tracks known paths
        discoveries = {}
        discoveries[start] = 1

        #list of accepted edges, will return to caller
        accepted_edges = []

        #construct set of starting edges
        start_vertex = self._graph[start]

        #prime PQ
        for sink in start_vertex:

            #recall in Python, heappush sorts based on first element
            #in tuple
            heappush(mst_queue, (start_vertex[sink], start, sink))

        while len(mst_queue) > 0 and len(discoveries) < len(self._graph):

            #pop off top
            top = heappop(mst_queue)
            weight = top[0]
            source = top[1]
            sink = top[2]

            #if not seen:
            if not sink in discoveries:

                #add to discoveries
                discoveries[sink] = 1

                #record in accepted edges
                accepted_edges.append(top)

                #add outoing edges from sink
                for vertex in self._graph[sink]:
                    new_edge_weight = self._graph[sink][vertex]
                    heappush(mst_queue, (new_edge_weight, sink, vertex))
        return accepted_edges

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
