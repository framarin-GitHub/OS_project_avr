#pragma once
#include <time.h>
typedef struct {
  int value;  
  time_t timestamp;
} ts_data;

ts_data* hour[60];
ts_data* day[24];
ts_data* month[30];
ts_data* year[12];

time_t start_time;

ts_data* createTsData(int value, time_t ts);

void deleteTsData(ts_data* del);

int getDataValue(ts_data* get);

float secElapsed(ts_data* end, ts_data* start);

time_t getTime();
