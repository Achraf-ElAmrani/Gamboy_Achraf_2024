#include <Adafruit_ILI9341.h>  // Bibliothèque pour gérer l'écran ILI9341
#include <Adafruit_GFX.h>      // Bibliothèque pour les fonctions graphiques

#define TFT_CS    10  // Broche de sélection de l'écran
#define TFT_DC    12  // Broche de commande de données
#define TFT_RST    6  // Broche de réinitialisation
#define x A0  // Axe X du joystick
#define y A2  // Axe Y du joystick

// Initialisation de l'écran ILI9341
Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);

// Position initiale du point
int pointX = 120, pointY = 160;
const int Radius = 5, threshold = 50, speed = 15; // Si la variation est inférieure à threshold = zone morte (50), elle est ignorée

// Fonction pour dessiner un point à une position donnée avec une couleur spécifique
void drawPoint(int x, int y, uint16_t color) {
  tft.fillCircle(x, y, Radius, color);
}

void setup() {
  tft.begin();  // Initialisation de l'écran
  tft.setRotation(3);  // Orientation de l'écran
  tft.fillScreen(ILI9341_BLACK);  // Effacement de l'écran
  drawPoint(pointX, pointY, ILI9341_WHITE);  // Affichage du point initial
}

void loop() {
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
  delay(50);  // Pause pour fluidifier le mouvement
}