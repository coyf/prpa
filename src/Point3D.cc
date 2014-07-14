#include "Point3D.hh"

namespace Geometry
{
  Point3D::Point3D(int x, int y, int z)
    : x_(x),
      y_(y),
      z_(z)
  {
  }

  // Getters
  int Point3D::getX() const
  {
    return x_;
  }

  int Point3D::getY() const
  {
    return y_;
  }

  int Point3D::getZ() const
  {
    return z_;
  }

  // Setters
  void Point3D::setX(int x)
  {
    x_ = x;
  }

  void Point3D::setY(int y)
  {
    y_ = y;
  }

  void Point3D::setZ(int z)
  {
    z_ = z;
  }
}
