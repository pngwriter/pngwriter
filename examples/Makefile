########################## PNGwriter #########################################
#
#   Website: Main:             http://pngwriter.sourceforge.net/
#            GitHub.com:       https://github.com/pngwriter/pngwriter
#            Sourceforge.net:  http://sourceforge.net/projects/pngwriter/
#
#
#    Author:                    Paul Blackburn https://github.com/individual61
#                               Axel Huebl https://github.com/ax3l
#
#    Email:                     individual61@users.sourceforge.net
#
#    Version:                   0.5.6 (December 2015)
#
#    Description:               Library that allows plotting a 48 bit
#                               PNG image pixel by pixel, which can
#                               then be opened with a graphics program.
#
#    License:                   GNU General Public License
#                               (C) 2002-2015 Paul Blackburn
#                               (C) 2013-2015 Axel Huebl
#
##############################################################################

######################## IMPORTANT ############################################
# This makefile is meant to help beginning programmers learn about simple 
# Makefiles. The compilation uses the object file, and not the library,
# because I belive it to be a more 'hands-on' approach.
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
	rm -f lyapunov.cc~ Makefile~
	rm -f .DS_Store out.png triangles.png
