#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

int calculateEditDistance(const string& first, const string& second)
{
   vector<vector<int>> matrix{};

   //build result matrix
   matrix.resize(first.length() + 1);
   for (auto& row : matrix)
   {
      row.resize(second.length() + 1);
   }

   //fill in first row  
   for (int i = 0; i < matrix[0].size(); i++)
   {
      matrix[0][i] = i;
   }

   //fill in first column
   for (int i = 0; i < matrix.size(); i++)
   {
      matrix[i][0] = i;
   }

   //compute rest of matrix
   for (int i = 1; i < matrix.size(); i++)
   {
      for (int j = 1; j < matrix[i].size(); j++)
      {
         //find least cost of our 3 choices
         int top_cost = matrix[i - 1][j] + 1;
         int left_cost = matrix[i][j - 1] + 1;
         int diagonal_cost = matrix[i - 1][j - 1];

         //add 1 if characters are not the same
         if (first[i - 1] != second[j - 1])
         {
            diagonal_cost++;
         }

         int best_choice = min(top_cost, min(left_cost, diagonal_cost));

         

         //store result in current cell
         matrix[i][j] = best_choice;
      }
   }

   return matrix[matrix.size() - 1][matrix[0].size() - 1];
}

int main(void)
{
   cout << calculateEditDistance("dog", "frog") << endl;
   return 0;
}