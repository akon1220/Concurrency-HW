CC = gcc
CFLAGS = -Wall -O2

PROGS = thread1 thread2 thread3

all: $(PROGS)

thread1: thread1.c mythreads.h .thread_util.o
	$(CC) $(CFLAGS) -o $@  $< .thread_util.o -lpthread

thread2: thread2.c mythreads.h .thread_util.o
	$(CC) $(CFLAGS) -o $@  $< .thread_util.o -lpthread

thread3: thread3.c mythreads.h .thread_util.o
	$(CC) $(CFLAGS) -o $@  $< .thread_util.o -lpthread

clean:
	rm -f $(PROGS)


