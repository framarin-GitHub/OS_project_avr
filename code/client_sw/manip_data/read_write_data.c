#include <stdlib.h>
#include <stdio.h>
#include "./struct_data.h"
#include "./read_write_data.h"

ts_data hour[60];
memset(hour, 0, 60*sizeof(ts_data));
ts_data day[24];
memset(day, 0, 24*sizeof(ts_data));
ts_data month[30];
memset(month, 0, 30*sizeof(ts_data));
ts_data year[12];
memset(year, 0, 12*sizeof(ts_data));

void synchroArrays(){
  FILE* f_h = fopen("./diagram_output/data/hour.temp", "rb+");
  FILE* f_d = fopen("./diagram_output/data/day.temp", "rb+");
  FILE* f_m = fopen("./diagram_output/data/month.temp", "rb+");
  FILE* f_y = fopen("./diagram_output/data/year.temp", "rb+");
  
  fread(hour, sizeof(ts_data), 60, f_h);
  fread(day, sizeof(ts_data), 24, f_d);
  fread(month, sizeof(ts_data), 30, f_m);
  fread(year, sizeof(ts_data), 12, f_y);
  
  fclose(f_h);
  fclose(f_d);
  fclose(f_m);
  fclose(f_y);
}

void asdasd(){
  FILE* f_h = fopen("./diagram_output/data/hour.temp", "rb+");
  ts_data* to_w1 = createTsData(5);
  ts_data* to_w2 = createTsData(33);
 // writing to file
  fwrite(&to_w1, sizeof(to_w1), 1, f_h);
  fwrite(&to_w2, sizeof(to_w2), 1, f_h);
  synchroArrays();
  printf("%d\n\n", hour[0].value); 
}
