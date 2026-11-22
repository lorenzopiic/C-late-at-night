#include<stdio.h>
#include <unistd.h>
#include<string.h>
#define GRID_ROWS 8
#define GRID_COLS 10
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

void animate_backwords(grid_t grid){
   static int x_copy = GRID_COLS-1;
   static int y_copy = GRID_ROWS-1;

#ifdef DEBUG
   	fprintf(stdout,"======================================"); 	
  	puts(""); 
   	fprintf(stdout,"x = %d\ny = %d\n", x_copy,y_copy); 
  #endif
  	
	if(x_copy<0){
   		x_copy = -x_copy;
		x_copy = GRID_COLS-x_copy; 
   }
	grid[x_copy][y_copy] = ALIVE;	
	
	if(x_copy == 0){
		y_copy--;
    }    
   	x_copy--; 
	return;
}



int main(void) {
    grid_t buf;

    init_grid(buf, DEAD);
    
	for(int i = 0;i<GRID_CELLS;i++){
        animate(buf);
        display_grid(buf);
        init_grid(buf,DEAD);
        usleep(100000);
    }
	
	for(int i = 0; i<GRID_CELLS;i++){
        animate_backwords(buf);
        display_grid(buf);
		init_grid(buf,DEAD);
		usleep(100000);
	}

    return 0;
}

