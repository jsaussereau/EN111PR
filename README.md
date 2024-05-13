# EN111 - Projet Microcontrôleurs PICs 

## Télécharger l'archive

- Exécuter dans un terminal :

```bash
cd ~/Documents/
git clone https://github.com/jsaussereau/EN111PR.git
```

- Le dossier `EN111PR` devrait être apparu sur votre session dans le dossier `Documents`

<details>
<summary>Solution alternative</summary>

- Cliquer [ici](https://github.com/jsaussereau/EN111PR/archive/refs/heads/main.zip) pour télécharger l'archive.
- Extraire l'archive sur la session dans **Documents**.

</details>

## Organisation du répertoire
Il y a 3 dossiers principaux :
* **doc** : Contient les documents nécessaires pour le projet : sujet, datasheet du PIC16F877A, datasheets de la carte et de l'afficheur.
* **src** : Contient les fichiers sources à utiliser (déjà importés dans le projet).
* **work** : Le dossier dans lequel se situe le projet MPLABX, déjà configuré.

# Sommaire
- [Cahier des charges](#cahier-des-charges)
- [Évaluation](#évaluation)
- [Aide](#aide)
	- [1. Get started](#-1-get-started-)
	- [2. Clignotement de la LED à la fréquence 0.5 Hz](#-2-clignotement-de-la-led-à-la-fréquence-05-hz-)
		- [2.1 Choix de la stratégie](#21-choix-de-la-stratégie)
		- [2.2 Développement d'une bibliothèque pour le Timer 1](#22-développement-dune-bibliothèque-pour-le-timer-1)
		- [2.3 Configuration du timer](#23-configuration-du-timer)
		- [2.4 Configuration du module CCP](#24-configuration-du-module-ccp)
  	- [3. Développement de la bibliothèque pour l'afficheur LCD ](#-3-développement-de-la-bibliothèque-pour-lafficheur-lcd-)
		- [Étape 1 : Simplification des accès](#documentation)
		- [Étape 2 : Développement d'une fonction d'envoi de n'importe quelle commande](#étape-2--développement-dune-fonction-denvoi-de-nimporte-quelle-commande)
		- [Étape 3 : Développement des fonctions correspondant aux différentes commandes](#étape-3--développement-des-fonctions-correspondant-aux-différentes-commandes)
  		- [Étape 4 : Développement de la fonction d'initialisation](#étape-4--développement-de-la-fonction-dinitialisation)
		- [Étape 5 : Développement des fonctions utilisateur restantes](#étape-5--développement-des-fonctions-utilisateur-restantes)
  	- [4. Affichage de l'horloge sur l'écran LCD ](#-4-affichage-de-lhorloge-sur-lécran-lcd-)
  	- [5. Développement de la fonctionnalité de configuration de l'horloge](#-5-développement-de-la-fonctionnalité-de-configuration-de-lhorloge-)

# Cahier des charges
## Objectifs principaux
- Faire clignoter une des LED à la fréquence 0.5 Hz (1 changement d'état toutes les secondes) à partir d'**interruptions** sur le Timer1. Cette fonctionnalité doit être maintenue même après le développement des étapes suivantes. ([Aide](#aide_led))

- Développer une bibliothèque pour l'afficheur LCD (`lib_LCD.h` et `lib_LCD.c`) proposant à l'utilisateur au minimum les fonctionnalités suivantes ([Aide](#aide_lib_lcd)) :
	- `lcd_init` : Initialisation générale de l'afficheur en mode 4 bits
	- `lcd_putch` : Ecriture d'un caractère sur l'afficheur
	- `lcd_puts` : Ecriture d'une chaîne de caractères sur l'afficheur
	- `lcd_pos` : Positionnement du curseur en (x,y) - origine en (1,1)
	- `lcd_home` : Cursor home : positionnement du curseur (1,1)
	- `lcd_clear` : Effacement de l'écran et cursor home  
	
- Affichage sur l'écran LCD d'une horloge au format `HH:MM:SS` qui s'incrémente à chaque seconde (via le Timer1). ([Aide](#aide_horloge))
- Pouvoir configurer l'horloge à l'aide des boutons poussoir S2 et S3 ([Aide](#aide_conf_horloge)) :
	- Un appui prolongé d'au moins 2 s sur S2 fera clignoter les heures, celles-ci s'incrémenteront à chaque appui sur S3, ou automatiquement (f ≈ 5 Hz) en cas d'appui maintenu au-delà de 2 s.
	- Un nouvel appui sur S2 permettra un réglage des minutes selon la même procédure.
	- Éventuellement, un nouvel appui sur S2 permettra un réglage des secondes selon la même procédure.
	- Un dernier appui sur S2 fera quitter le mode "réglage".  

## Objectifs Secondaires
#### (Au choix et si le temps le permet)
- Utilisation du potentiomètre pour régler les heures/minutes/secondes.
- Ajout de charactères personnalisés sur l'afficheur.
- Récupération via le protocole I²C de la température du capteur TC74.
- Ajout d'une alarme quand l'horloge atteint une heure configurée, avec une sonnerie ou une mélodie sur le buzzer P1.
- Utilisation de l'écran comme un afficheur à décalage (comme dans les bus/trams).
- Toute autre idée que vous aimeriez développer avec les éléments à disposition sur la carte.


# Évaluation
Le rendu se fait par mail avec comme objet `[EN111] NOM1 NOM2`, avant le **26/05/2024, 23:59**, à l'adresse suivante :
- Groupes D, E et G : [jsaussereau@bordeaux-inp.fr](mailto:jsaussereau@bordeaux-inp.fr?subject=[EN111]%20NOM1%20NOM2)
- Groupe F : [valery.lebret@enseirb-matmeca.fr](mailto:Valery.Lebret@enseirb-matmeca.fr?subject=[EN111]%20NOM1%20NOM2)

Sont à rendre:
- Le code source (tous les fichiers `.c` et `.h` dans le dossier `src`) compressés dans une archive `.zip`
- Un rapport par binôme, d'environ 10 pages (hors annexe), au format `.pdf`, contenant :
	- Une introduction du contexte en résumant le cahier des charges et en présentant les ressources utiles de la carte.
	- Une explication de la conception de chacune des parties du projet :
		- Génération de l'interruption toutes les secondes
			- Configuration du timer
			- Configuration du module CCP
		- Développement de la bibliothèque pour l'afficheur LCD 
			- Simplification des accès
			- Développement d'une fonction d'envoi de n'importe quelle commande
			- Développement des fonctions correspondants aux différentes commandes
			- Développement de la fonction d'initialisation
			- Développement des fonctions utilisateur restantes
		- Affichage de l'horloge sur l'écran LCD 
		- Développement de la fonctionnalité de configuration de l'horloge
		- Eventuelle(s) partie(s) bonus
	- Une conclusion sur les enseignements que l'on peut tirer de ce projet. Tant d'un point de vue technique que méthodologique.

Compléments sur le rapport : 
- Dès que l'on utilise **directement** des registres du microcontrôleur, expliquer : 
	- Quels sont les registres utilisés ?
	- Quelles sont les valeurs qui ont été mises dans ces registres ?
	- Quelles actions ont ces valeurs techniquement ? 
	- Quelles sont les fonctionnalités recherchées qui justifient ces valeurs ?
- Pour l'explication des fonctions, il ne s'agit pas de juste expliquer ce qu'elles font fonctionnemment (ça c'est le cahier des charges, que l'on a déjà). Il s'agit d'expliquer **comment elles ont été implémentées** (opérations utilisées, logique, optimisations, ...) et pourquoi elles sont implémentées comme ça et pas autrement.
- De manière générale, dès que des choix on été fait, comme des choix de configuration de module, ou des choix d'implémentation, expliquer ces choix, **même quand plusieurs configurations correspondaient aux exigences**. 
- La description de `lcd_write_instr_4bits`, `lcd_write_instr_8bits` et `lcd_init` pourra être accompagnée d'organigrammes expliquant le déroulement de ces fonctions.
- La description de la partie de configuration de l'horloge pourra être accompagnée d'un diagramme de la machine d'état.
- Bien faire apparaître, et justifier, ce qui est effectué par interruption et ce qui ne l'est pas.
- Même si vous n'avez pas réalisé une partie, vous pouvez l'indiquer et expliquer comment vous auriez fait.
- Bon courage ;)

> [!IMPORTANT]  
> 1. Le code source doit compiler !
> 2. La note qui vous sera attribuée sur ce module tient également compte du travail observé durant les séances de TP + projet et des éventuelles absences non justifiées.
> 3. Le [plagiat](https://nuxeo.ipb.fr/nuxeo/nxfile/default/fa82b9dd-f22c-4d41-8ace-5a5e7fa7e60d/blobholder:0/Charte-anti-plagiat.pdf) constitue une fraude dont les conséquences peuvent être graves :
attribution d’une note de zéro au travail incriminé, exclusion de l’établissement, exclusion définitive de tout établissement d’enseignement supérieur français.  
En matière de propriété intellectuelle, le plagiat constitue un délit.


# Aide
<h2 id="aide_get_started"> 1. Get started 🏁</h2>

Un projet déjà configuré est disponible dans `work`.

Plusieurs fichiers sont déjà créés dans le dossier `src` (voir "Header Files" et "Source Files" dans MPLABX) :
- `main.c` : Fichier principal. C'est ici que se trouve la fonction main et la fonction d'interruption.
- `timer.c` et `timer.h` : Fichiers où développer [la configuration du timer](#aide_led), [la mise en forme](#aide_horloge) et [la configuration](#aide_conf_horloge) de l'horloge.
- `lib_LCD.c` et `lib_LCD.h` : Fichiers où développer [la bibliothèque LCD](#aide_lib_lcd).
	
À chaque étape, pensez à faire valider votre travail avant de passer aux étapes suivantes.

<h2 id="aide_led"> 2. Clignotement de la LED à la fréquence 0.5 Hz </h2>

### 2.1 Choix de la stratégie

Nous avons ici une exigence de précision, alors comme en TP, c'est la stratégie par interruption qui s'impose face à l'attente active.

Pour génerer les interruptions qui ferront clignoter la LED, nous avons le choix entre les 3 timers du microcontrôleur. 

La datasheet *DS_PIC16F877A* nous apprend qu'il est possible de configurer le Timer 1 sur une horloge externe. 
Le schéma à la page 19 de la datasheet de la carte PICDEM2+ *DS_PICDEM_2_Plus_Users_Guide* montre qu'il y a un quartz (Y3) de 32.768 kHz ($2^{15}$ Hz) relié aux broches OSO (RC0) et OSI (RC1) du PIC. 

> [!TIP]
> L'incrémentation d'un compteur 16 bits comme le Timer 1 à une fréquence de $2^{15}$ Hz permettrait un débordement de celui-ci toutes les 2 secondes ($2^{16} / 2^{15}$) très précisément. 
> Le Timer 1 est donc un bon candidat pour cette application.

### 2.2 Développement d'une bibliothèque pour le Timer 1

La section "Timer1" de la datasheet du microcontrôleur *DS_PIC16F877A* détaille le fonctionnement de ce timer, avec notamment un schéma de son fonctionnement et un tableau regroupant les registres à utiliser pour le configurer.

On cherche tout d'abord à définir à l'aide de `#define` dans `timer.h` (Header Files) les différentes valeurs des champs associés au Timer 1. Cela permettra d'avoir juste à choisir la bonne constante lors de la configuration du timer.

En plus de faciliter l'étape de configuration, l'objectif est que par la suite chaque ligne de code soit compréhensible sans avoir à regarder la datasheet.

### Exemple de ce qu'il **ne faut PAS** faire :
`timer.c`
```c
void timer_init() {
	T1CON = 0x4c;
}
```
La notation est compacte mais on ne comprend rien à ce qu'il se passe... 
Sans la datasheet sous les yeux et un effort de compréhension (avec risque d'erreur), impossible de savoir à quelle configuration correspond cette valeur. 

> [!NOTE]  
> Dans le milieu professionnel, les codes sont écrits par plusieurs personnes et doivent pouvoir être repris par n'importe qui dans le futur. Il donc est impensable de proposer un tel code en entreprise.

### Exemple de notation bien plus lisible :
`timer.h`
```c
//T1CONbits.T1CKPS :
#define T1_PRESCALER_DIV8 0b11
#define T1_PRESCALER_DIV4 0b10
#define T1_PRESCALER_DIV2 0b01
#define T1_PRESCALER_DIV1 0b00

//...
```
`timer.c`
```c
void timer_init() {
	T1CONbits.T1CKPS = T1_PRESCALER_DIV8; // Division par 8 car ...
	T1CONbits.T1OSCEN = ...;
}
```

L'exemple ci dessus met en oeuvre plusieurs bonnes pratiques :
- L'initialisation des champs indépendaments les uns des autres plutôt que d'écrire sur tout le registre : le code est plus simple à comprendre et à modifier.
- L'utilisation de constantes avec des noms signifiants : permet de comprendre facilement quel est le rôle de la valeur qui a été mise dans le champs.

> [!NOTE]  
> Cette notation demande un effort supplémentaire lors de l'écriture du programme mais rendra le débuggage et la modification tellement plus facile. Ici, même sans la datasheet, on comprend ce qu'il se passe.
> De plus, les commentaires sont un bon moyen de se rappeler pourquoi on a fait tel ou tel choix.

### 2.3 Configuration du timer

Il ne reste plus qu'à utiliser ces définitions pour l'initialisation du timer dans la fonction `timer_init` (`timer.c`).

L'objectif étant dans un premier temps de le configurer pour qu'il déclenche une iterruption toutes les deux secondes.

La section `TIMER1 MODULE` de la datasheet *DS_PIC16F877A* décrit le fonctionnement du Timer1. Le schéma page 58 aide à comprendre son fonctionnement et le rôle de chaque champ de configuration.
> [!TIP]  
> Le tableau à la page 60 de la datasheet *DS_PIC16F877A* met en évidence tous les champs liés au Timer1. Pour être sûr de l'avoir bien configuré, il faut être sûr de comprendre quel est le rôle de chacun de ces champs et être sûr d'avoir assigné la bonne valeur aux champs qui en ont besoin.

Une fois le timer configuré, on veut déclencher une interruption à chaque débordement. Il faut aussi configurer notre fonction d'interruption pour faire changer d'état la LED à chaque interruption.
> [!TIP]  
> Le schéma page 153 permet de visualiser les conditions à remplir pour qu'une interruption se déclenche. 

> [!NOTE]  
> Une fois les interruptions configurées, on peut déjà essayer sur la carte pour voir si on a bien la LED qui change d'état toutes les 2 secondes.

### 2.4 Configuration du module CCP

Pour avoir un débordement toutes les secondes (et plus toutes les 2 secondes), on peut utiliser un module de comparaison CCP.  
Le but est ici d'utiliser ce module pour générer une interruption à chaque fois que la valeur du compteur du Timer1 est à mi-parcours (entre deux interruptions de débordement). Il faut donc également activer les interruptions sur le module CCP.  

Les modules CCP peuvent être utilisés dans différentes configurations, il faut choisir la plus adaptée au besoin.  
Il faut aussi penser à bien mettre une valeur à comparer.

Comme pour la configuration du timer, la configuration du module CCP se fera a l'aide de constantes définies au préalable.

> [!TIP]  
> Le tableau à la page 68 de la datasheet *DS_PIC16F877A* met en évidence tous les champs liés au module CCP. Pour être sûr de l'avoir bien configuré, il faut être sûr de comprendre quel est le rôle de chacun de ces champs et être sûr d'avoir assigné la bonne valeur aux champs qui en ont besoin.


<h2 id="aide_lib_lcd"> 3. Développement de la bibliothèque pour l'afficheur LCD </h2>

### Documentation
Pour développer la bibliothèque LCD, 2 documents seront utiles :
- *DS_PICDEM_2_Plus_Users_Guide* : Datasheet de la carte de développement. Le schéma électrique page 19 permet de comprendre les interconnexions entre le microcontrôleur et le module LCD.
- *DS_Afficheurs_Sunplus* : Datasheet du module LCD. On y trouve la description des entrées/sorties du module (page 4), ansi que les chronogrammes à respecter pour ces signaux (pages 23-24). Toutes les commandes proposées par le module y sont détaillées (pages 5-7). Enfin, la datasheet explicite la procédure d'initialisation du module (pages 10-11). 

### <ins>Étape 1</ins> : Simplification des accès

Pour envoyer des instructions, il faut être capable d'accéder individuellement aux différents champs du port D qui contrôlent l'écran LCD. Il est notamment nécessaire d'écrire sur les 4 bits de données sans modifier les autres bits du port.

> [!TIP]
> Avant toute chose, il est donc vivement recommandé de simplifier les lectures/écritures sur les différents champs du module LCD.  
> Deux approches sont présentées ici.

#### Méthode 1 : Masquage
<details>
<summary>Cliquer ici pour étendre</summary>

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
void lcd_write_instr_8bits(uint8_t rs, uint8_t rw, uint8_t data) {
    // [...]
    RS = rs;
    RW = rw;
    
    LCD &= 0xf0; // mise à 0 des 4 bits de poids faible  
    LCD |= (data_MSB & 0x0f); // application des 4 MSB de la donnée sur les 4 LSB de LCD 
    
    E = E_ENABLED;
    // [...]
}
```
</details>

#### Méthode 2 : Champs de bits (bitfields)
Une autre méthode, plus pratique à utiliser, se base sur le même principe d'[union](https://www.tutorialspoint.com/cprogramming/c_unions.htm) de [bitfields](https://www.tutorialspoint.com/cprogramming/c_bit_fields.htm) que dans le fichier d'include `pic16f877a.h`. Il suffit de créer un nouveau type sur le modèle de celui associé au PORTD.

Comme dans le fichier d'include, on peut donner plusieurs définitions aux [bitfields](https://www.tutorialspoint.com/cprogramming/c_bit_fields.htm) grâce aux [unions](https://www.tutorialspoint.com/cprogramming/c_unions.htm). On peut par exemple nommer les bits un à un, et, plus intéressant, définir des champs. Cela rend les lectures/écritures très simples.  

> [!NOTE]  
> L'ordre des bits dans les champs de bits n'est hélas pas normé, il dépend du compilateur et de l'architecture. Sur PIC, avec le compilateur XC8, le bit de poids faible (LSB) est en premier et le bit de poids fort (MSB) est en dernier.

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

Grâce au mot-clé [typedef](https://www.tutorialspoint.com/cprogramming/c_typedef.htm), on a ici défini notre propre type `LCDbits_t`, qui est une [union](https://www.tutorialspoint.com/cprogramming/c_unions.htm) de [bitfields](https://www.tutorialspoint.com/cprogramming/c_bit_fields.htm), représentant les champs de l'écran LCD, connectés au port D. 

Pour utiliser ce type sur le port D, on déclare donc une variable `LCDbits` de type `LCDbits_t` à l'adresse `0x008` qui est l'adresse du port D. C'est très exactement de la même manière que `PORTDbits` est défini dans `pic16f877a.h`.

Grâce aux deux définitions spécifiées du port, on a alors plusieurs façons d'accéder à nos signaux :
- On peut accéder au bits individuellement, comme DB5, RS, RW pu E par exemple. 
- On peut accéder à des champs entiers comme DB (DB7-DB4) ou OPERATION (RS,RW)

Exemple d'utilisation :
`lib_LCD.c`
```c
void lcd_write_instr_8bits(uint8_t rs, uint8_t rw, uint8_t data_8bits) {
    // [...]
    LCDbits.RS = rs; 
    // [...]
    LCDbits.DB = data_MSB;
    LCDbits.E = E_ENABLED;
    // [...]
}
```

### <ins>Étape 2</ins> : Développement d'une fonction d'envoi de n'importe quelle commande

Maintenant que les accès aux différents champs associés au module LCD sont plus simples à utiliser, la prochaine étape est de développer des fonctions qui pourront être utilisées par toutes les fonctions qui ont besoin d'envoyer une commande au module.

La datasheet du module LCD *DS_Afficheurs_Sunplus* nous apprend que l'on peut câbler ce module LCD à un microcontrôleur sur 8 bits (DB7-DB0) ou 4 bits (DB7-DB4)

> [!TIP]
> Le schéma à la page 19 de la datasheet de la carte PICDEM2+ *DS_PICDEM_2_Plus_Users_Guide* montre comment le module LCD est relié au microcontrôleur. On voit que le bus de données est ici utilisé sur 4 bits.

> [!NOTE]
> Cela n'a pas d'impact sur la taille des commandes que l'on peut envoyer. En effet, même lorsqu'il est cablé sur 4 bits, l'afficheur LCD peut recevoir des commandes avec des données de 4 bits ou bien 8 bits. C'est le protocole de communication qui change.

On va donc développer des fonctions pour ces deux cas :
- `lcd_write_instr_4bits` : envoi d'une commande avec 4 bits de données (pour les premières commandes de l'initialisation)
- `lcd_write_instr_8bits` : envoi d'une commande avec 8 bits de données (pour toutes les commandes classiques)

> [!IMPORTANT]
> Dans les deux cas, pour envoyer ces données, il faut veiller à respecter les chronogrammes à la page 24 de la datasheet *DS_Afficheurs_Sunplus*. 

#### ➤ Commandes 4 bits :
Dans la datasheet du module LCD *DS_Afficheurs_Sunplus* on voit que pour la partie d'initialisation, il y a des commandes avec une données de 4 bits et 2 bits de contrôle.

C'est le cas le plus simple : on écrit 4 bits de données sur un bus de 4 bits.

```c
void lcd_write_instr_4bits(uint8_t rs, uint8_t rw, uint8_t data_4bits) {
    // on assigne les signaux de contrôle
    // on écrit les 4 bits de la donnée
}
```
> [!TIP]  
> Pour faire des temporisations on peut utiliser les macros dans la bibliothèque `pic.h` (déjà importée par `xc.h`) :
> - `__delay_us(unsigned int t)` : délai en microsecondes
> - `__delay_ms(unsigned int t)` : délai en millisecondes

`__delay_us` et `__delay_ms` sont implémentées sous forme de boucles qui utilisent le paramètre `_XTAL_FREQ` (fréquence de l'oscilateur du microcontrôleur) pour faire des délais. Il faudra donc penser à le définir :
```c
#define _XTAL_FREQ XXXXXXX // remplacer XXXXXXX par la fréquence du microcontroleur
```

> [!NOTE]  
> Il faudra aussi se poser la question de la pertinence des délais les plus courts, au vu de la période l'horloge du microcontrôleur et sachant qu'une instruction assembleur s'exécute en 4 cycles d'horloge...
> Combien de temps s'écoule-t-il entre la fin de l'exécution d'une instruction et la fin de l'exécution de la suivante ?

#### ➤ Commandes 8 bits :

Dans le tableau récapitulatif des commandes du module LCD dans la datasheet *DS_Afficheurs_Sunplus*, on voit que les autres commandes sont composées d'une donnée sur 8 bits et, comme en mode 4 bits, 2 bits de contrôle.

On repart donc sur la même base qu'en mode 4 bits.
La différence est qu'il faut être capable d'envoyer 8 bits de données sur un bus de 4 bits. 

> [!TIP]
> Pour envoyer 8 bits de données sur un bus de 4 bits, pas le choix, il faut envoyer les données en 2 fois.
> Il faut donc faire des [opérations binaires](https://dept-info.labri.fr/ENSEIGNEMENT/programmation1/cours/CM_9___Manipulation_binaire.pdf) afin de séparer les 4 bits de poids fort des 4 bits de poids faible.

> [!IMPORTANT]
> Le protocole exige d'envoyer les bits de poids fort en premier.

```c
void lcd_write_instr_8bits(uint8_t rs, uint8_t rw, uint8_t data_8bits) {
    // on assigne les signaux de contrôle
    // on écrit les 4 bits de poids fort de la donnée
    // on écrit les 4 bits de poids faible de la donnée
}
```

#### ➤ lcd_busy :
Avant d'envoyer une commande il faut s'assurer que le module n'est pas occupé à exécuter la commande précédente. Sinon la commande envoyée ne sera pas exécutée. 

> [!TIP]  
> Pour savoir si la précédente commande a fini d'être exécutée, il est possible de lire le bit 'busy', avec la commande correspondante.
> Cependant, dans un premier temps, par souci de simplicité, on peut se contenter d'une temporisation. Sa durée doit à être supérieure au temps d'exécution de la commande la plus longue (cf. *DS_Afficheurs_Sunplus*).


### <ins>Étape 3</ins> : Développement des fonctions correspondant aux différentes commandes
La page 7 de la datasheet du module LCD *DS_Afficheurs_Sunplus* liste toutes les commandes proposées par le module. Avant de chercher à développer la fonction d'initialisation, il est préférable de développer des fonctions correspondant à ces commandes.

Notamment les suivantes :

- `Clear Display `
- `Return Home ` 
- `Entry Mode Set `
- `Display ON/OFF Control `
- `Cursor or Display Shift `
- `Function Set `
  
> [!TIP]
> Ces commandes sont caractérisées par 3 valeurs : `rs`, `rw` et une donnée de 8 bits.
> Ce sont justement les paramètres de la foncton `lcd_write_instr_8bits` décrite plus tôt.

> [!TIP]
> Pour générer la donnée de la commande avec les bons arguments, il sera nécessaire pour certaines fonctions d'effectuer des [opérations binaires](https://dept-info.labri.fr/ENSEIGNEMENT/programmation1/cours/CM_9___Manipulation_binaire.pdf).

### <ins>Étape 4</ins> : Développement de la fonction d'initialisation
La page 11 de la datasheet du module LCD *DS_Afficheurs_Sunplus* détaille la procédure d'initialisation du module.

> [!TIP]  
> Plutôt que d'envoyer les commandes avec les données brutes dans cette procédure, il est préférable de comprendre ce que fait chacune d'entre elles.
> Ainsi, on remarque qu'une grande partie de la procédure d'initialisation peut être réalisée en effectuant des appels aux fonctions définies plus haut.

> [!IMPORTANT]  
> - Penser à l'alimentation du module (*cf.* datasheet de la carte PICDEM2+).
> - Penser aux ports du microcontrôleur qui ont été utilisés... Ont-ils bien été définis comme entrée/sortie ?

> [!NOTE]  
> À ce stade on peut tester si tout fonctionne. Pour cela, on peut ajouter un appel à `lcd_display_control` avec les bons paramètres pour allumer l'écran et faire clignoter le curseur.
> Ainsi, si après avoir téléversé le programme sur la carte, le curseur clignote sur l'écran, les étapes précédentes sont validées !

### <ins>Étape 5</ins> : Développement des fonctions utilisateur restantes

Il ne manque alors plus qu'à réaliser les fonctions :
- `lcd_putch` pour écrire un caractère 
- `lcd_puts` pour écrire une chaîne de caractères 
- `lcd_shift_cursor` pour pour déplacer le curseur 
- `lcd_pos` pour le positionnement du curseur en un point de l'écran

<h2 id="aide_horloge"> 4. Affichage de l'horloge sur l'écran LCD </h2>

Maintenant que l'on peut afficher ce que l'on veut sur écran, on cherche à afficher l'horloge.
On utilise donc la fonction d'interruption (déclenchée toutes les secondes grâce à la configuration du timer) pour générer les heures, minutes et secondes qui seront affichés sur l'écran.

> [!TIP]  
> Comme toujours en programmation microcontroleur, bien réfléchir à ce qui doit être fait dans la fonction d'interruption et ce qui doit être fait ailleurs...

Pour formatter l'horloge dans une chaîne de caractère, le plus simple est certainement d'utiliser la fonction `sprintf` de la bibliothèque `stdio`.
Pour obtenir la documentation de `sprintf`, il suffit de taper dans un terminal :
```bash
man sprintf
```
On voit qu'elle fonctionne comme `printf` mais avec un argument en plus : une chaîne de charactère de destination.

Exemple :
```c
char formatted_time[STRING_LENGTH]; // STRING_LENGTH: nombre de caractères après formatage + 1 (pour le '\0' de fin de chaîne)
sprintf(formatted_time, "%d:%d:%d", t.hours, t.minutes, t.seconds);
```
Résultat : `12:1:8`

Comme `printf`, on peut forcer une mise en forme sur un nombre précis de charactères :
```c
sprintf(formatted_time, "%2d:%2d:%2d", t.hours, t.minutes, t.seconds);
```
Résultat : `12: 1: 8`

De même, on peut forcer l'affichage des 0 :
```c
sprintf(formatted_time, "%02d:%02d:%02d", t.hours, t.minutes, t.seconds);
```
Résultat : `12:01:08`

<h2 id="aide_conf_horloge"> 5. Développement de la fonctionnalité de configuration de l'horloge </h2>

### Rappel du cahier des charges

L'objectif de cette partie est de pouvoir configurer l'horloge à l'aide des boutons poussoir S2 et S3 :
- Un appui prolongé d'au moins 2 s sur S2 fera clignoter les heures, celles-ci s'incrémenteront à chaque appui sur S3, ou automatiquement (f ≈ 5 Hz) en cas d'appui maintenu au-delà de 2 s.
- Un nouvel appui sur S2 permettra un réglage des minutes selon la même procédure.
- Éventuellement, un nouvel appui sur S2 permettra un réglage des secondes selon la même procédure.
- Un dernier appui sur S2 fera quitter le mode "réglage".

> [!TIP]  
> Un bonne approche pour implémenter cette fonctionnalité est de développer une machine d'état.

> [!TIP]
> Les interrupteurs physiques ont une période de rebonds qui peut provoquer des faux déclenchements. Pour éviter des changements d'états non désirer un filtre anti-rebonds peut être implémenté à l'aide de délais de temporisation.

### Machine d'état en C

Le principe est le même que dans un langage de description matérielle comme le VHDL : représenter le comportement d'un système en réponse à des événements.

Voici un exemple d'une machine d'état implémentant le système de contrôle d'une porte automatique.

```c
// Déclaration de l'enumération représentant les états
enum state_e {
    ST_CLOSED,
    ST_OPENED,
    ST_CLOSING
    ST_OPENING,
};

void main() {
    enum state_e state; // Déclaration de la variable contenant l'état
    while (1) {
        switch(state) {
            case ST_CLOSED:
                // Condition de changement d'état
                if (BTN_OPEN == BTN_ON) {
                    state = ST_OPENING;
                }
                break;
            case ST_OPENED:
                // Comportement si le système est dans cet état
                if (BTN_OPEN == BTN_ON) {
                    reset_timer_opened();
                }
                // Condition de changement d'état
                if (timer_opened >= OPENED_DURATION) {
                    state = ST_CLOSING;
                }
                break;
            case ST_CLOSING:
                // Comportement si le système est dans cet état
                move_door(DIRECTION_CLOSE);

                // Condition de changement d'état
                if (SENSOR_SECURITY == PERSON_DETECTED || BTN_OPEN == BTN_ON) {
                    state = ST_OPENING;
                } else if (SENSOR_CLOSED == SENSOR_ON) {
                    state = ST_CLOSED;
                }
                break;
            case ST_OPENING:
                // Comportement si le système est dans cet état
                move_door(DIRECTION_OPEN);

                // Condition de changement d'état
                if (SENSOR_OPENED == SENSOR_ON) {
                    reset_timer_opened();
                    state = ST_OPENED;
                }
                break;
        }
    }
}
```
