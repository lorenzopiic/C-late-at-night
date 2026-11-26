#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<limits.h>
#define GRID_ROWS 21
#define GRID_COLS 21
#define GRID_CELLS (GRID_ROWS * GRID_COLS)
#define ALIVE '*'
#define DEAD '.'
#define TIME (useconds_t) 1000
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
		goto SKIPCLEAR;
#endif
    printf("\033[H\033[2J\033[3J");
SKIPCLEAR:
  		for(unsigned y = 0; y<GRID_ROWS;y++){
        for(unsigned x=0; x<GRID_COLS;x++){
            printf("%c ", grid[x][y]);
        }
    printf("\n");
    }
}

unsigned count_remainings(grid_t grid){
	
	unsigned ret = GRID_CELLS; 
		
	for(int y = 0; y < GRID_ROWS; y++){
		for(int x = 0; x < GRID_COLS; x++){
			if(grid[x][y] == ALIVE){
				ret--; 	
			}
		}
	}
	
	return ret; 

}

void randomize_grid(grid_t grid){

	static int times = 0;
	
	while((count_remainings(grid)) != 0 ){
	
		unsigned x = (rand() % INT_MAX); 
		if(x >= GRID_COLS){
			x = x % GRID_COLS; 
		}
		/*if(x <= GRID_COLS){
			x = -x;
			x = x % GRID_COLS; 
			x = GRID_COLS - x; 
		}
	*/
	unsigned y = (rand() % INT_MAX);
	if(y >= GRID_ROWS){
			y = y % GRID_ROWS; 
		}
		/*if(y <= GRID_ROWS){
			y = -y;
			y = y % GRID_ROWS; 
			y = GRID_ROWS - y; 
		}*/

#ifdef DEBUG
		printf("x = %ld\ny = %ld\nremainings = %d\n",
					x,y,count_remainings(grid));  
#endif		

		if(times % 100 == 0){
			x = 0;  
		}
		if(times % 200 == 0){
			y = 0; 
			times = 0;	
		}

		grid[x][y] = ALIVE;
		display_grid(grid);
		usleep(TIME);
		times++;
	}

}

int main(void) {
    grid_t buf;
	
	srand(time(NULL));
	
	init_grid(buf,DEAD);	
	randomize_grid(buf);

    return 0;
}
