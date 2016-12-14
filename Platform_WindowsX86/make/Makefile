# \file Makefile
#
# \brief Makefile for module Platform_WindowsX86
# 
# This makefile is based is based on template makefile, however, it will add 
# quite a few extras in order to make compilation of source files possible.
# Automatic dependency calculation was taken from 
# http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/
# and adapted to this project
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
$(MODULE_NAME)_CPP_FILES := $(wildcard $($(MODULE_NAME)_MODULE_PATH)/src/*.cpp)
#
# Add include directory to list of include directories for c source files
$(MODULE_NAME)_CC_INCLUDE := -I$($(MODULE_NAME)_MODULE_PATH)/include
#
# Add include directory to list of include directories for cpp source files
$(MODULE_NAME)_CPP_INCLUDE := -I$($(MODULE_NAME)_MODULE_PATH)/include

#
# The following lines are only important in platform modules
#
# Define command to delete files. Used by make clean target
RM = rm -f

#
# Create a list of all c files to be compiled
CC_FILES = $(foreach MODULE, $(MODULES), $($(MODULE)_CC_FILES))
#
# Create a list of all cpp files to be compiled
CPP_FILES = $(foreach MODULE, $(MODULES), $($(MODULE)_CPP_FILES))

#
# Create a list of all include directories to be used for C-files
CC_INCLUDE = $(foreach MODULE, $(MODULES), $($(MODULE)_CC_INCLUDE))
#
# Create a list of all include directories to be used for cpp-files
CPP_INCLUDE = $(foreach MODULE, $(MODULES), $($(MODULE)_CPP_INCLUDE))

#
# Only one list is used to store all to be generated object files 
# and dependency Mafiles for c files and c++ files.
# Generate list of .o files to be created from c files
# Change file suffix from .c to .o
CC_TO_OBJ_TO_BUILD = $(addsuffix .o,$(basename $(CC_FILES)))
#
# Add a list of .o files to be created from cpp files
# Change file suffix from .cpp to .o
CC_TO_OBJ_TO_BUILD += $(addsuffix .o,$(basename $(CPP_FILES)))
#
# Generate list of dependency makefile files
# Change file suffix from .c to .d
CC_DEP_FILES = $(addsuffix .d,$(basename $(CC_FILES)))
#
# Generate list of dependency makefile files
# Change file suffix from .cpp to .d
CPP_DEP_FILES += $(addsuffix .d,$(basename $(CPP_FILES)))

#
# Define compile options for c-files special for this platform
CC_OPTS += 

#
# Define compile options for cpp-files special for this platform
CPP_OPTS +=

#
# Options used for dependency calculation
DEP_OPTS += -MT $@ -MMD -MP -MF $*.d

#
#
# Linker options
LINK_OPTS += 

#
# Link final binary from object files
all: $(CC_TO_OBJ_TO_BUILD)
	$(CC) -o BlueMarlin.exe $(CC_TO_OBJ_TO_BUILD)

#
# Target to delete all files generated during compilation as well as 
# the binary
clean:
	$(RM) $(CC_TO_OBJ_TO_BUILD)
	$(RM) $(CC_DEP_FILES)
	$(RM) $(CPP_DEP_FILES)
	$(RM) BlueMarlin.exe
	
show:
	@echo Modules: $(MODULES)
	@echo C-Files: $(CC_FILES)
	@echo CPP-Files: $(CPP_FILES)
	@echo OBJ-Files to buid: $(CC_TO_OBJ_TO_BUILD)
	@echo C-Files include directories: $(CC_INCLUDE)
	@echo CPP-Files include directories: $(CPP_INCLUDE)
	@echo Modules Makfiles: $(MODULES_MAKEFILES)
	@echo C-Files Dependency Makfiles: $(CC_DEP_FILES)
	@echo CPP-Files Dependency Makfiles: $(CPP_DEP_FILES)
	

#
# Create a pattern rule with an empty recipe, so that make won’t fail if 
# the dependency file doesn’t exist.
# Mark the dependency files precious to make, so they won’t be automatically
# deleted as intermediate files.
%.d: ;
.PRECIOUS: %.d

#
# Generic rule to compile .c -> .o (and create corresponding dependency Makefile)
%.o: %.c
%.o: %.c %.d
	@echo Compiling $< ...
	$(CC) -c $(DEP_OPTS) $(CC_OPTS) $(CC_INCLUDE) $< -o $@
	@echo done
	@echo .

#
# Generic rule to compile .cpp -> .o (and create corresponding dependency Makefile)
%.o: %.cpp
%.o: %.cpp %.d
	$(CPP) -c $(DEP_OPTS) $(CC_OPTS) $(CPP_INCLUDE) $< -o $@
#
# Include generated dependency Makefile if they exist
-include $(CPP_DEP_FILES)
-include $(CC_DEP_FILES)
