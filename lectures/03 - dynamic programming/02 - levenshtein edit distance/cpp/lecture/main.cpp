#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

int calculateEditDistance(
   const string& first,
   const string& second,
   int first_index,
   int second_index,
   vector<vector<int>>& mem)
{
   int cost = 0;

   //ensure index is in bounds
   if (first_index >= first.length())
   {
      //at is point, we can no longer transform and delete doesn't 
      //make sense because we're smaller
      return second.length() - second_index;
   }
   else if (second_index >= second.length())
   {
      return first.length() - first_index;
   }

   //is there currently alignment at the indices?
   if (first[first_index] == second[second_index])
   {
      return calculateEditDistance(
         first,
         second,
         first_index + 1,
         second_index + 1,
         mem);
   }
   else
   {
      //before we make recursive calls, check mem
      //value greater than -1 means that we've calculated this before
      int insert_cost = mem[first_index][second_index + 1];
      int delete_cost = mem[first_index + 1][second_index];
      int transform_cost = mem[first_index + 1][second_index + 1];

      //recursive calls must be made if we have bad memory
      if (insert_cost == -1)
      {
         insert_cost = calculateEditDistance(
            first,
            second,
            first_index,
            second_index + 1,
            mem);
      }
      if (delete_cost == -1)
      {
         delete_cost = calculateEditDistance(
            first,
            second,
            first_index + 1,
            second_index,
            mem);
      }
      if (transform_cost == -1)
      {
         transform_cost = calculateEditDistance(
            first,
            second,
            first_index + 1,
            second_index + 1,
            mem);
      }
      cost = 1 + min(min(insert_cost, delete_cost), transform_cost);
      mem[first_index][second_index] = cost;
      return cost;
   }
   return -1;
}

int calculateEditDistance(
   const string& first,
   const string& second,
   int first_index = 0,
   int second_index = 0)
{
   vector<vector<int>> mem{};
   mem.resize(first.length() + 1);
   for (int i = 0; i < mem.size(); i++)
   {
      mem[i].resize(second.length() + 1);
      for (int j = 0; j < second.length() + 1; j++)
      {
         mem[i][j] = -1;
      }
   }
   int result = calculateEditDistance(first, second, first_index, second_index, mem);
   return result;
}

int calculateEditDistanceBU(const string& first, const string& second)
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
   cout << calculateEditDistanceBU("dog", "frog") << endl;
   return 0;
}