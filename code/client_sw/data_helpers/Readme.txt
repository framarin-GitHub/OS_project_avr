-void recData(int fd);

recData initialize and populates the 4 arrays of current values. The value -1 is flagging "no value".
  It receives up to 126 (constant number) values from avr and fills the arrays, then it writes arrays 
  to file using writeDataToFile(). writeDataToFile opens the files located in 
  ~/client_sw/diagram_output/data/ and writes the couple {timestamp,value} in the corresponding file,
  thanks to the global tm struct which contains time information of data reception. 
