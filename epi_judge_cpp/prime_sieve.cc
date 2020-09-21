#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
// Given n, return all primes up to and including n.
vector<int> GeneratePrimes(int n) {
  // time O(n log log n), space O(n)
  std::vector<int> primes;
  
  std::deque<bool> sieve(n + 1, true);
  sieve[0] = sieve[1] = false;

  for (int p = 2; p <= n; ++p)
  {
    if (sieve[p])
      primes.emplace_back(p);
     
    for (int i = p * 2; i <= n; i += p)
      sieve[i] = false;
  }

  return primes;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "prime_sieve.cc", "prime_sieve.tsv",
                         &GeneratePrimes, DefaultComparator{}, param_names);
}
