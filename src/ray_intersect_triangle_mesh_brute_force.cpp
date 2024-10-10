#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"
#include <limits>
#include <cmath>

bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  hit_t = std::numeric_limits<double>::infinity();
  Eigen::RowVector3i triangle;
  double hit_t_tmp;
  for (int tri_id = 0; tri_id < F.rows(); tri_id++) {
    triangle = F.row(tri_id);
    if (ray_intersect_triangle(
      ray, 
      V.row(triangle(0)), // A
      V.row(triangle(1)), // B
      V.row(triangle(2)), // C
      min_t, 
      max_t, 
      hit_t_tmp) && hit_t_tmp < hit_t) 
    {
      hit_t = hit_t_tmp;
      hit_f = tri_id;
    }
  }

  return !std::isinf(hit_t);
  ////////////////////////////////////////////////////////////////////////////
}