CC = /usr/bin/g++
CFLAGS =

sim: main.o generator.o
	$(CC) $(CFLAGS) -o sim main.o generator.o

main.o: generator.h main.cpp 
	$(CC) $(CFLAGS) -c main.cpp

generator.o: generator.h generator.cpp
	$(CC) $(CFLAGS) -c generator.cpp

clean:
	rm -f *.o sim
