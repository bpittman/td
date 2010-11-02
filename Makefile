GTESTDIR=$(HOME)/local/gtest-1.5.0/intel/
CXX=icc
all: td test

test:
	$(CXX) -g -lpthread -I$(GTESTDIR)/include test.cpp $(GTESTDIR)/lib/libgtest.a $(GTESTDIR)/lib/libgtest_main.a -o test
	./test

clean:
	rm test
