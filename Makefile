CC = gcc
CFLAGS = -Wall

ADHOCC_SRCS = adhocc.o string.o

build: adhocc.out

%.o: %.c
	$(CC) $(CFLAGS) -c $<

adhocc.out: $(ADHOCC_SRCS) adhocc_default.c adhocc.h
	$(CC) $(CFLAGS) -o adhocc.out $(ADHOCC_SRCS)

test: adhocc.out
	./test.sh

clean:
	rm adhocc.out $(ADHOCC_SRCS)
