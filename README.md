PNGwriter
=========
PNGwriter is a C++ library for creating PNG images.

[![Build Status master](https://img.shields.io/travis/pngwriter/pngwriter/master.svg?label=master)](https://travis-ci.org/pngwriter/pngwriter/branches)
[![Build Status dev](https://img.shields.io/travis/pngwriter/pngwriter/dev.svg?label=dev)](https://travis-ci.org/pngwriter/pngwriter/branches)
[![AppVeyor Build status dev](https://ci.appveyor.com/api/projects/status/d408e2j24ha2dopq/branch/dev?svg=true)](https://ci.appveyor.com/project/ax3l/pngwriter-2al7e/branch/dev)
[![Language](https://img.shields.io/badge/language-C%2B%2B98-orange.svg)](https://isocpp.org)
[![License](https://img.shields.io/badge/license-GPLv2-blue.svg)](https://www.gnu.org/licenses/gpl-2.0.html)


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

**Warning:** PNGwriter was never designed for reading untrusted files with it.
Do NOT use this in sensitive environments, especially DO NOT read PNGs from unknown sources with it!


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

[![Spack Package](https://img.shields.io/badge/spack.io-pngwriter-brightgreen.svg)](https://spack.io)

**Spack:**

```bash
spack install pngwriter
spack load pngwriter
```

**From Source:**

First install the dependencies [zlib](https://github.com/madler/zlib/), [libpng](http://download.sourceforge.net/libpng) and (optional for text support) [freetype](http://download.savannah.gnu.org/releases/freetype).
PNGwriter can then be installed using [CMake](http://cmake.org/):

```bash
git clone https://github.com/pngwriter/pngwriter.git

mkdir -p pngwriter-build
cd pngwriter-build

# for own install prefix append: -DCMAKE_INSTALL_PREFIX=$HOME/somepath
cmake ../pngwriter

make -j

# optional
make test

# sudo is only required for system paths
sudo make install
```


### Linking to your project

First set the following environment hint if PNGwriter was *not* installed in a system path:

```bash
# optional: only needed if installed outside of system paths
export CMAKE_PREFIX_PATH=$HOME/somepath:$CMAKE_PREFIX_PATH
```

Use the following lines in your projects `CMakeLists.txt`:
```cmake
find_package(PNGwriter 0.7.0)

if(PNGwriter_FOUND)
  target_link_libraries(YourTarget PRIVATE PNGwriter::PNGwriter)
endif(PNGwriter_FOUND)
```

### License

This software is released under **GPLv2+**.

### Changes

See the [CHANGELOG.md](CHANGELOG.md).
Please note that changes to PNGwriter prior to version 0.5.5 can be found in
the doc/CHANGES file.
