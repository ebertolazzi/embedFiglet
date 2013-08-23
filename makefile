SRCS = Sources/*.cc
CXX  = c++

all:    main

main:	$(SRCS)
	$(CXX) -I./Headers -o test test.cc $(SRCS)

run:	$(SRCS)
	./test