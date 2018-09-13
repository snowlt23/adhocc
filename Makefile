CC = gcc
CFLAGS = -Wall

ADHOCC_SRCS = adhocc.o string.o vector.o

build: adhocc.out

%.o: %.c
	$(CC) $(CFLAGS) -c $<

adhocc.out: $(ADHOCC_SRCS) adhocc_default.c adhocc.h
	$(CC) $(CFLAGS) -o adhocc.out $(ADHOCC_SRCS)

.PHONY: test
test: adhocc.out
	./test.sh

clean:
	rm -rf adhocc.out $(ADHOCC_SRCS) out.c adhocctmp/
