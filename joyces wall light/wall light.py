import pygame
import serial
import time
import sys

# --- ARDUINO BAĞLANTISI ---
try:
    arduino = serial.Serial('COM12', 9600, timeout=1) 
    time.sleep(2)
except:
    arduino = None
    print("Arduino bağlı değil, sadece simülasyon çalışıyor.")

# GÜNCEL PIN LİSTESİ
char_to_pin = {
    'A': 2, 'B': 3, 'C': 4, 'D': 5, 'E': 6, 'F': 7, 'G': 8, 'H': 9, 'I': 10,
    'J': 11, 'K': 12, 'L': 13, 'M': 14, 'N': 15, 'O': 16, 'P': 17, 'Q': 18, 'R': 19,
    'S': 20, 'T': 21, 'U': 26, 'V': 28, 'W': 22, 'X': 23, 'Y': 24, 'Z': 25
}

pygame.init()
img = pygame.image.load('walllight2.jpg')
w, h = img.get_width(), img.get_height()
screen = pygame.display.set_mode((w, h))

def send(char):
    pin = char_to_pin.get(char)
    if pin and arduino:
        arduino.write(f"{pin}\n".encode())
    print(f"Tıklanan Harf: {char} | Gönderilen Pin: {pin}")

running = True
while running:
    screen.blit(img, (0, 0))
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        
        if event.type == pygame.MOUSEBUTTONDOWN:
            mx, my = event.pos
            
            # 1. SATIR (A - I) - H ve I için özel bölge
            if my < h * 0.33:
                if mx > w * 0.88: # En sağ köşe
                    send('I')
                elif mx > w * 0.75: # I'dan bir önceki boşluklu alan
                    send('H')
                else:
                    idx = int(mx / (w * 0.75 / 7)) # A-G arasını 7'ye böl
                    chars = "ABCDEFG"
                    if idx < len(chars): send(chars[idx])
            
            # 2. SATIR (J - R)
            elif h * 0.33 <= my < h * 0.66:
                idx = int(mx / (w / 9))
                chars = "JKLMNOPQR"
                if idx < len(chars): send(chars[idx])
            
            # 3. SATIR (S - Z)
            else:
                idx = int(mx / (w / 8))
                chars = "STUVWXYZ"
                if idx < len(chars): send(chars[idx])

    pygame.display.flip()

pygame.quit()