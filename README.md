PNGwriter Fork
==============

This repository contains an unoffical fork from the
  http://pngwriter.sourceforge.net/
repository, Version **0.5.4**.

Since PNGwriter did not change since 2009 but contains minor
bugs / flaws, this fork tries to make our lives nicer (wuhu).

Hopefully, the changes will be merged back :)

### Install

- `git clone https://github.com/ax3l/pngwriter.git`
- `mkdir -p build && cd build`
- `cmake ../pngwriter`
- `make install` (creates the libs in `lib/` and a `pngwriter.h` in `include/`)

*Optional*, set a path where to install the libraries to:
- `cmake -DCMAKE_INSTALL_PREFIX=~/myPath/`
- `make install`
  (installs `libpngwriter.a` and `libpngwriter.so` to `~/myPath/lib/`)

### License

*Paul Blackburn* (kudos!) released this piece of software under **GPLv2+**.

Please see the original [README](README) files.

### Changes

- `CMakeLists.txt`: replace that out-dated make.include stuff
- `examples/pngtest.cc:48` and `examples/pngtest.espaniol.cc:47` fix `#include <iostream>`
- build the *static* archive **and** a *shared* library
- fixed compiler warnings for keys in `pngwriter.cc`

