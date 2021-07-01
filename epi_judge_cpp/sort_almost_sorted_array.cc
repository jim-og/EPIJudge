#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> SortApproximatelySortedData(
    vector<int>::const_iterator sequence_begin,
    const vector<int>::const_iterator &sequence_end, int k)
{

  std::vector<int> results;
  std::priority_queue<int, std::vector<int>, std::greater<>> min_heap;

  vector<int>::const_iterator it = sequence_begin;
  for (int i = 0; i < k; ++i)
  {
    min_heap.emplace(*it);
    ++it;
  }

  while (it != sequence_end)
  {
    min_heap.emplace(*it);
    results.emplace_back(min_heap.top());
    min_heap.pop();
    ++it;
  }

  // Sequence is exhausted, extract remaining elements
  while (!min_heap.empty())
  {
    results.emplace_back(min_heap.top());
    min_heap.pop();
  }

  return results;
}
vector<int> SortApproximatelySortedDataWrapper(const vector<int> &sequence,
                                               int k)
{
  return SortApproximatelySortedData(cbegin(sequence), cend(sequence), k);
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence", "k"};
  return GenericTestMain(
      args, "sort_almost_sorted_array.cc", "sort_almost_sorted_array.tsv",
      &SortApproximatelySortedDataWrapper, DefaultComparator{}, param_names);
}
