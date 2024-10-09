#include <util/delay.h>
#include <stdio.h>
#include "./avr_common/uart.h" // this includes the printf and initializes it
#include "./analog_read/analog_read.h"

int main(void){
  // this initializes the printf/uart thingies
  printf_init();
  
  while(1){
    int res = analogRead(0);
    printf("we read A0 = %d \n", res);
    _delay_ms(500);
  }
}
