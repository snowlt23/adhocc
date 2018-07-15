CC = gcc
CFLAGS = -Wall

ADHOCC_SRCS = adhocc.o string.o

build: adhocc

%.o: %.c
	$(CC) $(CFLAGS) -c $<

adhocc: $(ADHOCC_SRCS) adhocc.h
	$(CC) $(CFLAGS) -o adhocc $(ADHOCC_SRCS)

test: build
	./test.sh
