
/****************************************
            AFFICHEUR LCD 
          sur carte PICDEM2+
*****************************************

            Library LCD
  
****************************************/

#ifndef __LIB_LCD
#define	__LIB_LCD

#include <xc.h>  

/*
On introduira ici tous les symboles et macros utiles qui faciliteront 
la maintenance et la lisibilité du fichier source correspondant
*/

#define RS RD4 // entrée RS reliée à RD4

void lcd_init();
void lcd_busy();
void lcd_write_instr(unsigned char c);
void lcd_putch(unsigned char c);
void lcd_puts(const unsigned char *s);
void lcd_pos(unsigned char ligne, unsigned char pos);
void lcd_clear();
void lcd_home(void);

#endif	/* __LIB_LCD */
