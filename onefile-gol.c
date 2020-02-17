#include<stdio.h>
#include<conio.h>
#include<string.h>

#define UNIVERSE_HARDCODE {{{'.','.','.','.','.','.','.','.','.'},{'.','.','.','*','.','.','.','.','.'},{'.','.','*','*','*','.','.','.','.'},{'.','.','.','*','.','.','.','.','.'},{'.','.','.','.','.','.','.','.','.'}},5,9,4,8,0}

struct universe {
  char cells[5][9];
  int rows;
  int cols;
  int MAX_ROW_INDEX;
  int MAX_COL_INDEX;
  int generations;
  // percentage alive now
  // average percentage alive so far
  //    = ((alivesofar * generations - 1) + alivenow) / generations
};

//void read_in_file(FILE *infile, struct universe *u);
//void write_out_file(FILE *outfile, struct universe *u);

void write_out_console (struct universe *u) {
  printf("\n");
  for (int i = 0; i < u->rows; i++){
    for (int j = 0; j < u->cols; j++) {
      putc(u->cells[i][j], stdout);
    }
    printf("\n");
  }
  printf("\n");
};

int is_alive(struct universe *u, int column, int row){
  //printf("I receive %d as my row and %d as my column \n",row,column);
  if (u->cells[row][column] == '.') {
    //printf("%d,%d is dead \n",row,column);
    return(0);
  }
  else {
    //printf("%d,%d is alive \n",row,column);
    return(1);
  }
};

int will_be_alive(struct universe *u, int column, int row){

  //printf("investigating %d,%d's neighbours \n",row,column);

  int north, northeast, east, southeast, south, southwest, west, northwest = 0;

  if (row == 0) {
   north = 0;
  } else {
    north = is_alive(u,column,row-1);}
  if (row == 0 || column == u->MAX_COL_INDEX) {
    northeast = 0;
  } else {
    northeast = is_alive(u,column+1,row-1);}
  if (column == u->MAX_COL_INDEX) {
    east = 0;
  } else {
    east = is_alive(u,column+1,row);}
  if (row == u->MAX_ROW_INDEX || column == u->MAX_COL_INDEX) {
    southeast = 0;
  } else {
    southeast = is_alive(u,column+1,row+1);}
  if (row == u->MAX_ROW_INDEX) {
    south = 0;
  } else {
    south = is_alive(u,column,row+1);}
  if (row == u->MAX_ROW_INDEX || column == 0) {
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
  //printf("I have %d alive neighbours \n",neighbours);

  if (neighbours == 3) {
    //printf("so I live \n");
    return(1);
  } else if (neighbours == 2) {
    if (is_alive(u,column,row)) {
      //printf("and I'm alive, so I live \n");
      return(1);
    } else {
      //printf("and I'm dead, so I die \n");
      return(0);
    }
  } else {
    //printf("so I die \n");
    return(0);
  }
};

//int will_be_alive_torus(struct universe *u,  int column, int row);

void evolve(struct universe *u, int (*rule)(struct universe *u, int column, int row)){
  char newCells[u->rows][u->cols]; // MALLOC THIS LATER!
  for (int i = 0; i < u->rows; i++) {
    for (int j = 0; j < u->cols; j++) {
      if (rule(u, j, i)) {
        newCells[i][j] = '*';
      } else {
        newCells[i][j] = '.';
      }
    }
  }

  // replace the following with pointer magic
  for (int i = 0; i < u->rows; i++) {
    for (int j = 0; j < u->cols; j++) {
      u->cells[i][j] = newCells[i][j];
    }
  }

};



//void print_statistics(struct universe *u){};


int main(){
  struct universe v = UNIVERSE_HARDCODE;
  write_out_console(&v);
  evolve(&v,will_be_alive);
  write_out_console(&v);
  evolve(&v,will_be_alive);
  write_out_console(&v);
  evolve(&v,will_be_alive);
  write_out_console(&v);
  evolve(&v,will_be_alive);
  write_out_console(&v);
  evolve(&v,will_be_alive);
  write_out_console(&v);
  evolve(&v,will_be_alive);
  write_out_console(&v);
  evolve(&v,will_be_alive);
  write_out_console(&v);
return 0;
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