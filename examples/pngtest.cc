//**********  pngtest.cc   **********************************************
//  Author:                    Paul Blackburn
//
//  Email:                     individual61@users.sourceforge.net
//
//  Version:                   0.5.4   (19 / II / 2009)
//
//  Description:               Test and example for PNGwriter,
//                             a C++ library that enables plotting to a
//                             PNG image pixel by pixel, which can 
//                             then be opened with a graphics program.
//  
//  License:                   GNU General Public License
//                             Copyright 2002, 2003, 2004, 2005, 2006, 2007,
//                             2008, 2009 Paul Blackburn
//                             
//  Website: Main:             http://pngwriter.sourceforge.net/
//           Sourceforge.net:  http://sourceforge.net/projects/pngwriter/
//           Freshmeat.net:    http://freshmeat.net/projects/pngwriter/
//           
//  Documentation:             The PNGwriter header file is commented, but for a
//                             quick reference document, and support,
//                             take a look at the website.
//
//*************************************************************************

/*
 * ######################################################################
 *  This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty 
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *     
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307  USA
 * ######################################################################
 * */

#include <pngwriter.h>
#include <math.h>
#include <iostream.h>
#include <string>
using namespace std;
#include <time.h>
#include <stdlib.h>

int main()
{
   /* Introduction
    * This program is meant to serve as an introduction to using PNGwriter.
    * It is not the simplest possible use of it, and does not cover all
    * of its features. See the website for more examples.
    * This program will generate 4 PNG images. The first two will be
    * examples of using PNGwriter's figures.
    * The third will be an example of how to read an already existing PNG image.
    * The fourth will be an example of how to use plotHSV to generate a rainbow.
    * */
   
   //////////////////////////////////////////////////////////////////////
   
   /* one.png
    * This will be a 300x300 image with a black background, called one.png
    * */
   pngwriter one(300,300,0,"one.png");
   
   std::cout << "Generating one.png...";
   
   /* Purple rectangle (filled)
    * Make a purple filled retangle. Notice we are using
    * int colour levels, e.g. 65535 is the max level of green.
    * */ 
   one.filledsquare(30,5,45,295,65535,0,65535);
   
   /* Blue rectangle
    * Make a blue rectangle over the green one.
    * Notice that we are using colour coefficcients of type double. 
    * */
   one.square(20,10,40,290,0.0,0.0,1.0);
   
   /* Yellow circle (filled) and Grey Circle
    * Using colour coefficcients of type double.
    * */
   one.filledcircle(250,250,40,1.0,1.0,0.0);
   one.circle(250,70,30,20000,20000,50000);
   
   /* Lines
    * Draw 16 lines to test all general directions of line().
    * All start from the centre and radiate outwards.
    * The colour is varied to be able to distinguish each line.
    * */
   //Top row
   one.line(150,150,0,300,0,65535,4000);
   one.line(150,150,75,300,0,65535,8000);
   one.line(150,150,150,300,0,65535,12000);
   one.line(150,150,225,300,0,65535,16000);
   one.line(150,150,300,300,0,65535,20000);
   //Right side
   one.line(150,150,300,225,0,65535,24000);
   one.line(150,150,300,150,0,65535,28000);
   one.line(150,150,300,75,0,65535,32000);
   one.line(150,150,300,0,0,65535,36000);
   //Bottom row
   one.line(150,150,225,0,0,65535,40000);
   one.line(150,150,150,0,0,65535,44000);
   one.line(150,150,75,0,0,65535,48000);
   one.line(150,150,0,0,0,65535,52000);
   //Left side
   one.line(150,150,0,75,0,65535,56000);
   one.line(150,150,0,150,0,65535,60000);
   one.line(150,150,0,225,0,65535,64000);

   /*Change the text information in the PNG header
    * */
   one.settext("one.png", "John Cleese", "Test PNG", "pngtest");
    
   std::cout << " done. Writing to disk...";
   one.close();
   std::cout << " done." << std::endl;
  
  
  ////////////////////////////////////////////////////////////////////////////////////
   /*  two.png
    *  This will be a 300x300 image with a black background, it will be called two.png.
    * Note that we are using 0.0 as the background colour and that we are using a string
    * type object as the filename, which can convert itself into a const char * with 
    * filename.c_str().
    * */
   std::cout << "Generating two.png...";
   string filename = "two.png";
   pngwriter two(300,300,0.0,filename.c_str()); 
 
   /* Gradients
    * Here we will draw a few gradients, which are nothing more than drawing a filledsquare 
    * or line or filledcircle repeatedly, changing the colour as we go.
    * */
   
   /* Draw the gradient in the lower left corner.
    * */
   for(int iter = 1;iter< 300;iter++) 
     {	
	two.line(1,300,iter,1,65535-int(65535*((double)iter)/300.0), 0,65535);
     }
   
   /* Draw the green circles.
    * */
   for(int iter2 = 0; iter2 < 8; iter2++)
     {
	two.filledcircle(280-25*iter2,250,10,0,65535 - int(65535*((double)iter2/7.0)),0);
     }
   
   /* Draw the other central gradient.
    * Notice that it is drawing a filled square, and moving the upper right corner down
    * and left, while changind the colour.
    * */
   for(int iter3 = 120; iter3>0;iter3--)
     {
	two.filledsquare(70,70,70+iter3,70+iter3,0,0,65535 -int(65535*((double)iter3/120.0 )))	;	
     }

   /* Draw the orange circle gradient.
    * */
   for(int iter4 = 0; iter4<31; iter4++)
     {
	two.filledcircle(250,200,30-iter4,1.0,1.0 - double(iter4)/30.0,0.0);
     }
   
   
   /* Now, just as an example, we will use a lower compression on this image.
    * The default is 6 (from 0 to 9) and we will set it to 3. The lower the compression used
    * the faster the image will be close()d. Complex images will take longer to 
    * close() than simple ones.
    * */
   two.setcompressionlevel(3);
   std::cout << " done. Writing to disk...";
   two.close();
   std::cout << " done." << std::endl;
    
   
   ///////////////////////////////////////////////////////////////////
  
   /* copiaburro.png
    * This section opens burro.png and places it in the pngwriter instance called burro.
    * The PNGwriter instance burro is 1x1 pixels in size because we will use it
    * as a container for another PNG image that we will
    * soon read in. No point in grabbing memory now, so we'll set the width and height to 1.
    * Notice that the original is not altered in any way.
    * */
   pngwriter burro(1,1,0,"copiaburro.png"); 
  
   /* readfromfile()
    * Now we specify the path to the file we wish to place into 
    * the PNGwriter instance "burro":
    * */
   std::cout << "Opening burro.png...";   
   burro.readfromfile("burro.png"); //It really is that easy.
   std::cout << " done." << std::endl;
   
   /* getwidth() and getheight()
    * We may not know the size of the image we just read in. 
    * We find it out like this:
    * */
   int burrowidth = burro.getwidth();
   int burroheight = burro.getheight();
  
   
   std::cout << "The image that has just been read from disk (burro.png) is " << burro.getheight();
   std::cout << " pixels high and " << burro.getwidth()<<" pixels wide."<<std::endl;
   std::cout << "Bit depth is " << burro.getbitdepth()<<std::endl;
   std::cout << "Image gamma is: " << burro.getgamma() << std::endl; 
  
   /* Cover the Donkey
    * We now draw a red circle over the donkey, just to prove that the image was read in correctly,
    * and that it was manipulated.
    * */
   burro.filledcircle((int)(burrowidth/3.0),(int)(2.0*burroheight/3.0),(int)(burrowidth/5),65535,0,0);

   /* close()
    * Must close this instance to have it written to disk.
    * */
   std::cout << "Writing to disk...";
   burro.close();
   std::cout << " done." << std::endl; 
 
   /////////////////////////////////////////////////////////////////////
   
   /* Rainbow
    * To demonstrate the use and usefulness of plotHSV(), we will
    * generate a rainbow.
    * We will use the function plotHSV that
    * plots a pixel at x, y with the colour given in the HSV colourspace
    * (hue, saturation, value), instead of the traditional RGB.
    * */ 
   
   std::cout << "\nCreating arcoiris.png...";
   pngwriter arcoiris(300,300,0,"arcoiris.png");
   std::cout << " done." <<endl;
   std::cout << "Plotting...";
   for(int a= 1;a<301;a++)
      for(int b= 1;b<301;b++)
       arcoiris.plotHSV(a,b,double(a)/300.0,double(b)/300.0,1.0);

   std::cout << " done." << endl;
   
   arcoiris.setgamma(0.5);
   std::cout << "Writing to disk...";
   arcoiris.close();
   std::cout << " done." << std::endl; 
   /////////////////////////////////////////////////////////////////
   
   /* Random filled blended triangles.*/
   
   srand ( time(NULL) );
   
   std::cout << "\nCreating triangles.png...";
   pngwriter triangles(400,400,0,"triangles.png");
   std::cout << " done.";
   double opacityrange = 0.3;
   
   std::cout << "\nPlotting triangles...";
   for(int jj = 0; jj < 10;  jj++)
     {
	
	//This creates the blue triangle outlines.
	triangles.triangle(
				       ((int) rand()%500) - 50,
				       ((int) rand()%500) - 50, 
				       ((int) rand()%500) - 50, 
				       ((int) rand()%500) - 50,
				       ((int) rand()%500) - 50, 
				       ((int) rand()%500) - 50, 
				       0.0, 0.0, 1.0);
     }
   
   for(int ii = 0; ii < 20;  ii++)
     {
	//This creates the red blended triangles
	triangles.filledtriangle_blend(
				       ((int) rand()%500) - 50,
				       ((int) rand()%500) - 50, 
				       ((int) rand()%500) - 50, 
				       ((int) rand()%500) - 50,
				       ((int) rand()%500) - 50, 
				       ((int) rand()%500) - 50, 
				       0.4 + ((double)(rand()/RAND_MAX))*opacityrange, 
				       1.0, 0.0, 0.0);
     }
   std::cout << " done.";   
   std::cout << "\nWriting to disk...";
   triangles.close();
   std::cout << " done.";
   std::cout << "\n\npngtest has finished. Take a look at the PNG images that have been created!\n";
   return 0;
}
