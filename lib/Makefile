TOPDIR = ..
PROGRAM = dummy

all:
	@echo Do nothing

include $(TOPDIR)/Makerules

install:
	@for i in `find X11 -type f`; do\
		$(INSTALL) $$i lib/$$i; \
	done

clean:
	@echo Do nothing
	
depend:
	@echo Do nothing
