#include "parallel_nearest.hh"

namespace Parallel
{
  Parallel_nearest::Parallel_nearest(Geometry::Point3D p,
                                     int height,
                                     std::vector<std::vector<Geometry::Point3D>>& neurons)
    : p_(p),
      height_(height),
      neurons_(neurons),
      min_dist_(INT_MAX)
  {
  }

  Parallel_nearest::Parallel_nearest(Parallel_nearest& x, tbb::split)
    : p_(x.p_),
      height_(x.height_),
      neurons_(x.neurons_),
      min_dist_(INT_MAX)
  {
  }

  void
  Parallel_nearest::operator()(const tbb::blocked_range<size_t>& r)
  {
    double min_dist = INT_MAX;
    for (size_t i = r.begin(); i < r.end(); ++i)
      {
        for (int z = 0; z < height_; ++z)
          {
            double dist_tmp = p_.dist(neurons_[i][z]);
            if (dist_tmp < min_dist)
              {
                min_dist = dist_tmp;
                xnearest_ = i;
                ynearest_ = z;
              }
          }
        min_dist_ = std::min(min_dist_, min_dist);
      }
  }

  Geometry::Point3D
  Parallel_nearest::getNearest() const
  {
    return Geometry::Point3D(xnearest_, ynearest_, 0);
  }

  void
  Parallel_nearest::join(const Parallel_nearest& other)
  {
    if (other.min_dist_ < min_dist_)
      {
        xnearest_ = other.xnearest_;
        ynearest_ = other.ynearest_;
        min_dist_ = other.min_dist_;
      }
  }
}
