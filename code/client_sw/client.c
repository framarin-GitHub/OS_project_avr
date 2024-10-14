#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "./serial_linux.h"
#define HANDLE_ERROR(msg,err) \
	do{ \
	perror(msg); \
	exit(err); \
	} while(0)



int main(){
  //general settings
  const char* serial_device = "/dev/ttyACM0";
  int baudrate = 19200;
  int read_or_write = 1; // 1 read 0 write
  
  int fd = 0; serialOpen(serial_device);
  serialSetInterfaceAttribs(fd, baudrate, 0);
  serialSetBlocking(fd, 1);
  
  printf("in place\n");
  int i = 0;
  while(i < 4) {
    char buf[1024];
    memset(buf, 0, 1024);
      int nchars=read(fd, buf,2);
      printf("%s \n", buf);
      i++;
      usleep(50);
  }
  
  
}
