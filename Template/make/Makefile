# \file
#
# \brief Template Makefile to be used for all modules
# 
# This is a template Makefile which shall be used for all new modules. Please
# adapt for each new module. The following 
# - Module name and base directory must be identical
#
# \author kein0r
#
# Add this module to the list of modules. Make sure that the module name matches
# the directory name of the module.
MODULE_NAME := Template

#
# Generic defines which are usually not changed
#
#
# Path to the module assuming that this makefile is located in modulePath/make/
# Simply expanded variables (using :=) must be used here because MODULE_NAME is
# used in every module.
#
$(MODULE_NAME)_MODULE_PATH := $(subst \,/,$(dir $(lastword $(MAKEFILE_LIST)))..)

#
# Add all .c files from source directory of this modules to the list files to be
# compiled.
CC_FILES += $(wildcard $($(MODULE_NAME)_MODULE_PATH)/src/*.c)
#
# Add all .cpp files from source directory of this modules to the list files to be
# compiled.
CPP_FILES += $(wildcard $($(MODULE_NAME)_MODULE_PATH)/src/*.cpp)
#
# Add include directory to list of include directories for c source files
CC_INCLUDE += -I$($(MODULE_NAME)_MODULE_PATH)/include
#
# Add include directory to list of include directories for cpp source files
CPP_INCLUDE += -I$($(MODULE_NAME)_MODULE_PATH)/include