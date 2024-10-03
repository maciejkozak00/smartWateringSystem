#include "Controller.h"

Controller::Controller() : pump(7), deviceController(pump, manager.getSoilMoistureSensor(), manager.getSoilMoistureSensor())
{

}

void Controller::initDevice()
{
  Serial.begin(115200);

  pump.init();
  manager.initSensors();
  Serial.println("Sensors initialized");
  manager.getSoilMoistureSensor().getItsStrategy().setTresholds(40, 75);
  manager.getTemperatureSensor().getItsStrategy().setTresholds(25, 30);
  Serial.println("Treshold strategies set");

  logger.addSensor("temperature", &manager.getTemperatureSensor());
  logger.addSensor("pressure", &manager.getPressureSensor());
  logger.addSensor("soil moisture", &manager.getSoilMoistureSensor());
  Serial.println("LoggerInitialized");
}

void Controller::run()
{
  static Timer logTimer(5000, [this](){
    logger.printAllValues();
  });

  static Timer deviceControllerTimer(5000, [this](){
    deviceController.run();
  });
  logTimer.hasElapsed();
  deviceControllerTimer.hasElapsed();
  delay(50);
}

void addLoggingTimer()
{

}
