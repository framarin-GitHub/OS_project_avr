#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

const int timer_duration_ms = 1000;

void timerIntInit(){
  // configure timer
  // set the prescaler to 1024
  TCCR5A = 0;
  TCCR5B = (1 << WGM52) | (1 << CS50) | (1 << CS52); 
  
  // at this count rate
  // 1 ms will correspond do 15.62 counts
  // we set the output compare to an appropriate
  // value so that when the counter reaches that value
  // the interrupt will be triggered
  uint16_t ocrval=(uint16_t)(15.62*timer_duration_ms);

  OCR5A = ocrval;

  // clear int
  cli();
  TIMSK5 |= (1 << OCIE5A);  // enable the timer interrupt
  // enable int
  sei();
}
