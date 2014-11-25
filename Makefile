.PHONE: all clean

# variables definition
CPPFLAGS = -c -Wall

all: b.exe

b.exe : main.o big_float.o
	g++ -o @$ $^
	
big_float.o: big_float.cpp big_float.h
	g++ $(CPPFLAGS) -o $@ $^

main.o: main.c
	g++ $(CPPFLAGS) -o $@ $^

clean:
	-rm -rf *.~vsd *.o *.exe *.out 2>/dev/null

