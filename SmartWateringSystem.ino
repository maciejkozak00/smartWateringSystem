#include "Controller.h"

Controller controller;

void setup() {
  // put your setup code here, to run once:
  controller.initDevice();
}

void loop() {
  // put your main code here, to run repeatedly:
  controller.run();
}
