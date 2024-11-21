Data saved in [gitignored files]:\
  diagram_output/data/hour.temp, diagram_output/data/day.temp, diagram_output/data/month.temp, diagram_output/data/year.temp

First connection with avr:
  ./client f
  
Volt Equation:
  the value range is [0,1023] corresponding to [0,5] Volt. According to datasheet +-1V is equal to +-1A (considering +- as 
  current direction). Using 3.3V alimentation from arduino's pin, the current meter has the dinamic centered at 3.3V, 
  that is 675. In this scale 1V==1A is equal to 205. Viceversa, 1 is almost equal to 5mV==5mA (milliAmpere). 
