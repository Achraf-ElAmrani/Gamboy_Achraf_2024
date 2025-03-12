#include "console.h"
// Initialisation de l'écran ILI9341
Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);
// Position initiale du point
int pointX = 120, pointY = 160;
const int Radius = 5, threshold = 50, speed = 15; // Si la variation est inférieure à threshold = zone morte (50), elle est ignorée

byte Mode = 0;
byte MODE_POINT = 1;
byte MODE_INVADERS = 2;
Adafruit_MCP23008 mcp;

void drawPoint(int x, int y, uint16_t color) {
  tft.fillCircle(x, y, Radius, color);
}

void Menu(void){
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

void InitialisationButton(void){
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
}

void InitialisationEcran(void){
  tft.begin();  // Initialisation de l'écran
  tft.setRotation(3);  // Orientation de l'écran
  tft.fillScreen(ILI9341_BLACK);  // Effacement de l'écran
}

void MettreAJourPosition(void){
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
}
bool buttonappuyer(int button){
  return mcp.digitalRead(button) == LOW;
}

int Deplacement(int ValeurJoystick){
 if (abs(ValeurJoystick - 512)> threshold){
    return map(ValeurJoystick,0,1023,-speed,speed);
 } else {
  return 0;
 }

}