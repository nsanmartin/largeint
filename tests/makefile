CXXFLAGS = -O3  -std=c++11 -I../include -I. -lm -lgmp

CPP_FILES = $(wildcard ../src/*.cpp)
_OBJS = $(subst .cpp,.o, $(CPP_FILES))
ODIR=../obj
OBJECTS = $(subst ../src/,, $(patsubst %,$(ODIR)/%,$(_OBJS)))

../obj/natural.o: $(CPP_FILES)
	g++ $(CXXFLAGS) -c -o $@ $<

tests: tincr tincr0 tsum tsum0 tread tduplicate tduplicate1 \
	tlastbit   tmmm-rand \
	tdigit-mul tdigit-mul-rand tmul tmul-rand tmulmul-rand

tests-depr: tmul-digits-low tmul-digits-high tmul-digit-pair \
	tmul-digit-pair-times 

tincr: $(OBJECTS)
	g++ -o ../build/$@ $@.cpp  $(OBJECTS) $(CXXFLAGS)


tincr0: $(OBJECTS)
	g++ -o ../build/$@ $@.cpp  $(OBJECTS) $(CXXFLAGS)

tsum: $(OBJECTS)
	g++ -o ../build/$@ $@.cpp  $(OBJECTS) $(CXXFLAGS)

tsum0: $(OBJECTS)
	g++ -o ../build/$@ $@.cpp  $(OBJECTS) $(CXXFLAGS)

tread: $(OBJECTS)
	g++ -o ../build/$@ $@.cpp  $(OBJECTS) $(CXXFLAGS)

tduplicate: $(OBJECTS)
	g++  -o ../build/$@ $@.cpp  $(OBJECTS) $(CXXFLAGS)

tduplicate1: $(OBJECTS)
	g++  -o ../build/$@ $@.cpp  $(OBJECTS) $(CXXFLAGS)


tlastbit: $(OBJECTS)
	g++  -o ../build/$@ $@.cpp  $(OBJECTS) $(CXXFLAGS)


tmul-digits-low: $(OBJECTS)
	g++  -o ../build/$@ $@.cpp  $(OBJECTS) $(CXXFLAGS)

tmul-digits-high: $(OBJECTS)
	g++  -o ../build/$@ $@.cpp  $(OBJECTS) $(CXXFLAGS)

tmul-digit-pair: $(OBJECTS)
	g++  -o ../build/$@ $@.cpp  $(OBJECTS) $(CXXFLAGS)

tmul-digit-pair-times: $(OBJECTS)
	g++  -o ../build/$@ $@.cpp  $(OBJECTS) $(CXXFLAGS)

tdigit-mul: $(OBJECTS)
	g++  -o ../build/$@ $@.cpp  $(OBJECTS) $(CXXFLAGS)


tdigit-mul-rand: $(OBJECTS)
	g++  -o ../build/$@ $@.cpp  $(OBJECTS) $(CXXFLAGS)


tmul: $(OBJECTS)
	g++  -o ../build/$@ $@.cpp  $(OBJECTS) $(CXXFLAGS)

tmul-rand: $(OBJECTS)
	g++  -o ../build/$@ $@.cpp  $(OBJECTS) $(CXXFLAGS)

tmulmul-rand: $(OBJECTS)
	g++  -o ../build/$@ $@.cpp  $(OBJECTS) $(CXXFLAGS)

tsum-rand: $(OBJECTS)
	g++  -o ../build/$@ $@.cpp  $(OBJECTS) $(CXXFLAGS)

tmmm-rand: $(OBJECTS)
	g++  -o ../build/$@ $@.cpp  $(OBJECTS) $(CXXFLAGS)



clean:
	rm ../obj/* ../build/*
