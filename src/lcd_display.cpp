#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "lcd_display.h"
#include "definitions.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // Tidak digunakan di I2C

// Gunakan alamat I2C OLED Anda (biasanya 0x3C)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void centeredText(const String& text, int y, uint8_t textSize = 1) {
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(textSize);
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(text, 0, y, &x1, &y1, &w, &h);
  int x = (SCREEN_WIDTH - w) / 2;
  display.setCursor(x, y);
  display.print(text);
}

void typewriterText(const String& text, int y, uint8_t textSize = 1, int delayPerChar = 50) {
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(textSize);

  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(text, 0, y, &x1, &y1, &w, &h);
  int x = (SCREEN_WIDTH - w) / 2;

  display.setCursor(x, y);
  for (int i = 0; i < text.length(); i++) {
    display.print(text[i]);
    display.display(); // tampilkan setiap karakter
    delay(delayPerChar);
  }
}

void lcd_conf() {
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
}

void lcd_init() {
    lcd_conf();
    typewriterText("Reyette-Projects", 0, 1, 150);
    delay(100);
    typewriterText("ESP32", 16, 4, 500);
    delay(100);
    typewriterText("Deauther v1.0", 50, 1, 150);
    display.display();
}

void lcd_show_status(const char* message) {
    display.fillRect(0, 16, SCREEN_WIDTH, 16, SSD1306_BLACK); // Bersihkan area status
    display.setCursor(0, 16);
    display.print(message);
    display.display();
}
