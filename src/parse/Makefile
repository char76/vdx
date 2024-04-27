# Makefile
# $Log: Makefile,v $
# Revision 1.1.1.1.2.1  1998/07/01 18:31:51  lazy
# Patches gcc 2.8
#
# Revision 1.1.1.1  1998/04/24 23:45:52  lazy
# Imported to CVS
#
# Revision 1.3  1998/03/30 19:09:59  lazy
# *** empty log message ***
#
# Revision 1.2  1997/07/25  14:43:19  lazy
# Log eingefuegt.
#


TOPDIR = ../..

all:	library

LIBRARY = libparse.a

include $(TOPDIR)/Makerules

LFLAGS	= 
YFLAGS	= -d 

OBJS = 	y.o l.o write.o misc.o
SRCS = 	y.c l.c write.c misc.c

depend: depend-src

install:
	@echo Do nothing

clean: clean-src
	rm -f y.c l.c

# DO NOT DELETE

write.o: parse.h /usr/include/limits.h /usr/include/sys/stdsyms.h
write.o: /usr/include/stdlib.h /usr/include/stdio.h /usr/include/sys/types.h
write.o: /usr/include/sys/_inttypes.h /usr/include/string.h
write.o: /usr/include/errno.h /usr/include/sys/errno.h
misc.o: parse.h /usr/include/limits.h /usr/include/sys/stdsyms.h
misc.o: /usr/include/string.h /usr/include/stdlib.h
