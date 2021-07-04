#include <string>
#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

vector<vector<string>> FindAnagrams(const vector<string> &dictionary)
{
  std::unordered_map<std::string, std::vector<std::string>> sorted_string_to_anagrams;

  for (const std::string &entry : dictionary)
  {
    std::string sorted_string = std::string(entry);
    std::sort(sorted_string.begin(), sorted_string.end());
    sorted_string_to_anagrams[sorted_string].emplace_back(entry);
  }

  std::vector<std::vector<std::string>> anagram_groups;
  for (const auto &entry : sorted_string_to_anagrams)
    if (entry.second.size() >= 2)
      anagram_groups.emplace_back(entry.second);

  return anagram_groups;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"dictionary"};
  return GenericTestMain(args, "anagrams.cc", "anagrams.tsv", &FindAnagrams,
                         UnorderedComparator{}, param_names);
}
