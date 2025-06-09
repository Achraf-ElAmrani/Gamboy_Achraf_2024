#include "delay.h"
#include "console.h"
// Initialisation de l'écran ILI9341
Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);
// Position initiale du point
int pointX = 120, pointY = 160;
int Radius = 5, threshold = 10, speed = 7;  // Si la variation est inférieure à threshold = zone morte (10), elle est ignorée
unsigned long Time_ms = 0; //unsigned long peut contenir des valeurs de 0 à 4 294 967 295

byte Pos_X = 32;
bool difficulte = 0;
bool tire = 0;
byte position = rand() % 60; // division de rand() par 60 = nombre aléatoire entre 0 et 59.
int score = 0;

byte Mode = 0;
byte MODE_POINT = 1;
byte MODE_INVADERS = 2;
byte bibliotheque_de_son = 3;
Adafruit_MCP23008 mcp;
Adafruit_ZeroI2S i2s;

// Déclaration d'un tableau de fréquences représentant une mélodie (ici, le thème de Tetris).
// Chaque valeur correspond à une **note musicale** exprimée en Hertz (Hz).
// 0.0f Silence ou fin de la mélodie (aucun son)
float tetris_theme[] = {E4_HZ, B4_HZ, C4_HZ, D4_HZ, C4_HZ, B4_HZ, A4_HZ,A4_HZ, C4_HZ, E4_HZ, D4_HZ, C4_HZ, B4_HZ, C4_HZ,D4_HZ, E4_HZ, C4_HZ, A4_HZ, A4_HZ, 0.0f};

// Durées associées (en secondes) pour chaque note
float tetris_durations[] = {0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.4,0.2, 0.2, 0.4, 0.2, 0.2, 0.2, 0.2,0.2, 0.4, 0.2, 0.4, 0.2, 0.4};

// Crée des tableaux pour stocker des formes d'onde audio de base.
// SINE = onde sinusoïdale — son pur, utilisé pour les tonalités simples (comme un diapason)
int32_t sine[WAV_SIZE] = {0};      
// SAWTOOTH = onde en dent de scie — son "brut", utilisé dans les sons électroniques
int32_t sawtooth[WAV_SIZE] = {0};  
// TRIANGLE = onde triangulaire — son doux, un peu comme un son d’orgue ou de flûte
int32_t triangle[WAV_SIZE] = {0};  
// SQUARE = onde carrée — son très "numérique", utilisé dans les jeux rétro (comme NES ou GameBoy)
int32_t square[WAV_SIZE] = {0};    

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
  tft.setCursor(60, 180);
  tft.println("3. Librairie_de_son");
}

void InitialisationButton(void) {
  mcp.begin();
  // Configurer les broches comme entrées pour les boutons avec pull-ups
  mcp.pinMode(BUTTON1, INPUT);  mcp.pullUp(BUTTON1, HIGH);   mcp.pinMode(BUTTON2, INPUT);   mcp.pullUp(BUTTON2, HIGH);   
  mcp.pinMode(BUTTON3, INPUT);  mcp.pullUp(BUTTON3, HIGH);   mcp.pinMode(BUTTON4, INPUT);   mcp.pullUp(BUTTON4, HIGH);
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
    if (abs(xValue - 512) > threshold) pointX -= map(xValue, 0, 1023, -speed, speed);//chatgpt
    if (abs(yValue - 512) > threshold) pointY -= map(yValue, 0, 1023, -speed, speed);//chatgpt

    // Contraindre la position du point à l'intérieur des limites de l'écran
    pointX = constrain(pointX, Radius, tft.width() - Radius);//chatgpt
    pointY = constrain(pointY, Radius, tft.height() - Radius);//chatgpt

    drawPoint(oldX, oldY, ILI9341_BLACK);      // Effacer l'ancien point
    drawPoint(pointX, pointY, ILI9341_WHITE);  // Dessiner le nouveau point

    Time_ms = millis();
  }
  // Vérification si un bouton est pressé pour remettre le point au centre
  if (mcp.digitalRead(BUTTON1) == LOW) {

    pointX = tft.width() / 2;              // Réinitialiser la position X au centre
    pointY = tft.height() / 2;             // Réinitialiser la position Y au centre
    drawPoint(oldX, oldY, ILI9341_BLACK);  // Effacer l'ancien point
  }
}
void bouton_qui_bande(void)
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
  if (abs(ValeurJoystick - 512) > threshold) { //abs = chatgpt
    return map(ValeurJoystick, 0, 1023, -speed, speed);//return map = chatgpt
  } else {
    return 0;
  }
}
void cible_touche(void) {
  // Petit flash visuel
  for (int i = 0; i < 2; i++) {// refait le flash 2 fois puis bloque au dessus de 2 
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

  // rafraichi lors de la mise en score 
  tft.fillScreen(ILI9341_BLACK);
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
    tft.drawCircle(ancienne_position, 110, 5, ILI9341_BLACK);
  }

  // Dessine la nouvelle cible
  tft.drawCircle(position, 110, 5, ILI9341_PINK);

  // Mémorise la nouvelle position
  ancienne_position = position;
}

