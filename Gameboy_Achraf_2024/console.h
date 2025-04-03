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
 
 extern Adafruit_MCP23008 mcp;
 // Position initiale du point
 extern int pointX, pointY;
 // Si la variation est inférieure à threshold = zone morte (50), elle est ignorée
 extern const int Radius, threshold, speed; 
 // Initialisation de l'écran ILI9341
 extern Adafruit_ILI9341 tft;
 
 extern byte Mode;
 extern byte MODE_POINT;
 extern byte MODE_INVADERS;
 extern unsigned long Time_ms;
 
 void drawPoint(int, int, uint16_t);
 void Menu(void);
 void InitialisationButton(void);
 void InitialisationEcran(void);
 void MettreAJourPosition(void);
 bool buttonappuyer(int button);
 int Deplacement(int ValeurJoystick);
