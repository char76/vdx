                  Welcome to VDX

              (formerly known as View Designer/X)



    Copyright (C) 1996, 1997, 1998 by Dirk Laessig, Braunschweig, Germany
               ALL RIGHTS RESERVED
                 dirk@bredex.de


    From Sourceforge:
    View Designer/X (VDX) is a Motif Interface Builder developed for Linux.
    I(dirklaessig) developed this software in the late 90's as a product for Linux.
----
![vdx](https://github.com/char76/vdx/assets/1542010/81959fba-050a-4442-8fef-f903b7f384f0)

## 0. Introduction

My name is Charley Shin.

Original author is dirklaessig. I just change sources, compile and tested in Ubuntu 22.04.4.

Please visit Sourceforge https://sourceforge.net/projects/vdx/

## 1. Requirements

libX11, libXt, libXaw, libXmu, libXpm, libXm
```
$ sudo apt install libx11-dev libxt-dev libxaw-dev libxmu-dev libxpm-dev libxext-dev libxau-dev libxft-dev libxrender-dev libice-dev libsm-dev libmotif-common libmotif-dev
```
If you need libXp, please check https://askubuntu.com/questions/944838/libxp-so-6-missing-for-ubuntu-17-04
```
sudo add-apt-repository ppa:zeehio/libxp
sudo apt update
sudo apt install libxp6 libxp-dev
```

## 2. Build
execute build then enter 11 as below
```
$ ./build
1) hpux-matzen
2) linux-cde
3) linux-m1.2
4) linux-m2.0
5) linux-m2.0s
6) linux-m2.0s-debug
7) linux-m2.0xrt
8) linux-m2.1
9) linux-m2.1-glibc
10) linux-m2.1-lac
11) linux-m3-lac
12) solaris
Enter configuration to build
```

## 3. Install
type "make install" then please check "install" directory

## 4. Execution
execute ./install/vdx-v1.3.0-linux-m3-lac/bin/vdx
