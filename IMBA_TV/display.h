#pragma once
#include <stdint.h>
#include "euc_data.h"

void displayInit();
void displayOff();
void displaySetBrightness(uint8_t val);
void displaySetFlip(bool st);
void displayDrawLogo();
void displayDrawIface(uint8_t dev_charge, bool is_charging, euc_data_t& data);
void displayUpdateAlarm(euc_data_t& data);
