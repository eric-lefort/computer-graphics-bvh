#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue

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

  // iterative
  // best-first seach
  // priority queue for minimum distane bookkeeping

  // tree contains boxes which we know the min distance to
  // add boxes to queue
  // pop the closest one, if it is a leaf, you are done
  // add children to queue
  // repeat

  
  
  sqrd = 0;
  return false;
}
