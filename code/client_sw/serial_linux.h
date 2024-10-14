#pragma once  
//! returns the descriptor of a serial port
int serialOpen(const char* name);

//! sets the attributes
void serialSetInterfaceAttribs(int fd, int speed, int parity);
  
//! puts the port in blocking/nonblocking mode
void serialSetBlocking(int fd, int should_block);


