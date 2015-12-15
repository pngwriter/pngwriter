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


include ../make.include

OBJECTS=pngwriter.o
all: libpngwriter.a

libpngwriter.a: $(OBJECTS)
	ar rv $@ $^
	ranlib $@

pngwriter.o: pngwriter.cc pngwriter.h
	$(CXX) $(CXXFLAGS) $(INC) -g -c -o pngwriter.o pngwriter.cc

clean	:    
	rm -f $(OBJECTS) libpngwriter.a pngtest.cc~ pngwriter.cc~
	rm -f pngwriter.h~ Makefile~
	rm -f .DS_Store
