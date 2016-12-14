.SUFFIXES: .o

#
# Add all your test .c files here.
CC_FILES_TO_BUILD += $(wildcard $(CURDIR)/*.c)

#
# List of include directories
# For now it is assumed that tests are run only on Windows. Thus, the
# Windows platform is included automatically.
CC_INCLUDE += -I$(CURDIR)/../../Platform_WindowsX86/include

#
# C or C++ Compiler depending on the module under test
CC = g++

# Nothing to be changed below this line. Thus, stay out!
#
# Name of the final binary
OUTPUT = test

#
# Path to embUnit
EMBUNIT_DIR = $(CURDIR)/../../test/embUnit

#
# Change file suffix from .c to .o in list
CC_TO_OBJ_TO_BUILD = $(addsuffix .o,$(basename $(CC_FILES_TO_BUILD)))

#
# Add flags needed for gcov and -Wall which is never a bad idea
CFLAGS += -Wall -g -fprofile-arcs -ftest-coverage

#
# Add standard include directories 
CFLAGS += -I$(CURDIR)/stubs -I$(CURDIR)/../include -I$(CURDIR)/../src -I$(EMBUNIT_DIR) 
#-I$(CURDIR)/../../base/tools/MinGW/include

# 
# Add needed libraries. Generic and unit test
LIBS += -L$(EMBUNIT_DIR)/lib
#LIBS += -L$(CURDIR)/../../base/tools/MinGW/lib/gcc/mingw32/4.8.1
LIBS += -lgcov -lembUnit -ltextui

#
# Generic rule to compile .c -> .o
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
	
#
# Target to create final binary out of .o files
all: $(CC_TO_OBJ_TO_BUILD)
	gcc -o $(OUTPUT) $^ $(CFLAGS) $(LIBS)
	
.PHONY: clean run
	
clean:
	del /q *.o *.gcno *.gcda $(OUTPUT).exe
	
run: $(OUTPUT).exe
	$(OUTPUT)
	
embUnitLib:
	$(MAKE) --directory=$(EMBUNIT_DIR)/embUnit
	$(MAKE) --directory=$(EMBUNIT_DIR)/textui
