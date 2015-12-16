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

################# IMPORTANT ##################################################
#
# Please read the README file for instructions on compilation options.
#
##############################################################################

# Default installation is for a Linux/UNIX type system. 
# Makefile options for Mac OS X (with Fink-installed libpng) 
# are also available. See the README.



##############################################################################

include make.include

MAJVERSION=0
MINVERSION=5.6
VERSION=$(MAJVERSION).$(MINVERSION)


ifdef P_FREETYPE
FT_REPORT = without
else
FT_REPORT = with
endif




all	:    libpngwriter examples

libpngwriter: intro
	cd src;	make 

examples: libpngwriter
	cd examples; make

intro	:
	@ echo "#"
	@ echo "#"
	@ echo "#  PNGwriter $(VERSION)"
	@ echo "#  Copyright 2002-2015 Paul Blackburn, 2013-2015 Axel Huebl"
	@ echo "#  http://pngwriter.sourceforge.net/"
	@ echo "#  This library and its associated files are covered"
	@ echo "#  by the GNU General Public License."
	@ echo "#"
	@ echo "#  Using $(SELF) for your compilation/installation prefs."
	@ echo "#"
	@ echo "#  Important: If you do not have FreeType2 installed, "
	@ echo "#  see the README for instructions on compiling PNGwriter"
	@ echo "#  without FreeType2 support."
	@ echo "#"	
	@ echo "#  You have selected to compile PNGwriter $(FT_REPORT)"
	@ echo "#  FreeType2 support."
	@ echo "#"
	@ echo "#"


install:  docs 
	@ echo "#"
	@ echo "#"
	@ echo "#  PNGwriter $(VERSION)"
	@ echo "#  Copyright 2002-2015 Paul Blackburn, 2013-2015 Axel Huebl"
	@ echo "#  http://pngwriter.sourceforge.net/"
	@ echo "#  This library and its associated files are covered"
	@ echo "#  by the GNU General Public License."
	@ echo "#"
	@ echo "#  Note: You can only install to a directory you own,"
	@ echo "#  if you are not root. To install elsewhere, compile "
	@ echo "#  PNGwriter by giving Make the destination directory:"
	@ echo "#"
	@ echo "#  make DESTDIR=$HOME (for example)"
	@ echo "#"
	@ echo "#  Alternatively, you can change DESTDIR in 'make.include'."
	@ echo "#"
	@ echo "#  Using $(SELF) for your compilation/installation prefs."
	@ echo "#"
	@ echo "#  The following files will be installed:"
	@ echo "#"
	@ echo "#    pngwriter.h     in $(DESTDIR)$(PREFIX)/include/"
	@ echo "#    libpngwriter.a  in $(DESTDIR)$(PREFIX)/lib/"
	@ echo "#    examples/       in $(DESTDIR)$(PREFIX)/share/doc/pngwriter/"
	@ echo "#    doc/            in $(DESTDIR)$(PREFIX)/share/doc/pngwriter/"
	@ echo "#    Fonts	     in $(DESTDIR)$(PREFIX)/share/pngwriter/fonts"
	@ echo "#"
	@ echo "#"	
	$(INSTALL) -d -v $(DESTDIR)$(PREFIX)/include/ $(DESTDIR)$(PREFIX)/lib/
	$(INSTALL) -d -v $(DESTDIR)$(PREFIX)/share/pngwriter/fonts/
	$(INSTALL) -S -v -m644 src/pngwriter.h $(DESTDIR)$(PREFIX)/include/
	$(INSTALL) -S -v -m644 src/libpngwriter.a $(DESTDIR)$(PREFIX)/lib/
	$(INSTALL) -S -v -m644 fonts/*  $(DESTDIR)$(PREFIX)/share/pngwriter/fonts/
	$(INSTALL) -d -v $(DESTDIR)$(PREFIX)/share/doc/pngwriter
	cp -pR doc/* $(DESTDIR)$(PREFIX)/share/doc/pngwriter
	$(INSTALL) -d -v $(DESTDIR)$(PREFIX)/share/doc/pngwriter/examples
	cp examples/*.cc examples/*png  \
	$(DESTDIR)$(PREFIX)/share/doc/pngwriter/examples/
	$(OSXSPECIFIC)


docs	:
	cp doc/README doc/README.bak
	cat doc/README.bak | \
	sed   's# -  libpngwriter.a:# -  libpngwriter.a: $(PREFIX)/lib/#g' > doc/README
	
	cp doc/README doc/README.bak
	cat doc/README.bak | \
	sed   's# -  pngwriter.h:# -  pngwriter.h: $(PREFIX)/include/#g' > doc/README

	cp doc/README doc/README.bak
	cat doc/README.bak | \
	sed   's# -  documentation:# -  documentation: $(PREFIX)/share/doc/pngwriter/#g' > doc/README

	cp doc/README doc/README.bak
	cat doc/README.bak | \
	sed   's# -  examples:# -  examples: $(PREFIX)/share/doc/pngwriter/#g' > doc/README

	cp doc/README doc/README.bak
	cat doc/README.bak | \
	sed   's# -  fonts:# -  fonts: $(PREFIX)/share/pngwriter/fonts/#g' > doc/README

	rm doc/README.bak
#

	rm -f READMEe doc/READMEe


clean	:    
	cd src; make clean
	cd examples; make clean
	cd doc/; rm -f CHANGES~ README~ LICENSE~ EXAMPLES~ .DS_Store
	rm -f README~ Makefile~ make.include.linux~ make.include.osx~ .DS_Store
	rm -f make.include.linux.oldcpp~ make.include.osx_test~ doc/.DS_Store

#


	cp README README.bak
	cat README.bak | \
	sed   's# -  libpngwriter.a: $(PREFIX)/lib/# -  libpngwriter.a:#g' > README
	
	cp README README.bak
	cat README.bak | \
	sed   's# -  pngwriter.h: $(PREFIX)/include/# -  pngwriter.h:#g' > README

	cp README README.bak
	cat README.bak | \
	sed   's# -  documentation: $(PREFIX)/share/doc/pngwriter/# -  documentation:#g' > README

	cp README README.bak
	cat README.bak | \
	sed   's# -  examples: $(PREFIX)/share/doc/pngwriter/# -  examples:#g' > README

	cp README README.bak
	cat README.bak | \
	sed   's# -  fonts: $(PREFIX)/share/pngwriter/fonts/# -  fonts:#g' > README

	rm README.bak


#

	cp doc/README doc/README.bak
	cat doc/README.bak | \
	sed   's# -  libpngwriter.a: $(PREFIX)/lib/# -  libpngwriter.a:#g' > doc/README
	
	cp doc/README doc/README.bak
	cat doc/README.bak | \
	sed   's# -  pngwriter.h: $(PREFIX)/include/# -  pngwriter.h:#g' > doc/README

	cp doc/README doc/README.bak
	cat doc/README.bak | \
	sed   's# -  documentation: $(PREFIX)/share/doc/pngwriter/# -  documentation:#g' > doc/README

	cp doc/README doc/README.bak
	cat doc/README.bak | \
	sed   's# -  examples: $(PREFIX)/share/doc/pngwriter/# -  examples:#g' > doc/README

	cp doc/README doc/README.bak
	cat doc/README.bak | \
	sed   's# -  fonts: $(PREFIX)/share/pngwriter/fonts/# -  fonts:#g' > doc/README

	rm doc/README.bak


	rm -f READMEe doc/READMEe
