#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start,
                                         int finish) {

  class Point
  {
  public:
    Point(double x, double y) { x_ = x, y_ = y; }
    ~Point() {};
    double GetX() { return x_; }
    double GetY() { return y_; }
  private:
    double x_;
    double y_;
  };



  std::vector<Point> points;
  for (double i=0.0; i < 10.0; i++)
    points.emplace_back(Point(i, i+5.0));

  double value = 7.0;

  auto test = std::lower_bound(points.begin(), points.end(), value, [](Point & point, double rhs) {return point.GetY() < rhs;});


  shared_ptr<ListNode<int>> dummy_head = make_shared<ListNode<int>>(ListNode<int>{0, L});
  shared_ptr<ListNode<int>> sublist_head = dummy_head;

  int k = 1;
  while (k++ < start)
  {
    sublist_head = sublist_head->next;
  }

  // Reverse sublist
  shared_ptr<ListNode<int>> sublist_iter = sublist_head->next;
  while (start++ < finish)
  {
    shared_ptr<ListNode<int>> temp = sublist_iter->next;
    sublist_iter->next = temp->next;
    temp->next = sublist_head->next;
    sublist_head->next = temp;
  }

  return dummy_head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "start", "finish"};
  return GenericTestMain(args, "reverse_sublist.cc", "reverse_sublist.tsv",
                         &ReverseSublist, DefaultComparator{}, param_names);
}
