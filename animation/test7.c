#include<stdio.h>
#include <unistd.h>
#include<string.h>
#define GRID_ROWS 15
#define GRID_COLS 15
#define GRID_CELLS (GRID_ROWS * GRID_COLS)
#define ALIVE '*'
#define DEAD '.'
#define TIME 100000
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
            printf("%c ", grid[x][y]);
        }
    printf("\n");
    }
}
/*
 
   	"x_reps" is the rep counter
 
 	"y_p" is the is the current position point of the y
 */

void animate_column_lr(grid_t grid,int x_reps,int y_p){ 
	static int x_offset = 0; 
   	static int times = 0; 
	for(short unsigned x = 0; x < x_reps-x_offset;x++){
    	grid[x+x_offset][y_p] = ALIVE;
    	display_grid(grid);
    	init_grid(grid,DEAD);
    	usleep(TIME);
   }
	times++;
	if(times >= 2) {
		x_offset++; 
	}	
        return;
}

void animate_row_ud(grid_t grid,int x_p, int y_reps){
	static int y_offset = 0; 
	for(short unsigned y =y_offset; y < y_reps; y++){
        grid[x_p][y] = ALIVE;
    	display_grid(grid);
    	init_grid(grid,DEAD);
    	usleep(TIME);
      }
	y_offset++;
	return; 
}

void animate_column_rl(grid_t grid,int x_reps, int y_p){
	static int x_offset = 0; 
	static int times = 0; 
	
	for(short unsigned x = x_reps;x > x_offset;x--){
    	grid[x][y_p] = ALIVE;
    	display_grid(grid);
    	init_grid(grid,DEAD);
    	usleep(TIME);
   }
    if(times%2 == 0){
		x_offset++; 
	}    
	return;
}

void animate_row_du(grid_t grid,int x_reps,int y_reps){
	static int y_offset = 0; 
	for(short unsigned y = y_reps; y >y_offset; y--){
        grid[x_reps][y] = ALIVE;
    	display_grid(grid);
    	init_grid(grid,DEAD);
    	usleep(TIME);
      }
	y_offset++; 

	return; 
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
    for(short unsigned r = 0;r<=GRID_ROWS / 2;r++){
	  animate_column_lr(buf,GRID_COLS-1-r,r);	 // COLUMN LEFT RIGHT //
   		
   	  animate_row_ud(buf,GRID_COLS-1-r,GRID_ROWS-r);	  // ROW UP DOWN // 
	
	  animate_column_rl(buf,GRID_COLS-1-r,GRID_ROWS-1-r);   // 

      animate_row_du(buf,r,GRID_ROWS-1-r);	  
	
#ifdef DEBUG
	fprintf(stdout,"****************\nr >>> %d \n\n", r); 
#endif	
	}

    return 0;
}
