
# Console de jeux portable
 <img alt="GitHub followers" src="https://img.shields.io/github/followers/Achraf-ElAmrani?style=flat&logo=github"> <img alt="Static Badge" src="https://img.shields.io/badge/French-8A2BE2"> <img alt="Static Badge" src="https://img.shields.io/badge/Projet-8A2BE2?color=blue"> <img alt="Static Badge" src="https://img.shields.io/badge/-%20?logo=cplusplus"> <img alt="Static Badge" src="https://img.shields.io/badge/-%20?logo=easyeda&color=blue"> <img alt="Static Badge" src="https://img.shields.io/badge/-%20?logo=arduino&color=lightblue">

# Projet en cours de réalisation par : 
- El Amrani Achraf
- étudiant a l' INRACI
- 6 eme technique de qualification 
## Video
## Table de matie des matières
- [Introduction](#Introduction)
- [Liste des composants](#Liste-des-composants)
- [Les caractéristiques](#Les-caractéristiques)
- [Schéma de principe](#Schéma-de-principe)
- [le PCB](#le-PCB)
- [Schéma de principe](#Le-schéma-bloc)
- [Ordinogramme](#Ordinogramme)
- [3D](#3D)
- [Bibliothèques nécessaires](#Bibliothèques-nécessaires)
- [Source](#Source)
## Introduction

Passionné par les jeux vidéo et la mécanique, j’ai décidé de consacrer mon projet de fin d’études à la création d’une console de jeux portable. L’inspiration m’est venue après avoir découvert le film Tetris, qui met en lumière le célèbre jeu ainsi que la mythique Game Boy.

Mon objectif est de concevoir un appareil capable d’exécuter plusieurs jeux, avec Tetris comme titre principal. L’expérience de jeu sera optimisée grâce à un système de contrôle intuitif, combinant joystick et boutons physiques.

Ce projet est bien plus qu’un simple exercice technique : il représente l’aboutissement de mon parcours académique et l’opportunité d’appliquer concrètement les compétences que j’ai développées au fil des années. Il reflète mon engagement dans le domaine du jeu vidéo ainsi que mon envie de relever des défis techniques stimulants.

## Liste des composants

- Un micro controleur feather / Feather M0 express

- un  expandeur d'E/S (Entrées/Sorties) / MCP23008

- Un écran SPI / ILI9341 TFT 2.8"

- Un régulateur de tension linéaire LDO (Low Dropout) / MCP1826

- Un amplificateur audio de classe D / MAX98357A 

- Un contrôleur de charge pour batterie Li-Ion/Li-Po / MCP73831T-2ACI/OT

- Un  Mini Joystick Analogique 2 Axes / Joystick 2765

- Une double batterie Li-Ion

- x4 boutons

- x8 Résistances

- x1 condosateur 

- x1 LED 

- x3 diode

## Les caractéristiques
Feather M0 express : 

- Microcontrôleur : ATSAMD21G18 (32 bits)

- Fréquence : 48 MHz

- Mémoire Flash : 256 KB

- RAM : 32 KB

- Stockage : 2 Mo de SPI Flash intégré 

- Alimentation : via USB ou batterie Li-Po 3.7V 

- Ports I/O : 20 GPIO (dont 6 analogiques, PWM et I²C/SPI/UART)

- Sortie DAC 10 bits (1 broche analogique vraie)

- Connectivité : I²C, SPI, UART, PWM

- Compatible avec : Arduino IDE

MCP23008 :

- 8 broches d'E/S configurables individuellement en entrée ou sortie

- Communication via I²C (adresse configurable)

- Résistances de tirage (pull-up) intégrées (100 kΩ activables par logiciel)

- Interruption configurable (INT) pour détecter les changements d'état des broches

- Tension de fonctionnement : 1.8V à 5.5V

- Courant max par broche : environ 25mA (selon la tension)

MCP1826 :

- Tension d’entrée (Vin) : 2.1V à 13.2V

- Tension de sortie (Vout) : 5V 

- Courant de sortie max : 1A

- Faible chute de tension (Dropout) : ~0.525V 

- Faible consommation de courant : 120 µA

MAX98357A : 

- Entrée audio numérique : I²S (compatible standard 16, 24 et 32 bits)

- Sortie audio : Mono, puissance jusqu'à 3,2W sous 4Ω (avec une alimentation de 5V)

- Plage d’alimentation : 2.5V à 5.5V

- Convertisseur DAC + amplificateur intégré

- Faible consommation et haute efficacité 

- Filtrage interne pour réduire le bruit et améliorer la qualité sonore

- Fonctionne avec l'horloge interne du microcontrôleur

MCP73831T-2ACI/OT : 

- Tension d’entrée (Vin) : 3.75V à 6V

- Courant de charge max : 500 mA 

- Tension de charge : 4.2V (pour batteries Li-Ion / Li-Po)

- Faible consommation en veille

- Indicateur LED possible : indique l’état de charge (via la broche STAT)

Joystick 2765 : 

- Type : Joystick analogique auto-centrant à 2 axes.​

- Potentiomètres intégrés : Deux potentiomètres de 10 kΩ chacun, un pour l'axe vertical (haut/bas) et un pour l'axe horizontal (gauche/droite).

ILI9341 TFT 2.8" : 

- Taille : 2.8 pouces

- Résolution : 240x320 pixels (orientation portrait ou paysage)

- Couleurs : 65K ou 262K couleurs (16 ou 18 bits)

- Tension d’alimentation : 3.3V 

- Tactile en option :  écran tactile résistif 

- Fréquence SPI : Jusqu’à 40MHz, permettant un affichage fluide

- Rétroéclairage LED intégré

## Schéma de principe
## le PCB
## Le schéma bloc
![schema bloque  drawio (2)](https://github.com/user-attachments/assets/83ecc262-afdc-4523-affc-aa4a836d04b1)

## Ordinogramme
## 3D 
![Capture d'écran 2025-02-04 203529](https://github.com/user-attachments/assets/c2d2cccd-72f5-401e-8e14-7d100f6c450f)
![Capture d'écran 2025-02-04 194054](https://github.com/user-attachments/assets/2d69b65a-8281-49bf-bdec-56c905a3ff89)
![Capture d'écran 2025-02-04 194103](https://github.com/user-attachments/assets/9dff16ac-fc47-44fa-903b-3567f36d163e)
![Capture d'écran 2025-02-04 194122](https://github.com/user-attachments/assets/b390fd98-e645-4a37-a916-45a664a20343)
## Bibliothèques nécessaires
## Source 

