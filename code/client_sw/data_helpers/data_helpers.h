#pragma once
#include <time.h>

int hour[60];
int day[24];
int month[30];
int year[12];

time_t timestamp;

void recData(int fd);
