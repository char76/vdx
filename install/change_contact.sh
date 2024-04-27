#!/bin/sh

tmpdir=/tmp
archive=`pwd`/$1
base=`basename $1 .tar.gz`
name=$2
url=$3

(
	cd $tmpdir
	tar xzvf $archive
	sed -e "s/BREDEX/$name/" <$base/lib/X11/app-defaults/Vdx | \
	sed -e "s!http://www\.bredex\.de/EN/vdx!$url!" >$tmpdir/Vdx
	mv $tmpdir/Vdx $base/lib/X11/app-defaults/Vdx
	tar czvf $archive $base
	rm -rf ${tmpdir}/${base}
)