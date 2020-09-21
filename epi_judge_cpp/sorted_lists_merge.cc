#include "list_node.h"
#include "test_framework/generic_test.h"
shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1,
                                              shared_ptr<ListNode<int>> L2) {
  
  // time O(n + m), space O(1)
  shared_ptr<ListNode<int>> dummy_head(new ListNode<int>);
  shared_ptr<ListNode<int>> tail = dummy_head;

  while (L1 && L2)
  {
    shared_ptr<ListNode<int>> * node = L1->data < L2->data ? &L1 : &L2;
    tail->next = *node;
    tail = *node;
    *node = (*node)->next;
  }

  // Append the remaining nodes of L1 or L2
  tail->next = L1 ? L1 : L2;
  return dummy_head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L1", "L2"};
  return GenericTestMain(args, "sorted_lists_merge.cc",
                         "sorted_lists_merge.tsv", &MergeTwoSortedLists,
                         DefaultComparator{}, param_names);
}
