#for CSV parsing
import csv
from math import log2

class TreeNode:
   def __init__(self):
      self.children = {}
      self.value = ""

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

def calculate_entropy(outcome_levels):
   denominator = 0.0
   for key in outcome_levels:
      denominator += outcome_levels[key]
   
   entropy = 0.0
   for key in outcome_levels:
      ratio = outcome_levels[key] / denominator
      logged = log2(ratio)
      entropy += -ratio * logged
   return entropy

def build_frequency_distribution(sequence):
   distribution = {}
   for item in sequence:
      if not item in distribution:
         distribution[item] = 0
      distribution[item] += 1
   return distribution

def get_observations(matrix, column):
   result = []
   for i in range(len(matrix)):
      result.append(matrix[i][column])
   return result

def reduce_matrix(matrix, column, predictor):
   result = []
   for i in range(len(matrix)):
      if matrix[i][column] == predictor:
         result.append(matrix[i])
   return result

def find_max_gain(matrix, outcome_column, entropy):
   if len(matrix) == 0:
      return -1
   
   information_gain = []
   for column in range(len(matrix[0])):
      if column == outcome_column:
         information_gain.append(-1)
         continue
      observations = get_observations(matrix, column)
      observation_levels = build_frequency_distribution(observations)
      local_entropy = 0.0
      for level in observation_levels:
         reduced_matrix = reduce_matrix(matrix, column, level)
         reduced_observations = get_observations(reduced_matrix, outcome_column)
         local_entropy += observation_levels[level] / len(observations) * calculate_entropy(build_frequency_distribution(reduced_observations))
      information_gain.append(entropy - local_entropy)
   
   most_gain = 0
   for i in range(1, len(information_gain)):
      if information_gain[i] > information_gain[most_gain]:
         most_gain = i
   return most_gain

def build_tree(matrix, predictors, outcome_column):
   observations = get_observations(matrix, outcome_column)
   entropy = calculate_entropy(build_frequency_distribution(observations))
   if(entropy < 0.01):
      node = TreeNode()
      node.value = matrix[0][outcome_column]
      return node
   
   col = find_max_gain(matrix, outcome_column, entropy)
   node = TreeNode()
   node.value = predictors[col]

   selected_observations = get_observations(matrix, col)
   selected_levels = build_frequency_distribution(selected_observations)
   for level in selected_levels:
      reduced_matrix = reduce_matrix(matrix, col, level)
      node.children[level] = build_tree(reduced_matrix, predictors, outcome_column)
   return node

def main():
   
   result = process_csv("easy data set.csv")
   header = result[0]
   result = result[1:]
   root = build_tree(result, header, 4)
   print("done")

if __name__ == '__main__':
   main()