#include "battery.h"
#include <Arduino.h>

static const uint16_t volt_critical = 3000; //mV
static const uint16_t volt_low = 3100; //mV
static const uint16_t volt_high = 4150; //mV
static const uint16_t volt_step = 50; //mV
static const uint8_t soc_table[22] = {0, 2, 4, 7, 11, 16, 22, 29, 37, 45, 53, 60, 67, 73, 78, 82, 86, 89, 92, 95, 97, 100};

static float adc_filt = 0.0f;
static uint16_t volt = 0; //mV

void batteryInit()
{
  analogReference(AR_INTERNAL_1_2);
  analogSampleTime(40);
  adc_filt = analogReadVDDHDIV5();
  batteryUpdate();
}

void batteryUpdate()
{
  uint16_t adc = analogReadVDDHDIV5();
  adc_filt += ((float)adc - adc_filt) * 0.01f;
  volt = adc_filt * (5.0f * 1200.0f / 1024.0f);
}

bool batteryIsChargeCritical()
{
  return volt < volt_critical;
}

uint8_t batteryGetCharge()
{
  if(volt < volt_low) return 0;
  if(volt >= volt_high) return 100;

  uint8_t idx = (volt - volt_low) / volt_step;
  uint16_t offset = (volt - volt_low) % volt_step;
  uint8_t delta = ((soc_table[idx + 1] - soc_table[idx]) * offset) / volt_step;

  return soc_table[idx] + delta;
}
