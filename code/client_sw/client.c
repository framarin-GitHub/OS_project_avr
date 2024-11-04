#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include "./serial_communication/serial_settings.h"
#include "./serial_communication/read_write_serial.h"
#include "./diagram_output/diagram_gnuplot.h"
#include "./manip_data/struct_data.h"
#include "./manip_data/read_write_data.h"
#define HANDLE_ERROR(msg,err) \
	do{ \
	perror(msg); \
	exit(err); \
	} while(0)
#define HANDLE_ERROR_ERRNO(msg) \
	do{ \
	errno = 11;\
	perror(msg); \
	exit(11); \
	} while(0)


int main(){
  // Initialize data structures from data files
  initData();
  // Serial initialization
  const char* serial_device = "/dev/ttyACM0";
  int baudrate = 19200;
  int fd = serialOpen(serial_device);
  serialSetInterfaceAttribs(fd, baudrate, 0);
  serialSetBlocking(fd, 1);
  printf("//serial initialized ...\n");
   
  
  // CL menu cycles
  char user_input;
  do{
  printf("------------------------------------------------------------------------------\n");
  printf("WELCOME TO: Arduino current meter\n");
  printf("------------------------------------------------------------------------------\n\n");
  printf("What would you like to do?\n\n");
  printf("\t1) Query statistics\n");
  printf("\t2) Clear statistics\n");
  printf("\t3) Measure current\n\n");
  printf("\tq) Quit\n\n");

  scanf(" %c", &user_input);
  switch(user_input){
  case '1':
    do{
      printf("------------------------------------------------------------------------------\n");
      printf("What data do you want?\n");
      printf("\t1) last hour\n");
      printf("\t2) last month\n");
      printf("\t3) last day\n");
      printf("\t4) last year\n\n");
      printf("\tb) Back to main menu\n\n");
     
      scanf(" %c", &user_input);
      switch(user_input){
        case '1':
          plotDiag(0);
          break;
        case '2':
          plotDiag(1);
          break;
        case '3':
          plotDiag(2);
          break;
        case '4':
          plotDiag(3);
          break;        
      }
    } while(user_input != 'b');
    break;
  case '2':
    fclose(fopen("./diagram_output/data/hour.temp", "w"));
    fclose(fopen("./diagram_output/data/day.temp", "w"));
    fclose(fopen("./diagram_output/data/month.temp", "w"));
    fclose(fopen("./diagram_output/data/year.temp", "w"));
    printf("data cleared ...\n");
    break;
  case '3':
    printf("Insert the sampling rate(s): ");
    int sec_interval = 0;
    scanf("%d", &sec_interval);
    if(sec_interval == 0){
      printf("0 is not allowed\n");
      break; 
    }
    char to_send[500];
    char rec[500];
    memset(rec, 0, 500);
    // converts int to string
    sprintf(to_send, "%d\n", sec_interval);
    writeSerial(fd,to_send);
    while(1){
      readSerial(fd,rec);
      printf("\n%s", rec);
    }
    
    break;
  }
  
  
  } while(user_input != 'q');
  
  printf("closing pipe ...\n");
  close(fd);
}
