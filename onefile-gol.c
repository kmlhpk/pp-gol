#include<stdio.h>
#include<stdlib.h>

struct universe {
  char **cells;
  int rows;
  int cols;
  int maxRowIndex;
  int maxColIndex;
  int aliveNow;
  float aliveNowFrac;
  int aliveSoFar;
  int generations;
  float aliveAverageFrac;
};

void read_in_file(FILE *infile, struct universe *u){
  // Checks if the file is empty
  if (infile == NULL){
    fprintf(stderr, "Empty file\n");
    exit(1);
  }
  int columns = 0;
  int rows = 0;
  // Allocates slightly more than maximum column amount's worth of memory to a line "buffer"
  char *line = (char*)malloc(513 * sizeof(char));
  if (line == NULL){
    fprintf(stderr, "Failed to allocate memory\n");
    exit(1);
  }
  // Allocates one character pointer's worth of memory to the pointer-based "2D array"
  char **grid = (char **)malloc(sizeof(char *));
  if (grid == NULL){
    fprintf(stderr, "Failed to allocate memory\n");
    exit(1);
  }
  char c;
  int currentColumns;
  // Loops through characters in the input until it sees an EOF
  while (1) {
    c = fgetc(infile);
    // On the first line, sets the number of columns for each new line to check against
    if (columns == 0) {
      if (c == EOF) {break;} else {
        // Loops through characters in the line until it sees a line-feed
        while (c != '\n') {
          if (c == '.' || c == '*') {
            // Adds the character to the line buffer
            line[columns] = c;
            columns += 1;
          } else {
            fprintf(stderr, "Ill-formatted input - expected only . or *, saw a different character.\n");
            exit(1);
          }
          c = fgetc(infile);
        }
      }
    } else {
      if (c == EOF) {break;} else {
        // Loops through characters in the line until it sees a line-feed
        while (c != '\n') {
          if (c == '.' || c == '*') {
            // Adds the character to the line buffer
            line[currentColumns] = c;
            currentColumns += 1;
          } else {
            fprintf(stderr, "Ill-formatted input - expected only . or * (and line-feed), saw a different character.\n");
            exit(1);
          }
          c = fgetc(infile);
        }
      }
    }
    // After each line starting with the second, checks if column numbers are equal
    if (rows > 0) {
      if (currentColumns != columns) {
        fprintf(stderr, "Ill-formatted input - column numbers aren't equal in every row\n");
        exit(1);
      }
    }
    // Adds line buffer to array of lines
    grid[rows] = line;
    currentColumns = 0;
    rows += 1;
    // Adds one more line's worth of space in the 2D array
    grid = (char **)realloc(grid, (rows+1) * sizeof(char *));
    // Makes the line buffer point at some fresh blank memory
    line = (char *)malloc(513 * sizeof(char));
  }

  if (columns == 0 || columns > 512) {
    fprintf(stderr, "Invalid column number \n");
    exit(1);
  }

  // Populates the universe struct with necessary data
  u->cells = grid;
  u->rows = rows;
  u ->cols = columns;
  u->maxRowIndex = rows-1;
  u->maxColIndex = columns-1;
  int alive = 0;
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < columns; j++) {
      if (grid[i][j] == '*'){
        alive += 1;
      }
    }
  }
  u->aliveNow = alive;
  u->aliveSoFar = alive;
  u->aliveNowFrac = (float)alive / (float)(rows*columns);
  u->aliveAverageFrac = (float)alive / (float)(rows*columns);
  u->generations = 1;
}

void write_out_file(FILE *outfile, struct universe *u) {
  // Writes out every character in the universe's cell board
  for (int i = 0; i < u->rows; i++){
    for (int j = 0; j < u->cols; j++) {
      fputc(u->cells[i][j], outfile);
    }
    printf("\n");
  }
}

// Amends C's % operator to return a modulo like in Python, not a remainder
// Behaviour undefined for b = 0
int mod (int a, int b){
  if (b < 0) {
    return -mod(-a, -b);
  }
  int result = a % b;
  if (result < 0) {
    result += b;
  }
  return result;
}

int is_alive(struct universe *u, int column, int row){
  // Returns 0 if cell is dead, 1 if cell is alive, error if cell is somehow an illegal character
  if (u->cells[row][column] == '.') {
    return(0);
  } else if (u->cells[row][column] == '*') {
    return(1);
  } else {
    fprintf(stderr, "Encountered illegal character in cell grid");
    exit(1);
  }
}

