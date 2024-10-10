#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  I = -1;
  sqrD = std::numeric_limits<double>::infinity();
  double sq_dist;
  Eigen::RowVector3d point;
  for (int i = 0; i < points.rows(); i++) {
    point = points.row(i);
    sq_dist = (query - point).squaredNorm();
    if (sq_dist < sqrD) {
      I = i;
      sqrD = sq_dist;
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
