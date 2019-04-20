#include <Arduino.h>
#include "SmogDetector.hpp"
#include "settings.h"

SmogDetector smogDetector;

void setup(void)
{ 
  smogDetector.Initialize();
}

void loop(void)
{
  smogDetector.Loop();
}
