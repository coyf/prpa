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
                float r = (rand() % 1000) / 1000;
                float g = (rand() % 1000) / 1000;
                float b = (rand() % 1000) / 1000;
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

    void Neurons::update(Point3D p)
    {
        Point3D min_point = this->neuron_matrix_[0][0];
        int min_dist = 1000000;

        /* Loop to find the nearest neuron of the given point */
        for (int i = 0; i < width_; ++i)
        {
            for (int z = 0; z < height_; ++z)
            {
                int dist_tmp = p.dist(this->neuron_matrix_[i][z]);
                if (dist_tmp < min_dist)
                {
                    min_point = this->neuron_matrix_[i][z];
                    min_dist = dist_tmp;
                }
            }
        }
    }
}
