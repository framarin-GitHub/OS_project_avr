#include <util/delay.h>
#include <stdio.h>
#include "./avr_common/uart.h" // this includes the printf and initializes it
#include "./analog_read/analog_read.h"
#include "./serial_communication/serial_communication.h"

int main(void){
  // this initializes the printf/uart thingies
  printf_init();
  UART_init();
  UART_putString((uint8_t*)"connection opened\n");
  uint8_t buf[1024];
  while(1) {
    UART_getString(buf);
    UART_putString((uint8_t*)"received\n");
  }
}
