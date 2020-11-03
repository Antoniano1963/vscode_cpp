
CXX =/usr/local/Cellar/gcc/10.2.0/bin/g++-10
LD = $(CXX)

CXXFLAGS=-mavx2 -std=c++11  -fopenmp -O3
LDFLAGS=-fopenmp
#

dotp: main.o matoperation.o
	$(LD) $+ -o $@  $(LDFLAGS)

main.o:main.cpp

matoperation.o:matoperation.cpp

clean: 
	rm -f *.o dotp
