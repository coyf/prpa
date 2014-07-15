#include <cmath>
#include <iostream>
#include "neurons.hh"
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>

namespace Geometry
{
    Neurons::Neurons(std::vector<std::vector<Point3D>>* m)
    {
        neuron_matrix_ = m;
    }

    Neurons::Neurons(int width, int height, bool parallel)
    {
        width_ = width;
        height_ = height;

        neuron_matrix_ = new std::vector<std::vector<Point3D>>(width);

        if (!parallel)
        {
            for (int i = 0; i < width; ++i)
            {
                std::vector<Point3D> col;
                for (int z = 0; z < height; ++z)
                {
                    double r = (double) rand() / RAND_MAX;
                    double g = (double) rand() / RAND_MAX;
                    double b = (double) rand() / RAND_MAX;
                    col.push_back(Point3D(r, g, b));
                }
                (*neuron_matrix_)[i] = col;
            }
        }
        else
        {
            tbb::parallel_for(tbb::blocked_range<size_t>(0, width),
                    Parallel::Parallel_cube(neuron_matrix_, height));
        }
    }

    Neurons::~Neurons()
    {
    }

    std::vector<std::vector<Point3D>>* Neurons::getNeurons() const
    {
        return neuron_matrix_;
    }

    Point3D Neurons::nearest(Point3D p)
    {
        double min_dist = INT_MAX;
        int x = 0;
        int y = 0;

        /* Loop to find the nearest neuron of the given point */
        for (int i = 0; i < width_; ++i)
        {
            for (int z = 0; z < height_; ++z)
            {
                double dist_tmp = p.dist((*(this->neuron_matrix_))[i][z]);
                if (dist_tmp < min_dist)
                {
                    min_dist = dist_tmp;
                    x = i;
                    y = z;
                }
            }
        }
        return Point3D(x, y, 0);
    }

    Point3D Neurons::change_color(Point3D point,
            Point3D ref,
            double dist_radius) const
    {
        if (dist_radius == 0)
            dist_radius = 1;

        double r_offset = (ref.getX() - point.getX()) / dist_radius;
        double g_offset = (ref.getY() - point.getY()) / dist_radius;
        double b_offset = (ref.getZ() - point.getZ()) / dist_radius;

        double r = point.getX() + r_offset;
        double g = point.getY() + g_offset;
        double b = point.getZ() + b_offset;

        return Point3D(r, g, b);
    }

    void Neurons::update(Point3D ref, Point3D bmu, int iter, bool parallel)
    {
        double radius = getRadius((double) iter);

        if (!parallel)
        {
            for (int i = 0; i < width_; ++i)
            {
                for (int z = 0; z < height_; ++z)
                {
                    // Checks if point of the matrix is in the neighbourhood
                    // of the neuron
                    double dist_tmp = bmu.dist(Point3D(i, z, 0));
                    if (dist_tmp < radius)
                    {
                        (*(this->neuron_matrix_))[i][z] =
                            change_color((*neuron_matrix_)[i][z], ref, dist_tmp);
                    }
                }
            }
        }
        {
            tbb::parallel_for(tbb::blocked_range<size_t>(0, width_),
                    Parallel::Parallel_update(neuron_matrix_,
                        height_, radius, bmu, ref));
        }
    }

    // Get the radius needed to determine the neighbourhood of a neuron
    // 'i' represents the number of the current iteration 1,2,3 ...
    double Neurons::getRadius(int i)
    {
        return i;
    }

}
