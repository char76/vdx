#
# Makefile for vdx (formerly called lic)
#
# $Log: Makefile,v $
# Revision 1.1.1.1.2.2  1999/08/27 16:00:49  dirk
# .
#
# Revision 1.1.1.1.2.1  1998/07/01 18:31:44  lazy
# Patches gcc 2.8
#
# Revision 1.1.1.1  1998/04/24 23:45:13  lazy
# Imported to CVS
#
# Revision 1.3  1998/03/30 19:08:38  lazy
# *** empty log message ***
#
# Revision 1.2  1997/10/03  15:35:54  lazy
# Rules for vdxgen and vdxgen.bin added.
#
# Revision 1.1  1997/07/25  20:15:28  lazy
# Initial revision
#
#

all:: program

TOPDIR = ../..
PROGRAM = vdx.bin

include $(TOPDIR)/Makerules

EXTRA_CFLAGS = -I/usr/X11R6/include -I.. -I../parse 
  LOCAL_LIBS = ../lac/$(ARCH)/liblac.a \
../parse/$(ARCH)/libparse.a \
../lwid/$(ARCH)/liblwid.a 
#../Xfe/$(ARCH)/libXfeWidgets.a

LOCAL_SHLIB = $(LIBPATH) -L../vdxlib/$(ARCH) -lvdx

#LIBS=

$(ARCH)/vdx.bin: $(LOCAL_LIBS) ../vdxlib/$(ARCH)/libvdx.so

all:: 
	rm -f $(TOPDIR)/bin/vdx.bin
	ln -s ../src/lic/$(ARCH)/vdx.bin $(TOPDIR)/bin/vdx.bin



OBJS = Lwhere.o Lproject.o Lwidget.o Lcreator.o Lresource.o Lproperty.o \
  lic.o LresEditor.o InterfaceInfo.o LApp.o Lpalette.o Ltmpl.o MenuEdit.o \
  MenuEdit_base.o MainWindow.o MainWindow_base.o Tinst.o misc.o FontSelect.o \
  FontSelect_base.o ColorSelect.o ColorSelect_base.o TextEdit.o \
  TextEdit_base.o Converter.o WidgetPalette.o WidgetPalette_base.o \
  AgreeWindow.o AgreeWindow_base.o WidBrowseView.o WidBrowseView_base.o \
  WidResEditor.o WidResEditor_base.o TemplateView.o TemplateView_base.o \
  ProjectSettings.o ProjectSettings_base.o ControllerImpl.o MegaPipe.o \
  AttachmentEditor.o AttachmentEditor_base.o \
  GlobalResEditor.o GlobalResEditor_base.o \
  TransformDialog.o TransformDialog_base.o lic_gen.o VersionControl.o \
  WidClassMenu.o

SRCS =  Lwhere.C Lproject.C Lwidget.C Lcreator.C Lresource.C Lproperty.C \
lic.C LresEditor.C InterfaceInfo.C LApp.C Lpalette.C Ltmpl.C MenuEdit.C \
MenuEdit_base.C MainWindow.C MainWindow_base.C Tinst.C misc.C FontSelect.C \
FontSelect_base.C ColorSelect.C ColorSelect_base.C TextEdit.C TextEdit_base.C\
Converter.c WidgetPalette.C WidgetPalette_base.C AgreeWindow.C \
AgreeWindow_base.C WidBrowseView.C WidBrowseView_base.C \
WidResEditor.C WidResEditor_base.C TemplateView.C TemplateView_base.C \
ProjectSettings.C ProjectSettings_base.C ControllerImpl.C MegaPipe.c \
AttachmentEditor.C AttachmentEditor_base.C \
GlobalResEditor.C GlobalResEditor_base.C \
TransformDialog.C TransformDialog_base.C lic_gen.C VersionControl.C \
WidClassMenu.C


depend: depend-src

lic_msg.h:	lic_msg.ad
	cat lic_msg.ad | $(TOPDIR)/bin/ad2h.script > lic_msg.h

Vdx.ad: lic_msg.ad lic.ad lic.hlp WidgetPalette.rf MainWindow.rf TextEdit.rf \
ColorSelect.rf FontSelect.rf AgreeWindow.rf TemplateView.rf WidResEditor.rf \
WidBrowseView.rf ProjectSettings.rf AttachmentEditor.rf GlobalResEditor.rf \
TransformDialog.rf
	cat lic.ad *.rf lic_msg.ad lic.hlp | $(REPLACE) >Vdx.ad

fallback.h:	Vdx.ad
	LC_ALL=de_DE.UTF-8 cat Vdx.ad | LC_ALL=de_DE.UTF-8 $(TOPDIR)/bin/ad2fbh.script >fallback.h


install:
	@$(INSTALL) $(ARCH)/$(PROGRAM) bin/vdx.bin
	@$(INSTALL) vdx bin/vdx
	@$(INSTALL) vcopen bin/vcopen
	@$(INSTALL) vcsave bin/vcsave
	@$(INSTALL) vcclose bin/vcclose
	@$(INSTALL) vdxgen bin/vdxgen
	@$(INSTALL_LINK) bin/vdx.bin vdxgen.bin 
	@$(INSTALL) Vdx.ad lib/X11/app-defaults/Vdx

clean: clean-src


#%.rf: %.i
#	$(TOPDIR)/bin/vdxgen c++lac $< $@

#%_base.C: %.i
#	$(TOPDIR)/bin/vdxgen c++lac $< $@

#%_base.h: %.i
#	$(TOPDIR)/bin/vdxgen c++lac $< $@

# DO NOT DELETE

