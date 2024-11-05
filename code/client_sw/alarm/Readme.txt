-void initSignalHandler();

initSignalHandler sets up the struct sigaction to handle SIGALRM signal.
  the handler function is setting a global variable alarm_flag to end client reading process
  and is sending stop to the main, using another global variable to store the fd.
