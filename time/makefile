CXXFLAGS = -Wall -O3 -std=c++11 -I../include -I../tests -lm -lgmp

CPP_FILES = $(wildcard ../src/*.cpp)
_OBJS = $(subst .cpp,.o, $(CPP_FILES))
ODIR=../obj
OBJECTS = $(subst ../src/,, $(patsubst %,$(ODIR)/%,$(_OBJS)))
BUILD=../build
obj:
	if [ ! -d $(ODIR) ]; then mkdir $(ODIR); fi

build:
	if [ ! -d $(BUILD) ]; then mkdir $(BUILD); fi

../obj/natural.o: $(CPP_FILES) obj
	g++ $(CXXFLAGS) -c -o $@ $<

timetests: add-times duplicate-times mul-mpz-lint mul-mpz-lint

add-times: $(OBJECTS) build
	g++ -o $(BUILD)/$@ $@.cpp  $(OBJECTS) $(CXXFLAGS)


duplicate-times: $(OBJECTS) build
	g++ -o $(BUILD)/$@ $@.cpp  $(OBJECTS) $(CXXFLAGS)

mul-mpz-lint: $(OBJECTS) build
	g++  -o $(BUILD)/$@ $@.cpp  $(OBJECTS) $(CXXFLAGS)



sum-mpz-lint: $(OBJECTS) build
	g++  -o $(BUILD)/$@ $@.cpp  $(OBJECTS) $(CXXFLAGS)


clean:
	rm $(ODIR)/* $(BUILD)/* 
