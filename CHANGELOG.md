Change Log for PNGwriter
========================
**Note**: Changes to PNGwriter prior to version 0.5.5 can be found in the doc/CHANGES file.

0.6.0
-----
**Date:** TBA

Not done yet :)

  - `FindPNGwriter.cmake`: CMake `find_package` module, [see above](#linking-to-your-project)
  - #7 #9 #11 #12 #14 #15

0.5.5
-----
**Date:** TBA

This release fixes several bugs, removes Spanish language documentation and example files, and restructures the documentation file locations as a result of these changes.

All closed issues can be found at
  [Milestone 0.5.5](https://github.com/ax3l/pngwriter/issues?milestone=1&state=closed)

### Changes to 0.5.4

**New Features:**
  - support for libpng 1.4, 1.5 and 1.6 #10 #11
    (thanks to Daniel Hornung http://sourceforge.net/p/pngwriter/bugs/1 for the 1.4 patch)
  - added alternative cmake based install via `CMakeLists.txt`
  - cmake: build the *static* archive **and** a *shared* library

**Bug Fixes:**
  - `examples/pngtest.cc:48` and `examples/pngtest.espaniol.cc:47` fix `#include <iostream>`
  - compiler warnings for keys in `pngwriter.cc` #2
  - `filleddiamond()` bug reported in
    [Debian #633405](http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=633405) #6
  - memory leak in `pngwriter::readfromfile` reported
    [here](http://sourceforge.net/p/pngwriter/discussion/238247/thread/15ee786c/) 
    and again [here](http://sourceforge.net/p/pngwriter/bugs/2/) #5
  - read functions for 8bit images were broken: `read`/`dread` (reported by @f-schmitt-zih) #13
