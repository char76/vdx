TOPDIR = .
SUBDIRS = src lib install
PROGRAM = dummy
LIBRARY = dummy.a

all: subdirs

include $(TOPDIR)/Makerules

depend: depend-subdirs

clean: clean-subdirs

install: test-include install-subdirs

World: depend all install

test-include:
	test -d include || mkdir include
	test -d include/lac || mkdir include/lac
	test -d include/lwid || mkdir include/lwid

