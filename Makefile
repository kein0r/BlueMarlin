#
# Define compiler if not yet defined by environment variable
# If another compiler shold be used defined CC and CPP in console
# set CC=gcc, set CPP=g++
CC = gcc
CPP = g++

#
# List of modules to be used. Any modules that should be compiled must
# be added here.
# Important: Platform shall be included last to make compilation work
MODULES = Template Application_3DPrinter Platform_WindowsX86
#
# Below this line usually nothing needs to be changed
#
# Include makefiles of each module
include $(foreach MODULE, $(MODULES), $(MODULE)/make/Makefile)
