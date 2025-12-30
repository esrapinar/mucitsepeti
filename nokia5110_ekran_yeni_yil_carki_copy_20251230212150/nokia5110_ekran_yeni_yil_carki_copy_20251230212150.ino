#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Senin referans kodundaki pinler
Adafruit_PCD8544 display = Adafruit_PCD8544(13, 11, 10, 9, 8);

const int buttonPin = 2; 
const int buzzerPin = 3; 

const char* dilekler[] = {
  "MUTLULUK", "SAGLIK", "BOL PARA", "YENI EV", 
  "YENI IS", "BEREKET", "HUZUR", "ASK",
  "DUNYA TURU", "IKRAMIYE", "BASARI", "SANS",
  "PIYANGO", "MUCIZE", "SIFIR BORC", "LUKS TATIL", "YENI ARABA"
};
const int dilekSayisi = 17;

int mevcutSira = 0; // Sıralı dönme için
bool butonBasildi = false;

// Jingle Bells Giriş Notaları
int melody[] = { 330, 330, 330, 330, 330, 330, 330, 392, 262, 294, 330 };
int noteDurations[] = { 4, 4, 2, 4, 4, 2, 4, 4, 4, 4, 1 };

void setup() {
  display.begin();
  display.setContrast(40); 
  display.clearDisplay();
  
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  randomSeed(analogRead(0)); // Gerçek rastgelelik için boş pin oku
}

void jingleBellsGiris() {
  for (int thisNote = 0; thisNote < 11; thisNote++) {
    int noteDuration = 600 / noteDurations[thisNote];
    tone(buzzerPin, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(buzzerPin);
  }
}

void loop() {
  if (!butonBasildi) {
    // 1. AŞAMA: Dilekler sırayla döner (Görsel akış için)
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(BLACK);
    
    // Kelimeyi ortala
    int xPos = (84 - (strlen(dilekler[mevcutSira]) * 6)) / 2;
    display.setCursor(max(0, xPos), 20);
    display.print(dilekler[mevcutSira]);
    display.display();
    
    // Buton kontrolü (0.3 saniyelik bekleme sırasında butonu yakala)
    unsigned long startMillis = millis();
    while (millis() - startMillis < 500) { 
      if (digitalRead(buttonPin) == HIGH) {
        butonBasildi = true;
        
        // 2. AŞAMA: Butona basıldığı an RASTGELE bir dilek seçilir
        int rastgeleIndis = random(0, dilekSayisi);
        sonucuGoster(dilekler[rastgeleIndis]);
        break;
      }
    }
    
    // Sırayı bir sonraki dileğe geçir
    mevcutSira++;
    if (mevcutSira >= dilekSayisi) {
      mevcutSira = 0;
    }
  }
}

void sonucuGoster(const char* secilen) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(5, 5);
  display.print("2026'DA SANA:");
  
  // Seçilen rastgele dileği göster
  int xPos = (84 - (strlen(secilen) * 6)) / 2;
  display.setCursor(max(0, xPos), 25);
  display.print(secilen);
  display.display();
  
  // Jingle Bells başlar
  jingleBellsGiris();
  
  delay(1500); // Müzik bittikten sonra biraz daha bekle

  // 3. AŞAMA: Kar efekti ve Mutlu Yıllar
  for (int f = 0; f < 35; f++) {
    display.clearDisplay();
    for (int j = 0; j < 20; j++) {
      display.drawPixel(random(0, 84), random(0, 48), BLACK);
    }
    display.setCursor(5, 20);
    display.print("MUTLU YILLAR!");
    display.display();
    delay(80);
  }
  
  butonBasildi = false; // Döngüyü tekrar başlat
}