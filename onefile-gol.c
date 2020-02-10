#include<stdio.h>

struct universe {
    int cells[4][9] = {
        {0,0,0,0,0,0,0,0,0},
        {0,1,1,1,0,0,1,1,0},
        {0,0,0,0,0,0,1,1,0},
        {0,0,0,0,0,0,0,0,0}}


};

void read_in_file(FILE *infile, struct universe *u);
void write_out_file(FILE *outfile, struct universe *u);
int is_alive(struct universe *u, int column, int row);
int will_be_alive(struct universe *u, int column, int row);
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
