#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

struct IteratorCurrentAndEnd
{
  bool operator>(const IteratorCurrentAndEnd &that) const
  {
    return *current > *that.current;
  }
  vector<int>::const_iterator current;
  vector<int>::const_iterator end;
};

vector<int> MergeSortedArrays(const vector<vector<int>> &sorted_arrays)
{
  std::priority_queue<IteratorCurrentAndEnd, std::vector<IteratorCurrentAndEnd>, std::greater<>> min_heap;

  // Intialise min-heap with current and end iterators for each array.
  for (const auto &sorted_array : sorted_arrays)
    if (!sorted_array.empty())
      min_heap.emplace(IteratorCurrentAndEnd{sorted_array.cbegin(), sorted_array.cend()});

  std::vector<int> results;
  while (!min_heap.empty())
  {
    auto smallest_array = min_heap.top();
    min_heap.pop();
    if (smallest_array.current != smallest_array.end)
    {
      results.emplace_back(*smallest_array.current);
      min_heap.emplace(IteratorCurrentAndEnd{++smallest_array.current, smallest_array.end});
    }
  }

  return results;
}

vector<int> SortKIncreasingDecreasingArray(const vector<int> &A)
{
  // Decompose A into a set of sorted arrays
  std::vector<std::vector<int>> sorted_subarrays;
  typedef enum
  {
    INCREASING,
    DECREASING
  } SubarrayType;

  SubarrayType subarray_type = INCREASING;
  int start_index = 0;

  for (int i = 1; i <= A.size(); ++i)
  {
    if (i == A.size() || (A[i - 1] < A[i] && subarray_type == DECREASING) || (A[i - 1] >= A[i] && subarray_type == INCREASING))
    {
      if (subarray_type == INCREASING)
      {
        sorted_subarrays.emplace_back(A.cbegin() + start_index, A.cbegin() + i);
      }
      else
      {
        sorted_subarrays.emplace_back(A.crbegin() + A.size() - i, A.crbegin() + A.size() - start_index);
      }
      start_index = i;
      subarray_type = (subarray_type == INCREASING ? DECREASING : INCREASING);
    }
  }

  // Now have sorted arrays, leverage 10.1 MergeSortedArrays
  std::vector<int> result = MergeSortedArrays(sorted_subarrays);
  return result;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "sort_increasing_decreasing_array.cc",
                         "sort_increasing_decreasing_array.tsv",
                         &SortKIncreasingDecreasingArray, DefaultComparator{},
                         param_names);
}
