(1)serial_settings.c
-------------------------------------------------------------------
-int serialOpen(const char* name);

serialOpen initialize file descriptor to read and write with C functions. <name> is the
  address of the device. 0_RDWR is for read and write; O_NOCTTY avoids device to become
  controlling terminal of the process. O_SYNC guarantees all the data are transmitted.


-int serialSetInterfaceAttribs(int fd, int speed, int parity);

serialSetInterfaceAttribs uses termios.h struct to set serial port options, namely
  speed, parity check, size of bit communication (8-bit).
  

-void serialSetBlocking(int fd, int should_block);

serialSetBlocking allows to set blocking read and write communication. VMIN sets the number of
  char to read to 1, as a consequence it blocks until one char is read. VTIME sets the
  timeout for read at 0.5 sec.
 
 

(2)read_write_serial.c
------------------------------------------------------------------- 

-void writeSerial(int fd, char* to_send);

writeSerial sends at most 1024 char using write function. It adds '\n' at the ends of the     
  string to properly communicate with our protocol.
  
  
-int readSerial(int fd, char* buf);

readSerial reads strings from serial input one char at time, stopping when reading '\n' or '\r' 
  based on the getCharSerial function. It returns the number of char read.
