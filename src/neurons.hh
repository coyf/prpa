#ifndef NEURONS_HH
# define NEURONS_HH

# include "Point3D.hh"
# include <vector>
# include <stdlib.h>

namespace Geometry
{
    class Neurons
    {
        public:
            Neurons(std::vector<std::vector<Point3D>> m);
            Neurons(int width, int height);
            ~Neurons();

            Point3D nearest(Point3D p);
            void update(Point3D pt, int iter);
            Point3D change_color(Point3D point, Point3D ref, double coef);
            std::vector<std::vector<Point3D>> getNeurons() const;
        private:
            std::vector<std::vector<Point3D>> neuron_matrix_;
            int width_;
            int height_;

      double getRadius(int i);
    };
}

#endif /* !NEURONS_HH */
