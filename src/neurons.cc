#include "neurons.hh"

namespace Geometry
{
    Neurons::Neurons(std::vector<std::vector<Point3D>> m)
    {
        neuron_matrix_ = m;
    }

    Neurons::Neurons(int width, int height)
    {
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
}
