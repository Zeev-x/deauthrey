#ifndef DEAUTH_H
#define DEAUTH_H

#include <Arduino.h>

void start_deauth(int wifi_number, int attack_type, uint16_t reason);
void enable_deauth();
void stop_deauth();
void deauth_loop();

extern int eliminated_stations;
extern int deauth_type;

#endif