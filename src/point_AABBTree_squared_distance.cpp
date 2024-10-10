#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue
#include <iostream>

struct distance_node {
  double dist;
  std::shared_ptr<AABBTree> aabb;
};

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  ////////////////////////////////////////////////////////////////////////////
  
  // hard but simple problem

  // priority queue for minimum distance bookkeeping
  double cur_dist = max_sqrd;
  bool possible;
  sqrd = max_sqrd;
  // Specify the priority_queue type and comparator explicitly
  auto cmp = [](const distance_node& left, const distance_node& right) {
    return left.dist > right.dist;  // Min-heap based on distance
  };

  // Priority queue stores pairs of <distance, node>
  std::priority_queue<
    distance_node,
    std::vector<distance_node>,
    decltype(cmp)
  > p_queue(cmp);

  std::shared_ptr<Object> cur_descendant;
  std::shared_ptr<AABBTree> aabb_node;
  distance_node node;
  
  // tree contains boxes which we know the min distance to
  // add boxes to queue
  node.aabb = root;
  node.dist = point_box_squared_distance(query, node.aabb->box);
  p_queue.push(node);

  // pop the closest one
  while (!p_queue.empty()) {
    node = p_queue.top();
    cur_dist = node.dist;
    aabb_node = node.aabb;

    if (node.dist > sqrd) {
      return true;
    }
    p_queue.pop();
    
    // if leaf node, proper distance compute
    if (aabb_node->num_leaves == 1) {
      aabb_node->left->point_squared_distance(query, min_sqrd, max_sqrd, cur_dist, cur_descendant);

      if (cur_dist < sqrd) {
        sqrd = cur_dist;
        descendant = aabb_node->left;
      }
      continue;
    }
    // add left to queue
    node.aabb = std::dynamic_pointer_cast<AABBTree>(aabb_node->left);
    node.dist = point_box_squared_distance(query, node.aabb->box);
    p_queue.push(node);

    // add right to queue
    node.aabb = std::dynamic_pointer_cast<AABBTree>(aabb_node->right);
    node.dist = point_box_squared_distance(query, node.aabb->box);
    p_queue.push(node);
  }
  
  return false;
}
