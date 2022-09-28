
.PHONY all

all: test/main.c scrutil
  $(CC) test/main.c scrutil -otestscrutil
  
scrutil: src/scrutil.h src/scrutil.c
  $(CC) -c test/scrutil.c -oscrutil
