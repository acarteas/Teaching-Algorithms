#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

int align(
   const string& first,
   const string& second,
   const int& first_index,
   const int& second_index,
   int match_score,
   int mismatch_score,
   int gap_score,
   vector<vector<int>>& mem)
{

   if (first.length() <= first_index && second.length() <= second_index)
   {
      return 0;
   }
   else if (first.length() <= first_index)
   {
      return gap_score * (second.length() - second_index);
   }
   else if (second.length() <= second_index)
   {
      return gap_score * (first.length() - first_index);
   }

   //is match? (assmue positive score for match)
   if (first[first_index] == second[second_index])
   {
      return match_score += align(
         first, second,
         first_index + 1,
         second_index + 1,
         match_score,
         mismatch_score,
         gap_score,
         mem);
   }

   int cost_of_first_insert = mem[first_index + 1][second_index];
   if (cost_of_first_insert == INT_MIN)
   {
      cost_of_first_insert = gap_score + align(
         first, second,
         first_index + 1,
         second_index,
         match_score,
         mismatch_score,
         gap_score,
         mem); 
   }
   int cost_of_second_insert = mem[first_index][second_index + 1];
   if (cost_of_second_insert == INT_MIN)
   {
      cost_of_second_insert = gap_score + align(
         first, second,
         first_index,
         second_index + 1,
         match_score,
         mismatch_score,
         gap_score,
         mem);
   }
   int cost_of_misalignment = mem[first_index + 1][second_index + 1];
   if (cost_of_misalignment == INT_MIN)
   {
      cost_of_misalignment = mismatch_score + align(first, second,
         first_index + 1,
         second_index + 1,
         match_score,
         mismatch_score,
         gap_score,
         mem);
   }

   int best_choice = max(cost_of_first_insert, max(cost_of_second_insert, cost_of_misalignment));
   mem[first_index][second_index] = best_choice;
   return best_choice;
}

int align(
   const string& first,
   const string& second,
   const int& first_index,
   const int& second_index,
   int match_score,
   int mismatch_score,
   int gap_score)
{
   vector<vector<int>> mem;
   mem.resize(first.length() + 1);
   for (int i = 0; i < first.length() + 1; i++)
   {
      for (int j = 0; j < second.length() + 1; j++)
      {
         mem[i].push_back(INT_MIN);
      }
   }
   int result = align(first, second, first_index, second_index, match_score, mismatch_score, gap_score, mem);
   return result;
}



int main(void)
{
   //default scores are:
   // match: +1
   // mismatch: -1
   // gap: -2
   cout << align("ABBA", "BAB", 0, 0, 1, -1, -2) << endl;
   cout << align("ABBA", "BAB", 0, 0, 1, -1, -1) << endl;
   return 0;
}