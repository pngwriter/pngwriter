/********************************* PNGwriter **********************************
*
*   Website: Main:             http://pngwriter.sourceforge.net/
*            GitHub.com:       https://github.com/pngwriter/pngwriter
*            Sourceforge.net:  http://sourceforge.net/projects/pngwriter/
*
*
*    Author:                    Paul Blackburn https://github.com/individual61
*                               Axel Huebl https://github.com/ax3l
*
*    Email:                     individual61@users.sourceforge.net
*
*    Version:                   0.5.6 (December 2015)
*
*    Description:               Library that allows plotting a 48 bit
*                               PNG image pixel by pixel, which can
*                               then be opened with a graphics program.
*
*    License:                   GNU General Public License
*                               (C) 2002-2015 Paul Blackburn
*                               (C) 2013-2015 Axel Huebl
*
******************************************************************************/

/*
######################################################################
 This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License as
  published by the Free Software Foundation; either version 2 of
  the License, or (at your option) any later version.

  This program is distributed in the hope that it will be
  useful, but WITHOUT ANY WARRANTY; without even the implied warranty
  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.
######################################################################
*/

/* Lyapunov Exponents - A Test Program for PNGwriter
 * 
 * Introduction
 * I want to show a real-life example of the use of PNGwriter.
 * This program will output an image characterizing the lyapunov exponents of 
 * the logistic equation when the parameter R is not constant but a periodic series
 * of 2 values.
 * 
 * What does that mean?
 * Take a simple equation, and iterate it (take an initial value, put it into the
 * equation, get what it spits out, and plug it in again to the equation, etc, etc).
 * This equation has a number in it somewhere called a parameter. Imagine you iterate
 * the equation 1000 times with the parameter at a certain value. You see if the resulting
 * series of points is periodic or chaotic. Moreover, you determine a coefficient that
 * depends upon this parameter, which tells you how chaotic the equation is for that 
 * given parameter value. This is called a Lyapunov exponent.
 * 
 * Was that too rushed?
 * 
 * Ultimately the trajectory (the sequence of the resulting values of iterating the
 * function on an initial value) will be chaotic or periodic based solely on its parameter.
 * 
 * Here's a 1-dimensional example:
 * 
 * x_n is the nth iterate of an initial value, x_0, which is  a number between 0 and 1.
 * x_n+1 is the nth-plus-one iterate.
 * 
 * Take
 * 
 * x_n+1 = R * x_n * ( 1 - x_n )
 * 
 * where R is this parameter.
 * 
 * Take R = 2, for example, and you'll realise that the trajectory is periodic:
 * 
 * Initial x_0 = 0.45
 * 
 * 2*0.45* ( 1-0.45 ) = 0.49545
 * 2*0.49545* ( 1-0.49545 ) = 0.499959
 * 2*0.499959* ( 1-0.499959 ) = 0.5
 * 
 * It converged to its steady-state solution in just 3 iterations.... subsequent iterations will give 0.5.
 * 
 * This is because the equation is very stable for R = 2.
 * 
 * This would mean that, if you plotted a line of pixels, each representing
 * a value of R from 0 to 4, you'd see varying degrees of red, black and blue
 * (following the convention that red is chaos, black is neither chaos nor stable and blue is stable.
 * Thus the pixel representing R = 2 would be quite blue.
 * 
 * Imagine that instead of varying the parameter continuously from 0 to 4 (for example),
 * you replace this simple parameter with a series...
 * for example ABBB. This means that, for a given value of A (between 1 and 4) and a
 * given value of B (between 1 and 4) you can now iterate the equation first with A
 * as the parameter, then with B then with B then with B and then A again, looping
 * on until you do this 1000 times. You can calculate how chaotic this setup is for
 * these fixed values of A and B. Take A and B as your x-y coordinates, and the
 * lyapunov exponent as the colour value: chaotic is red, super-stable is deep
 * blue, and in between is black. 
 *
 * That's where the image comes from!
 * 
 * */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include "../src/pngwriter.h"

