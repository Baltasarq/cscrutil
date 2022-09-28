CFLAGS = -std=c99

.PHONY = all

all: test/main.c scrutil.o
	$(CC) $(CFLAGS) test/main.c scrutil.o -otestscrutil

scrutil.o: src/scrutil.h src/scrutil.c
	$(CC) $(CFLAGS) -c src/scrutil.c -oscrutil
