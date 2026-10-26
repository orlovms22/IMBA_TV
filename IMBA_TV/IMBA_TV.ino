#include <Adafruit_TinyUSB.h>
#include "utils.h"
#include "battery.h"
#include "ble.h"
#include "display.h"
#include "idle_off.h"

static const uint8_t brightness = 150;
static const bool flip_display = false;
static const uint32_t idle_off_timeout = 0; //s
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
    idleOffSetTimeout(idle_off_timeout);

    displayDrawLogo();
    delay(1000);
}

void shutdownNow()
{
    displayOff();
    powerOff();
    systemOff();
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
        shutdownNow();
    }

    euc_data_t& data = bleGetEucData();

    if(idleOffUpdate(data.is_connected))
    {
        shutdownNow();
    }

    displayDrawIface(batteryGetCharge(), usb_connected, data);
    displayUpdateAlarm(data);

    delay(update_period);
}
