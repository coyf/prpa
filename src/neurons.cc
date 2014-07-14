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
        double min_dist = 1000000;
        int x = 0;
        int y = 0;

        /* Loop to find the nearest neuron of the given point */
        for (int i = 0; i < width_; ++i)
        {
            for (int z = 0; z < height_; ++z)
            {
                double dist_tmp = p.dist(this->neuron_matrix_[i][z]);
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

    Point3D Neurons::change_color(Point3D point, Point3D ref, double coef)
    {
        double r;
        double g;
        double b;

        if (abs(point.getX() - ref.getX()) < coef)
            r = ref.getX();
        else
            r = point.getX() < ref.getX() ? point.getX() + coef :
                point.getX() - coef;

        if (abs(point.getY() - ref.getY()) < coef)
            g = ref.getY();
        else
            g = point.getY() < ref.getY() ? point.getY() + coef :
                point.getY() - coef;

        if (abs(point.getZ() - ref.getZ()) < coef)
            b = ref.getZ();
        else
            b = point.getZ() < ref.getZ() ? point.getZ() + coef :
                point.getZ() - coef;

        return Point3D(r, g, b);
    }

  void Neurons::update(Point3D pt, int iter)
  {
    double radius = getRadius((double) iter);

        for (int i = 0; i < width_; ++i)
        {
            for (int z = 0; z < height_; ++z)
            {
              // Checks if point of the matrix is in the neighbourhood
              // of the neuron
              double dist_tmp = pt.dist(Point3D(i, z, 0));
              //std::cout << "dist " << dist_tmp << " radius: " << radius << std::endl;
              if (dist_tmp < radius)
                {
                    this->neuron_matrix_[i][z] = Point3D(0, 1, 1);
                }
            }
        }
    }

  // Get the radius needed to determine the neighbourhood of a neuron
  // 'i' represents the number of the current iteration 1,2,3 ...
  double Neurons::getRadius(double i)
  {
    return sqrt(i*10);
  }

}
