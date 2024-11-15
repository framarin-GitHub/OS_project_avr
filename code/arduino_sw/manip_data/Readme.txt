-void insertSortData(int type, int to_ins);

insertSortData updates the 4 arrays with the new value keeping them sorted. It executes a head-insertion and 
  shifts all values to the next position, eventually discarding the last one, that is the oldest. When called with
  type 1,2 or 3 it makes the calculation of the to_ins value looking at more narrow array.


-void initData();

initData sets all the arrays to -1, namely the "no value" value.


-void sendData();

sendData sends the arrays via serial to the client. It sends up to a constant number of values: 126.
