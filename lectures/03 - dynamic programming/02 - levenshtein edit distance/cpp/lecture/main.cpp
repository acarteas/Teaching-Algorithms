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

int main(void)
{
   cout << calculateEditDistance("racket", "raccoon") << endl;
   return 0;
}