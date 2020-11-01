#include <memory>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

vector<vector<int>> BinaryTreeDepthOrder(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
  
  vector<vector<int>> result;
  
  if (!tree.get())
    // Empty tree
    return result;
  
  std::queue<BinaryTreeNode<int> *> curr_depth_nodes({ tree.get() });

  while (!curr_depth_nodes.empty())
  {
    std::queue<BinaryTreeNode<int> *> next_depth_nodes;
    std::vector<int> this_level;

    while (!curr_depth_nodes.empty())
    {
      // Get front node and remove
      auto curr = curr_depth_nodes.front();
      curr_depth_nodes.pop();

      this_level.emplace_back(curr->data);

      if (curr->left)
        next_depth_nodes.emplace(curr->left.get());
      if (curr->right)
        next_depth_nodes.emplace(curr->right.get());
    }
    result.emplace_back(this_level);
    curr_depth_nodes = next_depth_nodes;
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_level_order.cc", "tree_level_order.tsv",
                         &BinaryTreeDepthOrder, DefaultComparator{},
                         param_names);
}
