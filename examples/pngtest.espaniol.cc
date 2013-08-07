//**********  pngtest.cc   **********************************************
//  Autor:                     Paul Blackburn
//
//  Email:                     individual61@users.sourceforge.net
//
//  Version:                   0.5.4   (19 / II/ 2009)
//
//  Descripcion:               Programa de prueba y ejemplo para PNGwriter,
//                             una libreria de C++ que permite plotear una imagen PNG
//                             de 16 bit pixel por pixel, que luego puede
//                             ser abierta por un programa de graficos.
//
//  Licencia:                   GNU General Public License
//                             Copyright 2002, 2003, 2004, 2005, 2006, 2007,
//                             2008, 2009 Paul Blackburn
//
//  Website: Principal:        http://pngwriter.sourceforge.net/
//           Sourceforge.net:  http://sourceforge.net/projects/pngwriter/
//           Freshmeat.net:    http://freshmeat.net/projects/pngwriter/
//
//  Documentacion:             El archivo header tiene comentarios,
//                             pero para obtener un documento de referencia
//                             rapida y soporte, mira el website.
//
//*************************************************************************

/*
 * ######################################################################
 * Este programa es software libre. Puede redistribuirlo y/o modificarlo bajo los terminos 
 * de la Licencia Publica General de GNU segun es publicada por la Free Software
 * Foundation, bien de la version 2 de dicha Licencia o bien (segun su eleccion) de 
 * cualquier version posterior.
 * 
 *  Este programa se distribuye con la esperanza de que sea util, pero SIN
 * NINGUNA GARANTiA, incluso sin la garantia MERCANTIL implicita o sin garantizar la
 * CONVENIENCIA PARA UN PROPoSITO PARTICULAR. Vease la Licencia Publica General de
 * GNU para mas detalles.
 * 
 *         Deberia haber recibido una copia de la Licencia Publica General junto con
 * este programa. Si no ha sido asi, escriba a la Free Software Foundation, Inc., en
 * 675 Mass Ave, Cambridge, MA 02139, EEUU.
 * ######################################################################
 * */
  
#include "../src/pngwriter.h"
#include <math.h>
#include <iostream.h>
#include <string>
using namespace std;
#include <time.h>
#include <stdlib.h>


