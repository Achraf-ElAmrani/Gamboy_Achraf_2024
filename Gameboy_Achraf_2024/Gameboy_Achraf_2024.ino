// Programation console
// Ahraf El Amrani
// 6TQA-INRACI
// Feather M0 Express - 8-bit Expander, Ecran ILI9341 - Joystick - Ampli classe D MAX98357A
// 08.03.2025
#include "console.h"  // Inclusion du fichier contenant les fonctions du projet

void setup() {
  Serial.begin(9600);  // Démarre la communication série à 9600 bauds pour le débogage
  InitialisationEcran();  // Initialise l'écran ILI9341 (couleur, rotation, etc.)
  InitialisationButton();  // Configure les boutons via l'extendeur I2C MCP23008
  Menu();  // Affiche le menu principal de sélection des modes
  son();  // Initialise le module audio 

  // === Sélection du mode initial via les boutons ===
  while (Mode == 0) {  // Tant qu'aucun mode n'a été sélectionné (Mode = 0)
    if (mcp.digitalRead(BUTTON1) == LOW) Mode = MODE_POINT;  // Bouton 1 → Mode POINT
    if (mcp.digitalRead(BUTTON2) == LOW) Mode = MODE_INVADERS;  // Bouton 2 → Mode INVADERS
    if (mcp.digitalRead(BUTTON3) == LOW) Mode = bibliotheque_de_son;  // Bouton 3 → Bibliothèque de son
  }

  tft.fillScreen(ILI9341_BLACK);  // Efface l'écran avant d'entrer dans un mode
  // === Affiche le mode choisi ===
  if (Mode == MODE_POINT) {
    tft.setCursor(50, 100);
  } else if (Mode == MODE_INVADERS) {
    tft.setCursor(50, 100);
    tft.println("Mode: Invaders");
  } else if (Mode == bibliotheque_de_son) {
    tft.setCursor(50, 100);
    tft.println("Mode: bibliotheque de son");
  }

  tft.fillScreen(ILI9341_BLACK);  // Nettoie l’écran pour le mode choisi
}

void loop() {

  // === MENU PRINCIPAL ===
  // Si on revient au menu (Mode = 0), on réaffiche le menu et on attend une nouvelle sélection
  while (Mode == 0) {
    if (mcp.digitalRead(BUTTON1) == LOW) {
      Mode = MODE_POINT;
      tft.fillScreen(ILI9341_BLACK);
    }

    if (mcp.digitalRead(BUTTON2) == LOW) {
      Mode = MODE_INVADERS;
      tft.fillScreen(ILI9341_BLACK);
    }

    if (mcp.digitalRead(BUTTON3) == LOW) {
      Mode = bibliotheque_de_son;
      tft.fillScreen(ILI9341_BLACK);
    }
  }

  // === MODE POINT ===
  if (Mode == MODE_POINT) {
    while (Mode == MODE_POINT) {
      // Si bouton 4 appuyé → retour menu
      if (mcp.digitalRead(BUTTON4) == LOW) {
        Mode = 0;
        Menu();
        while (mcp.digitalRead(BUTTON4) == LOW) ;  // attend relâchement bouton
        break;
      }

      MettreAJourPosition();  // Lit le joystick et déplace le point blanc
      bouton_qui_bande();  // Permet de changer le rayon du point avec les boutons
    }
  }

  // === MODE INVADERS ===
  if (Mode == MODE_INVADERS) {
    while (Mode == MODE_INVADERS) {
      // Retour menu avec bouton 4
      if (mcp.digitalRead(BUTTON4) == LOW) {
        Mode = 0;
        Menu();
        while (mcp.digitalRead(BUTTON4) == LOW);
        break;
      }

      // Lecture du joystick vertical pour déplacer le vaisseau
      byte Pos_X_droit = Pos_X - 2;
      byte Pos_X_gauche = Pos_X + 2;
      int deplacement = Deplacement(analogRead(y));  // Retourne une valeur entre -speed et +speed
      Pos_X = constrain(Pos_X + deplacement, 0, 1023);  // Limite entre 0 et 1023
      // Si bouton de tir appuyé
      if (!mcp.digitalRead(BUTTON3)) {
        tire = 1;
        int tol = 5;  // Tolérance de 5 pixels autour de la cible
        if (abs(Pos_X - position) <= tol) {
          cible_touche();  // Animation et affichage du "score +1"
          score++;
          position = rand() % 64;
          if (score >= 5) position++;  // difficulté : décalage de la cible
        } else {
          score = score - 1;  // Tir manqué → -1 point
          delay(150);  // Petite pause pour éviter le spam
        }

      } else {
        tire = 0;  // pas de tir
      }

      // Affichages graphiques
      tire_affichage();  // Affiche ou efface la ligne de tir
      score_affichage();  // Affiche le score dans le coin
      cible_affichage();  // Dessine la cible
      triangleinv();  // Affiche le vaisseau en triangle
    }
  }

  // === MODE BIBLIOTHÈQUE DE SON ===
  if (Mode == bibliotheque_de_son) {
    while (Mode == bibliotheque_de_son) {
      // Affichage d'aide pour l'utilisateur
      tft.setCursor(10, 100);
      tft.setTextColor(ILI9341_GREEN);
      tft.setTextSize(2);
      tft.print(" Bouton 1 = tetris_them");

      while (mcp.digitalRead(BUTTON1) == LOW) ;  // attend relâchement bouton pour éviter spam
      // Retour menu
      if (mcp.digitalRead(BUTTON4) == LOW) {
        Mode = 0;
        Menu();
        while (mcp.digitalRead(BUTTON4) == LOW);
        break;
      }

      // Si bouton 1 appuyé → joue le thème Tetris
      if (mcp.digitalRead(BUTTON1) == LOW) {
        tetris_them();  // Joue la mélodie via I2S
        while (mcp.digitalRead(BUTTON1) == LOW);  // attend relâchement
      }
    }
  }
}
