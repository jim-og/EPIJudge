#include <string>
#include <stack>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;
bool IsWellFormed(const string& s) {
  std::stack<char> left_chars;

  std::unordered_map<char, char> lookup = {
    {'(', ')'},
    {'[', ']'},
    {'{', '}'},
  };

  for (const char & entry : s)
  {
    if (lookup.count(entry))
      left_chars.emplace(entry);
    else
    {
      if (left_chars.empty() || lookup[left_chars.top()] != entry)
        return false;
      left_chars.pop();
    }
  }
  return left_chars.empty();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_valid_parenthesization.cc",
                         "is_valid_parenthesization.tsv", &IsWellFormed,
                         DefaultComparator{}, param_names);
}
