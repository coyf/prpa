#include "parallel_update.hh"
#include <iostream>

namespace Parallel
{
    Parallel_update::Parallel_update (std::vector<std::vector<Geometry::Point3D>>*
            neuron_matrix, int height, double radius, Geometry::Point3D bmu,
            Geometry::Point3D ref) :
        neuron_matrix_(neuron_matrix),
        height_(height),
        radius_(radius),
        bmu_(bmu),
        ref_(ref)
    {
    }

    Geometry::Point3D Parallel_update::change_color(Geometry::Point3D point,
            Geometry::Point3D ref, double dist_radius) const
    {
        if (dist_radius == 0)
            dist_radius = 1;

        double r_offset = (ref.getX() - point.getX()) / dist_radius;
        double g_offset = (ref.getY() - point.getY()) / dist_radius;
        double b_offset = (ref.getZ() - point.getZ()) / dist_radius;

        double r = point.getX() + r_offset;
        double g = point.getY() + g_offset;
        double b = point.getZ() + b_offset;

        return Geometry::Point3D(r, g, b);
    }

    void Parallel_update::operator()(const tbb::blocked_range<size_t>& r) const
    {
        for (size_t i = r.begin(); i < r.end(); ++i)
        {
            for (int z = 0; z < height_; ++z)
            {
                // Checks if point of the matrix is in the neighbourhood
                // of the neuron
                double dist_tmp = bmu_.dist(Geometry::Point3D(i, z, 0));
                if (dist_tmp < radius_)
                {
                  (*(neuron_matrix_))[i][z] =
                    change_color((*neuron_matrix_)[i][z], ref_, dist_tmp);
                }
            }
        }
    }
}
