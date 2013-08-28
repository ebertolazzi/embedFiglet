SRCS = \
Sources/Figlet.cc \
Sources/Figlet_Font_banner.cc \
Sources/Figlet_Font_big.cc \
Sources/Figlet_Font_doom.cc \
Sources/Figlet_Font_larry3d.cc \
Sources/Figlet_Font_mini.cc \
Sources/Figlet_Font_script.cc \
Sources/Figlet_Font_small.cc \
Sources/Figlet_Font_standard.cc \
Sources/Figlet_Font_straight.cc

OBJS = $(SRCS:.cc=.o)
DEPS = Headers/Figlet.hh

#CC     = llvm-gcc
#CXX    = llvm-g++
#CC     = clang
#CXX    = clang++
CC     = gcc
CXX    = g++

CFLAGS =  -I./Headers -Wall -pedantic -O3
LIBS   = -L. -lembedFiglet

#AR     = ar rcs
AR     = libtool -static -o 

all: libembedFiglet.a
	$(CXX) $(CFLAGS) -o test test.cc $(LIBS)
	$(CXX) $(CFLAGS) -o example example.cc $(LIBS)

Sources/%.o: Sources/%.cc $(DEPS)
	$(CXX) $(CFLAGS) -c $< -o $@ 

Sources/%.o: Sources/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

libembedFiglet.a: $(OBJS)
	$(AR) libembedFiglet.a $(OBJS) 

run:
	./test
	./example

doc:
	doxygen
	
clean:
	rm -f libembedFiglet.a Sources/*.o