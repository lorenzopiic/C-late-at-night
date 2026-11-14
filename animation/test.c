#include<stdio.h>
#include <unistd.h>
#include<string.h>
#define GRID_ROWS 10
#define GRID_COLS 40
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

void animate(grid_t old, grid_t new){
// Mantiene lo stato del frame precedente prima di aggiornare 'new'
    memcpy(new, old, sizeof(grid_t));

    for (unsigned y = 0; y < GRID_ROWS; y++) {
        for (unsigned x = 0; x < GRID_COLS; x++) {
            if (old[y][x] == DEAD) {
                new[y][x] = ALIVE;
                return; // Interrompe entrambi i cicli dopo aver acceso una cella
            }
        }
    }
}

int main(void) {
    grid_t buf1, buf2;
    grid_t *old = &buf1;
    grid_t *new = &buf2;
    grid_t *temp = NULL;

    init_grid(*new, DEAD);
    init_grid(*old, DEAD);
    display_grid(*new);

    while (1) {
        animate(*old, *new);
        display_grid(*new);

        temp = old;
        old = new;
        new = temp;
        sleep(1); 
    }

    return 0;
}