void intro1(void); // These are the functions that give the intro and the help.
void intro2(void);
  
  
double x = 0.35489; // Initial x_0. Any value will do. 
double x1 = 0;
double xpixels;   //Size of image, will be set later by the user
double ypixels;
double ra;
double rb;
double r;
double rbmin;
double rbmax;
double ramin;

double imax;
double preiterate;  // How many times to iterate the equation before considering
                    // its output in the calculation of the lyapunov exponent.

double umax = 0.35;  // Scaling coefficients for the colours
double umaxb = 1.5; 

int series = 0;
int indexa = 0;
int indexb = 0;
int i;
double red;
double green;
double blue;
double u;
double sum;
char *hold1,  *hold2,  *hold3, *hold5, *hold6,  *hold7, *hold8;


int main(int argc, char *argv[])
{
   if((argc != 2)&&(argc != 8)) //If no arguments are given, spit out the help and quit.	     
     {
	intro1();
     }
   
   if(argc == 2)
     {
	hold1 = (*(argv+1)); // help
	if(int(atof(hold1))==999)
	  {
	     intro2();  //If 999 is given as an argument, spit out the Intro and quit.
	  }
	else
	  {
	     exit(0);
	  }
     }
   
   hold1 = (*(argv+1)); //lower limit to iterations
   hold2 = (*(argv+2));// max iterations
   hold3 = (*(argv+3));// ramin
   
   hold5 = (*(argv+4)); // rbmin
   hold6 = (*(argv+5)); // rabmax
   hold7 = (*(argv+6)); // xpixels
   hold8 = (*(argv+7)); // ypixels
   
   preiterate = atof(hold1);
   imax = atof(hold2);
   ramin = atof(hold3);
   rbmin = atof(hold5);
   rbmax = atof(hold6);
   xpixels = atof(hold7);
   ypixels = atof(hold8);
   
   if((ramin<1)||(rbmin<1)||(rbmax>4)||(rbmin>rbmax))
     {
	intro1();
     }
   
   pngwriter png((int)xpixels,(int)ypixels,0,"out.png");  //Here we create a PNGwriter instance called png, 
                                               // and whose associated file is called out.png
   
   //The upper bound for R_a max is calculated in accordance with the width and height in pixels
   // that the user has given, so as not to distort the image.
   double ramax = ramin + xpixels*(rbmax-rbmin)/ypixels;
   double stepsizea = (ramax - ramin)/xpixels;
   double stepsizeb = (rbmax - rbmin)/ypixels;
   
   // For all pixels in the image,
   for (ra = ramin; ra<=ramax; ra=ra+stepsizea)
     {
	for (rb = rbmin; rb<=rbmax; rb=rb+stepsizeb)
	  {
	     sum = 0;
	     for (i=0; i<=imax; i++) 
	       {
		  //This is the series
		  switch (series)
		    {
		     case 0: r = ra;
		       break;
		     case 1: r = ra;
		       break;
		     case 2: r = ra;			    
		       break;
		     case 3: r = rb;
		       break;
		     case 4: r = ra;
		       break;
		     case 5: r = ra;
		       break;
		     case 6: r = rb;
		       break;
		     case 7: r = rb;
		       break;
		     case 8: r = rb;
		       break;
		     case 10: r = ra;
		       break;
		     case 11: r = rb;
		       break;
		     case 12: r = ra;
		       break;

		    }
		  
		  x1 = r*x*(1-x);
		  if (i>preiterate) //If we have already thrown away the initial points,
		    {   
		       sum = sum + log(fabs(r*(1-2*x)));
		    }
		  x = x1;
		  series = series+1;
		  if (series == 13) 
		    {	    
		       series = 0;
		    }	       
	       }
	     
	     u = double(sum)/(double(imax)-double(preiterate));
	     
	     /* Play with these lines if you wish to use different colours.
	      * using plotHSV might be an interesting idea...
	      * */
	     if (u > 0)
	       {	       
		  red =  int(u*65535.0/umax);
	       }
	     
	     if (u>umax)
	       {
		  red = 65535;
	       }
	     
	     if (u < 0)
	       {       
		  blue =-int(u*65535.0/umaxb);
	       }
	     
	     if (u*65535/umaxb < -65535)
	       {     
		  blue = 65535;
	       }
	   
	     //And here we plot with PNGwriter!
	     png.plot(indexa,indexb,int(red),int(green),int(blue));	     
	   
	     indexb = indexb+1;
	     red = 0;
	     green = 0;
	     blue = 0;
	  }
	
	indexb = 0;
	indexa = indexa +1;
     }
   png.setcompressionlevel(1); // To speed things up. Set to 0 for max speed when close()ing the image.
   png.setgamma(0.7);
   png.close();
   return 0;
}





