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
int readSerial(int fd, char* buf){
  char* temp_buf = buf;
  while(1){
    char char_read = getCharSerial(fd);  
    *buf = char_read;
    buf++;
    // reading a \n  or a \r return results
    // in forcedly terminating the string
    if(char_read=='\n'||char_read=='\r'){
      *buf=0;
      buf++;
      return buf-temp_buf;
    }
  }
}

void writeSerial(int fd, char* to_send){
      char buf[1024];
      int l = strlen(to_send);
      strncpy(buf, to_send, l);
      buf[l] = '\n';
      l++;
      
      int flag = write(fd, buf, l);
      if(flag == -1) HANDLE_ERROR("Unable to write on serial", errno);
}
