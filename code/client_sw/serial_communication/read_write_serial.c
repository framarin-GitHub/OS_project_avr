#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "./read_write_serial.h"
#define HANDLE_ERROR(msg,err) \
	do{ \
	perror(msg); \
	exit(err); \
	} while(0)

char readSerial(int fd, char* buf){
  int b_r = read(fd, buf, 1024);
  if(b_r == -1) HANDLE_ERROR("Unable to read from serial", errno);
  return b_r;
}

void writeSerial(int fd, char* to_send){
      char buf[1024];
      int l=strlen(to_send);
      strncpy(buf, to_send, l);
      buf[l]='\n';
      ++l;
      write(fd, buf, l);
}
