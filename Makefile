.PHONE: all clean

# variables definition
CPPFLAGS = -c -Wall -g
COMM_FILES = debug.h

# rules
all: b.exe

b.exe : main.o big_float.o
	g++ -o $@ $^
	
big_float.o: big_float.cpp big_float.h $(COMM_FILES)
	g++ $(CPPFLAGS) -o $@ $<

main.o: main.cpp $(COMM_FILES)
	g++ $(CPPFLAGS) -o $@ $<

clean:
	-rm -rf *.~vsd *.o *.exe *.out 2>/dev/null

