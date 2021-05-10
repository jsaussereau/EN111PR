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

## Cahier des charges
### Objectifs principaux :
- Faire clignoter une des LED à la fréquence 0.5 Hz (1 changement d'état toutes les secondes) à partir d'**interrutpions** sur le Timer1. Cette fonctionnalité doit être maintenue même après le développement des étapes suivantes.   
([Aide](#aide_led))
- Développer une bibliothèque pour l'afficheur LCD (`lib_LCD.h` et `lib_LCD.c`)` proposant à l'utilisateur au minimum les fonctionnalités suivantes :
	- `lcd_init` : Initialisation générale de l'afficheur en mode 4 bits
	- `lcd_putch` : Ecriture d'un caractère sur l'afficheur
	- `lcd_puts` : Ecriture d'une chaîne de caractères sur l'afficheur
	- `lcd_pos` : Positionnement du curseur en (x,y) - origine en (1,1)
	- `lcd_home` : Cursor home : positionnement du curseur (1,1)
	- `lcd_clear` : Effacement de l'écran et cursor home  
	([Aide](#aide_lib_lcd))
- Affichage sur l'écran LCD d'une horloge au format `HH:MM:SS` qui s'incrémente à chaque seconde (via le Timer1).  
([Aide](#aide_horloge))
- Pouvoir configurer l'horloge à l'aide des boutons poussoir S2 et S3 :
	- Un appui prolongé d'au moins 2 s sur S2 fera clignoter les heures, celles-ci s'incrémenteront à chaque appui sur S3, ou automatiquement (f ≈ 5 Hz) en cas d'appui maintenu au-delà de 2 s.
	- Un nouvel appui sur S2 permettra un réglage des secondes selon la même procédure.
	- Éventuellement, un nouvel appui sur S2 permettra un réglage des minutes selon la même procédure.
	- Un dernier appui sur S2 fera quitter le mode "réglage".  
	([Aide](#aide_conf_horloge))

### Objectifs Secondaires :
##### (Au choix et si le temps le permet)
- Ajout de charactères personnalisés sur l'afficheur.
- Récupération via le protocole I²C de la température du capteur TC74.
- Ajout d'une alarme quand l'horloge atteint une heure configurée, avec une sonnerie ou une mélodie sur le buzzer P1.
- Toute autre idée que vous aimeriez développer avec les éléments à disposition sur la carte.

## Aide
<h3 id="aide_led"> 1. Clignotement de la LED à la fréquence 0.5 Hz </h3>

#### 1.1 Configuration du timer

Pour générer une horloge de fréquence 0.5 Hz précisément, on utilise le Timer 1. La section Timer1 de la datasheet du microcontrôleur *DS_PIC16F877A* détaille son fonctionnement et les registres à utiliser pour le configurer.

Il est possible de configurer le timer 1 sur une horloge externe. La carte PICDEM2+ intègre un quartz de 32,768 kHz relié aux broches OSO (RC0) et OSI (RC1) du PIC. Ceci permet une incrémentation du TIMER1 et un débordement de celui-ci toutes les 2 secondes (216/32768) très précisément.

Pour pouvoir faire une action à chaque débordement, il faut activer les interruptions sur les débordements du Timer1.

***Note*** : Le tableau à la page 60 de la datasheet *DS_PIC16F877A* met en évidence tous les champs liés au Timer1. Pour être sûr de l'avoir bien configuré, il faut être sûr de comprendre quel est le rôle de chacun de ces champs et être sûr d'avoir assigné la bonne valeur aux champs qui en ont besoin.

#### 1.2 Configuration du module CCP

Pour avoir un débordement toutes les secondes (et pas toutes les 2 secondes), on peut utiliser un module de comparaison CCP.  
Le but est ici d'utiliser ce module pour générer une interruption à chaque fois que la valeur du compteur du Timer1 est à mi-parcours (entre deux interruptions de débordement). Il faut donc également activer les interruptions sur module CCP.  
Les modules CCP peuvent être utilisés dans différentes configurations, il faut choisir la plus adaptée au besoin.  
Il faut aussi penser à bien mettre une valeur à comparer

***Note*** : Le tableau à la page 68 de la datasheet *DS_PIC16F877A* met en évidence tous les champs liés au module CCP. Pour être sûr de l'avoir bien configuré, il faut être sûr de comprendre quel est le rôle de chacun de ces champs et être sûr d'avoir assigné la bonne valeur aux champs qui en ont besoin.



<h3 id="aide_lib_lcd"> 2. Développement de la bibliothèque pour l'afficheur LCD </h3>

#### Documentation
Pour développer la bibliothèque LCD, 3 documents seront utiles :
- *DS_PICDEM_2_Plus_Users_Guide* : Datasheet de la carte de développement. Le schéma électrique page 19 permet de comprendre les interconnexions entre le microcontrôleur et le module LCD.
- *DS_LCD_Module_162F* : Datasheet de l'écran. Les pages 3 et 4 montrent les chronogrammes à respecter pendant une lecture/écriture.
- *DS_Afficheurs_Sunplus* : Datasheet du module LCD complet. On y trouve une description de toutes les fonctions proposées par le module. Toutes les instructions y sont détaillées.

#### <ins>Étape 1</ins>  : Simplification des accès
Pour envoyer des instructions, il faut être capable d'accéder individuellement aux différents champs du port D qui contrôlent l'écran LCD. Il est notamment nécessaire d'écrire sur les 4 bits de données sans modifier les autres bits du port.

Avant toute chose, il est donc vivement recommandé de simplifier les lectures/écritures sur les différents champs du module LCD.  
Deux principales méthodes sont présentées ici. Prenez le temps de prendre connaissance des deux, et faite votre choix !

##### Méthode 1 : Masquage
Le plus simple est de définir à l'aide de `#define` les alias des différents bits, pour un accès plus clair.  
Les accès au bits se font ainsi simplement par leurs noms. Pour écrire sur plusieurs bits, il faut effectuer un [masquage](https://dept-info.labri.fr/ENSEIGNEMENT/programmation1/cours/CM_9___Manipulation_binaire.pdf).

***Note*** : On a ici la chance de pouvoir accéder aux bits individuellement de base. Sinon, il aurait fallu utiliser le masquage dans tous les cas.

***Exemple*** :

`lib_LCD.h`
```c
#define LCD PORTD
#define E RD6

#define E_ENABLED 0b1
#define E_DISABLED 0b0
```

`lib_LCD.c`
```c
void lcd_write_instr_8bits(unsigned char rs, unsigned char rw, unsigned char data) {
    // [...]
    RS = rs;
    RW = rw;
    
    LCD &= 0xf0; // mise à 0 des 4 bits de poids faible  
    LCD |= (data_MSB & 0x0f); // mise à 0 des 4 bits de poids faible  
    
    E = E_ENABLED;
    // [...]
}
```
##### Méthode 2 : Champs de bits (bitfields)
Une autre méthode, plus pratique à utiliser, utilise le même principe d'union de champs de bits que dans le fichier d'include `pic16f877a.h`. Il suffit de créer un nouveau type sur le modèle de celui associé au PORTD.
Comme dans le fichier d'include, on peut donner plusieurs définitions aux champs de bits grâce aux unions. On peut par exemple nommer les bits un à un, et, plus intéressant, définir des champs. Cela rend les lectures/écritures très simples.  

***Note*** : L'ordre des bits dans les champs de bits n'est hélas pas normé, il dépend du compilateur et de l'architecture. Sur PIC, avec le compilateur XC8, le bit de poids faible (LSB) est en premier et le bit de poids fort (MSB) est en dernier.

***Exemple*** :

`lib_LCD.h`
```c
typedef union {
	// définitions des bits individuellement :
	struct { 
		unsigned DB4             :1;  // bit 0
		unsigned DB5             :1;  // bit 1
		unsigned DB6             :1;  // bit 2
		unsigned DB7             :1;  // bit 3
		unsigned RS              :1;  // bit 4
		unsigned RW              :1;  // bit 5
		unsigned E               :1;  // bit 6
		unsigned POWER           :1;  // bit 7
	}; 
    
	// définition des champs :
	struct {
		unsigned DB              :4;  // bits 0 à 3 : données
		unsigned OPERATION       :2;  // bits 4 et 5 : RS et RW : définissent le type d'opération
		unsigned                 :2;  // E et POWER déjà définis, facultatif
	};
    
} LCDbits_t;

extern volatile LCDbits_t LCDbits @ 0x008; // Définition de "LCDbits" de type LCDbits_t, avec l'adresse du PORTD
```

`lib_LCD.c`
```c
void lcd_write_instr_8bits(unsigned char operation, unsigned char data) {
    // [...]
    LCDbits.OPERATION = operation; 
    LCDbits.DB = data_MSB;
    LCDbits.E = ON;
    // [...]
}
```

#### <ins>Étape 2</ins>  : Développement d'une fonction d'envoi de n'importe quelle instruction

Maintenant que les accès aux différents champs associés au module LCD sont plus simples à utiliser, la prochaine étape est de développer une fonction qui pourra être utilisée par toutes les fonctions qui ont besoin d'envoyer une instruction au module.

Comme on peut le voir dans la datasheet de la carte PICDEM2+, le bus de données est de 4 bits. Pourtant on voit dans la datasheet du module LCD *DS_Afficheurs_Sunplus* qu'une instruction est constituée de 8 bits de données et 3 bits de contrôle.  
Il faut donc que la fonction développée soit capable d'envoyer 8 bits de données sur un bus de 4 bits. Pour cela, pas le choix, il faut envoyer les données en 2 fois.  

Avant d'envoyer une instruction, pour éviter qu'une instruction ne soit pas exécutée, il faut s'assurer que le module n'est pas occupé. Il est possible de lire le bit 'busy' pour cela, mais dans un souci de simplicité, dans un premier temps, on peut se contenter d'une temporisation.

Dans tous les cas, pour envoyer des données, il faut respecter les chronogrammes sur les pages 3 et 4 de la datasheet *DS_LCD_Module_162F*. 


#### <ins>Étape 3</ins> : Développement des fonctions correspondant aux différentes instructions
La page 7 de la datasheet du module LCD *DS_Afficheurs_Sunplus* liste toutes les instructions proposées par le module. Avant de chercher à développer la fonction d'initialisation, il est préférable de développer des fonctions correspondant à ces instructions. Notamment les suivantes :

- `Clear Display `
- `Return Home ` 
- `Entry Mode Set `
- `Display ON/OFF Control `
- `Cursor or Display Shift `
- `Function Set `

Certaines prennent des arguments, d'autres non. Voici une proposition de prototypes pour ces fonctions :
`lib_LCD.h`
```c
void lcd_clear();
void lcd_home();
void lcd_entry_mode_set(unsigned char inc_dec, unsigned char shift);
void lcd_display_control(unsigned char display, unsigned char cursor, unsigned char blink);
void lcd_shift_cursor(signed char amount);
void lcd_function_set(unsigned char data_length, unsigned char lines, unsigned char font);
```
Pour générer la donnée de l'instruction avec les bons arguments, il sera probablement nécessaire d'effectuer des [masquages](https://dept-info.labri.fr/ENSEIGNEMENT/programmation1/cours/CM_9___Manipulation_binaire.pdf).


#### <ins>Étape 4</ins>  : Développement de la fonction d'initialisation
La page 11 de la datasheet du module LCD *DS_Afficheurs_Sunplus* détaille la procédure d'initialisation du module.
Plutôt que d'envoyer les instructions avec les données brutes dans cette procédure, il est préférable de comprendre ce que fait chacune d'entre elles. Ainsi, on remarque que toute la procédure d'initialisation peut être réalisée en effectuant des appels aux fonctions définies plus haut.

***Note*** : Ne pas oublier d'activer l'alimentation du module (*cf.* datasheet de la carte PICDEM2+).

#### <ins>Étape 5</ins>  : Développement des fonctions utilisateur restantes.

Il ne manque alors plus qu'à réaliser les fonctions pour écrire un caractère `lcd_putch`, puis une pour écrire une chaîne de caractères `lcd_puts` et une fonction de positionnement sur l'écran `lcd_pos`.

<h3 id="aide_horloge"> 3. Affichage de l'horloge sur l'écran LCD </h3>

Pour formatter l'horloge dans une chaîne de caractère, le plus simple est certainement d'utiliser la fonction `sprintf` de la bibliothèque `stdio`.

<h3 id="aide_conf_horloge"> 4. Développement de la fonctionnalité de configuration de l'horloge </h3>

Pour cette partie, il est nécessaire de développer une machine d'état, avec une filtre anti-rebond (à base de temporisation active) sur les boutons. 

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


