
TOPDIR = ..
PROGRAM = dummy
TARFILE = $(SHORTNAME)-$(REVISION)-$(ARCH).tar
all:
	@$(INSTALL) README README
	@$(INSTALL) README.CDE README.CDE
	@$(INSTALL) COPYRIGHT COPYRIGHT
	@$(INSTALL) ad2fbh.script bin/ad2fbh.script

include $(TOPDIR)/Makerules

install: care
	@tar cvf $(TARFILE) $(INSTALLDIR)
	@$(COMPRESS) $(TARFILE)

disk:	care
	@echo Insert floppy in drive /dev/fd0 and press enter.
	@read sabel
	@tar czvf /dev/fd0 $(INSTALLDIR)

depend:
	@echo Do nothing.

clean: 
	rm -rf $(INSTALLDIR)
	rm -f $(TARFILE)*

care:
	strip $(INSTALLDIR)/bin/vdx.bin
	strip $(INSTALLDIR)/lib/libvdx.so
	rm -f $(INSTALLDIR)/lib/X11/vdx/license*

