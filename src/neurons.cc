#include "neurons.hh"

namespace Geometry
{
    Neurons::Neurons(std::list<Point3D> l)
    {
        neuron_list_ = l;
    }

    Neurons::Neurons()
    {
    }

    Neurons::~Neurons()
    {
    }

    std::list<Point3D> Neurons::getNeurons() const
    {
        return neuron_list_;
    }

    void Neurons::addNeuron(Point3D p)
    {
        neuron_list_.push_front(p);
    }
}
