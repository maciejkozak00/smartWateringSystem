#include "Controller.h"
#include "PrivateDefinitions.h"

Controller::Controller() : mqttPublisher(mqttMessageHandler), manager(mqttPublisher), pump(PUMP_PIN), deviceController(pump, manager.getSoilMoistureSensor(), manager.getSoilMoistureSensor())
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
  mqttMessageHandler.attach(&deviceController);
  mqttMessageHandler.attach(&manager);
  
  mqttPublisher.publish("garden/temperature", std::to_string(manager.getTemperatureSensor().readValue()));
  mqttPublisher.publish("garden/pressure", std::to_string(manager.getPressureSensor().readValue()));
  mqttPublisher.publish("garden/soilMoisure", std::to_string(manager.getSoilMoistureSensor().readValue()));
}

void Controller::run()
{
  static Timer logTimer(15000, [this](){
    logger.printAllValues();
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
// mqttPublisher.attach(std::make_shared<IMqttMessageObserver>(deviceController));