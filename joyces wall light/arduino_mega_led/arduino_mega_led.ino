#include <Adafruit_NeoPixel.h>

#define PIN            6   // LED şeridinin bağlı olduğu data pini
#define NUMPIXELS      26  // Alfabedeki harf sayısı (A-Z)

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600); // Python ile aynı baud rate olmalı
  pixels.begin();
  pixels.clear();
  pixels.show();
}

void loop() {
  if (Serial.available() > 0) {
    // Python'dan gelen karakteri oku
    char letter = Serial.read();
    
    // Harfi 0-25 arası bir indexe çevir (A=0, B=1...)
    int index = -1;
    if (letter >= 'A' && letter <= 'Z') {
      index = letter - 'A';
    } else if (letter >= 'a' && letter <= 'z') {
      index = letter - 'a';
    }

    if (index != -1) {
      pixels.clear(); // Diğerlerini söndür
      // Harfe özel renk ver (Örn: Parlak Beyaz/Sarı)
      pixels.setPixelColor(index, pixels.Color(255, 200, 50)); 
      pixels.show();
      delay(1000); // 1 saniye yanık kalsın
      pixels.clear();
      pixels.show();
    }
  }
}