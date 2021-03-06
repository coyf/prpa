#ifndef NEURONS_HH
# define NEURONS_HH

# include "Point3D.hh"
# include <vector>
# include <stdlib.h>
# include <climits>
# include "parallel_cube.hh"
# include "parallel_update.hh"
# include "parallel_nearest.hh"

namespace Geometry
{
    class Neurons
    {
        public:
            Neurons(std::vector<std::vector<Point3D>>* m);
            Neurons(int width, int height, bool parallel);
            ~Neurons();

            Point3D nearest(Point3D p, bool parallel_enabled);
            void update(Point3D ref, Point3D pt, int iter, bool parallel);
            Point3D change_color(Point3D point, Point3D ref, double coef) const;
            std::vector<std::vector<Point3D>>* getNeurons() const;
        private:
            std::vector<std::vector<Point3D>>* neuron_matrix_;
            int width_;
            int height_;

      double getRadius(int i);
    };
}

#endif /* !NEURONS_HH */
