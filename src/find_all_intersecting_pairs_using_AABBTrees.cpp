#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list>
#include <iostream>
#define left_child(node) (std::dynamic_pointer_cast<AABBTree>(node->left))
#define right_child(node) (std::dynamic_pointer_cast<AABBTree>(node->right))

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  // check readme
  // iterative BFS

  std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>> node_pair;
  std::shared_ptr<AABBTree> nodeA, nodeB;
  std::list<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>>> Q;

  // leaf_pairs ← {}  already init

  if (box_box_intersect(rootA->box, rootB->box)) {
    Q.push_back( std::make_pair(rootA, rootB) );
  }
  while (!Q.empty()) {
    // {nodeA,nodeB} ← Q.pop
    node_pair = Q.back();
    Q.pop_back();
    nodeA = std::dynamic_pointer_cast<AABBTree>(node_pair.first);
    nodeB = std::dynamic_pointer_cast<AABBTree>(node_pair.second);

    // DEBUG

    // std::cout << "QUEUE OP: #" << count 
    //           << " | nodeA n_leaf: " << nodeA->num_leaves
    //           << " left: " << nodeA->left
    //           << " right: " << nodeA->right
    //           << " | nodeB n_leaf: " << nodeB->num_leaves
    //           << " left: " << nodeB->left
    //           << " right: " << nodeB->right
    //           << std::endl;

    if (nodeA->num_leaves == 1 && nodeB->num_leaves == 1) {
      leaf_pairs.push_back( std::make_pair(nodeA->left, nodeB->left) );
    } else if (nodeA->num_leaves == 1) {
      if (box_box_intersect(nodeA->box, nodeB->left->box))
        Q.push_back( std::make_pair(nodeA, nodeB->left) );
      if (box_box_intersect(nodeA->box, nodeB->right->box))
        Q.push_back( std::make_pair(nodeA, nodeB->right) );
    } else if (nodeB->num_leaves == 1) {
      if (box_box_intersect(nodeA->left->box, nodeB->box))
        Q.push_back( std::make_pair(nodeA->left, nodeB) );
      if (box_box_intersect(nodeA->right->box, nodeB->box))
        Q.push_back( std::make_pair(nodeA->right, nodeB) );
    } else {
      if (box_box_intersect(nodeA->left->box, nodeB->left->box))
        Q.push_back( std::make_pair(nodeA->left, nodeB->left) );
      if (box_box_intersect(nodeA->left->box, nodeB->right->box))
        Q.push_back( std::make_pair(nodeA->left, nodeB->right) );
      if (box_box_intersect(nodeA->right->box, nodeB->right->box))
        Q.push_back( std::make_pair(nodeA->right, nodeB->right) );
      if (box_box_intersect(nodeA->right->box, nodeB->left->box))
        Q.push_back( std::make_pair(nodeA->right, nodeB->left) );
    }
  }
}
