FANGORN_ROOT = $(shell pwd)/..

include  $(FANGORN_ROOT)/config/mfCommonDefs.mk

Project = fangorn
Package = fangorn

PackagePath = $(FANGORN_ROOT)/fangorn
PackageName = fangorn-fangorn

Packager = Alessandro Thea

PACKAGE_VER_MAJOR = 0
PACKAGE_VER_MINOR = 0
PACKAGE_VER_PATCH = 1
PACKAGE_RELEASE = 0


LinkFlags+=$(shell root-config --libs)
ExecutableLinkFlags+=$(shell root-config --libs)

Library = fangorn

Includes = \
    include \
    $(ROOTSYS)/include 

Libraries = c++ 

LibraryPaths = \
  lib \
  $(ROOTSYS)/lib 

ExecutableLibraries += fangorn c++ TreePlayer Physics

include ${FANGORN_ROOT}/config/mfRules.mk
include ${FANGORN_ROOT}/config/mfRPMRules.mk