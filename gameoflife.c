#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gol.h"

int main(int argc, char *argv[]) {
  int torus = 0;
  int gens = 5;
  int stats = 0;
  char *inputFile = NULL;
  char *outputFile = NULL;

  int iFlagSeen = 0;
  int oFlagSeen = 0;
  int gFlagSeen = 0;

  // Iterates through all arguments supplied
  for (int i=1;i<argc;i++) {
    // Checks if flag starts with '-' (non-flag parameters to input, output and generations are skipped with i++)
    if (argv[i][0] != '-') {
      fprintf(stderr, "ERROR: Unrecognised argument %s: valid arguments are -i, -o, -g, -s, -t\n", argv[i]);
      exit(1);
    }
    switch (argv[i][1]) {
      case 'i':
        if (argv[i][2] != '\0') {
          fprintf(stderr, "ERROR: Unrecognised argument %s: valid arguments are -i, -o, -g, -s, -t\n", argv[i]);
          exit(1);
        }
        // Checks if flag is last in the list, or if flag's parameter is formatted like a flag
        if (i == argc-1 || argv[i+1][0] == '-') {
          fprintf(stderr, "ERROR: Input file flag used, but no filename specified\n");
          exit(1);
        }
        // On first time -i is seen, sets inputFile
        if (!iFlagSeen) {
          iFlagSeen = 1;
          inputFile = argv[i+1];
        } else {
        // All subsequent times, checks if new filename is the same as original
          if (strcmp(inputFile,argv[i+1]) != 0) {
            fprintf(stderr, "ERROR: Conflicting input file names\n");
            exit(1);
          }
        }
        i++;
        break;
      
      case 'o':
        if (argv[i][2] != '\0') {
          fprintf(stderr, "ERROR: Unrecognised argument %s: valid arguments are -i, -o, -g, -s, -t\n", argv[i]);
          exit(1);
        }
        // Checks if flag is last in the list, or if flag's parameter is formatted like a flag
        if (i == argc-1 || argv[i+1][0] == '-') {
          fprintf(stderr, "ERROR: Output file flag used, but no filename specified\n");
          exit(1);
        }
        // On first time -o is seen, sets inputFile
        if (!oFlagSeen) {
          oFlagSeen = 1;
          outputFile = argv[i+1];
        } else {
        // All subsequent times, checks if new filename is the same as original
          if (strcmp(outputFile,argv[i+1]) != 0) {
            fprintf(stderr, "ERROR: Conflicting output file names\n");
            exit(1);
          }
        }
        i++;
        break;

      case 'g':
        if (argv[i][2] != '\0') {
          fprintf(stderr, "ERROR: Unrecognised argument %s: valid arguments are -i, -o, -g, -s, -t\n", argv[i]);
          exit(1);
        }
        // Checks if flag is last in the list, or if flag's parameter is formatted like a flag
        if (i == argc-1 || argv[i+1][0] == '-') {
          fprintf(stderr, "ERROR: Generations flag used, but no number specified\n");
          exit(1);
        } else {
          // On first time -g is seen, sets gens
          if (!gFlagSeen) {
            gFlagSeen = 1;
            // 0 generations is a valid input
            if (argv[i+1][0] == '0' && argv[i+1][1] == '\0') {
              gens = 0;
            } else if (atoi(argv[i+1]) == 0) {
              // If string to int conversion fails, throws error
              fprintf(stderr, "ERROR: Invalid number of generations - not recognised as a number\n");
              exit(1);
            }
            gens = atoi(argv[i+1]);
            if (gens<0) {
            fprintf(stderr, "ERROR: Invalid number of generations - please enter a number at least 0\n");
            exit(1);
            }
          // All subsequent times, checks if new number is the same as original
          } else {
            if (argv[i+1][0] == '0' && argv[i+1][1] == '\0') {
              if (gens != 0) {
                fprintf(stderr, "ERROR: Conflicting number of generations\n");
                exit(1);
              }
            } else if (atoi(argv[i+1]) == 0) {
              // If string to int conversion fails, throws error
              fprintf(stderr, "ERROR: Invalid number of generations - not recognised as a number\n");
              exit(1);
            }
            if (atoi(argv[i+1]) != gens) {
              fprintf(stderr, "ERROR: Conflicting numbers of generations\n");
              exit(1);
            }
          }
        }
        i++;
        break;

      case 's':
        if (argv[i][2] != '\0') {
          fprintf(stderr, "ERROR: Unrecognised argument %s: valid arguments are -i, -o, -g, -s, -t\n", argv[i]);
          exit(1);
        }
        stats = 1;
        break;

      case 't':
        if (argv[i][2] != '\0') {
          fprintf(stderr, "ERROR: Unrecognised argument %s: valid arguments are -i, -o, -g, -s, -t\n", argv[i]);
          exit(1);
        }
        torus = 1;
        break;
      
      default:
        fprintf(stderr, "ERROR: Unrecognised argument %s: valid arguments are -i, -o, -g, -s, -t\n", argv[i]);
        exit(1);
        break;
    }
  }

  struct universe v;
  if (inputFile != NULL) {
    FILE *fp;
    fp = fopen(inputFile,"r");
    if (fp == NULL) {
      fprintf(stderr, "ERROR: Null input file pointer - program cannot open\n");
      exit(1);
    }
    read_in_file(fp,&v);
    fclose(fp);
  } else {
    read_in_file(stdin,&v);
  }

  if (gens != 0) {
    if (torus) {
      for (int i=0;i<gens;i++) {
        evolve(&v,will_be_alive_torus);
      } 
    } else {
      for (int i=0;i<gens;i++) {
        evolve(&v,will_be_alive);
      }
    }
  }

  if (outputFile != NULL) {
    FILE *fp;
    fp = fopen(outputFile,"w");
    if (fp == NULL) {
      fprintf(stderr, "ERROR: Null output file pointer - program cannot open\n");
      exit(1);
    }
    write_out_file(fp,&v);
    fclose(fp);
  } else {
    write_out_file(stdout,&v);
  }

  if (stats) {
    print_statistics(&v);
  }
  return 0;
}