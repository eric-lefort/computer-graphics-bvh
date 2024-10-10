#include "ray_intersect_triangle.h"
#include <Eigen/Dense>

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  // normal
  Eigen::RowVector3d x;
  Eigen::RowVector3d n = (B - A).cross(C-A);
  if (n.dot(ray.direction) == 0) {
    return false;
  }

  n /= n.norm();

  Eigen::Matrix3d m;
  m.col(0) = A-B;
  m.col(1) = A-C;
  m.col(2) = ray.direction;

  x = m.colPivHouseholderQr().solve(A.transpose() - ray.origin).transpose();
  double beta = x[0];
  double gamma = x[1];
  t = x[2];

  if ((t < min_t) || t > max_t || !(beta > 0 && gamma > 0 && beta + gamma < 1)) {
    return false;
  }

  return true;
  ////////////////////////////////////////////////////////////////////////////
}