#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

vector<double> OnlineMedian(vector<int>::const_iterator sequence_begin,
                            const vector<int>::const_iterator &sequence_end)
{
  std::vector<double> result;
  // max_heap stores the smaller half (max at top)
  std::priority_queue<double, std::vector<double>> max_heap;
  // min_heap stores the larger half (min at top)
  std::priority_queue<double, std::vector<double>, std::greater<>> min_heap;

  std::vector<int>::const_iterator it = sequence_begin;
  while (it != sequence_end)
  {
    double entry = *it;
    if (min_heap.empty())
    {
      // First entry
      min_heap.emplace(entry);
    }
    else
    {
      if (*it > min_heap.top())
        min_heap.emplace(entry);
      else
        max_heap.emplace(entry);
    }

    // Ensure heaps are balanced:
    // * if even, same number in each
    // * if odd, +1 in min_heap
    if (min_heap.size() > max_heap.size() + 1)
    {
      max_heap.emplace(min_heap.top());
      min_heap.pop();
    }
    else if (max_heap.size() > min_heap.size())
    {
      min_heap.emplace(max_heap.top());
      max_heap.pop();
    }

    result.emplace_back(
        (min_heap.size() == max_heap.size())
            ? 0.5 * (min_heap.top() + max_heap.top())
            : min_heap.top());

    ++it;
  }

  return result;
}
vector<double> OnlineMedianWrapper(const vector<int> &sequence)
{
  return OnlineMedian(cbegin(sequence), cend(sequence));
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence"};
  return GenericTestMain(args, "online_median.cc", "online_median.tsv",
                         &OnlineMedianWrapper, DefaultComparator{},
                         param_names);
}
