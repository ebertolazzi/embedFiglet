SRCS = Sources/*.cc test.cc
CXX  = c++

all:    main

main:	$(SRCS)
	$(CXX) -I./Headers -o test $(SRCS)
