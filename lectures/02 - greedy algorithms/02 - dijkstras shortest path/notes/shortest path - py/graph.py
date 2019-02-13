from heapq import *
class Graph:

   def __init__(self):
      self._graph = {}

   def add_vertex(self, node):
      self._graph[node] = {}

   def connect_vertex(self, source, sink, weight, is_bidirectional = False):
      self._graph[source][sink] = weight
      if is_bidirectional == True:
         self.connect_vertex(sink, source, weight, False)
   
   def compute_shortest_path(self, start):

      #tracks discovered edges
      known = {}
      if start in self._graph:

         #to_visit is our PQ
         to_visit = []

         #pushing on a tuple whose first value is weight will create a min-queue
         heappush(to_visit, (0, start))

         #until PQ is empty...
         while len(to_visit) > 0:

            #pop returns item in Python
            top = heappop(to_visit)

            #2nd item is key
            key = top[1]

            #1st item is weight
            known[key] = top[0]

            #push on unknown children
            for edge, weight in self._graph[key].items():
               if not edge in known:
                  heappush(to_visit, (weight + top[0], edge))
      return known
      