void intro1(void)
{
   std::cout << "     Lyapunov Exponents - A Test Program for PNGwriter" << std::endl;
   std::cout << "     Copyright 2002-2009 Paul Blackburn" << std::endl;
   std::cout << "This program is covered by the PNGwriter License" << std::endl;
   std::cout << "You must enter the parameters for this program to run." << std::endl;
   std::cout << "A suggested value is given in parentheses." << std::endl; 
   std::cout << "Arguments:" << std::endl;
   std::cout << "     [lower limit to iterations] (100)" << std::endl;
   std::cout << "     [maxmimum number of iterations] (400)" << std::endl; 
   std::cout << "     [lower limit to R_a] (3, must be between 1 and 4)" << std::endl;
   std::cout << "     [lower limit to R_b] (3, must be between 1 and 4)" << std::endl;
   std::cout << "     [upper limit to R_b] (4, must be between 1 and 4)" << std::endl;
   std::cout << "     [image width, in pixels] (500)" << std::endl;
   std::cout << "     [image height, in pixels] (500)" << std::endl;
   std::cout << "Remember that what you are doing is basically rendering a" << std::endl;
   std::cout << "section of the x-y plane, with R_a on the x axis and R_b on the y axis." << std::endl;
   std::cout << "For a description of what this program does, type" << std::endl;
   std::cout << "./lyapunov 999" << std::endl;
   exit(0);   
}

