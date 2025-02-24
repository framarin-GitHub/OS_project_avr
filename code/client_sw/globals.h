#pragma once
#include <time.h>
	
extern volatile int alarm_flag;
extern struct tm* timestamp;

extern int hour[60];
extern int day[24];
extern int month[30];
extern int year[12];

extern int partition;
extern double gain;