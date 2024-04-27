#!/bin/sh

ask() {
	a=k
	while [ x$a != xy -a x$a != xn ]; do
		read a
	done
	if [ x$a = xy ]; then
		echo YES
	else
		echo NO
	fi
}

echo Current Configuration
echo

awk '/define/{printf("%s\t%s\n", $2, $3)}' <config.tmpl

echo

for i in `awk '/define/{printf("%s ", $2)}' <config.tmpl`
do
	n=`echo $i| sed -e 's/Use//'`
	echo Add support for $n
	echo "(y/n)?"
	res=`ask`
	sed -e "s/#define.*$i.*/#define $i $res/" <config.tmpl >config.tmpl.bak
	mv config.tmpl.bak config.tmpl
	if [ x$res = xYES ]; then
		d=`grep ${n}Path config.tmpl | awk '{printf("%s", $3) }'  `
		if [ ! -d $d ]; then
			echo "*** Warning: $d not exists."
		fi
	fi
done

echo
echo Configuration done.
echo Building vdxlib ...
echo

xmkmf; make clean all



