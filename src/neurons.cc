#include "neurons.hh"

namespace Geometry
{
    Neuron::Neuron(std::list<Point3D> l)
    {
        neuron_list_ = l;
    }

    Neuron::Neuron()
    {
    }

    Neuron::~Neuron()
    {
    }

    std::list<Point3D> Neuron::getNeurons() const
    {
        return neuron_list_;
    }
}
