#ifndef PARALLEL_CUBE_HH
# define PARALLEL_CUBE_HH

# include "Point3D.hh"
# include <vector>
# include <stdlib.h>
# include <tbb/blocked_range.h>
# include <tbb/parallel_for.h>

namespace Parallel
{
    class Parallel_cube
    {
        public:
            Parallel_cube (std::vector<std::vector<Geometry::Point3D>>* neuron_matrix,
                           int height);
            void operator()(const tbb::blocked_range<size_t>& r) const;
        private:
            std::vector<std::vector<Geometry::Point3D>>* neuron_matrix_;
            int height_;
    };
}

#endif /* !PARALLEL_CUBE_HH */
