import cv2
import numpy as np
import serial
import math

# Arduino bağlantısı (Portu kontrol et: 'COM3', 'COM4' vb.)
try:
    arduino = serial.Serial('COM3', 9600)
    print("Arduino Baglandi!")
except:
    print("Arduino'ya baglanilamadi! Portu kontrol edin.")
    arduino = None

# Ekran ayarları
width, height = 800, 400
canvas = np.zeros((height, width, 3), dtype="uint8")

# YENI SIRA: R - G - B (Soldan Sağa)
centers = {
    "R": (200, 200), # Kırmızı Top (Solda)
    "G": (400, 200), # Yeşil Top (Ortada)
    "B": (600, 200)  # Mavi Top (Sağda)
}
colors = {"R": (0, 0, 255), "G": (0, 255, 0), "B": (255, 0, 0)}
radius = 60

last_sent = 'X' # Gereksiz veri trafiğini önlemek için son gönderilen harf

def check_mouse(event, x, y, flags, param):
    global arduino, last_sent
    active_color = 'X' 
    
    for key, center in centers.items():
        # Fare ile merkez arasındaki mesafeyi hesapla
        dist = math.sqrt((x - center[0])**2 + (y - center[1])**2)
        if dist < radius:
            active_color = key
            break
    
    # Sadece renk değiştiğinde Arduino'ya gönder
    if active_color != last_sent:
        if arduino:
            arduino.write(active_color.encode())
            print(f"Gonderilen Komut: {active_color}")
        last_sent = active_color

# Pencere oluştur ve fare takibini başlat
cv2.namedWindow("Renk Kontrol Paneli")
cv2.setMouseCallback("Renk Kontrol Paneli", check_mouse)

while True:
    temp_img = canvas.copy()
    
    # Topları çiz
    for key, center in centers.items():
        cv2.circle(temp_img, center, radius, colors[key], -1)
        # Harf etiketi ekle
        cv2.putText(temp_img, key, (center[0]-10, center[1]+10), 
                    cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2)

    cv2.imshow("Renk Kontrol Paneli", temp_img)
    
    # 'q' tuşuna basınca çık
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cv2.destroyAllWindows()
if arduino: 
    arduino.write(b'X') # Kapatırken tüm LED'leri söndür
    arduino.close()