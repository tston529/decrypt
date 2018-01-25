OBJS = main.o Word.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

p1: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o p1

main.o: Word.h
	$(CC) $(CFLAGS) main.cpp -std=c++14

Word.o: Word.h Word.cpp
	$(CC) $(CFLAGS) Word.cpp -std=c++14

clean:
	del p1.exe *.o