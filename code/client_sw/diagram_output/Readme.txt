-void plotDiag(int mode, FILE* gnuplot_pipe);

plotDiag calls gnuplot plot function with the right data file based on mode. It calls initGnuplot, which initializes gnuplot with format properties such as title, xaxis and yaxis,    
  depending upon queries, which is represented by mode. It sends these commands through gnuplot_pipe.


