#include<stdio.h>

struct universe {
  char cells[4][9] = {
    {'.','.','.','.','.','.','.','.','.'},
    {'.','*','*','*','.','.','*','*','.'},
    {'.','.','.','.','.','.','*','*','.'},
    {'.','.','.','.','.','.','.','.','.'}};
  int rows = 4;
  int cols = 9;
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
    int west = is_alive(u,row,column-1);
    int southwest = is_alive(u,row-1,column-1);
    int south = is_alive(u,row-1,column);
    int southeast = is_alive(u,row-1,column+1);
    int east = is_alive(u,row,column+1);
    int neighbours = northwest+north+northeast+west+southwest+south+southeast+east
    if (neighbours == 3) {
      return(1);
    }
    else if (neighbours == 2) {
      if (is_alive(u,row,column)) {
        return(1);
      }
      

    }
  }
  else if (column == 0) {
    int northwest == 0;
    int west == 0;
    int southwest == 0;
  }
  else if (row == u->rows) {
    int southwest == 0;
    int south == 0;
    int southeast == 0;
  }
  else if (column == u->columns) {
    int northeast == 0;
    int east == 0;
    int southeast == 0;
  }
};


int will_be_alive_torus(struct universe *u,  int column, int row);
void evolve(struct universe *u, int (*rule)(struct universe *u, int column, int row));
void print_statistics(struct universe *u);



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