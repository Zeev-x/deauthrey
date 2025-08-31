#include "deauth.h"
#include "definitions.h"
#include "lcd_display.h"

bool deauth_mode = false;
bool last_btn_state = LOW;

void btn_control() {
  int btn_state = digitalRead(BTN);
  if(btn_state == HIGH && last_btn_state == LOW) {
    deauth_mode = !deauth_mode;
    deauth_mode ? enable_deauth() : stop_deauth();
    delay(500); // Debounce delay
  }
  last_btn_state = btn_state;
}

void setup() {
  Serial.begin(115200);
  lcd_init();
  
  #ifdef LED
  pinMode(LED, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);
  #endif
}

void loop() {
  btn_control();
  deauth_loop();
}
