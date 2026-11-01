#include<stdio.h>
#include<unistd.h>
#include<stdbool.h>
#define COLS 15
#define ROWS 10

#define DEAD '.'
#define ALIVE '*'

//#define DEBUG
void print_grid(char grid[][COLS]);
void set_grid_state(char grid[][COLS], char state);
char get_cell_state(char grid[][COLS],int x, int y);
void set_cell_state(char grid[][COLS],int x,int y,char state); 
void module(int*x, int* y);
void clear(void);

int main(void){

	char grid[ROWS][COLS]; 
	
	clear(); 
	set_grid_state(grid,DEAD);
	print_grid(grid);
	sleep(3); 
	clear();	
	fprintf(stdout,"Setting alive cell at x = 1 , y = 2\n\n"); 
	set_cell_state(grid,1,2,ALIVE); 
	print_grid(grid);
	sleep(3);
	clear(); 
	fprintf(stdout,"Ok, no we test the module foo\n"); 
	sleep(3);
	clear(); 
	fprintf(stdout,"Setting alive cell at x = -3 , y = -1\n\n"); 
	set_grid_state(grid,DEAD);
	set_cell_state(grid,-3,-1,ALIVE);
	print_grid(grid);
	return 0; 
}

/* prints the grid */

void print_grid(char grid[][COLS]){
	
	printf("   "); 
	
	for(int n = 0; n<COLS;n++){
		printf("%d   ",n);
   	}
	
	printf("\n\n"); 
	
	for(int x = 0; x<ROWS;x++){
			printf("%d  ",x); 
	
	for(int y = 0; y<COLS; y++){
		if(y > 9){
			printf(" "); 
		}
		printf("%c   ",get_cell_state(grid,x,y)); 
	}
		
		printf("\n\n");
	}
	printf("\n"); 
}

char get_cell_state(char grid[][COLS],int x,int y){
	return grid[x][y];
}
void set_grid_state(char grid[][COLS], char state){
    for(int y = 0; y < ROWS; y++)
        for(int x = 0; x < COLS; x++)
            set_cell_state(grid, x, y, state);
}

void set_cell_state(char grid [][COLS],int x, int y,char state){
	module(&x,&y);
	grid[x][y] = state;
}

void module(int *x, int *y){
    if(*x < 0){
        *x = -*x;
        *x = *x % COLS;      
        *x = COLS - *x;
    }
    if(*y < 0){
        *y = -*y;
        *y = *y % ROWS;
        *y = ROWS - *y;
    }

    if(*x >= COLS){ *x = *x % COLS; }   
	if(*y >= ROWS){ *y = *y % ROWS; }

#ifdef DEBUG

	fprintf(stdout,"\nDEBUG into module()\n*x = %d\n*y = %d\n",
											*x,*y); 
#endif
}

void clear(void){
	printf("\033[H\033[2J\033[3J"); 

}
