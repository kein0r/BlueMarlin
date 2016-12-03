# \file
#
# \brief Makefile for module Platform_WindowsX86
# 
# This makefile is based is based on template makefile, however, it will add 
# quite a few extras in order to make compilation of source files possible.
#
# \author kein0r
#
# Add this module to the list of modules. Make sure that the module name matches
# the directory name of the module.
MODULE_NAME := Platform_WindowsX86

#
# Generic defines which are usually not changed
#
# Path to the module assuming that this makefile is located in modulePath/make/
# Simply expanded variables (using :=) must be used here because MODULE_NAME is
# used in every module.
$(MODULE_NAME)_MODULE_PATH := $(subst \,/,$(dir $(lastword $(MAKEFILE_LIST)))..)

#
# Add all .c files from source directory of this modules to the list files to be
# compiled.
$(MODULE_NAME)_CC_FILES := $(wildcard $($(MODULE_NAME)_MODULE_PATH)/src/*.c)
#
# Add all .cpp files from source directory of this modules to the list files to be
# compiled.
$(MODULE_NAME)_CPP_FILES += $(wildcard $(Platform_WindowsX86_MODULE_PATH)/src/*.cpp)
#
# Add include directory to list of include directories for c source files
$(MODULE_NAME)_CC_INCLUDE += -I$(Platform_WindowsX86_MODULE_PATH)/include
#
# Add include directory to list of include directories for cpp source files
$(MODULE_NAME)_CPP_INCLUDE += -I$(Platform_WindowsX86_MODULE_PATH)/include

#
# The following lines are only important in platform modules
#
# Define command to delete files
RM=rm -f

#
# Generate list of .o files to be created from c files
# Change file suffix from .c to .o
CC_TO_OBJ_TO_BUILD = $(addsuffix .o,$(basename $(CC_FILES)))

#
# Define compile options for c-files special for this platform
CC_OPTS +=

#
# Define compile options for cpp-files special for this platform
CPP_OPTS +=

#
# Generic rule to compile .c -> .o
%.o: %.c
	@build Building $<
	$(CC) -c $(CC_OPTS) $(CC_INCLUDE) $< -o $@
	@echo done

#
# Generic rule to compile .cpp -> .o
%.o: %.cpp
	$(CPP) -c $(CC_OPTS) $(CC_INCLUDE) $< -o $@

#
# Link final binary from object files
all: $(CC_TO_OBJ_TO_BUILD)
	$(CC) -o BlueMarlin.exe $(CC_TO_OBJ_TO_BUILD)
	@echo done

#
# Target to delete all compile object files as well as the binary
clean:
	$(foreach OBJ_FILE, $(CC_TO_OBJ_TO_BUILD), $(shell $(RM) $(OBJ_FILE)))
	$(RM) BlueMarlin.exe
