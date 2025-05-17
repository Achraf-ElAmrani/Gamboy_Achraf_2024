 #include <Adafruit_ILI9341.h>  // Bibliothèque pour gérer l'écran ILI9341
 #include <Adafruit_GFX.h>      // Bibliothèque pour les fonctions graphiques
 #include <Wire.h>
 #include <Adafruit_MCP23008.h> // Bibliothèque pour gérer le MCP23008
 #include <I2S.h>

 #define TFT_CS    10  // Broche de sélection de l'écran
 #define TFT_DC    12  // Broche de commande de données
 #define TFT_RST    6  // Broche de réinitialisation
 
 #define x A0  // Axe X du joystick
 #define y A2  // Axe Y du joystick
 
 #define BUTTON1 0
 #define BUTTON2 1
 #define BUTTON3 2
 #define BUTTON4 3
 
 extern Adafruit_MCP23008 mcp;
 // Position initiale du point
 extern int pointX, pointY;
 // Si la variation est inférieure à threshold = zone morte (50), elle est ignorée
 extern int Radius, threshold, speed; 
 // Initialisation de l'écran ILI9341
 extern Adafruit_ILI9341 tft;

 extern byte Pos_X;
 extern bool difficulte;
 extern bool tire;
 extern byte position;
 extern int score;
 
 extern byte Mode;
 extern byte MODE_POINT;
 extern byte MODE_INVADERS;
 extern unsigned long Time_ms;
 
 void bouton_qui_bande(void);
 void drawPoint(int, int, uint16_t);
 void Menu(void);
 void InitialisationButton(void);
 void InitialisationEcran(void);
 void MettreAJourPosition(void);
 bool buttonappuyer(int button);
 int Deplacement(int ValeurJoystick);
 void aile(uint16_t color);
 void cible_touche(void);
 void score_affichage(void);
 void cible_affichage(void);
 void tir_affichage(void);
 void triangleinv(void);
 
