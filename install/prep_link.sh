#!/bin/sh

source=`basename $2`
name=$3
destdir=`dirname $2`

echo Link $2 to $destdir/$name
(cd $1/$destdir; rm -f $name ; ln -fs $source $name)

