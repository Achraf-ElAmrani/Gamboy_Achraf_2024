#include <Adafruit_ILI9341.h>  // Bibliothèque pour gérer l'écran ILI9341
#include <Adafruit_GFX.h>      // Bibliothèque pour les fonctions graphiques
//#include <I2S.h>
/*
const int frequency = 440; // frequency of square wave in Hz
const int amplitude = 500; // amplitude of square wave
const int sampleRate = 8000; // sample rate in Hz

const int halfWavelength = (sampleRate / frequency); // half wavelength of square wave

short sample = amplitude; // current sample value
int count = 0;*/
//int sample = 0;
#define TFT_CS    10  // Broche de sélection de l'écran
#define TFT_DC    12  // Broche de commande de données
#define TFT_RST    6  // Broche de réinitialisation

// Initialisation de l'écran ILI9341
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

#define x A0  // Axe X du joystick
#define y A2  // Axe Y du joystick

// Position initiale du point
int pointX = 120, pointY = 160;
const int pointRadius = 5, threshold = 50, speed = 15; // Si la variation est inférieure à threshold = zone morte (50), elle est ignorée

// Fonction pour dessiner un point à une position donnée avec une couleur spécifique
void drawPoint(int x, int y, uint16_t color) {
  tft.fillCircle(x, y, pointRadius, color);
}

void setup() {
    /*if (!I2S.begin(I2S_PHILIPS_MODE, sampleRate, 16)) {
    Serial.println("Failed to initialize I2S!");
    while (1); // do nothing
  }*/
  tft.begin();  // Initialisation de l'écran
  tft.setRotation(3);  // Orientation de l'écran
  tft.fillScreen(ILI9341_BLACK);  // Effacement de l'écran
  drawPoint(pointX, pointY, ILI9341_WHITE);  // Affichage du point initial
}

void loop() {
  int xValue = analogRead(x), yValue = analogRead(y);  // Lecture des valeurs du joystick
  int oldX = pointX, oldY = pointY;  // Sauvegarde de l'ancienne position

  // Vérification des mouvements du joystick et mise à jour de la position
  if (abs(xValue - 512) > threshold)
  {
     pointX -= map(xValue, 0, 1023, -speed, speed);
      // I2S.write(sample);
  }
  if (abs(yValue - 512) > threshold)
  {
     pointY -= map(yValue, 0, 1023, -speed, speed); // Inversion ici
       //I2S.write(sample);
  }


  // Contraindre la position du point à l'intérieur des limites de l'écran
  pointX = constrain(pointX, pointRadius, tft.width() - pointRadius);
  pointY = constrain(pointY, pointRadius, tft.height() - pointRadius);

  drawPoint(oldX, oldY, ILI9341_BLACK);  // Effacer l'ancien point
  drawPoint(pointX, pointY, ILI9341_WHITE);  // Dessiner le nouveau point
  delay(50);  // Pause pour fluidifier le mouvement
}