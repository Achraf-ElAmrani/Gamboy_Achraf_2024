#include "console.h"
// Initialisation de l'écran ILI9341
Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);
// Position initiale du point
int pointX = 120, pointY = 160;
int Radius = 5, threshold = 10, speed = 7;  // Si la variation est inférieure à threshold = zone morte (10), elle est ignorée
unsigned long Time_ms = 0;//unsigned long peut contenir des valeurs de 0 à 4 294 967 295

byte Pos_X = 32;
bool difficulte = 0;
bool tire = 0;
byte position = rand() % 60; // division de rand() par 60 = nombre aléatoire entre 0 et 59.
int score = 0;

byte Mode = 0;
byte MODE_POINT = 1;
byte MODE_INVADERS = 2;
Adafruit_MCP23008 mcp;

void drawPoint(int x, int y, uint16_t color) { //couleur du point, codée sur 16 bits
  tft.fillCircle(x, y, Radius, color);
}

void Menu(void) {
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

void InitialisationButton(void) {
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
}

void InitialisationEcran(void) {
  tft.begin();                    // Initialisation de l'écran
  tft.setRotation(3);             // Orientation de l'écran
  tft.fillScreen(ILI9341_BLACK);  // Effacement de l'écran
}

void MettreAJourPosition(void) {
  int oldX = pointX, oldY = pointY;
  if (millis() >= Time_ms + 10) {
    int xValue = analogRead(x), yValue = analogRead(y);  // Lecture des valeurs du joystick
    int oldX = pointX, oldY = pointY;                    // Sauvegarde de l'ancienne position

    // Vérification des mouvements du joystick et mise à jour de la position
    if (abs(xValue - 512) > threshold) pointX -= map(xValue, 0, 1023, -speed, speed);
    if (abs(yValue - 512) > threshold) pointY -= map(yValue, 0, 1023, -speed, speed);

    // Contraindre la position du point à l'intérieur des limites de l'écran
    pointX = constrain(pointX, Radius, tft.width() - Radius);
    pointY = constrain(pointY, Radius, tft.height() - Radius);


    drawPoint(oldX, oldY, ILI9341_BLACK);      // Effacer l'ancien point
    drawPoint(pointX, pointY, ILI9341_WHITE);  // Dessiner le nouveau point

    Time_ms = millis();
    // Vérification si un bouton est pressé pour remettre le point au centre
  }
  if (mcp.digitalRead(BUTTON1) == LOW) {

    pointX = tft.width() / 2;              // Réinitialiser la position X au centre
    pointY = tft.height() / 2;             // Réinitialiser la position Y au centre
    drawPoint(oldX, oldY, ILI9341_BLACK);  // Effacer l'ancien point
  }
}
void bouton_qui_bande()
{
  if (mcp.digitalRead(BUTTON3))
  {
    Radius--;
  }
  if (mcp.digitalRead(BUTTON4))
  {
    Radius++;
  }
}
bool buttonappuyer(int button) {
  return mcp.digitalRead(button) == LOW;
}

int Deplacement(int ValeurJoystick) {
  if (abs(ValeurJoystick - 512) > threshold) {
    return map(ValeurJoystick, 0, 1023, -speed, speed);//return map = chatgpt
  } else {
    return 0;
  }
}
void aile(uint16_t color)
{
  static bool meme_aile;
  //ILI9341_GREEN
  if(meme_aile!=Pos_X)
  {
  color=ILI9341_BLACK;
  byte Pos_X_droit = meme_aile - 2;
  byte Pos_X_gauche = meme_aile + 2;
  byte aile_d_pixel1 = meme_aile - 1;
  byte aile_d_pixel2 = meme_aile - 2;
  byte aile_d_pixel3 = meme_aile - 3;
  byte aile_g_pixel1 = meme_aile + 1;
  byte aile_g_pixel2 = meme_aile + 2;
  byte aile_g_pixel3 = meme_aile + 3;
  tft.drawLine(aile_g_pixel1, 5, aile_g_pixel1, 5, color);
  tft.drawLine(aile_g_pixel2, 5, aile_g_pixel2, 5, color);
  tft.drawLine(aile_g_pixel3, 4, aile_g_pixel3, 10, color);
  tft.drawLine(aile_d_pixel1, 5, aile_d_pixel1, 5, color);
  tft.drawLine(aile_d_pixel2, 5, aile_d_pixel2, 5, color);
  tft.drawLine(aile_d_pixel3, 4, aile_d_pixel3, 10, color);
  }
  color=ILI9341_BLACK;
  byte Pos_X_droit = Pos_X - 2;
  byte Pos_X_gauche = Pos_X + 2;
  byte aile_d_pixel1 = Pos_X_droit - 1;
  byte aile_d_pixel2 = Pos_X_droit - 2;
  byte aile_d_pixel3 = Pos_X_droit - 3;
  byte aile_g_pixel1 = Pos_X_gauche + 1;
  byte aile_g_pixel2 = Pos_X_gauche + 2;
  byte aile_g_pixel3 = Pos_X_gauche + 3;
  tft.drawLine(aile_g_pixel1, 5, aile_g_pixel1, 5, color);
  tft.drawLine(aile_g_pixel2, 5, aile_g_pixel2, 5, color);
  tft.drawLine(aile_g_pixel3, 4, aile_g_pixel3, 10, color);
  tft.drawLine(aile_d_pixel1, 5, aile_d_pixel1, 5, color);
  tft.drawLine(aile_d_pixel2, 5, aile_d_pixel2, 5, color);
  tft.drawLine(aile_d_pixel3, 4, aile_d_pixel3, 10, color);
  meme_aile = Pos_X;
}
void cible_touche(void) {
  // Petit flash visuel
  for (int i = 0; i < 2; i++) {
    tft.invertDisplay(true);
    delay(100);
    tft.invertDisplay(false);
    delay(100);
  }

  // Affiche "score +1!"
  tft.setRotation(3);
  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(2);
  tft.setCursor(100, 120);
  tft.print("score +1!");

  delay(800); // Laisse le message visible brièvement

  // Efface proprement la zone du texte avec fillRect
  tft.fillRect(100, 120, 120, 20, ILI9341_BLACK); 
  // (ajuste la largeur/hauteur si nécessaire)
}


void score_affichage(void) {
  static int ancien_score;

  tft.setRotation(3);
  tft.setCursor(0, 0);

  // Efface l'ancien score si nécessaire
  if (ancien_score != score) {
    tft.setTextColor(ILI9341_BLACK);
    tft.print("score:");
    tft.print(ancien_score);
    
    tft.setCursor(0, 0); // Remet le curseur au début pour le nouveau score
    tft.setTextColor(ILI9341_WHITE); //couleur de fond 
    tft.print("score:");
    tft.print(score);

    ancien_score = score;
  }

  tft.setRotation(2);
}

void cible_affichage(void) {
  static int ancienne_position; // Valeur pour forcer le premier affichage

  // Si la position a changé, efface l'ancienne cible
  if (ancienne_position != position) {
    tft.drawCircle(ancienne_position, 110, 3, ILI9341_BLACK);
  }

  // Dessine la nouvelle cible
  tft.drawCircle(position, 110, 3, ILI9341_PINK);

  // Mémorise la nouvelle position
  ancienne_position = position;
}

void tir_affichage(void) {
  static int meme_tire; //initialisée meme tire une seule fois, puis garde en mémoire tant que le programme tourne.

  // Si la position du tir a changé, efface l'ancien tir
  if (meme_tire != Pos_X) {
    tft.drawLine(meme_tire, 15, meme_tire, 118, ILI9341_BLACK);
  }

  // Si un tir est actif, dessine le nouveau tir
  if (tire == 1) {
    tft.drawLine(Pos_X, 15, Pos_X, 118, ILI9341_RED);
    meme_tire = Pos_X; // Met à jour la position mémorisée
  } else {
    meme_tire; // Réinitialise si plus de tir actif
  }
}

void triangleinv(void) {
  static int meme_triangle;
  
  int Pos_X_droit = Pos_X + 5;
  int Pos_X_gauche = Pos_X - 5;

  // Si la position a changé, efface l'ancien triangle
  if (meme_triangle != Pos_X) {
    int ancien_droit = meme_triangle + 5;
    int ancien_gauche = meme_triangle - 5;
    tft.drawTriangle(meme_triangle, 15, ancien_droit, 5, ancien_gauche, 5, ILI9341_BLACK);
  }

  // Dessine le nouveau triangle à la nouvelle position
  tft.drawTriangle(Pos_X, 15, Pos_X_droit, 5, Pos_X_gauche, 5, ILI9341_GREEN);

  // Mémorise la nouvelle position
  meme_triangle = Pos_X;
}

