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

char getCharSerial(int fd){
  char res;
  int b_r = read(fd, &res, sizeof(res));
  if(b_r == -1) HANDLE_ERROR("Unable to read from serial", errno);
  return res;
}
