#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include "./alarm.h"

#define HANDLE_ERROR(msg,err) \
	do{ \
	perror(msg); \
	exit(err); \
	} while(0)

static void handler(int signum){
  alarm_flag = 0;
}

void initSignalHandler(){
  struct sigaction sa = { 0 };
  sa.sa_handler = handler;
  sa.sa_flags = SA_RESTART; // restart readSerial() when interrupted by handler                  
  int ret = sigaction(SIGALRM, &sa, NULL);  
  if (ret == -1) HANDLE_ERROR("Sigaction failure\n", errno);
  printf("//signal handler initialized ...\n");
}
