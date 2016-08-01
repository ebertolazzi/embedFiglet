# get the type of OS currently running
OS=$(shell uname)

LIB_EF = libembedFiglet.a
CC     = gcc
CXX    = g++

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
srcs/Figlet.cc \
srcs/Figlet_Font_banner.cc \
srcs/Figlet_Font_big.cc \
srcs/Figlet_Font_doom.cc \
srcs/Figlet_Font_larry3d.cc \
srcs/Figlet_Font_mini.cc \
srcs/Figlet_Font_script.cc \
srcs/Figlet_Font_small.cc \
srcs/Figlet_Font_standard.cc \
srcs/Figlet_Font_straight.cc

OBJS = $(SRCS:.cc=.o)
DEPS = srcs/Figlet.hh

CFLAGS =  -I./srcs -Wall -pedantic -O3
LIBS   = -Llibs -lembedFiglet

#AR     = ar rcs
AR     = libtool -static -o 
MKDIR  = mkdir -p

all:  libs/$(LIB_EF)
	$(CXX) $(CFLAGS) -o test tests/test.cc $(LIBS)
	$(CXX) $(CFLAGS) -o example examples/example.cc $(LIBS)

Sources/%.o: srcs/%.cc $(DEPS)
	$(CXX) $(CFLAGS) -c $< -o $@ 

Sources/%.o: srcs/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

libs/libembedFiglet.a: $(OBJS)
	$(MKDIR) libs
	$(AR) libs/libembedFiglet.a $(OBJS) 

libs/libembedFiglet.dylib: $(OBJS)
	$(MKDIR) libs
	$(CXX) -dynamiclib $(OBJS) -o libs/libembedFiglet.dylib $(LIB_DIR) -install_name libembedFiglet.dylib -Wl,-rpath,.

libs/libembedFiglet.so: $(OBJS)
	$(MKDIR) libs
	$(CXX) -shared $(OBJS) -o libs/libembedFiglet.so $(LIB_DIR)

install: libs/$(LIB_EF)
	cp srcs/Figlet.hh $(PREFIX)/include
	cp libs/$(LIB_EF) $(PREFIX)/lib

run:
	./test
	./example

doc:
	doxygen
	
clean:
	rm -f libs/libembedFiglet.* srcs/*.o