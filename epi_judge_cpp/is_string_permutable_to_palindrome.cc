#include <string>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;

bool CanFormPalindrome(const string &s)
{
  std::unordered_map<char, int> letter_count;
  for (const auto &letter : s)
    ++letter_count[letter];

  // There can be at most 1 odd letter which would sit in the middle,
  // all other letters must have an even frequency
  int odd_frequency_count = 0;
  return std::none_of(letter_count.begin(), letter_count.end(), [&odd_frequency_count](const auto &entry)
                      { return (entry.second % 2) && ++odd_frequency_count > 1; });
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_permutable_to_palindrome.cc",
                         "is_string_permutable_to_palindrome.tsv",
                         &CanFormPalindrome, DefaultComparator{}, param_names);
}
