GTESTDIR=/usr
MPI_LIBS= -lmpi++ -lmpi
CXX=g++

OBJECTS = \
   tower.o \
   entity.o \
   object.o \
   map.o \
   sim.o \
   path.o

all: td tdmpi test

td: $(OBJECTS) td.o
	$(CXX) -o $@ $(OBJECTS) td.o

tdmpi: $(OBJECTS) tdmpi.o
	$(CXX) -o $@ $(MPI_LIBS) $(OBJECTS) tdmpi.o

test: $(OBJECTS) test.cpp
	$(CXX) -g -lpthread \
	-I$(GTESTDIR)/include \
	test.cpp \
	$(GTESTDIR)/lib/libgtest.a \
	$(GTESTDIR)/lib/libgtest_main.a \
	$(OBJECTS) \
	-o test
	./test

clean:
	rm -rf *.o test td tdmpi
