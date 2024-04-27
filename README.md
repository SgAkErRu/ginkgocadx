# Ginkgo CADx - modified version with AppImage #

## Changes ##

1. Allow multiple selections for downloading.
2. Enable download button, if selected items more than one.
3. One date style (Y-m-d)
4. Add AppImageBuilder.yml

## Build AppImage ##

1. Install Debian 11 (or do it in Docker) and install `git`

2. Get `ginkgocadx` debian sources (for example, it will create dir `ginkgocadx-3.8.8`):

```
apt source ginkgocadx
```

3. Clone this repo and move changes of this branch like a debian patch:

```
git clone https://gitlab.com/SgAkErRu/ginkgocadx.git -b improvements
cd ./ginkgocadx
git format-patch 3.8.8 --stdout > ../improvements.patch
cp ../improvements.patch ../ginkgocadx-3.8.8/debian/patches/
```

4. Build and install new modified debian package:

```
cd ginkgocadx-3.8.8/
sudo apt install packaging-dev debian-keyring devscripts equivs
sudo mk-build-deps --install --remove
sudo dch -l mod
fakeroot debian/rules binary
sudo dpkg-buildpackage -b -us -uc
sudo apt install ../ginkgocadx_*_*.deb
```

5. Get or install `appimage-builder` (https://appimage-builder.readthedocs.io/en/latest/intro/install.html)

6. Create folder `GinkgoAppImage` and put `AppImageBuilder.yml` there, like `/home/user/GinkgoAppImage/`. 

Also change path in `AppImageBuilder.yml`, if you have path is not `/home/user/GinkgoAppImage/...`

7. Create there `AppDir` folder and unzip debian package binary files (`data.tar.xz`) there, like:

`AppDir/usr/bin/ginkgocadx`
`AppDir/usr/lib/...`
`AppDir/usr/share/...`

etc.

8. Build AppImage (it will create AppImage with `AppDir` binaries and deps that included in `AppImageBuilder.yml`):

```
cd ./GinkgoAppImage
appimage-builder
```

9. Launch `GinkgoCADx-3.8.8-mod1-x86_64.AppImage`

==========================================
==========================================
==========================================

[![Build Status](https://travis-ci.org/gerddie/ginkgocadx.svg?branch=master)](https://travis-ci.org/gerddie/ginkgocadx)
[![Coverity Status](https://scan.coverity.com/projects/8214/badge.svg)](https://scan.coverity.com/projects/ginkgocadx)

# Ginkgo CADx #

## Preface ##

* Currently the project is maintained on a voluntary basis. 
* There is no PRO version.
* I can't help you with compiling this on MS Windows or Mac OS X 

## Introduction ##

Ginkgo CADx is an advanced DICOM viewer and dicomizer that can
also be used to convert png, jpeg, bmp, pdf, tiff to DICOM files.

The version developed here is a continuation of the now abandoned
free version developed by MetaEmotion:

    http://ginkgo-cadx.com/en/


## License ##

Ginkgo CADx is licensed under the terms of the Lesser GNU Public
Licence 3.

## Build ##

To build Ginkgo CADx the following software packages are required:

* ITK (>= 4.8)
* VTK (>= 6.2), Please note that the code does currently not compile with the
  VTK OpenGL2 rendering backend (see #21 and #34). VTK >= 7.0 defaults to
  this newer backend when configured without parameters, and currently
  you will have to set VTK_RENDERING_BACKEND=OpenGL when building VTK to
  sucessfully compile ginkgocadx. 
* wxWidgets (>= 3.0.1)
* DCMTK (>= 3.6.1-20150924)
* A C++ compiler that supports the *C++11* standard
* CMake

With these prerequisites available run *cmake* on the Ginkgo CADx
source tree and then use the selected build system to build the software.
After the software was sucessfully compiled run the install target.


The original Ginkgo CADx implementation was done with cross-platform
compatibility in mind, i.e. the software should compile on MS Windows,
Mac OS X, and flavours of Linux. However, currently the main development
platforms are Debian GNU/Linux and Gentoo Linux using the GNU gcc compiler
tool chain. Hence incompatibilities may creep in and bug reports with fixes
for other platforms are very welcome. 


### Debian/Ubuntu specific build instructions ###

The following packages must be installed in order to compile it:


    chrpath
    cmake
    libcairo2-dev
    libcurl4-gnutls-dev
    libdcmtk-dev
    libfftw3-dev
    libfreetype6-dev
    libgtk2.0-dev
    libinsighttoolkit4-dev
    libjsoncpp-dev
    libmysqlclient-dev
    libsqlite3-dev
    libssl-dev
    libvtk6-dev
    libwrap0-dev
    libwxgtk3.0-dev
    libxml2-dev
    libgdcm-tools

On Debian *Stretch* and *Sid* these packages can be installed by simply running

    apt build-dep ginkgocadx

On Ubuntu Xenial (16.04 )the package can be installed from the Xenial ports PPA: 

   https://launchpad.net/~gert-die/+archive/ubuntu/xenial-mia

For Yantal the package available from the usual Ubuntu repositories. 


