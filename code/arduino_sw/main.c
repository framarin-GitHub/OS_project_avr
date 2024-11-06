#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <avr/io.h>
#include "./avr_common/uart.h" // this includes the printf and initializes it
#include "./analog_read/analog_read.h"
#include "./serial_communication/serial_communication.h"
#include "./manip_data/struct_data.h"
#include "./manip_data/handler_data.h"

// defined in struct_data.h
extern ts_data* hour[60];
extern ts_data* day[24];
extern ts_data* month[30];
extern ts_data* year[12];

extern time_t start_time;

uint8_t buf[1024];

int main(void){
  // this initializes the printf/uart thingies
  printf_init();
  UART_init();
  // Initialize global variables
  initData();
    
  int i1 = 0;
  int i2 = 0;
  int i3 = 0;
  int i4 = 0;
  int value_read = 0; 
  ts_data* to_ins = 0;
  int sec_interval;
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
        case 's':
          UART_putString((uint8_t*) buf);
          break;
        case 'o':
          UART_putString((uint8_t*) buf);
          UART_getString(buf);
          sec_interval = atoi((char*)buf);
          break;
        default:
          UART_putString((uint8_t*)"what have you sent to me?\n");
      }
    }  
    value_read += analogRead(0);
    i1++;
    // inserting one minute mean in hour array
    if(i1%60 == 0){
      value_read = value_read/60;
      to_ins = createTsData(value_read, -1);
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
    _delay_ms(1*1000);
  }
}
  
  
  
  
  /*
  
    uint8_t buf[1024];
  //on-line mode
    UART_getString(buf);
    //we need a menu swithc here for q quit 
    int sec_interval = atoi((char*)buf);
    // we loop until serial has data on it
    while(!(UCSR0A & (1<<RXC0))){
      int value = analogRead(0);
      //converts int to string
      sprintf((char*)buf, "%d\n", value);
      UART_putString((uint8_t*) buf);
      switch(sec_interval){
        case 1:
          _delay_ms(1*1000);
          break;
        case 2:
          _delay_ms(2*1000);
          break;
        case 4:
          _delay_ms(4*1000);
          break;
        case 8:
          _delay_ms(8*1000);
          break;
      }
    }
    // we send data back to avoid blocking read by client    
    UART_getString(buf);
    UART_putString((uint8_t*) buf);
  }
}*/
