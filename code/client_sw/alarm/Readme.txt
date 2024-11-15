-void initSignalHandler();

initSignalHandler sets up the struct sigaction to handle SIGALRM signal.
  the handler function is setting a global variable alarm_flag to end client reading process.
  The sa_flags SA_RESTART allows to start again the function interrupted.
