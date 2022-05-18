
/****************************************
            AFFICHEUR LCD 
          sur carte PICDEM2+
*****************************************

            Library LCD
  
****************************************/

#include "lib_LCD.h"

/************************************************************************
                                ETAPE 1
 Simplification des acces 
************************************************************************/

// voir dans "Header Files" => lib_LCD.h


/************************************************************************
                                ETAPE 2
 Developpement de fonctions d'envoi de n'importe quelle instruction
************************************************************************/

// Envoi d'une instruction au format 4 bits (initialisation) vers le module LCD
void lcd_write_instr_4bits(unsigned char rs, unsigned char rw, unsigned char data_4bits) {
    
}

// Envoi d'une instruction au format 8 bits vers le module LCD
void lcd_write_instr_8bits(unsigned char rs, unsigned char rw, unsigned char data_8bits) {
    
}

// Attend que la commande precedente ait ete traitee
void lcd_busy() {
    
}


/************************************************************************
                                ETAPE 3
 Developpement des fonctions correspondant aux differentes instructions
************************************************************************/

// voir DS_Afficheurs_Sunplus.pdf p5, p6 et p7

// Effacement de l'ecran
void lcd_clear() {
    
}

// Retour du curseur a l'origine
void lcd_home() {
    
}

// Direction du curseur et decalage pendant l'ecriture
void lcd_entry_mode_set(unsigned char inc_dec, unsigned char shift) {
    
}

// Ecran ON/OFF, Curseur ON/OFF, Clignotement ON/OFF
void lcd_display_control(unsigned char display, unsigned char cursor, unsigned char blink) {
    
}

// Deplacement du curseur ou de l'affichage d'un cran
void lcd_cursor_display_shift(unsigned char cursor_display, unsigned char left_right) {
    
}

// Taille des donnees (4 / 8 bits), nombre de lignes, taille des caract�res
void lcd_function_set(unsigned char data_length, unsigned char lines, unsigned char font) {
    
}


/************************************************************************
                                ETAPE 4
 Developpement de la fonction d'initialisation
************************************************************************/

// voir DS_Afficheurs_Sunplus.pdf p10 et p11

// Initialisation generale de l'afficheur
void lcd_init() {
    
}


/************************************************************************
                                ETAPE 5
 Developpement des fonctions utilisateur restantes.
************************************************************************/

// Ecriture d'un caractere sur l'afficheur
void lcd_putch(unsigned char c) {
    
}

// Ecriture d'une chaine de caracteres sur l'afficheur
void lcd_puts(const unsigned char *s) {
    
}

// Deplacement du curseur de <<amount>> crans. 
// <<amount>> negatif = vers la gauche
// <<amount>> positif = vers la droite
void lcd_shift_cursor(signed char amount) {
    
}

// Positionnement du curseur en (x,y) - origine en (1,1)
void lcd_pos(unsigned char pos, unsigned char ligne) {
    
}
