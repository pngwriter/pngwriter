############ PARTIAL MAKEFILE FOR PNGWRITER ######################################
#
#       Website: Main:             http://pngwriter.sourceforge.net/
#       Author:                    Paul Blackburn
#                                  Axel Huebl https://github.com/ax3l
#       Email:                     individual61@users.sourceforge.net
#       Version:                   0.5.5 (May 2014)
#       License:                   GNU General Public License
#                                  Copyright 2002, 2003, 2004, 2005, 2006, 2007,
#                                  2008, 2009 Paul Blackburn
#                                  Copyright 2013, 2014 Axel Huebl
#
##################################################################################


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


	
