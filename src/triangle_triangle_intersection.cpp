#include "triangle_triangle_intersection.h"
#include <iostream>
#include <Eigen/Dense> // For vector math

inline int sign(double val) {
  return (int)(0 < val) - (int)(val < 0);
}

bool triangle_triangle_intersection(
  const Eigen::RowVector3d & A0,
  const Eigen::RowVector3d & A1,
  const Eigen::RowVector3d & A2,
  const Eigen::RowVector3d & B0,
  const Eigen::RowVector3d & B1,
  const Eigen::RowVector3d & B2)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  ////////////////////////////////////////////////////////////////////////////
  
  // fast triangle-triangle intersection test
  // https://web.stanford.edu/class/cs277/resources/papers/Moller1997b.pdf
  
  
  Eigen::RowVector3d t, s, u;
  int sign0, sign1, sign2;
  const double epsilon = std::numeric_limits<double>::epsilon();

  // 1. Compute plane equation of triangle 2. N2.dot(p) + d2 = 0
  Eigen::RowVector3d N2 = (B1 - B0).cross(B2 - B0);
  double d2 = -N2.dot(B0);

  // 2. Reject as trivial if all points of triangle 1 are on same side.
  sign0 = sign(N2.dot(A0) + d2);
  sign1 = sign(N2.dot(A1) + d2);
  sign2 = sign(N2.dot(A2) + d2);

  if (sign0 == sign1 && sign1 == sign2)
    return false;
  
  if (sign0 == 0)
    std::cout << "HANDLE COPLANAR CASE!\n";

  // 3. Compute plane equation of triangle 1.
  Eigen::RowVector3d N1 = (A1 - A0).cross(A2 - A0);
  double d1 = -N1.dot(A0);
  
  // 4. Reject as trivial if all points of triangle 2 are on same side.
  sign0 = sign(N1.dot(B0) + d1);
  sign1 = sign(N1.dot(B1) + d1);
  sign2 = sign(N1.dot(B2) + d1);

  if (sign0 == sign1 && sign1 == sign2)
    return false;
  
  if (sign0 == 0)
    std::cout << "HANDLE COPLANAR CASE!\n";
  
  // 5. Compute intersection line and project onto largest axis.
  
  // first equation gives z(x,y)
  // z = (normal_a.dot(A0) - normal_a(0)*x - normal_a(1)*y) / normal_a(2)
  // second equation, plug in z(x,y)
  // 0 = normal_b(0)*x + normal_b(1)*y + normal_b(2)*z - normal_b.dot(B0)

  // I struggled with this for a bit, now imma base myself off an online solution for intersecting planes
  // https://www.kristakingmath.com/blog/parametric-equations-intersection-of-planes
  // damn its actually insanely easy, cant believe I couldn't 
  // figure out the cross of the normals was along the line

  // cross product of plane normals
  Eigen::RowVector3d normal_cross = N1.cross(N2);

  // find point on line CORRECTION: we don't need this point as we do not care about any 
  // offset, we project and compare onto translated version of the intersection line
  // have removed a bunch of ugly code

  // identify most closely aligned axis
  int dim;
  normal_cross.array().abs().maxCoeff(&dim);
  
  // project vertices onto most closely aligned coordinate axis to intersection line
  double p_A0 = A0(dim);
  double p_A1 = A1(dim);
  double p_A2 = A2(dim);
  double p_B0 = B0(dim);
  double p_B1 = B1(dim);
  double p_B2 = B2(dim);


  // 6. Compute the intervals for each triangle.
  double t1, t2, s1, s2;

  // while projecting to 1 dimension, we need a weighting to compute 
  // the actual intersection with line L, use signed distances to plane
  double d_v0 = N1.dot(B0) + d1;
  double d_v1 = N1.dot(B1) + d1;
  double d_v2 = N1.dot(B2) + d1;
  // identify the edges crossing the plane
  if (sign0 == sign1) {
    t1 = p_B0 + (p_B2 - p_B0) * d_v0 / (d_v0 - d_v2);
    t2 = p_B1 + (p_B2 - p_B1) * d_v1 / (d_v1 - d_v2);
  } else if (sign0 == sign2) {
    t1 = p_B0 + (p_B1 - p_B0) * d_v0 / (d_v0 - d_v1);
    t2 = p_B2 + (p_B1 - p_B2) * d_v2 / (d_v2 - d_v1);
  } else /* sign1 == sign2 */ {
    t1 = p_B1 + (p_B0 - p_B1) * d_v1 / (d_v1 - d_v0);
    t2 = p_B2 + (p_B0 - p_B2) * d_v2 / (d_v2 - d_v0);
  }
  
  d_v0 = N2.dot(A0) + d2;
  d_v1 = N2.dot(A1) + d2;
  d_v2 = N2.dot(A2) + d2;

  sign0 = sign(d_v0);
  sign1 = sign(d_v1);
  sign2 = sign(d_v2);

  if (sign0 == sign1) {
    s1 = p_A0 + (p_A2 - p_A0) * d_v0 / (d_v0 - d_v2);
    s2 = p_A1 + (p_A2 - p_A1) * d_v1 / (d_v1 - d_v2);
  } else if (sign0 == sign2) {
    s1 = p_A0 + (p_A1 - p_A0) * d_v0 / (d_v0 - d_v1);
    s2 = p_A2 + (p_A1 - p_A2) * d_v2 / (d_v2 - d_v1);
  } else /* sign1 == sign2 */ {
    s1 = p_A1 + (p_A0 - p_A1) * d_v1 / (d_v1 - d_v0);
    s2 = p_A2 + (p_A0 - p_A2) * d_v2 / (d_v2 - d_v0);
  }

  // 7. Intersect the intervals
  double t_max = t2 > t1 ? t2 : t1; // max
  double s_max = s2 > s1 ? s2 : s1;
  t1 = t2 < t1 ? t2 : t1; // min
  s1 = s2 < s1 ? s2 : s1;
  return (
    (s1 < t_max && t_max < s2) ||
    (t1 < s_max && s_max < t2)
  );
}
