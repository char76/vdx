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

![cde](https://github.com/char76/vdx/assets/1542010/d1628829-f493-4dea-a9cd-21085d4d27d3)

## 0. Introduction

My name is Charley Shin. I will maintain this git repository.

Original author is dirklaessig. I just change sources, compile and tested in Ubuntu 22.04.4(amd64) and Raspberry Pi 5(aarch64 or arm64).

Original sources are in Sourceforge https://sourceforge.net/projects/vdx/

## 1. Requirements
 #### - common - amd64 & aarch64
libX11, libXt, libXaw, libXmu, libXpm, libXm and so on.
```
$ sudo apt install libx11-dev libxt-dev libxaw7-dev libxmu-dev libxpm-dev libxext-dev libxau-dev libxft-dev libxrender-dev libice-dev libsm-dev libmotif-common libmotif-dev x11proto-print-dev
```
If you need libXp, please check https://askubuntu.com/questions/944838/libxp-so-6-missing-for-ubuntu-17-04
```
$ sudo add-apt-repository ppa:zeehio/libxp
$ sudo apt update
$ sudo apt install libxp6 libxp-dev
```
 #### - only aarch64
If you **can not** find the libs as follow in apt, you can search and download the libs in https://launchpad.net/ubuntu

Or you can download at Releases page

 * multiarch-support
 * x11proto-print-dev
 * libxp6
 * libxp-dev
## 2. Build
execute build then enter 11 as follow or if you want to build with CDE(It must be built and installed in system. Please refer to https://sourceforge.net/p/cdesktopenv/wiki/LinuxBuild/), enter 2
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
execute ./install/[build type]/bin/vdx

## 5. TODO
* enable xmPrintShellWidgetClass
  - cannot resolve this class at link. So comment out this class in LClassInfo.C
* integrate ViewKlass https://sourceforge.net/projects/viewklass/ 
