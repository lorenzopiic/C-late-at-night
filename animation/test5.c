#include<stdio.h>
#include <unistd.h>
#include<string.h>
#define GRID_ROWS 10
#define GRID_COLS 40
#define GRID_CELLS (GRID_ROWS * GRID_COLS)
#define ALIVE '*'
#define DEAD '.'

//#define DEBUG

typedef char grid_t[GRID_COLS][GRID_ROWS];

void init_grid(grid_t grid, char state){
    for(unsigned y = 0; y<GRID_ROWS;y++){
        for(unsigned x=0; x<GRID_COLS;x++){
            grid[x][y] = state;
        }
    }
}

void display_grid(grid_t grid){
#ifdef DEBUG


        puts("\n");

#endif
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

void animate_column_lr(grid_t grid){
   static int x_copy = 0;
   static int y_copy = 0;

   x_copy = x_copy % (GRID_COLS);
   y_copy = y_copy % (GRID_ROWS);

   grid[x_copy][y_copy] = ALIVE;

      /*  if(x_copy == GRID_COLS-1){
                y_copy++;
    }*/

        x_copy++;

        return;
}

void animate_row_ud(grid_t grid){
	static int y_copy = 0; 
	
	grid[GRID_COLS-1][y_copy] = ALIVE;
	y_copy++; 

}
void animate_column_rl(grid_t grid){
   static int x_copy = GRID_COLS-1;
   static int y_copy = GRID_ROWS-1;

   x_copy = x_copy % (GRID_COLS);
   y_copy = y_copy % (GRID_ROWS);

   grid[x_copy][y_copy] = ALIVE;

      /*  if(x_copy == GRID_COLS-1){
                y_copy++;
    }*/

        x_copy--;

        return;
}

void animate_row_du(grid_t grid){
	static int y_copy = GRID_ROWS-1; 
	
	grid[0][y_copy] = ALIVE;
	y_copy--; 

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




int main(void) {
    grid_t buf;

    init_grid(buf, DEAD);

        for(int i = 0;i<GRID_COLS;i++){
        animate_column_lr(buf); // COLUMN LEFT RIGHT // 
        display_grid(buf);
        init_grid(buf,DEAD);
        usleep(100000);
    }
		for(short unsigned i=0; i<GRID_ROWS;i++){
        animate_row_ud(buf); // ROW UP DOWN // 
        display_grid(buf);
		init_grid(buf,DEAD);		
		usleep(100000);	
	}
		for(int i = 0;i<GRID_COLS;i++){
        animate_column_rl(buf); // COLUMN LEFT RIGHT // 
        display_grid(buf);
        init_grid(buf,DEAD);
        usleep(100000);
    }
		for(short unsigned i=0; i<GRID_ROWS;i++){
        animate_row_du(buf); // ROW UP DOWN // 
        display_grid(buf);
		init_grid(buf,DEAD);		
		usleep(100000);	
	}

/*        for(int i = 0; i<GRID_CELLS;i++){
        animate_backwords(buf);
        display_grid(buf);
                init_grid(buf,DEAD);
                usleep(100000);
        }
*/
    return 0;
}
