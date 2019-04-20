CXXFLAGS = -g -std=c++11 -I./include -lm -lgmp

CPP_FILES = $(wildcard ./src/*.cpp)
_OBJS = $(subst .cpp,.o, $(CPP_FILES))
ODIR=./obj
OBJECTS = $(subst ./src/,, $(patsubst %,$(ODIR)/%,$(_OBJS)))

obj/nat.o: $(CPP_FILES)
	g++ $(CXXFLAGS) -c -o $@ $<

add: $(OBJECTS)
	g++ -o ./build/$@ $@.cpp  $(OBJECTS) $(CXXFLAGS)


tags:
	ctags -R -e .