int main()
{
   /* Introduccion
    * Este programa fue escrito como una introduccion al uso de PNGwriter.
    * No es el uso mas simple que se le puede dar, y tampoco muestra todas sus funciones.
    * Este programa generara 4 imagenes PNG. Las primeras 2 seran
    * ejemplos de usar las figuras de PNGwriter.
    * La tercera sera un ejemplo de como cargar una imagen PNG que ya existe.
    * La cuarta sera un ejemplo de como usar plotHSV para generar un arcoiris.
    * */
   
   //////////////////////////////////////////////////////////////////////
   
      /* one.png
    * Este sera una imagen 300x300 con un fondo negro llamado one.png
    * */
   pngwriter one(300,300,0,"one.png");
   
   std::cout << "Generating one.png...";
   
   /* Rectangulo Purpura (rellenado)
    * Crea un rectangulo purpura rellenado. Nota que estamos usando
    * niveles de color tipo int, asi que 65535 es el nivel maximo de rojo,
    * por ejemplo.
    * */ 
   one.filledsquare(30,5,45,295,65535,0,65535);
   
   /* Rectangulo Azul
    * Crea un rectangulo azul sobre el verde.
    * Nota que estamos usando coeficientes de color de tipo
    * double.
    * */
   one.square(20,10,40,290,0.0,0.0,1.0);
   
   /* Circulo amarillo rellenado y circulo gris
    * Usando coeficientes de color de tipo double,
    * luego int.
    * */
   one.filledcircle(250,250,40,1.0,1.0,0.0);
   one.circle(250,70,30,20000,20000,50000);
   
   /* Lineas
    * Dibuja 16 lineas para probar todas las direcciones de line().
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
   
   /*Cambia la informacion de texto en el header del archivo PNG
    * */
   one.settext("one.png", "John Cleese", "Test PNG", "pngtest");
   
   std::cout << " done. Writing to disk...";
   one.close();
   std::cout << " done." << std::endl;
  
  
  ////////////////////////////////////////////////////////////////////////////////////
   /*  two.png
    * Esta sera una imagen de 300x300 con un fondo negro, se llamara two.png.
    * Nota que estamos usando 0.0 como el color de fondo, y que estamos usando un objeto tipo
    * string como su nombre de archivo, el cual puede convertirse a un const char * diciendo
    * filename.c_str().
    * */
   std::cout << "Generating two.png...";
   string filename = "two.png";
   pngwriter two(300,300,0.0,filename.c_str()); 
 
   /* Gradientes
    * Aqui dibujamos algunos gradientes, los cuales no son mas que dibujar una
    * figura repetidas veces, moviendola lentamente y cambiando su color.
    * */
    
   /* Dibuja el gradiente en la esquina inferior izquierda.
    * */
   for(int iter = 1;iter< 300;iter++) 
     {	
	two.line(1,300,iter,1,65535-int(65535*((double)iter)/300.0), 0,65535);
     }
   
   /* Dibuja los circulos verdes.
    * */
   for(int iter2 = 0; iter2 < 8; iter2++)
     {
	two.filledcircle(280-25*iter2,250,10,0,65535 - int(65535*((double)iter2/7.0)),0);
     }
   
    /* Dibuja el otro gradiente central
    * Nota que estamos dibujando un cuadrado rellenado, y moviendo su esquina
    * superior derecha mientras se varia el color.
    * */
   for(int iter3 = 120; iter3>0;iter3--)
     {
	two.filledsquare(70,70,70+iter3,70+iter3,0,0,65535 -int(65535*((double)iter3/120.0 )))	;	
     }

  /* Dibuja el gradiente anaranjado circular.
    * */
   for(int iter4 = 0; iter4<31; iter4++)
     {
	two.filledcircle(250,200,30-iter4,1.0,1.0 - double(iter4)/30.0,0.0);
     }
   
   
   /* Ahora, como ejemplo, usaremos una compresion menor para esta imagen.
    * El valor prefijado es 6 (de 0 a 9) y lo fijaremos en 3.
    * Mientras mas baja sea la compresion, mas rapidamente se cerrara la imagen con close().
    * */
   two.setcompressionlevel(3);
   std::cout << " done. Writing to disk...";
   two.close();
   std::cout << " done." << std::endl;
    
   
   ///////////////////////////////////////////////////////////////////
  
   /* copiaburro.png
    * Esta seccion  abre burro.png y lo coloca en la instancia de PNGwriter
    * llamada burro.
    * Esta instancia tiene 1x1 pixeles, porque lo usaremos de contenedor
    * para otro png ya existente.
    * Nota que el original no es alterado.
    * */
   pngwriter burro(1,1,0,"copiaburro.png"); 
  
   /* readfromfile()
    * Ahora especificamos la ubicacion del archivo que deseamos colocar
    * dentro de la instancia de PNGwriter llamada burro.
    * */
   std::cout << "Opening burro.png...";   
   burro.readfromfile("src/burro.png"); //It really is that easy.
   std::cout << " done." << std::endl;
   
   /* getwidth() y getheight()
    * Quizas no conozcamos el tamanio de la imagen que acabamos de abrir.
    * Lo averiguamos con:
    * */
   int burrowidth = burro.getwidth();
   int burroheight = burro.getheight();
  
   
   std::cout << "The image that has just been read from disk (burro.png) is " << burro.getheight();
   std::cout << " pixels high and " << burro.getwidth()<<" pixels wide."<<std::endl;
   std::cout << "Bit depth is " << burro.getbitdepth()<<std::endl;
   std::cout << "Image gamma is: " << burro.getgamma() << std::endl; 
  
   /* Cubrir al Burro
    * Ahora dibujamos un circulo rojo sobre el burro,
    * solo para probar que la imagen ha sido leida correctamente y que
    * ha sido modificada.
    * */
   burro.filledcircle((int)(burrowidth/3.0),(int)(2.0*burroheight/3.0),(int)(burrowidth/5),65535,0,0);

   /* close()
    * Debemos cerrar la instancia para que se genere una imagen.
    * */
   std::cout << "Excribiendo imagen...";
   burro.close();
   std::cout << " listo." << std::endl; 
 
   /////////////////////////////////////////////////////////////////////
   
   /* Arcoiris
    * Para demostrar la utilidad de plotHSV(), generaremos
    * un arcoiris.
    * */ 
   pngwriter arcoiris(300,300,0,"arcoiris.png");
   
   for(int a= 1;a<301;a++)
      for(int b= 1;b<301;b++)
       arcoiris.plotHSV(a,b,double(a)/300.0,double(b)/300.0,1.0);

   arcoiris.setgamma(0.5);
   arcoiris.close();

   
   /////////////////////////////////////////////////////////////////
   
   /* Triangulos aleatorios llenados y combinados con el fondo.*/
   
   
   srand ( time(NULL) );
   
   std::cout << "\nCreando triangles.png...";
   pngwriter triangles(400,400,0,"triangles.png");
   std::cout << " listo.";
   double opacityrange = 0.3;
   
   std::cout << "\nPloteando triangulos...";
   for(int jj = 0; jj < 10;  jj++)
     {
	
	//Esto crea los triangulos azules
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
	//Esto crea los triangulos rojos combinados
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
   std::cout << " listo.";   
   std::cout << "\nEscribiendo imagen...";
   triangles.close();
   std::cout << " listo.";
   std::cout << "\n\npngtest ha terminado. Mira las imagenes creadas!\n";
   
   
   return 0;
}
