#ifndef PARALLEL_UPDATE_HH
# define PARALLEL_UPDATE_HH

# include "Point3D.hh"
# include "neurons.hh"
# include <vector>
# include <stdlib.h>
# include <tbb/blocked_range.h>
# include <tbb/parallel_for.h>

namespace Parallel
{
    class Parallel_update
    {
        public:
            Parallel_update (std::vector<std::vector<Geometry::Point3D>>* neuron_matrix,
                             int height,
                             double radius,
                             Geometry::Point3D bmu,
                             Geometry::Point3D ref);
            void operator()(const tbb::blocked_range<size_t>& r) const;
            Geometry::Point3D change_color(
                    Geometry::Point3D point, Geometry::Point3D ref,
                    double dist_radius) const;
        private:
            std::vector<std::vector<Geometry::Point3D>>* neuron_matrix_;
            int height_;
            double radius_;
            Geometry::Point3D bmu_;
            Geometry::Point3D ref_;
    };
}

#endif /* !PARALLEL_UPDATE_HH */
