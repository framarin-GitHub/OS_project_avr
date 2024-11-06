#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "./struct_data.h"
#include "./handler_data.h"
#include "../serial_communication/serial_communication.h"
#define HANDLE_ERROR_ERRNO(msg) \
	do{ \
	errno = 11;\
	perror(msg); \
	exit(11); \
	} while(0)



extern ts_data* hour[60];
extern ts_data* day[24];
extern ts_data* month[30];
extern ts_data* year[12];

extern time_t start_time;

void insertSortData(int type, ts_data* to_ins){
  ts_data* temp1;
  ts_data* temp2; 
  int value_to_ins = 0;
  switch(type){
    case 0:
      temp1 = hour[0];
      temp2 = to_ins;
      for(int i = 0; i < 60; i++){
        hour[i] = temp2;
        temp2 = temp1;
        if(i == 59)
          break;
        temp1 = hour[i+1];
      }
      if(temp1 != 0)
        deleteTsData(temp1);
      break;
    case 1:
      for (int i = 0; i < 60; i++)
        value_to_ins += hour[i]->value;
      temp1 = day[0];
      temp2 = createTsData(value_to_ins/60, to_ins->timestamp);
      for(int i = 0; i < 24; i++){
        day[i] = temp2;
        temp2 = temp1;
        if(i == 23)
          break;
        temp1 = day[i+1];
      }
      if(temp1 != 0)
        deleteTsData(temp1);
      break;
    case 2:
      for (int i = 0; i < 24; i++)
        value_to_ins += day[i]->value;
      temp1 = month[0];
      temp2 = createTsData(value_to_ins/24, to_ins->timestamp);
      for(int i = 0; i < 30; i++){
        month[i] = temp2;
        temp2 = temp1;
        if(i == 29)
          break;
        temp1 = month[i+1];
      }
      if(temp1 != 0)
        deleteTsData(temp1);
      break;
    case 3:  
      for (int i = 0; i < 30; i++)
        value_to_ins += month[i]->value;
      temp1 = year[0];
      temp2 = createTsData(value_to_ins/30, to_ins->timestamp);
      for(int i = 0; i < 12; i++){
        year[i] = temp2;
        temp2 = temp1;
        if(i == 11)
          break;
        temp1 = year[i+1];
      }
      if(temp1 != 0)
        deleteTsData(temp1);
      break;
  }
} 

void deleteAllObjects(){
  for(int i = 0; i < 60; i++){
    if(hour[i] == 0)
      break;
    deleteTsData(hour[i]);
  }
  for(int i = 0; i < 24; i++){
    if(day[i] == 0)
      break;
    deleteTsData(day[i]);
  }
  for(int i = 0; i < 30; i++){
    if(month[i] == 0)
      break;
    deleteTsData(month[i]);
  }
  for(int i = 0; i < 12; i++){
    if(year[i] == 0)
      break;
    deleteTsData(year[i]);
  }
}

void initData(){
  start_time = getTime();
  memset(hour, 0, sizeof(ts_data*)*60);
  memset(day, 0, sizeof(ts_data*)*24);
  memset(month, 0, sizeof(ts_data*)*30);
  memset(year, 0, sizeof(ts_data*)*12);
}

void sendData(){
  uint8_t buf[1024];
  char temp[1024];
  memset(buf, 0, 1024);
  memset(temp, 0, 1024);
  for(int i = 0; i < 60; i++){
    printf("-%d\n", (int)hour[i]);
    if(hour[i] == 0) break;  
    sprintf((char*)temp, "%d ", hour[i]->value);
    strcpy((char*)buf, temp);
    sprintf((char*)temp, "%ld\n", hour[i]->timestamp);
    strcat((char*)buf, temp);
    UART_putString((uint8_t*) buf);
  }
  for(int i = 0; i < 24; i++){
    printf("-%d\n", (int)day[i]);
    if(day[i] == 0) break;
    sprintf((char*)temp, "%d ", day[i]->value);
    strcpy((char*)buf, temp);
    sprintf((char*)temp, "%ld\n", day[i]->timestamp);
    strcat((char*)buf, temp);
    UART_putString((uint8_t*) buf);
  }
  for(int i = 0; i < 30; i++){
    printf("-%d\n", (int)month[i]);
    if(month[i] == 0) break;
    sprintf((char*)temp, "%d ", month[i]->value);
    strcpy((char*)buf, temp);
    sprintf((char*)temp, "%ld\n", month[i]->timestamp);
    strcat((char*)buf, temp);
    UART_putString((uint8_t*) buf);
  }
  for(int i = 0; i < 12; i++){
    printf("-%d\n", (int)year[i]);
    if(year[i] == 0) break;
    sprintf((char*)temp, "%d ", year[i]->value);
    strcpy((char*)buf, temp);
    sprintf((char*)temp, "%ld\n", year[i]->timestamp);
    strcat((char*)buf, temp);
    UART_putString((uint8_t*) buf);
  }
}
