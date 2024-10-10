#include "AABBTree.h"
// #include <iostream>

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  // Check current node (preorder traversal)
  if (! ray_intersect_box(ray, this->box, min_t, max_t))
    return false;

  // termination case
  if (this->num_leaves == 0) {
    return false;
  } else if (this->num_leaves == 1) {
    bool intersect = this->left->ray_intersect(ray, min_t, max_t, t, descendant);
    descendant = this->left;
    return intersect;
  }

  // checking left and right subtrees
  double t_left, t_right;
  bool intersect_left, intersect_right;
  std::shared_ptr<Object> descendant_left, descendant_right;
  intersect_left = left->ray_intersect(ray, min_t, max_t, t_left, descendant_left);
  intersect_right = right->ray_intersect(ray, min_t, max_t, t_right, descendant_right);

  if (intersect_left && intersect_right) {
    if (t_right < t_left) {
      t = t_right;
      descendant = descendant_right;
    } else {
      t = t_left;
      descendant = descendant_left;
    }
    return true;
  } else if (intersect_left) {
    t = t_left;
    descendant = descendant_left;
    return true;
  } else if (intersect_right) {
    t = t_right;
    descendant = descendant_right;
    // std::cout << "t: " << t << std::endl;
    // std::cout << "num_leaves: " << num_leaves << std::endl;
    // std::cout << "depth: " << depth << std::endl;
    // std::cout << "descendant: " << descendant << std::endl;
    return true;
  }

  return false;

  // TODO: implement interative solution using priority queue
}