void intro2(void)
{
   
		  
   std::cout << "   	  Lyapunov Exponents - A Test Program for PNGwriter " << std::endl; 
   std::cout << "    " << std::endl; 
   std::cout << "   	Copyright 2002-2009 Paul Blackburn " << std::endl; 
   std::cout << "   	This program is covered by the PNGwriter License " << std::endl; 
   std::cout << "    " << std::endl; 
   std::cout << "   You must enter the parameters for this program to run. " << std::endl; 
   std::cout << "   A suggested value is given in parentheses. " << std::endl; 
   std::cout << "   	 " << std::endl; 
   std::cout << "   	Arguments: " << std::endl; 
   std::cout << "           [lower limit to iterations] (100) " << std::endl; 
   std::cout << "   	[maxmimum number of iterations] (400) " << std::endl; 
   std::cout << "   	[lower limit to R_a] (3, must be between 0 and 4) " << std::endl; 
   std::cout << "   	[lower limit to R_b] (3, must be between 0 and 4) " << std::endl; 
   std::cout << "   	[upper limit to R_b] (4, must be between 0 and 4) " << std::endl; 
   std::cout << "   	[image width, in pixels] (500) " << std::endl; 
   std::cout << "   	[image height, in pixels] (500) " << std::endl; 
   std::cout << "   	Remember that what you are doing is basically rendering a " << std::endl; 
   std::cout << "   	section of the x-y plane, with R_a on the x axis and R_b on the y axis. " << std::endl; 
   std::cout << "   	[image height, in pixels] (500) " << std::endl; 
   std::cout << "      " << std::endl; 
   std::cout << "     Introduction " << std::endl; 
   std::cout << "     I want to show a real-life example of the use of PNGwriter. " << std::endl; 
   std::cout << "     This program will output an image characterizing the lyapunov exponents of  " << std::endl; 
   std::cout << "     the logistic equation when the parameter R is not constant but a periodic series " << std::endl; 
   std::cout << "     of 2 values. " << std::endl; 
   std::cout << "      " << std::endl; 
   std::cout << "     What does that mean? " << std::endl; 
   std::cout << "     Take a simple equation, and iterate it (take an initial value, put it into the " << std::endl; 
   std::cout << "     equation, get what it spits out, and plug it in again to the equation, etc, etc). " << std::endl; 
   std::cout << "     This equation has a number in it somewhere called a parameter. Imagine you iterate " << std::endl; 
   std::cout << "     the equation 1000 times with the parameter at a certain value. You see if the resulting " << std::endl; 
   std::cout << "     series of points is periodic or chaotic. Moreover, you determine a coefficient that " << std::endl; 
   std::cout << "     depends upon this parameter, which tells you how chaotic the equation is for that  " << std::endl; 
   std::cout << "     given parameter value. This is called a Lyapunov exponent. " << std::endl; 
   std::cout << "      " << std::endl; 
   std::cout << "     Was that too rushed? " << std::endl; 
   std::cout << "      " << std::endl; 
   std::cout << "     Ultimately the trajectory (the sequence of the resulting values of iterating the " << std::endl; 
   std::cout << "     function on an initial value) will be chaotic or periodic based solely on its parameter. " << std::endl; 
   std::cout << "      " << std::endl; 
   std::cout << "     Here's a 1-dimensional example: " << std::endl; 
   std::cout << "      " << std::endl; 
   std::cout << "     x_n is the nth iterate of an initial value, x_0, which is  a number between 0 and 1. " << std::endl; 
   std::cout << "     x_n+1 is the nth-plus-one iterate. " << std::endl; 
   std::cout << "      " << std::endl; 
   std::cout << "     Take " << std::endl; 
   std::cout << "      " << std::endl; 
   std::cout << "     x_n+1 = R * x_n * ( 1 - x_n ) " << std::endl; 
   std::cout << "      " << std::endl; 
   std::cout << "     where R is this parameter. " << std::endl; 
   std::cout << "      " << std::endl; 
   std::cout << "     Take R = 2, for example, and you'll realise that the trajectory is periodic: " << std::endl; 
   std::cout << "      " << std::endl; 
   std::cout << "     Initial x_0 = 0.45 " << std::endl; 
   std::cout << "      " << std::endl; 
   std::cout << "     2*0.45* ( 1-0.45 ) = 0.49545 " << std::endl; 
   std::cout << "     2*0.49545* ( 1-0.49545 ) = 0.499959 " << std::endl; 
   std::cout << "     2*0.499959* ( 1-0.499959 ) = 0.5 " << std::endl; 
   std::cout << "      " << std::endl; 
   std::cout << "     It converged to its steady-state solution in just 3 iterations.... subsequent iterations will give 0.5. " << std::endl;
   std::cout << "      " << std::endl; 
   std::cout << "     This is because the equation is very stable for R = 2. " << std::endl; 
   std::cout << "      " << std::endl; 
   std::cout << "     This would mean that, if you plotted a line of pixels, each representing " << std::endl; 
   std::cout << "     a value of R from 0 to 4, you'd see varying degrees of red, black and blue " << std::endl; 
   std::cout << "     (following the convention that red is chaos, black is neither chaos nor stable and blue is stable. " << std::endl;
   std::cout << "     Thus the pixel representing R = 2 would be quite blue. " << std::endl; 
   std::cout << "      " << std::endl; 
   std::cout << "     Imagine that instead of varying the parameter continuously from 0 to 4 (for example), " << std::endl; 
   std::cout << "     you replace this simple parameter with a series... " << std::endl; 
   std::cout << "     for example ABBB. This means that, for a given value of A (between 1 and 4) and a " << std::endl; 
   std::cout << "     given value of B (between 1 and 4) you can now iterate the equation first with A " << std::endl; 
   std::cout << "     as the parameter, then with B then with B then with B and then A again, looping " << std::endl; 
   std::cout << "     on until you do this 1000 times. You can calculate how chaotic this setup is for " << std::endl; 
   std::cout << "     these fixed values of A and B. Take A and B as your x-y coordinates, and the " << std::endl; 
   std::cout << "     lyapunov exponent as the colour value: chaotic is red, super-stable is deep " << std::endl; 
   std::cout << "     blue, and in between is black.  " << std::endl; 
   std::cout << "     " << std::endl; 
   std::cout << "      That's where the image comes from! " << std::endl;
   exit(0);   
   
}

