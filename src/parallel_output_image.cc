#include "parallel_output_image.hh"

namespace Parallel
{
  Parallel_output_image::
  Parallel_output_image(std::vector<std::vector<Geometry::Point3D>> neurons,
                        PixelPacket* pixels,
                        ssize_t cols)
    : neurons_(neurons),
      pixels_(pixels),
      cols_(cols)
  {
  }

  void
  Parallel_output_image::operator()(const tbb::blocked_range<size_t>& r) const
  {
    for (size_t i = r.begin(); i < r.end(); ++i)
      {
        for (ssize_t column = 0; column < cols_; ++column)
          {
            ColorRGB col(neurons_[column][i].getX(),
                         neurons_[column][i].getY(),
                         neurons_[column][i].getZ());
            *(pixels_ + (cols_ * i + column)) = col;
          }
      }
  }
}
