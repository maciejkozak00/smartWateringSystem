#include "Controller.h"

Controller::Controller() : pump(7), deviceController(pump, manager.getSoilMoistureSensor(), manager.getSoilMoistureSensor()), mqttPublisher(deviceController)
{

}

void Controller::initDevice()
{
  Serial.begin(115200);

  pump.init();
  manager.initSensors();
  Serial.println("Sensors initialized");
  manager.getSoilMoistureSensor().getItsStrategy();
  manager.getTemperatureSensor().getItsStrategy();
  Serial.println("Treshold strategies set");

  logger.addSensor("temperature", &manager.getTemperatureSensor());
  logger.addSensor("pressure", &manager.getPressureSensor());
  logger.addSensor("soil moisture", &manager.getSoilMoistureSensor());
  Serial.println("LoggerInitialized");

  mqttPublisher.init();
  mqttPublisher.publish("garden/temperature", std::to_string(manager.getTemperatureSensor().readValue()));
  mqttPublisher.publish("garden/pressure", std::to_string(manager.getPressureSensor().readValue()));
  mqttPublisher.publish("garden/soilMoisure", std::to_string(manager.getSoilMoistureSensor().readValue()));
}

void Controller::run()
{
  static Timer logTimer(15000, [this](){
    logger.printAllValues();
    mqttPublisher.publish("garden/temperature", std::to_string(manager.getTemperatureSensor().readValue()));
    mqttPublisher.publish("garden/pressure", std::to_string(manager.getPressureSensor().readValue()));
    mqttPublisher.publish("garden/soilMoisure", std::to_string(manager.getSoilMoistureSensor().readValue()));
  });

  static Timer deviceControllerTimer(15000, [this](){
    deviceController.run();
  });
  logTimer.hasElapsed();
  deviceControllerTimer.hasElapsed();
  delay(50);
  mqttPublisher.loop();
}

void addLoggingTimer()
{

}
