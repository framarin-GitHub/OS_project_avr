#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <termios.h>
#include "./serial_settings.h"
#define HANDLE_ERROR(msg,err) \
	do{ \
	perror(msg); \
	exit(err); \
	} while(0)


void serialSetInterfaceAttribs(int fd, int speed, int parity) {
  struct termios tty;
  // init termios struct
  memset(&tty, 0, sizeof tty);
  // copy from existing struct
  if (tcgetattr (fd, &tty) != 0) HANDLE_ERROR("error from tcgetattr \n", errno);
  switch (speed){
  case 19200:
    speed=B19200;
    break;
  case 57600:
    speed=B57600;
    break;
  case 115200:
    speed=B115200;
    break;
  case 230400:
    speed=B230400;
    break;
  case 576000:
    speed=B576000;
    break;
  case 921600:
    speed=B921600;
    break;
  default:
    HANDLE_ERROR("cannot set baudrate \n", speed);
  }
  // set in e out speed
  cfsetospeed (&tty, speed);
  cfsetispeed (&tty, speed);
  // sets "raw" mode
  cfmakeraw(&tty);
  tty.c_cflag |= (CREAD | CLOCAL); //enable receiver and ignore modem control
  tty.c_cflag &= ~CSIZE; //char size mask values cs5-8
  tty.c_cflag |=  CS8; //uno soltanto dei cs deve essere attivo e lo fanno ll.30-31
  tty.c_cflag &= ~CRTSCTS; //enable rts/cts hardware

  // sets the changes now
  if (tcsetattr (fd, TCSANOW, &tty) != 0) HANDLE_ERROR("error from tcsetattr \n", errno);
}

void serialSetBlocking(int fd, int should_block) {
  struct termios tty;
  memset(&tty, 0, sizeof tty);
  if (tcgetattr (fd, &tty) != 0) HANDLE_ERROR("error from tggetattr \n", errno);

  // 1 or 0 min char
  tty.c_cc[VMIN]  = should_block ? 1 : 0; 
  // 0.5 seconds read timeout
  tty.c_cc[VTIME] = 5; 

  if (tcsetattr (fd, TCSANOW, &tty) != 0) HANDLE_ERROR("error setting term attributes \n", errno);
}

int serialOpen(const char* name) {
  int fd = open(name, O_RDWR | O_NOCTTY | O_SYNC );
  if (fd < 0) HANDLE_ERROR("error opening serial, fd \n", errno);
  return fd;
}
