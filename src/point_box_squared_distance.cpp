#include "point_box_squared_distance.h"
#include <cmath>
#include <iostream>
#define min(a,b) b < a ? b : a

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  ////////////////////////////////////////////////////////////////////////////
  

  Eigen::Array3d min_dist = (query - box.min_corner).array().abs();
  Eigen::Array3d max_dist = (query - box.max_corner).array().abs();
  double x_dist, y_dist, z_dist;

  // dims overlap ? 0 : smaller of dist(q, min_corner), dist(q, max_corner)
  x_dist = (box.min_corner(0) < query(0) && query(0) < box.max_corner(0)) ? 0 
    : min(min_dist(0), max_dist(0));
  y_dist = (box.min_corner(1) < query(1) && query(1) < box.max_corner(1)) ? 0 
    : min(min_dist(1), max_dist(1));
  z_dist = (box.min_corner(2) < query(2) && query(2) < box.max_corner(2)) ? 0 
    : min(min_dist(2), max_dist(2));
  
  return x_dist*x_dist + y_dist*y_dist + z_dist*z_dist;
}
