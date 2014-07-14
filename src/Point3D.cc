#include <cmath>
#include "Point3D.hh"

namespace Geometry
{
  Point3D::Point3D(double x, double y, double z)
    : x_(x),
      y_(y),
      z_(z)
  {
  }

  Point3D::~Point3D()
  {
  }

  // Getters
  double Point3D::getX() const
  {
    return x_;
  }

  double Point3D::getY() const
  {
    return y_;
  }

  double Point3D::getZ() const
  {
    return z_;
  }

  // Setters
  void Point3D::setX(double x)
  {
    x_ = x;
  }

  void Point3D::setY(double y)
  {
    y_ = y;
  }

  void Point3D::setZ(double z)
  {
    z_ = z;
  }

  // Dist
  double Point3D::dist(Point3D pt)
  {
    double dx = pt.x_ - x_;
    double dy = pt.y_ - y_;
    double dz = pt.z_ - z_;

    return sqrt(dx * dx + dy * dy + dz * dz);
  }
}
