#include <stdio.h>
#include <stdlib.h>
#include "gol.h"

int main(int argc, char *argv[]){ //argv is char but input_filename can be a str???
  
  int torus = 0;
  int gens = 5;
  int stats = 0;

  for (int i=0;i<argc;i++) {
    switch (argv[i]){
      case "-i":
        if (i == argc-1) { //check also when it's not the last flag
          fprintf(stderr, "Input file flag used, but no ??? specified\n");
          exit(1);
        }
        break;
      
      case "-o":
        if (i == argc-1) {
          fprintf(stderr, "Output file flag used, but no ??? specified\n");
          exit(1);
        }
        break;

      case "-g":
        if (i == argc-1) {
          fprintf(stderr, "Generations flag used, but no number specified\n");
          exit(1);
        }
        if (argv[i+1]) {
          fprintf(stderr, "Generations flag used, but no number specified\n");
          exit(1);
        }
        break;

      case "-s":
        stats = 1;
        break;

      case "-t":
        torus = 1;
        break;
      
      default:
        break;
    }
  }

  struct universe v;
  read_in_file(stdin,&v);

  if (gens != 0) {
    if (torus) {
      for (int i=0;i<gens;i++){
        evolve(&v,will_be_alive_torus);
      } 
    } else {
      for (int i=0;i<gens;i++){
        evolve(&v,will_be_alive);
      }
    }
  }

  write_out_file(stdout,&v);

  if (stats) {
    print_statistics(&v);
  }

  return 0;
}