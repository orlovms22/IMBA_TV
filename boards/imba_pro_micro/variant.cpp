/*
  Copyright (c) 2014-2015 Arduino LLC.  All right reserved.
  Copyright (c) 2016 Sandeep Mistry All right reserved.
  Copyright (c) 2018, Adafruit Industries (adafruit.com)
  Copyright (c) 2026 orlovms22

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "variant.h"
#include "wiring_constants.h"
#include "wiring_digital.h"
#include "nrf.h"

const uint32_t g_ADigitalPinMap[] =
{
  // D0 .. D13
  _PINNUM(0, 8),   // D0  is P0.08 (UART TX)
  _PINNUM(0, 6),   // D1  is P0.06 (UART RX)
  _PINNUM(0, 17),  // D2  is P0.17
  _PINNUM(0, 20),  // D3  is P0.20
  _PINNUM(0, 22),  // D4  is P0.22
  _PINNUM(0, 24),  // D5  is P0.24
  _PINNUM(1, 0),   // D6  is P1.00
  _PINNUM(0, 11),  // D7  is P0.11
  _PINNUM(1, 4),   // D8  is P1.04
  _PINNUM(1, 6),   // D9  is P1.06
  _PINNUM(0, 9),   // D10 is P0.09
  _PINNUM(1, 1),   // D11 is P1.01
  _PINNUM(1, 2),   // D12 is P1.02
  _PINNUM(1, 7),   // D13 is P1.07

  // D14 .. D21
  _PINNUM(1, 11),  // D14 is P1.11
  _PINNUM(1, 13),  // D15 is P1.13
  _PINNUM(0, 10),  // D16 is P0.10
  _PINNUM(0, 15),  // D17 is P0.15 (BUILTIN LEDs)
  _PINNUM(1, 15),  // D18 is P1.15
  _PINNUM(0, 2),   // D19 is P0.02 (A0)
  _PINNUM(0, 29),  // D20 is P0.29 (A5)
  _PINNUM(0, 31),  // D21 is P0.31 (A7)

  // D22 .. D24
  _PINNUM(0, 13),  // D22 is P0.13 (PWR EN)
  _PINNUM(0, 4),   // D23 is P0.04 (A2, VBAT)
  _PINNUM(0, 27),  // D24 is P0.27 (phantom pin for LED_BLUE)
};

void initVariant()
{
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  pinMode(PIN_PWREN, OUTPUT);
  digitalWrite(PIN_PWREN, LOW);
}

