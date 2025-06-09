// Programation console
// Ahraf El Amrani
// 6TQA-INRACI
// Feather M0 Express - 8-bit Expander, Ecran ILI9341 - Joystick - Ampli classe D MAX98357A
// 08.03.2025
//probleme 1.tire pas rafraichi completement 2.Triangle qui depasse la limite haute de l'écran
#include "console.h"  // Inclusion du fichier contenant les fonctions du projet

void setup() {
  Serial.begin(9600);  // Initialisation de la communication série à 9600 bauds
  InitialisationEcran();  // Initialise l'écran ILI9341
  InitialisationButton(); // Initialise les boutons via l'extendeur MCP
  Menu();  // Affiche le menu de sélection des modes
  son();

  // Attente de la sélection du mode via les boutons
  while (Mode == 0) { //tant que Mode vaut 0
      if (mcp.digitalRead(BUTTON1) == LOW) Mode = MODE_POINT;     // Si bouton 1 pressé, mode Point
      if (mcp.digitalRead(BUTTON2) == LOW) Mode = MODE_INVADERS;  // Si bouton 2 pressé, mode Invaders
      if (mcp.digitalRead(BUTTON3) == LOW) Mode = bibliotheque_de_son;  // Si bouton 3 pressé, mode bibliotheque_de_son
  }

  tft.fillScreen(ILI9341_BLACK);  // Efface l'écran

  Time_ms = millis();  // Enregistre le temps initial

  // Affiche un message selon le mode choisi
  if (Mode == MODE_POINT) {
      tft.setCursor(50, 100);  // Positionne le curseur
  } else if (Mode == MODE_INVADERS) {
      tft.setCursor(50, 100);
      tft.println("Mode: Invaders");  // Affiche le nom du mode
  } else if (Mode == bibliotheque_de_son) {
      tft.setCursor(50, 100);
      tft.println("Mode: Librairie de son");  // Affiche le nom du mode
  }
  tft.fillScreen(ILI9341_BLACK);
}

void loop() {
  // --- Mode POINT ---
  while (Mode == MODE_POINT) //bloquant mais la variable mode n'est jamais réaffecter
  {
      MettreAJourPosition();  // Met à jour la position du joystick ou du point
      bouton_qui_bande();     // Gère l'entrée du bouton
  
  } 

// --- Mode INVADERS ---
  while (Mode == MODE_INVADERS) 
  {
    // Détermine les points verticaux du vaisseau (triangle)
    byte Pos_X_droit = Pos_X - 2;  byte Pos_X_gauche = Pos_X + 2;

    int deplacement = Deplacement(analogRead(y));
    Pos_X = constrain(Pos_X + deplacement, 0, 1023); // constrain = chatgpt : constrain(valeur, minimum, maximum)

    // Si le bouton de tir est pressé
    if (!mcp.digitalRead(BUTTON3)) {
      tire = 1;  // Active le tir

      // Vérifie si la cible est touchée
      if (Pos_X == position || Pos_X == position + 1 || Pos_X == position - 1) { //tolérance de ±1
        cible_touche();  // Fonction appelée quand la cible est touchée
        score++;         // Incrémente le score

        position = rand() % 64; // Change la position de la cible aléatoirement
        if (score >= 5) {
          position++;  // difficulté supplémentaire à partir d’un score de 5
        }
      } else {
      score = score - 1; // tire rater = -1 de score
      delay(100);
      }
    } else {
      tire = 0;  // Pas de tir si le bouton n'est pas pressé
    }

    tir_affichage(); score_affichage();  cible_affichage();  triangleinv(); tetris_them();     
  }

  
  while (Mode == bibliotheque_de_son) //bloquant mais la variable mode n'est jamais réaffecter
  {
      tetris_them();
  } 

}
