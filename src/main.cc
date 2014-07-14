#include <iostream>
#include <stdlib.h>
#include "timer.hh"
#include <Magick++.h>

using namespace Magick;

std::string get_file_ext(std::string filename)
{
  unsigned found = filename.find_last_of(".");
  std::string ext = filename.substr(found);

  return ext;
}

void color_to_3dpixel(ColorRGB col)
{
  double r;
  double g;
  double b;

  r = col.red();
  g = col.green();
  b = col.blue();

  std::cout << "red: [ " << r << " ] green: [ " << g << " ] blue: [ "
            << b << "]" << std::endl;
}

int loop_pixels(char *av[])
{
    InitializeMagick(*av);

    // Construct the image object. Seperating image construction from the 
    // the read operation ensures that a failure to read the image file 
    // doesn't render the image object useless. 
    Image image;
    try {
      // Read a file into image object
      image.read(av[2]);

      // Get image total rows and columns
      ssize_t cols = image.baseColumns();
      ssize_t rows = image.baseRows();
      //If this is not done, then image pixels will not be modified. 
      image.modifyImage();
      // Allocate pixel view
      Pixels view(image);

      // Get all of the image pixels
      PixelPacket *pixels = view.get(0, 0, cols, rows);
      // Test: set all pixels in green.
      for ( ssize_t row = 0; row < rows ; ++row ) 
        for ( ssize_t column = 0; column < cols ; ++column )
        {
          // Convert the Color to our 3dPixel class
          ColorRGB colrgb(*pixels++);
          color_to_3dpixel(colrgb);
        }
      // Test end.
      // Write the image to a file
      std::string fn(image.baseFilename());
      unsigned fd = fn.find_last_of(".");
      std::string out(fn.substr(0, fd));
      out.append("-output");
      out.append(get_file_ext(fn));
      std::cout << "output: " << out << std::endl;
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
  if (ac != 3)
    return 2;

  // check mode
  std::string mode = av[1];
  if (mode.size() == 10
      && mode.compare(0, 7, "--mode=") == 0)
  {
    if (mode.compare(7, 3, "par") == 0
        || mode.compare(7, 3, "seq") == 0)
      return 0;
    else
      return 1;
  }
  else
    return 2;
}

int main(int argc, char* argv[])
{
  int ca = check_args(argc, argv);
  int res = 0;

  if (ca != 0)
  {
    if (ca == 2)
      std::cout << "usage: ./prpa --mode=<seq|par> <image's path>" << std::endl;
    else if (ca == 1)
      std::cout << "unknow mode" << std::endl;
    return 2;
  }

  double ellapsed_time;
  { timer t(ellapsed_time);
    res = loop_pixels(argv);
  }

  std::cout << "Ellapsed time: " << ellapsed_time << std::endl;

  return res;
}
