#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./struct_data.h"
#include "./read_write_data.h"
#include <errno.h>
#define HANDLE_ERROR_ERRNO(msg) \
	do{ \
	errno = 11;\
	perror(msg); \
	exit(11); \
	} while(0)



ts_data* hour[60];
ts_data* day[24];
ts_data* month[30];
ts_data* year[12];


void synchroArrays(){
  memset(hour, 0, sizeof(ts_data*)*60);
  memset(day, 0, sizeof(ts_data*)*24);
  memset(month, 0, sizeof(ts_data*)*30);
  memset(year, 0, sizeof(ts_data*)*12);
  FILE* f_h = fopen("./diagram_output/data/hour.temp", "r+");
  FILE* f_d = fopen("./diagram_output/data/day.temp", "r+");
  FILE* f_m = fopen("./diagram_output/data/month.temp", "r+");
  FILE* f_y = fopen("./diagram_output/data/year.temp", "r+");
  int flag = 0;
  int i = 0;
  time_t ts_read = 0;
  int value_read = 0;
  do {  
    flag = fscanf(f_h,"%ld %d\n", &ts_read, &value_read);
    if(flag == EOF)
      break;
    if(flag == 1)
      HANDLE_ERROR_ERRNO("error reading hour.temp\n");
    if(i > 59)
      HANDLE_ERROR_ERRNO("error reading hour.temp\n");
    hour[i] = createTsData(value_read, ts_read);
    i++;
  } while(1);

  flag = 0;
  i = 0;
  ts_read = 0;
  value_read = 0;
  do {  
    flag = fscanf(f_d,"%ld %d\n", &ts_read, &value_read);
    if(flag == EOF)
      break;
    if(flag == 1)
      HANDLE_ERROR_ERRNO("error reading day.temp\n");
    if(i > 23)
      HANDLE_ERROR_ERRNO("error reading day.temp\n");
    day[i] = createTsData(value_read, ts_read);
    i++;
  } while(1);

  flag = 0;
  i = 0;
  ts_read = 0;
  value_read = 0;
  do {  
    flag = fscanf(f_m,"%ld %d\n", &ts_read, &value_read);
    if(flag == EOF)
      break;
    if(flag == 1)
      HANDLE_ERROR_ERRNO("error reading month.temp\n");
    if(i > 29)
      HANDLE_ERROR_ERRNO("error reading month.temp\n");
    month[i] = createTsData(value_read, ts_read);
    i++;
  } while(1);
  
  flag = 0;
  i = 0;
  ts_read = 0;
  value_read = 0;
  do {  
    flag = fscanf(f_y,"%ld %d\n", &ts_read, &value_read);
    if(flag == EOF)
      break;
    if(flag == 1)
      HANDLE_ERROR_ERRNO("error reading year.temp\n");
    if(i > 11)
      HANDLE_ERROR_ERRNO("error reading year.temp\n");
    year[i] = createTsData(value_read, ts_read);
    i++;
  } while(1);
  
  fclose(f_h);
  fclose(f_d);
  fclose(f_m);
  fclose(f_y);
}
void writeDataToFile(){
  FILE* f_h = fopen("./diagram_output/data/hour.temp", "w+");
  FILE* f_d = fopen("./diagram_output/data/day.temp", "w+");
  FILE* f_m = fopen("./diagram_output/data/month.temp", "w+");
  FILE* f_y = fopen("./diagram_output/data/year.temp", "w+");
    
  for(int i = 0; i < 60; i++)
    fprintf(f_h,"%ld %d\n", hour[i]->timestamp, hour[i]->value);    
  for(int i = 0; i < 24; i++)
    fprintf(f_d,"%ld %d\n", day[i]->timestamp, day[i]->value);
  for(int i = 0; i < 30; i++)
    fprintf(f_m,"%ld %d\n", month[i]->timestamp, month[i]->value);
  for(int i = 0; i < 12; i++)
    fprintf(f_y,"%ld %d\n", year[i]->timestamp, year[i]->value);
  
  fclose(f_h);
  fclose(f_d);
  fclose(f_m);
  fclose(f_y);
}

void insertSortData(int type, ts_data* to_ins){
  ts_data* temp1;
  ts_data* temp2; 
  switch(type){
    case 0:
      temp1 = hour[0];
      temp2 = to_ins;
      for(int i = 0; i < 60; i++){
        hour[i] = temp2;
        temp2 = temp1;
        if(i == 59)
          break;
        temp1 = hour[i+1];
      }
      if(temp1->timestamp != 0)
        deleteTsData(temp1);
      break;
    case 1:
      temp1 = day[0];
      temp2 = to_ins;
      for(int i = 0; i < 24; i++){
        day[i] = temp2;
        temp2 = temp1;
        if(i == 23)
          break;
        temp1 = day[i+1];
      }
      if(temp1->timestamp != 0)
        deleteTsData(temp1);
      break;
    case 2:
      temp1 = month[0];
      temp2 = to_ins;
      for(int i = 0; i < 30; i++){
        month[i] = temp2;
        temp2 = temp1;
        if(i == 29)
          break;
        temp1 = month[i+1];
      }
      if(temp1->timestamp != 0)
        deleteTsData(temp1);
      break;
    case 3:  
      temp1 = year[0];
      temp2 = to_ins;
      for(int i = 0; i < 12; i++){
        year[i] = temp2;
        temp2 = temp1;
        if(i == 11)
          break;
        temp1 = year[i+1];
      }
      if(temp1->timestamp != 0)
        deleteTsData(temp1);
      break;
  }
} 

void initData(){
  synchroArrays();
  printf("data initialized ...\n");
}

ts_data** getArrayData(int type){
  switch(type){
    case 0:
      return hour;
    case 1:
      return day;
    case 2:
      return month;   
    case 3:
      return year;
  }
  return (ts_data**)-1;
}
