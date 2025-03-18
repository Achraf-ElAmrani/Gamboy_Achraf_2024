// Programation console
// Ahraf El Amrani
// 6TQA-INRACI
// Feather M0 Express - 8-bit Expander, Ecran ILI9341 - Joystick - Module son
// 08.03.2025

#include "console.h"
int cpt = 0;

void setup() {
  Serial.begin(9600);
  InitialisationEcran();
  InitialisationButton();
  Menu();
  
  while (Mode == 0) {
      if (mcp.digitalRead(BUTTON1) == LOW) Mode = MODE_POINT;
      if (mcp.digitalRead(BUTTON2) == LOW) Mode = MODE_INVADERS;
  }
    
  tft.fillScreen(ILI9341_BLACK);

  Time_ms = millis();

  if (Mode == MODE_POINT) {
      tft.setCursor(50, 100);
      tft.println("Mode: Point");
  } else if (Mode == MODE_INVADERS) {
      tft.setCursor(50, 100);
      tft.println("Mode: Invaders");
  }
}

void loop() {
 if (Mode == MODE_POINT) {
     if (millis() >= Time_ms + 1000) {
      pointX = tft.width() / 2;
      pointY = tft.height() / 2;
     }
      MettreAJourPosition();
}else if (Mode == MODE_INVADERS) {
        //mode Space Invaders
    }

}