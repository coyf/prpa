# Makefile for TBB and C++11
# Setup for GNU Make
 
# Compilers and libs
 
# Adding /usr/local/include for FreeBSD
CPPFLAGS= -I/usr/local/include/ImageMagick

CXX=g++ -pthread
CXXFLAGS= -Wall -Wextra -std=c++11 # Debug flags -O0 -g

SDIR=src
# Source files
BSRC=main.cc neuron.cc
SRC=$(addprefix ${SDIR}/, $(BSRC))

DEP=$(SRC:.cc=.d)

# Adding /usr/local/lib for FreeBSD
LDFLAGS= -L/usr/local/lib
# Addiing pkg-config for gtk+

# libs flags
LDLIBS= -lrt -ltbb

OBJ=$(SRC:.cc=.o)

TARGET=prpa

# Empty all rule
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) `Magick++-config --cppflags --cxxflags --ldflags --libs` -o $@ $^ $(LDFLAGS) $(LDLIBS)

# Clean your dir
clean:
	$(RM) $(OBJ) *.core
	$(RM) $(TARGET)
	$(RM) $(DEP)

.PHONY: clean

-include $(DEP)
# END of Makefile
