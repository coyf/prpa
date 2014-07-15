#include <iostream>
#include <stdlib.h>
#include "timer.hh"
#include "Point3D.hh"
#include "neurons.hh"
#include "parallel_output_image.hh"
#include <Magick++.h>
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>


using namespace Magick;

std::string get_file_ext(std::string filename)
{
  unsigned found = filename.find_last_of(".");
  std::string ext = filename.substr(found);

  return ext;
}

int loop_pixels(char *av[], int iter, int mode)
{
    InitializeMagick(*av);

    // Construct the image object. Seperating image construction from the
    // the read operation ensures that a failure to read the image file
    // doesn't render the image object useless.
    Image image;
    try {
      // Read a file into image object
      image.read(av[3]);

      // Get image total rows and columns
      ssize_t cols = image.baseColumns();
      ssize_t rows = image.baseRows();
      //If this is not done, then image pixels will not be modified.
      image.modifyImage();
      // Allocate pixel view
      Pixels view(image);

      // Get all of the image pixels
      PixelPacket *pixels = view.get(0, 0, cols, rows);

      int radius = (cols + rows) * 0.025;
      std::cout << "radius: " << radius << std::endl;

      // Init neuron's map.
      Geometry::Neurons ns(cols, rows, mode == 1);

      srand(time(0));
      for (int i = 0; i < iter; ++i)
        {
          // Update neuron map.
          // Randomly select a pixel.
          ColorRGB rc(image.pixelColor(rand() % cols, rand() % rows));

          // Convert the pixel to Point3D.
          Geometry::Point3D rand_pt(rc.red(), rc.green(), rc.blue());

          ns.update(rand_pt, ns.nearest(rand_pt), radius);
        }

      std::vector<std::vector<Geometry::Point3D>> neurons = *(ns.getNeurons());

      // Build the image from Neurons.
      if (mode == 0)
        {
          // If it is sequentiql mode on
          for (ssize_t row = 0; row < rows; ++row)
            for (ssize_t column = 0; column < cols; ++column)
              {
                ColorRGB col(neurons[row][column].getX(),
                             neurons[row][column].getY(),
                             neurons[row][column].getZ());
                *pixels++ = col;
              }
        }
      else
        {
          // Parallel mode
          tbb::parallel_for(tbb::blocked_range<size_t>(0, rows),
                            Parallel::Parallel_output_image(neurons, pixels,
                                                            cols));
        }
      // Set output name.
      std::string fn(image.baseFilename());
      unsigned fd = fn.find_last_of(".");
      std::string out(fn.substr(0, fd));
      out.append("-output");
      out.append(get_file_ext(fn));
      std::cout << "output: " << out << std::endl;

      // Write image.
      image.write(out);
    }
    catch( Exception &error_)
    {
      std::cout << "Caught exception: " << error_.what() << std::endl;
      return 1;
    }
  return 0;
}


int check_args(int ac, char* av[])
{
  // check number of args
  if (ac != 4)
    return 2;

  // check mode
  std::string mode = av[1];
  std::string iter = av[2];
  if (mode.size() == 10
      && mode.compare(0, 7, "--mode=") == 0)
  {
    if (mode.compare(7, 3, "par") == 0)
      return 1;
    else if (mode.compare(7, 3, "seq") == 0)
      return 0;
    else
      return 2;
  }
  else if (iter.size() == 10
           && iter.compare(0, 7, "--iter=") == 0)
  {
    return 0;
  }
  else
    return 2;
}

int main(int argc, char* argv[])
{
  int ca = check_args(argc, argv);
  int res = 0;

  if (ca == 2)
  {
      std::cout
        << "usage: ./prpa --mode=<seq|par> --iter=<number> <image's path>"
        << std::endl;
    return 2;
  }

  double ellapsed_time;
  int iter_val;
  std::string arg2(argv[2]);
  std::string iter(arg2.substr(7, arg2.length() - 7));
  iter_val = atoi(iter.c_str());
  std::cout << "iter val: " << iter_val << std::endl;

  { timer t(ellapsed_time);
    res = loop_pixels(argv, iter_val, ca);
  }

  std::cout << "Ellapsed time: " << ellapsed_time << std::endl;

  return res;
}
