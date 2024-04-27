
TOPDIR = ../..
PROGRAM = vdx.bin

include $(TOPDIR)/Makerules

#
# USE_LWID	// Lazy Widget Library 
# USE_XRT	// Xrt widgets from Klg
# USE_INT	// Int widgets from Int
# USE_BX	// BXwidgets from Bredex
#

EXTRA_CFLAGS = $(SHLIB_OPTION) \
-DUSE_LWID -I.. \
-DUSE_XFE -I.. \
#-DUSE_XRT -I/usr/local/xrt/include \
#-DUSE_BX  -I/usr/local/BXwidgets/include \
#-DUSE_INT -I/usr/local/INT 


VDXLIB = $(ARCH)/libvdx.so

all:  $(VDXLIB) 
	rm -f $(TOPDIR)/lib/libvdx.so
	ln -s `pwd`/$(VDXLIB) $(TOPDIR)/lib

SRCS = LClassInfo.C
OBJS = LClassInfo.o

WIDGET_LIBS = \
-L../lwid/$(ARCH) -llwid \
-L../Xfe/$(ARCH) -lXfeWidgets \
-Wl,-R/usr/dt/lib,-R/usr/openwin/lib $(LIBS) 
#-L/usr/local/xrt/lib -lxrt3d -lxrtm -lxrttable -lxrtfield -lxrtgear \
#-L/usr/local/BXwidgets/lib -lBXm \
#-L/usr/local/INT/lib -lINT \



# -L/usr/local/metro/lib -lXpm -lXm -lXt -lXext -lX11 



$(VDXLIB): $(ARCH)/$(OBJS)
	$(MKSHARED) -o $@ $(ARCH)/LClassInfo.o $(WIDGET_LIBS)


depend: depend-src

clean: clean-src
	rm -f $(VDXLIB)

install:
	@$(INSTALL) $(VDXLIB) lib/libvdx.so
	@$(INSTALL) LClassInfo.C src/vdxlib/LClassInfo.C
	@$(INSTALL) LClassInfo.h src/vdxlib/LClassInfo.h
	@$(INSTALL) Imakefile src/vdxlib/Imakefile
	@$(INSTALL) config.sh src/vdxlib/config.sh
	@$(INSTALL) config.tmpl src/vdxlib/config.tmpl







# DO NOT DELETE
