#include <avr/io.h>

int analogRead(uint8_t pin){

   //INIT registers
   // set voltage reference
    ADMUX = (1 << REFS0);
   // we set MUX 4 3 2 1 0 based on pin
    ADMUX = (ADMUX & 0xE0) | (pin & 0x1F); 
   // we set MUX5 == 0 we use only the first 8 analog pins
    ADCSRB &= 0xF7;  
   //ADC turn on and set prescaler to 128
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    

   // Start the conversion
    ADCSRA |= (1 << ADSC);
   // Busy wait conversion
    while (ADCSRA & (1 << ADSC));
   // Return the ADC value
    return ADC;
}

