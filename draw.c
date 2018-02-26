#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

/*======== void add_point() ==========
Inputs:   struct matrix * points
         int x
         int y
         int z 
Returns: 
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, double x, double y, double z) {
    if(points->lastcol == points->cols){
        grow_matrix(points, points->lastcol+10);
    }
    points->m[0][points->lastcol] = x;
    points->m[1][points->lastcol] = y;
    points->m[2][points->lastcol] = z;
    points->m[3][points->lastcol] = 1;
    points->lastcol += 1;
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns: 
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/
void add_edge( struct matrix * points, 
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1) {
    add_point(points, x0, y0, z0);
    add_point(points, x1, y1, z1);
}

/*======== void draw_lines() ==========
Inputs:   struct matrix * points
         screen s
         color c 
Returns: 
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void draw_lines( struct matrix * points, screen s, color c) {
    int i;
    for (i = 0; i < points->lastcol; i+=2) {
        draw_line((int)points->m[0][i], (int)points->m[1][i], (int)points->m[0][i+1], (int)points->m[1][i+1], s, c);
    }
}

void swap_coords(int * x0, int * y0, int * x1, int * y1){
    int tmpx = *x0;
    int tmpy = *y0;
    *x0 = *x1;
    *y0 = *y1;
    *x1 = tmpx;
    *y1 = tmpy;
}

//draws lines in octant 2
//since c is pass by value, use x0 and y0 as manipulatable variables
void draw_oct2(int x0, int y0, int x1, int y1, screen s, color c, int a, int b){
    int d = a + 2*b;
    while(y0 <= y1){
        plot(s, c, x0, y0);
        if(d < 0){
            x0++;
            d += 2*a;
        }
        y0++;
        d += 2*b;
    }
    printf("oct 2 end: %d %d\n", x0, y0);
}

//draws lines in octant 1
void draw_oct1(int x0, int y0, int x1, int y1, screen s, color c, int a, int b){
    int d = 2*a + b;
    while(x0 <= x1){
        plot(s, c, x0, y0);
        if(d > 0){
            y0++;
            d += 2*b;
        }
        x0++;
        d += 2*a;
    }
    printf("oct 1 end: %d %d\n", x0, y0);
}

//draws lines in octant 8
void draw_oct8(int x0, int y0, int x1, int y1, screen s, color c, int a, int b){
    int d = 2*a - b;
    while(x0 <= x1){
        plot(s, c, x0, y0);
        if(d < 0){
            y0--;
            d -= 2*b;
        }
        x0++;
        d += 2*a;
    }
    printf("oct 8 end: %d %d\n", x0, y0);
}

//draws lines in octant 7
void draw_oct7(int x0, int y0, int x1, int y1, screen s, color c, int a, int b){
    int d = a - 2*b;
    while(y0 >= y1){
        plot(s, c, x0, y0);
        if(d > 0){
            x0++;
            d += 2*a;
        }
        y0--;
        d -= 2*b;
    }
    printf("oct 7 end: %d %d\n", x0, y0);
}

void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
    if(x1 < x0){ //to maintain a 4 octant drawing system, we draw always from left to right
        swap_coords(&x0, &y0, &x1, &y1);
    }
    int a = y1 - y0;//a is delta y
    int b = x0 - x1;//b is -delta x
    if(a >= -1*b && a > 0){ //if the slope is within octant 2
        draw_oct2(x0, y0, x1, y1, s, c, a, b);
    }
    else if(a < -1*b && a >= 0){//if the slope is within octant 1
        draw_oct1(x0, y0, x1, y1, s, c, a, b);
    }
    else if(-1*a < -1*b && a < 0){//if the slope is within octant 8
        draw_oct8(x0, y0, x1, y1, s, c, a, b);
    }
    else{//if the slope is within octant 7
        draw_oct7(x0, y0, x1, y1, s, c, a, b);
    }
}
