-void plotDiag(int mode, char* time);

plotDiag opens the pipe to send commands to gnuplot with persistent in order to leave the window open even 
  when program terminates. It calls initGnuplot, which initializes gnuplot with format properties such
  as title, xaxis, yaxis, ecc.; depending upon client queries, which is represented by mode.
  Strings to send through pipe are built with srcat() and strcpy() and they ends with new line.
  Data contains the 4 files in which information are stored.


