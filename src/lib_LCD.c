
/****************************************
            AFFICHEUR LCD 
          sur carte PICDEM2+
*****************************************

               Lib LCD
  
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

/// \brief Envoi d'une instruction de 4 bits vers le module LCD 
///        (utile pour l'initialisation) 
/// \param rs selectionne le registre de destination (1 bit)
/// \param rw selectionne s'il s'agit d'une lecture ou d'une ecriture (1 bit)
/// \param data_4bits est la donnee a ecrire (4 bits)
void lcd_write_instr_4bits(uint8_t rs, uint8_t rw, uint8_t data_4bits) {
    
}

/// \brief Envoi d'une instruction de 8 bits vers le module LCD
/// \param rs selectionne le registre de destination (1 bit)
/// \param rw selectionne s'il s'agit d'une lecture ou d'une ecriture (1 bit)
/// \param data_8bits est la donnee a ecrire (8 bits)
void lcd_write_instr_8bits(uint8_t rs, uint8_t rw, uint8_t data_8bits) {
    
}

/// \brief Attente le temps que la commande precedente ait ete traitee
void lcd_busy() {

}


/************************************************************************
                                ETAPE 3
 Developpement des fonctions correspondant aux differentes instructions
************************************************************************/

// voir DS_Afficheurs_Sunplus.pdf p5, p6 et p7
// chaque fonction correspond a une instruction de l'ecran LCD

/// \brief Effacement de l'ecran
void lcd_clear() {
    
}

/// \brief Retour du curseur a l'origine
void lcd_home() {
    
}

/// \brief Direction du curseur et decalage pendant l'ecriture
/// \param inc_dec (1 bit)
/// \param shift (1 bit)
void lcd_entry_mode_set(uint8_t inc_dec, uint8_t shift) {
    
}

/// \brief Ecran ON/OFF, Curseur ON/OFF, Clignotement ON/OFF
/// \param display (1 bit)
/// \param cursor (1 bit)
/// \param blink (1 bit)
void lcd_display_control(uint8_t display, uint8_t cursor, uint8_t blink) {
    
}

/// \brief Deplacement du curseur ou de l'affichage d'un cran a gauche ou a droite
/// \param cursor_display (1 bit)
/// \param left_right (1 bit)
void lcd_cursor_display_shift(uint8_t cursor_display, uint8_t left_right) {
    
}

/// \brief Taille des donnees (4 / 8 bits), nombre de lignes, taille des caracteres
/// \param data_length (1 bit)
/// \param lines (1 bit)
/// \param font (1 bit)
void lcd_function_set(uint8_t data_length, uint8_t lines, uint8_t font) {
    
}


/************************************************************************
                                ETAPE 4
 Developpement de la fonction d'initialisation
************************************************************************/

// voir DS_Afficheurs_Sunplus.pdf p10 et p11

/// \brief Initialisation generale de l'afficheur
void lcd_init() {
    
}


/************************************************************************
                                ETAPE 5
 Developpement des fonctions utilisateur restantes.
************************************************************************/

/// \brief Ecriture d'un caractere sur l'afficheur
/// \param c est le caratere a envoyer
void lcd_putch(char c) {
    
}

/// \brief Ecriture d'une chaine de caracteres sur l'afficheur
/// \param s est la chaine de carateres a envoyer
void lcd_puts(const char *s) {
    
}

/// \brief Deplacement du curseur de "amount" crans. 
/// \param amount est l'offset a appliquer au curseur
///        amount negatif = vers la gauche
///        amount positif = vers la droite
void lcd_shift_cursor(int8_t amount) {
    
}

/// \brief Positionnement du curseur en (x,y). Origine en (1,1)
/// \param pos est la position horizontale
/// \param ligne est la position verticale
void lcd_pos(uint8_t pos, uint8_t ligne) {
    
}
