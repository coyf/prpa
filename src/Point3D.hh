#ifndef POINT3D_HH
# define POINT3D_HH

namespace Geometry
{
  class Point3D
  {
  public:
    Point3D(double x, double y, double z);
    ~Point3D();

    double getX() const;
    double getY() const;
    double getZ() const;

    void setX(double x);
    void setY(double y);
    void setZ(double z);

    double dist(Point3D pt);
  private:
    double x_;
    double y_;
    double z_;
  };
}

#endif /* !POINT3D_HH */
