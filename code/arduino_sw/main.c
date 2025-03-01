#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "./avr_common/uart.h" // this includes the printf and initializes it
#include "./analog_read/analog_read.h"
#include "./serial_communication/serial_communication.h"
#include "./manip_data/handler_data.h"
#include "./timer/timer.h"

extern int hour[60];
extern int day[24];
extern int month[30];
extern int year[12];

uint8_t buf[1024];

int Rf;
int R1;
int partition;

double value_read = -1;
double value_max = -1;
double value_acc = 0;

int* value_arr;
int* temp;

int to_ins = -1;
int sec_interval = 1;
int samples = -1;
int samples_counter = 0;

int i1 = 0;
int i2 = 0;
int i3 = 0;
int i4 = 0;  

int online_mode = 0;
int fast_sample_mode = 0;
volatile int flag_read = 0;
volatile uint8_t timer_int_occ = 0;
// timer int
ISR(TIMER5_COMPA_vect) {
  timer_int_occ = 1;
}
// usart int
ISR(USART0_RX_vect) {
  flag_read = 1;
}


int main(void){
  // this initializes the printf/uart thingies
  printf_init();
  UART_init();
  // Initialize global variables
  initData();
  // Initialize timer
  timerIntInit();
  // Initialize analog read on pin 0
  initADC(0);

  UART_putString((uint8_t*)"avr\\\\init complete ...\n");
    
  while(1){
    value_read = analogRead();
    value_max = (value_max>value_read)? value_max : value_read;
    if(fast_sample_mode){
      *temp = (int)value_read;
      temp++;
      samples_counter++;
      if(samples_counter == samples){
        for(samples_counter = 0; samples_counter < samples; samples_counter++){
          sprintf((char*)buf, "%d\n", value_arr[samples_counter]);
          UART_putString(buf);    
        }
        fast_sample_mode = 0;
        free(value_arr);
      }
    }
    if(timer_int_occ){
      value_acc += value_max;
      i1++;
      // sending data in online mode every sec_interval seconds
      if(online_mode && (i1%sec_interval == 0)){
        sprintf((char*)buf, "%d\n", (int)value_max);
        UART_putString(buf);    
      }
      // inserting one minute mean in hour array
      if(i1%60 == 0){
        to_ins = (int)(value_acc/60);
        insertSortData(0, to_ins);
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
      timer_int_occ = 0;
      value_acc = 0;
      value_max = -1;
    }
    if(flag_read){
      UART_getString(buf);	
      UART_putString((uint8_t*) buf);
      switch(buf[0]){
        case 'i':
          UART_putString((uint8_t*)"avr\\\\init data ...\n");
          UART_getString(buf);
          Rf = atoi((char*)buf);
          UART_getString(buf);
          R1 = atoi((char*)buf);
          UART_getString(buf);
          partition = atoi((char*)buf);
          break;
        case 'r':
          UART_putString((uint8_t*)"avr\\\\send gain and partition ...\n");
          sprintf((char*)buf, "%d\n", Rf);
          UART_putString(buf);    
          sprintf((char*)buf, "%d\n", R1);
          UART_putString(buf); 
          sprintf((char*)buf, "%d\n", partition);
          UART_putString(buf); 
          break;
        case 'c':
          UART_putString((uint8_t*)"avr\\\\clearing stats ...\n");
          initData();
          break;
        case 'q':
          UART_putString((uint8_t*)"avr\\\\sending data ...\n");
          sendData();          
          break;
        case 'e':
          UART_putString((uint8_t*)"avr\\\\ending online mode ...\n");
          online_mode = 0;
          break;
        case 's':
          UART_putString((uint8_t*)"avr\\\\starting online mode ...\n");
          UART_getString(buf);
          sec_interval = atoi((char*)buf);
          online_mode = 1;
          break;
        case 'f':
          // sampling at 125kHz clock frequency, with 10 clock cycles required for 1 ADC
          // requires 250 samples to span across one period of 50Hz alternate current 
          UART_putString((uint8_t*)"avr\\\\starting fast sampling mode ...\n");
          UART_getString(buf);
          samples = atoi((char*)buf);
          samples_counter = 0;
          value_arr = (int*)malloc(sizeof(int)*samples);
          temp = value_arr;
          fast_sample_mode = 1;
          break;
        default:
          UART_putString((uint8_t*)"avr\\\\what have you sent to me?\n");
      }
      flag_read = 0;
    }
  } 
}
