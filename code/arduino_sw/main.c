#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <avr/io.h>
#include "./avr_common/uart.h" // this includes the printf and initializes it
#include "./analog_read/analog_read.h"
#include "./serial_communication/serial_communication.h"
#include "./manip_data/handler_data.h"

extern int hour[60];
extern int day[24];
extern int month[30];
extern int year[12];

int online_mode;

uint8_t buf[1024];

int main(void){
  // this initializes the printf/uart thingies
  printf_init();
  UART_init();
  // Initialize global variables
  initData();
  // Init offline
  online_mode = 0;
    
  int i1 = 0;
  int i2 = 0;
  int i3 = 0;
  int i4 = 0;
  
  int value_read = 0; 
  int to_ins = -1;
  int sec_interval = 1;
  
  while(1){
    if(UCSR0A & (1<<RXC0)){
      UART_getString(buf);	
      UART_putString((uint8_t*) buf);
      switch(buf[0]){
        case 'c':
          UART_putString((uint8_t*)"clearing stats ...\n");
          initData();
          break;
        case 'q':
          UART_putString((uint8_t*)"sending data ...\n");
          sendData();          
          break;
        case 'e':
          UART_putString((uint8_t*)"ending online mode ...\n");
          online_mode = 0;
          break;
        case 's':
          UART_putString((uint8_t*)"starting online mode, send me the interval ...\n");
          online_mode = 1;
          UART_getString(buf);
          sec_interval = atoi((char*)buf);
          break;
        default:
          UART_putString((uint8_t*)"what have you sent to me?\n");
      }
    }  
    int value = analogRead(0);
    value_read += value;
    i1++;
    // sending data in online mode every sec_interval seconds
    if(online_mode && (i1%sec_interval == 0)){
      sprintf((char*)buf, "%d\n", value);
      UART_putString(buf);    
    }
    // inserting one minute mean in hour array
    if(i1%60 == 0){
      to_ins = value_read/60;
      insertSortData(0, to_ins);
      value_read = 0;
      i1 = 0;
      i2++;
    }
    if(i2%60 == 0){
       insertSortData(1, to_ins);
       i2 = 0;
       i3++;
    }
    if(i3%24 == 0){
      insertSortData(2, to_ins);
      i3 = 0;
      i4++;
    }
    if(i4%30 == 0){
      insertSortData(3, to_ins);
      i4 = 0;
    }
    // SHOULD I BECOME A TIMER?
    _delay_ms(1*1000);
  }
}
  
