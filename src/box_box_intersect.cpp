#include "box_box_intersect.h"

#define min(a, b) b < a ? b : a
#define max(a, b) b > a ? b : a

bool box_box_intersect(
  const BoundingBox & A,
  const BoundingBox & B)
{
  // intersect x, y, and z intervals
  Eigen::Vector3d min_corner = A.min_corner.cwiseMax(B.min_corner);
  Eigen::Vector3d max_corner = A.max_corner.cwiseMin(B.max_corner);

  // intersect three previous intervals
  return (min_corner.array() <= max_corner.array()).all();
}

