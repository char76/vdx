#!gmake
#
# The contents of this file are subject to the Netscape Public License
# Version 1.0 (the "NPL"); you may not use this file except in
# compliance with the NPL.  You may obtain a copy of the NPL at
# http://www.mozilla.org/NPL/
#
# Software distributed under the NPL is distributed on an "AS IS" basis,
# WITHOUT WARRANTY OF ANY KIND, either express or implied. See the NPL
# for the specific language governing rights and limitations under the
# NPL.
#
# The Initial Developer of this code under the NPL is Netscape
# Communications Corporation.  Portions created by Netscape are
# Copyright (C) 1998 Netscape Communications Corporation.  All Rights
# Reserved.

all: library

TOPDIR = ../..
LIBRARY = libXfeWidgets.a

include $(TOPDIR)/Makerules

# 
#
# This guy is just a demo widget that has all the bells and whistles.
# It can be conveniently used as a template.
#
#		TempTwo.c
#

OBJS		= \
		  Arrow.o \
		  BmButton.o \
		  BmCascade.o \
		  Button.o \
		  BypassShell.o \
		  CallProcs.o \
		  Cascade.o \
		  ChildrenUtil.o \
		  Chrome.o \
		  ComboBox.o \
		  Converters.o \
		  Cursor.o \
		  DashBoard.o \
		  Debug.o \
		  DialogUtil.o \
		  Draw.o \
		  FancyBox.o \
		  Find.o \
		  FontChooser.o \
		  FrameShell.o \
		  GcUtil.o \
		  Geometry.o \
		  Label.o \
		  ListUtil.o \
		  Logo.o \
		  Manager.o \
		  MenuUtil.o \
		  Oriented.o \
		  Pane.o \
		  PixmapUtil.o \
		  Primitive.o \
		  Private.o \
		  ProgressBar.o \
		  RepType.o \
		  Resources.o \
		  ShellUtil.o \
		  StringUtil.o \
		  Tab.o \
		  TaskBar.o \
		  ToolBar.o \
		  ToolBox.o \
		  ToolItem.o \
		  ToolScroll.o \
		  Translations.o \
		  Util.o \
		  WmUtil.o 

SRCS = \
Arrow.c         Converters.c    GcUtil.c        Primitive.c     ToolBar.c \
BmButton.c      Cursor.c        Geometry.c      Private.c       ToolBox.c \
BmCascade.c     DashBoard.c     Label.c         ProgressBar.c   ToolItem.c \
Button.c        Debug.c         ListUtil.c      RepType.c       ToolScroll.c \
BypassShell.c   DialogUtil.c    Logo.c          Resources.c     Translations.c \
CallProcs.c     Draw.c          Manager.c       ShellUtil.c     Util.c \
Cascade.c       FancyBox.c      MenuUtil.c      StringUtil.c    WmUtil.c \
ChildrenUtil.c  Find.c          Oriented.c      Tab.c \
Chrome.c        FontChooser.c   Pane.c          TaskBar.c \
ComboBox.c      FrameShell.c    PixmapUtil.c    TempTwo.c

HEADERS = \
Arrow.h         ComboBox.h      FrameShellP.h   PaneP.h         TempTwo.h \
ArrowP.h        ComboBoxP.h     Geometry.h      PrepareP.h      TempTwoP.h \
BmButton.h      Converters.h    GeometryP.h     Primitive.h     ToolBar.h \
BmButtonP.h     DashBoard.h     Label.h         PrimitiveP.h    ToolBarP.h \
BmCascade.h     DashBoardP.h    LabelP.h        ProgressBar.h   ToolBox.h \
BmCascadeP.h    Debug.h         ListUtil.h      ProgressBarP.h  ToolBoxP.h \
Button.h        Defaults.h      ListUtilP.h     RepType.h       ToolItem.h \
ButtonP.h       DialogUtil.h    Logo.h          Resources.h     ToolItemP.h \
BypassShell.h   Draw.h          LogoP.h         ShellUtil.h     ToolScroll.h \
BypassShellP.h  FancyBox.h      Manager.h       StringDefs.h    ToolScrollP.h \
Cascade.h       FancyBoxP.h     ManagerP.h      StringUtil.h    WmUtil.h \
CascadeP.h      Find.h          MenuUtil.h      Tab.h           Xfe.h \
ChildrenUtil.h  FontChooser.h   Oriented.h      TabP.h          XfeAll.h \
Chrome.h        FontChooserP.h  OrientedP.h     TaskBar.h       XfeP.h \
ChromeP.h       FrameShell.h    Pane.h          TaskBarP.h

EXTRA_CFLAGS = -DVDX_CHANGES -I.. $(SHLIB_OPTION)

clean:	clean-src

depend: depend-src

install:
	@$(INSTALL) Imakefile src/Xfe/Imakefile
	@$(INSTALL) README src/Xfe/README
	@$(INSTALL) LICENSE src/Xfe/LICENSE
	@$(INSTALL) CHANGES src/Xfe/CHANGES
	@(for i in $(HEADERS) $(SRCS); do \
	   $(INSTALL) $$i src/Xfe/$$i ; \
	done)
# DO NOT DELETE

