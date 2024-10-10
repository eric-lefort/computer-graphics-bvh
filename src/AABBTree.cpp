#include "AABBTree.h"
#include "insert_box_into_box.h"
#include <algorithm>
// #include <iostream>

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  // construct bounding box for objects
  for (int i = 0; i < num_leaves; i++) {
    insert_box_into_box(objects[i]->box, this->box);
  }
  // construct binary tree
  if (num_leaves == 0) {
    // std::cout<<"ERROR: 0 elem AABB tree\n";
    exit(1);
  } else if (num_leaves == 1) {
    left = objects[0];
    return;
  }

  Eigen::RowVector3d range = this->box.max_corner - this->box.min_corner;
  int longest_dim;
  range.maxCoeff(&longest_dim);

  // SORTING METHOD, produces a balanced tree
  // sort along longest axis, based on min_corner
  auto sort_func = [&longest_dim](std::shared_ptr<Object> obj_a, std::shared_ptr<Object> obj_b) {
    return obj_a->box.min_corner(longest_dim) < obj_b->box.min_corner(longest_dim);
  };
  std::vector<std::shared_ptr<Object>> sortedObjects = objects;
  std::sort(sortedObjects.begin(), sortedObjects.end(), sort_func);

  // split tree such that half elements are in left and right subtrees
  const std::vector<std::shared_ptr<Object>> left_objects(sortedObjects.begin(), sortedObjects.begin() + sortedObjects.size() / 2);
  const std::vector<std::shared_ptr<Object>> right_objects(sortedObjects.begin() + sortedObjects.size() / 2, sortedObjects.end());

  // // Distance-based split, faster to compute, provided objects are reasonably distributed
  // std::vector<std::shared_ptr<Object>> left_objects;
  // std::vector<std::shared_ptr<Object>> right_objects;
  // double threshold = (this->box.max_corner(longest_dim) + this->box.min_corner(longest_dim)) / 2;
  // Eigen::RowVector3d center;

  // for (const auto& obj : objects) {
  //   center = obj->box.center()
  //   if (center(longest_dim) < threshold)
  //     left_objects.push_back(obj);
  //   else
  //     right_objects.push_back(obj);
  // }

  left = std::make_shared<AABBTree>(left_objects, depth + 1);
  right = std::make_shared<AABBTree>(right_objects, depth + 1);  
}
