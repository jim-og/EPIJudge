#include <string>
#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

int FindNearestRepetition(const vector<string> &paragraph)
{
  std::unordered_map<std::string, int> word_latest_index;
  int nearest_repeated_distance = std::numeric_limits<double>::max();
  bool repetition_found = false;

  for (int i = 0; i < paragraph.size(); ++i)
  {
    auto it = word_latest_index.find(paragraph[i]);
    if (it != word_latest_index.end())
    {
      nearest_repeated_distance = std::min(nearest_repeated_distance, i - it->second);
      repetition_found = true;
    }
    word_latest_index[paragraph[i]] = i;
  }

  return repetition_found ? nearest_repeated_distance : -1;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"paragraph"};
  return GenericTestMain(args, "nearest_repeated_entries.cc",
                         "nearest_repeated_entries.tsv", &FindNearestRepetition,
                         DefaultComparator{}, param_names);
}
