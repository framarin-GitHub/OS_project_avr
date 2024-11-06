#include <time.h>
#include <stdlib.h>
#include "./struct_data.h"

ts_data* createTsData(int value, time_t ts){
  ts_data* res = (ts_data*)calloc(1, sizeof(ts_data));
  res->value = value;
  if(ts == -1)
    res->timestamp = time(NULL);
  else
    res->timestamp = ts;
  return res;
}

void deleteTsData(ts_data* del){
  free(del);
}

float secElapsed(ts_data* end, ts_data* start){
  return difftime(end->timestamp, start->timestamp);
}

int getDataValue(ts_data* get){
  return get->value;
}

time_t getTime(){
  return time(NULL);
}