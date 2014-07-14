#include <cmath>
#include <iostream>
#include "neurons.hh"

namespace Geometry
{
    Neurons::Neurons(std::vector<std::vector<Point3D>> m)
    {
        neuron_matrix_ = m;
    }

    Neurons::Neurons(int width, int height)
    {
        width_ = width;
        height_ = height;
        for (int i = 0; i < width; ++i)
        {
            std::vector<Point3D> row;
            for (int z = 0; z < height; ++z)
            {
                double r = (double) rand() / RAND_MAX;
                double g = (double) rand() / RAND_MAX;
                double b = (double) rand() / RAND_MAX;
                row.push_back(Point3D(r, g, b));
            }
            neuron_matrix_.push_back(row);
        }
    }

    Neurons::~Neurons()
    {
    }

    std::vector<std::vector<Point3D>> Neurons::getNeurons() const
    {
        return neuron_matrix_;
    }

    Point3D Neurons::nearest(Point3D p)
    {
        Point3D nearest_point = this->neuron_matrix_[0][0];
        int min_dist = 1000000;

        /* Loop to find the nearest neuron of the given point */
        for (int i = 0; i < width_; ++i)
        {
            for (int z = 0; z < height_; ++z)
            {
                double dist_tmp = p.dist(this->neuron_matrix_[i][z]);
                if (dist_tmp < min_dist)
                {
                    nearest_point = this->neuron_matrix_[i][z];
                    min_dist = dist_tmp;
                }
            }
        }
        return nearest_point;
    }

  void Neurons::update(Point3D pt, int iter)
  {
    double radius = getRadius(iter);

        for (int i = 0; i < width_; ++i)
        {
            for (int z = 0; z < height_; ++z)
            {
              // Checks if point of the matrix is in the neighbourhood
              // of the neuron
              double dist_tmp = pt.dist(this->neuron_matrix_[i][z]);
              //std::cout << "dist " << dist_tmp << " radius: " << radius << std::endl;
              if (dist_tmp * 255 < radius)
                {
                  this->neuron_matrix_[i][z] = Point3D(0, 1, 1);
                }
            }
        }
  }

  // Get the radius needed to determine the neighbourhood of a neuron
  // 'i' represents the number of the current iteration 1,2,3 ...
  double Neurons::getRadius(int i)
  {
    return exp(-(i/50));
  }

}
