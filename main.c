#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {
  printf("General matrix tests --------------------\n");
  struct matrix * mat1;
  struct matrix * mat2;

  mat1 = new_matrix(4, 4);
  mat2 = new_matrix(4, 2);

  //populating mat1
  add_edge(mat1, 1.245, 4.128, 1233.122, 5.231, 7.412, 98.234);
  add_edge(mat1, 132.245, 5.128, 14.122, 5.231, 72.352, 3.134);

  //populating mat2
  add_edge(mat2, 85.352, 746.145, 33.142, 89.231, 1.412, 823.263);

  printf("\nDisplaying mat1 and mat2...\n");
  print_matrix(mat1);
  printf("\n");
  print_matrix(mat2);

  printf("\nMultiplying mat1 and mat2...\n");
  matrix_mult(mat1, mat2);
  print_matrix(mat2);

  printf("Turning mat1 into an identity matrix...\n");
  ident(mat1);
  print_matrix(mat1);

  free_matrix(mat1);
  free_matrix(mat2);

  //End of general matrix testing -------------------

  //Image production -----------------------

  screen s;
  color c;
  c.red = 250;
  c.green = 0;
  c.blue = 0;

  clear_screen(s);

  struct matrix *edges = new_matrix(4, 4);
  struct matrix *edges2 = new_matrix(4, 4);
  int i;
  for(i=0; i < 500; i++){
    add_edge(edges, i, (i-250)*(i-250) / 250, 1, i, (i-250)*(i-250)/(-250) +500, 1);
  }
  draw_lines(edges, s, c);

  c.red = 255;
  c.green = 255;
  c.blue = 255;
  for(i=15; i < 65; i++){
    add_edge(edges2, i, 400, 1, i, 475, 1);
  }
  for(i=435; i < 485; i++){
    add_edge(edges2, i, 400, 1, i, 475, 1);
  }

  draw_lines(edges2, s, c);

  c.red= 0;
  c.green=0;
  c.blue=0;
  draw_line(0, 250, 499, 250, s, c);

  display(s);  
  save_extension(s, "matrix.png");
  free_matrix( edges ); 
  free_matrix( edges2 );
}
