#ifndef NEURONS_HH
# define NEURONS_HH

# include "Point3D.hh"
# include <list>
namespace Geometry
{
    class Neurons
    {
        public:
            Neurons(std::list<Point3D> l);
            Neurons();
            ~Neurons();

            std::list<Point3D> getNeurons() const;
            void addNeuron(Point3D p);
        private:
            std::list<Point3D> neuron_list_;
    };
}

#endif /* !NEURONS_HH */
