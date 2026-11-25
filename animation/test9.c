/* Same as test7 but sets ALIVE the passed CELLS */

#include<stdio.h>
#include <unistd.h>
#include<string.h>
#define GRID_ROWS 21
#define GRID_COLS 21
#define GRID_CELLS (GRID_ROWS * GRID_COLS)
//#define ALIVE '*'
#define DEAD '.'
#define TIME 10000
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

void animate_column_lr(grid_t grid,char symbol,int* reset,int x_reps,int y_p){

        static int x_offset = 0;
        static int times = 0;
        
		if(*reset == 1){
			x_offset = 0; 
			times = 0;   
		}
		for(short unsigned x = 0; x < x_reps-x_offset;x++){
        grid[x+x_offset][y_p] = symbol;
        display_grid(grid);
        usleep(TIME);
   }
        times++;
        if(times >= 2) {
                x_offset++;
        }
        return;
}

void animate_row_ud(grid_t grid,char symbol,int* reset,int x_p, int y_reps){
        static int y_offset = 0;
        if(*reset == 1){
			y_offset = 0; 
		}
		for(short unsigned y =y_offset; y < y_reps; y++){
        grid[x_p][y] = symbol;
        display_grid(grid);
        usleep(TIME);
      }
        y_offset++;
        return;
}

void animate_column_rl(grid_t grid,char symbol,int* reset,int x_reps, int y_p){
        static int x_offset = 0;
        static int times = 0;

		if(*reset == 1){
			x_offset = 0; 
			times = 0; 
		}

        for(short unsigned x = x_reps;x > x_offset;x--){
        grid[x][y_p] = symbol;
        display_grid(grid);
        usleep(TIME);
   }
    if(times%2 == 0){
         x_offset++;
        }
        return;
}

void animate_row_du(grid_t grid,char symbol, int* reset,int x_reps,int y_reps){
        static int y_offset = 0;
        if(*reset == 1){
			y_offset = 0; 
		}
		for(short unsigned y = y_reps; y >y_offset; y--){
        grid[x_reps][y] = symbol;
        display_grid(grid);
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
	int reset = 0; 

	int* resetPtr = &reset;  
/*
	 
	"mlcounter" stands for Main Loop Couter 
*/ 
	int mlcounter = 0; 
		
	char symbols[10] = {'0','1','2','3','4','5','6','7','8','9'}; 
	 
	while(mlcounter < 10){
	
		char alive_symbol = symbols[mlcounter];

		for(short unsigned r = 0;r<=GRID_ROWS / 2;r++){
          animate_column_lr(buf,alive_symbol,resetPtr,
				  GRID_COLS-1-r,r);        

          animate_row_ud(buf,alive_symbol,resetPtr,
				  GRID_COLS-1-r,GRID_ROWS-r);         

          animate_column_rl(buf,alive_symbol,resetPtr,
				  GRID_COLS-1-r,GRID_ROWS-1-r);  

     	  animate_row_du(buf,alive_symbol,resetPtr,
				  r,GRID_ROWS-1-r);
 

#ifdef DEBUG
        fprintf(stdout,"****************\nr >>> %d \n\n", r);
#endif
        }
		mlcounter++; 
		reset = 1; 
		init_grid(buf,DEAD);
	
	}
    return 0;
}
