// Pin tanımlamaları
const int yesilLed = 6;
const int maviLed = 4;
const int kirmiziLed = 5;

void setup() {
  Serial.begin(9600);
  pinMode(yesilLed, OUTPUT);
  pinMode(maviLed, OUTPUT);
  pinMode(kirmiziLed, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char komut = Serial.read();

    // Önce hepsini söndür (Sadece üzerine gelinen yansın diye)
    digitalWrite(yesilLed, LOW);
    digitalWrite(maviLed, LOW);
    digitalWrite(kirmiziLed, LOW);

    if (komut == 'G') digitalWrite(yesilLed, HIGH);
    else if (komut == 'B') digitalWrite(maviLed, HIGH);
    else if (komut == 'R') digitalWrite(kirmiziLed, HIGH);
    // 'X' gelirse hepsi sönük kalmaya devam eder
  }
}