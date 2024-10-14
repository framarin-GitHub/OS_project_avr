#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "./serial_communication/serial_linux.h"
#include "./read_write_serial.h"
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
  
  char char_read;
  int i = 0;
  while(i<9){
  char char_read = getCharSerial(fd);
   	printf("%c", char_read);
   	usleep(50);
   	i++;
   }
  close(fd);
  
}
