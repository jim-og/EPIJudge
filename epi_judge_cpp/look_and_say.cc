#include <string>

#include "test_framework/generic_test.h"
using std::string;

std::string NextNumber(const std::string & s)
{
  // time O(n*2^n)
  std::string result;
  for (int i = 0; i < s.size(); ++i)
  {
    int count = 1;
    while (i + 1 < size(s) && s[i] == s[i + 1])
      ++i, ++count;
    result += std::to_string(count) + s[i];
  }

  return result;
}

string LookAndSay(int n) {
  
  std::string s = "1";

  for (int i = 1; i < n; ++i)
    s = NextNumber(s);

  return s;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "look_and_say.cc", "look_and_say.tsv",
                         &LookAndSay, DefaultComparator{}, param_names);
}
