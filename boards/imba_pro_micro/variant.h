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

#ifndef _VARIANT_IMBA_PRO_MICRO_
#define _VARIANT_IMBA_PRO_MICRO_

#define _PINNUM(port, pin)    ((port)*32 + (pin))

/** Master clock frequency */
#define VARIANT_MCK       (64000000ul)

#define USE_LFXO      // Board uses 32khz crystal for LF
// define USE_LFRC    // Board uses RC for LF

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "WVariant.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

// Number of pins defined in PinDescription array
#define PINS_COUNT           (25)
#define NUM_DIGITAL_PINS     (25)
#define NUM_ANALOG_INPUTS    (4)
#define NUM_ANALOG_OUTPUTS   (0)

#define LED_STATE_ON 1

// LEDs
#define PIN_LED              (17)

#define LED_BUILTIN          PIN_LED
#define LED_BLUE             (24)

/*
 * Analog pins
 */
#define PIN_A0               (19)
#define PIN_A2               (23)
#define PIN_A5               (20)
#define PIN_A7               (21)

static const uint8_t A0  = PIN_A0 ;
static const uint8_t A2  = PIN_A2 ;
static const uint8_t A5  = PIN_A5 ;
static const uint8_t A7  = PIN_A7 ;
#define ADC_RESOLUTION    12

// Other pins
#define PIN_VBAT           PIN_A2
#define PIN_PWREN            (22)

/*
 * Serial interfaces
 */
#define PIN_SERIAL1_RX       (1)
#define PIN_SERIAL1_TX       (0)

/*
 * Wire Interfaces
 */
#define WIRE_INTERFACES_COUNT 1

#define PIN_WIRE_SDA         (20)
#define PIN_WIRE_SCL         (21)

/*
 * SPI Interfaces
 */
#define SPI_INTERFACES_COUNT 1

#define PIN_SPI_MISO         (2)
#define PIN_SPI_MOSI         (3)
#define PIN_SPI_SCK          (4)

static const uint8_t SS   = (5);
static const uint8_t MOSI = PIN_SPI_MOSI ;
static const uint8_t MISO = PIN_SPI_MISO ;
static const uint8_t SCK  = PIN_SPI_SCK ;

#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#endif
