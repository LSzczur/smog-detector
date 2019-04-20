#include <Arduino.h>
#include "SmogDetector.hpp"

SmogDetector smogDetector;

void setup(void)
{ 
  smogDetector.Initialize();
}

void loop(void)
{
  smogDetector.Loop();
}
