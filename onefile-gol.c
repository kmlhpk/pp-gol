#include<stdio.h>

#define UNIVERSE_HARDCODE {{{'.','.','.','.','.','.','.','.','.'},{'.','.','.','*','.','.','.','.','.'},{'.','.','*','*','*','.','.','.','.'},{'.','.','.','*','.','.','.','.','.'},{'.','.','.','.','.','.','.','.','.'}},5,9,4,8,3,1.0/15.0,3,1,1.0/15.0}

// #define STUPID_1 {{{"."}},1,1,0,0,1}

// #define STUPID_2 {{{"*","*"},{".","."}},2,2,1,1,1}

struct universe {
  char cells[5][9];
  int rows;
  int cols;
  int MAX_ROW_INDEX;
  int MAX_COL_INDEX;
  int aliveNow;
  float aliveNowFrac;
  int aliveSoFar;
  int generations;
  float aliveAverageFrac;
};

//void read_in_file(FILE *infile, struct universe *u);
//void write_out_file(FILE *outfile, struct universe *u);

// A debug function to easily print shit to the console - DELETE LATER!!!!!!!!!!!!!!!
void write_out_console (struct universe *u) {
  printf("\n");
  for (int i = 0; i < u->rows; i++){
    for (int j = 0; j < u->cols; j++) {
      fputc(u->cells[i][j], stdout);
    }
    printf("\n");
  }
  printf("\n");
};

// Amends C's % operator to return a modulo like in Python, not a remainder
// Behaviour undefined for b = 0
// SLAP THIS IN A DEFINE AND DOUBLE-CHECK WITH KONRAD (possibly move this to gol.c) Qs 8 and 14 in FAQ
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
  #define ISALIVE_DEBUG1 printf("I receive %d as my row and %d as my column \n",row,column);
  if (u->cells[row][column] == '.') {
    #define ISALIVE_DEAD printf("%d,%d is dead \n",row,column);
    return(0);
  }
  else {
    #define ISALIVE_ALIVE printf("%d,%d is alive \n",row,column);
    return(1);
  }
};

int will_be_alive(struct universe *u, int column, int row){
  #define WILLBEALIVE_DEBUG1 printf("investigating %d,%d's neighbours \n",row,column);

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
  
  #define WILLBEALIVE_DEBUG2 printf("I have %d alive neighbours \n",neighbours);

  if (neighbours == 3) {
    #define SOILIVE printf("so I live \n");
    return(1);
  } else if (neighbours == 2) {
    if (is_alive(u,column,row)) {
      #define ALIVE_LIVE printf("and I'm alive, so I live \n");
      return(1);
    } else {
      #define DEAD_DIE printf("and I'm dead, so I die \n");
      return(0);
    }
  } else {
    #define SOIDIE printf("so I die \n");
    return(0);
  }
};

int will_be_alive_torus(struct universe *u,  int column, int row){
  int north, northeast, east, southeast, south, southwest, west, northwest = 0;

  north = is_alive(u,mod(column,u->cols),mod(row-1,u->rows));
  northeast = is_alive(u,mod(column+1,u->cols),mod(row-1,u->rows));
  east = is_alive(u,mod(column+1,u->cols),mod(row,u->rows));
  southeast = is_alive(u,mod(column+1,u->cols),mod(row+1,u->rows));
  south = is_alive(u,mod(column,u->cols),mod(row+1,u->rows));
  southwest = is_alive(u,mod(column-1,u->cols),mod(row+1,u->rows));
  west = is_alive(u,mod(column-1,u->cols),mod(row,u->rows));
  northwest = is_alive(u,mod(column-1,u->cols),mod(row-1,u->rows));

  int neighbours = northwest+north+northeast+west+southwest+south+southeast+east;

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
  char newCells[u->rows][u->cols]; // MALLOC THIS LATER!
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

  printf("%d alive in this generation\n",u->aliveNow);
  printf("%d alive so far\n",u->aliveSoFar);

  u->aliveNow = aliveNew;
  u->aliveNowFrac = (float)u->aliveNow / (float)(u->rows * u->cols);
  u->aliveSoFar += u->aliveNow;
  u->generations += 1;
  u->aliveAverageFrac = (float)u->aliveSoFar / (float)(u->generations*u->rows*u->cols);

  // replace the following with pointer magic
  for (int i = 0; i < u->rows; i++) {
    for (int j = 0; j < u->cols; j++) {
      u->cells[i][j] = newCells[i][j];
    }
  }
};

void print_statistics(struct universe *u){
  printf("%.3f%% of cells currently alive\n",u->aliveNowFrac*(float)100);
  printf("%.3f%% of cells alive on average\n",u->aliveAverageFrac*(float)100);
};

int main(){
  struct universe v = UNIVERSE_HARDCODE;
  write_out_console(&v);
  print_statistics(&v);
  evolve(&v,will_be_alive_torus);
  write_out_console(&v);
  print_statistics(&v);
  evolve(&v,will_be_alive_torus);
  write_out_console(&v);
  print_statistics(&v);
  evolve(&v,will_be_alive_torus);
  write_out_console(&v);
  print_statistics(&v);
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