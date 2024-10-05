#include "Controller.h"

Controller controller;

void setup()
{
  controller.initDevice();
}

void loop()
{
  controller.run();
}
