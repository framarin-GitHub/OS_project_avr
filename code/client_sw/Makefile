CC=gcc
CCOPTS=--std=gnu99 -g -Wall 
AR=ar

BINS=client

OBJS=./serial_communication/serial_settings.o ./serial_communication/read_write_serial.o client.o ./diagram_output/diagram_gnuplot.o ./manip_data/struct_data.o ./manip_data/read_write_data.o ./alarm/alarm.o

HEADERS=./serial_communication/serial_settings.h ./serial_communication/read_write_serial.h ./diagram_output/diagram_gnuplot.h ./manip_data/struct_data.h ./manip_data/read_write_data.h ./alarm/alarm.h

LIBS=

%.o:	%.c $(HEADERS)
	$(CC) $(CCOPTS) -c -o $@  $<


.phony: clean all


all:	$(BINS) $(LIBS)

$(BINS): $(OBJS)
	$(CC) $(CCOPTS) -o $@ $^

clean:
	rm -rf *.o *~ $(LIBS) $(BINS)
