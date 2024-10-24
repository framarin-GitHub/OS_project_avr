#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "./serial_communication/serial_settings.h"
#include "./serial_communication/read_write_serial.h"
#include "./diagram_output/diagram_gnuplot.h"
#define HANDLE_ERROR(msg,err) \
	do{ \
	perror(msg); \
	exit(err); \
	} while(0)



int main(){

  plotDiag(2);


  // Serial initialization
  const char* serial_device = "/dev/ttyACM0";
  int baudrate = 19200;
  int fd = serialOpen(serial_device);
  serialSetInterfaceAttribs(fd, baudrate, 0);
  serialSetBlocking(fd, 1);
  printf("serial initialized\n");
  
  
  char to_send[1024] = "we send data via serial\n"; 
  char rec[1024];
  memset(rec, 0, 1024);
  
  readSerial(fd,rec); // reads empty at the beginning
  printf("%s\n", rec);
  writeSerial(fd,to_send);
  readSerial(fd,rec);
  printf("%s\n", rec);
  close(fd);
  
}
