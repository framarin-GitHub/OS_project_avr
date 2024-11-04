#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./avr_common/uart.h" // this includes the printf and initializes it
#include "./analog_read/analog_read.h"
#include "./serial_communication/serial_communication.h"

int main(void){
  // this initializes the printf/uart thingies
  printf_init();
  UART_init();
  uint8_t buf[1024];
  UART_getString(buf);
  int sec_interval = atoi((char*)buf);
  while(sec_interval != 0) {
    int value = analogRead(1);
    //converts int to string
    sprintf((char*)buf, "%d\n", value);
    UART_putString((uint8_t*) buf);
    //works only with constant so we need a timer or switch 
    _delay_ms(1*1000);
  }
}
