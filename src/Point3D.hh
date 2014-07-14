#ifndef POINT3D_HH
# define POINT3D_HH

namespace Geometry
{
  class Point3D
  {
  public:
    Point3D(int x, int y, int z);
    ~Point3D();

    int getX() const;
    int getY() const;
    int getZ() const;

    void setX(int x);
    void setY(int y);
    void setZ(int z);
  private:
    int x_;
    int y_;
    int z_;
  };
}

#endif /* !POINT3D_HH */
