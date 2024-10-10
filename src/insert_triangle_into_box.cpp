#include "insert_triangle_into_box.h"

#define min(a, b) (b < a ? b : a)
#define max(a, b) (b > a ? b : a)

void insert_triangle_into_box(
  const Eigen::RowVector3d & a,
  const Eigen::RowVector3d & b,
  const Eigen::RowVector3d & c,
  BoundingBox & B)
{
  // min and max of x,y,z, across three vertices
  B.min_corner(0) = min(a(0), B.min_corner(0));
  B.min_corner(1) = min(a(1), B.min_corner(1));
  B.min_corner(2) = min(a(2), B.min_corner(2));
  
  B.min_corner(0) = min(b(0), B.min_corner(0));
  B.min_corner(1) = min(b(1), B.min_corner(1));
  B.min_corner(2) = min(b(2), B.min_corner(2));
  
  B.min_corner(0) = min(c(0), B.min_corner(0));
  B.min_corner(1) = min(c(1), B.min_corner(1));
  B.min_corner(2) = min(c(2), B.min_corner(2));

  // 
  B.max_corner(0) = max(a(0), B.max_corner(0));
  B.max_corner(1) = max(a(1), B.max_corner(1));
  B.max_corner(2) = max(a(2), B.max_corner(2));
  
  B.max_corner(0) = max(b(0), B.max_corner(0));
  B.max_corner(1) = max(b(1), B.max_corner(1));
  B.max_corner(2) = max(b(2), B.max_corner(2));
  
  B.max_corner(0) = max(c(0), B.max_corner(0));
  B.max_corner(1) = max(c(1), B.max_corner(1));
  B.max_corner(2) = max(c(2), B.max_corner(2));
}


