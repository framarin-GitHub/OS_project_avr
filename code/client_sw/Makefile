CC=gcc
CCOPTS=--std=gnu99 -g -Wall 
AR=ar

BINS=client

OBJS=./serial_communication/serial_settings.o ./serial_communication/read_write_serial.o client.o ./diagram_output/diagram_gnuplot.o ./alarm/alarm.o ./data_helpers/data_helpers.o

HEADERS=./serial_communication/serial_settings.h ./serial_communication/read_write_serial.h ./diagram_output/diagram_gnuplot.h ./alarm/alarm.h ./data_helpers/data_helpers.h

LIBS=

%.o:	%.c $(HEADERS)
	$(CC) $(CCOPTS) -c -o $@  $<


.phony: clean all


all:	$(BINS) $(LIBS)

$(BINS): $(OBJS)
	$(CC) $(CCOPTS) -o $@ $^

clean:
	rm -rf *.o *~ $(LIBS) $(BINS)
