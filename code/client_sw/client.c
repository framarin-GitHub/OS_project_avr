#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "./serial_communication/serial_settings.h"
#include "./serial_communication/read_write_serial.h"
#define HANDLE_ERROR(msg,err) \
	do{ \
	perror(msg); \
	exit(err); \
	} while(0)



int main(){
  //general settings
  const char* serial_device = "/dev/ttyACM0";
  int baudrate = 19200;
  
  int fd = serialOpen(serial_device);
  serialSetInterfaceAttribs(fd, baudrate, 0);
  serialSetBlocking(fd, 1);
  printf("serial initialized\n");
  char to_send[1024] = "we send data via serial"; 
  char rec[1024];
  memset(rec, 0, 1024);
  while(1){
  readSerial(fd,rec);
  printf("%s\n", rec);
  usleep(4999);
  writeSerial(fd,to_send);
  }
  close(fd);
  
}
