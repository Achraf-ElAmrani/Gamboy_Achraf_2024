// Programation console
// Ahraf El Amrani
// 6TQA-INRACI
// Feather M0 Express - 8-bit Expander, Ecran ILI9341 - Joystick - Module son
// 08.03.2025
#include <Adafruit_ILI9341.h>  // Bibliothèque pour gérer l'écran ILI9341
#include <Adafruit_GFX.h>      // Bibliothèque pour les fonctions graphiques
#include <Wire.h>
#include <Adafruit_MCP23008.h> // Bibliothèque pour gérer le MCP23008

#define TFT_CS    10  // Broche de sélection de l'écran
#define TFT_DC    12  // Broche de commande de données
#define TFT_RST    6  // Broche de réinitialisation
// Définition des axe
#define x A0  // Axe X du joystick
#define y A2  // Axe Y du joystick
// Définition des boutons connectés au MCP23008
#define BUTTON1 0
#define BUTTON2 1
#define BUTTON3 2
#define BUTTON4 3

// Initialisation de l'écran ILI9341
Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);

// Initialisation du MCP23008 pour la gestion des boutons
Adafruit_MCP23008 mcp;

byte Mode = 0;
byte MODE_POINT = 1;
byte MODE_INVADERS = 2;

// Position initiale du point
int pointX = 120, pointY = 160;
const int Radius = 5, threshold = 50, speed = 15; // Si la variation est inférieure à threshold = zone morte (50), elle est ignorée

void Menu() {
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.setCursor(40, 50);
    tft.println("Select Mode:");
    tft.setCursor(60, 100);
    tft.println("1. Point");
    tft.setCursor(60, 140);
    tft.println("2. Invaders");
}

// Fonction pour dessiner un point à une position donnée avec une couleur spécifique
void drawPoint(int x, int y, uint16_t color) {
  tft.fillCircle(x, y, Radius, color);
}

void setup() {
  tft.begin();  // Initialisation de l'écran
  tft.setRotation(3);  // Orientation de l'écran
  tft.fillScreen(ILI9341_BLACK);  // Effacement de l'écran

  // Initialisation du MCP23008
  mcp.begin();

  // Configurer les broches comme entrées pour les boutons avec pull-ups
  mcp.pinMode(BUTTON1, INPUT);
  mcp.pullUp(BUTTON1, HIGH);
  mcp.pinMode(BUTTON2, INPUT);
  mcp.pullUp(BUTTON2, HIGH);
  mcp.pinMode(BUTTON3, INPUT);
  mcp.pullUp(BUTTON3, HIGH);
  mcp.pinMode(BUTTON4, INPUT);
  mcp.pullUp(BUTTON4, HIGH);
  Menu();

  while (Mode == 0) {
      if (mcp.digitalRead(BUTTON1) == LOW) Mode = MODE_POINT;
      if (mcp.digitalRead(BUTTON2) == LOW) Mode = MODE_INVADERS;
  }
    
  tft.fillScreen(ILI9341_BLACK);
  if (Mode == MODE_POINT) {
      tft.setCursor(50, 100);
      tft.println("Mode: Point");
      delay(1000);
      pointX = tft.width() / 2;
      pointY = tft.height() / 2;
  } else if (Mode == MODE_INVADERS) {
      tft.setCursor(50, 100);
      tft.println("Mode: Invaders");
      delay(1000);
  }
}

void loop() {
  if (Mode == MODE_POINT) {
      int xValue = analogRead(x), yValue = analogRead(y);  // Lecture des valeurs du joystick
      int oldX = pointX, oldY = pointY;  // Sauvegarde de l'ancienne position

  // Vérification des mouvements du joystick et mise à jour de la position
      if (abs(xValue - 512) > threshold) pointX -= map(xValue, 0, 1023, -speed, speed);
      if (abs(yValue - 512) > threshold) pointY -= map(yValue, 0, 1023, -speed, speed);

  // Contraindre la position du point à l'intérieur des limites de l'écran
      pointX = constrain(pointX, Radius, tft.width() - Radius);
      pointY = constrain(pointY, Radius, tft.height() - Radius);

      drawPoint(oldX, oldY, ILI9341_BLACK);  // Effacer l'ancien point
      drawPoint(pointX, pointY, ILI9341_WHITE);  // Dessiner le nouveau point

  // Vérification si un bouton est pressé pour remettre le point au centre
      if (mcp.digitalRead(BUTTON1) == LOW) {
      pointX = tft.width() / 2;  // Réinitialiser la position X au centre
      pointY = tft.height() / 2;  // Réinitialiser la position Y au centre
  }
  delay(50);  // Pause pour fluidifier le mouvement
}else if (Mode == MODE_INVADERS) {
        //mode Space Invaders
    }
}


