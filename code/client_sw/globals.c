#include <time.h>

volatile int alarm_flag;
struct tm* timestamp;

int hour[60];
int day[24];
int month[30];
int year[12];

int partition = -1;
double gain = 0;