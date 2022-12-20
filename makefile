all: q1 q2

CC=gcc 
CFLAGS=-Wall -std=c99 -pedantic

q1: q1.c
	$(CC) $(CFLAGS) q1.c -o q1
q2: q2.c
	$(CC) $(CFLAGS) q2.c -o q2
clean:
	rm *.o q1.exe