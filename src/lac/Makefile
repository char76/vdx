# Makefile for lazy application concept library
#
# $Log: Makefile,v $
# Revision 1.1.1.1.2.1  1998/07/01 18:31:40  lazy
# Patches gcc 2.8
#
# Revision 1.1.1.1  1998/04/24 23:45:46  lazy
# Imported to CVS
#
# Revision 1.3  1998/03/30 19:09:32  lazy
# *** empty log message ***
#
# Revision 1.2  1997/07/25  19:47:44  lazy
# Header.
#
#
all: library

TOPDIR = ../..
LIBRARY = liblac.a

MLXHelp_res.h:	MLXHelp.rf
	cat MLXHelp.rf | $(TOPDIR)/bin/ad2fbh.script >MLXHelp_res.h

include $(TOPDIR)/Makerules

HEADERS = MsgCat.h Lobject.h View.h Model.h Rec.h WidgetRef.h \
	LicView.h TreeNode.h Ref.h RefArray.h TArray.h ConModel.h Ref.C \
	RefArray.C TreeNode.C TreeView.h ConModel.C MLXHelp.h MLXHelp_base.h \
	HelpNode.h SensitiveView.h IconView.h Controller.h OptionMenuView.h \
	HelpNodeController.h Lstring.h CallbackMethod.h

OBJS = 	MsgCat.o Lobject.o View.o Model.o Rec.o WidgetRef.o \
	LicView.o TreeView.o Tinst.o MLXHelp.o MLXHelp_base.o \
	HelpNode.o SensitiveView.o Lstring.o OptionMenuView.o \
	IconView.o Controller.o HelpNodeController.o CallbackMethod.o

SRCS = 	MsgCat.C \
	Lobject.C \
	View.C \
	Model.C \
	Rec.C \
	WidgetRef.C \
	LicView.C \
	TreeView.C \
	Tinst.C \
	MLXHelp.C \
	MLXHelp_base.C \
	HelpNode.C \
	SensitiveView.C \
	IconView.C \
	Controller.C \
	HelpNodeController.C \
	Lstring.C \
	OptionMenuView.C \
	CallbackMethod.C

EXTRA_CFLAGS = -I..

depend: depend-src

install:	$(ARCH)/liblac.a $(HEADERS)
	cp -f $(ARCH)/liblac.a $(TOPDIR)/lib; \
	cp -f $(HEADERS) $(TOPDIR)/include/lac


clean: clean-src

check: $(ARCH)/check
	@echo done

$(ARCH)/check:  check.C $(ARCH)/$(LIBRARY)
	$(CXXLINK) $(CFLAGS) -o $(ARCH)/check check.C $(ARCH)/$(LIBRARY) $(LIBS)


# DO NOT DELETE

