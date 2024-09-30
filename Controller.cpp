#include "Controller.h"

Controller::Controller() : pump(7), deviceController(pump, manager.getSoilMoistureSensor(), manager.getSoilMoistureSensor())
{

}

void Controller::initDevice()
{
  Serial.begin(115200);

  pump.init();
  manager.initSensors();

  manager.getSoilMoistureSensor().getItsStrategy().setTresholds(40, 75);
  manager.getTemperatureSensor().getItsStrategy().setTresholds(25, 30);

  logger.addSensor("temperature", &manager.getTemperatureSensor());
  logger.addSensor("pressure", &manager.getPressureSensor());
  logger.addSensor("soil moisture", &manager.getSoilMoistureSensor());
}

void Controller::run()
{
  deviceController.run();
  static Timer logTimer(5000, [this]()
  {
    logger.printAllValues();
  });
  delay(50);
}

void addLoggingTimer()
{

}
