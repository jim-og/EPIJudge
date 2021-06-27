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

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "sorted_arrays_merge.cc",
                         "sorted_arrays_merge.tsv", &MergeSortedArrays,
                         DefaultComparator{}, param_names);
}
