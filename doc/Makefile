TOPDIR = ..
PROGRAM = dummy

all:	user_guide
	@echo Do nothing.

include $(TOPDIR)/Makerules

install: clean-samples
	@for i in `find samples -type f | grep -v CVS`; do\
		$(INSTALL) $$i doc/$$i; \
	done

user_guide:	
	@(cd guide; make all)

depend:
	@echo Do nothing.

clean:
	@(cd guide; make clean)


clean-samples:
	@for i in `find samples -name Makefile`; do \
		(cd `dirname $$i`; make clean); \
	done


