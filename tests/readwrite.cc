/** Copyright 2016 Maximilian Knespel
  *
  * License: GPLv2+
  *
  */

#include <iostream>
#include <iomanip>
#include <cstdlib>      // srand, rand RAND_MAX
#undef NDEBUG           // do not undefine asserts in Release builds
#include <cassert>
#include <cstring>      // memcpy
#include <pngwriter.h>


unsigned int const nMaxPixelsPerDimension = 2048;
unsigned int const nImageDimsToTest = 20;
char const * const tmpFile = "tmp-jhuio87er9r.png";

void writeArray
(
    float * const rData,
    unsigned int const rWidth,
    unsigned int const rHeight
)
{
    pngwriter png( rWidth,rHeight, 0, tmpFile );

    for ( unsigned int ix = 0; ix < rWidth ; ++ix )
    for ( unsigned int iy = 0; iy < rHeight; ++iy )
    {
        float value = rData[ iy*rWidth + ix ];
        png.plot( 1+ix,1+iy, value, value, value );
    }

    png.close();
}


void readArray
(
    float * const rData,
    unsigned int const rWidth,
    unsigned int const rHeight
)
{
    pngwriter png( 1,1, 0 /* background color */, tmpFile );
    png.readfromfile( tmpFile );
    assert( png.getwidth () == (int) rWidth  );
    assert( png.getheight() == (int) rHeight );

    for ( unsigned int ix = 0; ix < rWidth ; ++ix )
    for ( unsigned int iy = 0; iy < rHeight; ++iy )
    {
        double r = png.dread( 1+ix,1+iy, 1 );
        double g = png.dread( 1+ix,1+iy, 1 );
        double b = png.dread( 1+ix,1+iy, 1 );
        assert( r == g && g == b );

        rData[ iy*rWidth + ix ] = r;
    }

    png.close();
}


int readWriteImage
(
    unsigned int const rWidth,
    unsigned int const rHeight
)
{
    /* initialize test data we want to write out and then read in again */
    float * pLastValues  = new float[ rWidth * rHeight ];
    float * pValues      = new float[ rWidth * rHeight ];
    for ( unsigned int i = 0; i < rWidth * rHeight; ++i )
        pLastValues[i] = (float) rand() / RAND_MAX;

    /* First write out value and read it in again and ignore tests, because
     * the first read/write cycle brings almost definitely different values.
     * But the next cycles shouldn't anymore or else there is no guarantee
     * the values being read and written will stop changing */
    writeArray( pLastValues, rWidth, rHeight );
    readArray ( pLastValues, rWidth, rHeight );

    writeArray( pLastValues, rWidth, rHeight );
    readArray ( pValues    , rWidth, rHeight );

    for ( unsigned int ix = 0; ix < rWidth ; ++ix )
    for ( unsigned int iy = 0; iy < rHeight; ++iy )
    {
        unsigned int const i = iy*rWidth + ix;
        assert( pLastValues[i] == pValues[i] );
    }

    delete[] pLastValues;
    delete[] pValues;

    return 0;
}


int testReadWrite( void )
{
    for ( unsigned int i = 0; i < nImageDimsToTest; ++i )
    {
        unsigned int width  = rand() % nMaxPixelsPerDimension;
        unsigned int height = rand() % nMaxPixelsPerDimension;
        if ( width  == 0 ) width  = 1;
        if ( height == 0 ) height = 1;
        std::cout << "Doing read write test with image "
                  << width << " x " << height << " pixels large\n";
        int error = readWriteImage( width, height );
        if ( error != 0 )
            return error;
    }
    return 0;
}


int testWithOnePixel( void )
{
    unsigned int const nValuesToTest = 1000;
    unsigned int iValuesFlawed = 0;
    srand(16546485);
    for ( unsigned int i = 0; i < nValuesToTest; ++i )
    {
        float firstValue = (float) rand() / RAND_MAX;
        writeArray( &firstValue, 1,1 );
        readArray ( &firstValue, 1,1 );

        float lastValue = firstValue;
        int iRepetition = 0;
        for ( iRepetition = 0; iRepetition < 100000; ++iRepetition )
        {
            float value;
            writeArray( &lastValue, 1,1 );
            readArray ( &value    , 1,1 );

            if ( lastValue == value )
                break;
            lastValue = value;
        }
        if ( iRepetition > 0 )
        {
            std::cout << "Input Value "   << std::setw(9) << firstValue
                      << " converged to " << std::setw(9) << lastValue
                      << " in "           << std::setw(5) << iRepetition
                      << " iterations" << std::endl;
            ++iValuesFlawed;
        }
    }
    std::cout << "Found " << iValuesFlawed << " problematic values out of "
              << nValuesToTest << "\n";

    return iValuesFlawed == 0;
}


int main( void )
{
    srand(16546485);
    int error = 0;
    error &= testWithOnePixel();
    error &= testReadWrite();
    return error;
}
