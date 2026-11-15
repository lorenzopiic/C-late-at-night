#include<stdio.h>
#include <unistd.h>
#include<string.h>
#define GRID_ROWS 10
#define GRID_COLS 30
#define ALIVE '*'
#define DEAD '.'
typedef char grid_t[GRID_COLS][GRID_ROWS];

void init_grid(grid_t grid, char state){
    for(unsigned y = 0; y<GRID_ROWS;y++){
        for(unsigned x=0; x<GRID_COLS;x++){
            grid[x][y] = state;
        }
    }
}

void display_grid(grid_t grid){
    printf("\033[H\033[2J\033[3J");
    for(unsigned y = 0; y<GRID_ROWS;y++){
        for(unsigned x=0; x<GRID_COLS;x++){
            printf("%c", grid[x][y]);
        }
    printf("\n");
    }
}

/*
 *          0 1 2 3 4 5 6 7 8 9
 *      0   . . . . . . . . . .
 *      1   . . . . . . . . . .
 *      2   . . . . . . . . . .
 *      3   . . . . . . . . . .
 *      4   . . . . . . . . . .
 *      5   . . . . . . . . . .
 *      6   . . . . . . . . . .
 *      7   . . . . . . . . . .
 *      8   . . . . . . . . . .
 *      9   . . . . . . . . . .
 *
 *                                                                */
void animate(grid_t grid){
   static int x_copy = 0;
   static int y_copy = 0;

   x_copy = x_copy % (GRID_COLS);
   y_copy = y_copy % (GRID_ROWS);

   grid[x_copy][y_copy] = ALIVE;

        if(x_copy == GRID_COLS-1){
                y_copy++;
    }

        x_copy++;

        return;
}

int main(void) {
    grid_t buf;

    init_grid(buf, DEAD);
    display_grid(buf);

    while (1) {
        animate(buf);
        display_grid(buf);
        init_grid(buf,DEAD);
        usleep(100000);
    }

    return 0;
}

