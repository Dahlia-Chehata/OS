CC=gcc
CFLAGS=-Wall -Wno-unused-value

caltrain: caltrain-runner.c caltrain.c caltrain.h
	$(CC) -c caltrain.c -o caltrain.o
	$(CC) -c caltrain-runner.c -o caltrain-runner.o
	$(CC) $(CFLAGS) caltrain.o caltrain-runner.o -o caltrain -lpthread