MsgCat.o: ../lac/MsgCat.h ../lac/Lobject.h /usr/include/stdio.h
MsgCat.o: /usr/include/sys/stdsyms.h /usr/include/sys/types.h
MsgCat.o: /usr/include/sys/_inttypes.h /usr/dt/include/X11/Intrinsic.h
MsgCat.o: /usr/dt/include/X11/Xlib.h /usr/dt/include/X11/X.h
MsgCat.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
MsgCat.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
MsgCat.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
MsgCat.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
MsgCat.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
MsgCat.o: /usr/dt/include/X11/RectObj.h /usr/include/stdlib.h
MsgCat.o: /usr/include/ctype.h /usr/include/stdarg.h /usr/include/varargs.h
Lobject.o: /usr/include/stdio.h /usr/include/sys/stdsyms.h
Lobject.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
Lobject.o: ../lac/Lobject.h
View.o: ../lac/View.h /usr/dt/include/X11/Intrinsic.h
View.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
View.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
View.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
View.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
View.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
View.o: /usr/include/string.h /usr/dt/include/X11/Core.h
View.o: /usr/dt/include/X11/Composite.h /usr/dt/include/X11/Constraint.h
View.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
View.o: ../lac/Lobject.h /usr/include/stdio.h ../lac/RefArray.h ../lac/Ref.h
View.o: ../lac/Rec.h ../lac/WidgetRef.h ../lac/TArray.h /usr/include/stdlib.h
View.o: /usr/include/limits.h ../../include/X11/xpm.h ../lac/Model.h
View.o: ../lac/CallbackMethod.h ../lac/ConModel.h /usr/include/math.h
View.o: /usr/dt/include/Xm/BulletinB.h /usr/dt/include/Xm/Xm.h
View.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
View.o: /usr/dt/include/Xm/XmStrDefs.h /usr/dt/include/X11/StringDefs.h
View.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
View.o: /usr/dt/include/Xm/MessageB.h /usr/dt/include/Xm/DialogS.h
View.o: /usr/dt/include/Xm/FileSB.h /usr/dt/include/Xm/DragIcon.h
View.o: loaderror.xpm
Model.o: ../lac/View.h /usr/dt/include/X11/Intrinsic.h
Model.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
Model.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
Model.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
Model.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
Model.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
Model.o: /usr/include/string.h /usr/dt/include/X11/Core.h
Model.o: /usr/dt/include/X11/Composite.h /usr/dt/include/X11/Constraint.h
Model.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
Model.o: ../lac/Lobject.h /usr/include/stdio.h ../lac/RefArray.h ../lac/Ref.h
Model.o: ../lac/Rec.h ../lac/WidgetRef.h ../lac/TArray.h
Model.o: /usr/include/stdlib.h /usr/include/limits.h ../../include/X11/xpm.h
Model.o: ../lac/Model.h ../lac/CallbackMethod.h /usr/include/ctype.h
Rec.o: ../lac/Rec.h /usr/dt/include/X11/Intrinsic.h
Rec.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
Rec.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
Rec.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
Rec.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
Rec.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
Rec.o: /usr/include/string.h /usr/dt/include/X11/Core.h
Rec.o: /usr/dt/include/X11/Composite.h /usr/dt/include/X11/Constraint.h
Rec.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
WidgetRef.o: ../lac/WidgetRef.h /usr/dt/include/X11/Intrinsic.h
WidgetRef.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
WidgetRef.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
WidgetRef.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
WidgetRef.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
WidgetRef.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
WidgetRef.o: /usr/include/string.h /usr/dt/include/X11/Core.h
WidgetRef.o: /usr/dt/include/X11/Composite.h /usr/dt/include/X11/Constraint.h
WidgetRef.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
LicView.o: /usr/dt/include/Xm/BulletinB.h /usr/dt/include/Xm/Xm.h
LicView.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
LicView.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
LicView.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
LicView.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
LicView.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
LicView.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
LicView.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
LicView.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
LicView.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
LicView.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
LicView.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
LicView.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/Xm/MessageB.h
LicView.o: /usr/dt/include/Xm/DialogS.h /usr/dt/include/Xm/FileSB.h
LicView.o: ../lac/LicView.h ../lac/View.h ../lac/Lobject.h
LicView.o: /usr/include/stdio.h ../lac/RefArray.h ../lac/Ref.h ../lac/Rec.h
LicView.o: ../lac/WidgetRef.h ../lac/TArray.h /usr/include/stdlib.h
LicView.o: /usr/include/limits.h ../../include/X11/xpm.h ../lac/Model.h
LicView.o: ../lac/CallbackMethod.h /usr/dt/include/Xm/Protocols.h
LicView.o: /usr/dt/include/Xm/AtomMgr.h /usr/dt/include/X11/cursorfont.h
LicView.o: /usr/dt/include/X11/IntrinsicP.h /usr/dt/include/X11/CoreP.h
LicView.o: /usr/dt/include/X11/CompositeP.h /usr/dt/include/X11/ConstrainP.h
LicView.o: /usr/dt/include/X11/ObjectP.h /usr/dt/include/X11/RectObjP.h
LicView.o: MLXHelp.h ../lac/HelpNode.h ../lac/TreeNode.h ../lac/ConModel.h
LicView.o: ../lac/MLXHelp_base.h ../lac/TreeView.h ../lac/SensitiveView.h
LicView.o: ../lac/Controller.h ../lac/Lstring.h /usr/dt/include/Xm/DragDrop.h
LicView.o: /usr/dt/include/Xm/DragC.h /usr/dt/include/Xm/Display.h
LicView.o: /usr/dt/include/Xm/DropSMgr.h /usr/dt/include/Xm/DragIcon.h
LicView.o: /usr/dt/include/Xm/DropTrans.h /usr/dt/include/Xm/DragOverS.h
LicView.o: /usr/dt/include/Xm/Screen.h /usr/dt/include/Xm/TextOutP.h
LicView.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/Xm/BaseClassP.h
LicView.o: /usr/dt/include/Xm/Text.h /usr/dt/include/Dt/Dt.h
TreeView.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Intrinsic.h
TreeView.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
TreeView.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
TreeView.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
TreeView.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
TreeView.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
TreeView.o: /usr/include/string.h /usr/dt/include/X11/Core.h
TreeView.o: /usr/dt/include/X11/Composite.h /usr/dt/include/X11/Constraint.h
TreeView.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
TreeView.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
TreeView.o: /usr/dt/include/Xm/XmStrDefs.h /usr/dt/include/X11/StringDefs.h
TreeView.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
TreeView.o: ../lac/TreeView.h ../lac/TreeNode.h ../lac/ConModel.h
TreeView.o: ../lac/Model.h ../lac/Lobject.h /usr/include/stdio.h
TreeView.o: ../lac/RefArray.h ../lac/Ref.h ../lac/TArray.h
TreeView.o: /usr/include/stdlib.h ../lac/CallbackMethod.h ../lac/View.h
TreeView.o: ../lac/Rec.h ../lac/WidgetRef.h /usr/include/limits.h
TreeView.o: ../../include/X11/xpm.h ../lac/SensitiveView.h
TreeView.o: ../lac/Controller.h ../lac/Lstring.h /usr/dt/include/Xm/AtomMgr.h
TreeView.o: /usr/dt/include/Xm/DragDrop.h /usr/dt/include/Xm/DragC.h
TreeView.o: /usr/dt/include/Xm/Display.h /usr/dt/include/Xm/DropSMgr.h
TreeView.o: /usr/dt/include/Xm/DragIcon.h /usr/dt/include/Xm/DropTrans.h
TreeView.o: /usr/dt/include/Xm/DragOverS.h /usr/dt/include/Xm/Screen.h
TreeView.o: /usr/dt/include/Xm/DragCP.h /usr/dt/include/Xm/XmP.h
TreeView.o: /usr/dt/include/X11/IntrinsicP.h /usr/dt/include/X11/CoreP.h
TreeView.o: /usr/dt/include/X11/CompositeP.h /usr/dt/include/X11/ConstrainP.h
TreeView.o: /usr/dt/include/X11/ObjectP.h /usr/dt/include/X11/RectObjP.h
TreeView.o: /usr/dt/include/Xm/BaseClassP.h /usr/dt/include/X11/ShellP.h
TreeView.o: /usr/dt/include/X11/VendorP.h /usr/dt/include/X11/Vendor.h
TreeView.o: /usr/dt/include/Xm/DropSMgrP.h forbidden.xbm forbiddenMask.xbm
TreeView.o: insertBefore.xbm insertBeforeMask.xbm asChild.xbm asChildMask.xbm
TreeView.o: expand.xpm collapse.xpm
Tinst.o: Ref.C ../lac/Ref.h ../lac/Lobject.h /usr/include/stdio.h
Tinst.o: /usr/include/sys/stdsyms.h /usr/include/sys/types.h
Tinst.o: /usr/include/sys/_inttypes.h RefArray.C ../lac/RefArray.h ConModel.C
Tinst.o: ../lac/ConModel.h ../lac/Model.h /usr/dt/include/X11/Intrinsic.h
Tinst.o: /usr/dt/include/X11/Xlib.h /usr/dt/include/X11/X.h
Tinst.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
Tinst.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
Tinst.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
Tinst.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
Tinst.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
Tinst.o: /usr/dt/include/X11/RectObj.h ../lac/TArray.h /usr/include/stdlib.h
Tinst.o: ../lac/CallbackMethod.h TreeNode.C ../lac/TreeNode.h Model.h View.h
Tinst.o: ../lac/Rec.h ../lac/WidgetRef.h /usr/include/limits.h
Tinst.o: ../../include/X11/xpm.h SensitiveView.h ../lac/View.h
Tinst.o: ../lac/Controller.h ../lac/Lstring.h /usr/dt/include/Xm/AtomMgr.h
Tinst.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
Tinst.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
Tinst.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
Tinst.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/Xm/DragDrop.h
Tinst.o: /usr/dt/include/Xm/DragC.h /usr/dt/include/Xm/Display.h
Tinst.o: /usr/dt/include/Xm/DropSMgr.h /usr/dt/include/Xm/DragIcon.h
Tinst.o: /usr/dt/include/Xm/DropTrans.h /usr/dt/include/Xm/DragOverS.h
Tinst.o: /usr/dt/include/Xm/Screen.h IconView.h ../lac/SensitiveView.h
Tinst.o: TreeView.h LicView.h Controller.h HelpNode.h MLXHelp.h
Tinst.o: ../lac/HelpNode.h ../lac/MLXHelp_base.h ../lac/LicView.h
Tinst.o: ../lac/TreeView.h /usr/dt/include/Xm/TextOutP.h
Tinst.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/X11/IntrinsicP.h
Tinst.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
Tinst.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
Tinst.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
Tinst.o: /usr/dt/include/Xm/Text.h OptionMenuView.h CallbackMethod.h
MLXHelp.o: MLXHelp.h ../lac/HelpNode.h ../lac/TreeNode.h ../lac/ConModel.h
MLXHelp.o: ../lac/Model.h ../lac/Lobject.h /usr/include/stdio.h
MLXHelp.o: /usr/include/sys/stdsyms.h /usr/include/sys/types.h
MLXHelp.o: /usr/include/sys/_inttypes.h ../lac/RefArray.h ../lac/Ref.h
MLXHelp.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
MLXHelp.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
MLXHelp.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
MLXHelp.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
MLXHelp.o: /usr/include/string.h /usr/dt/include/X11/Core.h
MLXHelp.o: /usr/dt/include/X11/Composite.h /usr/dt/include/X11/Constraint.h
MLXHelp.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
MLXHelp.o: ../lac/TArray.h /usr/include/stdlib.h ../lac/CallbackMethod.h
MLXHelp.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
MLXHelp.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
MLXHelp.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
MLXHelp.o: /usr/dt/include/Xm/VendorS.h ../lac/MLXHelp_base.h
MLXHelp.o: ../lac/LicView.h ../lac/View.h ../lac/Rec.h ../lac/WidgetRef.h
MLXHelp.o: /usr/include/limits.h ../../include/X11/xpm.h ../lac/TreeView.h
MLXHelp.o: ../lac/SensitiveView.h ../lac/Controller.h ../lac/Lstring.h
MLXHelp.o: /usr/dt/include/Xm/AtomMgr.h /usr/dt/include/Xm/DragDrop.h
MLXHelp.o: /usr/dt/include/Xm/DragC.h /usr/dt/include/Xm/Display.h
MLXHelp.o: /usr/dt/include/Xm/DropSMgr.h /usr/dt/include/Xm/DragIcon.h
MLXHelp.o: /usr/dt/include/Xm/DropTrans.h /usr/dt/include/Xm/DragOverS.h
MLXHelp.o: /usr/dt/include/Xm/Screen.h /usr/dt/include/Xm/TextOutP.h
MLXHelp.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/X11/IntrinsicP.h
MLXHelp.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
MLXHelp.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
MLXHelp.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/BaseClassP.h
MLXHelp.o: /usr/dt/include/Xm/Text.h HelpTreeNodeView.h ../lac/MLXHelp.h
MLXHelp.o: ../lac/HelpNodeController.h /usr/dt/include/Xm/TextP.h
MLXHelp.o: /usr/dt/include/Xm/PrimitiveP.h /usr/dt/include/Xm/TextInP.h
MLXHelp.o: /usr/dt/include/Xm/TextStrSoP.h /usr/dt/include/Xm/PushB.h
MLXHelp.o: /usr/dt/include/X11/cursorfont.h /usr/dt/include/Xm/ToggleB.h
MLXHelp.o: /usr/dt/include/Xm/SelectioB.h /usr/dt/include/Xm/FileSB.h
MLXHelp.o: /usr/include/ctype.h /usr/include/unistd.h
MLXHelp.o: /usr/include/sys/unistd.h MLXHelp_res.h
MLXHelp_base.o: MLXHelp_base.h /usr/dt/include/X11/Intrinsic.h
MLXHelp_base.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
MLXHelp_base.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
MLXHelp_base.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
MLXHelp_base.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
MLXHelp_base.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
MLXHelp_base.o: /usr/include/string.h /usr/dt/include/X11/Core.h
MLXHelp_base.o: /usr/dt/include/X11/Composite.h
MLXHelp_base.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
MLXHelp_base.o: /usr/dt/include/X11/RectObj.h ../lac/LicView.h
MLXHelp_base.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
MLXHelp_base.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
MLXHelp_base.o: /usr/dt/include/X11/StringDefs.h
MLXHelp_base.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
MLXHelp_base.o: ../lac/View.h ../lac/Lobject.h /usr/include/stdio.h
MLXHelp_base.o: ../lac/RefArray.h ../lac/Ref.h ../lac/Rec.h
MLXHelp_base.o: ../lac/WidgetRef.h ../lac/TArray.h /usr/include/stdlib.h
MLXHelp_base.o: /usr/include/limits.h ../../include/X11/xpm.h
MLXHelp_base.o: /usr/dt/include/Xm/Frame.h /usr/dt/include/Xm/Form.h
MLXHelp_base.o: /usr/dt/include/Xm/BulletinB.h /usr/dt/include/Xm/SelectioB.h
MLXHelp_base.o: /usr/dt/include/Xm/RowColumn.h /usr/dt/include/Xm/ToggleB.h
MLXHelp_base.o: /usr/dt/include/Xm/CascadeB.h /usr/dt/include/Xm/PushB.h
MLXHelp_base.o: /usr/dt/include/Xm/ArrowB.h /usr/dt/include/Xm/PanedW.h
MLXHelp_base.o: /usr/dt/include/Xm/ScrolledW.h /usr/dt/include/Xm/Text.h
MLXHelp_base.o: /usr/dt/include/Xm/Label.h /usr/dt/include/Xm/FileSB.h
HelpNode.o: HelpNode.h ../lac/TreeNode.h ../lac/ConModel.h ../lac/Model.h
HelpNode.o: ../lac/Lobject.h /usr/include/stdio.h /usr/include/sys/stdsyms.h
HelpNode.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
HelpNode.o: ../lac/RefArray.h ../lac/Ref.h /usr/dt/include/X11/Intrinsic.h
HelpNode.o: /usr/dt/include/X11/Xlib.h /usr/dt/include/X11/X.h
HelpNode.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
HelpNode.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
HelpNode.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
HelpNode.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
HelpNode.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
HelpNode.o: /usr/dt/include/X11/RectObj.h ../lac/TArray.h
HelpNode.o: /usr/include/stdlib.h ../lac/CallbackMethod.h
HelpNode.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
HelpNode.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
HelpNode.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
HelpNode.o: /usr/dt/include/Xm/VendorS.h View.h ../lac/Rec.h
HelpNode.o: ../lac/WidgetRef.h /usr/include/limits.h ../../include/X11/xpm.h
HelpNode.o: helpnode.xpm /usr/include/ctype.h
SensitiveView.o: /usr/include/string.h /usr/dt/include/Xm/BulletinB.h
SensitiveView.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Intrinsic.h
SensitiveView.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
SensitiveView.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
SensitiveView.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
SensitiveView.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
SensitiveView.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
SensitiveView.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
SensitiveView.o: /usr/dt/include/X11/Constraint.h
SensitiveView.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
SensitiveView.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
SensitiveView.o: /usr/dt/include/Xm/XmStrDefs.h
SensitiveView.o: /usr/dt/include/X11/StringDefs.h
SensitiveView.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
SensitiveView.o: /usr/dt/include/Xm/DrawingA.h /usr/dt/include/Xm/Text.h
SensitiveView.o: /usr/include/stdio.h /usr/dt/include/Xm/ScrolledW.h
SensitiveView.o: /usr/dt/include/Xm/ScrollBar.h ../lwid/Bubble.h
SensitiveView.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/X11/IntrinsicP.h
SensitiveView.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
SensitiveView.o: /usr/dt/include/X11/ConstrainP.h
SensitiveView.o: /usr/dt/include/X11/ObjectP.h /usr/dt/include/X11/RectObjP.h
SensitiveView.o: /usr/dt/include/Xm/BaseClassP.h ../lac/SensitiveView.h
SensitiveView.o: ../lac/View.h ../lac/Lobject.h ../lac/RefArray.h
SensitiveView.o: ../lac/Ref.h ../lac/Rec.h ../lac/WidgetRef.h ../lac/TArray.h
SensitiveView.o: /usr/include/stdlib.h /usr/include/limits.h
SensitiveView.o: ../../include/X11/xpm.h ../lac/Controller.h ../lac/Model.h
SensitiveView.o: ../lac/CallbackMethod.h ../lac/Lstring.h
SensitiveView.o: /usr/dt/include/Xm/AtomMgr.h /usr/dt/include/Xm/DragDrop.h
SensitiveView.o: /usr/dt/include/Xm/DragC.h /usr/dt/include/Xm/Display.h
SensitiveView.o: /usr/dt/include/Xm/DropSMgr.h /usr/dt/include/Xm/DragIcon.h
SensitiveView.o: /usr/dt/include/Xm/DropTrans.h
SensitiveView.o: /usr/dt/include/Xm/DragOverS.h /usr/dt/include/Xm/Screen.h
SensitiveView.o: ../lac/ConModel.h ../lac/LicView.h /usr/include/math.h
IconView.o: ../lac/IconView.h ../lac/Model.h ../lac/Lobject.h
IconView.o: /usr/include/stdio.h /usr/include/sys/stdsyms.h
IconView.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
IconView.o: ../lac/RefArray.h ../lac/Ref.h /usr/dt/include/X11/Intrinsic.h
IconView.o: /usr/dt/include/X11/Xlib.h /usr/dt/include/X11/X.h
IconView.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
IconView.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
IconView.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
IconView.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
IconView.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
IconView.o: /usr/dt/include/X11/RectObj.h ../lac/TArray.h
IconView.o: /usr/include/stdlib.h ../lac/CallbackMethod.h
IconView.o: ../lac/SensitiveView.h ../lac/View.h ../lac/Rec.h
IconView.o: ../lac/WidgetRef.h /usr/include/limits.h ../../include/X11/xpm.h
IconView.o: ../lac/Controller.h ../lac/Lstring.h /usr/dt/include/Xm/AtomMgr.h
IconView.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
IconView.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
IconView.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
IconView.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/Xm/DragDrop.h
IconView.o: /usr/dt/include/Xm/DragC.h /usr/dt/include/Xm/Display.h
IconView.o: /usr/dt/include/Xm/DropSMgr.h /usr/dt/include/Xm/DragIcon.h
IconView.o: /usr/dt/include/Xm/DropTrans.h /usr/dt/include/Xm/DragOverS.h
IconView.o: /usr/dt/include/Xm/Screen.h ../lac/ConModel.h
IconView.o: /usr/dt/include/Xm/ScrolledW.h /usr/dt/include/Xm/ScrollBar.h
Controller.o: Controller.h /usr/dt/include/X11/Intrinsic.h
Controller.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
Controller.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
Controller.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
Controller.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
Controller.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
Controller.o: /usr/include/string.h /usr/dt/include/X11/Core.h
Controller.o: /usr/dt/include/X11/Composite.h
Controller.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
Controller.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/IntrinsicP.h
Controller.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
Controller.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
Controller.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/Xm.h
Controller.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
Controller.o: /usr/dt/include/Xm/XmStrDefs.h /usr/dt/include/X11/StringDefs.h
Controller.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
Controller.o: /usr/dt/include/Xm/PushB.h /usr/dt/include/Xm/ToggleB.h
Controller.o: /usr/dt/include/Xm/CascadeB.h /usr/dt/include/Xm/Separator.h
Controller.o: /usr/dt/include/Xm/Label.h /usr/dt/include/Xm/RowColumn.h
HelpNodeController.o: HelpNode.h ../lac/TreeNode.h ../lac/ConModel.h
HelpNodeController.o: ../lac/Model.h ../lac/Lobject.h /usr/include/stdio.h
HelpNodeController.o: /usr/include/sys/stdsyms.h /usr/include/sys/types.h
HelpNodeController.o: /usr/include/sys/_inttypes.h ../lac/RefArray.h
HelpNodeController.o: ../lac/Ref.h /usr/dt/include/X11/Intrinsic.h
HelpNodeController.o: /usr/dt/include/X11/Xlib.h /usr/dt/include/X11/X.h
HelpNodeController.o: /usr/dt/include/X11/Xfuncproto.h
HelpNodeController.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
HelpNodeController.o: /usr/dt/include/X11/Xutil.h
HelpNodeController.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
HelpNodeController.o: /usr/dt/include/X11/Core.h
HelpNodeController.o: /usr/dt/include/X11/Composite.h
HelpNodeController.o: /usr/dt/include/X11/Constraint.h
HelpNodeController.o: /usr/dt/include/X11/Object.h
HelpNodeController.o: /usr/dt/include/X11/RectObj.h ../lac/TArray.h
HelpNodeController.o: /usr/include/stdlib.h ../lac/CallbackMethod.h
HelpNodeController.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
HelpNodeController.o: /usr/dt/include/X11/Xatom.h
HelpNodeController.o: /usr/dt/include/Xm/XmStrDefs.h
HelpNodeController.o: /usr/dt/include/X11/StringDefs.h
HelpNodeController.o: /usr/dt/include/Xm/VirtKeys.h
HelpNodeController.o: /usr/dt/include/Xm/VendorS.h HelpNodeController.h
HelpNodeController.o: ../lac/Controller.h ../lac/View.h ../lac/Rec.h
HelpNodeController.o: ../lac/WidgetRef.h /usr/include/limits.h
HelpNodeController.o: ../../include/X11/xpm.h ../lac/Lstring.h MLXHelp.h
HelpNodeController.o: ../lac/HelpNode.h ../lac/MLXHelp_base.h
HelpNodeController.o: ../lac/LicView.h ../lac/TreeView.h
HelpNodeController.o: ../lac/SensitiveView.h /usr/dt/include/Xm/AtomMgr.h
HelpNodeController.o: /usr/dt/include/Xm/DragDrop.h
HelpNodeController.o: /usr/dt/include/Xm/DragC.h /usr/dt/include/Xm/Display.h
HelpNodeController.o: /usr/dt/include/Xm/DropSMgr.h
HelpNodeController.o: /usr/dt/include/Xm/DragIcon.h
HelpNodeController.o: /usr/dt/include/Xm/DropTrans.h
HelpNodeController.o: /usr/dt/include/Xm/DragOverS.h
HelpNodeController.o: /usr/dt/include/Xm/Screen.h
HelpNodeController.o: /usr/dt/include/Xm/TextOutP.h /usr/dt/include/Xm/XmP.h
HelpNodeController.o: /usr/dt/include/X11/IntrinsicP.h
HelpNodeController.o: /usr/dt/include/X11/CoreP.h
HelpNodeController.o: /usr/dt/include/X11/CompositeP.h
HelpNodeController.o: /usr/dt/include/X11/ConstrainP.h
HelpNodeController.o: /usr/dt/include/X11/ObjectP.h
HelpNodeController.o: /usr/dt/include/X11/RectObjP.h
HelpNodeController.o: /usr/dt/include/Xm/BaseClassP.h
HelpNodeController.o: /usr/dt/include/Xm/Text.h
Lstring.o: Lstring.h /usr/include/stdlib.h /usr/include/string.h
OptionMenuView.o: OptionMenuView.h ../lac/View.h
OptionMenuView.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
OptionMenuView.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
OptionMenuView.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
OptionMenuView.o: /usr/dt/include/X11/Xfuncproto.h
OptionMenuView.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
OptionMenuView.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
OptionMenuView.o: /usr/include/string.h /usr/dt/include/X11/Core.h
OptionMenuView.o: /usr/dt/include/X11/Composite.h
OptionMenuView.o: /usr/dt/include/X11/Constraint.h
OptionMenuView.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
OptionMenuView.o: ../lac/Lobject.h /usr/include/stdio.h ../lac/RefArray.h
OptionMenuView.o: ../lac/Ref.h ../lac/Rec.h ../lac/WidgetRef.h
OptionMenuView.o: ../lac/TArray.h /usr/include/stdlib.h /usr/include/limits.h
OptionMenuView.o: ../../include/X11/xpm.h ../lac/ConModel.h ../lac/Model.h
OptionMenuView.o: ../lac/CallbackMethod.h /usr/dt/include/Xm/Xm.h
OptionMenuView.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
OptionMenuView.o: /usr/dt/include/Xm/XmStrDefs.h
OptionMenuView.o: /usr/dt/include/X11/StringDefs.h
OptionMenuView.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
OptionMenuView.o: /usr/dt/include/Xm/RowColumn.h /usr/dt/include/Xm/PushB.h
CallbackMethod.o: CallbackMethod.h
