# get the type of OS currently running
OS=$(shell uname)

LIB_EF = libembedFiglet.a
CC     = gcc
CXX    = g++
INC    = -I./src
CFLAGS = -Wall -pedantic -O3
LIBS   = -Llib -lembedFiglet

# check if the OS string contains 'Linux'
ifneq (,$(findstring Linux, $(OS)))
  #LIB_GC = libembedFiglet.so
endif

# check if the OS string contains 'Darwin'
ifneq (,$(findstring Darwin, $(OS)))
  CC     = clang
  CXX    = clang++
  #LIB_GC = libembedFiglet.dylib
endif

SRCS = \
src/Figlet.cc \
src/Figlet_Font_banner.cc \
src/Figlet_Font_big.cc \
src/Figlet_Font_doom.cc \
src/Figlet_Font_larry3d.cc \
src/Figlet_Font_mini.cc \
src/Figlet_Font_script.cc \
src/Figlet_Font_small.cc \
src/Figlet_Font_standard.cc \
src/Figlet_Font_straight.cc

OBJS = $(SRCS:.cc=.o)
DEPS = src/Figlet.hh

# prefix for installation, use make PREFIX=/new/prefix install
# to override
PREFIX    = /usr/local
FRAMEWORK = GenericContainer

#AR     = ar rcs
AR     = libtool -static -o 
MKDIR  = mkdir -p

all:  lib
	$(CXX) $(CXXFLAGS) $(INC) -o test tests/test.cc $(LIBS)
	$(CXX) $(CXXFLAGS) $(INC) -o example examples/example.cc $(LIBS)

lib:  lib/$(LIB_EF)

src/%.o: src/%.cc $(DEPS)
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@ 

src/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

lib/libembedFiglet.a: $(OBJS)
	$(MKDIR) lib
	$(AR) lib/libembedFiglet.a $(OBJS)

lib/libembedFiglet.dylib: $(OBJS)
	$(MKDIR) lib
	$(CXX) -dynamiclib $(OBJS) -o lib/libembedFiglet.dylib $(LIB_DIR) -install_name libembedFiglet.dylib -Wl,-rpath,.

lib/libembedFiglet.so: $(OBJS)
	$(MKDIR) lib
	$(CXX) -shared $(OBJS) -o lib/libembedFiglet.so $(LIB_DIR)

install: lib/$(LIB_EF)
	cp src/Figlet.hh $(PREFIX)/include
	cp lib/$(LIB_EF) $(PREFIX)/lib

install_as_framework: lib/$(LIB_EF)
	$(MKDIR) $(PREFIX)/include/$(FRAMEWORK)
	cp src/Figlet.hh $(PREFIX)/include/$(FRAMEWORK)
	cp lib/$(LIB_EF) $(PREFIX)/lib

run:
	./test
	./example

doc:
	doxygen
	
clean:
	rm -f lib/libembedFiglet.* src/*.o