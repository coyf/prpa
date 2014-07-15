#include "parallel_cube.hh"
#include <iostream>

namespace Parallel
{
    Parallel_cube::Parallel_cube (std::vector<std::vector<Geometry::Point3D>>*
            neuron_matrix, int height) :
        neuron_matrix_(neuron_matrix), height_(height)
    {
    }

    void Parallel_cube::operator()(const tbb::blocked_range<size_t>& r) const
    {
        for (size_t i = r.begin(); i < r.end(); ++i)
        {
            std::vector<Geometry::Point3D> col;
            for (int z = 0; z < height_; ++z)
            {
                double r = (double) rand() / RAND_MAX;
                double g = (double) rand() / RAND_MAX;
                double b = (double) rand() / RAND_MAX;
                col.push_back(Geometry::Point3D(r, g, b));
            }

            (*neuron_matrix_)[i] = col;
        }
    }
}
