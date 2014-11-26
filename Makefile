.PHONE: all clean

# variables definition
CPPFLAGS = -c -Wall

# rules
all: b.exe

b.exe : test.o big_float.o
	g++ -o $@ $^
	
big_float.o: big_float.cpp big_float.h
	g++ $(CPPFLAGS) -o $@ $<

test.o: test.cpp
	g++ $(CPPFLAGS) -o $@ $^

clean:
	-rm -rf *.~vsd *.o *.exe *.out 2>/dev/null

