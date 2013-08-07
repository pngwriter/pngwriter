############ MAKEFILE FOR PNGWRITER ######################################
#
#
#       Website: Main:             http://pngwriter.sourceforge.net/
#                Sourceforge.net:  http://sourceforge.net/projects/pngwriter/
#                Freshmeat.net:    http://freshmeat.net/projects/pngwriter/
#  
#       Author:                    Paul Blackburn
#
#       Email:                     individual61@users.sourceforge.net
#
#       Version:                   0.5.4   (19 / II / 2009)
#
#       Description:               Library that allows plotting a 48 bit
#                                  PNG image pixel by pixel, which can 
#                                  then be opened with a graphics program.
#  
#       License:                   GNU General Public License
#                                  Copyright 2002, 2003, 2004, 2005, 2006, 2007,
#                                  2008, 2009 Paul Blackburn
#
###############################################################################

######################## IMPORTANT - IMPORTANTE ###############################
# ENGLISH
# This makefile is meant to help beginning programmers learn about simple 
# Makefiles. The compilation uses the object file, and not the library,
# because I belive it to be a more 'hands-on' approach.
#
# CASTELLANO/ESPANIOL
# Este makefile se hizo teniendo en mente a los programadores principiantes,
# para ayudarles a aprender acerca de Makefiles simples. La compilacion usa
# el archivo objeto, no la libreria, porque creo que es una forma mas
# aplicada de hacer las cosas.
# La explicacion en castellano se encuentra al final de este Makefile.
###############################################################################


include ../make.include

EXAMPLES= pngtest lyapunov

all: $(EXAMPLES)

pngtest: pngtest.cc
	$(CXX) $(CXXFLAGS) $(INC) pngtest.cc -o pngtest $(LIBS) 

lyapunov: lyapunov.cc
	$(CXX) $(CXXFLAGS) $(INC) lyapunov.cc -o lyapunov $(LIBS) 

clean	:    
	rm -f $(EXAMPLES) *~ arcoiris.png copiaburro.png one.png two.png
	rm -f lyapunov.cc~ lyapunov.espaniol.cc~ Makefile~ pngtest.espaniol.cc~
	rm -f .DS_Store out.png triangles.png
	
	
	
# Note: The following section is a bit outdated, but the info is still useful
# in a general sense.


##############################################################################
# INTRODUCTION 
# This makefile can get you started if you dont know how to use one. 
#
# The important thing that you must know is that the most basic thing that you
# need to be able to use PNGwriter is an object file, pngwriter.o. To create
# it (we'll get to that in a moment), you'll need to have libpng installed and
# you can get that from www.libpng.org, but you'll probably have it already
# installed.
# 
#
# OPTIONS
# What Compilation Options Can I Choose From?
#
# This Makefile will allow you to compile PNGwriter and the test programs
# for two (2) different system types. These are:
#
#   ** UNIX/Linux                                 ('make')
#   ** Mac OS X with fink-installed libpng        ('make all-osx')
#
#
#  PNGwriter can be compiled on many more system configurations,
# but it's up to you to make your own custom Makefile to suit your needs.
#
#
# MAKEFILE BASICS
# What do the compiler flags that are used here mean?
# 
# -O3 (dash-oh-three). Code optimization. 1 is slight, 3 is max.
# 
# -o "What you output, output with this filename".
# 
# -c Compile the code, but don't link. Think of this as the instruction given
# to a carpenter who has made the parts to make a chair. He is told with this
# flag that he must not glue the chair together yet. The seat of the chair is
# useless by itself, it needs to be glued to the other parts of the chair to
# be useful. -c will make an object file, and this is what we want to do with
# PNGwriter, by creating pngwriter.o. This is like making a leg of a chair
# (the whole chair is your entire program) and we'll leave it ready for when
# your chair is ready for gluing (compiling and linking the final program).
# The advantage of this approach is, that if you need to re-do a part of the
# chair, you dont have to make (compile) the legs of the chair all over again.
# You can even take the object file (pngwriter.o) once it is compiled and use
# it in another project (remember to take the pngwriter.h file as well!)
#
# -I (uppercase i). If you, like me, have a few header files installed in a
# non-standard place, then say where with this option.
#
# -L The same, but for libraries.
#
# -l (lowecase L). To use a library. For libpng, use -lpng. For Zlib, use
#    -lz.
#
#    
#######################################################################################



Nota: Esta información ya no es muy vigente ni relevante, pero puede ser útil en general.


################################### CASTELLANO / ESPANIOL ###############################################
# INTRODUCCION
# Este makefile te puede ayudar si no sabes como usar uno. 
#
# Lo importante que
# tienes que saber es que lo basico para usar PNGwriter es que se pueda
# generar pngwriter.o. Necesita de libpng, una libreria de funciones para
# facilitar la vida a la gente que trabaja con lectores/creadores de imagenes
# PNG. Debes tener esta libreria ya instalada. Si no es asi, anda a
# www.libpng.org y bajala.
#
# Nota: Este documento se ha escrito sin acentos para que sea mas portatil.
#
# OPCIONES
# Que Opciones De Compilacion Puedo Elegir?
#
# PNGwriter puede ser compilado en muchas configuraciones distintas de sistemas,
# pero tu tendras que crear un Makefile personalizado.
#
#
# ASPECTOS BASICOS DE LOS MAKEFILE
# Que significan las opciones que se usan aqui?
#
# -O3 (raya oh tres). Optimizacion del codigo. 1 es leve, 3 es maximo.
#
# -o "Lo que produzcas, crealo con este nombre".
#
# -c Compila el codigo, pero no lo linkees. Piensa en esto como un carpintero
# que hace una silla pero todavia no pega las distintas partes. El respaldo es
# un respaldo, pero como silla, es inutil, necesita del resto de las partes.
# Eso hace el linker. Un .o es como el respaldo de la silla, o una pata. La gracia es que
# PNGwriter es como una de las patas, y uno puede usar la pata de PNGwriter ya
# tallada (ya compilada) en otra silla (otro proyecto).
#
# -I (i mayuscula): Si tu, como yo, tienes algunos "include" (.h) instalados en un lugar no
# estandard, especifica donde con -I. 
#
# -L: Lo mismo, pero para librerias.
#
# -l (L minuscula): Para usar una libreria. Para usar libpng, usa -lpng. Para Zlib,
# usa -lz.
#######################################################################################

