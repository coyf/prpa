#ifndef PARALLEL_NEAREST_HH
# define PARALLEL_NEAREST_HH

# include "Point3D.hh"
# include <vector>
# include <stdlib.h>
# include <tbb/blocked_range.h>
# include <tbb/parallel_for.h>
# include <climits>

namespace Parallel
{
  class Parallel_nearest
  {
  public:
    Parallel_nearest(Geometry::Point3D p,
                     int height,
                     std::vector<std::vector<Geometry::Point3D>>& 
                     neurons);
    Parallel_nearest(Parallel_nearest& x, tbb::split);
    void operator()(const tbb::blocked_range<size_t>& r);
    Geometry::Point3D getNearest() const;
    void join(const Parallel_nearest& other);
  private:
    Geometry::Point3D p_;
    int height_;
    std::vector<std::vector<Geometry::Point3D>>& neurons_;
    double min_dist_;
    int xnearest_;
    int ynearest_;
  };
}

#endif /* !PARALLEL_NEAREST_HH */
