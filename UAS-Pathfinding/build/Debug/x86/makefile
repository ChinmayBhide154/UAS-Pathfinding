# Makefile for building the Pathfinding binary

# The Compiler: gcc for C, g++ for C++
CC := g++


NAME := libPathfinding_x86_Debug
SNAME := $(NAME).a
DNAME := $(NAME).so

# Compiler flags:
# -m32 for 32bit, -m64 for 64bit
# -Wall turns on most, but not all, compiler warnings
#

CFLAGS := -m32 -Wall -std=c++11 -D_DEBUG -DDEBUG 

LDFLAGS = -shared

DEBUGFLAGS = -O0 -g3 
RELEASEFLAGS = -O3
OBJECTFLAGS = -c -fmessage-length=0 -fPIC -MMD -MP

SOURCES = $(wildcard ../../../*.cpp) $(wildcard ../../../../submodules/Minimum-Cost-Perfect-Matching/*.cpp)
SOURCES := $(filter-out ../../../../submodules/Minimum-Cost-Perfect-Matching/Example.cpp, $(SOURCES))
OBJECTS = $(addprefix obj/,$(notdir $(SOURCES:.cpp=.o)))
INCLUDES = -I../../.. -I../../../../submodules/Minimum-Cost-Perfect-Matching -I../../../../submodules/json/single_include/nlohmann -I../../../../submodules/WGS84toCartesian
# LIBPATH = -L../
# LIB = -l

all: $(SNAME) $(DNAME)

$(SNAME): $(OBJECTS)
	@echo 'Building target: $@'
	ar rcs $(SNAME) $(OBJECTS)
	@echo 'Finished building target: $@'
	@echo ' '

$(DNAME): $(OBJECTS)
	@echo 'Building target: $@'
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(DNAME) $(OBJECTS)
	@echo 'Finished building target: $@'
	@echo ' '
	
# Dependency source files for the binary
obj/%.o: ../../../../submodules/Minimum-Cost-Perfect-Matching/%.cpp
	@mkdir -p obj
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	$(CC) $(DEBUGFLAGS) $(CFLAGS) $(OBJECTFLAGS) $(INCLUDES) -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o $@ $<
	@echo 'Finished building: $<'
	@echo ' '

# General source files for the binary
obj/%.o: ../../../%.cpp
	@mkdir -p obj
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	$(CC) $(DEBUGFLAGS) $(CFLAGS) $(OBJECTFLAGS) $(INCLUDES) -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o $@ $<
	@echo 'Finished building: $<'
	@echo ' '

install:
	install -D $(SNAME) ../../../../bin/$(SNAME)
	install -D $(DNAME) ../../../../bin/$(DNAME)

# make clean
# Removes target file and any .o object files, 
# .d dependency files, or ~ backup files
clean:
	$(RM) $(SNAME) $(DNAME) obj/* *~
