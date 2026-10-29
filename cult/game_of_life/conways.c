#include<stdio.h>

#define COLS 30
#define ROWS 15

#define DEAD '.'
#define ALIVE '*'




void print_grid(char GRID[][COLS]);
void set_grid(char GRID[][COLS], char STATE);
char get_state(char GRID[][COLS],unsigned x, unsigned y);
void set_cell(char GRID[][COLS],unsigned x, unsigned y,char STATE); 
void clear(void);

int main(void){

	char GRID[ROWS][COLS]; 
	
	clear(); 
	set_grid(GRID,DEAD);
	//clear();
	//set_cell(12,13);
	print_grid(GRID);
		
}
/* prints the grid */
void print_grid(char GRID[][COLS]){

	for(unsigned i = 0; i<ROWS; i++){
			printf("\n"); 
		for(unsigned j = 0; j<COLS; j++){
			printf("%c", get_state(GRID,i,j)); 
		}
	}
	printf("\n"); 
}

char get_state(char GRID[][COLS],unsigned x,unsigned y){
	return GRID[x][y];
}

void set_grid(char GRID[ROWS][COLS],char STATE){
	for(unsigned i=0; i<ROWS; i++){
		for(unsigned j=0; j<COLS; j++){
			set_cell(GRID,i,j,STATE);
		}
	}	
}
void set_cell(char GRID [][COLS],unsigned x,unsigned y,char STATE){
	GRID[x][y] = STATE;

}	

void clear(void){
	printf("\033\[H\033[2J\033[3J"); 

}
