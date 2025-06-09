 #include <Adafruit_ILI9341.h>  // Bibliothèque pour gérer l'écran ILI9341
 #include <Adafruit_GFX.h>      // Bibliothèque pour les fonctions graphiques
 #include <Wire.h>
 #include <Adafruit_MCP23008.h> // Bibliothèque pour gérer le MCP23008
 #include <Adafruit_ZeroI2S.h>

 #define BUTTON1 0
 #define BUTTON2 1
 #define BUTTON3 2
 #define BUTTON4 3

 #define TFT_CS    10  // Broche de sélection de l'écran
 #define TFT_DC    12  // Broche de commande de données
 #define TFT_RST    6  // Broche de réinitialisation
 
 #define x A0  // Axe X du joystick
 #define y A2  // Axe Y du joystick

 #define SAMPLERATE_HZ 44100 // Définit la fréquence d'échantillonnage du son à 44 100 Hz.
                             // C’est le nombre d’échantillons audio par seconde. Plus ce chiffre est élevé, meilleure est la qualité du son.
                             // 44 100 Hz correspond à la qualité CD audio.

 #define AMPLITUDE     ((1<<29)-1)   // Définit l’amplitude maximale des ondes générées. Cela détermine le volume sonore.
                             // La valeur ((1<<29)-1) correspond à 2³⁰ - 1, soit 1 073 741 823.
                             // Tu peux la réduire si le son est trop fort ou sature. Par exemple : 1<<27 est plus doux.

 #define WAV_SIZE      256   // Taille du tableau qui contient une période de l'onde audio.
                             // Plus la taille est grande, plus l’onde est précise.
                             // 256 points suffisent pour générer des ondes simples.
 
//Définir la fréquence des notes de musique (à partir de http://www.phy.mtu.edu/~suits/notefreqs.html) :
 #define C4_HZ      261.63 // #define C4_HZ 261.63  -> note C (Do) de la 4e octave
 #define D4_HZ      293.66 // #define D4_HZ 293.66  -> note D (Ré) de la 4e octave
 #define E4_HZ      329.63 // #define E4_HZ 329.63  -> note E (Mi) de la 4e octave
 #define F4_HZ      349.23 // #define F4_HZ 349.23  -> note F (Fa) de la 4e octave
 #define G4_HZ      392.00 // #define G4_HZ 392.00  -> note G (Sol) de la 4e octave
 #define A4_HZ      440.00 // #define A4_HZ 440.00  -> note A (La) de la 4e octave
 #define B4_HZ      493.88 // #define B4_HZ 493.88  -> note B (Si) de la 4e octave

 // Déclaration d'un tableau de fréquences représentant une mélodie (ici, le thème de Tetris).
 // Chaque valeur correspond à une **note musicale** exprimée en Hertz (Hz).
 extern float tetris_theme[];
 // Durées associées (en secondes) pour chaque note
 extern float tetris_durations[];

 // tableaux pour stocker des formes d'onde audio de base.
 // SINE = onde sinusoïdale — son pur.
 extern int32_t sine[WAV_SIZE];
 // SAWTOOTH = onde en dent de scie — son brut.
 extern int32_t sawtooth[WAV_SIZE];
 // TRIANGLE = onde triangulaire — son doux, un peu comme un de flûte.
 extern int32_t triangle[WAV_SIZE];
 // SQUARE = onde carrée — son très numérique, un peu comme dans les jeux rétro.
 extern int32_t square[WAV_SIZE];

 extern Adafruit_MCP23008 mcp;
 extern Adafruit_ZeroI2S i2s;

 // Position initiale du point
 extern int pointX, pointY;
 // Si la variation est inférieure à threshold = zone morte (50), elle est ignorée
 extern int Radius, threshold, speed; 
 // Initialisation de l'écran ILI9341
 extern Adafruit_ILI9341 tft;

 extern byte Pos_X;
 extern bool tire;
 extern byte position;
 extern int score;
 
 extern byte Mode;
 extern byte MODE_POINT;
 extern byte MODE_INVADERS;
 extern byte bibliotheque_de_son;
 
 void bouton_qui_bande(void);
 void drawPoint(int, int, uint16_t);
 void Menu(void);
 void InitialisationButton(void);
 void InitialisationEcran(void);
 void MettreAJourPosition(void);
 bool buttonappuyer(int button);
 int Deplacement(int ValeurJoystick);
 void cible_touche(void);
 void score_affichage(void);
 void cible_affichage(void);
 void tire_affichage(void);
 void triangleinv(void);
 void generateSine(int32_t amplitude, int32_t* buffer, uint16_t length);
 void generateSawtooth(int32_t amplitude, int32_t* buffer, uint16_t length);
 void generateTriangle(int32_t amplitude, int32_t* buffer, uint16_t length);
 void generateSquare(int32_t amplitude, int32_t* buffer, uint16_t length);
 void playWave(int32_t* buffer, uint16_t length, float frequency, float seconds);
 void son(void);
 void tetris_them(void);
 
