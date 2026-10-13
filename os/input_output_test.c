/*  I/O routine example taken form hamaher's textbook
 *  on computers architecture. 
 *  ALL RIGHTS RESERVED TO THE AUTHORS */
#include <stdio.h>

// Alloco variabili reali in memoria per simulare i registri hardware
volatile char mock_kbd_data = 'A';
volatile char mock_kbd_status = 0x2;  // Bit 1 a 1: dato pronto
volatile char mock_disp_data = 0;
volatile char mock_disp_status = 0x4; // Bit 2 a 1: display pronto

// Faccio puntare le macro agli indirizzi di queste variabili
#define KBD_DATA    (&mock_kbd_data)
#define KBD_STATUS  (&mock_kbd_status)
#define DISP_DATA   (&mock_disp_data)
#define DISP_STATUS (&mock_disp_status)

int main(void){
    char ch;

    while(1){
        // Attende che la "tastiera" sia pronta (bit 1 == 1)
        while((*KBD_STATUS & 0x2) == 0){ ; } 
        ch  = *KBD_DATA;

        // Attende che il "display" sia pronto (bit 2 == 1)
        while((*DISP_STATUS & 0x4) == 0){ ; }
        
        *DISP_DATA = ch;

        // Aggiungiamo un print e un break per non farlo andare in loop infinito nel test
        fprintf(stdout, "Carattere letto e scritto nel registro: %c\n", *DISP_DATA);
        break; 
    }
    return 0;
}