int will_be_alive(struct universe *u, int column, int row){
  // Initialises all neighbours as dead
  int north, northeast, east, southeast, south, southwest, west, northwest = 0;

  // Checks if all 8 of the cell's neighbours are alive, unless the neighbour is outside the cell grid, in which case it is dead
  if (row == 0) {
   north = 0;
  } else {
    north = is_alive(u,column,row-1);}
  if (row == 0 || column == u->maxColIndex) {
    northeast = 0;
  } else {
    northeast = is_alive(u,column+1,row-1);}
  if (column == u->maxColIndex) {
    east = 0;
  } else {
    east = is_alive(u,column+1,row);}
  if (row == u->maxRowIndex || column == u->maxColIndex) {
    southeast = 0;
  } else {
    southeast = is_alive(u,column+1,row+1);}
  if (row == u->maxRowIndex) {
    south = 0;
  } else {
    south = is_alive(u,column,row+1);}
  if (row == u->maxRowIndex || column == 0) {
    southwest = 0;
  } else {
    southwest = is_alive(u,column-1,row+1);}
  if (column == 0) {
    west = 0;
  } else {
    west = is_alive(u,column-1,row);}
  if (row == 0 ||column == 0) {
    northwest = 0;
  } else {
    northwest = is_alive(u,column-1,row-1);}

  int neighbours = northwest+north+northeast+west+southwest+south+southeast+east;

  // Applies standard game of life rule to determine if the cell will be alive
  if (neighbours == 3) {
    return(1);
  } else if (neighbours == 2) {
    if (is_alive(u,column,row)) {
      return(1);
    } else {
      return(0);
    }
  } else {
    return(0);
  }
}

int will_be_alive_torus(struct universe *u,  int column, int row){
  // Initialises all neighbours as dead
  int north, northeast, east, southeast, south, southwest, west, northwest = 0;

  // Checks if all 8 of the cell's neighbours are alive; if the neighbour is "outside" the cell grid, then it is actually on the other side of the grid corresponding to a toroidal topology
  north = is_alive(u,mod(column,u->cols),mod(row-1,u->rows));
  northeast = is_alive(u,mod(column+1,u->cols),mod(row-1,u->rows));
  east = is_alive(u,mod(column+1,u->cols),mod(row,u->rows));
  southeast = is_alive(u,mod(column+1,u->cols),mod(row+1,u->rows));
  south = is_alive(u,mod(column,u->cols),mod(row+1,u->rows));
  southwest = is_alive(u,mod(column-1,u->cols),mod(row+1,u->rows));
  west = is_alive(u,mod(column-1,u->cols),mod(row,u->rows));
  northwest = is_alive(u,mod(column-1,u->cols),mod(row-1,u->rows));

  int neighbours = northwest+north+northeast+west+southwest+south+southeast+east;

  // Applies standard game of life rule to determine if the cell will be alive
  if (neighbours == 3) {
    return(1);
  } else if (neighbours == 2) {
    if (is_alive(u,column,row)) {
      return(1);
    } else {
      return(0);
    }
  } else {
    return(0);
  }
}

void evolve(struct universe *u, int (*rule)(struct universe *u, int column, int row)){
  int aliveNew = 0;
  // Makes new generation's cell grid
  char newCells[u->rows][u->cols];
  // Populates new cell grid 
  for (int i = 0; i < u->rows; i++) {
    for (int j = 0; j < u->cols; j++) {
      if (rule(u, j, i)) {
        newCells[i][j] = '*';
        aliveNew += 1;
      } else {
        newCells[i][j] = '.';
      }
    }
  }

  // Sets correct information for new generation, calculates statistics
  u->aliveNow = aliveNew;
  u->aliveNowFrac = (float)u->aliveNow / (float)(u->rows * u->cols);
  u->aliveSoFar += u->aliveNow;
  u->generations += 1;
  u->aliveAverageFrac = (float)u->aliveSoFar / (float)(u->generations*u->rows*u->cols);

  // Replaces the current universe's cell grid with the new cell grid
  // replace the following with pointer magic????????????????????
  for (int i = 0; i < u->rows; i++) {
    for (int j = 0; j < u->cols; j++) {
      u->cells[i][j] = newCells[i][j];
    }
  }
}

void print_statistics(struct universe *u){
  // Prints statistics about the universe (funnily enough)
  printf("%.3f%% of cells currently alive\n",u->aliveNowFrac*(float)100);
  printf("%.3f%% of cells alive on average\n",u->aliveAverageFrac*(float)100);
}

/*
int main(){
  struct universe v = UNIVERSE_HARDCODE;
  write_out_file(stdout,&v);
  print_statistics(&v);
  evolve(&v,will_be_alive_torus);
  write_out_file(stdout,&v);
  print_statistics(&v);
  evolve(&v,will_be_alive_torus);
  write_out_file(stdout,&v);
  print_statistics(&v);
  evolve(&v,will_be_alive_torus);
  write_out_file(stdout,&v);
  print_statistics(&v);
return 0;
}
*/

int main(){
  struct universe v; 
  read_in_file(stdin,&v);
  evolve(&v,will_be_alive);
  //evolve(&v,will_be_alive);
  //evolve(&v,will_be_alive);
  //evolve(&v,will_be_alive);
  //evolve(&v,will_be_alive);
  write_out_file(stdout,&v);
  print_statistics(&v);
}

/* Vanilla
int main(int argc, char *argv[]){
  struct universe v; 
  read_in_file(stdin,&v);
  evolve(&v,will_be_alive);
  evolve(&v,will_be_alive);
  evolve(&v,will_be_alive);
  evolve(&v,will_be_alive);
  evolve(&v,will_be_alive);
  write_out_file(stdout,&v);
return 0;
}
*/