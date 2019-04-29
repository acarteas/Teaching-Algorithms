#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
vector<vector<T>> multiply(vector<vector<T>>& a, vector<vector<T>>& b)
{
   //ensure proper matrix dimensions
   vector<vector<T>> product{};
   if (a.size() == 0 || a[0].size() != b.size())
   {
      return product;
   }

   //resize result matrix
   product.resize(a.size());
   for (auto& row : product)
   {
      row.resize(b[0].size());
   }

   for (int i = 0; i < a[0].size(); i++)
   {
      for (int j = 0; j < b.size(); j++)
      {
         for (int k = 0; k < b.size(); k++)
         {
            product[i][j] += a[i][k] * b[k][j];
         }
      }
   }
   return product;
}

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

int main(void)
{
   vector<vector<int>> a =
      { vector<int>{1, 2},
      vector<int>{3, 4} };
   vector<vector<int>> b = 
    { vector<int>{2, 4},
      vector<int>{1, 3} };
   /*
   1 2  x  2 4  =  4  10
   3 4     1 3     10 24
   */
   vector<vector<int>> product = multiply(a, b);
   int result = maximumSubsequenceV1(vector<int>{1, 2, 3, -4, 2, -10, 0, 1, 3, -2, 5, -2, -1, 3});
   return 0;
}