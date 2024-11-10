#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./diagram_gnuplot.h"
void initGnuplot(int mode, FILE* gnuplot_pipe){
  char* key_pos = "set key top center\n";
  char* pointsize = "set pointsize 2\n";
  //char* yrange = "set yrange [0:100]\n";
  char title[200];
  /*
  char xrange[200];
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
  }*/
  // send setting commands
  fprintf(gnuplot_pipe, "reset\n");
  fprintf(gnuplot_pipe, title);
  //fprintf(gnuplot_pipe, xrange);
  //fprintf(gnuplot_pipe, yrange);
  fprintf(gnuplot_pipe, key_pos);
  fprintf(gnuplot_pipe, pointsize);
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
      strcat(plot, "hour.temp\"");
      break;
    // day
    case 1:
      strcat(plot, "day.temp\"");
      break;
    // month 
    case 2:
      strcat(plot, "month.temp\"");    
      break;
    // year
    case 3:
      strcat(plot, "year.temp\"");
      break;
  }
  // points circle filled width 4 color orange
  strcat(plot, " with linespoints pointtype 7 lw 4 linecolor 4\n");
  fprintf(gnuplot_pipe, plot);
  fflush(gnuplot_pipe);
}

