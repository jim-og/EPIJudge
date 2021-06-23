#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

int GetDepth(const BinaryTreeNode<int>* node)
{
  int depth = 0;

  while (node->parent)
  {
    ++depth;
    node = node->parent;
  }

  return depth;
}

BinaryTreeNode<int>* Lca(const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) 
{
  BinaryTreeNode<int> * it0 = node0.get();
  BinaryTreeNode<int> * it1 = node1.get();

  int depth0 = GetDepth(node0.get());
  int depth1 = GetDepth(node1.get());

  // Make it0 the deepest node
  if (depth1 > depth0)
    std::swap(it0, it1);

  int depth_delta = std::abs(depth0 - depth1);

  while (depth_delta--)
  {
    // Move up until it0 is at the same depth as it1
    it0 = it0->parent;
  }

  while (it0 != it1)
  {
    it0 = it0->parent;
    it1 = it1->parent;
  }

  return it0;
}
int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return Lca(node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor_with_parent.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
