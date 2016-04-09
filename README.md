GIMP Plugin "Map Saliency"
==========================

Copyright 2016 Lloyd Konneker

A GIMP plugin that computes a saliency map.
Where a saliency map is a new gray image of a given image.
In the map, brightness indicates saliency: likelihood of being focused by human gaze.

Users
-----

Results of this plugin might not be all that useful.
The basic algorithm is a work in progress.
There are many alternative algorithms for computing saliency.
This algorithm is from [Saliency Detection] (https://github.com/kkduncan/SaliencyDetection.git)

Building is somewhat complicated.

Installing without building
---------------------------

The executable for 32-bit i86 Linux platform is in the repository.
You might be able to manually install to your personal GIMP at ~/.gimp-2.8/plug-ins, by copying gimp-plugin-engine-saliency.exe and plugin-map-saliency.py, and making the latter executable.
That might not work if your machine is configured much differently from my Ubuntu 15.10 development machine.


Building without using Eclipse, from a command line
---------------------------------------------------

Invoke autotools manually.
This  SEEMS to work:

    autoreconf -i
    ./configure
    make
    sudo make install

Install is to /usr/lib/gimp/2.0/plug-ins and /usr/local/lib/gimp/2.0/plug-ins.
I'm not sure why the latter, and you may need to add that plugin path to your GIMP configuration so that GIMP finds the installed plugin-map-saliency.py

The configure.ac is deficient and configure will not complain if you don't have the needed libsaliency.

Dependencies
------------

Building requires packages for:
- autotools
- GIMP dev 
- OpenCV v2 dev

Building also requires building and installing the separate libsaliency repository.

Architecture
------------

Constructed starting from [gimp-plugin-engine-template] (https://github.com/bootchk/gimp-plugin-engine-template.git)  See there a discussion of the architecture.  Also see "Developers" below.

Uses:
- [libsaliency[ (https://github.com/bootchk/libsaliency.git)
- OpenCV v2

libsaliency is statically linked but OpenCV is dynamically linked.  Users need OpenCV libraries installed.  Since libsaliency is statically linked (against many recommendations), this plugin might be fragile under changes to openCV APIs.

Developers
----------

This is an exercise in adapting openCV to Gimp.  You could easily(?) duplicate this (starting at gimp-plugin-engine-template) to adapt other openCV algorithms.  (There are other GIMP plugins using openCV, see Face Detection plugin.)

libsaliency uses openCV but is not in openCV.  There are other saliency and object detection algorithms in openCV.  I don't think the core algorithm of libsaliency makes much use of any acceleration by openCV.

This is also an exercise in testing the architecture of gimp-plugin-engine-template.
In that architecture, you need to build and install:

- a Python plugin (GUI wrapper)
- a C-language plugin (engine)
- a C++ language library (the algorithm library, unless statically linked.)
- openCV libs

It is not clear that this is better than one monolithic C/C++ plugin containing GUI and algorithms.


