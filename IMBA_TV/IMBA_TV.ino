#include <Adafruit_TinyUSB.h>
#include "utils.h"
#include "battery.h"
#include "ble.h"
#include "display.h"

static const uint8_t brightness = 150;
static const bool flip_display = false;
static const uint32_t update_period = 40; //ms

void setup()
{
    softDeviceInit();

    buttonInitSense();
    usbDetectEnable();
    batteryInit();

    if(isUsbWakeup())
    {
        if(!isUsbConnected()) systemOff();
    }
    else
    {
        if(batteryIsChargeCritical())
        {
            buttonInitNoSense();
            systemOff();
        }

        if(!buttonWaitPowerup()) systemOff();
    }

    bleInit();
    bleAdvertise();

    powerOn();
    delay(100);
    displayInit();
    displaySetBrightness(brightness);
    displaySetFlip(flip_display);

    displayDrawLogo();
    delay(1000);
}

void loop()
{
    if(buttonIsLongPress())
    {
        displayOff();
        powerOff();
        buttonWaitRelease();
        systemOff();
    }

    bool usb_connected = isUsbConnected();

    batteryUpdate();
    if(batteryIsChargeCritical() && !usb_connected)
    {
        buttonInitNoSense();
        displayOff();
        powerOff();
        systemOff();
    }

    euc_data_t& data = bleGetEucData();
    displayDrawIface(batteryGetCharge(), usb_connected, data);
    displayUpdateAlarm(data);

    delay(update_period);
}
