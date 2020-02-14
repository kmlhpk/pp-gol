#include<stdio.h>

struct universe {
  char cells[5][9] = {
    {'.','.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.','.'},
    {'.','*','*','*','.','.','*','*','.'},
    {'.','.','.','.','.','.','*','*','.'},
    {'.','.','.','.','.','.','.','.','.'}};
  int rows = 5;
  int cols = 9;
  int MAX_ROW_INDEX = rows - 1;
  int MAX_COL_INDEX = columns - 1;
  int generations = 0;
  // percentage alive now

  // average percentage alive so far
  //    = ((alivesofar * generations - 1) + alivenow) / generations
};

//void read_in_file(FILE *infile, struct universe *u);
//void write_out_file(FILE *outfile, struct universe *u);
int is_alive(struct universe *u, int column, int row){
  if (u->cells[row][column] == '.') {
    return(0);
  }
  else {
    return(1);
  }
};

int will_be_alive(struct universe *u, int column, int row){
  // Deals with cells on the top of the grid
  if (row == 0) {
    int northwest = 0;
    int north = 0;
    int northeast = 0;
    int west = is_alive(u,column-1,row);
    int southwest = is_alive(u,column-1,row-1);
    int south = is_alive(u,column,row-1);
    int southeast = is_alive(u,column+1,row-1);
    int east = is_alive(u,column+1,row);
  }
  // Deals with cells on the left of the grid
  else if (column == 0) {
    int northwest == 0;
    int west == 0;
    int southwest == 0;
    int south = is_alive(u,column,row-1);
    int southeast = is_alive(u,column+1,row-1);
    int east = is_alive(u,column+1,row);
    int northeast = is_alive(u,column+1,row+1);
    int north = is_alive(u,column,row+1);
  }
  // Deals with cells on the bottom of the grid
  else if (row == u->rows) {
    int southwest == 0;
    int south == 0;
    int southeast == 0;
    int east = is_alive(u,column+1,row);
    int northeast = is_alive(u,column+1,row+1);
    int north = is_alive(u,column,row+1);
    int northwest = is_alive(u,column-1,row+1);
    int west = is_alive(u,column-1,row);
  }
  // Deals with cells on the right of the grid
  else if (column == u->columns) {
    int northeast == 0;
    int east == 0;
    int southeast == 0;
    int north = is_alive(u,column,row+1);
    int northwest = is_alive(u,column-1,row+1);
    int west = is_alive(u,column-1,row);
    int southwest = is_alive(u,column-1,row-1);
    int south = is_alive(u,column,row-1);
  }
  // Deals with all other cells
  else {
    int north = is_alive(u,column,row+1);
    int northwest = is_alive(u,column-1,row+1);
    int west = is_alive(u,column-1,row);
    int southwest = is_alive(u,column-1,row-1);
    int south = is_alive(u,column,row-1);
    int southeast = is_alive(u,column+1,row-1);
    int east = is_alive(u,column+1,row);
    int northeast = is_alive(u,column+1,row+1);
  }
  int neighbours = northwest+north+northeast+west+southwest+south+southeast+east;
    if (neighbours == 3) {
      return(1);
    }
    else if (neighbours == 2) {
      if (is_alive(u,row,column)) {
        return(1);
      } else {
        return(0);
      }
    } else {
      return(0);
    }
};

//int will_be_alive_torus(struct universe *u,  int column, int row);

void evolve(struct universe *u, int (*rule)(struct universe *u, int column, int row));{
  char newCells[u->rows][u->columns]; // MALLOC THIS LATER!
  for (i = 0; i < u->rows; i++) {
    for (j = 0; j < u->columns; j++){
      newCells[i][j] = rule(u, j, i);
    }
  }






};



void print_statistics(struct universe *u);{};


// redownload gameoflife.c!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int main(int argc, char argv[]){
  struct universe v; 
  read_in_file(stdin,&me)
  evolve(&v,will_be_alive);
  evolve(&v,will_be_alive);
  evolve(&v,will_be_alive);
  evolve(&v,will_be_alive);
  evolve(&v,will_be_alive);
  write_out_file(stdout,&v);
return 0;
}