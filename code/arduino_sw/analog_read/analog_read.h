#pragma once
/*
  Reads the value on A<pin>, with <pin> range 0-7. RET is ranging from 0==0V to 1024==5V. 
*/
int analogRead(uint8_t pin);
