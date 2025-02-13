#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include "./serial_communication/serial_settings.h"
#include "./serial_communication/read_write_serial.h"
#include "./diagram_output/diagram_gnuplot.h"
#include "./alarm/alarm.h"
#include "./data_helpers/data_helpers.h"

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
	
extern volatile int alarm_flag;
extern struct tm* timestamp;

char send[1024];
char rec[1024];

void commProtocolRoutine(int mode, int fd);

int main(int argc, char *argv[]){
  // Serial initialization
  const char* serial_device = "/dev/ttyACM0";
  int baudrate = 19200;
  int fd = serialOpen(serial_device);
  serialSetInterfaceAttribs(fd, baudrate, 0, 1);
  printf("//serial initialized ...\n");
  // Initialize signal handler for sigalrm
  initSignalHandler();
  
  memset(send, 0, 1024);
  memset(rec, 0, 1024);
  
  // CL menu cycles
  char user_input;
  if(argc > 1 && argv[1][0] == 'f'){
    readSerial(fd,rec);
    printf("//first connection ... \n%s", rec);
    printf("------------------------------------------------------------------------------\n");
    int Rf = -1;
    int R1 = -1;
    double partition = -1;
    double gain = 0;
    do{
    printf("define circuit:\n");
    printf("0 is not allowed!\n");
      printf("\tRf(Ohm): ");
      scanf(" %d", &Rf);
      printf("\tR1(Ohm): ");
      scanf(" %d", &R1);
      printf("\tpartition(0,1]: ");
      scanf(" %lf", &partition);
    } while( (Rf == 0) || (R1 == 0) || (partition == 0));
    // gain formula for non invertent transresistence circuit
    gain = 1+(Rf/((double)R1));
    printf("gain : %lf\n", gain);
    // send data
    commProtocolRoutine(0, fd);
      sprintf(send, "%lf", gain);
      writeSerial(fd, send); 
      sprintf(send, "%lf", partition);
      writeSerial(fd, send); 
  }
  
  do{
  printf("------------------------------------------------------------------------------\n");
  printf("\t\t\tWELCOME TO: Arduino current meter\n");
  printf("------------------------------------------------------------------------------\n\n");
  printf("What would you like to do?\n\n");
  printf("\t1) Query statistics\n");
  printf("\t2) Clear statistics\n");
  printf("\t3) Measure current\n");
  printf("\t4) Fast sampling\n\n");
  printf("\tq) Quit\n\n");
  scanf(" %c", &user_input);
  switch(user_input){
  case '1': 
    commProtocolRoutine(1, fd);   
    // Get timestamp to recover timings
    time_t rawtime;
    time(&rawtime);
    timestamp = localtime(&rawtime);
    recData(fd);
    char time_string[500] = "";
    strcpy(time_string, asctime(timestamp));
    // remove \n from time_string to use it in gnuplot label
    time_string[strcspn(time_string, "\n")] = 0;
    printf("//data downloaded at %s\n", time_string);
           
    do{
      printf("------------------------------------------------------------------------------\n");
      printf("What data do you want?\n");
      printf("\t1) latest hour\n");
      printf("\t2) latest day\n");
      printf("\t3) latest month\n");
      printf("\t4) latest year\n\n");
      printf("\tb) Back to main menu\n\n");
      scanf(" %c", &user_input);
      switch(user_input){
        case '1':
          plotDiag(0, time_string);
          break;
        case '2':
          plotDiag(1, time_string);
          break;
        case '3':
          plotDiag(2, time_string);
          break;
        case '4':
          plotDiag(3, time_string);
          break;        
      }
    } while(user_input != 'b');
    break;
  case '2':
    commProtocolRoutine(2, fd);
    break;
  case '3':
    printf("Insert the sampling rate(s): ");
    int sec_interval = 0;
    scanf("%d", &sec_interval);
    if(sec_interval == 0 || sec_interval > 60){
      printf("//insert a valid value\n");
      break; 
    }
    printf("Insert how long you want to measure(s): ");
    int sec_alarm = 0;
    scanf("%d", &sec_alarm);
    if(sec_alarm == 0){
      printf("//0 is not allowed\n");
      break; 
    }
    // start online mode
    commProtocolRoutine(3, fd);
    // converts int to string to send sampling rate
    sprintf(send, "%d", sec_interval);
    writeSerial(fd, send);   
    alarm_flag = 1;
    alarm(sec_alarm);
    while(alarm_flag){        
      readSerial(fd,rec);
      printf("\n%s", rec);
    } 
    // ends online mode
    commProtocolRoutine(4, fd);
    break;
    case '4':
      printf("Insert the number of samples: ");
      int samples = 0;
      scanf("%d", &samples);
      // start fast sampling
      commProtocolRoutine(5, fd);
      sprintf(send, "%d", samples);
      writeSerial(fd, send);
      recFastSamples(fd, samples);
      plotDiag(4, NULL);    
      break;
    case 'q':
      break;
    default:
      user_input = '0';
  }
  } while(user_input != 'q');
  // closing routines
  printf("//closing pipe ...\n");
  close(fd);
}




void commProtocolRoutine(int mode, int fd){
  switch(mode){
    case 0: 
      strcpy(send, "i");
      break;
    case 1: 
      strcpy(send, "q");
      break;
    case 2:
      strcpy(send, "c");
      break;
    case 3:
      strcpy(send, "s");
      break;
    case 4:
      strcpy(send, "e");
      break;
    case 5:
      strcpy(send, "f");
      break;
    default:
      strcpy(send, "?");
  }    
  writeSerial(fd,send);
  // command is echoed 
  readSerial(fd,rec);
  // Enable for debug 
  /* printf("avr\\%s", rec);  */
  // feedback message
  readSerial(fd,rec);
  printf("%s", rec);
}
