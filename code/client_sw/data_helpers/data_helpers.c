#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "./data_helpers.h"
#include "../serial_communication/read_write_serial.h"
#define HANDLE_ERROR_ERRNO(msg) \
	do{ \
	errno = 11;\
	perror(msg); \
	exit(11); \
	} while(0)

char rec[1024];

extern int hour[60];
extern int day[24];
extern int month[30];
extern int year[12];

extern struct tm* timestamp;

void writeDataToFile(){
  FILE* f_h = fopen("./diagram_output/data/hour.temp", "w+");
  FILE* f_d = fopen("./diagram_output/data/day.temp", "w+");
  FILE* f_m = fopen("./diagram_output/data/month.temp", "w+");
  FILE* f_y = fopen("./diagram_output/data/year.temp", "w+");
  
  int m = timestamp->tm_min;
  for(int i = 0; i < 60; i++){
    fprintf(f_h,"%d %d\n", m, hour[i]);   
    m--;
  }
  int h = timestamp->tm_hour; 
  for(int i = 0; i < 24; i++){
    fprintf(f_d,"%d %d\n", h, day[i]);
    h--;
  }  
  int d = timestamp->tm_mday;
  for(int i = 0; i < 30; i++){
    fprintf(f_m,"%d %d\n", d, month[i]);
    d--;
  }
  int mo = timestamp->tm_mon;
  for(int i = 0; i < 12; i++){
    fprintf(f_y,"%d %d\n", mo+1, year[i]);
    mo--;
  }
  
  fclose(f_h);
  fclose(f_d);
  fclose(f_m);
  fclose(f_y);
}

void recData(int fd){
  memset(hour, -1, sizeof(int)*60);
  memset(day, -1, sizeof(int)*24);
  memset(month, -1, sizeof(int)*30);
  memset(year, -1, sizeof(int)*12);
  for(int i = 0; i < 60; i++){
    readSerial(fd,rec);
    int value = atoi(rec);
    if(value == -1) break;
    hour[i] = value;
  }
  for(int i = 0; i < 24; i++){
    readSerial(fd,rec);
    int value = atoi(rec);
    if(value == -1) break;
    day[i] = value;
  }
  for(int i = 0; i < 30; i++){
    readSerial(fd,rec);
    int value = atoi(rec);
    if(value == -1) break;
    month[i] = value;
  }
  for(int i = 0; i < 12; i++){
    readSerial(fd,rec);
    int value = atoi(rec);
    if(value == -1) break;
    year[i] = value;
  }
  writeDataToFile();
}

void recFastSamples(int fd, int samples){
  FILE* f_s = fopen("./diagram_output/data/fast_sample.temp", "w+");
  int counter = 0;
  while(samples--){
    readSerial(fd, rec);
    int value = atoi(rec);
    fprintf(f_s,"%d %d\n", counter++, value);
  }
  fclose(f_s);
}
