GTESTDIR=/usr
CXX=g++

OBJECTS = \
   tower.o \
   entity.o \
   object.o

all: td test

td: $(OBJECTS) td.o
	$(CXX) -o $@ $(OBJECTS) td.o

test: test.cpp
	$(CXX) -g -lpthread \
	-I$(GTESTDIR)/include \
	test.cpp \
	$(GTESTDIR)/lib/libgtest.a \
	$(GTESTDIR)/lib/libgtest_main.a \
	$(OBJECTS) \
	-o test
	./test

clean:
	rm -rf *.o test
