CFLAGS = -std=c99

.PHONY = all clean

all: test/main.c scrutil.o
	$(CC) $(CFLAGS) -I src/ test/main.c scrutil.o -otestscrutil

scrutil.o: src/scrutil.h src/scrutil.c
	$(CC) $(CFLAGS) -c src/scrutil.c -oscrutil.o

clean:
	$(RM) scrutil.o
	$(RM) testscrutil
