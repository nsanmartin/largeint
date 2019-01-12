CXXFLAGS = -g -std=c++11 -I../include

CPP_FILES = $(wildcard ../src/*.cpp)
_OBJS = $(subst .cpp,.o, $(CPP_FILES))
ODIR=../obj
OBJECTS = $(subst ../src/,, $(patsubst %,$(ODIR)/%,$(_OBJS)))

../obj/nat.o: $(CPP_FILES)
	g++ $(CXXFLAGS) -c -o $@ $<

# obj/%.o: ../src/%.cpp obj
# 	g++ $(CXXFLAGS) -c -o ../$@ $<

test:
	echo $(OBJECTS)

tincr: $(OBJECTS)
	g++ $(CXXFLAGS) -o ../build/$@ $@.cpp  $(OBJECTS)


tincr0: $(OBJECTS)
	g++ $(CXXFLAGS) -o ../build/$@ $@.cpp  $(OBJECTS)

tsum: $(OBJECTS)
	g++ $(CXXFLAGS) -o ../build/$@ $@.cpp  $(OBJECTS)

tsum0: $(OBJECTS)
	g++ $(CXXFLAGS) -o ../build/$@ $@.cpp  $(OBJECTS)







clean:
	rm ../obj/* ../build/*
