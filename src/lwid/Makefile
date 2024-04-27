all: library

TOPDIR = ../..
LIBRARY = liblwid.a

include $(TOPDIR)/Makerules

HEADERS = ButtonBox.h ButtonBoxP.h CellTable.h CellTableP.h Bubble.h BubbleP.h\
 DrawerP.h Drawer.h

OBJS = 	ButtonBox.o CellTable.o Bubble.o Drawer.o

SRCS = 	ButtonBox.c CellTable.c Bubble.c Drawer.c

EXTRA_CFLAGS = -I.. $(SHLIB_OPTION)

test: $(ARCH)/check

depend: depend-src

install: $(ARCH)/liblwid.a $(HEADERS)
	cp -f $(ARCH)/liblwid.a $(TOPDIR)/lib; \
	cp -f $(HEADERS) $(TOPDIR)/include/lwid
	@$(INSTALL) Imakefile src/lwid/Imakefile
	@$(INSTALL) README src/lwid/README
	@(for i in $(HEADERS) $(SRCS); do \
	   $(INSTALL) $$i src/lwid/$$i ; \
	done)


$(ARCH)/check: check.c $(ARCH)/$(LIBRARY)
	$(CCLINK) $(CFLAGS) -o $(ARCH)/check check.c $(ARCH)/$(LIBRARY) $(LIBS)

clean: clean-src





# DO NOT DELETE

ButtonBox.o: ButtonBoxP.h /usr/dt/include/X11/IntrinsicP.h
ButtonBox.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
ButtonBox.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
ButtonBox.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
ButtonBox.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
ButtonBox.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
ButtonBox.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
ButtonBox.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
ButtonBox.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
ButtonBox.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/CoreP.h
ButtonBox.o: /usr/dt/include/X11/CompositeP.h
ButtonBox.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
ButtonBox.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/ManagerP.h
ButtonBox.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/Xm/Xm.h
ButtonBox.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
ButtonBox.o: /usr/dt/include/Xm/XmStrDefs.h /usr/dt/include/X11/StringDefs.h
ButtonBox.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
ButtonBox.o: /usr/dt/include/Xm/BaseClassP.h ButtonBox.h /usr/include/stdio.h
CellTable.o: CellTableP.h /usr/dt/include/X11/IntrinsicP.h
CellTable.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
CellTable.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
CellTable.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
CellTable.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
CellTable.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
CellTable.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
CellTable.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
CellTable.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
CellTable.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/CoreP.h
CellTable.o: /usr/dt/include/X11/CompositeP.h
CellTable.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
CellTable.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/ManagerP.h
CellTable.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/Xm/Xm.h
CellTable.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
CellTable.o: /usr/dt/include/Xm/XmStrDefs.h /usr/dt/include/X11/StringDefs.h
CellTable.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
CellTable.o: /usr/dt/include/Xm/BaseClassP.h CellTable.h /usr/include/stdio.h
CellTable.o: /usr/include/stdlib.h
Bubble.o: BubbleP.h /usr/dt/include/X11/IntrinsicP.h
Bubble.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
Bubble.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
Bubble.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
Bubble.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
Bubble.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
Bubble.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
Bubble.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
Bubble.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
Bubble.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/CoreP.h
Bubble.o: /usr/dt/include/X11/CompositeP.h /usr/dt/include/X11/ConstrainP.h
Bubble.o: /usr/dt/include/X11/ObjectP.h /usr/dt/include/X11/RectObjP.h
Bubble.o: /usr/dt/include/X11/ShellP.h /usr/dt/include/X11/Shell.h
Bubble.o: /usr/dt/include/X11/VendorP.h /usr/dt/include/X11/Vendor.h Bubble.h
Bubble.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Xatom.h
Bubble.o: /usr/dt/include/Xm/XmStrDefs.h /usr/dt/include/X11/StringDefs.h
Bubble.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
Bubble.o: /usr/include/stdio.h /usr/dt/include/Xm/Label.h
Drawer.o: DrawerP.h /usr/dt/include/X11/IntrinsicP.h
Drawer.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
Drawer.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
Drawer.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
Drawer.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
Drawer.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
Drawer.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
Drawer.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
Drawer.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
Drawer.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/CoreP.h
Drawer.o: /usr/dt/include/X11/CompositeP.h /usr/dt/include/X11/ConstrainP.h
Drawer.o: /usr/dt/include/X11/ObjectP.h /usr/dt/include/X11/RectObjP.h
Drawer.o: /usr/dt/include/Xm/ManagerP.h /usr/dt/include/Xm/XmP.h
Drawer.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
Drawer.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
Drawer.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
Drawer.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/Xm/BaseClassP.h
Drawer.o: Drawer.h /usr/include/stdio.h /usr/dt/include/Xm/SashP.h
Drawer.o: /usr/dt/include/Xm/PrimitiveP.h /usr/dt/include/Xm/Label.h
Drawer.o: /usr/dt/include/Xm/ArrowB.h /usr/dt/include/Xm/Separator.h
