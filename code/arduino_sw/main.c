#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include "./avr_common/uart.h" // this includes the printf and initializes it
#include "./analog_read/analog_read.h"
#include "./serial_communication/serial_communication.h"

int main(void){
  // this initializes the printf/uart thingies
  printf_init();
  UART_init();
  while(1){
    uint8_t buf[1024];
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
}
