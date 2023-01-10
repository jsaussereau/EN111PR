
/****************************************
            AFFICHEUR LCD 
          sur carte PICDEM2+
*****************************************

              Lib Timer
  
****************************************/

#ifndef __HORLOGE
#define	__HORLOGE

#include <xc.h>  
#include <stdint.h>  

/*
On introduira ici des definitions pour toutes les valeurs des champs
associes au Timer 1. 
Cela simplifira beaucoup son parametrage et augmentera la lisibilite du code
*/

//T1CONbits.T1CKPS :
#define T1_PRESCALER_DIV8 0b11
#define T1_PRESCALER_DIV4 0b10
///...
///...

//T1CONbits.T1OSCEN :
///...
///...

//T1CONbits... :
///...

void timer_init();

#endif	/* __HORLOGE */
