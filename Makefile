#
# Define compiler if not yet defined by environment variable
# If another compiler shold be used defined CC and CPP in console
# set CC=gcc, set CPP=g++
CC = gcc
CPP = g++

#
# List of modules to be used. Any modules that should be compiled should
# be added here.
MODULES = Template Platform_WindowsX86
#
# Add makefiles for each module
include $(foreach MODULE, $(MODULES), $(MODULE)/make/Makefile)

#
# 
CC_FILES = $(foreach MODULE, $(MODULES), $($(MODULE)_CC_FILES))

show:
	@echo Modules: $(MODULES)
	@echo C-Files: $(CC_FILES)
	@echo CPP-Files: $(CPP_FILES)
	@echo OBJ-Files to buid: $(CC_TO_OBJ_TO_BUILD)
	@echo C-Files include directories: $(CC_INCLUDE)
	@echo CPP-Files include directories: $(CCP_INCLUDE)
	@echo Modules Makfiles: $(MODULES_MAKEFILES)
	@echo Platform: $(Platform_WindowsX86_CC_FILES)
	@echo Template: $(Template_CC_FILES)
