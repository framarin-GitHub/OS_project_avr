-void timerIntInit();

timerIntInit activates the avr's timer 5 to send an interrupt every second. TCCR5A register is set to 0, 
  to operate in normal mode, without using ports. TCCR5B register has WGM52 bit set to 1, which combined
  with WGM51 and WGM50 set to 0, makes the timer work in CTC mode; setting CS50 and CS52 to 1 and CS51 to 0
  sets the prescaler to 1024. OCR5A contains the value to compare with timer, when the value is equal to 
  timer it sends the interrupt. TIMSK5 bit OCIE5A set to 1 allows interrupt when timer and compare value are
  equal.
