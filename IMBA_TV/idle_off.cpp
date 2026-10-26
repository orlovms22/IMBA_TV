#include "idle_off.h"
#include <Arduino.h>

static uint32_t timeout = 0; // s
static uint32_t disconnect_since = 0;

void idleOffSetTimeout(uint32_t val)
{
  timeout = val;
}

bool idleOffUpdate(bool is_connected)
{
  if(timeout && !is_connected)
  {
    uint32_t now = millis();
    if(disconnect_since == 0)
    {
      disconnect_since = now;
    }
    else if(now - disconnect_since > timeout * 1000UL)
    {
      return true;
    }
  }
  else
  {
    disconnect_since = 0;
  }

  return false;
}