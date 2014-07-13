#include <iostream>
#include <stdlib.h>
#include "timer.hh"
#include <Magick++.h>

using namespace Magick;

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
    InitializeMagick(*argv);

    // Construct the image object. Seperating image construction from the 
    // the read operation ensures that a failure to read the image file 
    // doesn't render the image object useless. 
    Image image;
    try {
      // Read a file into image object
      image.read(argv[2]);

      // Crop the image to specified size (width, height, xOffset, yOffset)
      image.crop(Geometry(100,100, 100, 100));

      // Write the image to a file
      image.write("out.png");
    } 
    catch( Exception &error_)
    { 
      std::cout << "Caught exception: " << error_.what() << std::endl; 
      return 1; 
    }
  }

  std::cout << "Ellapsed time: " << ellapsed_time << std::endl;

  return 0;
}
