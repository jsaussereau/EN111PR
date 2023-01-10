
/****************************************
            AFFICHEUR LCD 
          sur carte PICDEM2+
****************************************/

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// LIBRARIES
#include <xc.h>	
#include <stdio.h>	
#include <stdint.h>  

#include "timer.h"
#include "lib_LCD.h"


/// \brief Fonction d'interruption
void interrupt IT() {
    
}

/// \brief Fonction d'initialisation
void init() {
    timer_init();
    lcd_init();
}

/// \brief Fonction principale
void main() { 
    init();
    
    while(1) {

    }
}