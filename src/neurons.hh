#ifndef NEURONS_HH
# define NEURONS_HH

# include "Point3D.hh"
# include <list>
namespace Geometry
{
    class Neuron
    {
        public:
            Neuron(std::list<Point3D>);
            Neuron();
            ~Neuron();

            std::list<Point3D> getNeurons() const;
        private:
            std::list<Point3D> neuron_list_;
    };
}

#endif /* !NEURONS_HH */