Arrow.o: ../Xfe/ArrowP.h ../Xfe/Arrow.h ../Xfe/Xfe.h /usr/dt/include/Xm/Xm.h
Arrow.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
Arrow.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
Arrow.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
Arrow.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
Arrow.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
Arrow.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
Arrow.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
Arrow.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
Arrow.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
Arrow.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
Arrow.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
Arrow.o: /usr/dt/include/Xm/VendorS.h ../Xfe/StringDefs.h ../Xfe/Defaults.h
Arrow.o: ../Xfe/ChildrenUtil.h ../Xfe/Converters.h ../Xfe/DialogUtil.h
Arrow.o: ../Xfe/Draw.h ../Xfe/Find.h /usr/include/assert.h ../Xfe/Geometry.h
Arrow.o: ../Xfe/ListUtil.h ../Xfe/MenuUtil.h ../Xfe/RepType.h
Arrow.o: ../Xfe/Resources.h ../Xfe/ShellUtil.h ../Xfe/StringUtil.h
Arrow.o: ../Xfe/WmUtil.h ../Xfe/ButtonP.h ../Xfe/Button.h ../Xfe/Label.h
Arrow.o: ../Xfe/Primitive.h ../Xfe/LabelP.h ../Xfe/PrimitiveP.h ../Xfe/XfeP.h
Arrow.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/X11/IntrinsicP.h
Arrow.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
Arrow.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
Arrow.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
Arrow.o: /usr/dt/include/Xm/DrawP.h ../Xfe/GeometryP.h ../Xfe/PrepareP.h
Arrow.o: /usr/dt/include/Xm/PrimitiveP.h ../Xfe/ManagerP.h ../Xfe/Manager.h
Arrow.o: /usr/dt/include/Xm/ManagerP.h /usr/dt/include/Xm/RowColumnP.h
Arrow.o: /usr/dt/include/Xm/RowColumn.h
Converters.o: ../Xfe/XfeP.h /usr/dt/include/Xm/XmP.h /usr/dt/include/Xm/Xm.h
Converters.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
Converters.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
Converters.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
Converters.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
Converters.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
Converters.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
Converters.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
Converters.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
Converters.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
Converters.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
Converters.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
Converters.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/X11/IntrinsicP.h
Converters.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
Converters.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
Converters.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
Converters.o: /usr/dt/include/Xm/DrawP.h ../Xfe/Xfe.h ../Xfe/StringDefs.h
Converters.o: ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h ../Xfe/Converters.h
Converters.o: ../Xfe/DialogUtil.h ../Xfe/Draw.h ../Xfe/Find.h
Converters.o: /usr/include/assert.h ../Xfe/Geometry.h ../Xfe/ListUtil.h
Converters.o: ../Xfe/MenuUtil.h ../Xfe/RepType.h ../Xfe/Resources.h
Converters.o: ../Xfe/ShellUtil.h ../Xfe/StringUtil.h ../Xfe/WmUtil.h
Converters.o: ../Xfe/GeometryP.h
GcUtil.o: ../Xfe/XfeP.h /usr/dt/include/Xm/XmP.h /usr/dt/include/Xm/Xm.h
GcUtil.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
GcUtil.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
GcUtil.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
GcUtil.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
GcUtil.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
GcUtil.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
GcUtil.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
GcUtil.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
GcUtil.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
GcUtil.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
GcUtil.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
GcUtil.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/X11/IntrinsicP.h
GcUtil.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
GcUtil.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
GcUtil.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
GcUtil.o: /usr/dt/include/Xm/DrawP.h ../Xfe/Xfe.h ../Xfe/StringDefs.h
GcUtil.o: ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h ../Xfe/Converters.h
GcUtil.o: ../Xfe/DialogUtil.h ../Xfe/Draw.h ../Xfe/Find.h
GcUtil.o: /usr/include/assert.h ../Xfe/Geometry.h ../Xfe/ListUtil.h
GcUtil.o: ../Xfe/MenuUtil.h ../Xfe/RepType.h ../Xfe/Resources.h
GcUtil.o: ../Xfe/ShellUtil.h ../Xfe/StringUtil.h ../Xfe/WmUtil.h
GcUtil.o: ../Xfe/GeometryP.h
Primitive.o: /usr/include/stdio.h /usr/include/sys/stdsyms.h
Primitive.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
Primitive.o: ../Xfe/PrimitiveP.h ../Xfe/XfeP.h /usr/dt/include/Xm/XmP.h
Primitive.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Intrinsic.h
Primitive.o: /usr/dt/include/X11/Xlib.h /usr/dt/include/X11/X.h
Primitive.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
Primitive.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
Primitive.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
Primitive.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
Primitive.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
Primitive.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
Primitive.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
Primitive.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
Primitive.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/X11/IntrinsicP.h
Primitive.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
Primitive.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
Primitive.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
Primitive.o: /usr/dt/include/Xm/DrawP.h ../Xfe/Xfe.h ../Xfe/StringDefs.h
Primitive.o: ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h ../Xfe/Converters.h
Primitive.o: ../Xfe/DialogUtil.h ../Xfe/Draw.h ../Xfe/Find.h
Primitive.o: /usr/include/assert.h ../Xfe/Geometry.h ../Xfe/ListUtil.h
Primitive.o: ../Xfe/MenuUtil.h ../Xfe/RepType.h ../Xfe/Resources.h
Primitive.o: ../Xfe/ShellUtil.h ../Xfe/StringUtil.h ../Xfe/WmUtil.h
Primitive.o: ../Xfe/GeometryP.h ../Xfe/Primitive.h ../Xfe/PrepareP.h
Primitive.o: /usr/dt/include/Xm/PrimitiveP.h
ToolBar.o: /usr/include/stdio.h /usr/include/sys/stdsyms.h
ToolBar.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
ToolBar.o: ../Xfe/ToolBarP.h ../Xfe/ToolBar.h ../Xfe/Oriented.h ../Xfe/Xfe.h
ToolBar.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Intrinsic.h
ToolBar.o: /usr/dt/include/X11/Xlib.h /usr/dt/include/X11/X.h
ToolBar.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
ToolBar.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
ToolBar.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
ToolBar.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
ToolBar.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
ToolBar.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
ToolBar.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
ToolBar.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
ToolBar.o: /usr/dt/include/Xm/VendorS.h ../Xfe/StringDefs.h ../Xfe/Defaults.h
ToolBar.o: ../Xfe/ChildrenUtil.h ../Xfe/Converters.h ../Xfe/DialogUtil.h
ToolBar.o: ../Xfe/Draw.h ../Xfe/Find.h /usr/include/assert.h
ToolBar.o: ../Xfe/Geometry.h ../Xfe/ListUtil.h ../Xfe/MenuUtil.h
ToolBar.o: ../Xfe/RepType.h ../Xfe/Resources.h ../Xfe/ShellUtil.h
ToolBar.o: ../Xfe/StringUtil.h ../Xfe/WmUtil.h ../Xfe/Manager.h
ToolBar.o: ../Xfe/Cascade.h ../Xfe/Button.h ../Xfe/Label.h ../Xfe/Primitive.h
ToolBar.o: ../Xfe/OrientedP.h ../Xfe/ManagerP.h ../Xfe/XfeP.h
ToolBar.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/X11/IntrinsicP.h
ToolBar.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
ToolBar.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
ToolBar.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
ToolBar.o: /usr/dt/include/Xm/DrawP.h ../Xfe/GeometryP.h ../Xfe/PrimitiveP.h
ToolBar.o: ../Xfe/PrepareP.h /usr/dt/include/Xm/PrimitiveP.h
ToolBar.o: /usr/dt/include/Xm/ManagerP.h /usr/dt/include/Xm/Separator.h
ToolBar.o: /usr/dt/include/Xm/SeparatoG.h
BmButton.o: ../Xfe/BmButtonP.h ../Xfe/PrimitiveP.h ../Xfe/XfeP.h
BmButton.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/Xm/Xm.h
BmButton.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
BmButton.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
BmButton.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
BmButton.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
BmButton.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
BmButton.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
BmButton.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
BmButton.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
BmButton.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
BmButton.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
BmButton.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
BmButton.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/X11/IntrinsicP.h
BmButton.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
BmButton.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
BmButton.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
BmButton.o: /usr/dt/include/Xm/DrawP.h ../Xfe/Xfe.h ../Xfe/StringDefs.h
BmButton.o: ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h ../Xfe/Converters.h
BmButton.o: ../Xfe/DialogUtil.h ../Xfe/Draw.h ../Xfe/Find.h
BmButton.o: /usr/include/assert.h ../Xfe/Geometry.h ../Xfe/ListUtil.h
BmButton.o: ../Xfe/MenuUtil.h ../Xfe/RepType.h ../Xfe/Resources.h
BmButton.o: ../Xfe/ShellUtil.h ../Xfe/StringUtil.h ../Xfe/WmUtil.h
BmButton.o: ../Xfe/GeometryP.h ../Xfe/Primitive.h ../Xfe/PrepareP.h
BmButton.o: /usr/dt/include/Xm/PrimitiveP.h ../Xfe/BmButton.h
BmButton.o: /usr/dt/include/Xm/PushBP.h /usr/dt/include/Xm/PushB.h
BmButton.o: /usr/dt/include/Xm/LabelP.h /usr/dt/include/Xm/Label.h
BmButton.o: ../Xfe/ManagerP.h ../Xfe/Manager.h /usr/dt/include/Xm/ManagerP.h
BmButton.o: ../Xfe/BmCascade.h ../Xfe/CascadeP.h ../Xfe/Cascade.h
BmButton.o: ../Xfe/Button.h ../Xfe/Label.h ../Xfe/ButtonP.h ../Xfe/LabelP.h
BmButton.o: /usr/dt/include/Xm/RowColumnP.h /usr/dt/include/Xm/RowColumn.h
Cursor.o: ../Xfe/XfeP.h /usr/dt/include/Xm/XmP.h /usr/dt/include/Xm/Xm.h
Cursor.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
Cursor.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
Cursor.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
Cursor.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
Cursor.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
Cursor.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
Cursor.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
Cursor.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
Cursor.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
Cursor.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
Cursor.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
Cursor.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/X11/IntrinsicP.h
Cursor.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
Cursor.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
Cursor.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
Cursor.o: /usr/dt/include/Xm/DrawP.h ../Xfe/Xfe.h ../Xfe/StringDefs.h
Cursor.o: ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h ../Xfe/Converters.h
Cursor.o: ../Xfe/DialogUtil.h ../Xfe/Draw.h ../Xfe/Find.h
Cursor.o: /usr/include/assert.h ../Xfe/Geometry.h ../Xfe/ListUtil.h
Cursor.o: ../Xfe/MenuUtil.h ../Xfe/RepType.h ../Xfe/Resources.h
Cursor.o: ../Xfe/ShellUtil.h ../Xfe/StringUtil.h ../Xfe/WmUtil.h
Cursor.o: ../Xfe/GeometryP.h
Geometry.o: /usr/include/stdarg.h /usr/include/sys/stdsyms.h
Geometry.o: /usr/include/varargs.h ../Xfe/PrimitiveP.h ../Xfe/XfeP.h
Geometry.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/Xm/Xm.h
Geometry.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
Geometry.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
Geometry.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
Geometry.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
Geometry.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
Geometry.o: /usr/include/string.h /usr/dt/include/X11/Core.h
Geometry.o: /usr/dt/include/X11/Composite.h /usr/dt/include/X11/Constraint.h
Geometry.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
Geometry.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
Geometry.o: /usr/dt/include/Xm/XmStrDefs.h /usr/dt/include/X11/StringDefs.h
Geometry.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
Geometry.o: /usr/dt/include/X11/IntrinsicP.h /usr/dt/include/X11/CoreP.h
Geometry.o: /usr/dt/include/X11/CompositeP.h /usr/dt/include/X11/ConstrainP.h
Geometry.o: /usr/dt/include/X11/ObjectP.h /usr/dt/include/X11/RectObjP.h
Geometry.o: /usr/dt/include/Xm/BaseClassP.h /usr/dt/include/Xm/DrawP.h
Geometry.o: ../Xfe/Xfe.h ../Xfe/StringDefs.h ../Xfe/Defaults.h
Geometry.o: ../Xfe/ChildrenUtil.h ../Xfe/Converters.h ../Xfe/DialogUtil.h
Geometry.o: ../Xfe/Draw.h ../Xfe/Find.h /usr/include/assert.h
Geometry.o: ../Xfe/Geometry.h ../Xfe/ListUtil.h ../Xfe/MenuUtil.h
Geometry.o: ../Xfe/RepType.h ../Xfe/Resources.h ../Xfe/ShellUtil.h
Geometry.o: ../Xfe/StringUtil.h ../Xfe/WmUtil.h ../Xfe/GeometryP.h
Geometry.o: ../Xfe/Primitive.h ../Xfe/PrepareP.h
Geometry.o: /usr/dt/include/Xm/PrimitiveP.h ../Xfe/ManagerP.h
Geometry.o: ../Xfe/Manager.h /usr/dt/include/Xm/ManagerP.h
Private.o: /usr/include/stdio.h /usr/include/sys/stdsyms.h
Private.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
Private.o: /usr/include/stdlib.h ../Xfe/XfeP.h /usr/dt/include/Xm/XmP.h
Private.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Intrinsic.h
Private.o: /usr/dt/include/X11/Xlib.h /usr/dt/include/X11/X.h
Private.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
Private.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
Private.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
Private.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
Private.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
Private.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
Private.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
Private.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
Private.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/X11/IntrinsicP.h
Private.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
Private.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
Private.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
Private.o: /usr/dt/include/Xm/DrawP.h ../Xfe/Xfe.h ../Xfe/StringDefs.h
Private.o: ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h ../Xfe/Converters.h
Private.o: ../Xfe/DialogUtil.h ../Xfe/Draw.h ../Xfe/Find.h
Private.o: /usr/include/assert.h ../Xfe/Geometry.h ../Xfe/ListUtil.h
Private.o: ../Xfe/MenuUtil.h ../Xfe/RepType.h ../Xfe/Resources.h
Private.o: ../Xfe/ShellUtil.h ../Xfe/StringUtil.h ../Xfe/WmUtil.h
Private.o: ../Xfe/GeometryP.h
ToolBox.o: /usr/include/stdio.h /usr/include/sys/stdsyms.h
ToolBox.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
ToolBox.o: ../Xfe/ToolBoxP.h ../Xfe/ToolBox.h ../Xfe/Manager.h ../Xfe/Xfe.h
ToolBox.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Intrinsic.h
ToolBox.o: /usr/dt/include/X11/Xlib.h /usr/dt/include/X11/X.h
ToolBox.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
ToolBox.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
ToolBox.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
ToolBox.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
ToolBox.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
ToolBox.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
ToolBox.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
ToolBox.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
ToolBox.o: /usr/dt/include/Xm/VendorS.h ../Xfe/StringDefs.h ../Xfe/Defaults.h
ToolBox.o: ../Xfe/ChildrenUtil.h ../Xfe/Converters.h ../Xfe/DialogUtil.h
ToolBox.o: ../Xfe/Draw.h ../Xfe/Find.h /usr/include/assert.h
ToolBox.o: ../Xfe/Geometry.h ../Xfe/ListUtil.h ../Xfe/MenuUtil.h
ToolBox.o: ../Xfe/RepType.h ../Xfe/Resources.h ../Xfe/ShellUtil.h
ToolBox.o: ../Xfe/StringUtil.h ../Xfe/WmUtil.h ../Xfe/ManagerP.h
ToolBox.o: ../Xfe/XfeP.h /usr/dt/include/Xm/XmP.h
ToolBox.o: /usr/dt/include/X11/IntrinsicP.h /usr/dt/include/X11/CoreP.h
ToolBox.o: /usr/dt/include/X11/CompositeP.h /usr/dt/include/X11/ConstrainP.h
ToolBox.o: /usr/dt/include/X11/ObjectP.h /usr/dt/include/X11/RectObjP.h
ToolBox.o: /usr/dt/include/Xm/BaseClassP.h /usr/dt/include/Xm/DrawP.h
ToolBox.o: ../Xfe/GeometryP.h ../Xfe/PrimitiveP.h ../Xfe/Primitive.h
ToolBox.o: ../Xfe/PrepareP.h /usr/dt/include/Xm/PrimitiveP.h
ToolBox.o: /usr/dt/include/Xm/ManagerP.h ../Xfe/Button.h ../Xfe/Label.h
ToolBox.o: ../Xfe/Tab.h /usr/dt/include/Xm/Form.h
ToolBox.o: /usr/dt/include/Xm/BulletinB.h
BmCascade.o: ../Xfe/BmCascadeP.h ../Xfe/PrimitiveP.h ../Xfe/XfeP.h
BmCascade.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/Xm/Xm.h
BmCascade.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
BmCascade.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
BmCascade.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
BmCascade.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
BmCascade.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
BmCascade.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
BmCascade.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
BmCascade.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
BmCascade.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
BmCascade.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
BmCascade.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
BmCascade.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/X11/IntrinsicP.h
BmCascade.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
BmCascade.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
BmCascade.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
BmCascade.o: /usr/dt/include/Xm/DrawP.h ../Xfe/Xfe.h ../Xfe/StringDefs.h
BmCascade.o: ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h ../Xfe/Converters.h
BmCascade.o: ../Xfe/DialogUtil.h ../Xfe/Draw.h ../Xfe/Find.h
BmCascade.o: /usr/include/assert.h ../Xfe/Geometry.h ../Xfe/ListUtil.h
BmCascade.o: ../Xfe/MenuUtil.h ../Xfe/RepType.h ../Xfe/Resources.h
BmCascade.o: ../Xfe/ShellUtil.h ../Xfe/StringUtil.h ../Xfe/WmUtil.h
BmCascade.o: ../Xfe/GeometryP.h ../Xfe/Primitive.h ../Xfe/PrepareP.h
BmCascade.o: /usr/dt/include/Xm/PrimitiveP.h ../Xfe/BmCascade.h
BmCascade.o: ../Xfe/BmButton.h /usr/dt/include/Xm/CascadeBP.h
BmCascade.o: /usr/dt/include/Xm/CascadeB.h /usr/dt/include/Xm/LabelP.h
BmCascade.o: /usr/dt/include/Xm/Label.h ../Xfe/BmButtonP.h
BmCascade.o: /usr/dt/include/Xm/PushBP.h /usr/dt/include/Xm/PushB.h
BmCascade.o: ../Xfe/Cascade.h ../Xfe/Button.h ../Xfe/Label.h
BmCascade.o: ../Xfe/ManagerP.h ../Xfe/Manager.h /usr/dt/include/Xm/ManagerP.h
BmCascade.o: /usr/dt/include/Xm/CascadeBGP.h /usr/dt/include/Xm/CascadeBG.h
BmCascade.o: /usr/dt/include/Xm/LabelGP.h /usr/dt/include/Xm/LabelG.h
BmCascade.o: /usr/dt/include/Xm/GadgetP.h /usr/dt/include/Xm/ExtObjectP.h
BmCascade.o: /usr/dt/include/Xm/MenuShellP.h /usr/dt/include/Xm/MenuShell.h
BmCascade.o: /usr/dt/include/X11/ShellP.h /usr/dt/include/X11/VendorP.h
BmCascade.o: /usr/dt/include/X11/Vendor.h /usr/dt/include/Xm/RowColumnP.h
BmCascade.o: /usr/dt/include/Xm/RowColumn.h
DashBoard.o: /usr/include/stdio.h /usr/include/sys/stdsyms.h
DashBoard.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
DashBoard.o: ../Xfe/DashBoardP.h ../Xfe/DashBoard.h ../Xfe/Xfe.h
DashBoard.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Intrinsic.h
DashBoard.o: /usr/dt/include/X11/Xlib.h /usr/dt/include/X11/X.h
DashBoard.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
DashBoard.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
DashBoard.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
DashBoard.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
DashBoard.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
DashBoard.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
DashBoard.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
DashBoard.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
DashBoard.o: /usr/dt/include/Xm/VendorS.h ../Xfe/StringDefs.h
DashBoard.o: ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h ../Xfe/Converters.h
DashBoard.o: ../Xfe/DialogUtil.h ../Xfe/Draw.h ../Xfe/Find.h
DashBoard.o: /usr/include/assert.h ../Xfe/Geometry.h ../Xfe/ListUtil.h
DashBoard.o: ../Xfe/MenuUtil.h ../Xfe/RepType.h ../Xfe/Resources.h
DashBoard.o: ../Xfe/ShellUtil.h ../Xfe/StringUtil.h ../Xfe/WmUtil.h
DashBoard.o: ../Xfe/Button.h ../Xfe/Label.h ../Xfe/Primitive.h
DashBoard.o: ../Xfe/ProgressBar.h ../Xfe/TaskBar.h ../Xfe/ToolBar.h
DashBoard.o: ../Xfe/Oriented.h ../Xfe/Manager.h ../Xfe/Cascade.h
DashBoard.o: ../Xfe/ManagerP.h ../Xfe/XfeP.h /usr/dt/include/Xm/XmP.h
DashBoard.o: /usr/dt/include/X11/IntrinsicP.h /usr/dt/include/X11/CoreP.h
DashBoard.o: /usr/dt/include/X11/CompositeP.h
DashBoard.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
DashBoard.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
DashBoard.o: /usr/dt/include/Xm/DrawP.h ../Xfe/GeometryP.h
DashBoard.o: ../Xfe/PrimitiveP.h ../Xfe/PrepareP.h
DashBoard.o: /usr/dt/include/Xm/PrimitiveP.h /usr/dt/include/Xm/ManagerP.h
DashBoard.o: ../Xfe/TaskBarP.h ../Xfe/ToolBarP.h ../Xfe/OrientedP.h
DashBoard.o: /usr/dt/include/Xm/DrawingA.h /usr/dt/include/Xm/Form.h
DashBoard.o: /usr/dt/include/Xm/BulletinB.h /usr/dt/include/Xm/Label.h
DashBoard.o: /usr/dt/include/Xm/LabelG.h /usr/dt/include/Xm/MwmUtil.h
DashBoard.o: /usr/dt/include/X11/Xmd.h /usr/dt/include/Xm/DialogS.h
Label.o: ../Xfe/LabelP.h ../Xfe/Label.h ../Xfe/Primitive.h ../Xfe/Xfe.h
Label.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Intrinsic.h
Label.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
Label.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
Label.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
Label.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
Label.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
Label.o: /usr/include/string.h /usr/dt/include/X11/Core.h
Label.o: /usr/dt/include/X11/Composite.h /usr/dt/include/X11/Constraint.h
Label.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
Label.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
Label.o: /usr/dt/include/Xm/XmStrDefs.h /usr/dt/include/X11/StringDefs.h
Label.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
Label.o: ../Xfe/StringDefs.h ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h
Label.o: ../Xfe/Converters.h ../Xfe/DialogUtil.h ../Xfe/Draw.h ../Xfe/Find.h
Label.o: /usr/include/assert.h ../Xfe/Geometry.h ../Xfe/ListUtil.h
Label.o: ../Xfe/MenuUtil.h ../Xfe/RepType.h ../Xfe/Resources.h
Label.o: ../Xfe/ShellUtil.h ../Xfe/StringUtil.h ../Xfe/WmUtil.h
Label.o: ../Xfe/PrimitiveP.h ../Xfe/XfeP.h /usr/dt/include/Xm/XmP.h
Label.o: /usr/dt/include/X11/IntrinsicP.h /usr/dt/include/X11/CoreP.h
Label.o: /usr/dt/include/X11/CompositeP.h /usr/dt/include/X11/ConstrainP.h
Label.o: /usr/dt/include/X11/ObjectP.h /usr/dt/include/X11/RectObjP.h
Label.o: /usr/dt/include/Xm/BaseClassP.h /usr/dt/include/Xm/DrawP.h
Label.o: ../Xfe/GeometryP.h ../Xfe/PrepareP.h /usr/dt/include/Xm/PrimitiveP.h
ProgressBar.o: ../Xfe/ProgressBarP.h ../Xfe/ProgressBar.h ../Xfe/Xfe.h
ProgressBar.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Intrinsic.h
ProgressBar.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
ProgressBar.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
ProgressBar.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
ProgressBar.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
ProgressBar.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
ProgressBar.o: /usr/include/string.h /usr/dt/include/X11/Core.h
ProgressBar.o: /usr/dt/include/X11/Composite.h
ProgressBar.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
ProgressBar.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
ProgressBar.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
ProgressBar.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
ProgressBar.o: /usr/dt/include/Xm/VendorS.h ../Xfe/StringDefs.h
ProgressBar.o: ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h ../Xfe/Converters.h
ProgressBar.o: ../Xfe/DialogUtil.h ../Xfe/Draw.h ../Xfe/Find.h
ProgressBar.o: /usr/include/assert.h ../Xfe/Geometry.h ../Xfe/ListUtil.h
ProgressBar.o: ../Xfe/MenuUtil.h ../Xfe/RepType.h ../Xfe/Resources.h
ProgressBar.o: ../Xfe/ShellUtil.h ../Xfe/StringUtil.h ../Xfe/WmUtil.h
ProgressBar.o: ../Xfe/LabelP.h ../Xfe/Label.h ../Xfe/Primitive.h
ProgressBar.o: ../Xfe/PrimitiveP.h ../Xfe/XfeP.h /usr/dt/include/Xm/XmP.h
ProgressBar.o: /usr/dt/include/X11/IntrinsicP.h /usr/dt/include/X11/CoreP.h
ProgressBar.o: /usr/dt/include/X11/CompositeP.h
ProgressBar.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
ProgressBar.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
ProgressBar.o: /usr/dt/include/Xm/DrawP.h ../Xfe/GeometryP.h
ProgressBar.o: ../Xfe/PrepareP.h /usr/dt/include/Xm/PrimitiveP.h
ToolItem.o: ../Xfe/ToolItemP.h ../Xfe/ToolItem.h ../Xfe/Xfe.h
ToolItem.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Intrinsic.h
ToolItem.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
ToolItem.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
ToolItem.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
ToolItem.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
ToolItem.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
ToolItem.o: /usr/include/string.h /usr/dt/include/X11/Core.h
ToolItem.o: /usr/dt/include/X11/Composite.h /usr/dt/include/X11/Constraint.h
ToolItem.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
ToolItem.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
ToolItem.o: /usr/dt/include/Xm/XmStrDefs.h /usr/dt/include/X11/StringDefs.h
ToolItem.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
ToolItem.o: ../Xfe/StringDefs.h ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h
ToolItem.o: ../Xfe/Converters.h ../Xfe/DialogUtil.h ../Xfe/Draw.h
ToolItem.o: ../Xfe/Find.h /usr/include/assert.h ../Xfe/Geometry.h
ToolItem.o: ../Xfe/ListUtil.h ../Xfe/MenuUtil.h ../Xfe/RepType.h
ToolItem.o: ../Xfe/Resources.h ../Xfe/ShellUtil.h ../Xfe/StringUtil.h
ToolItem.o: ../Xfe/WmUtil.h ../Xfe/Logo.h ../Xfe/ToolBar.h ../Xfe/Oriented.h
ToolItem.o: ../Xfe/Manager.h ../Xfe/Cascade.h ../Xfe/Button.h ../Xfe/Label.h
ToolItem.o: ../Xfe/Primitive.h ../Xfe/ManagerP.h ../Xfe/XfeP.h
ToolItem.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/X11/IntrinsicP.h
ToolItem.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
ToolItem.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
ToolItem.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
ToolItem.o: /usr/dt/include/Xm/DrawP.h ../Xfe/GeometryP.h ../Xfe/PrimitiveP.h
ToolItem.o: ../Xfe/PrepareP.h /usr/dt/include/Xm/PrimitiveP.h
ToolItem.o: /usr/dt/include/Xm/ManagerP.h /usr/dt/include/Xm/Label.h
ToolItem.o: /usr/dt/include/Xm/PushB.h
Button.o: ../Xfe/ButtonP.h ../Xfe/Button.h ../Xfe/Label.h ../Xfe/Primitive.h
Button.o: ../Xfe/Xfe.h /usr/dt/include/Xm/Xm.h
Button.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
Button.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
Button.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
Button.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
Button.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
Button.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
Button.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
Button.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
Button.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
Button.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
Button.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
Button.o: /usr/dt/include/Xm/VendorS.h ../Xfe/StringDefs.h ../Xfe/Defaults.h
Button.o: ../Xfe/ChildrenUtil.h ../Xfe/Converters.h ../Xfe/DialogUtil.h
Button.o: ../Xfe/Draw.h ../Xfe/Find.h /usr/include/assert.h ../Xfe/Geometry.h
Button.o: ../Xfe/ListUtil.h ../Xfe/MenuUtil.h ../Xfe/RepType.h
Button.o: ../Xfe/Resources.h ../Xfe/ShellUtil.h ../Xfe/StringUtil.h
Button.o: ../Xfe/WmUtil.h ../Xfe/LabelP.h ../Xfe/PrimitiveP.h ../Xfe/XfeP.h
Button.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/X11/IntrinsicP.h
Button.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
Button.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
Button.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
Button.o: /usr/dt/include/Xm/DrawP.h ../Xfe/GeometryP.h ../Xfe/PrepareP.h
Button.o: /usr/dt/include/Xm/PrimitiveP.h ../Xfe/ManagerP.h ../Xfe/Manager.h
Button.o: /usr/dt/include/Xm/ManagerP.h
ListUtil.o: ../Xfe/XfeP.h /usr/dt/include/Xm/XmP.h /usr/dt/include/Xm/Xm.h
ListUtil.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
ListUtil.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
ListUtil.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
ListUtil.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
ListUtil.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
ListUtil.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
ListUtil.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
ListUtil.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
ListUtil.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
ListUtil.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
ListUtil.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
ListUtil.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/X11/IntrinsicP.h
ListUtil.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
ListUtil.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
ListUtil.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
ListUtil.o: /usr/dt/include/Xm/DrawP.h ../Xfe/Xfe.h ../Xfe/StringDefs.h
ListUtil.o: ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h ../Xfe/Converters.h
ListUtil.o: ../Xfe/DialogUtil.h ../Xfe/Draw.h ../Xfe/Find.h
ListUtil.o: /usr/include/assert.h ../Xfe/Geometry.h ../Xfe/ListUtil.h
ListUtil.o: ../Xfe/MenuUtil.h ../Xfe/RepType.h ../Xfe/Resources.h
ListUtil.o: ../Xfe/ShellUtil.h ../Xfe/StringUtil.h ../Xfe/WmUtil.h
ListUtil.o: ../Xfe/GeometryP.h ../Xfe/PrimitiveP.h ../Xfe/Primitive.h
ListUtil.o: ../Xfe/PrepareP.h /usr/dt/include/Xm/PrimitiveP.h
ListUtil.o: ../Xfe/ManagerP.h ../Xfe/Manager.h /usr/dt/include/Xm/ManagerP.h
ListUtil.o: ../Xfe/ListUtilP.h /usr/dt/include/Xm/ListP.h
ListUtil.o: /usr/dt/include/Xm/List.h /usr/dt/include/Xm/ScrollBar.h
ListUtil.o: /usr/dt/include/Xm/ScrolledW.h /usr/dt/include/Xm/ScrolledWP.h
ListUtil.o: /usr/dt/include/Xm/DrawingA.h
RepType.o: /usr/dt/include/Xm/RepType.h /usr/dt/include/Xm/Xm.h
RepType.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
RepType.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
RepType.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
RepType.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
RepType.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
RepType.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
RepType.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
RepType.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
RepType.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
RepType.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
RepType.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
RepType.o: /usr/dt/include/Xm/VendorS.h ../Xfe/XfeP.h
RepType.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/X11/IntrinsicP.h
RepType.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
RepType.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
RepType.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
RepType.o: /usr/dt/include/Xm/DrawP.h ../Xfe/Xfe.h ../Xfe/StringDefs.h
RepType.o: ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h ../Xfe/Converters.h
RepType.o: ../Xfe/DialogUtil.h ../Xfe/Draw.h ../Xfe/Find.h
RepType.o: /usr/include/assert.h ../Xfe/Geometry.h ../Xfe/ListUtil.h
RepType.o: ../Xfe/MenuUtil.h ../Xfe/RepType.h ../Xfe/Resources.h
RepType.o: ../Xfe/ShellUtil.h ../Xfe/StringUtil.h ../Xfe/WmUtil.h
RepType.o: ../Xfe/GeometryP.h
ToolScroll.o: ../Xfe/ToolScrollP.h ../Xfe/ToolScroll.h ../Xfe/Oriented.h
ToolScroll.o: ../Xfe/Xfe.h /usr/dt/include/Xm/Xm.h
ToolScroll.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
ToolScroll.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
ToolScroll.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
ToolScroll.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
ToolScroll.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
ToolScroll.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
ToolScroll.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
ToolScroll.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
ToolScroll.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
ToolScroll.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
ToolScroll.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
ToolScroll.o: /usr/dt/include/Xm/VendorS.h ../Xfe/StringDefs.h
ToolScroll.o: ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h ../Xfe/Converters.h
ToolScroll.o: ../Xfe/DialogUtil.h ../Xfe/Draw.h ../Xfe/Find.h
ToolScroll.o: /usr/include/assert.h ../Xfe/Geometry.h ../Xfe/ListUtil.h
ToolScroll.o: ../Xfe/MenuUtil.h ../Xfe/RepType.h ../Xfe/Resources.h
ToolScroll.o: ../Xfe/ShellUtil.h ../Xfe/StringUtil.h ../Xfe/WmUtil.h
ToolScroll.o: ../Xfe/Manager.h ../Xfe/Logo.h ../Xfe/ToolBar.h
ToolScroll.o: ../Xfe/Cascade.h ../Xfe/Button.h ../Xfe/Label.h
ToolScroll.o: ../Xfe/Primitive.h ../Xfe/OrientedP.h ../Xfe/ManagerP.h
ToolScroll.o: ../Xfe/XfeP.h /usr/dt/include/Xm/XmP.h
ToolScroll.o: /usr/dt/include/X11/IntrinsicP.h /usr/dt/include/X11/CoreP.h
ToolScroll.o: /usr/dt/include/X11/CompositeP.h
ToolScroll.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
ToolScroll.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
ToolScroll.o: /usr/dt/include/Xm/DrawP.h ../Xfe/GeometryP.h
ToolScroll.o: ../Xfe/PrimitiveP.h ../Xfe/PrepareP.h
ToolScroll.o: /usr/dt/include/Xm/PrimitiveP.h /usr/dt/include/Xm/ManagerP.h
ToolScroll.o: ../Xfe/ToolBarP.h /usr/dt/include/Xm/DrawingA.h ../Xfe/Arrow.h
BypassShell.o: /usr/include/stdio.h /usr/include/sys/stdsyms.h
BypassShell.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
BypassShell.o: ../Xfe/BypassShellP.h ../Xfe/BypassShell.h ../Xfe/Xfe.h
BypassShell.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Intrinsic.h
BypassShell.o: /usr/dt/include/X11/Xlib.h /usr/dt/include/X11/X.h
BypassShell.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
BypassShell.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
BypassShell.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
BypassShell.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
BypassShell.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
BypassShell.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
BypassShell.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
BypassShell.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
BypassShell.o: /usr/dt/include/Xm/VendorS.h ../Xfe/StringDefs.h
BypassShell.o: ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h ../Xfe/Converters.h
BypassShell.o: ../Xfe/DialogUtil.h ../Xfe/Draw.h ../Xfe/Find.h
BypassShell.o: /usr/include/assert.h ../Xfe/Geometry.h ../Xfe/ListUtil.h
BypassShell.o: ../Xfe/MenuUtil.h ../Xfe/RepType.h ../Xfe/Resources.h
BypassShell.o: ../Xfe/ShellUtil.h ../Xfe/StringUtil.h ../Xfe/WmUtil.h
BypassShell.o: ../Xfe/Manager.h ../Xfe/ManagerP.h ../Xfe/XfeP.h
BypassShell.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/X11/IntrinsicP.h
BypassShell.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
BypassShell.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
BypassShell.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
BypassShell.o: /usr/dt/include/Xm/DrawP.h ../Xfe/GeometryP.h
BypassShell.o: ../Xfe/PrimitiveP.h ../Xfe/Primitive.h ../Xfe/PrepareP.h
BypassShell.o: /usr/dt/include/Xm/PrimitiveP.h /usr/dt/include/Xm/ManagerP.h
BypassShell.o: /usr/dt/include/X11/ShellP.h /usr/dt/include/X11/VendorP.h
BypassShell.o: /usr/dt/include/X11/Vendor.h /usr/dt/include/Xm/VendorSEP.h
BypassShell.o: /usr/dt/include/Xm/ShellEP.h /usr/dt/include/Xm/DesktopP.h
BypassShell.o: /usr/dt/include/Xm/ExtObjectP.h /usr/dt/include/Xm/MwmUtil.h
BypassShell.o: /usr/dt/include/X11/Xmd.h /usr/dt/include/Xm/AtomMgr.h
BypassShell.o: /usr/dt/include/Xm/Protocols.h
DialogUtil.o: ../Xfe/XfeP.h /usr/dt/include/Xm/XmP.h /usr/dt/include/Xm/Xm.h
DialogUtil.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
DialogUtil.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
DialogUtil.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
DialogUtil.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
DialogUtil.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
DialogUtil.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
DialogUtil.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
DialogUtil.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
DialogUtil.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
DialogUtil.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
DialogUtil.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
DialogUtil.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/X11/IntrinsicP.h
DialogUtil.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
DialogUtil.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
DialogUtil.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
DialogUtil.o: /usr/dt/include/Xm/DrawP.h ../Xfe/Xfe.h ../Xfe/StringDefs.h
DialogUtil.o: ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h ../Xfe/Converters.h
DialogUtil.o: ../Xfe/DialogUtil.h ../Xfe/Draw.h ../Xfe/Find.h
DialogUtil.o: /usr/include/assert.h ../Xfe/Geometry.h ../Xfe/ListUtil.h
DialogUtil.o: ../Xfe/MenuUtil.h ../Xfe/RepType.h ../Xfe/Resources.h
DialogUtil.o: ../Xfe/ShellUtil.h ../Xfe/StringUtil.h ../Xfe/WmUtil.h
DialogUtil.o: ../Xfe/GeometryP.h ../Xfe/ManagerP.h ../Xfe/PrimitiveP.h
DialogUtil.o: ../Xfe/Primitive.h ../Xfe/PrepareP.h
DialogUtil.o: /usr/dt/include/Xm/PrimitiveP.h ../Xfe/Manager.h
DialogUtil.o: /usr/dt/include/Xm/ManagerP.h
Logo.o: ../Xfe/LogoP.h ../Xfe/Logo.h ../Xfe/Xfe.h /usr/dt/include/Xm/Xm.h
Logo.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
Logo.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
Logo.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
Logo.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
Logo.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
Logo.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
Logo.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
Logo.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
Logo.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
Logo.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
Logo.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
Logo.o: /usr/dt/include/Xm/VendorS.h ../Xfe/StringDefs.h ../Xfe/Defaults.h
Logo.o: ../Xfe/ChildrenUtil.h ../Xfe/Converters.h ../Xfe/DialogUtil.h
Logo.o: ../Xfe/Draw.h ../Xfe/Find.h /usr/include/assert.h ../Xfe/Geometry.h
Logo.o: ../Xfe/ListUtil.h ../Xfe/MenuUtil.h ../Xfe/RepType.h
Logo.o: ../Xfe/Resources.h ../Xfe/ShellUtil.h ../Xfe/StringUtil.h
Logo.o: ../Xfe/WmUtil.h ../Xfe/ButtonP.h ../Xfe/Button.h ../Xfe/Label.h
Logo.o: ../Xfe/Primitive.h ../Xfe/LabelP.h ../Xfe/PrimitiveP.h ../Xfe/XfeP.h
Logo.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/X11/IntrinsicP.h
Logo.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
Logo.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
Logo.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
Logo.o: /usr/dt/include/Xm/DrawP.h ../Xfe/GeometryP.h ../Xfe/PrepareP.h
Logo.o: /usr/dt/include/Xm/PrimitiveP.h
Resources.o: ../Xfe/XfeP.h /usr/dt/include/Xm/XmP.h /usr/dt/include/Xm/Xm.h
Resources.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
Resources.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
Resources.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
Resources.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
Resources.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
Resources.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
Resources.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
Resources.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
Resources.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
Resources.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
Resources.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
Resources.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/X11/IntrinsicP.h
Resources.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
Resources.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
Resources.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
Resources.o: /usr/dt/include/Xm/DrawP.h ../Xfe/Xfe.h ../Xfe/StringDefs.h
Resources.o: ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h ../Xfe/Converters.h
Resources.o: ../Xfe/DialogUtil.h ../Xfe/Draw.h ../Xfe/Find.h
Resources.o: /usr/include/assert.h ../Xfe/Geometry.h ../Xfe/ListUtil.h
Resources.o: ../Xfe/MenuUtil.h ../Xfe/RepType.h ../Xfe/Resources.h
Resources.o: ../Xfe/ShellUtil.h ../Xfe/StringUtil.h ../Xfe/WmUtil.h
Resources.o: ../Xfe/GeometryP.h
Translations.o: ../Xfe/XfeP.h /usr/dt/include/Xm/XmP.h
Translations.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Intrinsic.h
Translations.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
Translations.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
Translations.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
Translations.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
Translations.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
Translations.o: /usr/include/string.h /usr/dt/include/X11/Core.h
Translations.o: /usr/dt/include/X11/Composite.h
Translations.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
Translations.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
Translations.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
Translations.o: /usr/dt/include/X11/StringDefs.h
Translations.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
Translations.o: /usr/dt/include/X11/IntrinsicP.h /usr/dt/include/X11/CoreP.h
Translations.o: /usr/dt/include/X11/CompositeP.h
Translations.o: /usr/dt/include/X11/ConstrainP.h
Translations.o: /usr/dt/include/X11/ObjectP.h /usr/dt/include/X11/RectObjP.h
Translations.o: /usr/dt/include/Xm/BaseClassP.h /usr/dt/include/Xm/DrawP.h
Translations.o: ../Xfe/Xfe.h ../Xfe/StringDefs.h ../Xfe/Defaults.h
Translations.o: ../Xfe/ChildrenUtil.h ../Xfe/Converters.h ../Xfe/DialogUtil.h
Translations.o: ../Xfe/Draw.h ../Xfe/Find.h /usr/include/assert.h
Translations.o: ../Xfe/Geometry.h ../Xfe/ListUtil.h ../Xfe/MenuUtil.h
Translations.o: ../Xfe/RepType.h ../Xfe/Resources.h ../Xfe/ShellUtil.h
Translations.o: ../Xfe/StringUtil.h ../Xfe/WmUtil.h ../Xfe/GeometryP.h
CallProcs.o: ../Xfe/XfeP.h /usr/dt/include/Xm/XmP.h /usr/dt/include/Xm/Xm.h
CallProcs.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
CallProcs.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
CallProcs.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
CallProcs.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
CallProcs.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
CallProcs.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
CallProcs.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
CallProcs.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
CallProcs.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
CallProcs.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
CallProcs.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
CallProcs.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/X11/IntrinsicP.h
CallProcs.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
CallProcs.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
CallProcs.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
CallProcs.o: /usr/dt/include/Xm/DrawP.h ../Xfe/Xfe.h ../Xfe/StringDefs.h
CallProcs.o: ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h ../Xfe/Converters.h
CallProcs.o: ../Xfe/DialogUtil.h ../Xfe/Draw.h ../Xfe/Find.h
CallProcs.o: /usr/include/assert.h ../Xfe/Geometry.h ../Xfe/ListUtil.h
CallProcs.o: ../Xfe/MenuUtil.h ../Xfe/RepType.h ../Xfe/Resources.h
CallProcs.o: ../Xfe/ShellUtil.h ../Xfe/StringUtil.h ../Xfe/WmUtil.h
CallProcs.o: ../Xfe/GeometryP.h ../Xfe/PrimitiveP.h ../Xfe/Primitive.h
CallProcs.o: ../Xfe/PrepareP.h /usr/dt/include/Xm/PrimitiveP.h
CallProcs.o: ../Xfe/ManagerP.h ../Xfe/Manager.h /usr/dt/include/Xm/ManagerP.h
Draw.o: ../Xfe/XfeP.h /usr/dt/include/Xm/XmP.h /usr/dt/include/Xm/Xm.h
Draw.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
Draw.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
Draw.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
Draw.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
Draw.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
Draw.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
Draw.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
Draw.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
Draw.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
Draw.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
Draw.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
Draw.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/X11/IntrinsicP.h
Draw.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
Draw.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
Draw.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
Draw.o: /usr/dt/include/Xm/DrawP.h ../Xfe/Xfe.h ../Xfe/StringDefs.h
Draw.o: ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h ../Xfe/Converters.h
Draw.o: ../Xfe/DialogUtil.h ../Xfe/Draw.h ../Xfe/Find.h /usr/include/assert.h
Draw.o: ../Xfe/Geometry.h ../Xfe/ListUtil.h ../Xfe/MenuUtil.h
Draw.o: ../Xfe/RepType.h ../Xfe/Resources.h ../Xfe/ShellUtil.h
Draw.o: ../Xfe/StringUtil.h ../Xfe/WmUtil.h ../Xfe/GeometryP.h
Draw.o: ../Xfe/ManagerP.h ../Xfe/PrimitiveP.h ../Xfe/Primitive.h
Draw.o: ../Xfe/PrepareP.h /usr/dt/include/Xm/PrimitiveP.h ../Xfe/Manager.h
Draw.o: /usr/dt/include/Xm/ManagerP.h
Manager.o: /usr/include/stdio.h /usr/include/sys/stdsyms.h
Manager.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
Manager.o: /usr/include/assert.h ../Xfe/ManagerP.h ../Xfe/XfeP.h
Manager.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/Xm/Xm.h
Manager.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
Manager.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
Manager.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
Manager.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
Manager.o: /usr/include/string.h /usr/dt/include/X11/Core.h
Manager.o: /usr/dt/include/X11/Composite.h /usr/dt/include/X11/Constraint.h
Manager.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
Manager.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
Manager.o: /usr/dt/include/Xm/XmStrDefs.h /usr/dt/include/X11/StringDefs.h
Manager.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
Manager.o: /usr/dt/include/X11/IntrinsicP.h /usr/dt/include/X11/CoreP.h
Manager.o: /usr/dt/include/X11/CompositeP.h /usr/dt/include/X11/ConstrainP.h
Manager.o: /usr/dt/include/X11/ObjectP.h /usr/dt/include/X11/RectObjP.h
Manager.o: /usr/dt/include/Xm/BaseClassP.h /usr/dt/include/Xm/DrawP.h
Manager.o: ../Xfe/Xfe.h ../Xfe/StringDefs.h ../Xfe/Defaults.h
Manager.o: ../Xfe/ChildrenUtil.h ../Xfe/Converters.h ../Xfe/DialogUtil.h
Manager.o: ../Xfe/Draw.h ../Xfe/Find.h ../Xfe/Geometry.h ../Xfe/ListUtil.h
Manager.o: ../Xfe/MenuUtil.h ../Xfe/RepType.h ../Xfe/Resources.h
Manager.o: ../Xfe/ShellUtil.h ../Xfe/StringUtil.h ../Xfe/WmUtil.h
Manager.o: ../Xfe/GeometryP.h ../Xfe/PrimitiveP.h ../Xfe/Primitive.h
Manager.o: ../Xfe/PrepareP.h /usr/dt/include/Xm/PrimitiveP.h ../Xfe/Manager.h
Manager.o: /usr/dt/include/Xm/ManagerP.h
ShellUtil.o: ../Xfe/XfeP.h /usr/dt/include/Xm/XmP.h /usr/dt/include/Xm/Xm.h
ShellUtil.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
ShellUtil.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
ShellUtil.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
ShellUtil.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
ShellUtil.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
ShellUtil.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
ShellUtil.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
ShellUtil.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
ShellUtil.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
ShellUtil.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
ShellUtil.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
ShellUtil.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/X11/IntrinsicP.h
ShellUtil.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
ShellUtil.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
ShellUtil.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
ShellUtil.o: /usr/dt/include/Xm/DrawP.h ../Xfe/Xfe.h ../Xfe/StringDefs.h
ShellUtil.o: ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h ../Xfe/Converters.h
ShellUtil.o: ../Xfe/DialogUtil.h ../Xfe/Draw.h ../Xfe/Find.h
ShellUtil.o: /usr/include/assert.h ../Xfe/Geometry.h ../Xfe/ListUtil.h
ShellUtil.o: ../Xfe/MenuUtil.h ../Xfe/RepType.h ../Xfe/Resources.h
ShellUtil.o: ../Xfe/ShellUtil.h ../Xfe/StringUtil.h ../Xfe/WmUtil.h
ShellUtil.o: ../Xfe/GeometryP.h ../Xfe/Cascade.h ../Xfe/Button.h
ShellUtil.o: ../Xfe/Label.h ../Xfe/Primitive.h /usr/dt/include/Xm/AtomMgr.h
ShellUtil.o: /usr/dt/include/Xm/Protocols.h /usr/dt/include/X11/ShellP.h
ShellUtil.o: /usr/dt/include/X11/VendorP.h /usr/dt/include/X11/Vendor.h
Util.o: /usr/include/stdio.h /usr/include/sys/stdsyms.h
Util.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
Util.o: /usr/include/stdlib.h ../Xfe/XfeP.h /usr/dt/include/Xm/XmP.h
Util.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Intrinsic.h
Util.o: /usr/dt/include/X11/Xlib.h /usr/dt/include/X11/X.h
Util.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
Util.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
Util.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
Util.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
Util.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
Util.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
Util.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
Util.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
Util.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/X11/IntrinsicP.h
Util.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
Util.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
Util.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
Util.o: /usr/dt/include/Xm/DrawP.h ../Xfe/Xfe.h ../Xfe/StringDefs.h
Util.o: ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h ../Xfe/Converters.h
Util.o: ../Xfe/DialogUtil.h ../Xfe/Draw.h ../Xfe/Find.h /usr/include/assert.h
Util.o: ../Xfe/Geometry.h ../Xfe/ListUtil.h ../Xfe/MenuUtil.h
Util.o: ../Xfe/RepType.h ../Xfe/Resources.h ../Xfe/ShellUtil.h
Util.o: ../Xfe/StringUtil.h ../Xfe/WmUtil.h ../Xfe/GeometryP.h
Util.o: ../Xfe/PrimitiveP.h ../Xfe/Primitive.h ../Xfe/PrepareP.h
Util.o: /usr/dt/include/Xm/PrimitiveP.h ../Xfe/ManagerP.h ../Xfe/Manager.h
Util.o: /usr/dt/include/Xm/ManagerP.h /usr/dt/include/Xm/LabelP.h
Util.o: /usr/dt/include/Xm/Label.h /usr/dt/include/Xm/LabelGP.h
Util.o: /usr/dt/include/Xm/LabelG.h /usr/dt/include/Xm/GadgetP.h
Util.o: /usr/dt/include/Xm/ExtObjectP.h ../Xfe/LabelP.h ../Xfe/Label.h
Cascade.o: ../Xfe/CascadeP.h ../Xfe/Cascade.h ../Xfe/Button.h ../Xfe/Label.h
Cascade.o: ../Xfe/Primitive.h ../Xfe/Xfe.h /usr/dt/include/Xm/Xm.h
Cascade.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
Cascade.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
Cascade.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
Cascade.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
Cascade.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
Cascade.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
Cascade.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
Cascade.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
Cascade.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
Cascade.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
Cascade.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
Cascade.o: /usr/dt/include/Xm/VendorS.h ../Xfe/StringDefs.h ../Xfe/Defaults.h
Cascade.o: ../Xfe/ChildrenUtil.h ../Xfe/Converters.h ../Xfe/DialogUtil.h
Cascade.o: ../Xfe/Draw.h ../Xfe/Find.h /usr/include/assert.h
Cascade.o: ../Xfe/Geometry.h ../Xfe/ListUtil.h ../Xfe/MenuUtil.h
Cascade.o: ../Xfe/RepType.h ../Xfe/Resources.h ../Xfe/ShellUtil.h
Cascade.o: ../Xfe/StringUtil.h ../Xfe/WmUtil.h ../Xfe/ButtonP.h
Cascade.o: ../Xfe/LabelP.h ../Xfe/PrimitiveP.h ../Xfe/XfeP.h
Cascade.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/X11/IntrinsicP.h
Cascade.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
Cascade.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
Cascade.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
Cascade.o: /usr/dt/include/Xm/DrawP.h ../Xfe/GeometryP.h ../Xfe/PrepareP.h
Cascade.o: /usr/dt/include/Xm/PrimitiveP.h ../Xfe/ManagerP.h ../Xfe/Manager.h
Cascade.o: /usr/dt/include/Xm/ManagerP.h /usr/dt/include/Xm/RowColumnP.h
Cascade.o: /usr/dt/include/Xm/RowColumn.h
FancyBox.o: /usr/include/stdio.h /usr/include/sys/stdsyms.h
FancyBox.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
FancyBox.o: ../Xfe/FancyBoxP.h ../Xfe/FancyBox.h ../Xfe/ComboBox.h
FancyBox.o: ../Xfe/Manager.h ../Xfe/Xfe.h /usr/dt/include/Xm/Xm.h
FancyBox.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
FancyBox.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
FancyBox.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
FancyBox.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
FancyBox.o: /usr/include/string.h /usr/dt/include/X11/Core.h
FancyBox.o: /usr/dt/include/X11/Composite.h /usr/dt/include/X11/Constraint.h
FancyBox.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
FancyBox.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
FancyBox.o: /usr/dt/include/Xm/XmStrDefs.h /usr/dt/include/X11/StringDefs.h
FancyBox.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
FancyBox.o: ../Xfe/StringDefs.h ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h
FancyBox.o: ../Xfe/Converters.h ../Xfe/DialogUtil.h ../Xfe/Draw.h
FancyBox.o: ../Xfe/Find.h /usr/include/assert.h ../Xfe/Geometry.h
FancyBox.o: ../Xfe/ListUtil.h ../Xfe/MenuUtil.h ../Xfe/RepType.h
FancyBox.o: ../Xfe/Resources.h ../Xfe/ShellUtil.h ../Xfe/StringUtil.h
FancyBox.o: ../Xfe/WmUtil.h ../Xfe/ComboBoxP.h ../Xfe/ManagerP.h
FancyBox.o: ../Xfe/XfeP.h /usr/dt/include/Xm/XmP.h
FancyBox.o: /usr/dt/include/X11/IntrinsicP.h /usr/dt/include/X11/CoreP.h
FancyBox.o: /usr/dt/include/X11/CompositeP.h /usr/dt/include/X11/ConstrainP.h
FancyBox.o: /usr/dt/include/X11/ObjectP.h /usr/dt/include/X11/RectObjP.h
FancyBox.o: /usr/dt/include/Xm/BaseClassP.h /usr/dt/include/Xm/DrawP.h
FancyBox.o: ../Xfe/GeometryP.h ../Xfe/PrimitiveP.h ../Xfe/Primitive.h
FancyBox.o: ../Xfe/PrepareP.h /usr/dt/include/Xm/PrimitiveP.h
FancyBox.o: /usr/dt/include/Xm/ManagerP.h ../Xfe/BypassShellP.h
FancyBox.o: ../Xfe/BypassShell.h /usr/dt/include/X11/ShellP.h
FancyBox.o: /usr/dt/include/X11/VendorP.h /usr/dt/include/X11/Vendor.h
FancyBox.o: /usr/dt/include/Xm/VendorSEP.h /usr/dt/include/Xm/ShellEP.h
FancyBox.o: /usr/dt/include/Xm/DesktopP.h /usr/dt/include/Xm/ExtObjectP.h
FancyBox.o: /usr/dt/include/Xm/MwmUtil.h /usr/dt/include/X11/Xmd.h
FancyBox.o: ../Xfe/ListUtilP.h /usr/dt/include/Xm/ListP.h
FancyBox.o: /usr/dt/include/Xm/List.h /usr/dt/include/Xm/ScrollBar.h
FancyBox.o: /usr/dt/include/Xm/ScrolledW.h /usr/dt/include/Xm/TextF.h
FancyBox.o: ../Xfe/Button.h ../Xfe/Label.h ../Xfe/Arrow.h
MenuUtil.o: ../Xfe/XfeP.h /usr/dt/include/Xm/XmP.h /usr/dt/include/Xm/Xm.h
MenuUtil.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
MenuUtil.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
MenuUtil.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
MenuUtil.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
MenuUtil.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
MenuUtil.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
MenuUtil.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
MenuUtil.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
MenuUtil.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
MenuUtil.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
MenuUtil.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
MenuUtil.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/X11/IntrinsicP.h
MenuUtil.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
MenuUtil.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
MenuUtil.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
MenuUtil.o: /usr/dt/include/Xm/DrawP.h ../Xfe/Xfe.h ../Xfe/StringDefs.h
MenuUtil.o: ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h ../Xfe/Converters.h
MenuUtil.o: ../Xfe/DialogUtil.h ../Xfe/Draw.h ../Xfe/Find.h
MenuUtil.o: /usr/include/assert.h ../Xfe/Geometry.h ../Xfe/ListUtil.h
MenuUtil.o: ../Xfe/MenuUtil.h ../Xfe/RepType.h ../Xfe/Resources.h
MenuUtil.o: ../Xfe/ShellUtil.h ../Xfe/StringUtil.h ../Xfe/WmUtil.h
MenuUtil.o: ../Xfe/GeometryP.h ../Xfe/ManagerP.h ../Xfe/PrimitiveP.h
MenuUtil.o: ../Xfe/Primitive.h ../Xfe/PrepareP.h
MenuUtil.o: /usr/dt/include/Xm/PrimitiveP.h ../Xfe/Manager.h
MenuUtil.o: /usr/dt/include/Xm/ManagerP.h ../Xfe/CascadeP.h ../Xfe/Cascade.h
MenuUtil.o: ../Xfe/Button.h ../Xfe/Label.h ../Xfe/ButtonP.h ../Xfe/LabelP.h
MenuUtil.o: ../Xfe/BmCascadeP.h ../Xfe/BmCascade.h ../Xfe/BmButton.h
MenuUtil.o: /usr/dt/include/Xm/CascadeBP.h /usr/dt/include/Xm/CascadeB.h
MenuUtil.o: /usr/dt/include/Xm/LabelP.h /usr/dt/include/Xm/Label.h
MenuUtil.o: ../Xfe/BmButtonP.h /usr/dt/include/Xm/PushBP.h
MenuUtil.o: /usr/dt/include/Xm/PushB.h /usr/dt/include/Xm/RowColumnP.h
MenuUtil.o: /usr/dt/include/Xm/RowColumn.h /usr/dt/include/Xm/DisplayP.h
MenuUtil.o: /usr/dt/include/Xm/DesktopP.h /usr/dt/include/Xm/ExtObjectP.h
MenuUtil.o: /usr/dt/include/Xm/VendorSEP.h /usr/dt/include/Xm/ShellEP.h
MenuUtil.o: /usr/dt/include/Xm/MwmUtil.h /usr/dt/include/X11/Xmd.h
MenuUtil.o: /usr/dt/include/Xm/DropSMgr.h /usr/dt/include/Xm/DragC.h
MenuUtil.o: /usr/dt/include/Xm/Display.h /usr/dt/include/Xm/ScreenP.h
MenuUtil.o: /usr/dt/include/Xm/Screen.h /usr/dt/include/Xm/DragIcon.h
MenuUtil.o: /usr/dt/include/Xm/DragCP.h /usr/dt/include/X11/ShellP.h
MenuUtil.o: /usr/dt/include/X11/VendorP.h /usr/dt/include/X11/Vendor.h
MenuUtil.o: /usr/dt/include/Xm/DragOverS.h /usr/dt/include/Xm/DropSMgrP.h
MenuUtil.o: /usr/dt/include/Xm/VirtKeysP.h /usr/dt/include/Xm/CascadeBGP.h
MenuUtil.o: /usr/dt/include/Xm/CascadeBG.h /usr/dt/include/Xm/LabelGP.h
MenuUtil.o: /usr/dt/include/Xm/LabelG.h /usr/dt/include/Xm/GadgetP.h
StringUtil.o: ../Xfe/XfeP.h /usr/dt/include/Xm/XmP.h /usr/dt/include/Xm/Xm.h
StringUtil.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
StringUtil.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
StringUtil.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
StringUtil.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
StringUtil.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
StringUtil.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
StringUtil.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
StringUtil.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
StringUtil.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
StringUtil.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
StringUtil.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
StringUtil.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/X11/IntrinsicP.h
StringUtil.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
StringUtil.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
StringUtil.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
StringUtil.o: /usr/dt/include/Xm/DrawP.h ../Xfe/Xfe.h ../Xfe/StringDefs.h
StringUtil.o: ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h ../Xfe/Converters.h
StringUtil.o: ../Xfe/DialogUtil.h ../Xfe/Draw.h ../Xfe/Find.h
StringUtil.o: /usr/include/assert.h ../Xfe/Geometry.h ../Xfe/ListUtil.h
StringUtil.o: ../Xfe/MenuUtil.h ../Xfe/RepType.h ../Xfe/Resources.h
StringUtil.o: ../Xfe/ShellUtil.h ../Xfe/StringUtil.h ../Xfe/WmUtil.h
StringUtil.o: ../Xfe/GeometryP.h
WmUtil.o: ../Xfe/XfeP.h /usr/dt/include/Xm/XmP.h /usr/dt/include/Xm/Xm.h
WmUtil.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
WmUtil.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
WmUtil.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
WmUtil.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
WmUtil.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
WmUtil.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
WmUtil.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
WmUtil.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
WmUtil.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
WmUtil.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
WmUtil.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
WmUtil.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/X11/IntrinsicP.h
WmUtil.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
WmUtil.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
WmUtil.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
WmUtil.o: /usr/dt/include/Xm/DrawP.h ../Xfe/Xfe.h ../Xfe/StringDefs.h
WmUtil.o: ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h ../Xfe/Converters.h
WmUtil.o: ../Xfe/DialogUtil.h ../Xfe/Draw.h ../Xfe/Find.h
WmUtil.o: /usr/include/assert.h ../Xfe/Geometry.h ../Xfe/ListUtil.h
WmUtil.o: ../Xfe/MenuUtil.h ../Xfe/RepType.h ../Xfe/Resources.h
WmUtil.o: ../Xfe/ShellUtil.h ../Xfe/StringUtil.h ../Xfe/WmUtil.h
WmUtil.o: ../Xfe/GeometryP.h
ChildrenUtil.o: ../Xfe/XfeP.h /usr/dt/include/Xm/XmP.h
ChildrenUtil.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Intrinsic.h
ChildrenUtil.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
ChildrenUtil.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
ChildrenUtil.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
ChildrenUtil.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
ChildrenUtil.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
ChildrenUtil.o: /usr/include/string.h /usr/dt/include/X11/Core.h
ChildrenUtil.o: /usr/dt/include/X11/Composite.h
ChildrenUtil.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
ChildrenUtil.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
ChildrenUtil.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
ChildrenUtil.o: /usr/dt/include/X11/StringDefs.h
ChildrenUtil.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
ChildrenUtil.o: /usr/dt/include/X11/IntrinsicP.h /usr/dt/include/X11/CoreP.h
ChildrenUtil.o: /usr/dt/include/X11/CompositeP.h
ChildrenUtil.o: /usr/dt/include/X11/ConstrainP.h
ChildrenUtil.o: /usr/dt/include/X11/ObjectP.h /usr/dt/include/X11/RectObjP.h
ChildrenUtil.o: /usr/dt/include/Xm/BaseClassP.h /usr/dt/include/Xm/DrawP.h
ChildrenUtil.o: ../Xfe/Xfe.h ../Xfe/StringDefs.h ../Xfe/Defaults.h
ChildrenUtil.o: ../Xfe/ChildrenUtil.h ../Xfe/Converters.h ../Xfe/DialogUtil.h
ChildrenUtil.o: ../Xfe/Draw.h ../Xfe/Find.h /usr/include/assert.h
ChildrenUtil.o: ../Xfe/Geometry.h ../Xfe/ListUtil.h ../Xfe/MenuUtil.h
ChildrenUtil.o: ../Xfe/RepType.h ../Xfe/Resources.h ../Xfe/ShellUtil.h
ChildrenUtil.o: ../Xfe/StringUtil.h ../Xfe/WmUtil.h ../Xfe/GeometryP.h
ChildrenUtil.o: ../Xfe/PrimitiveP.h ../Xfe/Primitive.h ../Xfe/PrepareP.h
ChildrenUtil.o: /usr/dt/include/Xm/PrimitiveP.h ../Xfe/ManagerP.h
ChildrenUtil.o: ../Xfe/Manager.h /usr/dt/include/Xm/ManagerP.h
Find.o: /usr/include/stdio.h /usr/include/sys/stdsyms.h
Find.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
Find.o: /usr/include/stdlib.h ../Xfe/XfeP.h /usr/dt/include/Xm/XmP.h
Find.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Intrinsic.h
Find.o: /usr/dt/include/X11/Xlib.h /usr/dt/include/X11/X.h
Find.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
Find.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
Find.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
Find.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
Find.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
Find.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
Find.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
Find.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
Find.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/X11/IntrinsicP.h
Find.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
Find.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
Find.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
Find.o: /usr/dt/include/Xm/DrawP.h ../Xfe/Xfe.h ../Xfe/StringDefs.h
Find.o: ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h ../Xfe/Converters.h
Find.o: ../Xfe/DialogUtil.h ../Xfe/Draw.h ../Xfe/Find.h /usr/include/assert.h
Find.o: ../Xfe/Geometry.h ../Xfe/ListUtil.h ../Xfe/MenuUtil.h
Find.o: ../Xfe/RepType.h ../Xfe/Resources.h ../Xfe/ShellUtil.h
Find.o: ../Xfe/StringUtil.h ../Xfe/WmUtil.h ../Xfe/GeometryP.h
Find.o: ../Xfe/PrimitiveP.h ../Xfe/Primitive.h ../Xfe/PrepareP.h
Find.o: /usr/dt/include/Xm/PrimitiveP.h ../Xfe/ManagerP.h ../Xfe/Manager.h
Find.o: /usr/dt/include/Xm/ManagerP.h
Oriented.o: ../Xfe/OrientedP.h ../Xfe/Oriented.h ../Xfe/Xfe.h
Oriented.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Intrinsic.h
Oriented.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
Oriented.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
Oriented.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
Oriented.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
Oriented.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
Oriented.o: /usr/include/string.h /usr/dt/include/X11/Core.h
Oriented.o: /usr/dt/include/X11/Composite.h /usr/dt/include/X11/Constraint.h
Oriented.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
Oriented.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
Oriented.o: /usr/dt/include/Xm/XmStrDefs.h /usr/dt/include/X11/StringDefs.h
Oriented.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
Oriented.o: ../Xfe/StringDefs.h ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h
Oriented.o: ../Xfe/Converters.h ../Xfe/DialogUtil.h ../Xfe/Draw.h
Oriented.o: ../Xfe/Find.h /usr/include/assert.h ../Xfe/Geometry.h
Oriented.o: ../Xfe/ListUtil.h ../Xfe/MenuUtil.h ../Xfe/RepType.h
Oriented.o: ../Xfe/Resources.h ../Xfe/ShellUtil.h ../Xfe/StringUtil.h
Oriented.o: ../Xfe/WmUtil.h ../Xfe/Manager.h ../Xfe/ManagerP.h ../Xfe/XfeP.h
Oriented.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/X11/IntrinsicP.h
Oriented.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
Oriented.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
Oriented.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
Oriented.o: /usr/dt/include/Xm/DrawP.h ../Xfe/GeometryP.h ../Xfe/PrimitiveP.h
Oriented.o: ../Xfe/Primitive.h ../Xfe/PrepareP.h
Oriented.o: /usr/dt/include/Xm/PrimitiveP.h /usr/dt/include/Xm/ManagerP.h
Tab.o: ../Xfe/TabP.h ../Xfe/Tab.h ../Xfe/Xfe.h /usr/dt/include/Xm/Xm.h
Tab.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
Tab.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
Tab.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
Tab.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
Tab.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
Tab.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
Tab.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
Tab.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
Tab.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
Tab.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
Tab.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
Tab.o: /usr/dt/include/Xm/VendorS.h ../Xfe/StringDefs.h ../Xfe/Defaults.h
Tab.o: ../Xfe/ChildrenUtil.h ../Xfe/Converters.h ../Xfe/DialogUtil.h
Tab.o: ../Xfe/Draw.h ../Xfe/Find.h /usr/include/assert.h ../Xfe/Geometry.h
Tab.o: ../Xfe/ListUtil.h ../Xfe/MenuUtil.h ../Xfe/RepType.h
Tab.o: ../Xfe/Resources.h ../Xfe/ShellUtil.h ../Xfe/StringUtil.h
Tab.o: ../Xfe/WmUtil.h ../Xfe/ButtonP.h ../Xfe/Button.h ../Xfe/Label.h
Tab.o: ../Xfe/Primitive.h ../Xfe/LabelP.h ../Xfe/PrimitiveP.h ../Xfe/XfeP.h
Tab.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/X11/IntrinsicP.h
Tab.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
Tab.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
Tab.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
Tab.o: /usr/dt/include/Xm/DrawP.h ../Xfe/GeometryP.h ../Xfe/PrepareP.h
Tab.o: /usr/dt/include/Xm/PrimitiveP.h ../Xfe/ManagerP.h ../Xfe/Manager.h
Tab.o: /usr/dt/include/Xm/ManagerP.h /usr/dt/include/Xm/RowColumnP.h
Tab.o: /usr/dt/include/Xm/RowColumn.h
Chrome.o: ../Xfe/ChromeP.h ../Xfe/Chrome.h ../Xfe/ToolBox.h ../Xfe/Manager.h
Chrome.o: ../Xfe/Xfe.h /usr/dt/include/Xm/Xm.h
Chrome.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
Chrome.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
Chrome.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
Chrome.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
Chrome.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
Chrome.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
Chrome.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
Chrome.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
Chrome.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
Chrome.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
Chrome.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
Chrome.o: /usr/dt/include/Xm/VendorS.h ../Xfe/StringDefs.h ../Xfe/Defaults.h
Chrome.o: ../Xfe/ChildrenUtil.h ../Xfe/Converters.h ../Xfe/DialogUtil.h
Chrome.o: ../Xfe/Draw.h ../Xfe/Find.h /usr/include/assert.h ../Xfe/Geometry.h
Chrome.o: ../Xfe/ListUtil.h ../Xfe/MenuUtil.h ../Xfe/RepType.h
Chrome.o: ../Xfe/Resources.h ../Xfe/ShellUtil.h ../Xfe/StringUtil.h
Chrome.o: ../Xfe/WmUtil.h ../Xfe/DashBoard.h ../Xfe/Button.h ../Xfe/Label.h
Chrome.o: ../Xfe/Primitive.h ../Xfe/ProgressBar.h ../Xfe/TaskBar.h
Chrome.o: ../Xfe/ToolBar.h ../Xfe/Oriented.h ../Xfe/Cascade.h
Chrome.o: /usr/dt/include/Xm/RowColumn.h ../Xfe/ManagerP.h ../Xfe/XfeP.h
Chrome.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/X11/IntrinsicP.h
Chrome.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
Chrome.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
Chrome.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
Chrome.o: /usr/dt/include/Xm/DrawP.h ../Xfe/GeometryP.h ../Xfe/PrimitiveP.h
Chrome.o: ../Xfe/PrepareP.h /usr/dt/include/Xm/PrimitiveP.h
Chrome.o: /usr/dt/include/Xm/ManagerP.h /usr/dt/include/Xm/Separator.h
Chrome.o: /usr/dt/include/Xm/DrawingA.h /usr/dt/include/Xm/MainW.h
Chrome.o: /usr/dt/include/Xm/Form.h /usr/dt/include/Xm/BulletinB.h
Chrome.o: /usr/dt/include/Xm/Frame.h
FontChooser.o: ../Xfe/FontChooserP.h ../Xfe/FontChooser.h ../Xfe/Cascade.h
FontChooser.o: ../Xfe/Button.h ../Xfe/Label.h ../Xfe/Primitive.h ../Xfe/Xfe.h
FontChooser.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Intrinsic.h
FontChooser.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
FontChooser.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
FontChooser.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
FontChooser.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
FontChooser.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
FontChooser.o: /usr/include/string.h /usr/dt/include/X11/Core.h
FontChooser.o: /usr/dt/include/X11/Composite.h
FontChooser.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
FontChooser.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
FontChooser.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
FontChooser.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
FontChooser.o: /usr/dt/include/Xm/VendorS.h ../Xfe/StringDefs.h
FontChooser.o: ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h ../Xfe/Converters.h
FontChooser.o: ../Xfe/DialogUtil.h ../Xfe/Draw.h ../Xfe/Find.h
FontChooser.o: /usr/include/assert.h ../Xfe/Geometry.h ../Xfe/ListUtil.h
FontChooser.o: ../Xfe/MenuUtil.h ../Xfe/RepType.h ../Xfe/Resources.h
FontChooser.o: ../Xfe/ShellUtil.h ../Xfe/StringUtil.h ../Xfe/WmUtil.h
FontChooser.o: ../Xfe/CascadeP.h ../Xfe/ButtonP.h ../Xfe/LabelP.h
FontChooser.o: ../Xfe/PrimitiveP.h ../Xfe/XfeP.h /usr/dt/include/Xm/XmP.h
FontChooser.o: /usr/dt/include/X11/IntrinsicP.h /usr/dt/include/X11/CoreP.h
FontChooser.o: /usr/dt/include/X11/CompositeP.h
FontChooser.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
FontChooser.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
FontChooser.o: /usr/dt/include/Xm/DrawP.h ../Xfe/GeometryP.h
FontChooser.o: ../Xfe/PrepareP.h /usr/dt/include/Xm/PrimitiveP.h
FontChooser.o: ../Xfe/ManagerP.h ../Xfe/Manager.h
FontChooser.o: /usr/dt/include/Xm/ManagerP.h /usr/dt/include/Xm/ToggleB.h
Pane.o: ../Xfe/PaneP.h ../Xfe/Pane.h ../Xfe/Xfe.h /usr/dt/include/Xm/Xm.h
Pane.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
Pane.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
Pane.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
Pane.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
Pane.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
Pane.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
Pane.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
Pane.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
Pane.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
Pane.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
Pane.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
Pane.o: /usr/dt/include/Xm/VendorS.h ../Xfe/StringDefs.h ../Xfe/Defaults.h
Pane.o: ../Xfe/ChildrenUtil.h ../Xfe/Converters.h ../Xfe/DialogUtil.h
Pane.o: ../Xfe/Draw.h ../Xfe/Find.h /usr/include/assert.h ../Xfe/Geometry.h
Pane.o: ../Xfe/ListUtil.h ../Xfe/MenuUtil.h ../Xfe/RepType.h
Pane.o: ../Xfe/Resources.h ../Xfe/ShellUtil.h ../Xfe/StringUtil.h
Pane.o: ../Xfe/WmUtil.h ../Xfe/Oriented.h ../Xfe/Manager.h ../Xfe/OrientedP.h
Pane.o: ../Xfe/ManagerP.h ../Xfe/XfeP.h /usr/dt/include/Xm/XmP.h
Pane.o: /usr/dt/include/X11/IntrinsicP.h /usr/dt/include/X11/CoreP.h
Pane.o: /usr/dt/include/X11/CompositeP.h /usr/dt/include/X11/ConstrainP.h
Pane.o: /usr/dt/include/X11/ObjectP.h /usr/dt/include/X11/RectObjP.h
Pane.o: /usr/dt/include/Xm/BaseClassP.h /usr/dt/include/Xm/DrawP.h
Pane.o: ../Xfe/GeometryP.h ../Xfe/PrimitiveP.h ../Xfe/Primitive.h
Pane.o: ../Xfe/PrepareP.h /usr/dt/include/Xm/PrimitiveP.h
Pane.o: /usr/dt/include/Xm/ManagerP.h /usr/include/stdio.h
TaskBar.o: /usr/include/stdio.h /usr/include/sys/stdsyms.h
TaskBar.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
TaskBar.o: ../Xfe/TaskBarP.h ../Xfe/ToolBarP.h ../Xfe/ToolBar.h
TaskBar.o: ../Xfe/Oriented.h ../Xfe/Xfe.h /usr/dt/include/Xm/Xm.h
TaskBar.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
TaskBar.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
TaskBar.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
TaskBar.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
TaskBar.o: /usr/include/string.h /usr/dt/include/X11/Core.h
TaskBar.o: /usr/dt/include/X11/Composite.h /usr/dt/include/X11/Constraint.h
TaskBar.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
TaskBar.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
TaskBar.o: /usr/dt/include/Xm/XmStrDefs.h /usr/dt/include/X11/StringDefs.h
TaskBar.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
TaskBar.o: ../Xfe/StringDefs.h ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h
TaskBar.o: ../Xfe/Converters.h ../Xfe/DialogUtil.h ../Xfe/Draw.h
TaskBar.o: ../Xfe/Find.h /usr/include/assert.h ../Xfe/Geometry.h
TaskBar.o: ../Xfe/ListUtil.h ../Xfe/MenuUtil.h ../Xfe/RepType.h
TaskBar.o: ../Xfe/Resources.h ../Xfe/ShellUtil.h ../Xfe/StringUtil.h
TaskBar.o: ../Xfe/WmUtil.h ../Xfe/Manager.h ../Xfe/Cascade.h ../Xfe/Button.h
TaskBar.o: ../Xfe/Label.h ../Xfe/Primitive.h ../Xfe/OrientedP.h
TaskBar.o: ../Xfe/ManagerP.h ../Xfe/XfeP.h /usr/dt/include/Xm/XmP.h
TaskBar.o: /usr/dt/include/X11/IntrinsicP.h /usr/dt/include/X11/CoreP.h
TaskBar.o: /usr/dt/include/X11/CompositeP.h /usr/dt/include/X11/ConstrainP.h
TaskBar.o: /usr/dt/include/X11/ObjectP.h /usr/dt/include/X11/RectObjP.h
TaskBar.o: /usr/dt/include/Xm/BaseClassP.h /usr/dt/include/Xm/DrawP.h
TaskBar.o: ../Xfe/GeometryP.h ../Xfe/PrimitiveP.h ../Xfe/PrepareP.h
TaskBar.o: /usr/dt/include/Xm/PrimitiveP.h /usr/dt/include/Xm/ManagerP.h
TaskBar.o: ../Xfe/TaskBar.h ../Xfe/Tab.h /usr/dt/include/Xm/AtomMgr.h
TaskBar.o: /usr/dt/include/Xm/Protocols.h
ComboBox.o: /usr/include/stdio.h /usr/include/sys/stdsyms.h
ComboBox.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
ComboBox.o: ../Xfe/ComboBoxP.h ../Xfe/ComboBox.h ../Xfe/Manager.h
ComboBox.o: ../Xfe/Xfe.h /usr/dt/include/Xm/Xm.h
ComboBox.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
ComboBox.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
ComboBox.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
ComboBox.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
ComboBox.o: /usr/include/string.h /usr/dt/include/X11/Core.h
ComboBox.o: /usr/dt/include/X11/Composite.h /usr/dt/include/X11/Constraint.h
ComboBox.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
ComboBox.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
ComboBox.o: /usr/dt/include/Xm/XmStrDefs.h /usr/dt/include/X11/StringDefs.h
ComboBox.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
ComboBox.o: ../Xfe/StringDefs.h ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h
ComboBox.o: ../Xfe/Converters.h ../Xfe/DialogUtil.h ../Xfe/Draw.h
ComboBox.o: ../Xfe/Find.h /usr/include/assert.h ../Xfe/Geometry.h
ComboBox.o: ../Xfe/ListUtil.h ../Xfe/MenuUtil.h ../Xfe/RepType.h
ComboBox.o: ../Xfe/Resources.h ../Xfe/ShellUtil.h ../Xfe/StringUtil.h
ComboBox.o: ../Xfe/WmUtil.h ../Xfe/ManagerP.h ../Xfe/XfeP.h
ComboBox.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/X11/IntrinsicP.h
ComboBox.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
ComboBox.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
ComboBox.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
ComboBox.o: /usr/dt/include/Xm/DrawP.h ../Xfe/GeometryP.h ../Xfe/PrimitiveP.h
ComboBox.o: ../Xfe/Primitive.h ../Xfe/PrepareP.h
ComboBox.o: /usr/dt/include/Xm/PrimitiveP.h /usr/dt/include/Xm/ManagerP.h
ComboBox.o: ../Xfe/ListUtilP.h /usr/dt/include/Xm/ListP.h
ComboBox.o: /usr/dt/include/Xm/List.h /usr/dt/include/Xm/ScrollBar.h
ComboBox.o: /usr/dt/include/Xm/ScrolledW.h ../Xfe/FrameShell.h
ComboBox.o: ../Xfe/BypassShell.h /usr/dt/include/Xm/TextF.h ../Xfe/Button.h
ComboBox.o: ../Xfe/Label.h ../Xfe/Arrow.h
FrameShell.o: /usr/include/stdio.h /usr/include/sys/stdsyms.h
FrameShell.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
FrameShell.o: ../Xfe/FrameShellP.h ../Xfe/FrameShell.h ../Xfe/Manager.h
FrameShell.o: ../Xfe/Xfe.h /usr/dt/include/Xm/Xm.h
FrameShell.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
FrameShell.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
FrameShell.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
FrameShell.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
FrameShell.o: /usr/include/string.h /usr/dt/include/X11/Core.h
FrameShell.o: /usr/dt/include/X11/Composite.h
FrameShell.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
FrameShell.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
FrameShell.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
FrameShell.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
FrameShell.o: /usr/dt/include/Xm/VendorS.h ../Xfe/StringDefs.h
FrameShell.o: ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h ../Xfe/Converters.h
FrameShell.o: ../Xfe/DialogUtil.h ../Xfe/Draw.h ../Xfe/Find.h
FrameShell.o: /usr/include/assert.h ../Xfe/Geometry.h ../Xfe/ListUtil.h
FrameShell.o: ../Xfe/MenuUtil.h ../Xfe/RepType.h ../Xfe/Resources.h
FrameShell.o: ../Xfe/ShellUtil.h ../Xfe/StringUtil.h ../Xfe/WmUtil.h
FrameShell.o: ../Xfe/BypassShell.h ../Xfe/ManagerP.h ../Xfe/XfeP.h
FrameShell.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/X11/IntrinsicP.h
FrameShell.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
FrameShell.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
FrameShell.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
FrameShell.o: /usr/dt/include/Xm/DrawP.h ../Xfe/GeometryP.h
FrameShell.o: ../Xfe/PrimitiveP.h ../Xfe/Primitive.h ../Xfe/PrepareP.h
FrameShell.o: /usr/dt/include/Xm/PrimitiveP.h /usr/dt/include/Xm/ManagerP.h
FrameShell.o: /usr/dt/include/X11/ShellP.h /usr/dt/include/X11/VendorP.h
FrameShell.o: /usr/dt/include/X11/Vendor.h /usr/dt/include/Xm/VendorSEP.h
FrameShell.o: /usr/dt/include/Xm/ShellEP.h /usr/dt/include/Xm/DesktopP.h
FrameShell.o: /usr/dt/include/Xm/ExtObjectP.h /usr/dt/include/Xm/MwmUtil.h
FrameShell.o: /usr/dt/include/X11/Xmd.h /usr/dt/include/Xm/AtomMgr.h
FrameShell.o: /usr/dt/include/Xm/Protocols.h
PixmapUtil.o: ../Xfe/XfeP.h /usr/dt/include/Xm/XmP.h /usr/dt/include/Xm/Xm.h
PixmapUtil.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
PixmapUtil.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
PixmapUtil.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
PixmapUtil.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
PixmapUtil.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
PixmapUtil.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
PixmapUtil.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
PixmapUtil.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
PixmapUtil.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
PixmapUtil.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
PixmapUtil.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
PixmapUtil.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/X11/IntrinsicP.h
PixmapUtil.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
PixmapUtil.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
PixmapUtil.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
PixmapUtil.o: /usr/dt/include/Xm/DrawP.h ../Xfe/Xfe.h ../Xfe/StringDefs.h
PixmapUtil.o: ../Xfe/Defaults.h ../Xfe/ChildrenUtil.h ../Xfe/Converters.h
PixmapUtil.o: ../Xfe/DialogUtil.h ../Xfe/Draw.h ../Xfe/Find.h
PixmapUtil.o: /usr/include/assert.h ../Xfe/Geometry.h ../Xfe/ListUtil.h
PixmapUtil.o: ../Xfe/MenuUtil.h ../Xfe/RepType.h ../Xfe/Resources.h
PixmapUtil.o: ../Xfe/ShellUtil.h ../Xfe/StringUtil.h ../Xfe/WmUtil.h
PixmapUtil.o: ../Xfe/GeometryP.h
TempTwo.o: /usr/include/stdio.h /usr/include/sys/stdsyms.h
TempTwo.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
TempTwo.o: ../Xfe/TempTwoP.h ../Xfe/TempTwo.h ../Xfe/Manager.h ../Xfe/Xfe.h
TempTwo.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Intrinsic.h
TempTwo.o: /usr/dt/include/X11/Xlib.h /usr/dt/include/X11/X.h
TempTwo.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
TempTwo.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
TempTwo.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
TempTwo.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
TempTwo.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
TempTwo.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
TempTwo.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
TempTwo.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
TempTwo.o: /usr/dt/include/Xm/VendorS.h ../Xfe/StringDefs.h ../Xfe/Defaults.h
TempTwo.o: ../Xfe/ChildrenUtil.h ../Xfe/Converters.h ../Xfe/DialogUtil.h
TempTwo.o: ../Xfe/Draw.h ../Xfe/Find.h /usr/include/assert.h
TempTwo.o: ../Xfe/Geometry.h ../Xfe/ListUtil.h ../Xfe/MenuUtil.h
TempTwo.o: ../Xfe/RepType.h ../Xfe/Resources.h ../Xfe/ShellUtil.h
TempTwo.o: ../Xfe/StringUtil.h ../Xfe/WmUtil.h ../Xfe/ManagerP.h
TempTwo.o: ../Xfe/XfeP.h /usr/dt/include/Xm/XmP.h
TempTwo.o: /usr/dt/include/X11/IntrinsicP.h /usr/dt/include/X11/CoreP.h
TempTwo.o: /usr/dt/include/X11/CompositeP.h /usr/dt/include/X11/ConstrainP.h
TempTwo.o: /usr/dt/include/X11/ObjectP.h /usr/dt/include/X11/RectObjP.h
TempTwo.o: /usr/dt/include/Xm/BaseClassP.h /usr/dt/include/Xm/DrawP.h
TempTwo.o: ../Xfe/GeometryP.h ../Xfe/PrimitiveP.h ../Xfe/Primitive.h
TempTwo.o: ../Xfe/PrepareP.h /usr/dt/include/Xm/PrimitiveP.h
TempTwo.o: /usr/dt/include/Xm/ManagerP.h ../Xfe/Label.h ../Xfe/Button.h
TempTwo.o: ../Xfe/Cascade.h /usr/dt/include/Xm/Separator.h
TempTwo.o: /usr/dt/include/Xm/SeparatoG.h
