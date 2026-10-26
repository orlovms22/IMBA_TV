#include "display.h"
#include "GyverOLED.h"
#include "logo.h"

static const uint32_t blink_period_low = 1000; //ms
static const uint32_t blink_period_high = 300; //ms
static const uint32_t blink_length = 50; //ms

static GyverOLED<SSH1106_128x64> oled;

void displayInit()
{
  oled.init();
  Wire.setClock(400000);
}

void displayOff()
{
  Wire.end();
  pinMode(PIN_WIRE_SCL, INPUT);
  pinMode(PIN_WIRE_SDA, INPUT);
}

void displaySetBrightness(uint8_t val)
{
  oled.setContrast(val);
}

void displaySetFlip(bool st)
{
  oled.flipH(st);
  oled.flipV(st);
}

void displayDrawLogo()
{
  oled.clear();
  oled.drawBitmap(logo_x, logo_y, logo_bitmap, logo_width, logo_height);
  oled.update();
}

static const uint8_t charging_bitmap[] = {
  0xff, 0x81, 0xb1, 0x99, 0x8d, 0x9d, 0xb9, 0xb1, 0x99, 0x8d, 0x81, 0xff, 0x3c, 0x3c
};

static void drawDevCharge(int x, int y, uint8_t charge, bool is_charging)
{
  charge = constrain(charge, 0, 100);

  if(is_charging)
  {
    oled.drawBitmap(x, y, charging_bitmap, 14, 8);
  }
  else
  {
    oled.setCursorXY(x, y);

    oled.drawByte(0xFF);

    uint8_t level = charge / 10;
    for(uint8_t i = 0; i < 10; i++)
    {
      if(i < level) oled.drawByte(0xFF);
      else oled.drawByte(0x81);
    }

    oled.drawByte(0xFF);
    oled.drawByte(0x3C);
    oled.drawByte(0x3C);
  }

  oled.setCursorXY(x + 17, y);
  oled.setScale(1);
  oled.print(charge);
  oled.print("%");
}

static void drawEucCharge(int x, int y, uint8_t charge)
{
  charge = constrain(charge, 0, 100);

  oled.setCursorXY(x, y);

  oled.drawByte(0xFF);

  uint8_t level = charge / 4;
  for(uint8_t i = 0; i < 25; i++)
  {
    if(i < level)
    {
      oled.drawByte(0x81);
      oled.drawByte(0xFF);
    }
    else
    {
      oled.drawByte(0x81);
      oled.drawByte(0x81);
    }
  }

  oled.drawByte(0xFF);
  oled.drawByte(0x3C);
  oled.drawByte(0x3C);

  oled.setCursorXY(x + 57, y);
  oled.setScale(1);
  oled.print(charge);
  oled.print("%");
}

static int cntDigits(uint16_t val)
{
  if(val == 0) return 1;

  int cnt = 0;
  while(val != 0)
  {
    val /= 10;
    ++cnt;
  }
  return cnt;
}

static void drawEucSpeed(int x, int y, uint16_t speed)
{
  speed = constrain(speed, 0, 999);

  oled.setCursorXY(x + 11, y);
  oled.setScale(1);
  oled.print("скорость");

  int digits = cntDigits(speed);
  oled.setCursorXY(x + (3 - digits) * 12, y + 16);
  oled.setScale(4);
  oled.print(speed);
}

static void drawEucPwm(int x, int y, uint8_t pwm)
{
  pwm = pwm % 100;

  oled.setCursorXY(x + 14, y);
  oled.setScale(1);
  oled.print("ШИМ");

  int digits = cntDigits(pwm);
  oled.setCursorXY(x + (2 - digits) * 12, y + 16);
  oled.setScale(4);
  oled.print(pwm);
}

void displayDrawIface(uint8_t dev_charge, bool is_charging, euc_data_t& data)
{
  oled.clear();
  drawDevCharge(0, 1, dev_charge, is_charging);
  if(data.is_connected)
  {
    drawEucCharge(47, 1, data.charge);
    drawEucSpeed(0, 16, data.speed);
    drawEucPwm(80, 16, data.pwm);
  }
  else
  {
    oled.setCursor(10, 3);
    oled.setScale(2);
    oled.print("нет связи");
  }
  oled.update();
}

void displayUpdateAlarm(euc_data_t& data)
{
  static uint32_t blink_prev = 0;
  static bool inverted = 0;
  uint32_t time = millis();

  if(data.pwm >= data.pwm_limit)
  {
    uint32_t period = map(data.pwm, data.pwm_limit, 100,
      blink_period_low, blink_period_high);

    if((time - blink_prev) > period)
    {
      blink_prev = time;
      inverted = true;
      oled.invertDisplay(true);
    }
  }

  if(inverted && (time - blink_prev) > blink_length)
  {
    inverted = false;
    oled.invertDisplay(false);
  }
}
