# EN111 - Projet Microcontrôleurs PICs 

## Télécharger l'archive

Appuyer sur 
<a class="bg-green-light mb-2">  **↓ Code** </a>
puis **Download ZIP**


## Organisation du répertoire
Extraire l'archive sur la session dans **Documents**.

Il y a 3 dossiers principaux :
* **doc** : Contient les documents nécessaires pour le projet : sujet, datasheet du PIC16F877A, datasheets de la carte et de l'afficheur.
* **src** : Contient les fichiers sources à utiliser (déjà importés dans le projet).
* **work** : Le dossier dans lequel se situe le projet MPLABX, déjà configuré.

## Attentes
Un rapport est à rendre à l'issue des séances. 
Vous devez être en capacité d'expliquer n'importe quelle valeur que vous avez mise dans les registres et ce qui a motivé votre choix. Pensez donc à prendre des notes, et surtout à avoir un code facilement lisible.

Vous rendrez également vos codes sources. La qualité du code est un critère important dans la notation : chaque ligne doit être compréhensible sans avoir à regarder la datasheet.

#### Exemple de ce qu'il **ne faut pas** faire :
`horloge.c`
```c
void timer_init() {
	T1CON = 0x4c;
}
```
La notation est compacte mais on ne comprend rien à ce qu'il se passe... 
Sans la datasheet sous les yeux et un effort de compréhension (avec risque d'erreur), impossible de savoir à quelle configuration correspond cette valeur. 

Dans le milieu professionnel, les codes sont écrits par plusieurs personnes et doivent pouvoir être repris par n'importe qui dans le futur. Il donc est impensable d'utiliser cette notation...

#### Exemple de notation bien plus lisible :
`horloge.h`
```c
#define T1_PRESCALER_DIV8 0b11
#define T1_INTERNAL_CLOCK 0b0
#define T1_ENABLED 0b1
```
`horloge.c`
```c
void timer_init() {
	T1CONbits.T1CKPS = T1_PRESCALER_DIV8; // Division par 8 : 2 Hz / 8 -> 0.250 Hz
	T1CONbits.TMR1CS = T1_INTERNAL_CLOCK; // Horloge interne car...
	T1CONbits.TMR1ON = T1_ENABLED;
}
```
Cette notation demande un effort supplémentaire lors de l'écriture du programme mais rendra le débuggage et la modification tellement plus facile. Ici, même sans la datasheet, on comprend ce qu'il se passe.

De plus, les commentaires sont un bon moyen de se rappeler pourquoi on a fait tel ou tel choix.
