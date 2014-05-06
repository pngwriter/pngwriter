PNGwriter Fork
==============

This repository contains an unoffical fork from the
  http://pngwriter.sourceforge.net/
repository, Version **0.5.4**.

Since PNGwriter did not change since 2009 but contains minor
bugs / flaws, this fork tries to make our lives nicer (wuhu).

~~Hopefully, the changes will be merged back :)~~
We (@ax3l and @individual61) are right now preparing a bug fix release
0.5.5 - stay tuned!

### Build Status

| master branch | 0.5.5 release branch |
|:-------------:|:--------------------:|
| [![Build Status Master](https://travis-ci.org/ax3l/pngwriter.png?branch=master)](https://travis-ci.org/ax3l/pngwriter "master") | [![Build Status 0.5.5 Release Branch](https://travis-ci.org/ax3l/pngwriter.png?branch=release-0.5.5)](https://travis-ci.org/ax3l/pngwriter "0.5.5 release branch") |

### Install

- `git clone https://github.com/ax3l/pngwriter.git`
- `mkdir -p build && cd build`
- `cmake ../pngwriter`
- `make install` (creates the libs in `lib/` and a `pngwriter.h` in `include/`)

*Optional*, set a path where to install the libraries to:
- `cmake -DCMAKE_INSTALL_PREFIX=~/myPath/`
- `make install`
  (installs `libpngwriter.a` and `libpngwriter.so` to `~/myPath/lib/`)

### Linking to your project

You can either link manually to the `libpngwriter.a`/`libpngwriter.so` (which can have dependencies to `libpng`, `libz`, `libm`, `libc` and `libfreetype`) or use our CMake module:

```bash
wget https://raw.githubusercontent.com/ComputationalRadiationPhysics/picongpu/dev/src/cmake/FindPNGwriter.cmake
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
#           (PNGwriter 0.5.4 REQUIRED)
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

*Paul Blackburn* (kudos!) released this software under **GPLv2+**.

Please see the original [README](README) files.

### Changes

See the [CHANGELOG.md](CHANGELOG.md).
