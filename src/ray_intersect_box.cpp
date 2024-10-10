#include "ray_intersect_box.h"

double max3(const double a, const double b, const double c) {
  double max_ab = b > a ? b : a;
  return c > max_ab ? c : max_ab;
}

double min3(const double a, const double b, const double c) {
  double min_ab = b < a ? b : a;
  return c < min_ab ? c : min_ab;
}

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:

  double t_x_min = -std::numeric_limits<double>::infinity();
  double t_x_max = std::numeric_limits<double>::infinity();
  double t_y_min = -std::numeric_limits<double>::infinity();
  double t_y_max = std::numeric_limits<double>::infinity();
  double t_z_min = -std::numeric_limits<double>::infinity();
  double t_z_max = std::numeric_limits<double>::infinity();

  // AABB
  /// compute min_t, max_t for collisions across all dimensions
  // x-dimension
  double x_min = box.min_corner(0);
  double x_max = box.max_corner(0);

  if (ray.direction(0) == 0 && 
      (x_min >= ray.origin(0) || ray.origin(0) >= x_max)) 
  {
    // origin outside box
    return false;
  }

  t_x_min = (x_min - ray.origin(0)) / ray.direction(0);
  t_x_max = (x_max - ray.origin(0)) / ray.direction(0);

  // y-dimension
  double y_min = box.min_corner(1);
  double y_max = box.max_corner(1);

  if (ray.direction(1) == 0 && 
      (y_min >= ray.origin(1) || ray.origin(1) >= y_max)) 
  {
    // origin outside box
    return false;
  }

  t_y_min = (y_min - ray.origin(1)) / ray.direction(1);
  t_y_max = (y_max - ray.origin(1)) / ray.direction(1);
  
  // z-dimension
  double z_min = box.min_corner(2);
  double z_max = box.max_corner(2);

  if (ray.direction(2) == 0 && 
      (z_min >= ray.origin(2) || ray.origin(2) >= z_max)) 
  {
    // origin outside box
    return false;
  }

  t_z_min = (z_min - ray.origin(2)) / ray.direction(2);
  t_z_max = (z_max - ray.origin(2)) / ray.direction(2);


  // intersect the three intervals
  double lower = max3(t_x_min, t_y_min, t_z_min);
  double upper = min3(t_x_max, t_y_max, t_z_max);
  lower = lower > min_t ? lower : min_t;
  upper = upper > max_t ? upper : max_t;
  return lower <= upper;
}
