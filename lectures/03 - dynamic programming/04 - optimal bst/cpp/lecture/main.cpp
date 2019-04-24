#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

double optimalBstTd(
   vector<string>& words,
   vector<double>& probabilities,
   int start_index,
   int end_index,
   vector<vector<double>>& memory
)
{
   //tree of size 1?  If so, it's just the native probability
   if (start_index == end_index)
   {
      return probabilities[start_index];
   }

   //did we go beyond bounds?
   if (start_index > end_index)
   {
      return 0;
   }

   //ensure proper memory size
   if (memory.size() < end_index)
   {
      memory.resize(end_index + 2);
      for (auto& row : memory)
      {
         row.resize(end_index + 2);
         for (int i = 0; i < row.size(); i++)
         {
            row[i] = -1;
         }
      }
   }

   //calculates edge lookup cost
   double tree_cost = 0.0;
   for (int i = start_index; i <= end_index; i++)
   {
      tree_cost += probabilities[i];
   }

   //recursively determine smallest cost
   double lowest_cost = INT_MAX;
   for (int i = start_index; i <= end_index; i++)
   {
      //left side
      double left_cost = 0.0;
      if ((i - 1) >= 0 && memory[start_index][i - 1] > 0)
      {
         left_cost = memory[start_index][i - 1];
      }
      else if((i - 1) >= 0)
      {
         left_cost = optimalBstTd(words, probabilities, start_index, i - 1, memory);
         memory[start_index][i - 1] = left_cost;
      }

      //right side
      double right_cost = 0.0;
      if ( (i + 1) <= end_index && memory[i + 1][end_index] > 0)
      {
         right_cost = memory[i + 1][end_index];
      }
      else if((i + 1) <= end_index)
      {
         right_cost = optimalBstTd(words, probabilities, i + 1, end_index, memory);
         memory[i + 1][end_index] = right_cost;
      }

      double total_cost = left_cost + right_cost;
      if (total_cost < lowest_cost)
      {
         lowest_cost = total_cost;
      }
   }
   return tree_cost + lowest_cost;
}

int main(void)
{
   //PA6 notes
   //char sample = 'T';

   ////T in binary is 01010100
   ////example converting T into two bytes
   //short low = (0b1111) & sample;
   //short high = (0b1111) & (sample >> 4);

   ////example recombining two bytes into a single byte
   //char converted = '\0';
   //converted = high << 4;
   //converted = converted | low;

   vector<string> words{
      "a",  "am", "and", "egg", "if", "the", "two"
   };
   vector<double> probabilities{
      0.22, 0.18, 0.20, 0.05, 0.25, 0.02, 0.08
   };

   vector<vector<double>> mem{};
   double min_cost = optimalBstTd(words, probabilities, 0, words.size() - 1, mem);
   cout << min_cost << endl;
   return 0;
}