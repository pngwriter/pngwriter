/** Copyright 2015 Axel Huebl
  *
  * License: GPLv2+
  *
  */

#include <pngwriter.h>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <iostream>     /* cout, endl */
#include <chrono>       /* high_resolution_clock, duration_cast */

using namespace std::chrono;

int main( )
{
  int w = 1.0e3;
  int h = 1.0e2;

  srand(time(NULL));
  typedef high_resolution_clock::time_point TV;

  TV t1 = high_resolution_clock::now();
  pngwriter img( w, h, 0, "/tmp/foo.png" );
  //img.setcompressionlevel(1);
  TV t2 = high_resolution_clock::now();

  std::cout << "allocation time: "
            << duration_cast<std::chrono::microseconds>( t2 - t1 ).count()
            << std::endl;

  t1 = high_resolution_clock::now();
  double val = 0.0;
  const double maxVal = 65535.;
  for( int x = 0; x < w; ++x )
  {
    for( int y = 0; y < h; ++y )
    {
       val = maxVal * 1.e-3 * ( rand() % 1000 );
       img.plot(x, y, int(val), int(val), int(val));
    }
  }
  t2 = high_resolution_clock::now();

  std::cout << "random value time: "
            << duration_cast<std::chrono::microseconds>( t2 - t1 ).count()
            << std::endl;

  t1 = high_resolution_clock::now();
  //img.scale_k(0.1);
  img.write_png();
  t2 = high_resolution_clock::now();

  std::cout << "write_png() time: "
            << std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count()
            << std::endl;

  return 0;
}
