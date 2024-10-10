#include "insert_box_into_box.h"

double min(const double a, const double b) {
  return b < a ? b : a;
}
double max(const double a, const double b) {
  return b > a ? b : a;
}

void insert_box_into_box(
  const BoundingBox & A,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////

  // BOX has min corner and max corner, simply compare these to B's corners

  Eigen::RowVector3d min_corner, max_corner;

  B.min_corner(0) = min(A.min_corner(0), B.min_corner(0));
  B.min_corner(1) = min(A.min_corner(1), B.min_corner(1));
  B.min_corner(2) = min(A.min_corner(2), B.min_corner(2));

  B.max_corner(0) = max(A.max_corner(0), B.max_corner(0));
  B.max_corner(1) = max(A.max_corner(1), B.max_corner(1));
  B.max_corner(2) = max(A.max_corner(2), B.max_corner(2));
}

