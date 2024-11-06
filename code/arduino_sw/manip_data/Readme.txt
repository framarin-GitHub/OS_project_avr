-ts_data* createTsData(int value);
-void deleteTsData(ts_data* del);
-int getDataValue(ts_data* get);

createTsData, deleteTsData and getDataValue are basic oop function for the C-style class 
  (struct) ts_data, which associates a timestamp to the value read from analogic input. It 
  wraps time(NULL) from time.h to get the actual time. 


-float secElapsed(ts_data* end, ts_data* start);

secElapsed allows to measure the interval of time between start and end measures in seconds 
  (float), wrapping difftime().
  
  
  
  
  
  !--->update with readme with read_write_data.h<---!
