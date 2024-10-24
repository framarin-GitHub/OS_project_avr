#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void initGnuplot(int mode, FILE* gnuplot_pipe){
  char title[200];
  char xrange[200];
  char* yrange = "set yrange [0:100]\n";
  strcpy(title, "set title \"");
  strcpy(xrange, "set xrange ");
  switch(mode){
    // hour
    case 0:
      strcat(title, "statistics of the latest hour\"\n");
      strcat(xrange, "[0:60]\n");
      break;
    // day
    case 1:
      strcat(title, "statistics of the latest day\"\n");
      strcat(xrange, "[0:24]\n");
      break;
    // month 
    case 2:
      strcat(title, "statistics of the latest month\"\n");
      strcat(xrange, "[0:30]\n");      
      break;
    // year
    case 3:
      strcat(title, "statistics of the latest year\"\n");
      strcat(xrange, "[0:12]\n");
      break;
  }
  // send setting commands
  fprintf(gnuplot_pipe, "reset\n");
  fprintf(gnuplot_pipe, title);
  fprintf(gnuplot_pipe, xrange);
  fprintf(gnuplot_pipe, yrange);
  fflush(gnuplot_pipe);
}


void plotDiag(int mode){
  FILE * gnuplot_pipe = popen("gnuplot -persistent", "w");
  initGnuplot(mode, gnuplot_pipe);
  
  char plot[200];
  // relative path from caller function location
  strcpy(plot, "plot \"./diagram_output/data/");
  switch(mode){
    // hour
    case 0:
      strcat(plot, "hour.temp\"\n");
      break;
    // day
    case 1:
      strcat(plot, "day.temp\"\n");
      break;
    // month 
    case 2:
      strcat(plot, "month.temp\"\n");    
      break;
    // year
    case 3:
      strcat(plot, "year.temp\"\n");
      break;
  }
  fprintf(gnuplot_pipe, plot);
  fflush(gnuplot_pipe);
}

FILE* pipeOpen(){

  return gnuplot_pipe;
}

