#!/bin/sh
#
# Copyright 1998, Dirk Laessig (dirk@bredex.de)
#
# $Log: mksrc-dist.sh,v $
# Revision 1.1.2.2  1998/07/01 18:31:23  lazy
# Patches gcc 2.8
#
#

echo "----------------------------------"
echo "    create source distribution    "
echo "----------------------------------"
echo
echo "Make sure that source tree is clean!"
echo "(return to proceed)"
read dummy


#
# Create archive
#

(
	cd ..
	tar cvf /tmp/vdx.tar vdx
)

#
# Untar in tmp and remove license stuff
#

(
	cd /tmp
	tar xvf vdx.tar
	cd /tmp/vdx/src/license 
	rm -rf * 
	cat >license.h <<END
#ifndef _LICENSE_H_
#define _LICENSE_H_

#ifdef __cplusplus
extern "C" {
#endif


int testLicenseFile(char *, char *str, int maxStr);

#ifdef __cplusplus
}
#endif

#endif
END


	cat >license.c <<END
#include "license.h"

int testLicenseFile(char *f, char *str, int maxStr)
{
	strncpy(str, "Source License", maxStr);
	return 1;
}
END



	cat >Makefile <<END
TOPDIR = ../..

all: library 

LIBRARY = liblicense.a

include \$(TOPDIR)/Makerules

LIBS = 

OBJS = 	license.o 
SRCS = 	license.c 

depend: depend-src

install:
	@echo "nothing to do"

clean: clean-src

END

	cd /tmp/vdx/doc/guide
	rm -rf *
	cat >Makefile <<END
all:
	@echo "Do nothing"

clean:
	@echo "Do nothing"

depend:
	@echo "Do nothing"

END
	cd /tmp/vdx/doc/
	rm -rf ax-docs

	cat Makefile | sed -e '/ax-docs\//d' | sed -e '/guide\//d' > Makefile.n
	mv Makefile.n Makefile

	cd /tmp/vdx
	rm -f lib/X11/vdx/licence.dat
	rm -f lib/X11/vdx/licence.cpu
)

(
	cd /tmp
	tar cvf vdx.tar vdx
	echo
	echo Uncompressed tar archive vdx.tar in /tmp
	echo
)
