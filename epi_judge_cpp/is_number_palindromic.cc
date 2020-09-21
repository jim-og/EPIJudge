#include "test_framework/generic_test.h"
bool IsPalindromeNumber(int x) { // 121
  
	if (x <= 0)
		return x == 0;

	const int digits = static_cast<int>(log10(x)) + 1;
	int msd_mask = static_cast<int>(pow(10, digits - 1));

	for (int i = 0; i < (digits / 2); ++i)
	{
		int msd = x / msd_mask;
		int lsd = x % 10;

		if (msd != lsd)
			return false;

		x %= msd_mask; // remove msd
		x /= 10; // remove lsd
		msd_mask /= 100;
		
	}

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "is_number_palindromic.cc",
                         "is_number_palindromic.tsv", &IsPalindromeNumber,
                         DefaultComparator{}, param_names);
}
