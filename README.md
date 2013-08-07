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
- `make install` (creates the libs in `lib/`)

*Optional*, set a path where to install the libraries to:
- `cmake -DCMAKE_INSTALL_PREFIX=~/myPath/`
- `make install`
  (installs `libpngwriter.a` and `libpngwriter.so` to `~/myPath/lib/`)

### Changes

- `CMakeLists.txt` : replace that crappy make.include stuff
- `examples/pngtest.cc:48` fix `#include <iostream>`