Lwhere.o: Lwhere.h /usr/dt/include/X11/IntrinsicP.h
Lwhere.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
Lwhere.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
Lwhere.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
Lwhere.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
Lwhere.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
Lwhere.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
Lwhere.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
Lwhere.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
Lwhere.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/CoreP.h
Lwhere.o: /usr/dt/include/X11/CompositeP.h /usr/dt/include/X11/ConstrainP.h
Lwhere.o: /usr/dt/include/X11/ObjectP.h /usr/dt/include/X11/RectObjP.h
Lwhere.o: ../lac/Rec.h Lwidget.h /usr/include/stdio.h ../lac/IconView.h
Lwhere.o: ../lac/Model.h ../lac/Lobject.h ../lac/RefArray.h ../lac/Ref.h
Lwhere.o: ../lac/TArray.h /usr/include/stdlib.h ../lac/CallbackMethod.h
Lwhere.o: ../lac/SensitiveView.h ../lac/View.h ../lac/WidgetRef.h
Lwhere.o: /usr/include/limits.h ../../include/X11/xpm.h ../lac/Controller.h
Lwhere.o: ../lac/Lstring.h /usr/dt/include/Xm/AtomMgr.h
Lwhere.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
Lwhere.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
Lwhere.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
Lwhere.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/Xm/DragDrop.h
Lwhere.o: /usr/dt/include/Xm/DragC.h /usr/dt/include/Xm/Display.h
Lwhere.o: /usr/dt/include/Xm/DropSMgr.h /usr/dt/include/Xm/DragIcon.h
Lwhere.o: /usr/dt/include/Xm/DropTrans.h /usr/dt/include/Xm/DragOverS.h
Lwhere.o: /usr/dt/include/Xm/Screen.h ../lac/ConModel.h ../lac/TreeNode.h
Lwhere.o: ../lac/TreeView.h ../lac/HelpNode.h ../parse/parse.h Lproject.h
Lwhere.o: ../lac/LicView.h ../lac/MLXHelp.h ../lac/MLXHelp_base.h
Lwhere.o: /usr/dt/include/Xm/TextOutP.h /usr/dt/include/Xm/XmP.h
Lwhere.o: /usr/dt/include/Xm/BaseClassP.h /usr/dt/include/Xm/Text.h LApp.h
Lwhere.o: Ltmpl.h Lproperty.h Lresource.h ../lac/LHashDictionary.h Lcreator.h
Lwhere.o: ../vdxlib/LClassInfo.h Lpalette.h /usr/dt/include/X11/cursorfont.h
Lwhere.o: /usr/include/unistd.h /usr/include/sys/unistd.h
Lproject.o: Lproject.h /usr/include/limits.h /usr/dt/include/X11/IntrinsicP.h
Lproject.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
Lproject.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
Lproject.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
Lproject.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
Lproject.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
Lproject.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
Lproject.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
Lproject.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
Lproject.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/CoreP.h
Lproject.o: /usr/dt/include/X11/CompositeP.h /usr/dt/include/X11/ConstrainP.h
Lproject.o: /usr/dt/include/X11/ObjectP.h /usr/dt/include/X11/RectObjP.h
Lproject.o: ../lac/Model.h ../lac/Lobject.h /usr/include/stdio.h
Lproject.o: ../lac/RefArray.h ../lac/Ref.h ../lac/TArray.h
Lproject.o: /usr/include/stdlib.h ../lac/CallbackMethod.h ../lac/IconView.h
Lproject.o: ../lac/SensitiveView.h ../lac/View.h ../lac/Rec.h
Lproject.o: ../lac/WidgetRef.h ../../include/X11/xpm.h ../lac/Controller.h
Lproject.o: ../lac/Lstring.h /usr/dt/include/Xm/AtomMgr.h
Lproject.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
Lproject.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
Lproject.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
Lproject.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/Xm/DragDrop.h
Lproject.o: /usr/dt/include/Xm/DragC.h /usr/dt/include/Xm/Display.h
Lproject.o: /usr/dt/include/Xm/DropSMgr.h /usr/dt/include/Xm/DragIcon.h
Lproject.o: /usr/dt/include/Xm/DropTrans.h /usr/dt/include/Xm/DragOverS.h
Lproject.o: /usr/dt/include/Xm/Screen.h ../lac/ConModel.h ../parse/parse.h
Lproject.o: ../lac/LicView.h ../lac/MLXHelp.h ../lac/HelpNode.h
Lproject.o: ../lac/TreeNode.h ../lac/MLXHelp_base.h ../lac/TreeView.h
Lproject.o: /usr/dt/include/Xm/TextOutP.h /usr/dt/include/Xm/XmP.h
Lproject.o: /usr/dt/include/Xm/BaseClassP.h /usr/dt/include/Xm/Text.h LApp.h
Lproject.o: Lwidget.h Lproperty.h Lresource.h ../lac/LHashDictionary.h
Lproject.o: Lcreator.h ../vdxlib/LClassInfo.h Ltmpl.h Lwhere.h LresEditor.h
Lproject.o: lic.h lic_msg.h lic_hlp.h ../lac/MsgCat.h Lpalette.h
Lproject.o: InterfaceInfo.h misc.h WidBrowseView.h WidBrowseView_base.h
Lproject.o: ControllerImpl.h WidClassMenu.h VersionControl.h
Lproject.o: /usr/include/ctype.h /usr/include/unistd.h
Lproject.o: /usr/include/sys/unistd.h /usr/dt/include/Xm/RowColumn.h
Lproject.o: /usr/dt/include/Xm/Label.h /usr/dt/include/Xm/PushB.h
Lproject.o: /usr/dt/include/Xm/Separator.h
Lwidget.o: lic.h lic_msg.h lic_hlp.h ../lac/MsgCat.h ../lac/Lobject.h
Lwidget.o: /usr/include/stdio.h /usr/include/sys/types.h
Lwidget.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
Lwidget.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
Lwidget.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
Lwidget.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
Lwidget.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
Lwidget.o: /usr/include/string.h /usr/dt/include/X11/Core.h
Lwidget.o: /usr/dt/include/X11/Composite.h /usr/dt/include/X11/Constraint.h
Lwidget.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
Lwidget.o: Lwidget.h /usr/dt/include/X11/IntrinsicP.h
Lwidget.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
Lwidget.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
Lwidget.o: /usr/dt/include/X11/RectObjP.h ../lac/IconView.h ../lac/Model.h
Lwidget.o: ../lac/RefArray.h ../lac/Ref.h ../lac/TArray.h
Lwidget.o: /usr/include/stdlib.h ../lac/CallbackMethod.h
Lwidget.o: ../lac/SensitiveView.h ../lac/View.h ../lac/Rec.h
Lwidget.o: ../lac/WidgetRef.h /usr/include/limits.h ../../include/X11/xpm.h
Lwidget.o: ../lac/Controller.h ../lac/Lstring.h /usr/dt/include/Xm/AtomMgr.h
Lwidget.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
Lwidget.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
Lwidget.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
Lwidget.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/Xm/DragDrop.h
Lwidget.o: /usr/dt/include/Xm/DragC.h /usr/dt/include/Xm/Display.h
Lwidget.o: /usr/dt/include/Xm/DropSMgr.h /usr/dt/include/Xm/DragIcon.h
Lwidget.o: /usr/dt/include/Xm/DropTrans.h /usr/dt/include/Xm/DragOverS.h
Lwidget.o: /usr/dt/include/Xm/Screen.h ../lac/ConModel.h ../lac/TreeNode.h
Lwidget.o: ../lac/TreeView.h ../lac/HelpNode.h ../parse/parse.h Lproject.h
Lwidget.o: ../lac/LicView.h ../lac/MLXHelp.h ../lac/MLXHelp_base.h
Lwidget.o: /usr/dt/include/Xm/TextOutP.h /usr/dt/include/Xm/XmP.h
Lwidget.o: /usr/dt/include/Xm/BaseClassP.h /usr/dt/include/Xm/Text.h LApp.h
Lwidget.o: Ltmpl.h Lproperty.h Lresource.h ../lac/LHashDictionary.h
Lwidget.o: Lcreator.h ../vdxlib/LClassInfo.h Lwhere.h Lpalette.h
Lwidget.o: InterfaceInfo.h MenuEdit.h MenuEdit_base.h ControllerImpl.h
Lwidget.o: MainWindow.h MainWindow_base.h /usr/include/signal.h
Lwidget.o: /usr/include/sys/signal.h /usr/include/sys/sigevent.h
Lwidget.o: /usr/include/sys/siginfo.h /usr/include/sys/newsig.h
Lwidget.o: WidgetPalette.h WidgetPalette_base.h WidBrowseView.h
Lwidget.o: WidBrowseView_base.h WidClassMenu.h WidResEditor.h
Lwidget.o: WidResEditor_base.h AttachmentEditor.h AttachmentEditor_base.h
Lwidget.o: ../lac/OptionMenuView.h TransformDialog.h TransformDialog_base.h
Lwidget.o: /usr/dt/include/X11/ShellP.h /usr/dt/include/X11/VendorP.h
Lwidget.o: /usr/dt/include/X11/Vendor.h /usr/include/ctype.h
Lwidget.o: /usr/dt/include/Xm/RowColumn.h /usr/dt/include/Xm/Label.h
Lwidget.o: /usr/dt/include/Xm/PushB.h /usr/dt/include/Xm/ScrolledW.h
Lwidget.o: /usr/dt/include/Xm/Form.h /usr/dt/include/Xm/BulletinB.h
Lwidget.o: /usr/dt/include/Xm/PanedW.h /usr/dt/include/Xm/ToggleB.h
Lwidget.o: /usr/dt/include/Xm/Separator.h noSource.xbm noSource_mask.xbm
Lcreator.o: ../lac/Model.h ../lac/Lobject.h /usr/include/stdio.h
Lcreator.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
Lcreator.o: /usr/include/sys/stdsyms.h ../lac/RefArray.h ../lac/Ref.h
Lcreator.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
Lcreator.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
Lcreator.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
Lcreator.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
Lcreator.o: /usr/include/string.h /usr/dt/include/X11/Core.h
Lcreator.o: /usr/dt/include/X11/Composite.h /usr/dt/include/X11/Constraint.h
Lcreator.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
Lcreator.o: ../lac/TArray.h /usr/include/stdlib.h ../lac/CallbackMethod.h
Lcreator.o: ../lac/View.h ../lac/Rec.h ../lac/WidgetRef.h
Lcreator.o: /usr/include/limits.h ../../include/X11/xpm.h ../lac/IconView.h
Lcreator.o: ../lac/SensitiveView.h ../lac/Controller.h ../lac/Lstring.h
Lcreator.o: /usr/dt/include/Xm/AtomMgr.h /usr/dt/include/Xm/Xm.h
Lcreator.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
Lcreator.o: /usr/dt/include/Xm/XmStrDefs.h /usr/dt/include/X11/StringDefs.h
Lcreator.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
Lcreator.o: /usr/dt/include/Xm/DragDrop.h /usr/dt/include/Xm/DragC.h
Lcreator.o: /usr/dt/include/Xm/Display.h /usr/dt/include/Xm/DropSMgr.h
Lcreator.o: /usr/dt/include/Xm/DragIcon.h /usr/dt/include/Xm/DropTrans.h
Lcreator.o: /usr/dt/include/Xm/DragOverS.h /usr/dt/include/Xm/Screen.h
Lcreator.o: ../lac/ConModel.h lic.h lic_msg.h lic_hlp.h ../lac/MsgCat.h
Lcreator.o: Lcreator.h /usr/dt/include/X11/IntrinsicP.h
Lcreator.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
Lcreator.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
Lcreator.o: /usr/dt/include/X11/RectObjP.h ../lac/LicView.h
Lcreator.o: ../vdxlib/LClassInfo.h ../lac/LHashDictionary.h Lwhere.h
Lcreator.o: Lwidget.h ../lac/TreeNode.h ../lac/TreeView.h ../lac/HelpNode.h
Lcreator.o: ../parse/parse.h Lproject.h ../lac/MLXHelp.h
Lcreator.o: ../lac/MLXHelp_base.h /usr/dt/include/Xm/TextOutP.h
Lcreator.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/Xm/BaseClassP.h
Lcreator.o: /usr/dt/include/Xm/Text.h LApp.h Ltmpl.h Lproperty.h Lresource.h
Lcreator.o: /usr/dt/include/Xm/PushB.h /usr/dt/include/Xm/Form.h
Lcreator.o: /usr/dt/include/Xm/BulletinB.h /usr/dt/include/Xm/RowColumn.h
Lcreator.o: /usr/dt/include/Xm/DrawingA.h /usr/dt/include/Xm/ToggleB.h
Lcreator.o: /usr/include/ctype.h ../lac/TFuncSort.h
Lresource.o: Lresource.h ../lac/Model.h ../lac/Lobject.h /usr/include/stdio.h
Lresource.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
Lresource.o: /usr/include/sys/stdsyms.h ../lac/RefArray.h ../lac/Ref.h
Lresource.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
Lresource.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
Lresource.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
Lresource.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
Lresource.o: /usr/include/string.h /usr/dt/include/X11/Core.h
Lresource.o: /usr/dt/include/X11/Composite.h /usr/dt/include/X11/Constraint.h
Lresource.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
Lresource.o: ../lac/TArray.h /usr/include/stdlib.h ../lac/CallbackMethod.h
Lresource.o: ../lac/View.h ../lac/Rec.h ../lac/WidgetRef.h
Lresource.o: /usr/include/limits.h ../../include/X11/xpm.h
Lresource.o: /usr/dt/include/X11/IntrinsicP.h /usr/dt/include/X11/CoreP.h
Lresource.o: /usr/dt/include/X11/CompositeP.h
Lresource.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
Lresource.o: /usr/dt/include/X11/RectObjP.h ../parse/parse.h
Lresource.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
Lresource.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
Lresource.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
Lresource.o: /usr/dt/include/Xm/VendorS.h ../lac/Lstring.h
Lresource.o: ../lac/LHashDictionary.h LApp.h ../lac/IconView.h
Lresource.o: ../lac/SensitiveView.h ../lac/Controller.h
Lresource.o: /usr/dt/include/Xm/AtomMgr.h /usr/dt/include/Xm/DragDrop.h
Lresource.o: /usr/dt/include/Xm/DragC.h /usr/dt/include/Xm/Display.h
Lresource.o: /usr/dt/include/Xm/DropSMgr.h /usr/dt/include/Xm/DragIcon.h
Lresource.o: /usr/dt/include/Xm/DropTrans.h /usr/dt/include/Xm/DragOverS.h
Lresource.o: /usr/dt/include/Xm/Screen.h ../lac/ConModel.h lic.h lic_msg.h
Lresource.o: lic_hlp.h ../lac/MsgCat.h Lproject.h ../lac/LicView.h
Lresource.o: ../lac/MLXHelp.h ../lac/HelpNode.h ../lac/TreeNode.h
Lresource.o: ../lac/MLXHelp_base.h ../lac/TreeView.h
Lresource.o: /usr/dt/include/Xm/TextOutP.h /usr/dt/include/Xm/XmP.h
Lresource.o: /usr/dt/include/Xm/BaseClassP.h /usr/dt/include/Xm/Text.h
Lresource.o: Lwidget.h Lproperty.h Lcreator.h ../vdxlib/LClassInfo.h Ltmpl.h
Lproperty.o: Lproperty.h ../lac/RefArray.h ../lac/Ref.h ../lac/Lobject.h
Lproperty.o: /usr/include/stdio.h /usr/include/sys/types.h
Lproperty.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
Lproperty.o: ../parse/parse.h /usr/include/limits.h
Lproperty.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
Lproperty.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
Lproperty.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
Lproperty.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
Lproperty.o: /usr/include/string.h /usr/dt/include/X11/Core.h
Lproperty.o: /usr/dt/include/X11/Composite.h /usr/dt/include/X11/Constraint.h
Lproperty.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
Lproperty.o: Lresource.h ../lac/Model.h ../lac/TArray.h /usr/include/stdlib.h
Lproperty.o: ../lac/CallbackMethod.h ../lac/View.h ../lac/Rec.h
Lproperty.o: ../lac/WidgetRef.h ../../include/X11/xpm.h
Lproperty.o: /usr/dt/include/X11/IntrinsicP.h /usr/dt/include/X11/CoreP.h
Lproperty.o: /usr/dt/include/X11/CompositeP.h
Lproperty.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
Lproperty.o: /usr/dt/include/X11/RectObjP.h /usr/dt/include/Xm/Xm.h
Lproperty.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
Lproperty.o: /usr/dt/include/Xm/XmStrDefs.h /usr/dt/include/X11/StringDefs.h
Lproperty.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
Lproperty.o: ../lac/Lstring.h ../lac/LHashDictionary.h Lproject.h
Lproperty.o: ../lac/IconView.h ../lac/SensitiveView.h ../lac/Controller.h
Lproperty.o: /usr/dt/include/Xm/AtomMgr.h /usr/dt/include/Xm/DragDrop.h
Lproperty.o: /usr/dt/include/Xm/DragC.h /usr/dt/include/Xm/Display.h
Lproperty.o: /usr/dt/include/Xm/DropSMgr.h /usr/dt/include/Xm/DragIcon.h
Lproperty.o: /usr/dt/include/Xm/DropTrans.h /usr/dt/include/Xm/DragOverS.h
Lproperty.o: /usr/dt/include/Xm/Screen.h ../lac/ConModel.h ../lac/LicView.h
Lproperty.o: ../lac/MLXHelp.h ../lac/HelpNode.h ../lac/TreeNode.h
Lproperty.o: ../lac/MLXHelp_base.h ../lac/TreeView.h
Lproperty.o: /usr/dt/include/Xm/TextOutP.h /usr/dt/include/Xm/XmP.h
Lproperty.o: /usr/dt/include/Xm/BaseClassP.h /usr/dt/include/Xm/Text.h LApp.h
Lproperty.o: Lwidget.h Lcreator.h ../vdxlib/LClassInfo.h Ltmpl.h
Lproperty.o: InterfaceInfo.h
lic.o: /usr/include/stdio.h /usr/include/sys/types.h
lic.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
lic.o: /usr/include/locale.h /usr/include/unistd.h /usr/include/sys/unistd.h
lic.o: /usr/include/errno.h /usr/include/sys/errno.h Lproject.h
lic.o: /usr/include/limits.h /usr/dt/include/X11/IntrinsicP.h
lic.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
lic.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
lic.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
lic.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
lic.o: /usr/include/string.h /usr/dt/include/X11/Core.h
lic.o: /usr/dt/include/X11/Composite.h /usr/dt/include/X11/Constraint.h
lic.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
lic.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
lic.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
lic.o: /usr/dt/include/X11/RectObjP.h ../lac/Model.h ../lac/Lobject.h
lic.o: ../lac/RefArray.h ../lac/Ref.h ../lac/TArray.h /usr/include/stdlib.h
lic.o: ../lac/CallbackMethod.h ../lac/IconView.h ../lac/SensitiveView.h
lic.o: ../lac/View.h ../lac/Rec.h ../lac/WidgetRef.h ../../include/X11/xpm.h
lic.o: ../lac/Controller.h ../lac/Lstring.h /usr/dt/include/Xm/AtomMgr.h
lic.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
lic.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
lic.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
lic.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/Xm/DragDrop.h
lic.o: /usr/dt/include/Xm/DragC.h /usr/dt/include/Xm/Display.h
lic.o: /usr/dt/include/Xm/DropSMgr.h /usr/dt/include/Xm/DragIcon.h
lic.o: /usr/dt/include/Xm/DropTrans.h /usr/dt/include/Xm/DragOverS.h
lic.o: /usr/dt/include/Xm/Screen.h ../lac/ConModel.h ../parse/parse.h
lic.o: ../lac/LicView.h ../lac/MLXHelp.h ../lac/HelpNode.h ../lac/TreeNode.h
lic.o: ../lac/MLXHelp_base.h ../lac/TreeView.h /usr/dt/include/Xm/TextOutP.h
lic.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/Xm/BaseClassP.h
lic.o: /usr/dt/include/Xm/Text.h LApp.h Lwidget.h Lproperty.h Lresource.h
lic.o: ../lac/LHashDictionary.h Lcreator.h ../vdxlib/LClassInfo.h Ltmpl.h
lic.o: MainWindow.h MainWindow_base.h Lpalette.h /usr/include/signal.h
lic.o: /usr/include/sys/signal.h /usr/include/sys/sigevent.h
lic.o: /usr/include/sys/siginfo.h /usr/include/sys/newsig.h WidgetPalette.h
lic.o: WidgetPalette_base.h lic.h lic_msg.h lic_hlp.h ../lac/MsgCat.h
lic.o: Converter.h AgreeWindow.h AgreeWindow_base.h MegaPipe.h lic_gen.h
lic.o: /usr/dt/include/Dt/Term.h /usr/include/sys/wait.h
lic.o: /usr/dt/include/Dt/TermPrim.h fallback.h
LresEditor.o: lic.h lic_msg.h lic_hlp.h ../lac/MsgCat.h ../lac/Lobject.h
LresEditor.o: /usr/include/stdio.h /usr/include/sys/types.h
LresEditor.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
LresEditor.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
LresEditor.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
LresEditor.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
LresEditor.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
LresEditor.o: /usr/include/string.h /usr/dt/include/X11/Core.h
LresEditor.o: /usr/dt/include/X11/Composite.h
LresEditor.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
LresEditor.o: /usr/dt/include/X11/RectObj.h Lproject.h /usr/include/limits.h
LresEditor.o: /usr/dt/include/X11/IntrinsicP.h /usr/dt/include/X11/CoreP.h
LresEditor.o: /usr/dt/include/X11/CompositeP.h
LresEditor.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
LresEditor.o: /usr/dt/include/X11/RectObjP.h ../lac/Model.h ../lac/RefArray.h
LresEditor.o: ../lac/Ref.h ../lac/TArray.h /usr/include/stdlib.h
LresEditor.o: ../lac/CallbackMethod.h ../lac/IconView.h
LresEditor.o: ../lac/SensitiveView.h ../lac/View.h ../lac/Rec.h
LresEditor.o: ../lac/WidgetRef.h ../../include/X11/xpm.h ../lac/Controller.h
LresEditor.o: ../lac/Lstring.h /usr/dt/include/Xm/AtomMgr.h
LresEditor.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
LresEditor.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
LresEditor.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
LresEditor.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/Xm/DragDrop.h
LresEditor.o: /usr/dt/include/Xm/DragC.h /usr/dt/include/Xm/Display.h
LresEditor.o: /usr/dt/include/Xm/DropSMgr.h /usr/dt/include/Xm/DragIcon.h
LresEditor.o: /usr/dt/include/Xm/DropTrans.h /usr/dt/include/Xm/DragOverS.h
LresEditor.o: /usr/dt/include/Xm/Screen.h ../lac/ConModel.h ../parse/parse.h
LresEditor.o: ../lac/LicView.h ../lac/MLXHelp.h ../lac/HelpNode.h
LresEditor.o: ../lac/TreeNode.h ../lac/MLXHelp_base.h ../lac/TreeView.h
LresEditor.o: /usr/dt/include/Xm/TextOutP.h /usr/dt/include/Xm/XmP.h
LresEditor.o: /usr/dt/include/Xm/BaseClassP.h /usr/dt/include/Xm/Text.h
LresEditor.o: LApp.h Lwidget.h Lproperty.h Lresource.h
LresEditor.o: ../lac/LHashDictionary.h Lcreator.h ../vdxlib/LClassInfo.h
LresEditor.o: Ltmpl.h LresEditor.h misc.h FontSelect.h FontSelect_base.h
LresEditor.o: ColorSelect.h ColorSelect_base.h TextEdit.h TextEdit_base.h
LresEditor.o: /usr/dt/include/Xm/Label.h /usr/dt/include/Xm/RowColumn.h
LresEditor.o: /usr/dt/include/Xm/PushB.h /usr/dt/include/Xm/ScrolledW.h
LresEditor.o: /usr/dt/include/Xm/Form.h /usr/dt/include/Xm/BulletinB.h
LresEditor.o: /usr/dt/include/Xm/ToggleB.h /usr/include/ctype.h
LresEditor.o: ../lwid/CellTable.h
InterfaceInfo.o: Ltmpl.h /usr/include/limits.h ../lac/Lobject.h
InterfaceInfo.o: /usr/include/stdio.h /usr/include/sys/types.h
InterfaceInfo.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
InterfaceInfo.o: Lproject.h /usr/dt/include/X11/IntrinsicP.h
InterfaceInfo.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
InterfaceInfo.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
InterfaceInfo.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
InterfaceInfo.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
InterfaceInfo.o: /usr/include/string.h /usr/dt/include/X11/Core.h
InterfaceInfo.o: /usr/dt/include/X11/Composite.h
InterfaceInfo.o: /usr/dt/include/X11/Constraint.h
InterfaceInfo.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
InterfaceInfo.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
InterfaceInfo.o: /usr/dt/include/X11/ConstrainP.h
InterfaceInfo.o: /usr/dt/include/X11/ObjectP.h /usr/dt/include/X11/RectObjP.h
InterfaceInfo.o: ../lac/Model.h ../lac/RefArray.h ../lac/Ref.h
InterfaceInfo.o: ../lac/TArray.h /usr/include/stdlib.h
InterfaceInfo.o: ../lac/CallbackMethod.h ../lac/IconView.h
InterfaceInfo.o: ../lac/SensitiveView.h ../lac/View.h ../lac/Rec.h
InterfaceInfo.o: ../lac/WidgetRef.h ../../include/X11/xpm.h
InterfaceInfo.o: ../lac/Controller.h ../lac/Lstring.h
InterfaceInfo.o: /usr/dt/include/Xm/AtomMgr.h /usr/dt/include/Xm/Xm.h
InterfaceInfo.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
InterfaceInfo.o: /usr/dt/include/Xm/XmStrDefs.h
InterfaceInfo.o: /usr/dt/include/X11/StringDefs.h
InterfaceInfo.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
InterfaceInfo.o: /usr/dt/include/Xm/DragDrop.h /usr/dt/include/Xm/DragC.h
InterfaceInfo.o: /usr/dt/include/Xm/Display.h /usr/dt/include/Xm/DropSMgr.h
InterfaceInfo.o: /usr/dt/include/Xm/DragIcon.h /usr/dt/include/Xm/DropTrans.h
InterfaceInfo.o: /usr/dt/include/Xm/DragOverS.h /usr/dt/include/Xm/Screen.h
InterfaceInfo.o: ../lac/ConModel.h ../parse/parse.h ../lac/LicView.h
InterfaceInfo.o: ../lac/MLXHelp.h ../lac/HelpNode.h ../lac/TreeNode.h
InterfaceInfo.o: ../lac/MLXHelp_base.h ../lac/TreeView.h
InterfaceInfo.o: /usr/dt/include/Xm/TextOutP.h /usr/dt/include/Xm/XmP.h
InterfaceInfo.o: /usr/dt/include/Xm/BaseClassP.h /usr/dt/include/Xm/Text.h
InterfaceInfo.o: LApp.h Lwidget.h Lproperty.h Lresource.h
InterfaceInfo.o: ../lac/LHashDictionary.h Lcreator.h ../vdxlib/LClassInfo.h
InterfaceInfo.o: InterfaceInfo.h misc.h lic.h lic_msg.h lic_hlp.h
InterfaceInfo.o: ../lac/MsgCat.h /usr/include/ctype.h /usr/include/time.h
InterfaceInfo.o: /usr/include/sys/utsname.h
LApp.o: lic.h lic_msg.h lic_hlp.h ../lac/MsgCat.h ../lac/Lobject.h
LApp.o: /usr/include/stdio.h /usr/include/sys/types.h
LApp.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
LApp.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
LApp.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
LApp.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
LApp.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
LApp.o: /usr/include/string.h /usr/dt/include/X11/Core.h
LApp.o: /usr/dt/include/X11/Composite.h /usr/dt/include/X11/Constraint.h
LApp.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h LApp.h
LApp.o: ../lac/Model.h ../lac/RefArray.h ../lac/Ref.h ../lac/TArray.h
LApp.o: /usr/include/stdlib.h ../lac/CallbackMethod.h ../lac/IconView.h
LApp.o: ../lac/SensitiveView.h ../lac/View.h ../lac/Rec.h ../lac/WidgetRef.h
LApp.o: /usr/include/limits.h ../../include/X11/xpm.h ../lac/Controller.h
LApp.o: ../lac/Lstring.h /usr/dt/include/Xm/AtomMgr.h /usr/dt/include/Xm/Xm.h
LApp.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
LApp.o: /usr/dt/include/Xm/XmStrDefs.h /usr/dt/include/X11/StringDefs.h
LApp.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
LApp.o: /usr/dt/include/Xm/DragDrop.h /usr/dt/include/Xm/DragC.h
LApp.o: /usr/dt/include/Xm/Display.h /usr/dt/include/Xm/DropSMgr.h
LApp.o: /usr/dt/include/Xm/DragIcon.h /usr/dt/include/Xm/DropTrans.h
LApp.o: /usr/dt/include/Xm/DragOverS.h /usr/dt/include/Xm/Screen.h
LApp.o: ../lac/ConModel.h ../parse/parse.h Lproject.h
LApp.o: /usr/dt/include/X11/IntrinsicP.h /usr/dt/include/X11/CoreP.h
LApp.o: /usr/dt/include/X11/CompositeP.h /usr/dt/include/X11/ConstrainP.h
LApp.o: /usr/dt/include/X11/ObjectP.h /usr/dt/include/X11/RectObjP.h
LApp.o: ../lac/LicView.h ../lac/MLXHelp.h ../lac/HelpNode.h ../lac/TreeNode.h
LApp.o: ../lac/MLXHelp_base.h ../lac/TreeView.h /usr/dt/include/Xm/TextOutP.h
LApp.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/Xm/BaseClassP.h
LApp.o: /usr/dt/include/Xm/Text.h Lwidget.h Lproperty.h Lresource.h
LApp.o: ../lac/LHashDictionary.h Lcreator.h ../vdxlib/LClassInfo.h Ltmpl.h
LApp.o: Lwhere.h Lpalette.h VersionControl.h MainWindow.h MainWindow_base.h
LApp.o: /usr/include/signal.h /usr/include/sys/signal.h
LApp.o: /usr/include/sys/sigevent.h /usr/include/sys/siginfo.h
LApp.o: /usr/include/sys/newsig.h WidgetPalette.h WidgetPalette_base.h
LApp.o: TextEdit.h TextEdit_base.h misc.h ../lwid/Bubble.h
LApp.o: /usr/include/unistd.h /usr/include/sys/unistd.h
LApp.o: /usr/include/sys/stat.h /usr/include/sys/_stat_body.h
LApp.o: /usr/include/time.h /usr/include/errno.h /usr/include/sys/errno.h
LApp.o: ../license/license.h
Lpalette.o: Lpalette.h Lwidget.h /usr/dt/include/X11/IntrinsicP.h
Lpalette.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
Lpalette.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
Lpalette.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
Lpalette.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
Lpalette.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
Lpalette.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
Lpalette.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
Lpalette.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
Lpalette.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/CoreP.h
Lpalette.o: /usr/dt/include/X11/CompositeP.h /usr/dt/include/X11/ConstrainP.h
Lpalette.o: /usr/dt/include/X11/ObjectP.h /usr/dt/include/X11/RectObjP.h
Lpalette.o: /usr/include/stdio.h ../lac/IconView.h ../lac/Model.h
Lpalette.o: ../lac/Lobject.h ../lac/RefArray.h ../lac/Ref.h ../lac/TArray.h
Lpalette.o: /usr/include/stdlib.h ../lac/CallbackMethod.h
Lpalette.o: ../lac/SensitiveView.h ../lac/View.h ../lac/Rec.h
Lpalette.o: ../lac/WidgetRef.h /usr/include/limits.h ../../include/X11/xpm.h
Lpalette.o: ../lac/Controller.h ../lac/Lstring.h /usr/dt/include/Xm/AtomMgr.h
Lpalette.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
Lpalette.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
Lpalette.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
Lpalette.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/Xm/DragDrop.h
Lpalette.o: /usr/dt/include/Xm/DragC.h /usr/dt/include/Xm/Display.h
Lpalette.o: /usr/dt/include/Xm/DropSMgr.h /usr/dt/include/Xm/DragIcon.h
Lpalette.o: /usr/dt/include/Xm/DropTrans.h /usr/dt/include/Xm/DragOverS.h
Lpalette.o: /usr/dt/include/Xm/Screen.h ../lac/ConModel.h ../lac/TreeNode.h
Lpalette.o: ../lac/TreeView.h ../lac/HelpNode.h ../parse/parse.h Lproject.h
Lpalette.o: ../lac/LicView.h ../lac/MLXHelp.h ../lac/MLXHelp_base.h
Lpalette.o: /usr/dt/include/Xm/TextOutP.h /usr/dt/include/Xm/XmP.h
Lpalette.o: /usr/dt/include/Xm/BaseClassP.h /usr/dt/include/Xm/Text.h LApp.h
Lpalette.o: Ltmpl.h Lproperty.h Lresource.h ../lac/LHashDictionary.h
Lpalette.o: Lcreator.h ../vdxlib/LClassInfo.h Lwhere.h misc.h lic.h lic_msg.h
Lpalette.o: lic_hlp.h ../lac/MsgCat.h VersionControl.h
Lpalette.o: /usr/dt/include/Xm/Form.h /usr/dt/include/Xm/BulletinB.h
Lpalette.o: /usr/dt/include/Xm/PushB.h
Ltmpl.o: /usr/include/stdio.h /usr/include/sys/types.h
Ltmpl.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
Ltmpl.o: /usr/include/string.h Ltmpl.h /usr/include/limits.h ../lac/Lobject.h
Ltmpl.o: /usr/include/errno.h /usr/include/sys/errno.h misc.h
Ltmpl.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
Ltmpl.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
Ltmpl.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
Ltmpl.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
Ltmpl.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
Ltmpl.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
Ltmpl.o: /usr/dt/include/X11/RectObj.h
MenuEdit.o: lic.h lic_msg.h lic_hlp.h ../lac/MsgCat.h ../lac/Lobject.h
MenuEdit.o: /usr/include/stdio.h /usr/include/sys/types.h
MenuEdit.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
MenuEdit.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
MenuEdit.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
MenuEdit.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
MenuEdit.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
MenuEdit.o: /usr/include/string.h /usr/dt/include/X11/Core.h
MenuEdit.o: /usr/dt/include/X11/Composite.h /usr/dt/include/X11/Constraint.h
MenuEdit.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
MenuEdit.o: MenuEdit.h ../lac/IconView.h ../lac/Model.h ../lac/RefArray.h
MenuEdit.o: ../lac/Ref.h ../lac/TArray.h /usr/include/stdlib.h
MenuEdit.o: ../lac/CallbackMethod.h ../lac/SensitiveView.h ../lac/View.h
MenuEdit.o: ../lac/Rec.h ../lac/WidgetRef.h /usr/include/limits.h
MenuEdit.o: ../../include/X11/xpm.h ../lac/Controller.h ../lac/Lstring.h
MenuEdit.o: /usr/dt/include/Xm/AtomMgr.h /usr/dt/include/Xm/Xm.h
MenuEdit.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
MenuEdit.o: /usr/dt/include/Xm/XmStrDefs.h /usr/dt/include/X11/StringDefs.h
MenuEdit.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
MenuEdit.o: /usr/dt/include/Xm/DragDrop.h /usr/dt/include/Xm/DragC.h
MenuEdit.o: /usr/dt/include/Xm/Display.h /usr/dt/include/Xm/DropSMgr.h
MenuEdit.o: /usr/dt/include/Xm/DragIcon.h /usr/dt/include/Xm/DropTrans.h
MenuEdit.o: /usr/dt/include/Xm/DragOverS.h /usr/dt/include/Xm/Screen.h
MenuEdit.o: ../lac/ConModel.h MenuEdit_base.h ../lac/LicView.h Lproject.h
MenuEdit.o: /usr/dt/include/X11/IntrinsicP.h /usr/dt/include/X11/CoreP.h
MenuEdit.o: /usr/dt/include/X11/CompositeP.h /usr/dt/include/X11/ConstrainP.h
MenuEdit.o: /usr/dt/include/X11/ObjectP.h /usr/dt/include/X11/RectObjP.h
MenuEdit.o: ../parse/parse.h ../lac/MLXHelp.h ../lac/HelpNode.h
MenuEdit.o: ../lac/TreeNode.h ../lac/MLXHelp_base.h ../lac/TreeView.h
MenuEdit.o: /usr/dt/include/Xm/TextOutP.h /usr/dt/include/Xm/XmP.h
MenuEdit.o: /usr/dt/include/Xm/BaseClassP.h /usr/dt/include/Xm/Text.h LApp.h
MenuEdit.o: Lwidget.h Lproperty.h Lresource.h ../lac/LHashDictionary.h
MenuEdit.o: Lcreator.h ../vdxlib/LClassInfo.h Ltmpl.h ControllerImpl.h
MenuEdit.o: Lwhere.h /usr/dt/include/Xm/ToggleB.h
MenuEdit_base.o: MenuEdit_base.h /usr/dt/include/X11/Intrinsic.h
MenuEdit_base.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
MenuEdit_base.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
MenuEdit_base.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
MenuEdit_base.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
MenuEdit_base.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
MenuEdit_base.o: /usr/include/string.h /usr/dt/include/X11/Core.h
MenuEdit_base.o: /usr/dt/include/X11/Composite.h
MenuEdit_base.o: /usr/dt/include/X11/Constraint.h
MenuEdit_base.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
MenuEdit_base.o: ../lac/LicView.h /usr/dt/include/Xm/Xm.h
MenuEdit_base.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
MenuEdit_base.o: /usr/dt/include/Xm/XmStrDefs.h
MenuEdit_base.o: /usr/dt/include/X11/StringDefs.h
MenuEdit_base.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
MenuEdit_base.o: ../lac/View.h ../lac/Lobject.h /usr/include/stdio.h
MenuEdit_base.o: ../lac/RefArray.h ../lac/Ref.h ../lac/Rec.h
MenuEdit_base.o: ../lac/WidgetRef.h ../lac/TArray.h /usr/include/stdlib.h
MenuEdit_base.o: /usr/include/limits.h ../../include/X11/xpm.h
MenuEdit_base.o: /usr/dt/include/Xm/Frame.h /usr/dt/include/Xm/MainW.h
MenuEdit_base.o: /usr/dt/include/Xm/Form.h /usr/dt/include/Xm/BulletinB.h
MenuEdit_base.o: /usr/dt/include/Xm/Label.h /usr/dt/include/Xm/ArrowB.h
MenuEdit_base.o: /usr/dt/include/Xm/RowColumn.h /usr/dt/include/Xm/PushB.h
MenuEdit_base.o: /usr/dt/include/Xm/CascadeB.h /usr/dt/include/Xm/ToggleB.h
MenuEdit_base.o: /usr/dt/include/Xm/Separator.h
MainWindow.o: MainWindow.h MainWindow_base.h /usr/dt/include/X11/Intrinsic.h
MainWindow.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
MainWindow.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
MainWindow.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
MainWindow.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
MainWindow.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
MainWindow.o: /usr/include/string.h /usr/dt/include/X11/Core.h
MainWindow.o: /usr/dt/include/X11/Composite.h
MainWindow.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
MainWindow.o: /usr/dt/include/X11/RectObj.h ../lac/LicView.h
MainWindow.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
MainWindow.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
MainWindow.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
MainWindow.o: /usr/dt/include/Xm/VendorS.h ../lac/View.h ../lac/Lobject.h
MainWindow.o: /usr/include/stdio.h ../lac/RefArray.h ../lac/Ref.h
MainWindow.o: ../lac/Rec.h ../lac/WidgetRef.h ../lac/TArray.h
MainWindow.o: /usr/include/stdlib.h /usr/include/limits.h
MainWindow.o: ../../include/X11/xpm.h LApp.h ../lac/Model.h
MainWindow.o: ../lac/CallbackMethod.h ../lac/IconView.h
MainWindow.o: ../lac/SensitiveView.h ../lac/Controller.h ../lac/Lstring.h
MainWindow.o: /usr/dt/include/Xm/AtomMgr.h /usr/dt/include/Xm/DragDrop.h
MainWindow.o: /usr/dt/include/Xm/DragC.h /usr/dt/include/Xm/Display.h
MainWindow.o: /usr/dt/include/Xm/DropSMgr.h /usr/dt/include/Xm/DragIcon.h
MainWindow.o: /usr/dt/include/Xm/DropTrans.h /usr/dt/include/Xm/DragOverS.h
MainWindow.o: /usr/dt/include/Xm/Screen.h ../lac/ConModel.h ../parse/parse.h
MainWindow.o: Lcreator.h /usr/dt/include/X11/IntrinsicP.h
MainWindow.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
MainWindow.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
MainWindow.o: /usr/dt/include/X11/RectObjP.h ../vdxlib/LClassInfo.h
MainWindow.o: ../lac/LHashDictionary.h Lwidget.h ../lac/TreeNode.h
MainWindow.o: ../lac/TreeView.h ../lac/HelpNode.h Lproject.h ../lac/MLXHelp.h
MainWindow.o: ../lac/MLXHelp_base.h /usr/dt/include/Xm/TextOutP.h
MainWindow.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/Xm/BaseClassP.h
MainWindow.o: /usr/dt/include/Xm/Text.h Ltmpl.h Lproperty.h Lresource.h
MainWindow.o: Lpalette.h /usr/include/signal.h /usr/include/sys/signal.h
MainWindow.o: /usr/include/sys/sigevent.h /usr/include/sys/siginfo.h
MainWindow.o: /usr/include/sys/newsig.h WidgetPalette.h WidgetPalette_base.h
MainWindow.o: lic.h lic_msg.h lic_hlp.h ../lac/MsgCat.h misc.h TextEdit.h
MainWindow.o: TextEdit_base.h LresEditor.h TemplateView.h TemplateView_base.h
MainWindow.o: ControllerImpl.h ProjectSettings.h ProjectSettings_base.h
MainWindow.o: ../lac/OptionMenuView.h GlobalResEditor.h
MainWindow.o: GlobalResEditor_base.h ColorSelect.h ColorSelect_base.h
MainWindow.o: FontSelect.h FontSelect_base.h VersionControl.h WidResEditor.h
MainWindow.o: WidResEditor_base.h /usr/dt/include/Xm/Form.h
MainWindow.o: /usr/dt/include/Xm/BulletinB.h /usr/dt/include/Xm/PushB.h
MainWindow.o: /usr/dt/include/Xm/Scale.h /usr/dt/include/Xm/ToggleB.h
MainWindow.o: /usr/dt/include/Xm/List.h /usr/dt/include/Xm/MessageB.h
MainWindow.o: ../lwid/Bubble.h /usr/include/unistd.h
MainWindow.o: /usr/include/sys/unistd.h /usr/include/sys/stat.h
MainWindow.o: /usr/include/sys/_stat_body.h /usr/include/fcntl.h
MainWindow.o: /usr/include/sys/fcntl.h /usr/include/sys/_flock_body.h
MainWindow.o: /usr/include/sys/wait.h /usr/include/ctype.h
MainWindow_base.o: MainWindow_base.h /usr/dt/include/X11/Intrinsic.h
MainWindow_base.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
MainWindow_base.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
MainWindow_base.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
MainWindow_base.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
MainWindow_base.o: /usr/dt/include/X11/Xutil.h
MainWindow_base.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
MainWindow_base.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
MainWindow_base.o: /usr/dt/include/X11/Constraint.h
MainWindow_base.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
MainWindow_base.o: ../lac/LicView.h /usr/dt/include/Xm/Xm.h
MainWindow_base.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
MainWindow_base.o: /usr/dt/include/Xm/XmStrDefs.h
MainWindow_base.o: /usr/dt/include/X11/StringDefs.h
MainWindow_base.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
MainWindow_base.o: ../lac/View.h ../lac/Lobject.h /usr/include/stdio.h
MainWindow_base.o: ../lac/RefArray.h ../lac/Ref.h ../lac/Rec.h
MainWindow_base.o: ../lac/WidgetRef.h ../lac/TArray.h /usr/include/stdlib.h
MainWindow_base.o: /usr/include/limits.h ../../include/X11/xpm.h
MainWindow_base.o: /usr/dt/include/Xm/Frame.h /usr/dt/include/Xm/Form.h
MainWindow_base.o: /usr/dt/include/Xm/BulletinB.h
MainWindow_base.o: /usr/dt/include/Xm/RowColumn.h
MainWindow_base.o: /usr/dt/include/Xm/CascadeB.h /usr/dt/include/Xm/PushB.h
MainWindow_base.o: /usr/dt/include/Xm/Separator.h
MainWindow_base.o: /usr/dt/include/Xm/ToggleB.h /usr/dt/include/Xm/DrawnB.h
MainWindow_base.o: /usr/dt/include/Xm/PanedW.h /usr/dt/include/Xm/Label.h
MainWindow_base.o: /usr/dt/include/Xm/ScrolledW.h /usr/dt/include/Xm/Text.h
MainWindow_base.o: /usr/dt/include/Xm/FileSB.h /usr/dt/include/Xm/Scale.h
MainWindow_base.o: /usr/dt/include/Xm/List.h /usr/dt/include/Xm/MessageB.h
MainWindow_base.o: ../lwid/CellTable.h
Tinst.o: Lproject.h /usr/include/limits.h /usr/dt/include/X11/IntrinsicP.h
Tinst.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
Tinst.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
Tinst.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
Tinst.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
Tinst.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
Tinst.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
Tinst.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
Tinst.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
Tinst.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/CoreP.h
Tinst.o: /usr/dt/include/X11/CompositeP.h /usr/dt/include/X11/ConstrainP.h
Tinst.o: /usr/dt/include/X11/ObjectP.h /usr/dt/include/X11/RectObjP.h
Tinst.o: ../lac/Model.h ../lac/Lobject.h /usr/include/stdio.h
Tinst.o: ../lac/RefArray.h ../lac/Ref.h ../lac/TArray.h /usr/include/stdlib.h
Tinst.o: ../lac/CallbackMethod.h ../lac/IconView.h ../lac/SensitiveView.h
Tinst.o: ../lac/View.h ../lac/Rec.h ../lac/WidgetRef.h
Tinst.o: ../../include/X11/xpm.h ../lac/Controller.h ../lac/Lstring.h
Tinst.o: /usr/dt/include/Xm/AtomMgr.h /usr/dt/include/Xm/Xm.h
Tinst.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
Tinst.o: /usr/dt/include/Xm/XmStrDefs.h /usr/dt/include/X11/StringDefs.h
Tinst.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
Tinst.o: /usr/dt/include/Xm/DragDrop.h /usr/dt/include/Xm/DragC.h
Tinst.o: /usr/dt/include/Xm/Display.h /usr/dt/include/Xm/DropSMgr.h
Tinst.o: /usr/dt/include/Xm/DragIcon.h /usr/dt/include/Xm/DropTrans.h
Tinst.o: /usr/dt/include/Xm/DragOverS.h /usr/dt/include/Xm/Screen.h
Tinst.o: ../lac/ConModel.h ../parse/parse.h ../lac/LicView.h ../lac/MLXHelp.h
Tinst.o: ../lac/HelpNode.h ../lac/TreeNode.h ../lac/MLXHelp_base.h
Tinst.o: ../lac/TreeView.h /usr/dt/include/Xm/TextOutP.h
Tinst.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/Xm/BaseClassP.h
Tinst.o: /usr/dt/include/Xm/Text.h LApp.h Lwidget.h Lproperty.h Lresource.h
Tinst.o: ../lac/LHashDictionary.h Lcreator.h ../vdxlib/LClassInfo.h Ltmpl.h
Tinst.o: InterfaceInfo.h Lpalette.h LresEditor.h lic.h lic_msg.h lic_hlp.h
Tinst.o: ../lac/MsgCat.h FontSelect.h FontSelect_base.h ColorSelect.h
Tinst.o: ColorSelect_base.h MenuEdit.h MenuEdit_base.h ControllerImpl.h
Tinst.o: TextEdit.h TextEdit_base.h MainWindow.h MainWindow_base.h
Tinst.o: /usr/include/signal.h /usr/include/sys/signal.h
Tinst.o: /usr/include/sys/sigevent.h /usr/include/sys/siginfo.h
Tinst.o: /usr/include/sys/newsig.h WidgetPalette.h WidgetPalette_base.h
Tinst.o: TemplateView.h TemplateView_base.h WidBrowseView.h
Tinst.o: WidBrowseView_base.h WidClassMenu.h WidResEditor.h
Tinst.o: WidResEditor_base.h ProjectSettings.h ProjectSettings_base.h
Tinst.o: ../lac/OptionMenuView.h AttachmentEditor.h AttachmentEditor_base.h
Tinst.o: GlobalResEditor.h GlobalResEditor_base.h TransformDialog.h
Tinst.o: TransformDialog_base.h ../lac/Ref.C ../lac/RefArray.C
Tinst.o: ../lac/ConModel.C ../lac/TreeNode.C
misc.o: misc.h /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
misc.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
misc.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
misc.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
misc.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
misc.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
misc.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
misc.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
misc.o: /usr/dt/include/X11/RectObj.h /usr/include/stdio.h
misc.o: /usr/include/unistd.h /usr/include/sys/unistd.h /usr/include/pwd.h
misc.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
misc.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
misc.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
misc.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/Xm/DragDrop.h
misc.o: /usr/dt/include/Xm/DragC.h /usr/dt/include/Xm/Display.h
misc.o: /usr/dt/include/Xm/DropSMgr.h /usr/dt/include/Xm/DragIcon.h
misc.o: /usr/dt/include/Xm/DropTrans.h /usr/dt/include/Xm/DragOverS.h
misc.o: /usr/dt/include/Xm/Text.h /usr/dt/include/Xm/TextF.h
misc.o: /usr/include/limits.h /usr/include/sys/stat.h
misc.o: /usr/include/sys/_stat_body.h /usr/include/errno.h
misc.o: /usr/include/sys/errno.h
FontSelect.o: FontSelect.h FontSelect_base.h /usr/dt/include/X11/Intrinsic.h
FontSelect.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
FontSelect.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
FontSelect.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
FontSelect.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
FontSelect.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
FontSelect.o: /usr/include/string.h /usr/dt/include/X11/Core.h
FontSelect.o: /usr/dt/include/X11/Composite.h
FontSelect.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
FontSelect.o: /usr/dt/include/X11/RectObj.h ../lac/LicView.h
FontSelect.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
FontSelect.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
FontSelect.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
FontSelect.o: /usr/dt/include/Xm/VendorS.h ../lac/View.h ../lac/Lobject.h
FontSelect.o: /usr/include/stdio.h ../lac/RefArray.h ../lac/Ref.h
FontSelect.o: ../lac/Rec.h ../lac/WidgetRef.h ../lac/TArray.h
FontSelect.o: /usr/include/stdlib.h /usr/include/limits.h
FontSelect.o: ../../include/X11/xpm.h LresEditor.h /usr/dt/include/Xm/Text.h
FontSelect.o: Lwidget.h /usr/dt/include/X11/IntrinsicP.h
FontSelect.o: /usr/dt/include/X11/CoreP.h /usr/dt/include/X11/CompositeP.h
FontSelect.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
FontSelect.o: /usr/dt/include/X11/RectObjP.h ../lac/IconView.h ../lac/Model.h
FontSelect.o: ../lac/CallbackMethod.h ../lac/SensitiveView.h
FontSelect.o: ../lac/Controller.h ../lac/Lstring.h
FontSelect.o: /usr/dt/include/Xm/AtomMgr.h /usr/dt/include/Xm/DragDrop.h
FontSelect.o: /usr/dt/include/Xm/DragC.h /usr/dt/include/Xm/Display.h
FontSelect.o: /usr/dt/include/Xm/DropSMgr.h /usr/dt/include/Xm/DragIcon.h
FontSelect.o: /usr/dt/include/Xm/DropTrans.h /usr/dt/include/Xm/DragOverS.h
FontSelect.o: /usr/dt/include/Xm/Screen.h ../lac/ConModel.h ../lac/TreeNode.h
FontSelect.o: ../lac/TreeView.h ../lac/HelpNode.h ../parse/parse.h Lproject.h
FontSelect.o: ../lac/MLXHelp.h ../lac/MLXHelp_base.h
FontSelect.o: /usr/dt/include/Xm/TextOutP.h /usr/dt/include/Xm/XmP.h
FontSelect.o: /usr/dt/include/Xm/BaseClassP.h LApp.h Ltmpl.h Lproperty.h
FontSelect.o: Lresource.h ../lac/LHashDictionary.h Lcreator.h
FontSelect.o: ../vdxlib/LClassInfo.h lic.h lic_msg.h lic_hlp.h
FontSelect.o: ../lac/MsgCat.h /usr/dt/include/Xm/List.h
FontSelect.o: /usr/dt/include/Xm/PushB.h
FontSelect_base.o: FontSelect_base.h /usr/dt/include/X11/Intrinsic.h
FontSelect_base.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
FontSelect_base.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
FontSelect_base.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
FontSelect_base.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
FontSelect_base.o: /usr/dt/include/X11/Xutil.h
FontSelect_base.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
FontSelect_base.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
FontSelect_base.o: /usr/dt/include/X11/Constraint.h
FontSelect_base.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
FontSelect_base.o: ../lac/LicView.h /usr/dt/include/Xm/Xm.h
FontSelect_base.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
FontSelect_base.o: /usr/dt/include/Xm/XmStrDefs.h
FontSelect_base.o: /usr/dt/include/X11/StringDefs.h
FontSelect_base.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
FontSelect_base.o: ../lac/View.h ../lac/Lobject.h /usr/include/stdio.h
FontSelect_base.o: ../lac/RefArray.h ../lac/Ref.h ../lac/Rec.h
FontSelect_base.o: ../lac/WidgetRef.h ../lac/TArray.h /usr/include/stdlib.h
FontSelect_base.o: /usr/include/limits.h ../../include/X11/xpm.h
FontSelect_base.o: /usr/dt/include/Xm/Frame.h ../lwid/CellTable.h
FontSelect_base.o: /usr/dt/include/Xm/RowColumn.h /usr/dt/include/Xm/PushB.h
FontSelect_base.o: /usr/dt/include/Xm/ScrolledW.h /usr/dt/include/Xm/List.h
FontSelect_base.o: /usr/dt/include/Xm/Text.h /usr/dt/include/Xm/Separator.h
FontSelect_base.o: ../lwid/ButtonBox.h /usr/dt/include/Xm/Label.h
ColorSelect.o: ColorSelect.h ColorSelect_base.h
ColorSelect.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
ColorSelect.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
ColorSelect.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
ColorSelect.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
ColorSelect.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
ColorSelect.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
ColorSelect.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
ColorSelect.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
ColorSelect.o: /usr/dt/include/X11/RectObj.h ../lac/LicView.h
ColorSelect.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
ColorSelect.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
ColorSelect.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
ColorSelect.o: /usr/dt/include/Xm/VendorS.h ../lac/View.h ../lac/Lobject.h
ColorSelect.o: /usr/include/stdio.h ../lac/RefArray.h ../lac/Ref.h
ColorSelect.o: ../lac/Rec.h ../lac/WidgetRef.h ../lac/TArray.h
ColorSelect.o: /usr/include/stdlib.h /usr/include/limits.h
ColorSelect.o: ../../include/X11/xpm.h ../lac/Lstring.h LresEditor.h
ColorSelect.o: /usr/dt/include/Xm/Text.h Lwidget.h
ColorSelect.o: /usr/dt/include/X11/IntrinsicP.h /usr/dt/include/X11/CoreP.h
ColorSelect.o: /usr/dt/include/X11/CompositeP.h
ColorSelect.o: /usr/dt/include/X11/ConstrainP.h /usr/dt/include/X11/ObjectP.h
ColorSelect.o: /usr/dt/include/X11/RectObjP.h ../lac/IconView.h
ColorSelect.o: ../lac/Model.h ../lac/CallbackMethod.h ../lac/SensitiveView.h
ColorSelect.o: ../lac/Controller.h /usr/dt/include/Xm/AtomMgr.h
ColorSelect.o: /usr/dt/include/Xm/DragDrop.h /usr/dt/include/Xm/DragC.h
ColorSelect.o: /usr/dt/include/Xm/Display.h /usr/dt/include/Xm/DropSMgr.h
ColorSelect.o: /usr/dt/include/Xm/DragIcon.h /usr/dt/include/Xm/DropTrans.h
ColorSelect.o: /usr/dt/include/Xm/DragOverS.h /usr/dt/include/Xm/Screen.h
ColorSelect.o: ../lac/ConModel.h ../lac/TreeNode.h ../lac/TreeView.h
ColorSelect.o: ../lac/HelpNode.h ../parse/parse.h Lproject.h ../lac/MLXHelp.h
ColorSelect.o: ../lac/MLXHelp_base.h /usr/dt/include/Xm/TextOutP.h
ColorSelect.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/Xm/BaseClassP.h
ColorSelect.o: LApp.h Ltmpl.h Lproperty.h Lresource.h
ColorSelect.o: ../lac/LHashDictionary.h Lcreator.h ../vdxlib/LClassInfo.h
ColorSelect.o: lic.h lic_msg.h lic_hlp.h ../lac/MsgCat.h
ColorSelect.o: /usr/dt/include/Xm/Scale.h /usr/dt/include/Xm/List.h
ColorSelect.o: /usr/include/ctype.h
ColorSelect_base.o: ColorSelect_base.h /usr/dt/include/X11/Intrinsic.h
ColorSelect_base.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
ColorSelect_base.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
ColorSelect_base.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
ColorSelect_base.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
ColorSelect_base.o: /usr/dt/include/X11/Xutil.h
ColorSelect_base.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
ColorSelect_base.o: /usr/dt/include/X11/Core.h
ColorSelect_base.o: /usr/dt/include/X11/Composite.h
ColorSelect_base.o: /usr/dt/include/X11/Constraint.h
ColorSelect_base.o: /usr/dt/include/X11/Object.h
ColorSelect_base.o: /usr/dt/include/X11/RectObj.h ../lac/LicView.h
ColorSelect_base.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
ColorSelect_base.o: /usr/dt/include/X11/Xatom.h
ColorSelect_base.o: /usr/dt/include/Xm/XmStrDefs.h
ColorSelect_base.o: /usr/dt/include/X11/StringDefs.h
ColorSelect_base.o: /usr/dt/include/Xm/VirtKeys.h
ColorSelect_base.o: /usr/dt/include/Xm/VendorS.h ../lac/View.h
ColorSelect_base.o: ../lac/Lobject.h /usr/include/stdio.h ../lac/RefArray.h
ColorSelect_base.o: ../lac/Ref.h ../lac/Rec.h ../lac/WidgetRef.h
ColorSelect_base.o: ../lac/TArray.h /usr/include/stdlib.h
ColorSelect_base.o: /usr/include/limits.h ../../include/X11/xpm.h
ColorSelect_base.o: /usr/dt/include/Xm/Frame.h /usr/dt/include/Xm/Form.h
ColorSelect_base.o: /usr/dt/include/Xm/BulletinB.h /usr/dt/include/Xm/Text.h
ColorSelect_base.o: /usr/dt/include/Xm/Separator.h /usr/dt/include/Xm/Label.h
ColorSelect_base.o: /usr/dt/include/Xm/RowColumn.h /usr/dt/include/Xm/Scale.h
ColorSelect_base.o: ../lwid/ButtonBox.h /usr/dt/include/Xm/PushB.h
ColorSelect_base.o: /usr/dt/include/Xm/ScrolledW.h /usr/dt/include/Xm/List.h
TextEdit.o: /usr/dt/include/Xm/Text.h /usr/dt/include/Xm/Xm.h
TextEdit.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
TextEdit.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
TextEdit.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
TextEdit.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
TextEdit.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
TextEdit.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
TextEdit.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
TextEdit.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
TextEdit.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/Shell.h
TextEdit.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
TextEdit.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
TextEdit.o: /usr/dt/include/Xm/VendorS.h /usr/include/stdio.h
TextEdit.o: /usr/dt/include/Xm/ToggleB.h lic.h lic_msg.h lic_hlp.h
TextEdit.o: ../lac/MsgCat.h ../lac/Lobject.h TextEdit.h TextEdit_base.h
TextEdit.o: ../lac/LicView.h ../lac/View.h ../lac/RefArray.h ../lac/Ref.h
TextEdit.o: ../lac/Rec.h ../lac/WidgetRef.h ../lac/TArray.h
TextEdit.o: /usr/include/stdlib.h /usr/include/limits.h
TextEdit.o: ../../include/X11/xpm.h LresEditor.h Lwidget.h
TextEdit.o: /usr/dt/include/X11/IntrinsicP.h /usr/dt/include/X11/CoreP.h
TextEdit.o: /usr/dt/include/X11/CompositeP.h /usr/dt/include/X11/ConstrainP.h
TextEdit.o: /usr/dt/include/X11/ObjectP.h /usr/dt/include/X11/RectObjP.h
TextEdit.o: ../lac/IconView.h ../lac/Model.h ../lac/CallbackMethod.h
TextEdit.o: ../lac/SensitiveView.h ../lac/Controller.h ../lac/Lstring.h
TextEdit.o: /usr/dt/include/Xm/AtomMgr.h /usr/dt/include/Xm/DragDrop.h
TextEdit.o: /usr/dt/include/Xm/DragC.h /usr/dt/include/Xm/Display.h
TextEdit.o: /usr/dt/include/Xm/DropSMgr.h /usr/dt/include/Xm/DragIcon.h
TextEdit.o: /usr/dt/include/Xm/DropTrans.h /usr/dt/include/Xm/DragOverS.h
TextEdit.o: /usr/dt/include/Xm/Screen.h ../lac/ConModel.h ../lac/TreeNode.h
TextEdit.o: ../lac/TreeView.h ../lac/HelpNode.h ../parse/parse.h Lproject.h
TextEdit.o: ../lac/MLXHelp.h ../lac/MLXHelp_base.h
TextEdit.o: /usr/dt/include/Xm/TextOutP.h /usr/dt/include/Xm/XmP.h
TextEdit.o: /usr/dt/include/Xm/BaseClassP.h LApp.h Ltmpl.h Lproperty.h
TextEdit.o: Lresource.h ../lac/LHashDictionary.h Lcreator.h
TextEdit.o: ../vdxlib/LClassInfo.h
TextEdit_base.o: TextEdit_base.h /usr/dt/include/X11/Intrinsic.h
TextEdit_base.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
TextEdit_base.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
TextEdit_base.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
TextEdit_base.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
TextEdit_base.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
TextEdit_base.o: /usr/include/string.h /usr/dt/include/X11/Core.h
TextEdit_base.o: /usr/dt/include/X11/Composite.h
TextEdit_base.o: /usr/dt/include/X11/Constraint.h
TextEdit_base.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
TextEdit_base.o: ../lac/LicView.h /usr/dt/include/Xm/Xm.h
TextEdit_base.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
TextEdit_base.o: /usr/dt/include/Xm/XmStrDefs.h
TextEdit_base.o: /usr/dt/include/X11/StringDefs.h
TextEdit_base.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
TextEdit_base.o: ../lac/View.h ../lac/Lobject.h /usr/include/stdio.h
TextEdit_base.o: ../lac/RefArray.h ../lac/Ref.h ../lac/Rec.h
TextEdit_base.o: ../lac/WidgetRef.h ../lac/TArray.h /usr/include/stdlib.h
TextEdit_base.o: /usr/include/limits.h ../../include/X11/xpm.h
TextEdit_base.o: /usr/dt/include/Xm/Frame.h /usr/dt/include/Xm/Form.h
TextEdit_base.o: /usr/dt/include/Xm/BulletinB.h
TextEdit_base.o: /usr/dt/include/Xm/RowColumn.h /usr/dt/include/Xm/CascadeB.h
TextEdit_base.o: /usr/dt/include/Xm/PushB.h /usr/dt/include/Xm/Separator.h
TextEdit_base.o: /usr/dt/include/Xm/FileSB.h /usr/dt/include/Xm/ScrolledW.h
TextEdit_base.o: /usr/dt/include/Xm/Text.h /usr/dt/include/Xm/Label.h
Converter.o: Converter.h /usr/dt/include/X11/Intrinsic.h
Converter.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
Converter.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
Converter.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
Converter.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
Converter.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
Converter.o: /usr/include/string.h /usr/dt/include/X11/Core.h
Converter.o: /usr/dt/include/X11/Composite.h /usr/dt/include/X11/Constraint.h
Converter.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
Converter.o: /usr/include/stdio.h /usr/dt/include/X11/StringDefs.h
WidgetPalette.o: WidgetPalette.h WidgetPalette_base.h
WidgetPalette.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
WidgetPalette.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
WidgetPalette.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
WidgetPalette.o: /usr/dt/include/X11/Xfuncproto.h
WidgetPalette.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
WidgetPalette.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
WidgetPalette.o: /usr/include/string.h /usr/dt/include/X11/Core.h
WidgetPalette.o: /usr/dt/include/X11/Composite.h
WidgetPalette.o: /usr/dt/include/X11/Constraint.h
WidgetPalette.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
WidgetPalette.o: ../lac/LicView.h /usr/dt/include/Xm/Xm.h
WidgetPalette.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
WidgetPalette.o: /usr/dt/include/Xm/XmStrDefs.h
WidgetPalette.o: /usr/dt/include/X11/StringDefs.h
WidgetPalette.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
WidgetPalette.o: ../lac/View.h ../lac/Lobject.h /usr/include/stdio.h
WidgetPalette.o: ../lac/RefArray.h ../lac/Ref.h ../lac/Rec.h
WidgetPalette.o: ../lac/WidgetRef.h ../lac/TArray.h /usr/include/stdlib.h
WidgetPalette.o: /usr/include/limits.h ../../include/X11/xpm.h
WidgetPalette.o: ../lac/IconView.h ../lac/Model.h ../lac/CallbackMethod.h
WidgetPalette.o: ../lac/SensitiveView.h ../lac/Controller.h ../lac/Lstring.h
WidgetPalette.o: /usr/dt/include/Xm/AtomMgr.h /usr/dt/include/Xm/DragDrop.h
WidgetPalette.o: /usr/dt/include/Xm/DragC.h /usr/dt/include/Xm/Display.h
WidgetPalette.o: /usr/dt/include/Xm/DropSMgr.h /usr/dt/include/Xm/DragIcon.h
WidgetPalette.o: /usr/dt/include/Xm/DropTrans.h
WidgetPalette.o: /usr/dt/include/Xm/DragOverS.h /usr/dt/include/Xm/Screen.h
WidgetPalette.o: ../lac/ConModel.h Lcreator.h
WidgetPalette.o: /usr/dt/include/X11/IntrinsicP.h /usr/dt/include/X11/CoreP.h
WidgetPalette.o: /usr/dt/include/X11/CompositeP.h
WidgetPalette.o: /usr/dt/include/X11/ConstrainP.h
WidgetPalette.o: /usr/dt/include/X11/ObjectP.h /usr/dt/include/X11/RectObjP.h
WidgetPalette.o: ../vdxlib/LClassInfo.h ../lac/LHashDictionary.h
WidgetPalette.o: /usr/dt/include/Xm/ToggleB.h lic_hlp.h LApp.h
WidgetPalette.o: ../parse/parse.h
WidgetPalette_base.o: WidgetPalette_base.h /usr/dt/include/X11/Intrinsic.h
WidgetPalette_base.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
WidgetPalette_base.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
WidgetPalette_base.o: /usr/dt/include/X11/X.h
WidgetPalette_base.o: /usr/dt/include/X11/Xfuncproto.h
WidgetPalette_base.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
WidgetPalette_base.o: /usr/dt/include/X11/Xutil.h
WidgetPalette_base.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
WidgetPalette_base.o: /usr/dt/include/X11/Core.h
WidgetPalette_base.o: /usr/dt/include/X11/Composite.h
WidgetPalette_base.o: /usr/dt/include/X11/Constraint.h
WidgetPalette_base.o: /usr/dt/include/X11/Object.h
WidgetPalette_base.o: /usr/dt/include/X11/RectObj.h ../lac/LicView.h
WidgetPalette_base.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
WidgetPalette_base.o: /usr/dt/include/X11/Xatom.h
WidgetPalette_base.o: /usr/dt/include/Xm/XmStrDefs.h
WidgetPalette_base.o: /usr/dt/include/X11/StringDefs.h
WidgetPalette_base.o: /usr/dt/include/Xm/VirtKeys.h
WidgetPalette_base.o: /usr/dt/include/Xm/VendorS.h ../lac/View.h
WidgetPalette_base.o: ../lac/Lobject.h /usr/include/stdio.h ../lac/RefArray.h
WidgetPalette_base.o: ../lac/Ref.h ../lac/Rec.h ../lac/WidgetRef.h
WidgetPalette_base.o: ../lac/TArray.h /usr/include/stdlib.h
WidgetPalette_base.o: /usr/include/limits.h ../../include/X11/xpm.h
WidgetPalette_base.o: /usr/dt/include/Xm/Frame.h /usr/dt/include/Xm/Form.h
WidgetPalette_base.o: /usr/dt/include/Xm/BulletinB.h
WidgetPalette_base.o: /usr/dt/include/Xm/Label.h
WidgetPalette_base.o: /usr/dt/include/Xm/RowColumn.h
WidgetPalette_base.o: /usr/dt/include/Xm/CascadeB.h
WidgetPalette_base.o: /usr/dt/include/Xm/PushB.h /usr/dt/include/Xm/ToggleB.h
WidgetPalette_base.o: /usr/dt/include/Xm/Separator.h
WidgetPalette_base.o: /usr/dt/include/Xm/ScrollBar.h
WidgetPalette_base.o: /usr/dt/include/Xm/PanedW.h
AgreeWindow.o: AgreeWindow.h AgreeWindow_base.h
AgreeWindow.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
AgreeWindow.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
AgreeWindow.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
AgreeWindow.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
AgreeWindow.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
AgreeWindow.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
AgreeWindow.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
AgreeWindow.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
AgreeWindow.o: /usr/dt/include/X11/RectObj.h ../lac/LicView.h
AgreeWindow.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
AgreeWindow.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
AgreeWindow.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
AgreeWindow.o: /usr/dt/include/Xm/VendorS.h ../lac/View.h ../lac/Lobject.h
AgreeWindow.o: /usr/include/stdio.h ../lac/RefArray.h ../lac/Ref.h
AgreeWindow.o: ../lac/Rec.h ../lac/WidgetRef.h ../lac/TArray.h
AgreeWindow.o: /usr/include/stdlib.h /usr/include/limits.h
AgreeWindow.o: ../../include/X11/xpm.h lic.h lic_msg.h lic_hlp.h
AgreeWindow.o: ../lac/MsgCat.h LApp.h ../lac/Model.h ../lac/CallbackMethod.h
AgreeWindow.o: ../lac/IconView.h ../lac/SensitiveView.h ../lac/Controller.h
AgreeWindow.o: ../lac/Lstring.h /usr/dt/include/Xm/AtomMgr.h
AgreeWindow.o: /usr/dt/include/Xm/DragDrop.h /usr/dt/include/Xm/DragC.h
AgreeWindow.o: /usr/dt/include/Xm/Display.h /usr/dt/include/Xm/DropSMgr.h
AgreeWindow.o: /usr/dt/include/Xm/DragIcon.h /usr/dt/include/Xm/DropTrans.h
AgreeWindow.o: /usr/dt/include/Xm/DragOverS.h /usr/dt/include/Xm/Screen.h
AgreeWindow.o: ../lac/ConModel.h ../parse/parse.h /usr/dt/include/Xm/Text.h
AgreeWindow.o: ../lac/HelpNode.h ../lac/TreeNode.h
AgreeWindow_base.o: AgreeWindow_base.h /usr/dt/include/X11/Intrinsic.h
AgreeWindow_base.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
AgreeWindow_base.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
AgreeWindow_base.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
AgreeWindow_base.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
AgreeWindow_base.o: /usr/dt/include/X11/Xutil.h
AgreeWindow_base.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
AgreeWindow_base.o: /usr/dt/include/X11/Core.h
AgreeWindow_base.o: /usr/dt/include/X11/Composite.h
AgreeWindow_base.o: /usr/dt/include/X11/Constraint.h
AgreeWindow_base.o: /usr/dt/include/X11/Object.h
AgreeWindow_base.o: /usr/dt/include/X11/RectObj.h ../lac/LicView.h
AgreeWindow_base.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
AgreeWindow_base.o: /usr/dt/include/X11/Xatom.h
AgreeWindow_base.o: /usr/dt/include/Xm/XmStrDefs.h
AgreeWindow_base.o: /usr/dt/include/X11/StringDefs.h
AgreeWindow_base.o: /usr/dt/include/Xm/VirtKeys.h
AgreeWindow_base.o: /usr/dt/include/Xm/VendorS.h ../lac/View.h
AgreeWindow_base.o: ../lac/Lobject.h /usr/include/stdio.h ../lac/RefArray.h
AgreeWindow_base.o: ../lac/Ref.h ../lac/Rec.h ../lac/WidgetRef.h
AgreeWindow_base.o: ../lac/TArray.h /usr/include/stdlib.h
AgreeWindow_base.o: /usr/include/limits.h ../../include/X11/xpm.h
AgreeWindow_base.o: /usr/dt/include/Xm/Frame.h /usr/dt/include/Xm/Form.h
AgreeWindow_base.o: /usr/dt/include/Xm/BulletinB.h
AgreeWindow_base.o: /usr/dt/include/Xm/ScrolledW.h /usr/dt/include/Xm/Text.h
AgreeWindow_base.o: /usr/dt/include/Xm/Label.h /usr/dt/include/Xm/PushB.h
WidBrowseView.o: WidBrowseView.h WidBrowseView_base.h
WidBrowseView.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
WidBrowseView.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
WidBrowseView.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
WidBrowseView.o: /usr/dt/include/X11/Xfuncproto.h
WidBrowseView.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
WidBrowseView.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
WidBrowseView.o: /usr/include/string.h /usr/dt/include/X11/Core.h
WidBrowseView.o: /usr/dt/include/X11/Composite.h
WidBrowseView.o: /usr/dt/include/X11/Constraint.h
WidBrowseView.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
WidBrowseView.o: ../lac/LicView.h /usr/dt/include/Xm/Xm.h
WidBrowseView.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
WidBrowseView.o: /usr/dt/include/Xm/XmStrDefs.h
WidBrowseView.o: /usr/dt/include/X11/StringDefs.h
WidBrowseView.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
WidBrowseView.o: ../lac/View.h ../lac/Lobject.h /usr/include/stdio.h
WidBrowseView.o: ../lac/RefArray.h ../lac/Ref.h ../lac/Rec.h
WidBrowseView.o: ../lac/WidgetRef.h ../lac/TArray.h /usr/include/stdlib.h
WidBrowseView.o: /usr/include/limits.h ../../include/X11/xpm.h
WidBrowseView.o: ControllerImpl.h WidClassMenu.h Lcreator.h
WidBrowseView.o: /usr/dt/include/X11/IntrinsicP.h /usr/dt/include/X11/CoreP.h
WidBrowseView.o: /usr/dt/include/X11/CompositeP.h
WidBrowseView.o: /usr/dt/include/X11/ConstrainP.h
WidBrowseView.o: /usr/dt/include/X11/ObjectP.h /usr/dt/include/X11/RectObjP.h
WidBrowseView.o: ../lac/IconView.h ../lac/Model.h ../lac/CallbackMethod.h
WidBrowseView.o: ../lac/SensitiveView.h ../lac/Controller.h ../lac/Lstring.h
WidBrowseView.o: /usr/dt/include/Xm/AtomMgr.h /usr/dt/include/Xm/DragDrop.h
WidBrowseView.o: /usr/dt/include/Xm/DragC.h /usr/dt/include/Xm/Display.h
WidBrowseView.o: /usr/dt/include/Xm/DropSMgr.h /usr/dt/include/Xm/DragIcon.h
WidBrowseView.o: /usr/dt/include/Xm/DropTrans.h
WidBrowseView.o: /usr/dt/include/Xm/DragOverS.h /usr/dt/include/Xm/Screen.h
WidBrowseView.o: ../lac/ConModel.h ../vdxlib/LClassInfo.h
WidBrowseView.o: ../lac/LHashDictionary.h Lwidget.h ../lac/TreeNode.h
WidBrowseView.o: ../lac/TreeView.h ../lac/HelpNode.h ../parse/parse.h
WidBrowseView.o: Lproject.h ../lac/MLXHelp.h ../lac/MLXHelp_base.h
WidBrowseView.o: /usr/dt/include/Xm/TextOutP.h /usr/dt/include/Xm/XmP.h
WidBrowseView.o: /usr/dt/include/Xm/BaseClassP.h /usr/dt/include/Xm/Text.h
WidBrowseView.o: LApp.h Ltmpl.h Lproperty.h Lresource.h lic.h lic_msg.h
WidBrowseView.o: lic_hlp.h ../lac/MsgCat.h Lwhere.h /usr/include/ctype.h
WidBrowseView.o: /usr/dt/include/Xm/ToggleB.h
WidBrowseView_base.o: WidBrowseView_base.h /usr/dt/include/X11/Intrinsic.h
WidBrowseView_base.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
WidBrowseView_base.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
WidBrowseView_base.o: /usr/dt/include/X11/X.h
WidBrowseView_base.o: /usr/dt/include/X11/Xfuncproto.h
WidBrowseView_base.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
WidBrowseView_base.o: /usr/dt/include/X11/Xutil.h
WidBrowseView_base.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
WidBrowseView_base.o: /usr/dt/include/X11/Core.h
WidBrowseView_base.o: /usr/dt/include/X11/Composite.h
WidBrowseView_base.o: /usr/dt/include/X11/Constraint.h
WidBrowseView_base.o: /usr/dt/include/X11/Object.h
WidBrowseView_base.o: /usr/dt/include/X11/RectObj.h ../lac/LicView.h
WidBrowseView_base.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
WidBrowseView_base.o: /usr/dt/include/X11/Xatom.h
WidBrowseView_base.o: /usr/dt/include/Xm/XmStrDefs.h
WidBrowseView_base.o: /usr/dt/include/X11/StringDefs.h
WidBrowseView_base.o: /usr/dt/include/Xm/VirtKeys.h
WidBrowseView_base.o: /usr/dt/include/Xm/VendorS.h ../lac/View.h
WidBrowseView_base.o: ../lac/Lobject.h /usr/include/stdio.h ../lac/RefArray.h
WidBrowseView_base.o: ../lac/Ref.h ../lac/Rec.h ../lac/WidgetRef.h
WidBrowseView_base.o: ../lac/TArray.h /usr/include/stdlib.h
WidBrowseView_base.o: /usr/include/limits.h ../../include/X11/xpm.h
WidBrowseView_base.o: /usr/dt/include/Xm/Frame.h /usr/dt/include/Xm/MainW.h
WidBrowseView_base.o: /usr/dt/include/Xm/RowColumn.h
WidBrowseView_base.o: /usr/dt/include/Xm/CascadeB.h
WidBrowseView_base.o: /usr/dt/include/Xm/PushB.h /usr/dt/include/Xm/ToggleB.h
WidBrowseView_base.o: /usr/dt/include/Xm/Separator.h
WidBrowseView_base.o: /usr/dt/include/Xm/Form.h
WidBrowseView_base.o: /usr/dt/include/Xm/BulletinB.h
WidBrowseView_base.o: /usr/dt/include/Xm/Label.h
WidResEditor.o: WidResEditor.h WidResEditor_base.h
WidResEditor.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
WidResEditor.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
WidResEditor.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
WidResEditor.o: /usr/dt/include/X11/Xfuncproto.h
WidResEditor.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
WidResEditor.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
WidResEditor.o: /usr/include/string.h /usr/dt/include/X11/Core.h
WidResEditor.o: /usr/dt/include/X11/Composite.h
WidResEditor.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
WidResEditor.o: /usr/dt/include/X11/RectObj.h ../lac/LicView.h
WidResEditor.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
WidResEditor.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
WidResEditor.o: /usr/dt/include/X11/StringDefs.h
WidResEditor.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
WidResEditor.o: ../lac/View.h ../lac/Lobject.h /usr/include/stdio.h
WidResEditor.o: ../lac/RefArray.h ../lac/Ref.h ../lac/Rec.h
WidResEditor.o: ../lac/WidgetRef.h ../lac/TArray.h /usr/include/stdlib.h
WidResEditor.o: /usr/include/limits.h ../../include/X11/xpm.h
WidResEditor.o: ../lac/CallbackMethod.h Lwidget.h
WidResEditor.o: /usr/dt/include/X11/IntrinsicP.h /usr/dt/include/X11/CoreP.h
WidResEditor.o: /usr/dt/include/X11/CompositeP.h
WidResEditor.o: /usr/dt/include/X11/ConstrainP.h
WidResEditor.o: /usr/dt/include/X11/ObjectP.h /usr/dt/include/X11/RectObjP.h
WidResEditor.o: ../lac/IconView.h ../lac/Model.h ../lac/SensitiveView.h
WidResEditor.o: ../lac/Controller.h ../lac/Lstring.h
WidResEditor.o: /usr/dt/include/Xm/AtomMgr.h /usr/dt/include/Xm/DragDrop.h
WidResEditor.o: /usr/dt/include/Xm/DragC.h /usr/dt/include/Xm/Display.h
WidResEditor.o: /usr/dt/include/Xm/DropSMgr.h /usr/dt/include/Xm/DragIcon.h
WidResEditor.o: /usr/dt/include/Xm/DropTrans.h /usr/dt/include/Xm/DragOverS.h
WidResEditor.o: /usr/dt/include/Xm/Screen.h ../lac/ConModel.h
WidResEditor.o: ../lac/TreeNode.h ../lac/TreeView.h ../lac/HelpNode.h
WidResEditor.o: ../parse/parse.h Lproject.h ../lac/MLXHelp.h
WidResEditor.o: ../lac/MLXHelp_base.h /usr/dt/include/Xm/TextOutP.h
WidResEditor.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/Xm/BaseClassP.h
WidResEditor.o: /usr/dt/include/Xm/Text.h LApp.h Ltmpl.h Lproperty.h
WidResEditor.o: Lresource.h ../lac/LHashDictionary.h Lcreator.h
WidResEditor.o: ../vdxlib/LClassInfo.h lic.h lic_msg.h lic_hlp.h
WidResEditor.o: ../lac/MsgCat.h LresEditor.h misc.h
WidResEditor.o: /usr/dt/include/Xm/ToggleB.h ../lwid/CellTable.h
WidResEditor.o: /usr/dt/include/Xm/ScrolledW.h /usr/dt/include/Xm/List.h
WidResEditor.o: /usr/dt/include/Xm/MessageB.h
WidResEditor_base.o: WidResEditor_base.h /usr/dt/include/X11/Intrinsic.h
WidResEditor_base.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
WidResEditor_base.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
WidResEditor_base.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
WidResEditor_base.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
WidResEditor_base.o: /usr/dt/include/X11/Xutil.h
WidResEditor_base.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
WidResEditor_base.o: /usr/dt/include/X11/Core.h
WidResEditor_base.o: /usr/dt/include/X11/Composite.h
WidResEditor_base.o: /usr/dt/include/X11/Constraint.h
WidResEditor_base.o: /usr/dt/include/X11/Object.h
WidResEditor_base.o: /usr/dt/include/X11/RectObj.h ../lac/LicView.h
WidResEditor_base.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
WidResEditor_base.o: /usr/dt/include/X11/Xatom.h
WidResEditor_base.o: /usr/dt/include/Xm/XmStrDefs.h
WidResEditor_base.o: /usr/dt/include/X11/StringDefs.h
WidResEditor_base.o: /usr/dt/include/Xm/VirtKeys.h
WidResEditor_base.o: /usr/dt/include/Xm/VendorS.h ../lac/View.h
WidResEditor_base.o: ../lac/Lobject.h /usr/include/stdio.h ../lac/RefArray.h
WidResEditor_base.o: ../lac/Ref.h ../lac/Rec.h ../lac/WidgetRef.h
WidResEditor_base.o: ../lac/TArray.h /usr/include/stdlib.h
WidResEditor_base.o: /usr/include/limits.h ../../include/X11/xpm.h
WidResEditor_base.o: /usr/dt/include/Xm/Frame.h /usr/dt/include/Xm/MainW.h
WidResEditor_base.o: /usr/dt/include/Xm/RowColumn.h
WidResEditor_base.o: /usr/dt/include/Xm/CascadeB.h /usr/dt/include/Xm/PushB.h
WidResEditor_base.o: /usr/dt/include/Xm/Separator.h
WidResEditor_base.o: /usr/dt/include/Xm/ToggleB.h /usr/dt/include/Xm/Form.h
WidResEditor_base.o: /usr/dt/include/Xm/BulletinB.h ../lwid/ButtonBox.h
WidResEditor_base.o: /usr/dt/include/Xm/ScrolledW.h
WidResEditor_base.o: /usr/dt/include/Xm/Label.h /usr/dt/include/Xm/MessageB.h
WidResEditor_base.o: /usr/dt/include/Xm/List.h
TemplateView.o: TemplateView.h TemplateView_base.h
TemplateView.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
TemplateView.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
TemplateView.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
TemplateView.o: /usr/dt/include/X11/Xfuncproto.h
TemplateView.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
TemplateView.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
TemplateView.o: /usr/include/string.h /usr/dt/include/X11/Core.h
TemplateView.o: /usr/dt/include/X11/Composite.h
TemplateView.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
TemplateView.o: /usr/dt/include/X11/RectObj.h ../lac/LicView.h
TemplateView.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
TemplateView.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
TemplateView.o: /usr/dt/include/X11/StringDefs.h
TemplateView.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
TemplateView.o: ../lac/View.h ../lac/Lobject.h /usr/include/stdio.h
TemplateView.o: ../lac/RefArray.h ../lac/Ref.h ../lac/Rec.h
TemplateView.o: ../lac/WidgetRef.h ../lac/TArray.h /usr/include/stdlib.h
TemplateView.o: /usr/include/limits.h ../../include/X11/xpm.h Lwidget.h
TemplateView.o: /usr/dt/include/X11/IntrinsicP.h /usr/dt/include/X11/CoreP.h
TemplateView.o: /usr/dt/include/X11/CompositeP.h
TemplateView.o: /usr/dt/include/X11/ConstrainP.h
TemplateView.o: /usr/dt/include/X11/ObjectP.h /usr/dt/include/X11/RectObjP.h
TemplateView.o: ../lac/IconView.h ../lac/Model.h ../lac/CallbackMethod.h
TemplateView.o: ../lac/SensitiveView.h ../lac/Controller.h ../lac/Lstring.h
TemplateView.o: /usr/dt/include/Xm/AtomMgr.h /usr/dt/include/Xm/DragDrop.h
TemplateView.o: /usr/dt/include/Xm/DragC.h /usr/dt/include/Xm/Display.h
TemplateView.o: /usr/dt/include/Xm/DropSMgr.h /usr/dt/include/Xm/DragIcon.h
TemplateView.o: /usr/dt/include/Xm/DropTrans.h /usr/dt/include/Xm/DragOverS.h
TemplateView.o: /usr/dt/include/Xm/Screen.h ../lac/ConModel.h
TemplateView.o: ../lac/TreeNode.h ../lac/TreeView.h ../lac/HelpNode.h
TemplateView.o: ../parse/parse.h Lproject.h ../lac/MLXHelp.h
TemplateView.o: ../lac/MLXHelp_base.h /usr/dt/include/Xm/TextOutP.h
TemplateView.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/Xm/BaseClassP.h
TemplateView.o: /usr/dt/include/Xm/Text.h LApp.h Ltmpl.h Lproperty.h
TemplateView.o: Lresource.h ../lac/LHashDictionary.h Lcreator.h
TemplateView.o: ../vdxlib/LClassInfo.h ControllerImpl.h Lpalette.h lic.h
TemplateView.o: lic_msg.h lic_hlp.h ../lac/MsgCat.h Lwhere.h
TemplateView.o: /usr/dt/include/Xm/ToggleB.h /usr/include/unistd.h
TemplateView.o: /usr/include/sys/unistd.h
TemplateView_base.o: TemplateView_base.h /usr/dt/include/X11/Intrinsic.h
TemplateView_base.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
TemplateView_base.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
TemplateView_base.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
TemplateView_base.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
TemplateView_base.o: /usr/dt/include/X11/Xutil.h
TemplateView_base.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
TemplateView_base.o: /usr/dt/include/X11/Core.h
TemplateView_base.o: /usr/dt/include/X11/Composite.h
TemplateView_base.o: /usr/dt/include/X11/Constraint.h
TemplateView_base.o: /usr/dt/include/X11/Object.h
TemplateView_base.o: /usr/dt/include/X11/RectObj.h ../lac/LicView.h
TemplateView_base.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
TemplateView_base.o: /usr/dt/include/X11/Xatom.h
TemplateView_base.o: /usr/dt/include/Xm/XmStrDefs.h
TemplateView_base.o: /usr/dt/include/X11/StringDefs.h
TemplateView_base.o: /usr/dt/include/Xm/VirtKeys.h
TemplateView_base.o: /usr/dt/include/Xm/VendorS.h ../lac/View.h
TemplateView_base.o: ../lac/Lobject.h /usr/include/stdio.h ../lac/RefArray.h
TemplateView_base.o: ../lac/Ref.h ../lac/Rec.h ../lac/WidgetRef.h
TemplateView_base.o: ../lac/TArray.h /usr/include/stdlib.h
TemplateView_base.o: /usr/include/limits.h ../../include/X11/xpm.h
TemplateView_base.o: /usr/dt/include/Xm/Frame.h /usr/dt/include/Xm/MainW.h
TemplateView_base.o: /usr/dt/include/Xm/RowColumn.h
TemplateView_base.o: /usr/dt/include/Xm/CascadeB.h /usr/dt/include/Xm/PushB.h
TemplateView_base.o: /usr/dt/include/Xm/ToggleB.h
TemplateView_base.o: /usr/dt/include/Xm/Separator.h /usr/dt/include/Xm/Form.h
TemplateView_base.o: /usr/dt/include/Xm/BulletinB.h
TemplateView_base.o: /usr/dt/include/Xm/Label.h /usr/dt/include/Xm/FileSB.h
ProjectSettings.o: ProjectSettings.h ProjectSettings_base.h
ProjectSettings.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
ProjectSettings.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
ProjectSettings.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
ProjectSettings.o: /usr/dt/include/X11/Xfuncproto.h
ProjectSettings.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
ProjectSettings.o: /usr/dt/include/X11/Xutil.h
ProjectSettings.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
ProjectSettings.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
ProjectSettings.o: /usr/dt/include/X11/Constraint.h
ProjectSettings.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
ProjectSettings.o: ../lac/LicView.h /usr/dt/include/Xm/Xm.h
ProjectSettings.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
ProjectSettings.o: /usr/dt/include/Xm/XmStrDefs.h
ProjectSettings.o: /usr/dt/include/X11/StringDefs.h
ProjectSettings.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
ProjectSettings.o: ../lac/View.h ../lac/Lobject.h /usr/include/stdio.h
ProjectSettings.o: ../lac/RefArray.h ../lac/Ref.h ../lac/Rec.h
ProjectSettings.o: ../lac/WidgetRef.h ../lac/TArray.h /usr/include/stdlib.h
ProjectSettings.o: /usr/include/limits.h ../../include/X11/xpm.h
ProjectSettings.o: ../lac/Lstring.h ../lac/OptionMenuView.h ../lac/ConModel.h
ProjectSettings.o: ../lac/Model.h ../lac/CallbackMethod.h Lproject.h
ProjectSettings.o: /usr/dt/include/X11/IntrinsicP.h
ProjectSettings.o: /usr/dt/include/X11/CoreP.h
ProjectSettings.o: /usr/dt/include/X11/CompositeP.h
ProjectSettings.o: /usr/dt/include/X11/ConstrainP.h
ProjectSettings.o: /usr/dt/include/X11/ObjectP.h
ProjectSettings.o: /usr/dt/include/X11/RectObjP.h ../lac/IconView.h
ProjectSettings.o: ../lac/SensitiveView.h ../lac/Controller.h
ProjectSettings.o: /usr/dt/include/Xm/AtomMgr.h /usr/dt/include/Xm/DragDrop.h
ProjectSettings.o: /usr/dt/include/Xm/DragC.h /usr/dt/include/Xm/Display.h
ProjectSettings.o: /usr/dt/include/Xm/DropSMgr.h
ProjectSettings.o: /usr/dt/include/Xm/DragIcon.h
ProjectSettings.o: /usr/dt/include/Xm/DropTrans.h
ProjectSettings.o: /usr/dt/include/Xm/DragOverS.h /usr/dt/include/Xm/Screen.h
ProjectSettings.o: ../parse/parse.h ../lac/MLXHelp.h ../lac/HelpNode.h
ProjectSettings.o: ../lac/TreeNode.h ../lac/MLXHelp_base.h ../lac/TreeView.h
ProjectSettings.o: /usr/dt/include/Xm/TextOutP.h /usr/dt/include/Xm/XmP.h
ProjectSettings.o: /usr/dt/include/Xm/BaseClassP.h /usr/dt/include/Xm/Text.h
ProjectSettings.o: LApp.h Lwidget.h Lproperty.h Lresource.h
ProjectSettings.o: ../lac/LHashDictionary.h Lcreator.h ../vdxlib/LClassInfo.h
ProjectSettings.o: Ltmpl.h lic.h lic_msg.h lic_hlp.h ../lac/MsgCat.h misc.h
ProjectSettings.o: /usr/include/ctype.h /usr/include/dirent.h
ProjectSettings.o: /usr/include/sys/dirent.h /usr/include/sys/stat.h
ProjectSettings.o: /usr/include/sys/_stat_body.h /usr/include/errno.h
ProjectSettings.o: /usr/include/sys/errno.h /usr/dt/include/Xm/PushB.h
ProjectSettings.o: /usr/dt/include/Xm/List.h
ProjectSettings_base.o: ProjectSettings_base.h
ProjectSettings_base.o: /usr/dt/include/X11/Intrinsic.h
ProjectSettings_base.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
ProjectSettings_base.o: /usr/include/sys/_inttypes.h
ProjectSettings_base.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
ProjectSettings_base.o: /usr/dt/include/X11/Xfuncproto.h
ProjectSettings_base.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
ProjectSettings_base.o: /usr/dt/include/X11/Xutil.h
ProjectSettings_base.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
ProjectSettings_base.o: /usr/dt/include/X11/Core.h
ProjectSettings_base.o: /usr/dt/include/X11/Composite.h
ProjectSettings_base.o: /usr/dt/include/X11/Constraint.h
ProjectSettings_base.o: /usr/dt/include/X11/Object.h
ProjectSettings_base.o: /usr/dt/include/X11/RectObj.h ../lac/LicView.h
ProjectSettings_base.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
ProjectSettings_base.o: /usr/dt/include/X11/Xatom.h
ProjectSettings_base.o: /usr/dt/include/Xm/XmStrDefs.h
ProjectSettings_base.o: /usr/dt/include/X11/StringDefs.h
ProjectSettings_base.o: /usr/dt/include/Xm/VirtKeys.h
ProjectSettings_base.o: /usr/dt/include/Xm/VendorS.h ../lac/View.h
ProjectSettings_base.o: ../lac/Lobject.h /usr/include/stdio.h
ProjectSettings_base.o: ../lac/RefArray.h ../lac/Ref.h ../lac/Rec.h
ProjectSettings_base.o: ../lac/WidgetRef.h ../lac/TArray.h
ProjectSettings_base.o: /usr/include/stdlib.h /usr/include/limits.h
ProjectSettings_base.o: ../../include/X11/xpm.h /usr/dt/include/Xm/Frame.h
ProjectSettings_base.o: /usr/dt/include/Xm/Form.h
ProjectSettings_base.o: /usr/dt/include/Xm/BulletinB.h ../lwid/CellTable.h
ProjectSettings_base.o: /usr/dt/include/Xm/Label.h /usr/dt/include/Xm/Text.h
ProjectSettings_base.o: /usr/dt/include/Xm/RowColumn.h
ProjectSettings_base.o: /usr/dt/include/Xm/DrawnB.h
ProjectSettings_base.o: /usr/dt/include/Xm/FileSB.h
ProjectSettings_base.o: /usr/dt/include/Xm/ScrolledW.h
ProjectSettings_base.o: /usr/dt/include/Xm/SelectioB.h
ProjectSettings_base.o: /usr/dt/include/Xm/MessageB.h
ProjectSettings_base.o: /usr/dt/include/Xm/List.h
ProjectSettings_base.o: /usr/dt/include/Xm/Separator.h ../lwid/ButtonBox.h
ProjectSettings_base.o: /usr/dt/include/Xm/PushB.h
ControllerImpl.o: ControllerImpl.h ../lac/RefArray.h ../lac/Ref.h
ControllerImpl.o: ../lac/Lobject.h /usr/include/stdio.h
ControllerImpl.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
ControllerImpl.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/Intrinsic.h
ControllerImpl.o: /usr/dt/include/X11/Xlib.h /usr/dt/include/X11/X.h
ControllerImpl.o: /usr/dt/include/X11/Xfuncproto.h
ControllerImpl.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
ControllerImpl.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
ControllerImpl.o: /usr/include/string.h /usr/dt/include/X11/Core.h
ControllerImpl.o: /usr/dt/include/X11/Composite.h
ControllerImpl.o: /usr/dt/include/X11/Constraint.h
ControllerImpl.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
ControllerImpl.o: ../lac/Controller.h ../lac/Model.h ../lac/TArray.h
ControllerImpl.o: /usr/include/stdlib.h ../lac/CallbackMethod.h ../lac/View.h
ControllerImpl.o: ../lac/Rec.h ../lac/WidgetRef.h /usr/include/limits.h
ControllerImpl.o: ../../include/X11/xpm.h ../lac/Lstring.h
ControllerImpl.o: ../lac/SensitiveView.h /usr/dt/include/Xm/AtomMgr.h
ControllerImpl.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
ControllerImpl.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
ControllerImpl.o: /usr/dt/include/X11/StringDefs.h
ControllerImpl.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
ControllerImpl.o: /usr/dt/include/Xm/DragDrop.h /usr/dt/include/Xm/DragC.h
ControllerImpl.o: /usr/dt/include/Xm/Display.h /usr/dt/include/Xm/DropSMgr.h
ControllerImpl.o: /usr/dt/include/Xm/DragIcon.h
ControllerImpl.o: /usr/dt/include/Xm/DropTrans.h
ControllerImpl.o: /usr/dt/include/Xm/DragOverS.h /usr/dt/include/Xm/Screen.h
MegaPipe.o: /usr/include/unistd.h /usr/include/sys/unistd.h
MegaPipe.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
MegaPipe.o: /usr/include/sys/stdsyms.h /usr/include/stdio.h
MegaPipe.o: /usr/include/stdlib.h /usr/include/string.h /usr/include/errno.h
MegaPipe.o: /usr/include/sys/errno.h /usr/include/signal.h
MegaPipe.o: /usr/include/sys/signal.h /usr/include/sys/sigevent.h
MegaPipe.o: /usr/include/sys/siginfo.h /usr/include/sys/newsig.h
MegaPipe.o: /usr/include/fcntl.h /usr/include/sys/fcntl.h
MegaPipe.o: /usr/include/sys/_flock_body.h /usr/include/sys/time.h
AttachmentEditor.o: AttachmentEditor.h AttachmentEditor_base.h
AttachmentEditor.o: /usr/dt/include/X11/Intrinsic.h
AttachmentEditor.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
AttachmentEditor.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
AttachmentEditor.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
AttachmentEditor.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
AttachmentEditor.o: /usr/dt/include/X11/Xutil.h
AttachmentEditor.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
AttachmentEditor.o: /usr/dt/include/X11/Core.h
AttachmentEditor.o: /usr/dt/include/X11/Composite.h
AttachmentEditor.o: /usr/dt/include/X11/Constraint.h
AttachmentEditor.o: /usr/dt/include/X11/Object.h
AttachmentEditor.o: /usr/dt/include/X11/RectObj.h ../lac/LicView.h
AttachmentEditor.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
AttachmentEditor.o: /usr/dt/include/X11/Xatom.h
AttachmentEditor.o: /usr/dt/include/Xm/XmStrDefs.h
AttachmentEditor.o: /usr/dt/include/X11/StringDefs.h
AttachmentEditor.o: /usr/dt/include/Xm/VirtKeys.h
AttachmentEditor.o: /usr/dt/include/Xm/VendorS.h ../lac/View.h
AttachmentEditor.o: ../lac/Lobject.h /usr/include/stdio.h ../lac/RefArray.h
AttachmentEditor.o: ../lac/Ref.h ../lac/Rec.h ../lac/WidgetRef.h
AttachmentEditor.o: ../lac/TArray.h /usr/include/stdlib.h
AttachmentEditor.o: /usr/include/limits.h ../../include/X11/xpm.h
AttachmentEditor.o: ControllerImpl.h ../lac/CallbackMethod.h
AttachmentEditor.o: ../lac/OptionMenuView.h ../lac/ConModel.h ../lac/Model.h
AttachmentEditor.o: ../lac/Lstring.h Lwidget.h
AttachmentEditor.o: /usr/dt/include/X11/IntrinsicP.h
AttachmentEditor.o: /usr/dt/include/X11/CoreP.h
AttachmentEditor.o: /usr/dt/include/X11/CompositeP.h
AttachmentEditor.o: /usr/dt/include/X11/ConstrainP.h
AttachmentEditor.o: /usr/dt/include/X11/ObjectP.h
AttachmentEditor.o: /usr/dt/include/X11/RectObjP.h ../lac/IconView.h
AttachmentEditor.o: ../lac/SensitiveView.h ../lac/Controller.h
AttachmentEditor.o: /usr/dt/include/Xm/AtomMgr.h
AttachmentEditor.o: /usr/dt/include/Xm/DragDrop.h /usr/dt/include/Xm/DragC.h
AttachmentEditor.o: /usr/dt/include/Xm/Display.h
AttachmentEditor.o: /usr/dt/include/Xm/DropSMgr.h
AttachmentEditor.o: /usr/dt/include/Xm/DragIcon.h
AttachmentEditor.o: /usr/dt/include/Xm/DropTrans.h
AttachmentEditor.o: /usr/dt/include/Xm/DragOverS.h
AttachmentEditor.o: /usr/dt/include/Xm/Screen.h ../lac/TreeNode.h
AttachmentEditor.o: ../lac/TreeView.h ../lac/HelpNode.h ../parse/parse.h
AttachmentEditor.o: Lproject.h ../lac/MLXHelp.h ../lac/MLXHelp_base.h
AttachmentEditor.o: /usr/dt/include/Xm/TextOutP.h /usr/dt/include/Xm/XmP.h
AttachmentEditor.o: /usr/dt/include/Xm/BaseClassP.h /usr/dt/include/Xm/Text.h
AttachmentEditor.o: LApp.h Ltmpl.h Lproperty.h Lresource.h
AttachmentEditor.o: ../lac/LHashDictionary.h Lcreator.h
AttachmentEditor.o: ../vdxlib/LClassInfo.h lic.h lic_msg.h lic_hlp.h
AttachmentEditor.o: ../lac/MsgCat.h /usr/dt/include/Xm/ToggleB.h
AttachmentEditor_base.o: AttachmentEditor_base.h
AttachmentEditor_base.o: /usr/dt/include/X11/Intrinsic.h
AttachmentEditor_base.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
AttachmentEditor_base.o: /usr/include/sys/_inttypes.h
AttachmentEditor_base.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
AttachmentEditor_base.o: /usr/dt/include/X11/Xfuncproto.h
AttachmentEditor_base.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
AttachmentEditor_base.o: /usr/dt/include/X11/Xutil.h
AttachmentEditor_base.o: /usr/dt/include/X11/Xresource.h
AttachmentEditor_base.o: /usr/include/string.h /usr/dt/include/X11/Core.h
AttachmentEditor_base.o: /usr/dt/include/X11/Composite.h
AttachmentEditor_base.o: /usr/dt/include/X11/Constraint.h
AttachmentEditor_base.o: /usr/dt/include/X11/Object.h
AttachmentEditor_base.o: /usr/dt/include/X11/RectObj.h ../lac/LicView.h
AttachmentEditor_base.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
AttachmentEditor_base.o: /usr/dt/include/X11/Xatom.h
AttachmentEditor_base.o: /usr/dt/include/Xm/XmStrDefs.h
AttachmentEditor_base.o: /usr/dt/include/X11/StringDefs.h
AttachmentEditor_base.o: /usr/dt/include/Xm/VirtKeys.h
AttachmentEditor_base.o: /usr/dt/include/Xm/VendorS.h ../lac/View.h
AttachmentEditor_base.o: ../lac/Lobject.h /usr/include/stdio.h
AttachmentEditor_base.o: ../lac/RefArray.h ../lac/Ref.h ../lac/Rec.h
AttachmentEditor_base.o: ../lac/WidgetRef.h ../lac/TArray.h
AttachmentEditor_base.o: /usr/include/stdlib.h /usr/include/limits.h
AttachmentEditor_base.o: ../../include/X11/xpm.h /usr/dt/include/Xm/Frame.h
AttachmentEditor_base.o: /usr/dt/include/Xm/MainW.h
AttachmentEditor_base.o: /usr/dt/include/Xm/RowColumn.h
AttachmentEditor_base.o: /usr/dt/include/Xm/CascadeB.h
AttachmentEditor_base.o: /usr/dt/include/Xm/PushB.h
AttachmentEditor_base.o: /usr/dt/include/Xm/ToggleB.h
AttachmentEditor_base.o: /usr/dt/include/Xm/Separator.h ../lwid/CellTable.h
AttachmentEditor_base.o: /usr/dt/include/Xm/Label.h ../lwid/ButtonBox.h
AttachmentEditor_base.o: /usr/dt/include/Xm/Text.h AttachNone.xpm
AttachmentEditor_base.o: BottomAttachForm.xpm BottomAttachWidget.xpm
AttachmentEditor_base.o: BottomAttachPosition.xpm BottomAttachSelf.xpm
AttachmentEditor_base.o: LeftAttachForm.xpm LeftAttachWidget.xpm
AttachmentEditor_base.o: LeftAttachPosition.xpm LeftAttachSelf.xpm
AttachmentEditor_base.o: RightAttachForm.xpm RightAttachWidget.xpm
AttachmentEditor_base.o: RightAttachPosition.xpm RightAttachSelf.xpm
AttachmentEditor_base.o: TopAttachForm.xpm TopAttachWidget.xpm
AttachmentEditor_base.o: TopAttachPosition.xpm TopAttachSelf.xpm
GlobalResEditor.o: GlobalResEditor.h GlobalResEditor_base.h
GlobalResEditor.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
GlobalResEditor.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
GlobalResEditor.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
GlobalResEditor.o: /usr/dt/include/X11/Xfuncproto.h
GlobalResEditor.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
GlobalResEditor.o: /usr/dt/include/X11/Xutil.h
GlobalResEditor.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
GlobalResEditor.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
GlobalResEditor.o: /usr/dt/include/X11/Constraint.h
GlobalResEditor.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
GlobalResEditor.o: ../lac/LicView.h /usr/dt/include/Xm/Xm.h
GlobalResEditor.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
GlobalResEditor.o: /usr/dt/include/Xm/XmStrDefs.h
GlobalResEditor.o: /usr/dt/include/X11/StringDefs.h
GlobalResEditor.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
GlobalResEditor.o: ../lac/View.h ../lac/Lobject.h /usr/include/stdio.h
GlobalResEditor.o: ../lac/RefArray.h ../lac/Ref.h ../lac/Rec.h
GlobalResEditor.o: ../lac/WidgetRef.h ../lac/TArray.h /usr/include/stdlib.h
GlobalResEditor.o: /usr/include/limits.h ../../include/X11/xpm.h LresEditor.h
GlobalResEditor.o: /usr/dt/include/Xm/Text.h Lwidget.h
GlobalResEditor.o: /usr/dt/include/X11/IntrinsicP.h
GlobalResEditor.o: /usr/dt/include/X11/CoreP.h
GlobalResEditor.o: /usr/dt/include/X11/CompositeP.h
GlobalResEditor.o: /usr/dt/include/X11/ConstrainP.h
GlobalResEditor.o: /usr/dt/include/X11/ObjectP.h
GlobalResEditor.o: /usr/dt/include/X11/RectObjP.h ../lac/IconView.h
GlobalResEditor.o: ../lac/Model.h ../lac/CallbackMethod.h
GlobalResEditor.o: ../lac/SensitiveView.h ../lac/Controller.h
GlobalResEditor.o: ../lac/Lstring.h /usr/dt/include/Xm/AtomMgr.h
GlobalResEditor.o: /usr/dt/include/Xm/DragDrop.h /usr/dt/include/Xm/DragC.h
GlobalResEditor.o: /usr/dt/include/Xm/Display.h /usr/dt/include/Xm/DropSMgr.h
GlobalResEditor.o: /usr/dt/include/Xm/DragIcon.h
GlobalResEditor.o: /usr/dt/include/Xm/DropTrans.h
GlobalResEditor.o: /usr/dt/include/Xm/DragOverS.h /usr/dt/include/Xm/Screen.h
GlobalResEditor.o: ../lac/ConModel.h ../lac/TreeNode.h ../lac/TreeView.h
GlobalResEditor.o: ../lac/HelpNode.h ../parse/parse.h Lproject.h
GlobalResEditor.o: ../lac/MLXHelp.h ../lac/MLXHelp_base.h
GlobalResEditor.o: /usr/dt/include/Xm/TextOutP.h /usr/dt/include/Xm/XmP.h
GlobalResEditor.o: /usr/dt/include/Xm/BaseClassP.h LApp.h Ltmpl.h Lproperty.h
GlobalResEditor.o: Lresource.h ../lac/LHashDictionary.h Lcreator.h
GlobalResEditor.o: ../vdxlib/LClassInfo.h lic.h lic_msg.h lic_hlp.h
GlobalResEditor.o: ../lac/MsgCat.h ColorSelect.h ColorSelect_base.h
GlobalResEditor.o: FontSelect.h FontSelect_base.h ../lwid/Bubble.h
GlobalResEditor_base.o: GlobalResEditor_base.h
GlobalResEditor_base.o: /usr/dt/include/X11/Intrinsic.h
GlobalResEditor_base.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
GlobalResEditor_base.o: /usr/include/sys/_inttypes.h
GlobalResEditor_base.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
GlobalResEditor_base.o: /usr/dt/include/X11/Xfuncproto.h
GlobalResEditor_base.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
GlobalResEditor_base.o: /usr/dt/include/X11/Xutil.h
GlobalResEditor_base.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
GlobalResEditor_base.o: /usr/dt/include/X11/Core.h
GlobalResEditor_base.o: /usr/dt/include/X11/Composite.h
GlobalResEditor_base.o: /usr/dt/include/X11/Constraint.h
GlobalResEditor_base.o: /usr/dt/include/X11/Object.h
GlobalResEditor_base.o: /usr/dt/include/X11/RectObj.h ../lac/LicView.h
GlobalResEditor_base.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
GlobalResEditor_base.o: /usr/dt/include/X11/Xatom.h
GlobalResEditor_base.o: /usr/dt/include/Xm/XmStrDefs.h
GlobalResEditor_base.o: /usr/dt/include/X11/StringDefs.h
GlobalResEditor_base.o: /usr/dt/include/Xm/VirtKeys.h
GlobalResEditor_base.o: /usr/dt/include/Xm/VendorS.h ../lac/View.h
GlobalResEditor_base.o: ../lac/Lobject.h /usr/include/stdio.h
GlobalResEditor_base.o: ../lac/RefArray.h ../lac/Ref.h ../lac/Rec.h
GlobalResEditor_base.o: ../lac/WidgetRef.h ../lac/TArray.h
GlobalResEditor_base.o: /usr/include/stdlib.h /usr/include/limits.h
GlobalResEditor_base.o: ../../include/X11/xpm.h /usr/dt/include/Xm/Frame.h
GlobalResEditor_base.o: /usr/dt/include/Xm/Form.h
GlobalResEditor_base.o: /usr/dt/include/Xm/BulletinB.h
GlobalResEditor_base.o: /usr/dt/include/Xm/RowColumn.h
GlobalResEditor_base.o: /usr/dt/include/Xm/CascadeB.h
GlobalResEditor_base.o: /usr/dt/include/Xm/PushB.h
GlobalResEditor_base.o: /usr/dt/include/Xm/Separator.h
GlobalResEditor_base.o: /usr/dt/include/Xm/FileSB.h
GlobalResEditor_base.o: /usr/dt/include/Xm/ScrolledW.h
GlobalResEditor_base.o: /usr/dt/include/Xm/Text.h /usr/dt/include/Xm/Label.h
GlobalResEditor_base.o: FontChooser.xpm ColorSelect.xpm Apply.xpm
TransformDialog.o: TransformDialog.h TransformDialog_base.h
TransformDialog.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
TransformDialog.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
TransformDialog.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
TransformDialog.o: /usr/dt/include/X11/Xfuncproto.h
TransformDialog.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
TransformDialog.o: /usr/dt/include/X11/Xutil.h
TransformDialog.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
TransformDialog.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
TransformDialog.o: /usr/dt/include/X11/Constraint.h
TransformDialog.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
TransformDialog.o: ../lac/LicView.h /usr/dt/include/Xm/Xm.h
TransformDialog.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
TransformDialog.o: /usr/dt/include/Xm/XmStrDefs.h
TransformDialog.o: /usr/dt/include/X11/StringDefs.h
TransformDialog.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
TransformDialog.o: ../lac/View.h ../lac/Lobject.h /usr/include/stdio.h
TransformDialog.o: ../lac/RefArray.h ../lac/Ref.h ../lac/Rec.h
TransformDialog.o: ../lac/WidgetRef.h ../lac/TArray.h /usr/include/stdlib.h
TransformDialog.o: /usr/include/limits.h ../../include/X11/xpm.h
TransformDialog.o: ../lac/OptionMenuView.h ../lac/ConModel.h ../lac/Model.h
TransformDialog.o: ../lac/CallbackMethod.h Lwidget.h
TransformDialog.o: /usr/dt/include/X11/IntrinsicP.h
TransformDialog.o: /usr/dt/include/X11/CoreP.h
TransformDialog.o: /usr/dt/include/X11/CompositeP.h
TransformDialog.o: /usr/dt/include/X11/ConstrainP.h
TransformDialog.o: /usr/dt/include/X11/ObjectP.h
TransformDialog.o: /usr/dt/include/X11/RectObjP.h ../lac/IconView.h
TransformDialog.o: ../lac/SensitiveView.h ../lac/Controller.h
TransformDialog.o: ../lac/Lstring.h /usr/dt/include/Xm/AtomMgr.h
TransformDialog.o: /usr/dt/include/Xm/DragDrop.h /usr/dt/include/Xm/DragC.h
TransformDialog.o: /usr/dt/include/Xm/Display.h /usr/dt/include/Xm/DropSMgr.h
TransformDialog.o: /usr/dt/include/Xm/DragIcon.h
TransformDialog.o: /usr/dt/include/Xm/DropTrans.h
TransformDialog.o: /usr/dt/include/Xm/DragOverS.h /usr/dt/include/Xm/Screen.h
TransformDialog.o: ../lac/TreeNode.h ../lac/TreeView.h ../lac/HelpNode.h
TransformDialog.o: ../parse/parse.h Lproject.h ../lac/MLXHelp.h
TransformDialog.o: ../lac/MLXHelp_base.h /usr/dt/include/Xm/TextOutP.h
TransformDialog.o: /usr/dt/include/Xm/XmP.h /usr/dt/include/Xm/BaseClassP.h
TransformDialog.o: /usr/dt/include/Xm/Text.h LApp.h Ltmpl.h Lproperty.h
TransformDialog.o: Lresource.h ../lac/LHashDictionary.h Lcreator.h
TransformDialog.o: ../vdxlib/LClassInfo.h lic.h lic_msg.h lic_hlp.h
TransformDialog.o: ../lac/MsgCat.h /usr/dt/include/Xm/PushB.h
TransformDialog_base.o: TransformDialog_base.h
TransformDialog_base.o: /usr/dt/include/X11/Intrinsic.h
TransformDialog_base.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
TransformDialog_base.o: /usr/include/sys/_inttypes.h
TransformDialog_base.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
TransformDialog_base.o: /usr/dt/include/X11/Xfuncproto.h
TransformDialog_base.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
TransformDialog_base.o: /usr/dt/include/X11/Xutil.h
TransformDialog_base.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
TransformDialog_base.o: /usr/dt/include/X11/Core.h
TransformDialog_base.o: /usr/dt/include/X11/Composite.h
TransformDialog_base.o: /usr/dt/include/X11/Constraint.h
TransformDialog_base.o: /usr/dt/include/X11/Object.h
TransformDialog_base.o: /usr/dt/include/X11/RectObj.h ../lac/LicView.h
TransformDialog_base.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
TransformDialog_base.o: /usr/dt/include/X11/Xatom.h
TransformDialog_base.o: /usr/dt/include/Xm/XmStrDefs.h
TransformDialog_base.o: /usr/dt/include/X11/StringDefs.h
TransformDialog_base.o: /usr/dt/include/Xm/VirtKeys.h
TransformDialog_base.o: /usr/dt/include/Xm/VendorS.h ../lac/View.h
TransformDialog_base.o: ../lac/Lobject.h /usr/include/stdio.h
TransformDialog_base.o: ../lac/RefArray.h ../lac/Ref.h ../lac/Rec.h
TransformDialog_base.o: ../lac/WidgetRef.h ../lac/TArray.h
TransformDialog_base.o: /usr/include/stdlib.h /usr/include/limits.h
TransformDialog_base.o: ../../include/X11/xpm.h /usr/dt/include/Xm/Frame.h
TransformDialog_base.o: /usr/dt/include/Xm/MessageB.h
TransformDialog_base.o: /usr/dt/include/Xm/RowColumn.h
TransformDialog_base.o: /usr/dt/include/Xm/PushB.h
lic_gen.o: Lproject.h /usr/include/limits.h /usr/dt/include/X11/IntrinsicP.h
lic_gen.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
lic_gen.o: /usr/include/sys/types.h /usr/include/sys/_inttypes.h
lic_gen.o: /usr/include/sys/stdsyms.h /usr/dt/include/X11/X.h
lic_gen.o: /usr/dt/include/X11/Xfuncproto.h /usr/dt/include/X11/Xosdefs.h
lic_gen.o: /usr/include/stddef.h /usr/dt/include/X11/Xutil.h
lic_gen.o: /usr/dt/include/X11/Xresource.h /usr/include/string.h
lic_gen.o: /usr/dt/include/X11/Core.h /usr/dt/include/X11/Composite.h
lic_gen.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
lic_gen.o: /usr/dt/include/X11/RectObj.h /usr/dt/include/X11/CoreP.h
lic_gen.o: /usr/dt/include/X11/CompositeP.h /usr/dt/include/X11/ConstrainP.h
lic_gen.o: /usr/dt/include/X11/ObjectP.h /usr/dt/include/X11/RectObjP.h
lic_gen.o: ../lac/Model.h ../lac/Lobject.h /usr/include/stdio.h
lic_gen.o: ../lac/RefArray.h ../lac/Ref.h ../lac/TArray.h
lic_gen.o: /usr/include/stdlib.h ../lac/CallbackMethod.h ../lac/IconView.h
lic_gen.o: ../lac/SensitiveView.h ../lac/View.h ../lac/Rec.h
lic_gen.o: ../lac/WidgetRef.h ../../include/X11/xpm.h ../lac/Controller.h
lic_gen.o: ../lac/Lstring.h /usr/dt/include/Xm/AtomMgr.h
lic_gen.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
lic_gen.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
lic_gen.o: /usr/dt/include/X11/StringDefs.h /usr/dt/include/Xm/VirtKeys.h
lic_gen.o: /usr/dt/include/Xm/VendorS.h /usr/dt/include/Xm/DragDrop.h
lic_gen.o: /usr/dt/include/Xm/DragC.h /usr/dt/include/Xm/Display.h
lic_gen.o: /usr/dt/include/Xm/DropSMgr.h /usr/dt/include/Xm/DragIcon.h
lic_gen.o: /usr/dt/include/Xm/DropTrans.h /usr/dt/include/Xm/DragOverS.h
lic_gen.o: /usr/dt/include/Xm/Screen.h ../lac/ConModel.h ../parse/parse.h
lic_gen.o: ../lac/LicView.h ../lac/MLXHelp.h ../lac/HelpNode.h
lic_gen.o: ../lac/TreeNode.h ../lac/MLXHelp_base.h ../lac/TreeView.h
lic_gen.o: /usr/dt/include/Xm/TextOutP.h /usr/dt/include/Xm/XmP.h
lic_gen.o: /usr/dt/include/Xm/BaseClassP.h /usr/dt/include/Xm/Text.h LApp.h
lic_gen.o: Lwidget.h Lproperty.h Lresource.h ../lac/LHashDictionary.h
lic_gen.o: Lcreator.h ../vdxlib/LClassInfo.h Ltmpl.h misc.h lic.h lic_msg.h
lic_gen.o: lic_hlp.h ../lac/MsgCat.h
VersionControl.o: lic.h lic_msg.h lic_hlp.h ../lac/MsgCat.h ../lac/Lobject.h
VersionControl.o: /usr/include/stdio.h /usr/include/sys/types.h
VersionControl.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
VersionControl.o: /usr/dt/include/X11/Intrinsic.h /usr/dt/include/X11/Xlib.h
VersionControl.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
VersionControl.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
VersionControl.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
VersionControl.o: /usr/include/string.h /usr/dt/include/X11/Core.h
VersionControl.o: /usr/dt/include/X11/Composite.h
VersionControl.o: /usr/dt/include/X11/Constraint.h
VersionControl.o: /usr/dt/include/X11/Object.h /usr/dt/include/X11/RectObj.h
VersionControl.o: LApp.h ../lac/Model.h ../lac/RefArray.h ../lac/Ref.h
VersionControl.o: ../lac/TArray.h /usr/include/stdlib.h
VersionControl.o: ../lac/CallbackMethod.h ../lac/IconView.h
VersionControl.o: ../lac/SensitiveView.h ../lac/View.h ../lac/Rec.h
VersionControl.o: ../lac/WidgetRef.h /usr/include/limits.h
VersionControl.o: ../../include/X11/xpm.h ../lac/Controller.h
VersionControl.o: ../lac/Lstring.h /usr/dt/include/Xm/AtomMgr.h
VersionControl.o: /usr/dt/include/Xm/Xm.h /usr/dt/include/X11/Shell.h
VersionControl.o: /usr/dt/include/X11/Xatom.h /usr/dt/include/Xm/XmStrDefs.h
VersionControl.o: /usr/dt/include/X11/StringDefs.h
VersionControl.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
VersionControl.o: /usr/dt/include/Xm/DragDrop.h /usr/dt/include/Xm/DragC.h
VersionControl.o: /usr/dt/include/Xm/Display.h /usr/dt/include/Xm/DropSMgr.h
VersionControl.o: /usr/dt/include/Xm/DragIcon.h
VersionControl.o: /usr/dt/include/Xm/DropTrans.h
VersionControl.o: /usr/dt/include/Xm/DragOverS.h /usr/dt/include/Xm/Screen.h
VersionControl.o: ../lac/ConModel.h ../parse/parse.h /usr/include/signal.h
VersionControl.o: /usr/include/sys/signal.h /usr/include/sys/sigevent.h
VersionControl.o: /usr/include/sys/siginfo.h /usr/include/sys/newsig.h
VersionControl.o: /usr/include/unistd.h /usr/include/sys/unistd.h
VersionControl.o: /usr/include/sys/wait.h
WidClassMenu.o: WidClassMenu.h ../lac/View.h /usr/dt/include/X11/Intrinsic.h
WidClassMenu.o: /usr/dt/include/X11/Xlib.h /usr/include/sys/types.h
WidClassMenu.o: /usr/include/sys/_inttypes.h /usr/include/sys/stdsyms.h
WidClassMenu.o: /usr/dt/include/X11/X.h /usr/dt/include/X11/Xfuncproto.h
WidClassMenu.o: /usr/dt/include/X11/Xosdefs.h /usr/include/stddef.h
WidClassMenu.o: /usr/dt/include/X11/Xutil.h /usr/dt/include/X11/Xresource.h
WidClassMenu.o: /usr/include/string.h /usr/dt/include/X11/Core.h
WidClassMenu.o: /usr/dt/include/X11/Composite.h
WidClassMenu.o: /usr/dt/include/X11/Constraint.h /usr/dt/include/X11/Object.h
WidClassMenu.o: /usr/dt/include/X11/RectObj.h ../lac/Lobject.h
WidClassMenu.o: /usr/include/stdio.h ../lac/RefArray.h ../lac/Ref.h
WidClassMenu.o: ../lac/Rec.h ../lac/WidgetRef.h ../lac/TArray.h
WidClassMenu.o: /usr/include/stdlib.h /usr/include/limits.h
WidClassMenu.o: ../../include/X11/xpm.h Lcreator.h
WidClassMenu.o: /usr/dt/include/X11/IntrinsicP.h /usr/dt/include/X11/CoreP.h
WidClassMenu.o: /usr/dt/include/X11/CompositeP.h
WidClassMenu.o: /usr/dt/include/X11/ConstrainP.h
WidClassMenu.o: /usr/dt/include/X11/ObjectP.h /usr/dt/include/X11/RectObjP.h
WidClassMenu.o: ../lac/IconView.h ../lac/Model.h ../lac/CallbackMethod.h
WidClassMenu.o: ../lac/SensitiveView.h ../lac/Controller.h ../lac/Lstring.h
WidClassMenu.o: /usr/dt/include/Xm/AtomMgr.h /usr/dt/include/Xm/Xm.h
WidClassMenu.o: /usr/dt/include/X11/Shell.h /usr/dt/include/X11/Xatom.h
WidClassMenu.o: /usr/dt/include/Xm/XmStrDefs.h
WidClassMenu.o: /usr/dt/include/X11/StringDefs.h
WidClassMenu.o: /usr/dt/include/Xm/VirtKeys.h /usr/dt/include/Xm/VendorS.h
WidClassMenu.o: /usr/dt/include/Xm/DragDrop.h /usr/dt/include/Xm/DragC.h
WidClassMenu.o: /usr/dt/include/Xm/Display.h /usr/dt/include/Xm/DropSMgr.h
WidClassMenu.o: /usr/dt/include/Xm/DragIcon.h /usr/dt/include/Xm/DropTrans.h
WidClassMenu.o: /usr/dt/include/Xm/DragOverS.h /usr/dt/include/Xm/Screen.h
WidClassMenu.o: ../lac/ConModel.h ../lac/LicView.h ../vdxlib/LClassInfo.h
WidClassMenu.o: ../lac/LHashDictionary.h /usr/dt/include/Xm/PushB.h
WidClassMenu.o: /usr/dt/include/Xm/CascadeB.h /usr/dt/include/Xm/RowColumn.h
