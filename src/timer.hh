// timer.hh: Measuring Time

#ifndef _PrPa_TP01_TIMER_HH_
#define _PrPa_TP01_TIMER_HH_

#include <chrono>

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::chrono::steady_clock;

struct timer
{
  timer(double& s)
    : seconds(s),
      t0(steady_clock::now())
  {
  }

  ~timer()
  {
    duration<double> d = duration_cast<duration<double>>(steady_clock::now() - t0);
    seconds = d.count();
  }

  double&                       seconds;
  steady_clock::time_point      t0;
};

#endif