void tir_affichage(void) {
  static int meme_tire; //initialisée meme tire une seule fois, puis garde en mémoire tant que le programme tourne.
  unsigned long times = millis();
  // Si la position du tir a changé, efface l'ancien tir
  if (meme_tire != Pos_X || meme_tire == Pos_X) {
    times = millis();
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

  delay(10);
}

// Fonction pour générer une onde sinusoïdale et la stocker dans un buffer
// generateSine(AMPLITUDE, sine, WAV_SIZE);
void generateSine(int32_t amplitude, int32_t* buffer, uint16_t length) {
  // Boucle sur chaque point (échantillon) du buffer
  for (int i = 0; i < length; ++i) {
    // Calcule la valeur de l'onde sinusoïdale à cet échantillon
    // - 2π * (i / length) correspond à un angle de 0 à 2π (un tour complet)
    // - sin(...) donne une valeur entre -1 et +1
    // - on la multiplie par l'amplitude souhaitée pour ajuster le volume
    buffer[i] = int32_t(float(amplitude) * sin(2.0 * PI * (1.0 / length) * i));
  }
}

void generateSawtooth(int32_t amplitude, int32_t* buffer, uint16_t length) {
  // On veut créer une onde qui monte progressivement de -amplitude/2 à +amplitude/2
  // dans un tableau de 'length' points (échantillons).
  
  // Calcule l'incrément entre chaque point.
  // Exemple : si amplitude = 100, length = 10, alors delta = 10.
  //Le tableau buffer contiendra : [-20, -10, 0, 10, 20]
  float delta = float(amplitude) / float(length);

  // Remplit le tableau 'buffer' avec les valeurs de l'onde en dent de scie.
  for (int i = 0; i < length; ++i) {
    // Chaque valeur monte progressivement :
    // - Commence à -amplitude/2
    // - Puis ajoute delta à chaque tour
    buffer[i] = -(amplitude / 2) + delta * i;
  }
  //Le tableau buffer contiendra : [-20, -10, 0, 10, 20]
}

void generateTriangle(int32_t amplitude, int32_t* buffer, uint16_t length) {
  // Cette fonction génère une onde triangulaire dans un tableau "buffer"
  // L'onde triangulaire monte puis descend linéairement.

  // On calcule delta, c’est-à-dire de combien la valeur change à chaque point.
  float delta = float(amplitude) / float(length);

  // Première moitié du signal : on part de -amplitude/2 et on monte jusqu'à +amplitude/2
  for (int i = 0; i < length / 2; ++i) {
    buffer[i] = -(amplitude / 2) + delta * i;
  }

  // Deuxième moitié du signal : on redescend de +amplitude/2 jusqu’à -amplitude/2
  for (int i = length / 2; i < length; ++i) {
    buffer[i] = (amplitude / 2) - delta * (i - length / 2);
  }
  //Exemple (amplitude = 100, length = 8) =[-50, -37, -25, -12,  37,  25,  12,  0] ← (approximation)
}

void generateSquare(int32_t amplitude, int32_t* buffer, uint16_t length) {
  // Cette fonction génère une onde carrée dans un tableau "buffer"
  // Une onde carrée alterne entre une valeur haute et une valeur basse.

  // Première moitié : on remplit la moitié du buffer avec -amplitude/2 (valeur basse)
  for (int i = 0; i < length / 2; ++i) {
    buffer[i] = -(amplitude / 2);
  }

  // Deuxième moitié : on remplit le reste du buffer avec +amplitude/2 (valeur haute)
  for (int i = length / 2; i < length; ++i) {
    buffer[i] = (amplitude / 2);
  }
  // Si amplitude = 100 et length = 8, alors buffer contient =[-50, -50, -50, -50, 50, 50, 50, 50]
}

//playWave(square, 256, 440.0, 0.5);
void playWave(int32_t* buffer, uint16_t length, float frequency, float seconds) {
  // Cette fonction joue une forme d'onde (stockée dans buffer)
  // pendant une durée donnée, à une certaine fréquence.

  // Calcul du nombre d'échantillons à générer (durée * fréquence d'échantillonnage)
  uint32_t iterations = seconds * SAMPLERATE_HZ;

  // Calcul du delta de lecture dans le buffer pour obtenir la bonne fréquence
  float delta = (frequency * length) / float(SAMPLERATE_HZ);

  // Boucle principale pour envoyer les échantillons
  for (uint32_t i = 0; i < iterations; ++i) {
    // Calcul de la position actuelle dans le buffer, avec boucle (modulo)
    //Quand i augmente, i * delta pointe sur la prochaine position dans l'onde.
    //Le % length garantit qu'on boucle dans le tableau (buffer[0 → length-1] → 0 à nouveau), donc le son est périodique.
    uint16_t pos = uint32_t(i * delta) % length;

    // Récupération de l'échantillon à cette position
    int32_t sample = buffer[pos];

    // Écriture du même échantillon sur les deux canaux (gauche et droite)
    i2s.write(sample, sample);
  }
}

void son(void) {
  // Configure le port série pour permettre l'affichage de messages dans le moniteur série.
  Serial.begin(9600);  // Vitesse de communication série : 9600 bauds
  Serial.println("Zero I2S Audio Tone Generator");  // Message de démarrage

  // Initialise le module I2S pour transmettre de l’audio.
  // Format : 32 bits par échantillon, fréquence d’échantillonnage définie par SAMPLERATE_HZ (44100 Hz).
  if (!i2s.begin(I2S_32_BIT, SAMPLERATE_HZ)) {
    // Si l'initialisation échoue, afficher un message d'erreur et arrêter le programme avec une boucle infinie.
    Serial.println("Failed to initialize I2S transmitter!");
    while (1);  // Boucle infinie pour bloquer l'exécution
  }

  // Active la transmission sur la sortie I2S.
  i2s.enableTx();

  // Génère toutes les formes d’onde de base et les stocke en mémoire dans leurs buffers respectifs.
  generateSine(AMPLITUDE, sine, WAV_SIZE);         // Onde sinusoïdale
  generateSawtooth(AMPLITUDE, sawtooth, WAV_SIZE); // Onde en dent de scie
  generateTriangle(AMPLITUDE, triangle, WAV_SIZE); // Onde triangulaire
  generateSquare(AMPLITUDE, square, WAV_SIZE);     // Onde carrée
}

void tetris_them(void) {
  // Affiche dans le moniteur série que la mélodie commence
  Serial.println("Tetris theme");

  // Boucle à travers toutes les notes de la mélodie Tetris
  for (int i = 0; i < sizeof(tetris_theme) / sizeof(float); i++) {
    
    // Si la note est différente de 0.0, on la joue (0.0 est utilisé ici comme silence)
    if (tetris_theme[i] > 0.0f) {
      playWave(square, WAV_SIZE, tetris_theme[i], tetris_durations[i]);  // Joue la note avec l'onde carrée
    } else {
      delay(tetris_durations[i] * 1000);  // Sinon on fait une pause (durée en secondes → multipliée par 1000 pour obtenir des millisecondes)
    }
  }
}







