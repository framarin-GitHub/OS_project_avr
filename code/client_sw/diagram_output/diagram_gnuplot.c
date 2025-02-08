#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./diagram_gnuplot.h"
void initGnuplot(int mode, FILE* gnuplot_pipe){
  char* key_pos = "set key top center\n";
  char* pointsize = "set pointsize 2\n";
  char* yrange = "set yrange [-1:1024]\n";
  char title[200]; 
  char xrange[200];
  char* ylabel = "set ylabel \"current(milliAmpere)\" offset (0, 0, 0) rotate by -270 textcolor lt -1\n";
  char* xlabel = "set xlabel \"values\" offset (0, 0, 0) rotate norotate textcolor lt -1\n";
  strcpy(title, "set title \"");
  strcpy(xrange, "set xrange ");
  switch(mode){
    // hour
    case 0:
      strcat(title, "statistics of the latest hour\"\n");
      strcat(xrange, "[-60:60]\n");
      break;
    // day
    case 1:
      strcat(title, "statistics of the latest day\"\n");
      strcat(xrange, "[-24:24]\n");
      break;
    // month 
    case 2:
      strcat(title, "statistics of the latest month\"\n");
      strcat(xrange, "[-30:30]\n");      
      break;
    // year
    case 3:
      strcat(title, "statistics of the latest year\"\n");
      strcat(xrange, "[-12:12]\n");
      break;
    case 4:
      strcat(title, "function representation\"\n");
      yrange = "set yrange [-1024:1024]\n";
      strcat(xrange, "[0:1000]\n");
      break;
  }
  // send setting commands
  fprintf(gnuplot_pipe, "reset\n");
  fprintf(gnuplot_pipe, title);
  fprintf(gnuplot_pipe, xrange);
  fprintf(gnuplot_pipe, yrange);
  fprintf(gnuplot_pipe, key_pos);
  fprintf(gnuplot_pipe, pointsize);
  fprintf(gnuplot_pipe, xlabel);
  fprintf(gnuplot_pipe, ylabel);
}


void plotDiag(int mode, char* time){
  FILE * gnuplot_pipe = popen("gnuplot -persistent", "w");
  initGnuplot(mode, gnuplot_pipe);
  char label[200];
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
    case 4:
      strcat(plot, "fast_sample.temp\"");
      break;
  }
  // points circle filled width 4 color orange
  strcat(plot, " with linespoints pointtype 7 lw 4 linecolor 4\n");
  strcpy(label, "set label \"");
  if(mode != 4)
    strcat(label, time);
  strcat(label, "\" at 0,20\n");
  if(mode != 4)
    fprintf(gnuplot_pipe, label);
  fprintf(gnuplot_pipe, plot);
  fflush(gnuplot_pipe);
}

