#include<stdio.h>
#include<unistd.h>
#define COLS 15
#define ROWS 10

#define DEAD '.'
#define ALIVE '*'


void print_grid(char GRID[][COLS]);
void set_grid(char GRID[][COLS], char STATE);
char get_cell_state(char GRID[][COLS],int x, int y);
void set_cell_state(char GRID[][COLS],int x,int y,char STATE); 
void module(int*x, int* y);
void clear(void);

int main(void){

	char GRID[ROWS][COLS]; 
	
	clear(); 
	set_grid(GRID,DEAD);
	print_grid(GRID);
	sleep(3); 
	clear();	
	fprintf(stdout,"Setting alive cell at x = 1 , y = 2\n"); 
	set_cell_state(GRID,1,2,ALIVE); 
	print_grid(GRID);
	sleep(3);
	clear(); 
	fprintf(stdout,"Ok, no we test the module foo\n"); 
	sleep(3);
	clear(); 
	fprintf(stdout,"Setting alive cell at x = -3 , y = -1\n"); 
	set_cell_state(GRID,-3,-1,ALIVE);
	print_grid(GRID);
	return 0; 
}

/* prints the grid */

void print_grid(char GRID[][COLS]){

	for(int x = 0; x<ROWS;x++){
			printf("%d  ",x); 
		for(int y = 0; y<COLS; y++){
			printf("%c",get_cell_state(GRID,x,y)); 
		}
	printf("\n\n");
	}
	printf("\n"); 
}

char get_cell_state(char GRID[][COLS],int x,int y){
	module(&x,&y);
	return GRID[x][y];
}

void set_grid(char GRID[ROWS][COLS],char STATE){
	for(int x=0; x<ROWS; x++){
		for(int y=0; y<COLS; y++){
			set_cell_state(GRID,x,y,STATE);
		}
	}	
}
void set_cell_state(char GRID [][COLS],int x, int y,char STATE){
	module(&x,&y);
	GRID[x][y] = STATE;
}

void module(int* x, int* y){
	if (*x < 0){
		*x = -(*x); 
		*x = ROWS - *x;
	}
	if (*y < 0){
		*y = -(*y);
		*y = COLS - *y; 
	}

	if(*x > ROWS){ *x = *x % ROWS; }
	
	if(*y > COLS){ *y = *y % COLS; }

}

void clear(void){
	printf("\033\[H\033[2J\033[3J"); 

}
