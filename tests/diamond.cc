/** Copyright 2011      Kevin Ryde
  * Copyright 2013-2014 Axel Huebl
  *
  * Example and bug report from Kevin Ryde
  *
  * License: GPLv2+
  *
  * http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=633405
  */

#include <pngwriter.h>
#include <cstdlib>

int main( )
{
  pngwriter img( 40,11, 0, "/tmp/foo.png" );

  img.diamond      ( 10,6, 8,8,  1.0,1.0,1.0 );
  img.filleddiamond( 30,6, 8,8,  1.0,1.0,1.0 );
  img.write_png();

  return system( "convert /tmp/foo.png /tmp/foo.xpm; cat /tmp/foo.xpm" );
}
