#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> PlusOne(vector<int> A) {
  // {1,2,9} => {1,3,0}
  // {9,9,9} => {1,0,0,0}

  // time O(n^2), space O(n), 47 us
  //std::vector<int> result;
  //int index = A.size() - 1;
  //int carry = 1;

  //while (index >= 0)
  //{
  //  int num = A.at(index--) + carry;
  //  result.emplace(result.begin(), num % 10);
  //  carry = num / 10;
  //}

  //if (carry > 0)
  //  result.emplace(result.begin(), carry);

  // time O(n), space O(1), 5us
  ++A.back();

  for (int i = A.size() - 1; i > 0; --i)
  {
    if (A.at(i) == 10)
    {
      ++A.at(i - 1);
      A.at(i) = 0;
    }
    else
      break;
  }

  if (A.front() == 10)
  {
    A.front() = 1;
    A.emplace_back(0);
  }

  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "int_as_array_increment.cc",
                         "int_as_array_increment.tsv", &PlusOne,
                         DefaultComparator{}, param_names);
}
