#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "./handler_data.h"
#include "../serial_communication/serial_communication.h"

extern int hour[60];
extern int day[24];
extern int month[30];
extern int year[12];

void insertSortData(int type, int to_ins){
  int temp1;
  int temp2; 
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
      break;
    case 1:
      for (int i = 0; i < 60; i++)
        value_to_ins += hour[i];
      temp1 = day[0];
      temp2 = value_to_ins/60;
      for(int i = 0; i < 24; i++){
        day[i] = temp2;
        temp2 = temp1;
        if(i == 23)
          break;
        temp1 = day[i+1];
      }
      break;
    case 2:
      for (int i = 0; i < 24; i++)
        value_to_ins += day[i];
      temp1 = month[0];
      temp2 = value_to_ins/24;
      for(int i = 0; i < 30; i++){
        month[i] = temp2;
        temp2 = temp1;
        if(i == 29)
          break;
        temp1 = month[i+1];
      }
      break;
    case 3:  
      for (int i = 0; i < 30; i++)
        value_to_ins += month[i];
      temp1 = year[0];
      temp2 = value_to_ins/30;
      for(int i = 0; i < 12; i++){
        year[i] = temp2;
        temp2 = temp1;
        if(i == 11)
          break;
        temp1 = year[i+1];
      }
      break;
  }
} 

void initData(){
  memset(hour, -1, sizeof(int)*60);
  memset(day, -1, sizeof(int)*24);
  memset(month, -1, sizeof(int)*30);
  memset(year, -1, sizeof(int)*12);
}

void sendData(){
  uint8_t buf[1024];
  memset(buf, 0, 1024);
  for(int i = 0; i < 60; i++){
    if(hour[i] == -1) {
      sprintf((char*)buf, "%d\n", hour[i]);
      UART_putString((uint8_t*) buf);
      break;
    }
    sprintf((char*)buf, "%d\n", hour[i]);
    UART_putString((uint8_t*) buf);
  }
  for(int i = 0; i < 60; i++){
    if(day[i] == -1) {
      sprintf((char*)buf, "%d\n", day[i]);
      UART_putString((uint8_t*) buf);
      break;
    } 
    sprintf((char*)buf, "%d\n", day[i]);
    UART_putString((uint8_t*) buf);
  }
  for(int i = 0; i < 60; i++){
    if(month[i] == -1) {
      sprintf((char*)buf, "%d\n", month[i]);
      UART_putString((uint8_t*) buf);
      break;
    }  
    sprintf((char*)buf, "%d\n", month[i]);
    UART_putString((uint8_t*) buf);
  }
  for(int i = 0; i < 60; i++){
    if(year[i] == -1) {
      sprintf((char*)buf, "%d\n", year[i]);
      UART_putString((uint8_t*) buf);
      break;
    }  
    sprintf((char*)buf, "%d\n", year[i]);
    UART_putString((uint8_t*) buf);
  }
}





