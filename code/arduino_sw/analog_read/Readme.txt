int analogRead(uint8_t pin);

analogRead uses 3 registers: 1)ADMUX;2)ADCSRA3)ADCSRB.
1)
  bits REFS1==0 and REFS0==1, setting the voltage reference to AVcc;
  bits MUX from 4 to 0 are selecting which pin to convert with ADC;
  ADLAR bit default;
2)
  we enable ADC setting ADEN to 1;
  we set the prescaler at 128 with ADPS2-1-0==111, obtaining a sample rate of 16MHz/128=125KHz
    using at most 0,2ms to complete first conversion(most time-consuming operation);
3)
  we only set MUX5 to 0 because we don't need A8-15.

after the setup, we switch on conversion by setting ADCSRA's bit ADSC==1. We busy wait for it to be ADSC==0, meaning conversion is over.
we return ADC which is the concat of ADCL and ADCH, with max precision of 10 bit. In other words, we have a sample ranging from 0 (0V) to 1024(5V).
