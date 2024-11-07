-void UART_init();

  initializes the UART


-uint8_t UART_getString(uint8_t* buf);

UART_getString reads until '\n' or '\r' from serial one char at time, based on getChar() that 
  busy waits looping on the satus bit RXC0 of UCSR0A register to check serial input.


-void UART_putString(uint8_t* buf);

UART_putString writes on serial one char at time, based on putChar() that busy waits looping on 
  the satus bit UDRE0 of UCSR0A register to check if any transmission is ongoing.
