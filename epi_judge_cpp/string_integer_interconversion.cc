#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(int x) {
  // time O(n), space(n)
  bool negative = x < 0;
  std::string s;

  do
  {
    s += '0' + abs(x % 10);
    x /= 10;
  } while (x);

  s += negative ? "-" : "";

  // Reverse
  return {s.rbegin(), s.rend()};
}
int StringToInt(const string& s) {
  // time O(n), space O(1)
  return (s[0] == '-' ? -1 : 1) * std::accumulate(s.begin() + (s[0] == '-' || s[0] == '+'), s.end(), 
    0, [](int sum, char c) {return sum * 10 + c - '0'; });
}
void Wrapper(int x, const string& s) {
  if (stoi(IntToString(x)) != x) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}
