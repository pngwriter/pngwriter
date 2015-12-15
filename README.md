PNGwriter
=========
PNGwriter is a C++ library for creating PNG images.

### Summary

PNGwriter is a very easy to use open source graphics library that uses PNG as
its output format. The interface has been designed to be as simple and
intuitive as possible. It supports plotting and reading pixels in the RGB (red,
green, blue), HSV (hue, saturation, value/brightness) and CMYK (cyan, magenta,
yellow, black) colour spaces, basic shapes, scaling, bilinear interpolation,
full TrueType antialiased and rotated text support, bezier curves, opening
existing PNG images and more. Documentation in English (and Spanish up to
v0.5.4). Runs under Linux, Unix, Mac OS X and Windows. Requires libpng and
optionally FreeType2 for the text support.


### Where to find information about PNGwriter

The PNGwriter project's online presence consists of:

- The [PNGwriter website](http://pngwriter.sourceforge.net), with a
- [FAQ](http://pngwriter.sourceforge.net/),
  [quickstart](http://pngwriter.sourceforge.net/quickstart-en.php),
  [examples](http://pngwriter.sourceforge.net/examples-en.php), and an online
  copy of the [manual](http://pngwriter.sourceforge.net/manual-en.php).
- This [PNGwriter GitHub repo](http://github.com/pngwriter/pngwriter), where
  source code is distributed and collaboration takes place. The distribution
  includes a PDF copy of the manual.

This project was migrated from the PNGwriter repository originally hosted on
SourceForge (and no longer maintained). The last version released on
SourceForge was 0.5.5.


### Build Status

| master branch | development branch |
|:-------------:|:--------------------:|
| [![Build Status Master](https://travis-ci.org/pngwriter/pngwriter.png?branch=master)](https://travis-ci.org/pngwriter/pngwriter "master") | [![Build Status Development Branch](https://travis-ci.org/pngwriter/pngwriter.png?branch=dev)](https://travis-ci.org/pngwriter/pngwriter "development branch") |


### Latest News

**New version and a new team member — August 2015 Update**

A long time has passed since PNGwriter's last release. Thanks to the skilled
and generous help of Axel Huebl ([@ax3l](http://github.com/ax3l)) many bugs
have been fixed, a new compilation procedure is in place, and PNGwriter is now
on [GitHub](https://github.com/pngwriter/pngwriter). Axel is now an active and
invaluable member of the PNGwriter Team, joining Paul Blackburn
([@individual61](https://github.com/individual61)), who created PNGwriter in
2002. Welcome aboard, Axel!

This nudge to action could not have come at a better time, since the
once-respectable host to the PNGwriter project, SourceForge.net, is no longer
what we consider a positive contribution to the Open Source community.
The PNGwriter website and files currently hosted on SourceForge.net will remain
on SourceForge.net, but the current and all future releases will be via
PNGwriter's GitHub repository.
 **Don't forget**!

Thank you, PNGwriter users, for your patience, bug fixes, and suggestions. I
hope you are as excited as we are to see where the next thirteen years take
PNGwriter!

Paul Blackburn  
San Jose, California  
August, 2015


### Feedback

We'd love to hear how you've used PNGwriter in your project. Are you doing
interesting things? Are you running it on interesting hardware? Tell us how you
use PNGwriter. [Open an issue](https://github.com/pngwriter/pngwriter/issues/new)
and let us know. Don't forget to include the following information:
- Project Title
- Link
- Cool image
- Authors list
- Single-sentence, one-line description of the project.


### Installation

The preferred way to install PNGwriter is using `CMake`:

- `git clone https://github.com/pngwriter/pngwriter.git`
- `mkdir -p build && cd build`
- `cmake ../pngwriter`
- `make install` (creates the libs in `lib/` and a `pngwriter.h` in `include/`)

*Optional*, set a path where to install the libraries to:
- `cmake -DCMAKE_INSTALL_PREFIX=~/myPath/`
- `make install`
  (installs `libpngwriter.a` and `libpngwriter.so` to `~/myPath/lib/`)

(There is also a pre-created `Makefile` shipped with the source files, but
since it is not directly portable we deprecated that install method and
will not support it any longer.)

### Linking to your project

You can either link manually to the `libpngwriter.a`/`libpngwriter.so` (which
can have dependencies to `libpng`, `libz`, `libm`, `libc` and `libfreetype`) or
use our CMake module:

```bash
wget https://raw.githubusercontent.com/ComputationalRadiationPhysics/cmake-modules/dev/FindPNGwriter.cmake
# read its documentation
cmake -DCMAKE_MODULE_PATH=. --help-module FindPNGwriter | less
```

Use the following lines in your projects `CMakeLists.txt`:
```cmake
# this example requires at least CMake 2.8.5
cmake_minimum_required(VERSION 2.8.5)

# add path to FindPNGwriter.cmake, e.g. in the directory in cmake/
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)

# find PNGwriter installation
#   optional: prefer static libraries over shared ones (but do not force them)
#set(PNGwriter_USE_STATIC_LIBS ON)

#   optional: specifiy (minimal) version / require to find it
#           (PNGwriter 0.5.6 REQUIRED)
find_package(PNGwriter)

if(PNGwriter_FOUND)
  # where to find the pngwriter.h header file (-I include for your compiler)
  include_directories(SYSTEM ${PNGwriter_INCLUDE_DIRS})
  # additional compiler flags (e.g. -DNO_FREETYPE)
  add_definitions(${PNGwriter_DEFINITIONS})
  # libraries to link against (including dependencies)
  set(LIBS ${LIBS} ${PNGwriter_LIBRARIES})
endif(PNGwriter_FOUND)

# add_executable(yourBinary ${SOURCES})
# ...
# target_link_libraries(yourBinary ${LIBS})
```

### License

This software is released under **GPLv2+**.

### Changes

See the [CHANGELOG.md](CHANGELOG.md).
Please note that changes to PNGwriter prior to version 0.5.5 can be found in
the doc/CHANGES file.
