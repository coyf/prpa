#include <iostream>
#include "timer.hh"

int main()
{
  double ellapsed_time;

  { timer t(ellapsed_time);
  }

  std::cout << "Ellapsed time: " << ellapsed_time << std::endl;

  return 0;
}
