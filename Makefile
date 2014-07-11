# Makefile for TBB and C++11
# Setup for GNU Make
 
# Compilers and libs
 
# Adding /usr/local/include for FreeBSD
CPPFLAGS= -I/usr/local/include

CXX=g++ -pthread
CXXFLAGS= -Wall -Wextra -std=c++11 # Debug flags -O0 -g

SDIR=src
# Source files
BSRC=main.cc
SRC=$(addprefix ${SDIR}/, $(BSRC))

DEP=$(SRC:.cc=.d)

# Adding /usr/local/lib for FreeBSD
LDFLAGS= -L/usr/local/lib
 
# libs flags
LDLIBS= -lrt -ltbb -lglut -lGL

OBJ=$(SRC:.cc=.o)

TARGET=prpa

# Empty all rule
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDLIBS)

# Clean your dir
clean:
	$(RM) $(OBJ) *.core
	$(RM) $(TARGET)
	$(RM) $(DEP)

.PHONY: clean

-include $(DEP)
# END of Makefile
