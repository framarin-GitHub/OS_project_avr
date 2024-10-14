CC=gcc
CCOPTS=--std=gnu99 -g -Wall 
AR=ar

BINS=client

OBJS=serial_linux.o client.o 

HEADERS=serial_linux.h

LIBS=

%.o:	%.c $(HEADERS)
	$(CC) $(CCOPTS) -c -o $@  $<


.phony: clean all


all:	$(BINS) $(LIBS)

$(BINS): $(OBJS)
	$(CC) $(CCOPTS) -o $@ $^

clean:
	rm -rf *.o *~ $(LIBS) $(BINS)
