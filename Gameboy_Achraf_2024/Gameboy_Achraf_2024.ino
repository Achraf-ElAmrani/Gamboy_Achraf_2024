// Programation console
// Ahraf El Amrani
// 6TQA-INRACI
// Feather M0 Express - 8-bit Expander, Ecran ILI9341 - Joystick - Ampli classe D MAX98357A
// 08.03.2025

#include "console.h"  // Inclusion du fichier contenant les fonctions du projet

void setup() {
  Serial.begin(9600);  // Initialisation de la communication série à 9600 bauds
  InitialisationEcran();  // Initialise l'écran ILI9341
  InitialisationButton(); // Initialise les boutons via l'extendeur MCP
  Menu();  // Affiche le menu de sélection des modes

  // Attente de la sélection du mode via les boutons
  while (Mode == 0) { //tant que Mode vaut 0
      if (mcp.digitalRead(BUTTON1) == LOW) Mode = MODE_POINT;     // Si bouton 1 pressé, mode Point
      if (mcp.digitalRead(BUTTON2) == LOW) Mode = MODE_INVADERS;  // Si bouton 2 pressé, mode Invaders
  }

  tft.fillScreen(ILI9341_BLACK);  // Efface l'écran

  Time_ms = millis();  // Enregistre le temps initial

  // Affiche un message selon le mode choisi
  if (Mode == MODE_POINT) {
      tft.setCursor(50, 100);  // Positionne le curseur
  } else if (Mode == MODE_INVADERS) {
      tft.setCursor(50, 100);
      tft.println("Mode: Invaders");  // Affiche le nom du mode
  }
}

void loop() {
  // --- Mode POINT ---
  if (Mode == MODE_POINT) 
  {
      MettreAJourPosition();  // Met à jour la position du joystick ou du point
      bouton_qui_bande();     // Gère l'entrée du bouton (fonction personnalisée)
  
  // --- Mode INVADERS ---
  } 
  else if (Mode == MODE_INVADERS) 
  {
    // Détermine les points verticaux du vaisseau (triangle)
    byte Pos_X_droit = Pos_X - 2;
    byte Pos_X_gauche = Pos_X + 2;

    int valeur_deplacement = analogRead(y) // ex : 5V → 1023

    // 1 printer la valeur de analogRead
    // trouver les "gaps" des valeurs en fonction de linclinaison du joystick
    // faire des verifs pour asigner a la variable de deplacement la valeur voulue

    int deplacement = Deplacement();//retourne une valeur entière. Cette valeur est ensuite stockée dans la variable deplacement
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
      }
    } else {
      tire = 0;  // Pas de tir si le bouton n'est pas pressé
    }

    tir_affichage();    // Affiche le tir
    score_affichage();  // Affiche le score
    cible_affichage();  // Affiche la cible
    triangleinv();      //Affiche le vaisseau
    aile(ILI9341_GREEN); //Affiche aile du vaisseau

  }
}
