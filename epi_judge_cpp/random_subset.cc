#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <vector>
#include <random>

#include "test_framework/generic_test.h"
#include "test_framework/random_sequence_checker.h"
#include "test_framework/timed_executor.h"
using std::bind;
using std::iota;
using std::vector;
// Returns a random k-sized subset of {0, 1, ..., n - 1}.
vector<int> RandomSubset(int n, int k) {
  // time O(k), space O(k)
  std::unordered_map<int, int> changed_elements;
  std::default_random_engine seed((std::random_device())());

  for (int i = 0; i < k; ++i)
  {
    int random_index = std::uniform_int_distribution<int>{ i, n - 1 }(seed);
    auto ptr_1 = changed_elements.find(random_index);
    auto ptr_2 = changed_elements.find(i);

    if (ptr_1 == changed_elements.end() && ptr_1 == changed_elements.end())
    {
      // Neither index is in changed_elements
      changed_elements[random_index] = i;
      changed_elements[i] = random_index;
    }
    else if (ptr_1 == changed_elements.end() && ptr_2 != changed_elements.end())
    {
      changed_elements[random_index] = ptr_2->second;
      ptr_2->second = random_index;
    }
    else if (ptr_1 != changed_elements.end() && ptr_2 == changed_elements.end())
    {
      changed_elements[i] = ptr_1->second;
      ptr_1->second = i;
    }
    else
    {
      int temp = ptr_2->second;
      changed_elements[i] = ptr_1->second;
      changed_elements[random_index] = temp;
    }
  }

  std::vector<int> result;
  result.reserve(k);
  for (int i = 0; i < k; ++i)
    result.emplace_back(changed_elements[i]);

  return result;
}
bool RandomSubsetRunner(TimedExecutor& executor, int n, int k) {
  using namespace test_framework;
  vector<vector<int>> results;

  executor.Run([&] {
    std::generate_n(back_inserter(results), 100000,
                    std::bind(RandomSubset, n, k));
  });

  int total_possible_outcomes = BinomialCoefficient(n, k);
  vector<int> A(n);
  iota(begin(A), end(A), 0);
  vector<vector<int>> combinations;
  for (int i = 0; i < BinomialCoefficient(n, k); ++i) {
    combinations.emplace_back(ComputeCombinationIdx(A, n, k, i));
  }
  vector<int> sequence;
  for (vector<int> result : results) {
    sort(begin(result), end(result));
    sequence.emplace_back(
        distance(begin(combinations),
                 find(begin(combinations), end(combinations), result)));
  }
  return CheckSequenceIsUniformlyRandom(sequence, total_possible_outcomes,
                                        0.01);
}

void RandomSubsetWrapper(TimedExecutor& executor, int n, int k) {
  RunFuncWithRetries(bind(RandomSubsetRunner, std::ref(executor), n, k));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "n", "k"};
  return GenericTestMain(args, "random_subset.cc", "random_subset.tsv",
                         &RandomSubsetWrapper, DefaultComparator{},
                         param_names);
}
