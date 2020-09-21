#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockOnce(const vector<double>& prices) {
  // time O(n), space O(1)
  double min_price = std::numeric_limits<double>::max();
  double max_profit = 0;

  for (const double & price : prices)
  {
    min_price = std::min(min_price, price);
    max_profit = std::max(max_profit, price - min_price);
  }

  return max_profit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}
