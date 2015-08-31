/** Copyright 2014 Felix Schmitt, Axel Huebl
  *
  * Example and bug report from Felix Schmitt
  *
  * License: GPLv2+
  *
  * https://github.com/pngwriter/pngwriter/issues/13
  */

#include <pngwriter.h>
#include <iostream>

int main(int argc, char **argv)
{
    if (argc < 2)
        return 1;

    const std::string filename = argv[1];

    const size_t size_x = 256, size_y = 256;

    pngwriter image(size_x, size_y, 0, (filename + std::string(".tmp")).c_str());
    image.readfromfile(filename.c_str());

    size_t width = image.getwidth();
    size_t height = image.getheight();
    size_t bit_depth = image.getbitdepth();

    bool black = false, white = false;
    bool black_int = false, white_int = false;

    std::cout << "bit depth = " << bit_depth << std::endl;

    for (size_t x = 0; x < width; ++x)
        for (size_t y = 0; y < height; ++y)
        {
            /* pngwriter coordinates start at (1,1) and the y direction is inverted */
            int pos_x = 1 + x;
            int pos_y = height - y - 1;

            double color = image.dread(pos_x, pos_y,3);
            //std::cout << "dread val = " << color << std::endl;
            if (color == 0.0)
                black = true;

            if (color == 1.0)
                white = true;

            int col = image.read(pos_x, pos_y,3);
            //std::cout << "read val = " << col << std::endl;
            if (col == 0)
                black_int = true;

            if (col == 65535 && bit_depth == 16)
                white_int = true;
            if (col == 255 && bit_depth == 8)
                white_int = true;
        }

    image.close();

    if (!(black && white))
        std::cout << "failed double" << std::endl;

    if (!(black_int && white_int))
        std::cout << "failed int" << std::endl;

    return 0;
}
