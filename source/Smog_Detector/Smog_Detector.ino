#include <Arduino.h>
#include "SmogDetector.hpp"

SmogDetector smogDetector;

void setup(void)
{
  smogDetector.Initialize();
}

void loop(void)
{
  // Pmsx003::PmsStatus status = updateData();
  // if (Pmsx003::OK == status)
  // {
  //   updateDisplay();
  // }
  // server.handleClient();
}

