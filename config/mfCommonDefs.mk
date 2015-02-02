# ifndef MP7_ROOT
#   MP7_ROOT:=${MP7_BACK_TO_ROOT}
# endif
# BUILD_HOME=${MP7_ROOT}
# $(info Using MP7_ROOT=${MP7_ROOT})
# $(info Using BUILD_HOME=${BUILD_HOME})

# Cactus config. This section shall be sources from /opt/cactus/config
# CACTUS_ROOT ?= /opt/cactus
FANGORN_PLATFORM=$(shell /usr/bin/python -c "import platform; print platform.platform()")
FANGORN_OS="unknown.os"

UNAME=$(strip $(shell uname -s))
ifeq ($(UNAME),Linux)
    ifneq ($(findstring redhat-5,$(FANGORN_PLATFORM)),)
        FANGORN_OS=slc5
    else ifneq ($(findstring redhat-6,$(FANGORN_PLATFORM)),)
        FANGORN_OS=slc6
    endif
    DynLibFlag="-shared"
    DynLibExt="so"
endif
ifeq ($(UNAME),Darwin)
    FANGORN_OS=osx
    DynLibFlag="-shared"
	DynLibExt="dylib"
endif

$(info OS Detected: $(FANGORN_OS))
# end of Cactus config

## Environment
# Make sure $CACTUS_ROOT/lib is present in LD_LIBRARY_PATH 
ifndef LD_LIBRARY_PATH
LD_LIBRARY_PATH:=$(ROOTSYS)/lib
else
LD_LIBRARY_PATH:="$(ROOTSYS)/lib:$(LD_LIBRARY_PATH)"
endif

export LD_LIBRARY_PATH


## Compilers
CPP:=clang
LD:=clang
	
## Tools
MakeDir=mkdir -p

## Python
PYTHON_VERSION ?= $(shell python -c "import distutils.sysconfig;print distutils.sysconfig.get_python_version()")
PYTHON_INCLUDE_PREFIX ?= $(shell python -c "import distutils.sysconfig;print distutils.sysconfig.get_python_inc()")

ifndef DEBUG
# Compiler flags
CxxFlags = -g -Wall -O3 -MMD -MP -fPIC -std=c++11
LinkFlags = -g $(DynLibFlag) -fPIC -Wall -O3 
ExecutableLinkFlags = -g -Wall -O3
else
CxxFlags = -g -ggdb -Wall -MMD -MP -fPIC -std=c++11
LinkFlags = -g -ggdb $(DynLibFlag) -fPIC -Wall 
ExecutableLinkFlags = -g -ggdb -Wall
endif

