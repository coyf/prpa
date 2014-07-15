#ifndef PARALLEL_OUTPUT_IMAGE_HH
# define PARALLEL_OUTPUT_IMAGE_HH

# include <vector>
# include <stdlib.h>
# include <Magick++.h>
# include <tbb/blocked_range.h>
# include <tbb/parallel_for.h>
# include "Point3D.hh"

using namespace Magick;

namespace Parallel
{
  class Parallel_output_image
  {
  public:
    Parallel_output_image(std::vector<std::vector<Geometry::Point3D>> neurons,
                          PixelPacket* pixels,
                          ssize_t cols);
    void operator()(const tbb::blocked_range<size_t>& r) const;
  private:
    std::vector<std::vector<Geometry::Point3D>> neurons_;
    PixelPacket* pixels_;
    ssize_t cols_;
  };
}

#endif /* !PARALLEL_OUTPUT_IMAGE_HH */
