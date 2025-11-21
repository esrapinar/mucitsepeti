/*
  Öğretmenim Canım Benim - Arduino Melodisi

  Çıkış Pini: 8
  by esra pınar yusuf
*/

#define BUZZER_PIN 8

// Nota Frekansları (Do, Re, Mi...)
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784
#define NOTE_A5  880
#define REST      0

// Tempo ayarı (Değiştirerek hızı ayarlayabilirsiniz)
int tempo = 120;

// Melodi Dizisi (Notalar)
int melody[] = {
  // 1. Satır
  REST, NOTE_C5, NOTE_C5, NOTE_D5, NOTE_E5, // Es - doo - do-re-miii  öğ-ret-me-niiim
       
  REST, NOTE_E5, NOTE_F5, NOTE_E5,NOTE_D5, // es - MI - FAA - MI    canım benim
   NOTE_D5,NOTE_E5,NOTE_D5, NOTE_C5, // es - RE - MII - RE -Do   canım benim
   
    
  // 2. Satır
  REST, NOTE_D5, NOTE_E5, // RE - MI
  NOTE_F5, NOTE_G5, // FAA - SOLL
  NOTE_E5, NOTE_A5, // MII - LA
  NOTE_G5, NOTE_E5, NOTE_F5, NOTE_D5, // SOL - MI - FA - REE 

// 3. Satır
  REST,NOTE_D5, NOTE_D5, NOTE_E5, // REE - REE - MI
  NOTE_F5, REST, // FAA (Noktalı) - es
  NOTE_E5, NOTE_E5, // MII - MII
  NOTE_F5, NOTE_G5, // FA - SOLL (Noktalı)

  // 4. Satır
  NOTE_A5, NOTE_G5, // LAA - SOLL
  NOTE_D5, NOTE_E5, // REE - MII
  NOTE_F5, NOTE_E5, // FAA - MII
  NOTE_D5, NOTE_C5, // RE - doo
  REST // Bitiş es'i
};

// Ritim Dizisi (Süreler)
// 4 = Çeyrek vuruş, 8 = Sekizlik vuruş
// Negatif sayılar (örn: -4) noktalı vuruş anlamına gelir (daha uzun)
int noteDurations[] = {
  // 1. Satır
  4, 4, -8,  8, -8,     // Es(Çeyrek), Do(8), Do(8), Re(8), Mi(Noktalı Çeyrek)
       // 
  8, 8, -8,8 , -8,  // Es(8), Mi(8), Fa(8), Mi(8), Re(8)
    8 ,-8,8,-8 ,// Es(8), Re(8), Mi(8), Re(8) - Do (
    

  // 2. Satır
  8, 8, 8,        // Re, Mi
  4, 4,        // Fa, Sol
  4, 8,        // Mi, La
  8, 8, 8, -4, // Sol(8), Mi(8), Fa(8), Re(Noktalı Çeyrek)

  // 3. Satır
 8, 4, 8, 8,     // Re(Çeyrek), Re(8), Mi(8)
  -4, 8,       // Fa(Noktalı Çeyrek), Es(8)
  4, 4,        // Mi, Mi
  8, -4,       // Fa(8), Sol(Noktalı Çeyrek)

  // 4. Satır
  4, 4,        // La, Sol
  4, 4,        // Re, Mi
  4, 4,        // Fa, Mi
  8, 8,        // Re, Do
  2            // Son Es*/
};

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Melodideki toplam nota sayısını hesapla
  int size = sizeof(melody) / sizeof(int);

  // Melodiyi çal
  for (int thisNote = 0; thisNote < size; thisNote++) {

    // Nota süresini hesapla
    int noteDuration = 0;
    int divider = noteDurations[thisNote];
    
    if (divider > 0) {
      // Normal nota (örneğin 4, 8)
      noteDuration = (60000 * 4) / tempo / divider;
    } else if (divider < 0) {
      // Noktalı nota (örneğin -4, -8)
      noteDuration = (60000 * 4) / tempo / abs(divider);
      noteDuration *= 1.5; // Süreyi 1.5 katına çıkar
    }

    // Notayı çal
    // %90 süreyle çalıp %10 susuyoruz ki notalar birbirine karışmasın
    tone(BUZZER_PIN, melody[thisNote], noteDuration * 0.9);

    // Bir sonraki notaya geçmeden önce bekle
    delay(noteDuration);
    
    // Sesi durdur (Notalar arası net geçiş için)
    noTone(BUZZER_PIN);
  }
}

void loop() {
  // Şarkı bitti, loop boş bırakıldı.
  // Tekrar çalmasını isterseniz yukarıdaki for döngüsünü buraya taşıyabilirsiniz.
}
