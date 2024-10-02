#include "ray_intersect_triangle.h"

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  t = 0;
  return false;
  ////////////////////////////////////////////////////////////////////////////
}



///// PREV ASSIGNMENT



bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  ////////////////////////////////////////////////////////////////////////////
  
  Eigen::Vector3d a, b, c, x;
  double beta, gamma;
  a = std::get<0>(this->corners);
  b = std::get<1>(this->corners);
  c = std::get<2>(this->corners);

  // early terminate if ray is parallel to plane
  n = (b-a).cross(c-a);
  if (n.dot(ray.direction) == 0) {
    return false;
  }

  n /= n.norm();

  Eigen::Matrix3d m;
  m.col(0) = a-b;
  m.col(1) = a-c;
  m.col(2) = ray.direction;

  x = m.colPivHouseholderQr().solve(a - ray.origin);
  beta = x[0];
  gamma = x[1];
  t = x[2];

  if ((t < min_t) || !(beta > 0 && gamma > 0 && beta + gamma < 1)) {
    return false;
  }

  return true;
}