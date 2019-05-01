#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

int maximumSubsequenceV1(vector<int> sequence)
{
   int max_sum = INT_MIN;
   for (int i = 0; i < sequence.size(); i++)
   {
      int local_sum = 0;
      for (int j = i + 1; j < sequence.size(); j++)
      {
         local_sum += sequence[j];
         if (local_sum > max_sum)
         {
            max_sum = local_sum;
         }
      }
   }
   return max_sum;
}

int maxSequence(vector<int>& data, int start, int end)
{
   //calculate total max
   int combination_max = INT_MIN;
   int local_max = 0;
   for (int i = start; i <= end; i++)
   {
      local_max += data[i];
      if (local_max > combination_max)
      {
         combination_max = local_max;
      }
   }
   return combination_max;
}

int maxSequenceDown(vector<int>& data, int start, int end)
{
   //calculate total max
   int combination_max = INT_MIN;
   int local_max = 0;
   for (int i = end; i >= start; i--)
   {
      local_max += data[i];
      if (local_max > combination_max)
      {
         combination_max = local_max;
      }
   }
   return combination_max;
}

int maximumSubsequenceRec(vector<int>& data, int start, int end)
{
   if (end < start)
   {
      return INT_MIN;
   }
   if (start < 0 || start >= data.size())
   {
      return INT_MIN;
   }
   if (end < 0 || end >= data.size())
   {
      return INT_MIN;
   }

   //base case: array size 1
   if (start == end)
   {
      return data[start];
   }
   else if (end - start == 1)
   {

      return max(data[start], max(data[end], data[start] + data[end]));
   }

   //three options: left, right, both
   //left: start - end / 2
   //right: end/2 + 1 - end
   int midpoint = (end - start) / 2 + start;
   int left_sum = maximumSubsequenceRec(data, start, midpoint);
   int right_sum = maximumSubsequenceRec(data, midpoint + 1, end);
   int left_border_max = maxSequenceDown(data, start, midpoint);
   int right_border_max = maxSequence(data, midpoint + 1, end);
   int combination_max = left_border_max + right_border_max;

   int max_result = max(left_sum, max(right_sum, combination_max));
   return max_result;
}

int maxSubsequenceV3(vector<int>& data)
{
   int max_sum = INT_MIN;
   int current_sum = 0;
   for (int i = 0; i < data.size(); i++)
   {
      current_sum += data[i];
      if (current_sum > max_sum)
      {
         max_sum = current_sum;
      }
      if (current_sum <= 0)
      {
         current_sum = 0;
      }
   }
   return max_sum;
}

int main(void)
{
   vector<int> data{1, 2, 3, -4, 2, -10, 0, 1, 3, -2, 5, -2, -1, 3};
   vector<int> mean_example{1, 12, -10, -4, 7, 3, -8, -9, 12, 4, -100, 10};
   vector<int> negatives{ -3, -4, -10, -1, -6 };
   int max = maximumSubsequenceRec(mean_example, 0, mean_example.size() - 1);
   int max2 = maxSubsequenceV3(negatives);
   return 0;
}