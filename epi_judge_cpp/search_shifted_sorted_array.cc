#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int SearchSmallest(const vector<int> &A)
{
  int left = 0, right = A.size() - 1;

  while (left < right)
  {
    int mid = left + (0.5 * (right - left));

    if (A[mid] > A[right])
      left = mid + 1;
    else if (A[mid] < A[right])
      right = mid;
  }

  // ends when left == right
  return left;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "search_shifted_sorted_array.cc",
                         "search_shifted_sorted_array.tsv", &SearchSmallest,
                         DefaultComparator{}, param_names);
}
