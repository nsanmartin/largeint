CXXFLAGS = -O3 -std=c++11 -I../include -lm -lgmp

CPP_FILES = $(wildcard ../src/*.cpp)
_OBJS = $(subst .cpp,.o, $(CPP_FILES))
ODIR=../obj
OBJECTS = $(subst ../src/,, $(patsubst %,$(ODIR)/%,$(_OBJS)))

../obj/natural.o: $(CPP_FILES)
	g++ $(CXXFLAGS) -c -o $@ $<

timetests: add-times duplicate-times

add-times: $(OBJECTS)
	g++ -o ../build/$@ $@.cpp  $(OBJECTS) $(CXXFLAGS)


duplicate-times: $(OBJECTS)
	g++ -o ../build/$@ $@.cpp  $(OBJECTS) $(CXXFLAGS)










clean:
	rm ../obj/* ../build/* 
