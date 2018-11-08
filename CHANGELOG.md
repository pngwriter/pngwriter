Change Log for PNGwriter
========================

0.7.0
-----
**Date:** 2018-01-22

Modernized CMake3 scripts, CMake package and Windows support.
All closed issues can be found at
  [Milestone 0.7.0](https://github.com/pngwriter/pngwriter/milestone/5?closed=1)

### Changes to 0.6.0

**New Features:**
  - CMake modernized: #122
    - use and create targets
    - `PNGwriterConfig.cmake` package
    - `make test` supported
    - removed legacy "Makefile"s
  - Windows build support #116

**Misc:**
  - removed warnings in tests #122


0.6.0
-----
**Date:** 2017-03-28

This release fixes 8bit RBG reads, adds performance improvements on large
images, removes warnings and cleans up larger sections of the code. Some
interfaces changed parameter attributes to reflect constants and static calls.

All closed issues can be found at
  [Milestone 0.6.0](https://github.com/pngwriter/pngwriter/milestone/2?closed=1)

### Changes to 0.5.6

**Bug Fixes:**
  - 8bit read: correct range #89 #90
  - unused parameters (no-freetype) #80 #81

**Misc:**
  - API changes:
    - added const and static where possible #86
  - performance improved:
    - CMake: add option to build performance test #109
    - extent the performance test #102
    - change nested loop order #98
  - refactoring:
    - remove unnecessary `std::string` casts from commit c1e1e7d #107
    - remove internet C strings and copies #99
    - EOL White Spaces in code base #88
    - round to nearest integer on float input #84
  - update `.gitignore` #101
  - add reference PNGs #96

Thanks to René (@psychocoderHPC), Paul (@pkohut), Maximilian (@mxmlnkn) and
Axel (@ax3l) for contributions to this release!


0.5.6
-----
**Date:** 2015-12-16

This release fixes a bug with creation time meta data and refactors several
internal methods based on coverity-scan reports.

All closed issues can be found at
  [Milestone 0.5.6](https://github.com/pngwriter/pngwriter/issues?q=milestone%3A0.5.6)

### Changes to 0.5.5

**Bug Fixes:**
  - creation time was randomly malformed and could cause memory corruption #76
  - fix memory leak in `ucs4text` on error, restore `std::cerr` state #70

**Misc:**
  - internal method `read_png_image` refactored #71
  - remove dead code in `readCMYK` #68
  - remove unused private member `rowbytes_` #69
  - add a set of compiler warnings for gcc, clang, icc, gpi #65


0.5.5
-----
**Date:** 2015-08-31

This release fixes several bugs, removes Spanish language documentation and
example files, and restructures the documentation file locations as a result of
these changes.

All closed issues can be found at
  [Milestone 0.5.5](https://github.com/pngwriter/pngwriter/issues?milestone=1&state=closed)

### Changes to 0.5.4

**New Features:**
  - support for libpng 1.4.X, 1.5.X and 1.6.X #10 #11 #54
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
  - read functions for 8bit images were broken: `read`/`dread` (reported by Felix Schmitt) #13
  - fix compile with new gcc versions and clean c++ includes #30
  - fix memory leak in `operator=` #23
  - fix `FilledTriangle` methods (reported by Dongkook Park, Nov 2009) #22
  - fix `triangle` method rounding/casting error (reported by Andrea Charao, Apr 2009) #19
    [SF 6e7f2697](http://sourceforge.net/p/pngwriter/discussion/238247/thread/6e7f2697/)
  - fix library order in linker for old makefile installs (reported by Piin-Ruey Pan) #35
  - remove manipulation of gamma after `png_read_update_info()` #56

**Misc:**
  - fixed Clang warnings #32
  - `OLD_CPP` install removed #30
  - removed freshmeat homepage link
  - speedup of ~20x for allocation of black images #46
  - `#define PNGWRITER_VERSION` is deprecated, better query `PNGWRITER_VERSION_MAJOR`,
    `PNGWRITER_VERSION_MINOR` and `PNGWRITER_VERSION_PATCH` #50


**Note**: Changes to PNGwriter prior to version 0.5.5 can be found in the doc/CHANGES file.
