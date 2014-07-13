#include <iostream>
#include <stdlib.h>
#include "timer.hh"
#include <Magick++.h>

using namespace Magick;

int main(int argc, char* argv[])
{
  double ellapsed_time;

  InitializeMagick(*argv);

  // Construct the image object. Seperating image construction from the 
  // the read operation ensures that a failure to read the image file 
  // doesn't render the image object useless. 
  Image image;
  try {
    // Read a file into image object
    image.read(argv[1]);

    // Crop the image to specified size (width, height, xOffset, yOffset)
    image.crop(Geometry(100,100, 100, 100));

    // Write the image to a file 
    image.write( "x.png" ); 
  } 
  catch( Exception &error_)
    { 
      std::cout << "Caught exception: " << error_.what() << std::endl; 
      return 1; 
    } ;
  { timer t(ellapsed_time);
  }


  std::cout << "Ellapsed time: " << ellapsed_time << std::endl;

  return 0;
}
