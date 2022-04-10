
/****************************************
            AFFICHEUR LCD 
          sur carte PICDEM2+
*****************************************

            Library LCD
  
****************************************/

#include "lib_LCD.h"

/************************************************************************
                                ETAPE 1
 Simplification des accès 
************************************************************************/

// voir dans "Header Files" => lib_LCD.h


/************************************************************************
                                ETAPE 2
 Développement de fonctions d'envoi de n'importe quelle instruction
************************************************************************/

// Envoi d'une instruction au format 4 bits (initialisation) vers le module LCD
void lcd_write_instr_4bits(unsigned char operation, unsigned char c){
    
}

// Envoi d'une instruction au format 8 bits vers le module LCD
void lcd_write_instr_8bits(unsigned char operation, unsigned char c) {
    
}

// Test le bit BF jusqu'à ce que l'afficheur soit prêt
void lcd_busy() {
    
}


/************************************************************************
                                ETAPE 3
 Développement des fonctions correspondant aux différentes instructions
************************************************************************/

// voir DS_Afficheurs_Sunplus.pdf p5, p6 et p7

// Effacement de l'écran
void lcd_clear() {
    
}

// Retour du curseur à l'origine
void lcd_home() {
    
}

// Direction du curseur et décalage pendant l'ecriture
void lcd_entry_mode_set(unsigned char inc_dec, unsigned char shift) {
    
}

// Ecran ON/OFF, Curseur ON/OFF, Clignotement ON/OFF
void lcd_display_control(unsigned char display, unsigned char cursor, unsigned char blink) {
    
}

// Déplacement du curseur
void lcd_shift_cursor(signed char amount) {
    
}

// Taille des données (4 / 8 bits), nombre de lignes, taille des caractères
void lcd_function_set(unsigned char data_length, unsigned char lines, unsigned char font) {
    
}


/************************************************************************
                                ETAPE 4
 Développement de la fonction d'initialisation
************************************************************************/

// voir DS_Afficheurs_Sunplus.pdf p10 et p11

// Initialisation générale de l'afficheur
void lcd_init() {
    
}


/************************************************************************
                                ETAPE 5
 Développement des fonctions utilisateur restantes.
************************************************************************/

// Ecriture d'un caractère sur l'afficheur
void lcd_putch(unsigned char c) {
    
}

// Ecriture d'une chaine de caractères sur l'afficheur
void lcd_puts(const unsigned char *s) {
    
}

// Positionnement du curseur en (x,y) - origine en (1,1)
void lcd_pos(unsigned char ligne, unsigned char pos) {
    
}
