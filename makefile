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

#CC     = llvm-gcc
#CXX    = llvm-g++
#CC     = clang
#CXX    = clang++
CC     = gcc
CXX    = g++

CFLAGS =  -I./srcs -Wall -pedantic -O3
LIBS   = -Llibs -lembedFiglet

#AR     = ar rcs
AR     = libtool -static -o 

all: libembedFiglet.a
	$(CXX) $(CFLAGS) -o test tests/test.cc $(LIBS)
	$(CXX) $(CFLAGS) -o example examples/example.cc $(LIBS)

Sources/%.o: srcs/%.cc $(DEPS)
	$(CXX) $(CFLAGS) -c $< -o $@ 

Sources/%.o: srcs/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

libembedFiglet.a: $(OBJS)
	$(AR) libs/libembedFiglet.a $(OBJS) 

run:
	./test
	./example

doc:
	doxygen
	
clean:
	rm -f libs/libembedFiglet.a srcs/*.o