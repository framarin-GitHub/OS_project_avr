#pragma once

typedef struct {
  time_t timestamp;
  int value;  
} ts_data;

ts_data* createTsData(int value, time_t ts);

void deleteTsData(ts_data* del);

int getDataValue(ts_data* get);

float secElapsed(ts_data* end, ts_data* start);
