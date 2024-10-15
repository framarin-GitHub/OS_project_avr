#pragma once  

char readSerial(int fd, char* buf);

void writeSerial(int fd, char* to_send);
